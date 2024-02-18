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
 *  \defgroup   Dem_MemState Memory State Manager
 *  \{
 *  \file       Dem_MemState_Interface.h
 *  \brief      Encapsulate global data stored for an event memory.
 *  \details    Interface file for MemState subcomponent which encapsulate global data stored for an event memory.
 *              This includes handling chronology for event entries, tracking occupancy, overflow status, update state
 *              etc.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMSTATE_INTERFACE_H)
#define DEM_MEMSTATE_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemState_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_MemState_PublicProperties Public Properties
 * \{
 */
 
/* ****************************************************************************
 * Dem_MemState_SetCurrentTimestamp
 *****************************************************************************/
/*!
 * \brief         Set current value for time stamp.
 *
 * \details       Set current value for time stamp.
 *
 * \param[in]     CurrentTimeStamp
 *                Current value for time stamp.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_SetCurrentTimestamp(                                                                                                
  CONST(uint32, AUTOMATIC)  CurrentTimeStamp
  );

/* ****************************************************************************
 * Dem_MemState_GetCurrentTimestamp
 *****************************************************************************/
/*!
 * \brief         Get current value for time stamp.
 *
 * \details       Get current value for time stamp.
 *
 * \return        Current value for time stamp.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MemState_GetCurrentTimestamp(                                                                                                
  void
  );




#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 * Dem_MemState_GetMemoryOverflow
 *****************************************************************************/
/*!
 * \brief         Get the memory overflow state.
 *
 * \details       Get the memory overflow state.
 *
 * \return        The memory overflow state.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OVFLIND == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemState_GetMemoryOverflow(                                                                                                  
  void
  );
#endif

/* ****************************************************************************
 * Dem_MemState_MemoryGetId
 *****************************************************************************/
/*!
 * \brief         Get the identifier of the event memory
 *
 * \details       Get the identifier of the event memory
 *
 * \param[in]     MemoryInfo
 *                Pointer to the memory descriptor for the event memory
 *
 * \return        Unique identifier of the event memory
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemState_MemoryGetId(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  );

/* ****************************************************************************
 * Dem_MemState_MemoryGetChronology
 *****************************************************************************/
/*!
 * \brief         Get the Nth oldest memory index.
 *
 * \details       Get the Nth oldest memory index. 0 is the oldest index.
 *
 * \param[in]     MemoryInfo
 *                Pointer to the memory descriptor for the event or time series memory.
 * \param[in]     ChronoIndex
 *                Index into chronology.
 *
 * \return        NV Block handle of the memory entry.
 *
 * \pre           MemoryInfo is initialized for event or time series memory.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemState_MemoryGetChronology(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(uint8, AUTOMATIC)  ChronoIndex
  );

/* ****************************************************************************
 * Dem_MemState_MemorySetChronology
 *****************************************************************************/
/*!
 * \brief         Set the Nth oldest memory index
 *
 * \details       Set the Nth oldest memory index. 0 is the oldest index.
 *
 * \param[in]     MemoryInfo
 *                Pointer to the memory descriptor for the event or time series memory.
 * \param[in]     ChronoIndex
 *                Index into chronology.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \pre           MemoryInfo is initialized for event or time series memory.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_MemorySetChronology(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(uint8, AUTOMATIC)  ChronoIndex,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );

/* ****************************************************************************
 * Dem_MemState_MemoryGetFirstIndex
 *****************************************************************************/
/*!
 * \brief         Get the start memory index of the event memory.
 *
 * \details       Get the start memory index of the event memory.
 *
 * \param[in]     MemoryInfo
 *                Pointer to the memory descriptor for the event memory.
 *
 * \return        Memory index of the first memory entry belonging to the range.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemState_MemoryGetFirstIndex(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  );

/* ****************************************************************************
 * Dem_MemState_MemoryGetLastIndex
 *****************************************************************************/
/*!
 * \brief         Get the end memory index of the event memory.
 *
 * \details       Get the end memory index of the event memory. The index
 *                returned does not belong to the event memory.
 *
 * \param[in]     MemoryInfo
 *                Pointer to the memory descriptor for the event or time series memory.
 *
 * \return        Memory index of the first memory entry not belonging to the range.
 *
 * \pre           MemoryInfo is initialized for event or time series memory.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemState_MemoryGetLastIndex(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  );

/* ****************************************************************************
 * Dem_MemState_MemoryGetMaxSize
 *****************************************************************************/
/*!
 * \brief         Get the size of the event memory.
 *
 * \details       Get the size of the event memory.
 *
 * \param[in]     MemoryInfo
 *                Pointer to the memory descriptor for the event memory.
 *
 * \return        The size of the event memory.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemState_MemoryGetMaxSize(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  );

/* ****************************************************************************
 * Dem_MemState_MemoryGetCurrentSize
 *****************************************************************************/
/*!
 * \brief         Get the number of occupied entries in the event memory.
 *
 * \details       Get the number of occupied entries in the event memory.
 *
 * \param[in]     MemoryInfo
 *                Pointer to the memory descriptor for the event memory.
 *
 * \return        The number of occupied entries in the event memory.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemState_MemoryGetCurrentSize(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  );

/* ****************************************************************************
 * Dem_MemState_MemorySetCurrentSize
 *****************************************************************************/
/*!
 * \brief         Set the number of occupied entries in the event memory.
 *
 * \details       Set the number of occupied entries in the event memory.
 *
 * \param[in]     MemoryInfo
 *                Pointer to the memory descriptor for the event memory.
 * \param[in]     Size
 *                New number of occupied entries in the event memory.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_MemorySetCurrentSize(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(uint8, AUTOMATIC)  Size
  );

/* ****************************************************************************
 * Dem_MemState_MemoryGetFirstEvent
 *****************************************************************************/
/*!
 * \brief         Get first event belonging to the event memory.
 *
 * \details       Get first event belonging to the event memory.
 *
 * \param[in]     MemoryInfo
 *                Pointer to the memory descriptor for the event memory.
 *
 * \return        Unique handle of the event.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemState_MemoryGetFirstEvent(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  );

/* ****************************************************************************
 * Dem_MemState_MemoryGetLastEvent
 *****************************************************************************/
/*!
 * \brief         Get last event belonging to the event memory.
 *
 * \details       Get last event belonging to the event memory.
 *
 * \param[in]     MemoryInfo
 *                Pointer to the memory descriptor for the event memory.
 *
 * \return        Unique handle of the event.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemState_MemoryGetLastEvent(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  );

/* ****************************************************************************
 * Dem_MemState_GetFirstValidEventBlockIndex
 *****************************************************************************/
/*!
 * \brief         Get the first valid event block index.
 *
 * \details       Get the first valid event block index.
 *
 * \return        First valid event block index.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemState_GetFirstValidEventBlockIndex(                                                                                       
  void
  );

/* ****************************************************************************
 * Dem_MemState_GetFirstInvalidEventBlockIndex
 *****************************************************************************/
/*!
 * \brief         Get the first invalid event block index.
 *
 * \details       Get the first invalid event block index.
 *
 * \return        First invalid event block index.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemState_GetFirstInvalidEventBlockIndex(                                                                                       
  void
  );

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
 * \defgroup Dem_MemState_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_MemState_MemoryInfoInit
 *****************************************************************************/
/*!
 * \brief         Get the memory descriptor for the event, time
 *                series and permanent memory.
 *
 * \details       Get the memory descriptor for the event, time
 *                series and permanent memory.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the requested memory.
 *
 * \return        Pointer to the memory descriptor for the requested memory.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MemState_MemoryInfoPtrType, DEM_CODE)
Dem_MemState_MemoryInfoInit(
  CONST(uint8, AUTOMATIC)  MemoryId
  );

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 * Dem_MemState_SetOverflow
 *****************************************************************************/
/*!
 * \brief         Set the 'overflowed' state for an event memory.
 *
 * \details       Set the 'overflowed' state for an event memory.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the event memory.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OVFLIND == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_SetOverflow(
  CONST(uint8, AUTOMATIC)  MemoryId
  );
#endif

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 * Dem_MemState_ResetOverflow
 *****************************************************************************/
/*!
 * \brief         Clear the 'overflowed' state for an event memory.
 *
 * \details       Clear the 'overflowed' state for an event memory.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the event memory.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OVFLIND == STD_ON.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_ResetOverflow(
  CONST(uint8, AUTOMATIC)  MemoryId
  );
#endif

/* ****************************************************************************
 * Dem_MemState_MemoryUpdateIndex
 *****************************************************************************/
/*!
 * \brief         Update the chronology of one entry in the event memory.
 *
 * \details       Moves the passed entry up to most current in the chronology
 *                list.
 *
 * \param[in]     MemoryInfo
 *                Event memory descriptor
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_MemoryUpdateIndex(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );

/* ****************************************************************************
 * Dem_MemState_SortEntryIntoChronologicalList
 *****************************************************************************/
/*!
 * \brief         Sort the memory entry into the chronological list.
 *
 * \details       Sort the memory entry into the chronological list.
 *
 * \param[in]     MemoryInfo
 *                Pointer to the memory descriptor for the event memory.
 * \param[in]     MemoryIndex
 *                Memory index of the current memory entry.
 * \param[in]     Timestamp
 *                Current timestamp of the Memory Entry.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_SortEntryIntoChronologicalList(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)    MemoryIndex,
  CONST(uint32, AUTOMATIC)                     Timestamp
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_MEMSTATE_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemState_Interface.h
 *********************************************************************************************************************/
