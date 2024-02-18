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
/*! \ingroup    Dem_TimeSeries
 *  \defgroup   Dem_Sampler Sampler
 *  \{
 *  \file       Dem_Sampler_Interface.h
 *  \brief      Manages time series sampling timer.
 *  \details    Manages time series sampling timer.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_SAMPLER_INTERFACE_H)
#define DEM_SAMPLER_INTERFACE_H

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
/* PRQA S 3415 EOF */ /* MD_DEM_13.5_cf */

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Sampler_Types.h"

/* Includes for Other types used by the Implementation */
/* ------------------------------------------------------------------------- */
#include "Dem_Client_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Sampler_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Memory_TimeSeries_Sampler_GetNormalRateTimer
 *****************************************************************************/
 /*!
 * \brief         Get the current value of time series normal rate timer.
 *
 * \details       Get the remaining number of main funtion ticks of the normal
 *                rate timer.
 *
 * \return        Current value of time series normal rate timer.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Memory_TimeSeries_Sampler_GetNormalRateTimer(
  void
  );

/* ****************************************************************************
 * Dem_Memory_TimeSeries_Sampler_GetFastRateTimer
 *****************************************************************************/
 /*!
 * \brief         Get the current value of time series fast rate timer.
 *
 * \details       Get the remaining number of main funtion ticks of the fast
 *                rate timer.
 *
 *
 * \return        Current value of time series fast rate timer.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Memory_TimeSeries_Sampler_GetFastRateTimer(
  void
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
 * \defgroup Dem_Sampler_Public Public Methods
 * \{
 */

/* ****************************************************************************
* Dem_Memory_TimeSeries_Sampler_Init
*****************************************************************************/
/*!
* \brief         Initializes time series sampler
*
* \details       Initializes time series sampler
*
* \pre           NvM must have restored NV mirrors
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_Sampler_Init(
  void
);

/* ****************************************************************************
 * Dem_Memory_TimeSeries_Sampler_ProcessTimerTask
 *****************************************************************************/
/*!
 * \brief         Processes sampling timer of time series snapshot records
 *
 * \details       Processes sampling timer of time series snapshot records
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_Sampler_ProcessTimerTask(
  void
  );

/* ****************************************************************************
 * Dem_Memory_TimeSeries_Sampler_ProcessWorkerTask
 *****************************************************************************/
/*!
 * \brief         Processes asynchronous tasks related to time series snapshot records
 *
 * \details       Each time the related timers have expired time series snapshot
 *                data is collected and stored into ring buffers.
 *                Furthermore the storage of future samples is triggered for
 *                all events which have allocated a time series entry.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_Sampler_ProcessWorkerTask(
  void
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_SAMPLER_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Sampler_Interface.h
 *********************************************************************************************************************/
