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
/*! \addtogroup Dem_MemoryIF
 *  \{
 *  \file       Dem_MemoryIF_Implementation.h
 *  \brief      Abstraction for multiple event memories.
 *  \details    Implementation of MemoryIF subcomponent which is facade for all memory related tasks.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMORYIF_IMPLEMENTATION_H)
#define DEM_MEMORYIF_IMPLEMENTATION_H

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
#include "Dem_MemoryIF_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/ - units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_TimeSeries_Interface.h"
#include "Dem_Mem_Interface.h"
#include "Dem_MemAccess_Interface.h"
#include "Dem_MemObdFreezeFrame_Interface.h"
#include "Dem_MemoryRestoration_Interface.h"
#include "Dem_MemPermanent_Interface.h"
#include "Dem_MemState_Interface.h"
#include "Dem_MemStorageManager_Interface.h"

#include "Dem_Client_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_Satellite_Interface.h"
#include "Dem_GlobalDiagnostics_Interface.h"
#include "Dem_Infrastructure_Interface.h"
#include "Dem_DiagnosticObserver_Interface.h"
#include "Dem_MemoryEntry_Interface.h"
#include "Dem_Prestore_Interface.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_MEMORYIF_IMPLEMENTATION_FILENAME "Dem_MemoryIF_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

#define DEM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! NvM requested initialization of admin data */
DEM_LOCAL VAR(boolean, DEM_VAR_NOINIT) Dem_Memory_InitAdminDataRequested;

#define DEM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
/*!
 * \defgroup Dem_Memory_PrivateProperties Private Properties
 * \{
 */
#define DEM_START_SEC_CODE
#include "MemMap.h"
/* ****************************************************************************
 * Dem_Memory_GetInitAdminDataRequested
 *****************************************************************************/
/*!
 * \brief         Returns if admin data was initialized or not
 *
 * \details       Returns if admin data was initialized or not
 *
 * \return        TRUE: Admin data was initialized by NvM
 * \return        FALSE: Otherwise
 *
 * \pre           NvM must have restored NV mirrors.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_GetInitAdminDataRequested(
  void
  );


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/


/* ****************************************************************************
 % Dem_Memory_GetInitAdminDataRequested
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_GetInitAdminDataRequested(
  void
  )
{
  return Dem_Memory_InitAdminDataRequested;
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
 * \addtogroup Dem_Memory_PublicProperties
 * \{
 */


/* ****************************************************************************
 % Dem_Memory_SetInitAdminDataRequested
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_SetInitAdminDataRequested(
  CONST(boolean, AUTOMATIC)  InitRequested
  )
{
  Dem_Memory_InitAdminDataRequested = InitRequested;
}

#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Memory_Private Private Methods
 * \{
 */


/* ****************************************************************************
 * Dem_Memory_Init_RestoreMemory
 *****************************************************************************/
/*!
 * \brief         Test and restore corrupted primary/secondary memory.
 *
 * \details       This function verifies the integrity of memory entries and
 *                links them up into the runtime control structures.
 *
 * \param[in]     MemoryInfo
 *                Event memory descriptor.
 *
 * \pre           NvM must have restored NV mirrors.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_Init_RestoreMemory(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_Memory_Init_RestoreMemory
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
Dem_Memory_Init_RestoreMemory(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  )
{ /* No reinitialization - restore primary stack */
  Dem_Memory_MemEntryIterType MemEntryIter;

  Dem_MemState_MemorySetCurrentSize(MemoryInfo, 0);                                                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  /* Iterate through all memory entries. The iteration order must be identical to Dem_MemAccess_MemoryFindIndex. */
  for (Dem_Memory_MemEntry_IterInit(MemoryInfo->MemoryId, &MemEntryIter);                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterExists(&MemEntryIter) == TRUE;                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterNext(&MemEntryIter))                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
    Dem_EventIdType lEventId;

    lMemoryIndex = Dem_Memory_MemEntry_IterGetMemoryIndex(&MemEntryIter);                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */

    /* Check and fix problems with internal corruption of the memory entry record: */
    if (Dem_MemoryRestoration_FixCorruptMemoryEntry(MemoryInfo, lMemoryIndex) == TRUE)                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    { /* Continue with next memory entry */
      continue;                                                                                                                  
    }

    /* If the memory entry is allocated to an event that already has a memory entry: */
    if (Dem_MemoryRestoration_FixDoubleAllocation(MemoryInfo, lMemoryIndex) == TRUE)                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    { /* Continue with next memory entry */
      continue;                                                                                                                  
    }

    lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);
    lEventId = Dem_MemoryEntry_GetEventId(lMemoryEntryId);
    if (lEventId != DEM_EVENT_INVALID)
    {
      uint32 lTimestamp;
      lTimestamp = Dem_MemoryEntry_GetTimestamp(lMemoryEntryId);

      Dem_StatusIndicator_UpdateOnMemoryInitRestoreMemory(lEventId, lMemoryIndex, lMemoryEntryId);

      Dem_MemoryRestoration_RestoreEventStatus(lMemoryEntryId, lMemoryIndex, lEventId);
      Dem_MemoryRestoration_RestoreTripCountFromCFCC(lMemoryEntryId, lEventId);

      Dem_Event_InitUdsFromStatusIndicator(lEventId, lMemoryEntryId);

      /* Synchronize the global timestamp with the timestamp stored in the memory entry */
      if (lTimestamp > Dem_MemState_GetCurrentTimestamp())
      {
        Dem_MemState_SetCurrentTimestamp(lTimestamp);
      }

      /* Sort the memory entry into the chronological list */
      Dem_MemState_SortEntryIntoChronologicalList(MemoryInfo, lMemoryIndex, lTimestamp);                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

      /* Update the number of occupied memory entries */
      Dem_MemState_MemorySetCurrentSize(MemoryInfo,                                                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        (uint8)(Dem_MemState_MemoryGetCurrentSize(MemoryInfo) + 1u));                                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
  }

  /* Update the global timestamp */
  Dem_MemState_SetCurrentTimestamp(Dem_MemState_GetCurrentTimestamp() + 1u);;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

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
 * \addtogroup Dem_Memory_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Memory_FindIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_FindIndex(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(Dem_Cfg_EventDestination(EventId));

  return Dem_MemAccess_MemoryFindIndex(lMemoryInfo,EventId);                                                                     /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

/* ****************************************************************************
 % Dem_Memory_FindTimeSeriesIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_FindTimeSeriesIndex(
  Dem_EventIdType EventId
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_TIMESERIES);

  return Dem_MemAccess_MemoryFindIndex(lMemoryInfo,EventId);                                                                     /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return DEM_MEM_INVALID_MEMORY_INDEX;
#endif
}


/* ****************************************************************************
 % Dem_Memory_FindMemoryIndex_StoredEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_FindMemoryIndex_StoredEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(Dem_Cfg_EventDestination(EventId));

  return Dem_MemAccess_FindMemoryIndex_StoredEvent(lMemoryInfo,EventId);                                                             /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

/* ****************************************************************************
 % Dem_Memory_FreeEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_FreeEvent(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(Dem_Cfg_EventDestination(EventId));
  Dem_MemAccess_MemoryFreeIndex(lMemoryInfo, MemoryIndex);                                                                       /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

/* ****************************************************************************
 % Dem_Memory_GetFirstMemoryIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_GetFirstMemoryIndex(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  return Dem_MemState_MemoryInfoInit(MemoryId)->FirstMemoryIndex;
}

/* ****************************************************************************
 % Dem_Memory_AllocateIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllocateIndex(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(Dem_Cfg_EventDestination(EventId));                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_MemAccess_MemoryAllocateIndex(lMemoryInfo, EventId);                                                                /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

#if ((DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON) && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 % Dem_Memory_AllocateIndexAging
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllocateIndexAging(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  Dem_Cfg_MemoryIndexType lMemoryIndex;
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(Dem_Cfg_EventDestination(EventId));                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lMemoryIndex = Dem_MemAccess_MemoryAllocateAging(lMemoryInfo, EventId);                                                        /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
  return lMemoryIndex;
}
#endif

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 % Dem_Memory_GetOverflow
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_GetOverflow(
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  boolean lReturnValue;

  if ((Dem_MemState_GetMemoryOverflow() & ((uint8)1 << MemoryId)) != 0u)
  {
    lReturnValue = TRUE;
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_Memory_AllocMemEntriesChrono_IterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterInit(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONSTP2VAR(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  Dem_Internal_AssertReturnVoid(MemoryId != DEM_CFG_MEMORYID_PERMANENT , DEM_E_INCONSISTENT_STATE)

  IterPtr->mMemoryInfoPtr = Dem_MemState_MemoryInfoInit(MemoryId);                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mIdx = 0u;                                                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  /*Assign number of stored events*/
  IterPtr->mEndIdx = *(IterPtr->mMemoryInfoPtr->SizePtr);                                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Memory_AllocMemEntriesChrono_IterResume
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterResume(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  StoredChronoIter,
  CONSTP2VAR(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  Dem_Internal_AssertReturnVoid(MemoryId != DEM_CFG_MEMORYID_PERMANENT , DEM_E_INCONSISTENT_STATE)
  IterPtr->mMemoryInfoPtr = Dem_MemState_MemoryInfoInit(MemoryId);                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mIdx = StoredChronoIter;                                                                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = *(IterPtr->mMemoryInfoPtr->SizePtr);                                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Memory_AllocMemEntriesChrono_IterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterNext(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  IterPtr->mIdx += 1u;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Memory_AllocMemEntriesChrono_IterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterExists(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}


/* ****************************************************************************
 % Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex(                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  return Dem_MemState_MemoryGetChronology(IterPtr->mMemoryInfoPtr,                                                               /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
         (uint8)((IterPtr->mEndIdx - 1u) - IterPtr->mIdx ));
}

/* ****************************************************************************
 % Dem_Memory_AllocMemEntriesChrono_IterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterGet(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  return (Dem_Cfg_MemoryIndexType)IterPtr->mIdx;
}

/* ****************************************************************************
 % Dem_Memory_AllEventMemEntries_IterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllEventMemEntries_IterInit(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  IterPtr->mIdx = Dem_MemState_GetFirstValidEventBlockIndex();                                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  /*Assign number of stored events*/
  IterPtr->mEndIdx = Dem_MemState_GetFirstInvalidEventBlockIndex();                                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Memory_AllEventMemEntries_IterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllEventMemEntries_IterNext(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  IterPtr->mIdx += 1u;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Memory_AllEventMemEntries_IterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_AllEventMemEntries_IterExists(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}


/* ****************************************************************************
 % Dem_Memory_AllEventMemEntries_IterGetMemoryIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllEventMemEntries_IterGetMemoryIndex(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  return (Dem_Cfg_MemoryIndexType)IterPtr->mIdx;
}


/* ****************************************************************************
 % Dem_Memory_MemEntry_IterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_MemEntry_IterInit(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONSTP2VAR(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(MemoryId);

  IterPtr->mIdx = Dem_MemState_MemoryGetFirstIndex(lMemoryInfo);                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */

  IterPtr->mEndIdx = Dem_MemState_MemoryGetLastIndex(lMemoryInfo);                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

/* ****************************************************************************
 % Dem_Memory_MemEntry_IterResume_FromIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_MemEntry_IterResume_FromIndex(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC) MemoryIndex,
  CONSTP2VAR(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(MemoryId);

  IterPtr->mIdx = MemoryIndex;                                                                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_MemState_MemoryGetLastIndex(lMemoryInfo);                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

/* ****************************************************************************
 % Dem_Memory_MemEntry_IterResume_FromEntryId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_MemEntry_IterResume_FromEntryId(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
CONST(uint8, AUTOMATIC)  MemoryId,
CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC) MemoryEntryId,
CONSTP2VAR(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
)
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(MemoryId);

  IterPtr->mIdx    = Dem_MemState_MemoryGetFirstIndex(lMemoryInfo) + MemoryEntryId;                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
  IterPtr->mEndIdx = Dem_MemState_MemoryGetLastIndex(lMemoryInfo);                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}


/* ****************************************************************************
 % Dem_Memory_MemEntry_IterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_MemEntry_IterNext(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  IterPtr->mIdx += 1u;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Memory_MemEntry_IterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_MemEntry_IterExists(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}


/* ****************************************************************************
 % Dem_Memory_MemEntry_IterGetMemoryIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_MemEntry_IterGetMemoryIndex(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  return (Dem_Cfg_MemoryIndexType)IterPtr->mIdx;
}


/* ****************************************************************************
 % Dem_Memory_MemEntry_IterGetEntryId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryEntryHandleType, DEM_CODE)
Dem_Memory_MemEntry_IterGetEntryId(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  return Dem_MemoryEntry_GetId((Dem_Cfg_MemoryIndexType)IterPtr->mIdx);
}


/* ****************************************************************************
 % Dem_Memory_GetNumAllocatedMemoryEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_GetNumAllocatedMemoryEntry(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(MemoryId);
  return Dem_MemState_MemoryGetCurrentSize(lMemoryInfo);                                                                         /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 % Dem_Memory_ResetOverflow
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_ResetOverflow(
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  Dem_MemState_ResetOverflow(MemoryId);
}
#endif

/* ****************************************************************************
 % Dem_Memory_UpdateChronology
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_UpdateChronology(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(Dem_Cfg_EventDestination(EventId));
  Dem_MemState_MemoryUpdateIndex(lMemoryInfo, MemoryIndex);                                                                      /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

/* ****************************************************************************
 % Dem_Memory_TriggerWWHOBDFreezeFrameStorage
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TriggerWWHOBDFreezeFrameStorage(
CONST(Dem_EventIdType, AUTOMATIC)  EventId,
CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  Effects,
CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
)
{
  uint8 lReturnValue;

  lReturnValue = DEM_DATA_NO_CHANGES;
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
  {
    lReturnValue = Dem_MemStorageManager_TriggerWwhObdFreezeFrameStorage(EventId, Effects, MemoryIndex);
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Effects)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Memory_TriggerObdIIFreezeFrameStorage
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TriggerObdIIFreezeFrameStorage(
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext                                                               /* PRQA S 3673 */ /* MD_DEM_8.13_Internal */
)
{
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
  {
    Dem_MemStorageManager_TriggerObdIIFreezeFrameUpdate(DTCContext);                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCContext)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

#if ((DEM_CFG_SUPPORT_TRIGGER_PASSED == STD_ON) && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF))
/* ****************************************************************************
 % Dem_Memory_UpdateEventEntryOnPassed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_UpdateEventEntryOnPassed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  UpdateFlags,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  return Dem_MemStorageManager_UpdateEventEntryOnPassed(EventId, UpdateFlags, MemoryIndex);
}
#endif

/* ****************************************************************************
 % Dem_Memory_UpdateEventEntryOnFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_UpdateEventEntryOnFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(Dem_Cfg_StorageTriggerType, AUTOMATIC)  UpdateFlags,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  return Dem_MemStorageManager_UpdateEventEntryOnFailed(EventId, UpdateFlags, MemoryIndex);
}

/* ****************************************************************************
 % Dem_Memory_TestEventEntryUpdatable
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
Dem_Memory_TestEventEntryUpdatable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  boolean  lUpdateable;
  Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;

  lMemoryEntryId = Dem_MemoryEntry_GetId(MemoryIndex);
  if (
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
     (Dem_DTCInternalStatus_GetStoredStatus(Dem_DTC_GetInternalStatus(EventId)) == Dem_DTCInternalStatus_StoredStatus_Aged)
      ||
# endif
#endif
      (Dem_MemoryEntry_TestAgingOnlyEntry(lMemoryEntryId) == TRUE)                                                               /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
     )
  {
    lUpdateable = FALSE;
  }
  else
  {
    lUpdateable = TRUE;
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return lUpdateable;
}

/* ****************************************************************************
 % Dem_Memory_UpdateEventsCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_UpdateEventsCycleCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleStatus
)
{
#if ( (DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON) \
   || (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) \
   || ((DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF)))
  boolean lBlockModification;
  Dem_Cfg_MemoryIndexType lMemoryIndex;
  Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;

  lMemoryIndex = Dem_Memory_FindMemoryIndex_StoredEvent(EventId);
  lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);

  lBlockModification = Dem_MemStorageManager_UpdateCycleCounter(EventId, lMemoryEntryId, CycleStatus);
  if (lBlockModification == TRUE)
  {
    Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
  }
#else
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(CycleStatus)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

#if (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)
/* ****************************************************************************
 % Dem_Memory_LatchCycleCounters
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_LatchCycleCounters(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(uint16, AUTOMATIC)  CycleCounter
)
{
  boolean lDirty;
  lDirty = Dem_MemStorageManager_TestCycleCounterLatched(Dem_MemoryEntry_GetId(MemoryIndex), CycleCounter);
  if (lDirty == TRUE)
  {
    Dem_Nvm_SetEventMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
  }
}
#endif

/* ****************************************************************************
 % Dem_Memory_GetFirstEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Memory_GetFirstEvent(
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  return Dem_MemState_MemoryGetFirstEvent(Dem_MemState_MemoryInfoInit(MemoryId));                                                /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

/* ****************************************************************************
 % Dem_Memory_GetLastEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Memory_GetLastEvent(
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  return Dem_MemState_MemoryGetLastEvent(Dem_MemState_MemoryInfoInit(MemoryId));                                                 /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

/* ****************************************************************************
 % Dem_Memory_Init
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_Init(
  void
  )
{
  boolean lResetStoredData;
  Dem_EventIdType lEventId;
  uint16 lDebounceNvIndex = 0u;


  for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
  { /* Only reset stored status, since debouncing can have changed since pre-initalization */
    Dem_Event_SetInternalStatus(lEventId,
      Dem_DTCInternalStatus_SetStoredStatus(Dem_Event_GetInternalStatus(lEventId), Dem_DTCInternalStatus_StoredStatus_None));

    /* If NV storage of debounce values is configured, and the event uses that feature */
    /* Its safe to do it here since supporting events are not allowed to report before Dem_Init() */
    if (Dem_Event_TestDebounceCounterStoredInNv(lEventId) == TRUE)
    {
      sint16 lDebounceValue;
      boolean lFailedThresholdReached;

      Dem_Internal_AssertReturnVoid(lDebounceNvIndex < Dem_Cfg_GlobalDebounceStorageEventCount(), DEM_E_INCONSISTENT_STATE)

      lDebounceValue = Dem_Mem_DebounceGetStoredValue(lDebounceNvIndex);
      lFailedThresholdReached = Dem_UDSStatus_Test_TF(Dem_Event_GetUDSStatus(lEventId));

      Dem_SatelliteCore_RestoreDebounceValue(
        Dem_Cfg_EventSatelliteId(lEventId),
        Dem_Cfg_EventSatelliteEventId(lEventId),
        lDebounceValue,
        lFailedThresholdReached);

      ++lDebounceNvIndex;
    }
  }

#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  {
    Dem_Cfg_CombinedGroupIndexType lGroupId;
    for (lGroupId = 0u; lGroupId < Dem_Cfg_GlobalCombinedGroupCount(); ++lGroupId)
    {
      Dem_Event_InternalStatusType lInternalStatus;
      Dem_Cfg_CombinedGroupIterType lSubEventIter;

      /* Initialize the combination group internal status */
      lInternalStatus = 0x00u;

      /* For all combination groups, test if at least one sub-events is available by configuration.
         Initialization in PreInit and Init can have different settings for
         event availability, so repeat the calculation for combined DTCs */
      for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lSubEventIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_CombinedGroupIterExists(&lSubEventIter) == TRUE;                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_CombinedGroupIterNext(&lSubEventIter))                                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        if (Dem_Cfg_EventAvailableByVariant(Dem_Cfg_CombinedGroupIterGet(&lSubEventIter)) == TRUE)                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
        { /* If so, set the availability in the combination status. */
          lInternalStatus = Dem_EventInternalStatus_SetAvailableInVariant(lInternalStatus);
          break;
        }
      }
      Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, lInternalStatus);
    }
  }
#endif

  /* Initialize enable and storage conditions (based on configuration) */
  Dem_EnableCondition_Init();
#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
  Dem_StorageCondition_Init();
#endif

  Dem_Memory_TimeSeries_Init();

  lResetStoredData = (boolean)( (Dem_Cfg_AdminData.ImplementationVersion != Dem_Make16Bit(DEM_SW_MAJOR_VERSION, DEM_SW_MINOR_VERSION))
                           || (Dem_Cfg_AdminData.ConfigurationId != Dem_Cfg_GlobalConfigurationId())                             
                           || (Dem_Memory_GetInitAdminDataRequested() == TRUE));                                                 

  if (lResetStoredData == TRUE)
  {
    /* If the NV data is not compatible to the configuration or could not be restored by NvM */
    /* Re-initialize all NV data content and reset the global time stamp */
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_Memory_AllEventMemEntriesIterType lEventMemEntryIter;

    Dem_Nvm_SetAllBlocksDirty();

    /* Do not reinitialize an already initialized Admin data block */
    if (Dem_Memory_GetInitAdminDataRequested() == FALSE)
    {
      (void)Dem_NvM_InitAdminData();
    }

    /* Reset flag to prevent re-initialization on Shutdown-MasterInit*/
    Dem_Memory_SetInitAdminDataRequested(FALSE);

    (void)Dem_NvM_InitStatusData();

    if (Dem_Mem_IsDebounceNvEnabled() == TRUE)
    {
      (void)Dem_NvM_InitDebounceData();
    }

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
    if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
    {
      (void)Dem_NvM_InitObdFreezeFrameData();
    }
#endif
#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
    if ( (Dem_Cfg_IsPermanentSupportedInVariant() == TRUE)
      && (Dem_Mem_PermanentGetInitPattern() != DEM_MEM_PERMANENT_INIT_PATTERN) )
    { /* only initialize permanent memory if it was not initialized before */
      (void)Dem_NvM_InitObdPermanentData();
    }
#endif
    if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
    {
      Dem_Iumpr_InitNv();

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
      (void)Dem_NvM_InitDtrData();
#endif
    }

#if (DEM_FEATURE_NEED_AGING_DATA == STD_ON)
    (void)Dem_NvM_InitAgingData();
#endif
    Dem_DTC_InitMemIndependentCycleCounterDataNv();

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE_NV == STD_ON)
    (void)Dem_NvM_InitEventAvailableData();
#endif

    Dem_MemState_SetCurrentTimestamp(1U);
    Dem_MemState_MemorySetCurrentSize(Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PRIMARY), 0);                                 /* SBSW_DEM_CALL_MEMORYINFO_POINTER */

#if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
    Dem_MemState_MemorySetCurrentSize(Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_SECONDARY), 0);                               /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
#endif
    if (Dem_Cfg_IsPermanentSupportedInVariant() == TRUE)
    {
      Dem_MemState_MemorySetCurrentSize(Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PERMANENT), 0);                               /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
    }

    for (Dem_Memory_AllEventMemEntries_IterInit(&lEventMemEntryIter);                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Memory_AllEventMemEntries_IterExists(&lEventMemEntryIter) == TRUE;                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Memory_AllEventMemEntries_IterNext(&lEventMemEntryIter))                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      lMemoryIndex = Dem_Memory_AllEventMemEntries_IterGetMemoryIndex(&lEventMemEntryIter);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_MemoryEntry_Init(Dem_MemoryEntry_GetId(lMemoryIndex));
    }
    Dem_Memory_TimeSeries_InitNvData();
  }
  /* Otherwise */
  else
  {
    Dem_MemState_SetCurrentTimestamp(0U);

    /* Rebuild the event memory control data from NV data contents */
    Dem_Memory_Init_RestoreMemory(Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PRIMARY));                                        /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
#if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
    Dem_Memory_Init_RestoreMemory(Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_SECONDARY));                                      /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
#endif

  }
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
  {
    /* In OBD configurations, initialize the visible OBD freeze frame */
    Dem_Mem_FreezeFrameIndexMode02 = Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame();
  }
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
  /* If prestore freeze frame is enabled, initialize freeze frame prestorage */
  Dem_Prestore_Init();
#endif

  Dem_StatusIndicator_Init();
}                                                                                                                                /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_Memory_InitConfirmedChronology
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_InitConfirmedChronology(
  void
  )
{
  Dem_MemPermanent_ConfirmedChronologyInit();
}
#endif

/* ****************************************************************************
 % Dem_Memory_ConfirmedChronologyResetOverflown
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_ConfirmedChronologyResetOverflown(
  void
  )
{
#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
  Dem_MemPermanent_ConfirmedChronologyResetOverflown();
#endif
}

/* ****************************************************************************
 % Dem_Memory_ConfirmedChronoAddEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_ConfirmedChronoAddEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  MasterEventId
  )
{
#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
  Dem_MemPermanent_ConfirmedChronoAddEvent(MasterEventId, FALSE);
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MasterEventId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Memory_PermanentFillUp
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_PermanentFillUp(void)
{
#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
  Dem_MemPermanent_FillUp();
#endif
}

/* ****************************************************************************
 % Dem_Memory_PermanentB1SetActive
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_PermanentB1SetActive(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  void
)
{
#if (DEM_FEATURE_NEED_PERMANENT_FOR_WWHOBD == STD_ON)
  Dem_MemPermanent_SetB1PermanentDTCsActive();
#endif
}

/* ****************************************************************************
 % Dem_Memory_ConfirmedChronoFreeEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_ConfirmedChronoFreeEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
  Dem_MemPermanent_ConfirmedChronoFreeEvent(EventId);
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Memory_UpdatePermanentEntryVisibility
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_UpdatePermanentEntryVisibility(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PERMANENTDTC_IMMEDIATE_VISIBLE == STD_ON)
  Dem_MemPermanent_UpdateEntryVisibility(EventId);
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_MEMORYIF_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemoryIF_Implementation.h
 *********************************************************************************************************************/
