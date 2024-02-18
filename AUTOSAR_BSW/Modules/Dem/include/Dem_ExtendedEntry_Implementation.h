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
/*! \addtogroup Dem_ExtendedEntry
 *  \{
 *  \file       Dem_ExtendedEntry_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Encapsulates the list of extended data record buffers stored in the memory entry
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_EXTENDEDENTRY_IMPLEMENTATION_H)
#define DEM_EXTENDEDENTRY_IMPLEMENTATION_H

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

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_ExtendedEntry_Interface.h"


/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Core_Interface.h"
#include "Dem_MemoryEntryIF_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_EXTENDEDENTRY_IMPLEMENTATION_FILENAME "Dem_ExtendedEntry_Implementation.h"

/*! Index indicating an invalid value */
#define DEM_EXTENDEDENTRY_USEREREC_STORAGEINDEX_INVALID    32U

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_ExtendedEntry_Public
 * \{
 */


/* ****************************************************************************
 % Dem_ExtendedEntry_ERecIsSupportedByAvailableCombinedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
# if ((DEM_CFG_SUPPORT_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_ExtendedEntry_ERecIsSupportedByAvailableCombinedEvent(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  CombinedDTCGroup,
  CONST(uint8, AUTOMATIC)  ERecId
  )
{
  Dem_Cfg_ExtendedDataRecordEventIterType lExtendedDataRecordEventIter;
  boolean lMatch;

  lMatch = FALSE;

  for (Dem_Cfg_ExtendedDataRecordEventIterInit(&lExtendedDataRecordEventIter, CombinedDTCGroup, ERecId);                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_ExtendedDataRecordEventIterExists(&lExtendedDataRecordEventIter) == TRUE;                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_ExtendedDataRecordEventIterNext(&lExtendedDataRecordEventIter))                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lEventId;
    lEventId = Dem_Cfg_ExtendedDataRecordEventIterGet(&lExtendedDataRecordEventIter);                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if ((Dem_Cfg_EventAvailableByVariant(lEventId) == TRUE)
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lEventId)) == FALSE))                        
    {
      lMatch = TRUE;
      break;
    }
  }

  return lMatch;
}
#endif

# if ((DEM_CFG_SUPPORT_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_ExtendedEntry_TestDTCHasERecConfigured
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
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_ExtendedEntry_TestDTCHasERecConfigured(
  CONST(uint8, AUTOMATIC)  ERecId,
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  CombinedDTCGroup,
  CONSTP2VAR(Dem_Cfg_ERecIndexType, AUTOMATIC, AUTOMATIC)  ERecEntryIndex
  )
{
  boolean lRecordFound;
  Dem_Cfg_DTCExtendedDataRecordIterType lDTCExtendedDataRecordIter;

  lRecordFound = FALSE;
  
  for (Dem_Cfg_DTCExtendedDataRecordIterInit(&lDTCExtendedDataRecordIter, CombinedDTCGroup);                                     /* PRQA S 0771 */ /*  MD_DEM_15.4_opt */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
       (Dem_Cfg_DTCExtendedDataRecordIterExists(&lDTCExtendedDataRecordIter) == TRUE);                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_DTCExtendedDataRecordIterNext(&lDTCExtendedDataRecordIter))                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    if (Dem_Cfg_DTCExtendedDataRecordIterGetRecordNr(&lDTCExtendedDataRecordIter) == ERecId)                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      if (Dem_ExtendedEntry_ERecIsSupportedByAvailableCombinedEvent(CombinedDTCGroup, ERecId) == TRUE)
      {
        Dem_Cfg_ERecIndexType lERecIndex;

        lRecordFound = TRUE;
        lERecIndex = Dem_Cfg_DTCExtendedDataRecordIterGetERecIndex(&lDTCExtendedDataRecordIter);                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */

        /* Retrieve index to requested extended data record from the configuration */
        *ERecEntryIndex = lERecIndex;                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
      break;                                                                                                                     
    }

    if (Dem_Cfg_DTCExtendedDataRecordIterGetRecordNr(&lDTCExtendedDataRecordIter) > ERecId)                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
    { /* In an ordered list, no point to search for entries greater the ERec Id. 
          This means the combined DTC does not have the Extended data record configured */
      break;
    }
  }

  return lRecordFound;
}
#endif


/* ****************************************************************************
 % Dem_ExtendedEntry_IterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtendedEntry_IterInit(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(Dem_ExtendedEntry_IterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_SUPPORT_ERECS == STD_ON)
  IterPtr->mIdx = Dem_Cfg_GetDataCollectionTableEdr2CollIndStartIdxOfExtendedDataTable(                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
                                                                  Dem_Cfg_GetExtendedDataTableIdxOfEventTable(EventId));
    
  IterPtr->mEndIdx = Dem_Cfg_GetDataCollectionTableEdr2CollIndEndIdxOfExtendedDataTable(                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
                                                                  Dem_Cfg_GetExtendedDataTableIdxOfEventTable(EventId));
# else
  IterPtr->mIdx = 0;                                                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = 0;                                                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# endif
}

/* ****************************************************************************
 % Dem_ExtendedEntry_IterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtendedEntry_IterNext(
  CONSTP2VAR(Dem_ExtendedEntry_IterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_ExtendedEntry_IterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ExtendedEntry_IterExists(
  CONSTP2CONST(Dem_ExtendedEntry_IterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}

/* ****************************************************************************
 % Dem_ExtendedEntry_IterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_ERecIndexType, DEM_CODE)
Dem_ExtendedEntry_IterGet(
  CONSTP2CONST(Dem_ExtendedEntry_IterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_ERECS == STD_ON)
  return (Dem_Cfg_ERecIndexType) Dem_Cfg_GetDataCollectionTableEdr2CollInd(IterPtr->mIdx);
#else
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
  return (Dem_Cfg_ERecIndexType)0U;
#endif
}

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_ExtendedEntry_IteratorGetExtendedRecordDataConstPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_ExtendedEntry_IteratorGetExtendedRecordDataConstPtr(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ExtendedEntryIndex
  )
{
  if (MemoryEntryId == DEM_MEMORYENTRY_HANDLE_INVALID)
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }
  return Dem_MemoryEntry_GetExtendedRecordDataConstPtr(MemoryEntryId, ExtendedEntryIndex);
}
#endif /* (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) */


/* ****************************************************************************
 % Dem_ExtendedEntry_IteratorIsExtendedRecordStored
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ExtendedEntry_IteratorIsExtendedRecordStored(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ExtendedEntryIndex
  )
{
  boolean lExtendedRecordIsStored;

  lExtendedRecordIsStored = FALSE;
#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
  if (MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID)
  {
    uint8 lMask;

    lMask = ((uint8)1 << ExtendedEntryIndex);
    if ((Dem_MemoryEntry_GetExtendedHeader(MemoryEntryId) & lMask) != 0u)
    {
      lExtendedRecordIsStored = TRUE;
    }
  }
  else
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ExtendedEntryIndex)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
  return lExtendedRecordIsStored;
}

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_ExtendedEntry_IteratorUpdateExtendedEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtendedEntry_IteratorUpdateExtendedEntry(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ExtendedEntryIndex
  )
{
  if (MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID)
  {
    uint8 lMask;

    lMask = ((uint8)1 << ExtendedEntryIndex);
    Dem_MemoryEntry_SetExtendedHeader(MemoryEntryId,(Dem_MemoryEntry_GetExtendedHeader(MemoryEntryId) | lMask));
  }
  else
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }
}
#endif /* (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) */

#if ((DEM_CFG_SUPPORT_USER_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_ExtendedEntry_CalculateUserERecStorageIndex
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
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_ExtendedEntry_CalculateUserERecStorageIndex(
  CONST(uint8, AUTOMATIC)  ERecId,
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) CombinedGroupId
  )
{
  uint8 lUserERecIndex;
  Dem_Cfg_DTCExtendedDataRecordIterType lDTCExtendedDataRecordIter;

  lUserERecIndex = 0x00;

  for (Dem_Cfg_DTCExtendedDataRecordIterInit(&lDTCExtendedDataRecordIter, CombinedGroupId);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      (Dem_Cfg_DTCExtendedDataRecordIterExists(&lDTCExtendedDataRecordIter) == TRUE);                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_DTCExtendedDataRecordIterNext(&lDTCExtendedDataRecordIter))                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    uint8 lERecId;
    Dem_Cfg_ERecIndexType lERecEntryIndex;

    lERecId = Dem_Cfg_DTCExtendedDataRecordIterGetRecordNr(&lDTCExtendedDataRecordIter);                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lERecEntryIndex = Dem_Cfg_DTCExtendedDataRecordIterGetERecIndex(&lDTCExtendedDataRecordIter);                                /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_ERecType(lERecEntryIndex) == DEM_CFG_EREC_TYPE_USER)
    {
      if (lERecId == ERecId)
      {
        break;
      }
      else
      {
        lUserERecIndex++;
      }
    }
  }

  if (Dem_Cfg_DTCExtendedDataRecordIterExists(&lDTCExtendedDataRecordIter) == FALSE)                                             /* SBSW_DEM_POINTER_FORWARD_STACK */
  {
    lUserERecIndex = DEM_EXTENDEDENTRY_USEREREC_STORAGEINDEX_INVALID;
  }

  return lUserERecIndex;
}
#endif 

#if ((DEM_CFG_SUPPORT_USER_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_ExtendedEntry_GetUserERecStorageStatus
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
Dem_ExtendedEntry_GetUserERecStorageStatus(
  CONST(uint8, AUTOMATIC)  UserERecStorageIndex,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint32 lMask;
  boolean lExtendedDataRecordIsStored;

  lMask = 0x00U;
  lExtendedDataRecordIsStored = FALSE;

  if (UserERecStorageIndex < DEM_EXTENDEDENTRY_USEREREC_STORAGEINDEX_INVALID)
  {
    lMask = (uint32)1 << UserERecStorageIndex;
    if ((Dem_MemoryEntry_GetCombinedDTCExtendedHeader(MemoryEntryId) & lMask) != 0u)
    {
      lExtendedDataRecordIsStored = TRUE;
    }
  }
  else
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }

  return lExtendedDataRecordIsStored;
}
#endif 

#if ((DEM_CFG_SUPPORT_USER_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
/* ****************************************************************************
 % Dem_ExtendedEntry_SetUserERecStorageStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtendedEntry_SetUserERecStorageStatus(
  CONST(uint8, AUTOMATIC)  UserERecStorageIndex,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  if (MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID)
  {
    uint32 lMask;

    lMask = 0x00U;
    if (UserERecStorageIndex < DEM_EXTENDEDENTRY_USEREREC_STORAGEINDEX_INVALID)
    {
      lMask = (uint32)1 << UserERecStorageIndex;
      Dem_MemoryEntry_SetCombinedDTCExtendedHeader(MemoryEntryId, 
        (Dem_MemoryEntry_GetCombinedDTCExtendedHeader(MemoryEntryId) | lMask));
    }
    else
    {
      Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
    }
  }
  else
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_EXTENDEDENTRY_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ExtendedEntry_Implementation.h
 *********************************************************************************************************************/
