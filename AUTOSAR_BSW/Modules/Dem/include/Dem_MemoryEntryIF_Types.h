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
/*! \addtogroup Dem_MemoryEntryIF
 *  \{
 *  \file       Dem_MemoryEntryIF_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Typedefinitions of Memory EntryIF subcomponent which encapsulates the Memory entry and known data stored 
 *              in the memory entry
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMORYENTRYIF_TYPES_H)
#define DEM_MEMORYENTRYIF_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*!
 * \defgroup  Dem_MemoryEntry_Handles  Macros encoding handles for specific memory entries.
 * \{
 */
#define DEM_MEMORYENTRY_HANDLE_PRIMARY          0U                                                              /*!< Value for the first primary memory entry handle */
#define DEM_MEMORYENTRY_HANDLE_SECONDARY        DEM_CFG_GLOBAL_PRIMARY_SIZE                                     /*!< Value for the first secondary memory entry handle */
#if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
#define DEM_MEMORYENTRY_HANDLE_READOUTBUFFER    DEM_CFG_GLOBAL_PRIMARY_SIZE + DEM_CFG_GLOBAL_SECONDARY_SIZE     /*!< Value for the first readout buffer memory entry handle */
#else
#define DEM_MEMORYENTRY_HANDLE_READOUTBUFFER    DEM_CFG_GLOBAL_PRIMARY_SIZE                                     /*!< Value for the first readout buffer memory entry handle */
#endif
#define DEM_MEMORYENTRY_HANDLE_INVALID          (DEM_MEMORYENTRY_HANDLE_READOUTBUFFER \
                                                 + (DEM_CFG_NUMBER_OF_READOUTBUFFERS \
                                                   * DEM_CFG_NUMBER_OF_SUBEVENT_DATA_READOUTBUFFERS))           /*!< Value for an invalid memory entry handle */

/*!
 * \}
 */

/*!
 * \defgroup  Dem_MemoryEntry_StandardEnvironmentalDataBytes  Macros encoding the bytes of the standard environmental data.
 * \{
 */
#define DEM_MEMORYENTRY_STDENVDATA_STATUS              0x00U  /*!< Status */
#define DEM_MEMORYENTRY_STDENVDATA_FIRSTODOMETER       0x01U  /*!< Original Odometer */
#define DEM_MEMORYENTRY_STDENVDATA_CURRENTODOMETER     0x03U  /*!< Most Recent Odometer */
#define DEM_MEMORYENTRY_STDENVDATA_TIME                0x05U  /*!< Operating Time */
#define DEM_MEMORYENTRY_STDENVDATA_TIMESTATUS          0x09U  /*!< Operating Time Status */
/*!
 * \}
 */

#define DEM_MEMORYENTRY_STD_ENV_DATA_SIZE       5U     /* Size of Standard Environmental data stored in a memory entry*/
#define DEM_MEMORYENTRY_EXT_ENV_DATA_SIZE       10U    /* Size of Extended Environmental data stored in a memory entry*/

#if (DEM_CFG_DATA_EXTENDED_ENV_DATA == STD_ON)                                                                               /* PRQA S 0883 */ /* MD_DEM_19.15 */
# define DEM_MEMORYENTRY_ENV_DATA_SIZE          DEM_MEMORYENTRY_EXT_ENV_DATA_SIZE
#elif (DEM_CFG_DATA_STANDARD_ENV_DATA == STD_ON)
# define DEM_MEMORYENTRY_ENV_DATA_SIZE          DEM_MEMORYENTRY_STD_ENV_DATA_SIZE
#endif

/*! Aging timer invalid (stopped) value */
#define DEM_MEMORYENTRY_AGINGTIME_INVALID              0x00000000UL

/*! Preconfirmed DTC status after re-initialization */
#define DEM_MEMORYENTRY_PC_STATUS_INITIALIZE           0x00U

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if (DEM_CFG_DATA_OCCCTR_2BYTE == STD_ON)
/*! Type for 2 byte DTC occurrence counter */
typedef uint16 Dem_MemoryEntry_OccurrenceCounterType;
#else
/*! Type for 1 byte DTC occurrence counter */
typedef uint8 Dem_MemoryEntry_OccurrenceCounterType;
#endif

#endif /* DEM_MEMORYENTRYIF_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemoryEntryIF_Types.h
 *********************************************************************************************************************/
