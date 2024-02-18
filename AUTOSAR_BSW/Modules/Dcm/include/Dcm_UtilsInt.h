/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Dcm_UtilsInt.h
 *        \brief  Contains public function declarations and complex type definitions of Utils unit.
 *
 *      \details  MICROSAR DCM based on AR 4.0.3
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
#if !defined(DCM_UTILSINT_H)
# define DCM_UTILSINT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_UtilsTypes.h"
# include "SchM_Dcm.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# if (DCM_DIDMGR_NVM_READ_ENABLED == STD_ON) || \
     (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON)
#  define DCM_UTI_NVM_READ_ENABLED                                   STD_ON
# else
#  define DCM_UTI_NVM_READ_ENABLED                                   STD_OFF
# endif

# if (DCM_DIDMGR_NVM_WRITE_ENABLED == STD_ON) || \
     (DCM_SVC_86_NVM_SUPPORT_ENABLED == STD_ON) || \
     (DCM_AUTHMGR_PERSIST_STATE_ENABLED == STD_ON)
#  define DCM_UTI_NVM_WRITE_ENABLED                                  STD_ON
# else
#  define DCM_UTI_NVM_WRITE_ENABLED                                  STD_OFF
# endif

# if (DCM_SVC_2C_NVRAM_SUPPORT_ENABLED == STD_ON)
#  define DCM_UTI_NVM_SET_RAM_BLOCK_STATUS_ENABLED                   STD_ON
# else
#  define DCM_UTI_NVM_SET_RAM_BLOCK_STATUS_ENABLED                   STD_OFF
# endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/*! AR4.x SchM enter exclusive area adapter implementation */
# define Dcm_UtiEnterCriticalSection()                               SchM_Enter_Dcm_DCM_EXCLUSIVE_AREA_0()                                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! AR4.x SchM leave exclusive area adapter implementation */
# define Dcm_UtiLeaveCriticalSection()                               SchM_Exit_Dcm_DCM_EXCLUSIVE_AREA_0()                                            /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Endless loop pattern */
# define DCM_UTI_LOOP_FOR_EVER                                       for(;;)
/*! Bit scanner loop pattern (for atomic bit-sets with up to 32 bits) */
# define DCM_UTI_LOOP_BIT_SCAN(bitRegister)                          for(;(bitRegister) != 0u; (bitRegister) >>= 1u)

/*! Move forward on pointer of abstract data */
# define Dcm_UtiNextItemByPtr(ptr, step)                             ((ptr)=&(ptr)[(step)])                                                          /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Promotes the sum of two integer arguments to a bigger integer data type to avoid result overflow */
# define Dcm_UtiPromotedSum(promoType, add1, add2)                   ((promoType)(add1) + (promoType)(add2))                                         /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Verifies if sum of two integer values is safe (will not cause result overflow) */
# define Dcm_UtiIsAdditionSafe(baseValueType, baseValue, add2)       (Dcm_UtiPromotedSum(baseValueType,(baseValue),(add2)) >= ((baseValueType)(baseValue))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Sets single or multiple bits in an atomic bit-set */
# define Dcm_UtiBitOpSet(bitRegisterType, bitRegister, bits)         ((bitRegister) |= (bitRegisterType)(bits))                                      /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Clears single or multiple bits in an atomic bit-set */
# define Dcm_UtiBitOpClr(bitRegisterType, bitRegister, bits)         ((bitRegister) &= (bitRegisterType)(~((bitRegisterType)(bits))))                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns TRUE if at least one bit in an atomic bit-set is set */
# define Dcm_UtiBitOpTest(bitRegisterType, bitRegister, bits)        (((bitRegister) & (bitRegisterType)(bits)) != 0u)                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Macros used instead of a function to avoid different memory pointer types and warnings for unused local functions! */

/*! Generic memory copy operation for array of elements (i.e. arrays of any data type) */
# define Dcm_UtiMemCopy(srcPtr, tgtPtr, length)                      {Dcm_CfgNetBufferSizeOptType memIter; for(memIter = 0u; memIter < (Dcm_CfgNetBufferSizeOptType)(length); ++memIter) {(tgtPtr)[memIter] = (srcPtr)[memIter];}} /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Generic RAM to RAM byte-wise memory copy operation */
# define Dcm_UtiByteMemCopy(srcPtr, tgtPtr, numBytes)                Dcm_UtiMemCopy((Dcm_Uint8VarDataPtrType)(srcPtr),(Dcm_Uint8VarDataPtrType)(tgtPtr), (numBytes)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Generic byte-wise memory copy operation from constant memory area */
# define Dcm_UtiConstByteMemCopy(srcPtr, tgtPtr, numBytes)           Dcm_UtiMemCopy((Dcm_Uint8ConstDataPtrType)(srcPtr),(Dcm_Uint8VarDataPtrType)(tgtPtr), (numBytes)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Generic memory set operation for array of elements (i.e. arrays of any data type) */
# define Dcm_UtiMemSetUintX(tgtPtr, uintType, uintValue, elements)   {Dcm_CfgNetBufferSizeOptType memIter; for(memIter = 0u; memIter < (Dcm_CfgNetBufferSizeOptType)(elements); ++memIter) {(tgtPtr)[memIter] = (uintType)(uintValue);}} /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Generic byte-wise direct memory set operation (i.e. writing to a physical address) */
# define Dcm_UtiMemSet(memAddr, uintValue, memSize, memLoc)          {uint16_least memIter; for(memIter = 0u; memIter < (uint16_least)(memSize); ++memIter) {((P2VAR(uint8, TYPEDEF, memLoc))(memAddr))[memIter] = (uint8)(uintValue);}} /* PRQA S 3453, 0850 */ /* MD_MSR_FctLikeMacro, MD_MSR_MacroArgumentEmpty */

/*! Returns a value of an unsigned integer type with a specific number of bits set starting with bit0 */
# define Dcm_UtiGetMaskFromXintType(uintType, numBits)               ((uintType)((1uL << ((numBits)-1u)) -1uL) | (uintType)( 1uL << ((numBits)-1u))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Returns the maximum possible unsigned integer value that can be stored in a specific unsigned integer data type */
# define Dcm_UtiMaxValueOfUintType(uintType)                         (Dcm_UtiGetMaskFromXintType(uintType,Dcm_UtiGetNumBitsOfXintType(uintType)))    /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns the maximum possible signed integer value that can be stored in a specific signed integer data type */
# define Dcm_UtiMaxValueOfSintType(sintType)                         ( (sintType)( (sintType)((1uL << (Dcm_UtiGetNumBitsOfXintType(sintType)-1u)) -1uL)) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Returns an atomic bit-set with just one bit set at specific position */
# define Dcm_UtiGetBitFromIndex(bitsetBaseType, bitIdx)              ((bitsetBaseType)(((bitsetBaseType)0x01u)<<(bitIdx)))                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns TRUE if the atomic bit-set contains exactly one bit set, otherwise returns FALSE */
# define Dcm_UtiIsPowerOfTwo(bitsetBaseType, bitSet)                 (((bitSet) != 0u) && (((bitSet) & ((bitsetBaseType)((bitSet) - 1u))) == 0u))    /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Generic bit-set pattern (with unlimited size) represented as array of bit registers of a specific (platform optimized) width */
/*! Returns the position in a row where the bit-set contains a specific bit */
# define Dcm_UtiBitSetGetColIdx(bitsetBaseType, bit)                 ( (bit) % Dcm_UtiGetNumBitsOfXintType(bitsetBaseType) )                         /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns the bit mask corresponding to a specific bit within a single bit-set row */
# define Dcm_UtiBitSetBitAt(bitsetBaseType, bit)                     ( (bitsetBaseType)(Dcm_UtiGetBitFromIndex(bitsetBaseType, Dcm_UtiBitSetGetColIdx(bitsetBaseType, (bit))) ) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns the bit-set row that contains a specific bit  */
# define Dcm_UtiBitSetAtRow(bitSet, bitsetBaseType, bit)             ( (bitSet)[ Dcm_UtiBitSetGetRowIdxSafe((bit), Dcm_UtiGetNumElementsOfTable(bitSet, bitsetBaseType), Dcm_UtiGetNumBitsOfXintType(bitsetBaseType)) ] ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Returns TRUE if a specific bit in a bit-set is set */
# define Dcm_UtiBitSetTestBit(bitsetBaseType, bitSet, bit)           ( Dcm_UtiBitOpTest(bitsetBaseType, Dcm_UtiBitSetAtRow((bitSet), bitsetBaseType, (bit)), Dcm_UtiBitSetBitAt(bitsetBaseType, (bit))) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Sets a specific bit in a bit-set */
# define Dcm_UtiBitSetSetBit(bitsetBaseType, bitSet, bit)            ( Dcm_UtiBitOpSet( bitsetBaseType, Dcm_UtiBitSetAtRow((bitSet), bitsetBaseType, (bit)), Dcm_UtiBitSetBitAt(bitsetBaseType, (bit))) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Clears a specific bit in a bit-set */
# define Dcm_UtiBitSetClrBit(bitsetBaseType, bitSet, bit)            ( Dcm_UtiBitOpClr( bitsetBaseType, Dcm_UtiBitSetAtRow((bitSet), bitsetBaseType, (bit)), Dcm_UtiBitSetBitAt(bitsetBaseType, (bit))) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Template for set/unset bits in a general purpose bit-set */
# define Dcm_UtiGenericBitSetTestBit(bitSet, bit)                    (Dcm_UtiBitSetTestBit(Dcm_UtiBitSetBaseType, (bitSet), (bit)))                  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGenericBitSetSetBit(bitSet, bit)                     (Dcm_UtiBitSetSetBit(Dcm_UtiBitSetBaseType, (bitSet), (bit)))                   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGenericBitSetClrBit(bitSet, bit)                     (Dcm_UtiBitSetClrBit(Dcm_UtiBitSetBaseType, (bitSet), (bit)))                   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Returns the argument with the lower value */
# define Dcm_UtiMathMin(a, b)                                        (((a)<=(b))?(a):(b))                                                            /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Check whether the given value is even or not */
# define Dcm_UtiIsEven(value)                                        (((value) % 2u) == 0u)                                                          /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiIsOdd(value)                                         (!Dcm_UtiIsEven(value))                                                         /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Returns the number of elements of a table */
# define Dcm_UtiGetNumElementsOfTable(table, baseType)               (sizeof(table)/sizeof(baseType))                                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Initializes a stack object */
# define Dcm_UtiStackInit(stackVar)                                  ((stackVar).StackTop=-1)                                                        /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Pushes a single element to a stack */
# define Dcm_UtiStackPush(stackVar, value)                           ((stackVar).Stack[++((stackVar).StackTop)]=(value))                             /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Pops a single element from a stack */
# define Dcm_UtiStackPop(stackVar)                                   (--((stackVar).StackTop))                                                       /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns the element on the top of a stack */
# define Dcm_UtiStackTop(stackVar)                                   ((stackVar).Stack[(stackVar).StackTop])                                         /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns TRUE if stack is full, otherwise returns FALSE */
# define Dcm_UtiStackIsFull(stackVar, stackBaseType)                 (((stackVar).StackTop) >= (Dcm_UtiStackCntrType)(Dcm_UtiGetNumElementsOfTable((stackVar).Stack, stackBaseType) - 1u)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns TRUE if stack is empty, otherwise returns FALSE */
# define Dcm_UtiStackIsEmpty(stackVar)                               (((stackVar).StackTop) < 0)                                                     /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Compose a 16 bit value from bytes */
# define Dcm_UtiMake16Bit(hiByte,loByte)                             ((uint16)((((uint16)(hiByte))<<8)|                                              /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */ \
                                                                     ((uint16)(loByte))))
/*! Compose a 32bit value from single bytes */
# define Dcm_UtiMake32Bit(hiHiByte,hiLoByte,loHiByte,loLoByte)       ((uint32)((((uint32)(hiHiByte))<<24)|                                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */ \
                                                                     (((uint32)(hiLoByte))<<16)| \
                                                                     (((uint32)(loHiByte))<<8) | \
                                                                     ((uint32)(loLoByte))))
/*! Extract the MSB of a WORD value */
# define Dcm_UtiGetHiByte(data16)                                    ((uint8)(((uint16)(data16))>>8))                                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extract the LSB of a WORD value */
# define Dcm_UtiGetLoByte(data16)                                    ((uint8)(((uint16)(data16)) & 0xFFu))                                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Extract the MSB of a DWORD value */
# define Dcm_UtiGetHiHiByte(data32)                                  ((uint8)(((uint32)(data32))>>24))                                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extract the byte next to the MSB of a DWORD value */
# define Dcm_UtiGetHiLoByte(data32)                                  ((uint8)(((uint32)(data32))>>16))                                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extract the byte next to the LSB of a DWORD value */
# define Dcm_UtiGetLoHiByte(data32)                                  ((uint8)(((uint32)(data32))>>8))                                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extract the LSB of a DWORD value */
# define Dcm_UtiGetLoLoByte(data32)                                  ((uint8)(((uint32)(data32)) & 0xFFu))                                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Extract the MSW of a DWORD value */
# define Dcm_UtiGetHiWord(data32)                                    ((uint16)(((uint32)(data32))>>16))                                              /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extract the LSW of a DWORD value */
# define Dcm_UtiGetLoWord(data32)                                    ((uint16)(((uint32)(data32)) & 0xFFFFu))                                        /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Extract MSN of a BYTE value */
# define Dcm_UtiGetHiNibble(data8)                                   ((uint8)(((uint8)(data8))>>4))                                                  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extract LSN of a BYTE value */
# define Dcm_UtiGetLoNibble(data8)                                   ((uint8)(((uint8)(data8)) & 0x0Fu))                                             /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Avoid warnings of unused API parameters */
# define DCM_IGNORE_UNREF_PARAM(param)                               ((void)(param))                                                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


# if (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON) || \
     (DCM_FBLMGR_SUPPORT_ENABLED == STD_ON)
/*! Extract the size of the length of the memory block from the format BYTE */
#  define Dcm_UtiGetMemBlockLenSize(formatByte)                      (Dcm_UtiGetHiNibble(formatByte))                                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Extract the size of the address of the memory block from the format BYTE */
#  define Dcm_UtiGetMemBlockAddrSize(formatByte)                     (Dcm_UtiGetLoNibble(formatByte))                                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# endif

/*! Updates request message length by specific amount of data already processed */
# define Dcm_UtiUpdateReqLength(msgContextPtr, step)                 ((msgContextPtr)->reqDataLen -= (Dcm_MsgLenType)(step))                         /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

# define Dcm_UtiGetReqDataAt(msgContextPtr, index)                   ((Dcm_MsgType)&((msgContextPtr)->reqData[(index)]))                             /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGetReqDataRel(msgContextPtr, index)                  (Dcm_UtiGetReqDataAt((msgContextPtr), ((msgContextPtr)->reqIndex) + (index)))   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGetReqData(msgContextPtr)                            (Dcm_UtiGetReqDataRel((msgContextPtr), 0u))                                     /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

# define Dcm_UtiGetReqDataAsU8At(msgContextPtr, index)               (*(Dcm_UtiGetReqDataAt((msgContextPtr), (index))))                              /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGetReqDataAsU16At(msgContextPtr, index)              (Dcm_UtiMake16Bit((msgContextPtr)->reqData[(index)], (msgContextPtr)->reqData[(index) + 1u])) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGetReqDataAsU24At(msgContextPtr, index)              (Dcm_UtiMake32Bit(0, (msgContextPtr)->reqData[(index)], (msgContextPtr)->reqData[(index) + 1u], (msgContextPtr)->reqData[(index) + 2u])) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGetReqDataAsU32At(msgContextPtr, index)              (Dcm_UtiMake32Bit((msgContextPtr)->reqData[(index)], (msgContextPtr)->reqData[(index) + 1u], (msgContextPtr)->reqData[(index) + 2u], (msgContextPtr)->reqData[(index) + 3u])) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

# define Dcm_UtiGetReqDataAsU8Rel(msgContextPtr, index)              (Dcm_UtiGetReqDataAsU8At((msgContextPtr), ((msgContextPtr)->reqIndex + (index)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGetReqDataAsU16Rel(msgContextPtr, index)             (Dcm_UtiGetReqDataAsU16At((msgContextPtr), ((msgContextPtr)->reqIndex + (index)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGetReqDataAsU24Rel(msgContextPtr, index)             (Dcm_UtiGetReqDataAsU24At((msgContextPtr), ((msgContextPtr)->reqIndex + (index)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGetReqDataAsU32Rel(msgContextPtr, index)             (Dcm_UtiGetReqDataAsU32At((msgContextPtr), ((msgContextPtr)->reqIndex + (index)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

# define Dcm_UtiGetReqDataAsU8(msgContextPtr)                        (Dcm_UtiGetReqDataAsU8Rel((msgContextPtr), 0u))                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGetReqDataAsU16(msgContextPtr)                       (Dcm_UtiGetReqDataAsU16Rel((msgContextPtr), 0u))                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGetReqDataAsU24(msgContextPtr)                       (Dcm_UtiGetReqDataAsU24Rel((msgContextPtr), 0u))                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGetReqDataAsU32(msgContextPtr)                       (Dcm_UtiGetReqDataAsU32Rel((msgContextPtr), 0u))                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Return pointer to response buffer */
# define Dcm_UtiGetResDataRel(msgContextPtr, index)                  (Dcm_UtiGetResDataAt((msgContextPtr), ((msgContextPtr)->resIndex) + (index)))   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGetResData(msgContextPtr)                            (Dcm_UtiGetResDataRel((msgContextPtr), 0u))                                     /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

# define Dcm_UtiGetResDataAsU8At(msgContextPtr, index)               (*(Dcm_UtiGetResDataAt((msgContextPtr), (index))))                              /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGetResDataAsU16At(msgContextPtr, index)              (Dcm_UtiMake16Bit((msgContextPtr)->resData[(index) + 0u], (msgContextPtr)->resData[(index) + 1u])) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGetResDataAsU24At(msgContextPtr, index)              (Dcm_UtiMake32Bit(0, (msgContextPtr)->resData[(index) + 0u], (msgContextPtr)->resData[(index) + 1u], (msgContextPtr)->resData[(index) + 2u])) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_UtiGetResDataAsU32At(msgContextPtr, index)              (Dcm_UtiMake32Bit((msgContextPtr)->resData[(index) + 0u], (msgContextPtr)->resData[(index) + 1u], (msgContextPtr)->resData[(index) + 2u], (msgContextPtr)->resData[(index) + 3u])) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/***********************************************************************************************************************
 *  Dcm_UtiGetRuntimeUsageIterations()
 ***********************************************************************************************************************/
/*! \brief         Getter function for DCM_RUNTIME_USAGE_ITERATIONS.
 *  \details       -
 *  \return        Returns DCM_RUNTIME_USAGE_ITERATIONS.
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(uint8, DCM_CODE) Dcm_UtiGetRuntimeUsageIterations(
  void
  );

/**********************************************************************************************************************
 *  Dcm_UtiBitSetGetRowIdxSafe()
 *********************************************************************************************************************/
 /*! \brief          Returns the array index of the element within a bitset array that contains the requested bit.
  *  \details        -
  *  \param[in]      bitsetPosition       Position of the bit within the bitset
  *  \param[in]      bitsetSize           Number of elements in the bitset array
  *  \param[in]      bitsetBaseTypeSize   Size of the base type of the bitset array (in bit)
  *  \return         The array index
  *  \context        ISR1|ISR2|TASK
  *  \reentrant      TRUE
  *  \synchronous    TRUE
  *  \pre            -
  *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(uint16_least, DCM_CODE) Dcm_UtiBitSetGetRowIdxSafe(                                                                           /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  uint16_least bitsetPosition,
  uint16_least bitsetSize,
  uint8_least bitsetBaseTypeSize
  );

/**********************************************************************************************************************
 *  Dcm_UtiHandleApplNrc()
 *********************************************************************************************************************/
/*! \brief          Verifies application feedback plausibility and corrects NRC if needed.
 *  \details        Provides default NRC handling in case an application callout has "forgotten" to do it
 *  \param[in]      StdResultAppl   The callout result from the application
 *  \param[in,out]  ErrorCodeAppl   The NRC from the application callout (in) and corrected one (out)
 *  \param[in]      DefaultNrc      The NRC to be used for correction in case application has not set any appropriate one
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiHandleApplNrc(
  Std_ReturnType StdResultAppl,
  Dcm_NegativeResponseCodePtrType ErrorCodeAppl,
  Dcm_NegativeResponseCodeType DefaultNrc
  );

/**********************************************************************************************************************
 *  Dcm_UtiSetReqDataAsU8At()
 *********************************************************************************************************************/
/*! \brief          Set request value in response buffer at a particular position.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      index         Index to response buffer
 *  \param[in]      value         Value to copy to response buffer
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiSetReqDataAsU8At(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_DiagBufferIndexType index,
  uint8 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiSetReqDataAsU8()
 *********************************************************************************************************************/
/*! \brief          Set request value in response buffer at current position.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      value         Value to copy to response buffer
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiSetReqDataAsU8(
  Dcm_MsgContextPtrType pMsgContext,
  uint8 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiSetResDataAsU8At()
 *********************************************************************************************************************/
/*! \brief          Set response value in response buffer.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      index         Index to response buffer
 *  \param[in]      value         Value to copy to response buffer
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiSetResDataAsU8At(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_DiagBufferIndexType index,
  uint8 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiSetResDataAsU8Rel()
 *********************************************************************************************************************/
/*! \brief          Set response value in response buffer.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      index         Relative index to response signal
 *  \param[in]      value         Value to copy to response buffer
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiSetResDataAsU8Rel(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_DiagBufferIndexType index,
  uint8 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiSetResDataAsU32()
 *********************************************************************************************************************/
/*! \brief          Set response value in response buffer.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      value         Value to copy to response buffer
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiSetResDataAsU32(
  Dcm_MsgContextPtrType pMsgContext,
  uint32 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiSetResDataAsUN()
 *********************************************************************************************************************/
/*! \brief          Set response value in response buffer.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      pSource       Pointer to source buffer
 *  \param[in]      size          Size of response data that shall be copied
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiSetResDataAsUN(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_ConstReadOnlyMsgType pSource,
  Dcm_MsgLenType size
  );

/**********************************************************************************************************************
 *  Dcm_UtiUpdateResLength()
 *********************************************************************************************************************/
/*! \brief          Updates response length and remaining size of response buffer.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      numBytes      Number of bytes
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiUpdateResLength(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_MsgLenType numBytes
  );

/**********************************************************************************************************************
 *  Dcm_UtiProvideResData()
 *********************************************************************************************************************/
/*! \brief          Moves index of response buffer and updates response buffer parameters.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      numBytes      Number of bytes
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideResData(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_MsgLenType numBytes
  );

/**********************************************************************************************************************
 *  Dcm_UtiProvideResDataAsU8()
 *********************************************************************************************************************/
/*! \brief          Sets UINT8 Value in response buffer and updates response buffer parameters.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      value         Value to be written tor response buffer
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideResDataAsU8(
  Dcm_MsgContextPtrType pMsgContext,
  uint8 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiProvideResDataAsU16()
 *********************************************************************************************************************/
/*! \brief          Sets UINT16 Value in response buffer and updates response buffer parameters.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      value         Value to be written tor response buffer
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideResDataAsU16(
  Dcm_MsgContextPtrType pMsgContext,
  uint16 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiProvideResDataAsU24()
 *********************************************************************************************************************/
/*! \brief          Sets UINT24 Value in response buffer and updates response buffer parameters.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      value         Value to be written tor response buffer
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideResDataAsU24(
  Dcm_MsgContextPtrType pMsgContext,
  uint32 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiProvideResDataAsU32()
 *********************************************************************************************************************/
/*! \brief          Sets UINT32 Value in response buffer and updates response buffer parameters.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      value         Value to be written tor response buffer
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideResDataAsU32(
  Dcm_MsgContextPtrType pMsgContext,
  uint32 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiProvideResDataAsUN()
 *********************************************************************************************************************/
/*! \brief          Copies response data to response buffer and updates response buffer parameters.
 *  \details        Copy given number of bytes from source buffer to response buffer
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      pSource       Pointer to source buffer
 *  \param[in]      size          Size of response data that shall be copied
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideResDataAsUN(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_ConstReadOnlyMsgType pSource,
  Dcm_MsgLenType size
  );

/**********************************************************************************************************************
 *  Dcm_UtiGetRemainingResLenWithOffset()
*********************************************************************************************************************/
/*! \brief          Returns remaining response buffer size reduced by given offset.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      offset        Offset value
 *  \return         Remaining buffer size reduced by offset
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
*********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Dcm_MsgLenType, DCM_CODE) Dcm_UtiGetRemainingResLenWithOffset(
  Dcm_ReadOnlyMsgContextPtrType pMsgContext,
  Dcm_MsgLenType offset
  );

/**********************************************************************************************************************
 *  Dcm_UtiConsumeReqData()
 *********************************************************************************************************************/
/*! \brief          Moves index of request buffer and updates response length.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      numBytes      Number of bytes
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiConsumeReqData(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_MsgLenType numBytes
  );

/**********************************************************************************************************************
 *  Dcm_UtiConsumeReqDataAsU8()
 *********************************************************************************************************************/
/*! \brief          Returns UINT8 value from request and updates request buffer parameter.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[out]     pValue        Pointer where value is written
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiConsumeReqDataAsU8(
  Dcm_MsgContextPtrType pMsgContext,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) pValue
  );

/**********************************************************************************************************************
 *  Dcm_UtiConsumeReqDataAsU16()
 *********************************************************************************************************************/
/*! \brief          Returns UINT16 value from request and updates request buffer parameter.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[out]     pValue        Pointer where value is written
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiConsumeReqDataAsU16(
  Dcm_MsgContextPtrType pMsgContext,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) pValue
  );

/**********************************************************************************************************************
 *  Dcm_UtiConsumeReqDataAsU24()
 *********************************************************************************************************************/
/*! \brief          Returns UINT24 value from request and updates request buffer parameter.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[out]     pValue        Pointer where value is written
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiConsumeReqDataAsU24(
  Dcm_MsgContextPtrType pMsgContext,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) pValue
  );

/**********************************************************************************************************************
 *  Dcm_UtiConsumeReqDataAsUN()
 *********************************************************************************************************************/
/*! \brief          Returns specified number of bytes from request buffer and updates request buffer parameters.
 *  \details        -
 *  \param[in,out]  pMsgContext         Current message context
 *  \param[out]     pTarget             Pointer to target buffer
 *  \param[in]      sizeOfTargetBuffer  Size of target buffer
 *  \param[in]      numBytes            Number of bytes to be copied
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiConsumeReqDataAsUN(
  Dcm_MsgContextPtrType pMsgContext,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) pTarget,
  Dcm_MsgLenType sizeOfTargetBuffer,
  Dcm_MsgLenType numBytes
  );

/**********************************************************************************************************************
 *  Dcm_UtiMsgContextVerifySize()
 *********************************************************************************************************************/
/*! \brief          Checks if the remaining buffer size is large enough.
 *  \details        -
 *  \param[in]      pMsgContext    Current message context
 *  \param[in]      numBytes       Number of bytes to be copied
 *  \param[out]     ErrorCode      Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK       Remaining buffer size is large enough
 *  \return         DCM_E_NOT_OK   Remaining buffer size is not large enough
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiMsgContextVerifySize(
  Dcm_ReadOnlyMsgContextPtrType pMsgContext,
  Dcm_MsgLenType numBytes,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/**********************************************************************************************************************
 *  Dcm_UtiInitDataContext()
 *********************************************************************************************************************/
/*! \brief          Initializes managed buffer data context.
 *  \details        -
 *  \param[out]     pDataContext    Pointer to the data context to be initialized
 *  \param[in]      Buffer          The buffer to be managed
 *  \param[in]      BufferSize      The size of the buffer to be managed
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiInitDataContext(
  Dcm_DiagDataContextPtrType pDataContext,
  Dcm_MsgType Buffer,
  Dcm_MsgLenType BufferSize
  );

/**********************************************************************************************************************
 *  Dcm_UtiDataContextSetAvailLen()
 *********************************************************************************************************************/
/*! \brief          Sets the available length of the data context.
 *  \details        Updates only the availability information, no data will be changed.
 *  \param[in,out]  pDataContext    Pointer to the data context
 *  \param[in]      length          New length
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            The new length must be smaller than or equal to the current available length
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiDataContextSetAvailLen(
  Dcm_DiagDataContextPtrType pDataContext,
  Dcm_MsgLenType length
  );

/**********************************************************************************************************************
 *  Dcm_UtiDataContextCheckSize()
 *********************************************************************************************************************/
/*! \brief          Checks if the size of the referenced buffer is large enough.
 *  \details        -
 *  \param[in]      pDataContext    Pointer to the data context
 *  \param[in]      size            Number of bytes
 *  \return         TRUE            Buffer size is large enough
 *  \return         FALSE           Buffer size is not large enough
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(boolean, DCM_CODE) Dcm_UtiDataContextCheckSize(
  Dcm_DiagDataContextConstPtrType pDataContext,
  Dcm_MsgLenType size
  );

/**********************************************************************************************************************
 *  Dcm_UtiDataContextVerifySize()
 *********************************************************************************************************************/
/*! \brief          Verifies that the size of the referenced buffer is large enough.
 *  \details        -
 *  \param[in]      pDataContext    Pointer to the data context
 *  \param[in]      size            Number of bytes
 *  \param[out]     ErrorCode       Negative response code in case return value is DCM_E_NOT_OK
 *  \return         DCM_E_OK        Buffer size is large enough
 *  \return         DCM_E_NOT_OK    Buffer size is not large enough
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiDataContextVerifySize(
  Dcm_DiagDataContextConstPtrType pDataContext,
  Dcm_MsgLenType size,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );

/**********************************************************************************************************************
 *  Dcm_UtiRevertData()
 *********************************************************************************************************************/
/*! \brief          Reverts a specific amount of the data from a data context.
 *  \details        Updates only the usage information, no data will be changed.
 *  \param[in,out]  pDataContext    Pointer to the data context
 *  \param[in]      length          Number of bytes to commit
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiRevertData(
  Dcm_DiagDataContextPtrType pDataContext,
  Dcm_MsgLenType length
  );

/**********************************************************************************************************************
 *  Dcm_UtiGetDataContextBuffer()
 *********************************************************************************************************************/
/*! \brief          Provides pointer to data context buffer.
 *  \details        Provides pointer to current usage position of data context buffer
 *  \param[in]      pDataContext    Pointer to the data context
 *  \return         Pointer to current usage position of data context buffer
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(Dcm_MsgType, DCM_CODE) Dcm_UtiGetDataContextBuffer(
  Dcm_DiagDataContextPtrType pDataContext
  );

/**********************************************************************************************************************
 *  Dcm_UtiSetDataAsU8At()
 *********************************************************************************************************************/
/*! \brief          Set value in data context buffer.
 *  \details        -
 *  \param[in,out]  pDataContext  Data context
 *  \param[in]      index         Position within the buffer
 *  \param[in]      value         Value to copy into buffer
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiSetDataAsU8At(
  Dcm_DiagDataContextPtrType pDataContext,
  Dcm_MsgLenType index,
  uint8 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiSetDataAsU8Rel()
 *********************************************************************************************************************/
/*! \brief          Set value in data context buffer.
 *  \details        -
 *  \param[in,out]  pDataContext  Data context
 *  \param[in]      index         Position relative to the current usage of the buffer
 *  \param[in]      value         Value to copy into buffer
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiSetDataAsU8Rel(                                                                                        /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_DiagDataContextPtrType pDataContext,
  Dcm_MsgLenType index,
  uint8 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiProvideDataAsU8()
 *********************************************************************************************************************/
/*! \brief          Provides data to the current data context.
 *  \details        Updates the usage information after writing to the buffer.
 *  \param[in,out]  pDataContext    Pointer to the data context
 *  \param[in]      value           Value to be written
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideDataAsU8(
  Dcm_DiagDataContextPtrType pDataContext,
  uint8 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiProvideDataAsU16()
 *********************************************************************************************************************/
/*! \brief          Provides data to the current data context.
 *  \details        Updates the usage information after writing to the buffer.
 *  \param[in,out]  pDataContext    Pointer to the data context
 *  \param[in]      value           Value to be written
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideDataAsU16(
  Dcm_DiagDataContextPtrType pDataContext,
  uint16 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiProvideDataAsU24()
 *********************************************************************************************************************/
/*! \brief          Provides data to the current data context.
 *  \details        Updates the usage information after writing to the buffer. Only the three lower bytes are written.
 *  \param[in,out]  pDataContext    Pointer to the data context
 *  \param[in]      value           Value to be written
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideDataAsU24(
  Dcm_DiagDataContextPtrType pDataContext,
  uint32 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiProvideDataAsU32()
 *********************************************************************************************************************/
/*! \brief          Provides data to the current data context.
 *  \details        Updates the usage information after writing to the buffer.
 *  \param[in,out]  pDataContext    Pointer to the data context
 *  \param[in]      value           Value to be written
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideDataAsU32(
  Dcm_DiagDataContextPtrType pDataContext,
  uint32 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiProvideDataAsF32()
 *********************************************************************************************************************/
/*! \brief          Provides data to the current data context.
 *  \details        Updates the usage information after writing to the buffer.
 *  \param[in,out]  pDataContext    Pointer to the data context
 *  \param[in]      value           Value to be written
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideDataAsF32(
  Dcm_DiagDataContextPtrType pDataContext,
  float32 value,
  Dcm_EndiannessType endianness
  );

/**********************************************************************************************************************
 *  Dcm_UtiProvideDataAsUN()
 *********************************************************************************************************************/
/*! \brief          Provides data to the current data context.
 *  \details        Updates the usage information after writing to the buffer.
 *  \param[in,out]  pDataContext    Pointer to the data context
 *  \param[in]      pSource         Pointer to source buffer
 *  \param[in]      length          Number of bytes to commit
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiProvideDataAsUN(
  Dcm_DiagDataContextPtrType pDataContext,
  Dcm_ConstReadOnlyMsgType pSource,
  Dcm_MsgLenType length
  );
# define DCM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define DCM_START_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_UtiLookUpUint16()
 *********************************************************************************************************************/
/*! \brief          Searches a word table for an element.
 *  \details        -
 *  \param[in]      lookUpTable    Pointer to the table to be scanned (first element is table-size!)
 *  \param[in]      value          Value to be found
 *  \return         -1             Look up failed (no match)
 *  \return         >=0            Success, index of the matched position
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \pre            Total number of elements for look up shall be < 32768.
 *********************************************************************************************************************/
FUNC(sint16_least, DCM_CODE) Dcm_UtiLookUpUint16(
  P2CONST(uint16, AUTOMATIC, DCM_CONST) lookUpTable,
  uint16 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiGetBitPosition()
 *********************************************************************************************************************/
/*! \brief          Returns the position of the most left set bit in a bit set.
 *  \details        -
 *  \param[in]      bitSet    A bit-set with only one bit set in it.
 *  \return         Returns the position of the set bit
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(uint8, DCM_CODE) Dcm_UtiGetBitPosition(
  uint32 bitSet
  );

/**********************************************************************************************************************
 *  Dcm_UtiLookUpUint8()
 *********************************************************************************************************************/
/*! \brief          Searches a byte table for an element.
 *  \details        -
 *  \param[in]      lookUpTable    Pointer to the table to be scanned
 *  \param[in]      value          Value to be found (first element is table-size!)
 *  \return         -1             Look up failed (no match)
 *  \return         >=0            Success, index of the matched position
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(sint16_least, DCM_CODE) Dcm_UtiLookUpUint8(
  Dcm_Uint8ConstDataPtrType lookUpTable,
  uint8 value
  );

# if (DCM_UTI_NVM_READ_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_UtiNvMRead()
 *********************************************************************************************************************/
/*! \brief          Reads a NvM data block.
 *  \details        -
 *  \param[in]      opStatus     The operation status
 *  \param[out]     data         Data buffer for the result
 *  \param[in]      blockId      Id of the NvRam block
 *  \return         DCM_E_OK        Read operation finished successfully.
 *  \return         DCM_E_NOT_OK    Read operation finished with error or got canceled.
 *  \return         DCM_E_PENDING   Read operation needs more time to be accomplished.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiNvMRead(
  Dcm_OpStatusType opStatus,
  Dcm_GenericDcmRamNoInitPtrType data,
  uint16 blockId
  );
# endif

# if (DCM_UTI_NVM_WRITE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_UtiNvMWrite()
 *********************************************************************************************************************/
/*! \brief          Writes a NvM data block.
 *  \details        -
 *  \param[in]      opStatus     The operation status
 *  \param[in]      data         Data buffer of the content to be written
 *  \param[in]      blockId      Id of the NvRam block
 *  \return         DCM_E_OK        Write operation finished successfully.
 *  \return         DCM_E_NOT_OK    Write operation finished with error or got canceled.
 *  \return         DCM_E_PENDING   Write operation needs more time to be accomplished.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiNvMWrite(
  Dcm_OpStatusType opStatus,
  Dcm_GenericDcmConstRamNoInitPtrType data,
  uint16 blockId
  );
# endif

# if (DCM_UTI_NVM_WRITE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_UtiNvMSwcDataWrite()
 *********************************************************************************************************************/
/*! \brief          Writes a NvM data block that is used by a SW-C.
 *  \details        -
 *  \param[in]      opStatus     The operation status
 *  \param[in]      data         Data buffer of the content to be written
 *  \param[in]      blockId      Id of the NvRam block
 *  \return         DCM_E_OK        Write operation finished successfully.
 *  \return         DCM_E_NOT_OK    Write operation finished with error or got canceled.
 *  \return         DCM_E_PENDING   Write operation needs more time to be accomplished.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiNvMSwcDataWrite(
  Dcm_OpStatusType opStatus,
  Dcm_GenericDcmConstRamNoInitPtrType data,
  uint16 blockId
  );
# endif

# if (DCM_UTI_NVM_SET_RAM_BLOCK_STATUS_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_UtiNvMSetRamBlockStatus()
 *********************************************************************************************************************/
/*! \brief          Sets the NvRam block status to true.
 *  \details        -
 *  \param[in]      blockId      Id of the NvRam block
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_UtiNvMSetRamBlockStatus(
  uint16 blockId
  );
# endif

/**********************************************************************************************************************
 *  Dcm_UtiConvertToUint16Array()
 *********************************************************************************************************************/
/*! \brief          Converts an uint8 array to an uint16 array.
 *  \details        Copies the data from the given uint8 source pointer to the uint16 target pointer considering the
 *                  target endiannes.
 *  \param[in]      sourcePtr          Pointer to the source array
 *  \param[out]     targetPtr          Pointer to the target array
 *  \param[in]      targetSize         Size of the target array (not the number of bytes)
 *  \param[in]      targetEndiannes    The endianness of the target
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_UtiConvertToUint16Array(
  Dcm_ConstReadOnlyMsgType sourcePtr,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) targetPtr,
  Dcm_MsgLenType targetSize,
  Dcm_EndiannessType targetEndiannes
  );

/**********************************************************************************************************************
 *  Dcm_UtiConvertToUint32Array()
 *********************************************************************************************************************/
/*! \brief          Converts an uint8 array to an uint32 array.
 *  \details        Copies the data from the given uint8 source pointer to the uint32 target pointer considering the
 *                  target endiannes.
 *  \param[in]      sourcePtr          Pointer to the source array
 *  \param[out]     targetPtr          Pointer to the target array
 *  \param[in]      targetSize         Size of the target array (not the number of bytes)
 *  \param[in]      targetEndiannes    The endianness of the target
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_UtiConvertToUint32Array(
  Dcm_ConstReadOnlyMsgType sourcePtr,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) targetPtr,
  Dcm_MsgLenType targetSize,
  Dcm_EndiannessType targetEndiannes
  );

/**********************************************************************************************************************
 *  Dcm_UtiConvertToFloat32Array()
 *********************************************************************************************************************/
/*! \brief          Converts an uint8 array to an float32 array.
 *  \details        Copies the data from the given uint8 source pointer to the float32 target pointer considering the
 *                  target endiannes.
 *  \param[in]      sourcePtr          Pointer to the source array
 *  \param[out]     targetPtr          Pointer to the target array
 *  \param[in]      targetSize         Size of the target array (not the number of bytes)
 *  \param[in]      targetEndiannes    The endianness of the target
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_UtiConvertToFloat32Array(
  Dcm_ConstReadOnlyMsgType sourcePtr,
  P2VAR(float32, AUTOMATIC, AUTOMATIC) targetPtr,
  Dcm_MsgLenType targetSize,
  Dcm_EndiannessType targetEndiannes
  );

/**********************************************************************************************************************
 *  Dcm_UtiResetRuntimeLimiter()
 *********************************************************************************************************************/
/*! \brief          Reset runtime limiter.
 *  \details        -
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_UtiResetRuntimeLimiter(
  void
  );

/**********************************************************************************************************************
 *  Dcm_UtiRuntimeLimitReached()
 *********************************************************************************************************************/
/*! \brief          Verifies whether the runtime limit is reached.
 *  \details        -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_UtiRuntimeLimitReached(
  void
  );

/**********************************************************************************************************************
 *  Dcm_UtiLookUpRangeUint16()
 *********************************************************************************************************************/
/*! \brief          Searches a word in a table of ranges.
 *  \details        -
 *  \param[in]      lookUpTable    Pointer to the table to be scanned (first element is table-size!)
 *  \param[in]      value          Value to be found
 *  \return         -1             Look up failed (no match)
 *  \return         >=0            Success, index of the matched position
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \pre            Total number of elements for look up shall be < 32768.
 *********************************************************************************************************************/
FUNC(sint16_least, DCM_CODE) Dcm_UtiLookUpRangeUint16(
  P2CONST(Dcm_UtiU16RangeType, AUTOMATIC, DCM_CONST) lookUpTable,
  uint16 value
  );

/**********************************************************************************************************************
 *  Dcm_UtiMemCopySafe()
 *********************************************************************************************************************/
 /*! \brief          Copies data from the given source pointer to the target pointer.
  *  \details        This function is a wrapper for Dcm_UtiMemCopy with additional checks of the input parameter.
  *  \param[in]      sourcePtr    Pointer to the source buffer
  *  \param[in]      targetPtr    Pointer to the target buffer
  *  \param[in]      targetPos    Buffer position where the data should be written to
  *  \param[in]      targetSize   Size of the target buffer
  *  \param[in]      length       Amount of data which should be written
  *  \context        ISR1|ISR2|TASK
  *  \reentrant      FALSE
  *  \synchronous    TRUE
  *  \pre            -
  *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_UtiMemCopySafe(
  Dcm_ConstReadOnlyMsgType sourcePtr,
  Dcm_ConstMsgType targetPtr,
  Dcm_MsgLenType targetPos,
  Dcm_MsgLenType targetSize,
  Dcm_MsgLenType length
  );

/**********************************************************************************************************************
 *  Dcm_UtiCommitData()
 *********************************************************************************************************************/
/*! \brief          Commits the data usage to a data context.
 *  \details        Updates only the usage information, no data will be changed.
 *  \param[in,out]  pDataContext    Pointer to the data context
 *  \param[in]      length          Number of bytes to commit
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_UtiCommitData(
  Dcm_DiagDataContextPtrType pDataContext,
  Dcm_MsgLenType length
  );

/**********************************************************************************************************************
 *  Dcm_UtiGetResDataAt()
 *********************************************************************************************************************/
/*! \brief          Returns pointer to response buffer.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      index         Index to response buffer
 *  \return         Pointer to requested index of response buffer
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_MsgType, DCM_CODE) Dcm_UtiGetResDataAt(
  Dcm_ReadOnlyMsgContextPtrType pMsgContext,
  Dcm_DiagBufferIndexType index
  );

# if (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON) || \
     (DCM_FBLMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_UtiConvMemoryOpResult()
 *********************************************************************************************************************/
/*! \brief          Converts memory operation result to standard result type.
 *  \details        -
 *  \param[in]      memOpResult   Memory operation result
 *  \param[in]      opStatus      Current operation status
 *  \param[out]     unknown       Indicates whether the memOpResult is a known valid value
 *                  TRUE          memOpResult is not valid
 *                  FALSE         memOpResult is valid
 *  \param[in,out]  ErrorCode     The NRC from application and result to diag core
 *  \return         Operation result
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiConvMemoryOpResult(
  Dcm_ReturnReadWriteMemoryType memOpResult,
  Dcm_OpStatusType opStatus,
  P2VAR(boolean, AUTOMATIC, DCM_VAR_NOINIT) unknown,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
# endif

# if (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON) || \
     (DCM_FBLMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_UtiDwordExtract()
 *********************************************************************************************************************/
/*! \brief          Extracts a double word from request.
 *  \details        -
 *  \param[in,out]  pMsgContext        The current request context
 *  \param[in]      numBytes           The number of bytes to extract from the request
 *  \return                            The extracted double word
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(uint32, DCM_CODE) Dcm_UtiDwordExtract(
  Dcm_MsgContextPtrType pMsgContext,
  uint8_least numBytes
  );

/**********************************************************************************************************************
 *  Dcm_UtiValidateAndGetAlfid()
 *********************************************************************************************************************/
/*! \brief          Validates the request memory ALFID and extracts it from request.
 *  \details        -
 *  \param[in,out]  pMsgContext        Requested memory data starting with the ALFID byte.
 *  \param[in]      lookUpTable        Pointer to the table to be scanned
 *  \param[out]     pAlfid             ALFID byte
 *  \param[out]     pBlockLength       Returns the left part of the stream (i.e. without protocol header)
 *  \param[out]     ErrorCode          The NRC
 *  \return         DCM_E_OK           no error found
 *  \return         DCM_E_NOT_OK       invalid ALFID (NRC is set to ErrorCode)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            The request data within the pMsgContext must contain an ALFID byte.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiValidateAndGetAlfid(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_Uint8ConstDataPtrType lookUpTable,
  Dcm_Uint8VarDataPtrType pAlfid,
  Dcm_Uint8VarDataPtrType pBlockLength,
  Dcm_NegativeResponseCodePtrType ErrorCode
  );
# endif
# define DCM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#endif /* !defined(DCM_UTILSINT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_UtilsInt.h
 *********************************************************************************************************************/
