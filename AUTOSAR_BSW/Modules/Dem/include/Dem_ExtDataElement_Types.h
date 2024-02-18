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
/*! \addtogroup Dem_ExtDataElement
 *  \{
 *  \file       Dem_ExtDataElement_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_EXTDATAELEMENT_TYPES_H)
#define DEM_EXTDATAELEMENT_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_RecordReader_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*! Data byte value substituted when callbacks fail to retrieve data */
#define DEM_EXTDATAELEMENT_INVALID_DATA_PATTERN            (0xffU)
#define DEM_EXTDATAELEMENT_INVALID_DATA_SIGNED             (-1)
#define DEM_EXTDATAELEMENT_INVALID_DATA_1Byte              (0xffU)
#define DEM_EXTDATAELEMENT_INVALID_DATA_2Byte              (0xffffU)
#define DEM_EXTDATAELEMENT_INVALID_DATA_4Byte              (0xffffffffU)
/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef Dem_DataReport_DidCopyInfoBaseType    Dem_ExtDataElement_CollectDidInfoType;
typedef Dem_DataReport_DidCopyInfoBasePtrType Dem_ExtDataElement_CollectDidInfoPtrType;

#endif /* DEM_EXTDATAELEMENT_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ExtDataElement_Types.h
 *********************************************************************************************************************/
