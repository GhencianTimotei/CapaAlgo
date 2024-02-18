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
/*! \addtogroup Dem_MemState
 *  \{
 *  \file       Dem_MemState_Types.h
 *  \brief      Encapsulate global data stored for an event memory.
 *  \details    File contains type definitions for MemState subcomponent which encapsulate global data stored for an 
 *              event memory. This includes handling chronology for event entries, tracking occupancy, overflow status,
 *              update state etc.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMSTATE_TYPES_H)
#define DEM_MEMSTATE_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
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

/*! Pointer to a chronology list */
typedef CONSTP2VAR(Dem_Cfg_MemoryIndexType, TYPEDEF, DEM_VAR_NOINIT) Dem_MemState_ChronoStackPtrType;
/*! Pointer to memory size variable */
typedef CONSTP2VAR(uint8, TYPEDEF, DEM_VAR_NOINIT) Dem_MemState_CurrentSizePtrType;

/*! memory function pointer for functions which tests if event entry stores the input event */
typedef P2FUNC(boolean, DEM_CODE, Dem_Memory_MemoryState_TestEntryForEventFctPtrType)(
  uint16 Index,            /* Index used to access an entry for the specified memory type*/
  Dem_EventIdType EventId  /* Event Id to test */
  );

  /*! memory function pointer for functions which frees the input memory entr */
typedef P2FUNC(void, DEM_CODE, Dem_Memory_MemoryState_FreeEntryFctPtrType)(
  uint16 Index            /* Index used to access an entry for the specified memory type*/
  );

/*! Event Memory management data */
struct Dem_MemState_MemoryInfoType_s
{
  Dem_MemState_ChronoStackPtrType                      ChronoPtr;  /*!< Pointer to the chronology list of the memory if available and null pointer otherwise */
  Dem_MemState_CurrentSizePtrType                      SizePtr;  /*!< Pointer to the current size variable */
  Dem_Cfg_MemoryIndexType                              FirstMemoryIndex;  /*!< First memory block index belonging to the memory */
  Dem_EventIdType                                      FirstEvent;  /*!< First event id belonging to the memory */
  Dem_EventIdType                                      LastEvent;  /*!< Last event Id belonging to the memory */
  uint8                                                MaxSize;  /*!< Maximum number of memory entries or slots for the memory */
  uint8                                                MemoryId;  /*!< Handle to identify the event memory */
  Dem_Memory_MemoryState_TestEntryForEventFctPtrType   TestEntryForEventFctPtr;   /*!< Pointer to a function which tests if event entry stores the input event */
  Dem_Memory_MemoryState_FreeEntryFctPtrType           FreeEntryFctPtr;   /*!< Pointer to a function which frees the input memory entry */
};

/*! Event Memory management data type */
typedef struct Dem_MemState_MemoryInfoType_s                      Dem_MemState_MemoryInfoType;
/*! Pointer to Event Memory management data */
typedef P2CONST(Dem_MemState_MemoryInfoType, TYPEDEF, DEM_CONST)  Dem_MemState_MemoryInfoPtrType;

#endif /* DEM_MEMSTATE_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemState_Types.h
 *********************************************************************************************************************/
