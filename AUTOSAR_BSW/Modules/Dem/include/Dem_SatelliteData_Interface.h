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
 *  \defgroup   Dem_SatelliteData Satellite Data
 *  \{
 *  \file       Dem_SatelliteData_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of SatelliteData subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_SATELLITEDATA_INTERFACE_H)
#define DEM_SATELLITEDATA_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                   /* Includes for own Types */
/* ------------------------------------------------------------------------- */
#include "Dem_SatelliteData_Types.h"

                      /* Includes for Other types used by the Implementation */
/* ------------------------------------------------------------------------- */
#include "Dem_Debounce_Types.h"
#include "Dem_Monitor_Types.h"
#include "Dem_Core_Types.h"
#include "Dem_FaultMemory_Types.h"

/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_SatelliteData_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_SatelliteData_IsSimilarConditionsEnabled
 *****************************************************************************/
/*!
 * \brief         Function verifies if the PP switch 
 *                DEM_CFG_SUPPORT_SIMILAR_CONDITIONS is enabled.
 *
 * \details       Function verifies if the PP switch 
 *                DEM_CFG_SUPPORT_SIMILAR_CONDITIONS is enabled.
 *
 * \return        TRUE
 *                Feature Similar Conditions is enabled.
 *                FALSE
 *                Feature Similar Conditions is not enabled.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteData_IsSimilarConditionsEnabled(
  void
  );

/* ****************************************************************************
 * Dem_SatelliteData_TestSimilarConditionStatus
 *****************************************************************************/
/*!
 * \brief         Reads the similar condition status from the given satellite data object.
 *
 * \details       Reads the similar condition status from the given satellite data object.
 *
 * \param[in]     SatelliteData
 *                The data object to read from.
 *
 * \return        TRUE
 *                Similar conditions not supported or similar conditions set
 *                FALSE
 *                Similar conditions not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteData_TestSimilarConditionStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

/* ****************************************************************************
 * Dem_SatelliteData_SetSimilarConditionStatus
 *****************************************************************************/
/*!
 * \brief         Set the similar condition status in the satellite data object.
 *
 * \details       Set the similar condition status in the satellite data object.
 *
 * \param[in]     SatelliteData
 *                The data object to modify
 *
 * \return        The modified satellite data object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_SetSimilarConditionStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

/* ****************************************************************************
 * Dem_SatelliteData_ResetSimilarConditionStatus
 *****************************************************************************/
/*!
 * \brief         Reset the similar condition status in the satellite data object.
 *
 * \details       Reset the similar condition status in the satellite data object.
 *
 * \param[in]     SatelliteData
 *                The data object to modify
 *
 * \return        The modified satellite data object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_ResetSimilarConditionStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

/* ****************************************************************************
 * Dem_SatelliteData_SetDebounceStatus
 *****************************************************************************/
/*!
 * \brief         Set the given debounce status into the satellite data object.
 *
 * \details       Set the given debounce status into the satellite data object.
 *
 * \param[in]     SatelliteData
 *                The data object to modify
 *
 * \param[in]     DebounceStatus
 *                The data to write to SatelliteData.
 *
 * \return        The modified satellite data object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_SetDebounceStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData,
  CONST(Dem_Debounce_StatusType, AUTOMATIC) DebounceStatus
  );

/* ****************************************************************************
 * Dem_SatelliteData_GetDebounceStatus
 *****************************************************************************/
/*!
 * \brief         Reads the debounce status from the given satellite data object.
 *
 * \details       Reads the debounce status from the given satellite data object.
 *
 * \param[in]     SatelliteData
 *                The data object to read from.
 *
 * \return        The requested data.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_SatelliteData_GetDebounceStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

/* ****************************************************************************
 * Dem_SatelliteData_SetDebounceData
 *****************************************************************************/
/*!
 * \brief         Set the given debounce data into the satellite data object.
 *
 * \details       Set the given debounce data into the satellite data object.
 *
 * \param[in]     SatelliteData
 *                The data object to modify.
 *
 * \param[in]     DebounceData
 *                The data to write to SatelliteData.
 *
 * \return        The modified satellite data object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_SetDebounceData(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData,
  CONST(Dem_Debounce_DataType, AUTOMATIC)  DebounceData
  );

/* ****************************************************************************
 * Dem_SatelliteData_GetDebounceData
 *****************************************************************************/
/*!
 * \brief         Reads the debounce data from the given satellite data object.
 *
 * \details       Reads the debounce data from the given satellite data object.
 *
 * \param[in]     SatelliteData
 *                The data object to read from.
 *
 * \return        The requested data.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Debounce_DataType, DEM_CODE)
Dem_SatelliteData_GetDebounceData(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

/* ****************************************************************************
 * Dem_SatelliteData_SetMonitorStatus
 *****************************************************************************/
/*!
 * \brief         Update the monitor status into the satellite data object.
 *
 * \details       Update the monitor status into the satellite data object.
 *
 * \param[in]     SatelliteDataValue
 *                The SatelliteData value to modify.
 *
 * \param[in]     MonitorStatusBits
 *                The data to write to SatelliteData.
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
Dem_SatelliteData_SetMonitorStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue,
  CONST(Dem_MonitorStatusType, AUTOMATIC)       MonitorStatusBits
  );

/* ****************************************************************************
 * Dem_SatelliteData_GetMonitorStatus
 *****************************************************************************/
/*!
 * \brief         Reads the monitor status from the given satellite data object.
 *
 * \details       Reads the monitor status from the given satellite data object.
 *
 * \param[in]     SatelliteDataValue
 *                The data object to read from.
 *
 * \return        The MonitorStatus.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_SatelliteData_GetMonitorStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue
  );

/* ****************************************************************************
 * Dem_SatelliteData_ResetMonitorStatus
 *****************************************************************************/
/*!
 * \brief         Set the monitor status in satellite data object to its
 *                initial value.
 *
 * \details       Set the monitor status bits from the given satellite data
 *                object to their initial value and return a new satellite data.
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
Dem_SatelliteData_ResetMonitorStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue
  );


/* ****************************************************************************
 * Dem_SatelliteData_SetQueueStatus
 *****************************************************************************/
/*!
 * \brief         Update the queue status into the satellite data object.
 *
 * \details       Update the queue status into the satellite data object.
 *
 * \param[in]     SatelliteDataValue
 *                The SatelliteData value to modify.
 *
 * \param[in]     QueueStatus
 *                The data to write to SatelliteData.
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
Dem_SatelliteData_SetQueueStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue,
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  );

/* ****************************************************************************
 * Dem_SatelliteData_GetQueueStatus
 *****************************************************************************/
/*!
 * \brief         Reads the queue status from the given satellite data object.
 *
 * \details       Reads the queue status from the given satellite data object.
 *
 * \param[in]     SatelliteDataValue
 *                The data object to read from.
 *
 * \return        The requested data.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_SatelliteData_GetQueueStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue
  );

/* ****************************************************************************
 * Dem_SatelliteData_GetPrestoreActionsQueued
 *****************************************************************************/
/*!
 * \brief         Reads the queued actions from the given satellite extended data object.
 *
 * \details       Reads the queued actions from the given satellite extended data object.
 *
 * \param[in]     SatelliteExtendedData
 *                The data object to read from.
 *
 * \return        The requested data.
 *
 * \pre           Function should only be invoked when features "Prestorage of 
 *                freeze frames" and "Multiple Satellite" are supported
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Prestore_QueueActionType, DEM_CODE)
Dem_SatelliteData_GetPrestoreActionsQueued(
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  SatelliteExtendedData
  );

/* ****************************************************************************
 * Dem_SatelliteData_QueuePrestoreFF
 *****************************************************************************/
/*!
 * \brief         Stores the action to prestore a freeze frame in the given 
 *                satellite extended data object.
 *
 * \details       Stores the action to prestore a freeze frame in the given 
 *                satellite extended data object.
 *
 * \param[in]     SatelliteExtendedData
 *                The data object to read from.
 *
 * \return        The new extended satellite data.
 *
 * \pre           Function should only be invoked when features "Prestorage of 
 *                freeze frames" and "Multiple satellites" are supported.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_ExtendedDataType, DEM_CODE)
Dem_SatelliteData_QueuePrestoreFF(
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  SatelliteExtendedData
  );

/* ****************************************************************************
 * Dem_SatelliteData_QueueClearPrestoredFF
 *****************************************************************************/
/*!
 * \brief         Stores the action to clear prestored freeze frames in the given 
 *                satellite extended data object.
 *
 * \details       Stores the action to clear prestored freeze frames in the given 
 *                satellite extended data object.
 *
 * \param[in]     SatelliteExtendedData
 *                The data object to read from.
 *
 * \return        The new extended satellite data.
 *
 * \pre           Function should only be invoked when features "Prestorage of 
 *                freeze frames" and "Multiple satellites" are supported.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_ExtendedDataType, DEM_CODE)
Dem_SatelliteData_QueueClearPrestoredFF(
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  SatelliteExtendedData
  );

/* ****************************************************************************
 * Dem_SatelliteData_DequeuePrestoreActions
 *****************************************************************************/
/*!
 * \brief         Clears all prestore actions in the given 
 *                satellite extended data object.
 *
 * \details       Clears all prestore actions in the given 
 *                satellite extended data object.
 *
 * \param[in]     SatelliteExtendedData
 *                The data object to read from.
 *
 * \return        The new extended satellite data.
 *
 * \pre           Function should only be invoked when the features "Support 
 *                prestorage of freeze frames" and "Multiple Satellites" are
 *                supported.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_ExtendedDataType, DEM_CODE)
Dem_SatelliteData_DequeuePrestoreActions(
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  SatelliteExtendedData
  );

/* ****************************************************************************
 * Dem_SatelliteData_GetStatusIndicatorActionsQueued
 *****************************************************************************/
/*!
 * \brief         Reads the queued action from the given satellite extended 
 *                data object.
 *
 * \details       Reads the queued action from the given satellite extended 
 *                data object.
 *
 * \param[in]     SatelliteExtendedData
 *                The data object to read from.
 *
 * \return        Queued StatusIndicator action.
 *
 * \pre           Function should only be invoked when feature "Support
 *                Extended Fim" is enabled.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_QueueActionType, DEM_CODE)
Dem_SatelliteData_GetStatusIndicatorActionsQueued(
  Dem_SatelliteData_ExtendedDataType SatelliteExtendedData
  );

/* ****************************************************************************
 * Dem_SatelliteData_QueueStatusIndicatorSymptomAction
 *****************************************************************************/
/*!
 * \brief         Queues the StatusIndicator symptom action in the given 
 *                satellite extended data object.
 *
 * \details       Queues the StatusIndicator symptom action in the given 
 *                satellite extended data object.
 *
 * \param[in]     SatelliteExtendedData
 *                The data object to read from.
 *
 * \return        The updated extended satellite data.
 *
 * \pre           Function should only be invoked when feature "Support
 *                Extended Fim" is enabled.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_ExtendedDataType, DEM_CODE)
Dem_SatelliteData_QueueStatusIndicatorSymptomAction(
  Dem_SatelliteData_ExtendedDataType SatelliteExtendedData
  );

/* ****************************************************************************
 * Dem_SatelliteData_DequeueStatusIndicatorActions
 *****************************************************************************/
/*!
 * \brief         Clears StatusIndicator Symptom action in the given satellite 
 *                extended data object.
 *
 * \details       Clears StatusIndicator Symptom action in the given satellite 
 *                extended data object.
 *
 * \param[in]     SatelliteExtendedData
 *                The data object to read from.
 *
 * \return        The updated extended satellite data.
 *
 * \pre           Function should only be invoked when feature "Support
 *                Extended Fim" is enabled.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_ExtendedDataType, DEM_CODE)
Dem_SatelliteData_DequeueStatusIndicatorActions(
  Dem_SatelliteData_ExtendedDataType SatelliteExtendedData
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
 * \defgroup Dem_SatelliteData_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_SatelliteData_GetInitValue
 *****************************************************************************/
/*!
 * \brief         Initialize the satellite data.
 *
 * \details       Initialize the satellite data.
 *
 * \return        The initialized data object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_GetInitValue(
  void
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_SATELLITEDATA_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_SatelliteData_Interface.h
 *********************************************************************************************************************/
