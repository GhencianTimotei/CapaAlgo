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
/*!        \file  Com_Serializer.c
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/
#define COM_SERIALIZER_SOURCE

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Com.h"
#include "Com_Serializer.h"

/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
**********************************************************************************************************************/
#if !defined (COM_LOCAL_INLINE)
# define COM_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#if ((COM_TXBUFFERUSEDOFTXSIGINFO == STD_ON) && (CPU_BYTE_ORDER == HIGH_BYTE_FIRST))
/**********************************************************************************************************************
  Com_Signal_getLSBSignalApplSourcePtr
**********************************************************************************************************************/
/*! \brief        This method returns the LSB pointer to application memory where the signal is located. This function should
 *                only be used if the configured byte order equals high byte order.
    \details      -
    \pre          -
    \param[in]    SignalApplSourcePtr Pointer to application memory where the signal is located
    \param[in]    SignalId Id of Signal
    \return       const uint8*
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(P2CONST(uint8, AUTOMATIC, COM_APPL_DATA), COM_CODE) Com_Signal_getLSBSignalApplSourcePtr(Com_TxSigInfoIterType SignalId,
                                                                                                               P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SignalApplSourcePtr);
#endif

#if ((COM_TXBUFFERUSEDOFTXSIGINFO == STD_ON) && ((COM_EXISTS_NBITNBYTE_BUSACCOFTXSIGINFO == STD_ON) || (COM_EXISTS_NBITNBYTE_SW_BUSACCOFTXSIGINFO == STD_ON)))
/**********************************************************************************************************************
  Com_Signal_WriteSignal_NBITNBYTE
**********************************************************************************************************************/
/*! \brief            This method writes a signal to the indicated buffer (i.e. ipdu buffer or shadow buffer)
    \details          -
    \pre              -
    \param[in]        SignalId
    \param[in,out]    SignalBusDestPtr    Valid pointer to TxBuffer, where the source signal is written to. Pointer has always
                                          to point on LSB.
    \param[in]        SignalApplSourcePtr Pointer to application memory where the signal is located
    \param[in]        signalStartBit      bit index in the byte, where the signal starts (0..7)
    \param[in]        isBusBigEndian      flag, if bus is big endian.
    \context          TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_WriteSignal_NBITNBYTE(Com_TxSigInfoIterType SignalId,
                                                                       P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SignalApplSourcePtr,
                                                                       Com_BitPositionOfTxSigInfoType signalStartBit, P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusDestPtr, boolean isBusBigEndian);
#endif

#if ((COM_TXBUFFERUSEDOFTXSIGINFO == STD_ON)  && ((COM_EXISTS_NBYTE_BUSACCOFTXSIGINFO == STD_ON) || (COM_EXISTS_NBYTE_SW_BUSACCOFTXSIGINFO == STD_ON) || (COM_EXISTS_ARRAY_BASED_BUSACCOFTXSIGINFO == STD_ON)))
/**********************************************************************************************************************
  Com_Signal_GetTxBufferLength
**********************************************************************************************************************/
/*! \brief        This method returns the Tx Buffer Length of the Signal in bytes.
    \details      -
    \pre          -
    \param[in]    SignalId            ID of the signal to be written to
    \return       Com_TxBufferLengthOfTxSigInfoType
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_TxBufferLengthOfTxSigInfoType, COM_CODE) Com_Signal_GetTxBufferLength(Com_TxSigInfoIterType SignalId);
#endif

/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

#if ((COM_TXBUFFERUSEDOFTXSIGINFO == STD_ON) && (CPU_BYTE_ORDER == HIGH_BYTE_FIRST))
/**********************************************************************************************************************
  Com_Signal_getLSBSignalApplSourcePtr
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(P2CONST(uint8, AUTOMATIC, COM_APPL_DATA), COM_CODE) Com_Signal_getLSBSignalApplSourcePtr(Com_TxSigInfoIterType SignalId,
                                                                                                               P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SignalApplSourcePtr)
{

  /* *INDENT-OFF* */
  /* Motorola plattform specific implementation
     We start writing with the lsb (writing from right to left). To do so it is required to know
     the byte of the lsb. This is not the SignalApplSourcePtr as this one always points to the leftmost
     byte. For motorola systems, this is the byte of the msb.
     Reason: Easier code generation + it is easier to start writing with the lsb and counting
     bits "downwards" to the msb. SignalBusDestPtr points always to the lsb of motorola or intel bus
     signals. */
  /* *INDENT-ON* */

  P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SignalApplSourcePtrIntern = SignalApplSourcePtr;

  switch (Com_GetApplTypeOfTxSigInfo(SignalId)) /* PRQA S 3315 */ /* MD_Com_3315 */
  {
# if (COM_EXISTS_UINT16_APPLTYPEOFTXSIGINFO == STD_ON)
    case COM_UINT16_APPLTYPEOFTXSIGINFO:
      SignalApplSourcePtrIntern = &SignalApplSourcePtrIntern[1];
      break;
# endif
# if (COM_EXISTS_SINT16_APPLTYPEOFTXSIGINFO == STD_ON)
    case COM_SINT16_APPLTYPEOFTXSIGINFO:
      SignalApplSourcePtrIntern = &SignalApplSourcePtrIntern[1];
      break;
# endif
# if (COM_EXISTS_UINT32_APPLTYPEOFTXSIGINFO == STD_ON)
    case COM_UINT32_APPLTYPEOFTXSIGINFO:
      SignalApplSourcePtrIntern = &SignalApplSourcePtrIntern[3];
      break;
# endif
# if (COM_EXISTS_SINT32_APPLTYPEOFTXSIGINFO == STD_ON)
    case COM_SINT32_APPLTYPEOFTXSIGINFO:
      SignalApplSourcePtrIntern = &SignalApplSourcePtrIntern[3];
      break;
# endif
# if (COM_EXISTS_FLOAT32_APPLTYPEOFTXSIGINFO == STD_ON)
    case COM_FLOAT32_APPLTYPEOFTXSIGINFO:
      SignalApplSourcePtrIntern = &SignalApplSourcePtrIntern[3];
      break;
# endif
# if (COM_EXISTS_UINT64_APPLTYPEOFTXSIGINFO == STD_ON)
    case COM_UINT64_APPLTYPEOFTXSIGINFO:
      SignalApplSourcePtrIntern = &SignalApplSourcePtrIntern[7];
      break;
# endif
# if (COM_EXISTS_SINT64_APPLTYPEOFTXSIGINFO == STD_ON)
    case COM_SINT64_APPLTYPEOFTXSIGINFO:
      SignalApplSourcePtrIntern = &SignalApplSourcePtrIntern[7];
      break;
# endif
# if (COM_EXISTS_FLOAT64_APPLTYPEOFTXSIGINFO == STD_ON)
    case COM_FLOAT64_APPLTYPEOFTXSIGINFO:
      SignalApplSourcePtrIntern = &SignalApplSourcePtrIntern[7];
      break;
# endif
# if (COM_EXISTS_SINT8_APPLTYPEOFTXSIGINFO == STD_ON)
    case COM_SINT8_APPLTYPEOFTXSIGINFO:
# endif
# if (COM_EXISTS_UINT8_APPLTYPEOFTXSIGINFO == STD_ON)
    case COM_UINT8_APPLTYPEOFTXSIGINFO:
# endif
# if (COM_EXISTS_UINT8_N_APPLTYPEOFTXSIGINFO == STD_ON)
    case COM_UINT8_N_APPLTYPEOFTXSIGINFO:
# endif
# if (COM_EXISTS_UINT8_DYN_APPLTYPEOFTXSIGINFO == STD_ON)
    case COM_UINT8_DYN_APPLTYPEOFTXSIGINFO:
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  COM_DUMMY_STATEMENT(SignalId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return SignalApplSourcePtrIntern;
}
#endif

#if ((COM_TXBUFFERUSEDOFTXSIGINFO == STD_ON) && ((COM_EXISTS_NBITNBYTE_BUSACCOFTXSIGINFO == STD_ON) || (COM_EXISTS_NBITNBYTE_SW_BUSACCOFTXSIGINFO == STD_ON)))
/**********************************************************************************************************************
  Com_Signal_WriteSignal_NBITNBYTE
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 ********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_WriteSignal_NBITNBYTE(Com_TxSigInfoIterType SignalId,  /* COV_WRITESIGNAL_NBITNBYTE_XX */
                                                                       P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SignalApplSourcePtr, Com_BitPositionOfTxSigInfoType signalStartBit,
                                                                       P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusDestPtr, boolean isBusBigEndian)
{
  uint8 mask;
  uint8 tmpByte;
  sint16_least i;

  uint16 maskCounter = 8u - (uint16) signalStartBit;
  Com_BitLengthOfTxSigInfoType signalBitCount = Com_GetBitLengthOfTxSigInfo(SignalId);

  /* #10 Write LSB of the passed signal */
  *SignalBusDestPtr &= COM_CAST2UINT8(~COM_CAST2UINT8(255u << signalStartBit)); /* SBSW_COM_VALID_PTR_BY_COMSTACK_01 */
  *SignalBusDestPtr |= COM_CAST2UINT8(*SignalApplSourcePtr << signalStartBit);  /* SBSW_COM_VALID_PTR_BY_COMSTACK_01 */

  /* #20 If more than 8 bits have to be copied */
  for(i = 1; i < ((sint16_least) Com_GetTxBufferLengthOfTxSigInfo(SignalId) - 1); i++)  /* COV_WRITESIGNAL_NBITNBYTE_XX */
  {
    /* #30 Copy all full bytes, byte align the source byte before it is copied */
# if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    tmpByte = COM_CAST2UINT8(SignalApplSourcePtr[-i + 1] >> (8u - signalStartBit));
    tmpByte |= COM_CAST2UINT8(SignalApplSourcePtr[-i] << signalStartBit);
# else
    tmpByte = COM_CAST2UINT8(SignalApplSourcePtr[i - 1] >> (8u - signalStartBit));
    tmpByte |= COM_CAST2UINT8(SignalApplSourcePtr[i] << signalStartBit);
# endif

# if ((COM_EXISTS_NBITNBYTE_BUSACCOFTXSIGINFO == STD_ON) && (COM_EXISTS_NBITNBYTE_SW_BUSACCOFTXSIGINFO == STD_ON))
    /* If little endian and big endian signals exist */
    SignalBusDestPtr[Com_NBITNBYTE_GetEndiannesIndex(i, isBusBigEndian)] = tmpByte;     /* SBSW_COM_VALID_PTR_BY_COMSTACK_02 */ /* COV_COM_NBITNBYTE_ENDIANNESS */
# elif (((CPU_BYTE_ORDER == HIGH_BYTE_FIRST)&&(COM_EXISTS_NBITNBYTE_BUSACCOFTXSIGINFO == STD_ON)) || ((CPU_BYTE_ORDER == LOW_BYTE_FIRST) && (COM_EXISTS_NBITNBYTE_SW_BUSACCOFTXSIGINFO == STD_ON)))
    /* #40 If bus signal is big endian, write with negative loop index as pointer is pointing to LSB (last byte). */
    SignalBusDestPtr[-i] = tmpByte;     /* SBSW_COM_VALID_PTR_BY_COMSTACK_02 */
# else
    /* #50 If bus signal is little endian, write with positive loop index as pointer is pointing to LSB (first byte). */
    SignalBusDestPtr[i] = tmpByte;      /* SBSW_COM_VALID_PTR_BY_COMSTACK_02 */
# endif
    maskCounter += 8u;
  }

# if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  tmpByte = COM_CAST2UINT8(SignalApplSourcePtr[-i + 1] >> (8u - signalStartBit));

  if(COM_CAST2UINT8(i) <= (COM_CAST2UINT8(signalBitCount - 1u) >> 3u))
  {
    tmpByte |= COM_CAST2UINT8(SignalApplSourcePtr[-i] << signalStartBit);
  }
# else
  tmpByte = COM_CAST2UINT8(SignalApplSourcePtr[i - 1] >> (8u - signalStartBit));

  if(COM_CAST2UINT8(i) <= (COM_CAST2UINT8(signalBitCount - 1u) >> 3u))
  {
    tmpByte |= COM_CAST2UINT8(SignalApplSourcePtr[i] << signalStartBit);
  }
# endif

  mask = COM_CAST2UINT8(255u >> (8u - (signalBitCount - maskCounter)));

# if ((COM_EXISTS_NBITNBYTE_BUSACCOFTXSIGINFO == STD_ON) && (COM_EXISTS_NBITNBYTE_SW_BUSACCOFTXSIGINFO == STD_ON))
  i = (sint16_least) Com_NBITNBYTE_GetEndiannesIndex(i, isBusBigEndian);        /* COV_COM_NBITNBYTE_ENDIANNESS */
# elif (((CPU_BYTE_ORDER == HIGH_BYTE_FIRST)&&(COM_EXISTS_NBITNBYTE_BUSACCOFTXSIGINFO == STD_ON)) || ((CPU_BYTE_ORDER == LOW_BYTE_FIRST) && (COM_EXISTS_NBITNBYTE_SW_BUSACCOFTXSIGINFO == STD_ON)))
  /* For big endian bus signals */
  i = -i;
# endif
  /* #60 Copy the remaining bits of last byte to the destination buffer */
  SignalBusDestPtr[i] = (SignalBusDestPtr[i] & COM_CAST2UINT8(~mask)) | (tmpByte & mask);       /* SBSW_COM_VALID_PTR_BY_COMSTACK_02 */

  COM_DUMMY_STATEMENT(isBusBigEndian);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if ((COM_TXBUFFERUSEDOFTXSIGINFO == STD_ON)  && ((COM_EXISTS_NBYTE_BUSACCOFTXSIGINFO == STD_ON) || (COM_EXISTS_NBYTE_SW_BUSACCOFTXSIGINFO == STD_ON) || (COM_EXISTS_ARRAY_BASED_BUSACCOFTXSIGINFO == STD_ON)))
/**********************************************************************************************************************
  Com_Signal_GetTxBufferLength
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(Com_TxBufferLengthOfTxSigInfoType, COM_CODE) Com_Signal_GetTxBufferLength(Com_TxSigInfoIterType SignalId)
{
  Com_TxBufferLengthOfTxSigInfoType txBufferLength;
# if ((COM_TXTPINFOUSEDOFTXPDUINFO == STD_ON) && (COM_EXISTS_UINT8_DYN_APPLTYPEOFTXSIGINFO == STD_ON))
  /* #10 If the passed signal is a dynamic length signal return the current dynamic byte length */
  if(Com_GetApplTypeOfTxSigInfo(SignalId) == COM_UINT8_DYN_APPLTYPEOFTXSIGINFO) /* COV_COM_UINT8_DYN_APPLTYPE */
  {
    Com_TxTpInfoIdxOfTxPduInfoType txTpPduInfoIdx = Com_GetTxTpInfoIdxOfTxPduInfo(Com_GetTxPduInfoIdxOfTxSigInfo(SignalId));
    txBufferLength = (Com_TxBufferLengthOfTxSigInfoType) Com_GetTxDynSignalLength(txTpPduInfoIdx);
  }
  /* #20 Otherwise use the static Tx Buffer Length */
  else
# endif
  {
    txBufferLength = Com_GetTxBufferLengthOfTxSigInfo(SignalId);
  }

  return txBufferLength;
}
#endif

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_TXBUFFERUSEDOFTXSIGINFO == STD_ON)
/**********************************************************************************************************************
  Com_Signal_WriteSignal
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, COM_CODE) Com_Signal_WriteSignal(Com_TxSigInfoIterType SignalId, P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SignalApplSourcePtr)
{
  P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SignalApplSourcePtrInternal = SignalApplSourcePtr;   /* PRQA S 2981 */ /* MD_MSR_RetVal */
# if ((COM_EXISTS_NBIT_BUSACCOFTXSIGINFO == STD_ON) || (COM_EXISTS_NBITNBYTE_BUSACCOFTXSIGINFO == STD_ON) || (COM_EXISTS_NBITNBYTE_SW_BUSACCOFTXSIGINFO == STD_ON))
  Com_BitPositionOfTxSigInfoType signalStartBit = Com_Signal_BitOffsetFromBitPos(Com_GetBitPositionOfTxSigInfo(SignalId));
# endif

# if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* #10 Set the source pointer to the least significant byte, if the CPU byte order is HIGH_BYTE_FIRST */
  SignalApplSourcePtrInternal = Com_Signal_getLSBSignalApplSourcePtr(SignalId, SignalApplSourcePtrInternal);    /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
# endif

  /* #20 If the bus access is type is */
  switch (Com_GetBusAccOfTxSigInfo(SignalId))
  {
# if (COM_EXISTS_NBIT_BUSACCOFTXSIGINFO == STD_ON)
    case (COM_NBIT_BUSACCOFTXSIGINFO): /* COV_COM_N_BIT_X */
    {
      /* #30 NBIT: copy the specific bits from the source pointer to the destination pointer */
      uint8 signalBusDest = Com_GetTxBuffer(Com_GetTxBufferStartIdxOfTxSigInfo(SignalId));

      uint8 mask = COM_CAST2UINT8((COM_CAST2UINT8(~(COM_CAST2UINT8(255u << Com_GetBitLengthOfTxSigInfo(SignalId))))) << signalStartBit);
      signalBusDest &= COM_CAST2UINT8(~mask);
      signalBusDest |= COM_CAST2UINT8(*SignalApplSourcePtrInternal << signalStartBit) & mask;

      Com_SetTxBuffer(Com_GetTxBufferStartIdxOfTxSigInfo(SignalId), signalBusDest);     /* SBSW_COM_CSL03 */
      break;
    }
# endif
# if (COM_EXISTS_BYTE_BUSACCOFTXSIGINFO == STD_ON)
    case (COM_BYTE_BUSACCOFTXSIGINFO):
    {
      /* #40 BYTE: Set the source pointer to the destination pointer */
      Com_SetTxBuffer(Com_GetTxBufferStartIdxOfTxSigInfo(SignalId), *SignalApplSourcePtrInternal);      /* SBSW_COM_CSL03 */
      break;
    }
# endif
# if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
#  if ((COM_EXISTS_NBYTE_BUSACCOFTXSIGINFO == STD_ON) || (COM_EXISTS_ARRAY_BASED_BUSACCOFTXSIGINFO == STD_ON))
#   if (COM_EXISTS_ARRAY_BASED_BUSACCOFTXSIGINFO == STD_ON)
    case (COM_ARRAY_BASED_BUSACCOFTXSIGINFO):
#   endif
#   if (COM_EXISTS_NBYTE_BUSACCOFTXSIGINFO == STD_ON)
    case (COM_NBYTE_BUSACCOFTXSIGINFO):
#   endif
    {
      Com_TxBufferEndIdxOfTxSigInfoType i;
      /* Pointer points to LSB of little endian signal, therefore start index is used */
      P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusDestPtr = Com_GetAddrTxBuffer(Com_GetTxBufferStartIdxOfTxSigInfo(SignalId));
      /* #50 (NBYTE or ARRAY_BASED) and CPU byte order is LOW_BYTE_FIRST: Copy N source bytes from position I to destination bytes at position I */
      /* Use-case: UINT8_N or UINT8_DYN */
    /* *INDENT-OFF* */
    /* ------------------------------- Intel (appl) to Intel (bus) AND Byte Arrays (Intel Hw) -------------------------
       - Writing Intel Signals on Intel Hw.
       - Writing Byte Arrays (no swap):
       - Writing Intel Byte Arrays */
    /* *INDENT-ON* */
      for(i = 0; i < Com_Signal_GetTxBufferLength(SignalId); i++)
      {
        SignalBusDestPtr[i] = SignalApplSourcePtrInternal[i];   /* SBSW_COM_TXBUFFER_CSL03 */
      }
      break;
    }
#  endif
#  if (COM_EXISTS_NBYTE_SW_BUSACCOFTXSIGINFO == STD_ON)
    case (COM_NBYTE_SW_BUSACCOFTXSIGINFO):
    {
    /*------------------------------- Intel (appl) to Motorola (bus)------------------------------------------------*/
      /* Pointer points to LSB of big endian signal, therefore end index is used */
      P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusDestPtr = Com_GetAddrTxBuffer(Com_GetTxBufferEndIdxOfTxSigInfo(SignalId) - 1u);
      /* #60 NBYTE_SW and CPU byte order is LOW_BYTE_FIRST: Copy N source bytes from position I to destination bytes at position -I */
      sint16_least i;
      /* ------------------------------- Intel (appl) to Motorola (bus) ---------------------------------------------- */
      for(i = 0; i < ((sint16_least) Com_Signal_GetTxBufferLength(SignalId)); i++)
      {
        SignalBusDestPtr[-i] = SignalApplSourcePtrInternal[i];  /* SBSW_COM_TXBUFFER_CSL03 */
      }
      break;
    }
#  endif
#  if (COM_EXISTS_NBITNBYTE_BUSACCOFTXSIGINFO == STD_ON)
    case (COM_NBITNBYTE_BUSACCOFTXSIGINFO):    /* COV_COM_NBITNBYTE_X */
    {
      /* #70 NBITNBYTE and CPU byte order is LOW_BYTE_FIRST: Copy N bits and N bytes from the source pointer to the destination pointer */
      /* Pointer points to LSB of little endian signal, therefore start index is used */
      P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusDestPtr = Com_GetAddrTxBuffer(Com_GetTxBufferStartIdxOfTxSigInfo(SignalId));
      Com_Signal_WriteSignal_NBITNBYTE(SignalId, SignalApplSourcePtrInternal, signalStartBit, SignalBusDestPtr, FALSE); /* SBSW_COM_VALID_PTR_BY_COMSTACK_01 */
      break;
    }
#  endif
#  if (COM_EXISTS_NBITNBYTE_SW_BUSACCOFTXSIGINFO == STD_ON)
    case (COM_NBITNBYTE_SW_BUSACCOFTXSIGINFO): /* COV_COM_NBITNBYTE_SW_BUSACCOFTXSIGINFO */
    {
      /* #80 NBITNBYTE_SW and CPU byte order is LOW_BYTE_FIRST: Copy N bits and N bytes from the source pointer to the destination pointer and perform endianness conversion */
      /* Pointer points to LSB of big endian signal, therefore end index is used */
      P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusDestPtr = Com_GetAddrTxBuffer(Com_GetTxBufferEndIdxOfTxSigInfo(SignalId) - 1u);
      Com_Signal_WriteSignal_NBITNBYTE(SignalId, SignalApplSourcePtrInternal, signalStartBit, SignalBusDestPtr, TRUE);  /* SBSW_COM_VALID_PTR_BY_COMSTACK_01 */
      break;
    }
#  endif
# else /* (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */
#  if ((COM_EXISTS_NBYTE_BUSACCOFTXSIGINFO == STD_ON) || (COM_EXISTS_ARRAY_BASED_BUSACCOFTXSIGINFO == STD_ON))
#   if (COM_EXISTS_ARRAY_BASED_BUSACCOFTXSIGINFO == STD_ON)
    case (COM_ARRAY_BASED_BUSACCOFTXSIGINFO):
    {
      /* #90 ARRAY_BASED and CPU byte order is HIGH_BYTE_FIRST: Set the source pointer to the last byte, and copy in reverse order */
      /* Use-case: UINT8_N or UINT8_DYN */
      SignalApplSourcePtrInternal = &SignalApplSourcePtrInternal[Com_Signal_GetTxBufferLength(SignalId) - 1u];
      /* No break required here! */
    }
#   endif
#   if (COM_EXISTS_NBYTE_BUSACCOFTXSIGINFO == STD_ON)
    case (COM_NBYTE_BUSACCOFTXSIGINFO):        /* PRQA S 2003 */ /* MD_Com_2003 */
#   endif
    {
      /* #100 NBYTE and CPU byte order is HIGH_BYTE_FIRST, copy in reverse order */
      sint16_least i;
      /* Pointer points to LSB of big endian signal, pointer points to last byte of actual txBuffer. */
      P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusDestPtr = Com_GetAddrTxBuffer((Com_GetTxBufferStartIdxOfTxSigInfo(SignalId) + Com_Signal_GetTxBufferLength(SignalId)) - 1u);
    /* *INDENT-OFF* */
    /* ---------------------- Motorola (appl) to Motorola (bus) AND Byte Arrays (Motorola Hw)--------------------------
       - Writing Motorola Signals on Motorola Hw.
       - Writing Byte Arrays (no swap):
       - Writing Motorola Byte Arrays
       - Also allows writing of Intel Byte Arrays (StartBit is not lsb -> is msb in this case) */
    /* *INDENT-ON* */

      for(i = 0; i < ((sint16_least) Com_Signal_GetTxBufferLength(SignalId)); i++)
      {
        SignalBusDestPtr[-i] = SignalApplSourcePtrInternal[-i]; /* SBSW_COM_TXBUFFER_CSL03 */
      }
      break;
    }
#  endif
#  if (COM_EXISTS_NBYTE_SW_BUSACCOFTXSIGINFO == STD_ON)
    case (COM_NBYTE_SW_BUSACCOFTXSIGINFO):
    {
      /* ------------------------------- Motorola (appl) to Intel (bus)------------------------------------------------ */
      /* #130 NBYTE_SW and CPU byte order is HIGH_BYTE_FIRST: Copy source -I to destination I */
      sint16_least i;
      P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusDestPtr = Com_GetAddrTxBuffer(Com_GetTxBufferStartIdxOfTxSigInfo(SignalId));
      /* ------------------------------- Motorola (appl) to Intel (bus) ---------------------------------------------- */
      for(i = 0; i < ((sint16_least) Com_Signal_GetTxBufferLength(SignalId)); i++)
      {
        SignalBusDestPtr[i] = SignalApplSourcePtrInternal[-i];  /* SBSW_COM_TXBUFFER_CSL03 */
      }
      break;
    }
#  endif
#  if (COM_EXISTS_NBITNBYTE_BUSACCOFTXSIGINFO == STD_ON)
    case (COM_NBITNBYTE_BUSACCOFTXSIGINFO):
    {
      /* #140 NBITNBYTE and CPU byte order is HIGH_BYTE_FIRST: Copy N bits and N bytes from the source pointer to the destination pointer */
      P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusDestPtr = Com_GetAddrTxBuffer(Com_GetTxBufferEndIdxOfTxSigInfo(SignalId) - 1u);
      Com_Signal_WriteSignal_NBITNBYTE(SignalId, SignalApplSourcePtrInternal, signalStartBit, SignalBusDestPtr, TRUE);  /* SBSW_COM_VALID_PTR_BY_COMSTACK_01 */
      break;
    }
#  endif
#  if (COM_EXISTS_NBITNBYTE_SW_BUSACCOFTXSIGINFO == STD_ON)
    case (COM_NBITNBYTE_SW_BUSACCOFTXSIGINFO):
    {
      /* #150 NBITNBYTE_SW and CPU byte order is HIGH_BYTE_FIRST: Copy N bits and N bytes from the source pointer to the destination pointer and perform endianness conversion */
      P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusDestPtr = Com_GetAddrTxBuffer(Com_GetTxBufferStartIdxOfTxSigInfo(SignalId));
      Com_Signal_WriteSignal_NBITNBYTE(SignalId, SignalApplSourcePtrInternal, signalStartBit, SignalBusDestPtr, FALSE); /* SBSW_COM_VALID_PTR_BY_COMSTACK_01 */

      break;
    }
#  endif
# endif
    default:   /* COV_COM_MISRA */
      break;
  }
}
#endif

#define COM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* *INDENT-OFF* */
/* Justifications for module-specific MISRA deviations:
   MD_Com_3315: Misra Rule 16.6
     Reason:     It depends on the configuration, if only one or more cases of the switch statement are executed.
     Risk:       No risk, because only warning that the switch statement is redundant.
     Prevention: No prevention necessary.
*/

/***********************************************************************************************************************
 *  SILENTBSW JUSTIFICATIONS
 **********************************************************************************************************************/
/* SBSW_JUSTIFICATION_BEGIN

SBSW_JUSTIFICATION_END */

/***********************************************************************************************************************
 *  COVERAGE JUSTIFICATIONS
 **********************************************************************************************************************/
/* START_COVERAGE_JUSTIFICATION

END_COVERAGE_JUSTIFICATION */
/* *INDENT-ON* */

/**********************************************************************************************************************
 *  END OF FILE: Com_Serializer.c
 *********************************************************************************************************************/
