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
/*!        \file  Com_Gateway.h
 *        \brief  MICROSAR Communication header file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/
#if !defined (COM_GATEWAY_H)
# define COM_GATEWAY_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "Com_Lcfg.h"

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

# if (COM_GWINFOENDIDXOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_SignalGw_InitRxIpdu
**********************************************************************************************************************/
/*! \brief        This function initializes a rx I-PDU in Com_SignalGw.
    \details      -
    \pre          -
    \param[in]    ComPduId Handle of the I-PDU.
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_SignalGw_InitRxIpdu(PduIdType ComPduId);
# endif

# if (COM_GWINFOUSEDOFRXSIGINFO == STD_ON)
/**********************************************************************************************************************
  Com_SignalGw_SigEvent
**********************************************************************************************************************/
/*! \brief        This function sets a signal routing event flag for the passed ComSignal.
    \details      -
    \pre          -
    \param[in]    idxRxSigInfo Index of RxSigInfo
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_SignalGw_SigEvent(Com_RxSigInfoIterType idxRxSigInfo);
# endif

# if (COM_GWINFOUSEDOFRXSIGGRPINFO == STD_ON)
/**********************************************************************************************************************
  Com_SignalGw_SigGrpEvent
**********************************************************************************************************************/
/*! \brief        This function sets a signal routing event flag for the passed ComSignalGroup.
    \details      -
    \pre          -
    \param[in]    idxRxSigGrpInfo Index of RxSigGrpInfo
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_SignalGw_SigGrpEvent(Com_RxSigGrpInfoIterType idxRxSigGrpInfo);
# endif

# if (COM_GWSIGMAPPINGENDIDXOFGWINFO == STD_ON)
/**********************************************************************************************************************
  Com_MainFunction_SignalRoutings
**********************************************************************************************************************/
/*! \brief        This function processes the routing of the passed ComSignal GwInfo.
    \details      -
    \pre          -
    \param[in]    idxGwInfo  Index of GwInfo
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_MainFunction_SignalRoutings(Com_GwInfoIterType idxGwInfo);
# endif

# if (COM_GWSIGGRPMAPPINGENDIDXOFGWINFO == STD_ON)
/**********************************************************************************************************************
  Com_MainFunction_SignalGroupRoutings
**********************************************************************************************************************/
/*! \brief        This function processes the routing of the passed ComSignalGroup GwInfo
    \details      -
    \pre          -
    \param[in]    idxGwInfo  Index of GwInfo
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_MainFunction_SignalGroupRoutings(Com_GwInfoIterType idxGwInfo);
# endif

# if (COM_GWEVENTCACHE == STD_ON)
/**********************************************************************************************************************
  Com_MainFunction_GwDescription
**********************************************************************************************************************/
/*! \brief    This function processes deferred gateway description events that are queued in the gateway Event Cache
 *            in reverse order.
    \details  -
    \pre      -
    \context  TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_MainFunction_GwDescription(void);
# endif

# if (COM_GWTXPDUDESCRIPTIONINFOUSEDOFRXPDUINFO == STD_ON)
/**********************************************************************************************************************
  Com_RxProcessing_GwDescriptionEvent
**********************************************************************************************************************/
/*! \brief        This function handles the gateway description events and initiates the transmission if the conditions of
 *                the configured transfer properties are satisfied.
    \details      -
    \pre          -
    \param[in]    rxComPduId          Handle of the rx I-PDU.
    \param[in]    PduInfoPtr          contains the SDU buffer and the SDU length
    \context      TASK|ISR2
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxProcessing_GwDescriptionEvent(PduIdType rxComPduId, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr);
# endif

# define COM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* COM_GATEWAY_H */

/**********************************************************************************************************************
  END OF FILE: Com_Gateway.h
**********************************************************************************************************************/
