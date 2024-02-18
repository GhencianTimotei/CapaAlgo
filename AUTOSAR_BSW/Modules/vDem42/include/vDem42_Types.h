/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  vDem42_Types.h
 *        \brief  vDem42 type definitions
 *
 *      \details  vDem42 definitions of structs and enumerations and simple types.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Yves Grau                     visygr        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  refer to vDem42.h
 *********************************************************************************************************************/

#if !defined (VDEM42_TYPES_H)
# define VDEM42_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Rte_VDem42_Type.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint8 VDem42_ReturnClearDTCType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/*! DTC selection for the ClearDTC operation */
typedef struct
{
  uint32 lastSelected_DTC;                         /*!< The DTC that was last selected by ClearDTC */
  VDem42_DTCFormatType lastSelected_DTCFormat;     /*!< The DTC format of the DTC that was last selected by ClearDTC */
  VDem42_DTCOriginType lastSelected_DTCOrigin;     /*!< The DTC origin of the DTC that was last selected by ClearDTC */
  boolean isDTCSelected;                           /*!< Flag to store whether a DTC is currently selected or not */
} VDem42_ClearDTC_SelectionState;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/* ----------------------------------------------
 ~&&&   Versions
---------------------------------------------- */

/*! Implementation version */
# define VDEM42_TYPES_MAJOR_VERSION                                  1u
# define VDEM42_TYPES_MINOR_VERSION                                  2u
# define VDEM42_TYPES_PATCH_VERSION                                  0u

#endif /* VDEM42_H */
/**********************************************************************************************************************
 *  END OF FILE: vDem42_Types.h
 *********************************************************************************************************************/