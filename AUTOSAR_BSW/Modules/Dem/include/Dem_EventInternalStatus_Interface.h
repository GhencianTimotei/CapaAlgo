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
/*! \ingroup    Dem_Event
 *  \defgroup   Dem_EventInternalStatus EventInternal Status
 *  \{
 *  \file       Dem_EventInternalStatus_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Interface of the EventInternalStatus subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_EVENTINTERNALSTATUS_INTERFACE_H)
#define DEM_EVENTINTERNALSTATUS_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_EventInternalStatus_Types.h"
/* ------------------------------------------------------------------------- */


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
 * \defgroup Dem_EventInternalStatus_PublicProperties Public Properties
 * \{
 */

/* Internal status bit 'event suppressed' ---------------------------------- */

/* ****************************************************************************
 * Dem_EventInternalStatus_TestAvailabilityChanged
 *****************************************************************************/
/*!
 * \brief         Test if event availability changed is set in the internal status
 *
 * \details       Test if event availability changed is set in the internal status
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        TRUE
 *                Flag is set
 * \return        FALSE
 *                Flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_TestAvailabilityChanged(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );

/* ****************************************************************************
 * Dem_EventInternalStatus_SetAvailabilityChanged
 *****************************************************************************/
/*!
 * \brief         Set event availability changed in the internal status.
 *
 * \details       Set event availability changed in the internal status.
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        InternalStatus with flag set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_SetAvailabilityChanged(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );

/* ****************************************************************************
 * Dem_EventInternalStatus_ResetAvailabilityChanged
 *****************************************************************************/
/*!
 * \brief         Reset event availability changed in the internal status
 *
 * \details       Reset event availability changed in the internal status.
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        InternalStatus with flag reset.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_ResetAvailabilityChanged(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );

/* Internal status bit 'event available' ----------------------------------- */

/* ****************************************************************************
 * Dem_EventInternalStatus_TestEventDisconnected
 *****************************************************************************/
/*!
 * \brief         Test if event disconnected is set in the internal status
 *
 * \details       Test if event disconnected is set in the internal status
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        TRUE
 *                Flag is set
 * \return        FALSE
 *                Flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_TestEventDisconnected(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );

/* ****************************************************************************
 * Dem_EventInternalStatus_SetEventDisconnected
 *****************************************************************************/
/*!
 * \brief         Set event disconnected in the internal status
 *
 * \details       Set event disconnected in the internal status. Only has an
 *                effect if event availability is supported
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        InternalStatus with flag set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_SetEventDisconnected(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );

#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON) || (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_ResetEventDisconnected
 *****************************************************************************/
/*!
 * \brief         Reset event disconnected in the internal status
 *
 * \details       Reset event disconnected in the internal status. Only has an
 *                effect if event availability is supported
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        InternalStatus with flag reset.
 *
 * \pre           -
 * \config        DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON
 *             || DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_ResetEventDisconnected(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );
#endif

/* Internal status bit 'DTC disabled by PB selectable' --------------------- */

/* ****************************************************************************
 * Dem_EventInternalStatus_TestAvailableInVariant
 *****************************************************************************/
/*!
 * \brief         Test if event available in variant is set in the internal status
 *
 * \details       Test if event available in variant is set in the internal status
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        TRUE
 *                Flag is set
 * \return        FALSE
 *                Flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_TestAvailableInVariant(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );

#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_SetAvailableInVariant
 *****************************************************************************/
/*!
 * \brief         Set event available in variant in the internal status
 *
 * \details       Set event available in variant in the internal status
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        InternalStatus with flag set.
 *
 * \pre           -
 * \config        DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_SetAvailableInVariant(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );
#endif

/* ****************************************************************************
 * Dem_EventInternalStatus_TestSimilarConditions
 *****************************************************************************/
/*!
 * \brief         Test if similar conditions is set in the internal status
 *
 * \details       Test if similar conditions is set in the internal status
 *
 * \param[in]     ExtendedStatus
 *                Extended status byte
 *
 * \return        TRUE
 *                Flag is set
 * \return        FALSE
 *                Flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_TestSimilarConditions(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  ExtendedStatus
);

/* ****************************************************************************
 * Dem_EventInternalStatus_SetSimilarConditions
 *****************************************************************************/
/*!
 * \brief         Set similar conditions in the extended status
 *
 * \details       Set similar conditions in the extended status
 *
 * \param[in]     ExtendedStatus
 *                Extended status byte
 *
 * \return        Extended status with similar condition flag set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_ExtendedStatusType, DEM_CODE)
Dem_EventInternalStatus_SetSimilarConditions(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  ExtendedStatus
);

/* ****************************************************************************
 * Dem_EventInternalStatus_ResetSimilarConditions
 *****************************************************************************/
/*!
 * \brief         Reset similar conditions in the extended status
 *
 * \details       Reset similar conditions in the extended status
 *
 * \param[in]     ExtendedStatus
 *                Extended status byte
 *
 * \return        Extended status with similar condition flag reset
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_ExtendedStatusType, DEM_CODE)
Dem_EventInternalStatus_ResetSimilarConditions(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  ExtendedStatus
);







#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_GetMilGroupPendingCount
 *****************************************************************************/
/*!
 * \brief         Get the number of pending events of the MIL group
 *
 * \details       Get the number of pending events of the MIL group
 *
 * \param[in]     MilGroupIndex
 *                Unique handle of the MIL group
 *
 * \return        The number of pending events of the MIL group
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_MIL_GROUPS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_EventInternalStatus_GetMilGroupPendingCount(
  CONST(uint16, AUTOMATIC)  MilGroupIndex
  );
#endif

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_SetMilGroupPendingCount
 *****************************************************************************/
/*!
 * \brief         Set the number of pending events of the MIL group
 *
 * \details       Set the number of pending events of the MIL group
 *
 * \param[in]     MilGroupIndex
 *                Unique handle of the MIL group
 * \param[in]     PendingCount
 *                New number of pending events of the MIL group
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_MIL_GROUPS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventInternalStatus_SetMilGroupPendingCount(
  CONST(uint16, AUTOMATIC)  MilGroupIndex,
  CONST(uint16, AUTOMATIC)  PendingCount
  );
#endif

/* ****************************************************************************
 * Dem_EventInternalStatus_Test_QualifyStatus_CDTC
 *****************************************************************************/
/*!
 * \brief         Test Confirmed DTC qualified state of event qualification status
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current qualify status of the event
 *
 * \return        TRUE
 *                The CDTC bit is qualified
 * \return        FALSE
 *                The CDTC bit is not qualified
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_Test_QualifyStatus_CDTC(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_EventInternalStatus_Set_QualifyStatus_CDTC
 *****************************************************************************/
/*!
 * \brief         Set Confirmed DTC qualified state of event qualification status.
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current event qualify status
 *
 * \return        Event qualify status with flag set for CDTC.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
  Dem_EventInternalStatus_Set_QualifyStatus_CDTC(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_EventInternalStatus_Reset_QualifyStatus_CDTC
 *****************************************************************************/
/*!
 * \brief         Reset Confirmed DTC qualified state of event qualification status.
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current event qualify status
 *
 * \return        Event qualify status with flag reset for CDTC.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_Reset_QualifyStatus_CDTC(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  );

/* Qualify status bit 'warningIndicatorRequested' -------------------------- */
/* ****************************************************************************
 * Dem_EventInternalStatus_Test_QualifyStatus_WIR
 *****************************************************************************/
/*!
 * \brief         Test Warning Indicator Requested qualified state 
 *                of event qualification status
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current qualify status of the event
 *
 * \return        TRUE
 *                The WIR bit is qualified
 * \return        FALSE
 *                The WIR bit is not qualified
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_Test_QualifyStatus_WIR(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_EventInternalStatus_Set_QualifyStatus_WIR
 *****************************************************************************/
/*!
 * \brief         Set Warning Indicator Requested qualified state 
 *                of event qualification status.
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current event qualify status
 *
 * \return        Event qualify status with flag set for WIR.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_Set_QualifyStatus_WIR(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_EventInternalStatus_Reset_QualifyStatus_WIR
 *****************************************************************************/
/*!
 * \brief         Reset Warning Indicator Requested qualified state 
 *                of event qualification status.
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current event qualify status
 *
 * \return        Event qualify status with flag reset for WIR.
 *
 * \pre           -
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_Reset_QualifyStatus_WIR(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_EventInternalStatus_Private Private Methods
 * \{
 */

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
 * \defgroup Dem_EventInternalStatus_Public Public Methods
 * \{
 */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_EVENTINTERNALSTATUS_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EventInternalStatus_Interface.h
 *********************************************************************************************************************/
