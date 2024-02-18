/* ********************************************************************************************************************
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
 *  -------------------------------------------------------------------------------------------------------------------
 */
/*! \addtogroup Dem_DTCIF
 *  \{
 *  \file       Dem_DTCIF_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of DTCIF subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DTCIF_IMPLEMENTATION_H)
#define DEM_DTCIF_IMPLEMENTATION_H

/* ********************************************************************************************************************
 *  GLOBAL MISRA JUSTIFICATIONS
 *********************************************************************************************************************/
/* PRQA S 2880 EOF */ /* MD_DEM_2.1_UNREACHABLE_STATEMENT */
/* PRQA S 2982 EOF */ /* MD_DEM_2982 */
/* PRQA S 2983 EOF */ /* MD_DEM_2983 */
/* PRQA S 2985 EOF */ /* MD_DEM_2985 */
/* PRQA S 2986 EOF */ /* MD_DEM_2986 */
/* PRQA S 2987 EOF */ /* MD_DEM_2987 */
/* PRQA S 2991 EOF */ /* MD_DEM_2991 */
/* PRQA S 2992 EOF */ /* MD_DEM_2992 */
/* PRQA S 2995 EOF */ /* MD_DEM_2995 */
/* PRQA S 2996 EOF */ /* MD_DEM_2996 */
/* PRQA S 0759 EOF */ /* MD_MSR_Union */

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DTCIF_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Satellite_Interface.h"
#include "Dem_FaultMemory_Interface.h"
#include "Dem_Infrastructure_Interface.h"
#include "Dem_GlobalDiagnostics_Interface.h"
#include "Dem_DiagnosticObserver_Interface.h"
#include "Dem_Client_Interface.h"
#include "Dem_Event_Interface.h"
#include "Dem_OperationCycle_Interface.h"
#include "Dem_UDSStatus_Interface.h"
#include "Dem_StatusIndicator_Interface.h"
#include "Dem_DTCInternalStatus_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_DTCIF_IMPLEMENTATION_FILENAME "Dem_DTCIF_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

#define DEM_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/*! Array of qualification processing states of combined DTCs */
DEM_LOCAL VAR(Dem_Cfg_ProcessedCombinedDTCGroupType, DEM_VAR_NOINIT) Dem_DTC_QualificationProcessedCombinedDTCs;                 /* PRQA S 3218 */ /* MD_DEM_8.7 */
#endif

#define DEM_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_DTC_PrivateProperties Private Properties
 * \{
 */


 /* ****************************************************************************
 * Dem_DTC_isRetryStorageEnabled
 *****************************************************************************/
 /*!
 * \brief         Returns true if feature 'retry storage' is enabled.
 * \details       -
 *
 * \return        TRUE
 *                Support for 'retry storage'
 * \return        FALSE
 *                No support for 'retry storage'
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_isRetryStorageEnabled(
  void
);


#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 * Dem_DTC_SetAgedCounter
 *****************************************************************************/
/*!
 * \brief         Sets the aged counter for the respective DTC.
 *
 * \details       Sets the aged counter for the respective DTC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \param[in]     AgedCounter
 *                The aged counter to be set.
 *
 * \config        DEM_CFG_DATA_AGED_COUNTER == STD_ON
 *
 * \pre           Event has a dedicated entry in the aged counter array.
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC) AgedCounter
  );
#endif

/* ****************************************************************************
 * Dem_DTC_IsEventCombinationType1Enabled
 *****************************************************************************/
/*!
 * \brief         Returns true if feature 'Event Combination Type 1' is enabled.
 * \details       -
 *
 * \return        TRUE
 *                Support for 'Event Combination Type 1'
 * \return        FALSE
 *                No support for 'Event Combination Type 1'
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_IsEventCombinationType1Enabled(
  void
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

 /* ****************************************************************************
 % Dem_DTC_isRetryStorageEnabled
 *****************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_isRetryStorageEnabled(
  void
  )
{
  return (boolean)(DEM_CFG_SUPPORT_RETRY_STORAGE == STD_ON);
}


#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 % Dem_DTC_SetAgedCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC) AgedCounter
  )
{
  uint16 lAgedCounterIndex;
  lAgedCounterIndex = Dem_Cfg_GetAgedCounterIndexOfEventTable(EventId);

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (lAgedCounterIndex >= DEM_CFG_MAX_NUMBER_AGED_DTCS)
  {
    Dem_Error_RunTimeCheckFailed(DEM_DTCIF_IMPLEMENTATION_FILENAME, __LINE__);                                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_GetAgingData().AgedCounter[lAgedCounterIndex] = AgedCounter;                                                         /* SBSW_DEM_ARRAY_WRITE_AGINGDATA_AGEDCOUNTER */
  }
}
#endif

/* ****************************************************************************
 % Dem_DTC_IsEventCombinationType1Enabled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_IsEventCombinationType1Enabled(
  void
  )
{
  return DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON;
}


/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_DTC_PublicProperties
 * \{
 */

/* ****************************************************************************
 % Dem_DTC_IsEventCombinationEnabled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_IsEventCombinationEnabled(                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
 )
{
  return ((Dem_DTC_IsEventCombinationType1Enabled()) || (Dem_DTC_IsEventCombinationType2Enabled()));                             
}

/* ****************************************************************************
% Dem_DTC_IsMemIndependentCycleCounterEnabled
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_IsMemIndependentCycleCounterEnabled(
  void
)
{
  return (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_ON);
}

/* ****************************************************************************
 % Dem_DTC_IsEventCombinationType2Enabled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_IsEventCombinationType2Enabled(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
)
{
  return DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON;
}


/* ****************************************************************************
 % Dem_DTC_GetInternalStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_InternalStatusType, DEM_CODE)
Dem_DTC_GetInternalStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_InternalStatusType lInternalStatus;
  /* Do not change to DEM_FEATURE_SUPPORT_EVENTCOMBINATION due to usage
     in Dem_Event_MayDisconnect and Dem_OperationCycle_UpdateTestEventAffected*/
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    lInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(lGroupId);
  }
  else
#endif
  {
    lInternalStatus = Dem_Event_GetInternalStatus(EventId);
  }
  return lInternalStatus;
}

/* ****************************************************************************
 % Dem_DTC_SetInternalStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetInternalStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, InternalStatus);
  }
  else
#endif
  {
    Dem_Event_SetInternalStatus(EventId, InternalStatus);
  }
}

/* ****************************************************************************
 % Dem_DTC_SetQualifyStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetQualifyStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  Status
  )
{
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);

  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_Cfg_CombinedGroupIterType lCombinedIter;
    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      /* Ignore event availability to prevent inconsistent qualification states later on */
      Dem_EventIdType lSubEventId;
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Event_SetQualifyStatus(lSubEventId, Status);
    }
  }
  else
# endif
  {
    Dem_Event_SetQualifyStatus(EventId, Status);
  }
}


#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 % Dem_DTC_GetAgedCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTC_GetAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  uint16 lAgedCounterIndex;

  lAgedCounterIndex = Dem_Cfg_GetAgedCounterIndexOfEventTable(EventId);
  return Dem_Cfg_GetAgingData().AgedCounter[lAgedCounterIndex];
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_DTC_Private Private Methods
 * \{
 */

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
 /* ****************************************************************************
 * Dem_DTC_SetFdcToc
 *****************************************************************************/
 /*!
 * \brief         Sets Fdc trip flag for the DTC
 *
 * \details       Sets Fdc trip flag of the DTC in the DTC internal status
 *                field.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING is off
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetFdcToc(
  Dem_EventIdType EventId
  );
#endif

 /* ****************************************************************************
 * Dem_DTC_IsMemIndependentFaultPendingCounterEnabled
 *****************************************************************************/
 /*!
 * \brief         Returns true if feature 'memory independent fault pending counter' is enabled.
 * \details       -
 *
 * \return        TRUE
 *                Feature supported
 * \return        FALSE
 *                Feature not supported
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_IsMemIndependentFaultPendingCounterEnabled(
  void
);

/* ****************************************************************************
* Dem_DTC_IsMemIndependentFailedCycleCounterEnabled
*****************************************************************************/
/*!
* \brief         Returns true if feature 'memory independent failed cycle counter' is enabled.
* \details       -
*
* \return        TRUE
*                Feature supported
* \return        FALSE
*                Feature not supported
*
* \pre           -
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_IsMemIndependentFailedCycleCounterEnabled(
  void
);

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_GenerateExternalOnlyType1CombinedStatus
 *****************************************************************************/
/*!
 * \brief         Calculate externally visible DTC status for a Type 1 combined
 *                event
 *
 * \details       This function calculates an externally visible DTC status byte
 *                for a Type 1 combined event taking user controlled WIR bit,
 *                visiblilty of CDTC and WIR bits into account.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     DtcStatus
 *                Unmodified DTC status byte
 *
 * \return        The resulting DTC status
 *
 * \pre           Event belongs to a Combined DTC group
 *
 * \config        DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_GenerateExternalOnlyType1CombinedStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DtcStatus
  );
#endif


#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_GenerateExternalOnlyType2CombinedStatus
 *****************************************************************************/
/*!
 * \brief         Calculate externally visible DTC status for a combined event
 *
 * \details       This function calculates an externally visible DTC status byte
 *                for the combined event taking user controlled WIR bit,
 *                visiblilty of CDTC and WIR bits into account.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     DtcStatus
 *                Unmodified DTC status byte
 *
 * \return        The resulting DTC status
 *
 * \pre           Event belongs to a Combined DTC group
 *
 * \config        DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_GenerateExternalOnlyType2CombinedStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DtcStatus
  );
#endif


# if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_TestStoredStatus_Type2
 *****************************************************************************/
/*!
 * \brief         Tests whether a memory entry exists for the DTC
 *
 * \details       Tests whether a memory entry exists for the DTC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                Memory entry for DTC exists.
 * \return        FALSE
 *                Memory entry for DTC does not exist.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
  Dem_DTC_TestStoredStatus_Type2(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


# if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_ProcessOperation
 *****************************************************************************/
/*!
 * \brief         Function processes the 'Requested effects' for a normal
 *                or combined event and recalculates the statuses.
 *
 * \details       Function processes the 'Requested effects' for a normal
 *                or combined event and recalculates the statuses.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     FuncPtr
 *                Operation to perform on all subevents
 * \param[in]     ArgPtr
 *                Arguments passed to the operation.
 *
 * \pre           -
 *
 * \config        (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ProcessOperation(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Util_ForEachCombinedFuncType, AUTOMATIC)  FuncPtr,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );
#endif


#if ((DEM_CFG_SUPPORT_OBDII == STD_ON) \
    && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF) \
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 * Dem_DTC_CycleQualifyDcy_EventCombType2_StoredOnly
 *****************************************************************************/
/*!
 * \brief         Qualifies the OBD driving cycle for a configuration supporting
 *                event combination Type 2 in case event confirmation
 *                is coupled with event memory entry creation.
 *
 * \details       When the driving cycle is qualified, the environmental data,
 *                ConfirmedDTC bit and WIR bit become visible for external
 *                testers and the application.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_OBDII == STD_ON)
 *                && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF)
 *                && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
 *
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CycleQualifyDcy_EventCombType2_StoredOnly(
  void
  );
#endif


/* ****************************************************************************
 * Dem_DTC_ProcessAgingOnPassed
 *****************************************************************************/
/*!
 * \brief         Process aging start conditions.
 *
 * \details       Process aging start conditions.
 *
 * \param[in]     DTCContext
 *                DTC processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ProcessAgingOnPassed(
  CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC)  DTCContext
  );


#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_GetCombinedGroupUDSStatus
 *****************************************************************************/
/*!
 * \brief         Get current status of the combined group
 *
 * \details       -
 *
 * \param[in]     GroupId
 *                Unique handle of the combined group
 *
 * \return        Current status of the combined group
 *
 * \pre           -
 * \config        DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTC_GetCombinedGroupUDSStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) GroupId
  );
#endif


#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) \
 && ((DEM_CFG_AGING_NEXT_TESTS_TNCTOC == STD_ON) || (DEM_CFG_AGING_NEXT_TESTS_TFTOC == STD_ON))
/* ****************************************************************************
 * Dem_DTC_TestStatusForAgingCycle
 *****************************************************************************/
/*!
 * \brief         Tests whether the current cycle fulfills the conditions for
 *                aging
 *
 * \details       Tests whether the current cycle fulfills the conditions for
 *                aging
 *
 * \param[in]     DtcStatus
 *                UDS DTC status to test
 *
 * \return        TRUE
 *                The aging conditions are fulfilled for this cycle
 * \return        FALSE
 *                the aging conditions are not fulfilled for this cycle
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF &&
 *                (DEM_CFG_AGING_NEXT_TESTS_TNCTOC == STD_ON ||
 *                DEM_CFG_AGING_NEXT_TESTS_TFTOC == STD_ON)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestStatusForAgingCycle(
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DTCStatus
  );
#endif


/* ****************************************************************************
 * Dem_DTC_TestGroupAvailable
 *****************************************************************************/
/*!
 * \brief         Tests if a combined event group is available based on runtime
 *                calibration
 *
 * \details       Tests if a combined event group is available based on runtime
 *                calibration
 *
 * \param[in]     GroupId
 *                Unique identifier of the combined event group
 *
 * \return        TRUE
 *                The group is available
 * \return        FALSE
 *                The group is not available
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestGroupAvailable(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId
  );


/* ****************************************************************************
 * Dem_DTC_TestGroupAvailableInVariant
 *****************************************************************************/
/*!
 * \brief         Tests if a combined event group is available based on the PB-S
 *                variant
 *
 * \details       Tests if a combined event group is available based on the PB-S
 *                variant
 *
 * \param[in]     GroupId
 *                Unique identifier of the combined event group
 *
 * \return        TRUE
 *                The group is available in the selected variant
 * \return        FALSE
 *                The group is not available in the selected variant
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestGroupAvailableInVariant(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId
  );


/* ****************************************************************************
 * Dem_DTC_TestGroupSuppression
 *****************************************************************************/
/*!
 * \brief         Tests if a combined event group is suppressed for reporting API
 *
 * \details       Tests if a combined event group is suppressed for reporting API
 *
 * \param[in]     GroupId
 *                Unique identifier of the combined event group
 *
 * \return        TRUE
 *                The group is suppressed
 * \return        FALSE
 *                The group is not suppressed
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestGroupSuppression(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId
  );


/* ****************************************************************************
 * Dem_DTC_ApplyUserControlledWIR
 *****************************************************************************/
/*!
 * \brief         Apply the user controlled WIR bit to the DTC's status
 *
 * \details       This function applies a user controlled WIR bit from the
 *                given internal status to the given DTC status byte.
 *
 *                The resulting WIR status cannot be reset by this function.
 *
 * \param[in]     DtcStatus
 *                Unmodified DTC status byte
 *
 * \param[in]     InternalStatus
 *                Internal event status information
 *
 * \return        The resulting DTC status
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_ApplyUserControlledWIR(
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DtcStatus,
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  InternalStatus
  );


#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_CombinedGroupGetFDC
 *****************************************************************************/
/*!
 * \brief         Calculates the fault detection counter of a combined event
 *
 * \details       This function iterates through all sub-events, and takes the
 *                largest fault detection counter to represent the combined
 *                FDC.
 *                This is not stable against preemptive modification of the
 *                set of FDCs concerned. This is not prevented as it would
 *                lead to a large runtime within a critical section, without
 *                actually increasing the expected quality of the result.
 *
 *                Explanation: If all sub-events report a fairly stable result
 *                (the FDCs count fairly linearly), the combined FDC is also
 *                reliable if it is collected without critical section.
 *                If the sub-events change their result often and chaotically,
 *                the combined FDC also behaves chaotically, based on report
 *                order and task priorities. Collecting the FDCs within a
 *                critical section will not improve the result.
 *
 * \param[in]     GroupId
 *                Unique identifier of the combined event group
 * \param[out]    FaultDetectionCounter
 *                Pointer to receive the FDC value
 *
 * \return        E_OK
 *                The combined FDC was returned in FaultDetectionCounter
 * \return        E_NOT_OK
 *                The combined FDC could not be determined.
 *
 * \pre           RTE is started (if RTE is used)
 * \config        ((DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_CFG_DATA_CURRENT_FDC == STD_ON))
 *                && (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) )
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_CombinedGroupGetFDC(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId,
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter
  );
#endif


#if ( ((DEM_FEATURE_NEED_AGING_TRIGGER_PASSED == STD_ON)\
      || ((DEM_FEATURE_NEED_AGING_TRIGGER_CYCLE == STD_ON) && (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)) )\
      && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 * Dem_DTC_TestDtcMayAge
 *****************************************************************************/
/*!
 * \brief         Tests whether an event or combined event may age
 *
 * \details       Tests whether an event or combined event may age
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event may age
 * \return        FALSE
 *                The event may not age
 *
 * \pre           -
 *
 * \config        ((DEM_FEATURE_NEED_AGING_TRIGGER_PASSED== STD_ON) ||
 *                 ((DEM_FEATURE_NEED_AGING_TRIGGER_CYCLE == STD_ON) &&
 *                  (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)))  &&
 *                 (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcMayAge(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) && (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_Disconnect_Combined
 *****************************************************************************/
/*!
 * \brief         Marks a combined event unavailable
 *
 * \details       This function sets a sub-event unavailable and re-calculates
 *                the availability and suppression states for the combined
 *                DTC.
 *
 *                A stored DTC may not be set to unavailable, so this function
 *                performes no actions on stored DTCs.
 *
 *                Do not call directly, use Dem_DTC_Disconnect instead.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           Must be called in critical section DiagMonitor
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON &&
 *                DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Disconnect_Combined(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) && (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_Reconnect_Combined
 *****************************************************************************/
/*!
 * \brief         Marks a combined event available
 *
 * \details       This function sets a sub-event available and re-calculates
 *                the availability and suppression states for the combined
 *                DTC.
 *
 *                Do not call directly, use Dem_DTC_Reconnect instead.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           Must be called in critical section DiagMonitor
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON &&
 *                DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Reconnect_Combined(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
 * Dem_DTC_AgingStartZeroTarget
 *****************************************************************************/
 /*!
 * \brief         Starts aging of an event with aging target 0
 *
 * \details       This function processes aging for events with aging target
 *                0. I.e. the event will age immediately. This function has
 *                no effect if the event in question is already aged or does
 *                not support aging.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     SuppressNotifications
 *                Suppress DTC and Event Status Change Notifications
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_AgingStartZeroTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  SuppressNotifications
  );
#endif


#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
 * Dem_DTC_AgingStartMultiTarget
 *****************************************************************************/
/*!
 * \brief         Starts aging of an event.
 *
 * \details       This function sets up an event for aging. In case the event
 *                already ages (or does not support aging), this function has
 *                no effect.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_AgingStartMultiTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
/* ****************************************************************************
 *  Dem_DTC_CustomizedAging
 *****************************************************************************/
/*!
 * \brief         Update event due to aging event (Customized trigger)
 *
 * \details       Update event due to aging event (Customized trigger)
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
 Dem_DTC_CustomizedAging(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
/* ****************************************************************************
 * Dem_DTC_CustomizedAgingStart
 *****************************************************************************/
/*!
 * \brief         Process event aging and occurrence counters
 *
 * \details       Process event aging and occurrence counters
 *
 * \param[in]     DTCContext
 *                DTC processing context
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CustomizedAgingStart(
  CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
  );
#endif


/* ****************************************************************************
 * Dem_DTC_Passed_ProcessDTCEffects_TPSLC
 *****************************************************************************/
/*!
 * \brief         Processes DTCs that are relevant for Pid01 calculation
 *
 * \details       Extended Status of DTC is set to 'passed since last clear'.
 *                For DTC with combined group status it is only set if all
 *                subevents are tested this cycle and no subevent has status
 *                failed.
 *
 * \param[in]     DTCContext
 *                DTC processing context
 *
 * \pre           -
 * \config        Feature Major Monitors and PID 01 is enabled
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different DTCContext
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Passed_ProcessDTCEffects_TPSLC(
  CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC)  DTCContext
  );

/* ****************************************************************************
 * Dem_DTC_ForEachCombinedSubEvent
 *****************************************************************************/
/*!
 * \brief         Executes a combined operation.
 *
 * \details       Due to excessive code duplication it was necessary to fall
 *                back to higher order functions. This function takes a
 *                function pointer to an operation to be executed for all
 *                sub-events of a combined event.
 *                For normal events, the operation is executed for that event
 *                only, so the caller does not need to distinguish between
 *                combined and non-combined events too much.
 *
 *                The caller is still reponsible to call this function only
 *                once per combined event, e.g. by calling it only for the
 *                master event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     FuncPtr
 *                Operation to perform on all subevents
 * \param[in]     ArgPtr
 *                Arguments passed to the operation.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ForEachCombinedSubEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Util_ForEachCombinedFuncType, AUTOMATIC)  FuncPtr,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );


#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_InitGroupInternalStatus
 *****************************************************************************/
/*!
 * \brief         Initializes the internal event status of a given combined
 *                event group
 *
 * \details       Initializes the internal event status of a given combined
 *                event group
 *
 * \param[in]     GroupId
 *                Unique identifier of the combined event group
 *
 * \pre           May be called only during module initialization
 * \config        DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InitGroupInternalStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId
  );
#endif


#if (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
/* ****************************************************************************
 * Dem_DTC_CycleQualifyDcy_AllDtc
 *****************************************************************************/
/*!
 * \brief         Qualifies the OBD driving cycle in case event confirmation
 *                is independent from event memory entry creation.
 *
 * \details       When the driving cycle is qualified, the environmental data,
 *                ConfirmedDTC bit and WIR bit become visible for external
 *                testers and the application.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON &&
 *                DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CycleQualifyDcy_AllDtc(
  void
  );
#endif


#if (DEM_FEATURE_NEED_OBD == STD_ON) \
   && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF) \
   && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_OFF)
/* ****************************************************************************
 * Dem_DTC_CycleQualifyDcy_StoredOnly
 *****************************************************************************/
/*!
 * \brief         Qualifies the OBD driving cycle in case event confirmation
 *                is coupled with event memory entry creation.
 *
 * \details       When the driving cycle is qualified, the environmental data,
 *                ConfirmedDTC bit and WIR bit become visible for external
 *                testers and the application.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON &&
 *                DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF &&
 *                DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CycleQualifyDcy_StoredOnly(
  void
  );
#endif


#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_SetDtcSuppression
 *****************************************************************************/
/*!
 * \brief         Marks an event's DTC suppressed
 *
 * \details       This function sets an event's DTC suppressed.
 *                For combined events, it does not matter which sub-event is
 *                passed to this function.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetDtcSuppression(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


/* ****************************************************************************
 * Dem_DTC_EventEntryReInit
 *****************************************************************************/
/*!
 * \brief         Reclaim an event memory entry
 *
 * \details       This function reclaims an event memory entry for
 *                the given event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \param[in]     MemoryIndex
 *                Valid Handle of the memory block
 *
 * \pre           The event is stored already
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_EventEntryReInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );


/* ****************************************************************************
 * Dem_DTC_EventCreateMemory
 *****************************************************************************/
/*!
 * \brief         Allocate an event memory entry
 *
 * \details       This function tries to allocate an event memory entry for
 *                the given event. This can displace existing memory entries
 *                if the memory is already full.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        MemoryIndex of the allocated memory entry. If no entry was
 *                allocated, DEM_MEM_INVALID_MEMORY_INDEX is returned.
 *
 * \pre           The event may not be stored already
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_DTC_EventCreateMemory(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );


#if ((DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) && (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF))
/* ****************************************************************************
 * Dem_DTC_StartAgingWithMemoryEntryMultiTarget
 *****************************************************************************/
/*!
 * \brief         Starts aging of an event.
 *
 * \details       This function sets up an event for aging according to the
 *                legacy aging algorithm. Here the aging proceeds only if a
 *                memory entry could be allocated for the event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
 *                && (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF)
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_StartAgingWithMemoryEntryMultiTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


#if ((DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) && (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON))
/* ****************************************************************************
 * Dem_DTC_StartAgingWithoutMemoryEntryMultiTarget
 *****************************************************************************/
/*!
 * \brief         Starts aging of an event.
 *
 * \details       This function sets up an event for aging. Here the aging
 *                proceeds event if a memory entry does not exist for the event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
 *                && (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_StartAgingWithoutMemoryEntryMultiTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/* ****************************************************************************
 * Dem_DTC_SetFaultPendingCounter
 *****************************************************************************/
/*!
 * \brief         Set the memory independent fault pending counter of 
 *                the respective DTC.
 *
 * \details       Set the memory independent fault pending counter of 
 *                the respective DTC.
 *
 * \param[in]     FaultPendingCounterIndex
 *                Index to array FaultPendingCounter.
 *                The Index must be in range [1..DEM_CFG_MAX_NUMBER_FAULT_PENDING_DTCS[.
 * \param[in]     FaultPendingCounter
 *                Value to set.
 *
 * \pre           Feature memory independent fault pending counter is enabled.
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_SetFaultPendingCounter(
  Dem_Cfg_FaultPendingCounterIndexOfEventTableType FaultPendingCounterIndex,
  uint8 FaultPendingCounter
  );

/* ****************************************************************************
* Dem_DTC_SetFailedCycleCounter
*****************************************************************************/
/*!
* \brief         Set the memory independent failed cycle counter of
*                the respective DTC.
*
* \details       Set the memory independent failed cycle counter of
*                the respective DTC.
*
* \param[in]     FailedCycleCounterIndex
*                Index to array FailedCycleCounter.
*                The Index must be in range [1..DEM_CFG_MAX_NUMBER_FAILED_CYCLE_DTCS[.
* \param[in]     FailedCycleCounter
*                Value to set.
*
* \pre           Feature memory independent failed cycle counter is enabled.
*
* \context       TASK/ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_SetFailedCycleCounter(
  Dem_Cfg_FailedCycleCounterIndexOfEventTableType FailedCycleCounterIndex,
  uint8 FailedCycleCounter
  );

/* ****************************************************************************
 * Dem_DTC_ResetFailedCycleCounter
 *****************************************************************************/
/*!
 * \brief         Reset the memory independent failed cycle counter of 
 *                the respective DTC.
 *
 * \details       Reset the memory independent failed cycle counter of 
 *                the respective DTC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           Feature memory independent failed cycle counter is supported.
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_ResetFailedCycleCounter(
  Dem_EventIdType EventId
  );

/* ****************************************************************************
* Dem_DTC_IncrementFailedCycleCounter
*****************************************************************************/
/*!
* \brief         Increments the memory independent failed cycle counter of
*                the respective DTC.
*
* \details       Increments the memory independent failed cycle counter of
*                the respective DTC.
*
* \param[in]     EventId
*                Unique handle of the Event.
*                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
*
* \pre           Feature memory independent failed cycle counter is supported.
*
* \context       TASK/ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_IncrementFailedCycleCounter(
  Dem_EventIdType EventId
);

/* ****************************************************************************
* Dem_DTC_IncrementFaultPendingCounter
*****************************************************************************/
/*!
* \brief         Increment the memory independent fault pending counter of
*                the respective DTC.
*
* \details       Increment the memory independent fault pending counter of
*                the respective DTC.
*
* \param[in]     EventId
*                Unique handle of the Event.
*                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
*
* \pre           Feature memory independent fault cycle counter is supported.
*
* \context       TASK/ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_IncrementFaultPendingCounter(
  Dem_EventIdType  EventId
);

#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 * Dem_DTC_ResetAgedCounter
 *****************************************************************************/
/*!
 * \brief         Reset the aged counter of the respective DTC.
 *
 * \details       Reset the aged counter of the respective DTC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \config        DEM_CFG_DATA_AGED_COUNTER == STD_ON
 *
 * \pre           -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_ResetAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 * Dem_DTC_IncrementAgedCounter
 *****************************************************************************/
/*!
 * \brief         Increments the aged counter for the respective DTC.
 *
 * \details       Increments the aged counter for the respective DTC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \config        DEM_CFG_DATA_AGED_COUNTER == STD_ON
 *
 * \pre           -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_IncrementAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) && \
    ((DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON) || (DEM_CFG_STORAGE_AT_FDC == STD_ON))
/* ****************************************************************************
 * Dem_DTC_CalcFdcUpdateFlags
 *****************************************************************************/
/*!
 * \brief         Test if the Fdc threshold is reached for the DTC for the first
 *                time in current operation cycle.
 *
 * \details       Test if the Fdc threshold is reached for the DTC for the first
 *                time in current operation cycle.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The Fdc Update Flag
 *                DEM_CFG_TRIGGER_FDC_FIRST_IN_CYCLE: Fdc threshold reached
 *                for the first time for DTC
 *                DEM_CFG_TRIGGER_FDC: Fdc threshold reached was reached for DTC
 *                before
 *
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF &&
 *                (DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON ||
 *                 DEM_CFG_STORAGE_AT_FDC == STD_ON)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_StorageTriggerType, DEM_CODE)
Dem_DTC_CalcFdcUpdateFlags(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


/* ****************************************************************************
 * Dem_DTC_FreeEventAgingOnly
 *****************************************************************************/
/*!
 * \brief         Ends aging process of event with 'aging only' entry.
 *
 * \details       Free the event memory entry, resets DTC internal status and
 *                mark the corresponding NV block as 'Dirty'
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \pre           -
 *
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_FreeEventAgingOnly(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );


/* ****************************************************************************
 * Dem_DTC_TestStoredStatusOnDtcRetrieval
 *****************************************************************************/
/*!
 * \brief         Tests whether a memory entry exists for the DTC
 *
 * \details       Tests whether a memory entry exists for the DTC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                Memory entry for DTC exists.
 * \return        FALSE
 *                Memory entry for DTC does not exist.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
  Dem_DTC_TestStoredStatusOnDtcRetrieval(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );


#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_EventCombinationOnStorage_Cleared
 *****************************************************************************/
/*!
 * \brief         Clears 'event combination on storage' DTCs.
 *
 * \details       Clears 'event combination on storage' DTCs.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                At least one subevent has been cleared.
 * \return        FALSE
 *                No subevent could be cleared.
 *
 * \pre           -
 *
 * \config        DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_EventCombinationOnStorage_Cleared(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_EventCombinationOnRetrieval_Cleared
 *****************************************************************************/
/*!
 * \brief         Clears 'event combination on retrieval' DTCs.
 *
 * \details       Clears 'event combination on retrieval' DTCs.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                At least one subevent has been cleared.
 * \return        FALSE
 *                No subevent could be cleared.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_EventCombinationOnRetrieval_Cleared(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
 % Dem_DTC_SetFdcToc
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetFdcToc(
  Dem_EventIdType EventId
  )
{
#if (DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON)
  Dem_Event_InternalStatusType lInternalStatus;
  /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
  Dem_EnterCritical_DiagMonitor();

  lInternalStatus = Dem_Event_GetInternalStatus(EventId);
  lInternalStatus = Dem_DTCInternalStatus_SetFdcToc(lInternalStatus);
  Dem_Event_SetInternalStatus(EventId, lInternalStatus);

  Dem_LeaveCritical_DiagMonitor();
  /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

 /* ****************************************************************************
 % Dem_DTC_IsMemIndependentFaultPendingCounterEnabled
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_IsMemIndependentFaultPendingCounterEnabled(
  void
)
{
  return (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_ON) && (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON);
}

/* ****************************************************************************
% Dem_DTC_IsMemIndependentFailedCycleCounterEnabled
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_IsMemIndependentFailedCycleCounterEnabled(
  void
)
{
  return (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_ON) && (DEM_CFG_DATA_FAILED_CYCLES == STD_ON);
}

 /* ****************************************************************************
 % Dem_DTC_ResetFailedCycleCounter
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_ResetFailedCycleCounter(
  Dem_EventIdType EventId
)
{
  if(Dem_DTC_IsMemIndependentFailedCycleCounterEnabled() == TRUE)
  {
    Dem_Cfg_FailedCycleCounterIndexOfEventTableType lFailedCounterIndex;

    lFailedCounterIndex = Dem_Cfg_GetFailedCycleCounterIndexOfEventTable(EventId);

    if (lFailedCounterIndex != DEM_CFG_FAILEDCYCLECOUNTER_INDEX_INVALID)
    { /* memory independent failed cycle counter supported for event */
      Dem_DTC_SetFailedCycleCounter(lFailedCounterIndex, 0);

      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_CYCLECOUNTERDATA),
        DEM_NVM_BLOCKSTATE_DIRTY);
    }
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}

/* ****************************************************************************
 % Dem_DTC_SetFaultPendingCounter
*****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_SetFaultPendingCounter(
  Dem_Cfg_FaultPendingCounterIndexOfEventTableType FaultPendingCounterIndex,
  uint8 FaultPendingCounter
)
{
#if (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_ON)
  if ((Dem_Error_isDevRunTimeChecksEnabled() == TRUE)
    && (FaultPendingCounterIndex >= DEM_CFG_MAX_NUMBER_FAULT_PENDING_DTCS))
  {
    Dem_Error_RunTimeCheckFailed(DEM_DTCIF_IMPLEMENTATION_FILENAME, __LINE__);                                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
  {
    Dem_Cfg_CycleCounterData.FaultPendingCounter[FaultPendingCounterIndex] = FaultPendingCounter;                                /* SBSW_DEM_ARRAY_WRITE_CYCLECOUNTERDATA_FAULTPENDINGCOUNTER */
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FaultPendingCounter)                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FaultPendingCounterIndex)                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
}

/* ****************************************************************************
 % Dem_DTC_SetFailedCycleCounter
*****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_SetFailedCycleCounter(
  Dem_Cfg_FailedCycleCounterIndexOfEventTableType FailedCycleCounterIndex,
  uint8 FailedCycleCounter
)
{
#if (DEM_CFG_DATA_FAILED_CYCLES == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_ON)
    if ( (Dem_Error_isDevRunTimeChecksEnabled() == TRUE)
      && (FailedCycleCounterIndex >= DEM_CFG_MAX_NUMBER_FAILED_CYCLE_DTCS))
    {
      Dem_Error_RunTimeCheckFailed(DEM_DTCIF_IMPLEMENTATION_FILENAME, __LINE__);                                                   /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    }
    else
    {
      Dem_Cfg_CycleCounterData.FailedCycleCounter[FailedCycleCounterIndex] = FailedCycleCounter;                                 /* SBSW_DEM_ARRAY_WRITE_CYCLECOUNTERDATA_FAILEDCYCLECOUNTER */
    }
#else
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(FailedCycleCounter)                                                                         /* PRQA S 3112 */ /* MD_DEM_14.2 */
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FailedCycleCounterIndex)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */
}

/* ****************************************************************************
% Dem_DTC_IncrementFailedCycleCounter
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
*/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_IncrementFailedCycleCounter(
  Dem_EventIdType EventId
)
{
  Dem_Cfg_FailedCycleCounterIndexOfEventTableType lFailedCounterIndex;

  if(Dem_DTC_IsMemIndependentFailedCycleCounterEnabled() == TRUE)
  {
    lFailedCounterIndex = Dem_Cfg_GetFailedCycleCounterIndexOfEventTable(EventId);

    if (lFailedCounterIndex != DEM_CFG_FAILEDCYCLECOUNTER_INDEX_INVALID)
    { /* memory independent failed cycle counter supported for event */
      uint8 lCycleCounter;
      lCycleCounter = Dem_DTC_GetFailedCycleCounter(lFailedCounterIndex);
      if (lCycleCounter < 0xffU)
      {
        lCycleCounter = (uint8)(lCycleCounter + 1u);
        Dem_DTC_SetFailedCycleCounter(lFailedCounterIndex, lCycleCounter);

        Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_CYCLECOUNTERDATA),
          DEM_NVM_BLOCKSTATE_DIRTY);
      }
    }
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}

/* ****************************************************************************
 % Dem_DTC_IncrementFaultPendingCounter
*****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_IncrementFaultPendingCounter(
  Dem_EventIdType EventId
)
{
  Dem_Cfg_FaultPendingCounterIndexOfEventTableType lFaultPendingCounterIndex;

  if(Dem_DTC_IsMemIndependentFaultPendingCounterEnabled() == TRUE)
  {
    lFaultPendingCounterIndex = Dem_Cfg_GetFaultPendingCounterIndexOfEventTable(EventId);

    if (lFaultPendingCounterIndex != DEM_CFG_FAULTPENDINGCOUNTER_INDEX_INVALID)
    { /* memory independent fault pending counter supported for event */
      uint8 lCycleCounter;
      lCycleCounter = Dem_DTC_GetFaultPendingCounter(lFaultPendingCounterIndex);
      if (lCycleCounter < 0xffU)
      {
        lCycleCounter = (uint8)(lCycleCounter + 1u);
        Dem_DTC_SetFaultPendingCounter(lFaultPendingCounterIndex, lCycleCounter);

        Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_CYCLECOUNTERDATA),
          DEM_NVM_BLOCKSTATE_DIRTY);
      }
    }
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_GenerateExternalOnlyType1CombinedStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_GenerateExternalOnlyType1CombinedStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DtcStatus
  )
{
  /* DTC has combined group*/
  boolean lWirActive;
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  Dem_DTC_UDSStatusType lExternalDTCSTatus;
# if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
  Dem_Cfg_CombinedGroupIterType lCombinedIter;
# endif

  lWirActive = FALSE;
  lExternalDTCSTatus = DtcStatus;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);

  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    lExternalDTCSTatus = (Dem_DTC_UDSStatusType)(lExternalDTCSTatus & Dem_Event_GetQualifyStatus(EventId));
  }

# if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
    /* Scan through all active sub-events */
  for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lSubEventId;

    lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
    if ( (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)                                                                  
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE) )                    
    {
      lWirActive = (boolean)(lWirActive                                                                                          
        || (Dem_DTCInternalStatus_TestUserControlledWir(Dem_Event_GetInternalStatus(lSubEventId)) == TRUE));                     
    }
  }

  if (lWirActive == TRUE)
  {
    lExternalDTCSTatus = Dem_UDSStatus_Set_WIR(lExternalDTCSTatus);
  }
# endif

  lExternalDTCSTatus = Dem_DTC_ApplyCombinedStatus(lExternalDTCSTatus);

  return lExternalDTCSTatus;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_GenerateExternalOnlyType2CombinedStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_GenerateExternalOnlyType2CombinedStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DtcStatus
  )
{
  /* DTC has combined group*/
  Dem_DTC_UDSStatusType lExternalDTCSTatus;

# if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtcStatus)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lExternalDTCSTatus = Dem_DTC_CalculateCombinedGroupType2_ExternalUdsStatus(EventId);
# else
  if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
  {
    lExternalDTCSTatus = Dem_DTC_CalculateCombinedGroupType2_ExternalUdsStatus(EventId);
  }
  else
  {
    lExternalDTCSTatus = DtcStatus;
  }
# endif

  lExternalDTCSTatus = Dem_DTC_ApplyCombinedStatus(lExternalDTCSTatus);

  return lExternalDTCSTatus;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_TestStoredStatus_Type2
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestStoredStatus_Type2(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  boolean lStoredStatus;
  Dem_EventIdType lSubEventId;
  Dem_Cfg_CombinedGroupIterType lCombinedIter;
  Dem_Cfg_CombinedGroupIndexType lGroupId;

  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  lStoredStatus = FALSE;

  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      if (Dem_DTCInternalStatus_GetStoredStatus(Dem_Event_GetInternalStatus(lSubEventId)) != Dem_DTCInternalStatus_StoredStatus_None)
      {
        lStoredStatus = TRUE;
        break;
      }
    }
  }
  else
  {
    /* no combined event */
    lStoredStatus = (boolean)(Dem_DTCInternalStatus_GetStoredStatus(Dem_Event_GetInternalStatus(EventId))
                      != Dem_DTCInternalStatus_StoredStatus_None);
  }
  return lStoredStatus;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_ProcessOperation
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ProcessOperation(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Util_ForEachCombinedFuncType, AUTOMATIC)  FuncPtr,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  )
{
  Dem_Cfg_CombinedGroupIndexType lCurrentlyProcessingGroupId;

  lCurrentlyProcessingGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lCurrentlyProcessingGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_DTC_UDSStatusType lCombinedGroupDtcStatus;
    ArgPtr->Common.OldDtcStatus = Dem_DTC_GetCombinedGroupUDSStatus(lCurrentlyProcessingGroupId);                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    (*FuncPtr)(EventId, ArgPtr);                                                                                                 /* SBSW_DEM_CALL_FUNCPTR_FOR_EVENT */
    lCombinedGroupDtcStatus = Dem_DTC_CalculateCombineGroupUdsStatus(lCurrentlyProcessingGroupId);
    Dem_DTC_SetCombinedGroupUDSStatus(lCurrentlyProcessingGroupId, lCombinedGroupDtcStatus);
    ArgPtr->Common.NewDtcStatus = lCombinedGroupDtcStatus;                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  else
  /* Event is not a combined event */
  {
    ArgPtr->Common.OldDtcStatus = Dem_Event_GetUDSStatus(EventId);                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    (*FuncPtr)(EventId, ArgPtr);                                                                                                 /* SBSW_DEM_CALL_FUNCPTR_FOR_EVENT */
    ArgPtr->Common.NewDtcStatus = Dem_Event_GetUDSStatus(EventId);                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((DEM_CFG_SUPPORT_OBDII == STD_ON) \
    && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF) \
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_DTC_CycleQualifyDcy_EventCombType2_StoredOnly
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CycleQualifyDcy_EventCombType2_StoredOnly(
  void
  )
{
  Dem_Memory_AllocMemEntriesIterType lStoredEventsIter;
  Dem_DTC_InitCombinedGroupProcessed(Dem_DTC_QualificationProcessedCombinedDTCs);                                                /* SBSW_DEM_POINTER_FORWARD_GLOBAL */

  for (Dem_Memory_AllocMemEntriesChrono_IterInit(DEM_CFG_MEMORYID_PRIMARY, &lStoredEventsIter);                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_AllocMemEntriesChrono_IterExists(&lStoredEventsIter) == TRUE;                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_AllocMemEntriesChrono_IterNext(&lStoredEventsIter))                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
    Dem_EventIdType lEventId;
    uint8 lOldDtcStatus;
    Dem_DTC_ForEachCombinedArgType lArgs;
    Dem_Cfg_CombinedGroupIndexType lGroupId;

    lMemoryIndex = Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex(&lStoredEventsIter);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);
    lEventId = Dem_MemoryEntry_GetEventId(lMemoryEntryId);

    if (Dem_Event_TestValidHandle(lEventId) == FALSE)
    {
      Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
      continue;                                                                                                                  
    }

    /* Skip non OBD Events */
    if (Dem_Cfg_EventObdRelated(lEventId) == FALSE)
    {
      continue;                                                                                                                  
    }

# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
    /* Skip aged Events */
    if (Dem_DTCInternalStatus_GetStoredStatus(Dem_DTC_GetInternalStatus(lEventId)) == Dem_DTCInternalStatus_StoredStatus_Aged)
    {
      continue;                                                                                                                  
    }
#endif

    lGroupId = Dem_Cfg_EventCombinedGroup(lEventId);
    if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
    {
      if (Dem_DTC_TestCombinedGroupProcessed(lGroupId, Dem_DTC_QualificationProcessedCombinedDTCs) == TRUE)                      /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
      {
        continue;                                                                                                                
      }
      else
      {
        lOldDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(lEventId, Dem_DTC_GetDTCStatus(lEventId));
        Dem_Event_ProcessDCYQualificationCombinedDTC_StoredOnly(lEventId, &lArgs);                                               /* SBSW_DEM_POINTER_FORWARD_STACK */
      }
    }
    else
    {
      lOldDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(lEventId, Dem_DTC_GetDTCStatus(lEventId));
      Dem_Event_ProcessDCYQualificationNonCombinedDTC_StoredOnly(lEventId, lMemoryIndex, &lArgs);                                /* SBSW_DEM_POINTER_FORWARD_STACK */
    }

    lArgs.Common.NewDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(lEventId,
                                                                   lArgs.Common.NewDtcStatus);

# if (DEM_CFG_SUPPORT_PERMANENTDTC_IMMEDIATE_VISIBLE == STD_ON)
    if ( (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
      && (Dem_UDSStatus_Test_WIR(lOldDtcStatus) == FALSE)
      && (Dem_UDSStatus_Test_WIR(lArgs.Common.NewDtcStatus) == TRUE))
    {
      Dem_Memory_UpdatePermanentEntryVisibility(lEventId);
    }
# endif

    Dem_Notifications_DtcStatusChanged(lEventId,
                                       lOldDtcStatus,
                                       lArgs.Common.NewDtcStatus,
                                       DEM_NOTIFICATIONS_CYCLE_QUALIFIED);

    if (Dem_UDSStatus_Test_CDTC((uint8)(lOldDtcStatus ^ lArgs.Common.NewDtcStatus)) == TRUE)
    {
      Dem_Notifications_EventDataChanged(lEventId);
    }
  }
}                                                                                                                                /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_DTC_ProcessAgingOnPassed
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ProcessAgingOnPassed(
CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCContext)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  Dem_DTC_CustomizedAgingStart(DTCContext);                                                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#else
# if (DEM_FEATURE_NEED_AGING_TRIGGER_PASSED == STD_ON)
  if (Dem_Cfg_EventAgingTarget(DTCContext->EventId) == 0u)
# endif
  {
# if (DEM_CFG_AGING_00_START_TRIGGER_PASSED == STD_ON)
    if (Dem_DTC_TestDtcMayAge(DTCContext->EventId) == TRUE)
    {
#  if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
      if (DTCContext->GroupId != DEM_CFG_COMBINED_GROUP_INVALID)
      {
        if ( (Dem_UDSStatus_Test_TF(DTCContext->NewDtcStatus) == FALSE)
          && (Dem_UDSStatus_Test_TNCTOC(DTCContext->NewDtcStatus) == FALSE)                                                      
#   if (DEM_CFG_AGING_00_START_TESTS_TFTOC == STD_ON)
          && (Dem_UDSStatus_Test_TFTOC(DTCContext->NewDtcStatus) == FALSE)                                                       
#   endif
          )
        {
          Dem_DTC_AgingStartZeroTarget(DTCContext->EventId, FALSE);
        }
      }
      else
#  endif
      {
#  if (DEM_CFG_AGING_00_START_TESTS_TFTOC == STD_ON)
        if (Dem_UDSStatus_Test_TFTOC(DTCContext->NewDtcStatus) == FALSE)
#  endif
        {
          Dem_DTC_AgingStartZeroTarget(DTCContext->EventId, FALSE);
        }
      }
    }
# endif
  }
# if (DEM_CFG_AGING_START_TRIGGER_PASSED == STD_ON)
  else
  {
    if (Dem_DTC_TestDtcMayAge(DTCContext->EventId) == TRUE)
    {
#  if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
      if (DTCContext->GroupId != DEM_CFG_COMBINED_GROUP_INVALID)
      {
        if ( (Dem_UDSStatus_Test_TF(DTCContext->NewDtcStatus) == FALSE)
          && (Dem_UDSStatus_Test_TNCTOC(DTCContext->NewDtcStatus) == FALSE)                                                      
#   if (DEM_CFG_AGING_START_TESTS_TFTOC == STD_ON)
          && (Dem_UDSStatus_Test_TFTOC(DTCContext->NewDtcStatus) == FALSE)                                                       
#   endif
          )
        {
          Dem_DTC_AgingStartMultiTarget(DTCContext->EventId);
        }
      }
      else
#  endif
      {
#  if (DEM_CFG_AGING_START_TESTS_TFTOC == STD_ON)
        if (Dem_UDSStatus_Test_TFTOC(DTCContext->NewDtcStatus) == FALSE)
#  endif
        {
          Dem_DTC_AgingStartMultiTarget(DTCContext->EventId);
        }
      }
    }
  }
# endif
#endif /* (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON) */
}

#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_GetCombinedGroupUDSStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTC_GetCombinedGroupUDSStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId
  )
{
  return Dem_Cfg_GetCombinedGroupStatus(GroupId);
}
#endif

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) \
 && ((DEM_CFG_AGING_NEXT_TESTS_TNCTOC == STD_ON) || (DEM_CFG_AGING_NEXT_TESTS_TFTOC == STD_ON))
/* ****************************************************************************
 % Dem_DTC_TestStatusForAgingCycle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
  Dem_DTC_TestStatusForAgingCycle(
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DTCStatus
  )
{
  return (boolean)(
# if (DEM_CFG_AGING_NEXT_TESTS_TFTOC == STD_ON)
    (Dem_UDSStatus_Test_TFTOC(DTCStatus) == FALSE)
    &&
# endif
    (Dem_UDSStatus_Test_TNCTOC(DTCStatus) == FALSE));                                                                            
}
#endif

/* ****************************************************************************
 % Dem_DTC_TestGroupAvailable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestGroupAvailable(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  boolean lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON) && (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
  lReturnValue = (boolean)(Dem_EventInternalStatus_TestEventDisconnected(Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(GroupId)) == FALSE);
#else
  lReturnValue = TRUE;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTC_TestGroupAvailableInVariant
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestGroupAvailableInVariant(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  boolean lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_EventInternalStatus_TestAvailableInVariant(Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(GroupId));
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTC_TestGroupSuppression
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestGroupSuppression(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  boolean lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON) && (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
  lReturnValue = Dem_DTCInternalStatus_TestDtcSuppressed(Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(GroupId));
#else
  lReturnValue = FALSE;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTC_ApplyUserControlledWIR
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_ApplyUserControlledWIR(
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DtcStatus,
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  InternalStatus                                                                 /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(InternalStatus)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
  return ((Dem_DTC_UDSStatusType)((DtcStatus) | ((InternalStatus) & DEM_DTCINTERNALSTATUS_USER_CONTROLLED_WIR)));
#else
  return DtcStatus;
#endif
}

#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_CombinedGroupGetFDC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_CombinedGroupGetFDC(
CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId,                                                                       /* PRQA S 3206 */ /* MD_DEM_3206 */
CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter
)
{
  Std_ReturnType lReturnValue;
  sint8 lMaxFdc;
  Dem_Cfg_CombinedGroupIterType lCombinedIter;

  /* In rare cases GroupId is not required */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lReturnValue = E_OK;
  lMaxFdc = -128;

  for (Dem_Cfg_CombinedGroupIterInit(GroupId, &lCombinedIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lSubEventId;
    lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if ((Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)                                                                   
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE))                     
    {
      sint8 lFdc;
      lFdc = -128;
      lReturnValue = Dem_GetFaultDetectionCounter(lSubEventId, &lFdc);                                                           /* SBSW_DEM_POINTER_FORWARD_STACK */
      if ((lReturnValue == E_OK) && (lMaxFdc < lFdc))
      {
        lMaxFdc = lFdc;
      }
    }
    if (lReturnValue != E_OK)
    {
      break;
    }
  }

  if (lReturnValue == E_OK)
  {
    *FaultDetectionCounter = lMaxFdc;                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ( ((DEM_FEATURE_NEED_AGING_TRIGGER_PASSED == STD_ON)\
      || ((DEM_FEATURE_NEED_AGING_TRIGGER_CYCLE == STD_ON) && (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)) )\
      && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 % Dem_DTC_TestDtcMayAge
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcMayAge(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lReturnValue;
  lReturnValue = TRUE;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

# if ((DEM_FEATURE_NEED_HEALING == STD_ON) && (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON))
  {
#  if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    Dem_Cfg_CombinedGroupIndexType lGroupId;
    lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
    if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
    {
      Dem_Cfg_CombinedGroupIterType lGroupIter;
      for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lGroupIter);                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_CombinedGroupIterExists(&lGroupIter) == TRUE;                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_CombinedGroupIterNext(&lGroupIter))                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        Dem_EventIdType lSubEvent;
        lSubEvent = Dem_Cfg_CombinedGroupIterGet(&lGroupIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
        if (Dem_Event_TestEventMayAge(lSubEvent, Dem_Event_GetUDSStatus(lSubEvent)) == FALSE)
        {
          break;
        }
      }
      lReturnValue = !(Dem_Cfg_CombinedGroupIterExists(&lGroupIter));                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
    }
    else
#  endif
    {
      lReturnValue = Dem_Event_TestEventMayAge(EventId, Dem_Event_GetUDSStatus(EventId));
    }
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) && (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_Disconnect_Combined
 *****************************************************************************/
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
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Disconnect_Combined(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  Dem_DTC_InternalStatusType lGroupInternalStatus;

  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  lGroupInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(lGroupId);

  /* Remove pending actions: time debouncing, FDC triggers and queue state  */
  Dem_SatelliteCore_ClearEvent(
    Dem_Cfg_EventSatelliteId(EventId),
    Dem_Cfg_EventSatelliteEventId(EventId));

  if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
  {
    Dem_Event_SetExtendedStatus(EventId,
      Dem_EventInternalStatus_ResetSimilarConditions(
      Dem_Event_GetExtendedStatus(EventId)
      )
      );
  }
  Dem_Event_SetUDSStatus(EventId, 0x00U);

  if (Dem_EventInternalStatus_TestEventDisconnected(lGroupInternalStatus) == FALSE)
  { /* If all Events belonging to a DTC are disconnected, that DTC is disconnected as well */
    /* If all connected events are suppressed or disconnected, the DTC is suppressed as well */
    uint8 lCombinedGroupStatus;
    boolean lDoDisconnect;
    Dem_Cfg_CombinedGroupIterType lCombinedIter;

    lCombinedGroupStatus = 0x00;
    lDoDisconnect = TRUE;

    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_EventIdType lSubEventId;
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      if (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)
      {
        Dem_Event_InternalStatusType lInternalStatus;
        lInternalStatus = Dem_Event_GetInternalStatus(lSubEventId);

        /* If all events are disconnected now, the combined group is set to disconnected */
        lDoDisconnect = (boolean)(lDoDisconnect && (Dem_EventInternalStatus_TestEventDisconnected(lInternalStatus) == TRUE));    

        lCombinedGroupStatus = (uint8)(lCombinedGroupStatus | Dem_Event_GetUDSStatus(lSubEventId));
      }
    }
    if (lDoDisconnect == TRUE)
    {
      lGroupInternalStatus = Dem_EventInternalStatus_SetEventDisconnected(lGroupInternalStatus);
    }

# if ((DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON) && (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON))
    /* If all combined events are tested this cycle and no one is currently test failed */
    if ( (Dem_Cfg_EventReadinessGroup(EventId) != DEM_CFG_READINESS_NONE)
      && (Dem_UDSStatus_Test_TF(lCombinedGroupStatus) == FALSE)                                                                  
      && (Dem_UDSStatus_Test_TNCTOC(lCombinedGroupStatus) == FALSE)                                                              
      )
    {
      for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        Dem_EventIdType lSubEventId;
        lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
        /* If event is available */
        if (Dem_Event_TestEventUnavailable(lSubEventId) == FALSE)
        {
          Dem_DTC_ExtendedStatusType lExtendedStatus;
          lExtendedStatus = Dem_Event_GetExtendedStatus(lSubEventId);
          lExtendedStatus = Dem_DTCInternalStatus_SetExtendedStatus_TPSLC(lExtendedStatus);
          Dem_Event_SetExtendedStatus(lSubEventId, lExtendedStatus);
        }
      }
    }
# endif
    Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, lGroupInternalStatus);
    Dem_DTC_SetCombinedGroupUDSStatus(lGroupId, lCombinedGroupStatus);
  }
}                                                                                                                                /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) && (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_Reconnect_Combined
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Reconnect_Combined(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  Dem_DTC_InternalStatusType lGroupInternalStatus;

  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  lGroupInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(lGroupId);

  Dem_Event_SetUDSStatus(EventId, 0x50U);

  if (Dem_EventInternalStatus_TestEventDisconnected(lGroupInternalStatus) == TRUE)
  {
    uint8 lCombinedGroupStatus;
    Dem_Cfg_CombinedGroupIterType lCombinedIter;

    lCombinedGroupStatus = 0x00;

    /* Reconnecting an event can cause a suppressed DTC to become un-suppressed */
    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_EventIdType lSubEventId;
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      if (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)
      {
        /* Calculate the combined event status - logical 'or' of all connected event status bytes (includes self) */
        lCombinedGroupStatus = (uint8)(lCombinedGroupStatus | Dem_Event_GetUDSStatus(lSubEventId));
      }
    }

    /* Since at least one sub-events is connected now, set the combined group to connected */
    lGroupInternalStatus = Dem_EventInternalStatus_ResetEventDisconnected(lGroupInternalStatus);

    Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, lGroupInternalStatus);
    Dem_DTC_SetCombinedGroupUDSStatus(lGroupId, lCombinedGroupStatus);
  }
  else
  {
    Dem_DTC_SetCombinedGroupUDSStatus(lGroupId, Dem_DTC_CalculateCombineGroupUdsStatus(lGroupId));
  }


}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
 % Dem_DTC_AgingStartZeroTarget
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_AgingStartZeroTarget(
CONST(Dem_EventIdType, AUTOMATIC)  EventId,
CONST(boolean, AUTOMATIC)  SuppressNotifications
)
{
  Dem_DTC_InternalStatusType lInternalStatus;

  lInternalStatus = Dem_DTC_GetInternalStatus(EventId);
  if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) < Dem_DTCInternalStatus_StoredStatus_Aging)
  {
    if (Dem_Cfg_EventSupportAging(EventId) == TRUE)
    {
      Dem_Cfg_MemoryIndexType  lMemoryIndex;
      
      if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
      {
        Dem_DTC_ClearOBDFreezeFrame(EventId);
      }

      lMemoryIndex = DEM_MEM_INVALID_MEMORY_INDEX;

      if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) == Dem_DTCInternalStatus_StoredStatus_Active)
      {
        lMemoryIndex = Dem_Memory_FindMemoryIndex_StoredEvent(EventId);
      }
      Dem_DTC_Aged(EventId, lMemoryIndex, SuppressNotifications);
    }
  }
}                                                                                                                                /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */
#endif /* DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF */

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
 % Dem_DTC_AgingStartMultiTarget
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_AgingStartMultiTarget(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
# if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  if (Dem_DTC_GetAgingStatus(EventId) == Dem_DTC_AgingStatusNone)
  {
    /* Age all events, irrespective of the memory entry */
    Dem_DTC_StartAgingWithoutMemoryEntryMultiTarget(EventId);
  }
# else
  {
    Dem_DTC_InternalStatusType lInternalStatus;
    lInternalStatus = Dem_DTC_GetInternalStatus(EventId);

    if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) < Dem_DTCInternalStatus_StoredStatus_Aging)
    {
      /* Age only events with memory entry */
      Dem_DTC_StartAgingWithMemoryEntryMultiTarget(EventId);
    }
  }
# endif
}
#endif

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
/* ****************************************************************************
 %  Dem_DTC_CustomizedAging
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
 Dem_DTC_CustomizedAging(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  if (Dem_Cfg_EventSupportAging(EventId) == TRUE)
  {
    uint8 lEventStatus;
    Dem_DTC_InternalStatusType lInternalStatus;

    lEventStatus = Dem_Event_GetUDSStatus(EventId);
    lInternalStatus = Dem_Event_GetInternalStatus(EventId);

    if ( (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) != Dem_DTCInternalStatus_StoredStatus_None)
      && (Dem_UDSStatus_Test_TF(lEventStatus) == FALSE) )                                                                        
    { /* Stored, not active event */
      Dem_Cfg_MemoryIndexType lMemoryIndex;
      Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
      Dem_UdsStatusByteType lOldEventStatus;
      Dem_UdsStatusByteType lOldExternalEventStatus;
      Dem_DTC_UDSStatusType lPreconfirmedStatus;

      lMemoryIndex = Dem_Memory_FindMemoryIndex_StoredEvent(EventId);
      lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);

      /* Update UDS status byte */
      /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
      Dem_EnterCritical_DiagMonitor();

      lEventStatus = Dem_Event_GetUDSStatus(EventId);
      lOldEventStatus = lEventStatus;
      lOldExternalEventStatus = Dem_Event_GetExternalUDSStatus(EventId, lOldEventStatus);

      lEventStatus = Dem_UDSStatus_Reset_CDTC(lEventStatus);

      Dem_Event_SetUDSStatus(EventId, lEventStatus);

      /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
      Dem_LeaveCritical_DiagMonitor();

      if (Dem_UDSStatus_IsNvRelevantStatusChange(lOldEventStatus, lEventStatus) == TRUE)
      {
        Dem_Nvm_SetStatusBlockChanged();
      }

      /* Update SI.30 status byte */
      lPreconfirmedStatus = Dem_MemoryEntry_GetPreConfirmedStatus(lMemoryEntryId);
      lPreconfirmedStatus = DEM_DTC_SET_PC_STATUS_ADTC(lPreconfirmedStatus);
      lPreconfirmedStatus = DEM_DTC_RESET_PC_STATUS_TFSLC(lPreconfirmedStatus);
      Dem_MemoryEntry_SetPreConfirmedStatus(lMemoryEntryId, lPreconfirmedStatus);

      Dem_Notifications_EventStatusChanged(EventId,
                                           lOldExternalEventStatus,
                                           Dem_Event_GetExternalUDSStatus(EventId, lEventStatus));
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
/* ****************************************************************************
 % Dem_DTC_CustomizedAgingStart
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CustomizedAgingStart(
CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
)
{
  Dem_DTC_InternalStatusType lInternalStatus;

  lInternalStatus = Dem_Event_GetInternalStatus(DTCContext->EventId);
  if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) != Dem_DTCInternalStatus_StoredStatus_None)
  {
    boolean lIsModified;
    boolean lEventAged;
    Dem_DTC_UDSStatusType lOldPreconfirmedStatus;
    Dem_DTC_UDSStatusType lNewPreconfirmedStatus;
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;

    lEventAged = FALSE;

    lMemoryIndex = Dem_Memory_FindMemoryIndex_StoredEvent(DTCContext->EventId);
    lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);

    lOldPreconfirmedStatus = Dem_MemoryEntry_GetPreConfirmedStatus(lMemoryEntryId);
    lNewPreconfirmedStatus = DEM_DTC_RESET_PC_STATUS_UDTC(lOldPreconfirmedStatus);
    Dem_MemoryEntry_SetPreConfirmedStatus(lMemoryEntryId, lNewPreconfirmedStatus);

    lIsModified = (boolean)(lOldPreconfirmedStatus != lNewPreconfirmedStatus);

    if ( (DEM_DTC_TEST_PC_STATUS_UDTCTOC(lOldPreconfirmedStatus) == FALSE)
      && ((DTCContext->DtcEffects & DEM_CFG_TRIGGER_FIRSTTHISCYCLE) != 0x00U) )
    { /* OCC2 if preconfirmed level had not been reached */
      if (Dem_MemoryEntry_GetOccurrenceCounter2(lMemoryEntryId) < 0xffU)
      {
        Dem_MemoryEntry_SetOccurrenceCounter2(lMemoryEntryId, Dem_MemoryEntry_GetOccurrenceCounter2(lMemoryEntryId) + 1u);
        lIsModified = TRUE;
      }

      /* OCC7 once per cycle, and also consider FDC preconfirmed */
      if (Dem_MemoryEntry_GetOccurrenceCounter7(lMemoryEntryId) < 0xffU)
      {
        Dem_MemoryEntry_SetOccurrenceCounter7(lMemoryEntryId, Dem_MemoryEntry_GetOccurrenceCounter7(lMemoryEntryId) + 1u);
        lIsModified = TRUE;
      }

      /* Start aging at event passed */
      if (Dem_MemoryEntry_GetOccurrenceCounter2(lMemoryEntryId) == Dem_Cfg_EventAgingTarget(DTCContext->EventId))
      {
         Dem_DTC_CustomizedAging(DTCContext->EventId);
        lIsModified = TRUE;
        lEventAged = TRUE;
      }
    }

    if (lIsModified == TRUE)
    {
      if ((Dem_Cfg_EventSupportImmediateNv(DTCContext->EventId) == TRUE)
        && (lEventAged == TRUE)
        )
      {
        Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
      }
      else
      {
        Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
      }
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON */


/* ****************************************************************************
 % Dem_DTC_Passed_ProcessDTCEffects_TPSLC
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Passed_ProcessDTCEffects_TPSLC(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC)  DTCContext
)
{
#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
  /* If event combination is supported and event is in a combined group */
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (DTCContext->GroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    /* If all combined events are tested this cycle and no one is currently test failed */
    if ((Dem_UDSStatus_Test_TF(DTCContext->NewDtcStatus) == FALSE)
      && (Dem_UDSStatus_Test_TNCTOC(DTCContext->NewDtcStatus) == FALSE)                                                          
      )
    {
      Dem_DTC_ExtendedStatusType lExtendedStatus;
      lExtendedStatus= Dem_Event_GetExtendedStatus(DTCContext->EventId);
      /* If TestPassedSinceLastClear is not set already */
      if (Dem_DTCInternalStatus_TestExtendedStatus_TPSLC(lExtendedStatus) == FALSE)
      {
        Dem_Cfg_CombinedGroupIterType lCombinedIter;

        /* Set all events of combined group to TestPassedSinceLastClear */
        for (Dem_Cfg_CombinedGroupIterInit(DTCContext->GroupId, &lCombinedIter);                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
             Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
             Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          Dem_EventIdType lSubEventId;
          lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
          /* If event is available */
          if (Dem_Event_TestEventUnavailable(lSubEventId) == FALSE)
          {
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
            Dem_EnterCritical_DiagMonitor();
            lExtendedStatus = Dem_Event_GetExtendedStatus(lSubEventId);
            lExtendedStatus = Dem_DTCInternalStatus_SetExtendedStatus_TPSLC(lExtendedStatus);
            Dem_Event_SetExtendedStatus(lSubEventId, lExtendedStatus);

            Dem_LeaveCritical_DiagMonitor();
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
          }
        }

        /* Check if monitor is complete for event readiness group */
        Dem_Data_Calc_Pid01_MonitorCompleted((Dem_Cfg_EventReadinessGroup(DTCContext->EventId)));
      }
    }
  }
  else
# endif
  {
    /* Otherwise*/
    Dem_DTC_ExtendedStatusType lExtendedStatus;
    lExtendedStatus = Dem_Event_GetExtendedStatus(DTCContext->EventId);
    if (Dem_DTCInternalStatus_TestExtendedStatus_TPSLC(lExtendedStatus) == FALSE)
    {
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
      Dem_EnterCritical_DiagMonitor();

      /* Set extended status of event to TestPassedSinceLastClear */
      lExtendedStatus = Dem_Event_GetExtendedStatus(DTCContext->EventId);
      lExtendedStatus = Dem_DTCInternalStatus_SetExtendedStatus_TPSLC(lExtendedStatus);
      Dem_Event_SetExtendedStatus(DTCContext->EventId, lExtendedStatus);

      Dem_LeaveCritical_DiagMonitor();
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

      /* Check if monitor is complete for event readiness group */
      Dem_Data_Calc_Pid01_MonitorCompleted(Dem_Cfg_EventReadinessGroup(DTCContext->EventId));
    }
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCContext)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_DTC_ForEachCombinedSubEvent
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ForEachCombinedSubEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Util_ForEachCombinedFuncType, AUTOMATIC)  FuncPtr,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  )
{
#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  Dem_DTC_UDSStatusType lOldCombinedGroupUdsStatus;

  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    /* DTC has combined group */
    Dem_DTC_UDSStatusType lDtcStatus;
    Dem_Cfg_CombinedGroupIterType lCombinedIter;
    Dem_EventIdType lSubEventId;

    lDtcStatus = 0u; /* neutral value */
    lOldCombinedGroupUdsStatus = Dem_DTC_GetCombinedGroupUDSStatus(lGroupId);

    ArgPtr->Common.OldDtcStatus = lOldCombinedGroupUdsStatus;                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

    /* Iterate through all active sub-events */
    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */

      if ( (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)                                                                
        && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE) )                  
      {
        (*FuncPtr)(lSubEventId, ArgPtr);                                                                                         /* SBSW_DEM_CALL_FOREACH_FUNCPTR */
        /* Combined event status created by ORing the status bits or all sub-events */
        lDtcStatus = (Dem_DTC_UDSStatusType)(lDtcStatus | Dem_Event_GetUDSStatus(lSubEventId));
      }
    }
    Dem_DTC_SetCombinedGroupUDSStatus(lGroupId, lDtcStatus);

    ArgPtr->Common.NewDtcStatus = lDtcStatus;                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  else
#endif
  {
    /* EventId is not a combined event */

    ArgPtr->Common.OldDtcStatus = Dem_Event_GetUDSStatus(EventId);                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    (*FuncPtr)(EventId, ArgPtr);                                                                                                 /* SBSW_DEM_CALL_FOREACH_FUNCPTR */
    ArgPtr->Common.NewDtcStatus = Dem_Event_GetUDSStatus(EventId);                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_InitGroupInternalStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InitGroupInternalStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
# if (DEM_FEATURE_NEED_EVENTAVAILABLE_DEFAULT == STD_ON)
  Dem_Cfg_CombinedGroupIterType lSubEventIter;
  Dem_Event_InternalStatusType lInternalStatus;

  lInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(GroupId);
  lInternalStatus = Dem_EventInternalStatus_SetEventDisconnected(lInternalStatus);

  for (Dem_Cfg_CombinedGroupIterInit(GroupId, &lSubEventIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_CombinedGroupIterExists(&lSubEventIter) == TRUE;                                                                  /* PRQA S 2990 */ /* MD_DEM_2990 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_CombinedGroupIterNext(&lSubEventIter))                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    if (Dem_Cfg_EventAvailableByDefault(Dem_Cfg_CombinedGroupIterGet(&lSubEventIter)) == TRUE)                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      lInternalStatus = Dem_EventInternalStatus_ResetEventDisconnected(lInternalStatus);
      break;
    }
  }
  Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(GroupId, lInternalStatus);
# endif
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
/* ****************************************************************************
 % Dem_DTC_CycleQualifyDcy_AllDtc
 *****************************************************************************/
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
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CycleQualifyDcy_AllDtc(
  void
)
{
  Dem_EventIdType lEventId;

  for (lEventId = Dem_Cfg_GlobalPrimaryFirst(); lEventId <= Dem_Cfg_GlobalPrimaryLast(); lEventId++)
  {
    uint8 lOldDtcStatus;
    Dem_DTC_ForEachCombinedArgType lArgs;

    /* Skip non OBD Events */
    if (Dem_Cfg_EventObdRelated(lEventId) == FALSE)
    {
      continue;                                                                                                                  
    }

# if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
    /* Only process master events (subevents are handled with the master) */
    if (lEventId != Dem_Cfg_GetMasterEvent(lEventId))
    {
      continue;                                                                                                                  
    }
# endif

    lOldDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(lEventId, Dem_DTC_GetDTCStatus(lEventId));

    /* Process the DTC status qualification of the stored event or combination group */
    Dem_DTC_ForEachCombinedSubEvent(lEventId, Dem_Event_CycleQualifyDcy, &lArgs);                                                /* SBSW_DEM_CALL_FOREACH_COMBINED_EVENT */

    lArgs.Common.NewDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(lEventId, lArgs.Common.NewDtcStatus);

    if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
    {
      /* When DEM_CFG_SUPPORT_TYPE2_COMBINATION == ON, OBDII freeze frame type can only be type-1 */
# if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)

      if ((Dem_UDSStatus_Test_CDTC(lOldDtcStatus) == FALSE)
        && (Dem_UDSStatus_Test_CDTC(lArgs.Common.NewDtcStatus) == TRUE))
      {
        Dem_MemObdFreezeFrame_SetFFOfEventVisible(lEventId);
        Dem_Mem_FreezeFrameIndexMode02 = Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame();
      }
# endif

# if (DEM_CFG_SUPPORT_PERMANENTDTC_IMMEDIATE_VISIBLE == STD_ON)
      if ((Dem_UDSStatus_Test_WIR(lOldDtcStatus) == FALSE)
        && (Dem_UDSStatus_Test_WIR(lArgs.Common.NewDtcStatus) == TRUE))
      {
        Dem_Memory_UpdatePermanentEntryVisibility(lEventId);
      }
#endif
    }

    Dem_Notifications_DtcStatusChanged(lEventId,
                                       lOldDtcStatus,
                                       lArgs.Common.NewDtcStatus,
                                       DEM_NOTIFICATIONS_CYCLE_QUALIFIED);

    if (Dem_UDSStatus_Test_CDTC((uint8)(lOldDtcStatus ^ lArgs.Common.NewDtcStatus)) == TRUE)
    {
      Dem_Notifications_EventDataChanged(lEventId);
    }

    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_STATUS),
                                DEM_NVM_BLOCKSTATE_DIRTY);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON) \
    && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF) \
    && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_OFF)
/* ****************************************************************************
 % Dem_DTC_CycleQualifyDcy_StoredOnly
 *****************************************************************************/
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
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CycleQualifyDcy_StoredOnly(
  void
  )
{
  Dem_Memory_AllocMemEntriesIterType lStoredEventsIter;

  for (Dem_Memory_AllocMemEntriesChrono_IterInit(DEM_CFG_MEMORYID_PRIMARY, &lStoredEventsIter);                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_AllocMemEntriesChrono_IterExists(&lStoredEventsIter) == TRUE;                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_AllocMemEntriesChrono_IterNext(&lStoredEventsIter))                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
    Dem_EventIdType lEventId;
    uint8 lOldDtcStatus;
    Dem_DTC_ForEachCombinedArgType lArgs;

    lMemoryIndex = Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex(&lStoredEventsIter);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);
    lEventId = Dem_MemoryEntry_GetEventId(lMemoryEntryId);

    if (Dem_Event_TestValidHandle(lEventId) == FALSE)
    {
      Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
      continue;                                                                                                                  
    }

    /* Skip non OBD Events */
    if (Dem_Cfg_EventObdRelated(lEventId) == FALSE)
    {
      continue;                                                                                                                  
    }

# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
    /* Skip aged Events */
    if (Dem_DTCInternalStatus_GetStoredStatus(Dem_DTC_GetInternalStatus(lEventId)) == Dem_DTCInternalStatus_StoredStatus_Aged)
    {
      continue;                                                                                                                  
    }
#endif

    lOldDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(lEventId, Dem_DTC_GetDTCStatus(lEventId));

    /* Process the DTC status qualification of the stored event or combination group */
    Dem_DTC_ForEachCombinedSubEvent(lEventId, Dem_Event_CycleQualifyDcy, &lArgs);                                                /* SBSW_DEM_CALL_FOREACH_COMBINED_EVENT */

    Dem_Event_UpdateQualificationStatus(lEventId, lMemoryIndex);

    lArgs.Common.NewDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(lEventId, lArgs.Common.NewDtcStatus);

    if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
    {
# if (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
      if ((Dem_UDSStatus_Test_CDTC(lOldDtcStatus) == FALSE)
        && (Dem_UDSStatus_Test_CDTC(lArgs.Common.NewDtcStatus) == TRUE))
      {
        Dem_MemObdFreezeFrame_SetFFOfEventVisible(lEventId);
        Dem_Mem_FreezeFrameIndexMode02 = Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame();
      }
#endif
# if (DEM_CFG_SUPPORT_PERMANENTDTC_IMMEDIATE_VISIBLE == STD_ON)
      if ((Dem_UDSStatus_Test_WIR(lOldDtcStatus) == FALSE)
        && (Dem_UDSStatus_Test_WIR(lArgs.Common.NewDtcStatus) == TRUE))
      {
        Dem_Memory_UpdatePermanentEntryVisibility(lEventId);
      }
#endif
    }
    Dem_Notifications_DtcStatusChanged(lEventId,
                                       lOldDtcStatus,
                                       lArgs.Common.NewDtcStatus,
                                       DEM_NOTIFICATIONS_CYCLE_QUALIFIED);
    if (Dem_UDSStatus_Test_CDTC((uint8)(lOldDtcStatus ^ lArgs.Common.NewDtcStatus)) == TRUE)
    {
      Dem_Notifications_EventDataChanged(lEventId);
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_SetDtcSuppression
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetDtcSuppression(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_InternalStatusType lInternalStatus;
# if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;

  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();
    lInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(lGroupId);
    lInternalStatus = Dem_DTCInternalStatus_SetDtcSuppressed(lInternalStatus);
    Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, lInternalStatus);

    Dem_LeaveCritical_DiagMonitor();
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
  }
  else
# endif
  {
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();
    lInternalStatus = Dem_Event_GetInternalStatus(EventId);
    lInternalStatus = Dem_DTCInternalStatus_SetDtcSuppressed(lInternalStatus);
    Dem_Event_SetInternalStatus(EventId, lInternalStatus);

    Dem_LeaveCritical_DiagMonitor();
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON) */

/* ****************************************************************************
 % Dem_DTC_EventEntryReInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_EventEntryReInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  Dem_DTC_InternalStatusType lInternalStatus;
  Dem_MemoryEntry_InitializeEntry(Dem_MemoryEntry_GetId(MemoryIndex));

/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
  Dem_EnterCritical_DiagMonitor();
  lInternalStatus = Dem_DTC_GetInternalStatus(EventId);
  lInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lInternalStatus, Dem_DTCInternalStatus_StoredStatus_Active);
  Dem_DTC_SetInternalStatus(EventId,lInternalStatus);
  Dem_LeaveCritical_DiagMonitor();
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

  if (Dem_Cfg_EventSupportImmediateNv(EventId) == TRUE)
  {
    Dem_Nvm_SetEventMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
  }
  else
  {
    Dem_Nvm_SetEventMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DTC_EventCreateMemory
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_DTC_EventCreateMemory(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Cfg_MemoryIndexType lMemoryIndex;

  lMemoryIndex = Dem_Memory_AllocateIndex(EventId);
  if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
  { /* Created new entry */
    Dem_DTC_InternalStatusType lInternalStatus;
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();
    lInternalStatus = Dem_DTC_GetInternalStatus(EventId);
    lInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lInternalStatus, Dem_DTCInternalStatus_StoredStatus_Active);
    Dem_DTC_SetInternalStatus(EventId, lInternalStatus);
    Dem_LeaveCritical_DiagMonitor();
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

    if (Dem_Cfg_EventSupportImmediateNv(EventId) == TRUE)
    {
      Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
    }
    else
    {
      Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
    }
  }
  return lMemoryIndex;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if ((DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) && (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF))
/* ****************************************************************************
 % Dem_DTC_StartAgingWithMemoryEntryMultiTarget
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_StartAgingWithMemoryEntryMultiTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_InternalStatusType lInternalStatus;
  Dem_Cfg_MemoryIndexType  lMemoryIndex;

  lInternalStatus = Dem_DTC_GetInternalStatus(EventId);
  lMemoryIndex = DEM_MEM_INVALID_MEMORY_INDEX;

# if (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)
  if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) == Dem_DTCInternalStatus_StoredStatus_None)
  {
    /* If necessary allocate an aging counter */
    if (Dem_UDSStatus_Test_CDTC(Dem_DTC_RetrieveStatus(EventId)) == TRUE)
    {
      lMemoryIndex = Dem_Memory_AllocateIndexAging(EventId);
    }
  }
  else
# endif
  if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) == Dem_DTCInternalStatus_StoredStatus_Active)
  {
    lMemoryIndex = Dem_Memory_FindMemoryIndex_StoredEvent(EventId);
  }
  else
  {
    /* MISRA */
  }

  if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
  { /* Start Aging */
    uint16 lAgingCounter;
    Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
    lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);

    Dem_Internal_AssertContinue((Dem_DTC_GetAgingCounter(EventId, lMemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID),\
      DEM_E_INCONSISTENT_STATE)

    /* Initialize the aging target of the memory entry */
    lAgingCounter = Dem_OperationCycle_GetCycleCounter(Dem_Cfg_EventAgingCycle(EventId));
    lAgingCounter = Dem_OperationCycle_AddCycleCount(lAgingCounter, Dem_Cfg_EventAgingTarget(EventId));
    Dem_DTC_SetAgingCounter(EventId, lMemoryIndex, lAgingCounter);

# if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
    if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
    {
      /* For WWH-OBD, also start the event's aging timer */
      if (Dem_Cfg_EventSupportAging(EventId) == TRUE)
      {
        uint32 lAgingTimer;

        lAgingTimer = Dem_Mem_GetCumulativeEngRuntime();
        lAgingTimer = Dem_Esm_AddAgingTime(lAgingTimer, DEM_ESM_AGINGTIME_200h);
        Dem_MemoryEntry_SetAgingTimer(lMemoryEntryId, lAgingTimer);
        Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
      }
    }
# endif

    /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();
    lInternalStatus = Dem_DTC_GetInternalStatus(EventId);
    /* In critical section 'DiagMonitor', set the events stored status to 'AGING' */
    lInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lInternalStatus, Dem_DTCInternalStatus_StoredStatus_Aging);
    Dem_DTC_SetInternalStatus(EventId, lInternalStatus);
    Dem_LeaveCritical_DiagMonitor();
    /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) && (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON))
/* ****************************************************************************
 % Dem_DTC_StartAgingWithoutMemoryEntryMultiTarget
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_StartAgingWithoutMemoryEntryMultiTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_InternalStatusType lInternalStatus;

  lInternalStatus = Dem_DTC_GetInternalStatus(EventId);

  if ((Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) == Dem_DTCInternalStatus_StoredStatus_Active)
     || (Dem_UDSStatus_Test_CDTC(Dem_DTC_RetrieveStatus(EventId)) == TRUE))                                                      
  {
      /* Start Aging, initialize the aging target of the memory entry */
    uint16 lAgingCounter;
    lAgingCounter = Dem_OperationCycle_GetCycleCounter(Dem_Cfg_EventAgingCycle(EventId));
    lAgingCounter = Dem_OperationCycle_AddCycleCount(lAgingCounter, Dem_Cfg_EventAgingTarget(EventId));
    Dem_DTC_SetAgingCounter(EventId, DEM_MEM_INVALID_MEMORY_INDEX, lAgingCounter);

    /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();
    lInternalStatus = Dem_DTC_GetInternalStatus(EventId);

    if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) == Dem_DTCInternalStatus_StoredStatus_Active)
    {
      /* In critical section 'DiagMonitor', set the events stored status to 'AGING' */
      lInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lInternalStatus, Dem_DTCInternalStatus_StoredStatus_Aging);
    }

    Dem_DTC_SetInternalStatus(EventId, lInternalStatus);
    Dem_LeaveCritical_DiagMonitor();
    /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 % Dem_DTC_IncrementAgedCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_IncrementAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  if (Dem_Cfg_EventSupportAgedCounter(EventId) == TRUE)
  {
    uint8 lAgedCounter;
    lAgedCounter = Dem_DTC_GetAgedCounter(EventId);
    if (lAgedCounter < DEM_DTC_AGED_COUNTER_MAX_VALUE)
    {
      Dem_DTC_SetAgedCounter(EventId, lAgedCounter + 1u);
      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_AGINGDATA),
        DEM_NVM_BLOCKSTATE_DIRTY);
    }
  }
}
#endif

/* ****************************************************************************
 % Dem_DTC_FreeEventAgingOnly
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_FreeEventAgingOnly(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
# if (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)
  Dem_Event_InternalStatusType lInternalStatus;
  Dem_Memory_FreeEvent(MemoryIndex, EventId);
  /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
  Dem_EnterCritical_DiagMonitor();
  lInternalStatus = Dem_DTC_GetInternalStatus(EventId);
  /* In critical section 'DiagMonitor', set the events stored status to 'AGING' */
  lInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lInternalStatus, Dem_DTCInternalStatus_StoredStatus_None);
  Dem_DTC_SetInternalStatus(EventId, lInternalStatus);
  Dem_LeaveCritical_DiagMonitor();
  /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
  Dem_Nvm_SetEventMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
# endif
#endif
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}

#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 % Dem_DTC_ResetAgedCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_ResetAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  if (Dem_Cfg_EventSupportAgedCounter(EventId) == TRUE)
  {
    if (Dem_DTC_GetAgedCounter(EventId) != DEM_DTC_AGED_COUNTER_INIT_VALUE)
    {
      Dem_DTC_SetAgedCounter(EventId, DEM_DTC_AGED_COUNTER_INIT_VALUE);
      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_AGINGDATA),
        DEM_NVM_BLOCKSTATE_DIRTY);
    }
  }
}
#endif

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) && ((DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON) || (DEM_CFG_STORAGE_AT_FDC == STD_ON))
/* ****************************************************************************
 % Dem_DTC_CalcFdcUpdateFlags
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_StorageTriggerType, DEM_CODE)
Dem_DTC_CalcFdcUpdateFlags(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Cfg_StorageTriggerType lUpdateFlags;

#if (DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON)
#  if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
#  endif

  lUpdateFlags = (Dem_Cfg_StorageTriggerType)DEM_CFG_TRIGGER_FDC_FIRST_IN_CYCLE;
#  if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)

  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_Cfg_CombinedGroupIterType lCombinedIter;
    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_EventIdType lSubEventId;
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      if (Dem_DTCInternalStatus_TestFdcToc(Dem_Event_GetInternalStatus(lSubEventId)) == TRUE)
      {
        lUpdateFlags = (Dem_Cfg_StorageTriggerType)DEM_CFG_TRIGGER_FDC;
        break;
      }
    }
  }
  else
#  endif /* DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON */
  {
    if (Dem_DTCInternalStatus_TestFdcToc(Dem_Event_GetInternalStatus(EventId)) == TRUE)
    {
      lUpdateFlags = (Dem_Cfg_StorageTriggerType)DEM_CFG_TRIGGER_FDC;
    }
  }
# else /* (DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON) */
  lUpdateFlags = (Dem_Cfg_StorageTriggerType)DEM_CFG_TRIGGER_FDC;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif
  return lUpdateFlags;
}
#endif

/* ****************************************************************************
 % Dem_DTC_TestStoredStatusOnDtcRetrieval
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestStoredStatusOnDtcRetrieval(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
  return Dem_DTC_TestStoredStatus_Type2(EventId);
#else
  return Dem_DTC_TestStoredStatus(EventId);
#endif
}

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_EventCombinationOnStorage_Cleared
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_EventCombinationOnStorage_Cleared(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  boolean lReturnValue;
  Dem_Cfg_CombinedGroupIterType lGroupIter;
# if (DEM_CFG_NOTIFY_CLEAR_ALLOWED == STD_ON)
  boolean lClearAllowed;
# endif
  lReturnValue = FALSE;

# if (DEM_CFG_NOTIFY_CLEAR_ALLOWED == STD_ON)
  lClearAllowed = TRUE;

  for (Dem_Cfg_CombinedGroupIterInit(Dem_Cfg_EventCombinedGroup(EventId), &lGroupIter);                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_CombinedGroupIterExists(&lGroupIter) == TRUE;                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_CombinedGroupIterNext(&lGroupIter))                                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lSubEventId;
    lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lGroupIter);                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
    if (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)
    {
      if ((Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE)
        && (Dem_ClearTask_ClearEventAllowed(lSubEventId) == FALSE))                                                              /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
      {
        lClearAllowed = FALSE;
        break;
      }
    }
  }
  if (lClearAllowed == TRUE)
# endif
  {
    Dem_DTC_Cleared_Internal(EventId);
    lReturnValue = TRUE;
  }
  /* Always call init monitor callbacks */
  if (Dem_Cfg_EventCombinedGroup(EventId) != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    for (Dem_Cfg_CombinedGroupIterInit(Dem_Cfg_EventCombinedGroup(EventId), &lGroupIter);                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterExists(&lGroupIter) == TRUE;                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterNext(&lGroupIter))                                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_EventIdType lSubEventId;
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lGroupIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
      if (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)
      {
        if (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE)
        {
          Dem_Notifications_InitMonitorForEvent(lSubEventId, DEM_INIT_MONITOR_CLEAR);
        }
      }
    }
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_EventCombinationOnRetrieval_Cleared
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_EventCombinationOnRetrieval_Cleared(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  boolean lReturnValue;
  Dem_Cfg_CombinedGroupIterType lGroupIter;
  lReturnValue = FALSE;

  for (Dem_Cfg_CombinedGroupIterInit(Dem_Cfg_EventCombinedGroup(EventId), &lGroupIter);                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_CombinedGroupIterExists(&lGroupIter) == TRUE;                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_CombinedGroupIterNext(&lGroupIter))                                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lSubEventId;
    lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lGroupIter);                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
    if (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)
    {
      if (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE)
      {
        if(Dem_Event_ProcessCleared(lSubEventId) == TRUE)
        {
          lReturnValue = TRUE;
        }
      }
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_DTC_Public
 * \{
 */


 /* ****************************************************************************
 % Dem_DTC_InvokeInitMonitorCallbacks
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InvokeInitMonitorCallbacks(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  Dem_Cfg_CombinedGroupIndexType lGroupId;

  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    /* DTC has combined group */
    Dem_Cfg_CombinedGroupIterType lCombinedIter;
    Dem_EventIdType lSubEventId;

    /* Iterate through all active sub-events */
    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */

      if ((Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)                                                               /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
        && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE))
      {
        /* Call Init Monitor Callbacks */
        Dem_Notifications_InitMonitorForEvent(lSubEventId, DEM_INIT_MONITOR_RESTART);
      }
    } 
  }
  else
  {
    /* Call Init Monitor for Event Callbacks */
    Dem_Notifications_InitMonitorForEvent(EventId, DEM_INIT_MONITOR_RESTART);
  }

  /* Call Init Monitor for function Callbacks */
  Dem_Notifications_InitMonitorForFunction(EventId);
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

 /* ****************************************************************************
 % Dem_DTC_ResetFaultPendingCounter
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_ResetFaultPendingCounter(
  Dem_EventIdType EventId
)
{
  if (Dem_DTC_IsMemIndependentFaultPendingCounterEnabled() == TRUE)
  {
    Dem_Cfg_FaultPendingCounterIndexOfEventTableType lFailedCounterIndex;

    lFailedCounterIndex = Dem_Cfg_GetFaultPendingCounterIndexOfEventTable(EventId);

    if (lFailedCounterIndex != DEM_CFG_FAULTPENDINGCOUNTER_INDEX_INVALID)
    { /* memory independent fault pending counter supported for event */
      Dem_DTC_SetFaultPendingCounter(lFailedCounterIndex, 0);

      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_CYCLECOUNTERDATA),
        DEM_NVM_BLOCKSTATE_DIRTY);
    }
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}

 /* ****************************************************************************
 % Dem_DTC_GetFailedCycleCounter
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTC_GetFailedCycleCounter(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_Cfg_FailedCycleCounterIndexOfEventTableType FailedCycleCounterIndex
)
{
  uint8 lFailedCycleCounter;

#if (DEM_CFG_DATA_FAILED_CYCLES == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_ON)
  {
    lFailedCycleCounter = Dem_Cfg_CycleCounterData.FailedCycleCounter[FailedCycleCounterIndex];
  }
#else
  {
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(FailedCycleCounterIndex)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
      Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
    lFailedCycleCounter = 0;
  }
#endif
  return lFailedCycleCounter;
}


 /* ****************************************************************************
 % Dem_DTC_GetFaultPendingCounter
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTC_GetFaultPendingCounter(
  Dem_Cfg_FaultPendingCounterIndexOfEventTableType FaultPendingCounterIndex
)
{
  uint8 lFaultPendingCounter;

#if (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_ON)
  {
    lFaultPendingCounter = Dem_Cfg_CycleCounterData.FaultPendingCounter[FaultPendingCounterIndex];
  }
#else
  {
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(FaultPendingCounterIndex)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
      Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
    lFaultPendingCounter = 0;
  }
#endif
  return lFaultPendingCounter;
}

 /* ****************************************************************************
 % Dem_DTC_UpdateMemIndependentCycleCounter
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *

 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_UpdateMemIndependentCycleCounter(
  Dem_EventIdType  EventId,
  Dem_Cfg_StorageTriggerType UpdateFlags
)
{
  if ((UpdateFlags & DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE) != 0u)
  {
    Dem_DTC_IncrementFailedCycleCounter(EventId);

    Dem_DTC_IncrementFaultPendingCounter(EventId);
  }
}

/* ****************************************************************************
 % Dem_DTC_RetryStorage
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */

DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_RetryStorage(
    Dem_EventIdType EventId
  )
{
  boolean lReturn;
  lReturn = (boolean)((Dem_DTC_isRetryStorageEnabled() == TRUE)
    && (Dem_DTCInternalStatus_GetStoredStatus(Dem_DTC_GetInternalStatus(EventId)) == Dem_DTCInternalStatus_StoredStatus_None));  

  return lReturn;
}

/* ****************************************************************************
 % Dem_DTC_Cleared_Internal
 *****************************************************************************/
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
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_Cleared_Internal(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  Dem_DTC_ForEachCombinedArgType lArgs;
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
#endif

  {
    Dem_DTC_InternalStatusType lInternalStatus;
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
    {
      lInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(lGroupId);
    }
    else
#endif
    {
      lInternalStatus = Dem_Event_GetInternalStatus(EventId);
    }

    if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) != Dem_DTCInternalStatus_StoredStatus_None)
    {
      Dem_Cfg_MemoryIndexType lMemoryIndex;
      lMemoryIndex = Dem_Memory_FindMemoryIndex_StoredEvent(EventId);
      /* Remove the event from the memory */
      Dem_Memory_FreeEvent(lMemoryIndex, EventId);
      Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYCLEAREDIMMEDIATE);
    }

    Dem_Memory_TimeSeries_InvalidateEntryOfEvent(EventId, DEM_NVM_BLOCKSTATE_DIRTYCLEAREDIMMEDIATE);

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
    {
      /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
      Dem_EnterCritical_DiagMonitor();

      Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, Dem_DTCInternalStatus_SetStoredStatus(lInternalStatus, Dem_DTCInternalStatus_StoredStatus_None));

      Dem_LeaveCritical_DiagMonitor();
      /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

    }
#endif
  }

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  if ( (Dem_Cfg_IsObdIISupportedInVariant() == TRUE) &&
       (Dem_Cfg_EventObdRelated(EventId) == TRUE) )
  { /* Clear the OBD FreezeFrame (if available) */
    uint8 lSelectedIndex;

    lSelectedIndex = Dem_Mem_FreezeFrameFindIndex(EventId);

    if (lSelectedIndex != Dem_Cfg_GlobalObdIIFFCount())
    { /* No need to clear the complete FreezeFrame entry as it is only valid if the EventId is valid */
      Dem_MemObdFreezeFrame_FreezeFrameFreeEntry(lSelectedIndex);
      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_OBDFREEZEFRAME),
        DEM_NVM_BLOCKSTATE_DIRTYCLEAREDIMMEDIATE);

      /* if this event is visible in Mode02, clear this cache also */
      if (Dem_Mem_FreezeFrameIndexMode02 == lSelectedIndex)
      {
        Dem_Mem_FreezeFrameIndexMode02 = Dem_Cfg_GlobalObdIIFFCount();
      }
    }
  }
#endif

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  { /* Test and invalidate the aging counter */
    Dem_DTC_TestAndInvalidateAgingCounter(EventId);
  }
#endif

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)                                                                                /* PRQA S 0883 */ /* MD_DEM_19.15 */
  Dem_DTC_ForEachCombinedSubEvent(EventId, Dem_Event_Cleared, &lArgs);                                                           /* SBSW_DEM_CALL_FOREACH_COMBINED_EVENT */
#elif (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
  Dem_DTC_ProcessOperation(EventId, Dem_Event_Cleared, &lArgs);                                                                  /* SBSW_DEM_CALL_OPERATION_FOR_EVENT */
#else
  Dem_Event_Cleared(EventId, &lArgs);                                                                                            /* SBSW_DEM_CALL_POINTER_FORWARD_STACK */
#endif
}                                                                                                                                /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */


#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_SetCombinedGroupUDSStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetCombinedGroupUDSStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId,
  CONST(uint8, AUTOMATIC)  Status
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (GroupId >= Dem_Cfg_GetSizeOfCombinedGroupStatus())
  {
    Dem_Error_RunTimeCheckFailed(DEM_DTCIF_IMPLEMENTATION_FILENAME, __LINE__);                                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_SetCombinedGroupStatus(GroupId, Status);                                                                             /* SBSW_DEM_ARRAY_WRITE_COMBINEDGROUPSTATUS */
  }
}
#endif

/* ****************************************************************************
 % Dem_DTC_InitCombinedGroupProcessed()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InitCombinedGroupProcessed(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
VAR(Dem_Cfg_ProcessedCombinedDTCGroupType, AUTOMATIC) ProcessedCombinedDTCGroup
)
{
  uint16_least lBitfieldIterator;
  for (lBitfieldIterator = 0u;
    lBitfieldIterator < DEM_CFG_PROCESSEDCOMBINEDDTCGROUP_SIZE;
    lBitfieldIterator++)
  {
    ProcessedCombinedDTCGroup[lBitfieldIterator] = 0u;                                                                         /* SBSW_DEM_ARRAY_WRITE_PROCESSEDCOMBINEDDTCGROUP */
  }
}

/* ****************************************************************************
 % Dem_DTC_TestCombinedGroupProcessed()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestCombinedGroupProcessed(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) GroupId,
  CONST(Dem_Cfg_ProcessedCombinedDTCGroupType, AUTOMATIC) ProcessedCombinedDTCGroup                                              /* PRQA S 3673 */ /* MD_DEM_8.13_Internal */
  )
{
  boolean lGroupProcessed;
  lGroupProcessed = FALSE;
  if (Dem_DTC_IsEventCombinationType2Enabled() == TRUE)
  {
    if (GroupId != DEM_CFG_COMBINED_GROUP_INVALID)
    {
     /* Check whether bit in the corresponding bit field is set */
      lGroupProcessed = Dem_Com_TestBitInBitfield(ProcessedCombinedDTCGroup,                                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                                  DEM_CFG_PROCESSEDCOMBINEDDTCGROUP_SIZE,
                                                  GroupId);
    }
  }
  return lGroupProcessed;
}


/* ****************************************************************************
 % Dem_DTC_SetCombinedGroupProcessed()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetCombinedGroupProcessed(                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) GroupId,
  VAR(Dem_Cfg_ProcessedCombinedDTCGroupType, AUTOMATIC) ProcessedCombinedDTCGroup
  )
{
  if (Dem_DTC_IsEventCombinationType2Enabled() == TRUE)
  {
    if (GroupId != DEM_CFG_COMBINED_GROUP_INVALID)
    {
      Dem_Com_SetBitInBitfield(ProcessedCombinedDTCGroup,                                                                        /* SBSW_DEM_ARRAY_FORWARD_PROCESSEDCOMBINEDDTCGROUP */
                               DEM_CFG_PROCESSEDCOMBINEDDTCGROUP_SIZE,
                               GroupId);
    }
  }
}


#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_CalculateCombineGroupUdsStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_CalculateCombineGroupUdsStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_DTC_UDSStatusType lReturnValue;
  Dem_Cfg_CombinedGroupIterType lCombinedIter;

  /* In rare cases GroupId is not required */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lReturnValue = 0x00u;

  for (Dem_Cfg_CombinedGroupIterInit(GroupId, &lCombinedIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lSubEventId;

    lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
    if ((Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE))                     
    {
      lReturnValue = (Dem_DTC_UDSStatusType)(lReturnValue | Dem_Event_GetUDSStatus(lSubEventId));
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_CalculateCombinedGroupType2_ExternalUdsStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_CalculateCombinedGroupType2_ExternalUdsStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_UDSStatusType lCombinedDTCStatus;
  Dem_DTC_UDSStatusType lCombinedSubEventStatus;
  Dem_Cfg_CombinedGroupIterType lCombinedIter;
  Dem_Cfg_CombinedGroupIndexType lGroupId;
# if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
  boolean lWirActive;
# endif

  lCombinedDTCStatus = 0x00U;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
# if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
  lWirActive = FALSE;
# endif

  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_EventIdType lSubEventId;

      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      if ((Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)
        && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE))                   
      {
        lCombinedSubEventStatus = Dem_Event_GetUDSStatus(lSubEventId);
        if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
        {
          lCombinedSubEventStatus = (Dem_Event_GetQualifyStatus(lSubEventId) & lCombinedSubEventStatus);
        }
        lCombinedDTCStatus = (Dem_DTC_UDSStatusType)(lCombinedDTCStatus | lCombinedSubEventStatus);

# if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
        lWirActive = (boolean)(lWirActive
                     || (Dem_DTCInternalStatus_TestUserControlledWir(Dem_Event_GetInternalStatus(lSubEventId)) == TRUE));        
# endif
      }
    }

# if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
    if (lWirActive == TRUE)
    {
      lCombinedDTCStatus = Dem_UDSStatus_Set_WIR(lCombinedDTCStatus);
    }
# endif
  }

  return lCombinedDTCStatus;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_DTC_GetQualifyStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_GetQualifyStatus(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_UDSStatusType lDTCQualifyStatus;
#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;

  lDTCQualifyStatus = 0x00;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);

  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_Cfg_CombinedGroupIterType lCombinedIter;
    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_EventIdType lSubEventId;

      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      if ((Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)
        && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE))                   
      {
        lDTCQualifyStatus = (Dem_DTC_UDSStatusType)(lDTCQualifyStatus | Dem_Event_GetQualifyStatus(lSubEventId));
      }
    }
  }
  else
#endif
  {
    lDTCQualifyStatus =  Dem_Event_GetQualifyStatus(EventId);
  }
  return lDTCQualifyStatus;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_DTC_TestStatusForPermanentStorage
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DTC_TestStatusForPermanentStorage(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
)
{
  boolean lReturnValue;

  lReturnValue = FALSE;

  if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
  {
    lReturnValue = (boolean)(Dem_UDSStatus_Test_WIR(Dem_DTC_GetDTCStatus(EventId)) == TRUE);
  }
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  else if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
  {
    uint8 lWwhObdDtcClass;
    lWwhObdDtcClass = Dem_Util_SeverityWwhObdDtcClass(Dem_Cfg_EventSeverity(EventId));

    lReturnValue = (boolean)
      ((Dem_EventInternalStatus_Test_QualifyStatus_CDTC(Dem_DTC_GetQualifyStatus(EventId)) == TRUE)
        && (Dem_UDSStatus_Test_TF(Dem_DTC_GetDTCStatus(EventId)) == TRUE)
        && ((lWwhObdDtcClass == DEM_ESM_WWHOBD_DTCCLASS_A) || (Dem_Mem_GetB1Counter() > DEM_DATA_B1COUNTER_200H)));
  }
  else
  {
    /* MISRA case */
  }
#endif
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_DTC_TestEventStoresPermanentDTC
 *****************************************************************************/
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
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DTC_TestEventStoresPermanentDTC(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  )
{
  boolean lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lReturnValue = FALSE;

  if (Dem_Cfg_IsPermanentSupportedInVariant() == TRUE)
  {
    if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
    {
      lReturnValue = Dem_Event_TestMilSupport(EventId);
    }
    else if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
    {
      if (Dem_Cfg_EventWwhObdFreezeFrameExists(EventId) == TRUE)
      {
        uint8 lWwhObdDtcClass;
        lWwhObdDtcClass = Dem_Util_SeverityWwhObdDtcClass(Dem_Cfg_EventSeverity(EventId));
        lReturnValue = (boolean)((lWwhObdDtcClass == DEM_ESM_WWHOBD_DTCCLASS_B1)
          || (lWwhObdDtcClass == DEM_ESM_WWHOBD_DTCCLASS_A));
      }
    }
    else
    {
      /* MISRA case */
    }
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTC_TestPfcRequired
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestPfcRequired(                                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  boolean lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
  {
#if (DEM_CFG_SUPPORT_CLEAR_PDTC_NO_PFC == STD_ON) && (DEM_CFG_SUPPORT_IUMPR == STD_ON)
    lReturnValue = FALSE;
# if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
    {
      Dem_Cfg_CombinedGroupIndexType lGroupId;

      lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
      if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
      {
        Dem_Cfg_CombinedGroupIterType lCombinedIter;
        for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          Dem_EventIdType lSubEventId;
          lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
          if ((Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)
            && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE))
          {
            if (Dem_Event_GetRatioIdx(lSubEventId) == DEM_CFG_RATIOINDEX_INVALID)
            {
              lReturnValue = TRUE;
              break;
            }
          }
        }
      }
      else
      {
        if (Dem_Event_GetRatioIdx(EventId) == DEM_CFG_RATIOINDEX_INVALID)
        {
          lReturnValue = TRUE;
        }
      }
    }
# else
    /* If event has a ratio attached, it can be cleared without respect the PFC cycle. So set PFC cycle to fulfilledPerm */
    if (Dem_Event_GetRatioIdx(EventId) == DEM_CFG_RATIOINDEX_INVALID)
    {
      lReturnValue = TRUE;
    }
# endif
#else
   lReturnValue = TRUE;
#endif
  }
  else
  {
    lReturnValue = TRUE;
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


/* ****************************************************************************
 % Dem_DTC_TestStoredStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestStoredStatus(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  boolean lReturnValue;
  Dem_DTCInternal_StoredStatusType lInternalStoredStatus;
  lInternalStoredStatus = Dem_DTCInternalStatus_GetStoredStatus(Dem_DTC_GetInternalStatus(EventId));

  if (lInternalStoredStatus != Dem_DTCInternalStatus_StoredStatus_None)
  {
    lReturnValue = TRUE;
  }
  else
  {
    lReturnValue = FALSE;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTC_TestDtcAvailable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcAvailable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lReturnValue;
  if (Dem_Cfg_EventIsCombined(EventId) == TRUE)
  {
    lReturnValue = Dem_DTC_TestGroupAvailable(Dem_Cfg_EventCombinedGroup(EventId));
  }
  else
  {
    lReturnValue = Dem_Event_TestEventRuntimeAvailable(EventId);
  }
  return lReturnValue;
}

/* ****************************************************************************
% Dem_DTC_TestSuppressionByRepresentiveEvent
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestSuppressionByRepresentiveEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  boolean lReturnValue;
  if (Dem_DTC_IsEventCombinationType1Enabled() == TRUE)
  {
    lReturnValue = Dem_DTC_TestSuppressionOnDtcRetrieval(EventId);
  }
  else
  {
    lReturnValue = Dem_Event_TestSuppressionOnEventRetrieval(EventId);
  }
  return lReturnValue;
}


/* ****************************************************************************
 % Dem_DTC_TestDtcAvailableInVariant
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcAvailableInVariant(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lReturnValue;
  if (Dem_Cfg_EventIsCombined(EventId) == TRUE)
  {
    lReturnValue = Dem_DTC_TestGroupAvailableInVariant(Dem_Cfg_EventCombinedGroup(EventId));
  }
  else
  {
    lReturnValue = Dem_Cfg_EventAvailableByVariant(EventId);
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTC_TestDtcSuppression
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcSuppression(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lReturnValue;

  if (Dem_Cfg_EventIsCombined(EventId) == TRUE)
  {
    lReturnValue = Dem_DTC_TestGroupSuppression(Dem_Cfg_EventCombinedGroup(EventId));
  }
  else
  {
    lReturnValue = Dem_DTCInternalStatus_TestDtcSuppressed(Dem_Event_GetInternalStatus(EventId));
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTC_TestSuppressionOnDtcRetrieval
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestSuppressionOnDtcRetrieval(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lReturnValue;
  lReturnValue = (boolean)
     ( (Dem_DTC_TestDtcSuppression(EventId) == TRUE)
    || (Dem_DTC_TestDtcAvailableInVariant(EventId) == FALSE)                                                                     
    || ( (Dem_DTC_TestDtcAvailable(EventId) == FALSE)                                                                            
      && (Dem_DTC_TestStoredStatusOnDtcRetrieval(EventId) == FALSE) )                                                            /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
     );
  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_DTC_TestRemainingEventforDtc
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestRemainingEventforDtc(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  boolean lReturnValue;
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  Dem_DTC_InternalStatusType lInternalStatus;
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif

# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  lReturnValue = FALSE;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);

  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_Cfg_CombinedGroupIterType lCombinedIter;

    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_EventIdType lSubEventId;
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      lInternalStatus = Dem_Event_GetInternalStatus(lSubEventId);
      if ( (lSubEventId != EventId)
        && (Dem_EventInternalStatus_TestEventDisconnected(lInternalStatus) == FALSE) )                                           
      {
        lReturnValue = TRUE;
        break;
      }
    }
  }
  else
# endif
  {
    lReturnValue = FALSE;
  }
  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_DTC_ResetFdcToc
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ResetFdcToc(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON)
  Dem_DTC_InternalStatusType lInternalStatus;
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
  Dem_EnterCritical_DiagMonitor();

  lInternalStatus = Dem_Event_GetInternalStatus(EventId);
  lInternalStatus = Dem_DTCInternalStatus_ResetFdcToc(lInternalStatus);
  Dem_Event_SetInternalStatus(EventId, lInternalStatus);

  Dem_LeaveCritical_DiagMonitor();
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_ResetDtcSuppression
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ResetDtcSuppression(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_DTC_InternalStatusType lInternalStatus;
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();
    lInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(lGroupId);
    lInternalStatus = Dem_DTCInternalStatus_ResetDtcSuppressed(lInternalStatus);
    Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, lInternalStatus);
    Dem_LeaveCritical_DiagMonitor();
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
  }
  else
# endif
  {
    Dem_DTC_InternalStatusType lInternalStatus;
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();
    lInternalStatus = Dem_Event_GetInternalStatus(EventId);
    lInternalStatus = Dem_DTCInternalStatus_ResetDtcSuppressed(lInternalStatus);
    Dem_Event_SetInternalStatus(EventId, lInternalStatus);
    Dem_LeaveCritical_DiagMonitor();
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON) */

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_ChangeDtcSuppression
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_ChangeDtcSuppression(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  SuppressionStatus
  )
{
  Std_ReturnType lReturnValue;

  lReturnValue = E_NOT_OK;


  if (EventId != DEM_EVENT_INVALID)
  {
    if (SuppressionStatus == TRUE)
    {
      Dem_DTC_SetDtcSuppression(EventId);
    }
    else
    {
      Dem_DTC_ResetDtcSuppression(EventId);
    }

    Dem_Dtr_DTCSuppressionChanged(EventId);
    lReturnValue = E_OK;
  }

  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_DTC_CalculateDTCStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CalculateDTCStatus(
CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
)
{
#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  if (DTCContext->GroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    DTCContext->NewDtcStatus = Dem_DTC_CalculateCombineGroupUdsStatus(DTCContext->GroupId);                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    Dem_DTC_SetCombinedGroupUDSStatus(DTCContext->GroupId, DTCContext->NewDtcStatus);
  }
  else
#endif
  {
    DTCContext->NewDtcStatus = Dem_Event_GetUDSStatus(DTCContext->EventId);                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}

/* ****************************************************************************
 % Dem_DTC_GetDTCStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_GetDTCStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_UDSStatusType lDtcStatus;
#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    lDtcStatus = Dem_DTC_GetCombinedGroupUDSStatus(lGroupId);
  }
  else
#endif
  {
    lDtcStatus = Dem_Event_GetUDSStatus(EventId);
  }
  return lDtcStatus;
}

/* ****************************************************************************
% Dem_DTC_GetExternalDTCStatus
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
DEM_LOCAL FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_GetExternalDTCStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  uint8 lDTCStatus;

  lDTCStatus = Dem_DTC_GenerateExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));
  lDTCStatus = (uint8)(lDTCStatus & Dem_Cfg_GlobalStatusMask());                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  
  return lDTCStatus;
}

/* ****************************************************************************
 % Dem_DTC_RetrieveStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_RetrieveStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_UDSStatusType lStatus;

# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  lStatus = Dem_DTC_GetDTCStatus(EventId);
# else
  lStatus = Dem_Event_GetUDSStatus(EventId);
# endif

  return lStatus;
}

/* ****************************************************************************
 % Dem_DTC_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_GetFaultDetectionCounter(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter
  )
{
  Std_ReturnType lGetFdcReturnValue;
# if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    lGetFdcReturnValue = Dem_DTC_CombinedGroupGetFDC(lGroupId, FaultDetectionCounter);                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
# endif
  {
    lGetFdcReturnValue = Dem_GetFaultDetectionCounter(EventId, FaultDetectionCounter);                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }

  return lGetFdcReturnValue;
}


#if ( (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) \
   && ( ( ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON) ) \
     || ((DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) && (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON) ) ) )
/* ****************************************************************************
 % Dem_DTC_CombinedGroupGetFDCMax
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(sint8, DEM_CODE)
Dem_DTC_CombinedGroupGetFDCMax(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  sint8 lMaxFdc;
  Dem_Cfg_CombinedGroupIterType lCombinedIter;

  /* In rare cases GroupId is not required */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lMaxFdc = 0;
  for (Dem_Cfg_CombinedGroupIterInit(GroupId, &lCombinedIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lSubEventId;
    lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
    if ( (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE) )                    
    {
      sint8 lFdc;
      lFdc = Dem_Satellite_GetMaxFaultDetectionCounter(
        Dem_Cfg_EventSatelliteId(lSubEventId),
        Dem_Cfg_EventSatelliteEventId(lSubEventId));
      if (lMaxFdc < lFdc)
      {
        lMaxFdc = lFdc;
      }
    }
  }

  return lMaxFdc;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_DTC_ApplyCombinedStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_ApplyCombinedStatus(
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DtcStatus
  )
{
  Dem_DTC_UDSStatusType lReturnValue;
  lReturnValue = DtcStatus;
# if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  if (Dem_UDSStatus_Test_TFSLC(lReturnValue) == TRUE)
  {
    lReturnValue = Dem_UDSStatus_Reset_TNCSLC(lReturnValue);
  }
  if (Dem_UDSStatus_Test_TFTOC(lReturnValue) == TRUE)
  {
    lReturnValue = Dem_UDSStatus_Reset_TNCTOC(lReturnValue);
  }
# endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTC_GenerateExternalOnlyStatus
 *****************************************************************************/
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
 */
DEM_LOCAL FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_GenerateExternalOnlyStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DtcStatus
  )
{
  Dem_DTC_UDSStatusType lExternalDTCSTatus;
#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
#endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    lExternalDTCSTatus = Dem_DTC_GenerateExternalOnlyType1CombinedStatus(EventId, DtcStatus);
#else
    lExternalDTCSTatus = Dem_DTC_GenerateExternalOnlyType2CombinedStatus(EventId, DtcStatus);
# endif
  }
  else
#endif
  {
    lExternalDTCSTatus = DtcStatus;

    /* EventId is not a combined event */
    if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
    {
      lExternalDTCSTatus = (Dem_DTC_UDSStatusType)(Dem_Event_GetQualifyStatus(EventId) & lExternalDTCSTatus);
    }
    lExternalDTCSTatus = (Dem_DTC_UDSStatusType)(Dem_DTC_ApplyUserControlledWIR(lExternalDTCSTatus, Dem_Event_GetInternalStatus(EventId)));
  }
  return lExternalDTCSTatus;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
 % Dem_DTC_AgingCycle
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_AgingCycle(
CONST(Dem_EventIdType, AUTOMATIC)  EventId,
CONST(uint16, AUTOMATIC)  CycleCounter,
CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
)
{
  Dem_DTC_UDSStatusType lDtcStatus;
  Dem_Cfg_MemoryEntryHandleType lMemoryEntryHandle;

  lDtcStatus = Dem_DTC_RetrieveStatus(EventId);
#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  if (MemoryIndex == DEM_MEM_INVALID_MEMORY_INDEX)
  {
    lMemoryEntryHandle = DEM_MEMORYENTRY_HANDLE_INVALID;
  }
  else
# endif
  {
    lMemoryEntryHandle = Dem_MemoryEntry_GetId(MemoryIndex);
  }

  if (Dem_UDSStatus_Test_TF(lDtcStatus) == FALSE)
  {
    /* passive event */
    uint16 lCycleCount;
    lCycleCount = Dem_DTC_GetAgingCounter(EventId, lMemoryEntryHandle);
#if ((DEM_CFG_AGING_NEXT_TESTS_TNCTOC == STD_ON) || (DEM_CFG_AGING_NEXT_TESTS_TFTOC == STD_ON))
    if (Dem_DTC_TestStatusForAgingCycle(lDtcStatus) == FALSE)
    {
      /* Untested cycle requires recalculation of aging target */
      if (lCycleCount <= DEM_OPERATIONCYCLE_CYCLECOUNT_MAX)
      { /* Ignore maxed (latched) counter */
        Dem_Event_DataUpdateStart(EventId);
        lCycleCount = Dem_OperationCycle_AddCycleCount(lCycleCount, 1);
        Dem_DTC_SetAgingCounter(EventId, MemoryIndex, lCycleCount);
        Dem_Event_DataUpdateFinish(EventId);
      }
    }
    else
#endif
    if (CycleCounter == lCycleCount)
    { /* Aging cycle reached, so this event has aged */
      Dem_Event_DataUpdateStart(EventId);
      Dem_DTC_Aged(EventId, MemoryIndex, FALSE);
      Dem_Event_DataUpdateFinish(EventId);
    }
    else
    { /* Still counting */ }
  }
}                                                                                                                                /* PRQA S 6080, 6050 */ /* MD_MSR_STMIF, MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
 % Dem_DTC_Aged
 *****************************************************************************/
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
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Aged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(boolean, AUTOMATIC)  SuppressNotifications
  )
{
  if (Dem_Cfg_EventSupportAging(EventId) == TRUE)
  {
    Dem_DTC_UDSStatusType lOldDtcStatus;
    Dem_DTC_ForEachCombinedArgType lArgs;


    Dem_DTC_ResetFailedCycleCounter(EventId);
    Dem_DTC_ResetFaultPendingCounter(EventId);

#if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
    if (MemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
    {
      lArgs.Specific.Event_Aged.IsAgingOnlyEntry = Dem_MemoryEntry_TestAgingOnlyEntry(Dem_MemoryEntry_GetId(MemoryIndex));
    }
    else
    {
      lArgs.Specific.Event_Aged.IsAgingOnlyEntry = FALSE;
    }
#endif

    /* Process aging for each sub-event status */
    lOldDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));
    lArgs.Specific.Event_Aged.SuppressNotifications = SuppressNotifications;

# if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_OFF)
    Dem_DTC_ForEachCombinedSubEvent(EventId, Dem_Event_Aged, &lArgs);                                                            /* SBSW_DEM_CALL_FOREACH_COMBINED_EVENT */
# else
    Dem_DTC_ProcessOperation(EventId, Dem_Event_Aged, &lArgs);                                                                   /* SBSW_DEM_CALL_OPERATION_FOR_EVENT */
# endif

    if (Dem_DTC_TestEventStoresPermanentDTC(EventId) == TRUE)
    {
      /* For event combination type 2, clear entry from permanent chronology
         only if the Confirmed DTC bit is reset in the DTC status */
# if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
      if ( (Dem_UDSStatus_Test_CDTC(lArgs.Common.OldDtcStatus) == TRUE)
        && (Dem_UDSStatus_Test_CDTC(lArgs.Common.NewDtcStatus) == FALSE) )                                                       
# endif
      {
        /* CDTC bit is always reset on aging -> free unconditionally*/
        Dem_Memory_ConfirmedChronoFreeEvent(Dem_Cfg_GetMasterEvent(EventId));
      }
    }

# if (DEM_CFG_SUPPORT_OBDII == STD_ON)
#  if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF)
    if (MemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
#  endif
    {
      /* clear the OBD freeze frame */
      if ( (Dem_Cfg_IsObdIISupportedInVariant() == TRUE) &&
           (Dem_Cfg_EventObdRelated(EventId) == TRUE) )
      {
        uint8 lObdFreezeFrameIndex;

        lObdFreezeFrameIndex = Dem_Mem_FreezeFrameFindIndex(EventId);

        if (lObdFreezeFrameIndex != Dem_Cfg_GlobalObdIIFFCount())
        {
          if (lObdFreezeFrameIndex == Dem_Mem_FreezeFrameIndexMode02)
          {
            Dem_Mem_FreezeFrameIndexMode02 = Dem_Cfg_GlobalObdIIFFCount();
          }

          Dem_MemObdFreezeFrame_FreezeFrameFreeEntry(lObdFreezeFrameIndex);
          Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_OBDFREEZEFRAME),
            DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
        }
      }
    }
# endif

    if (MemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
    {
#if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
      if (lArgs.Specific.Event_Aged.IsAgingOnlyEntry == TRUE)
      {
        Dem_Memory_FreeEvent(MemoryIndex, EventId);
      }
      else
      {
        Dem_DTC_SetAgingCounter(EventId, MemoryIndex, DEM_OPERATIONCYCLE_CYCLECOUNT_AGED);

        Dem_StatusIndicator_UpdateOnEventAged(MemoryIndex);
      }
#else
      {
        /* While clearing an aged memory entry, set the aging counter to Aged */
# if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
        Dem_DTC_SetAgingCounter(EventId, MemoryIndex, DEM_OPERATIONCYCLE_CYCLECOUNT_AGED);
# endif

        /* Remove the event from the memory */
        Dem_Memory_FreeEvent(MemoryIndex, EventId);
      }
#endif
      /* Block is set dirty due to updates from aging counter
         and free operation */
      if (Dem_Cfg_EventSupportImmediateNv(EventId) == TRUE)
      {
        Dem_Nvm_SetEventMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
      }
      else
      {
        Dem_Nvm_SetEventMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
      }

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
      /* For combined events, synchronize the combined internal stored status */
      {
        Dem_Cfg_CombinedGroupIndexType lGroupId;
        lGroupId = Dem_Cfg_EventCombinedGroup(EventId);

        if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
        {
          Dem_DTC_InternalStatusType lGroupInternalStatus;

          /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
          Dem_EnterCritical_DiagMonitor();

          lGroupInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(lGroupId);

          Dem_DTC_SetCombinedGroupUDSStatus(lGroupId, lArgs.Common.NewDtcStatus);
# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
          if(lArgs.Specific.Event_Aged.IsAgingOnlyEntry == FALSE)
          {
            lGroupInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lGroupInternalStatus, Dem_DTCInternalStatus_StoredStatus_Aged);
          }
          else /* 'aging only' entry is always removed */
# endif
          {
            lGroupInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lGroupInternalStatus, Dem_DTCInternalStatus_StoredStatus_None);
          }
          Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, lGroupInternalStatus);

          Dem_LeaveCritical_DiagMonitor();
          /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
        }
      }
#endif

      /* If configured, notify the DTC status change */
      if ((Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
        && (SuppressNotifications == FALSE))
      {
        Dem_Notifications_DtcStatusChanged(EventId,
                                           lOldDtcStatus,
                                           Dem_DTC_GenerateExternalOnlyStatus(EventId, lArgs.Common.NewDtcStatus),
                                           DEM_NOTIFICATIONS_DTC_AGED);
      }
    }
    else
    {
      /* When a memory entry is aged, set the aging counter to aged */
# if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
      Dem_DTC_SetAgingCounter(EventId, DEM_MEM_INVALID_MEMORY_INDEX, DEM_OPERATIONCYCLE_CYCLECOUNT_AGED);
# endif
    }
#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
      /* For event combination type 2, increment the Aged Counter only if the
         Confirmed DTC bit is reset in the DTC status */
# if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
    if ( (Dem_UDSStatus_Test_CDTC(lArgs.Common.OldDtcStatus) == TRUE)
       && (Dem_UDSStatus_Test_CDTC(lArgs.Common.NewDtcStatus) == FALSE) )                                                        
# endif
    {
      Dem_DTC_IncrementAgedCounter(EventId);
    }
#endif

    Dem_Memory_TimeSeries_InvalidateEntryOfEvent(EventId, DEM_NVM_BLOCKSTATE_DIRTY);
  }
  else
  {
    /* Every event has an aging counter and hence must be latched */
# if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF)
    if (MemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
# endif
    {
      /* Latch the aging counter and set the memory entries NV status to DIRTY */
      Dem_DTC_SetAgingCounter(EventId, MemoryIndex, DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED);
    }
  }
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

#endif

/* ****************************************************************************
 % Dem_DTC_ClearOBDFreezeFrame
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ClearOBDFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if ( (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PENDING_STORAGE_FREEZE_FRAME == STD_ON) )
  if ( (Dem_Cfg_EventObdRelated(EventId) == TRUE)
    && (Dem_UDSStatus_Test_CDTC(Dem_DTC_RetrieveStatus(EventId)) == FALSE) )
  { /* DTC did not confirm before starting to age - release the OBD freeze
       frame if held by the event */
    uint8 lObdFreezeFrameIndex;

    lObdFreezeFrameIndex = Dem_Mem_FreezeFrameFindIndex(EventId);

    if (lObdFreezeFrameIndex != Dem_Cfg_GlobalObdIIFFCount())
    {
      if (lObdFreezeFrameIndex == Dem_Mem_FreezeFrameIndexMode02)
      {
        Dem_Mem_FreezeFrameIndexMode02 = Dem_Cfg_GlobalObdIIFFCount();
      }
      Dem_MemObdFreezeFrame_FreezeFrameFreeEntry(lObdFreezeFrameIndex);
      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_OBDFREEZEFRAME),
                                  DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
    }
  }
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId);                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */


#if ((DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON) || (DEM_CFG_SUPPORT_TRIGGER_PASSED == STD_ON))
/* ****************************************************************************
 % Dem_DTC_Passed_CalcDTCEffects
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_DTC_Passed_CalcDTCEffects(
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC) EventEffects
  )
{
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (DTCContext->GroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    if ( (Dem_UDSStatus_Test_TF(DTCContext->OldDtcStatus) == TRUE)
      && (Dem_UDSStatus_Test_TF(DTCContext->NewDtcStatus) == FALSE))                                                             
    {
      DTCContext->DtcEffects = (Dem_Cfg_StorageTriggerType)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_PASSED);                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    if ( (Dem_UDSStatus_Test_TNCTOC(DTCContext->OldDtcStatus) == TRUE)
      && (Dem_UDSStatus_Test_TNCTOC(DTCContext->NewDtcStatus) == FALSE))                                                         
    {
      DTCContext->DtcEffects = (Dem_Cfg_StorageTriggerType)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_FIRSTTHISCYCLE);            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }
  else
#endif
  {
    DTCContext->DtcEffects = EventEffects;                                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}
#endif

/* ****************************************************************************
% Dem_DTC_InitMemIndependentCycleCounterDataNv
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InitMemIndependentCycleCounterDataNv(
  void
)
{
  if (Dem_DTC_IsMemIndependentCycleCounterEnabled() == TRUE)
  {
# if (DEM_CFG_DATA_FAILED_CYCLES == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_ON)
    Dem_MemSet((Dem_DataPtrType)&(Dem_Cfg_CycleCounterData.FailedCycleCounter[0]),                                               /* PRQA S 0602 */ /* MD_DEM_20.2 */ /* SBSW_DEM_ARRAY_WRITE_CYCLECOUNTERDATA_FAILEDCYCLECOUNTER */
      0x00u,
      DEM_CFG_MAX_NUMBER_FAILED_CYCLE_DTCS * sizeof(Dem_Cfg_CycleCounterData.FailedCycleCounter[0]));
# endif

# if (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_ON)
    Dem_MemSet((Dem_DataPtrType)&(Dem_Cfg_CycleCounterData.FaultPendingCounter[0]),                                              /* PRQA S 0602 */ /* MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_CYCLECOUNTERDATA_FAULTPENDINGCOUNTER */
      0x00u,
      DEM_CFG_MAX_NUMBER_FAULT_PENDING_DTCS * sizeof(Dem_Cfg_CycleCounterData.FaultPendingCounter[0]));
# endif
  }
}

/* ****************************************************************************
 % Dem_DTC_Cleared
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_Cleared(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lReturnValue;
  Dem_DTC_UDSStatusType lOldInternalDtcStatus;
  Dem_DTC_UDSStatusType lNewInternalDtcStatus;
  Dem_DTC_UDSStatusType lOldExternalDtcStatus;
  Dem_DTC_UDSStatusType lNewExternalDtcStatus;

  Dem_Event_DataUpdateStart(EventId);
  lOldInternalDtcStatus = Dem_DTC_GetDTCStatus(EventId);
  lOldExternalDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(EventId, lOldInternalDtcStatus);
#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  if (Dem_Cfg_EventCombinedGroup(EventId) != DEM_CFG_COMBINED_GROUP_INVALID)
  {
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    lReturnValue = Dem_DTC_EventCombinationOnStorage_Cleared(EventId);
# else
    lReturnValue = Dem_DTC_EventCombinationOnRetrieval_Cleared(EventId);
# endif
  }
  else
#endif
  {
    lReturnValue = Dem_Event_ProcessCleared(EventId);
  }
  lNewInternalDtcStatus = Dem_DTC_GetDTCStatus(EventId);
  lNewExternalDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(EventId, lNewInternalDtcStatus);

  if (Dem_DTC_TestEventStoresPermanentDTC(EventId) == TRUE)
  {
    Dem_Data_PermanentEntryClear(EventId, TRUE);

    /*CDTC bit could be reset already*/
    if ((Dem_UDSStatus_Test_CDTC(lOldInternalDtcStatus) == TRUE)
      && (Dem_UDSStatus_Test_CDTC(lNewInternalDtcStatus) == FALSE))                                                              
    {
      Dem_Memory_ConfirmedChronoFreeEvent(EventId);
    }
  }

  Dem_Notifications_InitMonitorForFunction(EventId);

  if (lReturnValue == TRUE)
  {

    Dem_DTC_ResetFailedCycleCounter(EventId);
    Dem_DTC_ResetFaultPendingCounter(EventId);

#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
    Dem_DTC_ResetAgedCounter(EventId);
#endif

    Dem_Notifications_DtcStatusChanged(EventId,
      lOldExternalDtcStatus,
      lNewExternalDtcStatus,
      DEM_NOTIFICATIONS_DTC_CLEAR);
  }

  Dem_Event_DataUpdateFinish(EventId);
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON)
/* ****************************************************************************
 % Dem_DTC_Displaced
 *****************************************************************************/
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

 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Displaced(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_UDSStatusType lOldDtcStatus;
  Dem_DTC_ForEachCombinedArgType lArgs;

  lOldDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));

# if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_OFF)
  Dem_DTC_ForEachCombinedSubEvent(EventId, Dem_Event_Displaced, &lArgs);                                                         /* SBSW_DEM_CALL_FOREACH_COMBINED_EVENT */
# else
  Dem_DTC_ProcessOperation(EventId, Dem_Event_Displaced, &lArgs);                                                                /* SBSW_DEM_CALL_OPERATION_FOR_EVENT */
# endif

# if (DEM_CFG_PROCESS_CDTC_STOREDONLY == STD_ON)
  if (Dem_DTC_TestEventStoresPermanentDTC(EventId) == TRUE)
  {
#  if ((DEM_CFG_STORAGE_AT_CONFIRMED == STD_OFF) || (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
    if ( (Dem_UDSStatus_Test_CDTC(lArgs.Common.OldDtcStatus) == TRUE)
      && (Dem_UDSStatus_Test_CDTC(lArgs.Common.NewDtcStatus) == FALSE) )                                                         
#  endif
    {
      Dem_EventIdType lMasterEventId;
      lMasterEventId = Dem_Cfg_GetMasterEvent(EventId);
      Dem_Memory_ConfirmedChronoFreeEvent(lMasterEventId);
    }
  }
# endif


# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  {
    Dem_Cfg_CombinedGroupIndexType lGroupId;
    lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
    if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
    {
      Dem_DTC_SetCombinedGroupUDSStatus(lGroupId, lArgs.Common.NewDtcStatus);

      /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
      Dem_EnterCritical_DiagMonitor();
      {
        Dem_DTC_InternalStatusType lInternalStatus;
        lInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(lGroupId);
        lInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lInternalStatus, Dem_DTCInternalStatus_StoredStatus_None);
        Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, lInternalStatus);
      }
      Dem_LeaveCritical_DiagMonitor();
      /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
    }
  }
# endif

  /* If the displaced memory entry is not confirmed, reset the aging counter */
# if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  {
    if (Dem_UDSStatus_Test_CDTC(Dem_DTC_RetrieveStatus(EventId)) == FALSE)
    {
      Dem_DTC_TestAndInvalidateAgingCounter(EventId);
    }
  }
# endif

  /* Call status changed notifications (there is always a change) */
  Dem_Notifications_DtcStatusChanged(EventId,
                                     lOldDtcStatus,
                                     Dem_DTC_GenerateExternalOnlyStatus(EventId, lArgs.Common.NewDtcStatus),
                                     DEM_NOTIFICATIONS_DTC_DISPLACED);
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
/* ****************************************************************************
 % Dem_DTC_CustomizedDisplacement
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CustomizedDisplacement(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  SI30
  )
{
  Dem_DTC_UDSStatusType lOldDtcStatus;
  Dem_DTC_ForEachCombinedArgType lArgs;

  lOldDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));
  lArgs.Specific.Event_CustomizedDisplacement_Internal.SI30 = SI30;
  Dem_DTC_ForEachCombinedSubEvent(EventId, Dem_Event_CustomizedDisplacement, &lArgs);                                            /* SBSW_DEM_CALL_FOREACH_COMBINED_EVENT */
  /* Call status changed notifications (there is always a change) */
  Dem_Notifications_DtcStatusChanged(EventId,
                                     lOldDtcStatus,
                                     Dem_DTC_GenerateExternalOnlyStatus(EventId, lArgs.Common.NewDtcStatus),
                                     DEM_NOTIFICATIONS_DTC_DISPLACED);
}
#endif

#if (DEM_FEATURE_NEED_AGING_TRIGGER_CYCLE == STD_ON) && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
 % Dem_DTC_OpCycleEnd_Aging
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_OpCycleEnd_Aging(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  OldUdsStatus                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(OldUdsStatus);                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */

  if (Dem_Cfg_EventAgingTarget(EventId) == 0u)
  {
# if (DEM_CFG_AGING_00_START_TRIGGER_PASSED == STD_OFF) || (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON)
#  if (DEM_CFG_AGING_00_START_TRIGGER_PASSED == STD_ON) && (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON)
    /* Events with healing target 0 are aged at passed result */
    if (Dem_Cfg_EventHealingTarget(EventId) != 0u)
#  endif
    {
      if ((Dem_UDSStatus_Test_TNCTOC(OldUdsStatus) == FALSE)
#  if (DEM_CFG_AGING_00_START_TESTS_TFTOC == STD_ON)
        && (Dem_UDSStatus_Test_TFTOC(OldUdsStatus) == FALSE))                                                                    
#  else
        && (Dem_UDSStatus_Test_TF(OldUdsStatus) == FALSE))                                                                       
#  endif
      {
#  if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
        if ((Dem_Cfg_EventCombinedGroup(EventId) == DEM_CFG_COMBINED_GROUP_INVALID)
            || (Dem_DTC_TestDtcMayAge(EventId) == TRUE))                                                                         /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
#  endif
        {
          Dem_DTC_AgingStartZeroTarget(EventId, TRUE);
        }
      }
    }
# endif
  }
  else
  {
# if (DEM_CFG_AGING_START_TRIGGER_PASSED == STD_OFF) || (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON)                         /* COV_DEM_UNSUPPORTED_FEATURE TX tf tf */
    if ((Dem_UDSStatus_Test_TNCTOC(OldUdsStatus) == FALSE)
#  if (DEM_CFG_AGING_START_TESTS_TFTOC == STD_ON)
      && (Dem_UDSStatus_Test_TFTOC(OldUdsStatus) == FALSE))                                                                      
#  else
      && (Dem_UDSStatus_Test_TF(OldUdsStatus) == FALSE))                                                                         
#  endif
    {
#  if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
        if ((Dem_Cfg_EventCombinedGroup(EventId) == DEM_CFG_COMBINED_GROUP_INVALID)
            || (Dem_DTC_TestDtcMayAge(EventId) == TRUE))                                                                         /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
#  endif
      {
        Dem_DTC_AgingStartMultiTarget(EventId);
      }
    }
# endif /* (DEM_CFG_AGING_START_TRIGGER_PASSED == STD_OFF) || (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON) */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /*(DEM_FEATURE_NEED_AGING_TRIGGER_CYCLE == STD_ON)*/

/* ****************************************************************************
 % Dem_DTC_InitDTCContext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InitDTCContext(
CONST(Dem_EventIdType, AUTOMATIC)  EventId,
CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
)
{
  DTCContext->EventId = EventId;                                                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DTCContext->OldDtcStatus = Dem_DTC_GetDTCStatus(EventId);                                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DTCContext->OldExternalDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(EventId, DTCContext->OldDtcStatus);                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  DTCContext->DtcEffects = DEM_CFG_TRIGGER_NONE;                                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DTCContext->GroupId = Dem_Cfg_EventCombinedGroup(EventId);                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#endif
  DTCContext->QualifyDTC = FALSE;                                                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_DTC_CalculateFailedEffects
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CalculateFailedEffects(
CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext,
CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  EventEffects
)
{
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (DTCContext->GroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
# if (DEM_CFG_SUPPORT_RETRY_STORAGE == STD_ON)
    if (Dem_DTC_TestStoredStatus(DTCContext->EventId) == FALSE)
    {
      DTCContext->DtcEffects = (Dem_Cfg_StorageTriggerType)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_TESTFAILED);                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      DTCContext->DtcEffects = (Dem_Cfg_StorageTriggerType)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE);       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      DTCContext->DtcEffects = (Dem_Cfg_StorageTriggerType)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_FIRSTTHISCYCLE);            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    else
# endif
    {
      if (Dem_UDSStatus_Test_TF(DTCContext->OldDtcStatus) == FALSE)
      {
        DTCContext->DtcEffects = (Dem_Cfg_StorageTriggerType)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_TESTFAILED);              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
      if (Dem_UDSStatus_Test_TFTOC(DTCContext->OldDtcStatus) == FALSE)
      {
        DTCContext->DtcEffects = (Dem_Cfg_StorageTriggerType)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE);     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        DTCContext->DtcEffects = (Dem_Cfg_StorageTriggerType)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_FIRSTTHISCYCLE);          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
    }
  }
  else
#endif
  {
    DTCContext->DtcEffects = EventEffects;                                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}

/* ****************************************************************************
 % Dem_DTC_CalculateFailedEffects_OnStorage
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CalculateFailedEffects_OnStorage(
CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext,
CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  EventEffects
)
{
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
   if (DTCContext->GroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    if((EventEffects & DEM_CFG_TRIGGER_PENDING) != 0u)
    {
      if ((Dem_UDSStatus_Test_PDTC(DTCContext->OldDtcStatus) == FALSE)
# if (DEM_CFG_SUPPORT_RETRY_STORAGE == STD_ON) && (DEM_CFG_PROCESS_PDTC_ALL_DTC == STD_ON)
        || (Dem_DTC_TestStoredStatus(DTCContext->EventId) == FALSE)                                                              /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
# endif
        )
      {
        DTCContext->DtcEffects = (Dem_Cfg_StorageTriggerType)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_PENDING);                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
    }

    if((EventEffects & DEM_CFG_TRIGGER_CONFIRMED) != 0u)
    {
      if ( (Dem_UDSStatus_Test_CDTC(DTCContext->OldDtcStatus) == FALSE)
# if (DEM_CFG_SUPPORT_RETRY_STORAGE == STD_ON) && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
        || (Dem_DTC_TestStoredStatus(DTCContext->EventId) == FALSE)                                                              /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
# endif
        )
      {
        DTCContext->DtcEffects = (Dem_Cfg_StorageTriggerType)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_CONFIRMED);               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
    }

    if((EventEffects & DEM_CFG_TRIGGER_INDICATOR) != 0u)
    {
      if (Dem_UDSStatus_Test_WIR(DTCContext->OldDtcStatus) == FALSE)
      {
        DTCContext->DtcEffects = (Dem_Cfg_StorageTriggerType)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_INDICATOR);               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
    }
  }
  else
#endif
  {
    DTCContext->DtcEffects = EventEffects;                                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}                                                                                                                                /* PRQA S 6010 */ /* MD_MSR_STPTH */

/* ****************************************************************************
 % Dem_DTC_ProcessFailedEffects
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ProcessFailedEffects(
CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
)
{
  Dem_DTC_InternalStatusType   lNewInternalStatus;
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
   Dem_EnterCritical_DiagMonitor();
   lNewInternalStatus = Dem_DTC_GetInternalStatus(DTCContext->EventId);
   if (Dem_DTCInternalStatus_GetStoredStatus(lNewInternalStatus) == Dem_DTCInternalStatus_StoredStatus_Aging)
   {
     lNewInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lNewInternalStatus, Dem_DTCInternalStatus_StoredStatus_Active);
     Dem_DTC_SetInternalStatus(DTCContext->EventId, lNewInternalStatus);
   }
    Dem_LeaveCritical_DiagMonitor();
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
}

/* ****************************************************************************
 % Dem_DTC_Passed_ProcessDTCEffects
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Passed_ProcessDTCEffects(
CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext,                                                            /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
)
{
#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
  /* if event is assigned to a readiness group */
  if (Dem_Cfg_EventReadinessGroup(DTCContext->EventId) != DEM_CFG_READINESS_NONE)
  {
    Dem_DTC_Passed_ProcessDTCEffects_TPSLC(DTCContext);                                                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
#endif

#if ((DEM_CFG_SUPPORT_TRIGGER_PASSED == STD_ON) && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
  if ((Dem_Cfg_EventUdsDtc(DTCContext->EventId) != DEM_CFG_DTC_UDS_INVALID)
    && (Dem_StorageCondition_TestEventStorageConditionsFulfilled(DTCContext->EventId) == TRUE))                                  
  {
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_Event_InternalStatusType lInternalStatus;
    Dem_DTCInternal_StoredStatusType lStoredStatus;

    lInternalStatus = Dem_DTC_GetInternalStatus(DTCContext->EventId);
    lStoredStatus = Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus);
    if ( (lStoredStatus == Dem_DTCInternalStatus_StoredStatus_Active)
      || (lStoredStatus == Dem_DTCInternalStatus_StoredStatus_Aging))
    {
      lMemoryIndex = Dem_Memory_FindMemoryIndex_StoredEvent(DTCContext->EventId);
#if (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)
      if (Dem_MemoryEntry_TestAgingOnlyEntry(Dem_MemoryEntry_GetId(lMemoryIndex)) == FALSE)
#endif
      {
        EventContext->DataModified = DEM_DATA_TEST_USERDATA_CHANGED(                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
                                     Dem_Memory_UpdateEventEntryOnPassed(DTCContext->EventId, DTCContext->DtcEffects, lMemoryIndex)); 

        if (EventContext->DataModified == TRUE)
        {
          if (Dem_Cfg_EventSupportImmediateNv(DTCContext->EventId) == TRUE)
          {
            Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
          }
          else
          {
            Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
          }
        }
      }
    }
  }
#endif

  /* Aging needs to be processed after event entry update at passed due
     feature retain in memory */
  Dem_DTC_ProcessAgingOnPassed(DTCContext);                                                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
    Dem_Prestore_StateSetDiscard();
#endif

  DEM_IGNORE_UNUSED_ARGUMENT(EventContext->DataModified)                                                                         /* PRQA S 1338, 3112 */ /* MD_MSR_DummyStmt, MD_DEM_14.2 */ /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_DTC_ProcessStorage
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ProcessStorage(
  CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext,
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
  )
{
  Dem_Cfg_MemoryIndexType lMemoryIndex;
  boolean lIsOccurrence;
  uint8 lBlockModification;

  lMemoryIndex = DEM_MEM_INVALID_MEMORY_INDEX;
  lIsOccurrence = FALSE;
  lBlockModification = DEM_DATA_NO_CHANGES;

  if (Dem_DTC_TestStoredStatus(DTCContext->EventId) == FALSE)
  { /* Not stored yet - If no entry can be created we need to discard some updates */
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
    /* Storage was not possible, discard changes to the status byte */
    EventContext->EventEffects = DEM_CFG_TRIGGER_NONE;                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    DTCContext->DtcEffects = DEM_CFG_TRIGGER_NONE;                                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#else
    if ((DTCContext->DtcEffects & DEM_ESM_EVENT_STORAGE_TRIGGER) != 0u)
    { /* We have to store this event in memory */
      lMemoryIndex = Dem_DTC_EventCreateMemory(DTCContext->EventId);
    }
    if (lMemoryIndex == DEM_MEM_INVALID_MEMORY_INDEX)
    { /* Storage was not possible, discard changes that require storage */
      EventContext->EventEffects = (Dem_Cfg_StorageTriggerType)(EventContext->EventEffects & DEM_ESM_EVENT_RESET_TRIGGER_MASK);  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      DTCContext->DtcEffects = (Dem_Cfg_StorageTriggerType)(DTCContext->DtcEffects & DEM_ESM_EVENT_RESET_TRIGGER_MASK);          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    else
    {
      EventContext->EventEffects = (Dem_Cfg_StorageTriggerType)(EventContext->EventEffects | DEM_ESM_EVENT_CATCHUP_TRIGGER);     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      DTCContext->DtcEffects = (Dem_Cfg_StorageTriggerType)(DTCContext->DtcEffects | DEM_ESM_EVENT_CATCHUP_TRIGGER);             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

      Dem_DTC_SetFdcToc(DTCContext->EventId);
    }
#endif
  }
  else
  { /* Already stored - Update the existing entry if necessary */

    lMemoryIndex = Dem_Memory_FindMemoryIndex_StoredEvent(DTCContext->EventId);

    if (Dem_Memory_TestEventEntryUpdatable(DTCContext->EventId, lMemoryIndex) == FALSE)
    {
      if ((DTCContext->DtcEffects & DEM_ESM_EVENT_STORAGE_TRIGGER) != 0u)
      { /* Reclaim event memory entry */
        Dem_DTC_EventEntryReInit(DTCContext->EventId, lMemoryIndex);

        EventContext->EventEffects = (Dem_Cfg_StorageTriggerType)(EventContext->EventEffects | DEM_ESM_EVENT_CATCHUP_TRIGGER);   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        DTCContext->DtcEffects = (Dem_Cfg_StorageTriggerType)(DTCContext->DtcEffects | DEM_ESM_EVENT_CATCHUP_TRIGGER);           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

        lIsOccurrence = TRUE;
      }
      else
      {
        if (Dem_MemoryEntry_TestAgingOnlyEntry(Dem_MemoryEntry_GetId(lMemoryIndex)) == TRUE)
        {
          Dem_DTC_FreeEventAgingOnly(DTCContext->EventId, lMemoryIndex);
        }
        lMemoryIndex = DEM_MEM_INVALID_MEMORY_INDEX;
      }
    }
  }

  if (Dem_Cfg_EventObdRelated(DTCContext->EventId) == TRUE)
  { /* store OBD II Freeze Frame depending on DTC triggers, no event entry required */
    Dem_Memory_TriggerObdIIFreezeFrameStorage(DTCContext);                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    if (DTCContext->QualifyDTC == TRUE)
    {
      /* Qualify status of event has to be updated */
      EventContext->QualifyEvent = TRUE;                                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }

  if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
  {
#if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_WRITELIMIT == STD_ON)
    uint16 lOldOccurrenceCount;
#endif

    if ((DTCContext->DtcEffects & DEM_ESM_EVENT_OCCURENCE_TRIGGER) != 0u)
    {
      lIsOccurrence = TRUE;
    }
    if (lIsOccurrence == TRUE)
    {
      /* event storage or update trigger matched */
      Dem_Memory_UpdateChronology(DTCContext->EventId, lMemoryIndex);
      lBlockModification |= DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
    }

#if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_WRITELIMIT == STD_ON)
    lOldOccurrenceCount = Dem_MemoryEntry_GetOccurrenceCounter(Dem_MemoryEntry_GetId(lMemoryIndex));
#endif
#if (DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
    /* initialize the CyclesSinceFirstFailed counter when not done yet, e.g. due memory entry allocation via FDC */
    if (Dem_MemoryEntry_GetCyclesSinceFirstFailed(Dem_MemoryEntry_GetId(lMemoryIndex)) == DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID)
    {
      Dem_MemoryEntry_SetCyclesSinceFirstFailed(Dem_MemoryEntry_GetId(lMemoryIndex), Dem_OperationCycle_GetCycleCounter(Dem_Cfg_EventOperationCycle(DTCContext->EventId)));
      lBlockModification |= DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
    }
#endif

    if (Dem_Cfg_EventObdRelated(DTCContext->EventId) == TRUE)
    { /* OBD related Event, store Freeze Frame */
      lBlockModification |= Dem_Memory_TriggerWWHOBDFreezeFrameStorage(DTCContext->EventId, DTCContext->DtcEffects, lMemoryIndex); 
    }

    lBlockModification |= Dem_Memory_UpdateEventEntryOnFailed(DTCContext->EventId, DTCContext->DtcEffects, lMemoryIndex);

    if ((DEM_DATA_TEST_USERDATA_CHANGED(lBlockModification)
      || (lIsOccurrence == TRUE))
      && (Dem_Cfg_EventSupportImmediateNv(DTCContext->EventId) == TRUE))                                                         
    {
      /* If the event is configured for immediate NV updates, set the entries NV state to immediate update */
#if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_WRITELIMIT == STD_ON)
      uint16 lNewOccurrenceCount;
      lNewOccurrenceCount = Dem_MemoryEntry_GetOccurrenceCounter(Dem_MemoryEntry_GetId(lMemoryIndex));
      Dem_Nvm_TestAndSetBlockStateImmediate(lMemoryIndex,
                                            lOldOccurrenceCount,
                                            lNewOccurrenceCount);
#else
    Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
#endif
    }
    else
    {
      if (lBlockModification != DEM_DATA_NO_CHANGES)
      {
        /* Otherwise set the entries NV state to 'DIRTY' */
        Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
      }
      else
      {
        /* MISRA */
      }
    }
    EventContext->DataModified = (boolean)DEM_DATA_TEST_USERDATA_CHANGED(lBlockModification);                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }

  /* store time series snapshot records when event is confirmed */
  if ( (Dem_Memory_TimeSeries_TestEventSupportTimeSeries(EventContext->EventId) == TRUE)
    && (Dem_Memory_TimeSeries_IsPowertrainEnabled() == FALSE)
    && ((EventContext->EventEffects & DEM_CFG_TRIGGER_CONFIRMED) != 0u))
  {
    Dem_Memory_TimeSeries_CreateEntry(EventContext->EventId);
  }
}                                                                                                                                /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) && \
    ((DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON) || (DEM_CFG_STORAGE_AT_FDC == STD_ON))
/* ****************************************************************************
 % Dem_DTC_FdcTrip
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_FdcTrip(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  Dem_Cfg_MemoryIndexType lMemoryIndex;

  lMemoryIndex = DEM_MEM_INVALID_MEMORY_INDEX;                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */

  Dem_Event_DataUpdateStart(EventId);
  if (Dem_DTC_TestStoredStatus(EventId) == FALSE)
  {
# if (DEM_CFG_STORAGE_AT_FDC == STD_ON)
    /* FdcTrip is the storage trigger and the event is not yet stored */
    lMemoryIndex = Dem_DTC_EventCreateMemory(EventId);

    /* store time series snapshot records when event gets stored */
    if ( (Dem_Memory_TimeSeries_TestEventSupportTimeSeries(EventId) == TRUE)
      && ((lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX))
      && (Dem_Memory_TimeSeries_IsPowertrainEnabled() == TRUE))
    {
      Dem_Memory_TimeSeries_CreateEntry(EventId);
    }
 # endif
  }
  else
  {
    lMemoryIndex = Dem_Memory_FindMemoryIndex_StoredEvent(EventId);

    if (Dem_Memory_TestEventEntryUpdatable(EventId, lMemoryIndex) == FALSE)
    {
# if (DEM_CFG_STORAGE_AT_FDC == STD_ON)
      /* Storage trigger reached - reclaim event entry */
       Dem_DTC_EventEntryReInit(EventId, lMemoryIndex);

       /* Store time series snapshot records when event gets re-stored - 
          Time Series entry is not retained in memory - no reinit required*/
       if ( (Dem_Memory_TimeSeries_TestEventSupportTimeSeries(EventId) == TRUE)
         && (Dem_Memory_TimeSeries_IsPowertrainEnabled() == TRUE))
       {
         Dem_Memory_TimeSeries_CreateEntry(EventId);
       }
# else
      lMemoryIndex = DEM_MEM_INVALID_MEMORY_INDEX;
# endif
    }
  }

  if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
  {
    uint8 lBlockModification;
    Dem_Cfg_StorageTriggerType lUpdateFlags;

# if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
    if (Dem_DTC_GetAgingCounter(EventId, Dem_MemoryEntry_GetId(lMemoryIndex)) == DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
    {
      Dem_DTC_TestAndInvalidateAgingCounter(EventId);
    }
# endif

    lUpdateFlags = Dem_DTC_CalcFdcUpdateFlags(EventId);

# if (DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON)

    /* Set internal status to FdcToc only when not yet set for event */
    if (( (lUpdateFlags & DEM_CFG_TRIGGER_FDC_FIRST_IN_CYCLE) != 0u)
#  if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
      || (Dem_DTCInternalStatus_TestFdcToc(Dem_Event_GetInternalStatus(EventId)) == FALSE)
#  endif
      )
    {
      Dem_DTC_SetFdcToc(EventId);
    }
# endif

    lBlockModification = Dem_Memory_UpdateEventEntryOnFailed(EventId, lUpdateFlags, lMemoryIndex);

    if (DEM_DATA_TEST_USERDATA_CHANGED(lBlockModification))
    {
      if (Dem_Cfg_EventSupportImmediateNv(EventId) == TRUE)
      {
        Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
      }
      else
      {
        Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
      }
    }

    if (DEM_DATA_TEST_USERDATA_CHANGED(lBlockModification) == TRUE)
    {
      Dem_Notifications_EventDataChanged(EventId);
    }
  }
  Dem_Event_DataUpdateFinish(EventId);
# if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
  Dem_Prestore_StateSetDiscard();
# endif
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
/* ****************************************************************************
 % Dem_DTC_CustomizedFdcTrip
 *****************************************************************************/
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
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CustomizedFdcTrip(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  TCTOC,
  CONST(boolean, AUTOMATIC)  FdcThresholdExceeded,
  CONST(boolean, AUTOMATIC)  FdcMaximumExceeded
  )
{
  if ( (Dem_DTC_TestStoredStatus(EventId) == TRUE) || (FdcThresholdExceeded == TRUE) )
  {
    Dem_Event_DataUpdateStart(EventId);
#if (DEM_FEATURE_NEED_HEALINGCOUNTER == STD_ON)
    if (Dem_UDSStatus_Test_PDTC(Dem_Event_GetUDSStatus(EventId)) == FALSE)
    {
      Dem_Event_SetTripCount(EventId, 0);
    }
#endif

    /* Don't store internal events (i.e. events without a DTC attached) */
    if ( (Dem_Cfg_EventUdsDtc(EventId) != DEM_CFG_DTC_UDS_INVALID)
         /* Don't store with disabled storage conditions */
      && (Dem_StorageCondition_TestEventStorageConditionsFulfilled(EventId) == TRUE) )                                             
    {
      Dem_Cfg_MemoryIndexType lMemoryIndex;
      boolean lNewEntry;

      if (Dem_DTCInternalStatus_GetStoredStatus(Dem_Event_GetInternalStatus(EventId)) != Dem_DTCInternalStatus_StoredStatus_None)
      { /* Already stored - Find, *but don't update* the memory entry */
        lNewEntry = FALSE;
        lMemoryIndex = Dem_Memory_FindMemoryIndex_StoredEvent(EventId);
      }
      else
      { /* Not stored yet */
        lNewEntry = TRUE;
        lMemoryIndex = Dem_DTC_EventCreateMemory(EventId);
      }

      if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
      {
        Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;

        lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);

        if (FdcThresholdExceeded == TRUE)
        {
          Dem_DTC_UDSStatusType lOldPreconfirmedStatus;
          Dem_DTC_UDSStatusType lNewPreconfirmedStatus;
          Dem_Cfg_StorageTriggerType lEffects;
          uint8 lBlockModification;

          lOldPreconfirmedStatus = Dem_MemoryEntry_GetPreConfirmedStatus(lMemoryEntryId);

          if (DEM_DTC_TEST_PC_STATUS_ADTC(lOldPreconfirmedStatus) == TRUE)
          { /* Reclaim aged event */
            lNewEntry = TRUE;
            Dem_MemoryEntry_InitializeEntry(lMemoryEntryId);
            lOldPreconfirmedStatus = Dem_MemoryEntry_GetPreConfirmedStatus(lMemoryEntryId);
          }

          lNewPreconfirmedStatus = lOldPreconfirmedStatus;
          lNewPreconfirmedStatus = DEM_DTC_SET_PC_STATUS_UDTC(lNewPreconfirmedStatus);
          lNewPreconfirmedStatus = DEM_DTC_SET_PC_STATUS_UDTCTOC(lNewPreconfirmedStatus);
          lNewPreconfirmedStatus = DEM_DTC_SET_PC_STATUS_UDTCSLC(lNewPreconfirmedStatus);

          Dem_MemoryEntry_SetPreConfirmedStatus(lMemoryEntryId, lNewPreconfirmedStatus);
          lEffects = DEM_CFG_TRIGGER_FDC;

          /* reset OCC1,2 (cycles without preconfirmed result) */
          {
            Dem_MemoryEntry_SetOccurrenceCounter1(lMemoryEntryId, 0);
            Dem_MemoryEntry_SetOccurrenceCounter2(lMemoryEntryId, 0);
          }

          if (DEM_DTC_TEST_PC_STATUS_UDTCTOC(lOldPreconfirmedStatus) == FALSE)
          { /* OCC4 at most once per cycle */
            if (Dem_MemoryEntry_GetOccurrenceCounter4(lMemoryEntryId) < 0xffU)
            {
              Dem_MemoryEntry_SetOccurrenceCounter4(lMemoryEntryId, Dem_MemoryEntry_GetOccurrenceCounter4(lMemoryEntryId) + 1u);
            }

            if ( /* Only increment existing counters */
              (lNewEntry == FALSE)
              /* If we are here, the preconfirmed limit has been exceeded on an already stored event. */
              /* Only increment if the event is not yet tested this cycle (exceeded the counter, not yet tested passed) */
              && ((Dem_UDSStatus_Test_TNCTOC(Dem_Event_GetUDSStatus(EventId)) == TRUE)                                              
                 /* Or increment if it is THIS test that has reset the Tested-Bit (e.g. test not debounced) */
                || (TCTOC == TRUE)))
            {
              if (Dem_MemoryEntry_GetOccurrenceCounter7(lMemoryEntryId) < 0xffU)
              {
                Dem_MemoryEntry_SetOccurrenceCounter7(lMemoryEntryId, Dem_MemoryEntry_GetOccurrenceCounter7(lMemoryEntryId) + 1u);
              }
            }

            lEffects = (Dem_Cfg_StorageTriggerType)(lEffects | DEM_CFG_TRIGGER_FIRSTTHISCYCLE);
          }

          lBlockModification = Dem_Memory_UpdateEventEntryOnFailed(EventId, lEffects, lMemoryIndex);

          if (Dem_Cfg_EventSupportImmediateNv(EventId) == TRUE)
          {
            Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
          }
          else
          {
            Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
          }

          if (DEM_DATA_TEST_USERDATA_CHANGED(lBlockModification) == TRUE)
          {
            Dem_Notifications_EventDataChanged(EventId);
          }
        }

        if (FdcMaximumExceeded == TRUE)
        {
          /* FDC 12 -> Max FDC since last clear */
          if (Dem_MemoryEntry_GetDebounceValueMax(lMemoryEntryId) < Dem_DebounceBaseSat_GetDebounceValueMax(EventId))
          {
            Dem_MemoryEntry_SetDebounceValueMax(lMemoryEntryId, Dem_DebounceBaseSat_GetDebounceValueMax(EventId));
            Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
          }
        }
      }
      /* else: Storage was not possible */
    }
    Dem_Event_DataUpdateFinish(EventId);

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
    /* Prestored data is discarded unconditionally even when storage fails */
    Dem_Prestore_StateSetDiscard();
#endif
  }
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

#endif

#if ((DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON) \
      && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 % Dem_DTC_UpdateFdcMax
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_UpdateFdcMax(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  if (Dem_DTC_TestStoredStatus(EventId) == TRUE)
  { /* Already stored - Find, *but don't update* the memory entry */
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;

    lMemoryIndex = Dem_Memory_FindMemoryIndex_StoredEvent(EventId);
    lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);

# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    if (Dem_Cfg_EventCombinedGroup(EventId) != DEM_CFG_COMBINED_GROUP_INVALID)
    {
      /* synchronize the current max FDC with the stored FDC max value */
      sint8 lOldFdc;
      sint8 lNewFdc;

      lOldFdc = (sint8) Dem_MemoryEntry_GetDebounceValueMax(lMemoryEntryId);
      lNewFdc = Dem_DTC_CombinedGroupGetFDCMax(Dem_Cfg_EventCombinedGroup(EventId));
      if (lOldFdc < lNewFdc)
      {
        Dem_MemoryEntry_SetDebounceValueMax(lMemoryEntryId, (sint16)lNewFdc);
        Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
      }
    }
    else
# endif
    {
      /* synchronize the current max FDC with the stored FDC max value */
      sint8 lOldFdc;
      sint8 lNewFdc;

      lOldFdc = (sint8)Dem_MemoryEntry_GetDebounceValueMax(lMemoryEntryId);
      lNewFdc = Dem_Satellite_GetMaxFaultDetectionCounter(
          Dem_Cfg_EventSatelliteId(EventId),
          Dem_Cfg_EventSatelliteEventId(EventId));
      if (lOldFdc < lNewFdc)
      {
        Dem_MemoryEntry_SetDebounceValueMax(lMemoryEntryId, (sint16)lNewFdc);
        Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
      }
    }
    /*
    No data changed callbacks for modified internal data
    */
  }
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_DTC_Disconnect
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Disconnect(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  if (Dem_Cfg_EventCombinedGroup(EventId) != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_DTC_Disconnect_Combined(EventId);
  }
  else
# endif
  {

    Dem_Event_Disconnect_Normal(EventId);
  }
}
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_DTC_Reconnect
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_DTC_Reconnect(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  if (Dem_Cfg_EventCombinedGroup(EventId) != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_DTC_Reconnect_Combined(EventId);
  }
  else
# endif
  {
    Dem_Event_Reconnect_Normal(EventId);
  }
}
#endif

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 % Dem_DTC_GetWIRStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_GetWIRStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
 return (boolean)(Dem_DTCInternalStatus_TestUserControlledWir(Dem_Event_GetInternalStatus(EventId)));
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 % Dem_DTC_SetWIRStatus
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_SetWIRStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC) WIRStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Event_InternalStatusType lInternalStatus;

  lReturnValue = E_NOT_OK;
# if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR_DURING_CDTCS == STD_OFF)
  if (Dem_EnableCondition_TestEnableConditionFulfilled(DEM_ENABLECONDITION_CONTROLDTCSETTING) == TRUE)
# endif
  {
    /* DTC setting is enabled, proceed */
    if (Dem_DTCInternalStatus_TestUserControlledWir(Dem_Event_GetInternalStatus(EventId)) != WIRStatus)
    {
      uint8 lOldExternalDtcStatus;
      uint8 lNewExternalDtcStatus;
      /* override status has to be changed */
      lOldExternalDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
      Dem_EnterCritical_DiagMonitor();

      /* update internal status bit */
      lInternalStatus = Dem_Event_GetInternalStatus(EventId);
      if (WIRStatus == FALSE)
      {
        lInternalStatus = Dem_DTCInternalStatus_ResetUserControlledWir(lInternalStatus);
      }
      else
      {
        lInternalStatus = Dem_DTCInternalStatus_SetUserControlledWir(lInternalStatus);
      }
      Dem_Event_SetInternalStatus(EventId, lInternalStatus);

      Dem_LeaveCritical_DiagMonitor();
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

      lNewExternalDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));
      Dem_Notifications_DtcStatusChanged(EventId,
                                         lOldExternalDtcStatus,
                                         lNewExternalDtcStatus,
                                         DEM_NOTIFICATIONS_USER_WIR);
    }

    lReturnValue = E_OK;
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_DTC_CycleQualifyDcy
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CycleQualifyDcy(
  void
  )
{
# if (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
  Dem_DTC_CycleQualifyDcy_AllDtc();
# else
#  if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
  Dem_DTC_CycleQualifyDcy_EventCombType2_StoredOnly();
#  else
  Dem_DTC_CycleQualifyDcy_StoredOnly();
#  endif
# endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


/* ****************************************************************************
 % Dem_DTC_OpCycle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_OpCycle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  )
{
  Dem_DTC_ForEachCombinedArgType lArgs;
  lArgs.Specific.EventOpCycle_Internal.CycleStatus = CycleStatus;
  Dem_DTC_ForEachCombinedSubEvent(EventId, Dem_Event_OpCycle, &lArgs);                                                           /* SBSW_DEM_CALL_FOREACH_COMBINED_EVENT */
}

/* ****************************************************************************
 % Dem_DTC_InitQualification
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InitQualification(
  void
  )
{
#if(DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF)
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    Dem_EventIdType lEventId;
    Dem_Memory_AllocMemEntriesIterType lStoredEventsIter;

    /* Scan the primary memory and extract qualified warningIndicatorRequested and confirmedDTC status */
    for (Dem_Memory_AllocMemEntriesChrono_IterInit(DEM_CFG_MEMORYID_PRIMARY, &lStoredEventsIter);                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Memory_AllocMemEntriesChrono_IterExists(&lStoredEventsIter) == TRUE;                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Memory_AllocMemEntriesChrono_IterNext(&lStoredEventsIter))                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_Cfg_MemoryIndexType lMemoryIndex;
      Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
      uint8 lEntryState;

      lMemoryIndex = Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex(&lStoredEventsIter);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);
      lEventId = Dem_MemoryEntry_GetEventId(lMemoryEntryId);

      if ( (Dem_Event_TestValidHandle(lEventId) == TRUE)
        && (Dem_Cfg_EventObdRelated(lEventId) == TRUE))
      { /* only OBD related events supports the qualification of Confirmed and WIR bit */
        lEntryState = Dem_MemoryEntry_GetState(lMemoryEntryId);
        Dem_DTC_SetQualifyStatus(lEventId, DEM_MEM_SET_NON_QUALIFIED_STATUS_BITS(lEntryState));
      }
    }
  }
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DTC_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Init(
  void
  )
{
#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  {
    lGroupId = Dem_Cfg_GlobalCombinedGroupCount();
    while (lGroupId > 0u)
    {
      --lGroupId;
      Dem_DTC_InitGroupInternalStatus(lGroupId);
      Dem_DTC_SetCombinedGroupUDSStatus(lGroupId, Dem_DTC_CalculateCombineGroupUdsStatus(lGroupId));
    }
  }
#endif

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  {
    Dem_EventIdType lEventId;
    Dem_DTC_InternalStatusType lInternalStatus;

    for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
    {
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
      /* Only process master events with memory entry */
      if (Dem_Cfg_GetMasterEvent(lEventId) != lEventId)
      {
        continue;                                                                                                                
      }
# endif

      lInternalStatus = Dem_DTC_GetInternalStatus(lEventId);

      /* Invalidate the aging counter of events which are not stored and confirmed */
      if ((Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) == Dem_DTCInternalStatus_StoredStatus_None)
        && (Dem_UDSStatus_Test_CDTC(Dem_DTC_RetrieveStatus(lEventId)) == FALSE))                                                 
      {
        Dem_DTC_TestAndInvalidateAgingCounter(lEventId);
      }
    }
  }
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DTC_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_PreInit(
  void
  )
{
#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  {
    Dem_Cfg_CombinedGroupIndexType lGroupId;
    for (lGroupId = 0u; lGroupId < Dem_Cfg_GlobalCombinedGroupCount(); ++lGroupId)
    {
      Dem_Event_InternalStatusType lInternalStatus;
      Dem_Cfg_CombinedGroupIterType lSubEventIter;

      lInternalStatus = Dem_EventInternalStatus_SetEventDisconnected(0);
      for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lSubEventIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Cfg_CombinedGroupIterExists(&lSubEventIter) == TRUE;                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Cfg_CombinedGroupIterNext(&lSubEventIter))                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        if (Dem_Cfg_EventAvailableByVariant(Dem_Cfg_CombinedGroupIterGet(&lSubEventIter)) == TRUE)                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          lInternalStatus = Dem_EventInternalStatus_SetAvailableInVariant(lInternalStatus);
        }
        if (Dem_Cfg_EventAvailableByDefault(Dem_Cfg_CombinedGroupIterGet(&lSubEventIter)) == TRUE)                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          lInternalStatus = Dem_EventInternalStatus_ResetEventDisconnected(lInternalStatus);
        }
      }
      Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, lInternalStatus);
    }
  }
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DTC_SetAgingCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_SetAgingCounter(                                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(uint16, AUTOMATIC) AgingCounter
  )
{
#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  if (Dem_Cfg_EventUdsDtc(EventId) != DEM_CFG_DTC_UDS_INVALID)
  {
    Dem_Event_SetAgingCounter(EventId, AgingCounter);
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_AGINGDATA),
                                DEM_NVM_BLOCKSTATE_DIRTY);
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryIndex)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  }
  else
  {
    /* MISRA */
  }
#else
  {
    Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
    lMemoryEntryId = Dem_MemoryEntry_GetId(MemoryIndex);
    Dem_MemoryEntry_SetAgingCounter(lMemoryEntryId, AgingCounter);
    Dem_Nvm_SetEventMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  }
#endif
}

/* ****************************************************************************
 % Dem_DTC_GetAgingCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_DTC_GetAgingCounter(                                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC) MemoryEntryId
  )
{
  uint16 lAgingCounter;

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  {
    lAgingCounter = Dem_Event_GetAgingCounter(EventId);
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  }
#else
  {
    lAgingCounter = Dem_MemoryEntry_GetAgingCounter(MemoryEntryId);
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  }
#endif

  return lAgingCounter;
}

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
/* ****************************************************************************
 % Dem_DTC_TestAndInvalidateAgingCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_TestAndInvalidateAgingCounter(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  if ((Dem_Cfg_EventUdsDtc(EventId) != DEM_CFG_DTC_UDS_INVALID)
      && (Dem_Event_GetAgingCounter(EventId) != DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID))                                          
  {
    Dem_Event_SetAgingCounter(EventId, DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID);
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_AGINGDATA),
                                DEM_NVM_BLOCKSTATE_DIRTY);
  }
}
#endif

/* ****************************************************************************
 % Dem_DTC_ResetAging
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ResetAging(                                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  Dem_DTC_TestAndInvalidateAgingCounter(EventId);
#else
# if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
  if(Dem_DTCInternalStatus_GetStoredStatus(Dem_DTC_GetInternalStatus(EventId)) == Dem_DTCInternalStatus_StoredStatus_Aging)
  {
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    lMemoryIndex = Dem_Memory_FindMemoryIndex_StoredEvent(EventId);
    Dem_DTC_SetAgingCounter(EventId, lMemoryIndex, DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID);
#  if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
    if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
    {
      Dem_MemoryEntry_SetAgingTimer(Dem_MemoryEntry_GetId(lMemoryIndex), DEM_MEMORYENTRY_AGINGTIME_INVALID);
    }
#  endif
    Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
  }
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId);                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
/* ****************************************************************************
 % Dem_DTC_GetAgingStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_DTC_AgingStatusType, DEM_CODE)
Dem_DTC_GetAgingStatus(                                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_AgingStatusType lAgingStatus;
  uint16 lEventAgingCounter;

  lAgingStatus = Dem_DTC_AgingStatusNone;
  lEventAgingCounter = Dem_Event_GetAgingCounter(EventId);
  if (lEventAgingCounter <= DEM_OPERATIONCYCLE_CYCLECOUNT_MAX)
  {
    lAgingStatus = Dem_DTC_AgingStatusInProgress;
  }
  else if ((lEventAgingCounter == DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED)
          || (lEventAgingCounter == DEM_OPERATIONCYCLE_CYCLECOUNT_AGED))
  {
    lAgingStatus = Dem_DTC_AgingStatusAged;
  }
  else
  {
    /* MISRA */
  }

  return lAgingStatus;
}
#endif

#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_SetQualificationProcessedCombinedDTC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetQualificationProcessedCombinedDTC(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) GroupId
  )
{
  Dem_DTC_SetCombinedGroupProcessed(GroupId, Dem_DTC_QualificationProcessedCombinedDTCs);                                        /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
}
#endif


/* ****************************************************************************
% Dem_DTC_QualifySingleDTC
*****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_QualifySingleDTC(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  const Dem_EventIdType EventId
)
{
# if (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
  uint8 lOldDtcStatus;
  Dem_DTC_ForEachCombinedArgType lArgs;
# if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
  boolean lOldMilIsActive;

  lOldMilIsActive = Dem_Indicator_TestMilReportedActive();
# endif


  lOldDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));

  /* Process the DTC status qualification of the stored event or combination group */
  Dem_DTC_ForEachCombinedSubEvent(EventId, Dem_Event_CycleQualifyDcy, &lArgs);                              /* SBSW_DEM_CALL_FOREACH_COMBINED_EVENT */ 
  Dem_Indicator_UpdateGlobalUserIndicatorForEvent(EventId);

# if (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
  /* Qualification state is stored in Status Block */
  Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_STATUS),
    DEM_NVM_BLOCKSTATE_DIRTY);
#else
/* Qualification state is stored in Memory Entry */
  if (Dem_DTC_TestStoredStatus(EventId) == TRUE)
  { /* Update qualification status in memory entry */
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    lMemoryIndex = Dem_Memory_FindMemoryIndex_StoredEvent(EventId);
    Dem_Event_UpdateQualificationStatus(EventId, lMemoryIndex);
    Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
  }
#endif


# if (DEM_CFG_SUPPORT_PERMANENTDTC_IMMEDIATE_VISIBLE == STD_ON)
  if ((Dem_UDSStatus_Test_WIR(lOldDtcStatus) == FALSE)
    && (Dem_UDSStatus_Test_WIR(lArgs.Common.NewDtcStatus) == TRUE))                                                            
  {
    Dem_Memory_UpdatePermanentEntryVisibility(EventId);
  }
#endif
  Dem_Notifications_DtcStatusChanged(EventId,
    lOldDtcStatus,
    lArgs.Common.NewDtcStatus,
    DEM_NOTIFICATIONS_CYCLE_QUALIFIED);
  if (Dem_UDSStatus_Test_CDTC((uint8)(lOldDtcStatus ^ lArgs.Common.NewDtcStatus)) == TRUE)
  {
    Dem_Notifications_EventDataChanged(EventId);
  }

  /* Synchronize the special indicator states */
  Dem_Indicator_UpdateSpecialIndicators();
# if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
  if ((lOldMilIsActive == FALSE)
    && (Dem_Indicator_TestMilReportedActive() == TRUE))                                                                         /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
  {
    Dem_Indicator_UpdatePIDsMilEnabled();
  }
# endif
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId);                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
% Dem_DTC_TestDtcActive
*****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcActive(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  const Dem_EventIdType EventId
  )
{
  boolean lIsActive;
  uint8 lDtcStatus;
  lDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));
  if (((Dem_UDSStatus_Test_TF(lDtcStatus) == TRUE) && (Dem_UDSStatus_Test_CDTC(lDtcStatus) == TRUE))
    || ((Dem_Cfg_IsObdSupportedInVariant() == TRUE) && (Dem_Event_TestMilSupport(EventId) == TRUE) && (Dem_UDSStatus_Test_WIR(lDtcStatus) == TRUE))
     )
  {
    lIsActive = TRUE;
  }
  else
  {
    lIsActive = FALSE;
  }
  return lIsActive;
}

/* ****************************************************************************
% Dem_DTC_TestDtcPreviouslyActive
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcPreviouslyActive(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  const Dem_EventIdType EventId
  )
{
  boolean lIsPreviouslyActive;
  uint8 lDtcStatus;
  lDtcStatus = Dem_DTC_GenerateExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));
  if ((Dem_UDSStatus_Test_TF(lDtcStatus) == FALSE) && (Dem_UDSStatus_Test_CDTC(lDtcStatus) == TRUE)
    && ((Dem_Cfg_IsObdSupportedInVariant() == FALSE) || ((Dem_Event_TestMilSupport(EventId) == FALSE) || (Dem_UDSStatus_Test_WIR(lDtcStatus) == FALSE))))
  {
    lIsPreviouslyActive = TRUE;
  }
  else
  {
    lIsPreviouslyActive = FALSE;
  }
  return lIsPreviouslyActive;
}

/* ****************************************************************************
 % Dem_DTC_GetFormatedDTCByEvent
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_GetFormatedDTCByEvent(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  Dem_EventIdType lEventId,
  Dem_DTCFormatType DTCFormat,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC
)
{
  Std_ReturnType lReturnValue;
  uint32 lTempDtc;

  lReturnValue = E_NOT_OK;

  switch (DTCFormat)
  {
  case DEM_DTC_FORMAT_UDS:
    lTempDtc = Dem_Cfg_EventUdsDtc(lEventId);
    if (lTempDtc != DEM_CFG_DTC_UDS_INVALID)
    {
      *DTC = lTempDtc;                                                                                                           /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
    }
    break;

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
  case DEM_DTC_FORMAT_J1939:
    lTempDtc = Dem_Cfg_EventJ1939Dtc(lEventId);
    if (lTempDtc != DEM_CFG_DTC_J1939_INVALID)
    {
      *DTC = lTempDtc;                                                                                                           /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
    }
    break;
#endif /* (DEM_CFG_SUPPORT_J1939 == STD_ON) */

  case DEM_DTC_FORMAT_OBD:
    if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
    {
      lTempDtc = Dem_Cfg_EventObdDtc(lEventId);
      if (lTempDtc != DEM_CFG_DTC_OBD_INVALID)
      { /* copy valid DTC number to out parameter */
        *DTC = (uint32)(lTempDtc << 8u);                                                                                         /* SBSW_DEM_POINTER_WRITE_API */
        lReturnValue = E_OK;
      }
    }
    else if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
    {
      lTempDtc = Dem_Cfg_EventUdsDtc(lEventId);
      if (DEM_CFG_DTC_UDS_INVALID != lTempDtc)
      {
        *DTC = lTempDtc;                                                                                                         /* SBSW_DEM_POINTER_WRITE_API */
        lReturnValue = E_OK;
      }
    }
    else
    {
      /* MISRA case */
      /* E_NOT_OK */
    }
    break;

  default:
    /* MISRA CASE */
    break;
  }

  return lReturnValue;
}


/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DTCIF_IMPLEMENTATION_H */
/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCIF_Implementation.h
 *********************************************************************************************************************/
