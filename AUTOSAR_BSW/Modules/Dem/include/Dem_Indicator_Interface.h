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
 *  \defgroup   Dem_Indicator Indicator
 *  \{
 *  \file       Dem_Indicator_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Manages the User and Special indicator states
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_INDICATOR_INTERFACE_H)
#define DEM_INDICATOR_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Indicator_Types.h"
#include "Dem_Client_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Indicator_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Indicator_TestHasIndicator
 *****************************************************************************/
/*!
 * \brief         Test, if the event has configured any indicator.
 *
 * \details       Test, if the event has configured any indicator.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \return        TRUE
 *                The event has configured a user- or a special indicator.
 * \return        FALSE
 *                The event has no indicators configured.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Indicator_TestHasIndicator(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_GetQualifiedActiveEventCount
 *****************************************************************************/
/*!
 * \brief         Get the number of qualified active and failed events for the
 *                WWH-OBD DTC class
 *
 * \details       Get the number of qualified active and failed events for the
 *                WWH-OBD DTC class
 *
 * \param[in]     WwhObdDtcClass
 *                Unique handle of the WWH-OBD DTC class
 *
 * \return        The number of qualified active and failed events
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Indicator_GetQualifiedActiveEventCount(
  CONST(uint8, AUTOMATIC)  WwhObdDtcClass
  );
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_SetQualifiedActiveEventCount
 *****************************************************************************/
/*!
 * \brief         Set the number of qualified active and failed events for the
 *                WWH-OBD DTC class
 *
 * \details       Set the number of qualified active and failed events for the
 *                WWH-OBD DTC class
 *
 * \param[in]     WwhObdDtcClass
 *                Unique handle of the WWH-OBD DTC class
 * \param[in]     QualifiedActiveEventCount
 *                The new number of qualified active and failed events
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetQualifiedActiveEventCount(
  CONST(uint8, AUTOMATIC)  WwhObdDtcClass,
  CONST(Dem_EventIdType, AUTOMATIC)  QualifiedActiveEventCount
  );
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_GetDtcClassMILCount
 *****************************************************************************/
/*!
 * \brief         Get the number of MIL requests for the WWHO-OBD DTC class
 *
 * \details       Get the number of MIL requests for the WWHO-OBD DTC class
 *
 * \param[in]     WwhObdDtcClass
 *                Unique handle of the WWH-OBD DTC class
 *
 * \return        The number of MIL requests
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Indicator_GetDtcClassMILCount(
  CONST(uint8, AUTOMATIC)  WwhObdDtcClass
  );
#endif




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
 * \defgroup Dem_Indicator_Public Public Methods
 * \{
 */

#if (DEM_FEATURE_NEED_REPORTED_MIL_STATE == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_TestMilReportedActive
 *****************************************************************************/
/*!
 * \brief         Returns if the MIL is considered as active.
 *
 * \details       The MIL is always considered as active (for reporting in 
 *                PID 0x01, PID 0x21 and PID 0x4D), if it is continuous (or 
 *                continuous blinking). 
 *                In configurations with 'Report Blinking Mil As Active' 
 *                enabled, the Mil is also considered as active if it is only
 *                blinking or flashing. 
 *
 * \return        TRUE
 *                The MIL is considered as active.
 * \return        FALSE
 *                The MIL is not considered as active
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_REPORTED_MIL_STATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Indicator_TestMilReportedActive(
  void
  );
#endif

#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_UpdatePIDsMilEnabled
 *****************************************************************************/
/*!
 * \brief         Hook function called when the MIL is activated
 *
 * \details       If the Mil status has changed from Off to On the current
 *                Odometer value (absolute) is set as base value and the
 *                Engine Run Time is set to 0
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdatePIDsMilEnabled(
  void
  );
#endif

/* ****************************************************************************
 * Dem_Indicator_UserIndicatorEnable
 *****************************************************************************/
/*!
 * \brief         Updates user-defined indicator counters
 *
 * \details       Adds the event's contribution to the indicator states.
 *                Basically this adds 1 to each indicators continuous or
 *                blinking count, if the indicator is enabled by the given
 *                event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UserIndicatorEnable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Indicator_SpecialIndicatorEnable
 *****************************************************************************/
/*!
 * \brief         Updates special indicator counters
 *
 * \details       Add the event's contribution to the indicator states.
 *                Basically this adds 1 from each indicators continuous,
 *                blinking, fast flash or slow flash count, if the indicator
 *                is enabled by the given event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SpecialIndicatorEnable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Indicator_UserIndicatorDisable
 *****************************************************************************/
/*!
 * \brief         Update user-defined indicator counters
 *
 * \details       Removes the event's contribution to the indicator states.
 *                Basically this subtracts 1 from each indicators continuous or
 *                blinking count, if the indicator is enabled by the given
 *                event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UserIndicatorDisable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Indicator_SpecialIndicatorDisable
 *****************************************************************************/
/*!
 * \brief         Updates special indicator counters
 *
 * \details       Removes the event's contribution to the indicator states.
 *                Basically this subtracts 1 from each indicators continuous or
 *                blinking count, if the indicator is enabled by the given
 *                event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SpecialIndicatorDisable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 ! Dem_Indicator_GlobalIndicatorActivationMode
 *****************************************************************************/
/*!
 * \brief         Gets the current Activation Mode.
 *
 * \details       Gets the current Activation Mode.
 *
 * \return        The current activation mode
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_IndicatorStatusType, DEM_CODE)
Dem_Indicator_GlobalIndicatorActivationMode(
  void
  );
#endif

/* ****************************************************************************
 * Dem_Indicator_IndicatorDisable
 *****************************************************************************/
/*!
 * \brief         Decrement indicator counters and update global indicator states
 *
 * \details       Update user indicators and special indicator
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_IndicatorDisable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Indicator_IndicatorEnable
 *****************************************************************************/
/*!
 * \brief         Increment indicator counters and update global indicator states
 *
 * \details       Update user indicators and special indicator
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_IndicatorEnable(
CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
);

/* ****************************************************************************
 * Dem_Indicator_InitWwhObdStatistics
 *****************************************************************************/
/*!
 * \brief         Initializes the WWHOBD Dtc class related statistics
 *
 * \details       Initializes the WWHOBD Dtc class related statistics
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_InitWwhObdStatistics(
  void
  );

/* ****************************************************************************
 * Dem_Indicator_UpdateSpecialIndicators
 *****************************************************************************/
/*!
 * \brief         Initializes the OBD and J1939 special indicator
 *
 * \details       Initializes the OBD and J1939 special indicator
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdateSpecialIndicators(
  void
  );

/* ****************************************************************************
 * Dem_Indicator_UpdateUserIndicators
 *****************************************************************************/
/*!
 * \brief         Initializes user indicators
 *
 * \details       Initializes user indicators
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdateUserIndicators(
  void
  );


/* ****************************************************************************
 * Dem_Indicator_GetIndicatorStatus
 *****************************************************************************/
/*!
 * \brief         Gets the current indicator status
 *
 * \details       Gets the current indicator status
 *
 * \param[in]     IndicatorId
 *                Unique identifier of the indicator
 *
 * \return        The current indicator status
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_IndicatorStatusType, DEM_CODE)
Dem_Indicator_GetIndicatorStatus(
  CONST(uint8, AUTOMATIC)  IndicatorId
  );

/* ****************************************************************************
 * Dem_Indicator_UpdateGlobalSpecialIndicatorStates
 *****************************************************************************/
/*!
 * \brief         Update the global indicator state of a special indicator
 *
 * \details       This function updates the global states of one of the special
 *                indicators red stop lamp, amber warning lamp, malfunction
 *                indicator lamp and the protect lamp.
 *
 * \param[in]     IndicatorId
 *                Unique handle of the special indicator
 *
 * \pre           IndicatorId must be a special indicator
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdateGlobalSpecialIndicatorStates(
  CONST(uint8, AUTOMATIC)  IndicatorId
  );

/* ****************************************************************************
 * Dem_Indicator_UpdateGlobalUserIndicatorForEvent
 *****************************************************************************/
/*!
 * \brief         Updates all global user indicators for an event
 *
 * \details       Updates all global user indicators for an event
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdateGlobalUserIndicatorForEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );


/* ****************************************************************************
 * Dem_Indicator_Init
 *****************************************************************************/
/*!
 * \brief         Initialize indicators.
 *
 * \details       If indicators are configured, initialize all indicator state counters.
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_Init(void);


#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_CalculateGlobalJ1939LampStatus
 *****************************************************************************/
/*!
 * \brief         Calculate the node specific J1939 lamp status and return it.
 *
 * \details       Calculate the node specific J1939 lamp status based on red stop lamp,
 *                amber warning lamp, malfunction indicator lamp and the protect lamp.
 *
 * \param[in]     NodeId
 *                The node Id.
 * \return        The node specific J1939 lamp status.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_J1939DcmLampStatusType, DEM_CODE)
Dem_Indicator_CalculateGlobalJ1939LampStatus(
  CONST(uint8, AUTOMATIC)  NodeId
);
#endif

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_CalculateEventJ1939LampStatus
 *****************************************************************************/
/*!
 * \brief         Calculate the event specific J1939 lamp status.
 *
 * \details       Calculate the event specific J1939 lamp status if the event 
 *                is configured for the requested NodeId.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     NodeId
 *                The node Id.
 * \param[out]    FilterResult
 *                Pointer to receive the next matching event.
 *                FilterResult->LampStatus : 
 *                              The lamp status of the matching event.
 *                Ignore other member of FilterResult
 *
 * \return        E_OK
 *                Event is configured for the requested node identifier.
 *                DEM_NO_SUCH_ELEMENT
 *                Event is not configured for the requested node identifier.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939_DM31 == STD_ON or
 *                DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) 
Dem_Indicator_CalculateEventJ1939LampStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  NodeId,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
);
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_INDICATOR_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Indicator_Interface.h
 *********************************************************************************************************************/
