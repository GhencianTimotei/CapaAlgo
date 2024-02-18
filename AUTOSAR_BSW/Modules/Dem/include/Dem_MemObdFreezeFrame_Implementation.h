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
/*! \addtogroup Dem_MemObdFreezeFrame
 *  \{
 *  \file       Dem_MemObdFreezeFrame_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of the Obd Freeze Frame Memory subcomponent which manages storage and erasing of the 
 *              legislative Obd Freeze Frame
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMOBDFREEZEFRAME_IMPLEMENTATION_H)
#define DEM_MEMOBDFREEZEFRAME_IMPLEMENTATION_H

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
#include "Dem_MemObdFreezeFrame_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_MemoryIF_Interface.h"
#include "Dem_MemState_Interface.h"
#include "Dem_MemoryEntry_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_MEMOBDFREEZEFRAME_IMPLEMENTATION_FILENAME "Dem_MemObdFreezeFrame_Implementation.h"

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
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_MemObdFreezeFrame_PrivateProperties Private Properties
 * \{
 */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
/* ****************************************************************************
 * Dem_MemObdFreezeFrame_FreezeFrameGetVisibility
 *****************************************************************************/
/*!
 * \brief         Get the state of the visibility flag of the freeze frame at
 *                position 'Index'.
 *
 * \details       Get the state of the visibility flag of the freeze frame at
 *                position 'Index'.
 *
 * \param[in]     Index
 *                Index of the freeze frame
 *
 * \return        The visibility flag of the freeze frame
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *                && DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameGetVisibility(
  CONST(uint8, AUTOMATIC)  Index
  );
#endif
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemObdFreezeFrame_FreezeFrameSetVisibility
 *****************************************************************************/
/*!
 * \brief         Set the state of the visibility flag of the freeze frame at
 *                position 'Index'.
 *
 * \details       Set the state of the visibility flag of the freeze frame at
 *                position 'Index'.
 *
 * \param[in]     Index
 *                Index of the freeze frame
 * \param[in]     Visible
 *                TRUE: Set the visibility flag of the freeze frame entry
 *                FALSE: Reset the visibility flag of the freeze frame entry
 *
 * \return        The stored EventId of the freeze frame
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameSetVisibility(
  CONST(uint8, AUTOMATIC)  Index,
  CONST(boolean, AUTOMATIC)  Visible
  );  
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
/* ****************************************************************************
 % Dem_MemObdFreezeFrame_FreezeFrameGetVisibility
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameGetVisibility(
  CONST(uint8, AUTOMATIC)  Index
  )
{
  return Dem_Cfg_FreezeFrameData[Index].IsVisible;
}
#endif
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemObdFreezeFrame_FreezeFrameSetVisibility
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameSetVisibility(
  CONST(uint8, AUTOMATIC)  Index,
  CONST(boolean, AUTOMATIC)  Visible
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (Index >= Dem_Cfg_GlobalObdIIFFCount())
  {
    Dem_Error_RunTimeCheckFailed(DEM_MEMOBDFREEZEFRAME_IMPLEMENTATION_FILENAME, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_FreezeFrameData[Index].IsVisible = Visible;                                                                          /* SBSW_DEM_ARRAY_WRITE_FREEZEFRAMEDATA */
  }
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
 * \defgroup Dem_MemObdFreezeFrame_Private Private Methods
 * \{
 */


#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemObdFreezeFrame_SelectNewestLowPrioFF
 *****************************************************************************/
/*!
 * \brief         Selects the index of the newest Obd freeze frame with low prio 
 *                readiness group
 *
 * \details       If there are multiple low prio Obd freeze frames stored 
 *                select the one with most recent timestamp
 *
 * \param[in]     SelectVisible
 *                TRUE:  Select newest low prio visible freeze frame
 *                FALSE: Select newest low prio invisible freeze frame
 *
 * \return        Freeze Frame Index of the event if found, otherwise
 *                Dem_Cfg_GlobalObdIIFFCount()
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemObdFreezeFrame_SelectNewestLowPrioFF(
  CONST(boolean, AUTOMATIC)  SelectVisible
  );
#endif


#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
/* ****************************************************************************
 * Dem_MemObdFreezeFrame_SelectOldestHighPrioFF
 *****************************************************************************/
/*!
 * \brief         Selects the index of the oldest Obd freeze frame with high
 *                prio readiness group
 *
 * \details       If there are multiple high prio Obd freeze frames stored
 *                select the one with oldest timestamp
 *
 * \param[in]     SelectVisible
 *                TRUE:  Select oldest high prio visible freeze frame
 *                FALSE: Select oldest high prio invisible freeze frame
 *
 * \return        Freeze Frame Index of the event if found, otherwise
 *                Dem_Cfg_GlobalObdIIFFCount()
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemObdFreezeFrame_SelectOldestHighPrioFF(
  CONST(boolean, AUTOMATIC)  SelectVisible
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
/* ****************************************************************************
 * Dem_MemObdFreezeFrame_FindDisplaceableInvisibleFreezeFrameForVisibleEvent
 *****************************************************************************/
/*!
 * \brief         Selects a displaceable Obd Freeze Frame entry for the freeze
 *                frame of an immediately visible event.
 *                Determines, if freeze frame visbility must be updated.
 *
 * \details       This function checks, if the freeze frame of a visible event
 *                is allowed to displace an invisible freeze frame related to 
 *                a non-misfire and non-fuel system event.
 *                It also determines, if an invisible freeze frame related to
 *                a misfire or fuel system event must be made visible
 *                immediately.
 *
 * \param[out]    SetHighPrioFFVisibleBeforeDcyQualified
 *                TRUE: invisible freeze frame related to a misfire or fuel
 *                system event must be set visible before DCY qualification
 *                FALSE: no visibility change required
 *
 * \return        Index of the displaceable entry. If no index is found, the
 *                number of configured freeze frames will be returned.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON &&
 *                DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON &&
 *                DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemObdFreezeFrame_FindDisplaceableInvisibleFreezeFrameForVisibleEvent(
  CONSTP2VAR(boolean, AUTOMATIC, AUTOMATIC) SetHighPrioFFVisibleBeforeDcyQualified
  );
#endif


#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemObdFreezeFrame_GetEventOfObdFF
 *****************************************************************************/
/*!
 * \brief         Get the stored EventId of the freeze frame at position
 *                'Index'.
 *
 * \details       If the given slot is occupied, returns the event Id
 *                otherwise returns the invalid event Id
 *
 * \param[in]     Index
 *                Index of the freeze frame
 *
 * \return        The stored EventId of the freeze frame
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemObdFreezeFrame_GetEventOfObdFF(
  CONST(uint8, AUTOMATIC)  Index
  );
#endif


#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemObdFreezeFrame_FreezeFrameTestVisible
 *****************************************************************************/
/*!
 * \brief         Tests whether a given freeze frame slot contains a visible
 *                freeze frame
 *
 * \details       Tests whether a given freeze frame slot contains a visible
 *                freeze frame
 *
 * \param[in]     Index
 *                Index of the freeze frame
 * \return        TRUE: Freeze frame stored at index is visible
 *                FALSE: Freeze frame stored at index is not visible
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameTestVisible(
  CONST(uint8, AUTOMATIC) Index
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemObdFreezeFrame_SelectNewestLowPrioFF
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemObdFreezeFrame_SelectNewestLowPrioFF(
  CONST(boolean, AUTOMATIC)  SelectVisible
  )
{
  uint8 lBestCandidate;
  uint8 lFreezeFrameIndex;
  uint32 lHighestTimestamp;

  lBestCandidate = Dem_Cfg_GlobalObdIIFFCount();
  lFreezeFrameIndex = Dem_Cfg_GlobalObdIIFFCount();
  lHighestTimestamp = 0u;


  while (lFreezeFrameIndex != 0U)
  {
    Dem_EventIdType lEventId;

    lFreezeFrameIndex--;
    lEventId = Dem_MemObdFreezeFrame_GetEventOfObdFF(lFreezeFrameIndex);

    if (Dem_MemObdFreezeFrame_FreezeFrameTestVisible(lFreezeFrameIndex) == SelectVisible)
    {
      if ((Dem_Event_TestHighPriorReadinessGroup(lEventId) == FALSE)
        && (Dem_Mem_FreezeFrameGetTimestamp(lFreezeFrameIndex) > lHighestTimestamp))                                             
      {
        lBestCandidate = lFreezeFrameIndex;
        lHighestTimestamp = Dem_Mem_FreezeFrameGetTimestamp(lFreezeFrameIndex);
      }
      else
      {
        /* no candidate found, lBestCandidate is still Dem_Cfg_GlobalObdIIFFCount()*/
      }
    }
  }
  return lBestCandidate;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
/* ****************************************************************************
% Dem_MemObdFreezeFrame_SelectOldestHighPrioFF
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemObdFreezeFrame_SelectOldestHighPrioFF(
  CONST(boolean, AUTOMATIC)  SelectVisible
  )
{
  uint8 lBestCandidate;
  uint8 lFreezeFrameIndex;
  uint32 lLowestTimestamp;

  lBestCandidate = Dem_Cfg_GlobalObdIIFFCount();
  lFreezeFrameIndex = Dem_Cfg_GlobalObdIIFFCount();
  lLowestTimestamp = 0xFFFFFFFFU;


  while (lFreezeFrameIndex != 0U)
  {
    Dem_EventIdType lEventId;

    lFreezeFrameIndex--;
    lEventId = Dem_MemObdFreezeFrame_GetEventOfObdFF(lFreezeFrameIndex);

    if (Dem_MemObdFreezeFrame_FreezeFrameTestVisible(lFreezeFrameIndex) == SelectVisible)
    {
      if ((Dem_Event_TestHighPriorReadinessGroup(lEventId) == TRUE)
        && (Dem_Mem_FreezeFrameGetTimestamp(lFreezeFrameIndex) < lLowestTimestamp))                                             
      {
        lBestCandidate = lFreezeFrameIndex;
        lLowestTimestamp = Dem_Mem_FreezeFrameGetTimestamp(lFreezeFrameIndex);
      }
      else
      {
        /* no candidate found, lBestCandidate is still Dem_Cfg_GlobalObdIIFFCount()*/
      }
    }
  }
  return lBestCandidate;
}
#endif
#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
/* ****************************************************************************
% Dem_MemObdFreezeFrame_FindDisplaceableInvisibleFreezeFrameForVisibleEvent
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemObdFreezeFrame_FindDisplaceableInvisibleFreezeFrameForVisibleEvent(
  CONSTP2VAR(boolean, AUTOMATIC, AUTOMATIC) SetHighPrioFFVisibleBeforeDcyQualified
  )
{
  uint8 lSelectedIndex;
  lSelectedIndex = Dem_Cfg_GlobalObdIIFFCount();

  if (Dem_Mem_IsFreezeFrameVisibleInMode02() == FALSE)
  {
    lSelectedIndex = Dem_MemObdFreezeFrame_SelectNewestLowPrioFF(FALSE);
    if (lSelectedIndex == Dem_Cfg_GlobalObdIIFFCount())
    {
      *SetHighPrioFFVisibleBeforeDcyQualified = TRUE;                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }

  return lSelectedIndex;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemObdFreezeFrame_GetEventOfObdFF
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemObdFreezeFrame_GetEventOfObdFF(
CONST(uint8, AUTOMATIC)  Index
)
{
  Dem_EventIdType lEventId;
  if (Index < Dem_Cfg_GlobalObdIIFFCount())
  {
    lEventId = Dem_Cfg_FreezeFrameData[Index].EventId;                                                                           /* PRQA S 2841 */ /* MD_DEM_Dir4.1_ReadOperation */
  }
  else
  {
    lEventId = DEM_EVENT_INVALID;
  }
  return lEventId;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemObdFreezeFrame_FreezeFrameTestVisible
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameTestVisible(
  CONST(uint8, AUTOMATIC) Index
  )
{
  boolean IsFFVisible;
# if (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
  IsFFVisible = Dem_MemObdFreezeFrame_FreezeFrameGetVisibility(Index);
#else
  IsFFVisible = TRUE;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Index);                                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
  return IsFFVisible;
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
 * \addtogroup Dem_MemObdFreezeFrame_Public
 * \{
 */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
% Dem_MemObdFreezeFrame_SelectFFDisplaceIndex
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
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemObdFreezeFrame_SelectFFDisplaceIndex(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  DisplacePendingFreezeFrame,
  CONSTP2VAR(boolean, AUTOMATIC, AUTOMATIC) SetHighPrioFFVisibleBeforeDcyQualified                                               /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_8.13_fp */
  )
{
  uint8 lBestCandidate;
# if (DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME == STD_ON)
  boolean lReplaceMisfireOrFuelSys;
#endif
  lBestCandidate = Dem_Cfg_GlobalObdIIFFCount();
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DisplacePendingFreezeFrame);                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SetHighPrioFFVisibleBeforeDcyQualified);                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  if (Dem_Event_TestHighPriorReadinessGroup(EventId) == TRUE)
  {
    lBestCandidate = Dem_MemObdFreezeFrame_SelectNewestLowPrioFF(FALSE);
    if (lBestCandidate == Dem_Cfg_GlobalObdIIFFCount())
    {
      lBestCandidate = Dem_MemObdFreezeFrame_SelectNewestLowPrioFF(TRUE);
# if (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
      if ((lBestCandidate != Dem_Cfg_GlobalObdIIFFCount())
        && (DEM_OPERATIONCYCLE_TEST_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()) == FALSE))                             
      {
        *SetHighPrioFFVisibleBeforeDcyQualified = TRUE;                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
#endif
    }
# if (DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME == STD_ON)
    lReplaceMisfireOrFuelSys = TRUE;
#endif
  }
# if (DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME == STD_ON)
  else
  {
    lReplaceMisfireOrFuelSys = FALSE;
  }
  if ( (lBestCandidate == Dem_Cfg_GlobalObdIIFFCount())
    && (DisplacePendingFreezeFrame == TRUE)
    )
  {
    /* All OBD freeze frame slots occupied by high prio monitors */
    lBestCandidate = Dem_Mem_FindDisplaceablePendingFreezeFrame(lReplaceMisfireOrFuelSys);
  }
#endif
# if (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
  if( ( lBestCandidate == Dem_Cfg_GlobalObdIIFFCount())
    && (Dem_Event_TestObdVisibilityDelayed(EventId) == FALSE))
  {
    lBestCandidate = Dem_MemObdFreezeFrame_FindDisplaceableInvisibleFreezeFrameForVisibleEvent(SetHighPrioFFVisibleBeforeDcyQualified);  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
#endif

  return lBestCandidate;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame
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
Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame(
  void
  )
{

  uint8 lBestCandidate;
  uint8 lFreezeFrameIndex;
  uint32 lLowestTimestamp;

  lBestCandidate = Dem_Cfg_GlobalObdIIFFCount();
  lLowestTimestamp = 0xFFFFFFFFU;

  for (lFreezeFrameIndex = 0u; lFreezeFrameIndex < Dem_Cfg_GlobalObdIIFFCount(); lFreezeFrameIndex++)
  {
    if (Dem_MemObdFreezeFrame_GetEventOfObdFF(lFreezeFrameIndex) == DEM_EVENT_INVALID)
    { /* Freeze Frame slot not in use, continue with next slot */
      continue;                                                                                                                  
    }

    if (Dem_MemObdFreezeFrame_FreezeFrameTestVisible(lFreezeFrameIndex) == FALSE)
    { /* Freeze Frame not visible, continue with next slot */
      continue;                                                                                                                  
    }

    if (Dem_Cfg_EventObdRelated(Dem_MemObdFreezeFrame_GetEventOfObdFF(lFreezeFrameIndex)) == FALSE)
    { /* Event of stored Freeze Frame is not OBD related (anymore), continue with next slot */
      continue;                                                                                                                  
    }

    if (Dem_Event_TestHighPriorReadinessGroup(Dem_MemObdFreezeFrame_GetEventOfObdFF(lFreezeFrameIndex)) == TRUE)
    {
      if ((Dem_Event_TestHighPriorReadinessGroup(Dem_MemObdFreezeFrame_GetEventOfObdFF(lBestCandidate)) == FALSE)
        || (Dem_Mem_FreezeFrameGetTimestamp(lFreezeFrameIndex) < lLowestTimestamp))                                              
      {/* current candidate has higher prio readiness group than best candidate
          or has same prio readiness group but is older than best candidate or 
          best candidate is not set yet -> set new best candidate and continue 
          with next slot */
        lBestCandidate = lFreezeFrameIndex;
        lLowestTimestamp = Dem_Mem_FreezeFrameGetTimestamp(lBestCandidate);
      }
    }
    /* Best candidate has low prio readiness group or is not set yet */
    else if (Dem_Event_TestHighPriorReadinessGroup(Dem_MemObdFreezeFrame_GetEventOfObdFF(lBestCandidate)) == FALSE)
    {
      if (Dem_Mem_FreezeFrameGetTimestamp(lFreezeFrameIndex) < lLowestTimestamp)
      { /* current and best candidate have the same priority so if timestamp of current index is older than best candidate-> set new best candidate and continue with next slot */
        lBestCandidate = lFreezeFrameIndex;
        lLowestTimestamp = Dem_Mem_FreezeFrameGetTimestamp(lBestCandidate);
      }
    }
    else
    {
      /* no candidate found, lBestCandidate is still Dem_Cfg_GlobalObdIIFFCount()*/
    }
  }

  return lBestCandidate;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemObdFreezeFrame_FreezeFrameSetVisible
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameSetVisible(
  CONST(uint8, AUTOMATIC)  Index
  )
{
  Dem_MemObdFreezeFrame_FreezeFrameSetVisibility(Index, TRUE);
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemObdFreezeFrame_FreezeFrameResetVisible
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameResetVisible(
  CONST(uint8, AUTOMATIC)  Index
  )
{
  Dem_MemObdFreezeFrame_FreezeFrameSetVisibility(Index, FALSE);
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemObdFreezeFrame_FreezeFrameFreeEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameFreeEntry(
  CONST(uint8, AUTOMATIC) Index
  )
{
  Dem_Mem_FreezeFrameSetEvent(Index, DEM_EVENT_INVALID);
}
#endif

#if ((DEM_CFG_SUPPORT_OBDII == STD_ON) \
  && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON))
/* ****************************************************************************
 % Dem_MemObdFreezeFrame_SetFFOfEventVisible
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_SetFFOfEventVisible(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  )
{
  uint8 lFreezeFrameIndex;
  Dem_EventIdType lMemoryRepresentativeEvent;

  lFreezeFrameIndex = Dem_Cfg_GlobalObdIIFFCount();
  lMemoryRepresentativeEvent = Dem_Cfg_GetMemoryRepresentative(EventId);

  while (lFreezeFrameIndex != 0U)
  {
    lFreezeFrameIndex--;

    if (Dem_MemObdFreezeFrame_GetEventOfObdFF(lFreezeFrameIndex) == lMemoryRepresentativeEvent)
    {
      Dem_MemObdFreezeFrame_FreezeFrameSetVisible(lFreezeFrameIndex);
    }
  }
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON)
/* ****************************************************************************
% Dem_MemObdFreezeFrame_SetOldestHighPrioFreezeFrameVisible
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
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemObdFreezeFrame_SetOldestHighPrioFreezeFrameVisible(
void
)
{
  Dem_EventIdType lEventId;
  uint8 lFreezeFrameIndex;

  lEventId = DEM_EVENT_INVALID;
  lFreezeFrameIndex = Dem_MemObdFreezeFrame_SelectOldestHighPrioFF(FALSE);

  if (lFreezeFrameIndex != Dem_Cfg_GlobalObdIIFFCount())
  {
    lEventId = Dem_MemObdFreezeFrame_GetEventOfObdFF(lFreezeFrameIndex);
    if (lEventId != DEM_EVENT_INVALID)
    {
      Dem_MemObdFreezeFrame_FreezeFrameSetVisible(lFreezeFrameIndex);
    }
  }

  return lEventId;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemObdFreezeFrame_IsFreezeFrameStorageValid
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemObdFreezeFrame_IsFreezeFrameStorageValid(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  )
{
  Dem_DTC_UDSStatusType lDTCStatus;
  boolean lIsFreezeFrameStorageValid;

  lIsFreezeFrameStorageValid = TRUE;
  lDTCStatus = Dem_DTC_RetrieveStatus(EventId);

  if ((Dem_UDSStatus_Test_CDTC(lDTCStatus) == FALSE)
# if (DEM_CFG_SUPPORT_PENDING_STORAGE_FREEZE_FRAME == STD_ON)
      && (Dem_UDSStatus_Test_PDTC(lDTCStatus) == FALSE)                                                                          
# endif
     )
  {
    lIsFreezeFrameStorageValid = FALSE;
  }
    
  return lIsFreezeFrameStorageValid;
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_MEMOBDFREEZEFRAME_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemObdFreezeFrame_Implementation.h
 *********************************************************************************************************************/
