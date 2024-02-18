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
/*! \ingroup    Dem_Master
 *  \defgroup   Dem_StorageCondition Storage Condition
 *  \{
 *  \file       Dem_StorageCondition_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Interface of the StorageCondition subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_STORAGECONDITION_INTERFACE_H)
#define DEM_STORAGECONDITION_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_StorageCondition_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_StorageCondition_PublicProperties Public Properties
 * \{
 */

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GetGlobalStorageConditionCount
 *****************************************************************************/
/*!
 * \brief         Get the number of configured storage conditions
 *
 * \details       Get the number of configured storage conditions
 *
 * \return        The number of configured storage conditions
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_StorageCondition_GetGlobalStorageConditionCount(
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
 * \defgroup Dem_StorageCondition_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_StorageCondition_PreInit
 *****************************************************************************/
/*!
 * \brief         Enables all storage conditions
 *
 * \details       Enables all storage conditions and set all storage condition 
 *                groups active
 *
 * \pre           May only be called during Dem preinitialization
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_PreInit(
  void
  ); 

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the storage conditions and storage condition groups
 *
 * \details       Initializes the storage conditions and storage condition groups
 *
 * \pre           May only be called during Dem initialization
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_Init(
  void
  );
#endif

/* ****************************************************************************
 * Dem_StorageCondition_TestEventStorageConditionsFulfilled
 *****************************************************************************/
/*!
 * \brief         Tests whether the storage conditions are fulfilled for an event
 *
 * \details       Tests whether the storage conditions are fulfilled for an event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [0..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The storage conditions are fulfilled
 * \return        FALSE
 *                The storage conditions are not fulfilled
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StorageCondition_TestEventStorageConditionsFulfilled(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_SetStorageConditionFulfilled
 *****************************************************************************/
/*!
 * \brief         Sets the storage condition
 *
 * \details       Sets the storage condition
 *
 * \param[in]     StorageConditionID
 *                Unique handle of the storage condition.
 *                The StorageConditionID must be in range [1..Dem_StorageCondition_GetGlobalStorageConditionCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_SetStorageConditionFulfilled(
  CONST(uint8, AUTOMATIC)  StorageConditionID
  );
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_ResetStorageConditionFulfilled
 *****************************************************************************/
/*!
 * \brief         Clears the storage condition
 *
 * \details       Clears the storage condition
 *
 * \param[in]     StorageCondition
 *                Unique handle of the storage condition.
 *                The StorageCondition must be in range [1..Dem_StorageCondition_GetGlobalStorageConditionCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_ResetStorageConditionFulfilled(
  CONST(uint8, AUTOMATIC)  StorageCondition
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_STORAGECONDITION_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_StorageCondition_Interface.h
 *********************************************************************************************************************/
