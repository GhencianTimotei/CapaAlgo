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
/*! \addtogroup Dem_API
 *  \{
 *  \file       Dem_Cbk.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Callback API declarations of the MICROSAR Dem.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_CBK_H)
#define DEM_CBK_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Dem.h"

#if (DEM_CFG_USE_NVM == STD_ON)
# include "NvM.h"
#endif

/* ********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_API_Public
 * \{
 */

/* ****************************************************************************
 * Dem_NvM_InitAdminData
 *****************************************************************************/
/*!
 * \brief         Initializes the NvBlock for administrative data
 *                Triggers initialization of all other NvBlocks during Dem
 *                initialization
 *
 * \details       This function is supposed to be called by the NvM in order to
 *                (re)initialize the data in case the non-volatile memory has
 *                never been stored, or was corrupted.
 *                (See NvMBlockDescriptor/NvMInitBlockCallback)
 *                Calling the function will also cause the Dem to
 *                (re)initialize all other NvBlocks during Dem initialization
 *                to avoid data inconsistencies.
 *                It can also be used to force a reinitialization of the Dem
 *                data triggered by the application (e.g. after a new software
 *                version has been flashed to the ECU). In the latter case,
 *                make sure the function is not called while the Dem is active.
 *
 * \return        E_OK
 *
 * \pre           Dem is pre-initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitAdminData(
  void
  );

/* ****************************************************************************
 * Dem_NvM_InitStatusData
 *****************************************************************************/
/*!
 * \brief         Initializes the NvBlock for event status data
 *
 * \details       This function is supposed to be called by the NvM in order to
 *                (re)initialize the data in case the non-volatile memory has
 *                never been stored, or was corrupted.
 *                (See NvMBlockDescriptor/NvMInitBlockCallback)
 *                It can also be used to force a reinitialization of the Dem
 *                data triggered by the application (e.g. after a new software
 *                version has been flashed to the ECU). In the latter case,
 *                make sure the function is not called while the Dem is active.
 *
 * \return        E_OK
 *
 * \pre           Dem is pre-initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitStatusData(
  void
  );

/* ****************************************************************************
 * Dem_NvM_InitDebounceData
 *****************************************************************************/
/*!
 * \brief         Initializes the NvBlock for persisted debounce values
 *
 * \details       This function is supposed to be called by the NvM in order to
 *                (re)initialize the data in case the non-volatile memory has
 *                never been stored, or was corrupted.
 *                (See NvMBlockDescriptor/NvMInitBlockCallback)
 *                It can also be used to force a reinitialization of the Dem
 *                data triggered by the application (e.g. after a new software
 *                version has been flashed to the ECU). In the latter case,
 *                make sure the function is not called while the Dem is active.
 *                This function must only be called if debounce values are
 *                persisted to non-volatile memory.
 *
 * \return        E_OK
 *
 * \pre           Dem is pre-initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitDebounceData(
  void
  );

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) && (DEM_CFG_SUPPORT_EVENTAVAILABLE_NV == STD_ON)
/* ****************************************************************************
 * Dem_NvM_InitEventAvailableData
 *****************************************************************************/
/*!
 * \brief         Initializes the NvBlock for persisted event availability
 *
 * \details       This function is supposed to be called by the NvM in order to
 *                (re)initialize the data in case the non-volatile memory has
 *                never been stored, or was corrupted.
 *                (See NvMBlockDescriptor/NvMInitBlockCallback)
 *                It can also be used to force a reinitialization of the Dem
 *                data triggered by the application (e.g. after a new software
 *                version has been flashed to the ECU). In the latter case,
 *                make sure the function is not called while the Dem is active.
 *
 * \return        E_OK
 *
 * \pre           Dem is pre-initialized
 * \config        (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
 *                && (DEM_CFG_SUPPORT_EVENTAVAILABLE_NV == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitEventAvailableData(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_NvM_InitObdFreezeFrameData
 *****************************************************************************/
/*!
 * \brief         Initializes the NvBlock for freeze frame data
 *
 * \details       This function is supposed to be called by the NvM in order to
 *                (re)initialize the data in case the non-volatile memory has
 *                never been stored, or was corrupted.
 *                (See NvMBlockDescriptor/NvMInitBlockCallback)
 *                It can also be used to force a reinitialization of the Dem
 *                data triggered by the application (e.g. after a new software
 *                version has been flashed to the ECU). In the latter case,
 *                make sure the function is not called while the Dem is active.
 *
 * \return        E_OK
 *
 * \pre           Dem is pre-initialized
 * \config        (DEM_CFG_SUPPORT_OBDII == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitObdFreezeFrameData(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_NvM_InitObdPermanentData
 *****************************************************************************/
/*!
 * \brief         Initializes the NvBlock for permanent DTCs
 *
 * \details       This function is supposed to be called by the NvM in order to
 *                (re)initialize the data in case the non-volatile memory has
 *                never been stored, or was corrupted.
 *                (See NvMBlockDescriptor/NvMInitBlockCallback)
 *                It can also be used to force a reinitialization of the Dem
 *                data triggered by the application (e.g. after a new software
 *                version has been flashed to the ECU). In the latter case,
 *                make sure the function is not called while the Dem is active.
 *
 * \return        E_OK
 *
 * \pre           Dem is pre-initialized
 * \config        (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitObdPermanentData(
  void
  );
#endif

/* ****************************************************************************
 * Dem_NvM_InitObdIumprData
 *****************************************************************************/
/*!
 * \brief         Initializes the NvBlock for ratio data
 *
 * \details       This function is supposed to be called by the NvM in order to
 *                (re)initialize the data in case the non-volatile memory has
 *                never been stored, or was corrupted.
 *                (See NvMBlockDescriptor/NvMInitBlockCallback)
 *                It can also be used to force a reinitialization of the Dem
 *                data triggered by the application (e.g. after a new software
 *                version has been flashed to the ECU). In the latter case,
 *                make sure the function is not called while the Dem is active.
 *
 * \return        E_OK
 *
 * \pre           Dem is pre-initialized
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitObdIumprData(
  void
  );

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_NvM_InitDtrData
 *****************************************************************************/
/*!
 * \brief         Initializes the NvBlock for Dtr data
 *
 * \details       This function is supposed to be called by the NvM in order to
 *                (re)initialize the data in case the non-volatile memory has
 *                never been stored, or was corrupted.
 *                (See NvMBlockDescriptor/NvMInitBlockCallback)
 *                It can also be used to force a reinitialization of the Dem
 *                data triggered by the application (e.g. after a new software
 *                version has been flashed to the ECU). In the latter case,
 *                make sure the function is not called while the Dem is active.
 *
 * \return        E_OK
 *
 * \pre           Dem is pre-initialized
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitDtrData(
  void
  );
#endif

#if (DEM_FEATURE_NEED_AGING_DATA == STD_ON)
/* ****************************************************************************
 * Dem_NvM_InitAgingData
 *****************************************************************************/
/*!
 * \brief         Initializes the NvBlock for Aging Counter data
 *
 * \details       This function is supposed to be called by the NvM in order to
 *                (re)initialize the data in case the non-volatile memory has
 *                never been stored, or was corrupted.
 *                (See NvMBlockDescriptor/NvMInitBlockCallback)
 *                It can also be used to force a reinitialization of the Dem
 *                data triggered by the application (e.g. after a new software
 *                version has been flashed to the ECU). In the latter case,
 *                make sure the function is not called while the Dem is active.
 *
 * \return        E_OK
 *
 * \pre           Dem is pre-initialized
 * \config        DEM_FEATURE_NEED_AGING_DATA == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitAgingData(
  void
  );
#endif

/* ****************************************************************************
* Dem_NvM_InitCycleCounterData
*****************************************************************************/
/*!
* \brief         Initializes the NvBlock for Cycle Counter data
*
* \details       This function is supposed to be called by the NvM in order to
*                (re)initialize the data in case the non-volatile memory has
*                never been stored, or was corrupted.
*                (See NvMBlockDescriptor/NvMInitBlockCallback)
*                It can also be used to force a reinitialization of the Dem
*                data triggered by the application (e.g. after a new software
*                version has been flashed to the ECU). In the latter case,
*                make sure the function is not called while the Dem is active.
*
* \return        E_OK
*
* \pre           Dem is pre-initialized
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     FALSE
*****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitCycleCounterData(
  void
);

#if ((DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_POLLING == STD_OFF))
/* ****************************************************************************
 * Dem_NvM_JobFinished
 *****************************************************************************/
/*!
 * \brief         Notifies the Dem module about a completed NV operation
 *
 * \details       This function has to be called by the NvM after a write
 *                operation has finished.
 *                (See NvMBlockDescriptor/NvMSingleBlockCallback)
 *
 * \param[in]     ServiceId
 *                Service identifier
 * \param[in]     JobResult
 *                Result of the NV job
 *
 * \return        E_OK
 *
 * \pre           -
 * \config        (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_POLLING == STD_OFF)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_JobFinished(
  uint8 ServiceId,
  NvM_RequestResultType JobResult
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * \}
 */
#endif /* DEM_CBK_H */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Cbk.h
 *********************************************************************************************************************/
