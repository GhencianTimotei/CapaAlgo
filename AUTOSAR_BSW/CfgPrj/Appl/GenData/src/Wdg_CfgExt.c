
/**
* @file    Wdg_CfgExt.c
* @version 1.0.1
* @brief   AUTOSAR Wdg - contains the data exported by the watchodg module
* @details Contains the information that will be exported by the module, as requested by Autosar.
*
* @addtogroup  Wdg
* @{
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

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Wdg_Cfg_c_REF_1
*          Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements
*          and comments before '#include'. This is an Autosar requirement about
*          the memory management (Autosar requirement MEMMAP003).
*
* @section Wdg_Cfg_c_REF_2
*          Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to
*          prevent the contents of a header file being included twice. All header files are
*          protected against multiple inclusions.
*
* @section Wdg_Cfg_c_REF_3
*          Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
*          that 31 character significance and case sensitivity are supported for external identifiers.
*          The defines are validated.
*
* @section Wdg_Cfg_c_REF_4
*          Violates MISRA 2004 Required Rule 8.10, All declarations and definitions of objects or
*          functions at file scope shall have internal linkage unless external linkage is required.
*          The functions/variables are part of external configuration
*
* @section [global]
*          Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
*          on the significance of more than 31 characters. The used compilers use more than 31 chars 
*          for identifiers.
*
*/


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/**
* @file           Wdg_CfgExt.c
*/

#include "Wdg_Channel.h"
#if (WDG_TYPE == WDG_INTERNAL_MODULE)
    #include "Reg_eSys_Wdog_defines.h"
#endif


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @file           Wdg_CfgExt.c
*/
#define WDG_VENDOR_ID_CFG_C                    43
/** @violates @ref Wdg_Cfg_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure
 *  that 31 character significance and case sensitivity are supported for external identifiers. */
#define WDG_AR_RELEASE_MAJOR_VERSION_CFG_C     4
/** @violates @ref Wdg_Cfg_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure
 *  that 31 character significance and case sensitivity are supported for external identifiers. */
#define WDG_AR_RELEASE_MINOR_VERSION_CFG_C     3
/** @violates @ref Wdg_Cfg_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure
*  that 31 character significance and case sensitivity are supported for external identifiers. */
#define WDG_AR_RELEASE_REVISION_VERSION_CFG_C  1
#define WDG_SW_MAJOR_VERSION_CFG_C             1
#define WDG_SW_MINOR_VERSION_CFG_C             0
#define WDG_SW_PATCH_VERSION_CFG_C             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Wdg header file are of the same vendor */
#if (WDG_VENDOR_ID_CFG_C != WDG_CHANNEL_VENDOR_ID)
    #error "Wdg_CfgExt.c and Wdg_Channel.h have different vendor ids"
#endif

/* Check if current file and Wdg header file are of the same Autosar version */
#if ((WDG_AR_RELEASE_MAJOR_VERSION_CFG_C    != WDG_CHANNEL_AR_RELEASE_MAJOR_VERSION) || \
     (WDG_AR_RELEASE_MINOR_VERSION_CFG_C    != WDG_CHANNEL_AR_RELEASE_MINOR_VERSION) || \
     (WDG_AR_RELEASE_REVISION_VERSION_CFG_C != WDG_CHANNEL_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AutoSar Version Numbers of Wdg_CfgExt.c and Wdg_Channel.h are different"
#endif
/* Check if current file and Wdg header file are of the same Software version */
#if ((WDG_SW_MAJOR_VERSION_CFG_C != WDG_CHANNEL_SW_MAJOR_VERSION) || \
     (WDG_SW_MINOR_VERSION_CFG_C != WDG_CHANNEL_SW_MINOR_VERSION) || \
     (WDG_SW_PATCH_VERSION_CFG_C != WDG_CHANNEL_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Wdg_CfgExt.c and Wdg_Channel.h are different"
#endif

#if (WDG_TYPE == WDG_INTERNAL_MODULE)
    /* Check if current file and Reg_eSys_Wdog header file are of the same vendor */
    #if (WDG_VENDOR_ID_CFG_C != REG_ESYS_WDOG_DEFINES_VENDOR_ID)
        #error "Wdg_CfgExt.c and Reg_eSys_Wdog_defines.h have different vendor ids"
    #endif
    
    /* Check if current file and Reg_eSys_Wdog header file are of the same Autosar version */
    #if ((WDG_AR_RELEASE_MAJOR_VERSION_CFG_C != REG_ESYS_WDOG_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
         (WDG_AR_RELEASE_MINOR_VERSION_CFG_C != REG_ESYS_WDOG_DEFINES_AR_RELEASE_MINOR_VERSION) || \
         (WDG_AR_RELEASE_REVISION_VERSION_CFG_C != REG_ESYS_WDOG_DEFINES_AR_RELEASE_REVISION_VERSION) \
        )
        #error "AutoSar Version Numbers of Wdg_CfgExt.c and Reg_eSys_Wdog_defines.h are different"
    #endif
    
    /* Check if current file and Reg_eSys_Wdog header file are of the same Software version */
    #if ((WDG_SW_MAJOR_VERSION_CFG_C != REG_ESYS_WDOG_DEFINES_SW_MAJOR_VERSION) || \
         (WDG_SW_MINOR_VERSION_CFG_C != REG_ESYS_WDOG_DEFINES_SW_MINOR_VERSION) || \
         (WDG_SW_PATCH_VERSION_CFG_C != REG_ESYS_WDOG_DEFINES_SW_PATCH_VERSION) \
        )
        #error "Software Version Numbers of Wdg_CfgExt.c and Reg_eSys_Wdog_defines.h are different"
    #endif
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/

#define WDG_START_SEC_CONST_8
/**
* @brief Include Memory mapping specification
* @violates @ref Wdg_Cfg_c_REF_1 MISRA 2004 Advisory Rule 19.1 , only preprocessor statements
*                and comments before '#include'
* @violates @ref Wdg_Cfg_c_REF_2 MISRA 2004 Required Rule 19.15 precautions to prevent the contents
*                of a header file being included twice
*/
#include "Wdg_MemMap.h"
/** @violates @ref Wdg_Cfg_c_REF_4 MISRA 2004 Required Rule 8.10 External Linkage */
CONST(uint8, WDG_CONST) Wdg_au8Index[WDG_NO_OF_INSTANCES] = 
{
    WdgConf_WdgGeneral_WdgIndex_U8
};

#define WDG_STOP_SEC_CONST_8
/**
* @brief Include Memory mapping specification
* @violates @ref Wdg_Cfg_c_REF_1 MISRA 2004 Advisory Rule 19.1 , only preprocessor statements
*                and comments before '#include'
* @violates @ref Wdg_Cfg_c_REF_2 MISRA 2004 Required Rule 19.15 precautions to prevent the contents
*                of a header file being included twice
*/
#include "Wdg_MemMap.h"

#define WDG_START_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @brief Include Memory mapping specification
* @violates @ref Wdg_Cfg_c_REF_1 MISRA 2004 Advisory Rule 19.1 , only preprocessor statements
*                and comments before '#include'
* @violates @ref Wdg_Cfg_c_REF_2 MISRA 2004 Required Rule 19.15 precautions to prevent the contents
*                of a header file being included twice
*/
#include "Wdg_MemMap.h"




extern CONST(Wdg_ConfigType, WDG_CONST) WdgSettingsConfig;


CONSTP2CONST(Wdg_ConfigType, WDG_VAR, WDG_APPL_CONST) Wdg_apPBCfgVariantPredefined[WDG_NO_OF_INSTANCES]={


&WdgSettingsConfig
};



 
#define WDG_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @brief Include Memory mapping specification
* @violates @ref Wdg_Cfg_c_REF_1 MISRA 2004 Required Rule 19.1 , only preprocessor statements
*                and comments before '#include'
* @violates @ref Wdg_Cfg_c_REF_2 MISRA 2004 Required Rule 19.15 precautions to prevent the contents
*                of a header file being included twice
*/
#include "Wdg_MemMap.h"

#define WDG_START_SEC_CONST_UNSPECIFIED
/**
* @brief Include Memory mapping specification
* @violates @ref Wdg_Cfg_c_REF_1 MISRA 2004 Required Rule 19.1 , only preprocessor statements
*                and comments before '#include'
* @violates @ref Wdg_Cfg_c_REF_2 MISRA 2004 Required Rule 19.15 precautions to prevent the contents
*                of a header file being included twice
*/
#include "Wdg_MemMap.h"








#define WDG_STOP_SEC_CONST_UNSPECIFIED
/**
* @brief Include Memory mapping specification
* @violates @ref Wdg_Cfg_c_REF_1 MISRA 2004 Advisory Rule 19.1 , only preprocessor statements
*                and comments before '#include'
* @violates @ref Wdg_Cfg_c_REF_2 MISRA 2004 Required Rule 19.15 precautions to prevent the contents
*                of a header file being included twice
*/
#include "Wdg_MemMap.h"

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                     GLOBAL FUNCTIONS
==================================================================================================*/
#ifdef __cplusplus
}
#endif

/** @} */
