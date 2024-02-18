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
/*! \addtogroup Dem_ConfigValidation
 *  \{
 *  \file       Dem_ConfigValidation_Implementation.h
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

#if !defined (DEM_CONFIGVALIDATION_IMPLEMENTATION_H)
#define DEM_CONFIGVALIDATION_IMPLEMENTATION_H

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

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_ConfigValidation_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

  /*! Filename declaration */
#define DEM_CONFIGVALIDATION_IMPLEMENTATION_FILENAME "Dem_ConfigValidation_Implementation.h"

 /* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED_RESTRICTED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
/*! Currently active module configuration  
 *  It is important for silence that pointer is only available when DEM_CFG_USE_INIT_POINTER is STD_ON
 *  because pointer will only be initalized in this case.
 *  Otherwise there will be no compile error when DEM_CFG_USE_INIT_POINTER is generated STD_OFF and generated files
 *  use Dem_GlobalConfigPtr
 */
P2CONST(Dem_ConfigType, DEM_VAR_NOINIT, DEM_INIT_DATA)  Dem_GlobalConfigPtr;                                                     /* PRQA S 3406 */ /* MD_DEM_8.6 */
#endif

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED_RESTRICTED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define DEM_START_SEC_VAR_INIT_8BIT_RESTRICTED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Status of the GlobalConfigPtr Initialization State  */
VAR(uint8, DEM_VAR_INIT)  Dem_GlobalConfigPtrInitState = DEM_CONFIGVALIDATION_CONFIGPTR_UNINITIALIZED;                           /* PRQA S 3406 */ /* MD_DEM_8.6 */

#define DEM_STOP_SEC_VAR_INIT_8BIT_RESTRICTED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_ConfigValidation_PrivateProperties Private Properties
 * \{
 */

/* ****************************************************************************
 * Dem_ConfigValidation_IsInitializationWithConfigPointerEnabled
 *****************************************************************************/
/*!
 * \brief         Returns if Config Pointer is used for initialization
 *
 * \details       Returns if Config Pointer is used for initialization
 *
 * \return        TRUE
 *                Feature Initialization using Config Pointer is enabled.
 *                FALSE
 *                Feature Initialization using Config Pointer is not enabled.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ConfigValidation_IsInitializationWithConfigPointerEnabled(
  void
  );

/* ****************************************************************************
 * Dem_ConfigurationValidation_GetGlobalConfigPointerInitState
 *****************************************************************************/
/*!
 * \brief         Returns Global Config Pointer initialization state 
 *
 * \details       Returns Global Config Pointer initialization state 
 *
 * \return        Value of Global Config Pointer initialization state 
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_ConfigurationValidation_GetGlobalConfigPointerInitState(
  void
  );

/* ****************************************************************************
 * Dem_ConfigurationValidation_SetGlobalConfigPointer
 *****************************************************************************/
/*!
 * \brief         Sets Global Config Pointer 
 *
 * \details       Sets Global Config Pointer 
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ConfigurationValidation_SetGlobalConfigPointer(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_ConfigValidation_PrivateProperties
 * \{
 */

/* ****************************************************************************
 % Dem_ConfigValidation_IsInitializationWithConfigPointerEnabled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ConfigValidation_IsInitializationWithConfigPointerEnabled(                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return (boolean)(DEM_CFG_USE_INIT_POINTER == STD_ON);
}

 /* ****************************************************************************
 % Dem_ConfigurationValidation_GetGlobalConfigPointerInitState
 *****************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_ConfigurationValidation_GetGlobalConfigPointerInitState(
  void
  )
{
  return Dem_GlobalConfigPtrInitState;
}

 /* ****************************************************************************
 % Dem_ConfigurationValidation_SetGlobalConfigPointer
 *****************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ConfigurationValidation_SetGlobalConfigPointer(                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr
  )
{
#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
  Dem_GlobalConfigPtr = ConfigPtr;
#else
  DEM_IGNORE_UNUSED_ARGUMENT(ConfigPtr)                                                                                          /* PRQA S 1338, 3112 */ /*  MD_MSR_DummyStmt, MD_DEM_14.2 */
#endif
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
 * \addtogroup Dem_ConfigValidation_Public_Properties
 * \{
 */

 /* ****************************************************************************
 % Dem_ConfigurationValidation_SetGlobalConfigPointerInitState
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ConfigurationValidation_SetGlobalConfigPointerInitState(
  uint8 GlobalConfigPtrInitState
  )
{
  Dem_GlobalConfigPtrInitState = GlobalConfigPtrInitState;
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE API DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_ConfigValidation_PrivateAPI Private APIs
 * \{
 */

#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
/* ****************************************************************************
 * Dem_ConfigValidation_IsPBLConfigPointerValid
 *****************************************************************************/
/*!
 * \brief         Returns whether passed config pointer is valid.
 *
 * \details       Function verifies whether config pointer used to initialize a 
 *                post build loadable configuration is valid.
 *
 * \param[in]     ConfigPtr
 *                Configuration pointer
 *
 * \return        TRUE
 *                Config Pointer is valid.
 *                FALSE
 *                Config Pointer is not valid.
 *
 * \pre           -
 *
 * \config        (DEM_CFG_USE_INIT_POINTER == STD_ON)
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_ConfigValidation_IsPBLConfigPointerValid(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE API DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_ConfigValidation_PrivateAPI
 * \{
 */

#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
 /* ****************************************************************************
 % Dem_ConfigValidation_IsPBLConfigPointerValid
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_ConfigValidation_IsPBLConfigPointerValid(                                                                                    
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr
  )
{
  boolean lConfigPtrValid;

  DEM_IGNORE_UNUSED_ARGUMENT(ConfigPtr)                                                                                          /* PRQA S 1338, 3112 */ /*  MD_MSR_DummyStmt, MD_DEM_14.2 */
# if (DEM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
  lConfigPtrValid = FALSE;
  if (Dem_Cfg_InitPtrFinalMagicNumber(ConfigPtr) != DEM_CFG_FINAL_MAGIC_NUMBER)                                                  /* SBSW_DEM_POINTER_FORWARD_API */
  {
    EcuM_BswErrorHook((uint16) DEM_MODULE_ID, (uint8) ECUM_BSWERROR_MAGICNUMBER);
  }
  else
  if (Dem_Cfg_InitPtrCompatibilityVersion(ConfigPtr) != DEM_CFG_GEN_COMPATIBILITY_VERSION)                                       /* SBSW_DEM_POINTER_FORWARD_API */
  {
    EcuM_BswErrorHook((uint16) DEM_MODULE_ID, (uint8) ECUM_BSWERROR_COMPATIBILITYVERSION);
  }
  else
# endif
  {
    lConfigPtrValid = TRUE;
  }

  return lConfigPtrValid;
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_ConfigValidation_Public
 * \{
 */

 /* ****************************************************************************
 % Dem_ConfigurationValidation_TestGlobalCfgPointerInState
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ConfigurationValidation_TestGlobalCfgPointerInState(                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  uint8 GlobalConfigPtrInitState
  )
{
  boolean lRetVal;

  lRetVal = TRUE;
  if (Dem_ConfigValidation_IsInitializationWithConfigPointerEnabled() == TRUE)
  {
    lRetVal = (boolean)(Dem_ConfigurationValidation_GetGlobalConfigPointerInitState() == GlobalConfigPtrInitState);
  }

  return lRetVal;
}


 /* ****************************************************************************
 % Dem_ConfigurationValidation_TestGlobalCfgPointerAtleastInState
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ConfigurationValidation_TestGlobalCfgPointerAtleastInState(                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  uint8 GlobalConfigPtrInitState
  )
{
  boolean lRetVal;

  lRetVal = TRUE;
  if (Dem_ConfigValidation_IsInitializationWithConfigPointerEnabled() == TRUE)
  {
    lRetVal = (boolean)(Dem_ConfigurationValidation_GetGlobalConfigPointerInitState() >= GlobalConfigPtrInitState);
  }

  return lRetVal;
}

#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
 /* ****************************************************************************
 % Dem_ConfigurationValidation_ValidateAndSetConfigPtr
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_ConfigurationValidation_ValidateAndSetConfigPtr(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr
  )
{
  /* With this function call, the global config pointer state is finalized
     in any condition. If the new pointer is not valid, the config pointer
     used in preinit stage is finalized */
  Std_ReturnType lReturnValue;
  
  if (Dem_ConfigValidation_IsPBLConfigPointerValid(ConfigPtr) == FALSE)                                                          /* SBSW_DEM_POINTER_FORWARD_API */
  {
    lReturnValue = E_NOT_OK;
  }
  else
  {
    Dem_ConfigurationValidation_SetGlobalConfigPointer(ConfigPtr);                                                               /* SBSW_DEM_POINTER_FORWARD_API */
    lReturnValue = E_OK;
  }

  return lReturnValue;
}
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_CONFIGVALIDATION_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_APIChecks_Implementation.h
 *********************************************************************************************************************/
