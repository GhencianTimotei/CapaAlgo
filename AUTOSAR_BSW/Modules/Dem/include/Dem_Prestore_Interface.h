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
 *  \defgroup   Dem_Prestore Prestore
 *  \{
 *  \file       Dem_Prestore_Interface.h
 *  \brief      Stores and manages 'prestored freezeframes'.
 *  \details    Pre-store snapshot data for an event, in order to freeze that data set when the event is stored later.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_PRESTORE_INTERFACE_H)
#define DEM_PRESTORE_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Prestore_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Prestore_PublicProperties Public Properties
 * \{
 */

 /* ****************************************************************************
 * Dem_Prestore_isPrestoreFFEnabled
 *****************************************************************************/
 /*!
 * \brief         Return if prestorage of freeze frames is supported.
 * \details       -
 *
 * \return        TRUE
 *                Supported
 * \return        FALSE
 *                Not supported
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Prestore_isPrestoreFFEnabled(
  void
  );

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_GetLockedIndex
 *****************************************************************************/
/*!
 * \brief         Get the LockedIndex value.
 *
 * \details       Get the LockedIndex value.
 *
 * \return        LockedIndex value.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_PrestorageIndexType, DEM_CODE)
Dem_Prestore_GetLockedIndex(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntryGetGlobalSRecDataPtr
 *****************************************************************************/
/*!
 * \brief         Get data buffer for global snapshot record data of a prestored
 *                entry.
 *
 * \details       Get data buffer for global snapshot record data of a prestored
 *                entry.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        Address of the data buffer.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
 *                && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetGlobalSRecDataPtr(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntryGetSRecDataPtr
 *****************************************************************************/
/*!
 * \brief         Get data buffer for UDS snapshot record data of a prestored
 *                entry.
 *
 * \details       Get data buffer for UDS snapshot record data of a prestored
 *                entry.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        Address of the data buffer.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
 *                && (DEM_CFG_SUPPORT_SRECS == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetSRecDataPtr(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntryGetObdIIFFDataPtr
 *****************************************************************************/
/*!
 * \brief         Get data buffer for OBD freeze frame data of a prestored
 *                entry.
 *
 * \details       Get data buffer for OBD freeze frame data of a prestored
 *                entry.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        Address of the data buffer.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
 *                && (DEM_CFG_SUPPORT_OBDII == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetObdIIFFDataPtr(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) && ((DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON) || (DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON))
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntryGetJ1939FFDataPtr
 *****************************************************************************/
/*!
 * \brief         Get data buffer for J1939 freeze frame data of a prestored
 *                entry.
 *
 * \details       Get data buffer for J1939 freeze frame data of a prestored
 *                entry.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        Address of the data buffer.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
 *                && ( (DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON)
 *                  || (DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON))
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetJ1939FFDataPtr(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) && (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntryGetWwhObdFFDataPtr
 *****************************************************************************/
/*!
 * \brief         Get data buffer for WWH-OBD freeze frame data of a prestored
 *                entry.
 *
 * \details       Get data buffer for WWH-OBD freeze frame data of a prestored
 *                entry.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        Address of the data buffer.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
 *                && (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetWwhObdFFDataPtr(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Prestore_Public Public Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the prestorage free list.
 *
 * \details       Initializes the prestorage free list.
 *
 * \pre           Can only be called during Dem initialization
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_Init(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_StateSetDiscard
 *****************************************************************************/
/*!
 * \brief         Marks a prestored entry as used up
 *
 * \details       Prestored data (if available) is valid throughout the whole
 *                event processing step. This function marks the current data
 *                to be discarded after event processing completes.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_StateSetDiscard(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_EventPrestorageLock
 *****************************************************************************/
/*!
 * \brief         Locks a ready prestored entry to use its data
 *
 * \details       This function prepares the prestored data of the given event
 *                (if available) for consumption during the event processing
 *                step.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           Must be called within critical section 'DiagMonitor'
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_EventPrestorageLock(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_EventPrestorageRelease
 *****************************************************************************/
/*!
 * \brief         Unlock the previously locked prestored entry
 *
 * \details       This function releases the prestored data locked by
 *                Dem_Prestore_EventPrestorageLock, if such data exists.
 *
 *                If the data was consumed during the event processing step,
 *                the data is discarded.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_EventPrestorageRelease(
  void
  );
#endif

/* ****************************************************************************
 * Dem_Prestore_EventPrestorageClear
 *****************************************************************************/
/*!
 * \brief         Clears the prestorage entry of an event
 *
 * \details       Clears the prestorage entry of an event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        E_OK
 *                The data was cleared successfully
 * \return        E_NOT_OK
 *                The data was not cleared, e.g. no data was available
 *
 * \pre           Must be called within critical section 'DiagMonitor'
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Prestore_EventPrestorageClear(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Prestore_EventPrestoreFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Trigger prestoring freeze frame data for an event
 *
 * \details       Trigger prestoring freeze frame data for an event if
 *                preconditions are fulfilled.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        E_OK
 *                The data was collected successfully (if processed synchronously).
 *                Prestore freeze frame request accepted (if processed asynchronously).
 *
 * \return        E_NOT_OK
 *                No data was collected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 * \pre           Function should only be invoked when feature "Prestorage of 
 *                freeze frames" is supported
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Prestore_EventPrestoreFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Prestore_EventClearPrestoredFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Trigger clearing the prestored freeze frame data for an event
 *
 * \details       Trigger clearing the prestored freeze frame data for an event
 *                if preconditions are fulfilled.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        E_OK
 *                Prestore data cleared (if processed synchronously).
 *                Clear prestore data request accepted (if processed asynchronously).
 *
 * \return        E_NOT_OK
 *                No data was cleared, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 * \pre           Function should only be invoked when the feature "Support 
 *                prestorage of freeze frames" is supported.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Prestore_EventClearPrestoredFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Prestore_MainFunction
 *****************************************************************************/
/*!
 * \brief         Process queued prestorage operations
 *
 * \details       Process queued prestorage operations
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_MainFunction(
  void
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_PRESTORE_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Prestore_Interface.h
 *********************************************************************************************************************/
