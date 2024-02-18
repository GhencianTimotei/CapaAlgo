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
/**        \file  Dcm_ExtInt.h
 *        \brief  Private data type definition and interface of DCM
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
#if !defined(DCM_EXTINT_H)
# define DCM_EXTINT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! Determines when the RoE task in the DCM extension is needed */
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
#  define DCM_EXT_TSK_NUM_ROE                                        1u
# else
#  define DCM_EXT_TSK_NUM_ROE                                        0u /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif

# if (DCM_EXT_TSK_NUM_ROE > 0u)
/*! Events of Dcm_ExtSvc86Task() (task located in the DCM extension part) */
#  define DCM_EXT_TSK_EV_ROE_ACTIVATE                                ((Dcm_TskTaskEvMemType)0x01u)  /*!< Activates the task (e.g. on power on to gather the RoE NvM state in the background) */
#  define DCM_EXT_TSK_EV_ROE_SEND                                    ((Dcm_TskTaskEvMemType)0x02u)  /*!< Event detected, the associated with the event STRT shall be executed */
#  define DCM_EXT_TSK_EV_ROE_TX_END                                  ((Dcm_TskTaskEvMemType)0x04u)  /*!< Signals that the STRT processing is finished */

/*! Registers the most significant bit in the event mask of the Dcm_ExtSvc86Task() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above */
#  define DCM_EXT_TSK_EV_ROE_MSB                                     0x04u

/*! Configures the RoE task as a one with a single activation within a single Dcm_MainFunction(Worker) activation since no chaining of complex activities is used */
#  define DCM_EXT_TSK_ATR_ROE_EXEC                                   DCM_TSK_ATR_EXEC_ONCE
# else
/*! No RoE task, no events, no MSB of the events available */
#  define DCM_EXT_TSK_EV_ROE_MSB                                     0x00u
# endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
#  define Dcm_ExtSvc86TxEnd()                                        (Dcm_TskSetEvent(DCM_TSK_ID_ROE, DCM_EXT_TSK_EV_ROE_TX_END))                    /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
/*! Service 0x86 temporary processing context */
struct DCM_SVC86REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_ExtSvc86NvMDataType NewNvmData;               /*!< Data to be read from or written to NvM RoE storage */
#  if (DCM_SVC_86_03_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_86_43_SUPPORT_ENABLED == STD_ON)                                                                                                      /* COV_DCM_SUPPORT_PARTIALLY TF tf xf */
  Dcm_DidMgrDidInfoContextType    DidInfoContext;   /*!< DID information context */
  Dcm_DidMgrDidOpTypeContextType  DidOpTypeContext; /*!< Did configuration operation context */
#  endif
  Dcm_DiagSubServiceRefMemType    SubSvcRef;        /*!< Index of the requested subfunction */
  boolean                         StoreState;       /*!< Whether the storageState Bit 6 was set */
};
typedef struct DCM_SVC86REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc86RepeaterProxyContextType;

typedef P2VAR(Dcm_Svc86RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_Svc86RepeaterProxyContextPtrType;
typedef P2CONST(Dcm_Svc86RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_Svc86RepeaterProxyContextConstPtrType;
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
  Dcm_ExtService86Init()
 **********************************************************************************************************************/
/*! \brief          Initialization function.
 *  \details        Service 0x86 initializer.
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_ExtService86Init(
  void
  );
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
# define DCM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#endif /* !defined(DCM_EXTINT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_ExtInt.h
 *********************************************************************************************************************/
