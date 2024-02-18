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
/*! \ingroup    Dem_MemoryEntry
 *  \defgroup   Dem_MemoryEntryIF Event Memory EntryIF
 *  \{
 *  \file       Dem_MemoryEntryIF_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public Interface of Memory EntryIF subcomponent which encapsulates the Memory entry and known data stored 
 *              in the memory entry
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMORYENTRYIF_INTERFACE_H)
#define DEM_MEMORYENTRYIF_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemoryEntryIF_Types.h"

                      /* Includes for Other Types used by the Implementation */
/* ------------------------------------------------------------------------- */
#include "Dem_Core_Types.h"

/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_MemoryEntry_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_MemoryEntry_GetEventId
 *****************************************************************************/
/*!
 * \brief         Get the Event Id of the memory entry
 *
 * \details       Get the Event Id of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The Event Id of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemoryEntry_GetEventId(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetEventId
 *****************************************************************************/
/*!
 * \brief         Set the event Id in the memory entry
 *
 * \details       Set the event Id in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     EventId
 *                The event Id to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetEventId(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetTimestamp
 *****************************************************************************/
/*!
 * \brief         Get the timestamp of the memory entry
 *
 * \details       Get the timestamp of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The timestamp of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MemoryEntry_GetTimestamp(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetTimestamp
 *****************************************************************************/
/*!
 * \brief         Set the timestamp in the memory entry
 *
 * \details       Set the timestamp in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     Timestamp
 *                The timestamp to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetTimestamp(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint32, AUTOMATIC) Timestamp
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetDebounceValueMax
 *****************************************************************************/
/*!
 * \brief         Get the maximum debounce value of the memory entry
 *
 * \details       Get the maximum debounce value of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The maximum debounce value of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint16, DEM_CODE)
Dem_MemoryEntry_GetDebounceValueMax(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetDebounceValueMax
 *****************************************************************************/
/*!
 * \brief         Set the maximum debounce value in the memory entry
 *
 * \details       Set the maximum debounce value in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     MaxDebounceValue
 *                The maximum debounce value to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetDebounceValueMax(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(sint16, AUTOMATIC) MaxDebounceValue
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetState
 *****************************************************************************/
/*!
 * \brief         Get the state of the memory entry
 *
 * \details       Get the state of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The state of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetState(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetState
 *****************************************************************************/
/*!
 * \brief         Set the state in the memory entry
 *
 * \details       Set the state in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     State
 *                The state to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetState(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) State
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetAgingCounter
 *****************************************************************************/
/*!
 * \brief         Get the aging counter of the memory entry
 *
 * \details       Get the aging counter of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The aging counter of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemoryEntry_GetAgingCounter(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetAgingCounter
 *****************************************************************************/
/*!
 * \brief         Set the aging counter in the memory entry
 *
 * \details       Set the aging counter in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     AgingCounter
 *                The aging counter to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetAgingCounter(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint16, AUTOMATIC) AgingCounter
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetAgingTimer
 *****************************************************************************/
/*!
 * \brief         Get the aging timer of the memory entry
 *
 * \details       Get the aging timer of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The aging timer of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MemoryEntry_GetAgingTimer(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetAgingTimer
 *****************************************************************************/
/*!
 * \brief         Set the aging timer in the memory entry
 *
 * \details       Set the aging timer in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     AgingTimer
 *                The aging timer to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetAgingTimer(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint32, AUTOMATIC) AgingTimer
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetOccurrenceCounter1Byte
 *****************************************************************************/
/*!
 * \brief         Get the 1 byte occurrence counter of the memory entry
 *
 * \details       Get the 1 byte occurrence counter of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The 1 byte occurrence counter of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter1Byte(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetOccurrenceCounter2Byte
 *****************************************************************************/
/*!
 * \brief         Get the 2 byte occurrence counter of the memory entry
 *
 * \details       Get the 2 byte occurrence counter of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The 2 byte occurrence counter of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter2Byte(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetFailedCycleCounter
 *****************************************************************************/
/*!
 * \brief         Get the 'Failed Cycle Counter' of the memory entry
 *
 * \details       Get the 'Failed Cycle Counter' of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The'Failed Cycle Counter' of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetFailedCycleCounter(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );


/* ****************************************************************************
 * Dem_MemoryEntry_GetConsecutiveFailedCycleCounter
 *****************************************************************************/
/*!
 * \brief         Get the 'Consecutive Failed Cycle Counter' of the memory 
 *                entry
 *
 * \details       Get the 'Consecutive Failed Cycle Counter' of the memory 
 *                entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The 'Consecutive Failed Cycle Counter' of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetConsecutiveFailedCycleCounter
 *****************************************************************************/
/*!
 * \brief         Set the 'Consecutive Failed Cycle Counter' in the memory 
 *                entry
 *
 * \details       Set the 'Consecutive Failed Cycle Counter' in the memory 
 *                entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     ConsecutiveFailedCycleCounter
 *                The 'Consecutive Failed Cycle Counter' to be set in the 
 *                memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetConsecutiveFailedCycleCounter(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) ConsecutiveFailedCycleCounter
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * \brief         Get the 'Cycles Since First Failed' of the memory entry
 *
 * \details       Get the 'Cycles Since First Failed' of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The 'Cycles Since First Failed' of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemoryEntry_GetCyclesSinceFirstFailed(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * \brief         Set the 'Cycles Since First Failed' in the memory entry
 *
 * \details       Set the 'Cycles Since First Failed' in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     CyclesSinceFirstFailed
 *                The 'Cycles Since First Failed' to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetCyclesSinceFirstFailed(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint16, AUTOMATIC) CyclesSinceFirstFailed
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetTestedCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * \brief         Get the 'Tested Cycles Since First Failed' of the memory 
 *                entry
 *
 * \details       Get the 'Tested Cycles Since First Failed' of the memory 
 *                entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The 'Tested Cycles Since First Failed' of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetTestedCyclesSinceFirstFailed(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetTestedCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * \brief         Set the 'Tested Cycles Since First Failed' in the memory 
 *                entry
 *
 * \details       Set the 'Tested Cycles Since First Failed' in the memory 
 *                entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     TestedCyclesSinceFirstFailed
 *                The 'Tested Cycles Since First Failed' to be set in the 
 *                memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetTestedCyclesSinceFirstFailed(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) TestedCyclesSinceFirstFailed
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetCyclesSinceLastFailed
 *****************************************************************************/
/*!
 * \brief         Get the 'Cycles Since Last Failed' of the memory entry
 *
 * \details       Get the 'Cycles Since Last Failed' of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The 'Cycles Since Last Failed' of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemoryEntry_GetCyclesSinceLastFailed(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetCyclesSinceLastFailed
 *****************************************************************************/
/*!
 * \brief         Set the 'Cycles Since Last Failed' in the memory entry
 *
 * \details       Set the 'Cycles Since Last Failed' in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     CyclesSinceLastFailed
 *                The 'Cycles Since Last Failed' to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetCyclesSinceLastFailed(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint16, AUTOMATIC) CyclesSinceLastFailed
  );

/* ****************************************************************************
* Dem_MemoryEntry_GetWarmUpCyclesSinceLastFailed
*****************************************************************************/
/*!
* \brief         Get the 'WarmUp Cycles Since Last Failed' of the memory entry
*
* \details       Get the 'WarmUp Cycles Since Last Failed' of the memory entry
*
* \param[in]     MemoryEntryId
*                The memory entry handle
*
* \return        The 'WarmUp Cycles Since Last Failed' of the memory entry
*
* \pre           -
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemoryEntry_GetWarmUpCyclesSinceLastFailed(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
* Dem_MemoryEntry_SetWarmUpCyclesSinceLastFailed
*****************************************************************************/
/*!
* \brief         Set the 'WarmUp Cycles Since Last Failed' in the memory entry
*
* \details       Set the 'WarmUp Cycles Since Last Failed' in the memory entry
*
* \param[in]     MemoryEntryId
*                The memory entry handle
* \param[in]     WarmUpCyclesSinceLastFailed
*                The 'WarmUp Cycles Since Last Failed' to be set in the memory
*                entry
*
* \pre           -
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetWarmUpCyclesSinceLastFailed(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint16, AUTOMATIC) WarmUpCyclesSinceLastFailed
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetPreConfirmedStatus
 *****************************************************************************/
/*!
 * \brief         Get the preconfirmed status of the memory entry
 *
 * \details       Get the preconfirmed status of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The preconfirmed status of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetPreConfirmedStatus(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetPreConfirmedStatus
 *****************************************************************************/
/*!
 * \brief         Set the preconfirmed status in the memory entry
 *
 * \details       Set the preconfirmed status in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     StatusIndicator
 *                The preconfirmed status to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetPreConfirmedStatus(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) StatusIndicator
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetOccurrenceCounter1
 *****************************************************************************/
/*!
 * \brief         Get the occurrence counter #1 of the memory entry
 *
 * \details       Get the occurrence counter #1 of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The occurrence counter #1 of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter1(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetOccurrenceCounter1
 *****************************************************************************/
/*!
 * \brief         Set the occurrence counter #1 in the memory entry
 *
 * \details       Set the occurrence counter #1 in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     OccurrenceCounter1
 *                The occurrence counter #1 to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter1(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) OccurrenceCounter1
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetOccurrenceCounter2
 *****************************************************************************/
/*!
 * \brief         Get the occurrence counter #2 of the memory entry
 *
 * \details       Get the occurrence counter #2 of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The occurrence counter #2 of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter2(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetOccurrenceCounter2
 *****************************************************************************/
/*!
 * \brief         Set the occurrence counter #2 in the memory entry
 *
 * \details       Set the occurrence counter #2 in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     OccurrenceCounter2
 *                The occurrence counter #2 to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter2(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) OccurrenceCounter2
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetOccurrenceCounter3
 *****************************************************************************/
/*!
 * \brief         Get the occurrence counter #3 of the memory entry
 *
 * \details       Get the occurrence counter #3 of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The occurrence counter #3 of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter3(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetOccurrenceCounter3
 *****************************************************************************/
/*!
 * \brief         Set the occurrence counter #3 in the memory entry
 *
 * \details       Set the occurrence counter #3 in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     OccurrenceCounter3
 *                The occurrence counter #3 to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter3(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) OccurrenceCounter3
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetOccurrenceCounter4
 *****************************************************************************/
/*!
 * \brief         Get the occurrence counter #4 of the memory entry
 *
 * \details       Get the occurrence counter #4 of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The occurrence counter #4 of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter4(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetOccurrenceCounter4
 *****************************************************************************/
/*!
 * \brief         Set the occurrence counter #4 in the memory entry
 *
 * \details       Set the occurrence counter #4 in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     OccurrenceCounter4
 *                The occurrence counter #4 to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter4(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) OccurrenceCounter4
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetOccurrenceCounter7
 *****************************************************************************/
/*!
 * \brief         Get the occurrence counter #7 of the memory entry
 *
 * \details       Get the occurrence counter #7 of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The occurrence counter #7 of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter7(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetOccurrenceCounter7
 *****************************************************************************/
/*!
 * \brief         Set the occurrence counter #7 in the memory entry
 *
 * \details       Set the occurrence counter #7 in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     OccurrenceCounter7
 *                The occurrence counter #7 to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter7(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) OccurrenceCounter7
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetStdEnvData
 *****************************************************************************/
/*!
 * \brief         Get the requested data element of the standard environmental 
 *                data of the memory entry
 *
 * \details       Get the requested data element of the standard environmental 
 *                data of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     DataIndex
 *                The index of the standard environmental data
 *
 * \return        The requested data element of the standard environmental 
 *                data of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetStdEnvData(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  DataIndex
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetStdEnvData
 *****************************************************************************/
/*!
 * \brief         Set the requested data element of the standard environmental 
 *                data in the memory entry
 *
 * \details       Set the requested data element of the standard environmental 
 *                data in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     DataIndex
 *                The index of the standard environmental data element
 * \param[in]     DataValue
 *                The data value to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetStdEnvData(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  DataIndex,
  CONST(uint8, AUTOMATIC)  DataValue
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetSnapshotHeader
 *****************************************************************************/
/*!
 * \brief         Get the snapshot header of the memory entry
 *
 * \details       Get the snapshot header of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The snapshot header of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetSnapshotHeader(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetSnapshotHeader
 *****************************************************************************/
 /*!
 * \brief         Set the snapshot header in the memory entry
 *
 * \details       Set the snapshot header in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     SnapshotHeader
 *                The snapshot header to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetSnapshotHeader(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) SnapshotHeader
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetCombinedDTCSnapshotHeader
 *****************************************************************************/
/*!
 * \brief         Get the combined DTC snapshot header of the memory entry
 *
 * \details       Get the combined DTC snapshot header of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The combined DTC snapshot header of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MemoryEntry_GetCombinedDTCSnapshotHeader(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetCombinedDTCSnapshotHeader
 *****************************************************************************/
 /*!
 * \brief         Set the combined DTC snapshot header in the memory entry
 *
 * \details       Set the combined DTC snapshot header in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     CombinedDTCSnapshotHeader
 *                The combined DTC snapshot header to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetCombinedDTCSnapshotHeader(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint32, AUTOMATIC) CombinedDTCSnapshotHeader
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetCombinedDTCExtendedHeader
 *****************************************************************************/
/*!
 * \brief         Get the combined DTC extended header of the memory entry
 *
 * \details       Get the combined DTC extended header of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The combined DTC extended header of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MemoryEntry_GetCombinedDTCExtendedHeader(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetCombinedDTCExtendedHeader
 *****************************************************************************/
 /*!
 * \brief         Set the combined DTC extended header in the memory entry
 *
 * \details       Set the combined DTC extended header in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     CombinedDTCExtendedHeader
 *                The combined DTC extended header to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetCombinedDTCExtendedHeader(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint32, AUTOMATIC) CombinedDTCExtendedHeader
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetExtendedHeader
 *****************************************************************************/
/*!
 * \brief         Get the extended header of the memory entry
 *
 * \details       Get the extended header of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The extended header of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetExtendedHeader(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetExtendedHeader
 *****************************************************************************/
/*!
 * \brief         Set the extended header in the memory entry
 *
 * \details       Set the extended header in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     ExtendedHeader
 *                The extended header to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetExtendedHeader(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) ExtendedHeader
  );

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_GetSnapshotRecordDataPtr
 *****************************************************************************/
/*!
 * \brief         Get the indexed snapshot data buffer of the memory entry
 *
 * \details       Get the indexed snapshot data buffer of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     SRecIndex
 *                Index of the snapshot data record
 *
 * \return        Pointer to the indexed snapshot data buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetSnapshotRecordDataPtr(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  SRecIndex
  );
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_GetSnapshotRecordDataConstPtr
 *****************************************************************************/
 /*!
 * \brief         Get the indexed snapshot data buffer of the memory entry
 *
 * \details       Get the indexed snapshot data buffer of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     SRecIndex
 *                Index of the snapshot data record
 *
 * \return        Pointer to the unmodifiable (const) indexed snapshot data
 *                buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetSnapshotRecordDataConstPtr(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_SRecIndexType, AUTOMATIC)  SRecIndex
  );
#endif

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_GetExtendedRecordDataPtr
 *****************************************************************************/
/*!
 * \brief         Get the indexed extended data buffer of the memory entry
 *
 * \details       Get the indexed extended data buffer of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     ERecIndex
 *                Index of the extended data record
 *
 * \return        Pointer to the indexed extended data buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_USER_ERECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetExtendedRecordDataPtr(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ERecIndex
  );
#endif

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_GetExtendedRecordDataConstPtr
 *****************************************************************************/
/*!
 * \brief         Get the indexed extended data buffer of the memory entry
 *
 * \details       Get the indexed extended data buffer of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     ERecIndex
 *                Index of the extended data record
 *
 * \return        Pointer to the unmodifiable (const) indexed extended data
 *                buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_USER_ERECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetExtendedRecordDataConstPtr(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ERecIndex
  );
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_GetWwhObdFreezeFrameDataPtr
 *****************************************************************************/
/*!
 * \brief         Get the WWH-OBD freeze frame data buffer of the memory entry
 *
 * \details       Get the WWH-OBD freeze frame data buffer of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        Pointer to the WWH-OBD freeze frame data buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetWwhObdFreezeFrameDataPtr(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );
#endif

#if (DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON) || (DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_GetJ1939FreezeFramePtr
 *****************************************************************************/
/*!
 * \brief         Get the J1939 freeze frame data buffer of the memory entry
 *
 * \details       Get the J1939 freeze frame data buffer of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        Pointer to the J1939 freeze frame data buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON ||
 *                DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetJ1939FreezeFramePtr(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_GetGlobalSnapshotRecordDataPtr
 *****************************************************************************/
/*!
 * \brief         Get the global snapshot record data buffer of the memory entry
 *
 * \details       Get the global snapshot record data buffer of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        Pointer to the global snapshot record data buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetGlobalSnapshotRecordDataPtr(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );
#endif

/* ****************************************************************************
 * Dem_MemoryEntry_TestGlobalSnapshotRecordStored
 *****************************************************************************/
/*!
 * \brief         Checks whether the global snapshot record of the event in 
 *                memory is stored.
 *
 * \details       Checks whether the global snapshot record of the event in 
 *                memory is stored.
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle.
 *
 * \return        TRUE
 *                Global snapshot record is stored.
 * \return        FALSE
 *                Otherwise
 *                
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_TestGlobalSnapshotRecordStored(                                                                                  
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetGlobalSnapshotRecordStored
 *****************************************************************************/
/*!
 * \brief         Sets the global snapshot record stored state of an event in 
 *                memory.
 *
 * \details       Sets the global snapshot record stored state of an event in 
 *                memory.
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle.
 * \param[in]     StoredState
 *                The global snapshot record stored state.                
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetGlobalSnapshotRecordStored(                                                                                   
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId,
  CONST(boolean, AUTOMATIC) StoredState
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetStatusIndicator
 *****************************************************************************/
/*!
 * \brief         Get the StatusIndicator byte of the memory entry
 *
 * \details       Get the StatusIndicator byte of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The StatusIndicator byte of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_Type, DEM_CODE)
Dem_MemoryEntry_GetStatusIndicator(
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId
);

/* ****************************************************************************
 * Dem_MemoryEntry_SetStatusIndicator
 *****************************************************************************/
/*!
 * \brief         Set the StatusIndicator byte in the memory entry
 *
 * \details       Set the StatusIndicator byte in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     StatusIndicator
 *                The StatusIndicator byte to be set in the memory
 *                entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetStatusIndicator(
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId,
  Dem_StatusIndicator_Type StatusIndicator
);

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
 * \defgroup Dem_MemoryEntry_Private Private Methods
 * \{
 */

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
 * \defgroup Dem_MemoryEntry_Public Public Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_TestGlobalSnapshotStored
 *****************************************************************************/
/*!
 * \brief         Test if global snapshot is stored in memory entry
 *
 * \details       Test if global snapshot is stored in memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        TRUE, global snapshot stored
 *                FALSE, global snapshot not stored
 *
 * \pre           -
   \config        DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_TestGlobalSnapshotStored(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );
#endif

/* ****************************************************************************
 * Dem_MemoryEntry_GetOccurrenceCounter
 *****************************************************************************/
/*!
 * \brief         Get the occurrence counter of the memory entry
 *
 * \details       Get the occurrence counter of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The occurrence counter of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MemoryEntry_OccurrenceCounterType, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_Init
 *****************************************************************************/
/*!
  * \brief         Initializes the memory entry
  *
  * \details       Initializes the memory entry
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
Dem_MemoryEntry_Init(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_CopyEntry
 *****************************************************************************/
/*!
 * \brief         Copies the content of a memory entry to another memory entry
 *
 * \details       Copies the content of a memory entry to another memory entry
 *
 * \param[in]     DestinationMemoryEntryId
 *                The memory entry handle of the destination memory entry
 * \param[in]     SourceMemoryEntryId
 *                The memory entry handle of the source memory entry
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_CopyEntry(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  DestinationMemoryEntryId,
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  SourceMemoryEntryId
  );
#endif

#if (DEM_FEATURE_NEED_OCC_COUNTER == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_IncrementOccurrenceCounter
 *****************************************************************************/
/*!
 * \brief         Increment the occurrence counter in the memory entry.
 *
 * \details       Increment the occurrence counter in the memory entry, if it
 *                is lower than the maximum value (latch at maximum value).
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle.
 *
 * \return        TRUE
 *                The occurrence counter was incremented succesfully.
 *                FALSE
 *                The occurrence counter was not incremented.
 * \config        DEM_FEATURE_NEED_OCC_COUNTER == STD_ON
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_IncrementOccurrenceCounter(
  Dem_Cfg_MemoryEntryHandleType  MemoryEntryId
  );
#endif

/* ****************************************************************************
 * Dem_MemoryEntry_IncrementFailedCycleCounter
 *****************************************************************************/
/*!
 * \brief         Increment the 'Failed Cycle Counter' in the memory entry.
 *
 * \details       Increment the 'Failed Cycle Counter' in the memory entry, if
 *                it is lower than the maximum value (latch at maximum value).
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle.
 *
 * \return        TRUE
 *                The 'Failed Cycle Counter' was incremented succesfully.
 *                FALSE
 *                The 'Failed Cycle Counter' was not incremented.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_IncrementFailedCycleCounter(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_IncrementConsecutiveFailedCycleCounter
 *****************************************************************************/
/*!
 * \brief         Increment the 'Consecutive Failed Cycle Counter' in the 
 *                memory entry
 *
 * \details       Increment the 'Consecutive Failed Cycle Counter' in the 
 *                memory entry, if it is lower than the maximum value (latch at
 *                maximum value).
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        TRUE
 *                The 'Consecutive Failed Cycle Counter' was incremented 
 *                succesfully
 *                FALSE
 *                The 'Consecutive Failed Cycle Counter' was not incremented
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_IncrementConsecutiveFailedCycleCounter(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_InitializeEntry
 *****************************************************************************/
/*!
 * \brief         Initializes an event memory entry.
 *
 * \details       Initialize the different elements of an event's MemoryEntry 
 *                struct.
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemoryEntry_InitializeEntry(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetId
 *****************************************************************************/
/*!
 * \brief         Get the memory entry Id
 *
 * \details       Get the memory entry Id from the block index
 *
 * \param[in]     BlockIndex
 *                NV Block index of the memory entry
 *
 * \return        The memory entry Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryEntryHandleType, DEM_CODE)
Dem_MemoryEntry_GetId(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex
  );

/* ****************************************************************************
 * Dem_MemoryEntry_TestAgingOnlyEntry
 *****************************************************************************/
/*!
 * \brief         Checks whether the event memory entry is an aging only entry.
 *
 * \details       Checks whether the event memory entry is an aging only entry.
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle.
 *
 * \return        TRUE
 *                Aging only entry
 * \return        FALSE
 *                Otherwise
 *                
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_TestAgingOnlyEntry(
  CONST(Dem_Cfg_MemoryEntryHandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_TestEntryForEvent
 *****************************************************************************/
/*!
 * \brief         Test if given event occupies event entry linked to given index
 *
 * \details       Test if given event occupies event entry linked to given index
 *
 * \param[in]     Index
 *                Handle of the memory block
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * 
 * \return        TRUE
 *                Event is present at given entry
 * \return        FALSE
 *                Event is not present at given entry
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_TestEntryForEvent(
  uint16 Index, 
  Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_FreeEntry
 *****************************************************************************/
/*!
 * \brief         Free event entry present at the given index
 *
 * \details       Free event entry present at the given index
 *
 * \param[in]     Index
 *                Handle of the memory block
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_FreeEntry(
  uint16 Index
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_MEMORYENTRYIF_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemoryEntryIF_Interface.h
 *********************************************************************************************************************/
