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
/*! \ingroup    Dem_Shared
 *  \defgroup   Dem_EventQueue Event Queue
 *  \{
 *  \file       Dem_EventQueue_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of EventQueue subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_EVENTQUEUE_INTERFACE_H)
#define DEM_EVENTQUEUE_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_EventQueue_Types.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_EventQueue_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_EventQueue_GetInitialQueueStatus
 *****************************************************************************/
/*!
 * \brief         Returns an empty initial event queue status.
 *
 * \details       -
 *
 *
 * \return        QueueStatus with status reset / initial status
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_GetInitialQueueStatus(void);


/* ****************************************************************************
 * Dem_EventQueue_SetSimilarConditionStatusChanged
 *****************************************************************************/
/*!
 * \brief         Set 'similar condition status changed' in the queue status
 *
 * \details       Set flag 'similar condition status changed' in the queue 
 *                status
 *
 * \param[in]     QueueStatus
 *                Queue status byte
 *
 * \return        Queue status with flag set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetSimilarConditionStatusChanged(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  );
  


/* ****************************************************************************
 * Dem_EventQueue_SetFdcTripStatus
 *****************************************************************************/
/*!
 * \brief         Set 'event fdc threshold exceeded' in the queue status
 *
 * \details       Set flag 'event fdc threshold exceeded' in the queue status
 *
 * \param[in]     QueueStatus
 *                Queue status byte
 *
 * \return        Queue status with flag set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetFdcTripStatus(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC) QueueStatus
  );


/* ****************************************************************************
 * Dem_EventQueue_SetFdcMaxSLCStatus
 *****************************************************************************/
/*!
 * \brief         Set 'event fdc maximum exceeded' in the queue status.
 *
 * \details       Set flag 'event fdc maximum exceeded' in the queue status.
 *
 * \param[in]     QueueStatus
 *                Queue status byte
 *
 * \return        Queue status with flag set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetFdcMaxSLCStatus(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC) QueueStatus
  );


/* ****************************************************************************
 * Dem_EventQueue_SetFdcProcessingStatus
 *****************************************************************************/
/*!
 * \brief         Set 'event fdc maximum exceeded' in the queue status.
 *
 * \details       Set flag 'event fdc maximum exceeded' in the queue status.
 *
 * \param[in]     QueueStatus
 *                Queue status byte
 *
 * \return        Queue status with flag set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetFdcProcessingStatus(
CONST(Dem_EventQueue_StatusType, AUTOMATIC) QueueStatus
);


/* ****************************************************************************
 * Dem_EventQueue_SetResetTestFailedRequested
 *****************************************************************************/
/*!
 * \brief         Set 'ResetTestFailedRequested' in the queue status.
 *
 * \details       Set flag 'ResetTestFailedRequested' in the queue status.
 *
 * \param[in]     QueueStatus
 *                Queue status byte
 *
 * \return        Queue status with flag set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetResetTestFailedRequested(
CONST(Dem_EventQueue_StatusType, AUTOMATIC) QueueStatus
);

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
 * \defgroup Dem_EventQueue_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_EventQueue_TestQueueOverflow
 *****************************************************************************/
/*!
 * \brief         Test for queue overflow.
 *
 * \details       Test for queue overflow.
 *
 * \param[in]     QueueStatus
 *                Current queue status byte
 * \param[in]     MonitorTrigger
 *                Application monitor result after debouncing
 *
 * \return        TRUE
 *                The queue
 * \return        FALSE
 *                The queue
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestQueueOverflow(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus,
  CONST(Dem_EventStatusType, AUTOMATIC)   MonitorTrigger
  );

/* ****************************************************************************
 * Dem_EventQueue_CalculateQueueStatus
 *****************************************************************************/
/*!
 * \brief         Processes queuing of event reports.
 *
 * \details       Processes queuing of event reports.
 *
 * \param[in]     QueueStatus
 *                Current queue status byte
 * \param[in]     MonitorTrigger
 *                Application monitor result after debouncing
 *
 * \return        QueueStatus
 *                Updated queue status byte
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_CalculateQueueStatus(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus,
  CONST(Dem_EventStatusType, AUTOMATIC)   MonitorTrigger
  );

/* ****************************************************************************
 * Dem_EventQueueCore_Init()
 *****************************************************************************/
/*!
 * \brief         Initialize the subcomponent.
 *
 * \details       Initializes the subcomponent.
 *
 * \pre           Only call during the initialization phase.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventQueueCore_Init(
  void
  );

/* ****************************************************************************
 * Dem_EventQueueCore_MainFunction
 *****************************************************************************/
/*!
 * \brief         Task function of subcomponent Event Queue.
 *
 * \details       Processes pending event status changes.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventQueueCore_MainFunction(
  void
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_EVENTQUEUE_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EventQueue_Interface.h
 *********************************************************************************************************************/
