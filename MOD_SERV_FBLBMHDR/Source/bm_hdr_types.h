/***********************************************************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief         BM Header module
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
 *  Marco Riedl                   Rie           Vector Informatik GmbH
 *  Marcel Viole                  MVi           Vector Informatik GmbH
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  01.00.00   2019-31-01  Rie     -                Initial release
 *  01.01.00   2019-02-18  MVi     -                No changes
 *                         Rie     ESCAN00102184    No changes
 *  01.02.00   2019-07-22  Rie     ESCAN00103790    Support invalid entry address configuration
 *                                 ESCAN00103791    No changes
 *                                 ESCAN00103803    No changes
 *  02.00.00   2019-12-03  Rie     FBL-456          No changes
 *  02.00.01   2020-01-15  Rie     ESCAN00105368    No changes
 **********************************************************************************************************************/

#ifndef BM_HDR_TYPES_H
#define BM_HDR_TYPES_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/

#include "FblBmHdr_Cfg.h"

/***********************************************************************************************************************
 *  TYPEDEFS
 **********************************************************************************************************************/
/* polyspace:begin < MISRA-C3:2.3 : Not a defect : Justify with annotations > struct should be kept for future usage */
typedef enum
{
   FBLBMHDR_CHKHDR_OK,
   FBLBMHDR_CHKHDR_BLOCK_INVALID,
   FBLBMHDR_CHKHDR_READ_FAIL,
   FBLBMHDR_CHKHDR_HEADER_INCONSISTENT,
   FBLBMHDR_CHKHDR_WRONG_TARGET,
   FBLBMHDR_CHKHDR_GET_MAC_FAIL,
   FBLBMHDR_CHKHDR_VERIFICATION_FAIL,
   FBLBMHDR_CHKHDR_NOT_FOUND
}tFblBmHdrCheckBmHeaderResult;
/* polyspace:end < MISRA-C3:2.3 : Not a defect : Justify with annotations > Should be kept for future usage */
#endif /* BM_HDR_TYPES_H */

/***********************************************************************************************************************
 *  END OF FILE: BM_HDR_TYPES.H
 **********************************************************************************************************************/
