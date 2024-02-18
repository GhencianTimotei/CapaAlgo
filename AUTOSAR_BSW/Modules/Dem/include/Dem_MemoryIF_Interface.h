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
 *  \defgroup   Dem_MemoryIF Dem MemoryIF
 *  \{
 *  \file       Dem_MemoryIF_Interface.h
 *  \brief      Abstraction for multiple event memories.
 *  \details    Public Interfaces of MemoryIF subcomponent which is facade for all memory related tasks.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMORYIF_INTERFACE_H)
#define DEM_MEMORYIF_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemoryIF_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Memory_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Memory_SetInitAdminDataRequested
 *****************************************************************************/
/*!
 * \brief         Sets if admin data was initialized or not
 *
 * \details       Sets if admin data was initialized or not
 *
 * \param[in]     InitRequested
 *                TRUE: Admin data was initialized by NvM
 *                FALSE: Otherwise
 *
 * \pre           NvM must have restored NV mirrors.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_SetInitAdminDataRequested(
  CONST(boolean, AUTOMATIC)  InitRequested
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
 * \defgroup Dem_Memory_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Memory_FindMemoryIndex_StoredEvent
 *****************************************************************************/
/*!
 * \brief         Finds the memory block index of the event.
 *
 * \details       Finds the memory block index of the event. 
 *                Calls Det and sets DEM to state DEM_INITSTATE_HALTED_AFTER_ERROR
 *                if event is not stored in memory and runtime checks are enabled.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Valid Memory Block Index: If event is stored in memory.
 *                DEM_MEM_INVALID_MEMORY_INDEX: If event is not stored in memory.
 *
 * \pre           The event must have a memory entry, i.e it is marked as
 *                'stored'. 
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_FindMemoryIndex_StoredEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Memory_FindIndex
 *****************************************************************************/
/*!
 * \brief         Finds the memory index of the event if allocated.
 *
 * \details       Finds the memory index of the event if allocated. If the event
 *                does not have a valid memory entry, an invalid index is
 *                returned instead.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The memory index used by the event.
 *                In error cases, an invalid index is returned.
 *
 * \pre           -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_FindIndex(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Memory_FindTimeSeriesIndex
 *****************************************************************************/
/*!
 * \brief         Finds the memory index of a time series entry for event if allocated.
 *
 * \details       Finds the memory index of a time series entry. If the event
 *                does not have a valid time series memory entry, an invalid index is
 *                returned instead.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The memory index used by the event.
 *                In error cases, an invalid index is returned.
 *
 * \pre           -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_FindTimeSeriesIndex(
  Dem_EventIdType  EventId
  );

/* ****************************************************************************
 * Dem_Memory_FreeEvent
 *****************************************************************************/
/*!
 * \brief         Frees an event memory entry
 *
 * \details       This function frees an event memory entry.
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block
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
Dem_Memory_FreeEvent(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Memory_GetFirstMemoryIndex
 *****************************************************************************/
/*!
 * \brief         Get the start memory index of a memory.
 *
 * \details       Get the start memory index of a memory.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
 *
 * \return        Memory index of the first memory entry belonging to the memory.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_GetFirstMemoryIndex(
  CONST(uint8, AUTOMATIC)  MemoryId
  );


/* ****************************************************************************
 * Dem_Memory_AllocateIndex
 *****************************************************************************/
/*!
 * \brief         Selects a memory entry for an event
 *
 * \details       This function manages the event memory storage. If a free
 *                slot is available, it is returned directly. In case no free
 *                slot is available, the configured displacement algorithm is
 *                applied to free a slot.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The memory index of the allocated event memory entry if one
 *                could be identified. DEM_MEM_INVALID_MEMORY_INDEX if no entry
 *                was allocated.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllocateIndex(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if ((DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON) && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 * Dem_Memory_AllocateIndexAging
 *****************************************************************************/
/*!
 * \brief         Selects a memory entry for an event's aging counter
 *
 * \details       If a free memory slot is available, it is returned directly.
 *                There is no fallback in case of a filled up event memory.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The memory index of the allocated event memory entry if one
 *                could be identified. DEM_MEM_INVALID_MEMORY_INDEX if no entry
 *                was allocated.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON 
 *                 && DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllocateIndexAging(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 * Dem_Memory_GetOverflow
 *****************************************************************************/
/*!
 * \brief         Get the 'overflowed' state for an event memory.
 *
 * \details       Get the 'overflowed' state for an event memory.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
 *
 * \return        TRUE
 *                The event memory overflowed.
 * \return        FALSE
 *                The event memory didn't overflow.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OVFLIND == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_GetOverflow(
  CONST(uint8, AUTOMATIC)  MemoryId
  );
#endif

/* ****************************************************************************
 * Dem_Memory_AllocMemEntriesChrono_IterExists
 *****************************************************************************/
/*!
 * \brief         Test if the iterator points to a valid element
 *
 * \details       Test if the iterator points to a valid element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        TRUE
 *                Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex() will return a valid element
 *                on this iterator
 * \return        FALSE
 *                Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex() is undefined on this iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterExists(
  CONSTP2CONST(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );

/* ****************************************************************************
 * Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex
 *****************************************************************************/
/*!
 * \brief         Get the event memory index derived from the iterator in 
 *                chronologial order starting with the most recent event entry.
 *
 * \details       Get the event memory index derived from the iterator in 
 *                chronologial order starting with the most recent event entry.
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Memory index derived from the iterator.
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex(
  CONSTP2CONST(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );

/* ****************************************************************************
 * Dem_Memory_AllocMemEntriesChrono_IterGet
 *****************************************************************************/
/*!
 * \brief         Get the current position of the iterator
 *
 * \details       Get the current position of the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Chrono index for the current position of the iterator.
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterGet(
  CONSTP2CONST(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );

/* ****************************************************************************
 * Dem_Memory_AllocMemEntriesChrono_IterInit
 *****************************************************************************/
/*!
 * \brief         Initializes for iteration over allocated event memory entries.
 *
 * \details       Initializes for iteration over allocated event memory entries.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the event memory.
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           Memory has a chronology.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterInit(
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONSTP2VAR(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );

/* ****************************************************************************
 * Dem_Memory_AllocMemEntriesChrono_IterResume
 *****************************************************************************/
/*!
 * \brief         Initializes for continued iteration over allocated event 
 *                memory entries.
 *
 * \details       Initializes for continued iteration over allocated event 
 *                memory entries. The previous iterator position is provided 
 *                by calling function.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the event memory.
 * \param[in]     StoredChronoIter
 *                Stored chrono iterator that shall be continued with.
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           Memory has a chronology.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterResume(
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  StoredChronoIter,
  CONSTP2VAR(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );



/* ****************************************************************************
 * Dem_Memory_AllocMemEntriesChrono_IterNext
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next (older) element
 *
 * \details       Move the iterator to the next (older) element
 *
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterNext(
  CONSTP2VAR(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );

/* ****************************************************************************
 * Dem_Memory_AllEventMemEntries_IterGetMemoryIndex
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator
 *
 * \details       Get the element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Memory index derived from the iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllEventMemEntries_IterGetMemoryIndex(
  CONSTP2CONST(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );

/* ****************************************************************************
 * Dem_Memory_AllEventMemEntries_IterInit
 *****************************************************************************/
/*!
 * \brief         Initializes for iteration over all event memory entries.
 *
 * \details       Initializes for iteration over all event memory entries.
 *
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllEventMemEntries_IterInit(
  CONSTP2VAR(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );

/* ****************************************************************************
 * Dem_Memory_AllEventMemEntries_IterNext
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next element
 *
 * \details       Move the iterator to the next element
 *
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllEventMemEntries_IterNext(
  CONSTP2VAR(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );

/* ****************************************************************************
 * Dem_Memory_AllEventMemEntries_IterExists
 *****************************************************************************/
/*!
 * \brief         Test if the iterator points to a valid element
 *
 * \details       Test if the iterator points to a valid element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        TRUE
 *                Dem_Memory_AllEventMemEntries_IterGetMemoryIndex() will return a valid element
 *                on this iterator
 * \return        FALSE
 *                Dem_Memory_AllEventMemEntries_IterGetMemoryIndex() is undefined on this iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_AllEventMemEntries_IterExists(
  CONSTP2CONST(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );

/* ****************************************************************************
 * Dem_Memory_MemEntry_IterGetMemoryIndex
 *****************************************************************************/
/*!
 * \brief         Get the memory index of element pointed to by the iterator
 *
 * \details       Get the memory index of element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        MemoryIndex
 *                Handle of the memory block
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_MemEntry_IterGetMemoryIndex(
  CONSTP2CONST(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );


/* ****************************************************************************
 * Dem_Memory_MemEntry_IterGetEntryId
 *****************************************************************************/
/*!
 * \brief         Get the memory entry id of element pointed to by the iterator
 *
 * \details       Get the memory entry id of element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        MemoryEntryId
 *                The memory entry handle
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryEntryHandleType, DEM_CODE)
Dem_Memory_MemEntry_IterGetEntryId(
  CONSTP2CONST(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );

/* ****************************************************************************
 * Dem_Memory_MemEntry_IterInit
 *****************************************************************************/
/*!
 * \brief         Initializes for iteration over memory entries of the given memory
 *
 * \details       Initializes for iteration over memory entries of the given memory
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_MemEntry_IterInit(
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONSTP2VAR(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );


/* ****************************************************************************
 Dem_Memory_MemEntry_IterResume_FromIndex
 *****************************************************************************/
/*!
 * \brief         Initializes for continued iteration over memory entries.
 *
 * \details       Initializes for continued iteration over memory entries. 
 *                The previous iterator position is provided by calling function.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
 * \param[in]     MemoryIndex
 *                Stored memory index that shall be continued with.
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_MemEntry_IterResume_FromIndex(
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONSTP2VAR(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );

/* ****************************************************************************
Dem_Memory_MemEntry_IterResume_FromEntryId
 *****************************************************************************/
/*!
 * \brief         Initializes for continued iteration over memory entries.
 *
 * \details       Initializes for continued iteration over memory entries.
 *                The previous iterator position is provided by calling function.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
 * \param[in]     MemoryEntryId
 *                Memory entry from which iteration should continue
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_MemEntry_IterResume_FromEntryId(
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC) MemoryEntryId,
  CONSTP2VAR(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );

/* ****************************************************************************
 * Dem_Memory_MemEntry_IterNext
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next element
 *
 * \details       Move the iterator to the next element
 *
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_MemEntry_IterNext(
  CONSTP2VAR(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );

/* ****************************************************************************
 * Dem_Memory_MemEntry_IterExists
 *****************************************************************************/
/*!
 * \brief         Test if the iterator points to a valid element
 *
 * \details       Test if the iterator points to a valid element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        TRUE
 *                Dem_Memory_MemEntry_IterGetMemoryIndex() will return a valid element
 *                on this iterator
 * \return        FALSE
 *                Dem_Memory_MemEntry_IterGetMemoryIndex() is undefined on this iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_MemEntry_IterExists(
  CONSTP2CONST(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );

/* ****************************************************************************
 * Dem_Memory_GetNumAllocatedMemoryEntry
 *****************************************************************************/
/*!
 * \brief         Facade, fetch the number of allocated entries of the respective memory.
 *
 * \details       Facade, fetch the number of allocated entries of the respective memory.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
 *
 * \return        Number of allocated entries.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_GetNumAllocatedMemoryEntry(                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryId
  );

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 * Dem_Memory_ResetOverflow
 *****************************************************************************/
/*!
 * \brief         Clear the 'overflowed' state for the given memory.
 *
 * \details       Clear the 'overflowed' state for the given memory.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OVFLIND == STD_ON.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_ResetOverflow(
  CONST(uint8, AUTOMATIC)  MemoryId
  );
#endif

/* ****************************************************************************
 * Dem_Memory_UpdateChronology
 *****************************************************************************/
/*!
 * \brief         Update the event memory entry chronolgy.
 *
 * \details       Update the event memory entry chronolgy.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \pre           The event must be stored
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_UpdateChronology(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );

/* ****************************************************************************
 * Dem_Memory_TriggerObdIIFreezeFrameStorage
 *****************************************************************************/
/*!
 * \brief         Initiate the storage of a OBD II FreezeFrame.
 *
 * \details       If the freeze frame storage trigger is met, initiate storage 
 *                of the OBD II Freeze Frame.
 *
 * \param[in,out] DTCContext
 *                DTC processing context. This function updates the QualifyDTC
 *                flag.
 *
 * \pre           The event must be a OBD relevant event
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TriggerObdIIFreezeFrameStorage(
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
  );

/* ****************************************************************************
 * Dem_Memory_TriggerWWHOBDFreezeFrameStorage
 *****************************************************************************/
/*!
 * \brief         Initiate the storage of a WWHOBD FreezeFrame.
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
 * \pre           The event must be a WHHOBD relevant event
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
Dem_Memory_TriggerWWHOBDFreezeFrameStorage(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  Effects,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );

#if ((DEM_CFG_SUPPORT_TRIGGER_PASSED == STD_ON) && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 * Dem_Memory_UpdateEventEntryOnPassed
 *****************************************************************************/
/*!
 * \brief         Updates all data stored for an event with trigger 'Passed'.
 *
 * \details       Updates all data stored for an event with trigger 'Passed'.
 *                 Protects data update against concurrent data readouts.
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
 * \config        DEM_CFG_SUPPORT_TRIGGER_PASSED == STD_ON
 *                && DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_UpdateEventEntryOnPassed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  UpdateFlags,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );
#endif

/* ****************************************************************************
 * Dem_Memory_UpdateEventEntryOnFailed
 *****************************************************************************/
/*!
 * \brief         Updates all data stored for an event with triggers derived from
 *                an event status report 'Failed' or 'Fdc Threshold Reached'.
 *
 * \details       Updates all data stored for an event with triggers derived from
 *                an event status report 'Failed' or 'Fdc Threshold Reached'.
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
Dem_Memory_UpdateEventEntryOnFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  UpdateFlags,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );

/* ****************************************************************************
 * Dem_Memory_TestEventEntryUpdatable
 *****************************************************************************/
/*!
 * \brief         Test if the event memory entry is not an 'aging only' or 
 *                'retained in memory' entry.
 *
 * \details       Test if the event memory entry is not an 'aging only' or 
 *                'retained in memory' entry.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \return        TRUE
 *                If entry is not of type 'aging only' or 'retained in memory'
 * \return        FALSE
 *                If entry is of type 'aging only' or 'retained in memory'
 *
 * \pre           The event must be stored
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TestEventEntryUpdatable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );


/* ****************************************************************************
 * Dem_Memory_UpdateEventsCycleCounter
 *****************************************************************************/
/*!
 * \brief         Update the operation cycle counter in the event memory entry.
 *
 * \details       Update the operation cycle counter in the event memory entry.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \param[in]     CycleStatus
 *                Cycle status changes
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_UpdateEventsCycleCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  );

#if (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)
/* ****************************************************************************
 * Dem_Memory_LatchCycleCounters
 *****************************************************************************/
/*!
 * \brief         Test if cycle counters need to be latched. Latch the counters 
 *                if it is required.
 *
 * \details       Test if cycle counters need to be latched. Latch the counters 
 *                if it is required.
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 * \param[in]     CycleCounter
 *                Current cycle count
 *
 * \pre           Cycle counters have already been incremented for the cycle
   \config        DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_LatchCycleCounters(
CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
CONST(uint16, AUTOMATIC)  CycleCounter
);
#endif

/* ****************************************************************************
 * Dem_Memory_GetFirstEvent
 *****************************************************************************/
/*!
 * \brief         Get the first event mapped to the given memory.
 *
 * \details       Get the first event mapped to the given memory.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
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
Dem_Memory_GetFirstEvent(
  CONST(uint8, AUTOMATIC)  MemoryId
  );

/* ****************************************************************************
 * Dem_Memory_GetLastEvent
 *****************************************************************************/
/*!
 * \brief         Get the last event mapped to the given memory.
 *
 * \details       Get the last event mapped to the given memory.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
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
Dem_Memory_GetLastEvent(
  CONST(uint8, AUTOMATIC)  MemoryId
  );

/* ****************************************************************************
 * Dem_Memory_Init
 *****************************************************************************/
/*!
 * \brief         Initializes backing memory
 *
 * \details       This function controls initialization of the memory
 *                subcomponent. After the function completes, event memories
 *                are available.
 *
 * \pre           May only be called during initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_Init(
  void
  );

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_Memory_InitConfirmedChronology
 *****************************************************************************/
/*!
 * \brief         Initialize confirmed chronology
 *
 * \details       Initialize confimred chronology
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_InitConfirmedChronology(
  void
  );
#endif

/* ****************************************************************************
 * Dem_Memory_ConfirmedChronologyResetOverflown
 *****************************************************************************/
/*!
 * \brief         Reset overflow state of confirmed chronology
 *
 * \details       Reset overflow state of confirmed chronology if permanent 
 *                memory is enabled
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_ConfirmedChronologyResetOverflown(
  void
  );


/* ****************************************************************************
 * Dem_Memory_ConfirmedChronoAddEvent
 *****************************************************************************/
/*!
 * \brief         Add an confirmed event to confirmed chronology
 *
 * \details       Add an confirmed event to confirmed chronology if permanent 
 *                memory is enabled
 *
 * \param[in]     MasterEventId
 *                Unique handle of the DTC.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_ConfirmedChronoAddEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  MasterEventId
  );

/* ****************************************************************************
 * Dem_Memory_PermanentFillUp
 *****************************************************************************/
/*!
 * \brief         Fillup permanent memory and confirmed chronology.
 *
 * \details       Fillup permanent memory and confirmed chronology if permanent 
 *                memory is enabled.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_PermanentFillUp(void);

/* ****************************************************************************
 * Dem_Memory_PermanentB1SetActive
 *****************************************************************************/
/*!
 * \brief         Ensure existing permanent entrys of B1 DTCs are in state 'Active'
 *
 * \details       Ensure existing permanent entrys of B1 DTCs are in state 'Active'  
 *                if permanent memory is enabled for WwhObd.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_PermanentB1SetActive(void);

/* ****************************************************************************
 * Dem_Memory_ConfirmedChronoFreeEvent
 *****************************************************************************/
/*!
 * \brief         Frees the entry in confirmed chronology for the event
 *
 * \details       Frees the entry in confirmed chronology for the event if permanent 
 *                memory is enabled.
 *
 * \param[in]     ConfirmedChronologyIndex
 *                Index in Dem_Cfg_StatusData.ConfirmedChronology[]
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_ConfirmedChronoFreeEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Memory_UpdatePermanentEntryVisibility
 *****************************************************************************/
/*!
 * \brief         Mark permanent entry of event VISIBLE
 *
 * \details       Mark permanent entry of event VISIBLE if OBDII and immediate 
 *                visibility of permanent DTCs is supported
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_UpdatePermanentEntryVisibility(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_MEMORYIF_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemoryIF_Interface.h
 *********************************************************************************************************************/
