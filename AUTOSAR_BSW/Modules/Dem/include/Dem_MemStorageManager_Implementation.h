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
/*! \addtogroup Dem_MemStorageManager
 *  \{
 *  \file       Dem_MemStorageManager_Implementation.h
 *  \brief      Control storage of additional data for DTCs based on storage/update triggers.
 *  \details    Knows depending on storage/update triggers which data to store/change.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMSTORAGEMANAGER_IMPLEMENTATION_H)
#define DEM_MEMSTORAGEMANAGER_IMPLEMENTATION_H

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
#include "Dem_MemStorageManager_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Core_Interface.h"
#include "Dem_Infrastructure_Interface.h"
#include "Dem_Client_Interface.h"
#include "Dem_MemoryEntry_Interface.h"
#include "Dem_ExtDataElement_Interface.h"
#include "Dem_DataStorage_Interface.h"
#include "Dem_Mem_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_MEMSTORAGEMANAGER_IMPLEMENTATION_FILENAME "Dem_MemStorageManager_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_MemStorageManager_Private Private Methods
 * \{
 */


#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_UpdateEventUserERecs
 *****************************************************************************/
/*!
 * \brief         Collects the user provided extended data records stored for
 *                an event entry.
 *
 * \details       Collects the user provided extended data records stored for
 *                an event entry.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     UpdateFlags
 *                Trigger flags
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_NO_CHANGES          nothing has changed
 *                DEM_DATA_USERDATA_CHANGED    user provided data was updated
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_USER_ERECS == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventUserERecs(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  UpdateFlags
  );
#endif


#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_UpdateEventSRecs
 *****************************************************************************/
/*!
 * \brief         Collect all user snapshot records for an event
 *
 * \details       This function will look for every snapshot record of the
 *                event that needs updating due to the status changes encoded
 *                by the trigger flags.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     UpdateFlags
 *                Trigger flags
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_NO_CHANGES          nothing has changed
 *                DEM_DATA_USERDATA_CHANGED    user provided data was updated
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventSRecs(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  UpdateFlags
  );
#endif


#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_UpdateGlobalSRecs
 *****************************************************************************/
/*!
 * \brief         Collect all global snapshot records for an event
 *
 * \details       This function verifies if global snapshot records of an 
 *                event needs updating due to the status changes encoded
 *                by the trigger flags. If required, function updates the 
 *                record.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     UpdateFlags
 *                Trigger flags
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_NO_CHANGES          nothing has changed
 *                DEM_DATA_USERDATA_CHANGED    user provided data was updated
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateGlobalSRecs(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  UpdateFlags
  );
#endif


#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_UpdateEventJ1939FF
 *****************************************************************************/
/*!
 * \brief         Collect J1939 Freeze Frame data stored for an event.
 *
 * \details       Collect J1939 Freeze Frame data stored for an event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_USERDATA_CHANGED    User provided data was updated.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventJ1939FF(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );
#endif


#if (DEM_FEATURE_NEED_SREC_OEMTRIGGER == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_TestOemSRecTrigger
 *****************************************************************************/
/*!
 * \brief         Evaluates if the snapshot data needs to be updated.
 *
 * \details       This function evaluates if the snapshot SRecIndex that can
 *                be stored in MemoryEntry is eligible for an update due to
 *                the status changes encoded by the trigger flags.
 *
 *                If the snapshot is not configured to update on OEM trigger,
 *                this function returns false.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     SRecIndex
 *                Index to the snapshot configuration
 * \param[in]     UpdateFlags
 *                Trigger flags
 *
 * \return        TRUE
 *                The snapshot needs updating
 * \return        FALSE
 *                The snapshot does not need updating
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_SREC_OEMTRIGGER == STD_ON)
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemStorageManager_TestOemSRecTrigger(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_SRecIndexType, AUTOMATIC)  SRecIndex,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  UpdateFlags
  );
#endif


#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_TestObdIIFreezeFrameUpdates
 *****************************************************************************/
/*!
 * \brief         Test which parts of the freeze frame data need updating
 *
 * \details       This function tests if the freeze frame data must be updated,
 *                e.g. because it is not yet stored, and if the freeze frame
 *                time stamp must be updated.
 *
 * \param[in]     DTCContext
 *                DTC processing context.
 * \param[in]     FreezeFrameIndex
 *                Index of the event's freeze frame
 *
 * \return        Bitcoded (ORed values)
 *                DEM_DATA_FF_UPDATE_DATA if the freeze frame data needs
 *                updating
 *                DEM_DATA_FF_UPDATE_VISIBILITY if the visibility flag needs updating
 *                DEM_DATA_FF_UPDATE_TIMESTAMP if the timestamp needs updating
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_TestObdIIFreezeFrameUpdates(
  CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext,
  CONST(uint8, AUTOMATIC)  FreezeFrameIndex
  );
#endif


#if (DEM_CFG_DATA_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_EXTENDED_ENV_DATA == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_UpdateCustomizedEnvData
 *****************************************************************************/
/*!
 * \brief         Function updates the standard environmental data.
 *
 * \details       Function updates the standard environmental data when 
 *                the event is reported failed.
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \pre           -
 * \config        (DEM_CFG_DATA_STANDARD_ENV_DATA == STD_ON)
 *                || (DEM_CFG_DATA_EXTENDED_ENV_DATA == STD_ON)
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemStorageManager_UpdateCustomizedEnvData(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );
#endif


/* ****************************************************************************
 * Dem_MemStorageManager_UpdateEventEntryOnTriggerFailed
 *****************************************************************************/
/*!
 * \brief         Function updates environmental data of an event on a Test
 *                Failed trigger.
 *
 * \details       Function updates environmental data of an event on a Test
 *                Failed trigger.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_NO_CHANGES          nothing has changed.
 *                DEM_DATA_USERDATA_CHANGED    user provided data was updated.
 *                DEM_DATA_STATISTICS_CHANGED  internal data was updated.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventEntryOnTriggerFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );


/* ****************************************************************************
 * Dem_MemStorageManager_UpdateEventEntryOnTriggerFailedThisCycle
 *****************************************************************************/
/*!
 * \brief         Function updates environmental data of an event on a Test
 *                Failed this cycle trigger.
 *
 * \details       Function updates environmental data of an event on a Test
 *                Failed this cycle trigger.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_NO_CHANGES          nothing has changed.
 *                DEM_DATA_STATISTICS_CHANGED  internal data was updated.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventEntryOnTriggerFailedThisCycle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,         
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );


#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_CustomizedUpdateEventEntryOnTriggerFailed
 *****************************************************************************/
/*!
 * \brief         Function updates environmental data of an event on a Test
 *                Failed or Test Failed this cycle trigger.
 *
 * \details       Function updates environmental data of an event on a Test
 *                Failed or Test Failed this cycle trigger.
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 * \param[in]     WIRIndicatorTriggered
 *                Indicates whether WIR indicator of the event is currently 
 *                triggered.
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_STATISTICS_CHANGED  internal data was updated.
 *
 * \pre           DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON
 * \config        -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_CustomizedUpdateEventEntryOnTriggerFailed(   
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(boolean, AUTOMATIC)  WIRIndicatorTriggered
  );
#endif


#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_UpdateEventUserERecs
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventUserERecs(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  UpdateFlags
  )
{
  uint8 lBlockModification;
  uint8 lExtendedEntryIndex;
  Dem_ExtendedEntry_IterType lExtendedEntryIter;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(UpdateFlags)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lBlockModification = DEM_DATA_NO_CHANGES;
  lExtendedEntryIndex = 0u;
  
  for (Dem_ExtendedEntry_IterInit(EventId, &lExtendedEntryIter);                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_ExtendedEntry_IterExists(&lExtendedEntryIter) == TRUE;                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_ExtendedEntry_IterNext(&lExtendedEntryIter))                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_ERecIndexType lCfgERecIndex;
    lCfgERecIndex = Dem_ExtendedEntry_IterGet(&lExtendedEntryIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_ERecType(lCfgERecIndex) == DEM_CFG_EREC_TYPE_USER)
    {
       if ( (  (Dem_Cfg_ERecUpdate(lCfgERecIndex) == TRUE)
            || (Dem_ExtendedEntry_IteratorIsExtendedRecordStored(MemoryEntryId, lExtendedEntryIndex) == FALSE))                  /* PRQA S 3415 */ /* MD_DEM_13.5_cf */                  
# if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
          && (Dem_Cfg_ERecTrigger(lCfgERecIndex) == (UpdateFlags & Dem_Cfg_ERecTrigger(lCfgERecIndex)))                          
# endif
       )
      {
        Dem_Data_DestinationBuffer lDestinationBuffer;
        Dem_ExtendedEntry_IteratorUpdateExtendedEntry(MemoryEntryId, lExtendedEntryIndex);

# if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
        {
          Dem_Cfg_CombinedGroupIndexType lCombinedDTCGroup;
          lCombinedDTCGroup = Dem_Cfg_EventCombinedGroup(EventId);
          if (Dem_Cfg_EventCombinedGroup(EventId) != DEM_CFG_COMBINED_GROUP_INVALID)
          {
            Dem_ExtendedEntry_SetUserERecStorageStatus(
              Dem_ExtendedEntry_CalculateUserERecStorageIndex(
                (uint8)Dem_Cfg_DidNumber(Dem_Cfg_ERecDid(lCfgERecIndex)), lCombinedDTCGroup),
              MemoryEntryId);
          }
        }
# endif
        Dem_Data_InitDestinationBuffer(&lDestinationBuffer,                                                                      /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
                                       Dem_MemoryEntry_GetExtendedRecordDataPtr(MemoryEntryId, lExtendedEntryIndex),
                                       Dem_Cfg_GlobalERecMaxRawSize());

        Dem_DataStorage_CollectERec(EventId, Dem_Cfg_ERecDid(lCfgERecIndex), &lDestinationBuffer);                             /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */

        lBlockModification = DEM_DATA_USERDATA_CHANGED;
      }
      else
      {
        /* MISRA */
      }
      lExtendedEntryIndex +=1u;
    }
  }

  return lBlockModification;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_UpdateEventSRecs
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
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventSRecs(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  UpdateFlags
  )
{
  uint8 lBlockModification;
# if (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
  uint8 lLastStoredEntryIndex;
# endif
  Dem_Cfg_SnapshotEntry_IterType lSnapshotEntryIter;

  lBlockModification = DEM_DATA_NO_CHANGES;
# if (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
  lLastStoredEntryIndex = 0xffU; /* Invalid */
# endif

  for (Dem_SnapshotEntry_IteratorInit(EventId, MemoryEntryId, &lSnapshotEntryIter);                                              /* SBSW_DEM_POINTER_FORWARD_STACK */
       Dem_SnapshotEntry_IteratorExists(&lSnapshotEntryIter) == TRUE;                                                            /* SBSW_DEM_POINTER_FORWARD_STACK */
       Dem_SnapshotEntry_IteratorNext(&lSnapshotEntryIter))                                                                      /* SBSW_DEM_POINTER_FORWARD_STACK */
  {
    Dem_Cfg_SRecIndexType lCfgSRecIndex;

    lCfgSRecIndex = Dem_SnapshotEntry_IteratorGetSnapshotRecordIndex(&lSnapshotEntryIter);                                       /* SBSW_DEM_POINTER_FORWARD_STACK */

    /* If an update is needed: Updates are required when the configured trigger matches,
     * and the record is either not stored or configured for updates */
    if ( (
# if (DEM_FEATURE_NEED_SREC_OEMTRIGGER == STD_ON)
           (Dem_MemStorageManager_TestOemSRecTrigger(EventId, MemoryEntryId, lCfgSRecIndex, UpdateFlags)) ||
# endif
           (Dem_Cfg_SRecTrigger(lCfgSRecIndex) == (UpdateFlags & Dem_Cfg_SRecTrigger(lCfgSRecIndex))) ) &&                       
         (  (Dem_Cfg_SRecUpdate(lCfgSRecIndex) == TRUE)                                                                          
         || (Dem_SnapshotEntry_IteratorIsSnapshotRecordStored(&lSnapshotEntryIter) == FALSE))                                    /* SBSW_DEM_POINTER_FORWARD_STACK */ /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
       )
    {
      Dem_SnapshotEntry_IteratorUpdateSnapshotEntry(&lSnapshotEntryIter);                                                        /* SBSW_DEM_POINTER_FORWARD_STACK */

# if ((DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON) && (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON))
      {
        Dem_Cfg_CombinedGroupIndexType lDTCGroup;
        lDTCGroup = Dem_Cfg_EventCombinedGroup(EventId);
        if (lDTCGroup != DEM_CFG_COMBINED_GROUP_INVALID)
        {
          Dem_SnapshotEntry_SetSRecStorageInDTCHeader(Dem_Cfg_SRecId(lCfgSRecIndex),
            lDTCGroup,
            lSnapshotEntryIter.MemoryEntryId);
        }
      }
# endif

# if (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
      /* For configured snapshot numbers, if the snapshot is already collected copy its data */
      if (lLastStoredEntryIndex != 0xffU)
      {
        Dem_SnapshotEntry_IteratorCopySnapshotEntry(&lSnapshotEntryIter, lLastStoredEntryIndex);                                 /* SBSW_DEM_POINTER_FORWARD_STACK */
      }
      else
# endif
      {
# if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
        /* If 'prestore freezeframe' is enabled and data is prestored, copy the prestored data */
        if (Dem_DataStorage_PrestorageApplySRec(Dem_MemoryEntry_GetSnapshotRecordDataPtr(                                      /* SBSW_DEM_POINTER_SNAPSHOT_BUFFER */
                                                  lSnapshotEntryIter.MemoryEntryId, 
                                                  lSnapshotEntryIter.SnapshotEntryIndex),                                                                                                
                                                  Dem_Cfg_EventSRecMaxRawSize()) == FALSE)
# endif
        {
          /* Otherwise, collect new samples from the application. */
          Dem_DataStorage_CollectSnapshot(EventId,                                                                             /* SBSW_DEM_POINTER_SNAPSHOT_BUFFER */
                                            Dem_MemoryEntry_GetSnapshotRecordDataPtr(lSnapshotEntryIter.MemoryEntryId, 
                                                                            lSnapshotEntryIter.SnapshotEntryIndex),
                                            Dem_Cfg_EventSRecMaxRawSize());
# if (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
          lLastStoredEntryIndex = Dem_SnapshotEntry_IteratorGetSnapshotEntryIndex(&lSnapshotEntryIter);                          /* SBSW_DEM_POINTER_FORWARD_STACK */
# endif
        }
        lBlockModification = DEM_DATA_USERDATA_CHANGED;
      }
      /* For calculated snapshot records, processing is completed */
# if (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
      break;
# endif
    }
  }

  return lBlockModification;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_UpdateGlobalSRecs
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateGlobalSRecs(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  UpdateFlags
  )
{
  uint8 lBlockModification;

  lBlockModification = DEM_DATA_NO_CHANGES;

  /* If an update is needed: Updates are required when the configured trigger matches,
    * and the record is either not stored or configured for updates */
  if ((Dem_Cfg_GlobalSRecTrigger() == (UpdateFlags & Dem_Cfg_GlobalSRecTrigger()))                                               /* COV_DEM_UNSUPPORTED_COMBINATION_GLOBAL_SRECS */
     && ((Dem_Cfg_GlobalSRecUpdate() == TRUE)                                                                                                                                                                     
     || (Dem_MemoryEntry_TestGlobalSnapshotRecordStored(MemoryEntryId) == FALSE))                                                /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
     )
  {
    Dem_MemoryEntry_SetGlobalSnapshotRecordStored(MemoryEntryId, TRUE);

# if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)     
    /* If 'prestore freezeframe' is enabled and data is prestored, copy the prestored data */
    if (Dem_DataStorage_PrestorageApplyGlobalSRec(Dem_MemoryEntry_GetGlobalSnapshotRecordDataPtr(MemoryEntryId),               /* SBSW_DEM_POINTER_GLOBAL_SNAPSHOT_BUFFER */                                                                         
                                                    Dem_Cfg_GlobalSRecMaxRawSize()) == FALSE)
# endif
     {
      /* Collect new samples from the application. */
       Dem_DataStorage_CollectGlobalSnapshot(EventId,                                                                          /* SBSW_DEM_POINTER_GLOBAL_SNAPSHOT_BUFFER */
                                                Dem_MemoryEntry_GetGlobalSnapshotRecordDataPtr(MemoryEntryId),
                                                Dem_Cfg_GlobalSRecMaxRawSize());
     }

     lBlockModification = DEM_DATA_USERDATA_CHANGED;

   }

  return lBlockModification;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_UpdateEventJ1939FF
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventJ1939FF(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
# if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
  if (Dem_DataStorage_PrestorageApplyJ1939FF(Dem_MemoryEntry_GetJ1939FreezeFramePtr(MemoryEntryId),                            /* SBSW_DEM_POINTER_J1939FREEZEFRAME_BUFFER */
                                      Dem_Cfg_GlobalJ1939FFTotalRawSize()) == FALSE)
# endif
  {
    Dem_DataStorage_CollectJ1939FreezeFrame(EventId,                                                                           /* SBSW_DEM_POINTER_J1939FREEZEFRAME_BUFFER */
                                     Dem_MemoryEntry_GetJ1939FreezeFramePtr(MemoryEntryId),
                                     Dem_Cfg_GlobalJ1939FFTotalRawSize());
  }
  return DEM_DATA_USERDATA_CHANGED;
}
#endif

#if (DEM_FEATURE_NEED_SREC_OEMTRIGGER == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_TestOemSRecTrigger
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
Dem_MemStorageManager_TestOemSRecTrigger(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_SRecIndexType, AUTOMATIC)  SRecIndex,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  UpdateFlags
  )
{
  boolean lReturnValue;

  if (Dem_Cfg_SRecTrigger(SRecIndex) != DEM_CFG_TRIGGER_OEM)
  {
    lReturnValue = FALSE;
  }
  else
  {
# if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
    {
      /* If the event is already confirmed, do not allow an update. */
      /* Status bits are stored to the event memory after collecting data */
      if (Dem_UDSStatus_Test_CDTC(Dem_Event_GetUDSStatus(EventId)) == TRUE)
      {
        lReturnValue = FALSE;
      }
      /* If the event was already tested 'failed', update with every first failed event per cycle */
      else if (DEM_DTC_TEST_PC_STATUS_TFSLC(Dem_MemoryEntry_GetPreConfirmedStatus(MemoryEntryId)) == TRUE)
      {
        /* Note: here the event was tested failed, but has not confirmed yet */
        lReturnValue = (boolean)(0u != (UpdateFlags & (DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE)));
      }
      /* Otherwise, update once per cycle on a preconfirmed trigger */
      else
      {
        /* Note: here the event is not yet tested */
        lReturnValue = (boolean)((DEM_CFG_TRIGGER_FDC | DEM_CFG_TRIGGER_FIRSTTHISCYCLE)
          == (UpdateFlags & (DEM_CFG_TRIGGER_FDC | DEM_CFG_TRIGGER_FIRSTTHISCYCLE)));
      }
    }
# endif
# if (DEM_FEATURE_NEED_SREC_TRIGGER_PDTC_AND_CDTC == STD_ON)
    {
      DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
      
      /* Status bits are stored to the event memory after collecting data */
      if (Dem_UDSStatus_Test_CDTC(Dem_DTC_GetDTCStatus(EventId)) == TRUE)
      {
        lReturnValue = FALSE;
      }
      else
      {
        lReturnValue = (boolean)(0u != (UpdateFlags & (DEM_CFG_TRIGGER_PENDING | DEM_CFG_TRIGGER_CONFIRMED)));
      }
    }
# endif
  }
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_TestObdIIFreezeFrameUpdates
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_TestObdIIFreezeFrameUpdates(
  CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext,
  CONST(uint8, AUTOMATIC)  FreezeFrameIndex
  )
{
  uint8 lUpdates;
  Dem_EventIdType lMemoryRepresentativeEvent;

  lUpdates = 0u;
  lMemoryRepresentativeEvent = Dem_Cfg_GetMemoryRepresentative(DTCContext->EventId);

  if (FreezeFrameIndex != Dem_Cfg_GlobalObdIIFFCount())
  {
    if (Dem_Mem_FreezeFrameGetEvent(FreezeFrameIndex) == lMemoryRepresentativeEvent)
    { /* 0-Trip events have both confirmed and pending triggers simultaneously, prioritize confirmed trigger */
      if ((DTCContext->DtcEffects & DEM_CFG_TRIGGER_CONFIRMED) != 0u)
      { /* If configured, confirmed trigger sets visibility flag */
# if (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
        if ((DEM_OPERATIONCYCLE_TEST_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()) == TRUE)
          || ((Dem_Event_TestObdVisibilityDelayed(DTCContext->EventId) == FALSE)))
        {
          lUpdates = (uint8)(lUpdates | DEM_DATA_FF_UPDATE_VISIBILITY);
        }
        lUpdates = (uint8)(lUpdates | DEM_DATA_FF_UPDATE_TIMESTAMP);
# endif
        /* If configured, confirmed trigger updates the data */
# if (DEM_CFG_SUPPORT_PENDING_UPDATE_FREEZE_FRAME == STD_ON)
        lUpdates = (uint8)(lUpdates | DEM_DATA_FF_UPDATE_DATA);
# endif
      }
    }
    else
    { /* 0-Trip events have both confirmed and pending triggers simultaneously, prioritize confirmed trigger */
      if ((DTCContext->DtcEffects & DEM_CFG_TRIGGER_CONFIRMED) != 0u)
      {
# if ((DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON))
        if ((DEM_OPERATIONCYCLE_TEST_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()) == TRUE)
          || (Dem_Event_TestObdVisibilityDelayed(DTCContext->EventId) == FALSE)
#  if(DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON)
          || (DTCContext->QualifyDTC == TRUE)
#  endif
          )
# endif
        {
          lUpdates = (uint8)(lUpdates | DEM_DATA_FF_UPDATE_VISIBILITY);
        }

        lUpdates = (uint8)(lUpdates | DEM_DATA_FF_UPDATE_DATA);
      }
# if (DEM_CFG_SUPPORT_PENDING_STORAGE_FREEZE_FRAME == STD_ON)
      else /* ((Effects & DEM_CFG_TRIGGER_PENDING) != 0u) */
      {
#  if (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_OFF)
        lUpdates = (uint8)(lUpdates | DEM_DATA_FF_UPDATE_VISIBILITY);
#  endif
        lUpdates = (uint8)(lUpdates | DEM_DATA_FF_UPDATE_DATA);
      }
# endif
    }
  }
# if (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
  else
  {
    if(DTCContext->QualifyDTC == TRUE)
    {
      lUpdates = (uint8) (lUpdates | DEM_DATA_FF_UPDATE_VISIBILITY);
    }
  }
# endif

  return lUpdates;
}
#endif

#if (DEM_CFG_DATA_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_EXTENDED_ENV_DATA == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_UpdateCustomizedEnvData
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
Dem_MemStorageManager_UpdateCustomizedEnvData(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint8 lExternalTester;

  /* Buffer Layout:
      [0]:    Status, 0.0 Presence Flag (Distinguish initial entry from updates)
                      0.1 external tester present
      [1][2]: Original Odometer Value
      [3][4]: MostRecent Odometer Value
      [5-8]:  Operating Time*
      [9]:    Operating Time Status*
    *: only with DEM_CFG_DATA_EXTENDED_ENV_DATA
  */
  Dem_ExtDataElement_GetCustomizedExternalTester(&lExternalTester);                                                            /* SBSW_DEM_POINTER_FORWARD_STACK */
  Dem_ExtDataElement_GetCustomizedCurrentOdometer(MemoryEntryId);
  #if (DEM_CFG_DATA_EXTENDED_ENV_DATA == STD_ON)
  /* Always store the operating time, even if the event only wants the standard version.
      Output resolves the different records later */
  Dem_ExtDataElement_GetCustomizedOperatingTime(MemoryEntryId);
  #endif

  if (Dem_MemoryEntry_GetStdEnvData(MemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_STATUS) == 0x00U)
  {
    /* Set original odometer to the same value as most recent odometer */
    Dem_MemoryEntry_SetStdEnvData(MemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_FIRSTODOMETER, 
                                  Dem_MemoryEntry_GetStdEnvData(MemoryEntryId, 
                                  DEM_MEMORYENTRY_STDENVDATA_CURRENTODOMETER));
    Dem_MemoryEntry_SetStdEnvData(MemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_FIRSTODOMETER + 1u, 
                                  Dem_MemoryEntry_GetStdEnvData(MemoryEntryId, 
                                  DEM_MEMORYENTRY_STDENVDATA_CURRENTODOMETER + 1u));
  }

  /* The external tester flag is bit 1, not bit 0 (see Standardized Diagnostic Data) */
  if ((boolean)lExternalTester == TRUE)                                                                                          /* PRQA S 4340 */ /* MD_MSR_AutosarBoolean */
  {
    Dem_MemoryEntry_SetStdEnvData(MemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_STATUS, 0x3U);
  }
  else
  {
    Dem_MemoryEntry_SetStdEnvData(MemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_STATUS, 0x1U);
  }
}
#endif

/* ****************************************************************************
 % Dem_MemStorageManager_UpdateEventEntryOnTriggerFailed
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventEntryOnTriggerFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  uint8 lBlockModification;
  Dem_Cfg_MemoryEntryHandleType lMemoryEntry;

  lMemoryEntry = Dem_MemoryEntry_GetId(MemoryIndex);
  lBlockModification = DEM_DATA_NO_CHANGES;

#if (DEM_CFG_DATA_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_EXTENDED_ENV_DATA == STD_ON)
  Dem_MemStorageManager_UpdateCustomizedEnvData(lMemoryEntry);
  lBlockModification = DEM_DATA_SET_USERDATA_CHANGED(lBlockModification);
#endif

#if (DEM_FEATURE_NEED_OCC_COUNTER == STD_ON)
# if (DEM_CFG_PROCESS_OCCTR_CONFIRMED == STD_ON)
  if ((Dem_UDSStatus_Test_CDTC(Dem_DTC_RetrieveStatus(EventId)) == TRUE)
    || ( Dem_MemoryEntry_GetOccurrenceCounter(lMemoryEntry) == 0U) )                                                             /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
# endif
  {
    if (Dem_MemoryEntry_IncrementOccurrenceCounter(lMemoryEntry) == TRUE)
    {
      lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
    }
  }
#endif

#if (DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
  {
    if (Dem_MemoryEntry_GetCyclesSinceFirstFailed(lMemoryEntry) 
          == DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID)
    {
      Dem_MemoryEntry_SetCyclesSinceFirstFailed(lMemoryEntry,
                                                Dem_OperationCycle_GetCycleCounter(
                                                Dem_Cfg_EventOperationCycle(EventId)));
      lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
    }
  }
#endif

#if (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON)
  {
# if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
    Dem_MemoryEntry_SetDebounceValueMax(lMemoryEntry, 
                                        Dem_Cfg_EventFailedTarget(EventId));
# else
    Dem_MemoryEntry_SetDebounceValueMax(lMemoryEntry, (sint16)0x7F);
# endif
    lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
  }
#endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return lBlockModification;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_MemStorageManager_UpdateEventEntryOnTriggerFailedThisCycle
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventEntryOnTriggerFailedThisCycle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  uint8 lBlockModification;
  lBlockModification = DEM_DATA_NO_CHANGES;

  if (Dem_MemoryEntry_IncrementFailedCycleCounter(Dem_MemoryEntry_GetId(MemoryIndex)) == TRUE)
  {
    lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
  }
  if (Dem_MemoryEntry_IncrementConsecutiveFailedCycleCounter(Dem_MemoryEntry_GetId(MemoryIndex)) == TRUE)
  {
    lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
  }

# if (DEM_CFG_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON)
  {
    Dem_MemoryEntry_SetCyclesSinceLastFailed(Dem_MemoryEntry_GetId(MemoryIndex), 
                                             Dem_OperationCycle_GetCycleCounter(Dem_Cfg_EventOperationCycle(EventId)));
    lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
  }
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif

  return lBlockModification;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_CustomizedUpdateEventEntryOnTriggerFailed
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_CustomizedUpdateEventEntryOnTriggerFailed(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex, 
  CONST(boolean, AUTOMATIC)  WIRIndicatorTriggered
  )
{
  uint8 lPreconfirmedStatus;
  Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
  uint8 lBlockModification;

  lBlockModification = DEM_DATA_NO_CHANGES;
  lMemoryEntryId = Dem_MemoryEntry_GetId(MemoryIndex);
  lPreconfirmedStatus = Dem_MemoryEntry_GetPreConfirmedStatus(lMemoryEntryId);
  lPreconfirmedStatus = DEM_DTC_SET_PC_STATUS_TFSLC(lPreconfirmedStatus);
  if (WIRIndicatorTriggered == TRUE)
  {
    lPreconfirmedStatus = DEM_DTC_SET_PC_STATUS_WIRSLC(lPreconfirmedStatus);
  }

  Dem_MemoryEntry_SetPreConfirmedStatus(lMemoryEntryId, lPreconfirmedStatus);
  lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);

  return lBlockModification;
}
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
 * \addtogroup Dem_MemStorageManager_Public
 * \{
 */

#if ( (DEM_CFG_SUPPORT_TRIGGER_PASSED == STD_ON)\
   && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 % Dem_MemStorageManager_UpdateEventEntryOnPassed
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventEntryOnPassed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  UpdateFlags,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  uint8 lBlockModification;

  lBlockModification = DEM_DATA_NO_CHANGES;

# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
  if (MemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
  {
    lBlockModification |= Dem_MemStorageManager_UpdateEventUserERecs(EventId,
      Dem_MemoryEntry_GetId(MemoryIndex),
      UpdateFlags);
  }
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
  if ((MemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
    && ((UpdateFlags & DEM_CFG_TRIGGER_PASSED) != 0u))
  {
    lBlockModification |= Dem_MemStorageManager_UpdateEventSRecs(EventId,
      Dem_MemoryEntry_GetId(MemoryIndex),
      UpdateFlags);
  }
#endif
   
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(UpdateFlags)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return lBlockModification;
}
#endif

/* ****************************************************************************
 % Dem_MemStorageManager_UpdateEventEntryOnFailed
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
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventEntryOnFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  UpdateFlags,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  uint8 lBlockModification;

  lBlockModification = DEM_DATA_NO_CHANGES;

  /* On a TestFailed trigger */
  if ((UpdateFlags & DEM_CFG_TRIGGER_TESTFAILED) != 0u)
  {
    lBlockModification = Dem_MemStorageManager_UpdateEventEntryOnTriggerFailed(EventId, MemoryIndex);
  }

  /* On a TestFailedThisCycle trigger */
  if ((UpdateFlags & DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE) != 0u)
  {
    lBlockModification |= Dem_MemStorageManager_UpdateEventEntryOnTriggerFailedThisCycle(EventId, MemoryIndex);
  }

#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  if ((UpdateFlags & (DEM_CFG_TRIGGER_TESTFAILED|DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE)) != 0u)
    /* Set SI.30 bit 7 */
  {
    boolean lWirIndicatorTriggered;
    if ((UpdateFlags & DEM_CFG_TRIGGER_INDICATOR) != 0u)
    {
      lWirIndicatorTriggered = TRUE;
    }
    else
    {
      lWirIndicatorTriggered = FALSE;
    }

    lBlockModification |= Dem_MemStorageManager_CustomizedUpdateEventEntryOnTriggerFailed(MemoryIndex, lWirIndicatorTriggered);
  }
# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
  if ((DEM_CFG_TRIGGER_FDC | DEM_CFG_TRIGGER_FIRSTTHISCYCLE) == 
      (UpdateFlags & (DEM_CFG_TRIGGER_FDC | DEM_CFG_TRIGGER_FIRSTTHISCYCLE)))
  {
    lBlockModification |= Dem_MemStorageManager_UpdateEventUserERecs(EventId,
      Dem_MemoryEntry_GetId(MemoryIndex),
      UpdateFlags);
  }
# endif
#else
# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
    lBlockModification |= Dem_MemStorageManager_UpdateEventUserERecs(EventId,
      Dem_MemoryEntry_GetId(MemoryIndex),
      UpdateFlags);
# endif
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
# if (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
  if ((UpdateFlags & DEM_CFG_TRIGGER_TESTFAILED) != 0u)
# endif
  {
    lBlockModification |= Dem_MemStorageManager_UpdateEventSRecs(EventId, 
                                                                  Dem_MemoryEntry_GetId(MemoryIndex),
                                                                  UpdateFlags);
  }
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
  {
    lBlockModification |= Dem_MemStorageManager_UpdateGlobalSRecs(EventId,
                                                                  Dem_MemoryEntry_GetId(MemoryIndex),
                                                                  UpdateFlags);
  }
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
  if ( (Dem_Cfg_EventJ1939Dtc(EventId) != DEM_CFG_DTC_J1939_INVALID)
    && ((UpdateFlags & DEM_CFG_TRIGGER_CONFIRMED) != 0u) )
  {
    lBlockModification |= Dem_MemStorageManager_UpdateEventJ1939FF(EventId,
                                                                    Dem_MemoryEntry_GetId(MemoryIndex));
  }
#endif

#if (DEM_CFG_DATA_WUC_SINCE_LAST_FAILED == STD_ON)
  {
    /* Reset the WUC Since Last Failed during 
    positive transition of event failed report including TF, TFTOC bit. */
    Dem_MemoryEntry_SetWarmUpCyclesSinceLastFailed(Dem_MemoryEntry_GetId(MemoryIndex),
                                                   Dem_OperationCycle_GetCycleCounter(Dem_Cfg_GlobalWarmupCycleId()));
    lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
  }
#endif

  if (Dem_StatusIndicator_UpdateOnTestFailed(EventId, MemoryIndex, UpdateFlags) == TRUE) 
  {
    lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
  }

  return lBlockModification;
}                                                                                                                                /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_TriggerWwhObdFreezeFrameStorage
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_TriggerWwhObdFreezeFrameStorage(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  Effects,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  uint8 lReturnValue;

  lReturnValue = DEM_DATA_NO_CHANGES;

  if ( (((Effects & DEM_CFG_TRIGGER_PENDING) != 0u)
    && (Dem_UDSStatus_Test_CDTC(Dem_DTC_GetDTCStatus(EventId)) == FALSE))                                                        
# if (DEM_CFG_SUPPORT_PENDING_UPDATE_FREEZE_FRAME == STD_ON)
    || ((Effects & DEM_CFG_TRIGGER_CONFIRMED) != 0u)
# endif
    )
  {
    lReturnValue = Dem_Mem_StoreWwhObdFreezeFrame(EventId, MemoryIndex);
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_TriggerObdIIFreezeFrameUpdate
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemStorageManager_TriggerObdIIFreezeFrameUpdate(
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
  )
{
  if ( ((DTCContext->DtcEffects & DEM_CFG_TRIGGER_CONFIRMED) != 0u)
# if (DEM_CFG_SUPPORT_PENDING_STORAGE_FREEZE_FRAME == STD_ON)
    || ((DTCContext->DtcEffects & DEM_CFG_TRIGGER_PENDING) != 0u)
# endif
    )
  {
    Dem_EventIdType lUpdatedEventId;
    boolean lDisplacePendingFreezeFrame;
    uint8 lFreezeFrameSlot;
    uint8 lRequiredUpdates;

    lUpdatedEventId = DEM_EVENT_INVALID;

# if (DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME == STD_ON)
    if ((DTCContext->DtcEffects & DEM_CFG_TRIGGER_CONFIRMED) != 0u)
    {
      lDisplacePendingFreezeFrame = TRUE;
    }
    else
# endif
    {
      lDisplacePendingFreezeFrame = FALSE;
    }

    lFreezeFrameSlot = Dem_Mem_FindOBDIIFreezeFrameSlot(DTCContext, lDisplacePendingFreezeFrame);                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

    lRequiredUpdates = Dem_MemStorageManager_TestObdIIFreezeFrameUpdates(DTCContext,lFreezeFrameSlot);                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

    lUpdatedEventId = Dem_Mem_UpdateOBDIIFreezeFrame(DTCContext->EventId, lFreezeFrameSlot, lRequiredUpdates);


# if (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
    if ((DTCContext->QualifyDTC == TRUE)
        && (lUpdatedEventId != DTCContext->EventId))
    {
      Dem_DTC_QualifySingleDTC(lUpdatedEventId);
    }
# endif
  }
}                                                                                                                                
#endif 

#if (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_TestCycleCounterLatched
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
Dem_MemStorageManager_TestCycleCounterLatched(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint16, AUTOMATIC)  CycleCount
  )
{
  boolean lReturnValue;
  Dem_EventIdType lEventId;
  lReturnValue = FALSE;

  lEventId = Dem_MemoryEntry_GetEventId(MemoryEntryId);
# if (DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
  if ((Dem_MemoryEntry_GetCyclesSinceFirstFailed(MemoryEntryId) < DEM_OPERATIONCYCLE_CYCLECOUNT_MAX)
    && (Dem_OperationCycle_CycleCountDistance(Dem_MemoryEntry_GetCyclesSinceFirstFailed(MemoryEntryId), CycleCount) >= 0xffU))   
  {
    Dem_Event_DataUpdateStart(lEventId);
    Dem_MemoryEntry_SetCyclesSinceFirstFailed(MemoryEntryId, DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED);
    lReturnValue = TRUE;
    Dem_Event_DataUpdateFinish(lEventId);
  }
# endif
# if (DEM_CFG_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON)
  if ((Dem_MemoryEntry_GetCyclesSinceLastFailed(MemoryEntryId) < DEM_OPERATIONCYCLE_CYCLECOUNT_MAX)
    && (Dem_OperationCycle_CycleCountDistance(Dem_MemoryEntry_GetCyclesSinceLastFailed(MemoryEntryId), CycleCount) >= 0xffU))    
  {
    Dem_Event_DataUpdateStart(lEventId);
    Dem_MemoryEntry_SetCyclesSinceLastFailed(MemoryEntryId, DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED);
    lReturnValue = TRUE;
    Dem_Event_DataUpdateFinish(lEventId);
  }
# endif
# if (DEM_CFG_DATA_WUC_SINCE_LAST_FAILED == STD_ON)
  if ((Dem_MemoryEntry_GetWarmUpCyclesSinceLastFailed(MemoryEntryId) < DEM_OPERATIONCYCLE_CYCLECOUNT_MAX)
      && (Dem_OperationCycle_CycleCountDistance(Dem_MemoryEntry_GetWarmUpCyclesSinceLastFailed(MemoryEntryId), CycleCount) >= 0xffU))    /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
  {
      Dem_Event_DataUpdateStart(lEventId);
      Dem_MemoryEntry_SetWarmUpCyclesSinceLastFailed(MemoryEntryId, DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED);
      lReturnValue = TRUE;
      Dem_Event_DataUpdateFinish(lEventId);
  }
# endif
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ( (DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON) \
   || (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) \
   || ((DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF)) )
/* ****************************************************************************
 % Dem_MemStorageManager_UpdateCycleCounter
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemStorageManager_UpdateCycleCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  CycleStatus
)
{
  uint8 lDtcStatus;
  boolean lBlockModification;

  lDtcStatus = Dem_DTC_ApplyCombinedStatus(Dem_DTC_RetrieveStatus(EventId));
  lBlockModification = FALSE;

  if ( ((CycleStatus & DEM_OPERATIONCYCLE_CYCLE_STOPPED) != 0u)
    && (Dem_UDSStatus_Test_TNCTOC(lDtcStatus) == FALSE) )                                                                        
  {
#if ( (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) \
   || ((DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF)))
    if (Dem_UDSStatus_Test_TFTOC(lDtcStatus) == FALSE)
    { /* reset the 'consecutive failed cycles' */
      Dem_MemoryEntry_SetConsecutiveFailedCycleCounter(MemoryEntryId, 0);
      lBlockModification = TRUE;
    }
# endif

# if (DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON)
#  if (DEM_CFG_STORAGE_AT_FDC == STD_ON)
    if (Dem_UDSStatus_Test_TFSLC(lDtcStatus) == TRUE)
#  endif
    {
      if (Dem_MemoryEntry_GetTestedCyclesSinceFirstFailed(MemoryEntryId) < 255u)
      {
        Dem_MemoryEntry_SetTestedCyclesSinceFirstFailed(MemoryEntryId, 
                                                        (Dem_MemoryEntry_GetTestedCyclesSinceFirstFailed(MemoryEntryId)
                                                         + 1u));
        lBlockModification = TRUE;
      }
    }
# endif
  }

  return lBlockModification;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_MEMSTORAGEMANAGER_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemStorageManager_Implementation.h
 *********************************************************************************************************************/
