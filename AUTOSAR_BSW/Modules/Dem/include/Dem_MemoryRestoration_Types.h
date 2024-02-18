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
/*! \addtogroup Dem_MemoryRestoration
 *  \{
 *  \file       Dem_MemoryRestoration_Types.h
 *  \brief      Type definitions of Memory Restoration subcomponent which restores the status of a memory entry, 
 *              fixes memory entry allocation errors etc.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMORYRESTORATION_TYPES_H)
#define DEM_MEMORYRESTORATION_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Structure to store a pointer to a data record and a current read position.
 * \details  This type is currently identical to Dem_DataReport_DidSourceBufferReadInfoType_s but has been 
 *           duplicated in order to reduce dependencies between subcomponents. 
 */
struct Dem_MemoryRestoration_IndexedDataRecordBufferInfoType_s
{
  Dem_ConstSharedDataPtrType                 SourceBuffer; /*!< source buffer providing the data record */
  uint16                                     ReadIndex;    /*!< Current read index from the source buffer */
};


/*! Type for data record read */
typedef struct Dem_MemoryRestoration_IndexedDataRecordBufferInfoType_s Dem_MemoryRestoration_IndexedDataRecordBufferInfoType;
/*! Pointer to type for data record read */
typedef P2VAR(Dem_MemoryRestoration_IndexedDataRecordBufferInfoType, TYPEDEF, AUTOMATIC)
  Dem_MemoryRestoration_IndexedDataRecordBufferInfoPtrType;
/*! Non-writable pointer to type data record read */
typedef P2CONST(Dem_MemoryRestoration_IndexedDataRecordBufferInfoType, TYPEDEF, AUTOMATIC)
  Dem_MemoryRestoration_ConstIndexedDataRecordBufferInfoPtrType;


  /* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

#endif /* DEM_MEMORYRESTORATION_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemoryRestoration_Types.h
 *********************************************************************************************************************/
