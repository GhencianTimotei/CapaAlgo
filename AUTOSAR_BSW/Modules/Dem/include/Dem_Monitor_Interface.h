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
/*! \ingroup    Dem_Satellite
 *  \defgroup   Dem_Monitor Monitor Status
 *  \{
 *  \file       Dem_Monitor_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) Interface declaration file
 *  \details    Public interface of subcomponent Monitor
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MONITOR_INTERFACE_H)
#define DEM_MONITOR_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Monitor_Types.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Monitor_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Monitor_TestMonitorStatusTF
 *****************************************************************************/
/*!
 * \brief         Tests whether the 'Test Failed' bit of the monitor status is set.
 *
 * \details       Tests whether the 'Test Failed' bit of the monitor status is set.
 *
 * \param[in]     MonitorStatus
 *                The Monitor status.
 *
 * \return        TRUE
 *                TF bit is set.
 * \return        FALSE
 *                TF bit is not set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Monitor_TestMonitorStatusTF(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  );

/* ****************************************************************************
 * Dem_Monitor_TestMonitorStatusTNCTOC
 *****************************************************************************/
/*!
 * \brief         Tests whether the 'Test Not Completed This Operation Cycle'
 *                bit of the monitor status is set.
 *
 * \details       Tests whether the 'Test Not Completed This Operation Cycle'
 *                bit of the monitor status is set.
 *
 * \param[in]     MonitorStatus
 *                The Monitor status.
 *
 * \return        TRUE
 *                TNCTOC bit is set.
 * \return        FALSE
 *                TNCTOC bit is not set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Monitor_TestMonitorStatusTNCTOC(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  );







/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Monitor_Private Private Methods
 * \{
 */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"     

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PUBLIC FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Monitor_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Monitor_CalculateMonitorStatus
 *****************************************************************************/
/*!
 * \brief         Calculate and update the MonitorStatus from monitor trigger
 *                and event status.
 *
 * \details       Evaluate the Monitor Trigger and Event Status to set, 
 *                reset or latch the bits in input MonitorStatusValue, 
 *                and return the new MonitorStatusValue.
 *
 * \param[in]     MonitorStatusValue
 *                The existing MonitorStatusValue.
 * \param[in]     MonitorTrigger
 *                The monitor result reported by the application monitor.
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Resulting MonitorStatusValue.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Monitor_CalculateMonitorStatus(
  CONST(Dem_MonitorStatusType, AUTOMATIC)   MonitorStatusValue,
  CONST(Dem_EventStatusType, AUTOMATIC)     MonitorTrigger,
  CONST(Dem_EventIdType, AUTOMATIC)         EventId
  );

/* ****************************************************************************
 * Dem_Monitor_ResetTNCTOC
 *****************************************************************************/
/*!
 * \brief         Set the TNCTOC status in the satellite data object 
 *
 * \details       Set the monitor status bits from the given satellite data
 *                object to include the TNCTOC flag, and return a new satellite
 *                data.
 *
 * \param[in]     SatelliteDataValue
 *                The data object to read from.
 *
 * \return        The new SatelliteData value.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Monitor_ResetTNCTOC(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_MONITOR_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Monitor_Interface.h
 *********************************************************************************************************************/
