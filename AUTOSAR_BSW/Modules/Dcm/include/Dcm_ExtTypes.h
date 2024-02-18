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
/**        \file  Dcm_ExtTypes.h
 *        \brief  Public data type definition interface of DCM
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
#if !defined(DCM_EXTTYPES_H)
# define DCM_EXTTYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
typedef uint8  Dcm_ExtSvc86STRTStateType;
typedef uint8  Dcm_ExtSvc86RoeStateType;
typedef uint8  Dcm_ExtSvc86STRTType;

/*! Information about event record */
union DCM_EXTSVC86EVENTRECORDTYPE_TAG
{                                                                                                                                                    /* PRQA S 0750 */ /* MD_Dcm_Rule19.2 */
  uint8   DTCStatusMask;
  uint16  Did;
};
typedef union DCM_EXTSVC86EVENTRECORDTYPE_TAG Dcm_ExtSvc86EventRecordType;

/*! Information used for block size calculation of NvM RoE storage */
struct DCM_EXTSVC86NVMDATATYPE_TAG
{
  uint16                      ClientSrcAddr;   /*!< The testers source identifier */
  PduIdType                   RxPduId;         /*!< Id of connection currently requesting RoE */
  Dcm_ExtSvc86EventRecordType EventTypeRecord; /*!< Event record which is either DID or DTC status mask */
  Dcm_ExtSvc86RoeStateType    RoEState;        /*!< internal state of RoE Event */
  Dcm_ExtSvc86STRTType        EventType;       /*!< Type of event which is one of service 0x86 internally handled sub-functions */
  uint8                       EventId;         /*!< Id of the event to be stored */
};
typedef struct DCM_EXTSVC86NVMDATATYPE_TAG Dcm_ExtSvc86NvMDataType;
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#endif /* !defined(DCM_EXTTYPES_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_ExtTypes.h
 *********************************************************************************************************************/
