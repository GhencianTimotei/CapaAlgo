/**
*   @file    Crypto_Cse_Irq.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Crypto - CSE Irq header file.
*   @details CSE Irq low level driver API.
*
*   @addtogroup Crypto
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.3 MCAL
*   Platform             : ARM
*   Peripheral           : Crypto
*   Dependencies         : none
*
*   Autosar Version      : 4.3.1
*   Autosar Revision     : ASR_REL_4_3_REV_0001
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : S32K14x_MCAL_1_0_1_RTM_P1_HF3_ASR_REL_4_3_REV_0001_20210324
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2019 NXP
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef CRYPTO_CSE_IRQ_H
#define CRYPTO_CSE_IRQ_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Crypto_Cse_Irq_h_REF_1
*           Violates MISRA 2004 Required Rule 1.4, Identifier clash.
*           This violation is due to the requirement that request to have a file version check.
*
* @section Crypto_Cse_Irq_h_REF_2
*           Violates MISRA 2004 Required Rule 5.1, External identifiers shall be distinct.
*           The used compilers use more than 31 chars for identifiers.
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit

==================================================================================================*/

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CRYPTO_CSE_IRQ_VENDOR_ID                       43
/**
* @violates @ref Crypto_Cse_Irq_h_REF_1 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
/**
* @violates @ref Crypto_Cse_Irq_h_REF_2 Violates MISRA 2004 Required Rule 5.1, External identifiers shall be distinct.
*/
#define CRYPTO_CSE_IRQ_AR_RELEASE_MAJOR_VERSION        4
/**
* @violates @ref Crypto_Cse_Irq_h_REF_1 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
/**
* @violates @ref Crypto_Cse_Irq_h_REF_2 Violates MISRA 2004 Required Rule 5.1, External identifiers shall be distinct.
*/
#define CRYPTO_CSE_IRQ_AR_RELEASE_MINOR_VERSION        3
/**
* @violates @ref Crypto_Cse_Irq_h_REF_1 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
/**
* @violates @ref Crypto_Cse_Irq_h_REF_2 Violates MISRA 2004 Required Rule 5.1, External identifiers shall be distinct.
*/
#define CRYPTO_CSE_IRQ_AR_RELEASE_REVISION_VERSION     1
/**
* @violates @ref Crypto_Cse_Irq_h_REF_1 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
/**
* @violates @ref Crypto_Cse_Irq_h_REF_2 Violates MISRA 2004 Required Rule 5.1, External identifiers shall be distinct.
*/
#define CRYPTO_CSE_IRQ_SW_MAJOR_VERSION                1
/**
* @violates @ref Crypto_Cse_Irq_h_REF_1 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
/**
* @violates @ref Crypto_Cse_Irq_h_REF_2 Violates MISRA 2004 Required Rule 5.1, External identifiers shall be distinct.
*/
#define CRYPTO_CSE_IRQ_SW_MINOR_VERSION                0
/**
* @violates @ref Crypto_Cse_Irq_h_REF_1 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
/**
* @violates @ref Crypto_Cse_Irq_h_REF_2 Violates MISRA 2004 Required Rule 5.1, External identifiers shall be distinct.
*/
#define CRYPTO_CSE_IRQ_SW_PATCH_VERSION                1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

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
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define CRYPTO_START_SEC_CODE

#include "Crypto_MemMap.h"

ISR(CRYPTO_CSE_FTFC_ISR);

#define CRYPTO_STOP_SEC_CODE

#include "Crypto_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* CRYPTO_CSE_IRQ_H */

/** @} */
