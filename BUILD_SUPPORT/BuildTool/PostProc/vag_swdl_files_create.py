# -*- coding: iso-8859-1 -*-

# #####################################################################################################################
#  FILE DESCRIPTION
#  --------------------------------------------------------------------------------------------------------------------
#  \file
#  \brief        Python script for automating data processing on hex files using HexView
#  --------------------------------------------------------------------------------------------------------------------
#  COPYRIGHT
#  --------------------------------------------------------------------------------------------------------------------
#  \par Copyright
#  \verbatim
#  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.
#
#                This software is copyright protected and proprietary to Vector Informatik GmbH.
#                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
#                All other rights remain with Vector Informatik GmbH.
#  \endverbatim
#
# #####################################################################################################################

# #####################################################################################################################
#  AUTHOR IDENTITY
#  --------------------------------------------------------------------------------------------------------------------
#  Name                          Initials      Company
#  --------------------------------------------------------------------------------------------------------------------
#  Joern Herwig                  JHg           Vector Informatik GmbH
#  Alexander Starke              ASe           Vector Informatik GmbH
#  Daniel Mueller                DMr           Vector Informatik GmbH
#  Achim Strobelt                Ach           Vector Informatik GmbH
#  Johannes Hoetzer              Hrj           Vector Informatik GmbH
#  --------------------------------------------------------------------------------------------------------------------
#  REVISION HISTORY
#  --------------------------------------------------------------------------------------------------------------------
#  Version   Date        Author  Change Id          Description
#  --------------------------------------------------------------------------------------------------------------------
#  01.00.00  2013-12-20  ASe     -                  First implementation
#  01.01.00  2017-11-16  JHg     -                  Added support for FDS 3.0.0
#  01.01.01  2019-01-31  DMr     -                  Added Python Version Check 
#                                                   (Script only support Python version < 3.6.0)
#  02.00.00  2019-05-14  Ach     -                  Add automatic base path configuration, add new compression modes
#  02.01.00  2020-01-20  Ach     -                  Allow usage on standard delivery installation path
#  02.01.01  2020-01-01  Hrj     -                  Printing help message in case of no arguments
# #####################################################################################################################

# ---------------------------------------------------------------------------------------------------------------------
# Imported modules
# ---------------------------------------------------------------------------------------------------------------------

import sys
import os
import shutil
import fnmatch
import struct
import argparse
import re
import time

# ---------------------------------------------------------------------------------------------------------------------
# Configuration variables
# ---------------------------------------------------------------------------------------------------------------------

# Paths / directories

# Project base path

HEXVIEW_PATH = r'\BuildTool\HexView\hexview.exe'
#ECL_COMPRESSION_TOOL_PATH = r'\ThirdParty\CmprEclEb_Vag\compression_tool\bin\EB_ECL.exe'
#LZMA_COMPRESSION_TOOL_PATH = r'\Misc\Cmpr_Lzma\COMPRESS_LZMA_Util.exe'
#LZ77_COMPRESSION_TOOL_PATH = r'\Misc\Cmpr_Vector\VectorCompression.exe'
#AES_INITIALIZATION_VECTOR = r'b928a8af363efe24b0854637fd4f1a62'
#AES_KEY = r'00112233445566778899aabbccddeeff'
#AES_PADDING_PATTERN = r'8000000000000000000000000000000000000000'
KEY_FILE = r'\BuildTool\PostProc\Key-File.txt'
HMAC_KEY = r'HMACKey01'
RSA_KEY_FDS2 = r'RSAKey01'
RSA_KEY_FDS3 = r'RSAKey01_3072'

# Other parameters

FILL_CHARACTER = 0xFF
FILL_WORD = 0xFFFF
FILL_DWORD = 0xFFFFFFFF
ALIGNMENT = 2
DFI_NONE = 0x00
DFI_COMPRESSION = 0xA0
DFI_ENCRYPTION = 0x0A
DFI_COMPRESSION_ENCRYPTION = 0xAA
DP_RSA_FDS2 = r'8'
DP_RSA_FDS3 = r'38'

LZMA_OPT_LEVEL = r'9'
LZMA_DICT_SIZE = r'4096'

# ---------------------------------------------------------------------------------------------------------------------
# Global variables
# ---------------------------------------------------------------------------------------------------------------------
RSA_KEY = RSA_KEY_FDS2
DP_RSA = DP_RSA_FDS2

compressionList = []

# ---------------------------------------------------------------------------------------------------------------------
# Helper functions
# ---------------------------------------------------------------------------------------------------------------------

def consistency_check():
    # assert len(AES_INITIALIZATION_VECTOR) == 32
    # assert len(AES_KEY) == 32
    assert os.path.exists(basePath + HEXVIEW_PATH)

def clean_up():
    if os.path.exists(r'tmp'):
        shutil.rmtree(r'tmp', ignore_errors=True)
    if os.path.exists(r'out'):
        shutil.rmtree(r'out', ignore_errors=True)

def prepare():
    if not os.path.exists(r'tmp'):
        os.mkdir(r'tmp')
    if not os.path.exists(r'out'):
        os.mkdir(r'out')
    assert os.path.exists(r'tmp')
    assert os.path.exists(r'out')

def get_file_name_without_extension_from_path(path):
    fileName = os.path.basename(path)
    fileName = os.path.splitext(fileName)
    fileName = fileName[0]
    return fileName

def concatenate_files(inputFiles, outputFile):
    # Avoid creating the file multiple times in case HMAC and RSA are used
    if not os.path.exists(outputFile):
        destination = open(outputFile, r'wb')
        totalSize = 0
        for file in inputFiles:
            totalSize += os.path.getsize(file)
            shutil.copyfileobj(open(file, r'rb'), destination)
        destination.close()
        assert totalSize == os.path.getsize(outputFile)
    assert os.path.exists(outputFile)

def create_file_path(path, folder, suffix, extension):
    fileName = get_file_name_without_extension_from_path(path)
    filePath = os.path.normpath(r'./' + folder + '/' + fileName + suffix + r'.' + extension)
    return filePath

def create_copy_of_input_file(inputFile):
    copiedInputFile = create_file_path(inputFile, r'out', r'', os.path.splitext(inputFile)[1][1:])
    shutil.copyfile(inputFile, copiedInputFile)
    assert os.path.exists(copiedInputFile)
    return copiedInputFile

# ---------------------------------------------------------------------------------------------------------------------
# Signature / checksum calculation and binary generation functions
# ---------------------------------------------------------------------------------------------------------------------

def create_aes_parameter_files():
    hexViewCommand = basePath + HEXVIEW_PATH + r' /S /XN /FR:0x0000-0x000F /FP:'
    hexViewAesIvCommand = hexViewCommand + AES_INITIALIZATION_VECTOR + r' /O:tmp\aes_initialization_vector.bin'
    hexViewAesKeyCommand = hexViewCommand + AES_KEY + r' /O:tmp\aes_key.bin'
    os.system(hexViewAesIvCommand)
    assert os.path.exists(r'tmp\aes_initialization_vector.bin')
    os.system(hexViewAesKeyCommand)
    assert os.path.exists(r'tmp\aes_key.bin')

def single_region_create_binary_with_prepended_address_and_length_from_binary(binFile, address, length):
    binaryWithPrependedAddressAndLength = create_file_path(binFile, r'tmp', r'_addr_len', 'bin')
    # Avoid creating the file multiple times in case HMAC and RSA are used
    if not os.path.exists(binaryWithPrependedAddressAndLength):
        addressLengthString = r'%08x%08x' % (address, length)
        hexViewCommand = basePath + HEXVIEW_PATH + r'  /S /MO:' + binFile + r';8 /FR:0,8 /FP:' + addressLengthString + r' /XN /O:' + binaryWithPrependedAddressAndLength
        os.system(hexViewCommand)
    assert os.path.exists(binaryWithPrependedAddressAndLength)

def single_region_create_binary_and_calculate_crc32_from_hex(inputFile):
    binary = create_file_path(inputFile, r'out', r'', r'bin')
    crc = create_file_path(inputFile, r'out', r'', r'crc')
    hexViewCommand = basePath + HEXVIEW_PATH + r' "' + inputFile + r'" /S /AF:' + str(FILL_CHARACTER) + r' /FA /XN -cs9:' + crc + r' /O:' + binary
    os.system(hexViewCommand)
    assert os.path.exists(binary)
    assert os.path.exists(crc)

def multi_region_calculate_crc32_from_hex(inputFile):
    crc = create_file_path(inputFile, r'out', r'', r'crc')
    hexViewCommand = basePath + HEXVIEW_PATH + r' "' + inputFile + r'" /S -cs9:' + crc
    os.system(hexViewCommand)
    assert os.path.exists(crc)

def encrypt_aes_from_binary(binFile, outputDirectory):
    binaryEncryptedPath = create_file_path(binFile, outputDirectory, r'_aes', r'bin')
    # Encrypt file
    hexViewCommand = basePath + HEXVIEW_PATH + r' ' + binFile + r' /S /DP11:' + AES_KEY + r';RFC1321#IV=' + AES_INITIALIZATION_VECTOR + r' /XN /O:' + binaryEncryptedPath
    os.system(hexViewCommand)
    assert os.path.exists(binaryEncryptedPath)
    # Encrypt compressed files
    for compression in compressionList:
        compressedBinary = create_file_path(binFile, outputDirectory, compression[0], r'bin')
        compressedBinaryEncrypt = create_file_path(binFile, outputDirectory, compression[0] + r'_aes', r'bin')
        hexViewCommand = basePath + HEXVIEW_PATH + r' ' + compressedBinary + r' /S /DP11:' + AES_KEY + r';RFC1321#IV=' + AES_INITIALIZATION_VECTOR + r' /XN /O:' + compressedBinaryEncrypt
        os.system(hexViewCommand)
        assert os.path.exists(compressedBinaryEncrypt)

# Create ECL compressed file
def compress_from_binary_ecl(binFile, compressedFile):
    compressionToolCommand = basePath + ECL_COMPRESSION_TOOL_PATH + r' c ' + binFile + ' ' + compressedFile + r' >nul 2>&1'
    os.system(compressionToolCommand)

# Create LZMA compressed file
def compress_from_binary_lzma(binFile, compressedFile):
    compressionToolCommand = basePath + LZMA_COMPRESSION_TOOL_PATH + r' -O' + LZMA_OPT_LEVEL + r' -ws=' + LZMA_DICT_SIZE + ' ' + binFile + ' ' + compressedFile + r' >nul 2>&1'
    os.system(compressionToolCommand)

# Create Vector compressed file
def compress_from_binary_vector(binFile, compressedFile):
    compressionToolCommand = basePath + LZ77_COMPRESSION_TOOL_PATH + r' 0 ' + binFile + ' ' + compressedFile + r' >nul 2>&1'
    os.system(compressionToolCommand)

# Create compressed files
def compress_from_binary(binFile, outputDirectory):
    for compression in compressionList:
        compressedBinary = create_file_path(binFile, outputDirectory, compression[0], r'bin')
        compression[1](binFile, compressedBinary)
        assert os.path.exists(compressedBinary)

# Calculate HMAC for one binary file
def single_region_calculate_hmac_from_binary(processedBinFile, unprocessedBinFile, logicalBlock):
    hmacSignature = create_file_path(processedBinFile, r'out', r'', r'hmac')
    hmacSignatureHexview = create_file_path(processedBinFile, r'../out', r'', r'hmac')
    binaryWithPrependedAddressAndLength = create_file_path(processedBinFile, r'tmp', r'_addr_len', r'bin')
    fileSize = os.path.getsize(unprocessedBinFile)
    single_region_create_binary_with_prepended_address_and_length_from_binary(processedBinFile, logicalBlock, fileSize)
    hexViewCommand = basePath + HEXVIEW_PATH + r' ' + binaryWithPrependedAddressAndLength + r' /S -dp4:' + basePath + KEY_FILE + r',' + HMAC_KEY + r',Value;' + hmacSignatureHexview
    os.system(hexViewCommand)
    assert os.path.exists(hmacSignature)

# Calculate RSA for one binary file
def single_region_calculate_rsa_from_binary(processedBinFile, unprocessedBinFile, logicalBlock):
    rsaSignature = create_file_path(processedBinFile, r'out', r'', r'rsa')
    rsaSignatureHexview = create_file_path(processedBinFile, r'../out', r'', r'rsa')
    binaryWithPrependedAddressAndLength = create_file_path(processedBinFile, r'tmp', r'_addr_len', r'bin')
    fileSize = os.path.getsize(unprocessedBinFile)
    single_region_create_binary_with_prepended_address_and_length_from_binary(processedBinFile, logicalBlock, fileSize)
    hexViewCommand = basePath + HEXVIEW_PATH + r' ' + binaryWithPrependedAddressAndLength + r' /S -dp' + DP_RSA + ':' + basePath + KEY_FILE + r',' + RSA_KEY + r',KEY-PRIV;' + rsaSignatureHexview
    os.system(hexViewCommand)
    assert os.path.exists(rsaSignature)

# Calculate signatures for all binary files (all variants)
def single_region_calculate_signature(binFile, logicalBlock):
    # Unprocessed file
    single_region_calculate_hmac_from_binary(binFile, binFile, logicalBlock)
    single_region_calculate_rsa_from_binary(binFile, binFile, logicalBlock)
    # Encrypted file
    # encryptedBinary = create_file_path(binFile, r'out', '_aes', 'bin')
    # single_region_calculate_hmac_from_binary(encryptedBinary, binFile, logicalBlock)
    # single_region_calculate_rsa_from_binary(encryptedBinary, binFile, logicalBlock)
    # Compressed files
    for compression in compressionList:
        compressedBinary = create_file_path(binFile, r'out', compression[0], r'bin')
        single_region_calculate_hmac_from_binary(compressedBinary, binFile, logicalBlock)
        single_region_calculate_rsa_from_binary(compressedBinary, binFile, logicalBlock)
    # Compressed/encrypted files
    # for compression in compressionList:
        # compressedBinary = create_file_path(binFile, r'out', compression[0] + r'_aes', r'bin')
        # single_region_calculate_hmac_from_binary(compressedBinary, binFile, logicalBlock)
        # single_region_calculate_rsa_from_binary(compressedBinary, binFile, logicalBlock)

# Calculate HMAC for one hex file
def multi_region_calculate_hmac_from_binaries(processedBinFiles, unprocessedBinFiles, fileName, suffix, logicalBlock):
    hmacSignature = create_file_path(fileName, r'out', suffix, r'hmac')
    hmacSignatureHexview = create_file_path(fileName, r'../out', suffix, r'hmac')
    binariesWithPrependedAddressAndLength = []
    segment = 1
    for binFile in processedBinFiles:
        binaryWithPrependedAddressAndLength = create_file_path(binFile, r'tmp', r'_addr_len', r'bin')
        fileSize = os.path.getsize(unprocessedBinFiles[segment - 1])
        single_region_create_binary_with_prepended_address_and_length_from_binary(binFile, ((logicalBlock * 256) + segment), fileSize)
        binariesWithPrependedAddressAndLength.append(binaryWithPrependedAddressAndLength)
        segment += 1
    binaryWithPrependedAddressAndLength = create_file_path(fileName, r'tmp', suffix + r'_addr_len', r'bin')
    concatenate_files(binariesWithPrependedAddressAndLength, binaryWithPrependedAddressAndLength)
    assert os.path.exists(binaryWithPrependedAddressAndLength)
    hexViewCommand = basePath + HEXVIEW_PATH + r' ' + binaryWithPrependedAddressAndLength + r' /S -dp4:' + basePath + KEY_FILE + r',' + HMAC_KEY + r',Value;' + hmacSignatureHexview
    os.system(hexViewCommand)
    assert os.path.exists(hmacSignature)

# Calculate RSA for one hex file
def multi_region_calculate_rsa_from_binaries(processedBinFiles, unprocessedBinFiles, fileName, suffix, logicalBlock):
    rsaSignature = create_file_path(fileName, r'out', suffix, r'rsa')
    rsaSignatureHexview = create_file_path(fileName, r'../out', suffix, r'rsa')
    binariesWithPrependedAddressAndLength = []
    segment = 1
    for binFile in processedBinFiles:
        binaryWithPrependedAddressAndLength = create_file_path(binFile, r'tmp', r'_addr_len', r'bin')
        fileSize = os.path.getsize(unprocessedBinFiles[segment - 1])
        single_region_create_binary_with_prepended_address_and_length_from_binary(binFile, ((logicalBlock * 256) + segment), fileSize)
        binariesWithPrependedAddressAndLength.append(binaryWithPrependedAddressAndLength)
        segment += 1
    binaryWithPrependedAddressAndLength = create_file_path(fileName, r'tmp', suffix + r'_addr_len', r'bin')
    concatenate_files(binariesWithPrependedAddressAndLength, binaryWithPrependedAddressAndLength)
    assert os.path.exists(binaryWithPrependedAddressAndLength)
    hexViewCommand = basePath + HEXVIEW_PATH + r' ' + binaryWithPrependedAddressAndLength + r' /S -dp' + DP_RSA + ':' + basePath + KEY_FILE + r',' + RSA_KEY + r',KEY-PRIV;' + rsaSignatureHexview
    os.system(hexViewCommand)
    assert os.path.exists(rsaSignature)

# Calculate signatures for all hex files
def multi_region_calculate_signature(segmentedBinaries, fileName, logicalBlock):
    # Unprocessed file
    multi_region_calculate_hmac_from_binaries(segmentedBinaries, segmentedBinaries, fileName, r'', logicalBlock)
    multi_region_calculate_rsa_from_binaries(segmentedBinaries, segmentedBinaries, fileName, r'', logicalBlock)
    # Encrypted file
    segmentedEncryptedBinaries = [segmentBinary.replace(r'.bin', r'_aes.bin') for segmentBinary in segmentedBinaries]
    multi_region_calculate_hmac_from_binaries(segmentedEncryptedBinaries, segmentedBinaries, fileName, r'_aes', logicalBlock)
    multi_region_calculate_rsa_from_binaries(segmentedEncryptedBinaries, segmentedBinaries, fileName, r'_aes', logicalBlock)
    # Compressed files
    for compression in compressionList:
        segmentedCompressedBinaries = [segmentBinary.replace(r'.bin', compression[0] + r'.bin') for segmentBinary in segmentedBinaries]
        multi_region_calculate_hmac_from_binaries(segmentedCompressedBinaries, segmentedBinaries, fileName, compression[0], logicalBlock)
        multi_region_calculate_rsa_from_binaries(segmentedCompressedBinaries, segmentedBinaries, fileName, compression[0], logicalBlock)
    # Compressed / encrypted files
    for compression in compressionList:
        segmentedCompressedBinaries = [segmentBinary.replace(r'.bin', compression[0] + r'_aes.bin') for segmentBinary in segmentedBinaries]
        multi_region_calculate_hmac_from_binaries(segmentedCompressedBinaries, segmentedBinaries, fileName, compression[0] + r'_aes', logicalBlock)
        multi_region_calculate_rsa_from_binaries(segmentedCompressedBinaries, segmentedBinaries, fileName, compression[0] + r'_aes', logicalBlock)

def get_address_from_segment_binary_file_name(fileName):
    # Strip '.bin' from fileName, separate string into substrings, last substring contains hexadecimal address
    fileName = fileName[:-4]
    temp = fileName.split(r'_')
    segment = 0
    for namePart in temp:
        if namePart == r'segment':
            segmentfound = segment
        segment += 1
    assert temp[segmentfound] == r'segment'
    return int(temp[segmentfound + 1], 16)

def sort_array_of_segment_binaries(segmentedBinaries):
    sortedSegmentedBinaries = sorted(segmentedBinaries, key=get_address_from_segment_binary_file_name)
    return sortedSegmentedBinaries

def split_hex_file_into_multiple_binaries(inputFile):
    binaries = create_file_path(inputFile, r'tmp', r'_segment', r'bin')
    hexViewCommand = basePath + HEXVIEW_PATH + r' "' + inputFile + r'" /S /xsb /O:' + binaries
    os.system(hexViewCommand)
    segmentedBinaries = []
    for file in os.listdir(os.path.normpath(r'./tmp/')):
        if fnmatch.fnmatch(file, get_file_name_without_extension_from_path(inputFile) + '_segment_*.bin'):
            segmentedBinaries.append(os.path.normpath(r'./tmp/' + file))
    assert len(segmentedBinaries) > 0
    return segmentedBinaries

# Concatenate one set of segmented binaries into one hex file
def concatenate_segment_binaries_into_hex_file(segmentedBinaries, fileName, suffix):
    hexFilePath = create_file_path(fileName, r'out', suffix, r'hex')
    open(hexFilePath, 'a').close()
    lastAddress = 0
    for binFile in segmentedBinaries:
        address = get_address_from_segment_binary_file_name(binFile)
        fileSize = os.path.getsize(binFile)
        # Check if addresses overlap
        if lastAddress > address:
            address = lastAddress + (ALIGNMENT - (lastAddress % ALIGNMENT))
        hexAddress = r'0x%08x' % address
        hexViewCommand = basePath + HEXVIEW_PATH + r' /S /XI /MO:' + hexFilePath + r'+' + binFile + r';' + hexAddress + r' /O:' + hexFilePath
        os.system(hexViewCommand)
        lastAddress = address + fileSize
    assert os.path.exists(hexFilePath)

# Concatenate segmented files into hex files
def concatenate_segment_binaries(segmentedBinaries, fileName):
    # Unprocessed data
    concatenate_segment_binaries_into_hex_file(segmentedBinaries, fileName, r'')
    # Encrypted data
    segmentedEncryptedBinaries = [segmentBinary.replace(r'.bin', r'_aes.bin') for segmentBinary in segmentedBinaries]
    concatenate_segment_binaries_into_hex_file(segmentedEncryptedBinaries, fileName, r'_aes')
    # Compressed data
    for compression in compressionList:
        segmentedCompressedBinaries = [segmentBinary.replace(r'.bin', compression[0] + r'.bin') for segmentBinary in segmentedBinaries]
        concatenate_segment_binaries_into_hex_file(segmentedCompressedBinaries, fileName, compression[0])
        segmentedCompressedBinaries = [segmentBinary.replace(r'.bin', compression[0] + r'_aes.bin') for segmentBinary in segmentedBinaries]
        concatenate_segment_binaries_into_hex_file(segmentedCompressedBinaries, fileName, compression[0] + r'_aes')

def parse_numbers_from_file(fileName, suffix, extension, expectedLength):
    filePath = create_file_path(fileName, r'out', suffix, extension)
    with open(filePath, r'r') as tmpFile:
        outData = tmpFile.read()
    outData = outData.split(r',')
    outData = [data.strip() for data in outData]
    outData = [data.replace(r'0x', r'') for data in outData]
    outData = [int(data, 16) for data in outData]
    assert len(outData) == expectedLength
    return outData

def parse_crc_file(fileName, suffix):
    return parse_numbers_from_file(fileName, suffix, r'crc', 4)

def parse_hmac_file(fileName, suffix):
    return parse_numbers_from_file(fileName, suffix, r'hmac', 20)

def parse_rsa_file(fileName, suffix):
    return parse_numbers_from_file(fileName, suffix, r'rsa', 128)

# ---------------------------------------------------------------------------------------------------------------------
# Main function
# ---------------------------------------------------------------------------------------------------------------------

def main():

    global RSA_KEY
    global DP_RSA

    global basePath

    inputFilePaths = []
    fileNames = []
    logicalBlocks = []

    fdsArgValid = [r'2', r'3']

    # Extract base path from working directory
    executePath = os.getcwd()
    basePath = os.path.abspath(os.path.join(os.path.sep, executePath ,'..','..'))
    print('Basepath: ' + basePath)
    assert(basePath)

    # Check which compression algorithms should be used
    # if os.path.exists(basePath + ECL_COMPRESSION_TOOL_PATH):
        # compressionList.append(['_lzss', compress_from_binary_ecl])
    # if os.path.exists(basePath + LZMA_COMPRESSION_TOOL_PATH):
        # compressionList.append(['_lzma', compress_from_binary_lzma])
    # if os.path.exists(basePath + LZ77_COMPRESSION_TOOL_PATH):
        # compressionList.append(['_lz77', compress_from_binary_vector])

    # Check for input arguments
    parser = argparse.ArgumentParser(prog=r'vag_swdl_files_create.py', description=r'Data processing on hex files using HexView. Provide multiple input files to merge them.')
    parser.add_argument(r'-i', r'--input', type=str, action=r'append', metavar=r'YourInputFilePath', help=r'The input file path, multiple paths can be specified')
    parser.add_argument(r'-b', r'--block', type=str, action=r'append', metavar=r'LogicalBlock', help=r'The logical block number, multiple block numbers can be specified')
    parser.add_argument(r'-s', r'--segments', action=r'store_true', default=False, help=r'Preserve segments in the input file(s)')
    parser.add_argument(r'-f', r'--fds', type=str, action=r'store', default=r'2', metavar=r'FdsVersion', help=r'FDS specification version (2 or 3)')
    if len(sys.argv)==1:
        parser.print_help(sys.stderr)
        sys.exit(1)
    args = parser.parse_args()
    
    args.block = [] if None else args.block
    args.input = [] if None else args.input

    assert len(args.block) == len(args.input)
    assert len(args.block) > 0
    assert args.fds in fdsArgValid

    for path in args.input:
        assert os.path.exists(path)
        inputFilePaths.append(path)
    for block in args.block:
        if r'0x' in block:
            block = int(block.replace(r'0x', ''), 16)
        else:
            block = int(block, 10)
        assert (block >= 0) and (block <= 256)
        logicalBlocks.append(block)

    if args.fds == r'3':
        RSA_KEY = RSA_KEY_FDS3
        DP_RSA = DP_RSA_FDS3

    preserveSegments = args.segments

    # Preparation phase -----------------------------------------------------------------------------------------------
    consistency_check()
    clean_up()
    prepare()
    #create_aes_parameter_files()

    # Iterate over input files ----------------------------------------------------------------------------------------
    for index, inputFilePath in enumerate(inputFilePaths):

        inputFile = create_copy_of_input_file(inputFilePath)
        fileName = get_file_name_without_extension_from_path(inputFile)
        logicalBlock = logicalBlocks[index]
        fileNames.append(fileName)

        segmentedBinaries = split_hex_file_into_multiple_binaries(inputFile)

        # Process single region file ----------------------------------------------------------------------------------
        if not preserveSegments or (len(segmentedBinaries) == 1):
            # Ignore the created segment binary and use the binary created together with the CRC32
            binary = create_file_path(fileName, r'out', '', 'bin')
            single_region_create_binary_and_calculate_crc32_from_hex(inputFile)
            #compress_from_binary(binary, r'out')
            #encrypt_aes_from_binary(binary, r'out')
            single_region_calculate_signature(binary, logicalBlock)

        # Process file containing multiple segments -------------------------------------------------------------------
        else:

            # Process the segment binaries
            segmentedBinaries = sort_array_of_segment_binaries(segmentedBinaries)

            multi_region_calculate_crc32_from_hex(inputFile)

            for segmentBinary in segmentedBinaries:
                binary = create_file_path(segmentBinary, r'tmp', '', 'bin')
                compress_from_binary(binary, r'tmp')
                encrypt_aes_from_binary(binary, r'tmp')

            multi_region_calculate_signature(segmentedBinaries, fileName, logicalBlock)

            concatenate_segment_binaries(segmentedBinaries, fileName)

        print(r'Processing ' + fileName + ' completed')

# ---------------------------------------------------------------------------------------------------------------------
# Script entry point
# ---------------------------------------------------------------------------------------------------------------------

if __name__ == "__main__":
    main()
