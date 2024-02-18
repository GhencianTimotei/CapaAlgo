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
/*! \addtogroup Dem_Prestore
 *  \{
 *  \file       Dem_Prestore_Types.h
 *  \brief      Stores and manages 'prestored freezeframes'.
 *  \details    - Stores the snapshot data for an event, in order to freeze that data set when the event qualifies 'failed' later.
 *              - Manage the prestored data in a FIFO list. The data sets are discarded once the event reports a qualified result,
 *                or the queue overflows.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_PRESTORE_TYPES_H)
#define DEM_PRESTORE_TYPES_H

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
 * \defgroup  Dem_Prestored_InvalidHandles  Macros encoding invalid index values
 * Macros encoding invalid index values
 * \{
 */
/*! Invalid index into Dem_Cfg_Prestorage array - this is the maximum *index* with a buffer at that location. */
# define DEM_PRESTORE_INVALID_BUFFER_ENTRY                                     (Dem_Cfg_GlobalPrestorageSize())
/*! Invalid index into Dem_Cfg_PrestorageIndex array, typically used for 'this event has no prestore memory configured'. */
# define DEM_PRESTORE_NOT_CONFIGURED_FOR_EVENT                                 DEM_G_GLOBAL_PRESTORED_EVENT_COUNT
/*!
 * \}
 */

/*! Handle for prestorage actions set on satellite, read on master*/

/*!
 * \defgroup  Dem_Prestored_QueueStates  Macros encoding prestorage queue states
 * Macros encoding prestorage queue state
 * \{
 */
# define DEM_PRESTORE_QUEUE_INITIAL                  ((uint8)(0x00U))  /*!< Initial state */
# define DEM_PRESTORE_QUEUE_PRESTOREFF               ((uint8)(0x01U))  /*!< Freeze Frame shall be prestored */
# define DEM_PRESTORE_QUEUE_CLEAR                    ((uint8)(0x02U))  /*!< Prestored Freeze Frame shall be cleared */

typedef uint8 Dem_Prestore_QueueActionType;

/*!
 * \}
 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/


/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#endif /* DEM_PRESTORE_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Prestore_Types.h
 *********************************************************************************************************************/
