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
/*! \addtogroup Dem_ConfigValidation
 *  \{
 *  \file       Dem_ConfigValidation_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of validations for configurations requiring a configuration pointer
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_CONFIGVALIDATION_TYPES_H)
#define DEM_CONFIGVALIDATION_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*!
 * \defgroup  Dem_ConfigPtr_InitState Macros encoding Initialization state of config pointer
 * Macros encoding Initialization state of config pointer
 * \{
 */
#define DEM_CONFIGVALIDATION_CONFIGPTR_UNINITIALIZED             (0x01U)  /*!< GlobalConfigPointer not initialized */
#define DEM_CONFIGVALIDATION_CONFIGPTR_ERROR                     (0x02U)  /*!< Global Config Pointer Initialization through Dem_SafePreInit() OR Dem_SafeInit() failed */
#define DEM_CONFIGVALIDATION_CONFIGPTR_PREINITIALIZED            (0x03U)  /*!< Preliminary GlobalConfigPointer initialized during PreInitialization phase */
#define DEM_CONFIGVALIDATION_CONFIGPTR_INITIALIZED               (0x04U)  /*!< Final GlobalConfigPointer initialized during Initialization phase*/

/*!
 * \}
 */

 /* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


#endif /* DEM_CONFIGVALIDATION_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ConfigValidation_Types.h
 *********************************************************************************************************************/
