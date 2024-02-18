import sys, subprocess
import os, shutil, stat
import re
from subprocess import Popen

# ----------- MAIN Function -----------
def main(post_build,build_type):
    
    os.chdir("..\\..\\BuildOutput\\")
    path = OutputDirIdentify()
    
    # Copy documentation files (map, calltree) and Extend hex files with version number    
    CopyFiles(path,build_type)
    os.chdir("..\\..\\BuildOutput\\")
    # Create .hex file, out of .out file
    BuildDir = os.getcwd()
    OutFileName = "S32K" + ".out"
    HexFileName = "S32K" + ".hex"
    MergedHexFileName = "S32K" + "_merged.hex"
    MergedSeriesHexFileName = "S32K" + "_merged_series.hex"
    BlFilePath =  os.path.join(os.path.dirname(os.path.realpath(OutputDirIdentify())), "..\\BuildTool\\BL_binary\\Bootloader.hex")
    BlSeriesFilePath =  os.path.join(os.path.dirname(os.path.realpath(OutputDirIdentify())), "..\\BuildTool\\BL_binary\\Bootloader_series.hex")
    ValidPatternFilePath =  os.path.join(os.path.dirname(os.path.realpath(OutputDirIdentify())), "..\\BuildTool\\BL_binary\\ApplValidPattern.hex")
    CreateHexFile(BuildDir, OutFileName, HexFileName)
    CreateMergedHexFile(HexFileName, MergedHexFileName, BlFilePath, ValidPatternFilePath)
    CreateMergedHexFile(HexFileName, MergedSeriesHexFileName, BlSeriesFilePath, ValidPatternFilePath)

    
# --------- end MAIN

# Identify the Output Folder Name( e.g.: MCU_NCF2953) by using the MCU_* pattern
def OutputDirIdentify():
    arg = ""
    onlyDir = [f for f in os.listdir(os.getcwd()) if not os.path.isfile(os.path.join(os.getcwd(), f))]
    for d in onlyDir:
        if "HufBSW_" in d: arg = d
    return arg

# Copy documentation files (map, calltree) and Extend hex files with version number                    
def CopyFiles(path, args):
    try:
        extended = True if "extended" in args else False      
        # remove read-only flag
        
        for f in os.listdir(os.getcwd()):
            if os.path.isfile(os.path.join(os.getcwd(), f)) and "Prog_" in f: os.chmod ( f, stat.S_IWRITE )  
        #calculate Destination and Source Folder
        dst = os.getcwd()
        os.chdir(path)
        src = os.getcwd()

        # parse and copy the desired files
        onlyfiles = [f for f in os.listdir(os.getcwd()) if os.path.isfile(os.path.join(os.getcwd(), f))]
        for f in onlyfiles:
            os.chmod ( f, stat.S_IWRITE )                                                  
            if f.startswith("S32K"):
                shutil.copy2(f, dst + "\\"+ f )

    except:
        print "\n PostBuild Error: the folder HufBSW_*** with map, elf, hex files was not found or some files are Read-Only!"
#create hex file from out file
def CreateHexFile(BuildDir, OutFileName, HexFileName):
    
    existIElfTool = True
    
    for dir in os.environ['COMPILER_PATH'].split(os.pathsep):
        dir = dir.replace("\"","")
        if os.path.isdir(dir):
            elfTool = os.path.join(dir , 'ielftool.exe')
            if os.path.isfile(elfTool):  
				cmd = str(elfTool) + ' --ihex ' + " " + BuildDir + "\\" + str(OutFileName) + " " + BuildDir + "\\" + str(HexFileName)
				process = Popen(cmd)
				stdout, stderr = process.communicate()
				print 'comanda', cmd
            else:
                existIElfTool = False

    if not existIElfTool:
        print 'The tool(ielftool) that converts the .cout file to .hex file not found!'       
#create bin file from out file
def CreateMergedHexFile(HexFileName, MergedHexFileName, BlFilePath, ValidPatternFilePath):
    HexViewTool =  os.path.join(os.path.dirname(os.path.realpath(__file__)), "..\\HexView\\hexview.exe")
    if os.path.isfile(HexViewTool): 
        cmd = str(HexViewTool) + " /S " + str(HexFileName) + " /AR:0x30000-0x7EFFF /XI /O:S32K_NoPDL.hex"
        print 'Generating Hex without PDL data... '
        print 'Running command: ', cmd
        process = Popen(cmd)
        stdout, stderr = process.communicate()

        cmd = str(HexViewTool) + " /S S32K_NoPDL.hex /AFFF /FA /XI /O:S32K_NoPDL_filled.hex"
        print 'Generating filled Hex without PDL data... '
        print 'Running command: ', cmd
        process = Popen(cmd)
        stdout, stderr = process.communicate()

        cmd = str(HexViewTool) + " /S S32K_NoPDL_filled.hex /CS9:@0x80000 /XI /O:S32K_NoPDL_with_CRC.hex"
        print 'Generating Hex without PDL data and with CRC... '
        print 'Running command: ', cmd
        process = Popen(cmd)
        stdout, stderr = process.communicate()

        cmd = str(HexViewTool) + " " + BlFilePath + " /S /MO:" + str(HexFileName) + ";0x0-0x30000+" + str(ValidPatternFilePath) + "  /CSR9:@0x7FFDC;0x7F000-0x7FFDB /XI /O:" + str(MergedHexFileName)
        print 'Generating merged hex file... '
        print 'Running command: ', cmd
        process = Popen(cmd)
        stdout, stderr = process.communicate()

        cmd = str(HexViewTool) + " " + MergedHexFileName + " /S /MO:S32K_NoPDL_with_CRC.hex;-0x1024:0x80000-0x80003 /XI /O:" + str(MergedHexFileName)
        print 'Generating CRC32 over app in merged hex file... '
        print 'Running command: ', cmd
        process = Popen(cmd)
        stdout, stderr = process.communicate()

        print 'Removing Hex without PDL data and with CRC... '

        cmd = "" + os.path.join(os.path.dirname(os.path.realpath(__file__))) + "\..\..\\BuildOutput\S32K_NoPDL_filled.hex"
        print 'Deleting file: ', cmd
        os.remove(cmd)
        cmd = os.path.join(os.path.dirname(os.path.realpath(__file__))) + "\..\..\\BuildOutput\S32K_NoPDL_with_CRC.hex"
        print 'Deleting file: ', cmd
        os.remove(cmd)

    else:
        print 'The hexview tool that converts the .hex file to flashable .bin file not found!'

if __name__ == "__main__":
    main(sys.argv[1:])
