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
 *  \defgroup   Dem_APIChecks APIChecks
 *  \{
 *  \file       Dem_APIChecks_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of all DET checks used in API sub-components.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_APICHECKS_INTERFACE_H)
#define DEM_APICHECKS_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_APIChecks_Types.h"

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
 * \defgroup Dem_APIChecks_Public Public Methods
 * \{
 */
 /* ****************************************************************************
 * Dem_APIChecks_SatelliteInState
 *****************************************************************************/
 /*!
 * \brief         Test if the Dem Satellite is in the given state
 *
 * \details       Test if the Dem Satellite is in the given state
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 * \param[in]     InitState
 *                The initialization state
 *
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 *
 * \pre           Developement error detection enabled
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_SatelliteInState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(uint8, AUTOMATIC) InitState
);

 /* ****************************************************************************
 * Dem_APIChecks_MasterInState
 *****************************************************************************/
 /*!
 * \brief         Test if the Dem is in the given state
 *
 * \details       Test if the Dem is in the given state if developement
 *                error detection is on.
 *
 * \param[in]     InitState
 *                The initialization state
 *
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_MasterInState(
  CONST(uint8, AUTOMATIC) InitState
);

/* ****************************************************************************
 * Dem_APIChecks_GlobalConfigPointerInState
 *****************************************************************************/
/*!
 * \brief         Test if the Global Config Pointer is in the given state
 *
 * \details       Test if the Global Config Pointer is in the given state 
 *                if developement error detection is on.
 *
 * \param[in]     InitState
 *                The initialization state
 *
 * \return        TRUE
 *                Error Detection is disabled or pointer is in given state
 * \return        FALSE
 *                Pointer is not in given state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_GlobalConfigPointerInState(
  CONST(uint8, AUTOMATIC) InitState
);

/* ****************************************************************************
 * Dem_APIChecks_GlobalConfigPointerAtleastInState
 *****************************************************************************/
/*!
 * \brief         Test if the Global Config Pointer is atleast in the given state
 *
 * \details       Test if the Global Config Pointer is atleast in the given state 
 *                if developement error detection is on.
 *
 * \param[in]     InitState
 *                The initialization state
 *
 * \return        TRUE
 *                Error Detection is disabled or pointer is ate least in given state
 * \return        FALSE
 *                Pointer is not at least in given state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_GlobalConfigPointerAtleastInState(
  CONST(uint8, AUTOMATIC) InitState
);

/* ****************************************************************************
 * Dem_APIChecks_MasterNotInState
 *****************************************************************************/
/*!
 * \brief         Test if the Dem is not in the given state
 *
 * \details       Test if the Dem is not in the given state if developement
 *                error detection is on.
 *
 * \param[in]     InitState
 *                The initialization state
 *
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_MasterNotInState(
  CONST(uint8, AUTOMATIC) InitState
);


/* ****************************************************************************
 * Dem_APIChecks_MasterAtLeastInState
 *****************************************************************************/
/*!
 * \brief         Test if the Dem is at least in the given state
 *
 * \details       Test if the Dem is at least in the given state if developement
 *                error detection is on.
 *
 * \param[in]     InitState
 *                The initialization state
 *
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_MasterAtLeastInState(
  CONST(uint8, AUTOMATIC) InitState
);

/* ****************************************************************************
 * Dem_APIChecks_SatelliteAtLeastInState
 *****************************************************************************/
/*!
 * \brief         Test if the Dem is at least in the given state
 *
 * \details       Test if the Dem is at least in the given state if developement
 *                error detection is on.
 *
 * \param[in]     InitState
 *                The initialization state
 *
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_SatelliteAtLeastInState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(uint8, AUTOMATIC) InitState
);

/* ****************************************************************************
 * Dem_APIChecks_SingleSatellite
 *****************************************************************************/
/*!
 * \brief         Check that only one satellite is configured.
 *
 * \details       Check that only one satellite is configured if developement
 *                error detection is on.
 *
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_SingleSatellite(
  void
);

/* ****************************************************************************
 * Dem_APIChecks_IsBoolean
 *****************************************************************************/
/*!
 * \brief         Check that passed parameter matches definition of type boolean
 *
 * \details       Check that passed parameter matches definition of type boolean
 *                if developement error detection is on.
 * \param[in]     Paramter
 *                An abitrary boolean parameter
 *
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsBoolean(
  boolean  Parameter
  );
 
/* ****************************************************************************
 * Dem_APIChecks_IsBoolean
 *****************************************************************************/
/*!
 * \brief         Check that current partition is master partition
 *
 * \details       Check that current partition is master partition if developement
 *                error detection is on.
 *
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsMasterPartition(
  void
  );

/* ****************************************************************************
 * Dem_APIChecks_DebounceCounterNvConditions
 *****************************************************************************/
/*!
 * \brief         Test that preconditions for status reports are fulfilled 
 *                if debounce counters are stored non-volatile.
 *
 * \details       Test that preconditions for status reports are fulfilled 
 *                if debounce counters are stored non-volatile anf if developement
 *                error detection is on.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_DebounceCounterNvConditions(
  Dem_EventIdType  EventId
);

 /* ****************************************************************************
 * Dem_APIChecks_ReportedSimilarConditions
 *****************************************************************************/
 /*!
 * \brief         Test if the passed status is valid.
 *
 * \details       Test That the passed status is not a similar condition status or
 *                that a similar condition status is supported by the passed event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     Monitor result reported for the Event.
 *
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_ReportedSimilarConditions(
  Dem_EventIdType  EventId,
  Dem_EventStatusType EventStatus
);

 /* ****************************************************************************
 * Dem_APIChecks_EventId
 *****************************************************************************/
 /*!
 * \brief         Test if the passed event id is in valid range.
 *
 * \details       Test if the passed event id is in valid range if developement
 *                 error detection is on.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_EventId(
  Dem_EventIdType EventId
);

/* ****************************************************************************
 * Dem_APIChecks_ClientId
 *****************************************************************************/
/*!
 * \brief         Test if the passed client id is in valid range.
 *
 * \details       Test if the passed client id is in valid range if developement
 *                error detection is on.
 *
 * \param[in]     ClientId
 *                Unique handle of the Client.
 *                The EventId must be in range 
 *                [1..Dem_Client_ClientAccess_GlobalClientCount()[.
 *
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_ClientId(
  uint8  ClientId
);

/* ****************************************************************************
 * Dem_APIChecks_NullPointer
 *****************************************************************************/
/*!
 * \brief         Test that the passed pointer is not 'null pointer'.
 *
 * \details       Test that the passed pointer is not 'null pointer'if developement
 *                error detection is on.
 *
 * \param[in]     ExternalPtr
 *                An abitrary external pointer.
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_NullPointer(
  CONSTP2CONST(void, AUTOMATIC, DEM_SHARED_DATA)  ExternalPtr
  );

 /* ****************************************************************************
 * Dem_APIChecks_EventApplicationId
 *****************************************************************************/
 /*!
 * \brief         Check whether the event can be processed in the current
 *                execution context
 *
 * \details       Checks whether the given event is configured to be processed
 *                on the current OS application. In single partition
 *                configurations, this is always the case.
 *
 * \param[in]     EventId
 *                Global Event Id
 *
 * \return        TRUE
 *                The event can be processed
 * \return        FALSE
 *                The event belongs to a different OS application
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_EventApplicationId(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
);

 /* ****************************************************************************
 * Dem_APIChecks_ReportedStatus
 *****************************************************************************/
 /*!
 * \brief         Test if the passed status is valid.
 *
 * \details       Test if the passed status is valid if developement
 *                error detection is on.
 *
 * \param[in]     Monitor result reported for the Event.
 *
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_ReportedStatus(
  Dem_EventStatusType EventStatus
);



/* ****************************************************************************
 * Dem_APIChecks_IsIUMPRRatioIDValid
 *****************************************************************************/
/*!
 * \brief         Test if the passed ratio index is valid.
 *
 * \details       Test if the passed ratio index is valid. if developement
 *                error detection is on.
 *
 * \param[in]     RatioID
 *                Unique handle of the Ratio, which is equal to the EventId
 *                associated with the Ratio.
 *
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsIUMPRRatioIDValid(
  Dem_RatioIdType  RatioID
);

/* ****************************************************************************
 * Dem_APIChecks_IsRatioIDOfApiType
 *****************************************************************************/
/*!
 * \brief         Test if the passed ratio is of api type
 *
 * \details       Test if the passed ratio is of api type if developement
 *                error detection is on.
 *
 * \param[in]     RatioID
 *                Unique handle of the Ratio, which is equal to the EventId
 *                associated with the Ratio.
 *
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsRatioIDOfApiType(
  Dem_RatioIdType  RatioID
);

/* ****************************************************************************
 * Dem_APIChecks_IsRatioDenominatorLockable
 *****************************************************************************/
/*!
 * \brief         Test if the passed ratio denominator is allowed to be locked.
 *
 * \details       Test if the passed ratio denominator is allowed to be locked.
 *                If developement error detection is on.
 *
 * \param[in]     RatioID
 *                Unique handle of the Ratio, which is equal to the EventId
 *                associated with the Ratio.
 *
 * \return        TRUE
 *                No error detected
 * \return        FALSE
 *                Error detected
 *
 * \pre           RatioIndex is valid.
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsRatioDenominatorLockable(
  Dem_RatioIdType  RatioID
);

/* ****************************************************************************
 * Dem_APIChecks_IsObdSupportedInVariant
 *****************************************************************************/
/*!
 * \brief         Check whether any OBD version is supported in the current variant
 *
 * \details       Checks whether any OBD version is is supported in the current variant.
 *                In non PBS configurations the general OBD support is checked.
 *
 *
 * \return        TRUE
 *                An OBD version is supported
 * \return        FALSE
 *                No OBD Version is supported
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsObdSupportedInVariant(
  void
);

/* ****************************************************************************
 * Dem_APIChecks_IsObdIISupportedInVariant
 *****************************************************************************/
/*!
 * \brief         Check whether OBDII is supported in the current variant
 *
 * \details       Checks whether OBDII is supported in the current variant.
 *                In non PBS configurations the general OBDII support is checked.
 *
 *
 * \return        TRUE
 *                OBDII is supported
 * \return        FALSE
 *                OBDII is not supported
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsObdIISupportedInVariant(
  void
);

/* ****************************************************************************
 * Dem_APIChecks_IsWwhObdSupportedInVariant
 *****************************************************************************/
/*!
 * \brief         Check whether WWHOBD is supported in the current variant
 *
 * \details       Checks whether WWHOBD is supported in the current variant.
 *                In non PBS configurations the general WWHOBD support is checked.
 *
 *
 * \return        TRUE
 *                WWHOBD is supported
 * \return        FALSE
 *                WWHOBD is not supported
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsWwhObdSupportedInVariant(
  void
);


/* ****************************************************************************
 * Dem_APIChecks_IsService19_16Enabled
 *****************************************************************************/
/*!
 * \brief         Check whether Service 0x19 Subfunction 0x16 is supported
 *
 * \details       Check whether Service 0x19 Subfunction 0x16 is supported
 *
 *
 * \return        TRUE
 *                Service API supports provided DTC origin
 * \return        FALSE
 *                Service API does not support provided DTC origin
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsService19_16Enabled(
  void
);

/* ****************************************************************************
 * Dem_APIChecks_IsExtendedDataRecordFilterValid
 *****************************************************************************/
/*!
 * \brief         Checks whether the ClientId maps to an extended data record filter.
 *
 * \details       Checks whether the ClientId maps to an extended data record filter.
 *
 * \param[in]     ClientId
 *                Unique handle of the Client.
 *                The EventId must be in range 
 *                [1..Dem_Client_ClientAccess_GlobalClientCount()[.
 *
 * \return        TRUE
 *                Service API supports provided DTC origin
 * \return        FALSE
 *                Service API does not support provided DTC origin
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsExtendedDataRecordFilterValid(
  uint8  ClientId
);

/* ****************************************************************************
 * Dem_APIChecks_IsExtendedDataRecordFilterSet
 *****************************************************************************/
/*!
 * \brief         Check whether ERec filter is set
 *
 * \details       Check whether ERec filter is set
 *
 * \param[in]     ClientId
 *                Unique handle of the Client.
 *                The EventId must be in range
 *                [1..Dem_Client_ClientAccess_GlobalClientCount()[.
 *
 * \return        TRUE
 *                ERec filter is set
 * \return        FALSE
 *                ERec filter is invalid
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsExtendedDataRecordFilterSet(
  uint8  ClientId
);

/* ****************************************************************************
 * Dem_APIChecks_IsDTCOriginSupportedFor0x1916
 *****************************************************************************/
/*!
 * \brief         Check whether Service 0x19 Subfunction 0x16 supports
 *                the origin.
 *
 * \details       Check whether Service 0x19 Subfunction 0x16 supports
 *                the origin.
 *
 * \param[in]     DTCOrigin
 *                The external identifier of the event memory
 *
 * \return        TRUE
 *                Service API supports provided DTC origin
 * \return        FALSE
 *                Service API does not support provided DTC origin
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsDTCOriginSupportedFor0x1916(
  Dem_DTCOriginType  DTCOrigin
);

/* ****************************************************************************
 * Dem_APIChecks_IsDTCFormatSupported
 *****************************************************************************/
/*!
 * \brief         Check whether Service supports the DTC format.
 *
 * \details       Check whether Service supports the DTC format.
 *
 * \param[in]     DTCFormat
 *                The requested DTC format
 *
 * \return        TRUE
 *                Service API supports provided DTC format
 * \return        FALSE
 *                Service API does not support provided DTC format
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsDTCFormatSupported(
  Dem_DTCFormatType  DTCFormat
);

/* ****************************************************************************
 * Dem_APIChecks_IsDTCFormatSupportedFor0x1916
 *****************************************************************************/
/*!
 * \brief         Check whether Service 0x19 Subfunction 0x16 supports
 *                the DTC format.
 *
 * \details       Check whether Service 0x19 Subfunction 0x16 supports
 *                the DTC format.
 *
 * \param[in]     DTCFormat
 *                The requested DTC format
 *
 * \return        TRUE
 *                Service API supports provided DTC format
 * \return        FALSE
 *                Service API does not support provided DTC format
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsDTCFormatSupportedFor0x1916(
  Dem_DTCFormatType  DTCFormat
);

/* ****************************************************************************
 * Dem_APIChecks_IsService19_56Enabled
 *****************************************************************************/
/*!
 * \brief         Check whether Service 0x19 Subfunction 0x56 is supported
 *
 * \details       Check whether Service 0x19 Subfunction 0x56 is supported
 *
 *
 * \return        TRUE
 *                Service API supports provided DTC origin
 * \return        FALSE
 *                Service API does not support provided DTC origin
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsService19_56Enabled(
  void
);

/* ****************************************************************************
 * Dem_ApiChecks_TestReadinessGroupValid
 *****************************************************************************/
/*!
 * \brief         Checks whether a readiness group is valid.
 *
 * \details       Checks whether a readiness group is valid.
 *
 * \param[in]     ReadinessGroup
 *                Readiness group number
 *
 * \return        TRUE
 *                The readiness group is valid
 * \return        FALSE
 *                The readiness group is invalid
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ApiChecks_TestReadinessGroupValid(
  Dem_EventOBDReadinessGroupType ReadinessGroup
);

/* ****************************************************************************
 * Dem_ApiChecks_TestDTCFilterValid
 *****************************************************************************/
/*!
 * \brief         Checks whether thr provided client has a valid DTC filter.
 *
 * \details       Checks whether thr provided client has a valid DTC filter.
 *
 * \param[in]     ClientId
 *                Unique handle of the Client.
 *                The EventId must be in range
 *                [1..Dem_Client_ClientAccess_GlobalClientCount()[.
 *
 * \return        TRUE
 *                The DTC filter is valid
 * \return        FALSE
 *                The DTC filter is invalid
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ApiChecks_TestDTCFilterValid(
  uint8 ClientId
);

/* ****************************************************************************
 * Dem_APIChecks_IsExtendedFiMEnabled
 *****************************************************************************/
/*!
 * \brief         Check whether Extended FiM feature is supported
 *
 * \details       Check whether Extended FiM feature is supported
 *
 *
 * \return        TRUE
 *                Extended FiM feature is enabled
 * \return        FALSE
 *                Extended FiM feature is NOT enabled
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsExtendedFiMEnabled(
  void
);

/* ****************************************************************************
 * Dem_APIChecks_IsCounterDebounce
 *****************************************************************************/
/*!
 * \brief         Check whether the debounce algorithm of the event is
 *                counter based
 *
 * \details       Check whether the debounce algorithm of the event is
 *                counter based
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                Debounce algorithm is counter based
 * \return        FALSE
 *                Debounce algorithm is NOT counter based
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsCounterDebounce(
  Dem_EventIdType EventId
);

/* ****************************************************************************
 * Dem_APIChecks_IsService19_1AEnabled
 *****************************************************************************/
/*!
 * \brief         Check whether Service 0x19 Subfunction 0x1A is supported
 *
 * \details       Check whether Service 0x19 Subfunction 0x1A is supported
 *
 *
 * \return        TRUE
 *                Service API supports provided DTC origin
 * \return        FALSE
 *                Service API does not support provided DTC origin
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_APIChecks_IsService19_1AEnabled(
  void
);

/* ****************************************************************************
 * Dem_ApiChecks_TestReadinessGroupValid
 *****************************************************************************/
/*!
 * \brief         Checks whether a extended data record number is valid.
 *
 * \details       Checks whether a extended data record number is valid.
 *
 * \param[in]     ExtendedDataRecordNumber
 *                Number of the extended data record
 *
 * \return        TRUE
 *                The extended data record number is valid
 * \return        FALSE
 *                The extended data record number is invalid
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ApiChecks_TestExtendedDataRecordNumberValid(
  uint8 ExtendedDataRecordNumber
);

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_APICHECKS_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_APIChecks_Interface.h
 *********************************************************************************************************************/
