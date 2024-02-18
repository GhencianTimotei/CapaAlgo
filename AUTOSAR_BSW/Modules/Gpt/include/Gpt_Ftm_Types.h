/**
*   @file           Gpt_Ftm_Types.h
*   @version        1.0.1
*
*   @brief          AUTOSAR Gpt - Ftm data types header file.
*   @details        Ftm defines, types used by GPT driver.
*
*   @addtogroup     PWM_MODULE
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.3 MCAL
*   Platform             : ARM
*   Peripheral           : Ftm
*   Dependencies         : none
*
*   Autosar Version      : 4.3.1
*   Autosar Revision     : ASR_REL_4_3_REV_0001
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : S32K14x_MCAL_1_0_1_RTM_HF3_ASR_REL_4_3_REV_0001_20201116
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2019 NXP
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef GPT_FTM_TYPES_H
#define GPT_FTM_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
* 
* @section [global]
*       Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
*       on the significance of more than 31 characters. The used compilers use more than 31 chars
*       for identifiers
*/

/*===============================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
===============================================================================================*/
#include "Ftm_Common_Types.h"

#include "Reg_eSys_Ftm.h"

#include "Gpt_EnvCfg.h"
#include "Gpt_Cfg.h"

/*===============================================================================================
*                               SOURCE FILE VERSION INFORMATION
===============================================================================================*/

#define GPT_FTM_TYPES_VENDOR_ID                       43
#define GPT_FTM_TYPES_MODULE_ID                       100
#define GPT_FTM_TYPES_AR_RELEASE_MAJOR_VERSION        4
#define GPT_FTM_TYPES_AR_RELEASE_MINOR_VERSION        3
#define GPT_FTM_TYPES_AR_RELEASE_REVISION_VERSION     1
#define GPT_FTM_TYPES_SW_MAJOR_VERSION                1
#define GPT_FTM_TYPES_SW_MINOR_VERSION                0
#define GPT_FTM_TYPES_SW_PATCH_VERSION                1

/*===============================================================================================
*                                      FILE VERSION CHECKS
===============================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK

#if (GPT_FTM_TYPES_VENDOR_ID != FTM_COMMON_TYPES_VENDOR_ID)
    #error "Gpt_Ftm_Types.h and Ftm_Common_Types.h have different vendor ids"
#endif
/* Check if the header files are of the same Autosar version */
#if ((GPT_FTM_TYPES_AR_RELEASE_MAJOR_VERSION != FTM_COMMON_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (GPT_FTM_TYPES_AR_RELEASE_MINOR_VERSION != FTM_COMMON_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (GPT_FTM_TYPES_AR_RELEASE_REVISION_VERSION != FTM_COMMON_TYPES_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Gpt_Ftm_Types.h and Ftm_Common_Types.h are different"
#endif
/* Check if the header files are of the same Software version */
#if ((GPT_FTM_TYPES_SW_MAJOR_VERSION != FTM_COMMON_TYPES_SW_MAJOR_VERSION) || \
     (GPT_FTM_TYPES_SW_MINOR_VERSION != FTM_COMMON_TYPES_SW_MINOR_VERSION) || \
     (GPT_FTM_TYPES_SW_PATCH_VERSION != FTM_COMMON_TYPES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Gpt_Ftm_Types.h and Ftm_Common_Types.h are different"
#endif

    #if (GPT_FTM_TYPES_VENDOR_ID != REG_ESYS_FTM_VENDOR_ID)
        #error "Gpt_Ftm_Types.h and Reg_eSys_Ftm.h have different vendor ids"
    #endif
    /* Check if the header files are of the same Autosar version */
    #if ((GPT_FTM_TYPES_AR_RELEASE_MAJOR_VERSION != REG_ESYS_FTM_AR_RELEASE_MAJOR_VERSION) || \
        (GPT_FTM_TYPES_AR_RELEASE_MINOR_VERSION != REG_ESYS_FTM_AR_RELEASE_MINOR_VERSION) || \
        (GPT_FTM_TYPES_AR_RELEASE_REVISION_VERSION != REG_ESYS_FTM_AR_RELEASE_REVISION_VERSION))
        #error "AutoSar Version Numbers of Gpt_Ftm_Types.h and Reg_eSys_Ftm.h are different"
    #endif
    /* Check if the header files are of the same Software version */
    #if ((GPT_FTM_TYPES_SW_MAJOR_VERSION != REG_ESYS_FTM_SW_MAJOR_VERSION) || \
        (GPT_FTM_TYPES_SW_MINOR_VERSION != REG_ESYS_FTM_SW_MINOR_VERSION) || \
        (GPT_FTM_TYPES_SW_PATCH_VERSION != REG_ESYS_FTM_SW_PATCH_VERSION))
        #error "Software Version Numbers of Gpt_Ftm_Types.h and Reg_eSys_Ftm.h are different"
    #endif
#endif

#if (GPT_FTM_TYPES_VENDOR_ID != GPT_ENVCFG_VENDOR_ID)
    #error "Gpt_Ftm_Types.h and Gpt_EnvCfg.h have different vendor ids"
#endif
/* Check if the header files are of the same Autosar version */
#if ((GPT_FTM_TYPES_AR_RELEASE_MAJOR_VERSION != GPT_ENVCFG_AR_RELEASE_MAJOR_VERSION) || \
     (GPT_FTM_TYPES_AR_RELEASE_MINOR_VERSION != GPT_ENVCFG_AR_RELEASE_MINOR_VERSION) || \
     (GPT_FTM_TYPES_AR_RELEASE_REVISION_VERSION != GPT_ENVCFG_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Gpt_Ftm_Types.h and Gpt_EnvCfg.h are different"
#endif
/* Check if the header files are of the same Software version */
#if ((GPT_FTM_TYPES_SW_MAJOR_VERSION != GPT_ENVCFG_SW_MAJOR_VERSION) || \
     (GPT_FTM_TYPES_SW_MINOR_VERSION != GPT_ENVCFG_SW_MINOR_VERSION) || \
     (GPT_FTM_TYPES_SW_PATCH_VERSION != GPT_ENVCFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Gpt_Ftm_Types.h and Gpt_EnvCfg.h are different"
#endif

#if (GPT_FTM_TYPES_VENDOR_ID != GPT_VENDOR_ID_CFG)
    #error "Gpt_Ftm_Types.h and Gpt_Cfg.h have different vendor ids"
#endif
/* Check if the header files are of the same Autosar version */
#if ((GPT_FTM_TYPES_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (GPT_FTM_TYPES_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION_CFG) || \
     (GPT_FTM_TYPES_AR_RELEASE_REVISION_VERSION != GPT_AR_RELEASE_REVISION_VERSION_CFG))
    #error "AutoSar Version Numbers of Gpt_Ftm_Types.h and Gpt_Cfg.h are different"
#endif
/* Check if the header files are of the same Software version */
#if ((GPT_FTM_TYPES_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION_CFG) || \
     (GPT_FTM_TYPES_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION_CFG) || \
     (GPT_FTM_TYPES_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION_CFG))
    #error "Software Version Numbers of Gpt_Ftm_Types.h and Gpt_Cfg.h are different"
#endif

/*===============================================================================================
*                                           CONSTANTS
===============================================================================================*/

/*===============================================================================================
*                                       DEFINES AND MACROS
===============================================================================================*/

/*===============================================================================================
*                                             ENUMS
===============================================================================================*/

/*===============================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
===============================================================================================*/

/*===============================================================================================
*                                       DEFINES AND MACROS
===============================================================================================*/

/*===============================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
===============================================================================================*/

/*===============================================================================================
*                                     FUNCTION PROTOTYPES
===============================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* GPT_FTM_TYPES_H */

/** @} */
