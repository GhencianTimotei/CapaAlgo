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
/*! \addtogroup Dem_MemPermanent
 *  \{
 *  \file       Dem_MemPermanent_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file.
 *  \details    Implementation of the Permanent Memory subcomponent which manages storage of permanent DTCs.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMPERMANENT_IMPLEMENTATION_H)
#define DEM_MEMPERMANENT_IMPLEMENTATION_H

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
#include "Dem_MemPermanent_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_Client_Interface.h"
#include "Dem_MemState_Interface.h"
#include "Dem_Core_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_MEMPERMANENT_IMPLEMENTATION_FILENAME "Dem_MemPermanent_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/*! Number of stored entries in confirmed chronology */
DEM_LOCAL VAR(boolean, DEM_VAR_NOINIT)                    Dem_MemPermanent_ConfirmedChronoOverflow;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define DEM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/*! Number of stored entries in confirmed chronology */
DEM_LOCAL VAR(uint16, DEM_VAR_NOINIT)                    Dem_MemPermanent_ConfirmedChronoCurrentCount;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */




/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_MemPermanent_PrivateProperties Private Properties
 * \{
 */


#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologyGetEventId
 *****************************************************************************/
/*!
 * \brief         Get the event Id in confirmed chronology
 *
 * \details       Get the event Id in confirmed chronology
 *
 * \param[in]     ConfirmedChronologyIndex
 *                Index in Dem_Cfg_StatusData.ConfirmedChronology[]
 *
 * \return        EventId
 *                Unique handle of the event.
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyGetEventId(
  CONST(uint16, AUTOMATIC)  ConfirmedChronologyIndex
  );
#endif
#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologySetEventId
 *****************************************************************************/
/*!
 * \brief         Set the event Id in confirmed chronology
 *
 * \details       Set the event Id in confirmed chronology
 *
 * \param[in]     ConfirmedChronologyIndex
 *                Index in Dem_Cfg_StatusData.ConfirmedChronology[]
 * \param[in]     EventId
 *                Unique handle of the event.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologySetEventId(
  CONST(uint16, AUTOMATIC)  ConfirmedChronologyIndex,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif
#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologyGetCurrentSize
 *****************************************************************************/
/*!
 * \brief         Get the number of occupied entries in the confirmed chronology.
 *
 * \details       Get the number of occupied entries in the confirmed chronology.
 *
 *
 * \return        Size
 *                Number of occupied entries in the confirmed chronology.
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyGetCurrentSize(
  void
  );
#endif
#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologySetCurrentSize
 *****************************************************************************/
/*!
 * \brief         Set the number of occupied entries in the confirmed chronology.
 *
 * \details       Set the number of occupied entries in the confirmed chronology.
 *
 * \param[in]     Size
 *                New number of occupied entries in the confirmed chronology.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologySetCurrentSize(
  CONST(uint16, AUTOMATIC)  Size
  );
#endif


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologyGetEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyGetEventId(
  CONST(uint16, AUTOMATIC)  ConfirmedChronologyIndex
  )
{
  return Dem_Cfg_GetStatusData().ConfirmedChronology[ConfirmedChronologyIndex];                                                  /* PRQA S 2841 */ /* MD_DEM_Dir4.1_ReadOperationLoopExit */
}
#endif
#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologySetEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologySetEventId(
  CONST(uint16, AUTOMATIC)  ConfirmedChronologyIndex,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (ConfirmedChronologyIndex >= Dem_Cfg_ConfirmedChronologyMaxCount())
  {
    Dem_Error_RunTimeCheckFailed(DEM_MEMPERMANENT_IMPLEMENTATION_FILENAME, __LINE__);                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_GetStatusData().ConfirmedChronology[ConfirmedChronologyIndex] = EventId;                                             /* SBSW_DEM_ARRAY_WRITE_STATUSDATA_CONFIRMEDCHRONOLOGY */
  }
}
#endif
#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologyGetCurrentSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyGetCurrentSize(void)
{
  return Dem_MemPermanent_ConfirmedChronoCurrentCount;
}
#endif
#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologySetCurrentSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologySetCurrentSize(
  CONST(uint16, AUTOMATIC)  Size
  )
{
  Dem_MemPermanent_ConfirmedChronoCurrentCount = Size;
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
 * \addtogroup Dem_MemPermanent_PublicProperties
 * \{
 */
#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologySetOverflown
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologySetOverflown( 
  void
  )
{
  Dem_MemPermanent_ConfirmedChronoOverflow = TRUE;
}
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologyResetOverflown
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyResetOverflown(
  void
  )
{
  Dem_MemPermanent_ConfirmedChronoOverflow = FALSE;
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
 * \defgroup Dem_MemPermanent_Private Private Methods
 * \{
 */


#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_PermanentFillUpAddEvent
 *****************************************************************************/
/*!
 * \brief         Add an event to the permanent memory.
 *
 * \details       Add an event to the permanent memory. Set the event to 'active '
 *                and 'visible' if it's WIR-bit is qualified.
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemPermanent_PermanentFillUpAddEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_PermanentFillUpFromPrimary
 *****************************************************************************/
/*!
 * \brief         Fills up the permanent memory after healing some entries
 *
 * \details       This function checks for OBD relevant DTCs that currently
 *                trigger the MIL but are not stored in permanent memory. Up to
 *                all empty permanent slots are filled with such events.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_PermanentFillUpFromPrimary(
  void
  );
#endif


#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_PermanentFillUpFromConfirmedChronology
 *****************************************************************************/
/*!
 * \brief         Fill up the permanent memory from entries of the 
 *                confirmed chronology.
 *
 * \details       Fill up the permanent memory from entries of the 
 *                confirmed chronology.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \return        E_OK
 *                The permanent memory is completly filled.
 *
 * \return        E_NOT_OK
 *                The permanent memory is not completly filled.
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_MemPermanent_PermanentFillUpFromConfirmedChronology(
  void
  );
#endif


#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologyEventStored
 *****************************************************************************/
/*!
 * \brief         Test if event is already stored in confirmed chronology.
 *
 * \details       Test if event is already stored in confirmed chronology.
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyEventStored(
  CONST(Dem_EventIdType, AUTOMATIC)  Event
  );
#endif


#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronoFreeEntry
 *****************************************************************************/
/*!
 * \brief         Frees the entry in confirmed chronology at forwarded index position
 *
 * \details       Move all entries that are newer than the entry to delete 
 *                one step forward in the chronology array until the entry
 *                at the forwarded index position is overwritten.
 *
 * \param[in]     ConfirmedChronologyIndex
 *                Index in Dem_Cfg_StatusData.ConfirmedChronology[]
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronoFreeEntry(
  CONST(uint16, AUTOMATIC)  ConfirmedChronologyIndex
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_PermanentFillUpAddEvent
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
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemPermanent_PermanentFillUpAddEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;
  uint8 lPermanentIndex;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PERMANENT);


  lPermanentIndex = Dem_Data_PermanentEntryFind(EventId);
  if (Dem_MemState_MemoryGetMaxSize(lMemoryInfo) == lPermanentIndex)                                                             /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
  {
    uint8 lPermanentState;

    lPermanentIndex = Dem_Data_PermanentEntryFind(DEM_EVENT_INVALID);
    lPermanentState = DEM_ESM_PERMANENT_NONE;

    Dem_Mem_PermanentSetEvent(lPermanentIndex, EventId);
    lPermanentState = DEM_ESM_SET_PERMANENT_STATE(lPermanentState, DEM_ESM_PERMANENT_ACTIVE);

    {
      if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
      {
        /* Only a qualified WIR is immediately visible */
        uint8 lQualifyState;
        lQualifyState = Dem_Event_GetQualifyStatus(EventId);
        if (Dem_EventInternalStatus_Test_QualifyStatus_WIR(lQualifyState) == TRUE)
        {
          lPermanentState = DEM_ESM_SET_PERMANENT_VISIBLE(lPermanentState);
        }
      }
      else
      {
        lPermanentState = DEM_ESM_SET_PERMANENT_VISIBLE(lPermanentState);
      }
    }
    Dem_MemState_MemorySetCurrentSize(lMemoryInfo, Dem_MemState_MemoryGetCurrentSize(lMemoryInfo) + 1u);                          /* SBSW_DEM_CALL_MEMORYINFO_POINTER */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
    Dem_Mem_PermanentSetStatus(lPermanentIndex, lPermanentState);
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_PERMANENT),
      DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
  }
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif 

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_PermanentFillUpFromPrimary
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
Dem_MemPermanent_PermanentFillUpFromPrimary(
  void
  )
{
  Dem_EventIdType lEventId;
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PERMANENT);

  /* scan for events which support the MIL. */
  for (lEventId = Dem_MemState_MemoryGetFirstEvent(lMemoryInfo);                                                                 /* PRQA S 0771 */ /* MD_DEM_15.4_opt */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */ 
       (lEventId <= Dem_MemState_MemoryGetLastEvent(lMemoryInfo));                                                               /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
       ++lEventId)
  {
    /* Only process master events (subevents are handled with the master) */
    if (Dem_Cfg_GetMasterEvent(lEventId) != lEventId)
    {
      continue;                                                                                                                  
    }

    if (Dem_DTC_TestEventStoresPermanentDTC(lEventId) == TRUE)
    {
      if (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() < Dem_Cfg_ConfirmedChronologyMaxCount())
      {
        if (Dem_UDSStatus_Test_CDTC(Dem_DTC_GetDTCStatus(lEventId)) == TRUE)
        { /* Confirmed event found */
          Dem_MemPermanent_ConfirmedChronoAddEvent(lEventId, TRUE);
        }
      }
      else
      {
        if (Dem_MemState_MemoryGetCurrentSize(lMemoryInfo) >= Dem_MemState_MemoryGetMaxSize(lMemoryInfo))                        /* SBSW_DEM_CALL_MEMORYINFO_POINTER */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
        {
          /*Confirmed chronology and permanent memory are full*/
          break;
        }
      }

      if (Dem_MemState_MemoryGetCurrentSize(lMemoryInfo) < Dem_MemState_MemoryGetMaxSize(lMemoryInfo))                           /* SBSW_DEM_CALL_MEMORYINFO_POINTER */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
      {
        if (Dem_DTC_TestStatusForPermanentStorage(lEventId) == TRUE)
        {
          Dem_MemPermanent_PermanentFillUpAddEvent(lEventId);
        }
      }
      else
      {
        if (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() >= Dem_Cfg_ConfirmedChronologyMaxCount())
        {
          /*Confirmed chronology and permanent memory are full*/
          break;
        }
      }
    }
  }
  if (lEventId >  Dem_MemState_MemoryGetLastEvent(lMemoryInfo))                                                                  /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
  {
    /*All primary events have been evaluated*/
    if (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() < Dem_Cfg_ConfirmedChronologyMaxCount())
    {
      /* Chronology has still empty entries - remember confirmed chronology is not overflown*/
      Dem_MemPermanent_ConfirmedChronologyResetOverflown();
    }
  }
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

#endif 

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologyEventStored
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyEventStored(
  CONST(Dem_EventIdType, AUTOMATIC)  Event
  )
{
  boolean lEventStored;
  uint16 lChronoIndex;
  lChronoIndex = 0u;
  lEventStored = FALSE;
  while (lChronoIndex < Dem_MemPermanent_ConfirmedChronologyGetCurrentSize())
  {
    if (Event == Dem_MemPermanent_ConfirmedChronologyGetEventId(lChronoIndex))
    {
      lEventStored = TRUE;
      break;
    }
    lChronoIndex++;
  }
  return lEventStored;
}
#endif 

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_PermanentFillUpFromConfirmedChronology
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_MemPermanent_PermanentFillUpFromConfirmedChronology(void)
{
  Std_ReturnType lReturnValue;
  uint16 lChronoIndex;
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PERMANENT);
  lChronoIndex = 0u;
  lReturnValue = E_NOT_OK;

  while (lChronoIndex < Dem_MemPermanent_ConfirmedChronologyGetCurrentSize())
  {
    Dem_EventIdType lEventCandidate;
    lEventCandidate = Dem_MemPermanent_ConfirmedChronologyGetEventId(lChronoIndex);

    if (Dem_DTC_TestStatusForPermanentStorage(lEventCandidate) == TRUE)
    {
      Dem_MemPermanent_PermanentFillUpAddEvent(lEventCandidate);

      if (Dem_MemState_MemoryGetCurrentSize(lMemoryInfo) >= Dem_MemState_MemoryGetMaxSize(lMemoryInfo))                          /* SBSW_DEM_CALL_MEMORYINFO_POINTER */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
      {
        /* Permanent memory is completely filled up */
        lReturnValue = E_OK;
        break;
      }
    }
    lChronoIndex++;
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif 

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronoFreeEntry
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronoFreeEntry(
  CONST(uint16, AUTOMATIC)  ConfirmedChronologyIndex
  )
{
  Dem_EventIdType lTempEventId;
  uint16 lChronoIterator;

  Dem_Internal_AssertReturnVoid(ConfirmedChronologyIndex < Dem_MemPermanent_ConfirmedChronologyGetCurrentSize(), 
    DEM_E_INCONSISTENT_STATE)

  lChronoIterator = Dem_MemPermanent_ConfirmedChronologyGetCurrentSize();
  --lChronoIterator;
  Dem_MemPermanent_ConfirmedChronologySetCurrentSize(lChronoIterator);

  lTempEventId = Dem_MemPermanent_ConfirmedChronologyGetEventId(lChronoIterator);
  Dem_MemPermanent_ConfirmedChronologySetEventId(lChronoIterator, DEM_EVENT_INVALID);
  while (lChronoIterator != ConfirmedChronologyIndex)
  {
    /* go backwards through the chronological list and move down all entries, until the entry to delete is overwritten */
    Dem_EventIdType lSwap;

    lSwap = lTempEventId;

    --lChronoIterator;
    lTempEventId = Dem_MemPermanent_ConfirmedChronologyGetEventId(lChronoIterator);
    Dem_MemPermanent_ConfirmedChronologySetEventId(lChronoIterator, lSwap);
    Dem_Nvm_SetStatusBlockChanged();
  }
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
 * \addtogroup Dem_MemPermanent_Public
 * \{
 */
#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologyInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyInit(
  void
  )
{
  uint16 lConfirmedChronologyIndex;
  lConfirmedChronologyIndex = Dem_Cfg_ConfirmedChronologyMaxCount();
  while (lConfirmedChronologyIndex != 0u)
  {
    lConfirmedChronologyIndex--;
    Dem_MemPermanent_ConfirmedChronologySetEventId(lConfirmedChronologyIndex, DEM_EVENT_INVALID);
  }
  /* Initiliaze with worst case sceanrio */
  Dem_MemPermanent_ConfirmedChronoOverflow = FALSE;
}
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologyRestore
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
Dem_MemPermanent_ConfirmedChronologyRestore(void)
{
  uint16 lConfirmedChronoIndex;
  Dem_EventIdType lEventId;
  Dem_MemState_MemoryInfoPtrType lMemoryInfo; 

  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PERMANENT);

  /*Initialize current size of chronology*/
  Dem_MemPermanent_ConfirmedChronologySetCurrentSize(0);
  

  /*Start at the end of the chronology array*/
  lConfirmedChronoIndex = Dem_Cfg_ConfirmedChronologyMaxCount();
  while (lConfirmedChronoIndex != 0u)
  {
    --lConfirmedChronoIndex;
    lEventId = Dem_MemPermanent_ConfirmedChronologyGetEventId(lConfirmedChronoIndex);

    if (lEventId != DEM_EVENT_INVALID)
    {
      if (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() == 0u)
      {
        Dem_MemPermanent_ConfirmedChronologySetCurrentSize(lConfirmedChronoIndex + 1u);
      }

      if ( (Dem_Cfg_GetMasterEvent(lEventId) != lEventId)                                                                        /* COV_DEM_GENERATED_EVENTID */
        || (lMemoryInfo->FirstEvent > lEventId)
        || (lMemoryInfo->LastEvent < lEventId) )
      {
        /*The configuration has changed somehow, event no longer belongs to primary memory - remove entry */
        Dem_MemPermanent_ConfirmedChronoFreeEntry(lConfirmedChronoIndex);
      }
      else
      {
        if (Dem_UDSStatus_Test_CDTC(Dem_DTC_GetDTCStatus(lEventId)) == FALSE)
        {
          /*Confirmed bit no longer set - remove entry */
          Dem_MemPermanent_ConfirmedChronoFreeEntry(lConfirmedChronoIndex);
        }
      }
    }
    else
    {
      if (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() != 0u)
      {
        /*There is an empty entry in the chronology although we already found a newer event -> fix chronology by clearing this entry*/
        Dem_MemPermanent_ConfirmedChronoFreeEntry(lConfirmedChronoIndex);
      }
    }
  } /*End while*/
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronoFreeEvent
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronoFreeEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_EventIdType lTempEventId;
  Dem_EventIdType lSwap;
  uint16 lChronoIterator;
  boolean lEventFound;
  lEventFound = FALSE;

  lChronoIterator = 0u;
  lTempEventId = Dem_MemPermanent_ConfirmedChronologyGetEventId(lChronoIterator);

  if (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() > 1u)
  {
    /* Go forwards through the chronological list and search for the event to free.
    If found shift all entries one entry backwards beginning at the entry to free  */
    do
    {
      lSwap = Dem_MemPermanent_ConfirmedChronologyGetEventId(lChronoIterator + 1u);
      if ((lTempEventId == EventId) || (lEventFound == TRUE))
      {
        lEventFound = TRUE;
        Dem_MemPermanent_ConfirmedChronologySetEventId(lChronoIterator, lSwap);
      }
      lTempEventId = lSwap;
      ++lChronoIterator;
    }
    while (lChronoIterator < (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() - 1u));
    
    if ((lSwap == EventId) || (lEventFound == TRUE))
    {
      /* Free last entry */
      Dem_MemPermanent_ConfirmedChronologySetEventId(lChronoIterator, DEM_EVENT_INVALID);
      if (lEventFound == FALSE)
      {
        lEventFound = TRUE;
      }
    }
  }
  else
  {
    if (lTempEventId == EventId)
    {
     /* Just free the one existing entry */
      lEventFound = TRUE;
      Dem_MemPermanent_ConfirmedChronologySetEventId(lChronoIterator, DEM_EVENT_INVALID);
    }
  }

  if (lEventFound == TRUE)
  {
    if (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() > 0u)
    {
      Dem_MemPermanent_ConfirmedChronologySetCurrentSize(Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() - 1u);
    }
    else
    {
      Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */
    }
  }

}
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronoAddEvent
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronoAddEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  ConfirmedEvent,
  CONST(boolean, AUTOMATIC) SearchExistingEvent
  )
{
  uint16 lChronoIndex;
  boolean lEventStored;

  lEventStored = FALSE;
  if (SearchExistingEvent == TRUE)
  {
    lEventStored = Dem_MemPermanent_ConfirmedChronologyEventStored(ConfirmedEvent);
  }

  if (lEventStored == FALSE)
  {
    lChronoIndex = Dem_MemPermanent_ConfirmedChronologyGetCurrentSize();
    if (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() < Dem_Cfg_ConfirmedChronologyMaxCount())
    {
      Dem_MemPermanent_ConfirmedChronologySetCurrentSize(lChronoIndex + 1u);
      Dem_MemPermanent_ConfirmedChronologySetEventId(lChronoIndex, ConfirmedEvent);
      Dem_Nvm_SetStatusBlockChanged();
    }
    else
    {
      /*Confirmed chronology overflow -> Configuration error: Size of confirmed chronology is too small*/
      Dem_MemPermanent_ConfirmedChronoOverflow = TRUE;
    }
  }
}
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_FillUp
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
Dem_MemPermanent_FillUp(
  void
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;
  Std_ReturnType lReturnValue;
  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PERMANENT);

  if (Dem_MemState_MemoryGetCurrentSize(lMemoryInfo) < Dem_MemState_MemoryGetMaxSize(lMemoryInfo))                               /* SBSW_DEM_CALL_MEMORYINFO_POINTER */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
  {
    lReturnValue = Dem_MemPermanent_PermanentFillUpFromConfirmedChronology();

    if ((lReturnValue == E_NOT_OK) && (Dem_MemPermanent_ConfirmedChronoOverflow == TRUE))
    {
      Dem_MemPermanent_PermanentFillUpFromPrimary();
    }
  }
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_FEATURE_NEED_PERMANENT_FOR_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_SetB1PermanentDTCsActive
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
Dem_MemPermanent_SetB1PermanentDTCsActive(
  void
  )
{
  uint8 lPermanentIndex;
  uint8 lWwhObdDtcClass;
  boolean lEntryChanged;
  Dem_EventIdType lMasterEventId;
  lEntryChanged = FALSE;

  for (lPermanentIndex = 0u; lPermanentIndex < Dem_Cfg_GlobalPermanentMaxCount(); ++lPermanentIndex)
  {
    lMasterEventId = Dem_Mem_PermanentGetEvent(lPermanentIndex);
    if (lMasterEventId != DEM_EVENT_INVALID)
    {
      if ((DEM_ESM_GET_PERMANENT_STATE(Dem_Mem_PermanentGetStatus(lPermanentIndex)) == DEM_ESM_PERMANENT_PASSIVE))
      {
        lWwhObdDtcClass = Dem_Util_SeverityWwhObdDtcClass(Dem_Cfg_EventSeverity(lMasterEventId));
        if ( (lWwhObdDtcClass == DEM_ESM_WWHOBD_DTCCLASS_B1)
           && (Dem_EventInternalStatus_Test_QualifyStatus_CDTC(Dem_DTC_GetQualifyStatus(lMasterEventId)) == TRUE)                
           && (Dem_UDSStatus_Test_TF(Dem_DTC_GetDTCStatus(lMasterEventId)) == TRUE) )                                            
        {
          uint8 lPermanentState;
          lPermanentState = Dem_Mem_PermanentGetStatus(lPermanentIndex);
          lPermanentState = DEM_ESM_SET_PERMANENT_STATE(lPermanentState, DEM_ESM_PERMANENT_ACTIVE);

          Dem_Mem_PermanentSetStatus(lPermanentIndex, lPermanentState);
          lEntryChanged = TRUE;
        }
      }
    }
  }
  if (lEntryChanged == TRUE)
  {
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_PERMANENT),
      DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

# if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PERMANENTDTC_IMMEDIATE_VISIBLE == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_UpdateEntryVisibility
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_UpdateEntryVisibility(
 CONST(Dem_EventIdType, AUTOMATIC)  EventId
 )
{
  uint8 lPermanentIndex;
  uint8 lPermanentState;
  Dem_EventIdType lMasterEventId;

  lMasterEventId = Dem_Cfg_GetMasterEvent(EventId);

  /* scan through the permanent memory if the given event is available */
  lPermanentIndex = Dem_Data_PermanentEntryFind(lMasterEventId);
  if (lPermanentIndex != Dem_Cfg_GlobalPermanentMaxCount())
  {
    lPermanentState = Dem_Mem_PermanentGetStatus(lPermanentIndex);
    if (DEM_ESM_TEST_PERMANENT_VISIBLE(lPermanentState) == FALSE)
    {
      lPermanentState = DEM_ESM_SET_PERMANENT_VISIBLE(lPermanentState);
      Dem_Mem_PermanentSetStatus(lPermanentIndex, lPermanentState);

      /* persist status change in NVM */
      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_PERMANENT),
        DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
    }
  }
}
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_TestEntryForEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemPermanent_TestEntryForEvent(
  uint16 Index, 
  Dem_EventIdType EventId
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Index)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return FALSE;
}
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_FreeEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_FreeEntry(
  uint16 Index
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Index)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */
}
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_MEMPERMANENT_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemPermanent_Implementation.h
 *********************************************************************************************************************/
