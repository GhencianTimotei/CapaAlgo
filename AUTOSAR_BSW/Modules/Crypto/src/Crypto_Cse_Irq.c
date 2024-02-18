/**
*   @file    Crypto_Cse_Irq.c
*   @version 1.0.1
*
*   @brief   AUTOSAR Crypto - Files used by Crypto that contain the ISRs.
*   @details This files implements ISR functions used for Crypto interrupts
*
*   @addtogroup CRYPTO
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

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Crypto_Cse_Irq_c_REF_1
*           Violates MISRA 2004 Required Rule 1.4, Identifier clash.
*           This violation is due to the requirement that request to have a file version check.
*
* @section Crypto_Cse_Irq_c_REF_2
*           Violates MISRA 2004 Required Rule 5.1, External identifiers shall be distinct.
*           The used compilers use more than 31 chars for identifiers.
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Crypto_Cse.h"
#include "Crypto_Cse_Irq.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CRYPTO_CSE_IRQ_VENDOR_ID_C                    43
/**
* @violates @ref Crypto_Cse_Irq_c_REF_1 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
/**
* @violates @ref Crypto_Cse_Irq_c_REF_2 Violates MISRA 2004 Required Rule 5.1, External identifiers shall be distinct.
*/
#define CRYPTO_CSE_IRQ_AR_RELEASE_MAJOR_VERSION_C     4
/**
* @violates @ref Crypto_Cse_Irq_c_REF_1 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
/**
* @violates @ref Crypto_Cse_Irq_c_REF_2 Violates MISRA 2004 Required Rule 5.1, External identifiers shall be distinct.
*/
#define CRYPTO_CSE_IRQ_AR_RELEASE_MINOR_VERSION_C     3
/**
* @violates @ref Crypto_Cse_Irq_c_REF_1 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
/**
* @violates @ref Crypto_Cse_Irq_c_REF_2 Violates MISRA 2004 Required Rule 5.1, External identifiers shall be distinct.
*/
#define CRYPTO_CSE_IRQ_AR_RELEASE_REVISION_VERSION_C  1
/**
* @violates @ref Crypto_Cse_Irq_c_REF_1 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
/**
* @violates @ref Crypto_Cse_Irq_c_REF_2 Violates MISRA 2004 Required Rule 5.1, External identifiers shall be distinct.
*/
#define CRYPTO_CSE_IRQ_SW_MAJOR_VERSION_C             1
/**
* @violates @ref Crypto_Cse_Irq_c_REF_1 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
/**
* @violates @ref Crypto_Cse_Irq_c_REF_2 Violates MISRA 2004 Required Rule 5.1, External identifiers shall be distinct.
*/
#define CRYPTO_CSE_IRQ_SW_MINOR_VERSION_C             0
/**
* @violates @ref Crypto_Cse_Irq_c_REF_1 Violates MISRA 2004 Required Rule 1.4,  Identifier clash
*/
/**
* @violates @ref Crypto_Cse_Irq_c_REF_2 Violates MISRA 2004 Required Rule 5.1, External identifiers shall be distinct.
*/
#define CRYPTO_CSE_IRQ_SW_PATCH_VERSION_C             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Crypto_Cse_Irq source file and Crypto_Cse.h header file are of the same vendor */
#if (CRYPTO_CSE_IRQ_VENDOR_ID_C != CRYPTO_CSE_H_VENDOR_ID)
    #error "Crypto_Cse_Irq.c and Crypto_Cse.h have different vendor ids"
#endif

/* Check if Crypto_Cse_Irq source file and Crypto_Cse.h header file are of the same Autosar version */
#if ((CRYPTO_CSE_IRQ_AR_RELEASE_MAJOR_VERSION_C    != CRYPTO_CSE_H_AR_RELEASE_MAJOR_VERSION) || \
     (CRYPTO_CSE_IRQ_AR_RELEASE_MINOR_VERSION_C    != CRYPTO_CSE_H_AR_RELEASE_MINOR_VERSION) || \
     (CRYPTO_CSE_IRQ_AR_RELEASE_REVISION_VERSION_C != CRYPTO_CSE_H_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Crypto_Cse_Irq.c  and Crypto_Cse.h are different"
#endif

/* Check if Crypto_Cse_Irq source file and Crypto_Cse.h header file are of the same Software version */
#if ((CRYPTO_CSE_IRQ_SW_MAJOR_VERSION_C != CRYPTO_CSE_H_SW_MAJOR_VERSION) || \
     (CRYPTO_CSE_IRQ_SW_MINOR_VERSION_C != CRYPTO_CSE_H_SW_MINOR_VERSION) || \
     (CRYPTO_CSE_IRQ_SW_PATCH_VERSION_C != CRYPTO_CSE_H_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Crypto_Cse_Irq.c  and Crypto_Cse.h are different"
#endif

/* Check if Crypto_Cse_Irq source file and Crypto_Cse_Irq.h header file are of the same vendor */
#if (CRYPTO_CSE_IRQ_VENDOR_ID_C != CRYPTO_CSE_IRQ_VENDOR_ID)
    #error "Crypto_Cse_Irq.c and Crypto_Cse_Irq.h have different vendor ids"
#endif

/* Check if Crypto_Cse_Irq source file and Crypto_Cse_Irq.h header file are of the same Autosar version */
#if ((CRYPTO_CSE_IRQ_AR_RELEASE_MAJOR_VERSION_C    != CRYPTO_CSE_IRQ_AR_RELEASE_MAJOR_VERSION) || \
     (CRYPTO_CSE_IRQ_AR_RELEASE_MINOR_VERSION_C    != CRYPTO_CSE_IRQ_AR_RELEASE_MINOR_VERSION) || \
     (CRYPTO_CSE_IRQ_AR_RELEASE_REVISION_VERSION_C != CRYPTO_CSE_IRQ_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Crypto_Cse_Irq.c  and Crypto_Cse_Irq.h are different"
#endif

/* Check if Crypto_Cse_Irq source file and Crypto_Cse_Irq.h header file are of the same Software version */
#if ((CRYPTO_CSE_IRQ_SW_MAJOR_VERSION_C != CRYPTO_CSE_IRQ_SW_MAJOR_VERSION) || \
     (CRYPTO_CSE_IRQ_SW_MINOR_VERSION_C != CRYPTO_CSE_IRQ_SW_MINOR_VERSION) || \
     (CRYPTO_CSE_IRQ_SW_PATCH_VERSION_C != CRYPTO_CSE_IRQ_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Crypto_Cse_Irq.c  and Crypto_Cse_Irq.h are different"
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define CRYPTO_START_SEC_CODE

#include "Crypto_MemMap.h"

ISR(CRYPTO_CSE_FTFC_ISR)
{
    Crypto_Cse_FTFCProcessInterrupt();

    EXIT_INTERRUPT();
}

#define CRYPTO_STOP_SEC_CODE

#include "Crypto_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
