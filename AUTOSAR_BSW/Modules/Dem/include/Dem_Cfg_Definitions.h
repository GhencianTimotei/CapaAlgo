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
 *         File:  Dem_Cfg_Definitions.h
 *      Project:  MICROSAR Diagnostic Event Manager (Dem)
 *       Module:  Configuration
 *    Generator:  -
 *
 *  Description:  Inline function definitions of the configuration subcomponent
 *
 *********************************************************************************************************************/
/*!
 *  \addtogroup   Dem_Ungrouped
 *  \{
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_CFG_DEFINITIONS_H)                                                                                             /* PRQA S 0883 */ /* MD_DEM_19.15 */
#define DEM_CFG_DEFINITIONS_H

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

#include "Dem_Cfg_Declarations.h"
#include "Dem_Error_Interface.h"
#include "Dem_Esm_Interface.h"

/* ********************************************************************************************************************
 *  GLOBAL INLINE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_CFG_DEFINITIONS_FILENAME "Dem_Cfg_Definitions.h"

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_ComplexIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_ComplexIterExists(                                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Cfg_ComplexIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}
#endif

/* ****************************************************************************
 % Dem_Cfg_ComplexIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_DataIndexType, DEM_CODE)
Dem_Cfg_ComplexIterGet(                                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Cfg_ComplexIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  return (Dem_Cfg_DataIndexType)IterPtr->mIdx;
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_ComplexIterClear
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_ComplexIterClear(
  CONSTP2VAR(Dem_Cfg_ComplexIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                             /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  IterPtr->mIdx = 0u;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = 0u;                                                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_ComplexIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_ComplexIterInit(
  CONSTP2VAR(Dem_Cfg_ComplexIterType, AUTOMATIC, AUTOMATIC)  IterPtr,
  CONST(uint16_least, AUTOMATIC)  StartIndex,
  CONST(uint16_least, AUTOMATIC)  EndIndex
  )
{
  IterPtr->mIdx = StartIndex;                                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = EndIndex;                                                                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_ComplexIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_ComplexIterNext(                                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Cfg_ComplexIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                             /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

/* ****************************************************************************
 % Dem_Cfg_CombinedGroupIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_CombinedGroupIterExists(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Cfg_CombinedGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}

/* ****************************************************************************
 % Dem_Cfg_CombinedGroupIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Cfg_CombinedGroupIterGet(
  CONSTP2CONST(Dem_Cfg_CombinedGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  return Dem_Cfg_GetCombinedEventIds(IterPtr->mIdx);
#else
  return DEM_EVENT_INVALID;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_CombinedGroupIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_CombinedGroupIterInit(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId,                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(Dem_Cfg_CombinedGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                                                        /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  IterPtr->mIdx = Dem_Cfg_GetCombinedEventIdsStartIdxOfCombinedGroups(GroupId);                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetCombinedEventIdsEndIdxOfCombinedGroups(GroupId);                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#else
  IterPtr->mIdx = 0;                                                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = 0;                                                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#endif
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}

/* ****************************************************************************
 % Dem_Cfg_CombinedGroupIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_CombinedGroupIterNext(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Cfg_CombinedGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                                                        /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}


#if (DEM_CFG_SUPPORT_OPCYCLE_STORAGE == STD_OFF) || (DEM_CFG_SUPPORT_OPCYCLE_AUTOMATIC_END == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_CycleIsAutomaticEnd
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_CycleIsAutomaticEnd(
  CONST(uint8, AUTOMATIC)  CycleId                                                                                               /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  boolean lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CycleId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_OPCYCLE_STORAGE == STD_ON) && (DEM_CFG_SUPPORT_OPCYCLE_AUTOMATIC_END == STD_ON)
  lReturnValue = (boolean)Dem_Cfg_IsEndsOnInitOfCycleIdTable(CycleId);
# else
  lReturnValue = TRUE;
# endif
  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_Cfg_CycleIsObdDcy
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_CycleIsObdDcy(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  boolean result;

  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    result = (boolean)(Dem_Cfg_GetOpCycleTypeOfCycleIdTable(CycleId) == DEM_CFG_OPCYC_OBD_DCY);
  }
  else
  {
    result = FALSE;
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CycleId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return result;
}

/* ****************************************************************************
 % Dem_Cfg_CycleIsWarmup
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_CycleIsWarmup(                                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  boolean lResult;
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    lResult = (boolean)(Dem_Cfg_GetOpCycleTypeOfCycleIdTable(CycleId) == DEM_CFG_OPCYC_WARMUP);
  }
  else
  {
    lResult =  FALSE;
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CycleId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return lResult;
}

/* ****************************************************************************
 % Dem_Cfg_DataCallbackType
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_DataCallbackType(
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex                                                                             /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DataIndex)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint8)(Dem_Cfg_GetElementKindOfDataElementTable(DataIndex));
}

#if ( (DEM_CFG_SUPPORT_ERECS == STD_ON) \
   || (DEM_CFG_SUPPORT_SRECS == STD_ON) \
   || (DEM_CFG_SUPPORT_OBDII == STD_ON) \
   || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) \
   || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) \
   || (DEM_FEATURE_NEED_OBD_ODOMETER == STD_ON) \
   || (DEM_FEATURE_NEED_ENGINE_RUN_TIME == STD_ON) \
   || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) )
/* ****************************************************************************
 % Dem_Cfg_DataCbkRead
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_ReadDataFPtrType, DEM_CODE)
Dem_Cfg_DataCbkRead(
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DataIndex)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (Dem_ReadDataFPtrType)(Dem_Cfg_GetReadDataFuncOfDataElementTable(DataIndex));
}
#endif

/* ****************************************************************************
 % Dem_Cfg_DataIsStoredInNV
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_DataIsStoredInNV(
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DataIndex)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (boolean)Dem_Cfg_IsDataIsStoredInNVOfDataElementTable(DataIndex);
}

/* ****************************************************************************
 % Dem_Cfg_DataSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_DataSize(
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex                                                                             /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DataIndex)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint8)(Dem_Cfg_GetElementSizeOfDataElementTable(DataIndex));
}

/* ****************************************************************************
 % Dem_Cfg_DidBufferIndexFast
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_DidBufferIndexFast(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DidIndex)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
  return Dem_Cfg_GetDidOffsetFastOfDataCollectionTable(DidIndex);
#else
  return (uint16)0x00U;
#endif
}


/* ****************************************************************************
 % Dem_Cfg_DidBufferIndexNormal
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_DidBufferIndexNormal(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DidIndex)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  return Dem_Cfg_GetDidOffsetNormalOfDataCollectionTable(DidIndex);
#else
  return (uint16)0x00;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_DidDataIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_DidDataIterExists(
  CONSTP2CONST(Dem_Cfg_DidDataIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}

/* ****************************************************************************
 % Dem_Cfg_DidDataIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_DataIndexType, DEM_CODE)
Dem_Cfg_DidDataIterGet(
  CONSTP2CONST(Dem_Cfg_DidDataIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetDataElementTableCol2ElmtInd(IterPtr->mIdx);
}

/* ****************************************************************************
 % Dem_Cfg_DidDataIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_DidDataIterInit(
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex,                                                                              /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(Dem_Cfg_DidDataIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                             /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DidIndex)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  IterPtr->mIdx = Dem_Cfg_GetDataElementTableCol2ElmtIndStartIdxOfDataCollectionTable(DidIndex);                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetDataElementTableCol2ElmtIndEndIdxOfDataCollectionTable(DidIndex);                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Cfg_DidDataIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_DidDataIterNext(
  CONSTP2VAR(Dem_Cfg_DidDataIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                             /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Cfg_DidNumber
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_DidNumber(                                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex                                                                               /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DidIndex)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_CFG_SUPPORT_OBDII == STD_ON) \
   || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) )
  return Dem_Cfg_GetIdNumberOfDataCollectionTable(DidIndex);
#else
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
  return 0U;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_DidSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_DidSize(                                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex                                                                               /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DidIndex)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_CFG_SUPPORT_OBDII == STD_ON) \
   || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) )
  return Dem_Cfg_GetCollectionSizeOfDataCollectionTable(DidIndex);
#else
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
  return 0U;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_ERecDid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_DidIndexType, DEM_CODE)
Dem_Cfg_ERecDid(                                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_ERecIndexType, AUTOMATIC)  ERecIndex
  )
{
  return (Dem_Cfg_DidIndexType)(ERecIndex);
}

/* ****************************************************************************
 % Dem_Cfg_ERecType
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_ERecType(                                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_ERecIndexType, AUTOMATIC)  ERecIndex                                                                             /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ERecIndex)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_ERECS == STD_ON)
  return Dem_Cfg_GetStorageKindOfDataCollectionTable(ERecIndex);
#else
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  return 0;
#endif
}

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) && (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)
/* ****************************************************************************
 % Dem_Cfg_ERecTrigger
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_StorageTriggerType, DEM_CODE)
Dem_Cfg_ERecTrigger(
  CONST(Dem_Cfg_ERecIndexType, AUTOMATIC)  ERecIndex                                                                             /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ERecIndex)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetTriggerOfDataCollectionTable(ERecIndex);
}
#endif

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_ERecUpdate
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_ERecUpdate(
  CONST(Dem_Cfg_ERecIndexType, AUTOMATIC)  ERecIndex                                                                             /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ERecIndex)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (boolean)Dem_Cfg_IsUpdateOfDataCollectionTable(ERecIndex);
}
#endif

#if (DEM_FEATURE_NEED_EVENT_PRECONFIRMED == STD_OFF)
/* ****************************************************************************
 % Dem_Cfg_EventAgingCycle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_EventAgingCycle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetAgingCycleIdOfEventTable(EventId);
}
#endif

/* ****************************************************************************
 % Dem_Cfg_EventAgingTarget
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_EventAgingTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetAgingCycleCounterThresholdOfEventTable(EventId);
}

/* ****************************************************************************
 % Dem_Cfg_EventAvailableByDefault
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventAvailableByDefault(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_EVENTAVAILABLE_DEFAULT == STD_ON)
  return Dem_Cfg_IsEventAvailableDefault(EventId);
#else
  return TRUE;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventAvailableByVariant
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventAvailableByVariant(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_IsEventAvailableInVariant(EventId);                                                                             /* PRQA S 2843 */ /* MD_DEM_Dir4.1_ReadOperation */
}

#if (DEM_CFG_NOTIFY_CLEAR_ALLOWED == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventCbkClearAllowed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_ClearEventAllowedFPtrType, DEM_CODE)
Dem_Cfg_EventCbkClearAllowed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_ClearEventAllowedFPtrType lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (Dem_Cfg_GetCallbackClearEventAllowedIdxOfEventTable(EventId) >= Dem_Cfg_GetSizeOfCallbackClearEventAllowed())
  {
    lReturnValue = (Dem_ClearEventAllowedFPtrType)NULL_PTR;
    Dem_Error_RunTimeCheckFailed(DEM_CFG_DEFINITIONS_FILENAME, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    lReturnValue = Dem_Cfg_GetCallbackClearEventAllowed(Dem_Cfg_GetCallbackClearEventAllowedIdxOfEventTable(EventId));
  }
  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_Cfg_EventCbkData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventDataChangedFPtrType, DEM_CODE)
Dem_Cfg_EventCbkData(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_EventDataChangedFPtrType lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_NOTIFY_EVENT_DATA == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (Dem_Cfg_GetEventDataChangedIdxOfEventTable(EventId) >= Dem_Cfg_GetSizeOfEventDataChanged())
  {
    lReturnValue = (Dem_EventDataChangedFPtrType)NULL_PTR;
    Dem_Error_RunTimeCheckFailed(DEM_CFG_DEFINITIONS_FILENAME, __LINE__);                                                        /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    lReturnValue = (Dem_EventDataChangedFPtrType)Dem_Cfg_GetEventDataChanged(Dem_Cfg_GetEventDataChangedIdxOfEventTable(EventId));
  }
#else
  lReturnValue = (Dem_EventDataChangedFPtrType)NULL_PTR;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_EventCbkGetFDC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_GetFDCFPtrType, DEM_CODE)
Dem_Cfg_EventCbkGetFDC(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_GetFDCFPtrType lReturnValue;

  lReturnValue = (Dem_GetFDCFPtrType)NULL_PTR;

#if ((DEM_CFG_SUPPORT_DEBOUNCE_MONITORINTERNAL == STD_ON) && (DEM_CFG_SUPPORT_DEBOUNCE_MONITORINTERNAL_GETFDC == STD_ON))
  {
    boolean lCheckResult;
    lCheckResult = (boolean)(Dem_Cfg_GetCallbackGetFdcIdxOfEventTable(EventId) >= Dem_Cfg_GetSizeOfCallbackGetFdc());
    DEM_IGNORE_UNUSED_VARIABLE(lCheckResult)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */ 

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
    if (lCheckResult == TRUE)
    {
      Dem_Error_RunTimeCheckFailed(DEM_CFG_DEFINITIONS_FILENAME, __LINE__);                                                      /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    }
    else
# endif
    {
      lReturnValue = Dem_Cfg_GetCallbackGetFdc(Dem_Cfg_GetCallbackGetFdcIdxOfEventTable(EventId));
    }
  }
#endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_EventCbkInitFuncIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventCbkInitFuncIterExists(
  CONSTP2CONST(Dem_Cfg_EventCbkInitFuncIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                  /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_NOTIFY_INIT_FUNC == STD_ON)
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
#else
  return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventCbkInitFuncIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_InitMonitorForFuncFPtrType, DEM_CODE)
Dem_Cfg_EventCbkInitFuncIterGet(
  CONSTP2CONST(Dem_Cfg_EventCbkInitFuncIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                  /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_InitMonitorForFuncFPtrType lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_NOTIFY_INIT_FUNC == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (IterPtr->mIdx >= Dem_Cfg_GetSizeOfInitMonitorsForFunc())
  {
    lReturnValue = (Dem_InitMonitorForFuncFPtrType)NULL_PTR;
    Dem_Error_RunTimeCheckFailed(DEM_CFG_DEFINITIONS_FILENAME, __LINE__);                                                        /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    lReturnValue = Dem_Cfg_GetInitMonitorsForFunc(IterPtr->mIdx);
  }
#else
  lReturnValue = (Dem_InitMonitorForFuncFPtrType)NULL_PTR;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_EventCbkInitFuncIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_EventCbkInitFuncIterInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(Dem_Cfg_EventCbkInitFuncIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                    /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  #if (DEM_CFG_NOTIFY_INIT_FUNC == STD_ON)
  IterPtr->mIdx = Dem_Cfg_GetInitMonitorsForFuncStartIdxOfInitMonListForFunc(Dem_Cfg_GetInitMonListForFuncIdxOfEventTable(EventId));   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetInitMonitorsForFuncEndIdxOfInitMonListForFunc(Dem_Cfg_GetInitMonListForFuncIdxOfEventTable(EventId));  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#else
  IterPtr->mIdx    = 0u;                                                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = 0u;                                                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventCbkInitFuncIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_EventCbkInitFuncIterNext(
  CONSTP2VAR(Dem_Cfg_EventCbkInitFuncIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                    /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_NOTIFY_INIT_FUNC == STD_ON)
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventCbkInitMonitor
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_InitMonitorForEventFPtrType, DEM_CODE)
Dem_Cfg_EventCbkInitMonitor(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_InitMonitorForEventFPtrType lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_NOTIFY_INIT_MONITOR == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (Dem_Cfg_GetInitMonitorForEventIdxOfEventTable(EventId) >= Dem_Cfg_GetSizeOfInitMonitorForEvent())
  {
    lReturnValue = (Dem_InitMonitorForEventFPtrType)NULL_PTR;
    Dem_Error_RunTimeCheckFailed(DEM_CFG_DEFINITIONS_FILENAME, __LINE__);                                                        /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    lReturnValue = (Dem_InitMonitorForEventFPtrType)(Dem_Cfg_GetInitMonitorForEvent(Dem_Cfg_GetInitMonitorForEventIdxOfEventTable(EventId)));
  }
#else
  lReturnValue = (Dem_InitMonitorForEventFPtrType)NULL_PTR;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_EventCbkStatusIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventCbkStatusIterExists(
  CONSTP2CONST(Dem_Cfg_EventCbkStatusIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_NOTIFY_EVENT_STATUS == STD_ON) && (Dem_Cfg_HasEventStatusChanged() == TRUE)
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
#else
  return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventCbkStatusIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventStatusChangedFPtrType, DEM_CODE)
Dem_Cfg_EventCbkStatusIterGet(
  CONSTP2CONST(Dem_Cfg_EventCbkStatusIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_EventStatusChangedFPtrType lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_NOTIFY_EVENT_STATUS == STD_ON) && (Dem_Cfg_HasEventStatusChanged() == TRUE)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (IterPtr->mIdx >= Dem_Cfg_GetSizeOfEventStatusChanged())
  {
    lReturnValue = (Dem_EventStatusChangedFPtrType)NULL_PTR;
    Dem_Error_RunTimeCheckFailed(DEM_CFG_DEFINITIONS_FILENAME, __LINE__);                                                        /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    lReturnValue = Dem_Cfg_GetEventStatusChanged(IterPtr->mIdx);
  }
#else
  lReturnValue = (Dem_EventStatusChangedFPtrType)NULL_PTR;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_EventCbkStatusIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_EventCbkStatusIterInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(Dem_Cfg_EventCbkStatusIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                      /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_NOTIFY_EVENT_STATUS == STD_ON) && (Dem_Cfg_HasEventStatusChanged() == TRUE)
  IterPtr->mIdx = Dem_Cfg_GetEventStatusChangedStartIdxOfEventTable(EventId);                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetEventStatusChangedEndIdxOfEventTable(EventId);                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  IterPtr->mIdx = 0u;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = 0u;                                                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventCbkStatusIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_EventCbkStatusIterNext(
  CONSTP2VAR(Dem_Cfg_EventCbkStatusIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                      /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_NOTIFY_EVENT_STATUS == STD_ON) && (Dem_Cfg_HasEventStatusChanged() == TRUE)
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventCombinedGroup
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_CombinedGroupIndexType, DEM_CODE)
Dem_Cfg_EventCombinedGroup(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  return (Dem_Cfg_CombinedGroupIndexType)(Dem_Cfg_GetCombinedGroupsIdxOfEventTable(EventId));
#else
  return DEM_CFG_COMBINED_GROUP_INVALID;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventIsCombined
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventIsCombined(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  return (boolean)Dem_Cfg_IsCombinedGroupsUsedOfEventTable(EventId);
#else
  return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventDebounceContinuous
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventDebounceContinuous(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  boolean lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if ( (DEM_FEATURE_NEED_DEBOUNCE == STD_ON) \
   || (DEM_CFG_RESET_DEBOUNCE_ON_ENABLE_ENABLE_CONDITIONS == STD_ON))
    lReturnValue = (boolean)(Dem_Cfg_IsDebounceContinuousOfDebounceTable(Dem_Cfg_GetDebounceTableIdxOfEventTable(EventId)));
#else
  lReturnValue = FALSE;
#endif

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_EventDebounceReset
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventDebounceReset(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (boolean)(Dem_Cfg_IsEventDebounceBehaviorOfDebounceTable(Dem_Cfg_GetDebounceTableIdxOfEventTable(EventId)));
}

/* ****************************************************************************
 % Dem_Cfg_EventDebounceType
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_EventDebounceType(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint8)(Dem_Cfg_GetEventDebounceAlgorithmOfDebounceTable(Dem_Cfg_GetDebounceTableIdxOfEventTable(EventId)));
}

/* ****************************************************************************
 % Dem_Cfg_EventDestination
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_EventDestination(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint8)(Dem_Cfg_GetEventDestinationOfEventTable(EventId));
}

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventDidIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventDidIterExists(
  CONSTP2CONST(Dem_Cfg_EventDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventDidIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_DidIndexType, DEM_CODE)
Dem_Cfg_EventDidIterGet(
  CONSTP2CONST(Dem_Cfg_EventDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetDataCollectionTableFfm2CollInd(IterPtr->mIdx);
}
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventDidIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_EventDidIterInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(Dem_Cfg_EventDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                            /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  IterPtr->mIdx = Dem_Cfg_GetDataCollectionTableFfm2CollIndStartIdxOfFreezeFrameTable(Dem_Cfg_GetFreezeFrameTableStdFFIdxOfEventTable(EventId));   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetDataCollectionTableFfm2CollIndEndIdxOfFreezeFrameTable(Dem_Cfg_GetFreezeFrameTableStdFFIdxOfEventTable(EventId));  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventDidIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_EventDidIterNext(
  CONSTP2VAR(Dem_Cfg_EventDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                            /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalSnapshotDidIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_GlobalSnapshotDidIterExists(
  CONSTP2CONST(Dem_Cfg_GlobalSnapshotDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalSnapshotDidIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_DidIndexType, DEM_CODE)
Dem_Cfg_GlobalSnapshotDidIterGet(
  CONSTP2CONST(Dem_Cfg_GlobalSnapshotDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                 /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetDataCollectionTableFfm2CollInd(IterPtr->mIdx);
}
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalSnapshotDidIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_GlobalSnapshotDidIterInit(
  CONSTP2VAR(Dem_Cfg_GlobalSnapshotDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                   /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  IterPtr->mIdx = Dem_Cfg_GetDataCollectionTableFfm2CollIndStartIdxOfFreezeFrameTable(Dem_Cfg_GetFreezeFrameTableIdxOfGlobalSnapshotRecord(0));   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetDataCollectionTableFfm2CollIndEndIdxOfFreezeFrameTable(Dem_Cfg_GetFreezeFrameTableIdxOfGlobalSnapshotRecord(0));  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalSnapshotDidIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_GlobalSnapshotDidIterNext(
  CONSTP2VAR(Dem_Cfg_GlobalSnapshotDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                   /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

/* ****************************************************************************
 % Dem_Cfg_EventFailedTarget
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(sint16, DEM_CODE)
Dem_Cfg_EventFailedTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_SUPPORT_DEBOUNCE_COUNTER == STD_ON)
  return (sint16)(Dem_Cfg_GetFailedThresholdOfDebounceTable(Dem_Cfg_GetDebounceTableIdxOfEventTable(EventId)));
# else
  return 1;
# endif
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventFunctionalUnit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_EventFunctionalUnit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint8)(Dem_Cfg_GetFunctionalUnitOfDtcTable(Dem_Cfg_GetDtcTableIdxOfEventTable(EventId)));
}
#endif

/* ****************************************************************************
 % Dem_Cfg_EventHealingTarget
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_EventHealingTarget(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint8)(Dem_Cfg_GetHealingTargetOfEventTable(EventId));
}

#if (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventNormalIndicatorIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventNormalIndicatorIterExists(
  CONSTP2CONST(Dem_Cfg_EventNormalIndicatorIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                              /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}
#endif

#if (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventNormalIndicatorIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_NormalIndicatorIndexType, DEM_CODE)
Dem_Cfg_EventNormalIndicatorIterGet(
  CONSTP2CONST(Dem_Cfg_EventNormalIndicatorIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                              /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  return (Dem_Cfg_NormalIndicatorIndexType)(IterPtr->mIdx);
}
#endif

#if (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventNormalIndicatorIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_EventNormalIndicatorIterInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(Dem_Cfg_EventNormalIndicatorIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  IterPtr->mIdx = Dem_Cfg_GetNormalIndicatorTableStartIdxOfEventTable(EventId);                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetNormalIndicatorTableEndIdxOfEventTable(EventId);                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventNormalIndicatorIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_EventNormalIndicatorIterNext(
  CONSTP2VAR(Dem_Cfg_EventNormalIndicatorIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

/* ****************************************************************************
 % Dem_Cfg_EventSpecialIndicatorIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventSpecialIndicatorIterExists(
  CONSTP2CONST(Dem_Cfg_EventSpecialIndicatorIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}

/* ****************************************************************************
 % Dem_Cfg_EventSpecialIndicatorIterGetId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_EventSpecialIndicatorIterGetId(
  CONSTP2CONST(Dem_Cfg_EventSpecialIndicatorIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                             /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  uint8 lSpecialIndicatorId;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr);
# if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
  lSpecialIndicatorId= (uint8)(Dem_Cfg_GetIdOfSpecialIndicatorTable(IterPtr->mIdx));
#else
  lSpecialIndicatorId = 0;
#endif
  return lSpecialIndicatorId;
}


/* ****************************************************************************
 % Dem_Cfg_EventSpecialIndicatorIterInit
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
Dem_Cfg_EventSpecialIndicatorIterInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(Dem_Cfg_EventSpecialIndicatorIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                               /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
  IterPtr->mIdx = Dem_Cfg_GetSpecialIndicatorTableStartIdxOfEventTable(EventId);                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetSpecialIndicatorTableEndIdxOfEventTable(EventId);                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  if (Dem_Cfg_EventSpecialIndicatorIterGetId(IterPtr) == DEM_CFG_SPECIAL_INDICATOR_NONE)                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
#endif
  { 
    IterPtr->mIdx = Dem_Cfg_GetSizeOfSpecialIndicatorTable();                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    IterPtr->mEndIdx = Dem_Cfg_GetSizeOfSpecialIndicatorTable();                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}

/* ****************************************************************************
 % Dem_Cfg_EventSpecialIndicatorIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_EventSpecialIndicatorIterNext(
  CONSTP2VAR(Dem_Cfg_EventSpecialIndicatorIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                               /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Cfg_GetSpecialIndicatorBehavior
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_IndicatorStatusType, DEM_CODE)
Dem_Cfg_GetSpecialIndicatorBehavior(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Cfg_EventSpecialIndicatorIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                             /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_IndicatorStatusType lSpecialIndicatorBehavior;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr);
  lSpecialIndicatorBehavior = DEM_INDICATOR_OFF;
#if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
  lSpecialIndicatorBehavior = (Dem_IndicatorStatusType)(Dem_Cfg_GetBehaviorOfSpecialIndicatorTable(IterPtr->mIdx));
#else
  lSpecialIndicatorBehavior = DEM_INDICATOR_OFF;
#endif
  return lSpecialIndicatorBehavior;
}

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventJ1939Dtc
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Cfg_EventJ1939Dtc(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
  return Dem_Cfg_GetJ1939DtcOfDtcJ1939Table(Dem_Cfg_GetDtcJ1939TableIdxOfEventTable(EventId));
# else
  return Dem_Cfg_GetJ1939DtcOfDtcTable(Dem_Cfg_GetDtcTableIdxOfEventTable(EventId));                                             /* PRQA S 2843 */ /* MD_DEM_Dir4.1_ReadOperation */
# endif
}
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventJ1939ExpFFExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventJ1939ExpFFExists(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON)
  return (Dem_Cfg_GetRecordSizeOfGeneralJ1939Table(Dem_Cfg_GetGeneralJ1939TableExpFrFrmIdxOfEventTable(EventId)) > 0u);
# else
  return FALSE;
# endif
}
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventJ1939FFExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventJ1939FFExists(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON)
  return (Dem_Cfg_GetRecordSizeOfGeneralJ1939Table(Dem_Cfg_GetGeneralJ1939TableFrzFrmIdxOfEventTable(EventId)) > 0u);
# else
  return FALSE;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventJ1939NodeIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventJ1939NodeIterExists(
  CONSTP2CONST(Dem_Cfg_EventJ1939NodeIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventJ1939NodeIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_EventJ1939NodeIterGet(
  CONSTP2CONST(Dem_Cfg_EventJ1939NodeIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetJ1939NodeIdInd(IterPtr->mIdx);
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventJ1939NodeIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_EventJ1939NodeIterInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(Dem_Cfg_EventJ1939NodeIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                      /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  IterPtr->mIdx = Dem_Cfg_GetJ1939NodeIdIndStartIdxOfDtcTable(Dem_Cfg_GetDtcTableIdxOfEventTable(EventId));                      /* PRQA S 2843 */ /* MD_DEM_Dir4.1_ReadOperation */ /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetJ1939NodeIdIndEndIdxOfDtcTable(Dem_Cfg_GetDtcTableIdxOfEventTable(EventId));                     /* PRQA S 2843 */ /* MD_DEM_Dir4.1_ReadOperation */ /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventJ1939NodeIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_EventJ1939NodeIterNext(
  CONSTP2VAR(Dem_Cfg_EventJ1939NodeIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                      /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

/* ****************************************************************************
 % Dem_Cfg_EventJumpDownValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(sint16, DEM_CODE)
Dem_Cfg_EventJumpDownValue(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  sint16 lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_DEBOUNCE_COUNTER == STD_ON)
  lReturnValue = (sint16)(Dem_Cfg_GetJumpDownValueOfDebounceTable(Dem_Cfg_GetDebounceTableIdxOfEventTable(EventId)));
#else
  lReturnValue = 0;
#endif

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_EventJumpUpValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(sint16, DEM_CODE)
Dem_Cfg_EventJumpUpValue(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  sint16 lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_DEBOUNCE_COUNTER == STD_ON)
  lReturnValue = (sint16)(Dem_Cfg_GetJumpUpValueOfDebounceTable(Dem_Cfg_GetDebounceTableIdxOfEventTable(EventId)));
#else
  lReturnValue = 0;
#endif

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_EventLatchTestFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventLatchTestFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (boolean)(Dem_Cfg_IsEventLatchTFOfEventTable(EventId));
}

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventMilGroupIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_EventMilGroupIndex(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  uint16 lReturn;
  if(Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    lReturn = Dem_Cfg_GetMilGroupIdOfEventTable(EventId);
  }
  else
  {
    lReturn = DEM_CFG_MIL_GROUP_INVALID;
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return lReturn;
}
#endif

/* ****************************************************************************
 % Dem_Cfg_EventObdDidIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventObdDidIterExists(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Cfg_EventObdDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                       /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
#else
  return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventObdDidIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_DidIndexType, DEM_CODE)
Dem_Cfg_EventObdDidIterGet(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Cfg_EventObdDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                       /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  return Dem_Cfg_GetDataCollectionTableFfm2CollInd(IterPtr->mIdx);
#else
  return 0u;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventObdDidIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_EventObdDidIterInit(                                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(Dem_Cfg_EventObdDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                         /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  IterPtr->mIdx = Dem_Cfg_GetDataCollectionTableFfm2CollIndStartIdxOfFreezeFrameTable(Dem_Cfg_GetFreezeFrameTableWwhFFIdxOfEventTable(EventId));   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetDataCollectionTableFfm2CollIndEndIdxOfFreezeFrameTable(Dem_Cfg_GetFreezeFrameTableWwhFFIdxOfEventTable(EventId));  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#else
  IterPtr->mIdx = 0u;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = 0u;                                                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventObdDidIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_EventObdDidIterNext(                                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Cfg_EventObdDidIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                         /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventObdDtc
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_EventObdDtc(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3206, 3112 */ /* MD_DEM_3206, MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
# if (DEM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
  return Dem_Cfg_GetObdDtcOfDtcNumberTable(Dem_Cfg_GetDtcNumberTableIdxOfEventTable(EventId));
# else
  return Dem_Cfg_GetObdDtcOfDtcTable(Dem_Cfg_GetDtcTableIdxOfEventTable(EventId));
# endif
#else
  return DEM_CFG_DTC_OBD_INVALID;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventOperationCycle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_EventOperationCycle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint8)(Dem_Cfg_GetOperationCycleIdOfEventTable(EventId));
}

/* ****************************************************************************
 % Dem_Cfg_EventPassedTarget
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(sint16, DEM_CODE)
Dem_Cfg_EventPassedTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  sint16 lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_DEBOUNCE_COUNTER == STD_ON)
  lReturnValue = (sint16)(Dem_Cfg_GetPassedThresholdOfDebounceTable(Dem_Cfg_GetDebounceTableIdxOfEventTable(EventId)));
#else
  lReturnValue = 1;
#endif

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_EventPreconfirmedTarget
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_EventPreconfirmedTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_NEED_EVENT_PRECONFIRMED == STD_ON)
  return (uint16)(Dem_Cfg_GetPreconfirmedThresholdOfDebounceTable(Dem_Cfg_GetDebounceTableIdxOfEventTable(EventId)));
#else
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
  return 0;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventPrefailedStep
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(sint16, DEM_CODE)
Dem_Cfg_EventPrefailedStep(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  sint16 lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_DEBOUNCE_COUNTER == STD_ON)
  lReturnValue = (sint16)(Dem_Cfg_GetIncrementStepSizeOfDebounceTable(Dem_Cfg_GetDebounceTableIdxOfEventTable(EventId)));
#else
  lReturnValue = 0;
#endif

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_EventPrepassedStep
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(sint16, DEM_CODE)
Dem_Cfg_EventPrepassedStep(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  sint16 lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_DEBOUNCE_COUNTER == STD_ON)
    lReturnValue = (sint16)(Dem_Cfg_GetDecrementStepSizeOfDebounceTable(Dem_Cfg_GetDebounceTableIdxOfEventTable(EventId)));
#else
    lReturnValue = 0;
#endif

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_EventPrestorageIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_EventPrestorageIndex(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  uint16 lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
  lReturnValue = Dem_Cfg_GetFFPrestorageOfEventTable(EventId);
#else
  lReturnValue = DEM_PRESTORE_NOT_CONFIGURED_FOR_EVENT;
#endif

  return lReturnValue;
}

#if ( (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON) \
   || ( ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_PRIORITY == STD_ON)) )
/* ****************************************************************************
 % Dem_Cfg_EventPriority
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_EventPriority(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint8)(Dem_Cfg_GetEventPriorityOfEventTable(EventId));
}
#endif

/* ****************************************************************************
 % Dem_Cfg_EventSatelliteEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Cfg_EventSatelliteEventId(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetSatelliteEventIdxOfEventTable(EventId);
}

/* ****************************************************************************
 % Dem_Cfg_EventSatelliteId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Satellite_IdType, DEM_CODE)
Dem_Cfg_EventSatelliteId(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetSatelliteInfoIdxOfEventTable(EventId);
}

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventSPNIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventSPNIterExists(
  CONSTP2CONST(Dem_Cfg_EventSPNIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventSPNIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_DidIndexType, DEM_CODE)
Dem_Cfg_EventSPNIterGet(
  CONSTP2CONST(Dem_Cfg_EventSPNIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetDataCollectionTableEvt2J1939CollInd(IterPtr->mIdx);
}
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventSPNIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_EventSPNIterInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(Dem_Cfg_EventSPNIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                            /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  IterPtr->mIdx = Dem_Cfg_GetDataCollectionTableEvt2J1939CollIndStartIdxOfEventTable(EventId);                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetDataCollectionTableEvt2J1939CollIndEndIdxOfEventTable(EventId);                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventSPNIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_EventSPNIterNext(
  CONSTP2VAR(Dem_Cfg_EventSPNIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                            /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ( (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) \
     || (DEM_CFG_SUPPORT_SRECS == STD_ON) ) )
/* ****************************************************************************
 % Dem_Cfg_EventSRecUdsSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_EventSRecUdsSize(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint16)(Dem_Cfg_GetRecordSizeUdsOfFreezeFrameTable(Dem_Cfg_GetFreezeFrameTableStdFFIdxOfEventTable(EventId)));
}
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_GlobalSRecUdsSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalSRecUdsSize(
  void
  )
{
  return (uint16)(Dem_Cfg_GetRecordSizeUdsOfFreezeFrameTable(Dem_Cfg_GetFreezeFrameTableIdxOfGlobalSnapshotRecord(0)));
}
#endif

/* ****************************************************************************
 % Dem_Cfg_EventSeverity
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTCSeverityType, DEM_CODE)
Dem_Cfg_EventSeverity(                                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (Dem_DTCSeverityType)(Dem_Cfg_GetDtcSeverityOfDtcTable(Dem_Cfg_GetDtcTableIdxOfEventTable(EventId)));
}

/* ****************************************************************************
 % Dem_Cfg_EventSignificance
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_EventSignificance(                                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint8)(Dem_Cfg_GetEventSignificanceOfEventTable(EventId));
}

/* ****************************************************************************
 % Dem_Cfg_EventStorageTarget
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_EventStorageTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  uint16 lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (Dem_Cfg_HasStorageThresholdOfDebounceTable() == TRUE)
  lReturnValue = (uint16)(Dem_Cfg_GetStorageThresholdOfDebounceTable(Dem_Cfg_GetDebounceTableIdxOfEventTable(EventId)));
#else
  lReturnValue = 0u;
#endif

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_EventSupportAging
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventSupportAging(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (boolean)(Dem_Cfg_IsAgingAllowedOfEventTable(EventId));
}

#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventSupportAgedCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventSupportAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (boolean)(Dem_Cfg_GetAgedCounterIndexOfEventTable(EventId) != DEM_CFG_AGEDCOUNTER_INDEX_INVALID);
}
#endif

/* ****************************************************************************
 % Dem_Cfg_IsPermanentSupportedInVariant
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_IsPermanentSupportedInVariant(
  void
)
{
  return (boolean)(Dem_Cfg_IsUsePermanentInVariant() == TRUE);
}

/* ****************************************************************************
 % Dem_Cfg_IsObdIISupportedInVariant
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_IsObdIISupportedInVariant(
  void
)
{
  return (boolean)(Dem_Cfg_IsUseOBDIIInVariant() == TRUE);                                                                       /* PRQA S 2812 */ /* MD_DEM_Dir4.1_NullPointerDereference */
}

/* ****************************************************************************
 % Dem_Cfg_IsWwhObdSupportedInVariant
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_IsWwhObdSupportedInVariant(
  void
)
{
  return (boolean)(Dem_Cfg_IsUseWWHOBDInVariant() == TRUE);                                                                      /* PRQA S 2812 */ /* MD_DEM_Dir4.1_NullPointerDereference */
}

/* ****************************************************************************
 % Dem_Cfg_IsObdSupportedInVariant
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_IsObdSupportedInVariant(
  void
)
{
  return (Dem_Cfg_IsObdIISupportedInVariant() || Dem_Cfg_IsWwhObdSupportedInVariant());
}

/* ****************************************************************************
 % Dem_Cfg_IsObdIIFreezeFrameInService19Enabled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_IsObdIIFreezeFrameInService19Enabled(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
)
{
  return (boolean)(DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON);
}

/* ****************************************************************************
 % Dem_Cfg_EventSupportImmediateNv
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventSupportImmediateNv(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_NVM_IMMEDIATE == STD_ON)
    return (boolean)(Dem_Cfg_IsImmediateNvStorageOfDtcTable(Dem_Cfg_GetDtcTableIdxOfEventTable(EventId)));
#else
    return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventSupportJumpDown
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventSupportJumpDown(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  boolean lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_DEBOUNCE_COUNTER == STD_ON)
  lReturnValue = (boolean)(Dem_Cfg_IsJumpDownOfDebounceTable(Dem_Cfg_GetDebounceTableIdxOfEventTable(EventId)));
#else
  lReturnValue = FALSE;
#endif

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_EventSupportJumpUp
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventSupportJumpUp(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  boolean lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_DEBOUNCE_COUNTER == STD_ON)
    lReturnValue = (boolean)(Dem_Cfg_IsJumpUpOfDebounceTable(Dem_Cfg_GetDebounceTableIdxOfEventTable(EventId)));
#else
    lReturnValue = FALSE;
#endif

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_EventTripTarget
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_EventTripTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint8)(Dem_Cfg_GetEventFailureCycleCounterThresholdOfEventTable(EventId));
}

/* ****************************************************************************
 % Dem_Cfg_EventUdsDtc
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Cfg_EventUdsDtc(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
  return Dem_Cfg_GetUdsDtcOfDtcNumberTable(Dem_Cfg_GetDtcNumberTableIdxOfEventTable(EventId));
#else
  return Dem_Cfg_GetUdsDtcOfDtcTable(Dem_Cfg_GetDtcTableIdxOfEventTable(EventId));                                               /* PRQA S 2843 */ /* MD_DEM_Dir4.1_ReadOperation */
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventWwhObdFFUdsSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_EventWwhObdFFUdsSize(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  return Dem_Cfg_GetRecordSizeUdsOfFreezeFrameTable(Dem_Cfg_GetFreezeFrameTableWwhFFIdxOfEventTable(EventId));
#else
  return 0u;
#endif
}

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalAwlIndicator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalAwlIndicator(
  void
  )
{
# if (DEM_CFG_SUPPORT_AWL == STD_ON)
  return DEM_CFG_GLOBAL_AWL_INDICATOR;
# else
  return DEM_CFG_INDICATOR_INVALID;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalCbkControlDtcSetting
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_ControlDtcSettingChangedFPtrType, DEM_CODE)
Dem_Cfg_GlobalCbkControlDtcSetting(
  void
  )
{
  return (Dem_ControlDtcSettingChangedFPtrType)DEM_CFG_GLOBALCBKCONTROLDTCSETTING_FUNC;                                          /* PRQA S 0428 */ /* MD_DEM_16.9_fp */
}
#endif

/* ****************************************************************************
 % Dem_Cfg_GlobalCbkData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_GlobalDataChangedFPtrType, DEM_CODE)
Dem_Cfg_GlobalCbkData(
  void
  )
{
  return (Dem_GlobalDataChangedFPtrType)DEM_CFG_GLOBALCBKDATA_FUNC;                                                              /* PRQA S 0428 */ /* MD_DEM_16.9_fp */
}

/* ****************************************************************************
 % Dem_Cfg_GlobalCbkDtcIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_GlobalCbkDtcIterExists(
  CONSTP2CONST(Dem_Cfg_GlobalCbkDtcIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_NOTIFY_DTC_STATUS == STD_ON) && (DEM_CFG_HAVEITER_GLOBALCBKDTC == STD_ON)
  return (boolean)(*IterPtr < Dem_Cfg_GetSizeOfCallbackDtcStatusChanged());
#else
  return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_GlobalCbkDtcIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DtcStatusChangedFPtrType, DEM_CODE)
Dem_Cfg_GlobalCbkDtcIterGet(
  CONSTP2CONST(Dem_Cfg_GlobalCbkDtcIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_DtcStatusChangedFPtrType lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_NOTIFY_DTC_STATUS == STD_ON) && (DEM_CFG_HAVEITER_GLOBALCBKDTC == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (*IterPtr >= Dem_Cfg_GetSizeOfCallbackDtcStatusChanged())
  {
    lReturnValue = (Dem_DtcStatusChangedFPtrType)NULL_PTR;
    Dem_Error_RunTimeCheckFailed(DEM_CFG_DEFINITIONS_FILENAME, __LINE__);                                                        /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    lReturnValue = Dem_Cfg_GetCallbackDtcStatusChanged(*IterPtr);
  }
#else
  lReturnValue = (Dem_DtcStatusChangedFPtrType)NULL_PTR;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_GlobalCbkDtcIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_GlobalCbkDtcIterInit(
  CONSTP2VAR(Dem_Cfg_GlobalCbkDtcIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                        /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  *IterPtr = 0u;                                                                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Cfg_GlobalCbkDtcIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_GlobalCbkDtcIterNext(
  CONSTP2VAR(Dem_Cfg_GlobalCbkDtcIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                        /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_NOTIFY_DTC_STATUS == STD_ON) && (DEM_CFG_HAVEITER_GLOBALCBKDTC == STD_ON)
  *IterPtr += 1u;                                                                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# endif
}

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalCbkJ1939DtcIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_GlobalCbkJ1939DtcIterExists(
  CONSTP2CONST(Dem_Cfg_GlobalCbkJ1939DtcIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                 /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalCbkJ1939DtcIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DtcStatusChangedFPtrType, DEM_CODE)
Dem_Cfg_GlobalCbkJ1939DtcIterGet(
  CONSTP2CONST(Dem_Cfg_GlobalCbkJ1939DtcIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                 /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_DtcStatusChangedFPtrType lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_NOTIFY_J1939DTC_STATUS == STD_ON) && (DEM_CFG_HAVEITER_GLOBALCBKJ1939DTC == STD_ON)
#  if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (IterPtr->mIdx >= Dem_Cfg_GetSizeOfCallbackJ1939DtcStatusChanged())
  {
    lReturnValue = (Dem_DtcStatusChangedFPtrType)NULL_PTR;
    Dem_Error_RunTimeCheckFailed(DEM_CFG_DEFINITIONS_FILENAME, __LINE__);                                                        /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#  endif
  {
    lReturnValue = Dem_Cfg_GetCallbackJ1939DtcStatusChanged(IterPtr->mIdx);
  }
# else
  lReturnValue = (Dem_DtcStatusChangedFPtrType)NULL_PTR;
# endif
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalCbkJ1939DtcIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_GlobalCbkJ1939DtcIterInit(
  CONSTP2VAR(Dem_Cfg_GlobalCbkJ1939DtcIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                   /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  IterPtr->mIdx = 0u;                                                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# if (DEM_CFG_NOTIFY_J1939DTC_STATUS == STD_ON) && (DEM_CFG_HAVEITER_GLOBALCBKJ1939DTC == STD_ON)
  IterPtr->mEndIdx = Dem_Cfg_GetSizeOfCallbackJ1939DtcStatusChanged();                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# else
  IterPtr->mEndIdx = 0u;                                                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# endif
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalCbkJ1939DtcIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_GlobalCbkJ1939DtcIterNext(
  CONSTP2VAR(Dem_Cfg_GlobalCbkJ1939DtcIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                                   /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

/* ****************************************************************************
 % Dem_Cfg_GlobalCbkStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_GlobalStatusChangedFPtrType, DEM_CODE)
Dem_Cfg_GlobalCbkStatus(
  void
  )
{
  return (Dem_GlobalStatusChangedFPtrType)DEM_CFG_GLOBALCBKSTATUS_FUNC;                                                          /* PRQA S 0428 */ /* MD_DEM_16.9_fp */
}

#if (DEM_CFG_SUPPORT_CLEAR_DTC_RUNTIME_LIMIT == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalClearDtcRuntimeLimit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalClearDtcRuntimeLimit(
  void
  )
{
  return DEM_CFG_GLOBAL_CLEAR_DTC_RUNTIME_LIMIT;
}
#endif

/* ****************************************************************************
 % Dem_Cfg_GlobalJ1939ReadDtcRuntimeLimit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalJ1939ReadDtcRuntimeLimit(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return DEM_CFG_GLOBAL_J1939_READING_DTC_RUNTIME_LIMIT;
}

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON || DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalCombinedGroupCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_CombinedGroupIndexType, DEM_CODE)
Dem_Cfg_GlobalCombinedGroupCount(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return DEM_CFG_GLOBAL_COMBINED_GROUP_COUNT;
}
#endif

/* ****************************************************************************
 % Dem_Cfg_GlobalConfigurationId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalConfigurationId(
  void
  )
{
  return (uint16)(Dem_Cfg_GetConfigurationId());
}

/* ****************************************************************************
 % Dem_Cfg_GlobalCycleCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalCycleCount(
  void
  )
{
  return DEM_CFG_GLOBAL_CYCLE_COUNT;
}

#if ( (DEM_DEV_RUNTIME_CHECKS == STD_ON) \
   && ( (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) \
     || (DEM_CFG_SUPPORT_SRECS == STD_ON) \
     || (DEM_CFG_SUPPORT_OBDII == STD_ON) \
     || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) \
     || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
     || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) \
     || (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) ) )
/* ****************************************************************************
 * Dem_Cfg_GlobalDataElementCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalDataElementCount(
  void
  )
{
  return Dem_Cfg_GetSizeOfDataElementTable();
}
#endif

/* ****************************************************************************
 % Dem_Cfg_GlobalDebounceStorageEventCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalDebounceStorageEventCount(
  void
  )
{
#if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
  return DEM_CFG_GLOBAL_DEBOUNCE_STORAGE_EVENT_COUNT;
#else
  return 0u;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_GlobalObdDrivingCycleId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalObdDrivingCycleId(
  void
  )
{
  uint8 lResult;
#if(DEM_FEATURE_NEED_OBD == STD_ON)
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    lResult = DEM_CFG_GLOBAL_OBD_DRIVING_CYCLE_ID;
  }
  else
#endif
  {
    lResult = DEM_CFG_GLOBAL_CYCLE_COUNT;
  }
  return lResult;
}

/* ****************************************************************************
 % Dem_Cfg_GlobalWarmupCycleId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalWarmupCycleId(
  void
  )
{
  uint8 lResult;
#if (DEM_CFG_DATA_WUC_SINCE_LAST_FAILED == STD_ON)
  lResult = DEM_CFG_GLOBAL_WARMUP_CYCLE_ID;
#else
# if(DEM_FEATURE_NEED_OBD == STD_ON) 
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    lResult = DEM_CFG_GLOBAL_WARMUP_CYCLE_ID;
  }
  else
# endif
  {
    lResult = DEM_CFG_GLOBAL_CYCLE_COUNT;
  }
#endif
  return lResult;
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalDtcFormat
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalDtcFormat(
  void
  )
{
  return DEM_CFG_GLOBAL_DTC_FORMAT;
}
#endif

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) && (DEM_DEV_RUNTIME_CHECKS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalERecMaxCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalERecMaxCount(
  void
  )
{
  return DEM_CFG_MAX_NUM_EXT_RECORDS;
}
#endif

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalERecMaxRawSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalERecMaxRawSize(
  void
  )
{
  return DEM_CFG_MAX_SIZE_EXT_RECORD;
}
#endif

#if ( (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON) \
   || (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_GlobalPid01SupportedMask
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Cfg_GlobalPid01SupportedMask(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return Dem_Cfg_GetGlobalPid01SupportedMask();
}
#endif

/* ****************************************************************************
 % Dem_Cfg_GlobalEventCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalEventCount(
  void
  )
{
  return Dem_Cfg_GetSizeOfEventTable();
}

/* ****************************************************************************
 % Dem_Cfg_EventCycleStatusCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_EventCycleStatusCount(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_DEV_RUNTIME_CHECKS == STD_ON)
# if (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
  return Dem_Cfg_GetSizeOfEventTable();
# else
  return Dem_Cfg_GetSizeOfEventCycleStatus();
# endif
#else
  return 0u;
#endif
}

/* ****************************************************************************
 * Dem_Cfg_GlobalSatelliteCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalSatelliteCount(
  void
  )
{
  return Dem_Cfg_GetSizeOfSatelliteInfo();
}

/* ****************************************************************************
 % Dem_Cfg_GlobalIndicatorCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalIndicatorCount(
  void
  )
{
  return DEM_CFG_GLOBAL_INDICATOR_COUNT;
}

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalJ1939ExpFFRawSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalJ1939ExpFFRawSize(
  void
  )
{
  return (uint16)DEM_CFG_MAX_J1939_EXP_FF_SIZE;
}
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalJ1939FFRawSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalJ1939FFRawSize(
  void
  )
{
  return (uint16)DEM_CFG_MAX_J1939_FF_SIZE;
}
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalJ1939FFTotalRawSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalJ1939FFTotalRawSize(
  void
  )
{
  return (uint16)(Dem_Cfg_GlobalJ1939FFRawSize() + Dem_Cfg_GlobalJ1939ExpFFRawSize());
}
#endif

/* ****************************************************************************
 % Dem_Cfg_GlobalJ1939NodeCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalJ1939NodeCount(
  void
  )
{
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
  return DEM_G_MAX_NUMBER_J1939_NODES;
# else
  return 1;
# endif
}

#if ( (DEM_CFG_SUPPORT_ERECS == STD_ON) \
   || (DEM_CFG_SUPPORT_SRECS == STD_ON) \
   || (DEM_CFG_SUPPORT_OBDII == STD_ON) \
   || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) \
   || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) )
/* ****************************************************************************
 % Dem_Cfg_GlobalMaxDataValueSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalMaxDataValueSize(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return DEM_CFG_SIZEOF_MAX_DATA_VALUE_TYPE;
}
#endif

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalMilGroupCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalMilGroupCount(
  void
  )
{
  return DEM_CFG_GLOBAL_MIL_GROUP_COUNT;
}
#endif

/* ****************************************************************************
 % Dem_Cfg_ConfirmedChronologyMaxCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_ConfirmedChronologyMaxCount(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
  return DEM_CFG_MAX_NUMBER_PERMANENT_CHRONOLOGY;
#else
  return 0u;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_GlobalMilIndicator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalMilIndicator(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  uint8 lResult;

#if (DEM_CFG_SUPPORT_MIL == STD_ON)
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    lResult = DEM_CFG_GLOBAL_MIL_INDICATOR;
  }
  else
#endif
  {
    lResult = DEM_CFG_INDICATOR_INVALID;
  }
  return lResult;
}

/* ****************************************************************************
 % Dem_Cfg_GlobalNvBlockCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Cfg_GlobalNvBlockCount(
  void
  )
{
  return DEM_CFG_GLOBAL_NV_BLOCK_COUNT;
}

#if (DEM_CFG_SUPPORT_NVM_WRITELIMIT == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalNvStorageLimit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalNvStorageLimit(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return DEM_CFG_GLOBAL_NV_STORAGE_LIMIT;
}
#endif

/* ****************************************************************************
 % Dem_Cfg_GlobalObdIIFFCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalObdIIFFCount(
  void
  )
{
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  return DEM_CFG_GLOBAL_FREEZEFRAME_SIZE;
#else
  return 0u;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_GlobalObdIIFFUdsSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalObdIIFFUdsSize(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON)
  return DEM_CFG_GLOBAL_OBD_IIFFUDS_SIZE;
#else
  return 0u;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_GlobalObdRequirements
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalObdRequirements(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  uint8 lReturn;
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    lReturn =  Dem_Cfg_GetGlobalObdRequirements();
  }
  else
  {
    lReturn = 5; /* No OBD */
  }
  return lReturn;
}

/* ****************************************************************************
 % Dem_Cfg_GlobalPermanentDtcRelActivationDist
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Cfg_GlobalPermanentDtcRelActivationDist(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
  return DEM_CFG_GLOBAL_PERMANENT_DTC_REL_ACTIVATION_DIST;
#else
  return 0u;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_GlobalPermanentMaxCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalPermanentMaxCount(
  void
  )
{
#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
  return DEM_CFG_GLOBAL_PERMANENT_SIZE;
#else
  return 0u;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_GlobalPidIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_GlobalPidIterExists(                                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Cfg_GlobalPidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
#if (DEM_CFG_SUPPORT_FREEZEFRAME == STD_ON)
  return (boolean)(*IterPtr < Dem_Cfg_GetDataCollectionTablePid2CollIndEndIdxOfPidTable(0));
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)
  return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_GlobalPidIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_DidIndexType, DEM_CODE)
Dem_Cfg_GlobalPidIterGet(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Cfg_GlobalPidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_FREEZEFRAME == STD_ON)
  return Dem_Cfg_GetDataCollectionTablePid2CollInd(*IterPtr);
#else
  return 0u;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_GlobalPidIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_GlobalPidIterInit(                                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Cfg_GlobalPidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
#if (DEM_CFG_SUPPORT_FREEZEFRAME == STD_ON)
  *IterPtr = Dem_Cfg_GetDataCollectionTablePid2CollIndStartIdxOfPidTable(0);                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#else
  *IterPtr = 0u;                                                                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#endif
}

/* ****************************************************************************
 % Dem_Cfg_GlobalPidIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_GlobalPidIterNext(                                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Cfg_GlobalPidIterType, AUTOMATIC, AUTOMATIC) IterPtr                                                            /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
#if (DEM_CFG_SUPPORT_FREEZEFRAME == STD_ON)
  *IterPtr += 1u;                                                                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalPlIndicator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalPlIndicator(
  void
  )
{
# if (DEM_CFG_SUPPORT_PL == STD_ON)
  return DEM_CFG_GLOBAL_PL_INDICATOR;
# else
  return DEM_CFG_INDICATOR_INVALID;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalPrestorageSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalPrestorageSize(
  void
  )
{
  return DEM_CFG_GLOBAL_PRESTORED_FF_SIZE;
}
#endif

/* ****************************************************************************
 % Dem_Cfg_GlobalPrimaryFirst
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalPrimaryFirst(
  void
  )
{
  return DEM_CFG_GLOBAL_PRIMARY_FIRST;
}

/* ****************************************************************************
 % Dem_Cfg_GlobalPrimaryLast
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalPrimaryLast(
  void
  )
{
  return DEM_CFG_GLOBAL_PRIMARY_LAST;
}

/* ****************************************************************************
 % Dem_Cfg_GlobalPrimaryMaxCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalPrimaryMaxCount(
  void
  )
{
  return DEM_CFG_GLOBAL_PRIMARY_SIZE;
}

#if (DEM_CFG_SUPPORT_RESTART_CYCLE == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalRestartCycleId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalRestartCycleId(
  void
  )
{
  return DEM_CFG_GLOBAL_RESTART_CYCLE_ID;
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalRslIndicator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalRslIndicator(
  void
  )
{
# if (DEM_CFG_SUPPORT_RSL == STD_ON)
  return DEM_CFG_GLOBAL_RSL_INDICATOR;
# else
  return DEM_CFG_INDICATOR_INVALID;
# endif
}
#endif

/* ****************************************************************************
 % Dem_Cfg_GlobalSecondaryFirst
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalSecondaryFirst(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  Dem_EventIdType lReturnValue;
#if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
  lReturnValue = DEM_CFG_GLOBAL_SECONDARY_FIRST;
#else
  lReturnValue = DEM_EVENT_INVALID;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_GlobalSecondaryLast
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalSecondaryLast(                                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  Dem_EventIdType lReturnValue;
#if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
  lReturnValue = DEM_CFG_GLOBAL_SECONDARY_LAST;
#else
  lReturnValue = DEM_EVENT_INVALID;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_GlobalSecondaryMaxCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalSecondaryMaxCount(
  void
  )
{
  return DEM_CFG_GLOBAL_SECONDARY_SIZE;
}

/* ****************************************************************************
 % Dem_Cfg_GlobalSeverityMask
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTCSeverityType, DEM_CODE)
Dem_Cfg_GlobalSeverityMask(
  void
  )
{
  return (Dem_DTCSeverityType)Dem_Cfg_GetGlobalSeverityMask();
}


#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalSRecMaxCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalSRecMaxCount(
  void
  )
{
  return DEM_CFG_MAX_NUM_SNAPSHOTS;
}
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_EventSRecMaxRawSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_EventSRecMaxRawSize(
  void
  )
{
  return DEM_CFG_MAX_SIZE_SNAPSHOT;
}
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalSRecMaxRawSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalSRecMaxRawSize(
  void
  )
{
  return DEM_CFG_MAX_SIZE_GLOBAL_SNAPSHOT;
}
#endif


/* ****************************************************************************
 % Dem_Cfg_GlobalObdFreezeFrameMaxSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalObdFreezeFrameMaxSize(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  return DEM_CFG_MAX_SIZE_OBDFREEZEFRAME;
#else
  return 0u;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_GlobalWwhobdFreezeFrameDataSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalWwhobdFreezeFrameDataSize(                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  return sizeof(Dem_Cfg_PrimaryEntry_0.ObdFreezeFrameData)/sizeof(Dem_Cfg_PrimaryEntry_0.ObdFreezeFrameData[0]);
#else
  return 0u;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_GlobalPrestoredWwhobdFreezeFrameDataSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalPrestoredWwhobdFreezeFrameDataSize(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
  return sizeof(Dem_Cfg_GetPrestorage()[0].ObdFreezeFrameData)/sizeof(Dem_Cfg_GetPrestorage()[0].ObdFreezeFrameData[0]);
#else
  return 0u;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_GlobalStatusMask
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalStatusMask(
  void
  )
{
  return DEM_CFG_GLOBAL_STATUS_MASK;
}

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalTimeSeriesFastBufferSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalTimeSeriesFastBufferSize(
  void
  )
{
  return DEM_CFG_TIMESERIES_FAST_BUFFER_SIZE;
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalTimeSeriesNormalBufferSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalTimeSeriesNormalBufferSize(
  void
  )
{
  return DEM_CFG_TIMESERIES_NORMAL_BUFFER_SIZE;
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalTimeSeriesMaxCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalTimeSeriesMaxCount(
  void
  )
{
  return DEM_CFG_GLOBAL_TIMESERIES_SNAPSHOTS_SIZE;
}
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE_NV == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalEventAvailableDataSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_GlobalEventAvailableDataSize(
  void
  )
{
  return DEM_CFG_EVENTAVAILABLEDATATYPE_SIZE;
}
#endif

#if (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_IndicatorId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_IndicatorId(
  CONST(Dem_Cfg_NormalIndicatorIndexType, AUTOMATIC)  IndicatorIndex                                                             /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorIndex)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint8)(Dem_Cfg_GetIdOfNormalIndicatorTable(IndicatorIndex));
}
#endif

#if (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_IndicatorBehavior
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_IndicatorBehavior(
  CONST(Dem_Cfg_NormalIndicatorIndexType, AUTOMATIC)  IndicatorIndex                                                             /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorIndex)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint8)(Dem_Cfg_GetBehaviorOfNormalIndicatorTable(IndicatorIndex));
}
#endif

#if (DEM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_InitPtrCompatibilityVersion
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Cfg_InitPtrCompatibilityVersion(
  CONSTP2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr                                                              /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ConfigPtr)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint32)(Dem_Cfg_GetCompatibilityVersion(ConfigPtr));
}
#endif

#if (DEM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_InitPtrFinalMagicNumber
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_InitPtrFinalMagicNumber(
  CONSTP2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr                                                              /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ConfigPtr)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint16)(Dem_Cfg_GetFinalMagicNumber(ConfigPtr));
}
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_J1939NodeIndicatorReadiness
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_J1939NodeIndicatorReadiness(
  CONST(uint8, AUTOMATIC)  NodeIndex                                                                                             /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NodeIndex)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetJ1939NodeIndicator(NodeIndex);
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_J1939NmNodeId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Cfg_J1939NmNodeId(
  CONST(uint8, AUTOMATIC)  NodeIndex
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NodeIndex)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetJ1939NodeId(NodeIndex);
}
#endif

#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_MemoryAdminIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Cfg_MemoryAdminIndex(
  void
  )
{
  return DEM_CFG_MEMORY_ADMIN_INDEX;
}
#endif

#if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_MemoryDebounceIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Cfg_MemoryDebounceIndex(
  void
  )
{
  return DEM_CFG_MEMORY_DEBOUNCE_INDEX;
}
#endif

/* ****************************************************************************
 % Dem_Cfg_SizeOfReadOutBufferData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_SizeOfReadOutBufferData(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return DEM_CFG_NUMBER_OF_SUBEVENT_DATA_READOUTBUFFERS;
}

/* ****************************************************************************
 % Dem_Cfg_MemoryDtrIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Cfg_MemoryDtrIndex(                                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_DTR == STD_ON)
  return DEM_CFG_MEMORY_DTR_DATA_INDEX;
#else
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
  return 0u;
#endif
}

#if (DEM_CFG_USE_NVM == STD_ON) && (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_MemoryEventAvailableIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Cfg_MemoryEventAvailableIndex(
  void
  )
{
  return DEM_CFG_MEMORY_EVENT_AVAILABLE_INDEX;
}
#endif

/* ****************************************************************************
 % Dem_Cfg_MemoryFreezeFrameIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Cfg_MemoryFreezeFrameIndex(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
)
{
  Dem_Cfg_MemoryIndexType lReturnValue;
#if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON)
  if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
  {
    lReturnValue = DEM_CFG_MEMORY_FREEZEFRAME_INDEX;
  }
  else
#endif
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
    lReturnValue  = 0u;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_MemoryPermanentIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Cfg_MemoryPermanentIndex(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
)
{
  Dem_Cfg_MemoryIndexType lReturnValue;
#if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
  if (Dem_Cfg_IsPermanentSupportedInVariant() == TRUE)
  {
    lReturnValue = DEM_CFG_MEMORY_PERMANENT_INDEX;
  }
  else
#endif
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
    lReturnValue = 0u;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Cfg_MemoryPrimaryIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Cfg_MemoryPrimaryIndex(
  void
  )
{
  return DEM_CFG_MEMORY_PRIMARY_INDEX;
}

#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_MemoryStatusIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Cfg_MemoryStatusIndex(
  void
  )
{
  return DEM_CFG_MEMORY_STATUS_INDEX;
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_MemoryTimeSeriesStartIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Cfg_MemoryTimeSeriesStartIndex(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return DEM_CFG_MEMORY_TIME_SERIES_INDEX;
}
#endif

#if ( (DEM_CFG_USE_NVM == STD_ON) \
   && (DEM_FEATURE_NEED_AGING_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_Cfg_MemoryAgingDataIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Cfg_MemoryAgingDataIndex(
  void
  )
{
  return DEM_CFG_MEMORY_AGING_INDEX;
}
#endif

#if ( (DEM_CFG_USE_NVM == STD_ON) \
   && (DEM_FEATURE_NEED_CYCLE_COUNTER_DATA == STD_ON) )
/* ****************************************************************************
% Dem_Cfg_MemoryCycleCounterDataIndex
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Cfg_MemoryCycleCounterDataIndex(
  void
)
{
  return DEM_CFG_MEMORY_CYCLE_COUNTER_INDEX;
}
#endif

#if (DEM_FEATURE_NEED_OBD_ODOMETER == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_ObdDistanceInformation
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_DataIndexType, DEM_CODE)
Dem_Cfg_ObdDistanceInformation(
  void
  )
{
  return Dem_Cfg_GetDataElementTableIdxOfGeneralObdInput(DEM_CFG_OBDDISTANCEINFORMATION_INDEX);
}
#endif

#if (DEM_FEATURE_NEED_ENGINE_RUN_TIME == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_ObdEngineRunTime
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_DataIndexType, DEM_CODE)
Dem_Cfg_ObdEngineRunTime(
  void
  )
{
  return Dem_Cfg_GetDataElementTableIdxOfGeneralObdInput(DEM_CFG_OBDENGINERUNTIME_INDEX);
}
#endif


/* ****************************************************************************
 % Dem_Cfg_SpecialIndicatorCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_SpecialIndicatorCount(
void
)
{
#if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
  return DEM_G_NUMBER_SPECIAL_INDICATORS;
#else
  return 0;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventWwhObdFreezeFrameExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_EventWwhObdFreezeFrameExists(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  return (boolean)(Dem_Cfg_GetRecordSizeOfFreezeFrameTable(Dem_Cfg_GetFreezeFrameTableWwhFFIdxOfEventTable(EventId)) != 0u);
#else
  return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_EventObdRelated
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
Dem_Cfg_EventObdRelated(                                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC) EventId                                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  boolean lReturnValue;

  lReturnValue = FALSE;

  if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
  {
    lReturnValue = (boolean)(Dem_Cfg_EventObdDtc(EventId) != DEM_CFG_DTC_OBD_INVALID);
  }

  if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
  {
    /* An event is actually Obd relevant for WWH-OBD if
       - it has WWH-OBD class A, B1, B2, C configured or
       - if it is a Black MIL DTC (WWH-OBD class 'No class' and a WWH-OBD freeze frame configured)
       As these conditions can never be covered fully,
       we assume that each Obd relevant DTC has a WWH-OBD freeze frame class configured (as this is ensured by the validator) */
    lReturnValue = (boolean) (Dem_Cfg_EventWwhObdFreezeFrameExists(EventId) == TRUE);
  }

  return lReturnValue;
}

#if (DEM_CFG_DATA_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_EXTENDED_ENV_DATA == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_OemCbkGetCurrentOdometer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_OemCbkGetCurrentOdometerFptrType, DEM_CODE)
Dem_Cfg_OemCbkGetCurrentOdometer(
  void
  )
{
  return (Dem_OemCbkGetCurrentOdometerFptrType)DEM_CFG_OEMCBKGETCURRENTODOMETER_FUNC;                                            /* PRQA S 0428 */ /* MD_DEM_16.9_fp */
}
#endif

#if (DEM_CFG_DATA_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_EXTENDED_ENV_DATA == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_OemCbkGetExternalTesterStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_OemCbkGetExternalTesterStatusFptrType, DEM_CODE)
Dem_Cfg_OemCbkGetExternalTesterStatus(
  void
  )
{
  return (Dem_OemCbkGetExternalTesterStatusFptrType)DEM_CFG_OEMCBKGETEXTERNALTESTERSTATUS_FUNC;                                  /* PRQA S 0428 */ /* MD_DEM_16.9_fp */
}
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_SRecId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_SRecId(
  CONST(Dem_Cfg_SRecIndexType, AUTOMATIC)  SRecIndex                                                                             /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SRecIndex)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetFFNumberOfFreezeFrameNumTable(SRecIndex);
}
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalSRecId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GlobalSRecId(                                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
 void
 )
{
  return Dem_Cfg_GetRecordNrOfGlobalSnapshotRecord(0);
}
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalSRecTrigger
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_StorageTriggerType, DEM_CODE)
Dem_Cfg_GlobalSRecTrigger(
  void
  )
{
  return Dem_Cfg_GetFFTriggerOfGlobalSnapshotRecord(0);
}
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_GlobalSRecUpdate
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_GlobalSRecUpdate(
  void
  )
{
  return Dem_Cfg_IsFFUpdateOfGlobalSnapshotRecord(0);
}
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_SRecTrigger
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_StorageTriggerType, DEM_CODE)
Dem_Cfg_SRecTrigger(
  CONST(Dem_Cfg_SRecIndexType, AUTOMATIC)  SRecIndex                                                                             /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SRecIndex)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetFFTriggerOfFreezeFrameNumTable(SRecIndex);
}
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_SRecUpdate
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_SRecUpdate(
  CONST(Dem_Cfg_SRecIndexType, AUTOMATIC)  SRecIndex                                                                             /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SRecIndex)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (boolean)Dem_Cfg_IsFFUpdateOfFreezeFrameNumTable(SRecIndex);                                                            /* PRQA S 2841 */ /* MD_DEM_Dir4.1_ReadOperation */
}
#endif

/* ****************************************************************************
 % Dem_Cfg_EventReadinessGroup
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_EventReadinessGroup(                                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC) EventId                                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  uint8 lReturn;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if ( (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON) \
   || (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON) \
   || (DEM_CFG_SUPPORT_OBDII == STD_ON))
  if(Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    lReturn = Dem_Cfg_GetReadinessGroupOfEventTable(EventId);
  }
  else
#endif
  {
    lReturn = DEM_CFG_READINESS_NONE;
  }
  return lReturn;
}

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_TimeSeriesDidFastIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_TimeSeriesDidFastIterExists(
  CONSTP2CONST(Dem_Cfg_TimeSeriesDidFastIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  return (boolean)(*IterPtr < Dem_Cfg_GetSizeOfTimeSeriesFastRateDids());
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_TimeSeriesDidFastIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_DidIndexType, DEM_CODE)
Dem_Cfg_TimeSeriesDidFastIterGet(
  CONSTP2CONST(Dem_Cfg_TimeSeriesDidFastIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetDataCollectionTableTsF2CollIdxOfTimeSeriesFastRateDids(*IterPtr);
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_TimeSeriesDidFastIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_TimeSeriesDidFastIterInit(
  CONSTP2VAR(Dem_Cfg_TimeSeriesDidFastIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  *IterPtr = 0u;                                                                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_TimeSeriesDidFastIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_TimeSeriesDidFastIterNext(
  CONSTP2VAR(Dem_Cfg_TimeSeriesDidFastIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  *IterPtr += 1u;                                                                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_TimeSeriesDidNormalIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_TimeSeriesDidNormalIterExists(
  CONSTP2CONST(Dem_Cfg_TimeSeriesDidNormalIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  return (boolean)(*IterPtr < Dem_Cfg_GetSizeOfTimeSeriesNormalRateDids());
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_TimeSeriesDidNormalIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_DidIndexType, DEM_CODE)
Dem_Cfg_TimeSeriesDidNormalIterGet(
  CONSTP2CONST(Dem_Cfg_TimeSeriesDidNormalIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetDataCollectionTableNormalDataCollIdxOfTimeSeriesNormalRateDids(*IterPtr);
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_TimeSeriesDidNormalIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_TimeSeriesDidNormalIterInit(
  CONSTP2VAR(Dem_Cfg_TimeSeriesDidNormalIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  *IterPtr = 0u;                                                                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_TimeSeriesDidNormalIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_TimeSeriesDidNormalIterNext(
  CONSTP2VAR(Dem_Cfg_TimeSeriesDidNormalIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  *IterPtr += 1u;                                                                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif


/* ****************************************************************************
 % Dem_Cfg_TimeSeriesFastRate
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Cfg_TimeSeriesFastRate(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
  return (uint32)DEM_CFG_TIME_SERIES_FAST_RATE;
#else
  return (uint32)0x00U;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_TimeSeriesNormalRate
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Cfg_TimeSeriesNormalRate(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  return (uint32)DEM_CFG_TIME_SERIES_NORMAL_RATE;
#else
  return (uint32)0x00U;
#endif
}

#if (DEM_CFG_SUPPORT_TIME_SERIES_POWERTRAIN == STD_ON)
/* ****************************************************************************
% Dem_Cfg_DemTaskTime
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(float32, DEM_CODE)
Dem_Cfg_DemTaskTime(
  void
  )
{
  return (float32)DEM_CFG_TASK_TIME;
}
#endif

/* ****************************************************************************
 % Dem_Cfg_TimeSeriesPastSamplesFast
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_TimeSeriesPastSamplesFast(                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
  return (uint8)DEM_CFG_TIMESERIES_FAST_PAST_SAMPLES;
#else
  return (uint8)0x00U;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_TimeSeriesFutureSamplesFast
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_TimeSeriesFutureSamplesFast(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
  return DEM_CFG_TIMESERIES_FAST_FUTURE_SAMPLES;
#else
  return 0u;
#endif
}

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON) && (DEM_DEV_RUNTIME_CHECKS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_TimeSeriesBufferCountFast
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_TimeSeriesBufferCountFast(
  void
  )
{
  uint8 lBufferCount;
# if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_ON)
  lBufferCount = Dem_Cfg_TimeSeriesPastSamplesFast();
# else
  lBufferCount = 1u;
# endif
  return lBufferCount;
}
#endif

/* ****************************************************************************
 % Dem_Cfg_TimeSeriesPastSamplesNormal
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_TimeSeriesPastSamplesNormal(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  return (uint8)DEM_CFG_TIMESERIES_NORMAL_PAST_SAMPLES;
#else
  return (uint8)0x00U;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_TimeSeriesFutureSamplesNormal
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_TimeSeriesFutureSamplesNormal(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  return (uint8)DEM_CFG_TIMESERIES_NORMAL_FUTURE_SAMPLES;
#else
  return (uint8)0x00U;
#endif
}

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_DEV_RUNTIME_CHECKS == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_TimeSeriesBufferCountNormal
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_TimeSeriesBufferCountNormal(
  void
  )
{
  uint8 lBufferCount;
# if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL == STD_ON)
  lBufferCount = Dem_Cfg_TimeSeriesPastSamplesNormal();
# else
  lBufferCount = 1u;
# endif
  return lBufferCount;
}
#endif

/* ****************************************************************************
 % Dem_Cfg_TimerEngineRunTimePollRate
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Cfg_TimerEngineRunTimePollRate(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_FEATURE_NEED_ENGINE_RUN_TIME == STD_ON)
  return DEM_CFG_TIMER_ENGINE_RUN_TIME_POLL_RATE;
#else
  return 0u;
#endif
}

/* ****************************************************************************
 % Dem_Cfg_FindEventFromUdsDtc
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Cfg_FindEventFromUdsDtc(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  Dem_EventIdType lLowerLimit;
  Dem_EventIdType lEventId;
  switch (MemoryId)
  {
  case DEM_CFG_MEMORYID_PRIMARY:
  case DEM_CFG_MEMORYID_PERMANENT:
    lLowerLimit = Dem_Cfg_GlobalPrimaryFirst();
    lEventId    = Dem_Cfg_GlobalPrimaryLast();
    break;
#if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
  case DEM_CFG_MEMORYID_SECONDARY:
    lLowerLimit = Dem_Cfg_GlobalSecondaryFirst();
    lEventId    = Dem_Cfg_GlobalSecondaryLast();
    break;
#endif
  default:
    lLowerLimit = DEM_EVENT_INVALID;
    lEventId    = DEM_EVENT_INVALID;
    break;
  }

  if (lLowerLimit != DEM_EVENT_INVALID)
  {
    for (; lEventId >= lLowerLimit; --lEventId)
    {
      if (DTC == Dem_Cfg_EventUdsDtc(lEventId))
      {
        break;
      }
    }
    if (lEventId < lLowerLimit)
    {
      lEventId = DEM_EVENT_INVALID;
    }
  }

  return lEventId;
}

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_FindJ1939NodeFromNmNode
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_FindJ1939NodeFromNmNode(
  CONST(uint16, AUTOMATIC)  NmNodeId                                                                                             /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  uint8 lReturnValue;
  uint8 lNmNodeIndex;

  lReturnValue = DEM_CFG_J1939_NODE_INVALID;

  if (NmNodeId != DEM_CFG_NMNODEID_INVALID)
  {
    lNmNodeIndex = DEM_CFG_J1939_NODE_INVALID;

    do
    {
      --lNmNodeIndex;
      if (NmNodeId == Dem_Cfg_J1939NmNodeId(lNmNodeIndex))
      {
        lReturnValue = (uint8)lNmNodeIndex;
        break;
      }
    } while (lNmNodeIndex > 0u);                                                                                                  /* PRQA S 2993 */ /* MD_DEM_2993 */
  }
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Cfg_FindEventFromJ1939Dtc
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Cfg_FindEventFromJ1939Dtc(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  Dem_EventIdType lLowerLimit;
  Dem_EventIdType lEventId;
  switch (MemoryId)
  {
  case DEM_CFG_MEMORYID_PRIMARY:
    lLowerLimit = Dem_Cfg_GlobalPrimaryFirst();
    lEventId    = Dem_Cfg_GlobalPrimaryLast();
    break;
  case DEM_CFG_MEMORYID_SECONDARY:
    lLowerLimit = Dem_Cfg_GlobalSecondaryFirst();
    lEventId    = Dem_Cfg_GlobalSecondaryLast();
    break;
  default:
    lLowerLimit = DEM_EVENT_INVALID;
    lEventId    = DEM_EVENT_INVALID;
    break;
  }

  if (lLowerLimit != DEM_EVENT_INVALID)
  {
    for (; lEventId >= lLowerLimit; --lEventId)
    {
      if (DTC == Dem_Cfg_EventJ1939Dtc(lEventId))
      {
        break;
      }
    }
    if (lEventId < lLowerLimit)
    {
      lEventId = DEM_EVENT_INVALID;
    }
  }

  return lEventId;
}
#endif

#if (DEM_CFG_CLEAR_GROUP_DTCS == STD_ON)
/************************************************************************************************************
 %  Dem_Cfg_EventGroupMask
 ***********************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_EventGroupMask(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  uint8 lGroupMask;
  uint32 lDTC;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lDTC = Dem_Cfg_EventUdsDtc(EventId);
  if (lDTC == 0x00FFFFFFUL)
  {
    /* event has no Dtc configured */
    lGroupMask = DEM_CFG_GROUPMASK_NONE;
  }
  else
  {
    lGroupMask = DEM_CFG_GROUPMASK_NONE;
# if (Dem_Cfg_HasDtcGroupMask() == TRUE)
    {
      uint8 lIter;
      uint32 lGroupDTC;
      for (lIter = Dem_Cfg_GetSizeOfDtcGroupMask(); lIter > 0u; lIter--)
      {
        lGroupDTC= Dem_Cfg_GetUdsGroupDtcOfDtcGroupMask(lIter - 1u);
        if (lDTC >= lGroupDTC)
        {
          lGroupMask = Dem_Cfg_GetGroupMaskOfDtcGroupMask(lIter - 1u);
          break;
        }
      }
    }
#endif
  }

  return lGroupMask;
}
#endif

/* ****************************************************************************
 % Dem_Cfg_CombinedGroupGetEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Cfg_CombinedGroupGetEvent(                                                                                                   /* PRQA S 3206, 3219 */ /* MD_DEM_3206, MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId
  )
{
  Dem_Cfg_CombinedGroupIterType lGroupIter;

  /* In rare cases GroupId is not required */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

  Dem_Cfg_CombinedGroupIterInit(GroupId, &lGroupIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
  return Dem_Cfg_CombinedGroupIterGet(&lGroupIter);                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
}

/* ****************************************************************************
 % Dem_Cfg_GetMasterEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Cfg_GetMasterEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_EventIdType  lMasterEventId;

  lMasterEventId = EventId;

#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  if (EventId != DEM_EVENT_INVALID)
  {
    Dem_Cfg_CombinedGroupIndexType lGroupId;
    lGroupId = Dem_Cfg_EventCombinedGroup(EventId);

    if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
    {
      lMasterEventId = Dem_Cfg_CombinedGroupGetEvent(lGroupId);
    }
  }
#endif

  return lMasterEventId;
}

/* ****************************************************************************
 % Dem_Cfg_GetMemoryRepresentative
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Cfg_GetMemoryRepresentative(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_EventIdType  lRepresentativeEventId;

  lRepresentativeEventId = EventId;

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (EventId != DEM_EVENT_INVALID)
  {
    Dem_Cfg_CombinedGroupIndexType lGroupId;
    lGroupId = Dem_Cfg_EventCombinedGroup(EventId);

    if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
    {
      lRepresentativeEventId = Dem_Cfg_CombinedGroupGetEvent(lGroupId);
    }
  }
#endif

  return lRepresentativeEventId;
}

#if ((DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_DTCFreezeFrameRecordIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_DTCFreezeFrameRecordIterExists(
  CONSTP2CONST(Dem_Cfg_DTCFreezeFrameIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}
#endif

#if ((DEM_CFG_SUPPORT_SRECS == STD_ON) \
  && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_DTCFreezeFrameRecordIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_DTCFreezeFrameRecordIterGet(
  CONSTP2CONST(Dem_Cfg_DTCFreezeFrameIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
    return Dem_Cfg_GetRecordIdOfSnapshotDataRecordsOfCombinedDTCs(Dem_Cfg_GetSnapshotDataRecordsOfCombinedDTCs_DTC2FF_Ind(IterPtr->mIdx));
}
#endif

#if ((DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_DTCFreezeFrameRecordIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_DTCFreezeFrameRecordIterInit(
  CONSTP2VAR(Dem_Cfg_DTCFreezeFrameIterType, AUTOMATIC, AUTOMATIC)  IterPtr,
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) CombinedGroupIdx
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CombinedGroupIdx)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
  IterPtr->mIdx = Dem_Cfg_GetSnapshotDataRecordsOfCombinedDTCs_DTC2FF_IndStartIdxOfCombinedGroups(CombinedGroupIdx);             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetSnapshotDataRecordsOfCombinedDTCs_DTC2FF_IndEndIdxOfCombinedGroups(CombinedGroupIdx);            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if ((DEM_CFG_SUPPORT_SRECS)\
     && (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)\
     && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_GetMaxFreezeFrameIdCombinedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_GetMaxFreezeFrameIdCombinedEvent(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) CombinedGroupIdx
  )
{
  Dem_Cfg_SnapshotDataRecordsOfCombinedDTCs_DTC2FF_IndEndIdxOfCombinedGroupsType lMaxSRecIndex;
  lMaxSRecIndex = (Dem_Cfg_GetSnapshotDataRecordsOfCombinedDTCs_DTC2FF_IndEndIdxOfCombinedGroups(CombinedGroupIdx) - 1u);
  return Dem_Cfg_GetRecordIdOfSnapshotDataRecordsOfCombinedDTCs(Dem_Cfg_GetSnapshotDataRecordsOfCombinedDTCs_DTC2FF_Ind(lMaxSRecIndex));
}
#endif

#if ((DEM_CFG_SUPPORT_SRECS == STD_ON) \
  && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_DTCFreezeFrameRecordIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_DTCFreezeFrameRecordIterNext(
  CONSTP2VAR(Dem_Cfg_DTCFreezeFrameIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if ((DEM_CFG_SUPPORT_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_DTCExtendedDataRecordIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_DTCExtendedDataRecordIterExists(
  CONSTP2CONST(Dem_Cfg_DTCExtendedDataRecordIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}
#endif

#if ((DEM_CFG_SUPPORT_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_DTCExtendedDataRecordIterGetRecordNr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Cfg_DTCExtendedDataRecordIterGetRecordNr(
  CONSTP2CONST(Dem_Cfg_DTCExtendedDataRecordIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
    return (uint8)(Dem_Cfg_GetIdNumberOfDataCollectionTable(Dem_Cfg_GetDataCollectionTableIdxOfExtendedDataRecordsOfCombinedDTCs(Dem_Cfg_GetExtendedDataRecordsOfCombinedDTCs_DTC2EDR_Ind(IterPtr->mIdx))));
}
#endif

#if ((DEM_CFG_SUPPORT_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_DTCExtendedDataRecordIterGetERecIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_ERecIndexType, DEM_CODE)
Dem_Cfg_DTCExtendedDataRecordIterGetERecIndex(
  CONSTP2CONST(Dem_Cfg_DTCExtendedDataRecordIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
    return (Dem_Cfg_GetDataCollectionTableIdxOfExtendedDataRecordsOfCombinedDTCs(Dem_Cfg_GetExtendedDataRecordsOfCombinedDTCs_DTC2EDR_Ind(IterPtr->mIdx)));
}
#endif

#if ((DEM_CFG_SUPPORT_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_DTCExtendedDataRecordIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_DTCExtendedDataRecordIterInit(
  CONSTP2VAR(Dem_Cfg_DTCExtendedDataRecordIterType, AUTOMATIC, AUTOMATIC)  IterPtr,
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) CombinedGroupIdx
  )
{
  IterPtr->mIdx = Dem_Cfg_GetExtendedDataRecordsOfCombinedDTCs_DTC2EDR_IndStartIdxOfCombinedGroups(CombinedGroupIdx);            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetExtendedDataRecordsOfCombinedDTCs_DTC2EDR_IndEndIdxOfCombinedGroups(CombinedGroupIdx);           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if ((DEM_CFG_SUPPORT_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_DTCExtendedDataRecordIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_DTCExtendedDataRecordIterNext(
  CONSTP2VAR(Dem_Cfg_DTCExtendedDataRecordIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if ((DEM_CFG_SUPPORT_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_ExtendedDataRecordEventIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_ExtendedDataRecordEventIterExists(
  CONSTP2CONST(Dem_Cfg_ExtendedDataRecordEventIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}
#endif

#if ((DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_FreezeFrameRecordEventIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Cfg_FreezeFrameRecordEventIterExists(
CONSTP2CONST(Dem_Cfg_FreezeFrameRecordEventIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}
#endif

#if ((DEM_CFG_SUPPORT_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_ExtendedDataRecordEventIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Cfg_ExtendedDataRecordEventIterGet(
  CONSTP2CONST(Dem_Cfg_ExtendedDataRecordEventIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (Dem_EventIdType)(Dem_Cfg_GetCombinedEventIds(Dem_Cfg_GetCombinedEventIds_ERec2Subevent_Ind(IterPtr->mIdx)));
}
#endif

#if ((DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_FreezeFrameRecordEventIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Cfg_FreezeFrameRecordEventIterGet(
CONSTP2CONST(Dem_Cfg_FreezeFrameRecordEventIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
    return (Dem_EventIdType)(Dem_Cfg_GetCombinedEventIds(Dem_Cfg_GetCombinedEventIds_SRec2Subevent_Ind(IterPtr->mIdx)));
}
#endif

#if ((DEM_CFG_SUPPORT_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_ExtendedDataRecordEventIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Cfg_ExtendedDataRecordEventIterInit(
  CONSTP2VAR(Dem_Cfg_ExtendedDataRecordEventIterType, AUTOMATIC, AUTOMATIC)  IterPtr,
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) CombinedGroupIdx,
  CONST(uint8, AUTOMATIC) ERecId
  )
{
  Dem_Cfg_DTCExtendedDataRecordIterType lERecIterator;

  for (Dem_Cfg_DTCExtendedDataRecordIterInit(&lERecIterator, CombinedGroupIdx);                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_DTCExtendedDataRecordIterExists(&lERecIterator) == TRUE;                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_DTCExtendedDataRecordIterNext(&lERecIterator))                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    if (Dem_Cfg_DTCExtendedDataRecordIterGetRecordNr(&lERecIterator) == ERecId)                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      IterPtr->mIdx = Dem_Cfg_GetCombinedEventIds_ERec2Subevent_IndStartIdxOfExtendedDataRecordsOfCombinedDTCs(Dem_Cfg_GetExtendedDataRecordsOfCombinedDTCs_DTC2EDR_Ind(lERecIterator.mIdx)); /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      IterPtr->mEndIdx = Dem_Cfg_GetCombinedEventIds_ERec2Subevent_IndEndIdxOfExtendedDataRecordsOfCombinedDTCs(Dem_Cfg_GetExtendedDataRecordsOfCombinedDTCs_DTC2EDR_Ind(lERecIterator.mIdx)); /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      break;
    }
  }

  /* Inconsistency between tables */
  if (Dem_Cfg_DTCExtendedDataRecordIterExists(&lERecIterator) == FALSE)                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    IterPtr->mIdx = 0x00U;                                                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    IterPtr->mEndIdx = 0x00U;                                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
  }
}
#endif

#if ((DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_FreezeFrameRecordEventIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Cfg_FreezeFrameRecordEventIterInit(
CONSTP2VAR(Dem_Cfg_FreezeFrameRecordEventIterType, AUTOMATIC, AUTOMATIC)  IterPtr,
CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) CombinedGroupIdx,
CONST(uint8, AUTOMATIC) SRecId
)
{
  Dem_Cfg_DTCFreezeFrameIterType lSRecIterator;

  for (Dem_Cfg_DTCFreezeFrameRecordIterInit(&lSRecIterator, CombinedGroupIdx);                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_DTCFreezeFrameRecordIterExists(&lSRecIterator) == TRUE;                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_DTCFreezeFrameRecordIterNext(&lSRecIterator))                                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    if (Dem_Cfg_DTCFreezeFrameRecordIterGet(&lSRecIterator) == SRecId)                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      IterPtr->mIdx = Dem_Cfg_GetCombinedEventIds_SRec2Subevent_IndStartIdxOfSnapshotDataRecordsOfCombinedDTCs(Dem_Cfg_GetSnapshotDataRecordsOfCombinedDTCs_DTC2FF_Ind(lSRecIterator.mIdx)); /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      IterPtr->mEndIdx = Dem_Cfg_GetCombinedEventIds_SRec2Subevent_IndEndIdxOfSnapshotDataRecordsOfCombinedDTCs(Dem_Cfg_GetSnapshotDataRecordsOfCombinedDTCs_DTC2FF_Ind(lSRecIterator.mIdx)); /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      break;
    }
  }

  /* Inconsistency between tables */
  if (Dem_Cfg_DTCFreezeFrameRecordIterExists(&lSRecIterator) == FALSE)                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    IterPtr->mIdx = 0x00U;                                                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    IterPtr->mEndIdx = 0x00U;                                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
  }
}
#endif

#if ((DEM_CFG_SUPPORT_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_ExtendedDataRecordEventIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_ExtendedDataRecordEventIterNext(
  CONSTP2VAR(Dem_Cfg_ExtendedDataRecordEventIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if ((DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_Cfg_FreezeFrameRecordEventIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Cfg_FreezeFrameRecordEventIterNext(
CONSTP2VAR(Dem_Cfg_FreezeFrameRecordEventIterType, AUTOMATIC, AUTOMATIC) IterPtr
)
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif  /* DEM_CFG_DEFINITIONS_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Cfg_Definitions.h
 *********************************************************************************************************************/
