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
 *  \defgroup   Dem_MemObdFreezeFrame Dem_MemObdFreezeFrame
 *  \{
 *  \file       Dem_MemObdFreezeFrame_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Interface of the Obd Freeze Frame Memory subcomponent which manages storage and erasing of the 
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

#if !defined (DEM_MEMOBDFREEZEFRAME_INTERFACE_H)
#define DEM_MEMOBDFREEZEFRAME_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemObdFreezeFrame_Types.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_MemObdFreezeFrame_Public Public Methods
 * \{
 */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemObdFreezeFrame_SelectFFDisplaceIndex
 *****************************************************************************/
/*!
 * \brief         Selects Obd freeze frame index for displacement.
 *                Determines, if freeze frame visbility must be updated
 *
 * \details       Selects lowest prior Obd freeze frame index for displacement.
 *                It also determines, if an invisible freeze frame related to a
 *                misfire or fuel system event must be made visible immediately.
 *                If no less prior entry than Event Id is found,
 *                an invalid index is returned.
 *
 * \param[in]     EventId
 *                EventId of the freeze frame that needs to be stored
 * \param[in]     DisplacePendingFreezeFrame
 *                TRUE: trigger and configuration for displacing a pending 
 *                      freeze frame is given
 *                FALSE: displacing pending freeze frames with confirmed is
 *                       either excluded by configuration or the trigger is not
 *                       confirmed
 * \param[out]    SetHighPrioFFVisibleBeforeDcyQualified
 *                TRUE: invisible freeze frame related to a misfire or fuel
 *                      system event must be set visible before DCY
 *                      qualification
 *                FALSE: no visibility change required
 *
 * \return        Index of the freeze frame to displace if found, otherwise
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
Dem_MemObdFreezeFrame_SelectFFDisplaceIndex(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  DisplacePendingFreezeFrame,
  CONSTP2VAR(boolean, AUTOMATIC, AUTOMATIC) SetHighPrioFFVisibleBeforeDcyQualified
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Selects the freeze frame to be reported in Obd mode 02
 *
 * \details       Selects the oldest freeze frame of a misfire or fuel system 
 *                monitor if available, otherwise selects the oldest visible 
 *                freeze frame
 *
 * \return        Index of the freeze frame to display in mode 02, if no 
 *                candidate is found, return Dem_Cfg_GlobalObdIIFFCount()
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemObdFreezeFrame_FreezeFrameSetVisible
 *****************************************************************************/
/*!
 * \brief         Marks a given freeze frame slot as visible
 *
 * \details       Marks a given freeze frame slot as visible
 *
 * \param[in]     Index
 *                Index of the freeze frame
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameSetVisible(
CONST(uint8, AUTOMATIC)  Index
);  
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemObdFreezeFrame_FreezeFrameResetVisible
 *****************************************************************************/
/*!
 * \brief         Marks a given freeze frame slot as not visible
 *
 * \details       Marks a given freeze frame slot as not visible
 *
 * \param[in]     Index
 *                Index of the freeze frame
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameResetVisible(
  CONST(uint8, AUTOMATIC)  Index
  );  
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemObdFreezeFrame_FreezeFrameFreeEntry
 *****************************************************************************/
/*!
 * \brief         Marks freeze frame entry as unused
 *
 * \details       Reset eventId of a freeze frame entry
 *
 * \param[in]     Index
 *                Index of the freeze frame
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameFreeEntry(
  CONST(uint8, AUTOMATIC) Index
  );  
#endif

#if ((DEM_CFG_SUPPORT_OBDII == STD_ON) \
  && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON))
/* ****************************************************************************
 * Dem_MemObdFreezeFrame_SetFFOfEventVisible
 *****************************************************************************/
/*!
 * \brief         Marks a freeze frame slot related to an event as visible
 *
 * \details       Searches for a freeze frame slot related to the EventId
 *                and marks it as visible
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *                && DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_SetFFOfEventVisible(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON)
/* ****************************************************************************
 * Dem_MemObdFreezeFrame_SetOldestHighPrioFreezeFrameVisible
 *****************************************************************************/
/*!
 * \brief         Marks the oldest freeze frame related to a misfire or fuel
 *                system event as visible
 *
 * \details       Searches for the oldest invisible freeze frame slot related
 *                to a misfire and fuel system event and marks it as visible

 * \return        EventId of the event whose slot was marked as visible
 * \return        DEM_EVENT_INVALID if no invisible freeze frame related to a
 *                misfire or fuel system event is stored
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON &&
 *                DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemObdFreezeFrame_SetOldestHighPrioFreezeFrameVisible(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemObdFreezeFrame_IsFreezeFrameStorageValid
 *****************************************************************************/
/*!
 * \brief         Tests if freeze frame storage is valid for a certain event.
 *
 * \details       Tests if freeze frame storage is valid for a certain event,
 *                depending on obd freeze frame storage configuration.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE:  Freeze frame storage for event is valid
 *                FALSE: Freeze frame storage for event is invalid
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemObdFreezeFrame_IsFreezeFrameStorageValid(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_MEMOBDFREEZEFRAME_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemObdFreezeFrame_Interface.h
 *********************************************************************************************************************/
