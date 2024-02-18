/**
*     @file         Crcu_Types.h
*     @version      1.0.1
*
*     @brief        AUTOSAR Crcu driver types header file.
*     @details      Crcu driver header file, containing type definitions
*                   that are needed by the Crcu driver.
*
*     @addtogroup   CRCU_MODULE
*     @{
*/
/*==================================================================================================
*     Project             : AUTOSAR 4.3 MCAL
*     Platform            : ARM
*     Peripheral          : CRCV2
*     Dependencies        : none
*
*     Autosar Version     : 4.3.1
*     Autosar Revision    : ASR_REL_4_3_REV_0001
*     Autosar ConfVariant :
*     SWVersion           : 1.0.1
*     BuildVersion        : S32K14x_MCAL_1_0_1_RTM_ASR_REL_4_3_REV_0001_20190621
*
*     (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2019 NXP
*     All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef CRCU_TYPES_H
#define CRCU_TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section [global]
*          Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
*          on the significance of more than 31 characters. The used compilers use more than 31 chars for
*          identifiers.
*/

/*==================================================================================================
*                                          INCLUDE FILES
*  1) system and project includes
*  2) needed interfaces from external units
*  3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Crcu_Ipw_Types.h"

/*==================================================================================================
*                                SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CRCU_TYPES_VENDOR_ID                    43
#define CRCU_TYPES_MODULE_ID                    255
#define CRCU_TYPES_AR_RELEASE_MAJOR_VERSION     4
#define CRCU_TYPES_AR_RELEASE_MINOR_VERSION     3
#define CRCU_TYPES_AR_RELEASE_REVISION_VERSION  1
#define CRCU_TYPES_SW_MAJOR_VERSION             1
#define CRCU_TYPES_SW_MINOR_VERSION             0
#define CRCU_TYPES_SW_PATCH_VERSION             1

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Crcu_Ipw_Types.h header file are of the same vendor Id */
#if (CRCU_TYPES_VENDOR_ID != CRCU_IPW_TYPES_VENDOR_ID)
    #error "Crcu_Types.h and Crcu_Ipw_Types.h have different vendor ids"
#endif
/* Check if current file and Crcu_Ipw_Types.h header file are of the same Autosar version */
#if ((CRCU_TYPES_AR_RELEASE_MAJOR_VERSION    != CRCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (CRCU_TYPES_AR_RELEASE_MINOR_VERSION    != CRCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (CRCU_TYPES_AR_RELEASE_REVISION_VERSION != CRCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Crcu_Types.h and Crcu_Ipw_Types.h are different"
#endif
/* Check if current file and Crcu_Ipw_Types.h header file are of the same software version */
#if ((CRCU_TYPES_SW_MAJOR_VERSION != CRCU_IPW_TYPES_SW_MAJOR_VERSION) || \
     (CRCU_TYPES_SW_MINOR_VERSION != CRCU_IPW_TYPES_SW_MINOR_VERSION) || \
     (CRCU_TYPES_SW_PATCH_VERSION != CRCU_IPW_TYPES_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Crcu_Types.h and Crcu_Ipw_Types.h are different"
#endif

 /* Check if header file and Std_Types.h file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((CRCU_TYPES_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (CRCU_TYPES_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION)    \
        )
    #error "AutoSar Version Numbers of Crcu_Types.h and Std_Types.h are different"
    #endif
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                        DEFINES AND MACROS
==================================================================================================*/


/*==================================================================================================
*                                              ENUMS
==================================================================================================*/


/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
 * @brief       Type that defines the identifier of a CRCU channel.
 * @details     Provides CRCU channel selection
 * @implements  Crcu_ChannelIdType_typedef
 * */
typedef uint8 Crcu_ChannelIdType;

/**
 * @brief       Type that defines the identifier of a CRCU channel configuration.
 * @details     Provides CRCU channel configuration selection
 * @implements  Crcu_ChannelConfigIdType_typedef
 * */
typedef uint8 Crcu_ChannelConfigIdType;

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                      FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif  /* CRCU_TYPES_H */
/** @} */
