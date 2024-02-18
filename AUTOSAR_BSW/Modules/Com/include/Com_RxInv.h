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
/*!        \file  Com_RxInv.h
 *        \brief  MICROSAR Communication source file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/
#if !defined (COM_RXINV_H)
# define COM_RXINV_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "Com.h"
# include "Com_RxProcessing.h"
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

# if (((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) || (COM_CONSTVALUEARRAYBASEDINVVALUEUSEDOFRXACCESSINFO == STD_ON)) && (COM_RXSIGINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_PerformInvalidAction
**********************************************************************************************************************/
/*! \brief            This function performs the configured invalid action (replace/notify)
    \details          -
    \pre              -
    \param[in]        idxRxSigInfo - Index of RxSigInfo
    \param[in,out]    fctPtrCacheStrctPtr - Pointer to function pointer struct containing all cache managment attributes
                                    (Cache location, size, index).
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxInv_Sig_PerformInvalidAction(Com_RxSigInfoIterType idxRxSigInfo, P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) fctPtrCacheStrctPtr);
# endif

# if (COM_INVEVENTOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxInv_SigGrp
**********************************************************************************************************************/
/*! \brief             This function evaluates whether any new value of the a ComGroupSignals is an invalid value
    \details           -
    \pre               -
    \param[in]         idxRxSigGrpInfo index of Rx SigGrpInfo
    \param[in,out]     fctPtrCacheStrctPtr  pointer containing all function pointer cache informations (location, size index)
    \param[in]         sduLength Length of Sdu
    \return            Com_RxSigProcessState
    \context           TASK|ISR2
    \synchronous       TRUE
    \reentrant         TRUE, for different handles
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_SigGrp(Com_RxSigGrpInfoIterType idxRxSigGrpInfo, P2VAR(FctPtrCacheStrct, AUTOMATIC, COM_APPL_DATA) fctPtrCacheStrctPtr, PduLengthType sduLength);
# endif

# if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_UINT8_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_UInt8_EvaluateInvalidValue
**********************************************************************************************************************/
/*!
 * \brief       Checks if the received value is an invalid value
 * \details     -
 * \pre         -
 * \param[in]   idxRxAccessInfo   index of Rx SigInfo
 * \param[in]   tmpNewValue       received value
 * \return      Com_RxSigProcessState
 * \context     TASK
 * \synchronous TRUE
 * \reentrant   TRUE, for different handles
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_UInt8_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, uint8 tmpNewValue);
# endif

# if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_SINT8_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_SInt8_EvaluateInvalidValue
**********************************************************************************************************************/
/*!
 * \brief       Checks if the received value is an invalid value
 * \details     -
 * \pre         -
 * \param[in]   idxRxAccessInfo   index of Rx SigInfo
 * \param[in]   tmpNewValue       received value
 * \return      Com_RxSigProcessState
 * \context     TASK
 * \synchronous TRUE
 * \reentrant   TRUE, for different handles
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_SInt8_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, sint8 tmpNewValue);
# endif

# if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_UINT16_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_UInt16_EvaluateInvalidValue
**********************************************************************************************************************/
/*!
 * \brief       Checks if the received value is an invalid value
 * \details     -
 * \pre         -
 * \param[in]   idxRxAccessInfo   index of Rx SigInfo
 * \param[in]   tmpNewValue       received value
 * \return      Com_RxSigProcessState
 * \context     TASK
 * \synchronous TRUE
 * \reentrant   TRUE, for different handles
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_UInt16_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, uint16 tmpNewValue);
# endif

# if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_SINT16_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_SInt16_EvaluateInvalidValue
**********************************************************************************************************************/
/*!
 * \brief       Checks if the received value is an invalid value
 * \details     -
 * \pre         -
 * \param[in]   idxRxAccessInfo   index of Rx SigInfo
 * \param[in]   tmpNewValue       received value
 * \return      Com_RxSigProcessState
 * \context     TASK
 * \synchronous TRUE
 * \reentrant   TRUE, for different handles
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_SInt16_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, sint16 tmpNewValue);
# endif

# if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_UINT32_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_UInt32_EvaluateInvalidValue
**********************************************************************************************************************/
/*!
 * \brief       Checks if the received value is an invalid value
 * \details     -
 * \pre         -
 * \param[in]   idxRxAccessInfo   index of Rx SigInfo
 * \param[in]   tmpNewValue       received value
 * \return      Com_RxSigProcessState
 * \context     TASK
 * \synchronous TRUE
 * \reentrant   TRUE, for different handles
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_UInt32_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, uint32 tmpNewValue);
# endif

# if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_SINT32_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_SInt32_EvaluateInvalidValue
**********************************************************************************************************************/
/*!
 * \brief       Checks if the received value is an invalid value
 * \details     -
 * \pre         -
 * \param[in]   idxRxAccessInfo   index of Rx SigInfo
 * \param[in]   tmpNewValue       received value
 * \return      Com_RxSigProcessState
 * \context     TASK
 * \synchronous TRUE
 * \reentrant   TRUE, for different handles
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_SInt32_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, sint32 tmpNewValue);
# endif

# if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_UINT64_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_UInt64_EvaluateInvalidValue
**********************************************************************************************************************/
/*!
 * \brief       Checks if the received value is an invalid value
 * \details     -
 * \pre         -
 * \param[in]   idxRxAccessInfo   index of Rx SigInfo
 * \param[in]   tmpNewValue       received value
 * \return      Com_RxSigProcessState
 * \context     TASK
 * \synchronous TRUE
 * \reentrant   TRUE, for different handles
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_UInt64_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, uint64 tmpNewValue);
# endif

# if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_SINT64_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_SInt64_EvaluateInvalidValue
**********************************************************************************************************************/
/*!
 * \brief       Checks if the received value is an invalid value
 * \details     -
 * \pre         -
 * \param[in]   idxRxAccessInfo   index of Rx SigInfo
 * \param[in]   tmpNewValue       received value
 * \return      Com_RxSigProcessState
 * \context     TASK
 * \synchronous TRUE
 * \reentrant   TRUE, for different handles
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_SInt64_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, sint64 tmpNewValue);
# endif

# if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_FLOAT32_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_Float32_EvaluateInvalidValue
**********************************************************************************************************************/
/*!
 * \brief       Checks if the received value is an invalid value
 * \details     -
 * \pre         -
 * \param[in]   idxRxAccessInfo   index of Rx SigInfo
 * \param[in]   tmpNewValue       received value
 * \return      Com_RxSigProcessState
 * \context     TASK
 * \synchronous TRUE
 * \reentrant   TRUE, for different handles
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_Float32_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, float32 tmpNewValue);
# endif

# if ((COM_INVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_FLOAT64_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_Float64_EvaluateInvalidValue
**********************************************************************************************************************/
/*!
 * \brief       Checks if the received value is an invalid value
 * \details     -
 * \pre         -
 * \param[in]   idxRxAccessInfo   index of Rx SigInfo
 * \param[in]   tmpNewValue       received value
 * \return      Com_RxSigProcessState
 * \context     TASK
 * \synchronous TRUE
 * \reentrant   TRUE, for different handles
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_Float64_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, float64 tmpNewValue);
# endif

# if ((COM_CONSTVALUEARRAYBASEDINVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_UINT8_N_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_UInt8_N_EvaluateInvalidValue
**********************************************************************************************************************/
/*!
 * \brief         Checks if the received value is an invalid value
 * \details       -
 * \pre           -
 * \param[in]     idxRxAccessInfo index of Rx AccessInfo
 * \param[in]     newValue pointer to new value
 * \return        Com_RxSigProcessState
 * \context     TASK
 * \synchronous TRUE
 * \reentrant   TRUE, for different handles
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_UInt8_N_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, AUTOMATIC) newValue);
# endif

# if ((COM_RXTPINFOUSEDOFRXPDUINFO == STD_ON) && (COM_CONSTVALUEARRAYBASEDINVVALUEUSEDOFRXACCESSINFO == STD_ON) && (COM_EXISTS_UINT8_DYN_APPLTYPEOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
  Com_RxInv_Sig_UInt8_Dyn_EvaluateInvalidValue
**********************************************************************************************************************/
/*!
 * \brief         Checks if the received value is an invalid value
 * \details       -
 * \pre           -
 * \param[in]     idxRxAccessInfo index of Rx AccessInfo
 * \param[in]     newValue pointer to new value
 * \param[in]     sduLength new dynamic length
 * \return        Com_RxSigProcessState
 * \context     TASK
 * \synchronous TRUE
 * \reentrant   TRUE, for different handles
**********************************************************************************************************************/
FUNC(Com_RxSigProcessState, COM_CODE) Com_RxInv_Sig_UInt8_Dyn_EvaluateInvalidValue(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, AUTOMATIC) newValue, PduLengthType sduLength);
# endif

# define COM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* COM_RXINV_H */
/**********************************************************************************************************************
  END OF FILE: Com_RxInv.h
**********************************************************************************************************************/
