/***********************************************************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief        System specific assertion defines
 *
 *  --------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.
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
 *  Daniel Moessner               DlM           Vector Informatik GmbH
 *  Torben Stoessel               TnS           Vector Informatik GmbH
 *  Christian Baeuerle            CB            Vector Informatik GmbH
 *  Joern Herwig                  JHg           Vector Informatik GmbH
 *  Marco Riedl                   Rie           Vector Informatik GmbH
 *  Daniel Koebel                 DKl           Vector Informatik GmbH
 *  Dan Jiga                      JDn           Vector Informatik GmbH
 *  Thomas Bezold                 TBe           Vector Informatik GmbH
 *  Matteo Trovo                  TMo           Vector Informatik GmbH
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  04.00.00   2016-02-26  Ach     ESCAN00088307    Rework to support FblMain 3.xx
 *                                 ESCAN00088433    Moved assertion specific code to fbl_assert.h
 *  04.00.01   2016-07-15  DlM     ESCAN00091011    No changes
 *  04.01.00   2016-08-18  TnS     ESCAN00091531    No changes
 *  04.02.00   2016-10-31  CB      ESCAN00092597    No changes
 *  04.02.01   2017-05-09  JHg     ESCAN00095090    No changes
 *                         Rie     ESCAN00095204    Added assertion defines for DET
 *  04.03.00   2017-07-28  CB      ESCAN00095458    No changes
 *                         Ach     ESCAN00096096    No changes
 *  04.04.00   2018-02-26  DKl     ESCAN00098503    No changes
 *  04.04.01   2018-07-06  DKl     ESCAN00099860    No changes
 *  04.04.01   2018-07-06  DKl     ESCAN00099860    No changes
 *  04.05.00   2018-09-13  Rie     ESCAN00100731    No changes
 *             2018-11-20  DKl     ESCAN00101393    No changes
 *  04.06.00   2019-12-03  JDn     FBL-999          No changes
 *  05.00.00   2020-03-02  TBe     FBL-949          No changes
 *                                 ESCAN00105231    No changes
 *  05.01.00   2020-04-29  TMo     FBL-1584         No changes
 *  05.02.00   2020-05-08  Rie     FBL-1414         No changes
 *  05.03.00   2020-07-16  Rie     FBL-2021         No changes
 **********************************************************************************************************************/

#ifndef FBL_ASSERT_H
#define FBL_ASSERT_H

/***********************************************************************************************************************
 *  DEFINITION OF ASSERTION CODES (SYSTEM)
 **********************************************************************************************************************/

#if defined( FBL_ENABLE_ASSERTION )
/* Note: System assertions are only allowed in the range from 0x00-0x7F. Others are reserved. */

/* 0x00-0x1F: General FBL assertions */
/* polyspace:begin < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define kFblSysAssertMissingForcedRCRRP               0x00u

#define kFblSysAssertInitializationFailed             0x10u

/* 0x20-0x3F: Internal assertions */
#define kFblSysAssertServiceReqBeforeResp             0x20u
#define kFblSysAssertServiceMainHandlerInvalid        0x21u

#define kFblSysAssertDet                              0x22u

/* 0x40-0x4F: Generated data assertions */
#define kFblSysAssertWdBufferOverflow                 0x40u

/* 0x50-0x6F: User parameter assertions */
#define kFblSysAssertParameterOutOfRange              0x50u

#define kFblSysAssertRepeatedCallOnConcludedService   0x60u

/* 0x70-0x7F: Communication wrapper assertions */
#define kFblSysAssertStateNotIdle                     0x70u
#define kFblSysAssertNoBufferAvailable                0x71u
/* polyspace:end < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
/* 0x80-0xFF: OEM specific */
#include "fbl_assert_oem.h"

# if defined( __LINE__ ) && defined( __FILE__ ) && defined( FBL_ENABLE_ASSERTION_EXTENDED_INFO )
#  define FBL_DECL_ASSERT_EXTENDED_INFO(n)       const vuint8* module, vuint16 line, n
#  define FBL_USED_ASSERT_EXTENDED_INFO(n)       __FILE__, __LINE__,(n)
# else
/* polyspace < MISRA-C3:D4.9,2.5 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */
#  define FBL_DECL_ASSERT_EXTENDED_INFO(n)        n   /* PRQA S 3410 */ /* MD_FblAssert_3410 */
/* polyspace < MISRA-C3:D4.9,2.5 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */
#  define FBL_USED_ASSERT_EXTENDED_INFO(n)       (n)  /* PRQA S 3453 */ /* MD_MSR_19.7 */
# endif
/* No statement should be added to below if clauses, in order to prevent errors suggested by Misra rule 14.9 */
/* PRQA S 3412 4 */ /* MD_FblAssert_Assertion */
/* polyspace:begin < MISRA-C3:D4.9,2.5 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */
# define assertFbl(p, e)         if (!(p)) ApplFblFatalError(FBL_USED_ASSERT_EXTENDED_INFO(e)) /* PRQA S 2214 */ /* MD_FblAssert_Assertion */
# define assertFblUser(p, e)     if (!(p)) ApplFblFatalError(FBL_USED_ASSERT_EXTENDED_INFO(e)) /* PRQA S 2214 */ /* MD_FblAssert_Assertion */
# define assertFblGen(p, e)      if (!(p)) ApplFblFatalError(FBL_USED_ASSERT_EXTENDED_INFO(e)) /* PRQA S 2214 */ /* MD_FblAssert_Assertion */
# define assertFblInternal(p, e) if (!(p)) ApplFblFatalError(FBL_USED_ASSERT_EXTENDED_INFO(e)) /* PRQA S 2214 */ /* MD_FblAssert_Assertion */
/* polyspace:end < MISRA-C3:D4.9,2.5 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */
#else
# define assertFbl(p, e)
# define assertFblUser(p, e)
# define assertFblGen(p, e)
# define assertFblInternal(p, e)
#endif /* FBL_ENABLE_ASSERTION */

/* Module specific MISRA deviations:

   MD_FblAssert_Assertion:
      Reason:     This is an assertion macro used only for debugging in development (FBL_ENABLE_ASSERTION). There should
                  be no need to extend the amount of statements, so the current usage is accepted.
      Risk:       Unintended debugging code behavior could result, through adding further statements,
      Prevention: A comment is in place to avoid that further statements are added to the if condition.

   MD_FblAssert_3410:
      Reason:     This macro serves as function parameter type qualifier and cannot have parentheses, because this would
                  result in an invalid function parameter list.
      Risk:       Usage at not intended places and unintended code behavior due to the missing parentheses.
      Prevention: Reviews must ensure that this macro is only used in function parameter lists.
*/

#endif /* FBL_ASSERT_H */

/***********************************************************************************************************************
 *  END OF FILE: FBL_ASSERT.H
 **********************************************************************************************************************/
