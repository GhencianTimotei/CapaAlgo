/**
*    @file        typedefs.h
*    @version     1.0.1
*
*    @brief       Integration Framework - global type definition header
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
/*==================================================================================================
====================================================================================================*/

#ifndef _TYPEDEFS_H_
    /* polyspace < MISRA-C3:21.1 :  Not a defect : Justify with annotations > Defines needed to avoid duble inclusion. */
    #define _TYPEDEFS_H_
    /* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
    #define SWCRTE_STD_ON   1U
    /* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
	#define SWCRTE_STD_OFF  0U
    /* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
    #define SWCRTE_TRUE   1U
    /* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
	#define SWCRTE_FALSE  0U

    /* polyspace+18 MISRA-C3:2.3 [Justified:Low] "Added for further implementation." */
    /* polyspace <  MISRA-C3:5.6 :  Not a defect : Justify with annotations > The identifier is unique. */	
    typedef unsigned char boolean_t;
    /* polyspace <  MISRA-C3:5.6 :  Not a defect : Justify with annotations > The identifier is unique. */
    typedef unsigned char uint8_t;
    /* polyspace <  MISRA-C3:5.6 :  Not a defect : Justify with annotations > The identifier is unique. */
    typedef unsigned short uint16_t;
    /* polyspace <  MISRA-C3:5.6 :  Not a defect : Justify with annotations > The identifier is unique. */
    typedef unsigned int uint32_t;
    /* polyspace <  MISRA-C3:5.6 :  Not a defect : Justify with annotations > The identifier is unique. */
    typedef unsigned long long uint64_t;
    
    typedef signed char         int8_t;
    /* polyspace <  MISRA-C3:5.6 :  Not a defect : Justify with annotations > The identifier is unique. */
    typedef signed short        int16_t;
    /* polyspace <  MISRA-C3:5.6 :  Not a defect : Justify with annotations > The identifier is unique. */
    typedef signed int         int32_t;
    /* polyspace <  MISRA-C3:5.6 :  Not a defect : Justify with annotations > The identifier is unique. */
    typedef signed long long    int64_t;

    /* Standard typedefs used by header files, based on ISO C standard */
    /* polyspace <  MISRA-C3:8.1,D4.6 : Not a defect : Justify with annotations > Standard typedefs used by header files, based on ISO C standard */
    /* polyspace:begin < MISRA-C3:2.2,2.3 : Not a defect : Justify with annotations > Should be kept for future usage */
    /* polyspace+11 MISRA-C3:D4.6 [Justified:Low] "Standard typedefs used by header files, based on ISO C standard" */
    typedef volatile signed char vint8_t;
    typedef volatile unsigned char vuint8_t;

    typedef volatile signed short vint16_t;
    typedef volatile unsigned short vuint16_t;

    typedef volatile signed int vint32_t;
    typedef volatile unsigned int vuint32_t;
    
    typedef volatile signed long long vint64_t;
    typedef volatile unsigned long long vuint64_t;
    /* polyspace:end < MISRA-C3:2.2,2.3 : Not a defect : Justify with annotations > Should be kept for future usage */

    /*************************************************************************/

    /* typedef unsigned char  BOOL; for compatibility with legacy SW*/
	#define STATIC static
	#define READONLY const
	#define NEAR
	#define U8_NULL  ((U8)0)
	#define U16_MAX_VALUE   ((U16)0xFFFFU)
    typedef unsigned int       XINT;
	#define LOCAL   static				  /* no export of identifiers */
    /***************************************************************************/
#endif





