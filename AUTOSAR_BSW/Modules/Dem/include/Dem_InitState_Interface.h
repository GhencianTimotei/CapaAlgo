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
 *  \defgroup   Dem_InitState DEM Initialization State
 *  \{
 *  \file       Dem_InitState_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) Interface declaration file
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_INITSTATE_INTERFACE_H)
#define DEM_INITSTATE_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_InitState_Types.h"
#include "Dem_Satellite_Types.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

 /* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_InitState_PublicProperties Public Properties
 * \{
 */


/* ****************************************************************************
 * Dem_InitState_SetInitState
 *****************************************************************************/
/*!
 * \brief         Set the Dem initialization state
 *
 * \details       Set the Dem initialization state
 *
 * \param[in]     InitState
 *                The initialization state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_InitState_SetInitState(
  uint8 InitState
  );


/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_InitState_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_InitState_TestMasterInState
 *****************************************************************************/
/*!
 * \brief         Test if the Dem is in the given state
 *
 * \details       Test if the Dem is in the given state
 *
 * \param[in]     InitState
 *                The initialization state
 *
 * \return        TRUE: The Dem is in the given state
 * \return        FALSE: The Dem is not in the given state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_InitState_TestMasterInState(
  CONST(uint8, AUTOMATIC) InitState
  );

/* ****************************************************************************
 * Dem_InitState_TestMasterAtLeastInState
 *****************************************************************************/
/*!
 * \brief         Test if the Dem is at least in the given state
 *
 * \details       Test if the Dem is at least in the given state
 *
 * \param[in]     InitState
 *                The initialization state
 *
 * \return        TRUE: The Dem is in the given state
 * \return        FALSE: The Dem is not in the given state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_InitState_TestMasterAtLeastInState(
  CONST(uint8, AUTOMATIC) InitState
  );

/* ****************************************************************************
 * Dem_InitState_TestSatelliteInState
 *****************************************************************************/
/*!
 * \brief         Test if the Dem is in the given state
 *
 * \details       Test if the Dem is in the given state
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 * \param[in]     InitState
 *                The initialization state
 *
 * \return        TRUE: The Dem Satellite is in the given state
 * \return        FALSE: The Dem Satellite is not in the given state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_InitState_TestSatelliteInState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(uint8, AUTOMATIC) InitState
  );

/* ****************************************************************************
 * Dem_InitState_TestAllSatellitesAtLeastInState
 *****************************************************************************/
/*!
 * \brief         Test if all Satellites are at least in the given state
 *
 * \details       Test if all Satellites are at least in the given state
 *
 * \param[in]     InitState
 *                The initialization state
 *
 * \return        TRUE: All Satellites are at least in the given state
 * \return        FALSE: At least one Satellite is not in the given state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_InitState_TestAllSatellitesAtLeastInState(
  CONST(uint8, AUTOMATIC) InitState
  );

/* ****************************************************************************
 * Dem_InitState_TestSatelliteAtLeastInState
 *****************************************************************************/
/*!
 * \brief         Test if the Dem is at least in the given state
 *
 * \details       Test if the Dem is at least in the given state
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 * \param[in]     InitState
 *                The initialization state
 *
 * \return        TRUE: The Dem Satellite is in the given state
 * \return        FALSE: The Dem Satellite is not in the given state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_InitState_TestSatelliteAtLeastInState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(uint8, AUTOMATIC) InitState
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_INITSTATE_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_InitState_Interface.h
 *********************************************************************************************************************/
