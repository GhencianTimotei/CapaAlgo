/**
*   @file    CDD_I2c_Cfg.h
*   @version 1.0.1
*
*   @brief   AUTOSAR I2c - High level header of I2c driver.
*   @details This file contains declarations of the functions defined by AutoSAR.
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

#ifndef I2C_CFG_H
#define I2C_CFG_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely on the significance of more than 31 characters. 
* The used compilers use more than 31 chars for identifiers.
*
* @section CDD_I2c_Cfg_h_REF_1
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure that 31 character significance and case sensitivity are supported 
* for external identifiers. This violation is due to the requirement that requests to have a file version check.
*
* @section CDD_I2c_Cfg_h_REF_2
* Violates MISRA 2004 Required Rule 8.7, Objects shall be defined at block scope if they are only accessed from within a single function
*
* @section CDD_I2c_Cfg_h_REF_3
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined. This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
*
* @section CDD_I2c_Cfg_h_REF_4
* Violates MISRA 2004 Required Rule 19.4, C macros shall only expand to braced initialiser,
* a constant, a parenthesised expression, a type qualifier, a storage class specifier, or
* a do-while-zero construct
**
* @section CDD_I2c_Cfg_h_REF_5
* Violates MISRA 2004 Required Rule 19.10, In the definition of a function-like macro each instance of a
* parameter shall be enclosed in parentheses unless it is used as * the operand of # or ##.
* This is used to define user configurable callbacks with parameters.
*
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcal.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/* Inclusion of incompatible header files shall be avoided */

#define I2C_VENDOR_ID_CFG                    43
#define I2C_MODULE_ID_CFG                    255
#define I2C_AR_RELEASE_MAJOR_VERSION_CFG     4
#define I2C_AR_RELEASE_MINOR_VERSION_CFG     3
/*
* @violates @ref CDD_I2c_Cfg_h_REF_1 The compiler/linker shall be checked to
* ensure that 31 character significance and case sensitivity are supported for
* external identifiers.
*/
#define I2C_AR_RELEASE_REVISION_VERSION_CFG  1
#define I2C_SW_MAJOR_VERSION_CFG             1
#define I2C_SW_MINOR_VERSION_CFG             0
#define I2C_SW_PATCH_VERSION_CFG             1
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
  /* Check if current file and Mcal.h header file are of the same Autosar version */
    #if ((I2C_AR_RELEASE_MAJOR_VERSION_CFG != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (I2C_AR_RELEASE_MINOR_VERSION_CFG != MCAL_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of CDD_I2c_Cfg.h and Mcal.h are different"
    #endif
#endif


/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/**
* @brief          Precompile Support On.
* @details        VARIANT-PRE-COMPILE: Only parameters with "Pre-compile time"
*                 configuration are allowed in this variant.
*
* @api
*/
#define I2C_PRECOMPILE_SUPPORT   (STD_ON)

/**
* @brief   Total number of available hardware I2c channels.
*/
#define I2C_HW_MAX_MODULES          (3U)

/**
* @brief   Total number of available hardware LPI2C channels.
*/
#define I2C_LPI2C_MAX_MODULES       (1U)

/**
* @brief   Total number of available hardware FLEXIO sub channels. Each FLEXIO module can support 2 I2c channels
*/
#define I2C_FLEXIO_MAX_CHANNELS     (2U)

/**
* @brief   Unified Interrupt.
*/
#define I2C_UNIFIED_INTERRUPTS  (STD_OFF) 

/**
* @brief            This is the ID of the first FLEXIO channel.
*/
#define I2C_FLEXIO_FIRST_CHANNEL_U8   (I2C_LPI2C_MAX_MODULES)

/**
* @brief   Number of loops before returning I2C_E_TIMEOUT.
*
* @api
*/
#define  I2C_TIMEOUT_LOOPS 1000U

/**
* @brief   Switches the Development Error Detection and Notification ON or OFF.
*
* @api
*/
#define I2C_DEV_ERROR_DETECT      (STD_OFF) /* Disable Development Error Detection */

/**
* @brief          Support for version info API.
* @details        Switches the I2c_GetVersionInfo() API ON or OFF.
*
* @api
*/
#define I2C_VERSION_INFO_API      (STD_ON)  /* Enable API I2c_GetVersionInfo      */


/**
* @brief          Link I2c channels symbolic names with I2c channel IDs.
* @details        Link I2c channels symbolic names with I2c channel IDs.
*
* @api
*/



#define LPI2C_0    0U



#define FLEXIO_0_CH_0_1    1U



#define FLEXIO_0_CH_2_3    2U



/**
* @brief          Symbolic names for configured channels.
* @details        Symbolic names for configured channels.
*
* @api
*/
/*
* @violates @ref CDD_I2c_Cfg_h_REF_1 The compiler/linker shall be checked to
* ensure that 31 character significance and case sensitivity are supported for
* external identifiers.
*/
#define I2cConf_I2cChannelConfiguration_I2cChannel         0

/**
* @brief          FLEXIO Channel Used
* @details        FLEXIO Channel Used
*
* @api
*/

/**
* @brief            Enable/Disable the API for reporting the Dem Error.
*/
#define I2C_DISABLE_DEM_REPORT_ERROR_STATUS   (STD_ON)


/**
* @brief            The call out configured by the user for error notifications.
*/
/** @violates @ref CDD_I2c_Cfg_h_REF_3 MISRA 2004 Advisory Rule 19.7 This is used to define user configurable callouts with parameters .*/
/** @violates @ref CDD_I2c_Cfg_h_REF_5 This is used to define user configurable callouts with parameters */
#define I2C_ERROR_NOTIFICATION(u8Channel, u8ErrorCode) (I2C_ErrorNotification(u8Channel, u8ErrorCode))



/**
* @brief            The call out configured by the user for master transmission completion.
*/
/** @violates @ref CDD_I2c_Cfg_h_REF_3 MISRA 2004 Advisory Rule 19.7 This is used to define user configurable callouts with parameters .*/
/** @violates @ref CDD_I2c_Cfg_h_REF_5 This is used to define user configurable callouts with parameters */
#define I2C_MASTER_TRANSMIT_COMPLETE_NOTIFICATION(u8Channel, u8NumberOfBytes) (I2C_MasterTransComplNotif(u8Channel, u8NumberOfBytes))



/**
* @brief            The call out configured by the user for master reception completion.
*/
/** @violates @ref CDD_I2c_Cfg_h_REF_3 MISRA 2004 Advisory Rule 19.7 This is used to define user configurable callouts with parameters .*/
/** @violates @ref CDD_I2c_Cfg_h_REF_5 This is used to define user configurable callouts with parameters */
#define I2C_MASTER_RECEIVE_COMPLETE_NOTIFICATION(u8Channel, u8NumberOfBytes) (I2C_MasterRcvComplNotif(u8Channel, u8NumberOfBytes))



/**
* @brief            The call out configured by the user for address matching notifications.
*/
/** @violates @ref CDD_I2c_Cfg_h_REF_3 MISRA 2004 Advisory Rule 19.7 This is used to define user configurable callouts with parameters .*/
/** @violates @ref CDD_I2c_Cfg_h_REF_5 This is used to define user configurable callouts with parameters */
#define I2C_SLAVE_ADDR_MATCH_NOTIFICATION(u8Channel, eDirection) (I2C_SlaveAddrMatchNotif(u8Channel, eDirection))



/**
* @brief            The call out configured by the user for slave transmission completion.
*/
/** @violates @ref CDD_I2c_Cfg_h_REF_3 MISRA 2004 Advisory Rule 19.7 This is used to define user configurable callouts with parameters .*/
/** @violates @ref CDD_I2c_Cfg_h_REF_5 This is used to define user configurable callouts with parameters */
#define I2C_SLAVE_TRANSMIT_COMPLETE_NOTIFICATION(u8Channel, u8NumberOfBytes) (I2C_SlateTransComplNotif(u8Channel, u8NumberOfBytes))



/**
* @brief            The call out configured by the user for slave reception completion.
*/
/** @violates @ref CDD_I2c_Cfg_h_REF_3 MISRA 2004 Advisory Rule 19.7 This is used to define user configurable callouts with parameters .*/
/** @violates @ref CDD_I2c_Cfg_h_REF_5 This is used to define user configurable callouts with parameters */
#define I2C_SLAVE_RECEIVE_COMPLETE_NOTIFICATION(u8Channel, u8NumberOfBytes) (I2C_SlaveRcvComplNotif(u8Channel, u8NumberOfBytes))



/**
* @brief            The call out configured by the user for slave byte reception.
*/
/** @violates @ref CDD_I2c_Cfg_h_REF_3 MISRA 2004 Advisory Rule 19.7 This is used to define user configurable callouts with parameters .*/
/** @violates @ref CDD_I2c_Cfg_h_REF_5 This is used to define user configurable callouts with parameters */
#define I2C_SLAVE_BYTE_RECEIVE_NOTIFICATION(u8Channel, u8ByteIndex) (I2C_SlaveByteRcvNotif(u8Channel, u8ByteIndex))


/**
* @brief            DMA is used for at least one channel (STD_ON/STD_OFF)
*/
#define I2C_DMA_USED   (STD_OFF)

/**
* @brief            FlexIO channel is used (STD_ON/STD_OFF)
*/
#define I2C_FLEXIO_USED   (STD_OFF)

/* Errors to be reported by the user configurable error notification */
#define I2C_E_PIN_LOW_TIMEOUT           ((uint8)0x01U)
#define I2C_E_FIFO_ERROR                ((uint8)0x02U)
#define I2C_E_ARBITRATION_LOST          ((uint8)0x03U)
#define I2C_E_UNEXPECTED_NACK           ((uint8)0x04U)

#define I2C_E_TX_UNDERFLOW              ((uint8)0x05U)
#define I2C_E_RX_OVERFLOW               ((uint8)0x06U)

#define I2C_E_SLAVE_FIFO_ERROR          ((uint8)0x10U)
#define I2C_E_SLAVE_BIT_ERROR           ((uint8)0x11U)






/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
/**
 * @brief Definition of the type of activation or procession mechanism of an I2c hw unit
 * @implements     I2c_DataDirectionType_enumeration
 * 
 */
typedef enum
{
    I2C_SEND_DATA       = 0x0U, /**< @brief Used to send data to a slave */
    I2C_RECEIVE_DATA    = 0x1U  /**< @brief Used to receive data from a slave */
} I2c_DataDirectionType;

/**
 * @brief Definition of the hardware channel type
 * 
 */
typedef enum
{
    I2C_LPI2C_CHANNEL       = 0x0U, /**< @brief This is used for LPI2C channels */
    I2C_FLEXIO_CHANNEL      = 0x1U  /**< @brief This is used for FlexIO channels */
} I2c_HwChannelType;

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief            DEM error reporting configuration.
* @details          This structure contains information DEM error reporting
*/
typedef struct
{
    VAR( Mcal_DemErrorType, I2C_VAR) I2c_E_TimeoutFailureCfg;

} I2c_DemConfigType;

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

extern CONST( I2c_DemConfigType, I2C_CONST) I2c_DemConfig;


/**
* @brief            The call out configured by the user for error notifications.
*/
/** @violates @ref CDD_I2c_Cfg_h_REF_2 MISRA 2004 Required Rule 8.7, these object are used trough the entire I2c code*/
extern FUNC(void, I2C_CODE) I2C_ERROR_NOTIFICATION(VAR (uint8, AUTOMATIC) u8Channel, VAR (uint8, AUTOMATIC) u8ErrorCode);



/**
* @brief            The call out configured by the user for master transmission completion.
*/
/** @violates @ref CDD_I2c_Cfg_h_REF_2 MISRA 2004 Required Rule 8.7, these object are used trough the entire I2c code*/
extern FUNC(void, I2C_CODE) I2C_MASTER_TRANSMIT_COMPLETE_NOTIFICATION(VAR (uint8, AUTOMATIC) u8Channel, VAR (uint8, AUTOMATIC) u8NumberOfBytes);



/**
* @brief            The call out configured by the user for master reception completion.
*/
/** @violates @ref CDD_I2c_Cfg_h_REF_2 MISRA 2004 Required Rule 8.7, these object are used trough the entire I2c code*/
extern FUNC(void, I2C_CODE) I2C_MASTER_RECEIVE_COMPLETE_NOTIFICATION(VAR (uint8, AUTOMATIC) u8Channel, VAR (uint8, AUTOMATIC) u8NumberOfBytes);



/**
* @brief            The call out configured by the user for address matching notifications.
*/
/** @violates @ref CDD_I2c_Cfg_h_REF_2 MISRA 2004 Required Rule 8.7, these object are used trough the entire I2c code*/
extern FUNC(void, I2C_CODE) I2C_SLAVE_ADDR_MATCH_NOTIFICATION(VAR (uint8, AUTOMATIC) u8Channel, VAR (I2c_DataDirectionType, AUTOMATIC) eDirection);



/**
* @brief            The call out configured by the user for slave transmission completion.
*/
/** @violates @ref CDD_I2c_Cfg_h_REF_2 MISRA 2004 Required Rule 8.7, these object are used trough the entire I2c code*/
extern FUNC(void, I2C_CODE) I2C_SLAVE_TRANSMIT_COMPLETE_NOTIFICATION(VAR (uint8, AUTOMATIC) u8Channel, VAR (uint8, AUTOMATIC) u8NumberOfBytes);



/**
* @brief            The call out configured by the user for slave reception completion.
*/
/** @violates @ref CDD_I2c_Cfg_h_REF_2 MISRA 2004 Required Rule 8.7, these object are used trough the entire I2c code*/
extern FUNC(void, I2C_CODE) I2C_SLAVE_RECEIVE_COMPLETE_NOTIFICATION(VAR (uint8, AUTOMATIC) u8Channel, VAR (uint8, AUTOMATIC) u8NumberOfBytes);



/**
* @brief            The call out configured by the user for slave byte reception.
*/
/** @violates @ref CDD_I2c_Cfg_h_REF_2 MISRA 2004 Required Rule 8.7, these object are used trough the entire I2c code*/
extern FUNC(boolean, I2C_CODE) I2C_SLAVE_BYTE_RECEIVE_NOTIFICATION(VAR (uint8, AUTOMATIC) u8Channel, VAR (uint8, AUTOMATIC) u8ByteIndex);


#ifdef __cplusplus
}
#endif

#endif /* I2C_CFG_H */
