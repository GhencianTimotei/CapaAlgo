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
/*!        \file  Com_Deserializer.c
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/
#define COM_DESERIALIZER_SOURCE

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Com.h"
#include "Com_Deserializer.h"
#include "vstdlib.h"

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

#if (COM_EXISTS_SINT8_APPLTYPEOFRXACCESSINFO == STD_ON)
/*! \brief    Union used for sign extension
    \details  -
    \pre      -
*/
typedef union uSignExt8Bit      /* PRQA S 3213 */ /* MD_Com_3213 */
{                               /* PRQA S 0750 */ /* MD_MSR_Union */
  uint8 unsignedAccess;
  sint8 signedAccess;
} uSignExt8BitType;
#endif

#if (COM_EXISTS_SINT16_APPLTYPEOFRXACCESSINFO == STD_ON)
/*! \brief    Union used for sign extension
    \details  -
    \pre      -
 */
typedef union uSignExt16Bit     /* PRQA S 3213 */ /* MD_Com_3213 */
{                               /* PRQA S 0750 */ /* MD_MSR_Union */
  uint8 unsignedAccess[2];
  sint16 signedAccess;
} uSignExt16BitType;
#endif

#if (COM_EXISTS_SINT32_APPLTYPEOFRXACCESSINFO == STD_ON)
/*! \brief    Union used for sign extension
    \details  -
    \pre      -
*/
typedef union uSignExt32Bit     /* PRQA S 3213 */ /* MD_Com_3213 */
{                               /* PRQA S 0750 */ /* MD_MSR_Union */
  uint8 unsignedAccess[4];
  sint32 signedAccess;
} uSignExt32BitType;
#endif

#if (COM_EXISTS_SINT64_APPLTYPEOFRXACCESSINFO == STD_ON)
/*! \brief    Union used for sign extension
    \details  -
    \pre      -
*/
typedef union uSignExt64Bit     /* PRQA S 3213 */ /* MD_Com_3213 */
{                               /* PRQA S 0750 */ /* MD_MSR_Union */
  uint8 unsignedAccess[8];
  sint64 signedAccess;
} uSignExt64BitType;
#endif

/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#if (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON)
/**********************************************************************************************************************
  Com_Signal_ReadSignalApplTypeSpecific
**********************************************************************************************************************/
/*! \brief        This method reads the signal value ApplType specific form the source buffer.
    \details      -
    \pre          -
    \param[in]    rxAccessInfoId     ID of the Rx AccessInfo
    \param[out]   SignalApplDestPtr  Pointer where the signal is written to
    \param[in]    SignalBusSourcePtr Pointer to the first byte of the signal in the source memory
    \param[in]    destLength         length of the destination buffer in bytes.
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignalApplTypeSpecific(Com_RxAccessInfoIterType rxAccessInfoId,
                                                                            P2VAR(uint8, AUTOMATIC, COM_APPL_VAR) SignalApplDestPtr,
                                                                            P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr, uint32 destLength);
#endif

#if ((CPU_BYTE_ORDER == LOW_BYTE_FIRST) && (COM_EXISTS_NBITNBYTE_BUSACCOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_LB_NBITNBYTE
**********************************************************************************************************************/
/*! \brief        This method reads a signal from the indicated buffer (i.e. ipdu buffer or shadow buffer)
                  Unused bits are set to 0.
    \details      -
    \pre          -
    \param[in]    SignalId            ID of the signal to be read
    \param[out]   SignalApplDestPtr   Pointer where the signal is written to
    \param[in]    SignalBusSourcePtr  Pointer to the first byte of the signal in the source memory
    \param[in]    signalStartBit      bit index in the byte, where the signal starts (0..7)
    \param[in]    destLength          destination buffer length
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignal_LB_NBITNBYTE(Com_RxAccessInfoIterType SignalId, P2VAR(uint8, AUTOMATIC, COM_APPL_VAR) SignalApplDestPtr,
                                                                         P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr, Com_BitPositionOfRxAccessInfoType signalStartBit,
                                                                         uint32 destLength);
#endif

#if ((CPU_BYTE_ORDER == LOW_BYTE_FIRST) && (COM_EXISTS_NBITNBYTE_SW_BUSACCOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_LB_SW_NBITNBYTE
**********************************************************************************************************************/
/*! \brief        This method reads a signal from the indicated buffer (i.e. ipdu buffer or shadow buffer)
                  Unused bits are set to 0. Endianness is converted from BigEndian(BUS) to LittleEndian (ECU).
    \details      -
    \pre          -
    \param[in]    SignalId        ID of the signal to be read
    \param[out]   SignalApplDestPtr   Pointer where the signal is written to
    \param[in]    SignalBusSourcePtr  Pointer to the first byte (least significant) of the signal in the source memory
    \param[in]    signalStartBit  bit index in the byte, where the signal starts (0..7) (LSB)
    \param[in]    destLength      destination buffer length
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignal_LB_SW_NBITNBYTE(Com_RxAccessInfoIterType SignalId, P2VAR(uint8, AUTOMATIC, COM_APPL_VAR) SignalApplDestPtr,
                                                                            P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr,
                                                                            Com_BitPositionOfRxAccessInfoType signalStartBit, uint32 destLength);
#endif

#if ((CPU_BYTE_ORDER == HIGH_BYTE_FIRST) && (COM_EXISTS_NBITNBYTE_BUSACCOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_HB_NBITNBYTE
**********************************************************************************************************************/
/*! \brief        This method reads a signal from the indicated buffer (i.e. ipdu buffer or shadow buffer)
                  Unused bits are set to 0.
    \details      -
    \pre          -
    \param[in]    rxAccessInfoId      ID of the signal to be read
    \param[out]   SignalApplDestPtr   Pointer where the signal is written to
    \param[in]    SignalBusSourcePtr  Pointer to the first byte of the signal in the source memory
    \param[in]    signalStartBit  bit index in the byte, where the signal starts (0..7)
    \param[in]    destLength      destination buffer length
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignal_HB_NBITNBYTE(Com_RxAccessInfoIterType rxAccessInfoId, P2VAR(uint8, AUTOMATIC, COM_APPL_VAR) SignalApplDestPtr,
                                                                         P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr, Com_BitPositionOfRxAccessInfoType signalStartBit,
                                                                         uint32 destLength);
#endif

#if ((CPU_BYTE_ORDER == HIGH_BYTE_FIRST) && (COM_EXISTS_NBITNBYTE_SW_BUSACCOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_HB_SW_NBITNBYTE
**********************************************************************************************************************/
/*! \brief        This method reads a signal from the indicated buffer (i.e. ipdu buffer or shadow buffer)
                  Unused bits are set to 0. Endianness conversion is performed.
    \details      -
    \pre          -
    \param[in]    rxAccessInfoId      ID of the signal to be read
    \param[out]   SignalApplDestPtr   Pointer where the signal is written to
    \param[in]    SignalBusSourcePtr  Pointer to the first byte of the signal in the source memory
    \param[in]    signalStartBit  bit index in the byte, where the signal starts (0..7)
    \param[in]    destLength      destination buffer length
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignal_HB_SW_NBITNBYTE(Com_RxAccessInfoIterType rxAccessInfoId, P2VAR(uint8, AUTOMATIC, COM_APPL_VAR) SignalApplDestPtr,
                                                                            P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr,
                                                                            Com_BitPositionOfRxAccessInfoType signalStartBit, uint32 destLength);
#endif

#if ((COM_SIGNEXTREQUIREDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_SINT8_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_ReadSignalSignExtension_SINT8
*********************************************************************************************************************/
/*!
    \brief            This method performs the Sign extension for signals
    \details          -
    \pre              -
    \param[in]        idxAccessInfo     index of ComSignal
    \param[in,out]    signExtValue      ApplType specific stack value that will be sign extended
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignalSignExtension_SINT8(Com_RxAccessInfoIterType idxAccessInfo, P2VAR(uSignExt8BitType, AUTOMATIC, COM_APPL_VAR) signExtValue);  /* PRQA S 0750 */ /* MD_MSR_Union */
#endif

#if ((COM_SIGNEXTREQUIREDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_SINT16_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_ReadSignalSignExtension_SINT16
*********************************************************************************************************************/
/*!
    \brief            This method performs the Sign extension for signals
    \details          -
    \pre              -
    \param[in]        idxAccessInfo     index of ComSignal
    \param[in,out]    signExtValue      ApplType specific stack value that will be sign extended
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignalSignExtension_SINT16(Com_RxAccessInfoIterType idxAccessInfo, P2VAR(uSignExt16BitType, AUTOMATIC, COM_APPL_VAR) signExtValue);        /* PRQA S 0750 */ /* MD_MSR_Union */
#endif

#if ((COM_SIGNEXTREQUIREDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_SINT32_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_ReadSignalSignExtension_SINT32
*********************************************************************************************************************/
/*!
    \brief            This method performs the Sign extension for signals
    \details          -
    \pre              -
    \param[in]        idxAccessInfo     index of ComSignal
    \param[in,out]    signExtValue      ApplType specific stack value that will be sign extended
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignalSignExtension_SINT32(Com_RxAccessInfoIterType idxAccessInfo, P2VAR(uSignExt32BitType, AUTOMATIC, COM_APPL_VAR) signExtValue);        /* PRQA S 0750 */ /* MD_MSR_Union */
#endif

#if ((COM_SIGNEXTREQUIREDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_SINT64_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_ReadSignalSignExtension_SINT64
*********************************************************************************************************************/
/*!
    \brief            This method performs the Sign extension for signals
    \details          -
    \pre              -
    \param[in]        idxAccessInfo     index of ComSignal
    \param[in,out]    signExtValue      ApplType specific stack value that will be sign extended
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignalSignExtension_SINT64(Com_RxAccessInfoIterType idxAccessInfo, P2VAR(uSignExt64BitType, AUTOMATIC, COM_APPL_VAR) signExtValue);        /* PRQA S 0750 */ /* MD_MSR_Union */
#endif


/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

#if (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON)
/**********************************************************************************************************************
  Com_Signal_ReadSignalApplTypeSpecific
**********************************************************************************************************************/
/*! Internal comment removed.
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
 *********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignalApplTypeSpecific(Com_RxAccessInfoIterType rxAccessInfoId,
                                                                            P2VAR(uint8, AUTOMATIC, COM_APPL_VAR) SignalApplDestPtr,
                                                                            P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr, uint32 destLength)
{
  P2VAR(uint8, AUTOMATIC, COM_APPL_VAR) SignalApplDestPtrIntern = SignalApplDestPtr;
# if ((COM_EXISTS_NBIT_BUSACCOFRXACCESSINFO == STD_ON) || (COM_EXISTS_NBITNBYTE_BUSACCOFRXACCESSINFO == STD_ON) || (COM_EXISTS_NBITNBYTE_SW_BUSACCOFRXACCESSINFO == STD_ON))
  Com_BitPositionOfRxAccessInfoType signalStartBit = Com_Signal_BitOffsetFromBitPos(Com_GetBitPositionOfRxAccessInfo(rxAccessInfoId));
# endif
# if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  SignalApplDestPtrIntern = &SignalApplDestPtrIntern[destLength - 1u];
# endif
  switch (Com_GetBusAccOfRxAccessInfo(rxAccessInfoId))
  {
# if (COM_EXISTS_NBIT_BUSACCOFRXACCESSINFO == STD_ON)
    case (COM_NBIT_BUSACCOFRXACCESSINFO):
    {
      *SignalApplDestPtrIntern = COM_CAST2UINT8((*SignalBusSourcePtr) >> signalStartBit) & COM_CAST2UINT8(255u >> (8u - Com_GetBitLengthOfRxAccessInfo(rxAccessInfoId)));       /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
      break;
    }
# endif
# if (COM_EXISTS_BYTE_BUSACCOFRXACCESSINFO == STD_ON)
    case (COM_BYTE_BUSACCOFRXACCESSINFO):
    {
      *SignalApplDestPtrIntern = COM_CAST2UINT8(*SignalBusSourcePtr);   /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
      break;
    }
# endif
# if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
#  if (COM_EXISTS_NBYTE_BUSACCOFRXACCESSINFO == STD_ON)
    case (COM_NBYTE_BUSACCOFRXACCESSINFO):
    {
      VStdLib_MemCpy_s(SignalApplDestPtrIntern, (VStdLib_CntType) destLength, SignalBusSourcePtr, (VStdLib_CntType) Com_GetByteLengthOfRxAccessInfo(rxAccessInfoId));   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_COM_VSTDLIB_SAFE */
      break;
    }
#  endif
#  if (COM_EXISTS_NBYTE_SW_BUSACCOFRXACCESSINFO == STD_ON)
    case (COM_NBYTE_SW_BUSACCOFRXACCESSINFO):
    {
      if(Com_GetByteLengthOfRxAccessInfo(rxAccessInfoId) <= destLength) /* COV_COM_SILENT_TX */
      {
        sint16_least i;
        /* ------------------------------- Motorola (bus) to Intel (appl) -------------------------------------------- */
        for(i = (((sint16_least) Com_GetByteLengthOfRxAccessInfo(rxAccessInfoId)) - 1); i >= 0; i--)
        {
          SignalApplDestPtrIntern[i] = COM_CAST2UINT8(SignalBusSourcePtr[-i]);  /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
        }
      }
      break;
    }
#  endif
#  if (COM_EXISTS_NBITNBYTE_BUSACCOFRXACCESSINFO == STD_ON)
    case (COM_NBITNBYTE_BUSACCOFRXACCESSINFO):
    {
      Com_Signal_ReadSignal_LB_NBITNBYTE(rxAccessInfoId, SignalApplDestPtrIntern, SignalBusSourcePtr, signalStartBit, destLength);      /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC_AND_STACKPTR */
      break;
    }
#  endif
#  if (COM_EXISTS_NBITNBYTE_SW_BUSACCOFRXACCESSINFO == STD_ON)
    case (COM_NBITNBYTE_SW_BUSACCOFRXACCESSINFO):
    {
      Com_Signal_ReadSignal_LB_SW_NBITNBYTE(rxAccessInfoId, SignalApplDestPtrIntern, SignalBusSourcePtr, signalStartBit, destLength);   /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC_AND_STACKPTR */
      break;
    }
#  endif
# else /* (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */
#  if (COM_EXISTS_NBYTE_BUSACCOFRXACCESSINFO == STD_ON)
    case (COM_NBYTE_BUSACCOFRXACCESSINFO):
    {
      if(Com_GetByteLengthOfRxAccessInfo(rxAccessInfoId) <= destLength) /* COV_COM_SILENT_TX */
      {
        sint16_least i;
        /* ------------------------------- Motorola (bus) to Motorola (appl) -------------------------------------------- */
        for(i = (((sint16_least) Com_GetByteLengthOfRxAccessInfo(rxAccessInfoId)) - 1); i >= 0; i--)
        {
          SignalApplDestPtrIntern[-i] = SignalBusSourcePtr[-i]; /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
        }
      }
      break;
    }
#  endif
#  if (COM_EXISTS_NBYTE_SW_BUSACCOFRXACCESSINFO == STD_ON)
    case (COM_NBYTE_SW_BUSACCOFRXACCESSINFO):
    {
      if(Com_GetByteLengthOfRxAccessInfo(rxAccessInfoId) <= destLength) /* COV_COM_SILENT_TX */
      {
        sint16_least i;
        /* ------------------------------- Intel(bus) to Motorola (appl) -------------------------------------------- */
        for(i = (((sint16_least) Com_GetByteLengthOfRxAccessInfo(rxAccessInfoId)) - 1); i >= 0; i--)
        {
          SignalApplDestPtrIntern[-i] = SignalBusSourcePtr[i];  /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
        }
      }
      break;
    }
#  endif
#  if (COM_EXISTS_NBITNBYTE_BUSACCOFRXACCESSINFO == STD_ON)
    case (COM_NBITNBYTE_BUSACCOFRXACCESSINFO):
    {
      Com_Signal_ReadSignal_HB_NBITNBYTE(rxAccessInfoId, SignalApplDestPtrIntern, SignalBusSourcePtr, signalStartBit, destLength);      /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC_AND_STACKPTR */
      break;
    }
#  endif
#  if (COM_EXISTS_NBITNBYTE_SW_BUSACCOFRXACCESSINFO == STD_ON)
    case (COM_NBITNBYTE_SW_BUSACCOFRXACCESSINFO):
    {
      Com_Signal_ReadSignal_HB_SW_NBITNBYTE(rxAccessInfoId, SignalApplDestPtrIntern, SignalBusSourcePtr, signalStartBit, destLength);   /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC_AND_STACKPTR */
      break;
    }
#  endif
# endif
    default:   /* COV_COM_MISRA */
      break;
  }
  COM_DUMMY_STATEMENT(destLength);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if ((CPU_BYTE_ORDER == LOW_BYTE_FIRST) && (COM_EXISTS_NBITNBYTE_BUSACCOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_LB_NBITNBYTE
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignal_LB_NBITNBYTE(Com_RxAccessInfoIterType SignalId, P2VAR(uint8, AUTOMATIC, COM_APPL_VAR) SignalApplDestPtr,
                                                                         P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr, Com_BitPositionOfRxAccessInfoType signalStartBit,
                                                                         uint32 destLength)
{
  /* #5 This function is used if the CPU byte order is LOW_BYTE_FIRST */
  uint16_least nFullBytes = 0u;
  Com_BitLengthOfRxAccessInfoType nBitsToWrite = Com_GetBitLengthOfRxAccessInfo(SignalId);
  /* ------------------------------- Intel (bus) to Intel (appl) ----------------------------------------------- */
  /* #10 If more than 8 bits have to be copied */
  if(nBitsToWrite > 8u) /* COV_COM_NBITNBYTE */
  {
    sint16_least i;
    nFullBytes = (uint16_least) (nBitsToWrite >> 3u);   /* PRQA S 4391 */ /* MD_Com_4391 */
    if(((uint32) nFullBytes) <= destLength)     /* COV_COM_SILENT_TX */
    {
      /* #20 Copy all full bytes, byte align the source byte before it is copied */
      for(i = ((sint16_least) nFullBytes - 1); i >= 0; i--)
      {
        SignalApplDestPtr[i] = COM_CAST2UINT8(SignalBusSourcePtr[i] >> signalStartBit); /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
        SignalApplDestPtr[i] |= COM_CAST2UINT8(SignalBusSourcePtr[i + 1] << (8u - signalStartBit));     /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
        nBitsToWrite -= 8u;
      }
    }
    else
    {
      nFullBytes = 0u;
    }
  }

  /* #30 If the signal not only has full bytes, copy the remaining bits to the destination buffer */
  if(0u != nBitsToWrite)        /* COV_COM_NBITNBYTE_COPY_REMAININGBITS */
  {
    uint8 tmpByte = COM_CAST2UINT8(SignalBusSourcePtr[nFullBytes] >> signalStartBit);
    uint8 sourceEndByteIdx = COM_CAST2UINT8((signalStartBit + Com_GetBitLengthOfRxAccessInfo(SignalId) - 1u) >> 3u);

    if(sourceEndByteIdx > (uint8) nFullBytes)   /* COV_COM_NBITNBYTE_BY_UINT8_ONLY */
    {
      tmpByte |= COM_CAST2UINT8(SignalBusSourcePtr[nFullBytes + 1u] << (8u - signalStartBit));
    }

    SignalApplDestPtr[nFullBytes] = tmpByte & COM_CAST2UINT8(~(COM_CAST2UINT8(255u << nBitsToWrite)));  /* PRQA S 2793, 2842 */ /* MD_Com_2793, MD_Com_2842_SignalApplDestPtr */ /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
  }
}
#endif

#if ((CPU_BYTE_ORDER == LOW_BYTE_FIRST) && (COM_EXISTS_NBITNBYTE_SW_BUSACCOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_LB_SW_NBITNBYTE
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignal_LB_SW_NBITNBYTE(Com_RxAccessInfoIterType SignalId, P2VAR(uint8, AUTOMATIC, COM_APPL_VAR) SignalApplDestPtr,
                                                                            P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr,
                                                                            Com_BitPositionOfRxAccessInfoType signalStartBit, uint32 destLength)
{
  /* #5 This function is used if the CPU byte order is LOW_BYTE_FIRST */
  sint16_least nFullBytes = 0;
  Com_BitLengthOfRxAccessInfoType nBitsToWrite = Com_GetBitLengthOfRxAccessInfo(SignalId);
  /* ------------------------------- Motorola (bus) to Intel (appl) -------------------------------------------- */
  /* #10 If more than 8 bits have to be copied */
  if(nBitsToWrite > 8u) /* COV_COM_NBITNBYTE */
  {
    sint16_least i;
    nFullBytes = (sint16_least) (nBitsToWrite >> 3u);   /* PRQA S 4394 */ /* MD_Com_4394 */
    if(((uint32) nFullBytes) <= destLength)     /* COV_COM_SILENT_TX */
    {
      for(i = (sint16_least) (nFullBytes - 1); i >= 0; i--)
      {
        /* #20 Copy all full bytes, byte align the source byte before it is copied and perform endianess conversion */
        SignalApplDestPtr[i] = COM_CAST2UINT8(SignalBusSourcePtr[-i] >> signalStartBit);        /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
        SignalApplDestPtr[i] |= COM_CAST2UINT8(SignalBusSourcePtr[-i - 1] << (8u - signalStartBit));    /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
        nBitsToWrite -= 8u;
      }
    }
    else
    {
      nFullBytes = 0;
    }
  }

  /* #30 If the signal not only has full bytes, copy the remaining bits to the destination buffer and perform endianess conversion */
  if(0u != nBitsToWrite)        /* COV_COM_NBITNBYTE_COPY_REMAININGBITS */
  {
    uint8 tmpByte = COM_CAST2UINT8(SignalBusSourcePtr[0 - nFullBytes] >> signalStartBit);       /* PRQA S 2986 */ /* MD_Com_2985_2986 */
    uint8 sourceEndByteIdx = COM_CAST2UINT8(Com_GetBytePositionOfRxAccessInfo(SignalId) - Com_GetStartByteInPduPositionOfRxAccessInfo(SignalId));

    if(sourceEndByteIdx > (uint8) nFullBytes)   /* COV_COM_NBITNBYTE_BY_UINT8_ONLY */
    {
      tmpByte |= COM_CAST2UINT8(SignalBusSourcePtr[-1 - nFullBytes] << (8u - signalStartBit));
    }

    SignalApplDestPtr[nFullBytes] = tmpByte & COM_CAST2UINT8(~(COM_CAST2UINT8(255u << nBitsToWrite)));  /* PRQA S 2793, 2842 */ /* MD_Com_2793, MD_Com_2842_SignalApplDestPtr */ /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
  }
}
#endif

#if ((CPU_BYTE_ORDER == HIGH_BYTE_FIRST) && (COM_EXISTS_NBITNBYTE_BUSACCOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_HB_NBITNBYTE
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignal_HB_NBITNBYTE(Com_RxAccessInfoIterType rxAccessInfoId, P2VAR(uint8, AUTOMATIC, COM_APPL_VAR) SignalApplDestPtr,
                                                                         P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr, Com_BitPositionOfRxAccessInfoType signalStartBit,
                                                                         uint32 destLength)
{
  /* #5 This function is used if the CPU byte order is HIGH_BYTE_FIRST */
  sint16_least nFullBytes = 0;
  Com_BitLengthOfRxAccessInfoType nBitsToWrite = Com_GetBitLengthOfRxAccessInfo(rxAccessInfoId);
  /* ------------------------------- Motorola (bus) to Motorola (appl) ----------------------------------------- */
  /* #10 If more than 8 bits have to be copied */
  if(nBitsToWrite > 8u) /* COV_COM_NBITNBYTE */
  {
    sint16_least i;
    nFullBytes = (sint16_least) (nBitsToWrite >> 3u);   /* PRQA S 4394 */ /* MD_Com_4394 */
    if(((uint32) nFullBytes) <= destLength)     /* COV_COM_NBITNBYTE_TX_01 */
    {
      for(i = (sint16_least) (nFullBytes - 1); i >= 0; i--)     /* COV_COM_NBITNBYTE_XX */
      {
        /* #20 Copy all full bytes, byte align the source byte before it is copied */
        SignalApplDestPtr[-i] = COM_CAST2UINT8(SignalBusSourcePtr[-i] >> signalStartBit);       /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
        SignalApplDestPtr[-i] |= COM_CAST2UINT8(SignalBusSourcePtr[-i - 1] << (8u - signalStartBit));   /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
        nBitsToWrite -= 8u;
      }
    }
    else
    {
      nFullBytes = 0;
    }
  }

  /* #30 If the signal not only has full bytes, copy the remaining bits to the destination buffer */
  if(0u != nBitsToWrite)        /* COV_COM_NBITNBYTE_COPY_REMAININGBITS */
  {
    uint8 tmpByte = COM_CAST2UINT8(SignalBusSourcePtr[0 - nFullBytes] >> signalStartBit);       /* PRQA S 2986 */ /* MD_Com_2985_2986 */

    uint8 sourceEndByteIdx = COM_CAST2UINT8(Com_GetBytePositionOfRxAccessInfo(rxAccessInfoId) - Com_GetStartByteInPduPositionOfRxAccessInfo(rxAccessInfoId));

    if(sourceEndByteIdx > (uint8) nFullBytes)   /* COV_COM_NBITNBYTE_BY_UINT8_ONLY */
    {
      tmpByte |= COM_CAST2UINT8(SignalBusSourcePtr[-1 - nFullBytes] << (8u - signalStartBit));
    }

    SignalApplDestPtr[0 - nFullBytes] = tmpByte & COM_CAST2UINT8(~(COM_CAST2UINT8(255u << nBitsToWrite)));      /* PRQA S 2986, 2793, 2842 */ /* MD_Com_2985_2986, MD_Com_2793, MD_Com_2842_SignalApplDestPtr */ /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
  }
}
#endif

#if ((CPU_BYTE_ORDER == HIGH_BYTE_FIRST) && (COM_EXISTS_NBITNBYTE_SW_BUSACCOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_HB_SW_NBITNBYTE
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignal_HB_SW_NBITNBYTE(Com_RxAccessInfoIterType rxAccessInfoId, P2VAR(uint8, AUTOMATIC, COM_APPL_VAR) SignalApplDestPtr,
                                                                            P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr,
                                                                            Com_BitPositionOfRxAccessInfoType signalStartBit, uint32 destLength)
{
  /* #5 This function is used if the CPU byte order is HIGH_BYTE_FIRST */
  sint16_least nFullBytes = 0;
  Com_BitLengthOfRxAccessInfoType nBitsToWrite = Com_GetBitLengthOfRxAccessInfo(rxAccessInfoId);
  /* ------------------------------- Intel (bus) to Motorola (appl) -------------------------------------------- */
  /* #10 If more than 8 bits have to be copied */
  if(nBitsToWrite > 8u) /* COV_COM_NBITNBYTE */
  {
    sint16_least i;
    nFullBytes = (sint16_least) (nBitsToWrite >> 3u);   /* PRQA S 4394 */ /* MD_Com_4394 */
    if(((uint32) nFullBytes) <= destLength)     /* COV_COM_NBITNBYTE_TX_01 */
    {
      for(i = (sint16_least) (nFullBytes - 1); i >= 0; i--)     /* COV_COM_NBITNBYTE_XX */
      {
        /* #20 Copy all full bytes, byte align the source byte before it is copied and perform endianess conversion */
        SignalApplDestPtr[-i] = COM_CAST2UINT8(SignalBusSourcePtr[i] >> signalStartBit);        /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
        SignalApplDestPtr[-i] |= COM_CAST2UINT8(SignalBusSourcePtr[i + 1] << (8u - signalStartBit));    /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
        nBitsToWrite -= 8u;
      }
    }
    else
    {
      nFullBytes = 0;
    }
  }

  /* #30 If the signal not only has full bytes, copy the remaining bits to the destination buffer and perform endianess conversion */
  if(0u != nBitsToWrite)        /* COV_COM_NBITNBYTE_COPY_REMAININGBITS */
  {
    uint8 tmpByte = COM_CAST2UINT8(SignalBusSourcePtr[nFullBytes] >> signalStartBit);
    uint8 sourceEndByteIdx = COM_CAST2UINT8((signalStartBit + Com_GetBitLengthOfRxAccessInfo(rxAccessInfoId) - 1u) >> 3u);

    if(sourceEndByteIdx > (uint8) nFullBytes)   /* COV_COM_NBITNBYTE_BY_UINT8_ONLY */
    {
      tmpByte |= COM_CAST2UINT8(SignalBusSourcePtr[nFullBytes + 1] << (8u - signalStartBit));
    }

    SignalApplDestPtr[0 - nFullBytes] = tmpByte & COM_CAST2UINT8(~(COM_CAST2UINT8(255u << nBitsToWrite)));      /* PRQA S 2986, 2793, 2842 */ /* MD_Com_2985_2986, MD_Com_2793, MD_Com_2842_SignalApplDestPtr */ /* SBSW_COM_WRITEACCESS_STACKPTR_WITH_LENGTH */
  }
}
#endif

#if ((COM_SIGNEXTREQUIREDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_SINT8_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
 Com_Signal_ReadSignalSignExtension_SINT8
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignalSignExtension_SINT8(Com_RxAccessInfoIterType idxAccessInfo, P2VAR(uSignExt8BitType, AUTOMATIC, COM_APPL_VAR) signExtValue)   /* PRQA S 0750 */ /* MD_MSR_Union */
{
  uint8 signMask, msbMask;
  Com_BitLengthOfRxAccessInfoType tmp = Com_GetBitLengthOfRxAccessInfo(idxAccessInfo) - 1u;
  uint8 signBitPos = Com_Signal_BitOffsetFromBitPos(tmp);

  signMask = COM_CAST2UINT8(1u << signBitPos);
  msbMask = COM_CAST2UINT8(255u << signBitPos);

  /* #10 if required, perform sign extension */
  if(0u != (signMask & signExtValue->unsignedAccess))
  {     /* negative value */
    signExtValue->unsignedAccess |= msbMask;    /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
  }
}
#endif

#if ((COM_SIGNEXTREQUIREDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_SINT16_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
 Com_Signal_ReadSignalSignExtension_SINT16
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignalSignExtension_SINT16(Com_RxAccessInfoIterType idxAccessInfo, P2VAR(uSignExt16BitType, AUTOMATIC, COM_APPL_VAR) signExtValue) /* PRQA S 0750, 3673 */ /* MD_MSR_Union, MD_MSR_Rule8.13 */
{
  uint8 signMask, msbMask;
  Com_BitLengthOfRxAccessInfoType tmp = Com_GetBitLengthOfRxAccessInfo(idxAccessInfo) - 1u;
  Com_BitLengthOfRxAccessInfoType signMSBOffset = tmp >> 3u;
  uint8 signBitPos = Com_Signal_BitOffsetFromBitPos(tmp);
  uint8 *destPtr;
# if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
  destPtr = &(signExtValue->unsignedAccess[0]);
# endif
# if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  destPtr = &(signExtValue->unsignedAccess[1]);
# endif

  signMask = COM_CAST2UINT8(1u << signBitPos);
  msbMask = COM_CAST2UINT8(255u << signBitPos);
  /* #10 if required, perform sign extension */
# if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
  /* Implementation for Intel Plattforms */
  if(0u != (signMask & destPtr[signMSBOffset]))
  {     /* negative value */
    if(0u == signMSBOffset)     /* COV_COM_SIGNMSBOFFSET */
    {   /* signal smaller or equal 8 bit */
      *destPtr |= msbMask;      /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
      destPtr[1] = 255u;        /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
    }
    else
    {
      destPtr[1] |= msbMask;    /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
    }
  }
# else /* (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */
  if(0u != (signMask & destPtr[(Com_BitLengthOfRxAccessInfoType) 0u - signMSBOffset]))  /* PRQA S 2986 */ /* MD_Com_2985_2986 */
  {     /* negative value */
    destPtr[(Com_BitLengthOfRxAccessInfoType) 0u - signMSBOffset] |= msbMask;   /* PRQA S 2986 */ /* MD_Com_2985_2986 */ /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
    if(0u == signMSBOffset)     /* COV_COM_SIGNMSBOFFSET */
    {   /* signal smaller or equal 8 bit */
      destPtr[-1] = 255u;       /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
    }
  }
# endif
}
#endif

#if ((COM_SIGNEXTREQUIREDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_SINT32_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
 Com_Signal_ReadSignalSignExtension_SINT32
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignalSignExtension_SINT32(Com_RxAccessInfoIterType idxAccessInfo, P2VAR(uSignExt32BitType, AUTOMATIC, COM_APPL_VAR) signExtValue) /* PRQA S 0750, 3673 */ /* MD_MSR_Union, MD_MSR_Rule8.13 */
{
  uint8 signMask, msbMask;
  Com_BitLengthOfRxAccessInfoType tmp = Com_GetBitLengthOfRxAccessInfo(idxAccessInfo) - 1u;
  Com_BitLengthOfRxAccessInfoType signMSBOffset = tmp >> 3u;
  uint8 signBitPos = Com_Signal_BitOffsetFromBitPos(tmp);
  uint8 *destPtr;
# if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
  destPtr = &(signExtValue->unsignedAccess[0]);
# endif
# if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  destPtr = &(signExtValue->unsignedAccess[3]);
# endif

  signMask = COM_CAST2UINT8(1u << signBitPos);
  msbMask = COM_CAST2UINT8(255u << signBitPos);

  /* #10 if required, perform sign extension */
# if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
  /* Implementation for Intel Plattforms */
  {
    sint16_least i;
    if(0u != (signMask & destPtr[signMSBOffset]))
    {   /* negative value */
      destPtr[signMSBOffset] |= msbMask;        /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
      for(i = (((sint16_least) signMSBOffset) + 1); i < 4; i++)
      {
        destPtr[i] = 255u;      /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
      }
    }
  }
# else /* (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */
  {
    sint16_least i;
    if(0u != (signMask & destPtr[0u - signMSBOffset]))  /* PRQA S 2986 */ /* MD_Com_2985_2986 */
    {   /* negative value */
      destPtr[0u - signMSBOffset] |= msbMask;   /* PRQA S 2986 */ /* MD_Com_2985_2986 */ /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
      for(i = (((sint16_least) signMSBOffset) + 1); i < 4; i++)
      {
        destPtr[-i] = 255u;     /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
      }
    }
  }
# endif
}
#endif

#if ((COM_SIGNEXTREQUIREDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_SINT64_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
 Com_Signal_ReadSignalSignExtension_SINT64
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(void, COM_CODE) Com_Signal_ReadSignalSignExtension_SINT64(Com_RxAccessInfoIterType idxAccessInfo, P2VAR(uSignExt64BitType, AUTOMATIC, COM_APPL_VAR) signExtValue) /* PRQA S 0750, 3673 */ /* MD_MSR_Union, MD_MSR_Rule8.13 */
{
  uint8 signMask, msbMask;
  Com_BitLengthOfRxAccessInfoType tmp = Com_GetBitLengthOfRxAccessInfo(idxAccessInfo) - 1u;
  Com_BitLengthOfRxAccessInfoType signMSBOffset = tmp >> 3u;
  uint8 signBitPos = Com_Signal_BitOffsetFromBitPos(tmp);
  uint8 *destPtr;
# if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
  destPtr = &(signExtValue->unsignedAccess[0]);
# endif
# if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  destPtr = &(signExtValue->unsignedAccess[7]);
# endif

  signMask = COM_CAST2UINT8(1u << signBitPos);
  msbMask = COM_CAST2UINT8(255u << signBitPos);

  /* #10 if required, perform sign extension */
# if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
  /* Implementation for Intel Plattforms */
  {
    sint16_least i;
    if(0u != (signMask & destPtr[signMSBOffset]))
    {   /* negative value */
      destPtr[signMSBOffset] |= msbMask;        /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
      for(i = ((sint16_least) signMSBOffset + 1); i < 8; i++)
      {
        destPtr[i] = 255u;      /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
      }
    }
  }
# else /* (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */
  {
    sint16_least i;
    if(0u != (signMask & destPtr[0u - signMSBOffset]))  /* PRQA S 2986 */ /* MD_Com_2985_2986 */
    {   /* negative value */
      destPtr[0u - signMSBOffset] |= msbMask;   /* PRQA S 2986 */ /* MD_Com_2985_2986 */ /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
      for(i = (((sint16_least) signMSBOffset) + 1); i < 8; i++)
      {
        destPtr[-i] = 255u;     /* SBSW_COM_WRITEACCESS_STACKPTR_01 */
      }
    }
  }
# endif
}
#endif


/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

#if ((COM_EXISTS_UINT8_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_UInt8
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_Signal_ReadSignal_UInt8(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr)
{
  uint8 tmpNewValue = 0;
  Com_Signal_ReadSignalApplTypeSpecific(idxRxAccessInfo, &tmpNewValue, SignalBusSourcePtr, 1);  /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */
  return tmpNewValue;
}
#endif

#if ((COM_EXISTS_SINT8_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_SInt8
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(sint8, COM_CODE) Com_Signal_ReadSignal_SInt8(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr)
{
  uSignExt8BitType tmpNewValue; /* PRQA S 0759 */ /* MD_MSR_Union */
  tmpNewValue.signedAccess = 0;
  Com_Signal_ReadSignalApplTypeSpecific(idxRxAccessInfo, &(tmpNewValue.unsignedAccess), SignalBusSourcePtr, 1); /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC */

# if (COM_SIGNEXTREQUIREDOFRXACCESSINFO == STD_ON)
  if(Com_IsSignExtRequiredOfRxAccessInfo(idxRxAccessInfo))
  {
    Com_Signal_ReadSignalSignExtension_SINT8(idxRxAccessInfo, &tmpNewValue);    /* SBSW_COM_FCTCALL_STACKPTR */
  }
# endif

  return tmpNewValue.signedAccess;
}
#endif

#if ((COM_EXISTS_UINT16_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_UInt16
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(uint16, COM_CODE) Com_Signal_ReadSignal_UInt16(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr)
{
  uint16 tmpNewValue = 0;
  uint8 *startBytePtr = &((P2VAR(uint8, AUTOMATIC, COM_APPL_VAR)) & tmpNewValue)[0];
  Com_Signal_ReadSignalApplTypeSpecific(idxRxAccessInfo, startBytePtr, SignalBusSourcePtr, 2);  /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC_AND_STACKPTR */

  return tmpNewValue;
}
#endif

#if ((COM_EXISTS_SINT16_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_SInt16
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(sint16, COM_CODE) Com_Signal_ReadSignal_SInt16(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr)
{
  uSignExt16BitType tmpNewValue;        /* PRQA S 0759 */ /* MD_MSR_Union */
  tmpNewValue.signedAccess = 0;
  Com_Signal_ReadSignalApplTypeSpecific(idxRxAccessInfo, &(tmpNewValue.unsignedAccess[0]), SignalBusSourcePtr, 2);      /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC_AND_STACKPTR */

# if (COM_SIGNEXTREQUIREDOFRXACCESSINFO == STD_ON)
  if(Com_IsSignExtRequiredOfRxAccessInfo(idxRxAccessInfo))
  {
    Com_Signal_ReadSignalSignExtension_SINT16(idxRxAccessInfo, &tmpNewValue);   /* SBSW_COM_FCTCALL_STACKPTR */
  }
# endif

  return tmpNewValue.signedAccess;
}
#endif

#if ((COM_EXISTS_UINT32_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_UInt32
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(uint32, COM_CODE) Com_Signal_ReadSignal_UInt32(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr)
{
  uint32 tmpNewValue = 0;
  uint8 *startBytePtr = &((P2VAR(uint8, AUTOMATIC, COM_APPL_VAR)) & tmpNewValue)[0];
  Com_Signal_ReadSignalApplTypeSpecific(idxRxAccessInfo, startBytePtr, SignalBusSourcePtr, 4);  /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC_AND_STACKPTR */

  return tmpNewValue;
}
#endif

#if ((COM_EXISTS_SINT32_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_SInt32
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(sint32, COM_CODE) Com_Signal_ReadSignal_SInt32(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr)
{
  uSignExt32BitType tmpNewValue;        /* PRQA S 0759 */ /* MD_MSR_Union */
  tmpNewValue.signedAccess = 0;

  Com_Signal_ReadSignalApplTypeSpecific(idxRxAccessInfo, &(tmpNewValue.unsignedAccess[0]), SignalBusSourcePtr, 4);      /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC_AND_STACKPTR */

# if (COM_SIGNEXTREQUIREDOFRXACCESSINFO == STD_ON)
  if(Com_IsSignExtRequiredOfRxAccessInfo(idxRxAccessInfo))
  {
    Com_Signal_ReadSignalSignExtension_SINT32(idxRxAccessInfo, &tmpNewValue);   /* SBSW_COM_FCTCALL_STACKPTR */
  }
# endif

  return tmpNewValue.signedAccess;
}
#endif

#if ((COM_EXISTS_UINT64_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_UInt64
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(uint64, COM_CODE) Com_Signal_ReadSignal_UInt64(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr)
{
  uint64 tmpNewValue = 0;
  uint8 *startBytePtr = &((P2VAR(uint8, AUTOMATIC, COM_APPL_VAR)) & tmpNewValue)[0];
  Com_Signal_ReadSignalApplTypeSpecific(idxRxAccessInfo, startBytePtr, SignalBusSourcePtr, 8);  /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC_AND_STACKPTR */

  return tmpNewValue;
}
#endif

#if ((COM_EXISTS_SINT64_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_SInt64
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(sint64, COM_CODE) Com_Signal_ReadSignal_SInt64(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr)
{
  uSignExt64BitType tmpNewValue;        /* PRQA S 0759 */ /* MD_MSR_Union */
  tmpNewValue.signedAccess = 0;

  Com_Signal_ReadSignalApplTypeSpecific(idxRxAccessInfo, &(tmpNewValue.unsignedAccess[0]), SignalBusSourcePtr, 8);      /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC_AND_STACKPTR */

# if (COM_SIGNEXTREQUIREDOFRXACCESSINFO == STD_ON)
  if(Com_IsSignExtRequiredOfRxAccessInfo(idxRxAccessInfo))
  {
    Com_Signal_ReadSignalSignExtension_SINT64(idxRxAccessInfo, &tmpNewValue);   /* SBSW_COM_FCTCALL_STACKPTR */
  }
# endif

  return tmpNewValue.signedAccess;
}
#endif

#if ((COM_EXISTS_FLOAT32_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_Float32
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(float32, COM_CODE) Com_Signal_ReadSignal_Float32(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr)
{
  float32 tmpNewValue = 0.0f;
  uint8 *startBytePtr = &((P2VAR(uint8, AUTOMATIC, COM_APPL_VAR)) & tmpNewValue)[0];
  Com_Signal_ReadSignalApplTypeSpecific(idxRxAccessInfo, startBytePtr, SignalBusSourcePtr, 4);  /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC_AND_STACKPTR */

  return tmpNewValue;
}
#endif

#if ((COM_EXISTS_FLOAT64_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_Signal_ReadSignal_Float64
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(float64, COM_CODE) Com_Signal_ReadSignal_Float64(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr)
{
  float64 tmpNewValue = 0.0;
  uint8 *startBytePtr = &((P2VAR(uint8, AUTOMATIC, COM_APPL_VAR)) & tmpNewValue)[0];
  Com_Signal_ReadSignalApplTypeSpecific(idxRxAccessInfo, startBytePtr, SignalBusSourcePtr, 8);  /* SBSW_COM_VALID_PTR_ENSURED_BY_CALLING_FUNC_AND_STACKPTR */

  return tmpNewValue;
}
#endif

#define COM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* *INDENT-OFF* */
/* Justifications for module-specific MISRA deviations:
   MD_Com_3213: Misra Rule 2.4
     Reason:     It depends on the configuration if the union tag is used or not.
     Risk:       No risk.
     Prevention: No prevention necessary.

   MD_Com_4391:  Misra Rule 10.8
     Reason:     The composite expression has to be cast as a whole because of the shift or bitwise operation. Shift and bitwise operations should only be performed with esentially unsigned types. The cast is necessary, because the result of the shift or bitwise operation is signed.
     Risk:       No risk
     Prevention: No prevention necessary

   MD_Com_4394:  Misra Rule 10.8
     Reason:     The composite expression has to be cast as a whole because of the shift or bitwise operation. Shift and bitwise operations should only be performed with esentially unsigned types. The cast is necessary, because the result of the shift or bitwise operation is signed.
     Risk:       No risk
     Prevention: No prevention necessary

  MD_Com_2793: Misra Rule 10.1, Misra Rule 12.2
     Reason:     nBitsToWrite is > 0 and is cast to uint8 so it isn't too large.
     Risk:       No risk.
     Prevention: No prevention necessary

  MD_Com_2842_SignalApplDestPtr: Misra Rule 18.1, Misra Rule 21.18, Misra Dir 4.1
     Reason:     SignalApplDestPtr is always initialized.
     Risk:       No risk.
     Prevention: No prevention necessary
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
 *  END OF FILE: Com_Deserializer.c
 *********************************************************************************************************************/
