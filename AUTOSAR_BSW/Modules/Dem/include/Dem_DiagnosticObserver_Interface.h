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
/*! \ingroup    Dem
 *  \defgroup   Dem_DiagnosticObserver Dem DiagnosticObserver
 *  \{
 *  \file       Dem_DiagnosticObserver_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public Interface of Diagnostic Observer Logical Unit
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DIAGNOSTICOBSERVER_INTERFACE_H)
#define DEM_DIAGNOSTICOBSERVER_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/* Includes to expose public functions belonging to Sub-(logical) units to be exposed outwards */
/* ------------------------------------------------------------------------- */
#include "Dem_Notifications_Interface.h"
#include "Dem_Iumpr_Interface.h"
#include "Dem_Indicator_Interface.h"
#include "Dem_Dtr_Interface.h"
#include "Dem_Notifications_Interface.h"


/* ********************************************************************************************************************
 *  LOGICAL UNIT PUBLIC FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_DiagnosticObserver_Public Public Methods
 * \{
 */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DIAGNOSTICOBSERVER_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DiagnosticObserver_Interface.h
 *********************************************************************************************************************/
