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
/*! \ingroup    Dem_ClientData
 *  \defgroup   Dem_ClearDTC ClearDTC
 *  \{
 *  \file       Dem_ClearDTC_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) Interface declaration file
 *  \details    Public interface of ClearDTC subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_CLEARDTC_INTERFACE_H)
#define DEM_CLEARDTC_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_ClearDTC_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_ClearDTC_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_ClearDTC_GetClearStatus()
 *****************************************************************************/
/*!
 * \brief         Get the status of a clear operation.
 *
 * \details       -
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle to modify.
 *
 * \return        The status of the clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ClearDTC_StatusType, DEM_CODE) Dem_ClearDTC_GetClearStatus(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
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
 * \defgroup Dem_ClearDTC_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_ClearDTC_Init()
 *****************************************************************************/
/*!
 * \brief         Initialize the clear DTC subcomponent.
 *
 * \details       Initializes the subcomponent. All clear operations are idle
 *                after initialization.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_Init(
  void
  );

/* ****************************************************************************
 * Dem_ClearDTC_SetClearData()
 *****************************************************************************/
/*!
 * \brief         Set the data of a clear operation.
 *
 * \details       Set the data of a clear operation.
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle of the data to be modified.
 * \param[in]     ClearDTCData
 *                The clear data to be set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_SetClearData(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle,
  CONST(Dem_ClearDTC_DataType, AUTOMATIC)  ClearDTCData
  );

/* ****************************************************************************
 % Dem_ClearDTC_StartClear()
 *****************************************************************************/
/*!
 * \brief         Start clear DTC for a single event
 *
 * \details       Initializes a clear DTC handler to process clearing a single
 *                event
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle to modify.
 * \param[in]     DTCSelector
 *                The selector holding the selected DTC to clear
 *
 * \return        Status of the started clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClear(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  );

#if (DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON)
/* ****************************************************************************
 * Dem_ClearDTC_StartClearJ1939()
 *****************************************************************************/
/*!
 * \brief         Start clear J1939 DTCs
 *
 * \details       Initializes a clear DTC handler to process clearing J1939 DTCs
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle to modify.
 * \param[in]     DTCSelector
 *                The selector holding the selected DTC to clear
 * \param[in]     DTCTypeFilter
 *                The type of DTCs to be cleared
 * \param[in]     Node
 *                The node to be cleared
 *
 * \return        Status of the started clear operation
 *
 * \config        DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearJ1939(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector,
  CONST(uint8, AUTOMATIC)  DTCTypeFilter,
  CONST(uint8, AUTOMATIC)  Node
  );
#endif

/* ****************************************************************************
 * Dem_ClearDTC_ResetClearStatus()
 *****************************************************************************/
/*!
 * \brief         Reset the clear status.
 *
 * \details       Clears the status of the ClearDTCHandle to IDLE. 
 *                This operation will fail if the current state is not final.
 *                
 *                The use-case of this API is to allow clients to clear the
 *                final clear result, distinguishing between a result poll and
 *                a new clear request.
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle to modify.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_ResetClearStatus(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  );

/* ****************************************************************************
 * Dem_ClearDTC_NotifyClearResult()
 *****************************************************************************/
/*!
 * \brief         Notification after clear has finished.
 *
 * \details       Notification callback to report the end of a clear operation.
 *
 * \param[in]     QueueClearState
 *                The notified state.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_NotifyClearResult(
  CONST(uint8, AUTOMATIC)  QueueClearState
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* DEM_CLEARDTC_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ClearDTC_Interface.h
 *********************************************************************************************************************/
