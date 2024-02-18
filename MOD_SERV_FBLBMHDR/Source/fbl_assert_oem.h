/***********************************************************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief        OEM specific assertion defines
 *
 *  --------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  06.00.00   2019-03-05  visach  ESCAN00102277    Support Q-LAH 80126 2.7 and FblDiag_14229_Core 4.x
 *                                 ESCAN00102363    No changes
 *                                 ESCAN00102367    No changes
 *  06.00.01   2019-04-17  vistbe  ESCAN00102722    No changes
 *  06.00.02   2019-09-24  visrcn  ESCAN00103825    No changes
 *                                 ESCAN00103818    No changes
 *                                 ESCAN00103751    No changes
 *                                 ESCAN00103642    No changes
 *                                 ESCAN00104149    No changes
 *  06.00.03   2020-02-10  vistbe  ESCAN00104798    No changes
 *                                 ESCAN00105205    No changes
 *                                 ESCAN00105312    No changes
 *  07.00.00   2020-04-27  visrie  FBL-1412         No changes
 *  07.00.01   2020-05-06  visrie  ESCAN00106319    No changes
 *  07.01.00   2020-05-07  visrie  FBL-1414         No changes
 *  07.01.01   2020-05-20  visrie  ESCAN00106406    No changes
 *  07.02.00   2020-06-12  vistmo  ESCAN00106370    No changes
 *                                 ESCAN00106371    No changes
 *                                 ESCAN00106542    No changes
 *                                 FBL-1970         No changes
 *  07.02.01   2020-07-13  visjdn  ESCAN00106501    No changes
 *  07.03.00   2020-08-06  visrie  FBL-2024         No changes
 *  07.03.01   2020-09-09  visrcn  ESCAN00106681    No changes
 *  07.03.02   2020-10-15  visrcn  ESCAN00107409    No changes
 *  07.03.03   2021-01-05  visjdn  ESCAN00107532    No changes
 *  07.03.04   2021-02-05  vishor  ESCAN00108471    No changes
 *  07.03.05   2021-03-04  visrie  ESCAN00107826    No changes
 *                                 ESCAN00108176    No changes
 *                                 FBL-2929         No changes
 **********************************************************************************************************************/

#ifndef FBL_ASSERT_OEM_H
#define FBL_ASSERT_OEM_H

/***********************************************************************************************************************
 *  DEFINITION OF ASSERTION CODES (OEM)
 **********************************************************************************************************************/

/* 0x80-0xFF: OEM specific */
/* Diagnostic module errors */
/* polyspace:begin < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define kFblOemAssertMainHandlerIdxInvalid   0x80u
#define kFblOemAssertWrongServiceHandler     0x81u
#define kFblOemAssertInvalidError            0x82u
#define kFblOemAssertNoNrcSet                0x83u
#define kFblOemAssertParameterOutOfRange     0xA0u
#define kFblOemAssertTooManyPseudoFlashDrv   0xA1u
#define kFblOemAssertInvalidPfdSize          0xA2u
#define kFblOemAssertRxBufferLinkage         0xA3u
/* polyspace:end < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */

/***********************************************************************************************************************
 *  END OF FILE: FBL_ASSERT_OEM.H
 **********************************************************************************************************************/

#endif /* FBL_ASSERT_OEM_H */
