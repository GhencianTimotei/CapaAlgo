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
/*! \ingroup    Dem_Debounce
 *  \defgroup   Dem_DebounceTimeBased Timer Based Debounce
 *
 *  \{
 *  \file       Dem_DebounceTimeBased_Interface.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Public interface of DebounceTimeBased subcomponent
 *
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DEBOUNCETIMEBASED_INTERFACE_H)
#define DEM_DEBOUNCETIMEBASED_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_DebounceTimeBased_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PUBLIC FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_DebounceTimeBased_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_DebounceTimeBased_InfoInit
 *****************************************************************************/
/*!
 * \brief         Initializes a debounce object for time based debouncing.
 *
 * \details       This function initializes the fields of a time based
 *                debounce descriptor. Debounce state and timer values are 
 *                set to the given values.
 *
 * \param[out]    DebounceInfoData
 *                The debouncing element to be initialized.
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     SatelliteData
 *                The satellite data element holding the data used to 
 *                initialize the debouncing info.
 *
 * \returns       Pointer to the base debounce object.
 *
 * \pre           The event must use time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceBase_InfoPtrType, DEM_CODE)
Dem_DebounceTimeBased_InfoInit(
  CONST(Dem_DebounceTimeBased_InfoPtrType, AUTOMATIC) DebounceInfoData,
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_Calculate
 *****************************************************************************/
/*!
 * \brief         Process the time based debouncing of an event.
 *
 * \details       Process the time based debouncing of an event.
 *
 * \param[in,out] DebounceInfoPtr
 *                The debouncing information.
 *
 * \return        TRUE
 *                Debouncing was processed.

 * \return        FALSE
 *                Debouncing failed due to enable condition OR
 *                DebounceInfoPtr was not initialized for time based debouncing.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DebounceTimeBased_Calculate(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_Freeze
 *****************************************************************************/
/*!
 * \brief         Pauses time based debouncing for an event.
 *
 * \details       Pauses time based debouncing for an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_Freeze(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_Reset
 *****************************************************************************/
/*!
 * \brief         Resets time based debouncing for an event.
 *
 * \details       Resets time based debouncing for an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_Reset(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

 /* ****************************************************************************
  * Dem_DebounceTimeBased_GetDebouncingState
  *****************************************************************************/
 /*!
  * \brief         Calculates the debouncing state of an event.
  *
  * \details       Calculates the debouncing state of an event.
  *
  * \param[in,out] DebounceInfoPtr
  *                The debouncing information.
  *
  * \return        The debouncing state of the event.
  *
  * \pre           DebounceInfoPtr was initialized for time based debouncing.
  *
  * \context       TASK|ISR2
  * \synchronous   TRUE
  * \reentrant     TRUE for different events
  *****************************************************************************/
 DEM_LOCAL FUNC(Dem_DebouncingStateType, DEM_CODE)
 Dem_DebounceTimeBased_GetDebouncingState(
   CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
   );

 /* ****************************************************************************
  * Dem_DebounceTimeBasedSat_UpdateDebounceValueMax
  *****************************************************************************/
 /*!
  * \brief         Updates the stored maximum debounce value for an event.
  *
  * \details       Updates the stored maximum debounce value for an event.
  *
  * \param[in]     DebounceInfoPtr
  *                The debouncing information.
  *
  * \pre           DebounceInfoPtr was initialized for time based debouncing.
  *
  * \context       TASK|ISR2
  * \synchronous   TRUE
  * \reentrant     TRUE
  *****************************************************************************/
 DEM_LOCAL FUNC(void, DEM_CODE)
 Dem_DebounceTimeBasedSat_UpdateDebounceValueMax(
   CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
   );

/* ****************************************************************************
 * Dem_DebounceTimeBasedSat_ResetDebounceValueMax
 *****************************************************************************/
/*!
 * \brief         Resets the stored maximum debounce value for an event.
 *
 * \details       Resets the stored maximum debounce value for an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBasedSat_ResetDebounceValueMax(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Calculates the current fault detection counter of an event.
 *
 * \details       Calculates the current fault detection counter of an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \param[out]    FaultDetectionCounter
 *                The current FDC based on the debounce time and state.
 *
 * \return        Always E_OK
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DebounceTimeBased_GetFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_GetMaxFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Calculates the maximum fault detection counter of an event.
 *
 * \details       Calculates the maximum fault detection counter of an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 * \param[out]    FaultDetectionCounter
 *                The maximum FDC based on the debounce time and state
 *
 * \return        Always E_OK
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DebounceTimeBased_GetMaxFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_GetDebouncingResult
 *****************************************************************************/
/*!
 * \brief         Updates the debouncing data of an event.
 *
 * \details       Updates the debouncing data of an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \param[in]     SatelliteData
 *                Data object holding the current debounce data
 *
 * \return        Data object holding the modified debounce data
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_DebounceTimeBased_GetDebouncingResult(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_RestoreDebounceValue
 *****************************************************************************/
/*!
 * \brief         Restore the debouncing value of an event.
 *
 * \details       Value is restored, if
 *                 - the given debounce value is not qualified
 *                 - or if the debounce value is qualified and the reached
 *                   threshold equals the ExpectedThreshold.
 *
 *                Otherwise Value is not restored.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to query.
 *
 * \param[in]     SatelliteData
 *                Data object holding the current debounce data
 *
 * \param[in]     Value
 *                The value to be restored
 *
 * \param[in]     ExpectedThreshold
 *                Specifies whether the negative threshold is expected to be
 *                reached (TRUE), or the positive one (FALSE).
 *
 * \return        Data object holding the modified debounce data
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_DebounceTimeBased_RestoreDebounceValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC) SatelliteData,
  CONST(sint16, AUTOMATIC) Value,
  CONST(boolean, AUTOMATIC) ExpectedThreshold
  );

/* ****************************************************************************
 * Dem_DebounceTimeBasedSat_ProcessDebounce
 *****************************************************************************/
/*!
 * \brief         Processes the time based debouncing of an event.
 *
 * \details       Updates the debouncing state and timers of the debounced
 *                event. Any resulting event processing is deferred to the
 *                context of the Dem task.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *                Feature time debouncing is supported.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceTimeBasedSat_ProcessDebounce(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC) DebounceInfoPtr
  );


/* ****************************************************************************
 * Dem_DebounceTimeBasedSat_IsTimerActive
 *****************************************************************************/
/*!
 * \brief         Tests if the debounce timer of the event is active.
 *
 * \details       Tests if the debounce timer of the event is active, i.e.
 *                the timer is already started, not frozen and not expired.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \return        TRUE
 *                Debounce timer is active
 *                FALSE
 *                Debounce timer is inactive
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *                Time debounce feature is supported.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebounceTimeBasedSat_IsTimerActive(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DEBOUNCETIMEBASED_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DebounceTimeBased_Interfaces.h
 *********************************************************************************************************************/
