/**
*   @file    I2c_LPI2C_Types.h
*   @version 1.0.1
*
*   @brief   AUTOSAR I2c - I2C driver header file.
*   @details I2C driver header file, containing variables, functions prototypes, data types and/or
*            defines and macros that:
*            - are Autosar independent.
*            - are platform dependent.
*
*   @addtogroup I2C
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

#ifndef I2C_LPI2C_TYPES_H
#define I2C_LPI2C_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif
/**
* @page misra_violations MISRA-C:2004 violations
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*/
/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define I2C_LPI2C_TYPES_VENDOR_ID                      43
#define I2C_LPI2C_TYPES_AR_RELEASE_MAJOR_VERSION       4
#define I2C_LPI2C_TYPES_AR_RELEASE_MINOR_VERSION       3
#define I2C_LPI2C_TYPES_AR_RELEASE_REVISION_VERSION    1
#define I2C_LPI2C_TYPES_SW_MAJOR_VERSION               1
#define I2C_LPI2C_TYPES_SW_MINOR_VERSION               0
#define I2C_LPI2C_TYPES_SW_PATCH_VERSION               1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief   The structure contains the hardware channel configuration parameters.
*/
typedef struct
{
    VAR( uint32, I2C_VAR)   u32MasterControlConfig;
    VAR( uint32, I2C_VAR)   u32MasterConfig1;
    VAR( uint32, I2C_VAR)   u32MasterConfig2;
    VAR( uint32, I2C_VAR)   u32MasterConfig3;
    VAR( uint32, I2C_VAR)   u32ClockingConfig0;
    VAR( uint32, I2C_VAR)   u32ClockingConfig1;
    VAR( uint32, I2C_VAR)   u32SlaveControlConfig;
    VAR( uint32, I2C_VAR)   u32SlaveConfig1;
    VAR( uint32, I2C_VAR)   u32SlaveConfig2;
    VAR( uint32, I2C_VAR)   u32SlaveAddressConfig;

#if (STD_ON == I2C_DMA_USED)
    /**< @brief Dma Channel used for transmitting data */
    VAR( uint8, I2C_VAR)    u8TxDmaChannel;
    /**< @brief Dma Channel used for receiving data */
    VAR( uint8, I2C_VAR)    u8RxDmaChannel;
#endif
} I2c_LPI2C_HwChannelConfigType;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /*I2C_LPI2C_TYPES_H*/

/** @} */
