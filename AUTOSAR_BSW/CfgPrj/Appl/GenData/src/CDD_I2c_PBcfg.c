/**
*   @file    CDD_I2c_PBcfg.c
*   @version 1.0.1
*
*   @brief   AUTOSAR I2c - Data structures for the I2c driver.
*   @details Post build structure configurations for the driver initialization.
*
*   @addtogroup I2c
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.3 MCAL
*   Platform             : ARM
*   Peripheral           : LPI2C,FlexIO
*   Dependencies         : none
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
/*==================================================================================================
==================================================================================================*/


#ifdef __cplusplus
extern "C"
{
#endif


/**
* @page misra_violations MISRA-C:2004 violations
*
* @section CDD_I2c_PBcfg_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h,  Precautions shall be
* taken in order to prevent the contents of a header file being included twice This is not a violation
* since all header files are protected against multiple inclusions
*
* @section CDD_I2c_PBcfg_c_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
* before '#include' MemMap.h included after each section define in order to set the current memory section
*
* @section CDD_I2c_PBcfg_c_REF_3
* Violates MISRA 2004 Required Rule 8.10, All declarations and definitions of objects or functions
* at file scope shall have internal linkage unless external linkage is required.
*
* @section CDD_I2c_PBcfg_c_REF_4
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure that 31
* character significance and case sensitivity are supported for external identifiers.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*/

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "CDD_I2c.h"

#include "Reg_eSys_LPI2C.h"

#if (STD_ON == I2C_FLEXIO_USED)
    #include "Reg_eSys_FlexIO.h"
#endif

#if (I2C_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Dem.h"
#endif /* (I2C_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define I2C_PBCFG_VENDOR_ID_C                     43
#define I2C_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define I2C_PBCFG_AR_RELEASE_MINOR_VERSION_C      3
#define I2C_PBCFG_AR_RELEASE_REVISION_VERSION_C   1
#define I2C_PBCFG_SW_MAJOR_VERSION_C              1
#define I2C_PBCFG_SW_MINOR_VERSION_C              0
#define I2C_PBCFG_SW_PATCH_VERSION_C              1


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and I2c header file are of the same vendor */
#if (I2C_PBCFG_VENDOR_ID_C != I2C_VENDOR_ID)
    #error "I2c_PBcfg.c and CDD_I2c.h have different vendor ids"
#endif
/* Check if current file and I2c header file are of the same Autosar version */
#if ((I2C_PBCFG_AR_RELEASE_MAJOR_VERSION_C != I2C_AR_RELEASE_MAJOR_VERSION) || \
     (I2C_PBCFG_AR_RELEASE_MINOR_VERSION_C != I2C_AR_RELEASE_MINOR_VERSION) || \
     (I2C_PBCFG_AR_RELEASE_REVISION_VERSION_C != I2C_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of I2c_PBcfg.c and CDD_I2c.h are different"
#endif
/* Check if current file and I2c header file are of the same Software version */
#if ((I2C_PBCFG_SW_MAJOR_VERSION_C != I2C_SW_MAJOR_VERSION) || \
     (I2C_PBCFG_SW_MINOR_VERSION_C != I2C_SW_MINOR_VERSION) || \
     (I2C_PBCFG_SW_PATCH_VERSION_C != I2C_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of I2c_PBcfg.c and CDD_I2c.h are different"
#endif

/* Check if source file and Reg_eSys_LPI2C.h are from the same vendor */
#if (I2C_PBCFG_VENDOR_ID_C != REG_ESYS_LPI2C_VENDOR_ID)
    #error "I2c_PBcfg.c and Reg_eSys_LPI2C.h have different vendor ids"
#endif
/* Check if source file and Reg_eSys_LPI2C.h are of the same Autosar version */
#if ((I2C_PBCFG_AR_RELEASE_MAJOR_VERSION_C != REG_ESYS_LPI2C_AR_RELEASE_MAJOR_VERSION) || \
     (I2C_PBCFG_AR_RELEASE_MINOR_VERSION_C != REG_ESYS_LPI2C_AR_RELEASE_MINOR_VERSION) || \
     (I2C_PBCFG_AR_RELEASE_REVISION_VERSION_C != REG_ESYS_LPI2C_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of I2c_PBcfg.c and Reg_eSys_LPI2C.h are different"
#endif
/*Check if source file and Reg_eSys_LPI2C.h are of the same Software version */
#if ((I2C_PBCFG_SW_MAJOR_VERSION_C != REG_ESYS_LPI2C_SW_MAJOR_VERSION) || \
     (I2C_PBCFG_SW_MINOR_VERSION_C != REG_ESYS_LPI2C_SW_MINOR_VERSION) || \
     (I2C_PBCFG_SW_PATCH_VERSION_C != REG_ESYS_LPI2C_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of I2c_PBcfg.c and Reg_eSys_LPI2C.h are different"
#endif

/* Check if source file and Reg_eSys_FlexIO.h are of the same Autosar version */
#if (STD_ON == I2C_FLEXIO_USED)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#if ((I2C_PBCFG_AR_RELEASE_MAJOR_VERSION_C != REG_ESYS_FLEXIO_AR_RELEASE_MAJOR_VERSION) || \
     (I2C_PBCFG_AR_RELEASE_MINOR_VERSION_C != REG_ESYS_FLEXIO_AR_RELEASE_MINOR_VERSION) || \
     (I2C_PBCFG_AR_RELEASE_REVISION_VERSION_C != REG_ESYS_FLEXIO_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of I2c_PBcfg.c and Reg_eSys_FlexIO.h are different"
#endif
#endif
#endif

/* Check if current file and DEM header file are of the same version */
#if (I2C_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((I2C_PBCFG_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
         (I2C_PBCFG_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of I2c_PBcfg.c and Dem.h are different"
    #endif
#endif
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


#define I2C_START_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref CDD_I2c_PBcfg_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref CDD_I2c_PBcfg_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
* statements and comments before '#include'
*/
#include "I2c_MemMap.h"





/**
* @brief        Definition of LPI2C hardware channel structure.
* @details      Configures the hardware peripheral of a LPI2C channel.
*               Configuration set by calling I2c_Init() API.
*/
/** @violates @ref CDD_I2c_c_REF_4 MISRA 2004 Required Rule 1.4, 31 character significance */
static CONST( I2c_LPI2C_HwChannelConfigType, I2C_CONST) I2c_LPI2CChannelConfigPB0Ch0 =
{
    /* Master Control Config */
    (
    /* Debug Enable. */
    LPI2C_MCR_MASTER_DISABLED_IN_DBG_U32 |
    /* Doze Mode Enable. */
    LPI2C_MCR_MASTER_ENABLED_IN_DOZE_U32
    ),
    
    /* Master Config 1 */
    (LPI2C_2PIN_OPEN_DRAIN_U32 |
    LPI2C_PRESCALE_U32((uint32)0U)
    ),
    
    /* Master Config 2 */
    (LPI2C_FILTSDA_U32((uint32)0U) |
     LPI2C_FILTSCL_U32((uint32)0U) |
     LPI2C_BUSIDLE_U32((uint32)50U)
    ),
    
    /* Master Config 3 */
    (LPI2C_PINLOW_U32((uint32)0U)),
    
    /* Clock Config 0 */
    (LPI2C_DATAVD_U32((uint32)1U) |
     LPI2C_SETHOLD_U32((uint32)2U) |
     LPI2C_CLKHI_U32((uint32)3U) |
     LPI2C_CLKLO_U32((uint32)3U)
    ),
    
    /* Clock Config 1 - for High Speed */
    (LPI2C_DATAVD_U32((uint32)1U) |
     LPI2C_SETHOLD_U32((uint32)2U) |
     LPI2C_CLKHI_U32((uint32)3U) |
     LPI2C_CLKLO_U32((uint32)3U)
    ),
    
    /* Slave Control Config */
    (
    /* Filter Enable. */
    LPI2C_SCR_FILTER_ENABLED_U32 |
    /* Doze Mode Enable. */
    LPI2C_SCR_FILTER_ENABLED_IN_DOZE_U32
    ),
    
    /* Slave Config 1 */
    (
    /* Address matching */
    LPI2C_SLAVE_MATCH_ADDR0_7BIT_U32 |
    /* ACK SCL Stall */
    LPI2C_ACK_SCL_STALL_DISABLE_U32 |
    /* TX Data SCL Stall. */
    LPI2C_TX_DATA_SCL_STALL_DISABLE_U32 |
    /* RX Data SCL Stall. */
    LPI2C_RX_DATA_SCL_STALL_DISABLE_U32 |
    /* Address SCL Stall. */
    LPI2C_ADDRESS_SCL_STALL_DISABLE_U32
    ),
    
    /* Slave Config 2 */
    (LPI2C_SLAVE_FILTSDA_U32((uint32)0U) |
     LPI2C_SLAVE_FILTSCL_U32((uint32)0U) |
     LPI2C_SLAVE_DATAVD_U32((uint32)0U) |
     LPI2C_SLAVE_CLKHOLD_U32((uint32)0U)
    ),
    
    /* Slave Address Config */
    (
     LPI2C_ADDR0_U32((uint32)0U)
    )
    
#if (STD_ON == I2C_DMA_USED)
    ,
    
    0U,
    0U
    
#endif
};

/**
* @brief        Definition of I2c hardware channel structure.
* @details      Configures the hardware peripheral of an I2c channel.
*               Configuration set by calling I2c_Init() API.
*/
static CONST( I2c_HwUnitConfigType, I2C_CONST) I2c_ChannelConfigPB0[1] =
{

    /* Start of I2c_ChannelConfig[0]*/
    {
        /* The hardware channel ID. */
        (uint8)LPI2C_0,
        
        (I2c_MasterSlaveModeType)I2C_MASTER_MODE,
        
        (I2c_AsynchronousMethodType)I2C_INTERRUPT_MODE,
        
        {
            I2C_LPI2C_CHANNEL,

            
            &I2c_LPI2CChannelConfigPB0Ch0
            
        }
    }/* end of I2c_ChannelConfigPB0[0]. */

};



/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/**
* @brief          Initialization data for the I2c driver.
* @details        A pointer to such a structure is provided to the I2c initialization routines for configuration.
*
*/
/** @violates @ref CDD_I2c_c_REF_3 MISRA 2004 Required Rule 8.10, external linkage */
CONST(I2c_ConfigType, I2C_CONST) I2c_PBCfgVariantPredefined =
{
    /* Number of channel configurations. */
    (I2c_HwUnitType)1U,

#if (I2C_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
    /* Pointer to DEM error reporting configurations. */
    &I2c_DemConfig,
#endif

    /* Pointer to I2c hardware unit configuration. */
    &I2c_ChannelConfigPB0
};



#define I2C_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref CDD_I2c_PBcfg_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref CDD_I2c_PBcfg_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
* statements and comments before '#include'
*/
#include "I2c_MemMap.h"

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

