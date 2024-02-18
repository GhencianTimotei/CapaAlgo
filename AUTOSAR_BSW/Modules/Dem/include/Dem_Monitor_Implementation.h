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
/*!  Project    MICROSAR Diagnostic Event Manager (Dem)
 *  \addtogroup Dem_Monitor
 *  \{
 *  \file       Dem_Monitor_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) Implementation file
 *  \details
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MONITOR_IMPLEMENTATION_H)
#define DEM_MONITOR_IMPLEMENTATION_H

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

                                                  /* Own header */
/* ------------------------------------------------------------------------- */
#include "Dem_Monitor_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_SatelliteData_Interface.h"
#include "Dem_Infrastructure_Interface.h"
#include "Dem_Core_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_MONITOR_IMPLEMENTATION_FILENAME "Dem_Monitor_Implementation.h"

#if ( (DEM_MONITOR_STATUS_TF < DEM_SATELLITEDATA_MONITOR_STATUS_POS) \
   || (DEM_MONITOR_STATUS_TF > DEM_SATELLITEDATA_MONITOR_STATUS_POS + DEM_SATELLITEDATA_MONITOR_STATUS_SIZE) \
   || (DEM_MONITOR_STATUS_TNCTOC < DEM_SATELLITEDATA_MONITOR_STATUS_POS) \
   || (DEM_MONITOR_STATUS_TNCTOC > DEM_SATELLITEDATA_MONITOR_STATUS_POS + DEM_SATELLITEDATA_MONITOR_STATUS_SIZE) )
# error "Monitor status definition not compatible with satellite data definition"
#endif

#if (DEM_MONITOR_STATUS_TF != DEM_BIT(0u))
# error "Monitor status definition is not compatible"
#endif

#if (DEM_MONITOR_STATUS_TNCTOC != DEM_BIT(1u))
# error "Monitor status definition is not compatible"
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/
#define DEM_MONITOR_STATUS_TF_MASK               DEM_BIT_MASK(0u, DEM_1BYTE)  /*!< Byte mask to reset test failed */
#define DEM_MONITOR_STATUS_TNCTOC_MASK           DEM_BIT_MASK(1u, DEM_1BYTE)  /*!< Byte mask to reset test failed this operating cycle*/


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Monitor_PrivateProperties Private Properties
 * \{
 */
/* ****************************************************************************
 * Dem_Monitor_SetMonitorStatusTF
 *****************************************************************************/
/*!
 * \brief         Sets the 'Test Failed' bit of the monitor status.
 *
 * \details       Sets the 'Test Failed' bit of the monitor status.
 *
 * \param[in]     MonitorStatus
 *                The Monitor status.
 *
 * \return        Monitor status with 'Test Failed' bit set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Monitor_SetMonitorStatusTF(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  );


/* ****************************************************************************
 * Dem_Monitor_SetMonitorStatusTNCTOC
 *****************************************************************************/
/*!
 * \brief         Sets the 'Test Not Completed This Operation Cycle' bit of the
 *                monitor status.
 *
 * \details       Sets the 'Test Not Completed This Operation Cycle' bit of the
 *                monitor status.
 *
 * \param[in]     MonitorStatus
 *                The Monitor status.
 *
 * \return        Monitor status with 'Test Not Completed This Operation Cycle'
 *                bit set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Monitor_SetMonitorStatusTNCTOC(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  );


/* ****************************************************************************
 * Dem_Monitor_ResetMonitorStatusTF
 *****************************************************************************/
/*!
 * \brief         Resets the 'Test Failed' bit of the monitor status.
 *
 * \details       Resets the 'Test Failed' bit of the monitor status.
 *
 * \param[in]     MonitorStatus
 *                The Monitor status.
 *
 * \return        Monitor status with 'Test Failed' bit reset.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Monitor_ResetMonitorStatusTF(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  );


/* ****************************************************************************
 * Dem_Monitor_ResetMonitorStatusTNCTOC
 *****************************************************************************/
/*!
 * \brief         Resets the 'Test Not Completed This Operation Cycle' bit of the
 *                monitor status.
 *
 * \details       Resets the 'Test Not Completed This Operation Cycle' bit of the
 *                monitor status.
 *
 * \param[in]     MonitorStatus
 *                The Monitor status.
 *
 * \return        Monitor status with 'Test Not Completed This Operation Cycle'
 *                bit reset.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Monitor_ResetMonitorStatusTNCTOC(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_Monitor_SetMonitorStatusTF
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Monitor_SetMonitorStatusTF(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  )
{
  return ((Dem_MonitorStatusType)((MonitorStatus) | DEM_MONITOR_STATUS_TF));
}


/* ****************************************************************************
 % Dem_Monitor_SetMonitorStatusTNCTOC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Monitor_SetMonitorStatusTNCTOC(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  )
{
  return ((Dem_MonitorStatusType)((MonitorStatus) | DEM_MONITOR_STATUS_TNCTOC));
}


/* ****************************************************************************
 % Dem_Monitor_ResetMonitorStatusTF
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Monitor_ResetMonitorStatusTF(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  )
{
  return ((Dem_MonitorStatusType)((MonitorStatus) & DEM_MONITOR_STATUS_TF_MASK));
}


/* ****************************************************************************
 % Dem_Monitor_ResetMonitorStatusTNCTOC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Monitor_ResetMonitorStatusTNCTOC(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  )
{
  return ((Dem_MonitorStatusType)((MonitorStatus) & DEM_MONITOR_STATUS_TNCTOC_MASK));
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
 * \addtogroup Dem_Monitor_PublicProperties
 * \{
 */


/* ****************************************************************************
 % Dem_Monitor_TestMonitorStatusTF
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Monitor_TestMonitorStatusTF(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  )
{
  return (boolean)(((MonitorStatus) & DEM_MONITOR_STATUS_TF) != 0u);
}

/* ****************************************************************************
 % Dem_Monitor_TestMonitorStatusTNCTOC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Monitor_TestMonitorStatusTNCTOC(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  )
{
  return (boolean)(((MonitorStatus) & DEM_MONITOR_STATUS_TNCTOC) != 0u);
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
 * \addtogroup Dem_Monitor_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Monitor_CalculateMonitorStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Monitor_CalculateMonitorStatus(
  CONST(Dem_MonitorStatusType, AUTOMATIC)   MonitorStatusValue,
  CONST(Dem_EventStatusType, AUTOMATIC)     MonitorTrigger,
  CONST(Dem_EventIdType, AUTOMATIC)         EventId
  )
{
  Dem_MonitorStatusType lReturnValue;

  lReturnValue = MonitorStatusValue;

  switch (MonitorTrigger)
  {
  case DEM_EVENT_STATUS_FAILED:
    lReturnValue = Dem_Monitor_SetMonitorStatusTF(lReturnValue);
    lReturnValue = Dem_Monitor_ResetMonitorStatusTNCTOC(lReturnValue);
    break;
  case DEM_EVENT_STATUS_PASSED:
    /* 
      UDS status of the event is only available after the Dem Master is initialized.
      If the Dem Master is not initialized, bypass the check for Latched Test Faled .
    */
    if ((Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
        || (Dem_Event_TestLatchedTestFailed(EventId) == FALSE))                                                                  /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
    {
      lReturnValue = Dem_Monitor_ResetMonitorStatusTF(lReturnValue);
      lReturnValue = Dem_Monitor_ResetMonitorStatusTNCTOC(lReturnValue);
    }
    break;
  default:                                                                                                                       /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
    /* Do nothing */
    break;
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Monitor_ResetTNCTOC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Monitor_ResetTNCTOC(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue
  )
{
  Dem_MonitorStatusType lMonitorStatus;
  lMonitorStatus = Dem_Monitor_SetMonitorStatusTNCTOC(Dem_SatelliteData_GetMonitorStatus(SatelliteDataValue));
  return Dem_SatelliteData_SetMonitorStatus(SatelliteDataValue, lMonitorStatus);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_MONITOR_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Monitor_Implementation.h
 *********************************************************************************************************************/
