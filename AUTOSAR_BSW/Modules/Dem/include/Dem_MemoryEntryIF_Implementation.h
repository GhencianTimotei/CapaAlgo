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
/*! \addtogroup Dem_MemoryEntryIF
 *  \{
 *  \file       Dem_MemoryEntryIF_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of Memory EntryIF subcomponent which encapsulates the Memory entry and known data 
 *              stored in the memory entry
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMORYENTRYIF_IMPLEMENTATION_H)                                                                                /* PRQA S 0883 */ /* MD_DEM_19.15 */
#define DEM_MEMORYENTRYIF_IMPLEMENTATION_H

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
#include "Dem_MemoryEntryIF_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Core_Interface.h"
#include "Dem_Infrastructure_Interface.h"
#include "Dem_Client_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_MEMORYENTRYIF_IMPLEMENTATION_FILENAME "Dem_MemoryEntryIF_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_MemoryEntry_PrivateProperties Private Properties
 * \{
 */

/* ****************************************************************************
 * Dem_MemoryEntry_GetEntry
 *****************************************************************************/
/*!
 * \brief         Get the N-th memory entry
 *
 * \details       Get the N-th memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle selects the index 'N'
 *
 * \return        Pointer to the N-th memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SharedMemoryEntryPtrType, DEM_CODE)
Dem_MemoryEntry_GetEntry(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );


/* ****************************************************************************
 * Dem_MemoryEntry_SetOccurrenceCounter
 *****************************************************************************/
/*!
 * \brief         Set the occurrence counter in the memory entry
 *
 * \details       Set the occurrence counter in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     OccurrenceCounter
 *                The occurrence counter to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_MemoryEntry_OccurrenceCounterType, AUTOMATIC) OccurrenceCounter
  );



/* ****************************************************************************
 * Dem_MemoryEntry_ResetOccurrenceCounter
 *****************************************************************************/
/*!
 * \brief         Reset the occurrence counter in the memory entry
 *
 * \details       Reset the occurrence counter in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_ResetOccurrenceCounter(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );


/* ****************************************************************************
 * Dem_MemoryEntry_SetFailedCycleCounter
 *****************************************************************************/
/*!
 * \brief         Set the 'Failed Cycle Counter' in the memory entry
 *
 * \details       Set the 'Failed Cycle Counter' in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     FailedCycleCounter
 *                The 'Failed Cycle Counter' to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetFailedCycleCounter(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) FailedCycleCounter
  );


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_MemoryEntry_GetEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SharedMemoryEntryPtrType, DEM_CODE)
Dem_MemoryEntry_GetEntry(
CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
)
{
  Dem_SharedMemoryEntryPtrType lMemoryEntry;
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (MemoryEntryId >= Dem_Cfg_GetSizeOfMemoryEntry())
  {
    Dem_Error_RunTimeCheckFailed(DEM_MEMORYENTRYIF_IMPLEMENTATION_FILENAME, __LINE__);                                             /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lMemoryEntry = Dem_Cfg_GetMemoryEntry(0);                                                                                    /* PRQA S 0310, 3305 */ /* MD_DEM_11.4_nvm, MD_DEM_3305 */
  }
  else
# endif
  {
    lMemoryEntry = Dem_Cfg_GetMemoryEntry(MemoryEntryId);                                                                        /* PRQA S 0310, 3305, 2841, 2842 */ /* MD_DEM_11.4_nvm, MD_DEM_3305, MD_DEM_Dir4.1_MemoryEntryPointerAccess, MD_DEM_Dir4.1_MemoryEntryPointerAccess */
  }

  return lMemoryEntry;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetOccurrenceCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter(                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_MemoryEntry_OccurrenceCounterType, AUTOMATIC) OccurrenceCounter
  )
{
#if (DEM_FEATURE_NEED_OCC_COUNTER == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->OccurrenceCounter = OccurrenceCounter;                                                /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(OccurrenceCounter)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}


/* ****************************************************************************
 % Dem_MemoryEntry_ResetOccurrenceCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_ResetOccurrenceCounter(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
#if (DEM_FEATURE_NEED_OCC_COUNTER == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->OccurrenceCounter = DEM_DATA_OCCURRENCE_INIT;                                         /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}


/* ****************************************************************************
 % Dem_MemoryEntry_SetFailedCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetFailedCycleCounter(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) FailedCycleCounter
  )
{
#if (DEM_CFG_DATA_FAILED_CYCLES == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->FailedCycleCounter = FailedCycleCounter;                                              /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FailedCycleCounter)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
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
 * \addtogroup Dem_MemoryEntry_PublicProperties
 * \{
 */

/* ****************************************************************************
 % Dem_MemoryEntry_GetEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemoryEntry_GetEventId(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  return (Dem_MemoryEntry_GetEntry(MemoryEntryId)->EventId);
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetEventId(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  )
{
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->EventId = EventId;                                                                    /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetTimestamp
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MemoryEntry_GetTimestamp(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  return (Dem_MemoryEntry_GetEntry(MemoryEntryId)->Timestamp);
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetTimestamp
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetTimestamp(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint32, AUTOMATIC) Timestamp
  )
{
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->Timestamp = Timestamp;                                                                /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetDebounceValueMax
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(sint16, DEM_CODE)
Dem_MemoryEntry_GetDebounceValueMax(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  sint16 lMaxDebounceValue;
#if (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON)
  lMaxDebounceValue = Dem_MemoryEntry_GetEntry(MemoryEntryId)->MaxDebounceValue;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lMaxDebounceValue = 0;
#endif
  return lMaxDebounceValue;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetDebounceValueMax
 *****************************************************************************/
/*!
  * Internal comment removed.
 *
 *
  */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetDebounceValueMax(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(sint16, AUTOMATIC) MaxDebounceValue
  )
{
#if (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->MaxDebounceValue = MaxDebounceValue;                                                  /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MaxDebounceValue)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetState(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint8 lState;
#if (DEM_CFG_SUPPORT_OBDII == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) || (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
  lState = Dem_MemoryEntry_GetEntry(MemoryEntryId)->State;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lState = 0u;
#endif
  return lState;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetState(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) State
  )
{
#if (DEM_CFG_SUPPORT_OBDII == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) || (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->State = State;                                                                        /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(State)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetAgingCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemoryEntry_GetAgingCounter(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint16 lAgingCounter;
#if ((DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) && (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF))
  lAgingCounter = Dem_MemoryEntry_GetEntry(MemoryEntryId)->AgingCounter;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lAgingCounter = 0u;
#endif
  return lAgingCounter;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetAgingCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetAgingCounter(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint16, AUTOMATIC) AgingCounter
  )
{
#if ((DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF) && (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF))
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->AgingCounter = AgingCounter;                                                          /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(AgingCounter)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetAgingTimer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MemoryEntry_GetAgingTimer(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint32 lAgingTimer;
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  lAgingTimer = Dem_MemoryEntry_GetEntry(MemoryEntryId)->AgingTimer;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lAgingTimer = 0u;
#endif
  return lAgingTimer;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetAgingTimer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetAgingTimer(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint32, AUTOMATIC) AgingTimer
  )
{
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->AgingTimer = AgingTimer;                                                              /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(AgingTimer)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetOccurrenceCounter1Byte
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter1Byte(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint8 lOccurrenceCounter;
#if (DEM_FEATURE_NEED_OCC_COUNTER == STD_ON) && (DEM_CFG_DATA_OCCCTR_2BYTE == STD_OFF)
  lOccurrenceCounter = Dem_MemoryEntry_GetEntry(MemoryEntryId)->OccurrenceCounter;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lOccurrenceCounter = 0u;
#endif
  return lOccurrenceCounter;
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetOccurrenceCounter2Byte
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter2Byte(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint16 lOccurrenceCounter;
#if (DEM_CFG_DATA_OCCCTR_2BYTE == STD_ON)
  lOccurrenceCounter = Dem_MemoryEntry_GetEntry(MemoryEntryId)->OccurrenceCounter;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lOccurrenceCounter = 0u;
#endif
  return lOccurrenceCounter;
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetFailedCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetFailedCycleCounter(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint8 lFailedCycleCounter;
#if (DEM_CFG_DATA_FAILED_CYCLES == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF)
  lFailedCycleCounter = Dem_MemoryEntry_GetEntry(MemoryEntryId)->FailedCycleCounter;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lFailedCycleCounter = 0u;
#endif
  return lFailedCycleCounter;
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetConsecutiveFailedCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint8 lConsecutiveFailedCycleCounter;
#if ( (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) \
   || ((DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF)))
  lConsecutiveFailedCycleCounter = Dem_MemoryEntry_GetEntry(MemoryEntryId)->ConsecutiveFailedCycleCounter;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lConsecutiveFailedCycleCounter = 0u;
#endif
  return lConsecutiveFailedCycleCounter;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetConsecutiveFailedCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetConsecutiveFailedCycleCounter(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
 CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
 CONST(uint8, AUTOMATIC) ConsecutiveFailedCycleCounter
 )
{
#if ( (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) \
  || ((DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF)))
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->ConsecutiveFailedCycleCounter = ConsecutiveFailedCycleCounter;                        /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ConsecutiveFailedCycleCounter)                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemoryEntry_GetCyclesSinceFirstFailed(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint16 lCyclesSinceFirstFailed;
#if (DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
  lCyclesSinceFirstFailed = Dem_MemoryEntry_GetEntry(MemoryEntryId)->CyclesSinceFirstFailed;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lCyclesSinceFirstFailed = 0u;
#endif
  return lCyclesSinceFirstFailed;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetCyclesSinceFirstFailed(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint16, AUTOMATIC) CyclesSinceFirstFailed
  )
{
#if (DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->CyclesSinceFirstFailed = CyclesSinceFirstFailed;                                      /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CyclesSinceFirstFailed)                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetTestedCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetTestedCyclesSinceFirstFailed(                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint8 lTestedCyclesSinceFirstFailed;
#if (DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON)
  lTestedCyclesSinceFirstFailed = Dem_MemoryEntry_GetEntry(MemoryEntryId)->TestedCyclesSinceFirstFailed;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lTestedCyclesSinceFirstFailed = 0u;
#endif
  return lTestedCyclesSinceFirstFailed;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetTestedCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetTestedCyclesSinceFirstFailed(                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) TestedCyclesSinceFirstFailed
  )
{
#if (DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->TestedCyclesSinceFirstFailed = TestedCyclesSinceFirstFailed;                          /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(TestedCyclesSinceFirstFailed)                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetCyclesSinceLastFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemoryEntry_GetCyclesSinceLastFailed(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint16 lCyclesSinceLastFailed;
#if (DEM_CFG_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON)
  lCyclesSinceLastFailed = Dem_MemoryEntry_GetEntry(MemoryEntryId)->CyclesSinceLastFailed;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lCyclesSinceLastFailed = 0u;
#endif
  return lCyclesSinceLastFailed;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetCyclesSinceLastFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetCyclesSinceLastFailed(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint16, AUTOMATIC) CyclesSinceLastFailed
  )
{
#if (DEM_CFG_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->CyclesSinceLastFailed = CyclesSinceLastFailed;                                        /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CyclesSinceLastFailed)                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
% Dem_MemoryEntry_GetWarmUpCyclesSinceLastFailed
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemoryEntry_GetWarmUpCyclesSinceLastFailed(                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint16 lWarmUpCyclesSinceLastFailed;
#if (DEM_CFG_DATA_WUC_SINCE_LAST_FAILED == STD_ON)
  lWarmUpCyclesSinceLastFailed = Dem_MemoryEntry_GetEntry(MemoryEntryId)->WUCSinceLastFailed;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lWarmUpCyclesSinceLastFailed = 0u;
#endif
  return lWarmUpCyclesSinceLastFailed;
}

/* ****************************************************************************
% Dem_MemoryEntry_SetWarmUpCyclesSinceLastFailed
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetWarmUpCyclesSinceLastFailed(                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint16, AUTOMATIC) WarmUpCyclesSinceLastFailed
  )
{
#if (DEM_CFG_DATA_WUC_SINCE_LAST_FAILED == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->WUCSinceLastFailed = WarmUpCyclesSinceLastFailed;                                     /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(WarmUpCyclesSinceLastFailed)                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetPreConfirmedStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetPreConfirmedStatus(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint8 lPreconfirmedStatus;
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  lPreconfirmedStatus = Dem_MemoryEntry_GetEntry(MemoryEntryId)->StatusIndicator;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lPreconfirmedStatus = 0u;
#endif
  return lPreconfirmedStatus;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetPreConfirmedStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetPreConfirmedStatus(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) StatusIndicator
  )
{
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->StatusIndicator = StatusIndicator;                                                    /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StatusIndicator)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetOccurrenceCounter1
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter1(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint8 lOccurrenceCounter1;
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  lOccurrenceCounter1 = Dem_MemoryEntry_GetEntry(MemoryEntryId)->OCC1;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lOccurrenceCounter1 = 0u;
#endif
  return lOccurrenceCounter1;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetOccurrenceCounter1
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter1(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) OccurrenceCounter1
  )
{
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->OCC1 = OccurrenceCounter1;                                                            /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(OccurrenceCounter1)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetOccurrenceCounter2
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter2(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint8 lOccurrenceCounter2;
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  lOccurrenceCounter2 = Dem_MemoryEntry_GetEntry(MemoryEntryId)->OCC2;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lOccurrenceCounter2 = 0u;
#endif
  return lOccurrenceCounter2;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetOccurrenceCounter2
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter2(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) OccurrenceCounter2
  )
{
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->OCC2 = OccurrenceCounter2;                                                            /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(OccurrenceCounter2)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetOccurrenceCounter3
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter3(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint8 lOccurrenceCounter3;
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  lOccurrenceCounter3 = Dem_MemoryEntry_GetEntry(MemoryEntryId)->OCC3;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lOccurrenceCounter3 = 0u;
#endif
  return lOccurrenceCounter3;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetOccurrenceCounter3
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter3(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) OccurrenceCounter3
  )
{
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->OCC3 = OccurrenceCounter3;                                                            /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(OccurrenceCounter3)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetOccurrenceCounter4
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter4(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint8 lOccurrenceCounter4;
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  lOccurrenceCounter4 = Dem_MemoryEntry_GetEntry(MemoryEntryId)->OCC4;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lOccurrenceCounter4 = 0u;
#endif
  return lOccurrenceCounter4;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetOccurrenceCounter4
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter4(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) OccurrenceCounter4
  )
{
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->OCC4 = OccurrenceCounter4;                                                            /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(OccurrenceCounter4)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetOccurrenceCounter7
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter7(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint8 lOccurrenceCounter7;
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  lOccurrenceCounter7 = Dem_MemoryEntry_GetEntry(MemoryEntryId)->OCC7;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lOccurrenceCounter7 = 0u;
#endif
  return lOccurrenceCounter7;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetOccurrenceCounter7
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter7(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) OccurrenceCounter7
  )
{
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->OCC7 = OccurrenceCounter7;                                                            /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(OccurrenceCounter7)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetStdEnvData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetStdEnvData(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  DataIndex
  )
{
  uint8 lDataElement;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DataIndex)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_DATA_EXTENDED_ENV_DATA == STD_ON)                                                                              /* PRQA S 0883 */ /* MD_DEM_19.15 */
  if (DataIndex < DEM_MEMORYENTRY_EXT_ENV_DATA_SIZE)
  {
    lDataElement = Dem_MemoryEntry_GetEntry(MemoryEntryId)->StdEnvData[DataIndex];
  }
  else
# elif (DEM_CFG_DATA_STANDARD_ENV_DATA == STD_ON)
  if (DataIndex < DEM_MEMORYENTRY_STD_ENV_DATA_SIZE)
  {
    lDataElement = Dem_MemoryEntry_GetEntry(MemoryEntryId)->StdEnvData[DataIndex];
  }
  else
# endif
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
    lDataElement = 0u;
  }
  return lDataElement;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetStdEnvData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetStdEnvData(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  DataIndex,
  CONST(uint8, AUTOMATIC)  DataValue
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DataIndex)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DataValue)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_DATA_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_EXTENDED_ENV_DATA == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (DataIndex >= DEM_MEMORYENTRY_ENV_DATA_SIZE)
  {
    Dem_Error_RunTimeCheckFailed(DEM_MEMORYENTRYIF_IMPLEMENTATION_FILENAME, __LINE__);                                             /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_MemoryEntry_GetEntry(MemoryEntryId)->StdEnvData[DataIndex] = DataValue;                                                  /* SBSW_DEM_WRITE_MEMENTRY_STDENVDATA */
  }
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetSnapshotHeader
 *****************************************************************************/
/*!
  * Internal comment removed.
 *
 *
  */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetSnapshotHeader(                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint8 lSnapshotHeader;
#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
  lSnapshotHeader = Dem_MemoryEntry_GetEntry(MemoryEntryId)->SnapshotHeader;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lSnapshotHeader = 0u;
#endif
  return lSnapshotHeader;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetSnapshotHeader
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetSnapshotHeader(                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) SnapshotHeader
  )
{
#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->SnapshotHeader = SnapshotHeader;                                                      /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SnapshotHeader)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetCombinedDTCSnapshotHeader
 *****************************************************************************/
/*!
  * Internal comment removed.
 *
 *
  */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MemoryEntry_GetCombinedDTCSnapshotHeader(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint32 lCombinedDTCSnapshotHeader;
#if ((DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)\
     && (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)\
     && (DEM_CFG_SUPPORT_SRECS == STD_ON))
  lCombinedDTCSnapshotHeader = Dem_MemoryEntry_GetEntry(MemoryEntryId)->CombinedDTCSnapshotHeader;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lCombinedDTCSnapshotHeader = 0x00U;
#endif
  return lCombinedDTCSnapshotHeader;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetCombinedDTCSnapshotHeader
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetCombinedDTCSnapshotHeader(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint32, AUTOMATIC) CombinedDTCSnapshotHeader
  )
{
#if ((DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)\
     && (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)\
     && (DEM_CFG_SUPPORT_SRECS == STD_ON))
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->CombinedDTCSnapshotHeader = CombinedDTCSnapshotHeader;                                /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CombinedDTCSnapshotHeader)                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetCombinedDTCExtendedHeader
 *****************************************************************************/
/*!
  * Internal comment removed.
 *
 *
  */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MemoryEntry_GetCombinedDTCExtendedHeader(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint32 lCombinedDTCExtendedHeader;
#if ((DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON) && (DEM_CFG_SUPPORT_USER_ERECS == STD_ON))
  lCombinedDTCExtendedHeader = Dem_MemoryEntry_GetEntry(MemoryEntryId)->CombinedDTCExtendedHeader;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lCombinedDTCExtendedHeader = 0u;
#endif
  return lCombinedDTCExtendedHeader;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetCombinedDTCExtendedHeader
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetCombinedDTCExtendedHeader(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint32, AUTOMATIC) CombinedDTCExtendedHeader
  )
{
#if ((DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON) && (DEM_CFG_SUPPORT_USER_ERECS == STD_ON))
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->CombinedDTCExtendedHeader = CombinedDTCExtendedHeader;                                /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CombinedDTCExtendedHeader)                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetExtendedHeader
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetExtendedHeader(                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint8 lExtendedHeader;
#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
  lExtendedHeader = Dem_MemoryEntry_GetEntry(MemoryEntryId)->ExtendedHeader;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lExtendedHeader = 0u;
#endif
  return lExtendedHeader;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetExtendedHeader
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetExtendedHeader(                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) ExtendedHeader
  )
{
#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->ExtendedHeader = ExtendedHeader;                                                      /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ExtendedHeader)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_MemoryEntry_GetSnapshotRecordDataPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetSnapshotRecordDataPtr(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  SRecIndex
  )
{
  Dem_SharedDataPtrType lReturnValue;

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (SRecIndex >= Dem_Cfg_GlobalSRecMaxCount())
  {
    Dem_Error_RunTimeCheckFailed(DEM_MEMORYENTRYIF_IMPLEMENTATION_FILENAME, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = &(Dem_MemoryEntry_GetEntry(MemoryEntryId)->SnapshotData[0][0]);
  }
  else
# endif
  {
    lReturnValue = &(Dem_MemoryEntry_GetEntry(MemoryEntryId)->SnapshotData[SRecIndex][0]);
  }
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_MemoryEntry_GetSnapshotRecordDataConstPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetSnapshotRecordDataConstPtr(                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_SRecIndexType, AUTOMATIC)  SRecIndex
  )
{
  Dem_ConstSharedDataPtrType lReturnValue;

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (SRecIndex >= Dem_Cfg_GlobalSRecMaxCount())
  {
    Dem_Error_RunTimeCheckFailed(DEM_MEMORYENTRYIF_IMPLEMENTATION_FILENAME, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = &(Dem_MemoryEntry_GetEntry(MemoryEntryId)->SnapshotData[0][0]);
  }
  else
# endif
  {
    lReturnValue = &(Dem_MemoryEntry_GetEntry(MemoryEntryId)->SnapshotData[SRecIndex][0]);
  }
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_MemoryEntry_GetExtendedRecordDataPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetExtendedRecordDataPtr(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ERecIndex
  )
{
  Dem_SharedDataPtrType lReturnValue;

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (ERecIndex >= Dem_Cfg_GlobalERecMaxCount())
  {
    Dem_Error_RunTimeCheckFailed(DEM_MEMORYENTRYIF_IMPLEMENTATION_FILENAME, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = &(Dem_MemoryEntry_GetEntry(MemoryEntryId)->ExtendedData[0][0]);
  }
  else
# endif
  {
    lReturnValue = &(Dem_MemoryEntry_GetEntry(MemoryEntryId)->ExtendedData[ERecIndex][0]);
  }
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_MemoryEntry_GetExtendedRecordDataConstPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetExtendedRecordDataConstPtr(                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ERecIndex
  )
{
  Dem_ConstSharedDataPtrType lReturnValue;

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (ERecIndex >= Dem_Cfg_GlobalERecMaxCount())
  {
    Dem_Error_RunTimeCheckFailed(DEM_MEMORYENTRYIF_IMPLEMENTATION_FILENAME, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = &(Dem_MemoryEntry_GetEntry(MemoryEntryId)->ExtendedData[0][0]);
  }
  else
# endif
  {
    lReturnValue = &(Dem_MemoryEntry_GetEntry(MemoryEntryId)->ExtendedData[ERecIndex][0]);
  }
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_MemoryEntry_GetWwhObdFreezeFrameDataPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetWwhObdFreezeFrameDataPtr(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  Dem_SharedDataPtrType lReturnValue;

  lReturnValue = &(Dem_MemoryEntry_GetEntry(MemoryEntryId)->ObdFreezeFrameData[0]);
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON) || (DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_MemoryEntry_GetJ1939FreezeFramePtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetJ1939FreezeFramePtr(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  Dem_SharedDataPtrType lReturnValue;
  lReturnValue = &(Dem_MemoryEntry_GetEntry(MemoryEntryId)->J1939FreezeFrame[0]);
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_MemoryEntry_GetGlobalSnapshotRecordDataPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetGlobalSnapshotRecordDataPtr(                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  Dem_SharedDataPtrType lReturnValue;
  lReturnValue = &(Dem_MemoryEntry_GetEntry(MemoryEntryId)->GlobalSnapshotData[0]);
  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_MemoryEntry_TestGlobalSnapshotRecordStored
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_TestGlobalSnapshotRecordStored(                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  boolean lGlobalSnapshotRecordStored;

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
  lGlobalSnapshotRecordStored = Dem_MemoryEntry_GetEntry(MemoryEntryId)->GlobalSnapshotRecordStored;
#else
  {
    lGlobalSnapshotRecordStored = FALSE;
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }
#endif

  return lGlobalSnapshotRecordStored;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetGlobalSnapshotRecordStored
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetGlobalSnapshotRecordStored(                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(boolean, AUTOMATIC) StoredState
  )
{
#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->GlobalSnapshotRecordStored = StoredState;                                             /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StoredState)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_GetStatusIndicator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_Type, DEM_CODE)
Dem_MemoryEntry_GetStatusIndicator(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId
  )
{
  uint8 lStatusIndicator;

#if (DEM_CFG_SUPPORT_SI30_STATUS == STD_ON)
  lStatusIndicator = Dem_MemoryEntry_GetEntry(MemoryEntryId)->SI30Status;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  lStatusIndicator = 0u;
#endif

  return lStatusIndicator;
}

/* ****************************************************************************
 % Dem_MemoryEntry_SetStatusIndicator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetStatusIndicator(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_StatusIndicator_Type StatusIndicator
  )
{
#if (DEM_CFG_SUPPORT_SI30_STATUS == STD_ON)
  Dem_MemoryEntry_GetEntry(MemoryEntryId)->SI30Status = StatusIndicator;                                                         /* SBSW_DEM_POINTER_WRITE_MEMORYENTRY */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StatusIndicator)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
#endif
}

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
 * \addtogroup Dem_MemoryEntry_Public
 * \{
 */

/* ****************************************************************************
 % Dem_MemoryEntry_TestEntryForEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_TestEntryForEvent(
  uint16 Index, 
  Dem_EventIdType EventId
  )
{
  return (boolean)(Dem_MemoryEntry_GetEventId(Dem_MemoryEntry_GetId((Dem_Cfg_MemoryIndexType)Index)) == EventId);
}

/* ****************************************************************************
 % Dem_MemoryEntry_FreeEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_FreeEntry(
  uint16 Index
  )
{
  Dem_Cfg_MemoryEntryHandleType lMemoryEntryId;
  lMemoryEntryId = Dem_MemoryEntry_GetId((Dem_Cfg_MemoryIndexType)Index);
  Dem_MemoryEntry_SetEventId(lMemoryEntryId, DEM_EVENT_INVALID);
  Dem_MemoryEntry_SetTimestamp(lMemoryEntryId, 0);
}

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_MemoryEntry_TestGlobalSnapshotStored
 *****************************************************************************/
/*!
  * Internal comment removed.
 *
 *
  */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_TestGlobalSnapshotStored(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  return Dem_MemoryEntry_GetEntry(MemoryEntryId)->GlobalSnapshotRecordStored;
}
#endif

/* ****************************************************************************
 % Dem_MemoryEntry_GetOccurrenceCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_MemoryEntry_OccurrenceCounterType, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter(                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
# if (DEM_CFG_DATA_OCCCTR_2BYTE == STD_ON)
    return Dem_MemoryEntry_GetOccurrenceCounter2Byte(MemoryEntryId);
# else
    return Dem_MemoryEntry_GetOccurrenceCounter1Byte(MemoryEntryId);
# endif
}

/* ****************************************************************************
 % Dem_MemoryEntry_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_Init(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  Dem_SharedMemoryEntryPtrType lEntry;
  lEntry = Dem_MemoryEntry_GetEntry(MemoryEntryId);
  Dem_MemCpy((Dem_SharedDataPtrType)lEntry,                                                                                      /* PRQA S 0310, 0311, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_11.8, MD_DEM_20.2 */ /* SBSW_DEM_POINTER_MEMCPY_PRIMARYENTRY */
    (Dem_ConstDataPtrType)(&Dem_Cfg_MemoryEntryInit),
    sizeof(Dem_Cfg_PrimaryEntryType));
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_MemoryEntry_CopyEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_CopyEntry(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  DestinationMemoryEntryId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  SourceMemoryEntryId
  )
{
  Dem_ConstSharedMemoryEntryPtrType lSourceEntry;
  Dem_SharedMemoryEntryPtrType lDestinationEntry;
  lSourceEntry = Dem_MemoryEntry_GetEntry(SourceMemoryEntryId);
  lDestinationEntry = Dem_MemoryEntry_GetEntry(DestinationMemoryEntryId);
  Dem_MemCpy((Dem_SharedDataPtrType)lDestinationEntry,                                                                           /* PRQA S 0310, 0311, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_11.8, MD_DEM_20.2 */ /* SBSW_DEM_POINTER_MEMCPY_PRIMARYENTRY */
             (Dem_ConstSharedDataPtrType)lSourceEntry,
             sizeof(Dem_Cfg_PrimaryEntryType));
}
#endif

#if (DEM_FEATURE_NEED_OCC_COUNTER == STD_ON)
/* ****************************************************************************
 % Dem_MemoryEntry_IncrementOccurrenceCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_IncrementOccurrenceCounter(
  Dem_Cfg_MemoryEntryHandleType  MemoryEntryId
  )
{
  boolean lSuccessfulIncrement;
  Dem_MemoryEntry_OccurrenceCounterType lOccurrenceCounter;
  lSuccessfulIncrement = FALSE;
  lOccurrenceCounter = Dem_MemoryEntry_GetOccurrenceCounter(MemoryEntryId);

  if (lOccurrenceCounter < DEM_DATA_OCCURRENCE_MAX)
  {
    lOccurrenceCounter = (Dem_MemoryEntry_OccurrenceCounterType)(lOccurrenceCounter + 1u);
    Dem_MemoryEntry_SetOccurrenceCounter(MemoryEntryId, lOccurrenceCounter);
    lSuccessfulIncrement = TRUE;
  }
  return lSuccessfulIncrement;
}
#endif

/* ****************************************************************************
 % Dem_MemoryEntry_IncrementFailedCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_IncrementFailedCycleCounter(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  boolean lSuccessfulIncrement;
  lSuccessfulIncrement = FALSE;
#if (DEM_CFG_DATA_FAILED_CYCLES == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF)
  {
    uint8 lCycleCounter;

    lCycleCounter = Dem_MemoryEntry_GetFailedCycleCounter(MemoryEntryId);
    if (lCycleCounter < 0xffU)
    {
      lCycleCounter = (uint8)(lCycleCounter + 1u);
      Dem_MemoryEntry_SetFailedCycleCounter(MemoryEntryId, lCycleCounter);
      lSuccessfulIncrement = TRUE;
    }
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
  return lSuccessfulIncrement;
}

/* ****************************************************************************
 % Dem_MemoryEntry_IncrementConsecutiveFailedCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_IncrementConsecutiveFailedCycleCounter(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  boolean lSuccessfulIncrement;
  lSuccessfulIncrement = FALSE;
#if ( (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) \
   || ((DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF)))
  {
    uint8 lCycleCounter;

    lCycleCounter = Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(MemoryEntryId);
    if (lCycleCounter < 0xffU)
    {
      lCycleCounter = (uint8)(lCycleCounter + 1u);
      Dem_MemoryEntry_SetConsecutiveFailedCycleCounter(MemoryEntryId, lCycleCounter);
      lSuccessfulIncrement = TRUE;
    }
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
  return lSuccessfulIncrement;
}

/* ****************************************************************************
 % Dem_MemoryEntry_InitializeEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemoryEntry_InitializeEntry(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
  Dem_MemoryEntry_SetGlobalSnapshotRecordStored(MemoryEntryId, FALSE);
#endif
#if (DEM_FEATURE_NEED_OCC_COUNTER == STD_ON)
  Dem_MemoryEntry_ResetOccurrenceCounter(MemoryEntryId);
#endif
#if (((DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_OFF)) && (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF))
  Dem_MemoryEntry_SetAgingCounter(MemoryEntryId, DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID);
#endif
#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
  Dem_MemoryEntry_SetExtendedHeader(MemoryEntryId, 0U);
#endif
#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
  Dem_MemoryEntry_SetSnapshotHeader(MemoryEntryId, 0U);
# if ((DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
  Dem_MemoryEntry_SetCombinedDTCSnapshotHeader(MemoryEntryId, 0U);
# endif
#endif
#if ((DEM_CFG_SUPPORT_USER_ERECS == STD_ON) && (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON))
  Dem_MemoryEntry_SetCombinedDTCExtendedHeader(MemoryEntryId, 0U);
#endif
#if (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON)
  Dem_MemoryEntry_SetDebounceValueMax(MemoryEntryId, 0);
#endif
#if ((DEM_CFG_DATA_FAILED_CYCLES == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF))
  Dem_MemoryEntry_SetFailedCycleCounter(MemoryEntryId, 0U);
#endif
#if ( (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) \
   || ((DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) && (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_OFF)))
  Dem_MemoryEntry_SetConsecutiveFailedCycleCounter(MemoryEntryId, 0U);
#endif
#if (DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
  Dem_MemoryEntry_SetCyclesSinceFirstFailed(MemoryEntryId, DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID);
#endif
#if (DEM_CFG_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON)
  Dem_MemoryEntry_SetCyclesSinceLastFailed(MemoryEntryId, DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID);
#endif
#if (DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON)
  Dem_MemoryEntry_SetTestedCyclesSinceFirstFailed(MemoryEntryId, 0U);
#endif
#if (DEM_CFG_DATA_WUC_SINCE_LAST_FAILED == STD_ON)
  Dem_MemoryEntry_SetWarmUpCyclesSinceLastFailed(MemoryEntryId, DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID);
#endif
#if (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON)
  Dem_MemoryEntry_SetState(MemoryEntryId, 0U);
#endif
#if (DEM_CFG_DATA_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_EXTENDED_ENV_DATA == STD_ON)
  {
    uint8 lDataIndex;
    for (lDataIndex = 0u; lDataIndex < DEM_MEMORYENTRY_STD_ENV_DATA_SIZE; lDataIndex++)
    {
      Dem_MemoryEntry_SetStdEnvData(MemoryEntryId, lDataIndex, 0U);
    }
  }
#endif
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
  Dem_MemoryEntry_SetPreConfirmedStatus(MemoryEntryId, DEM_MEMORYENTRY_PC_STATUS_INITIALIZE);
  Dem_MemoryEntry_SetOccurrenceCounter1(MemoryEntryId, 0U);
  Dem_MemoryEntry_SetOccurrenceCounter2(MemoryEntryId, 0U);
  Dem_MemoryEntry_SetOccurrenceCounter3(MemoryEntryId, 0U);
  Dem_MemoryEntry_SetOccurrenceCounter4(MemoryEntryId, 0U);
  Dem_MemoryEntry_SetOccurrenceCounter7(MemoryEntryId, 0U);
#endif
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
  {
    Dem_MemoryEntry_SetAgingTimer(MemoryEntryId, DEM_MEMORYENTRY_AGINGTIME_INVALID);
  }
#endif
  if (Dem_StatusIndicator_isStatusIndicatorEnabled() == TRUE)
  {
    Dem_MemoryEntry_SetStatusIndicator(MemoryEntryId, 0U);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_MemoryEntry_GetId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryEntryHandleType, DEM_CODE)    
Dem_MemoryEntry_GetId(                                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex
  )
{
  Dem_Cfg_MemoryEntryHandleType lReturnValue;
  
  Dem_Internal_AssertReturnValue((BlockIndex < Dem_Cfg_GetSizeOfMemoryBlockIdToMemoryEntryId()),\
                                  DEM_E_INCONSISTENT_STATE, DEM_MEMORYENTRY_HANDLE_INVALID)

  lReturnValue = Dem_Cfg_GetMemoryBlockIdToMemoryEntryId(BlockIndex);

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_MemoryEntry_TestAgingOnlyEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_TestAgingOnlyEntry(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  )
{
  boolean lAgingOnlyEntry;

#if (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)
  if (DEM_MEM_TEST_AGING_ONLY(Dem_MemoryEntry_GetState(MemoryEntryId)) == TRUE)
  {
    lAgingOnlyEntry = TRUE;
  }
  else
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
  {
    lAgingOnlyEntry = FALSE;
  }

  return lAgingOnlyEntry;
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_MEMORYENTRY_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemoryEntry_Implementation.h
 *********************************************************************************************************************/
