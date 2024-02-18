/**
*   @file     Wdg_Cfg.h
*   @implements Wdg_Cfg.h_Artifact
*   @version  1.0.1
*
*   @brief    AUTOSAR Wdg - Contains the implementation of the Watchdog API
*   @details  It contains the layer requested by autosar. The functions are independent of
*             hardware settings.
*
*   @addtogroup  Wdg  
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.3 MCAL
*   Platform             : ARM
*   Peripheral           : Wdog
*   Dependencies         : none
*
*   Autosar Version      : 4.3.1
*   Autosar Revision     : ASR_REL_4_3_REV_0001
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : S32K14x_MCAL_1_0_1_RTM_HF4_ASR_REL_4_3_REV_0001_20201126
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2019 NXP
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef WDG_CFG_H
#define WDG_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Wdg_Cfg_h_REF_1
*          Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to
*          prevent the contents of a header file being included twice. All header files are
*          protected against multiple inclusions.
*
* @section Wdg_Cfg_h_REF_2
*          Violates MISRA 2004 Required Rule 19.4, C macros shall only expand to a braced initialiser, 
*          a constant, a parenthesised expression, a type qualifier, a storage class specifier, or a
*          do-while-zero construct. 
*          This is used to abstract the export of configuration sets
*
* @section [global]
*          Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
*          on the significance of more than 31 characters. The used compilers use more than 31 chars 
*          for identifiers.
*
* @section Wdg_Cfg_h_REF_3
*          Violates MISRA 2004 Required Rule 8.7, Objects shall be defined at block scope if they are 
*          only accessed from within a single function.
*          These objects are used in various parts of the code
*
* @section [global]
*          Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
*          that 31 character significance and case sensitivity are supported for external identifiers.
*          The defines are validated.
*
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "WdgIf_Types.h"
/** @violates @ref Wdg_Cfg_h_REF_1 MISRA 2004 Required Rule 19.15 precautions to prevent the contents
 *                of a header file being included twice */
#include "Mcal.h"


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @file           Wdg_Cfg.h
*/
#define WDG_VENDOR_ID_CFG                    43
#define WDG_MODULE_ID_CFG                    102
#define WDG_AR_RELEASE_MAJOR_VERSION_CFG     4
#define WDG_AR_RELEASE_MINOR_VERSION_CFG     3
#define WDG_AR_RELEASE_REVISION_VERSION_CFG  1
#define WDG_SW_MAJOR_VERSION_CFG             1
#define WDG_SW_MINOR_VERSION_CFG             0
#define WDG_SW_PATCH_VERSION_CFG             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/



/* Check if source file and WdgIf_Types header file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if (( WDG_AR_RELEASE_MAJOR_VERSION_CFG != WDGIF_TYPES_AR_RELEASE_MAJOR_VERSION) || \
         ( WDG_AR_RELEASE_MINOR_VERSION_CFG != WDGIF_TYPES_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Wdg_Cfg.h and WdgIf_Types.h are different"
    #endif
#endif


/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/
#define WDG_START_SEC_CONST_UNSPECIFIED
/**
* @brief Include Memory mapping specification
* @violates @ref Wdg_Cfg_h_REF_1 MISRA 2004 Required Rule 19.15 precautions to prevent the contents
*                of a header file being included twice*/
#include "Wdg_MemMap.h"
 /**
 * @brief Dem error codes
 */

#define WDG_STOP_SEC_CONST_UNSPECIFIED
/**
* @brief Include Memory mapping specification
* @violates @ref Wdg_Cfg_h_REF_1 MISRA 2004 Required Rule 19.15 precautions to prevent the contents
*                of a header file being included twice
*/
#include "Wdg_MemMap.h"
 /**
 * @brief Dem error codes
 */

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/








/**
  * @brief  This constant specifies if the instance of the WDG is selected or not
  */
#define WDG_INSTANCE0 (STD_ON)




/**
  * @brief  This constant specifies if the instance of the WDG is selected or not
  */
#define WDG_INSTANCE1 (STD_OFF)




/**
  * @brief  This constant specifies if the instance of the WDG is selected or not
  */
#define WDG_INSTANCE2 (STD_OFF)




/**
  * @brief  This constant specifies if the instance of the WDG is selected or not
  */
#define WDG_INSTANCE3 (STD_OFF)




/**
* @brief  This define indicate that the watchdog is internal
*/
#define WDG_INTERNAL_MODULE         (0U)

/**
* @brief  This define indicate that the watchdog is external connected on SPI
*/
#define WDG_EXTERNAL_MODULE_SPI     (1U)

/**
* @brief  This define indicate that the watchdog is external connected on DIO
*/
#define WDG_EXTERNAL_MODULE_DIO     (2U)

 /**
 * @brief  This define indicate the number of HW IPs available on the Platform
 */
#define WDG_NO_OF_INSTANCES            (1U)
/**
* @brief  This variable will indicate which type of driver is in use
*/
#define WDG_TYPE (          WDG_INTERNAL_MODULE)


/**
* @brief  Compile switch to enable/disable development error detection for this module
*/
#define WDG_DEV_ERROR_DETECT   (STD_ON)
/**
* @brief  Compile switch to enable/disable the validation of the configuration update by Wdg_SetMode API
*/
#define WDG_VALIDATE_CONFIG_UPDATE      (STD_ON)
/** 
* @brief  Switch to globaly enable/disable the production error reporting.
*/
#define WDG_DISABLE_DEM_REPORT_ERROR_STATUS           (STD_ON)

/**
* @brief  Compile switch to allow/forbid disabling the watchdog driver during runtime
*/
#define WDG_DISABLE_ALLOWED    (STD_OFF)

/**
* @brief  Compile switch to enable/disable the version information
*/
#define WDG_VERSION_INFO_API   (STD_ON)

/**
* @brief  This variable will indicate the index of instance 0
*/
#define WdgConf_WdgGeneral_WdgIndex_U8 ((uint8)0)

/**
* @brief  This variable will indicate the Wdg Initial Timeout parameter in miliseconds
*/
#define WDG_INITIAL_TIMEOUT_U16 ((uint16)0)

/**
* @brief  This variable will indicate the Wdg Max Timeout parameter in miliseconds
*/
#define WDG_MAX_TIMEOUT_U16     ((uint16)0)

/**
* @brief  This macro indicate Wdg Max Timeout to fix compiler warning comparision always true
*/
#define WDG_MAX_TIMEOUT_VALUE (0U)
/**
* @brief  This macro will indicate max value of 16bits integer type
*/
#define WDG_MAX_VALUE_TYPE16      (65535U)

/**
* @brief  This define indicate that the watchdog is Enable or Disable User mode support
*/
#define WDG_ENABLE_USER_MODE_SUPPORT    (STD_OFF)


#ifdef WDG_ENABLE_USER_MODE_SUPPORT
    #if(STD_ON == WDG_ENABLE_USER_MODE_SUPPORT)
        /**
        * @brief  This define indicate that the ipv SWT is protected by register protection 
        */
        #define WDG_WDOG_REG_PROT_AVAILABLE
    #endif /* (STD_ON == WDG_ENABLE_USER_MODE_SUPPORT) */
#endif /* ifdef WDG_ENABLE_USER_MODE_SUPPORT */

/**
* @brief  perform checking marco MCAL_ENABLE_USER_MODE_SUPPORT available or not.
*/
#ifndef MCAL_ENABLE_USER_MODE_SUPPORT
    #if (STD_ON == WDG_ENABLE_USER_MODE_SUPPORT)
        #error MCAL_ENABLE_USER_MODE_SUPPORT is not enabled. For running Wdg in user mode, the MCAL_ENABLE_USER_MODE_SUPPORT needs to be defined
    #endif /* (STD_ON == WDG_ENABLE_USER_MODE_SUPPORT) */
#endif /* ifndef MCAL_ENABLE_USER_MODE_SUPPORT */




/**
* @brief  This variable will indicate if the ISR0 is used
*/
#define  WDG_ISR0_USED







/** 
* @brief  This variable will indicate RAM/ROM execution
*/
#define WDG_ROM


 

/**
* @brief Defines the use of Pre compile (PC) support
*/
              


#define WDG_PRECOMPILE_SUPPORT  (STD_ON)



 
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                   FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* WDG_CFG_H */
/** @} */
