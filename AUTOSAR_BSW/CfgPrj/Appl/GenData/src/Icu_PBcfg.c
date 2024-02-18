

/**
 *   @file         Icu_PBCfg.c
 *   @implements Icu_PBCfg.c_Artifact
 *   @version 1.0.1
 *
 *   @brief   AUTOSAR Icu - contains the data exported by the Icu module
 *   @details Contains the information that will be exported by the module, as requested by Autosar.
 *
 *   @addtogroup ICU_MODULE
 *   @{
 */
/*==================================================================================================
 *   Project              : AUTOSAR 4.3 MCAL
 *   Platform             : ARM
 *   Peripheral           : FTM PORT_CI LPIT LPTMR
 *   Dependencies         : none
 *
 *   Autosar Version      : 4.3.1
 *   Autosar Revision     : ASR_REL_4_3_REV_0001
 *   Autosar Conf.Variant :
 *   SW Version           : 1.0.1
 *   Build Version        : S32K14x_MCAL_1_0_1_RTM_HF6_ASR_REL_4_3_REV_0001_20210225
 *
 *   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2019 NXP
 *   All Rights Reserved.
 =================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifdef __cplusplus
extern "C"{
#endif

/**
 *@page misra_violations MISRA-C:2004 violations
 *
 *@section Icu_PBCfg_c_1
 *          Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
 *          before "#include". This violation  is not  fixed since  the inclusion  of Icu_MemMap.h
 *          is as  per Autosar  requirement MEMMAP003.
 *
 *@section Icu_PBCfg_c_2
 *          Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent
 *          the contents of a header file being included twice
 *          This is not a violation since all header files are protected against multiple inclusions
 *
 * @section Icu_PBCfg_c_3
 *          Violates MISRA 2004 Required Rule 8.10, external ... could be made static
 *          The respective code could not be made static because of layers architecture design of
 *          the driver.
 *
 * @section Icu_PBCfg_c_4
 *          Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure 31
 *          character significance and case sensitivity are supported for external identifiers.
 *          This is not a violation since all the compilers used interpret the identifiers correctly
 *
  * @section Icu_PBCfg_c_5
 *          Violates MISRA 2004 Required Rule 8.8, An external object or function shall be
 *          declared in one and only one file.
 *
 * @section [global]
 *          Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
 *          on the significance of more than 31 characters. The used compilers use more than 31 chars
 *          for identifiers.
 */
 /*==================================================================================================
 *                                         INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
 *================================================================================================*/
#include "Icu.h"
#include "Icu_Ipw.h"

#if ((ICU_SIGNALMEASUREMENT_USES_DMA == STD_ON) || (ICU_TIMESTAMP_USES_DMA == STD_ON))
#include "CDD_Mcl.h"
#endif


/*==================================================================================================
 *                              SOURCE FILE VERSION INFORMATION
 *================================================================================================*/

#define ICU_PBCFG_VENDOR_ID_C                   43

#define ICU_PBCFG_AR_RELEASE_MAJOR_VERSION_C    4
#define ICU_PBCFG_AR_RELEASE_MINOR_VERSION_C    3
/*
 * @violates @ref Icu_PBCfg_c_4 Identifier clash
 */
#define ICU_PBCFG_AR_RELEASE_REVISION_VERSION_C       1

#define ICU_PBCFG_SW_MAJOR_VERSION_C            1
#define ICU_PBCFG_SW_MINOR_VERSION_C            0
#define ICU_PBCFG_SW_PATCH_VERSION_C            1

/*==================================================================================================
 *                                      FILE VERSION CHECKS
 *================================================================================================*/

/* Check Icu_PBCfg.c against Icu.h file versions */
#if (ICU_PBCFG_VENDOR_ID_C != ICU_VENDOR_ID)
    #error "Icu_PBCfg.c and Icu.h have different vendor IDs"
#endif

#if ((ICU_PBCFG_AR_RELEASE_MAJOR_VERSION_C != ICU_AR_RELEASE_MAJOR_VERSION) || \
     (ICU_PBCFG_AR_RELEASE_MINOR_VERSION_C != ICU_AR_RELEASE_MINOR_VERSION) || \
     (ICU_PBCFG_AR_RELEASE_REVISION_VERSION_C != ICU_AR_RELEASE_REVISION_VERSION))
  #error "AutoSar Version Numbers of Icu_PBCfg.c and Icu.h are different"
#endif

#if ((ICU_PBCFG_SW_MAJOR_VERSION_C != ICU_SW_MAJOR_VERSION) || \
     (ICU_PBCFG_SW_MINOR_VERSION_C != ICU_SW_MINOR_VERSION) || \
     (ICU_PBCFG_SW_PATCH_VERSION_C != ICU_SW_PATCH_VERSION))
       #error "Software Version Numbers of Icu_PBCfg.c  and Icu.h are different"
#endif


/* Check Icu_PBCfg.c against Icu_Ipw.h file versions */
#if (ICU_PBCFG_VENDOR_ID_C != ICU_IPW_VENDOR_ID)
    #error "Icu_PBCfg.c and Icu_Ipw.h have different vendor IDs"
#endif

#if ((ICU_PBCFG_AR_RELEASE_MAJOR_VERSION_C != ICU_IPW_AR_RELEASE_MAJOR_VERSION) || \
     (ICU_PBCFG_AR_RELEASE_MINOR_VERSION_C != ICU_IPW_AR_RELEASE_MINOR_VERSION) || \
     (ICU_PBCFG_AR_RELEASE_REVISION_VERSION_C != ICU_IPW_AR_RELEASE_REVISION_VERSION))
  #error "AutoSar Version Numbers of Icu_PBCfg.c and Icu_Ipw.h are different"
#endif

#if ((ICU_PBCFG_SW_MAJOR_VERSION_C != ICU_IPW_SW_MAJOR_VERSION) || \
     (ICU_PBCFG_SW_MINOR_VERSION_C != ICU_IPW_SW_MINOR_VERSION) || \
     (ICU_PBCFG_SW_PATCH_VERSION_C != ICU_IPW_SW_PATCH_VERSION))
       #error "Software Version Numbers of Icu_PBCfg.c  and Icu_Ipw.h are different"
#endif

#if (ICU_TIMESTAMP_USES_DMA == STD_ON)

/* Check Icu_PBCfg.c against CDD_Mcl.h file versions */
#if (ICU_PBCFG_VENDOR_ID_C != MCL_VENDOR_ID)
    #error "Icu_PBCfg.c and CDD_Mcl.h have different vendor IDs"
#endif

#if ((ICU_PBCFG_AR_RELEASE_MAJOR_VERSION_C != MCL_AR_RELEASE_MAJOR_VERSION) || \
     (ICU_PBCFG_AR_RELEASE_MINOR_VERSION_C != MCL_AR_RELEASE_MINOR_VERSION) || \
     (ICU_PBCFG_AR_RELEASE_REVISION_VERSION_C != MCL_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Icu_PBCfg.c and CDD_Mcl.h are different"
#endif

#if ((ICU_PBCFG_SW_MAJOR_VERSION_C != MCL_SW_MAJOR_VERSION) || \
     (ICU_PBCFG_SW_MINOR_VERSION_C != MCL_SW_MINOR_VERSION) || \
     (ICU_PBCFG_SW_PATCH_VERSION_C != MCL_SW_PATCH_VERSION))
    #error "Software Version Numbers of Icu_PBCfg.c and CDD_Mcl.h are different"
#endif
#endif

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 *================================================================================================*/


/*==================================================================================================
 *                                       LOCAL MACROS
 *================================================================================================*/


/*==================================================================================================
 *                                      LOCAL CONSTANTS
 *================================================================================================*/


/*==================================================================================================
 *                                       LOCAL VARIABLES
 *================================================================================================*/


/*==================================================================================================
 *                                       GLOBAL CONSTANTS
 *================================================================================================*/








#define ICU_START_SEC_CODE
/*
 * @violates @ref Icu_PBCfg_c_1 Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements
 *           and comments before "#include"
 * @violates @ref Icu_PBCfg_c_2 precautions to prevent the contents of a header file being included
 *           twice
 */
#include "Icu_MemMap.h"



/**
 *   @brief External Notifications for Edge Detection
 */

/**
 *  @violates @ref Icu_PBCfg_c_5 violates Misra 8.8 Maybe used in multiple configuration variants
 */
extern FUNC (void, ICU_CODE) Nfc_NfcChipIrqIsr(void);

                
/**
 *  @violates @ref Icu_PBCfg_c_5 violates Misra 8.8 Maybe used in multiple configuration variants
 */
extern FUNC (void, ICU_CODE) LDC3114_ISR(void);

                
/**
 *  @violates @ref Icu_PBCfg_c_5 violates Misra 8.8 Maybe used in multiple configuration variants
 */
extern FUNC (void, ICU_CODE) EcuM_CanWakeUp(void);

                

#define ICU_STOP_SEC_CODE
/*
 * @violates @ref Icu_PBCfg_c_1 Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements
 *           and comments before "#include"
 * @violates @ref Icu_PBCfg_c_2 precautions to prevent the contents of a header file being included
 *           twice
 */
#include "Icu_MemMap.h"

 #define ICU_START_SEC_CONFIG_DATA_UNSPECIFIED
/*
 * @violates @ref Icu_PBCfg_c_1 Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements
 *           and comments before "#include"
 * @violates @ref Icu_PBCfg_c_2 precautions to prevent the contents of a header file being included
 *           twice
 */
#include "Icu_MemMap.h"



/*
 *  @brief    PB Default Configuration
 *  @violates @ref Icu_PBCfg_c_3 violates Misra 8.10 external ... could be made static
 */
 CONST(Icu_ChannelConfigType, ICU_CONST) Icu_InitChannel_PB[3]=
 {
         /* IcuChannel_NFC_REQ_Interrupt*/
        {
            ((Icu_ParamType)((Icu_ParamType)ICU_RISING_EDGE << ICU_EDGE_PARAM_SHIFT)),
            (Icu_MeasurementModeType)ICU_MODE_SIGNAL_EDGE_DETECT,
            (Icu_MeasurementSubModeType)0U,
            &Nfc_NfcChipIrqIsr,
#if (ICU_TIMESTAMP_USES_DMA == STD_ON)
            (Mcl_ChannelType)NoMclDmaChannel,
#endif
#if (ICU_OVERFLOW_NOTIFICATION_API == STD_ON)
            NULL_PTR,
#endif  /* ICU_OVERFLOW_NOTIFICATION_API */
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
            (Icu_WakeupValueType)0U

#endif /* (ICU_REPORT_WAKEUP_SOURCE == STD_ON) */
        },
        /* IcuChannel_LDC_INTB_Interrupt*/
        {
            ((Icu_ParamType)((Icu_ParamType)ICU_FALLING_EDGE << ICU_EDGE_PARAM_SHIFT)),
            (Icu_MeasurementModeType)ICU_MODE_SIGNAL_EDGE_DETECT,
            (Icu_MeasurementSubModeType)0U,
            &LDC3114_ISR,
#if (ICU_TIMESTAMP_USES_DMA == STD_ON)
            (Mcl_ChannelType)NoMclDmaChannel,
#endif
#if (ICU_OVERFLOW_NOTIFICATION_API == STD_ON)
            NULL_PTR,
#endif  /* ICU_OVERFLOW_NOTIFICATION_API */
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
            (Icu_WakeupValueType)0U

#endif /* (ICU_REPORT_WAKEUP_SOURCE == STD_ON) */
        },
        /* IcuChannel_CanWakeup*/
        {
            ((Icu_ParamType)((Icu_ParamType)ICU_FALLING_EDGE << ICU_EDGE_PARAM_SHIFT)),
            (Icu_MeasurementModeType)ICU_MODE_SIGNAL_EDGE_DETECT,
            (Icu_MeasurementSubModeType)0U,
            &EcuM_CanWakeUp,
#if (ICU_TIMESTAMP_USES_DMA == STD_ON)
            (Mcl_ChannelType)NoMclDmaChannel,
#endif
#if (ICU_OVERFLOW_NOTIFICATION_API == STD_ON)
            NULL_PTR,
#endif  /* ICU_OVERFLOW_NOTIFICATION_API */
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
            (Icu_WakeupValueType)0U

#endif /* (ICU_REPORT_WAKEUP_SOURCE == STD_ON) */
        }

 };








    /** @brief No Ftm channels configured */



/*
 *  @brief    PB Default PORT Configuration
 *  @violates @ref Icu_PBCfg_c_3 violates Misra 8.10 external ... could be made static
 *  @violates @ref Icu_PBCfg_c_4 violates Misra 1.4 Identifier clash
 */
 CONST(Icu_Port_Ci_ChannelConfigType, ICU_CONST) Icu_Port_Ci_ChannelConfig_PB[3] =
 {
    
    /** @brief IcuChannel_NFC_REQ_Interrupt */
    {
        /** @brief Port HW Module and Channel used by the Icu channel */
        ICU_PORT_4_CH_9,
        /** @brief Port default start Edge */
        (uint8)ICU_RISING_EDGE
    },

    /** @brief IcuChannel_LDC_INTB_Interrupt */
    {
        /** @brief Port HW Module and Channel used by the Icu channel */
        ICU_PORT_2_CH_7,
        /** @brief Port default start Edge */
        (uint8)ICU_FALLING_EDGE
    },

    /** @brief IcuChannel_CanWakeup */
    {
        /** @brief Port HW Module and Channel used by the Icu channel */
        ICU_PORT_4_CH_4,
        /** @brief Port default start Edge */
        (uint8)ICU_FALLING_EDGE
    }

 };

/*
 *  @violates @ref Icu_PBCfg_c_3 violates Misra 8.10 external ... could be made static
 */
 CONST(Icu_Port_Ci_IpConfigType, ICU_CONST) Icu_Port_Ci_IpConfig_PB =
 {
    /** @brief Number of Port channels in the Icu configuration */
    (uint8)3,
    /** @brief Pointer to the array of Port enabled Icu channel configurations */
    &Icu_Port_Ci_ChannelConfig_PB
 };




    /** @brief No LPit channels configured */



    /** @brief No Lptmr channels configured */


/*
 * @brief   Icu channels IP related configuration array
 * @violates @ref Icu_PBCfg_c_3 violates Misra 8.10 external ... could be made static
 */
 CONST(Icu_IpChannelConfigType, ICU_CONST) Icu_IpChannelConfig_PB[3] =
 {
    
    /** @brief IcuChannel_NFC_REQ_Interrupt */
    {
        /** @brief IP type of this channel */
        ICU_PORT_CI_CHANNEL,
        /** @brief Index in the configuration table of the Port channels */
        (uint8)0,
    },

    /** @brief IcuChannel_LDC_INTB_Interrupt */
    {
        /** @brief IP type of this channel */
        ICU_PORT_CI_CHANNEL,
        /** @brief Index in the configuration table of the Port channels */
        (uint8)1,
    },

    /** @brief IcuChannel_CanWakeup */
    {
        /** @brief IP type of this channel */
        ICU_PORT_CI_CHANNEL,
        /** @brief Index in the configuration table of the Port channels */
        (uint8)2,
    }

 };


/*
 *   @brief This index relates the Hardware channels with the respective ICU channel. *
 *   When an normal interrupt is asserted this index is used to locate the corresponding ICU channel
 *
 *  @violates @ref Icu_PBCfg_c_3 external ... could be made static
 */


/*
 * @violates @ref Icu_PBCfg_c_3 violates Misra 8.10 external ... could be made static
 */
CONST(Icu_ChannelType,ICU_CONST) Icu_InitHWMap_PB[ICU_MAX_HW_CHANNELS] =
{
    NoIcuChannel, /* maps to FTM_0_CH_0 */
    NoIcuChannel, /* maps to FTM_0_CH_1 */
    NoIcuChannel, /* maps to FTM_0_CH_2 */
    NoIcuChannel, /* maps to FTM_0_CH_3 */
    NoIcuChannel, /* maps to FTM_0_CH_4 */
    NoIcuChannel, /* maps to FTM_0_CH_5 */
    NoIcuChannel, /* maps to FTM_0_CH_6 */
    NoIcuChannel, /* maps to FTM_0_CH_7 */
    NoIcuChannel, /* maps to FTM_1_CH_0 */
    NoIcuChannel, /* maps to FTM_1_CH_1 */
    NoIcuChannel, /* maps to FTM_1_CH_2 */
    NoIcuChannel, /* maps to FTM_1_CH_3 */
    NoIcuChannel, /* maps to FTM_1_CH_4 */
    NoIcuChannel, /* maps to FTM_1_CH_5 */
    NoIcuChannel, /* maps to FTM_1_CH_6 */
    NoIcuChannel, /* maps to FTM_1_CH_7 */
    NoIcuChannel, /* maps to FTM_2_CH_0 */
    NoIcuChannel, /* maps to FTM_2_CH_1 */
    NoIcuChannel, /* maps to FTM_2_CH_2 */
    NoIcuChannel, /* maps to FTM_2_CH_3 */
    NoIcuChannel, /* maps to FTM_2_CH_4 */
    NoIcuChannel, /* maps to FTM_2_CH_5 */
    NoIcuChannel, /* maps to FTM_2_CH_6 */
    NoIcuChannel, /* maps to FTM_2_CH_7 */
    NoIcuChannel, /* maps to FTM_3_CH_0 */
    NoIcuChannel, /* maps to FTM_3_CH_1 */
    NoIcuChannel, /* maps to FTM_3_CH_2 */
    NoIcuChannel, /* maps to FTM_3_CH_3 */
    NoIcuChannel, /* maps to FTM_3_CH_4 */
    NoIcuChannel, /* maps to FTM_3_CH_5 */
    NoIcuChannel, /* maps to FTM_3_CH_6 */
    NoIcuChannel, /* maps to FTM_3_CH_7 */
    NoIcuChannel, /* maps to FTM_4_CH_0 */
    NoIcuChannel, /* maps to FTM_4_CH_1 */
    NoIcuChannel, /* maps to FTM_4_CH_2 */
    NoIcuChannel, /* maps to FTM_4_CH_3 */
    NoIcuChannel, /* maps to FTM_4_CH_4 */
    NoIcuChannel, /* maps to FTM_4_CH_5 */
    NoIcuChannel, /* maps to FTM_4_CH_6 */
    NoIcuChannel, /* maps to FTM_4_CH_7 */
    NoIcuChannel, /* maps to FTM_5_CH_0 */
    NoIcuChannel, /* maps to FTM_5_CH_1 */
    NoIcuChannel, /* maps to FTM_5_CH_2 */
    NoIcuChannel, /* maps to FTM_5_CH_3 */
    NoIcuChannel, /* maps to FTM_5_CH_4 */
    NoIcuChannel, /* maps to FTM_5_CH_5 */
    NoIcuChannel, /* maps to FTM_5_CH_6 */
    NoIcuChannel, /* maps to FTM_5_CH_7 */
    NoIcuChannel, /* maps to FTM_6_CH_0 */
    NoIcuChannel, /* maps to FTM_6_CH_1 */
    NoIcuChannel, /* maps to FTM_6_CH_2 */
    NoIcuChannel, /* maps to FTM_6_CH_3 */
    NoIcuChannel, /* maps to FTM_6_CH_4 */
    NoIcuChannel, /* maps to FTM_6_CH_5 */
    NoIcuChannel, /* maps to FTM_6_CH_6 */
    NoIcuChannel, /* maps to FTM_6_CH_7 */
    NoIcuChannel, /* maps to FTM_7_CH_0 */
    NoIcuChannel, /* maps to FTM_7_CH_1 */
    NoIcuChannel, /* maps to FTM_7_CH_2 */
    NoIcuChannel, /* maps to FTM_7_CH_3 */
    NoIcuChannel, /* maps to FTM_7_CH_4 */
    NoIcuChannel, /* maps to FTM_7_CH_5 */
    NoIcuChannel, /* maps to FTM_7_CH_6 */
    NoIcuChannel, /* maps to FTM_7_CH_7 */
    NoIcuChannel, /* maps to PORT_0_CH_0 */
    NoIcuChannel, /* maps to PORT_0_CH_1 */
    NoIcuChannel, /* maps to PORT_0_CH_2 */
    NoIcuChannel, /* maps to PORT_0_CH_3 */
    NoIcuChannel, /* maps to PORT_0_CH_4 */
    NoIcuChannel, /* maps to PORT_0_CH_5 */
    NoIcuChannel, /* maps to PORT_0_CH_6 */
    NoIcuChannel, /* maps to PORT_0_CH_7 */
    NoIcuChannel, /* maps to PORT_0_CH_8 */
    NoIcuChannel, /* maps to PORT_0_CH_9 */
    NoIcuChannel, /* maps to PORT_0_CH_10 */
    NoIcuChannel, /* maps to PORT_0_CH_11 */
    NoIcuChannel, /* maps to PORT_0_CH_12 */
    NoIcuChannel, /* maps to PORT_0_CH_13 */
    NoIcuChannel, /* maps to PORT_0_CH_14 */
    NoIcuChannel, /* maps to PORT_0_CH_15 */
    NoIcuChannel, /* maps to PORT_0_CH_16 */
    NoIcuChannel, /* maps to PORT_0_CH_17 */
    NoIcuChannel, /* maps to PORT_0_CH_18 */
    NoIcuChannel, /* maps to PORT_0_CH_19 */
    NoIcuChannel, /* maps to PORT_0_CH_20 */
    NoIcuChannel, /* maps to PORT_0_CH_21 */
    NoIcuChannel, /* maps to PORT_0_CH_22 */
    NoIcuChannel, /* maps to PORT_0_CH_23 */
    NoIcuChannel, /* maps to PORT_0_CH_24 */
    NoIcuChannel, /* maps to PORT_0_CH_25 */
    NoIcuChannel, /* maps to PORT_0_CH_26 */
    NoIcuChannel, /* maps to PORT_0_CH_27 */
    NoIcuChannel, /* maps to PORT_0_CH_28 */
    NoIcuChannel, /* maps to PORT_0_CH_29 */
    NoIcuChannel, /* maps to PORT_0_CH_30 */
    NoIcuChannel, /* maps to PORT_0_CH_31 */
    NoIcuChannel, /* maps to PORT_1_CH_0 */
    NoIcuChannel, /* maps to PORT_1_CH_1 */
    NoIcuChannel, /* maps to PORT_1_CH_2 */
    NoIcuChannel, /* maps to PORT_1_CH_3 */
    NoIcuChannel, /* maps to PORT_1_CH_4 */
    NoIcuChannel, /* maps to PORT_1_CH_5 */
    NoIcuChannel, /* maps to PORT_1_CH_6 */
    NoIcuChannel, /* maps to PORT_1_CH_7 */
    NoIcuChannel, /* maps to PORT_1_CH_8 */
    NoIcuChannel, /* maps to PORT_1_CH_9 */
    NoIcuChannel, /* maps to PORT_1_CH_10 */
    NoIcuChannel, /* maps to PORT_1_CH_11 */
    NoIcuChannel, /* maps to PORT_1_CH_12 */
    NoIcuChannel, /* maps to PORT_1_CH_13 */
    NoIcuChannel, /* maps to PORT_1_CH_14 */
    NoIcuChannel, /* maps to PORT_1_CH_15 */
    NoIcuChannel, /* maps to PORT_1_CH_16 */
    NoIcuChannel, /* maps to PORT_1_CH_17 */
    NoIcuChannel, /* maps to PORT_1_CH_18 */
    NoIcuChannel, /* maps to PORT_1_CH_19 */
    NoIcuChannel, /* maps to PORT_1_CH_20 */
    NoIcuChannel, /* maps to PORT_1_CH_21 */
    NoIcuChannel, /* maps to PORT_1_CH_22 */
    NoIcuChannel, /* maps to PORT_1_CH_23 */
    NoIcuChannel, /* maps to PORT_1_CH_24 */
    NoIcuChannel, /* maps to PORT_1_CH_25 */
    NoIcuChannel, /* maps to PORT_1_CH_26 */
    NoIcuChannel, /* maps to PORT_1_CH_27 */
    NoIcuChannel, /* maps to PORT_1_CH_28 */
    NoIcuChannel, /* maps to PORT_1_CH_29 */
    NoIcuChannel, /* maps to PORT_1_CH_30 */
    NoIcuChannel, /* maps to PORT_1_CH_31 */
    NoIcuChannel, /* maps to PORT_2_CH_0 */
    NoIcuChannel, /* maps to PORT_2_CH_1 */
    NoIcuChannel, /* maps to PORT_2_CH_2 */
    NoIcuChannel, /* maps to PORT_2_CH_3 */
    NoIcuChannel, /* maps to PORT_2_CH_4 */
    NoIcuChannel, /* maps to PORT_2_CH_5 */
    NoIcuChannel, /* maps to PORT_2_CH_6 */
    IcuChannel_LDC_INTB_Interrupt, /* maps to PORT_2_CH_7 */
    NoIcuChannel, /* maps to PORT_2_CH_8 */
    NoIcuChannel, /* maps to PORT_2_CH_9 */
    NoIcuChannel, /* maps to PORT_2_CH_10 */
    NoIcuChannel, /* maps to PORT_2_CH_11 */
    NoIcuChannel, /* maps to PORT_2_CH_12 */
    NoIcuChannel, /* maps to PORT_2_CH_13 */
    NoIcuChannel, /* maps to PORT_2_CH_14 */
    NoIcuChannel, /* maps to PORT_2_CH_15 */
    NoIcuChannel, /* maps to PORT_2_CH_16 */
    NoIcuChannel, /* maps to PORT_2_CH_17 */
    NoIcuChannel, /* maps to PORT_2_CH_18 */
    NoIcuChannel, /* maps to PORT_2_CH_19 */
    NoIcuChannel, /* maps to PORT_2_CH_20 */
    NoIcuChannel, /* maps to PORT_2_CH_21 */
    NoIcuChannel, /* maps to PORT_2_CH_22 */
    NoIcuChannel, /* maps to PORT_2_CH_23 */
    NoIcuChannel, /* maps to PORT_2_CH_24 */
    NoIcuChannel, /* maps to PORT_2_CH_25 */
    NoIcuChannel, /* maps to PORT_2_CH_26 */
    NoIcuChannel, /* maps to PORT_2_CH_27 */
    NoIcuChannel, /* maps to PORT_2_CH_28 */
    NoIcuChannel, /* maps to PORT_2_CH_29 */
    NoIcuChannel, /* maps to PORT_2_CH_30 */
    NoIcuChannel, /* maps to PORT_2_CH_31 */
    NoIcuChannel, /* maps to PORT_3_CH_0 */
    NoIcuChannel, /* maps to PORT_3_CH_1 */
    NoIcuChannel, /* maps to PORT_3_CH_2 */
    NoIcuChannel, /* maps to PORT_3_CH_3 */
    NoIcuChannel, /* maps to PORT_3_CH_4 */
    NoIcuChannel, /* maps to PORT_3_CH_5 */
    NoIcuChannel, /* maps to PORT_3_CH_6 */
    NoIcuChannel, /* maps to PORT_3_CH_7 */
    NoIcuChannel, /* maps to PORT_3_CH_8 */
    NoIcuChannel, /* maps to PORT_3_CH_9 */
    NoIcuChannel, /* maps to PORT_3_CH_10 */
    NoIcuChannel, /* maps to PORT_3_CH_11 */
    NoIcuChannel, /* maps to PORT_3_CH_12 */
    NoIcuChannel, /* maps to PORT_3_CH_13 */
    NoIcuChannel, /* maps to PORT_3_CH_14 */
    NoIcuChannel, /* maps to PORT_3_CH_15 */
    NoIcuChannel, /* maps to PORT_3_CH_16 */
    NoIcuChannel, /* maps to PORT_3_CH_17 */
    NoIcuChannel, /* maps to PORT_3_CH_18 */
    NoIcuChannel, /* maps to PORT_3_CH_19 */
    NoIcuChannel, /* maps to PORT_3_CH_20 */
    NoIcuChannel, /* maps to PORT_3_CH_21 */
    NoIcuChannel, /* maps to PORT_3_CH_22 */
    NoIcuChannel, /* maps to PORT_3_CH_23 */
    NoIcuChannel, /* maps to PORT_3_CH_24 */
    NoIcuChannel, /* maps to PORT_3_CH_25 */
    NoIcuChannel, /* maps to PORT_3_CH_26 */
    NoIcuChannel, /* maps to PORT_3_CH_27 */
    NoIcuChannel, /* maps to PORT_3_CH_28 */
    NoIcuChannel, /* maps to PORT_3_CH_29 */
    NoIcuChannel, /* maps to PORT_3_CH_30 */
    NoIcuChannel, /* maps to PORT_3_CH_31 */
    NoIcuChannel, /* maps to PORT_4_CH_0 */
    NoIcuChannel, /* maps to PORT_4_CH_1 */
    NoIcuChannel, /* maps to PORT_4_CH_2 */
    NoIcuChannel, /* maps to PORT_4_CH_3 */
    IcuChannel_CanWakeup, /* maps to PORT_4_CH_4 */
    NoIcuChannel, /* maps to PORT_4_CH_5 */
    NoIcuChannel, /* maps to PORT_4_CH_6 */
    NoIcuChannel, /* maps to PORT_4_CH_7 */
    NoIcuChannel, /* maps to PORT_4_CH_8 */
    IcuChannel_NFC_REQ_Interrupt, /* maps to PORT_4_CH_9 */
    NoIcuChannel, /* maps to PORT_4_CH_10 */
    NoIcuChannel, /* maps to PORT_4_CH_11 */
    NoIcuChannel, /* maps to PORT_4_CH_12 */
    NoIcuChannel, /* maps to PORT_4_CH_13 */
    NoIcuChannel, /* maps to PORT_4_CH_14 */
    NoIcuChannel, /* maps to PORT_4_CH_15 */
    NoIcuChannel, /* maps to PORT_4_CH_16 */
    NoIcuChannel, /* maps to PORT_4_CH_17 */
    NoIcuChannel, /* maps to PORT_4_CH_18 */
    NoIcuChannel, /* maps to PORT_4_CH_19 */
    NoIcuChannel, /* maps to PORT_4_CH_20 */
    NoIcuChannel, /* maps to PORT_4_CH_21 */
    NoIcuChannel, /* maps to PORT_4_CH_22 */
    NoIcuChannel, /* maps to PORT_4_CH_23 */
    NoIcuChannel, /* maps to PORT_4_CH_24 */
    NoIcuChannel, /* maps to PORT_4_CH_25 */
    NoIcuChannel, /* maps to PORT_4_CH_26 */
    NoIcuChannel, /* maps to PORT_4_CH_27 */
    NoIcuChannel, /* maps to PORT_4_CH_28 */
    NoIcuChannel, /* maps to PORT_4_CH_29 */
    NoIcuChannel, /* maps to PORT_4_CH_30 */
    NoIcuChannel, /* maps to PORT_4_CH_31 */
    NoIcuChannel, /* maps to LPIT_0_CH_0 */
    NoIcuChannel, /* maps to LPIT_0_CH_1 */
    NoIcuChannel, /* maps to LPIT_0_CH_2 */
    NoIcuChannel, /* maps to LPIT_0_CH_3 */
    NoIcuChannel  /* maps to LPTMR_0_CH_0 */
};




/*
 *   @brief Pre-Compile Default Configuration
 *   @violates @ref Icu_PBCfg_c_3 external ... could be made static
 */
#ifdef ICU_PRECOMPILE_SUPPORT
 CONST(Icu_ConfigType, ICU_CONST) Icu_PBCfgVariantPredefined =
{
    (Icu_ChannelType)3U, /* The number of channels configured*/
    &Icu_InitChannel_PB,
    {
    /** @brief Pointer to the structure containing Ftm configuration */
        NULL_PTR,
    /** @brief Pointer to the structure containing Port configuration */
        &Icu_Port_Ci_IpConfig_PB,
        /** @brief Pointer to the structure containing LPit configuration */
        NULL_PTR,
        /** @brief Pointer to the structure containing Lptmr configuration */
        NULL_PTR,
    /** @brief Pointer to Array containing channel IP related information */
        &Icu_IpChannelConfig_PB
    },
    &Icu_InitHWMap_PB
};
#endif /*ICU_PRECOMPILE_SUPPORT*/
#define ICU_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/*
 * @violates @ref Icu_PBCfg_c_1 Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements
 *           and comments before "#include"
 * @violates @ref Icu_PBCfg_c_2 precautions to prevent the contents of a header file being included
 *           twice
 */
#include "Icu_MemMap.h"
/*==================================================================================================
 *                                       GLOBAL VARIABLES
 *================================================================================================*/


/*==================================================================================================
 *                                   LOCAL FUNCTION PROTOTYPES
 *================================================================================================*/


/*==================================================================================================
 *                                       LOCAL FUNCTIONS
 *================================================================================================*/


/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 *================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */
