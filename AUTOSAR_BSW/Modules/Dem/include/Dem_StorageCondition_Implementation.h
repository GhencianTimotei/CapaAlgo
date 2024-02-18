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
/*! \addtogroup Dem_StorageCondition
 *  \{
 *  \file       Dem_StorageCondition_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of the StorageCondition subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_STORAGECONDITION_IMPLEMENTATION_H)
#define DEM_STORAGECONDITION_IMPLEMENTATION_H

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
#include "Dem_StorageCondition_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_STORAGECONDITION_IMPLEMENTATION_FILENAME "Dem_StorageCondition_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_StorageCondition_PublicProperties
 * \{
 */

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GetGlobalStorageConditionCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_StorageCondition_GetGlobalStorageConditionCount(
  void
  )
{
  return DEM_CFG_GLOBAL_STORAGE_COND_COUNT;
}
#endif

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
 * \defgroup Dem_StorageCondition_Private Private Methods
 * \{
 */


#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GetStorageConditionActive
 *****************************************************************************/
/*!
 * \brief         Get current activation state of storage condition
 *
 * \details       Get current activation state of storage condition
 *
 * \param[in]     StorageCondition
 *                Unique handle of the storage condition
 *
 * \return        Activation state of storage condition
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StorageCondition_GetStorageConditionActive(
  CONST(uint8, AUTOMATIC)  StorageCondition
  );
#endif


#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_SetStorageConditionActive
 *****************************************************************************/
/*!
 * \brief         Set current activation status of storage condition
 *
 * \details       Set current activation status of storage condition
 *
 * \param[in]     StorageCondition
 *                Unique handle of the storage condition
 * \param[in]     ActiveStatus
 *                New activation state of the storage condition
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_SetStorageConditionActive(
  CONST(uint8, AUTOMATIC)  StorageCondition,
  CONST(boolean, AUTOMATIC)  ActiveStatus
  );
#endif


#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GetStorageConditionGroupCounter
 *****************************************************************************/
/*!
 * \brief         Get current internal counter of storage condition group
 *
 * \details       Get current internal counter of storage condition group
 *
 * \param[in]     StorageConditionGroup
 *                Unique handle of the storage condition group
 *
 * \return        Internal counter of storage condition group
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_StorageCondition_GetStorageConditionGroupCounter(
  CONST(uint16, AUTOMATIC)  StorageConditionGroup
  );
#endif


#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_SetStorageConditionGroupCounter
 *****************************************************************************/
/*!
 * \brief         Set current internal counter of storage condition group
 *
 * \details       Set current internal counter of storage condition group
 *
 * \param[in]     StorageConditionGroup
 *                Unique handle of the storage condition group
 * \param[in]     Counter
 *                New internal counter of the storage condition group
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_SetStorageConditionGroupCounter(
  CONST(uint16, AUTOMATIC)  StorageConditionGroup,
  CONST(uint8, AUTOMATIC)  Counter
  );
#endif


#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GetEventStorageConditionGroup
 *****************************************************************************/
/*!
 * \brief         Get the storage condition group for an event
 *
 * \details       Get the storage condition group for an event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Storage condition group for the event
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_StorageCondition_GetEventStorageConditionGroup(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GetStorageConditionInitValue
 *****************************************************************************/
/*!
 * \brief         Get the initial value of storage condition
 *
 * \details       Get the initial value of storage condition
 *
 * \param[in]     StorageCondition
 *                Unique handle of the storage condition.
 *
 * \return        TRUE 
 *                The initial value of storage condition, is TRUE
 * \return        FALSE 
 *                The initial value of storage condition, is FALSE
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StorageCondition_GetStorageConditionInitValue(
  CONST(uint8, AUTOMATIC)  StorageCondition
  );
#endif


#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GroupIterExists
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
 *                Dem_StorageCondition_GroupIterGet() will return a valid element
 *                on this iterator
 * \return        FALSE
 *                Dem_StorageCondition_GroupIterGet() is undefined on this iterator
 *
 * \pre           IterPtr has been initialized
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StorageCondition_GroupIterExists(
  CONSTP2CONST(Dem_StorageCondition_EventStorageConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );
#endif


#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GroupIterGet
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator
 *
 * \details       Get the element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Handle to Storage condition group descriptor table
 *
 * \pre           IterPtr has been initialized
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_StorageCondition_GroupIterGet(
  CONSTP2CONST(Dem_StorageCondition_EventStorageConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );
#endif


#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GroupIterInit
 *****************************************************************************/
/*!
 * \brief         Init the iterator
 *
 * \details       Initializes the iterator to enumerate storage condition groups
 *                referencing given storage condition
 *
 * \param[in]     StorageConditionID
 *                Unique handle of the storage condition.
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_GroupIterInit(
  CONST(uint8, AUTOMATIC) StorageConditionID,
  CONSTP2VAR(Dem_StorageCondition_EventStorageConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );
#endif


#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GroupIterNext
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next element
 *
 * \details       Move the iterator to the next element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_GroupIterNext(
  CONSTP2VAR(Dem_StorageCondition_EventStorageConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GetStorageConditionActive
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StorageCondition_GetStorageConditionActive(
  CONST(uint8, AUTOMATIC)  StorageCondition
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StorageCondition)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  return Dem_Cfg_IsStorageConditionFulfilled(StorageCondition);
# else
  return TRUE;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_SetStorageConditionActive
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_SetStorageConditionActive(
  CONST(uint8, AUTOMATIC)  StorageCondition,
  CONST(boolean, AUTOMATIC)  ActiveStatus
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ActiveStatus)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StorageCondition)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
#  if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (StorageCondition >= Dem_Cfg_GetSizeOfStorageConditionFulfilled())
  {
    Dem_Error_RunTimeCheckFailed(DEM_STORAGECONDITION_IMPLEMENTATION_FILENAME, __LINE__);                                        /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#  endif
  {
    Dem_Cfg_SetStorageConditionFulfilled(StorageCondition, ActiveStatus);                                                        /* SBSW_DEM_ARRAY_WRITE_STORAGECONDITIONFULFILLED */
  }
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GetStorageConditionGroupCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_StorageCondition_GetStorageConditionGroupCounter(
  CONST(uint16, AUTOMATIC)  StorageConditionGroup
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StorageConditionGroup)                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  return Dem_Cfg_GetStorageConditionGroupCounter(StorageConditionGroup);
# else
  return 0;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_SetStorageConditionGroupCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_SetStorageConditionGroupCounter(
  CONST(uint16, AUTOMATIC)  StorageConditionGroup,
  CONST(uint8, AUTOMATIC)  Counter
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StorageConditionGroup)                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Counter)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
#  if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (StorageConditionGroup >= Dem_Cfg_GetSizeOfStorageConditionGroupCounter())
  {
    Dem_Error_RunTimeCheckFailed(DEM_STORAGECONDITION_IMPLEMENTATION_FILENAME, __LINE__);                                        /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#  endif
  {
    Dem_Cfg_SetStorageConditionGroupCounter(StorageConditionGroup, Counter);                                                     /* PRQA S 2841 */ /* MD_DEM_Dir4.1_RunTimeCheckWriteOperation */ /* SBSW_DEM_ARRAY_WRITE_STORAGECONDITIONGROUPCOUNTER */
  }
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GetEventStorageConditionGroup
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_StorageCondition_GetEventStorageConditionGroup(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  return Dem_Cfg_GetStorageConditionGroupTableIdxOfEventTable(EventId);
# else
  return DEM_STORAGECONDITION_NO_STORAGE_CONDITION_GROUP;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GetStorageConditionInitValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StorageCondition_GetStorageConditionInitValue(
  CONST(uint8, AUTOMATIC) StorageCondition
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StorageCondition)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  return Dem_Cfg_IsFulfilledAtInitOfStorageConditionInitTable(StorageCondition);                                                 /* PRQA S 2841 */ /* MD_DEM_Dir4.1_ReadOperation */
# else
  return TRUE;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GroupIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StorageCondition_GroupIterExists(
  CONSTP2CONST(Dem_StorageCondition_EventStorageConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                            /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
# else
  return FALSE;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GroupIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_StorageCondition_GroupIterGet(
  CONSTP2CONST(Dem_StorageCondition_EventStorageConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                            /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  return Dem_Cfg_GetStorageConditionGroupTableInd(IterPtr->mIdx);
# else
  return 0;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GroupIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_GroupIterInit(
  CONST(uint8, AUTOMATIC)  StorageConditionID,                                                                                   /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(Dem_StorageCondition_EventStorageConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                              /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StorageConditionID)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  IterPtr->mIdx = Dem_Cfg_GetStorageConditionGroupTableIndStartIdxOfStorageConditionTable(StorageConditionID);                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetStorageConditionGroupTableIndEndIdxOfStorageConditionTable(StorageConditionID);                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# else
  IterPtr->mIdx = 0;                                                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = 0;                                                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GroupIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_GroupIterNext(
  CONSTP2VAR(Dem_StorageCondition_EventStorageConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                              /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  IterPtr->mIdx += 1u;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# endif
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
 * \addtogroup Dem_StorageCondition_Public
 * \{
 */

/* ****************************************************************************
 % Dem_StorageCondition_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_StorageCondition_PreInit(
  void
  )
{
#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
  uint8  lStorageCondition;
  uint16 lStorageConditionGroupCounter;

  for (lStorageCondition = 0u;
    lStorageCondition < Dem_Cfg_GetSizeOfStorageConditionFulfilled();                                                            /* PRQA S 2994 */ /* MD_DEM_2994 */
    ++lStorageCondition)
  {
    Dem_StorageCondition_SetStorageConditionActive(lStorageCondition, TRUE);
  }

  for (lStorageConditionGroupCounter = 0u;
    lStorageConditionGroupCounter < Dem_Cfg_GetSizeOfStorageConditionGroupCounter();                                             /* PRQA S 2994 */ /* MD_DEM_2994 */
    ++lStorageConditionGroupCounter
    )
  {
    Dem_StorageCondition_SetStorageConditionGroupCounter(lStorageConditionGroupCounter, 0u);
  }
#endif
}

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_Init(
  void
  )
{
  uint8 lStorageCondition;
  /* Initialize storage condition group counter */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  Dem_MemSet((Dem_DataPtrType)&Dem_Cfg_GetStorageConditionGroupCounter(0),                                                       /* PRQA S 0310, 0312, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_11.8, MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_STORAGECONDITIONGROUPCOUNTER */
    0,
    Dem_Cfg_GetSizeOfStorageConditionGroupCounter()*sizeof(Dem_Cfg_GetStorageConditionGroupCounter(0)));
# endif

  for (lStorageCondition = 0u; lStorageCondition < Dem_StorageCondition_GetGlobalStorageConditionCount(); ++lStorageCondition)   /* PRQA S 2994 */ /* MD_DEM_2994 */
  {
    boolean lStorageConditionInitState;
    Dem_StorageCondition_EventStorageConditionGroupIterType lStorageConditionIter;

    lStorageConditionInitState = Dem_StorageCondition_GetStorageConditionInitValue(lStorageCondition);

    if (lStorageConditionInitState == FALSE)
    {
      for (Dem_StorageCondition_GroupIterInit(lStorageCondition, &lStorageConditionIter);                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_StorageCondition_GroupIterExists(&lStorageConditionIter) == TRUE;                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_StorageCondition_GroupIterNext(&lStorageConditionIter))                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        uint16 lStorageConditionGroup;

        lStorageConditionGroup = Dem_StorageCondition_GroupIterGet(&lStorageConditionIter);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */

        Dem_StorageCondition_SetStorageConditionGroupCounter(lStorageConditionGroup, 
          (uint8)(Dem_StorageCondition_GetStorageConditionGroupCounter(lStorageConditionGroup) + 1u));
      }
    }
    Dem_StorageCondition_SetStorageConditionActive(lStorageCondition, lStorageConditionInitState);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_StorageCondition_TestEventStorageConditionsFulfilled
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
Dem_StorageCondition_TestEventStorageConditionsFulfilled(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
  boolean lStorageConditionsSatisfied;
  uint16 lStorageConditionGroup;

  lStorageConditionGroup = Dem_StorageCondition_GetEventStorageConditionGroup(EventId);
  if (lStorageConditionGroup != DEM_STORAGECONDITION_NO_STORAGE_CONDITION_GROUP)
  {
    if (Dem_StorageCondition_GetStorageConditionGroupCounter(lStorageConditionGroup) > 0u)
    {
      lStorageConditionsSatisfied = FALSE;
    }
    else
    {
      lStorageConditionsSatisfied = TRUE;
    }
  }
  else
  {
    lStorageConditionsSatisfied = TRUE;
  }

  return lStorageConditionsSatisfied;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return TRUE;
#endif
}

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_SetStorageConditionFulfilled
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
Dem_StorageCondition_SetStorageConditionFulfilled(
  CONST(uint8, AUTOMATIC)  StorageConditionID
  )
{
/* >>>> -------------------------------- Enter Critical Section: StateManager */
  Dem_EnterCritical_StateManager();

  if (Dem_StorageCondition_GetStorageConditionActive(StorageConditionID) == FALSE)
  {
    Dem_StorageCondition_EventStorageConditionGroupIterType lStorageConditionIter;
    for (Dem_StorageCondition_GroupIterInit(StorageConditionID, &lStorageConditionIter);                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_StorageCondition_GroupIterExists(&lStorageConditionIter) == TRUE;                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_StorageCondition_GroupIterNext(&lStorageConditionIter))                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      uint16 lStorageConditionGroup;

      lStorageConditionGroup = Dem_StorageCondition_GroupIterGet(&lStorageConditionIter);                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
      if (Dem_StorageCondition_GetStorageConditionGroupCounter(lStorageConditionGroup) > 0u)
# endif
      {
        Dem_StorageCondition_SetStorageConditionGroupCounter(lStorageConditionGroup,
          (uint8)(Dem_StorageCondition_GetStorageConditionGroupCounter(lStorageConditionGroup) - 1u));
      }
    }
    Dem_StorageCondition_SetStorageConditionActive(StorageConditionID, TRUE);
  }

  Dem_LeaveCritical_StateManager();
/* <<<< -------------------------------- Leave Critical Section: StateManager */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_ResetStorageConditionFulfilled
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
Dem_StorageCondition_ResetStorageConditionFulfilled(
  CONST(uint8, AUTOMATIC)  StorageCondition
  )
{
/* >>>> -------------------------------- Enter Critical Section: StateManager */
  Dem_EnterCritical_StateManager();

  if (Dem_StorageCondition_GetStorageConditionActive(StorageCondition) == TRUE)
  {
    Dem_StorageCondition_EventStorageConditionGroupIterType lStorageConditionIter;
    for (Dem_StorageCondition_GroupIterInit(StorageCondition, &lStorageConditionIter);                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_StorageCondition_GroupIterExists(&lStorageConditionIter) == TRUE;                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */ /* PRQA S 2994 */ /* MD_DEM_2994 */
         Dem_StorageCondition_GroupIterNext(&lStorageConditionIter))                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      uint16 lStorageConditionGroup;

      lStorageConditionGroup = Dem_StorageCondition_GroupIterGet(&lStorageConditionIter);                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_StorageCondition_SetStorageConditionGroupCounter(lStorageConditionGroup,
        (uint8)(Dem_StorageCondition_GetStorageConditionGroupCounter(lStorageConditionGroup) + 1u));
    }
    Dem_StorageCondition_SetStorageConditionActive(StorageCondition, FALSE);
  }

  Dem_LeaveCritical_StateManager();
/* <<<< -------------------------------- Leave Critical Section: StateManager */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* DEM_STORAGECONDITION_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_StorageCondition_Implementation.h
 *********************************************************************************************************************/
