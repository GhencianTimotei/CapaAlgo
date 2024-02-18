/* ********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 */
/*! \ingroup    Dem_ClientAccess
 *  \defgroup   Dem_DTCReporting DTCReporting
 *  \{
 *  \file       Dem_DTCReporting_Interface.h
 *  \brief      DTC Reporting Settings
 *  \details    Global Settings regarding DTC reports
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DTCREPORTING_INTERFACE_H)
#define DEM_DTCREPORTING_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DTCReporting_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_DTCReporting_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_DTCReporting_TestObdHideOccurrences
 *****************************************************************************/
/*!
 * \brief         Test flag HideOBDOccurrences 
 *
 * \details       Test flag HideOBDOccurrences if feature Obd Hide Occurence 
 *                and Dcm is enabled
 *
 * \return        TRUE
 *                Flag HideOBDOccurrences is set
 * \return        FALSE
 *                Flag HideOBDOccurrences is not set or one of the features Obd Hide  
 *                Occurence, Dcm or ObdII is disabled
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReporting_TestObdHideOccurrences(
  void
  );

/* ****************************************************************************
 * Dem_DTCReporting_SetObdHideOccurrences
 *****************************************************************************/
/*!
 * \brief         Set flag HideOBDOccurrences 
 *
 * \details       Set flag HideOBDOccurrences if feature Obd Hide Occurence 
 *                and Dcm are enabled
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReporting_SetObdHideOccurrences(
  void
  );

/* ****************************************************************************
 * Dem_DTCReporting_ResetObdHideOccurrences
 *****************************************************************************/
/*!
 * \brief         Reset flag HideOBDOccurrences 
 *
 * \details       Reset flag HideOBDOccurrences if feature Obd Hide Occurence 
 *                and Dcm are enabled
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReporting_ResetObdHideOccurrences(
  void
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DTCREPORTING_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCReporting_Interface.h
 *********************************************************************************************************************/
