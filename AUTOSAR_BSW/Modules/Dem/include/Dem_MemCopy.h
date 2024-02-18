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
/*! \addtogroup Dem_Ungrouped
 *  \{
 *  \file       Dem_MemCopy.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of MemCopy subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMCOPY_H)
#define DEM_MEMCOPY_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_Cfg_Macros.h"
#if (DEM_CFG_USE_MEMCOPY_MACROS == STD_OFF)
#include "vstdlib.h"
#endif
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

#if (DEM_CFG_USE_MEMCOPY_MACROS == STD_ON)
# if !defined(Dem_MemCpy_Macro)                                                                                                  /* COV_DEM_USER_MACROS TX */
/*! Default Macro implementation of memcopy. Can be used instead of external function call. BEWARE: 'dst' and 'src' MUST have the type 'uint8 *'. */
#  define Dem_MemCpy_Macro(dst, src, len)        { uint16_least lMemCopyIndex; \
                                                   for ( lMemCopyIndex = 0x00u; lMemCopyIndex < (len); ++lMemCopyIndex) \
                                                   { (dst)[lMemCopyIndex] = (src)[lMemCopyIndex]; \
                                                 } }
# endif

# if !defined(Dem_MemSet_Macro)                                                                                                  /* COV_DEM_USER_MACROS TX */
/*! Macro implementation of memset. Can be used instead of external function call. BEWARE: 'dst' MUST have the type 'uint8 *'. */
#  define Dem_MemSet_Macro(dst, val, len)        { uint16_least lMemCopyIndex; \
                                                   for ( lMemCopyIndex = 0x00u; lMemCopyIndex < (len); ++lMemCopyIndex) \
                                                   { (dst)[lMemCopyIndex] = (val); \
                                                 } }
# endif

/*! Wrapper macro for memcopy */
# define Dem_MemCpy(dst, src, len)               Dem_MemCpy_Macro((dst), (src), (len))
/*! Wrapper macro for memset */
# define Dem_MemSet(dst, val, len)               Dem_MemSet_Macro((dst), (val), (len))
#else
/*! Wrapper macro for memcopy */
# define Dem_MemCpy(dst, src, len)               VStdMemCpy((Dem_SharedDataPtrType)(dst), (Dem_SharedDataPtrType)(src), (len))
/*! Wrapper macro for memset */
# define Dem_MemSet(dst, val, len)               VStdMemSet((Dem_SharedDataPtrType)(dst), (val), (len))
#endif

#endif /* DEM_MEMCOPY_H */
/*!
 *  \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemCopy.h
 *********************************************************************************************************************/
