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
 *  \defgroup   Dem_Infrastructure Dem Infrastructure
 *  \{
 *  \file       Dem_Infrastructure_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public Interface of Infrastructure Logical Unit
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_INFRASTRUCTURE_INTERFACE_H)
#define DEM_INFRASTRUCTURE_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/* Includes to expose public functions belonging to Sub-(logical) units to be exposed outwards */
/* ------------------------------------------------------------------------- */
#include "Dem_ExtCom_Interface.h"
#include "Dem_EventQueue_Interface.h"
#include "Dem_Com_Interface.h"
#include "Dem_InitState_Interface.h"
#include "Dem_Error_Interface.h"
#include "Dem_Scheduler_Interface.h"
#include "Dem_Nvm_Interface.h"
#include "Dem_ConfigValidation_Interface.h"
#include "Dem_APIChecks_Interface.h"

#endif /* DEM_INFRASTRUCTURE_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Infrastructure_Interface.h
 *********************************************************************************************************************/
