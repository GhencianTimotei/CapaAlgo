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
/*!        \file  Com_SignalFilterHdlr.c
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/

#define COM_SIGNALFILTERHDLR_SOURCE

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Com.h"
#include "Com_SignalFilterHdlr.h"
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

/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#if (((COM_EXISTS_FLOAT64_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)) || ((COM_EXISTS_FLOAT64_APPLTYPEOFTXSIGINFO == STD_ON) && (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_FLOAT64 == STD_ON)))
/**********************************************************************************************************************
  Com_CalculateFloat64AbsValue
**********************************************************************************************************************/
/*! \brief        This function calculates the absolute value of a float64 value.
    \details      -
    \pre          -
    \param[in]    value                       value for which the absolute value is calculated.
    \return       positive float64 value
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(float64, COM_CODE) Com_CalculateFloat64AbsValue(float64 value);
#endif

#if ((COM_TXFILTERINITVALUEARRAYBASEDFILTERINITVALUEUSEDOFTXSIGINFO == STD_ON) || (COM_FILTERINITVALUEIDXOFTXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_GetOldValuePtr
**********************************************************************************************************************/
/*! \brief        This method delivers a pointer to Com_TxFilterOldValueX according to Com_GetFilterInitValueIdxOfTxSigInfo(idxTxSigInfo)
    \details      -
    \pre          -
    \param[in]    idxTxSigInfo      Index of Tx Signal Info
    \return       P2CONST(void, AUTOMATIC, AUTOMATIC), COM_CODE)
    \context      TASK|ISR2
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(P2CONST(void, AUTOMATIC, AUTOMATIC), COM_CODE) Com_GetOldValuePtr(Com_TxSigInfoIterType idxTxSigInfo);
#endif

#if (((COM_EXISTS_FLOAT32_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)) || ((COM_EXISTS_FLOAT32_APPLTYPEOFTXSIGINFO == STD_ON) && (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_FLOAT32 == STD_ON)))
/**********************************************************************************************************************
  Com_CalculateFloat32AbsValue
**********************************************************************************************************************/
/*! \brief        This function calculates the absolute value of a float32 value.
    \details      -
    \pre          -
    \param[in]    value                       value for which the absolute value is calculated.
    \return       positive float32 value
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(float32, COM_CODE) Com_CalculateFloat32AbsValue(float32 value);
#endif

#if   ((COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_UINT8 == STD_ON) || (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_UINT8 == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_UInt8_NewIsWithIn
*********************************************************************************************************************/
/*!
    \brief        Checks if the new value is within the configured range.
    \details      -
    \pre          -
    \param[in]    idxFilterInfo      index of filter info
    \param[in]    newValue           new value
    \return       filter result
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Signal_UInt8_NewIsWithIn(Com_FilterInfo_UInt8IterType idxFilterInfo, uint8 newValue);
#endif

#if   ((COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_SINT8 == STD_ON) || (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_SINT8 == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_SInt8_NewIsWithIn
*********************************************************************************************************************/
/*!
    \brief        Checks if the new value is within the configured range.
    \details      -
    \pre          -
    \param[in]    idxFilterInfo      index of filter info
    \param[in]    newValue           new value
    \return       filter result
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Signal_SInt8_NewIsWithIn(Com_FilterInfo_SInt8IterType idxFilterInfo, sint8 newValue);
#endif

#if   ((COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_UINT16 == STD_ON) || (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_UINT16 == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_UInt16_NewIsWithIn
*********************************************************************************************************************/
/*!
    \brief        Checks if the new value is within the configured range.
    \details      -
    \pre          -
    \param[in]    idxFilterInfo      index of filter info
    \param[in]    newValue           new value
    \return       filter result
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Signal_UInt16_NewIsWithIn(Com_FilterInfo_UInt16IterType idxFilterInfo, uint16 newValue);
#endif

#if   ((COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_SINT16 == STD_ON) || (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_SINT16 == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_SInt16_NewIsWithIn
*********************************************************************************************************************/
/*!
    \brief        Checks if the new value is within the configured range.
    \details      -
    \pre          -
    \param[in]    idxFilterInfo      index of filter info
    \param[in]    newValue           new value
    \return       filter result
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Signal_SInt16_NewIsWithIn(Com_FilterInfo_SInt16IterType idxFilterInfo, sint16 newValue);
#endif

#if   ((COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_UINT32 == STD_ON) || (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_UINT32 == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_UInt32_NewIsWithIn
*********************************************************************************************************************/
/*!
    \brief        Checks if the new value is within the configured range.
    \details      -
    \pre          -
    \param[in]    idxFilterInfo      index of filter info
    \param[in]    newValue           new value
    \return       filter result
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Signal_UInt32_NewIsWithIn(Com_FilterInfo_UInt32IterType idxFilterInfo, uint32 newValue);
#endif

#if   ((COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_SINT32 == STD_ON) || (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_SINT32 == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_SInt32_NewIsWithIn
*********************************************************************************************************************/
/*!
    \brief        Checks if the new value is within the configured range.
    \details      -
    \pre          -
    \param[in]    idxFilterInfo      index of filter info
    \param[in]    newValue           new value
    \return       filter result
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Signal_SInt32_NewIsWithIn(Com_FilterInfo_SInt32IterType idxFilterInfo, sint32 newValue);
#endif

#if   ((COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_UINT64 == STD_ON) || (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_UINT64 == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_UInt64_NewIsWithIn
*********************************************************************************************************************/
/*!
    \brief        Checks if the new value is within the configured range.
    \details      -
    \pre          -
    \param[in]    idxFilterInfo      index of filter info
    \param[in]    newValue           new value
    \return       filter result
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Signal_UInt64_NewIsWithIn(Com_FilterInfo_UInt64IterType idxFilterInfo, uint64 newValue);
#endif

#if   ((COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_SINT64 == STD_ON) || (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_SINT64 == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_SInt64_NewIsWithIn
*********************************************************************************************************************/
/*!
    \brief        Checks if the new value is within the configured range.
    \details      -
    \pre          -
    \param[in]    idxFilterInfo      index of filter info
    \param[in]    newValue           new value
    \return       filter result
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Signal_SInt64_NewIsWithIn(Com_FilterInfo_SInt64IterType idxFilterInfo, sint64 newValue);
#endif

/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

#if (((COM_EXISTS_FLOAT64_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)) || ((COM_EXISTS_FLOAT64_APPLTYPEOFTXSIGINFO == STD_ON) && (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_FLOAT64 == STD_ON)))
/**********************************************************************************************************************
  Com_CalculateFloat64AbsValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(float64, COM_CODE) Com_CalculateFloat64AbsValue(float64 value)
{
  /* #10 If the passed value is negative, calculate the absolute value and return the positive value */
  return (value < 0.0) ? -value : value;
}
#endif

#if (((COM_EXISTS_FLOAT32_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)) || ((COM_EXISTS_FLOAT32_APPLTYPEOFTXSIGINFO == STD_ON) && (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_FLOAT32 == STD_ON)))
/**********************************************************************************************************************
  Com_CalculateFloat32AbsValue
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(float32, COM_CODE) Com_CalculateFloat32AbsValue(float32 value)
{
  /* #10 If the passed value is negative, calculate the absolute value and return the positive value */
  return (value < 0.0f) ? -value : value;
}
#endif

#if ((COM_TXFILTERINITVALUEARRAYBASEDFILTERINITVALUEUSEDOFTXSIGINFO == STD_ON) || (COM_FILTERINITVALUEIDXOFTXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_GetOldValuePtr
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(P2CONST(void, AUTOMATIC, AUTOMATIC), COM_CODE) Com_GetOldValuePtr(Com_TxSigInfoIterType idxTxSigInfo)
{
  P2CONST(void, AUTOMATIC, AUTOMATIC) oldValuePtr = NULL_PTR;
  /* #10 Get the old value pointer of the ApplType related buffer */
# if(COM_FILTERINITVALUEUSEDOFTXSIGINFO == STD_ON)
  if(Com_IsFilterInitValueUsedOfTxSigInfo(idxTxSigInfo))        /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_FilterInitValueIdxOfTxSigInfoType idxTxFilterOldValue = Com_GetFilterInitValueIdxOfTxSigInfo(idxTxSigInfo);

    switch (Com_GetApplTypeOfTxSigInfo(idxTxSigInfo))
    {
#  if (COM_TXFILTERINITVALUEUINT8 == STD_ON)
      case COM_UINT8_APPLTYPEOFTXSIGINFO:
      {
        oldValuePtr = (P2CONST(void, AUTOMATIC, AUTOMATIC)) Com_GetAddrTxFilterOldValueUInt8(idxTxFilterOldValue);      /* PRQA S 0314 */ /* MD_Com_0314_0315 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUESINT8 == STD_ON)
      case COM_SINT8_APPLTYPEOFTXSIGINFO:
      {
        oldValuePtr = (P2CONST(void, AUTOMATIC, AUTOMATIC)) Com_GetAddrTxFilterOldValueSInt8(idxTxFilterOldValue);      /* PRQA S 0314 */ /* MD_Com_0314_0315 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUEUINT16 == STD_ON)
      case COM_UINT16_APPLTYPEOFTXSIGINFO:
      {
        oldValuePtr = (P2CONST(void, AUTOMATIC, AUTOMATIC)) Com_GetAddrTxFilterOldValueUInt16(idxTxFilterOldValue);     /* PRQA S 0314 */ /* MD_Com_0314_0315 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUESINT16 == STD_ON)
      case COM_SINT16_APPLTYPEOFTXSIGINFO:
      {
        oldValuePtr = (P2CONST(void, AUTOMATIC, AUTOMATIC)) Com_GetAddrTxFilterOldValueSInt16(idxTxFilterOldValue);     /* PRQA S 0314 */ /* MD_Com_0314_0315 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUEUINT32 == STD_ON)
      case COM_UINT32_APPLTYPEOFTXSIGINFO:
      {
        oldValuePtr = (P2CONST(void, AUTOMATIC, AUTOMATIC)) Com_GetAddrTxFilterOldValueUInt32(idxTxFilterOldValue);     /* PRQA S 0314 */ /* MD_Com_0314_0315 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUESINT32 == STD_ON)
      case COM_SINT32_APPLTYPEOFTXSIGINFO:
      {
        oldValuePtr = (P2CONST(void, AUTOMATIC, AUTOMATIC)) Com_GetAddrTxFilterOldValueSInt32(idxTxFilterOldValue);     /* PRQA S 0314 */ /* MD_Com_0314_0315 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUEUINT64 == STD_ON)
      case COM_UINT64_APPLTYPEOFTXSIGINFO:
      {
        oldValuePtr = (P2CONST(void, AUTOMATIC, AUTOMATIC)) Com_GetAddrTxFilterOldValueUInt64(idxTxFilterOldValue);     /* PRQA S 0314 */ /* MD_Com_0314_0315 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUESINT64 == STD_ON)
      case COM_SINT64_APPLTYPEOFTXSIGINFO:
      {
        oldValuePtr = (P2CONST(void, AUTOMATIC, AUTOMATIC)) Com_GetAddrTxFilterOldValueSInt64(idxTxFilterOldValue);     /* PRQA S 0314 */ /* MD_Com_0314_0315 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUEFLOAT32 == STD_ON)
      case COM_FLOAT32_APPLTYPEOFTXSIGINFO:
      {
        oldValuePtr = (P2CONST(void, AUTOMATIC, AUTOMATIC)) Com_GetAddrTxFilterOldValueFloat32(idxTxFilterOldValue);    /* PRQA S 0314 */ /* MD_Com_0314_0315 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUEFLOAT64 == STD_ON)
      case COM_FLOAT64_APPLTYPEOFTXSIGINFO:
      {
        oldValuePtr = (P2CONST(void, AUTOMATIC, AUTOMATIC)) Com_GetAddrTxFilterOldValueFloat64(idxTxFilterOldValue);    /* PRQA S 0314 */ /* MD_Com_0314_0315 */
        break;
      }
#  endif
      default: /* COV_COM_MISRA */
        break;
    }
  }
# endif

# if ((COM_TXFILTERINITVALUEARRAYBASEDFILTERINITVALUEUSEDOFTXSIGINFO == STD_ON) && (COM_EXISTS_UINT8_N_APPLTYPEOFTXSIGINFO == STD_ON))
  if(Com_GetApplTypeOfTxSigInfo(idxTxSigInfo) == COM_UINT8_N_APPLTYPEOFTXSIGINFO)       /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    oldValuePtr = (P2CONST(void, AUTOMATIC, AUTOMATIC)) Com_GetAddrTxFilterOldValueArrayBased(Com_GetTxFilterInitValueArrayBasedFilterInitValueStartIdxOfTxSigInfo(idxTxSigInfo));      /* PRQA S 0314 */ /* MD_Com_0314_0315 */
  }
# endif
  return oldValuePtr;
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if   ((COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_UINT8 == STD_ON) || (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_UINT8 == STD_ON))
/**********************************************************************************************************************
  Com_Signal_UInt8_NewIsWithIn
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Signal_UInt8_NewIsWithIn(Com_FilterInfo_UInt8IterType idxFilterInfo, uint8 newValue)
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  uint8 filterMin = Com_GetFilterMinOfFilterInfo_UInt8(idxFilterInfo);
  uint8 filterMax = Com_GetFilterMaxOfFilterInfo_UInt8(idxFilterInfo);

  if((filterMin <= newValue) && (newValue <= filterMax))
  {
    filterState = TRUE;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return filterState;
}
#endif

#if   ((COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_SINT8 == STD_ON) || (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_SINT8 == STD_ON))
/**********************************************************************************************************************
  Com_Signal_SInt8_NewIsWithIn
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Signal_SInt8_NewIsWithIn(Com_FilterInfo_SInt8IterType idxFilterInfo, sint8 newValue)
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  sint8 filterMin = Com_GetFilterMinOfFilterInfo_SInt8(idxFilterInfo);
  sint8 filterMax = Com_GetFilterMaxOfFilterInfo_SInt8(idxFilterInfo);

  if((filterMin <= newValue) && (newValue <= filterMax))
  {
    filterState = TRUE;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return filterState;
}
#endif

#if   ((COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_UINT16 == STD_ON) || (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_UINT16 == STD_ON))
/**********************************************************************************************************************
  Com_Signal_UInt16_NewIsWithIn
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Signal_UInt16_NewIsWithIn(Com_FilterInfo_UInt16IterType idxFilterInfo, uint16 newValue)
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  uint16 filterMin = Com_GetFilterMinOfFilterInfo_UInt16(idxFilterInfo);
  uint16 filterMax = Com_GetFilterMaxOfFilterInfo_UInt16(idxFilterInfo);

  if((filterMin <= newValue) && (newValue <= filterMax))
  {
    filterState = TRUE;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return filterState;
}
#endif

#if   ((COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_SINT16 == STD_ON) || (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_SINT16 == STD_ON))
/**********************************************************************************************************************
  Com_Signal_SInt16_NewIsWithIn
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Signal_SInt16_NewIsWithIn(Com_FilterInfo_SInt16IterType idxFilterInfo, sint16 newValue)
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  sint16 filterMin = Com_GetFilterMinOfFilterInfo_SInt16(idxFilterInfo);
  sint16 filterMax = Com_GetFilterMaxOfFilterInfo_SInt16(idxFilterInfo);

  if((filterMin <= newValue) && (newValue <= filterMax))
  {
    filterState = TRUE;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return filterState;
}
#endif

#if   ((COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_UINT32 == STD_ON) || (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_UINT32 == STD_ON))
/**********************************************************************************************************************
  Com_Signal_UInt32_NewIsWithIn
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Signal_UInt32_NewIsWithIn(Com_FilterInfo_UInt32IterType idxFilterInfo, uint32 newValue)
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  uint32 filterMin = Com_GetFilterMinOfFilterInfo_UInt32(idxFilterInfo);
  uint32 filterMax = Com_GetFilterMaxOfFilterInfo_UInt32(idxFilterInfo);

  if((filterMin <= newValue) && (newValue <= filterMax))
  {
    filterState = TRUE;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return filterState;
}
#endif

#if   ((COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_SINT32 == STD_ON) || (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_SINT32 == STD_ON))
/**********************************************************************************************************************
  Com_Signal_SInt32_NewIsWithIn
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Signal_SInt32_NewIsWithIn(Com_FilterInfo_SInt32IterType idxFilterInfo, sint32 newValue)
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  sint32 filterMin = Com_GetFilterMinOfFilterInfo_SInt32(idxFilterInfo);
  sint32 filterMax = Com_GetFilterMaxOfFilterInfo_SInt32(idxFilterInfo);

  if((filterMin <= newValue) && (newValue <= filterMax))
  {
    filterState = TRUE;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return filterState;
}
#endif

#if   ((COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_UINT64 == STD_ON) || (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_UINT64 == STD_ON))
/**********************************************************************************************************************
  Com_Signal_UInt64_NewIsWithIn
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Signal_UInt64_NewIsWithIn(Com_FilterInfo_UInt64IterType idxFilterInfo, uint64 newValue)
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  uint64 filterMin = Com_GetFilterMinOfFilterInfo_UInt64(idxFilterInfo);
  uint64 filterMax = Com_GetFilterMaxOfFilterInfo_UInt64(idxFilterInfo);

  if((filterMin <= newValue) && (newValue <= filterMax))
  {
    filterState = TRUE;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return filterState;
}
#endif

#if   ((COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_SINT64 == STD_ON) || (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_SINT64 == STD_ON))
/**********************************************************************************************************************
  Com_Signal_SInt64_NewIsWithIn
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
COM_LOCAL_INLINE FUNC(boolean, COM_CODE) Com_Signal_SInt64_NewIsWithIn(Com_FilterInfo_SInt64IterType idxFilterInfo, sint64 newValue)
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  sint64 filterMin = Com_GetFilterMinOfFilterInfo_SInt64(idxFilterInfo);
  sint64 filterMax = Com_GetFilterMaxOfFilterInfo_SInt64(idxFilterInfo);

  if((filterMin <= newValue) && (newValue <= filterMax))
  {
    filterState = TRUE;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return filterState;
}
#endif

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

#if (((COM_EXISTS_FLOAT32_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)) || ((COM_EXISTS_FLOAT32_APPLTYPEOFTXSIGINFO == STD_ON) && (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_FLOAT32 == STD_ON)))
/**********************************************************************************************************************
  Com_CompareFloat32Values
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_CompareFloat32Values(float32 firstValue, float32 scndValue)
{
  boolean retVal = FALSE;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* #10 If the difference between both float32 values is smaller than COM_FLT_EPSILON. */
  if(Com_CalculateFloat32AbsValue(firstValue - scndValue) < COM_FLT_EPSILON)
  {
    retVal = TRUE;
  }
  return retVal;
}
#endif

#if (((COM_EXISTS_FLOAT64_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)) || ((COM_EXISTS_FLOAT64_APPLTYPEOFTXSIGINFO == STD_ON) && (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_FLOAT64 == STD_ON)))
/**********************************************************************************************************************
  Com_CompareFloat64Values
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_CompareFloat64Values(float64 firstValue, float64 scndValue)
{
  boolean retVal = FALSE;       /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* #10 If the difference between both float64 values is smaller than COM_DBL_EPSILON. */
  if(Com_CalculateFloat64AbsValue(firstValue - scndValue) < COM_DBL_EPSILON)
  {
    retVal = TRUE;
  }
  return retVal;
}
#endif

#if ((COM_TXFILTERINITVALUEARRAYBASEDFILTERINITVALUEUSEDOFTXSIGINFO == STD_ON) || (COM_FILTERINITVALUEIDXOFTXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_SetTxFilterOldValueX
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_SetTxFilterOldValueX(Com_TxSigInfoIterType idxTxSigInfo, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr, uint16 Length)
{
  /* #10 Copy the passed value to the ApplType related old value buffer */
# if (COM_FILTERINITVALUEUSEDOFTXSIGINFO == STD_ON)
  if(Com_IsFilterInitValueUsedOfTxSigInfo(idxTxSigInfo))        /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_FilterInitValueIdxOfTxSigInfoType idxTxFilterOldValue = Com_GetFilterInitValueIdxOfTxSigInfo(idxTxSigInfo);
    switch (Com_GetApplTypeOfTxSigInfo(idxTxSigInfo))
    {
#  if (COM_TXFILTERINITVALUEUINT8 == STD_ON)
      case COM_UINT8_APPLTYPEOFTXSIGINFO:
      {
        Com_SetTxFilterOldValueUInt8(idxTxFilterOldValue, *((P2CONST(uint8, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr)); /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_CSL02 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUESINT8 == STD_ON)
      case COM_SINT8_APPLTYPEOFTXSIGINFO:
      {
        Com_SetTxFilterOldValueSInt8(idxTxFilterOldValue, *((P2CONST(sint8, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr)); /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_CSL02 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUEUINT16 == STD_ON)
      case COM_UINT16_APPLTYPEOFTXSIGINFO:
      {
        Com_SetTxFilterOldValueUInt16(idxTxFilterOldValue, *((P2CONST(uint16, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr));       /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_CSL02 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUESINT16 == STD_ON)
      case COM_SINT16_APPLTYPEOFTXSIGINFO:
      {
        Com_SetTxFilterOldValueSInt16(idxTxFilterOldValue, *((P2CONST(sint16, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr));       /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_CSL02 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUEUINT32 == STD_ON)
      case COM_UINT32_APPLTYPEOFTXSIGINFO:
      {
        Com_SetTxFilterOldValueUInt32(idxTxFilterOldValue, *((P2CONST(uint32, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr));       /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_CSL02 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUESINT32 == STD_ON)
      case COM_SINT32_APPLTYPEOFTXSIGINFO:
      {
        Com_SetTxFilterOldValueSInt32(idxTxFilterOldValue, *((P2CONST(sint32, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr));       /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_CSL02 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUEUINT64 == STD_ON)
      case COM_UINT64_APPLTYPEOFTXSIGINFO:
      {
        Com_SetTxFilterOldValueUInt64(idxTxFilterOldValue, *((P2CONST(uint64, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr));       /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_CSL02 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUESINT64 == STD_ON)
      case COM_SINT64_APPLTYPEOFTXSIGINFO:
      {
        Com_SetTxFilterOldValueSInt64(idxTxFilterOldValue, *((P2CONST(sint64, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr));       /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_CSL02 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUEFLOAT32 == STD_ON)
      case COM_FLOAT32_APPLTYPEOFTXSIGINFO:
      {
        Com_SetTxFilterOldValueFloat32(idxTxFilterOldValue, *((P2CONST(float32, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr));     /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_CSL02 */
        break;
      }
#  endif
#  if (COM_TXFILTERINITVALUEFLOAT64 == STD_ON)
      case COM_FLOAT64_APPLTYPEOFTXSIGINFO:
      {
        Com_SetTxFilterOldValueFloat64(idxTxFilterOldValue, *((P2CONST(float64, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr));     /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_CSL02 */
        break;
      }
#  endif
      default: /* COV_COM_MISRA */
        break;
    }
  }
# endif

# if ((COM_TXFILTERINITVALUEARRAYBASEDFILTERINITVALUEUSEDOFTXSIGINFO == STD_ON) && (COM_EXISTS_UINT8_N_APPLTYPEOFTXSIGINFO == STD_ON))
  if(Com_IsTxFilterInitValueArrayBasedFilterInitValueUsedOfTxSigInfo(idxTxSigInfo))     /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
  {
    Com_TxFilterInitValueArrayBasedIterType bufferIdx = Com_GetTxFilterInitValueArrayBasedFilterInitValueStartIdxOfTxSigInfo(idxTxSigInfo);
    VStdMemCpyRamToRam(Com_GetAddrTxFilterOldValueArrayBased(bufferIdx), (P2CONST(uint8, AUTOMATIC, COM_APPL_DATA)) SignalDataPtr, Com_GetTxFilterInitValueArrayBasedFilterInitValueLengthOfTxSigInfo(idxTxSigInfo));   /* PRQA S 0315, 0316 */ /* MD_MSR_VStdLibCopy, MD_Com_0316_0317 */ /* SBSW_COM_CSL03 */
  }
# endif

  COM_DUMMY_STATEMENT(Length);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if ((COM_FILTERINFOUSEDOFTXSIGINFO == STD_ON) || (COM_ONCHANGEUSEDOFTXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_TxSignal_EvaluateFilter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_TxSignal_EvaluateFilter(Com_TxSigInfoIterType idxTxSigInfo, uint32 idxFilterInfo, P2CONST(void, AUTOMATIC, AUTOMATIC) newValuePtr)
{
  /* #10 Apply the filter state using the filter algorithm of the passed FilterInfo */
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */
  switch (Com_GetApplTypeOfTxSigInfo(idxTxSigInfo))
  {
# if ((COM_FILTERINFO_UINT8 == STD_ON) &&(COM_EXISTS_UINT8_APPLTYPEOFTXSIGINFO == STD_ON))
    case (COM_UINT8_APPLTYPEOFTXSIGINFO):
    {
      uint8 oldValue = 0;
#  if (COM_FILTERINITVALUEUSEDOFTXSIGINFO == STD_ON)
      if(Com_IsFilterInitValueUsedOfTxSigInfo(idxTxSigInfo))    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        P2CONST(uint8, AUTOMATIC, AUTOMATIC) oldValuePtr = Com_GetOldValuePtr(idxTxSigInfo);    /* PRQA S 0317 */ /* MD_Com_0316_0317 */
        oldValue = *oldValuePtr;
      }
#  endif
      filterState = Com_Signal_UInt8_EvaluateFilter((Com_FilterInfo_UInt8IterType) idxFilterInfo, *((P2CONST(uint8, AUTOMATIC, AUTOMATIC)) newValuePtr), oldValue, FALSE);      /* PRQA S 0316 */ /* MD_Com_0316_0317 */
      break;
    }
# endif

# if ((COM_FILTERINFO_SINT8 == STD_ON) &&(COM_EXISTS_SINT8_APPLTYPEOFTXSIGINFO == STD_ON))
    case (COM_SINT8_APPLTYPEOFTXSIGINFO):
    {
      sint8 oldValue = 0;
#  if (COM_FILTERINITVALUEUSEDOFTXSIGINFO == STD_ON)
      if(Com_IsFilterInitValueUsedOfTxSigInfo(idxTxSigInfo))    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        P2CONST(sint8, AUTOMATIC, AUTOMATIC) oldValuePtr = Com_GetOldValuePtr(idxTxSigInfo);    /* PRQA S 0317 */ /* MD_Com_0316_0317 */
        oldValue = *oldValuePtr;
      }
#  endif
      filterState = Com_Signal_SInt8_EvaluateFilter((Com_FilterInfo_SInt8IterType) idxFilterInfo, *((P2CONST(sint8, AUTOMATIC, AUTOMATIC)) newValuePtr), oldValue, FALSE);      /* PRQA S 0316 */ /* MD_Com_0316_0317 */
      break;
    }
# endif

# if ((COM_FILTERINFO_UINT16 == STD_ON) &&(COM_EXISTS_UINT16_APPLTYPEOFTXSIGINFO == STD_ON))
    case (COM_UINT16_APPLTYPEOFTXSIGINFO):
    {
      uint16 oldValue = 0;
#  if (COM_FILTERINITVALUEUSEDOFTXSIGINFO == STD_ON)
      if(Com_IsFilterInitValueUsedOfTxSigInfo(idxTxSigInfo))    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        P2CONST(uint16, AUTOMATIC, AUTOMATIC) oldValuePtr = Com_GetOldValuePtr(idxTxSigInfo);   /* PRQA S 0317 */ /* MD_Com_0316_0317 */
        oldValue = *oldValuePtr;
      }
#  endif
      filterState = Com_Signal_UInt16_EvaluateFilter((Com_FilterInfo_UInt16IterType) idxFilterInfo, *((P2CONST(uint16, AUTOMATIC, AUTOMATIC)) newValuePtr), oldValue, FALSE);   /* PRQA S 0316 */ /* MD_Com_0316_0317 */
      break;
    }
# endif

# if ((COM_FILTERINFO_SINT16 == STD_ON) &&(COM_EXISTS_SINT16_APPLTYPEOFTXSIGINFO == STD_ON))
    case (COM_SINT16_APPLTYPEOFTXSIGINFO):
    {
      sint16 oldValue = 0;
#  if (COM_FILTERINITVALUEUSEDOFTXSIGINFO == STD_ON)
      if(Com_IsFilterInitValueUsedOfTxSigInfo(idxTxSigInfo))    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        P2CONST(sint16, AUTOMATIC, AUTOMATIC) oldValuePtr = Com_GetOldValuePtr(idxTxSigInfo);   /* PRQA S 0317 */ /* MD_Com_0316_0317 */
        oldValue = *oldValuePtr;
      }
#  endif
      filterState = Com_Signal_SInt16_EvaluateFilter((Com_FilterInfo_SInt16IterType) idxFilterInfo, *((P2CONST(sint16, AUTOMATIC, AUTOMATIC)) newValuePtr), oldValue, FALSE);   /* PRQA S 0316 */ /* MD_Com_0316_0317 */
      break;
    }
# endif

# if ((COM_FILTERINFO_UINT32 == STD_ON) &&(COM_EXISTS_UINT32_APPLTYPEOFTXSIGINFO == STD_ON))
    case (COM_UINT32_APPLTYPEOFTXSIGINFO):
    {
      uint32 oldValue = 0;
#  if (COM_FILTERINITVALUEUSEDOFTXSIGINFO == STD_ON)
      if(Com_IsFilterInitValueUsedOfTxSigInfo(idxTxSigInfo))    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        P2CONST(uint32, AUTOMATIC, AUTOMATIC) oldValuePtr = Com_GetOldValuePtr(idxTxSigInfo);   /* PRQA S 0317 */ /* MD_Com_0316_0317 */
        oldValue = *oldValuePtr;
      }
#  endif
      filterState = Com_Signal_UInt32_EvaluateFilter((Com_FilterInfo_UInt32IterType) idxFilterInfo, *((P2CONST(uint32, AUTOMATIC, AUTOMATIC)) newValuePtr), oldValue, FALSE);   /* PRQA S 0316 */ /* MD_Com_0316_0317 */
      break;
    }
# endif

# if ((COM_FILTERINFO_SINT32 == STD_ON) &&(COM_EXISTS_SINT32_APPLTYPEOFTXSIGINFO == STD_ON))
    case (COM_SINT32_APPLTYPEOFTXSIGINFO):
    {
      sint32 oldValue = 0;
#  if (COM_FILTERINITVALUEUSEDOFTXSIGINFO == STD_ON)
      if(Com_IsFilterInitValueUsedOfTxSigInfo(idxTxSigInfo))    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        P2CONST(sint32, AUTOMATIC, AUTOMATIC) oldValuePtr = Com_GetOldValuePtr(idxTxSigInfo);   /* PRQA S 0317 */ /* MD_Com_0316_0317 */
        oldValue = *oldValuePtr;
      }
#  endif
      filterState = Com_Signal_SInt32_EvaluateFilter((Com_FilterInfo_SInt32IterType) idxFilterInfo, *((P2CONST(sint32, AUTOMATIC, AUTOMATIC)) newValuePtr), oldValue, FALSE);   /* PRQA S 0316 */ /* MD_Com_0316_0317 */
      break;
    }
# endif

# if ((COM_FILTERINFO_UINT64 == STD_ON) &&(COM_EXISTS_UINT64_APPLTYPEOFTXSIGINFO == STD_ON))
    case (COM_UINT64_APPLTYPEOFTXSIGINFO):
    {
      uint64 oldValue = 0;
#  if (COM_FILTERINITVALUEUSEDOFTXSIGINFO == STD_ON)
      if(Com_IsFilterInitValueUsedOfTxSigInfo(idxTxSigInfo))    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        P2CONST(uint64, AUTOMATIC, AUTOMATIC) oldValuePtr = Com_GetOldValuePtr(idxTxSigInfo);   /* PRQA S 0317 */ /* MD_Com_0316_0317 */
        oldValue = *oldValuePtr;
      }
#  endif
      filterState = Com_Signal_UInt64_EvaluateFilter((Com_FilterInfo_UInt64IterType) idxFilterInfo, *((P2CONST(uint64, AUTOMATIC, AUTOMATIC)) newValuePtr), oldValue, FALSE);   /* PRQA S 0316 */ /* MD_Com_0316_0317 */
      break;
    }
# endif

# if ((COM_FILTERINFO_SINT64 == STD_ON) &&(COM_EXISTS_SINT64_APPLTYPEOFTXSIGINFO == STD_ON))
    case (COM_SINT64_APPLTYPEOFTXSIGINFO):
    {
      sint64 oldValue = 0;
#  if (COM_FILTERINITVALUEUSEDOFTXSIGINFO == STD_ON)
      if(Com_IsFilterInitValueUsedOfTxSigInfo(idxTxSigInfo))    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        P2CONST(sint64, AUTOMATIC, AUTOMATIC) oldValuePtr = Com_GetOldValuePtr(idxTxSigInfo);   /* PRQA S 0317 */ /* MD_Com_0316_0317 */
        oldValue = *oldValuePtr;
      }
#  endif
      filterState = Com_Signal_SInt64_EvaluateFilter((Com_FilterInfo_SInt64IterType) idxFilterInfo, *((P2CONST(sint64, AUTOMATIC, AUTOMATIC)) newValuePtr), oldValue, FALSE);   /* PRQA S 0316 */ /* MD_Com_0316_0317 */
      break;
    }
# endif

# if ((COM_FILTERINFO_FLOAT32 == STD_ON) &&(COM_EXISTS_FLOAT32_APPLTYPEOFTXSIGINFO == STD_ON))
    case (COM_FLOAT32_APPLTYPEOFTXSIGINFO):
    {
      float32 oldValue = 0.0f;
      if(Com_IsFilterInitValueUsedOfTxSigInfo(idxTxSigInfo))    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        P2CONST(float32, AUTOMATIC, AUTOMATIC) oldValuePtr = Com_GetOldValuePtr(idxTxSigInfo);  /* PRQA S 0317 */ /* MD_Com_0316_0317 */
        oldValue = *oldValuePtr;
      }
      filterState = Com_Signal_Float32_EvaluateFilter((Com_FilterInfo_Float32IterType) idxFilterInfo, *((P2CONST(float32, AUTOMATIC, AUTOMATIC)) newValuePtr), oldValue, FALSE);        /* PRQA S 0316 */ /* MD_Com_0316_0317 */
      break;
    }
# endif

# if ((COM_FILTERINFO_FLOAT64 == STD_ON) &&(COM_EXISTS_FLOAT64_APPLTYPEOFTXSIGINFO == STD_ON))
    case (COM_FLOAT64_APPLTYPEOFTXSIGINFO):
    {
      float64 oldValue = 0.0;
      if(Com_IsFilterInitValueUsedOfTxSigInfo(idxTxSigInfo))    /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        P2CONST(float64, AUTOMATIC, AUTOMATIC) oldValuePtr = Com_GetOldValuePtr(idxTxSigInfo);  /* PRQA S 0317 */ /* MD_Com_0316_0317 */
        oldValue = *oldValuePtr;
      }
      filterState = Com_Signal_Float64_EvaluateFilter((Com_FilterInfo_Float64IterType) idxFilterInfo, *((P2CONST(float64, AUTOMATIC, AUTOMATIC)) newValuePtr), oldValue, FALSE);        /* PRQA S 0316 */ /* MD_Com_0316_0317 */
      break;
    }
# endif

# if ((COM_FILTERINFO_UINT8_N == STD_ON) && (COM_EXISTS_UINT8_N_APPLTYPEOFTXSIGINFO == STD_ON))
    case (COM_UINT8_N_APPLTYPEOFTXSIGINFO):
    {
      P2CONST(uint8, AUTOMATIC, AUTOMATIC) oldValuePtr = NULL_PTR;
      /* Currently FILTERINFO_UINT8_N only exists when TriggeredOnChange or MASKED_NEW_DIFFERS_MASKED_OLD */
#  if (COM_TXFILTERINITVALUEARRAYBASEDFILTERINITVALUEUSEDOFTXSIGINFO == STD_ON) /* COV_COM_VAR_DEPENDENT_SWITCH */
      if(Com_IsTxFilterInitValueArrayBasedFilterInitValueUsedOfTxSigInfo(idxTxSigInfo)) /* COV_COM_FEATURE_ALWAYS_TRUE_TX */
      {
        oldValuePtr = Com_GetOldValuePtr(idxTxSigInfo); /* PRQA S 0317 */ /* MD_Com_0316_0317 */
      }
#  endif
      filterState = Com_Signal_UInt8_N_EvaluateFilter((Com_FilterInfo_UInt8_NIterType) idxFilterInfo, ((P2CONST(uint8, AUTOMATIC, AUTOMATIC)) newValuePtr), oldValuePtr, (PduLengthType) Com_GetByteLengthOfTxSigInfo(idxTxSigInfo), FALSE);    /* PRQA S 0316 */ /* MD_Com_0316_0317 */ /* SBSW_COM_COMST_PTR */
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(newValuePtr);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxTxSigInfo);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return filterState;
}       /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
#endif

#if (COM_FILTERINFO_UINT8 == STD_ON)
/**********************************************************************************************************************
  Com_Signal_UInt8_EvaluateFilter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_UInt8_EvaluateFilter(Com_FilterInfo_UInt8IterType idxFilterInfo, uint8 newValue, uint8 oldValue, boolean timeOutOccurred)    /* PRQA S 3206 */ /* MD_Com_3206 */
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (Com_GetFilterAlgoOfFilterInfo_UInt8(idxFilterInfo))
  {
# if (COM_EXISTS_MASKED_NEW_DIFFERS_X_FILTERALGOOFFILTERINFO_UINT8 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_X_FILTERALGOOFFILTERINFO_UINT8:
    {
      uint8 filterMask = Com_GetFilterMaskOfFilterInfo_UInt8(idxFilterInfo);
      uint8 filterX = Com_GetFilterXOfFilterInfo_UInt8(idxFilterInfo);
      if((uint8) (((uint8) newValue) & filterMask) != filterX)  /* PRQA S 4394 */ /* MD_Com_4394 */
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_UINT8 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_UINT8:
    {
#  if (COM_RXTOUTINFO == STD_ON)
      if(timeOutOccurred == FALSE)      /* COV_COM_MASKED_NEW_DIFFERS_MASKED_OLD_TX */ /* \trace SPEC-2736780 */
#  endif
      {
        uint8 filterMask = Com_GetFilterMaskOfFilterInfo_UInt8(idxFilterInfo);
        if((((uint8) newValue) & filterMask) != (((uint8) oldValue) & filterMask))      /* PRQA S 2985 */ /* MD_Com_2985_2986 */
        {
          filterState = TRUE;
        }
      }
#  if (COM_RXTOUTINFO == STD_ON)
      else
      {
        filterState = TRUE;
      }
#  endif
      break;
    }
# endif
# if (COM_EXISTS_MASKED_NEW_EQUALS_X_FILTERALGOOFFILTERINFO_UINT8 == STD_ON)
    case COM_MASKED_NEW_EQUALS_X_FILTERALGOOFFILTERINFO_UINT8:
    {
      uint8 filterMask = Com_GetFilterMaskOfFilterInfo_UInt8(idxFilterInfo);
      uint8 filterX = Com_GetFilterXOfFilterInfo_UInt8(idxFilterInfo);
      if((uint8) (((uint8) newValue) & filterMask) == filterX)  /* PRQA S 4394 */ /* MD_Com_4394 */
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_UINT8 == STD_ON)
    case COM_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_UINT8:
    {
      if(Com_Signal_UInt8_NewIsWithIn(idxFilterInfo, newValue) == FALSE)
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_UINT8 == STD_ON)
    case COM_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_UINT8:
    {
      filterState = Com_Signal_UInt8_NewIsWithIn(idxFilterInfo, newValue);
      break;
    }
# endif
# if (COM_EXISTS_NEVER_FILTERALGOOFFILTERINFO_UINT8 == STD_ON)
    case COM_NEVER_FILTERALGOOFFILTERINFO_UINT8:
    {
      filterState = FALSE;
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(newValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(oldValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(timeOutOccurred); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return filterState;
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if (COM_FILTERINFO_SINT8 == STD_ON)
/**********************************************************************************************************************
  Com_Signal_SInt8_EvaluateFilter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_SInt8_EvaluateFilter(Com_FilterInfo_SInt8IterType idxFilterInfo, sint8 newValue, sint8 oldValue, boolean timeOutOccurred)    /* PRQA S 3206 */ /* MD_Com_3206 */
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (Com_GetFilterAlgoOfFilterInfo_SInt8(idxFilterInfo))
  {
# if (COM_EXISTS_MASKED_NEW_DIFFERS_X_FILTERALGOOFFILTERINFO_SINT8 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_X_FILTERALGOOFFILTERINFO_SINT8:
    {
      uint8 filterMask = Com_GetFilterMaskOfFilterInfo_SInt8(idxFilterInfo);
      sint8 filterX = Com_GetFilterXOfFilterInfo_SInt8(idxFilterInfo);
      if((sint8) (((uint8) newValue) & filterMask) != filterX)  /* PRQA S 4394 */ /* MD_Com_4394 */
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_SINT8 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_SINT8:
    {
#  if (COM_RXTOUTINFO == STD_ON)
      if(timeOutOccurred == FALSE)      /* COV_COM_MASKED_NEW_DIFFERS_MASKED_OLD_TX */ /* \trace SPEC-2736780 */
#  endif
      {
        uint8 filterMask = Com_GetFilterMaskOfFilterInfo_SInt8(idxFilterInfo);
        if((((uint8) newValue) & filterMask) != (((uint8) oldValue) & filterMask))      /* PRQA S 2985 */ /* MD_Com_2985_2986 */
        {
          filterState = TRUE;
        }
      }
#  if (COM_RXTOUTINFO == STD_ON)
      else
      {
        filterState = TRUE;
      }
#  endif
      break;
    }
# endif
# if (COM_EXISTS_MASKED_NEW_EQUALS_X_FILTERALGOOFFILTERINFO_SINT8 == STD_ON)
    case COM_MASKED_NEW_EQUALS_X_FILTERALGOOFFILTERINFO_SINT8:
    {
      uint8 filterMask = Com_GetFilterMaskOfFilterInfo_SInt8(idxFilterInfo);
      sint8 filterX = Com_GetFilterXOfFilterInfo_SInt8(idxFilterInfo);
      if((sint8) (((uint8) newValue) & filterMask) == filterX)  /* PRQA S 4394 */ /* MD_Com_4394 */
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_SINT8 == STD_ON)
    case COM_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_SINT8:
    {
      if(Com_Signal_SInt8_NewIsWithIn(idxFilterInfo, newValue) == FALSE)
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_SINT8 == STD_ON)
    case COM_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_SINT8:
    {
      filterState = Com_Signal_SInt8_NewIsWithIn(idxFilterInfo, newValue);
      break;
    }
# endif
# if (COM_EXISTS_NEVER_FILTERALGOOFFILTERINFO_SINT8 == STD_ON)
    case COM_NEVER_FILTERALGOOFFILTERINFO_SINT8:
    {
      filterState = FALSE;
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(newValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(oldValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(timeOutOccurred); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return filterState;
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if (COM_FILTERINFO_UINT16 == STD_ON)
/**********************************************************************************************************************
  Com_Signal_UInt16_EvaluateFilter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_UInt16_EvaluateFilter(Com_FilterInfo_UInt16IterType idxFilterInfo, uint16 newValue, uint16 oldValue, boolean timeOutOccurred)        /* PRQA S 3206 */ /* MD_Com_3206 */
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (Com_GetFilterAlgoOfFilterInfo_UInt16(idxFilterInfo))
  {
# if (COM_EXISTS_MASKED_NEW_DIFFERS_X_FILTERALGOOFFILTERINFO_UINT16 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_X_FILTERALGOOFFILTERINFO_UINT16:
    {
      uint16 filterMask = Com_GetFilterMaskOfFilterInfo_UInt16(idxFilterInfo);
      uint16 filterX = Com_GetFilterXOfFilterInfo_UInt16(idxFilterInfo);
      if((uint16) (((uint16) newValue) & filterMask) != filterX)        /* PRQA S 4394 */ /* MD_Com_4394 */
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_UINT16 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_UINT16:
    {
#  if (COM_RXTOUTINFO == STD_ON)
      if(timeOutOccurred == FALSE)      /* COV_COM_MASKED_NEW_DIFFERS_MASKED_OLD_TX */ /* \trace SPEC-2736780 */
#  endif
      {
        uint16 filterMask = Com_GetFilterMaskOfFilterInfo_UInt16(idxFilterInfo);
        if((((uint16) newValue) & filterMask) != (((uint16) oldValue) & filterMask))    /* PRQA S 2985 */ /* MD_Com_2985_2986 */
        {
          filterState = TRUE;
        }
      }
#  if (COM_RXTOUTINFO == STD_ON)
      else
      {
        filterState = TRUE;
      }
#  endif
      break;
    }
# endif
# if (COM_EXISTS_MASKED_NEW_EQUALS_X_FILTERALGOOFFILTERINFO_UINT16 == STD_ON)
    case COM_MASKED_NEW_EQUALS_X_FILTERALGOOFFILTERINFO_UINT16:
    {
      uint16 filterMask = Com_GetFilterMaskOfFilterInfo_UInt16(idxFilterInfo);
      uint16 filterX = Com_GetFilterXOfFilterInfo_UInt16(idxFilterInfo);
      if((uint16) (((uint16) newValue) & filterMask) == filterX)        /* PRQA S 4394 */ /* MD_Com_4394 */
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_UINT16 == STD_ON)
    case COM_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_UINT16:
    {
      if(Com_Signal_UInt16_NewIsWithIn(idxFilterInfo, newValue) == FALSE)
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_UINT16 == STD_ON)
    case COM_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_UINT16:
    {
      filterState = Com_Signal_UInt16_NewIsWithIn(idxFilterInfo, newValue);
      break;
    }
# endif
# if (COM_EXISTS_NEVER_FILTERALGOOFFILTERINFO_UINT16 == STD_ON)
    case COM_NEVER_FILTERALGOOFFILTERINFO_UINT16:
    {
      filterState = FALSE;
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(newValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(oldValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(timeOutOccurred); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return filterState;
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if (COM_FILTERINFO_SINT16 == STD_ON)
/**********************************************************************************************************************
  Com_Signal_SInt16_EvaluateFilter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_SInt16_EvaluateFilter(Com_FilterInfo_SInt16IterType idxFilterInfo, sint16 newValue, sint16 oldValue, boolean timeOutOccurred)        /* PRQA S 3206 */ /* MD_Com_3206 */
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (Com_GetFilterAlgoOfFilterInfo_SInt16(idxFilterInfo))
  {
# if (COM_EXISTS_MASKED_NEW_DIFFERS_X_FILTERALGOOFFILTERINFO_SINT16 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_X_FILTERALGOOFFILTERINFO_SINT16:
    {
      uint16 filterMask = Com_GetFilterMaskOfFilterInfo_SInt16(idxFilterInfo);
      sint16 filterX = Com_GetFilterXOfFilterInfo_SInt16(idxFilterInfo);
      if((sint16) (((uint16) newValue) & filterMask) != filterX)        /* PRQA S 4394 */ /* MD_Com_4394 */
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_SINT16 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_SINT16:
    {
#  if (COM_RXTOUTINFO == STD_ON)
      if(timeOutOccurred == FALSE)      /* COV_COM_MASKED_NEW_DIFFERS_MASKED_OLD_TX */ /* \trace SPEC-2736780 */
#  endif
      {
        uint16 filterMask = Com_GetFilterMaskOfFilterInfo_SInt16(idxFilterInfo);
        if((((uint16) newValue) & filterMask) != (((uint16) oldValue) & filterMask))    /* PRQA S 2985 */ /* MD_Com_2985_2986 */
        {
          filterState = TRUE;
        }
      }
#  if (COM_RXTOUTINFO == STD_ON)
      else
      {
        filterState = TRUE;
      }
#  endif
      break;
    }
# endif
# if (COM_EXISTS_MASKED_NEW_EQUALS_X_FILTERALGOOFFILTERINFO_SINT16 == STD_ON)
    case COM_MASKED_NEW_EQUALS_X_FILTERALGOOFFILTERINFO_SINT16:
    {
      uint16 filterMask = Com_GetFilterMaskOfFilterInfo_SInt16(idxFilterInfo);
      sint16 filterX = Com_GetFilterXOfFilterInfo_SInt16(idxFilterInfo);
      if((sint16) (((uint16) newValue) & filterMask) == filterX)        /* PRQA S 4394 */ /* MD_Com_4394 */
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_SINT16 == STD_ON)
    case COM_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_SINT16:
    {
      if(Com_Signal_SInt16_NewIsWithIn(idxFilterInfo, newValue) == FALSE)
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_SINT16 == STD_ON)
    case COM_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_SINT16:
    {
      filterState = Com_Signal_SInt16_NewIsWithIn(idxFilterInfo, newValue);
      break;
    }
# endif
# if (COM_EXISTS_NEVER_FILTERALGOOFFILTERINFO_SINT16 == STD_ON)
    case COM_NEVER_FILTERALGOOFFILTERINFO_SINT16:
    {
      filterState = FALSE;
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(newValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(oldValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(timeOutOccurred); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return filterState;
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if (COM_FILTERINFO_UINT32 == STD_ON)
/**********************************************************************************************************************
  Com_Signal_UInt32_EvaluateFilter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_UInt32_EvaluateFilter(Com_FilterInfo_UInt32IterType idxFilterInfo, uint32 newValue, uint32 oldValue, boolean timeOutOccurred)        /* PRQA S 3206 */ /* MD_Com_3206 */
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (Com_GetFilterAlgoOfFilterInfo_UInt32(idxFilterInfo))
  {
# if (COM_EXISTS_MASKED_NEW_DIFFERS_X_FILTERALGOOFFILTERINFO_UINT32 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_X_FILTERALGOOFFILTERINFO_UINT32:
    {
      uint32 filterMask = Com_GetFilterMaskOfFilterInfo_UInt32(idxFilterInfo);
      uint32 filterX = Com_GetFilterXOfFilterInfo_UInt32(idxFilterInfo);
      if((uint32) (((uint32) newValue) & filterMask) != filterX)        /* PRQA S 4394 */ /* MD_Com_4394 */
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_UINT32 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_UINT32:
    {
#  if (COM_RXTOUTINFO == STD_ON)
      if(timeOutOccurred == FALSE)      /* COV_COM_MASKED_NEW_DIFFERS_MASKED_OLD_TX */ /* \trace SPEC-2736780 */
#  endif
      {
        uint32 filterMask = Com_GetFilterMaskOfFilterInfo_UInt32(idxFilterInfo);
        if((((uint32) newValue) & filterMask) != (((uint32) oldValue) & filterMask))    /* PRQA S 2985 */ /* MD_Com_2985_2986 */
        {
          filterState = TRUE;
        }
      }
#  if (COM_RXTOUTINFO == STD_ON)
      else
      {
        filterState = TRUE;
      }
#  endif
      break;
    }
# endif
# if (COM_EXISTS_MASKED_NEW_EQUALS_X_FILTERALGOOFFILTERINFO_UINT32 == STD_ON)
    case COM_MASKED_NEW_EQUALS_X_FILTERALGOOFFILTERINFO_UINT32:
    {
      uint32 filterMask = Com_GetFilterMaskOfFilterInfo_UInt32(idxFilterInfo);
      uint32 filterX = Com_GetFilterXOfFilterInfo_UInt32(idxFilterInfo);
      if((uint32) (((uint32) newValue) & filterMask) == filterX)        /* PRQA S 4394 */ /* MD_Com_4394 */
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_UINT32 == STD_ON)
    case COM_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_UINT32:
    {
      if(Com_Signal_UInt32_NewIsWithIn(idxFilterInfo, newValue) == FALSE)
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_UINT32 == STD_ON)
    case COM_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_UINT32:
    {
      filterState = Com_Signal_UInt32_NewIsWithIn(idxFilterInfo, newValue);
      break;
    }
# endif
# if (COM_EXISTS_NEVER_FILTERALGOOFFILTERINFO_UINT32 == STD_ON)
    case COM_NEVER_FILTERALGOOFFILTERINFO_UINT32:
    {
      filterState = FALSE;
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(newValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(oldValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(timeOutOccurred); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return filterState;
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if (COM_FILTERINFO_SINT32 == STD_ON)
/**********************************************************************************************************************
  Com_Signal_SInt32_EvaluateFilter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_SInt32_EvaluateFilter(Com_FilterInfo_SInt32IterType idxFilterInfo, sint32 newValue, sint32 oldValue, boolean timeOutOccurred)        /* PRQA S 3206 */ /* MD_Com_3206 */
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (Com_GetFilterAlgoOfFilterInfo_SInt32(idxFilterInfo))
  {
# if (COM_EXISTS_MASKED_NEW_DIFFERS_X_FILTERALGOOFFILTERINFO_SINT32 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_X_FILTERALGOOFFILTERINFO_SINT32:
    {
      uint32 filterMask = Com_GetFilterMaskOfFilterInfo_SInt32(idxFilterInfo);
      sint32 filterX = Com_GetFilterXOfFilterInfo_SInt32(idxFilterInfo);
      if((sint32) (((uint32) newValue) & filterMask) != filterX)        /* PRQA S 4394 */ /* MD_Com_4394 */
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_SINT32 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_SINT32:
    {
#  if (COM_RXTOUTINFO == STD_ON)
      if(timeOutOccurred == FALSE)      /* COV_COM_MASKED_NEW_DIFFERS_MASKED_OLD_TX */ /* \trace SPEC-2736780 */
#  endif
      {
        uint32 filterMask = Com_GetFilterMaskOfFilterInfo_SInt32(idxFilterInfo);
        if((((uint32) newValue) & filterMask) != (((uint32) oldValue) & filterMask))    /* PRQA S 2985 */ /* MD_Com_2985_2986 */
        {
          filterState = TRUE;
        }
      }
#  if (COM_RXTOUTINFO == STD_ON)
      else
      {
        filterState = TRUE;
      }
#  endif
      break;
    }
# endif
# if (COM_EXISTS_MASKED_NEW_EQUALS_X_FILTERALGOOFFILTERINFO_SINT32 == STD_ON)
    case COM_MASKED_NEW_EQUALS_X_FILTERALGOOFFILTERINFO_SINT32:
    {
      uint32 filterMask = Com_GetFilterMaskOfFilterInfo_SInt32(idxFilterInfo);
      sint32 filterX = Com_GetFilterXOfFilterInfo_SInt32(idxFilterInfo);
      if((sint32) (((uint32) newValue) & filterMask) == filterX)        /* PRQA S 4394 */ /* MD_Com_4394 */
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_SINT32 == STD_ON)
    case COM_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_SINT32:
    {
      if(Com_Signal_SInt32_NewIsWithIn(idxFilterInfo, newValue) == FALSE)
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_SINT32 == STD_ON)
    case COM_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_SINT32:
    {
      filterState = Com_Signal_SInt32_NewIsWithIn(idxFilterInfo, newValue);
      break;
    }
# endif
# if (COM_EXISTS_NEVER_FILTERALGOOFFILTERINFO_SINT32 == STD_ON)
    case COM_NEVER_FILTERALGOOFFILTERINFO_SINT32:
    {
      filterState = FALSE;
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(newValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(oldValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(timeOutOccurred); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return filterState;
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if (COM_FILTERINFO_UINT64 == STD_ON)
/**********************************************************************************************************************
  Com_Signal_UInt64_EvaluateFilter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_UInt64_EvaluateFilter(Com_FilterInfo_UInt64IterType idxFilterInfo, uint64 newValue, uint64 oldValue, boolean timeOutOccurred)        /* PRQA S 3206 */ /* MD_Com_3206 */
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (Com_GetFilterAlgoOfFilterInfo_UInt64(idxFilterInfo))
  {
# if (COM_EXISTS_MASKED_NEW_DIFFERS_X_FILTERALGOOFFILTERINFO_UINT64 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_X_FILTERALGOOFFILTERINFO_UINT64:
    {
      uint64 filterMask = Com_GetFilterMaskOfFilterInfo_UInt64(idxFilterInfo);
      uint64 filterX = Com_GetFilterXOfFilterInfo_UInt64(idxFilterInfo);
      if((uint64) (((uint64) newValue) & filterMask) != filterX)        /* PRQA S 4394 */ /* MD_Com_4394 */
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_UINT64 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_UINT64:
    {
#  if (COM_RXTOUTINFO == STD_ON)
      if(timeOutOccurred == FALSE)      /* COV_COM_MASKED_NEW_DIFFERS_MASKED_OLD_TX */ /* \trace SPEC-2736780 */
#  endif
      {
        uint64 filterMask = Com_GetFilterMaskOfFilterInfo_UInt64(idxFilterInfo);
        if((((uint64) newValue) & filterMask) != (((uint64) oldValue) & filterMask))    /* PRQA S 2985 */ /* MD_Com_2985_2986 */
        {
          filterState = TRUE;
        }
      }
#  if (COM_RXTOUTINFO == STD_ON)
      else
      {
        filterState = TRUE;
      }
#  endif
      break;
    }
# endif
# if (COM_EXISTS_MASKED_NEW_EQUALS_X_FILTERALGOOFFILTERINFO_UINT64 == STD_ON)
    case COM_MASKED_NEW_EQUALS_X_FILTERALGOOFFILTERINFO_UINT64:
    {
      uint64 filterMask = Com_GetFilterMaskOfFilterInfo_UInt64(idxFilterInfo);
      uint64 filterX = Com_GetFilterXOfFilterInfo_UInt64(idxFilterInfo);
      if((uint64) (((uint64) newValue) & filterMask) == filterX)        /* PRQA S 4394 */ /* MD_Com_4394 */
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_UINT64 == STD_ON)
    case COM_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_UINT64:
    {
      if(Com_Signal_UInt64_NewIsWithIn(idxFilterInfo, newValue) == FALSE)
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_UINT64 == STD_ON)
    case COM_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_UINT64:
    {
      filterState = Com_Signal_UInt64_NewIsWithIn(idxFilterInfo, newValue);
      break;
    }
# endif
# if (COM_EXISTS_NEVER_FILTERALGOOFFILTERINFO_UINT64 == STD_ON)
    case COM_NEVER_FILTERALGOOFFILTERINFO_UINT64:
    {
      filterState = FALSE;
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(newValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(oldValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(timeOutOccurred); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return filterState;
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if (COM_FILTERINFO_SINT64 == STD_ON)
/**********************************************************************************************************************
  Com_Signal_SInt64_EvaluateFilter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_SInt64_EvaluateFilter(Com_FilterInfo_SInt64IterType idxFilterInfo, sint64 newValue, sint64 oldValue, boolean timeOutOccurred)        /* PRQA S 3206 */ /* MD_Com_3206 */
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (Com_GetFilterAlgoOfFilterInfo_SInt64(idxFilterInfo))
  {
# if (COM_EXISTS_MASKED_NEW_DIFFERS_X_FILTERALGOOFFILTERINFO_SINT64 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_X_FILTERALGOOFFILTERINFO_SINT64:
    {
      uint64 filterMask = Com_GetFilterMaskOfFilterInfo_SInt64(idxFilterInfo);
      sint64 filterX = Com_GetFilterXOfFilterInfo_SInt64(idxFilterInfo);
      if((sint64) (((uint64) newValue) & filterMask) != filterX)        /* PRQA S 4394 */ /* MD_Com_4394 */
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_SINT64 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_SINT64:
    {
#  if (COM_RXTOUTINFO == STD_ON)
      if(timeOutOccurred == FALSE)      /* COV_COM_MASKED_NEW_DIFFERS_MASKED_OLD_TX */ /* \trace SPEC-2736780 */
#  endif
      {
        uint64 filterMask = Com_GetFilterMaskOfFilterInfo_SInt64(idxFilterInfo);
        if((((uint64) newValue) & filterMask) != (((uint64) oldValue) & filterMask))    /* PRQA S 2985 */ /* MD_Com_2985_2986 */
        {
          filterState = TRUE;
        }
      }
#  if (COM_RXTOUTINFO == STD_ON)
      else
      {
        filterState = TRUE;
      }
#  endif
      break;
    }
# endif
# if (COM_EXISTS_MASKED_NEW_EQUALS_X_FILTERALGOOFFILTERINFO_SINT64 == STD_ON)
    case COM_MASKED_NEW_EQUALS_X_FILTERALGOOFFILTERINFO_SINT64:
    {
      uint64 filterMask = Com_GetFilterMaskOfFilterInfo_SInt64(idxFilterInfo);
      sint64 filterX = Com_GetFilterXOfFilterInfo_SInt64(idxFilterInfo);
      if((sint64) (((uint64) newValue) & filterMask) == filterX)        /* PRQA S 4394 */ /* MD_Com_4394 */
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_SINT64 == STD_ON)
    case COM_NEW_IS_OUTSIDE_FILTERALGOOFFILTERINFO_SINT64:
    {
      if(Com_Signal_SInt64_NewIsWithIn(idxFilterInfo, newValue) == FALSE)
      {
        filterState = TRUE;
      }
      break;
    }
# endif
# if (COM_EXISTS_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_SINT64 == STD_ON)
    case COM_NEW_IS_WITHIN_FILTERALGOOFFILTERINFO_SINT64:
    {
      filterState = Com_Signal_SInt64_NewIsWithIn(idxFilterInfo, newValue);
      break;
    }
# endif
# if (COM_EXISTS_NEVER_FILTERALGOOFFILTERINFO_SINT64 == STD_ON)
    case COM_NEVER_FILTERALGOOFFILTERINFO_SINT64:
    {
      filterState = FALSE;
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(newValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(oldValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(timeOutOccurred); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return filterState;
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if (COM_FILTERINFO_FLOAT32 == STD_ON)
/**********************************************************************************************************************
  Com_Signal_Float32_EvaluateFilter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_Float32_EvaluateFilter(Com_FilterInfo_Float32IterType idxFilterInfo, float32 newValue, float32 oldValue, boolean timeOutOccurred)    /* PRQA S 3206 */ /* MD_Com_3206 */
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (Com_GetFilterAlgoOfFilterInfo_Float32(idxFilterInfo))
  {
# if (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_FLOAT32 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_FLOAT32:
    {
#  if (COM_RXTOUTINFO == STD_ON)
      if(timeOutOccurred == FALSE)      /* COV_COM_MASKED_NEW_DIFFERS_MASKED_OLD_TX */ /* \trace SPEC-2736780 */
#  endif
      {
        if(!Com_CompareFloat32Values(newValue, oldValue))
        {
          filterState = TRUE;
        }
      }
#  if (COM_RXTOUTINFO == STD_ON)
      else
      {
        filterState = TRUE;
      }
#  endif
      break;
    }
# endif
# if (COM_EXISTS_NEVER_FILTERALGOOFFILTERINFO_FLOAT32 == STD_ON)
    case COM_NEVER_FILTERALGOOFFILTERINFO_FLOAT32:
    {
      filterState = FALSE;
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(newValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(oldValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(timeOutOccurred); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return filterState;
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if (COM_FILTERINFO_FLOAT64 == STD_ON)
/**********************************************************************************************************************
  Com_Signal_Float64_EvaluateFilter
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_Float64_EvaluateFilter(Com_FilterInfo_Float64IterType idxFilterInfo, float64 newValue, float64 oldValue, boolean timeOutOccurred)    /* PRQA S 3206 */ /* MD_Com_3206 */
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (Com_GetFilterAlgoOfFilterInfo_Float64(idxFilterInfo))
  {
# if (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_FLOAT64 == STD_ON)
    case COM_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_FLOAT64:
    {
#  if (COM_RXTOUTINFO == STD_ON)
      if(timeOutOccurred == FALSE)      /* COV_COM_MASKED_NEW_DIFFERS_MASKED_OLD_TX */ /* \trace SPEC-2736780 */
#  endif
      {
        if(!Com_CompareFloat64Values(newValue, oldValue))
        {
          filterState = TRUE;
        }
      }
#  if (COM_RXTOUTINFO == STD_ON)
      else
      {
        filterState = TRUE;
      }
#  endif
      break;
    }
# endif
# if (COM_EXISTS_NEVER_FILTERALGOOFFILTERINFO_FLOAT64 == STD_ON)
    case COM_NEVER_FILTERALGOOFFILTERINFO_FLOAT64:
    {
      filterState = FALSE;
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(newValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(oldValue);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(timeOutOccurred); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return filterState;
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#if (COM_FILTERINFO_UINT8_N == STD_ON)
/**********************************************************************************************************************
  Com_Signal_UIn8_N_NewIsWithIn
**********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_UInt8_N_EvaluateFilter(Com_FilterInfo_UInt8_NIterType idxFilterInfo, P2CONST(uint8, AUTOMATIC, AUTOMATIC) newValuePtr, P2CONST(uint8, AUTOMATIC, AUTOMATIC) oldValuePtr, PduLengthType length, boolean timeOutOccurred)      /* PRQA S 3206 */ /* MD_Com_3206 */
{
  boolean filterState = FALSE;  /* PRQA S 2981 */ /* MD_MSR_RetVal */

  switch (Com_GetFilterAlgoOfFilterInfo_UInt8_N(idxFilterInfo))
  {
      /* Currently FILTERINFO_UINT8_N only exists when TriggeredOnChange or MASKED_NEW_DIFFERS_MASKED_OLD */
# if (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_UINT8_N == STD_ON)        /* COV_COM_VAR_DEPENDENT_SWITCH */
    case COM_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_UINT8_N:
    {
#  if (COM_RXTOUTINFO == STD_ON)
      if(timeOutOccurred == FALSE)
#  endif
      {
        PduLengthType i = 0;
        filterState = FALSE;
        for(; i < length; i++)
        {
          if(((P2CONST(uint8, AUTOMATIC, AUTOMATIC)) newValuePtr)[i] != (((P2CONST(uint8, AUTOMATIC, AUTOMATIC)) oldValuePtr)[i]))      /* PRQA S 2822 */ /* MD_Com_oldValuePtrNoNULLPTR */
          {
            filterState = TRUE;
            break;
          }
        }
      }
#  if (COM_RXTOUTINFO == STD_ON)
      else
      {
        filterState = TRUE;
      }
#  endif
      break;
    }
# endif
    default:   /* COV_COM_MISRA */
      break;
  }

  COM_DUMMY_STATEMENT(timeOutOccurred); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  COM_DUMMY_STATEMENT(idxFilterInfo);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return filterState;
}       /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif

#define COM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 **********************************************************************************************************************/
/* *INDENT-OFF* */
/* Justifications for module-specific MISRA deviations:
   MD_Com_0314_0315: Misra Dir 1.1
     Reason:     A void pointer is used because it depends on the configuration of which type the pointer is. It is easier to use a void pointer insead of different functions for different pointer types.
     Risk:       No risk, because the underlying pointer type is known via the configuration.
     Prevention: No prevention necessary.

   MD_Com_4394:  Misra Rule 10.8
     Reason:     The composite expression has to be cast as a whole because of the shift or bitwise operation. Shift and bitwise operations should only be performed with esentially unsigned types. The cast is necessary, because the result of the shift or bitwise operation is signed.
     Risk:       No risk
     Prevention: No prevention necessary

  MD_Com_oldValuePtrNoNULLPTR: Misra Dir 4.1
     Reason:     The oldValuePtr can never be a NULL_PTR because of the Control Flow. The oldValuePtr is only used if the Filter Algorithm is MASED_NEW_DIFFERS_MASKED_OLD and in this case a FilterInitValue and thus the oldValuePtr is always present.
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
 *  END OF FILE: Com_SignalFilterHdlr.c
 *********************************************************************************************************************/
