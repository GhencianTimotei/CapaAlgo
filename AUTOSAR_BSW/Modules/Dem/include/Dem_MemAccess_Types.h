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
/*! \addtogroup Dem_MemAccess
 *  \{
 *  \file       Dem_MemAccess_Types.h
 *  \brief      Basic routines for event memories.
 *  \details    In general, returns a memory entry or allows queries concerning the whole event memory
 *              - find free memory entries including displacement and aging
 *              - allocate memory entries
 *              - free event memory entries and trigger removal of event related data (OBD freeze frame, time series & permanent entries).
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMACCESS_TYPES_H)
#define DEM_MEMACCESS_TYPES_H

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

/*! Displacement info data type for selecting the "best" element for displacement */
struct Dem_MemAccess_DisplacementInfoType_s
  {
    uint16                   EventId;                 /*!< EventId of current element */
    Dem_Cfg_MemoryIndexType  MemoryIndex;             /*!< Memory index of current element; DEM_MEM_INVALID_MEMORY_INDEX marks invalid structure */
#if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON) || (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)
    Dem_Cfg_MemoryIndexType  MemoryIndexAging;        /*!< Memory index of current element for considering aging */
#endif
#if (DEM_CFG_DISPLACEMENT_FALLBACK_OLDEST == STD_ON)
    Dem_Cfg_MemoryIndexType  OldestDisplaceableIndex; /*!< Memory index of oldest event can be always displaced - used as fallback */
#endif
    uint8                    UdsStatus;               /*!< DTC/Event status considered for displacement */
};

/*! Displacement info data type for selecting the "best" element for displacement */
typedef struct Dem_MemAccess_DisplacementInfoType_s Dem_MemAccess_DisplacementInfoType;


/*! Result of a displacement check */
typedef enum
{
  Dem_MemAccess_Displace_NeedMoreTests,   /*!< Candidate is not classified yet, apply further tests on this candidate */
  Dem_MemAccess_Displace_RatingDone,      /*!< Candidate is classified, continue the scan with next candidate */
  Dem_MemAccess_Displace_FoundBestMatch   /*!< Candidate is the best match, abort scanning for better matches */
} Dem_MemAccess_Displace_CheckResultType;



#endif /* DEM_MEMACCESS_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemAccess_Types.h
 *********************************************************************************************************************/
