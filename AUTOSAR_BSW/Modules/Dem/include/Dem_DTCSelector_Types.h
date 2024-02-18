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
/*! \addtogroup Dem_DTCSelector
 *  \{
 *  \file       Dem_DTCSelector_Types.h
 *  \brief      Diagnostic Event Manager (Dem) Type and Macro definition file
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DTCSELECTOR_TYPES_H)
#define DEM_DTCSELECTOR_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! This used for DTCSelector handles. */
typedef uint8 Dem_DTCSelector_HandleType;


/*!
 * \defgroup  Dem_DTCSelector_ResultType Dem_DTCSelector_ResultType
 * \{
 */
/*! This type is used to encode the result of a DTC selection */
typedef uint8 Dem_DTCSelector_ResultType;
#define DEM_DTCSELECTOR_SELECTION_INIT           0u  /*!< Initialization value */
#define DEM_DTCSELECTOR_SELECTION_DTC            1u  /*!< A DTC was selected */
#define DEM_DTCSELECTOR_SELECTION_GROUP          2u  /*!< A DTC group was selected */
#define DEM_DTCSELECTOR_SELECTION_ALL_DTCS       3u  /*!< All DTCs were selected */
#define DEM_DTCSELECTOR_SELECTION_NO_MATCH       4u  /*!< Selected number does not map to a DTC or DTC group */
#define DEM_DTCSELECTOR_SELECTION_WRONG_ORIGIN   5u  /*!< DTC Origin not supported*/
/*!
 * \}
 */


/*!
 * \defgroup  Dem_DTCSelector_GroupIdType Dem_DTCSelector_GroupIdType
 * \{
 */
/*! This type is used to encode the selected DTC group */
typedef uint8 Dem_DTCSelector_GroupIdType;
#define DEM_DTCSELECTOR_GROUP_INVALID            0u  /*!< No group */
#define DEM_DTCSELECTOR_GROUP_ALL_DTCS           1u  /*!< UDS group All DTCs */
#define DEM_DTCSELECTOR_GROUP_EMISSION_RELATED   2u  /*!< OBD group All DTCs */
#define DEM_DTCSELECTOR_GROUP_WWH_OBD_ALL_DTC    3u  /*!< WWH-OBD group All DTCs */
/*!
 * \}
 */


/*! storage for selection data */
union Dem_DTCSelector_Selection_u
{                                                                                                                                /* PRQA S 0750 */ /* MD_MSR_Union */
  Dem_EventIdType              EventId;          /*!< Selected EventId */
  Dem_DTCSelector_GroupIdType  GroupId;          /*!< Selected GroupId */
  uint8                        GroupMask;        /*!< Selected GroupMask */
};
/*! type for selection data */
typedef union Dem_DTCSelector_Selection_u Dem_DTCSelector_SelectionType;

/*! storage for the original selection request */
struct Dem_DTCSelector_RequestType_s
{
  uint32 DTC;                                    /*!< Selected DTC value */
  Dem_DTCFormatType DTCFormat;                   /*!< Selected DTC format */
  Dem_DTCOriginType DTCOrigin;                   /*!< Selected DTC origin */
};
/*! type for original selection request*/
typedef struct Dem_DTCSelector_RequestType_s Dem_DTCSelector_RequestType;

/*! storage for DTC selector data */
struct Dem_DTCSelector_DataType_s
{
  Dem_DTCSelector_RequestType    Request;        /*!< Selection Request */
  Dem_DTCSelector_SelectionType  Selection;      /*!< Selection data */
  uint8                          MemoryId;       /*!< MemoryId the event or group belongs to */
  Dem_DTCSelector_ResultType     SelectorState;  /*!< DTC Selection Result */
  uint8                          ActiveAsyncOps; /*!< Number of currently active asynchronous operation that require a Dem_SelectDTC() */
};
/*! type for storage of a DTC selector */
typedef struct Dem_DTCSelector_DataType_s Dem_DTCSelector_DataType;

/*! pointer type for storage of a DTC selector */
typedef P2VAR(Dem_DTCSelector_DataType, TYPEDEF, DEM_VAR_NOINIT) Dem_DTCSelector_DataPtrType;

#endif /* DEM_DTCSELECTOR_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCSelector_Types.h
 *********************************************************************************************************************/
