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
/*! \ingroup    Dem_Satellite
 *  \defgroup   Dem_Debounce Debounce Interface (Facade)
 *  \{
 *  \file       Dem_Debounce_Interface.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Public interface of Debounce Logical Unit
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DEBOUNCE_INTERFACE_H)
#define DEM_DEBOUNCE_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/* Includes to expose public functions belonging to Sub-(logical) units to be exposed outwards */
/* ------------------------------------------------------------------------- */
#include "Dem_DebounceCounterBased_Interface.h"
#include "Dem_DebounceTimeBased_Interface.h"
#include "Dem_DebouncingState_Interface.h"
#include "Dem_DebounceBase_Interface.h"
#include "Dem_DebounceIF_Interface.h"

#endif /* DEM_DEBOUNCE_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Debounce_Interface.h
 *********************************************************************************************************************/
