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
/*! \ingroup    Dem_Shared
 *  \defgroup   Dem_ExternalCommunication External Communication
 *  \{
 *  \file       Dem_ExtCom_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of external communication subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_EXTCOM_INTERFACE_H)
#define DEM_EXTCOM_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_ExtCom_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_ExternalCommunication_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_ExtCom_TestCurrentPartitionIsMaster()
 *****************************************************************************/
/*!
 * \brief         Verify whether the calling context is the master partition.
 *
 * \details       Verify whether the calling context is the master partition.
 *
 * \return        TRUE
 *                Calling context is the master partition.
 * \return        FALSE
 *                Calling context is not the master partition.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) Dem_ExtCom_TestCurrentPartitionIsMaster(
  void
  );

/* ****************************************************************************
 * Dem_ExtCom_GetCurrentApplicationId()
 *****************************************************************************/
/*!
 * \brief         Get the current application Id from Os.
 *
 * \details       Get the current application Id from Os.
 *
 * \return        Application identifier
 *
 * \pre           Feature multiple satellites is enabled.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ExtCom_ApplicationType, DEM_CODE) Dem_ExtCom_GetCurrentApplicationId(
  void
);


/* ****************************************************************************
 * Dem_ExtCom_FimInitSatellite()
 *****************************************************************************/
/*!
 * \brief         Initialize FiM satellites with os application Id of Dem satellite
 *
 * \details       Initialize FiM satellites with os application Id of Dem satellite
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ExtCom_FimInitSatellite(
  Dem_ExtCom_ApplicationType ApplicationId
  );

/*!
 * \}
 */

/* ****************************************************************************
 * Dem_ExtCom_FimGetFunctionPendingStatus()
 *****************************************************************************/
/*!
 * \brief         Initialize FiM satellites with os application Id of Dem satellite
 *
 * \details       Initialize FiM satellites with os application Id of Dem satellite
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE) Dem_ExtCom_FimGetFunctionPendingStatus(
  CONST(Dem_ExtCom_FiMFunctionIdType, AUTOMATIC) FID,
  CONSTP2VAR(boolean, AUTOMATIC, AUTOMATIC) FimFaultPending
  );

/* ****************************************************************************
 * Dem_ExtCom_FimDemTriggerOnUnconfirmed()
 *****************************************************************************/
/*!
 * \brief         Trigger FiM on Dem unconfirmed DTC.
 *
 * \details       Trigger FiM on Dem unconfirmed DTC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE) Dem_ExtCom_FimDemTriggerOnUnconfirmed(
  Dem_EventIdType EventId
  );

/*!
 * \}
 */

#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_EXTCOM_INTERFACE_H */
/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ExtCom_Interface.h
 *********************************************************************************************************************/
