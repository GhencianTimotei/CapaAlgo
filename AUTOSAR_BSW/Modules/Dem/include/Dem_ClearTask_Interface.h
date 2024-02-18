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
/*! \ingroup    Dem_Master
 *  \defgroup   Dem_ClearTask Clear Task
 *  \{
 *  \file       Dem_ClearTask_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of ClearTask subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_CLEARTASK_INTERFACE_H)
#define DEM_CLEARTASK_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_ClearTask_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_ClearTask_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_ClearTask_GetClearClient()
 *****************************************************************************/
/*!
 * \brief         Get the client of the current clear operation.
 *
 * \details       Get the client of the current clear operation.
 *
 * \return        The client of the clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE) 
Dem_ClearTask_GetClearClient(
  void
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
 * \defgroup Dem_ClearTask_Public Public Methods
 * \{
 */


/* ****************************************************************************
 * Dem_ClearTask_Init()
 *****************************************************************************/
/*!
 * \brief         Initialize the subcomponent
 *
 * \details       Initializes the subcomponent
 *
 * \pre           Only call during the initialization phase
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ClearTask_Init(
  void
  );

/* ****************************************************************************
 * Dem_ClearTask_MainFunction()
 *****************************************************************************/
/*!
 * \brief         Process the current clear requests
 *
 * \details       Process the current clear requests
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ClearTask_MainFunction(
  void
  );

/* ****************************************************************************
 * Dem_ClearTask_TryNewClear()
 *****************************************************************************/
/*!
 * \brief         Try to start a clear DTC operation
 *
 * \details       Starts a clear operation
 *
 * \param[in]     ClearRequest
 *                The ClearDTC request
 * \param[in]     DTCSelector
 *                The selector holding the selected DTC to clear
 *
 * \return        E_OK
 *                The Clear DTC operation was started
 * \return        E_NOT_OK
 *                Another Clear DTC operation is active
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_ClearTask_TryNewClear(
  CONST(Dem_ClearTask_ClearRequestConstPtrType, AUTOMATIC)  ClearRequest,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  );

# if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_ClearTask_NotifyClearCompleted()
 *****************************************************************************/
/*!
 * \brief         Notify all cleared blocks are persisted in NV
 *
 * \details       Notify all cleared blocks are persisted in NV
 *
 * \pre           -
 * \config        (DEM_CFG_USE_NVM ==STD_ON)
 *                && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ClearTask_NotifyClearCompleted(
  void
  );
#endif

# if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_ClearTask_NotifyClearWriteError()
 *****************************************************************************/
/*!
 * \brief         Notify write error occurred while writing a cleared block
 *
 * \details       Notify write error occurred while writing a cleared block
 *
 * \pre           -
 * \config        (DEM_CFG_USE_NVM ==STD_ON)
 *                && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ClearTask_NotifyClearWriteError(
  void
  );
#endif

#if (DEM_CFG_NOTIFY_CLEAR_ALLOWED == STD_ON)
/* ****************************************************************************
 * Dem_ClearTask_ClearEventAllowed
 *****************************************************************************/
/*!
 * \brief         Calls user defined clear allowed callback
 *
 * \details       This function calls a user defined clear allowed callback
 *                and handles the related error conditions.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event may be cleared
 * \return        FALSE
 *                The application does not allow clearing
 *
 * \pre           RTE is started
 * \config        DEM_CFG_NOTIFY_CLEAR_ALLOWED == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClearTask_ClearEventAllowed(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
);
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* DEM_CLEARTASK_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ClearTask_Interface.h
 *********************************************************************************************************************/
