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
/*! \addtogroup Dem_MemState
 *  \{
 *  \file       Dem_MemState_Implementation.h
 *  \brief      Encapsulate global data stored for an event memory.
 *  \details    Implementation file for MemState subcomponent which encapsulate global data stored for an event memory.
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

#if !defined (DEM_MEMSTATE_IMPLEMENTATION_H)
#define DEM_MEMSTATE_IMPLEMENTATION_H

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
#include "Dem_MemState_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_TimeSeries_Interface.h"
#include "Dem_MemoryEntry_Interface.h"
#include "Dem_MemPermanent_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_MEMSTATE_IMPLEMENTATION_FILENAME "Dem_MemState_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Number of stored entries in primary memory */
DEM_LOCAL VAR(uint8, DEM_VAR_NOINIT)                    Dem_MemState_PrimaryCurrentCount;

#if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
/*! Number of stored entries in secondary memory */
DEM_LOCAL VAR(uint8, DEM_VAR_NOINIT)                    Dem_MemState_SecondaryCurrentCount;
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/*! Number of permanent DTCs */
DEM_LOCAL VAR(uint8, DEM_VAR_NOINIT)          Dem_MemState_PermanentCurrentCount;
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/*! Number of stored time-series entries */
DEM_LOCAL VAR(uint8, DEM_VAR_NOINIT)          Dem_MemState_TimeSeriesCurrentCount;                                               /* PRQA S 3218 */ /* MD_DEM_8.7 */
#endif

#define DEM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define DEM_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Current time stamp, used to establish a chronological ordering */
DEM_LOCAL VAR(uint32, DEM_VAR_NOINIT)         Dem_MemState_CurrentTimestamp;

#define DEM_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */     

#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */     

/*! MemoryInfo for the primary memory */
DEM_LOCAL CONST(Dem_MemState_MemoryInfoType, DEM_CONST) Dem_MemState_PrimaryInfo =                                               /* PRQA S 3218 */ /* MD_DEM_8.7 */
{
  &Dem_Cfg_PrimaryChronology[0],
  &Dem_MemState_PrimaryCurrentCount,
  DEM_CFG_MEMORY_PRIMARY_INDEX,
  DEM_CFG_GLOBAL_PRIMARY_FIRST,
  DEM_CFG_GLOBAL_PRIMARY_LAST,
  DEM_CFG_GLOBAL_PRIMARY_SIZE,
  DEM_CFG_MEMORYID_PRIMARY,
  Dem_MemoryEntry_TestEntryForEvent,
  Dem_MemoryEntry_FreeEntry
};

#if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
/*! MemoryInfo for the secondary memory */
DEM_LOCAL CONST(Dem_MemState_MemoryInfoType, DEM_CONST) Dem_MemState_SecondaryInfo =                                             /* PRQA S 3218 */ /* MD_DEM_8.7 */
{
  &Dem_Cfg_SecondaryChronology[0],
  &Dem_MemState_SecondaryCurrentCount,
  DEM_CFG_MEMORY_SECONDARY_INDEX,
  DEM_CFG_GLOBAL_SECONDARY_FIRST,
  DEM_CFG_GLOBAL_SECONDARY_LAST,
  DEM_CFG_GLOBAL_SECONDARY_SIZE,
  DEM_CFG_MEMORYID_SECONDARY,
  Dem_MemoryEntry_TestEntryForEvent,
  Dem_MemoryEntry_FreeEntry
};
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/*! MemoryInfo for the time series memory */
DEM_LOCAL CONST(Dem_MemState_MemoryInfoType, DEM_CONST) Dem_MemState_TimeSeriesInfo =                                            /* PRQA S 3218 */ /* MD_DEM_8.7 */
{
  &Dem_Cfg_TimeSeriesChronology[0],
  &Dem_MemState_TimeSeriesCurrentCount,
  DEM_CFG_MEMORY_TIME_SERIES_INDEX,
  DEM_CFG_GLOBAL_PRIMARY_FIRST,
  DEM_CFG_GLOBAL_PRIMARY_LAST,
  DEM_CFG_GLOBAL_TIMESERIES_SNAPSHOTS_SIZE,
  DEM_CFG_MEMORYID_TIMESERIES,
  Dem_Memory_TimeSeries_TestEntryForEvent,
  Dem_Memory_TimeSeries_FreeEntry
};
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/*! MemoryInfo for the permanent memory */
DEM_LOCAL CONST(Dem_MemState_MemoryInfoType, DEM_CONST) Dem_MemState_PermanentInfo =                                            /* PRQA S 3218 */ /* MD_DEM_8.7 */
{
  NULL_PTR,
  &Dem_MemState_PermanentCurrentCount,
  DEM_CFG_MEMORY_PERMANENT_INDEX,
  DEM_CFG_GLOBAL_PRIMARY_FIRST,
  DEM_CFG_GLOBAL_PRIMARY_LAST,
  DEM_CFG_GLOBAL_PERMANENT_SIZE,
  DEM_CFG_MEMORYID_PERMANENT,
  Dem_MemPermanent_TestEntryForEvent,
  Dem_MemPermanent_FreeEntry
};
#endif

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_MemState_PrivateProperties Private Properties
 * \{
 */
#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 * Dem_MemState_SetMemoryOverflow
 *****************************************************************************/
/*!
 * \brief         Set the memory overflow state.
 *
 * \details       Set the memory overflow state.
 *
 * \param[in]     MemoryOverflow
 *                The memory overflow state.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OVFLIND == STD_ON
 *
 * \context       ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_SetMemoryOverflow(                                                                                                  
  CONST(uint8, AUTOMATIC)  MemoryOverflow
  );
#endif


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 % Dem_MemState_SetMemoryOverflow
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_SetMemoryOverflow(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryOverflow
  )
{
  Dem_Cfg_AdminData.MemoryOverflow = MemoryOverflow;
}
#endif
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
 * \addtogroup Dem_MemState_PublicProperties
 * \{
 */
/* ****************************************************************************
 % Dem_MemState_SetCurrentTimestamp
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_SetCurrentTimestamp(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint32, AUTOMATIC)  CurrentTimeStamp
  )
{
  Dem_MemState_CurrentTimestamp = CurrentTimeStamp;
}

/* ****************************************************************************
 % Dem_MemState_GetCurrentTimestamp
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MemState_GetCurrentTimestamp(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return Dem_MemState_CurrentTimestamp;
}



#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 % Dem_MemState_GetMemoryOverflow
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemState_GetMemoryOverflow(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return Dem_Cfg_AdminData.MemoryOverflow;
}
#endif

/* ****************************************************************************
 % Dem_MemState_MemoryGetId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemState_MemoryGetId(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  )
{
  return MemoryInfo->MemoryId;
}

/* ****************************************************************************
 % Dem_MemState_MemoryGetChronology
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemState_MemoryGetChronology(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(uint8, AUTOMATIC)  ChronoIndex
  )
{
  return (MemoryInfo->ChronoPtr)[ChronoIndex];                                                                                   /* PRQA S 2822 */ /* MD_DEM_Dir4.1_ReadOperation */
}

/* ****************************************************************************
 % Dem_MemState_MemorySetChronology
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_MemorySetChronology(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(uint8, AUTOMATIC)  ChronoIndex,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ((ChronoIndex >= Dem_MemState_MemoryGetMaxSize(MemoryInfo))                                                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    || (MemoryInfo->ChronoPtr == NULL_PTR))
  {
    Dem_Error_RunTimeCheckFailed(DEM_MEMSTATE_IMPLEMENTATION_FILENAME, __LINE__);                                                /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    (MemoryInfo->ChronoPtr)[ChronoIndex] = MemoryIndex;                                                                          /* SBSW_DEM_ARRAY_WRITE_MEMORYCHRONOLOGY */
  }
}

/* ****************************************************************************
 % Dem_MemState_MemoryGetFirstIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemState_MemoryGetFirstIndex(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  )
{
  return MemoryInfo->FirstMemoryIndex;
}

/* ****************************************************************************
 % Dem_MemState_MemoryGetLastIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemState_MemoryGetLastIndex(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  )
{
#if(DEM_CFG_SUPPORT_PERMANENT == STD_ON)
  Dem_Internal_AssertReturnValue(MemoryInfo->MemoryId != DEM_CFG_MEMORYID_PERMANENT, DEM_E_INCONSISTENT_STATE, MemoryInfo->FirstMemoryIndex);
#endif
  return (Dem_Cfg_MemoryIndexType)(MemoryInfo->FirstMemoryIndex + MemoryInfo->MaxSize);
}

/* ****************************************************************************
 % Dem_MemState_MemoryGetMaxSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemState_MemoryGetMaxSize(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  )
{
  return MemoryInfo->MaxSize;
}

/* ****************************************************************************
 % Dem_MemState_MemoryGetCurrentSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemState_MemoryGetCurrentSize(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  )
{
  return *(MemoryInfo->SizePtr);
}

/* ****************************************************************************
 % Dem_MemState_MemorySetCurrentSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_MemorySetCurrentSize(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(uint8, AUTOMATIC)  Size
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (Size > Dem_MemState_MemoryGetMaxSize(MemoryInfo))                                                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    Dem_Error_RunTimeCheckFailed(DEM_MEMSTATE_IMPLEMENTATION_FILENAME, __LINE__);                                                /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    *(MemoryInfo->SizePtr) = Dem_MemState_MemoryGetMaxSize(MemoryInfo);                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
#endif
  {
    *(MemoryInfo->SizePtr) = Size;                                                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}

/* ****************************************************************************
 % Dem_MemState_MemoryGetFirstEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemState_MemoryGetFirstEvent(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  )
{
  return MemoryInfo->FirstEvent;
}

/* ****************************************************************************
 % Dem_MemState_MemoryGetLastEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemState_MemoryGetLastEvent(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  )
{
  return MemoryInfo->LastEvent;
}

/* ****************************************************************************
 % Dem_MemState_GetFirstValidEventMemoryBlockIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemState_GetFirstValidEventBlockIndex(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return Dem_Cfg_MemoryPrimaryIndex();
}

/* ****************************************************************************
 % Dem_MemState_GetFirstInvalidEventMemoryBlockIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemState_GetFirstInvalidEventBlockIndex(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  Dem_Cfg_MemoryIndexType lReturnValue;
  lReturnValue = (Dem_Cfg_MemoryIndexType)
                 ( Dem_Cfg_MemoryPrimaryIndex() 
                 + Dem_Cfg_GlobalPrimaryMaxCount()
                 + Dem_Cfg_GlobalSecondaryMaxCount());

  return lReturnValue;
}

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
 * \defgroup Dem_MemState_Private Private Methods
 * \{
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
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
 * \addtogroup Dem_MemState_Public
 * \{
 */

/* ****************************************************************************
 % Dem_MemState_MemoryInfoInit
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
DEM_LOCAL_INLINE FUNC(Dem_MemState_MemoryInfoPtrType, DEM_CODE)
Dem_MemState_MemoryInfoInit(
  CONST(uint8, AUTOMATIC)  MemoryId                                                                                              /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_MemState_MemoryInfoPtrType lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
  if (MemoryId == DEM_CFG_MEMORYID_PERMANENT)
  {
    lReturnValue = &Dem_MemState_PermanentInfo;
  }
  else
#endif
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  if (MemoryId == DEM_CFG_MEMORYID_TIMESERIES)
  {
    lReturnValue = &Dem_MemState_TimeSeriesInfo;
  }
  else
#endif
#if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
  if (MemoryId == DEM_CFG_MEMORYID_SECONDARY)
  {
    lReturnValue = &Dem_MemState_SecondaryInfo;
  }
  else
#endif
  {
    lReturnValue = &Dem_MemState_PrimaryInfo;
  }
  return lReturnValue;
}

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 % Dem_MemState_SetOverflow
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_SetOverflow(
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  uint8 lOldOverflow;
  uint8 lNewOverflow;

  lOldOverflow = Dem_MemState_GetMemoryOverflow();
  lNewOverflow = lOldOverflow | ((uint8)1 << MemoryId);
  if (lOldOverflow != lNewOverflow)
  {
    Dem_MemState_SetMemoryOverflow(lNewOverflow);
  }
}
#endif

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 % Dem_MemState_ResetOverflow
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_ResetOverflow(
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  uint8 lOldOverflow;
  uint8 lNewOverflow;

  lOldOverflow = Dem_MemState_GetMemoryOverflow();
  lNewOverflow = lOldOverflow & (~((uint8)1 << MemoryId));
  if (lOldOverflow != lNewOverflow)
  {
    Dem_MemState_SetMemoryOverflow(lNewOverflow);
  }
}
#endif

/* ****************************************************************************
 % Dem_MemState_MemoryUpdateIndex
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
Dem_MemState_MemoryUpdateIndex(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  uint8 lChronoIterator;
  Dem_Cfg_MemoryIndexType lTempIndex;

  /* Store the global timestamp to the entry, and update it */
  Dem_MemoryEntry_SetTimestamp(Dem_MemoryEntry_GetId(MemoryIndex), Dem_MemState_GetCurrentTimestamp());
  Dem_MemState_SetCurrentTimestamp(Dem_MemState_GetCurrentTimestamp() + 1u);

  /* move downwards the chronology moving all entries, until the updated element is overwritten */
  lChronoIterator = (uint8)(Dem_MemState_MemoryGetCurrentSize(MemoryInfo) - 1u);                                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lTempIndex = Dem_MemState_MemoryGetChronology(MemoryInfo, lChronoIterator);                                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  while (lTempIndex != MemoryIndex)
  {
    Dem_Cfg_MemoryIndexType lSwap;

    lSwap = lTempIndex;
    --lChronoIterator;
    lTempIndex = Dem_MemState_MemoryGetChronology(MemoryInfo, lChronoIterator);                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    Dem_MemState_MemorySetChronology(MemoryInfo, lChronoIterator, lSwap);                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
    if ((lChronoIterator == 0u) && (lTempIndex != MemoryIndex))
    {
      /* chronology is inconsistent */
      Dem_Error_RunTimeCheckFailed(DEM_MEMSTATE_IMPLEMENTATION_FILENAME, __LINE__);                                              /* SBSW_DEM_POINTER_RUNTIME_CHECK */
      break;
    }
#endif
  }

  Dem_MemState_MemorySetChronology(MemoryInfo, (uint8)(Dem_MemState_MemoryGetCurrentSize(MemoryInfo) - 1u), MemoryIndex);         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_MemState_SortEntryIntoChronologicalList
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
Dem_MemState_SortEntryIntoChronologicalList(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)    MemoryIndex,
  CONST(uint32, AUTOMATIC)                     Timestamp
  )
{
  uint8 lSortedIndex;
  for ( lSortedIndex = Dem_MemState_MemoryGetCurrentSize(MemoryInfo);                                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        (lSortedIndex > 0u)  && (Dem_MemoryEntry_GetTimestamp(Dem_MemoryEntry_GetId(                                             /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
                                Dem_MemState_MemoryGetChronology(MemoryInfo, (uint8)(lSortedIndex - 1u))))  > Timestamp);        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
       --lSortedIndex
    )
  {
    Dem_MemState_MemorySetChronology(
      MemoryInfo,                                                                                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      lSortedIndex,
      Dem_MemState_MemoryGetChronology(MemoryInfo, (uint8)(lSortedIndex - 1u)));                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }

  Dem_MemState_MemorySetChronology(MemoryInfo, lSortedIndex, MemoryIndex);                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_MEMSTATE_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemState_Implementation.h
 *********************************************************************************************************************/
