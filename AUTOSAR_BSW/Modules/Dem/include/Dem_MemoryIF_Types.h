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
/*! \addtogroup Dem_MemoryIF
 *  \{
 *  \file       Dem_MemoryIF_Types.h
 *  \brief      Abstraction for multiple event memories.
 *  \details    Typedefinitions of MemoryIF subcomponent which is facade for all memory related tasks.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMORYIF_TYPES_H)
#define DEM_MEMORYIF_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_TimeSeries_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Invalid memory index used for 'no index available' */
#define DEM_MEM_INVALID_MEMORY_INDEX             Dem_Cfg_GlobalNvBlockCount()

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
struct Dem_Memory_AllocMemEntriesIterType_s
{
  Dem_Cfg_MemoryIndexIterType mIdx;    /*!< Current iterator position */
  Dem_Cfg_MemoryIndexIterType mEndIdx; /*!< Iterator end position */
  Dem_MemState_MemoryInfoPtrType mMemoryInfoPtr; /*!< Pointer to Event Memory management data */
};

/*! Iterator for iterations over all event memory entries in chronological order*/
typedef struct Dem_Memory_AllocMemEntriesIterType_s Dem_Memory_AllocMemEntriesIterType;

struct Dem_Memory_ComplexIterType_s
{
  Dem_Cfg_MemoryIndexIterType mIdx;    /*!< Current iterator position */
  Dem_Cfg_MemoryIndexIterType mEndIdx; /*!< Iterator end position */
};

/*! Type for iterations over all event memory entries (Primary and User Defined) */
typedef struct Dem_Memory_ComplexIterType_s Dem_Memory_AllEventMemEntriesIterType;
/*! Type for iterations over memory entries of one memory*/
typedef struct Dem_Memory_ComplexIterType_s Dem_Memory_MemEntryIterType;


#endif /* DEM_MEMORYIF_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemoryIF_Types.h
 *********************************************************************************************************************/
