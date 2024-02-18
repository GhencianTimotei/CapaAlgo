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
 *  02.02.00   2016-04-26  CB      ESCAN00089744    No changes
 *  02.03.00   2016-06-16  Rie     ESCAN00090350    Minor changes
 *  02.04.00   2017-07-04  Dod     ESCAN00095748    No changes
 *                         Ach     ESCAN00096160    No changes
 *  02.04.01   2019-03-22  TBe     ESCAN00102585    No changes
 **********************************************************************************************************************/

#ifndef APPL_VECT_H
#define APPL_VECT_H

/***********************************************************************************************************************
 *  VERSION
 **********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : FblVtabAppl_Mpc5500 CQComponent : Implementation */
#define FBLVTABAPPL_MPC5500_VERSION             0x0204u
#define FBLVTABAPPL_MPC5500_RELEASE_VERSION     0x01u

/***********************************************************************************************************************
 *  DEFINES
 **********************************************************************************************************************/
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define APPLVECT_FROM_BOOT       0xA5000000UL                             /* Reserved for Bootloader internal value   */
                                                                          /* Set this magic code just for the table   */
                                                                          /* linked with the bootloade, but not       */
                                                                          /* for the application vector table,  r     */

#define APPLVECT_FROM_APPL       0xAA000000UL                             /* Set this label for the user              */
                                                                          /* Application vector table only            */

/***********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

# define FBL_APPLVECT_START_SEC_CONST
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
/* polyspace <MISRA-C3:8.11 : Not a defect : Justify with annotations > The size of array it is not known, should be modified */
V_MEMROM0 extern V_MEMROM1 vuint32 V_MEMROM2 ApplIntJmpTable[];

# define FBL_APPLVECT_STOP_SEC_CONST
/* polyspace <MISRA-C3:20.1  : Not a defect : Justify with annotations >  "Replace <STATUS> with {To investigate|To fix|Justified|No action planned|Not a defect|Other} and <SEVERITY> with {Unset|High|Medium|Low}" */
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* APPL_VECT_H */

/***********************************************************************************************************************
 *  END OF FILE: APPLVECT.H
 **********************************************************************************************************************/
