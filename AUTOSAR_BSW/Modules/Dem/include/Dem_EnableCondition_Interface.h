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
 *  \defgroup   Dem_EnableCondition Enable Condition
 *  \{
 *  \file       Dem_EnableCondition_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Interface of the EnableCondition subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_ENABLECONDITION_INTERFACE_H)
#define DEM_ENABLECONDITION_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_EnableCondition_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_EnableCondition_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_EnableCondition_GetGlobalEnableConditionCount
 *****************************************************************************/
/*!
 * \brief         Get the number of configured enable conditions
 *
 * \details       Get the number of configured enable conditions
 *
 * \return        The number of configured enable conditions
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetGlobalEnableConditionCount(
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
 * \defgroup Dem_EnableCondition_Public Public Methods
 * \{
 */


#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) || (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_EnableCondition_SetEnableConditionFulfilled
 *****************************************************************************/
/*!
 * \brief         Sets the enable condition
 *
 * \details       Sets the enable condition
 *
 * \param[in]     EnableConditionID
 *                Unique handle of the enable condition.
 *                The EnableConditionID must be in range [0..Dem_EnableCondition_GetGlobalEnableConditionCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON ||
 *                DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_SetEnableConditionFulfilled(
  CONST(uint8, AUTOMATIC)  EnableConditionID
  );
#endif

#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) || (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_EnableCondition_ResetEnableConditionFulfilled
 *****************************************************************************/
/*!
 * \brief         Clears the enable condition
 *
 * \details       Clears the enable condition
 *
 * \param[in]     EnableConditionID
 *                Unique handle of the enable condition.
 *                The EnableConditionID must be in range [0..Dem_EnableCondition_GetGlobalEnableConditionCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON ||
 *                DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_ResetEnableConditionFulfilled(
  CONST(uint8, AUTOMATIC)  EnableConditionID
  );
#endif

/* ****************************************************************************
 * Dem_EnableCondition_MainFunction
 *****************************************************************************/
/*!
 * \brief         Process enable condition changes
 *
 * \details       This function processes changes of the enable conditions for
 *                all events.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_MainFunction(
  void
  );

/* ****************************************************************************
 * Dem_EnableCondition_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the enable conditions and enable condition groups
 *
 * \details       Initializes the enable conditions and enable condition groups
 *
 * \pre           May only be called during Dem initialization
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_Init(
  void
  );

/* ****************************************************************************
 * Dem_EnableCondition_PreInit
 *****************************************************************************/
/*!
 * \brief         Enables all enable conditions
 *
 * \details       Enables all enable conditions
 *
 * \pre           May only be called during Dem preinitialization
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_PreInit(
  void
  );    

#if ((DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) \
    ||((DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) \
      && (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR_DURING_CDTCS == STD_OFF)))
/* ****************************************************************************
 * Dem_EnableCondition_TestEnableConditionFulfilled
 *****************************************************************************/
/*!
 * \brief         Retrieves activation state of an enable condition
 *
 * \details       This function retrieves activation state of an enable condition
 *
 * \param[in]     EnableCondition
 *                Unique handle of the enable condition.
 *                The EnableCondition must be in range [0..Dem_EnableCondition_GetGlobalEnableConditionCount()[.
 *
 * \return        TRUE
 *                The enable condition is fulfilled
 *                FALSE
 *                The enable condition is not fulfilled
 *
 * \pre           -
 * \config        ((DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) \
 *                ||((DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) \
 *                  && (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR_DURING_CDTCS == STD_OFF))
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
  Dem_EnableCondition_TestEnableConditionFulfilled(
  CONST(uint8, AUTOMATIC)  EnableCondition
  );
#endif

/* ****************************************************************************
 * Dem_EnableCondition_TestEventEnableConditionsFulfilled
 *****************************************************************************/
/*!
 * \brief         Tests whether the enable conditions are fulfilled for an event
 *
 * \details       Tests whether the enable conditions are fulfilled for an event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [0..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The enable conditions are fulfilled
 * \return        FALSE
 *                The enable conditions are not fulfilled
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_TestEventEnableConditionsFulfilled(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_EnableCondition_TestEventProcessingPrecondition
 *****************************************************************************/
/*!
 * \brief         Tests if enable condition blocks event processing
 *
 * \details       Test if the current enable condition state blocks
 *                the processing of an event, ignoring enable condition 
 *                'control DTC setting' .
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [0..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                Event processing preconditions fulfilled
 * \return        FALSE
 *                Event processing preconditions are not fulfilled
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_TestEventProcessingPrecondition(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_ENABLECONDITION_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EnableCondition_Interface.h
 *********************************************************************************************************************/
