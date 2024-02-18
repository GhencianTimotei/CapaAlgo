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
 *  \defgroup   Dem_Client Dem Client
 *  \{
 *  \file       Dem_Client_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public Interface of Client Logical Unit
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_CLIENT_INTERFACE_H)
#define DEM_CLIENT_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/

/* Includes to expose public functions belonging to Sub-(logical) units to be exposed outwards */
/* ------------------------------------------------------------------------- */
#include "Dem_Data_Interface.h"
#include "Dem_ClientAccess_Interface.h"
#include "Dem_FilterData_Interface.h"
#include "Dem_FreezeFrameIterator_Interface.h"
#include "Dem_DTCSelector_Interface.h"
#include "Dem_DTCReporting_Interface.h"
#include "Dem_ClearTask_Interface.h"
#include "Dem_ClearDTC_Interface.h"

#endif /* DEM_CLIENT_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Client_Interface.h
 *********************************************************************************************************************/
