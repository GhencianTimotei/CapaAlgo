/* polyspace MISRA-C3:1.1 [Justified:Unset] "All macro definitions are needed." */
/*================================================================================================*/
/**
*   @file    config.c
*   @version 1.0.0
*
*   @brief   Config file for ASW
*   @details None
*     
*    (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*    All Rights Reserved.
*
*    This file contains sample code only. It is not part of the production code deliverables.
*/       
/*=================================================================================================
*    Platform      :      ARM
*    Build Version :      S32K14x_MCAL_1_0_1_RTM_ASR_REL_4_3_REV_0001_20190620
*
==================================================================================================*/

#include "typedefs.h"
#include "Std_Types.h"
#include "config.h"
#include "v_cfg.h"
#include "v_def.h"

/*==================================================================================================
*                                        LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
/* polyspace+1 MISRA-C3:2.4 [Justified:Low] "Added for further implementation." */
typedef struct tAswHeader
{
    U8 const * pWVLogicalSwBlockASW;
    void* p1;
    void* p2;
    void* p3;
    void* p4;
    void* p5;
    void* p6;
    void* p7;
} tAswHeader;
/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/
/* polyspace+2 MISRA-C3:5.1 [Justified:Low] "External identifiers are different" */
/* polyspace+1 MISRA-C3:10.3 [Not a defect:Low] "does not affect the functionality" */
const U8 VW_Logical_Software_Block_Version_ASW[4] = {ENGDROP, ECU_VAR, RUN, SPRINT};
/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/
/* polyspace+2 MISRA-C3:20.1 [Justified:Low] "The file inclusion is used for memory mapping." */
#define ASWHEADER_START_SEC_CONST
#include "MemMap.h"
/* polyspace+1 MISRA-C3:8.4 [Justified:Low] "External Usage dependent on project setup" */
V_MEMROM0 V_MEMROM1 tAswHeader V_MEMROM2 AswHeader = 
{
    &VW_Logical_Software_Block_Version_ASW[0],
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
};

/* polyspace+2 MISRA-C3:20.1 [Justified:Low] "The file inclusion is used for memory mapping." */
#define ASWHEADER_STOP_SEC_CONST
#include "MemMap.h"
/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
