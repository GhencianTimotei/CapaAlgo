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
/*!        \file  Com_SignalFilterHdlr.h
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/
#if !defined (COM_SIGNALFILTERHDLR_H)
# define COM_SIGNALFILTERHDLR_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "Com_Lcfg.h"

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES (Com)
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

# define COM_START_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

# if (((COM_EXISTS_FLOAT32_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)) || ((COM_EXISTS_FLOAT32_APPLTYPEOFTXSIGINFO == STD_ON) && (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_FLOAT32 == STD_ON)))
/**********************************************************************************************************************
  Com_CompareFloat32Values
**********************************************************************************************************************/
/*! \brief        This function compares two float32 values with each other.
    \details      -
    \pre          -
    \param[in]    firstValue                  first float32 value.
    \param[in]    scndValue                   second float32 value.
    \return       TRUE                        if difference is smaller than COM_FLT_EPSILON.
                  FALSE                       Otherwise.
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_CompareFloat32Values(float32 firstValue, float32 scndValue);
# endif

# if (((COM_EXISTS_FLOAT64_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON)) || ((COM_EXISTS_FLOAT64_APPLTYPEOFTXSIGINFO == STD_ON) && (COM_EXISTS_MASKED_NEW_DIFFERS_MASKED_OLD_FILTERALGOOFFILTERINFO_FLOAT64 == STD_ON)))
/**********************************************************************************************************************
  Com_CompareFloat64Values
**********************************************************************************************************************/
/*! \brief        This function compares two float64 values with each other.
    \details      -
    \pre          -
    \param[in]    firstValue                  first float64 value.
    \param[in]    scndValue                   second float64 value.
    \return       TRUE                        if difference is smaller than COM_FLT_EPSILON.
                  FALSE                       Otherwise.
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_CompareFloat64Values(float64 firstValue, float64 scndValue);
# endif

# if ((COM_TXFILTERINITVALUEARRAYBASEDFILTERINITVALUEUSEDOFTXSIGINFO == STD_ON) || (COM_FILTERINITVALUEIDXOFTXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_SetTxFilterOldValueX
**********************************************************************************************************************/
/*! \brief        This method sets the Com_TxFilterOldValueX
    \details      -
    \pre          -
    \param[in]    idxTxSigInfo      Index of Tx Signal Info
    \param[in]    SignalDataPtr     Reference to the signal data to be transmitted.
    \param[in]    Length        Length of the dynamic length signal.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_SetTxFilterOldValueX(Com_TxSigInfoIterType idxTxSigInfo, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr, uint16 Length);
# endif

# if ((COM_FILTERINFOUSEDOFTXSIGINFO == STD_ON) || (COM_ONCHANGEUSEDOFTXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_TxSignal_EvaluateFilter
**********************************************************************************************************************/
/*! \brief        This function evaluates the state of the signal and group signal filters.
    \details      -
    \pre          -
    \param[in]    idxTxSigInfo        Index of TxSigInfo
    \param[in]    idxFilterInfo       Index of filter information table
    \param[in]    newValuePtr         Pointer to the memory where the new signal value is located
    \return       boolean             TRUE, if filter condition is passed, FALSE otherwise.
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_TxSignal_EvaluateFilter(Com_TxSigInfoIterType idxTxSigInfo, uint32 idxFilterInfo, P2CONST(void, AUTOMATIC, AUTOMATIC) newValuePtr);
# endif

# if (COM_FILTERINFO_UINT8 == STD_ON)
/**********************************************************************************************************************
*  Com_Signal_UInt8_EvaluateFilter
*********************************************************************************************************************/
/*!
    \brief        This method evaluated the the filter state appl type specific
    \details      -
    \pre          -
    \param[in]    idxFilterInfo    index of related filter info
    \param[in]    newValue         new value
    \param[in]    oldValue         old value
    \param[in]    timeOutOccurred  indicates whether a timeout occurred
    \trace        SPEC-2736780
    \return       boolean
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
*********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_UInt8_EvaluateFilter(Com_FilterInfo_UInt8IterType idxFilterInfo, uint8 newValue, uint8 oldValue, boolean timeOutOccurred);
# endif

# if (COM_FILTERINFO_SINT8 == STD_ON)
/**********************************************************************************************************************
*  Com_Signal_SInt8_EvaluateFilter
*********************************************************************************************************************/
/*!
    \brief        This method evaluated the the filter state appl type specific
    \details      -
    \pre          -
    \param[in]    idxFilterInfo    index of related filter info
    \param[in]    newValue         new value
    \param[in]    oldValue         old value
    \param[in]    timeOutOccurred  indicates whether a timeout occurred
    \trace        SPEC-2736780
    \return       boolean
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
*********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_SInt8_EvaluateFilter(Com_FilterInfo_SInt8IterType idxFilterInfo, sint8 newValue, sint8 oldValue, boolean timeOutOccurred);
# endif

# if (COM_FILTERINFO_UINT16 == STD_ON)
/**********************************************************************************************************************
*  Com_Signal_UInt16_EvaluateFilter
*********************************************************************************************************************/
/*!
    \brief        This method evaluated the the filter state appl type specific
    \details      -
    \pre          -
    \param[in]    idxFilterInfo    index of related filter info
    \param[in]    newValue         new value
    \param[in]    oldValue         old value
    \param[in]    timeOutOccurred  indicates whether a timeout occurred
    \trace        SPEC-2736780
    \return       boolean
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
*********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_UInt16_EvaluateFilter(Com_FilterInfo_UInt16IterType idxFilterInfo, uint16 newValue, uint16 oldValue, boolean timeOutOccurred);
# endif

# if (COM_FILTERINFO_SINT16 == STD_ON)
/**********************************************************************************************************************
*  Com_Signal_SInt16_EvaluateFilter
*********************************************************************************************************************/
/*!
    \brief        This method evaluated the the filter state appl type specific
    \details      -
    \pre          -
    \param[in]    idxFilterInfo    index of related filter info
    \param[in]    newValue         new value
    \param[in]    oldValue         old value
    \param[in]    timeOutOccurred  indicates whether a timeout occurred
    \trace        SPEC-2736780
    \return       boolean
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
*********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_SInt16_EvaluateFilter(Com_FilterInfo_SInt16IterType idxFilterInfo, sint16 newValue, sint16 oldValue, boolean timeOutOccurred);
# endif

# if (COM_FILTERINFO_UINT32 == STD_ON)
/**********************************************************************************************************************
*  Com_Signal_UInt32_EvaluateFilter
*********************************************************************************************************************/
/*!
    \brief        This method evaluated the the filter state appl type specific
    \details      -
    \pre          -
    \param[in]    idxFilterInfo    index of related filter info
    \param[in]    newValue         new value
    \param[in]    oldValue         old value
    \param[in]    timeOutOccurred  indicates whether a timeout occurred
    \trace        SPEC-2736780
    \return       boolean
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
*********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_UInt32_EvaluateFilter(Com_FilterInfo_UInt32IterType idxFilterInfo, uint32 newValue, uint32 oldValue, boolean timeOutOccurred);
# endif

# if (COM_FILTERINFO_SINT32 == STD_ON)
/**********************************************************************************************************************
*  Com_Signal_SInt32_EvaluateFilter
*********************************************************************************************************************/
/*!
    \brief        This method evaluated the the filter state appl type specific
    \details      -
    \pre          -
    \param[in]    idxFilterInfo    index of related filter info
    \param[in]    newValue         new value
    \param[in]    oldValue         old value
    \param[in]    timeOutOccurred  indicates whether a timeout occurred
    \trace        SPEC-2736780
    \return       boolean
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
*********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_SInt32_EvaluateFilter(Com_FilterInfo_SInt32IterType idxFilterInfo, sint32 newValue, sint32 oldValue, boolean timeOutOccurred);
# endif

# if (COM_FILTERINFO_UINT64 == STD_ON)
/**********************************************************************************************************************
*  Com_Signal_UInt64_EvaluateFilter
*********************************************************************************************************************/
/*!
    \brief        This method evaluated the the filter state appl type specific
    \details      -
    \pre          -
    \param[in]    idxFilterInfo    index of related filter info
    \param[in]    newValue         new value
    \param[in]    oldValue         old value
    \param[in]    timeOutOccurred  indicates whether a timeout occurred
    \trace        SPEC-2736780
    \return       boolean
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
*********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_UInt64_EvaluateFilter(Com_FilterInfo_UInt64IterType idxFilterInfo, uint64 newValue, uint64 oldValue, boolean timeOutOccurred);
# endif

# if (COM_FILTERINFO_SINT64 == STD_ON)
/**********************************************************************************************************************
*  Com_Signal_SInt64_EvaluateFilter
*********************************************************************************************************************/
/*!
    \brief        This method evaluated the the filter state appl type specific
    \details      -
    \pre          -
    \param[in]    idxFilterInfo    index of related filter info
    \param[in]    newValue         new value
    \param[in]    oldValue         old value
    \param[in]    timeOutOccurred  indicates whether a timeout occurred
    \trace        SPEC-2736780
    \return       boolean
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
*********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_SInt64_EvaluateFilter(Com_FilterInfo_SInt64IterType idxFilterInfo, sint64 newValue, sint64 oldValue, boolean timeOutOccurred);
# endif

# if (COM_FILTERINFO_FLOAT32 == STD_ON)
/**********************************************************************************************************************
*  Com_Signal_Float32_EvaluateFilter
*********************************************************************************************************************/
/*!
    \brief        This method evaluated the the filter state appl type specific
    \details      -
    \pre          -
    \param[in]    idxFilterInfo    index of related filter info
    \param[in]    newValue         new value
    \param[in]    oldValue         old value
    \param[in]    timeOutOccurred  indicates whether a timeout occurred
    \trace        SPEC-2736780
    \return       boolean
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
*********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_Float32_EvaluateFilter(Com_FilterInfo_Float32IterType idxFilterInfo, float32 newValue, float32 oldValue, boolean timeOutOccurred);
# endif

# if (COM_FILTERINFO_FLOAT64 == STD_ON)
/**********************************************************************************************************************
*  Com_Signal_Float64_EvaluateFilter
*********************************************************************************************************************/
/*!
    \brief        This method evaluated the the filter state appl type specific
    \details      -
    \pre          -
    \param[in]    idxFilterInfo    index of related filter info
    \param[in]    newValue         new value
    \param[in]    oldValue         old value
    \param[in]    timeOutOccurred  indicates whether a timeout occurred
    \trace        SPEC-2736780
    \return       boolean
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
*********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_Float64_EvaluateFilter(Com_FilterInfo_Float64IterType idxFilterInfo, float64 newValue, float64 oldValue, boolean timeOutOccurred);
# endif


# if (COM_FILTERINFO_UINT8_N == STD_ON)
/**********************************************************************************************************************
*  Com_Signal_UInt8_N_EvaluateFilter
*********************************************************************************************************************/
/*! \brief        This method evaluated the the filter state appl type specific
    \details      -
    \pre          -
    \param[in]    idxFilterInfo    index of related filter info
    \param[in]    newValuePtr      pointer to new value
    \param[in]    oldValuePtr      pointer old value
    \param[in]    length           number bytes to be evaluated.
    \param[in]    timeOutOccurred  indicates whether a timeout occurred
    \return       boolean
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
*********************************************************************************************************************/
FUNC(boolean, COM_CODE) Com_Signal_UInt8_N_EvaluateFilter(Com_FilterInfo_UInt8_NIterType idxFilterInfo, P2CONST(uint8, AUTOMATIC, AUTOMATIC) newValuePtr,
                                                          P2CONST(uint8, AUTOMATIC, AUTOMATIC) oldValuePtr, PduLengthType length, boolean timeOutOccurred);
# endif

# define COM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* COM_SIGNALFILTERHDLR_H */
/**********************************************************************************************************************
  END OF FILE: Com_SignalFilterHdlr.h
**********************************************************************************************************************/
