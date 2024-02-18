/* *********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  --------------------------------------------------------------------------------------------------------------------
 */
/*! \ingroup    Dem_Dtr
 *  \defgroup   Dem_DtrData DTR Storage Handling
 *  \{
 *  \file       Dem_DtrData_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) Interface declaration file
 *  \details    Public Interfaces of DtrData subcomponent 
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DTRDATA_INTERFACE_H)
#define DEM_DTRDATA_INTERFACE_H


/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Own module header */
/* ------------------------------------------------------------------------- */
#include "Dem_DtrData_Types.h"


#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                            /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
/*!
 * \defgroup Dem_Dtr_Private Private Methods
 * \{
 */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Dtr_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_DtrData_GetGlobalDtrCount
 *****************************************************************************/
/*!
 * \brief         Get the number of configured Dtrs
 *
 * \details       Get the number of configured Dtrs.
 *
 * \return        The number of configured Dtr
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(DTRIdType, DEM_CODE)
Dem_DtrData_GetGlobalDtrCount(
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
 * \defgroup Dem_Dtr_Public Public Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_SetDtrValues
 *****************************************************************************/
/*!
 * \brief         Writes DTR values into memory.
 *
 * \details       -
 *
 * \param[in]     DTRId
 *                Unique handle of the Dtr.
 * \param[in]     TestValue
 *                The result value of a test.
 * \param[in]     LowerLimit
 *                The the lower limit of TestValue.
 * \param[in]     UpperLimit
 *                The the upper limit of TestValue.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_SetDtrValues(
  CONST(DTRIdType, AUTOMATIC) DTRId,
  CONST(uint16, AUTOMATIC) TestValue,
  CONST(uint16, AUTOMATIC) LowerLimit,
  CONST(uint16, AUTOMATIC) UpperLimit
  );
#endif

/* ****************************************************************************
 * Dem_DtrData_Init
 *****************************************************************************/
/*!
 * \brief         Initializes Dtr functionality
 *
 * \details       This function controls initialization of the Dtr
 *                subcomponent.
 *
 * \pre           May only be called during initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_Init(
  void
  );

/* ****************************************************************************
 * Dem_DtrData_PreInit
 *****************************************************************************/
/*!
 * \brief         Pre-initializes DTR data
 *
 * \details       This function performs basic initialization to allow later
 *                full initialization.
 *
 * \pre           May only be called during pre-initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_PreInit(
  void
  );

/* ****************************************************************************
 *  Dem_DtrData_MainFunction
 *****************************************************************************/
/*!
 * \brief         Process Dtr functionality
 *
 * \details       This function performs asynchronous tasks related to DTR
 *                management.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_MainFunction(
  void
  );

/* ****************************************************************************
 * Dem_DtrData_Shutdown
 *****************************************************************************/
/*!
 * \brief         Finalize DTR data
 *
 * \details       This function finalizes DTR data for writing into NV ram
 *
 * \pre           May only be called during shutdown
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_Shutdown(
  void
  );

/* ****************************************************************************
 * Dem_DtrData_IsValidHandle
 *****************************************************************************/
/*!
 * \brief         Tests whether a Dtr Id is valid
 *
 * \details       Tests whether a Dtr Id is valid
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr.
 *
 * \return        returns whether a Dtr Id is valid
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DtrData_IsValidHandle(
  CONST(DTRIdType, AUTOMATIC) DtrId
  );

/* ****************************************************************************
 * Dem_DtrData_EventAvailabilityChanged
 *****************************************************************************/
/*!
 * \brief         Report a change in Dtr visibility, if the availability of 
 *                the event has changed and the event is assigned to any Dtr.
 *
 * \details       Report a change in Dtr visibility, if the availability of 
 *                the event has changed and the event is assigned to any Dtr.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_EventAvailabilityChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_DTCSuppressionChanged
 *****************************************************************************/
/*!
 * \brief         Report a change in Dtr visibility, if required by a change
 *                of DTC suppression.
 *
 * \details       Report a change in Dtr visibility, if the suppression of 
 *                the event's DTC has changed and at least one subevent is 
 *                assigned to any Dtr.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_DTCSuppressionChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/* ****************************************************************************
 * Dem_DtrData_ResetDtrsOfEvent
 *****************************************************************************/
/*!
 * \brief         Resets Dtr Values of all Dtrs referencing a specific event
 *
 * \details       Resets Dtr Values of all Dtrs referencing a specific event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_ResetDtrsOfEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_DtrData_ResetDtrsWithoutEvent
 *****************************************************************************/
/*!
 * \brief         Resets Dtr Values of all Dtrs not referencing an event
 *
 * \details       Resets Dtr Values of all Dtrs not referencing an event
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_ResetDtrsWithoutEvent(
  void
  );

/* ****************************************************************************
 * Dem_DtrData_SetDtr
 *****************************************************************************/
/*!
 * \brief         Reports a DTR result with lower and upper limit
 *
 * \details       Reports a DTR result with lower and upper limit.
 *                Depending on the reported control value and the configured
 *                DTR attributes the DTR values are either ignored, processed
 *                or reset.
 *
 * \param[in]     DTRId
 *                Unique handle of the Dtr.
 * \param[in]     TestResult
 *                Test Result
 * \param[in]     LowerLimit
 *                Lower Limit
 * \param[in]     UpperLimit
 *                Upper Limit
 * \param[in]     Ctrlval
 *                Dtr Control Value
 *
 * \return        E_OK
 *                Report of DTR result was succesful
 * \return        E_NOT_OK
 *                Report of DTR result failed
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different Dtr Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DtrData_SetDtr(
  CONST(DTRIdType, AUTOMATIC) DTRId,
  CONST(sint32, AUTOMATIC) TestResult,
  CONST(sint32, AUTOMATIC) LowerLimit,
  CONST(sint32, AUTOMATIC) UpperLimit,
  CONST(Dem_DTRControlType, AUTOMATIC) Ctrlval
  );

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_TestDtrVisibility
 *****************************************************************************/
/*!
 * \brief         Test whether the Dtr is visible to the diagnostic tester
 *
 * \details       Test whether the Dtr is visible to the diagnostic tester
 *
 * \param[in]     DTRId
 *                Unique handle of the Dtr.
 *
 * \return        TRUE
 *                The Dtr may be reported to a tester
 * \return        FALSE
 *                The Dtr may not be reported to a tester
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DtrData_TestDtrVisibility(
  CONST(DTRIdType, AUTOMATIC) DTRId
  );
#endif

/* ****************************************************************************
 * Dem_DtrData_GetUaSId
 *****************************************************************************/
/*!
 * \brief         Get the UaSId for the Dtr
 *
 * \details       Get the UaSId for the Dtr
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr.
 *                The DtrId must be in range [0..Dem_DtrData_GetGlobalDtrCount()-1[.
 *
 * \return        UaSId for the Dtr.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DtrData_GetUaSId(
  CONST(DTRIdType, AUTOMATIC) DtrId
  );

/* ****************************************************************************
 * Dem_DtrData_GetTestValue
 *****************************************************************************/
/*!
 * \brief         Get the test value of the Dtr
 *
 * \details       Get the test value of the Dtr
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr
 *                The DtrId must be in range [0..Dem_DtrData_GetGlobalDtrCount()[.
 *
 * \return        The test value
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_DtrData_GetTestValue(
  CONST(DTRIdType, AUTOMATIC)  DtrId
  );

/* ****************************************************************************
 * Dem_DtrData_GetLowerLimit
 *****************************************************************************/
/*!
 * \brief         Get the lower limit of the Dtr
 *
 * \details       Get the lower limit of the Dtr
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr
 *                The DtrId must be in range [0..Dem_DtrData_GetGlobalDtrCount()[.
 *
 * \return        The lower limit
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_DtrData_GetLowerLimit(
  CONST(DTRIdType, AUTOMATIC)  DtrId
  );

/* ****************************************************************************
 * Dem_DtrData_GetUpperLimit
 *****************************************************************************/
 /*!
 * \brief         Get the upper limit of the Dtr
 *
 * \details       Get the upper limit of the Dtr
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr
 *                The DtrId must be in range [0..Dem_DtrData_GetGlobalDtrCount()[.
 *
 * \return        The upper limit
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_DtrData_GetUpperLimit(
  CONST(DTRIdType, AUTOMATIC)  DtrId
  );

/*!
 * \}
 */

#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DTRDATA_INTERFACE_H */

/*!
 * \}
 */


/* ********************************************************************************************************************
 *  END OF FILE: Dem_DtrData_Interface.h
 *********************************************************************************************************************/
