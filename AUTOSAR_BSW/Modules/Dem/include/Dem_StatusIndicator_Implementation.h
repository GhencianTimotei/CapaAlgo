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
/*! \addtogroup Dem_StatusIndicator
 *  \{
 *  \file       Dem_StatusIndicator_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of StatusIndicator subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_STATUSINDICATOR_IMPLEMENTATION_H)
#define DEM_STATUSINDICATOR_IMPLEMENTATION_H

 /* ********************************************************************************************************************
  *  GLOBAL MISRA JUSTIFICATIONS
  *********************************************************************************************************************/
 /* PRQA S 2982 EOF */ /* MD_DEM_2982 */
 /* PRQA S 2991 EOF */ /* MD_DEM_2991 */
 /* PRQA S 2992 EOF */ /* MD_DEM_2992 */
 /* PRQA S 2995 EOF */ /* MD_DEM_2995 */
 /* PRQA S 2996 EOF */ /* MD_DEM_2996 */

 /* ********************************************************************************************************************
  * INCLUDES
  *********************************************************************************************************************/

                                                   /* Own subcomponent header */
 /* ------------------------------------------------------------------------- */
#include "Dem_StatusIndicator_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Satellite_Interface.h"
#include "Dem_FaultMemory_Interface.h"
#include "Dem_Infrastructure_Interface.h"
#include "Dem_DiagnosticObserver_Interface.h"
#include "Dem_DTC_Interface.h"
#include "Dem_Event_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*! Filename declaration */
#define DEM_STATUSINDICATOR_IMPLEMENTATION_FILENAME "Dem_StatusIndicator_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_StatusIndicator_PrivateProperties Private Properties
 * \{
 */

/* ****************************************************************************
 * Dem_StatusIndicator_Set_SSLC
 *****************************************************************************/
/*!
 * \brief         Set symptom since last clear bit of StatusIndicator byte.
 *
 * \details       Set symptom since last clear bit of StatusIndicator byte.
 *
 * \param[in]     StatusIndicator
 *                StatusIndicator byte
 *
 * \return        StatusIndicator byte with SSLC bit set
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_Type, DEM_CODE)
Dem_StatusIndicator_Set_SSLC(
  Dem_StatusIndicator_Type StatusIndicator
  );

/* ****************************************************************************
 * Dem_StatusIndicator_Set_WIRSLC
 *****************************************************************************/
/*!
 * \brief         Set warning indicator requested since last clear bit 
 *                of StatusIndicator byte.
 *
 * \details       Set warning indicator requested since last clear bit
 *                of StatusIndicator byte.
 *
 * \param[in]     StatusIndicator
 *                StatusIndicator byte.
 *
 * \return        StatusIndicator byte with WIRSLC bit set.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_Type, DEM_CODE)
Dem_StatusIndicator_Set_WIRSLC(
  Dem_StatusIndicator_Type StatusIndicator
  );

/* ****************************************************************************
 * Dem_StatusIndicator_Reset_WIRSLC
 *****************************************************************************/
/*!
 * \brief         Reset warning indicator requested since last clear bit
 *                of StatusIndicator byte.
 *
 * \details       Reset warning indicator requested since last clear bit
 *                of StatusIndicator byte.
 *
 * \param[in]     StatusIndicator
 *                StatusIndicator byte.
 *
 * \return        StatusIndicator byte with WIRSLC bit reset.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_Type, DEM_CODE)
Dem_StatusIndicator_Reset_WIRSLC(
  Dem_StatusIndicator_Type StatusIndicator
  );

/* ****************************************************************************
 * Dem_StatusIndicator_Set_ERDTC
 *****************************************************************************/
/*!
 * \brief         Set emission related DTC bit of StatusIndicator byte.
 *
 * \details       Set emission related DTC bit of StatusIndicator byte.
 *
 * \param[in]     StatusIndicator
 *                StatusIndicator byte.
 *
 * \return        StatusIndicator byte with ERDTC bit set.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_Type, DEM_CODE)
Dem_StatusIndicator_Set_ERDTC(
  Dem_StatusIndicator_Type StatusIndicator
  );

/* ****************************************************************************
 * Dem_StatusIndicator_Set_TFSLC
 *****************************************************************************/
/*!
 * \brief         Set test failed since last clear bit
 *                of StatusIndicator byte.
 *
 * \details       Set test failed since last clear bit
 *                of StatusIndicator byte.
 *
 * \param[in]     StatusIndicator
 *                StatusIndicator byte.
 *
 * \return        StatusIndicator byte with TFSLC bit set.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_Type, DEM_CODE)
Dem_StatusIndicator_Set_TFSLC(
  Dem_StatusIndicator_Type StatusIndicator
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
 /*!
  * \defgroup Dem_StatusIndicator_Private Private Methods
  * \{
  */

/* ****************************************************************************
 * Dem_StatusIndicator_SymptomAction
 *****************************************************************************/
/*!
 * \brief         Process the queued StatusIndicator symptom action.
 *
 * \details       Process the queued StatusIndicator symptom action.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StatusIndicator_SymptomAction(
  Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_StatusIndicator_ProcessSatelliteQueueActions
 *****************************************************************************/
/*!
 * \brief         Process queued StatusIndicator symptom actions.
 *
 * \details       Iterate over all events and process the queued StatusIndicator 
 *                symptom action.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StatusIndicator_ProcessSatelliteQueueActions(
  Dem_Satellite_IdType SatelliteId
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_StatusIndicator_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 % Dem_StatusIndicator_isStatusIndicatorEnabled()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StatusIndicator_isStatusIndicatorEnabled(void)
{
  return (boolean)(DEM_CFG_SUPPORT_SI30_STATUS == STD_ON);
}

/* ****************************************************************************
 % Dem_Satellite_IsExtendedFimEnabled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StatusIndicator_IsExtendedFimEnabled(void)
{
  return (boolean)(DEM_CFG_SUPPORT_EXTENDED_FIM == STD_ON);
}

/* ****************************************************************************
 % Dem_StatusIndicator_Test_WIRSLC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StatusIndicator_Test_WIRSLC(
  CONST(Dem_StatusIndicator_Type, AUTOMATIC) StatusIndicator
  )
{
  return (boolean)(((StatusIndicator) & DEM_STATUSINDICATOR_WIRSLC) != 0u);
}

/* ****************************************************************************
 % Dem_StatusIndicator_Test_TFSLC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StatusIndicator_Test_TFSLC(
  CONST(Dem_StatusIndicator_Type, AUTOMATIC) StatusIndicator
  )
{
  return (boolean)(((StatusIndicator) & DEM_STATUSINDICATOR_TFSLC) != 0u);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h" 

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_StatusIndicator_PrivateProperties Private Properties
 * \{
 */

/* ****************************************************************************
 % Dem_StatusIndicator_Set_SSLC()
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_Type, DEM_CODE)
Dem_StatusIndicator_Set_SSLC(
  Dem_StatusIndicator_Type StatusIndicator
)
{
  return (Dem_StatusIndicator_Type)((StatusIndicator) | DEM_STATUSINDICATOR_SSLC);
}

/* ****************************************************************************
 % Dem_StatusIndicator_Set_WIRSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_Type, DEM_CODE)
Dem_StatusIndicator_Set_WIRSLC(
  Dem_StatusIndicator_Type StatusIndicator
  )
{
  return (Dem_StatusIndicator_Type)((StatusIndicator) | DEM_STATUSINDICATOR_WIRSLC);
}

/* ****************************************************************************
 % Dem_StatusIndicator_Reset_WIRSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_Type, DEM_CODE)
Dem_StatusIndicator_Reset_WIRSLC(
  Dem_StatusIndicator_Type StatusIndicator
  )
{
  return (Dem_StatusIndicator_Type)((StatusIndicator) & ~DEM_STATUSINDICATOR_WIRSLC);
}

/* ****************************************************************************
 % Dem_StatusIndicator_Set_ERDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_Type, DEM_CODE)
Dem_StatusIndicator_Set_ERDTC(
  Dem_StatusIndicator_Type StatusIndicator
  )
{
  return (Dem_StatusIndicator_Type)((StatusIndicator) | DEM_STATUSINDICATOR_ERDTC);
}

/* ****************************************************************************
 % Dem_StatusIndicator_Set_TFSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_Type, DEM_CODE)
Dem_StatusIndicator_Set_TFSLC(
  Dem_StatusIndicator_Type StatusIndicator
  )
{
  return (Dem_StatusIndicator_Type)((StatusIndicator) | DEM_STATUSINDICATOR_TFSLC);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_StatusIndicator_Private Private Methods
 * \{
 */

/* ****************************************************************************
 % Dem_StatusIndicator_SymptomAction
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
Dem_StatusIndicator_SymptomAction(
  Dem_EventIdType EventId
  )
{
  Dem_DTCInternal_StoredStatusType lStoredStatus;

  lStoredStatus = Dem_DTCInternalStatus_GetStoredStatus(Dem_Event_GetInternalStatus(EventId));

  if ((lStoredStatus != Dem_DTCInternalStatus_StoredStatus_None) && (lStoredStatus != Dem_DTCInternalStatus_StoredStatus_Aged))
  {
    Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_StatusIndicator_Type lOldStatusIndicatorByte;
    Dem_StatusIndicator_Type lStatusIndicatorByte;

    lMemoryIndex = Dem_Memory_FindMemoryIndex_StoredEvent(EventId);
    lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);

    if (Dem_MemoryEntry_TestAgingOnlyEntry(lMemoryEntryId) == FALSE)
    {
      lOldStatusIndicatorByte = Dem_MemoryEntry_GetStatusIndicator(lMemoryEntryId);

      lStatusIndicatorByte = Dem_StatusIndicator_Set_SSLC(lOldStatusIndicatorByte);

      if (lStatusIndicatorByte != lOldStatusIndicatorByte)
      {
        Dem_MemoryEntry_SetStatusIndicator(lMemoryEntryId, lStatusIndicatorByte);

        Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
      }
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_StatusIndicator_ProcessSatelliteQueueActions
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
Dem_StatusIndicator_ProcessSatelliteQueueActions(
  Dem_Satellite_IdType SatelliteId
  )
{
  Dem_Satellite_MonitorIdType lMonitorId;

  for (lMonitorId = 0u; lMonitorId < Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId); ++lMonitorId)
  {
    if (Dem_Satellite_PeekStatusIndicatorActionQueue(SatelliteId, lMonitorId) != DEM_STATUSINDICATOR_QUEUE_INITIAL)
    {
      Dem_StatusIndicator_QueueActionType lStatusIndicatorQueueStatus;
      Dem_EventIdType lEventId;

      lStatusIndicatorQueueStatus = Dem_Satellite_ConsumeStatusIndicatorActionQueue(SatelliteId, lMonitorId);
      lEventId = Dem_Satellite_GetEventId(SatelliteId, lMonitorId);
      if (lStatusIndicatorQueueStatus == DEM_STATUSINDICATOR_QUEUE_SYMPTOM_REACHED)
      {
        Dem_StatusIndicator_SymptomAction(lEventId);
      }
    }
  }
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"
/*!
 * \defgroup Dem_StatusIndicator_ApiFunctions Api Functions
 * \{
 */

/* ****************************************************************************
  % Dem_StatusIndicator_Init
  *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
  DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_StatusIndicator_Init(void)
  {
    if (Dem_StatusIndicator_IsExtendedFimEnabled() == TRUE)
    {
      Dem_Scheduler_EnableTask(Dem_Scheduler_Task_StatusIndicator);
    }
  }

/* ****************************************************************************
 % Dem_StatusIndicator_MainFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StatusIndicator_MainFunction(void)
{
  Dem_Satellite_IdType lSatelliteId;

  for (lSatelliteId = 0u; lSatelliteId < Dem_Cfg_GlobalSatelliteCount(); ++lSatelliteId)
  {
    if (Dem_SatelliteCore_TestAndClearStatusIndicatorQueueUpdated(lSatelliteId) == TRUE)
    {
      Dem_StatusIndicator_ProcessSatelliteQueueActions(lSatelliteId);
    }
  }
}

/* ****************************************************************************
 % Dem_StatusIndicator_UpdateOnTestFailed
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
Dem_StatusIndicator_UpdateOnTestFailed(
  Dem_EventIdType EventId,
  Dem_Cfg_MemoryIndexType MemoryIndex,
  Dem_Cfg_StorageTriggerType UpdateFlags
  )
{
  boolean lReturnValue;

  lReturnValue = FALSE;

  if (Dem_StatusIndicator_isStatusIndicatorEnabled() == TRUE)
  {
    Dem_StatusIndicator_Type lStatusIndicatorByte;
    Dem_Cfg_MemoryIndexType lMemoryEntryId;

    lMemoryEntryId = Dem_MemoryEntry_GetId(MemoryIndex);
    lStatusIndicatorByte = Dem_MemoryEntry_GetStatusIndicator(lMemoryEntryId);

    if ((UpdateFlags & DEM_CFG_TRIGGER_INDICATOR) != 0u)
    {
      lStatusIndicatorByte = Dem_StatusIndicator_Set_WIRSLC(lStatusIndicatorByte);

      lReturnValue = TRUE;
    }

    if ((UpdateFlags & DEM_CFG_TRIGGER_TESTFAILED) != 0u) {
      lStatusIndicatorByte = Dem_StatusIndicator_Set_TFSLC(lStatusIndicatorByte);

      if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
      {
        lStatusIndicatorByte = Dem_StatusIndicator_Set_ERDTC(lStatusIndicatorByte);
      }

      lReturnValue = TRUE;
    }

    Dem_MemoryEntry_SetStatusIndicator(lMemoryEntryId, lStatusIndicatorByte);
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_StatusIndicator_UpdateOnEventAged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StatusIndicator_UpdateOnEventAged(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_Cfg_MemoryIndexType MemoryIndex
  )
{
  if (Dem_StatusIndicator_isStatusIndicatorEnabled() == TRUE)
  {
    Dem_Cfg_MemoryIndexType lMemoryEntryId;

    lMemoryEntryId = Dem_MemoryEntry_GetId(MemoryIndex);
    
    Dem_MemoryEntry_SetStatusIndicator(lMemoryEntryId, 0x00);
  }
}

/* ****************************************************************************
 % Dem_StatusIndicator_UpdateOnMemoryInitRestoreMemory
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
Dem_StatusIndicator_UpdateOnMemoryInitRestoreMemory(
  Dem_EventIdType EventId,
  Dem_Cfg_MemoryIndexType MemoryIndex,
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId
  )
{
  if (Dem_StatusIndicator_isStatusIndicatorEnabled() == TRUE)
  {
    if (Dem_Indicator_TestHasIndicator(EventId) == FALSE)
    {
      Dem_StatusIndicator_Type lStatusIndicatorByte;
      lStatusIndicatorByte = Dem_MemoryEntry_GetStatusIndicator(MemoryEntryId);
      if (Dem_StatusIndicator_Test_WIRSLC(lStatusIndicatorByte) == TRUE)
      {
        lStatusIndicatorByte = Dem_StatusIndicator_Reset_WIRSLC(lStatusIndicatorByte);
        Dem_MemoryEntry_SetStatusIndicator(MemoryEntryId, lStatusIndicatorByte);
        Dem_Nvm_SetEventMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
      }
    }
  }
}

/* ****************************************************************************
 % Dem_StatusIndicator_UpdateOnObdMemoryRestoreSetWIRSLC
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
Dem_StatusIndicator_UpdateOnObdMemoryRestoreSetWIRSLC(                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventIdType EventId
  )
{
  if (Dem_StatusIndicator_isStatusIndicatorEnabled() == TRUE)
  {
    Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
    Dem_Cfg_MemoryIndexType lMemoryIndex;

    lMemoryIndex = Dem_Memory_FindIndex(EventId);
    if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
    { 
      Dem_StatusIndicator_Type lStatusIndicatorByte;
      Dem_StatusIndicator_Type lOldStatusIndicatorByte;

      lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);
      lOldStatusIndicatorByte = Dem_MemoryEntry_GetStatusIndicator(lMemoryEntryId);
      lStatusIndicatorByte = Dem_StatusIndicator_Set_WIRSLC(lOldStatusIndicatorByte);

      if (lStatusIndicatorByte != lOldStatusIndicatorByte)
      {
        Dem_MemoryEntry_SetStatusIndicator(lMemoryEntryId, lStatusIndicatorByte);
        Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
      }
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_StatusIndicator_GetStatusIndicator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
*/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_StatusIndicator_GetStatusIndicator(
  Dem_EventIdType EventId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Status
  )
{
  Std_ReturnType lReturnValue;
  lReturnValue = E_NOT_OK;

  if (Dem_StatusIndicator_IsExtendedFimEnabled() == TRUE)
  {
    Dem_DTCInternal_StoredStatusType lStoredStatus;

    lStoredStatus = Dem_DTCInternalStatus_GetStoredStatus(Dem_Event_GetInternalStatus(EventId));

    if (lStoredStatus != Dem_DTCInternalStatus_StoredStatus_None)
    {
      Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
      Dem_Cfg_MemoryIndexType lMemoryIndex;
      Dem_StatusIndicator_Type lStatusIndicatorByte;

      lMemoryIndex = Dem_Memory_FindMemoryIndex_StoredEvent(EventId);
      lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);

      if (Dem_MemoryEntry_TestAgingOnlyEntry(lMemoryEntryId) == FALSE)
      {
        lStatusIndicatorByte = Dem_MemoryEntry_GetStatusIndicator(lMemoryEntryId);

        *Status = lStatusIndicatorByte;                                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

        lReturnValue = E_OK;
      }
    }
  }

  return lReturnValue;
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif /* DEM_STATUSINDICATOR_IMPLEMENTATION_H */

 /*!
  * \}
  */
 /* ********************************************************************************************************************
  *  END OF FILE: Dem_StatusIndicator_Implementation.h
  *********************************************************************************************************************/
