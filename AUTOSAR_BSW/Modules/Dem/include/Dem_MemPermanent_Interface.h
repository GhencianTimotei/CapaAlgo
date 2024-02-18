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
 *  \defgroup   Dem_MemPermanent MemPermanent
 *  \{
 *  \file       Dem_MemPermanent_Interface.h
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

#if !defined (DEM_MEMPERMANENT_INTERFACE_H)
#define DEM_MEMPERMANENT_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemPermanent_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_MemPermanent_PublicProperties Public Properties
 * \{
 */

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologyResetOverflown
 *****************************************************************************/
/*!
 * \brief         Mark the confirmed chronology as NOT overflown.
 *
 * \details       Mark the confirmed chronology as NOT overflown.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyResetOverflown( 
  void
  );
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologySetOverflown
 *****************************************************************************/
/*!
 * \brief         Mark the confirmed chronology as overflown.
 *
 * \details       Mark the confirmed chronology as overflown.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologySetOverflown( 
  void
  );
#endif






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
 * \defgroup Dem_MemPermanent_Public Public Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologyInit
 *****************************************************************************/
/*!
 * \brief         Initialize complete confirmed chronology with 'invalid event id'
 *
 * \details       Initialize complete confimred chronology with 'invalid event id'
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyInit(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronologyRestore
 *****************************************************************************/
/*!
 * \brief         Initialize and validates confirmed chronology of permanent memory
 *
 * \details       Initialize current size of chronology and removes entries in 
 *                chronology belonging to events that do not belong to primary 
 *                memory anymore or do not have the 'Confirmed Bit' set.
 *
 * \param[in]     -
 *
 * \pre           Initialization and restoration of event status at 
 *                Dem initialization is done.
 *
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyRestore(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronoFreeEvent
 *****************************************************************************/
/*!
 * \brief         Frees the entry in confirmed chronology for the event
 *
 * \details       Move all entries that are newer than the entry to delete 
 *                one step forward in the chronology array until the entry
 *                with the forwarded event is overwritten.
 *
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronoFreeEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_ConfirmedChronoAddEvent
 *****************************************************************************/
/*!
 * \brief         Add an event to confirmed chronology
 *
 * \details       Add an event to confirmed chronology.
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 * \param[in]     SearchExistingEvent
 *                TRUE  Add the event only if there is no existing entry
 *                FALSE Add the event unconditionally
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronoAddEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  ConfirmedEvent,
  CONST(boolean, AUTOMATIC) SearchExistingEvent
  );
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_FillUp
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
Dem_MemPermanent_FillUp(
  void
  );
#endif

#if (DEM_FEATURE_NEED_PERMANENT_FOR_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_SetB1PermanentDTCsActive
 *****************************************************************************/
/*!
 * \brief         Ensure existing permanent entrys of B1 DTCs are in state 'Active'
 *
 * \details       Search for existing permanent entrys of B1 DTCs. If 'Passive'
 *                entrys are found, set them to 'Active'.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_PERMANENT_FOR_WWHOBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_SetB1PermanentDTCsActive(
  void
  );
#endif

# if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PERMANENTDTC_IMMEDIATE_VISIBLE == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_UpdateEntryVisibility
 *****************************************************************************/
/*!
 * \brief         Mark permanent entry of event VISIBLE
 *
 * \details       Mark permanent entry of event VISIBLE
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON && 
 *                DEM_CFG_SUPPORT_PERMANENTDTC_IMMEDIATE_VISIBLE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_UpdateEntryVisibility(
 CONST(Dem_EventIdType, AUTOMATIC)  EventId
 );
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_TestEntryForEvent
 *****************************************************************************/
/*!
 * \brief         Functionality not currently required for permanent memory.
 *
 * \details       Functionality not currently required for permanent memory.
 *                Raise development error on invocation.
 *
 * \param[in]     Index
 *                Handle of the memory
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \return        FALSE unconditionally
 * \pre           -
 *
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemPermanent_TestEntryForEvent(
  uint16 Index, 
  Dem_EventIdType EventId
  );
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_MemPermanent_FreeEntry
 *****************************************************************************/
/*!
 * \brief         Functionality not currently required for permanent memory.
 *
 * \details       Functionality not currently required for permanent memory.
 *                Raise development error on invocation.
 *
 * \param[in]     Index
 *                Handle of the memory
 * \pre           -
 *
 * \config        DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_FreeEntry(
  uint16 Index
  );
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_MEMPERMANENT_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemPermanent_Interface.h
 *********************************************************************************************************************/
