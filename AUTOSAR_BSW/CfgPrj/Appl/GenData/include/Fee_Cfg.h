/**
*   @file    Fee_Cfg.h
*   @implements Fee_Cfg.h_Artifact
*   @version 1.0.1
*
*   @brief   AUTOSAR Fee - AUTOSAR Module Flash EEPROM Emulation Driver.
*   @details Definitions of all pre-compile configuration parameters..
*
*   @addtogroup FEE
*   @{

*/
/*==================================================================================================
*   Project              : AUTOSAR 4.3 MCAL
*   Platform             : ARM
*   Peripheral           : none
*   Dependencies         : Fls
*
*   Autosar Version      : 4.3.1
*   Autosar Revision     : ASR_REL_4_3_REV_0001
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : S32K14x_MCAL_1_0_1_RTM_ASR_REL_4_3_REV_0001_20190621
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2019 NXP
*   All Rights Reserved.
==================================================================================================*/

#ifndef FEE_CFG_H
#define FEE_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Fee_cfg_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file.
* Repeatedly included but does not have a standard include guard due to AUTOSAR
* requirement MEMMAP003.
*
* @section Fee_cfg_h_REF_2
* Violates MISRA 2004 Required Rule 19.4, Disallowed definition for a macro.
*
* @section [global]
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external
* identifiers.
* Block name symbol defines are too long, handled by preprocessor.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifier exceeds 31 characters due to
* AUTOSAR compatibility.
*
*/

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Fee_Types.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @implements   VendorId_Object */
#define FEE_VENDOR_ID_CFG                    43
/** @implements   ModuleId_Object */
#define FEE_MODULE_ID_CFG                    21
/** @implements   ArReleaseMajorVersion_Object */
#define FEE_AR_RELEASE_MAJOR_VERSION_CFG     4
/** @implements   ArReleaseMinorVersion_Object */
#define FEE_AR_RELEASE_MINOR_VERSION_CFG     3
/** @implements   ArReleaseRevisionVersion_Object */
#define FEE_AR_RELEASE_REVISION_VERSION_CFG  1
/** @implements   SwMajorVersion_Object */
#define FEE_SW_MAJOR_VERSION_CFG             1
/** @implements   SwMinorVersion_Object */
#define FEE_SW_MINOR_VERSION_CFG             0
/** @implements   SwPatchVersion_Object */
#define FEE_SW_PATCH_VERSION_CFG             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and MODULENAME configuration header file are of the same vendor */
#if (FEE_VENDOR_ID_CFG != FEE_TYPES_VENDOR_ID)
    #error "Fee_Types.h and Fee_Cfg.h have different vendor ids"
#endif
/* Check if current file and MODULENAME configuration header file are
   of the same Autosar version
*/
#if ((FEE_AR_RELEASE_MAJOR_VERSION_CFG    != FEE_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (FEE_AR_RELEASE_MINOR_VERSION_CFG    != FEE_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (FEE_AR_RELEASE_REVISION_VERSION_CFG != FEE_TYPES_AR_RELEASE_REVISION_VERSION)\
    )
    #error "AutoSar Version Numbers of Fee_Types.h and Fee_Cfg.h are different"
#endif
/* Check if current file and MODULENAME configuration header file are
   of the same software version
*/
#if ((FEE_SW_MAJOR_VERSION_CFG != FEE_TYPES_SW_MAJOR_VERSION) || \
     (FEE_SW_MINOR_VERSION_CFG != FEE_TYPES_SW_MINOR_VERSION) || \
     (FEE_SW_PATCH_VERSION_CFG != FEE_TYPES_SW_PATCH_VERSION)\
    )
    #error "Software Version Numbers of Fee_Types.h and Fee_Cfg.h are different"
#endif


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/* Pre-processor switch to enable and disable development error detection */
/** @implements   FeeDevErrorDetect_Object */
#define FEE_DEV_ERROR_DETECT                (STD_OFF)

/* Pre-processor switch to enable / disable the API to read out the modules
    version information */
/** @implements   FeeVersionInfoApi_Object */
#define FEE_VERSION_INFO_API                (STD_ON)

/* Compiler switch to enable/disable the SetMode functionality of the module */
/** @implements   FeeSetModeSupported_Object */
#define FEE_SETMODE_API_SUPPORTED           (STD_ON)

/* Pre-processor switch to enable /disable the Fls_Cancel function of the module */
#define FEE_CANCEL_API                     (STD_ON)

/* The size in bytes to which logical blocks shall be aligned */
/** @implements   FeeVirtualPageSize_Object */
#define FEE_VIRTUAL_PAGE_SIZE               8U

/* Job end notification routine provided by the upper layer module (declaration) */
/** @implements   FeeNvmJobEndNotification_Object */
/* @violates @ref Fee_cfg_h_REF_2 Disallowed definition for macro */
#define FEE_NVM_JOB_END_NOTIFICATION_DECL   extern void NvM_JobEndNotification(void);

/* Job end notification routine provided by the upper layer module */
/** @implements   FeeNvmJobEndNotification_Object */
/* @violates @ref Fee_cfg_h_REF_2 Disallowed definition for macro */
#define FEE_NVM_JOB_END_NOTIFICATION        NvM_JobEndNotification();

/* Job error notification routine provided by the upper layer module (declaration) */
/** @implements   FeeNvmJobErrorNotification_Object */
/* @violates @ref Fee_cfg_h_REF_2 Disallowed definition for macro */
#define FEE_NVM_JOB_ERROR_NOTIFICATION_DECL  extern void DemDtc_NvM_JobErrorNotification(void);

/* Job error notification routine provided by the upper layer module */
/** @implements   FeeNvmJobErrorNotification_Object */
/* @violates @ref Fee_cfg_h_REF_2 Disallowed definition for macro */
#define FEE_NVM_JOB_ERROR_NOTIFICATION       DemDtc_NvM_JobErrorNotification();

/* Job cluster format notification routine provided by the upper layer module (declaration) */
/* @violates @ref Fee_cfg_h_REF_2 Disallowed definition for macro */
#define FEE_NVM_CLUSTER_FORMAT_NOTIFICATION_DECL  extern void Fee_ClusterFormatNotif(void);

/* Job cluster format notification routine provided by the upper layer module */
/* @violates @ref Fee_cfg_h_REF_2 Disallowed definition for macro */
#define FEE_NVM_CLUSTER_FORMAT_NOTIFICATION       Fee_ClusterFormatNotif();

/* Number of configured Fee cluster groups */
#define FEE_NUMBER_OF_CLUSTER_GROUPS        1U

/* Number of configured Fee blocks */
#define FEE_CRT_CFG_NR_OF_BLOCKS                106U

/* Maximum number of Fee blocks in all project versions and configurations */
#define FEE_MAX_NR_OF_BLOCKS        (FEE_CRT_CFG_NR_OF_BLOCKS)
/* Management overhead per logical block in bytes */
/** @implements   FeeBlockOverhead_Object */
#define FEE_BLOCK_OVERHEAD                  32U

/* Management overhead per logical cluster in bytes */
#define FEE_CLUSTER_OVERHEAD                32U

/* Size of the data buffer in bytes */
#define FEE_DATA_BUFFER_SIZE                96U

/* The contents of an erased flash memory cell */
#define FEE_ERASED_VALUE                    0xffU

/* Value of the block and cluster validation flag */
#define FEE_VALIDATED_VALUE                0x81U

/* Value of the block and cluster invalidation flag */
#define FEE_INVALIDATED_VALUE              0x18U

/* If reset, power loss etc. occurs here, neither newly nor previously written data is available */
#define FEE_BLOCK_ALWAYS_AVAILABLE          (STD_OFF)

/* Compile switch to enable Legacy mode (original FEE immediate data handling) */
#define FEE_LEGACY_MODE                     (STD_ON)

/* Behavior of Fee_ImmediateBlockErase */
#define FEE_LEGACY_IMM_ERASE_MODE           (STD_OFF)

/* This configuration defines wheather Fee should swap foreign blocks found in flash at swap or not */
#define FEE_SWAP_FOREIGN_BLOCKS_ENABLED          (STD_OFF)

/* This configuration defines for which project the Fee configuration is used  */
#define FEE_BOOTLOADER_CONFIG           (STD_OFF)

/* This configuration defines if the status for the never written blocks must be INVALID or INCONSISTENT */
#define FEE_MARK_EMPTY_BLOCKS_INVALID    (STD_OFF)

/* Symbolic names of configured Fee blocks */
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_012     64U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_007     128U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_015     192U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_017     256U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_020     320U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_025     384U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_065     448U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_023     512U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_035     576U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_040     640U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_043     704U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_010     768U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_052     832U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_058     896U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_059     960U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_011     1024U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_013     1088U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_006     1152U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_009     1216U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_008     1280U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_005     1344U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_014     1408U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_016     1472U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_003     1536U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_004     1600U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_001     1664U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_002     1728U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_018     1792U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_026     1856U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_061     1920U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_062     1984U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_062_cons0     1985U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_024     2048U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_021     2112U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_041     2176U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_053     2240U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_027     2304U
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_066     2368U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_019     2432U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064     2496U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons0     2497U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons1     2498U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons2     2499U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons3     2500U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons4     2501U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons5     2502U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons6     2503U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons7     2504U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons8     2505U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons9     2506U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons10     2507U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons11     2508U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons12     2509U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons13     2510U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons14     2511U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons15     2512U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons16     2513U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons17     2514U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons18     2515U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons19     2516U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons20     2517U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons21     2518U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons22     2519U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons23     2520U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons24     2521U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons25     2522U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons26     2523U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons27     2524U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons28     2525U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons29     2526U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons30     2527U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons31     2528U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons32     2529U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons33     2530U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons34     2531U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons35     2532U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons36     2533U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons37     2534U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons38     2535U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons39     2536U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons40     2537U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons41     2538U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons42     2539U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons43     2540U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons44     2541U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons45     2542U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons46     2543U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons47     2544U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons48     2545U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons49     2546U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons50     2547U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons51     2548U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_064_cons52     2549U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_063     2560U
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration     2624U
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_cons0     2625U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_022     2688U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_038     2752U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_044     2816U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_066     2880U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_067     2944U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_068     3008U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_069     3072U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_070     3136U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_071     3200U
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_072     3264U


#define FEE_START_SEC_CONST_UNSPECIFIED
/* @violates @ref Fee_cfg_h_REF_1 Repeated include file */
#include "Fee_MemMap.h"

       




/* Configuration of cluster group set */
extern CONST(Fee_ClusterGroupType, FEE_CONST) Fee_ClrGrps[ FEE_NUMBER_OF_CLUSTER_GROUPS ];

/* Configuration of Fee blocks */
extern CONST(Fee_BlockConfigType, FEE_CONST) Fee_BlockConfig[ FEE_CRT_CFG_NR_OF_BLOCKS ];

#define FEE_STOP_SEC_CONST_UNSPECIFIED
/* @violates @ref Fee_cfg_h_REF_1 Repeated include file */
#include "Fee_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* FEE_CFG_H */
/** @} */
