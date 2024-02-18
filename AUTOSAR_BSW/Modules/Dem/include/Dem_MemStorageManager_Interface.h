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
/*! \ingroup    Dem_Memory
 *  \defgroup   Dem_MemStorageManager Event Memory Storage Manager
 *  \{
 *  \file       Dem_MemStorageManager_Interface.h
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

#if !defined (DEM_MEMSTORAGEMANAGER_INTERFACE_H)
#define DEM_MEMSTORAGEMANAGER_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemStorageManager_Types.h"

                                                           /* Required types */
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_MemStorageManager_Public Public Methods
 * \{
 */

#if ( (DEM_CFG_SUPPORT_TRIGGER_PASSED == STD_ON)\
   && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 * Dem_MemStorageManager_UpdateEventEntryOnPassed
 *****************************************************************************/
/*!
 * \brief         Updates enviromental data stored for an event on passed report.
 *
 * \details       Depending on configuration of the event data, collect the
 *                data to be updated due to the update trigger(s) in UpdateFlags.
 *                This includes environment data collected from callback routines.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     UpdateFlags
 *                Trigger flags.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_NO_CHANGES          nothing has changed
 *                DEM_DATA_USERDATA_CHANGED    user provided data was updated
 *
 * \pre           The event must be stored.
 * \config        DEM_CFG_SUPPORT_TRIGGER_PASSED == STD_ON
 *                && DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventEntryOnPassed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  UpdateFlags,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );
#endif

/* ****************************************************************************
 * Dem_MemStorageManager_UpdateEventEntryOnFailed
 *****************************************************************************/
/*!
 * \brief         Updates enviromental data stored for an event on failed report.
 *
 * \details       Depending on configuration of the event data, collect the
 *                data to be updated due to the update trigger(s) in UpdateFlags.
 *                This includes statistical data (e.g. occurrence counter) as
 *                well as environment data collected from callback routines.
 *
 *                Statistical data is stored separately in the MemoryEntry and
 *                is mapped into snapshot and extended records when reading the
 *                data.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     UpdateFlags
 *                Trigger flags.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_NO_CHANGES          nothing has changed
 *                DEM_DATA_USERDATA_CHANGED    user provided data was updated
 *                DEM_DATA_STATISTICS_CHANGED  internal data was updated
 *
 * \pre           The event must be stored.
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventEntryOnFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  UpdateFlags,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_TriggerWwhObdFreezeFrameStorage
 *****************************************************************************/
/*!
 * \brief         Initiate the storage of a WWH-OBD FreezeFrame.
 *
 * \details       If the freeze frame storage trigger is met, initiate storage 
 *                of the WWHOBD Freeze Frame.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     Effects
 *                Trigger flags
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \pre           The event must be a WWH-OBD relevant event
                  The event must be stored.
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_NO_CHANGES          nothing has changed
 *                DEM_DATA_USERDATA_CHANGED    user provided data was updated
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_TriggerWwhObdFreezeFrameStorage(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  Effects,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_TriggerObdIIFreezeFrameUpdate
 *****************************************************************************/
/*!
 * \brief         Initiate the storage or update of an OBDII FreezeFrame.
 *
 * \details       If the freeze frame storage trigger is met, initiate storage 
 *                or update of an OBDII Freeze Frame.
 *
 * \param[in,out] DTCContext
 *                DTC processing context. This function updates the QualifyDTC 
 *                flag.
 *
 * \pre           The event must be an OBD relevant event
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemStorageManager_TriggerObdIIFreezeFrameUpdate(
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
  );
#endif

#if (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_TestCycleCounterLatched
 *****************************************************************************/
/*!
 * \brief         Latches overflowing operation cycle counters
 *
 * \details       Latches overflowing operation cycle counters
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     CycleCount
 *                The new cycle counter
 *
 * \return        TRUE: The memory entry has been modified
 *                FALSE: The memory entry has not been modified
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemStorageManager_TestCycleCounterLatched(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint16, AUTOMATIC)  CycleCount
  );
#endif

#if ( (DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON) \
   || (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) \
   || ((DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF)))
/* ****************************************************************************
 * Dem_MemStorageManager_UpdateCycleCounter
 *****************************************************************************/
/*!
 * \brief         Updates operation cycle counters, if necessary.
 *
 * \details       Function resets the consecutive failed cycles and cycles tested
 *                since first failed, if required.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     CycleStatus
 *                Cycle status changes
 *
 * \return        TRUE: The memory entry has been modified
 *                FALSE: The memory entry has not been modified
 *
 * \pre           The passed event must be a master event
 * \config        DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON ||
 *                DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON ||
 *                (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON && 
 *                DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF)
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemStorageManager_UpdateCycleCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_MEMSTORAGEMANAGER_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemStorageManager_Interface.h
 *********************************************************************************************************************/
