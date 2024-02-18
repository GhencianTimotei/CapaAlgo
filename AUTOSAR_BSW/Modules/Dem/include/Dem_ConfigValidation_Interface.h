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
 *  \defgroup   Dem_ConfigValidation ConfigValidation
 *  \{
 *  \file       Dem_ConfigValidation_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of validations for configurations requiring a configuration pointer
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_CONFIGVALIDATION_INTERFACE_H)
#define DEM_CONFIGVALIDATION_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_ConfigValidation_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * \defgroup Dem_ConfigValidation_Public_Properties Public Properties
 * \{
 */


 /* ****************************************************************************
 * Dem_ConfigurationValidation_SetGlobalConfigPointerInitState
 *****************************************************************************/
 /*!
 * \brief         Set the Global Config Pointer Initization Status to the 
 *                given state
 *
 * \details       Set the Global Config Pointer Initization Status to the 
 *                given state. For configurations in which usage of config
 *                pointer during initialization is disabled, the function 
 *                should not be invoked
 *
 * \param[in]     GlobalConfigPtrInitState
 *                The initialization state
 *
 *
 * \pre           Usage of config pointer during initialization is enabled
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ConfigurationValidation_SetGlobalConfigPointerInitState(
  uint8 GlobalConfigPtrInitState
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
 * \defgroup Dem_ConfigValidation_Public Public Methods
 * \{
 */

 /* ****************************************************************************
 * Dem_ConfigurationValidation_TestGlobalCfgPointerInState
 *****************************************************************************/
 /*!
 * \brief         Test if the Global Config Pointer is in the given state
 *
 * \details       Test if the Global Config Pointer is in the given state
 *
 * \param[in]     GlobalConfigPtrInitState
 *                The initialization state
 *
 * \return        TRUE
 *                Global Config Pointer is in the given state
 * \return        FALSE
 *                Global Config Pointer is in the given state
 *
 * \pre           Usage of config pointer during initialization is enabled
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ConfigurationValidation_TestGlobalCfgPointerInState(                                                                             
  uint8 GlobalConfigPtrInitState
  );

 /* ****************************************************************************
 * Dem_ConfigurationValidation_TestGlobalCfgPointerAtleastInState
 *****************************************************************************/
 /*!
 * \brief         Test if the Global Config Pointer is atleast in the given state
 *
 * \details       Test if the Global Config Pointer is atleast in the given state
 *
 * \param[in]     GlobalConfigPtrInitState
 *                The initialization state
 *
 * \return        TRUE
 *                Global Config Pointer equal to or greater than the given state
 * \return        FALSE
 *                Global Config Pointer not equal to or greater than the given state
 *
 * \pre           Development error detection enabled
 *                and usage of config pointer during initialization is enabled
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ConfigurationValidation_TestGlobalCfgPointerAtleastInState(                                                                             
  uint8 GlobalConfigPtrInitState
  );

#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
 /* ****************************************************************************
 * Dem_ConfigurationValidation_ValidateAndSetConfigPtr
 *****************************************************************************/
 /*!
 * \brief         Verifies the input config pointer for validity and stores it 
 *                to the global config pointer.
 *
 * \details       Verifies the input config pointer for validity and stores it 
 *                to the global config pointer.
 *
 * \param[in]     ConfigPtr
 *                Configuration pointer
 *
 * \pre           Usage of config pointer during Initialization is enabled
 *                Input pointer must not be a NULL pointer
 *
 * \config        (DEM_CFG_USE_INIT_POINTER == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_ConfigurationValidation_ValidateAndSetConfigPtr(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_CONFIGVALIDATION_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ConfigValidation_Interface.h
 *********************************************************************************************************************/
