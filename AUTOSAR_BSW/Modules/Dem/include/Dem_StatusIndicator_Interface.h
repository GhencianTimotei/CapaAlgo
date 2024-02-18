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
 *  \defgroup   Dem_StatusIndicator
 *  \{
 *  \file       Dem_StatusIndicator_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of StatusIndicator subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/
#if !defined (DEM_STATUSINDICATOR_INTERFACE_H)
#define DEM_STATUSINDICATOR_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                         /* Dem module header */
 /* ------------------------------------------------------------------------- */
#include "Dem_StatusIndicator_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
 /*!
  * \defgroup Dem_StatusIndicator_PublicProperties Public Properties
  * \{
  */

/* ****************************************************************************
 * Dem_StatusIndicator_isStatusIndicatorEnabled
 *****************************************************************************/
/*!
 * \brief         Tests whether feature Status Indicator is enabled.
 *
 * \details       Tests whether feature Status Indicator is enabled.
 *
 * \return        TRUE
 *                Status Indicator feature is enabled.
 * \return        FALSE
 *                Status Indicator featured is NOT enabled.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StatusIndicator_isStatusIndicatorEnabled(
  void
  );

/* ****************************************************************************
 * Dem_StatusIndicator_isExtendedFimEnabled
 *****************************************************************************/
/*!
 * \brief         Tests whether feature Extended FiM is enabled.
 *
 * \details       Tests whether feature Extended FiM is enabled.
 *
 * \return        TRUE
 *                Extended FiM feature is enabled.
 * \return        FALSE
 *                Extended FiM feature is NOT enabled.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StatusIndicator_IsExtendedFimEnabled(
  void
  );

/* ****************************************************************************
 * Dem_StatusIndicator_Test_WIRSLC
 *****************************************************************************/
/*!
 * \brief         Tests warning indicator requested since last clear bit
 *                of StatusIndicator byte
 *
 * \details       Tests warning indicator requested since last clear bit
 *                of StatusIndicator byte
 *
 * \param[in]     StatusIndicator
 *                Current StatusIndicator byte of the event.
 *
 * \return        TRUE
 *                The WIRSLC bit is set
 * \return        FALSE
 *                The WIRSLC bit not set
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StatusIndicator_Test_WIRSLC(
  CONST(Dem_StatusIndicator_Type, AUTOMATIC) StatusIndicator
  );

/* ****************************************************************************
 * Dem_StatusIndicator_Test_TFSLC
 *****************************************************************************/
/*!
 * \brief         Tests test failed since last clear bit of StatusIndicator byte
 *                
 * \details       Tests test failed since last clear bit of StatusIndicator byte
 *
 * \param[in]     StatusIndicator
 *                Current StatusIndicator byte of the event.
 *
 * \return        TRUE
 *                The TFSLC bit is set
 * \return        FALSE
 *                The TFSLC bit not set
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StatusIndicator_Test_TFSLC(
  CONST(Dem_StatusIndicator_Type, AUTOMATIC) StatusIndicator
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h" 

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 ********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"
/*!
* \defgroup Dem_StatusIndicator_ApiFunctions Api Functions
* \{
*/

/* ****************************************************************************
 * Dem_StatusIndicator_Init
 *****************************************************************************/
/*!
 * \brief         Run the initialization sequence
 *
 * \details       Run the initialization sequence
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
  DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_StatusIndicator_Init(
    void
  );

/* ****************************************************************************
 * Dem_StatusIndicator_MainFunction
 *****************************************************************************/
/*!
 * \brief         Process queued StatusIndicator related actions.
 *
 * \details       Process queued StatusIndicator related actions.
 *                Function is invoked from the Dem main function when 
 *                Dem_SetSI30Symptom is called.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StatusIndicator_MainFunction(
  void
  );

/* ****************************************************************************
 * Dem_StatusIndicator_UpdateOnTestFailed
 *****************************************************************************/
/*!
 * \brief         Set the TFSLC, WIRSLC and ERDTC bits if conditions met, and
 *                store the StatusIndicator byte.
 *
 * \details       Set the TFSLC, WIRSLC and ERDTC bits if conditions met, and
 *                store the StatusIndicator byte.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[in]     MemoryIndex
 *                Handle of the memory block.
 * \param[in]     UpdateFlags
 *                Trigger flags.
 *
 * \return        TRUE
 *                Memory block is modified.
 * \return        FALSE
 *                Memory block is NOT modified.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StatusIndicator_UpdateOnTestFailed(
  Dem_EventIdType EventId,
  Dem_Cfg_MemoryIndexType MemoryIndex,
  Dem_Cfg_StorageTriggerType UpdateFlags
  );

/* ****************************************************************************
 * Dem_StatusIndicator_UpdateOnEventAged
 *****************************************************************************/
/*!
 * \brief         Reset all bits and store the StatusIndicator byte.
 *
 * \details       Reset all bits and store the StatusIndicator byte.
 *
 * \pre           DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_OFF
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StatusIndicator_UpdateOnEventAged(
  Dem_Cfg_MemoryIndexType MemoryIndex
  );

/* ****************************************************************************
 * Dem_StatusIndicator_UpdateOnMemoryInitRestoreMemory
 *****************************************************************************/
/*!
 * \brief         Synchronize the WIRSLC bit and store the StatusIndicator byte.
 *
 * \details       Synchronize the WIRSLC bit and store the StatusIndicator byte.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[in]     MemoryIndex
 *                Handle of the memory block.
 * \param[in]     MemoryEntryId
 *                The memory entry handle.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StatusIndicator_UpdateOnMemoryInitRestoreMemory(
  Dem_EventIdType EventId,
  Dem_Cfg_MemoryIndexType MemoryIndex,
  Dem_Cfg_MemoryEntryHandleType MemoryEntryId
  );

/* ****************************************************************************
 * Dem_StatusIndicator_UpdateOnObdMemoryRestoreSetWIRSLC
 *****************************************************************************/
/*!
 * \brief         Set WIRSLC bit and store the StatusIndicator byte.
 *
 * \details       Set WIRSLC bit and store the StatusIndicator byte.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StatusIndicator_UpdateOnObdMemoryRestoreSetWIRSLC(
  Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_StatusIndicator_GetStatusIndicator
 *****************************************************************************/
/*!
 * \brief         Gets Status Indicator byte and writes it to the Status 
 *                pointer.
 *
 * \details       Gets Status Indicator byte and writes it to the Status 
 *                pointer.
 *
 * \param[in]     EventId
 *                Unique handle of the Event to report.
 * \param[out]    Status
 *                Status Indicator byte containing the status bits.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_StatusIndicator_GetStatusIndicator(
  Dem_EventIdType EventId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Status
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_STATUSINDICATOR_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_StatusIndicator_Interface.h
 *********************************************************************************************************************/
