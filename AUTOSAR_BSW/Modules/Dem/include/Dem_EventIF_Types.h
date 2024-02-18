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
/*! \addtogroup Dem_EventIF
 *  \{
 *  \file       Dem_EventIF_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Typedefinitions of EventIF subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_EVENTIF_TYPES_H)
#define DEM_EVENTIF_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_UDSStatus_Types.h"
#include "Dem_Cfg_Types.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
 /*! Set flag in which indicate an ongoing commit */
#define DEM_EVENT_DATA_COMMIT_STARTED                   (0x80U) 
 /*! Reset flag which indicate an ongoing commit */
#define DEM_EVENT_DATA_COMMIT_FINISHED                  (0x7FU)
 /*! Initial transaction number of NV transaction state  */
#define DEM_EVENT_INIT_DATA_COMMIT_NUMBER               (0x00U)

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Event status processing data */
struct Dem_Event_Context_s
{
  Dem_EventIdType EventId;  /*!< Processed Event */
  Dem_UDSStatus_Type OldEventStatus;  /*!< [in] event status before processing */
  Dem_UDSStatus_Type OldExternalEventStatus;  /*!< [in] external event status before processing */
  Dem_UDSStatus_Type NewEventStatus;  /*!< [in,out] event status after processing */
  Dem_Cfg_StorageTriggerType EventEffects; /*!< [in,out] status change triggers resulting from event status changes */
  boolean DataModified;  /*!< [in,out] processing has modified enviromental data */
  boolean QualifyEvent;  /*!< [in,out] Qualify single event without driving cycle qualification */
};

/*! Event status processing data type */
typedef struct Dem_Event_Context_s Dem_Event_ContextType;

#endif /* DEM_EVENTIF_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EventIF_Types.h
 *********************************************************************************************************************/
