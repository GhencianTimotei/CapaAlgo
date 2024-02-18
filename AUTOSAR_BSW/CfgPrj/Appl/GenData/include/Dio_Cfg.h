/**
*   @file    Dio_Cfg.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Dio configuration header.
*   @details This file is the Autosar DIO driver configuration header. This
*            file is automatically generated, do not modify manually.
*
*   @addtogroup DIO_CFG
*   @{
*/
/*=================================================================================================
*   Project              : AUTOSAR 4.3 MCAL
*   Platform             : ARM
*   Peripheral           : GPIO
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
=================================================================================================*/
/*=================================================================================================
=================================================================================================*/

#ifndef DIO_CFG_H
#define DIO_CFG_H

#ifdef __cplusplus
extern "C" {
#endif
/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Dio_Cfg_H_REF_1
*          Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
*          that 31 character significance and case sensitivity are supported for external
*          identifiers. 
*          The used compilers/linkers allow more than 31 characters significance for external identifiers.
* 
* @section Dio_Cfg_H_REF_2
*          Violates MISRA 2004 Required Rule 19.15, Repeated include file, 
*          Precautions shall be taken in order to prevent the contents of a header file 
*          being included twice. This violation is not fixed since the inclusion of MemMap.h is as per 
*          Autosar requirement MEMMAP003.
*
* @section Dio_Cfg_H_REF_3
*          Violates MISRA 2004 Required Rule 8.7, Objects shall be defined at block scope 
*          if they are only accessed from within a single function. 
*          These objects are used in various parts of the code.
*
* @section [global]
*          Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not
*          rely on the significance of more than 31 characters. The used compilers use more than
*          31 chars for identifiers.
**/


/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/
/** @violates @ref Dio_Cfg_H_REF_2 Precautions to prevent the contents of a header file being included twice. */
#include "Dio_EnvCfg.h"

/**
 *     @file       Dio_Cfg.h
 *     @implements Dio_Cfg.h_Artifact
 * */

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/

#define DIO_VENDOR_ID_CFG                   43
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define DIO_AR_RELEASE_MAJOR_VERSION_CFG    4
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define DIO_AR_RELEASE_MINOR_VERSION_CFG    3
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define DIO_AR_RELEASE_REVISION_VERSION_CFG 1
#define DIO_SW_MAJOR_VERSION_CFG            1
#define DIO_SW_MINOR_VERSION_CFG            0
#define DIO_SW_PATCH_VERSION_CFG            1

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/

/* Dio_EnvCfg.h version check start */
#if ((DIO_AR_RELEASE_MAJOR_VERSION_CFG != DIO_ENVCFG_AR_RELEASE_MAJOR_VERSION) ||   \
     (DIO_AR_RELEASE_MINOR_VERSION_CFG != DIO_ENVCFG_AR_RELEASE_MINOR_VERSION) ||   \
     (DIO_AR_RELEASE_REVISION_VERSION_CFG != DIO_ENVCFG_AR_RELEASE_REVISION_VERSION)\
    )
    #error "AUTOSAR Version Numbers of Dio_Cfg.h and Dio_EnvCfg.h are different"
#endif

#if ((DIO_SW_MAJOR_VERSION_CFG != DIO_ENVCFG_SW_MAJOR_VERSION) || \
     (DIO_SW_MINOR_VERSION_CFG != DIO_ENVCFG_SW_MINOR_VERSION) || \
     (DIO_SW_PATCH_VERSION_CFG != DIO_ENVCFG_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Dio_Cfg.h and Dio_EnvCfg.h are different"
#endif

#if ((DIO_VENDOR_ID_CFG != DIO_ENVCFG_VENDOR_ID))
    #error "VENDOR ID for Dio_Cfg.h and Dio_EnvCfg.h is different"
#endif
/* Dio_EnvCfg.h version check end */
/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/

/**
* @brief          Enable or Disable Development Error Detection.
*
* @implements     DIO_DEV_ERROR_DETECT_define
* @api
*/
#define DIO_DEV_ERROR_DETECT    (STD_OFF)

/**
* @brief          Function @p Dio_GetVersionInfo() enable switch.
*
* @implements     DIO_VERSION_INFO_API_define
* @api
*/
#define DIO_VERSION_INFO_API    (STD_OFF)

/**
* @brief          Function @p Dio_FlipChannel() enable switch.
*
* @api
*/
#define DIO_FLIP_CHANNEL_API    (STD_OFF)

/**
* @brief          Function @p Dio_MaskedWritePort() enable switch.
*
* @api
*/
#define DIO_MASKEDWRITEPORT_API (STD_OFF)

/**
* @brief          Reversed port functionality enable switch.
*
* @implements     DIO_REVERSEPORTBITS_define
* @api
*/
#define DIO_REVERSEPORTBITS     (STD_OFF)

/**
* @brief          Undefined pins masking enable switch.
*
* @api
*/
#define DIO_READZERO_UNDEFINEDPORTS (STD_OFF)


/**
* @brief          Number of implemented ports.
*
* @note           Used for channel, port and channel group validation.
*
* @api
*/
#define DIO_NUM_PORTS_U16               ((uint16)0x5)

/**
* @brief          Number channel in a port.
*
* @note           Used for channel, port and channel group validation.
*
* @api
*/
#define DIO_NUM_CHANNELS_PER_PORT_U16   ((uint16)(sizeof(Dio_PortLevelType) * 0x8U))

/**
* @brief          Number of channels available on the implemented ports.
*
* @note           Used for channel validation.
*
* @api
*/
#define DIO_NUM_CHANNELS_U16            ((uint16)(DIO_NUM_PORTS_U16 * DIO_NUM_CHANNELS_PER_PORT_U16))

/**
* @brief          Mask representing no available channels on a port.
*
* @note           Used for channel validation.
*
* @api
*/
#define DIO_NO_AVAILABLE_CHANNELS_U16   ((Dio_PortLevelType)0x0U)

/**
* @brief          Mask representing the maximum valid offset for a channel group.
*
* @note           Used for channel group validation.
*
* @api
*/
#define DIO_MAX_VALID_OFFSET_U8           ((uint8)0x1F)

/**
* @brief          Define to state if the current platform supports configuring the pins
*                 as input-output in the same time.
*
* @note           Used by Dio_FlipChannel() function.
*
* @api
*/
#define DIO_INOUT_CONFIG_SUPPORTED        (STD_OFF)
/**
*   @brief   Enables or disables the access to a hardware register from user mode
*            USER_MODE_SOFT_LOCKING:        All reads to hw registers will be done via REG_PROT, user mode access
*            SUPERVISOR_MODE_SOFT_LOCKING:  Locks the access to the registers only for supervisor mode
*
*   @note    Currently, no register protection mechanism is used for Dio driver.
*/
#define DIO_USER_MODE_SOFT_LOCKING      (STD_OFF)

/**
* @brief          Dio driver Pre-Compile configuration switch.
*
* @api
*/
#define DIO_PRECOMPILE_SUPPORT


/**
* @brief Support for User mode.
*        If this parameter has been configured to 'STD_ON', the Dio driver code can be executed from both supervisor and user mode.
*
*/

#define DIO_ENABLE_USER_MODE_SUPPORT   (STD_OFF)


#ifndef MCAL_ENABLE_USER_MODE_SUPPORT
 #ifdef DIO_ENABLE_USER_MODE_SUPPORT
  #if (STD_ON == DIO_ENABLE_USER_MODE_SUPPORT)
    #error MCAL_ENABLE_USER_MODE_SUPPORT is not enabled. For running Dio in user mode the MCAL_ENABLE_USER_MODE_SUPPORT needs to be defined
  #endif /* (STD_ON == DIO_ENABLE_USER_MODE_SUPPORT) */
 #endif /* ifdef DIO_ENABLE_USER_MODE_SUPPORT*/
#endif /* ifndef MCAL_ENABLE_USER_MODE_SUPPORT */

/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/

/**
* @brief          Symbolic name for the configuration Dio_ConfigPC.
*
*/
#define Dio_ConfigPC    (DioConfig)  

/* ========== DioConfig ========== */

/* ---------- DioPort_PORT_A ---------- */

/**
* @brief          Symbolic name for the port DioPort_PORT_A.
*
*/
#define DioConf_DioPort_DioPort_PORT_A  ((uint8)0x00U)

/**
* @brief          Symbolic name for the channel Dio_PTA0_Actor_EN.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The used compilers use more than 31 chars for identifiers. */
#define  DioConf_DioChannel_Dio_PTA0_Actor_EN ((uint16)0x0000U)

/* ---------- DioPort_PORT_B ---------- */

/**
* @brief          Symbolic name for the port DioPort_PORT_B.
*
*/
#define DioConf_DioPort_DioPort_PORT_B  ((uint8)0x01U)

/**
* @brief          Symbolic name for the channel Dio_PTB2_U_SPG1_IO.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The used compilers use more than 31 chars for identifiers. */
#define  DioConf_DioChannel_Dio_PTB2_U_SPG1_IO ((uint16)0x0022U)

/**
* @brief          Symbolic name for the channel Dio_SPI_CS00_NFC.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The used compilers use more than 31 chars for identifiers. */
#define  DioConf_DioChannel_Dio_SPI_CS00_NFC ((uint16)0x0025U)

/**
* @brief          Symbolic name for the channel Dio_PTB13_DEBUG.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The used compilers use more than 31 chars for identifiers. */
#define  DioConf_DioChannel_Dio_PTB13_DEBUG ((uint16)0x002dU)

/* ---------- DioPort_PORT_C ---------- */

/**
* @brief          Symbolic name for the port DioPort_PORT_C.
*
*/
#define DioConf_DioPort_DioPort_PORT_C  ((uint8)0x02U)

/**
* @brief          Symbolic name for the channel Dio_PTC7_OP_AMP_EN.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The used compilers use more than 31 chars for identifiers. */
#define  DioConf_DioChannel_Dio_PTC7_OP_AMP_EN ((uint16)0x0047U)

/**
* @brief          Symbolic name for the channel Dio_PTC8_DEBUG.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The used compilers use more than 31 chars for identifiers. */
#define  DioConf_DioChannel_Dio_PTC8_DEBUG ((uint16)0x0048U)

/* ---------- DioPort_PORT_D ---------- */

/**
* @brief          Symbolic name for the port DioPort_PORT_D.
*
*/
#define DioConf_DioPort_DioPort_PORT_D  ((uint8)0x03U)

/**
* @brief          Symbolic name for the channel Dio_PTD0_CAN_SLP.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The used compilers use more than 31 chars for identifiers. */
#define  DioConf_DioChannel_Dio_PTD0_CAN_SLP ((uint16)0x0060U)

/**
* @brief          Symbolic name for the channel Dio_PTD2_Ind_Sensor_IO.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The used compilers use more than 31 chars for identifiers. */
#define  DioConf_DioChannel_Dio_PTD2_Ind_Sensor_IO ((uint16)0x0062U)

/* ---------- DioPort_PORT_E ---------- */

/**
* @brief          Symbolic name for the port DioPort_PORT_E.
*
*/
#define DioConf_DioPort_DioPort_PORT_E  ((uint8)0x04U)

/**
* @brief          Symbolic name for the channel Dio_PTE8_NFC_PDOWN.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The used compilers use more than 31 chars for identifiers. */
#define  DioConf_DioChannel_Dio_PTE8_NFC_PDOWN ((uint16)0x0088U)

/**
* @brief          Symbolic name for the channel Dio_PTE4_CAN_RX.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The used compilers use more than 31 chars for identifiers. */
#define  DioConf_DioChannel_Dio_PTE4_CAN_RX ((uint16)0x0084U)

/**
* @brief          Symbolic name for the channel Dio_IRQ_NFC.
*
*/


/** @violates @ref Dio_Cfg_H_REF_1 The used compilers use more than 31 chars for identifiers. */
#define  DioConf_DioChannel_Dio_IRQ_NFC ((uint16)0x0089U)


/*=================================================================================================
*                                             ENUMS
=================================================================================================*/

/*=================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/

/**
* @brief          Type of a DIO port representation.
*
* @implements     Dio_PortType_typedef
*
* @api
*/
typedef uint8 Dio_PortType;

/**
* @brief          Type of a DIO channel representation.
*
* @implements     Dio_ChannelType_typedef
*
* @api
*/
typedef uint16 Dio_ChannelType;

/**
* @brief          Type of a DIO port levels representation.
*
* @implements     Dio_PortLevelType_typedef
*
* @api
*/
typedef uint32 Dio_PortLevelType;

/**
* @brief          Type of a DIO channel levels representation.
*
* @implements     Dio_LevelType_typedef
*
* @api
*/
typedef uint8 Dio_LevelType;

/**
* @brief          Type of a DIO channel group representation.
*
* @implements     Dio_ChannelGroupType_struct
*
* @api
*/
typedef struct
{
    VAR(Dio_PortType, AUTOMATIC)      port;      /**< @brief Port identifier.  */
    VAR(uint8, AUTOMATIC)             u8offset;    /**< @brief Bit offset within the port. */
    VAR(Dio_PortLevelType, AUTOMATIC) mask;      /**< @brief Group mask. */
} Dio_ChannelGroupType;

/**
* @brief          Type of a DIO configuration structure.
*
* @note           In this implementation there is no need for a configuration
*                 structure there is only a dummy field, it is recommended
*                 to initialize this field to zero.
*
*
* @api
*/
typedef struct
{                                                                       
    VAR(uint8, AUTOMATIC) u8NumChannelGroups; /**< @brief Number of channel groups in configuration */
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) pChannelGroupList;  /**< @brief 
                                               Pointer to list of channel groups in configuration */
} Dio_ConfigType;

/*=================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/

#define DIO_START_SEC_CONFIG_DATA_UNSPECIFIED
/** @violates @ref Dio_Cfg_H_REF_2 Precautions to prevent the contents of a header file being included twice. */
#include "Dio_MemMap.h"

/**
* @brief Array of bitmaps of output pins available per port
*/
/** @violates @ref Dio_Cfg_H_REF_3 Objects shall be defined at block scope if they are only accessed from within a single function. */
extern CONST(Dio_PortLevelType, DIO_CONST) Dio_aAvailablePinsForWrite[DIO_NUM_PORTS_U16];

/**
* @brief Array of bitmaps of input pins available per port
*/
/** @violates @ref Dio_Cfg_H_REF_3 Objects shall be defined at block scope if they are only accessed from within a single function. */
extern CONST(Dio_PortLevelType, DIO_CONST) Dio_aAvailablePinsForRead[DIO_NUM_PORTS_U16];

/**
* @brief          List of channel groups in configuration DioConfig.
*/



#define DIO_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/** @violates @ref Dio_Cfg_H_REF_2 Precautions to prevent the contents of a header file being included twice. */
#include "Dio_MemMap.h"
/*=================================================================================================
*                                    FUNCTION PROTOTYPES
=================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif  /* DIO_CFG_H */

/** @} */
