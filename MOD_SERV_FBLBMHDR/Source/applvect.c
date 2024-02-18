/***********************************************************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief         This file contains the start address of the application software. It is usually linked and
 *                 compiled with the Bootloader and is located OUTSIDE the protected area of the FBL. The start
 *                 address has to be overwritten by the downloaded application software.
 *
 *                 Please note that there is no interrupt indirection on Freescale PPC platforms. Please use the
 *                 appropriate setting (e.g. IVPR, interrupt vector prefix register) to redirect interrupts to
 *                 your application software.
 *                 This file must be compiled and linked in the Bootloader and the application software to the
 *                 same memory location.
 *
 *  \note          Please note, that this file contains example source code used by the Flash Bootloader. These
 *                 functions may influence the behavior of the bootloader in principle. Therefore, great care must
 *                 be taken to verify the correctness of the implementation. The contents of the originally delivered
 *                 files are only examples resp. implementation proposals. With regard to the fact that these
 *                 functions are meant for demonstration purposes only, Vector Informatik's liability shall be
 *                 expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
 *
 *  --------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  --------------------------------------------------------------------------------------------------------------------
 *  Achim Strobelt                Ach           Vector Informatik GmbH
 *  Christian Baeuerle            CB            Vector Informatik GmbH
 *  Marco Riedl                   Rie           Vector Informatik GmbH
 *  Dennis O'Donnell              Dod           Vector North America, Inc.
 *  Thomas Bezold                 TBe           Vector Informatik GmbH
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  02.00.00   2013-07-05  Ach     ESCAN00068525    Rework of module, support MPC57xx
 *  02.01.00   2014-07-18  Ach     ESCAN00075904    Rework of compiler switches
 *  02.02.00   2016-04-26  CB      ESCAN00089744    Support for S32K
 *  02.03.00   2016-06-16  Rie     ESCAN00090350    Support for IMX6X
 *  02.04.00   2017-08-03  Dod     ESCAN00095748    Support for Accordo2
 *                         Ach     ESCAN00096160    Include FblHal_Cfg.h for Cfg5 based configurations
 *  02.04.01   2019-03-22  TBe     ESCAN00102585    Jump to application leads to exception
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/

#include "v_cfg.h"
#if defined( V_GEN_GENERATOR_MSR )
# include "FblHal_Cfg.h"
#endif /* V_GEN_GENRATOR_MSR */
#include "v_def.h"
#include "applvect.h"

/***********************************************************************************************************************
 *  VERSION
 **********************************************************************************************************************/

#if ((FBLVTABAPPL_MPC5500_VERSION != 0x0204u ) || \
     (FBLVTABAPPL_MPC5500_RELEASE_VERSION != 0x01u))
# error "Error in applvect.c: Source and header file are inconsistent!"
#endif

/***********************************************************************************************************************
 *  EXERNAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/* Reset vector pointer definition */
/* polyspace < MISRA-C3:8.3,8.5 : Not a defect : Justify with annotations > Function use the same names and type */
extern void Reset_Handler( void );
# if defined (BRS_INSTRUCTION_SET_THUMB)
/* For THUMB instruction set the call must be made to an odd address.
   As the linker label Startup_Handler points to an even address it must be incremented */
#  define RESET_ENTRY_POINT (vuint32)((vuint32)Reset_Handler + 1u)
# else
/* polyspace < MISRA-C3:11.1 : Not a defect : Justify with annotations > Function address is needed */
#  define RESET_ENTRY_POINT (vuint32)Reset_Handler
# endif /* BRS_INSTRUCTION_SET_THUMB */

/***********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

# define FBL_APPLVECT_START_SEC_CONST
     /* polyspace <MISRA-C3:20.1  : Not a defect : Justify with annotations > "Replace <STATUS> with {To investigate|To fix|Justified|No action planned|Not a defect|Other} and <SEVERITY> with {Unset|High|Medium|Low}" */
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

V_MEMROM0 V_MEMROM1 vuint32 V_MEMROM2 ApplIntJmpTable[] = {APPLVECT_FROM_APPL, RESET_ENTRY_POINT};

# define FBL_APPLVECT_STOP_SEC_CONST
/* polyspace <MISRA-C3:20.1  : Not a defect : Justify with annotations > "Replace <STATUS> with {To investigate|To fix|Justified|No action planned|Not a defect|Other} and <SEVERITY> with {Unset|High|Medium|Low}" */
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***********************************************************************************************************************
 *  END OF FILE: APPLVECT.C
 **********************************************************************************************************************/
