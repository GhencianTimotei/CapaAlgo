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
/*!
 *  \addtogroup Dem_SatelliteIF
 *  \{
 *  \file       Dem_SatelliteIF_Implementation.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Implementation of SatelliteIF subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_SATELLITEIF_IMPLEMENTATION_H)                                                                                    /* PRQA S 0883 */ /* MD_DEM_19.15 */
#define DEM_SATELLITEIF_IMPLEMENTATION_H

/* ********************************************************************************************************************
 *  GLOBAL MISRA JUSTIFICATIONS
 *********************************************************************************************************************/
/* PRQA S 2880 EOF */ /* MD_DEM_2.1_UNREACHABLE_STATEMENT */
/* PRQA S 2982 EOF */ /* MD_DEM_2982 */
/* PRQA S 2983 EOF */ /* MD_DEM_2983 */
/* PRQA S 2985 EOF */ /* MD_DEM_2985 */
/* PRQA S 2986 EOF */ /* MD_DEM_2986 */
/* PRQA S 2987 EOF */ /* MD_DEM_2987 */
/* PRQA S 2991 EOF */ /* MD_DEM_2991 */
/* PRQA S 2992 EOF */ /* MD_DEM_2992 */
/* PRQA S 2995 EOF */ /* MD_DEM_2995 */
/* PRQA S 2996 EOF */ /* MD_DEM_2996 */
/* PRQA S 0759 EOF */ /* MD_MSR_Union */

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own LU header */
/* ------------------------------------------------------------------------- */
#include "Dem_SatelliteIF_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_SatelliteData_Interface.h"
#include "Dem_SatelliteInfo_Interface.h"
#include "Dem_Debounce_Interface.h"
#include "Dem_Monitor_Interface.h"

#include "Dem_Infrastructure_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_FaultMemory_Interface.h"
#include "Dem_DiagnosticObserver_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_SATELLITEIF_IMPLEMENTATION_FILENAME "Dem_SatelliteIF_Implementation.h"

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
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * \defgroup Dem_Satellite_PrivateProperties Private Properties
 * \{
 */ 
/* ****************************************************************************
 * Dem_Satellite_GetApplicationId
 *****************************************************************************/
/*!
 * \brief         Get the application Id of a satellite
 *
 * \details       Get the application Id of a satellite
 *
 * \param[in]     SatelliteId
 *                Unique handle of the Satellite.
 *                The SatelliteId must be in range [1..Dem_Cfg_GlobalSatelliteCount()[.
 *
 * \return        The application Id of the given satellite
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Satellite_ApplicationType, DEM_CODE)
Dem_Satellite_GetApplicationId(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId                                                                            /* PRQA S 3206 */ /* MD_DEM_3206 */
  );

/* ****************************************************************************
 * Dem_Satellite_GetCurrentDebounceLoResTimer
 *****************************************************************************/
/*!
 * \brief         Gets low resolution timer for the passed Satellite Id
 *
 * \details       Gets low resolution timer for the passed Satellite Id
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \return        Current value of low-res debounce time in main function 'ticks'
 *
 * \pre           Low resoution timer feature is supported
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Satellite_DebounceLoResTimerType, DEM_CODE)
Dem_Satellite_GetCurrentDebounceLoResTimer(
  Dem_Satellite_IdType  SatelliteId
  );


/* ****************************************************************************
 * Dem_Satellite_SetDebounceLoResTimer
 *****************************************************************************/
/*!
 * \brief         Sets a new low resolution timer for the passed Satellite Id
 *
 * \details       Sets a new low resolution timer for the passed Satellite Id
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 * \param[in]     LoResTimer
 *                New low resolution timer
 *
 * \pre           Low resoution timer feature is supported
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Satellite_SetDebounceLoResTimer(
  Dem_Satellite_IdType SatelliteId,
  Dem_Satellite_DebounceLoResTimerType LoResTimer
  );


/* ****************************************************************************
 * Dem_Satellite_GetDebounceLoResTimeBase
 *****************************************************************************/
/*!
 * \brief         Get the low-res debounce time base
 *
 * \details       Get the low-res debounce time base
 *
 * \return        The low-res debounce time base in main function 'ticks'
 *
 * \pre           Low resolution feature is supported
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Satellite_DebounceLoResTimerType, DEM_CODE)
Dem_Satellite_GetDebounceLoResTimeBase(
  void
  );


/* ****************************************************************************
 * Dem_Satellite_IsMultipleSatellitesEnabled
 *****************************************************************************/
/*!
 * \brief         Function verifies if the PP switch 
 *                DEM_CFG_SUPPORT_MULTIPLE_SATELLITES is enabled.
 *
 * \details       Function verifies if the PP switch 
 *                DEM_CFG_SUPPORT_MULTIPLE_SATELLITES is enabled.
 *
 * \return        TRUE
 *                Feature Multiple Satellites is enabled.
 *                FALSE
 *                Feature Multiple Satellites is not enabled.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_IsMultipleSatellitesEnabled(
  void
  );


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/


/* ****************************************************************************
 % Dem_Satellite_GetApplicationId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Satellite_ApplicationType, DEM_CODE)
Dem_Satellite_GetApplicationId(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId                                                                            /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_Satellite_ApplicationType lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_Cfg_GetApplicationIdOfSatelliteInfo(SatelliteId);

  return lReturnValue;
}


/* ****************************************************************************
 % Dem_Satellite_GetCurrentDebounceLoResTimer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Satellite_DebounceLoResTimerType, DEM_CODE)
Dem_Satellite_GetCurrentDebounceLoResTimer(
  Dem_Satellite_IdType SatelliteId
)
{
  Dem_Satellite_DebounceLoResTimerType lReturnValue;
  Dem_Cfg_DebounceLoResTimerConstPtrType lLowResTimerptr;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lLowResTimerptr = (Dem_Cfg_DebounceLoResTimerConstPtrType)Dem_Cfg_GetDebounceLoResTimerOfSatelliteInfo(SatelliteId);
  if (lLowResTimerptr != NULL_PTR)
  {
    lReturnValue = *lLowResTimerptr;
  }
  else
  {
    lReturnValue = (Dem_Satellite_DebounceLoResTimerType)0;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Satellite_SetDebounceLoResTimer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Satellite_SetDebounceLoResTimer(
  Dem_Satellite_IdType  SatelliteId,
  Dem_Satellite_DebounceLoResTimerType  LoResTimer
  )
{
  if (Dem_SatelliteSat_IsLRTimeDebouncingEnabled() == TRUE)
  {
    Dem_Cfg_DebounceLoResTimerPtrType lLowResTimerptr;

    lLowResTimerptr = (Dem_Cfg_DebounceLoResTimerPtrType)Dem_Cfg_GetDebounceLoResTimerOfSatelliteInfo(SatelliteId);              /* PRQA S 2842, 2843 */ /* MD_DEM_Dir4.1_SatelliteInfoStructPointers, MD_DEM_Dir4.1_SatelliteInfoStructPointers */
    
    /* ----- Runtime Checks ------------------------------------------------ */
    if (Dem_Error_isDevRunTimeChecksEnabled() == TRUE)                                                                           
    {
      if ( (SatelliteId >= Dem_Cfg_GetSizeOfSatelliteInfo())
        || (lLowResTimerptr == NULL_PTR))
      {
        Dem_Error_RunTimeCheckFailed(DEM_SATELLITEIF_IMPLEMENTATION_FILENAME, __LINE__);                                           /* SBSW_DEM_POINTER_RUNTIME_CHECK */
      }
      else
      {
        *lLowResTimerptr = LoResTimer;                                                                                           /* SBSW_DEM_WRITE_SATELLITEINFO_OPTIONAL_MEMBER */
      }
    }
    else
    {
      *lLowResTimerptr = LoResTimer;                                                                                             /* SBSW_DEM_WRITE_SATELLITEINFO_OPTIONAL_MEMBER */
    }
  }
}

/* ****************************************************************************
 % Dem_Satellite_GetDebounceLoResTimeBase
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Satellite_DebounceLoResTimerType, DEM_CODE)
Dem_Satellite_GetDebounceLoResTimeBase(
  void
)
{
  return DEM_CFG_DEBOUNCE_LO_RES_TIMER_VALUE;
}


/* ****************************************************************************
 % Dem_Satellite_IsMultipleSatellitesEnabled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_IsMultipleSatellitesEnabled(
  void
  )
{
  return (boolean)(DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON);
}
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_Satellite_PublicProperties
 * \{
 */
 /* ****************************************************************************
 % Dem_SatelliteSat_IsHRTimeDebouncingEnabled
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteSat_IsHRTimeDebouncingEnabled(
  void
)
{
  return (boolean)(DEM_CFG_SUPPORT_DEBOUNCE_TIME_HR == STD_ON);
}

/* ****************************************************************************
 % Dem_SatelliteSat_IsLRTimeDebouncingEnabled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteSat_IsLRTimeDebouncingEnabled(
  void
)
{
  return (boolean)(DEM_CFG_SUPPORT_DEBOUNCE_TIME_LR == STD_ON);
}

/* ****************************************************************************
 % Dem_Satellite_GetEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Satellite_GetEventId(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetEventTableInd(Dem_Cfg_GetEventTableIndStartIdxOfSatelliteInfo(SatelliteId) + MonitorId);
}

/* ****************************************************************************
 % Dem_Satellite_CheckEventApplicationId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_CheckEventApplicationId(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  boolean lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

  if (Dem_Satellite_IsMultipleSatellitesEnabled() == TRUE)
  {
    lReturnValue = (boolean)(Dem_ExtCom_GetCurrentApplicationId() == Dem_Satellite_GetApplicationId(Dem_Cfg_GetSatelliteInfoIdxOfEventTable(EventId)));
  }
  else
  {
    lReturnValue = TRUE;
  }

  return lReturnValue;
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Satellite_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_SatelliteSat_SetStatusIndicatorSymptomActionQueue
 *****************************************************************************/
/*!
 * \brief         Queue the StatusIndicator symptom requested operation 
 *                for an event.
 *
 * \details       Queue the StatusIndicator symptom requested operation for 
 *                an event in the Satellite shared buffers.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \pre           Function should only be invoked when the feature "Support
 *                Extended FiM" is enabled.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetStatusIndicatorSymptomActionQueue(
  Dem_Satellite_IdType SatelliteId,
  Dem_Satellite_MonitorIdType MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteSat_SetStatusIndicatorQueueUpdated
 *****************************************************************************/
/*!
 * \brief         Sets the StatusIndicator queue updated flag for the given 
 *                satellite.
 *
 * \details       Sets the StatusIndicator queue updated flag for the given 
 *                satellite.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event.
 *
 * \pre           Function should only be invoked when the feature "Support
 *                Extended FiM" is enabled.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetStatusIndicatorQueueUpdated(
  Dem_Satellite_IdType SatelliteId
  );

/* ****************************************************************************
 * Dem_Satellite_DecrementAndTestLoResTimerElapsed
 *****************************************************************************/
/*!
 * \brief         Decrement low resolution tick timer and return if the
 *                timer is elapsed.
 *
 * \details       Decrement low resolution tick timer by one tick and return if the
 *                timer is elapsed.
 *
 * \return        TRUE
 *                Feature is supported
 * \return        FALSE
 *                Feature is not supported
 *
 * \pre           Low resolution debouncing feature is supported.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different satellite Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_DecrementAndTestLoResTimerElapsed(
  Dem_Satellite_IdType  SatelliteId
  );

 
/* ****************************************************************************
 * Dem_Satellite_DebounceHiResIterExists
 *****************************************************************************/
 /*!
 * \brief         Test if the iterator points to a valid element
 *
 * \details       Test if the iterator points to a valid element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        TRUE
 *                Dem_Satellite_DebounceHiResIterGet() will return a valid element
 *                on this iterator
 * \return        FALSE
 *                Dem_Satellite_DebounceHiResIterGet() is undefined on this iterator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_DebounceHiResIterExists(
  CONSTP2CONST(Dem_Satellite_DebounceHiResIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  );


/* ****************************************************************************
 * Dem_Satellite_DebounceHiResIterGet
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator
 *
 * \details       Get the element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        An EventId using time based debouncing with the high resolution
 *                timer
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Satellite_DebounceHiResIterGet(
  CONSTP2CONST(Dem_Satellite_DebounceHiResIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  );


/* ****************************************************************************
 * Dem_Satellite_DebounceHiResIterInit
 *****************************************************************************/
/*!
 * \brief         Initializes the iterator for the satellite Id
 *
 * \details       Initializes the iterator to enumerate all EventIds assigned
 *                to the satellite and using hi-res time based debouncing.
 *                Invalidate iterator if hi-res time based debouncing is not supported.
 *
 * \param[in]     SatelliteId
 *                Unique handle of the Satellite.
 *                The SatelliteId must be in range [1..Dem_Cfg_GlobalSatelliteCount()[.
 *
 * \param[out]    IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Satellite_DebounceHiResIterInit(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONSTP2VAR(Dem_Satellite_DebounceHiResIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  );


/* ****************************************************************************
 * Dem_Satellite_DebounceHiResIterNext
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next element
 *
 * \details       Move the iterator to the next element
 *
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Satellite_DebounceHiResIterNext(
  CONSTP2VAR(Dem_Satellite_DebounceHiResIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  );


/* ****************************************************************************
 * Dem_Satellite_DebounceLoResIterExists
 *****************************************************************************/
/*!
 * \brief         Test if the iterator points to a valid element
 *
 * \details       Test if the iterator points to a valid element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        TRUE
 *                Dem_Satellite_DebounceLoResIterGet() will return a valid element
 *                on this iterator
 * \return        FALSE
 *                Dem_Satellite_DebounceLoResIterGet() is undefined on this iterator
 *
 * \pre           Low resolution debouncing feature is supported.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_DebounceLoResIterExists(
  CONSTP2CONST(Dem_Satellite_DebounceLoResIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  );


/* ****************************************************************************
 * Dem_Satellite_DebounceLoResIterGet
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator
 *
 * \details       Get the element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        An EventId using time based debouncing with the low resolution
 *                timer
 *
 * \pre           Low resolution debouncing feature is supported and 
 *                IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Satellite_DebounceLoResIterGet(
  CONSTP2CONST(Dem_Satellite_DebounceLoResIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  );


/* ****************************************************************************
 * Dem_Satellite_DebounceLoResIterInit
 *****************************************************************************/
/*!
 * \brief         Init the iterator for the satellite Id
 *
 * \details       Initializes the iterator to enumerate all EventIds assigned
 *                to this satellite and using lo-res time based debouncing
 *
 * \param[in]     SatelliteId
 *                Unique handle of the Satellite.
 *                The SatelliteId must be in range [1..Dem_Cfg_GlobalSatelliteCount()[.
 *
 * \param[out]    IterPtr
 *                Pointer to the iterator
 *
 * \pre           Low resolution debouncing feature is supported.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Satellite_DebounceLoResIterInit(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONSTP2VAR(Dem_Satellite_DebounceLoResIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  );


/* ****************************************************************************
 * Dem_Satellite_DebounceLoResIterNext
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next element
 *
 * \details       Move the iterator to the next element
 *
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           Low resolution debouncing feature is supported
 *                IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Satellite_DebounceLoResIterNext(
  CONSTP2VAR(Dem_Satellite_DebounceLoResIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  );


/* ****************************************************************************
 * Dem_Satellite_GetSatelliteInfo
 *****************************************************************************/
/*!
 * \brief         Reads the satellite status of the given satellite.
 *
 * \details       Reads the satellite status of the given satellite.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \return        The satellite status of the satellite
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_Satellite_GetSatelliteInfo(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );


/* ****************************************************************************
 * Dem_SatelliteSat_SetSatelliteInfo
 *****************************************************************************/
/*!
 * \brief         Writes the satellite status of the given satellite.
 *
 * \details       Writes the satellite status of the given satellite.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \param[in]     NewSatelliteInfo
 *                The modified data to write
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetSatelliteInfo(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  NewSatelliteInfo
  );


/* ****************************************************************************
 * Dem_SatelliteSat_SyncSetSatelliteInfo
 *****************************************************************************/
/*!
 * \brief         Writes the satellite status of the given satellite.
 *
 * \details       Write is only performed, if the current data content is
 *                identical to the the given parameter 'OldSatelliteInfo'.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \param[in]     OldSatelliteInfo
 *                The data before modification
 *                (returned by Dem_Satellite_GetSatelliteInfo()).
 *
 * \param[in]     NewSatelliteInfo
 *                The modified data to write.
 *
 * \return        TRUE
 *                Satellite status was successfully written
 * \return        FALSE
 *                Satellite status could not be written due to modification
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteSat_SyncSetSatelliteInfo(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC) OldSatelliteInfo,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC) NewSatelliteInfo
  );


/* ****************************************************************************
 * Dem_SatelliteCore_SyncSetSatelliteInfo
 *****************************************************************************/
/*!
 * \brief         Writes the satellite status.
 *
 * \details       Write is only performed, if the current data content is
 *                identical to the the given parameter 'OldSatelliteInfo'.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \param[in]     OldSatelliteInfo
 *                The data before modification
 *                (returned by Dem_Satellite_GetSatelliteInfo()).
 *
 * \param[in]     NewSatelliteInfo
 *                The modified data to write.
 *
 * \return        TRUE
 *                Satellite status was successfully written
 * \return        FALSE
 *                Satellite status could not be written due to modification
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteCore_SyncSetSatelliteInfo(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC) OldSatelliteInfo,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC) NewSatelliteInfo
  );


/* ****************************************************************************
 * Dem_Satellite_GetSatelliteData
 *****************************************************************************/
/*!
 * \brief         Reads the satellite data of the given event.
 *
 * \details       Reads the satellite data of the given event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The satellite data of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Satellite_GetSatelliteData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );


/* ****************************************************************************
 * Dem_Satellite_GetSatelliteExtendedData
 *****************************************************************************/
/*!
 * \brief         Reads the satellite extended data of the given event.
 *
 * \details       Reads the satellite extended data of the given event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The satellite extended data of the event
 *
 * \pre           Function should only be invoked when features "Prestorage of 
 *                freeze frames" and "Multiple Satellites" are supported
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_ExtendedDataType, DEM_CODE)
Dem_Satellite_GetSatelliteExtendedData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );


/* ****************************************************************************
 * Dem_SatelliteSat_SetSatelliteData
 *****************************************************************************/
/*!
 * \brief         Writes the satellite data of the given event.
 *
 * \details       Writes the satellite data of the given event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \param[in]     NewSatelliteData
 *                The modified data to write
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetSatelliteData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  );


/* ****************************************************************************
 * Dem_SatelliteSat_SetSatelliteExtendedData
 *****************************************************************************/
/*!
 * \brief         Writes the satellite extended data of the given event.
 *
 * \details       Writes the satellite extended data of the given event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \param[in]     NewSatelliteExtendedData
 *                The modified data to write
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetSatelliteExtendedData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  NewSatelliteExtendedData
  );
  
/* ****************************************************************************
 * Dem_SatelliteSat_SyncSetSatelliteData
 *****************************************************************************/
/*!
 * \brief         Tries to write the satellite data of the given event to the
 *                communication buffer.
 *
 * \details       Write is only performed, if the current communication buffer
 *                content is identical to the the given parameter
 *                'OldSatelliteData'.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id whose data is updated
 *
 * \param[in]     OldSatelliteData
 *                The data before modification
 *                (returned by Dem_Satellite_GetSatelliteData()).
 *
 * \param[in]     NewSatelliteData
 *                The modified data to write.
 *
 * \return        TRUE
 *                Either Satellite data was successfully written
 *                Or MonitorId / SatelliteId are out of bounds to avoid
 *                endless loops
 * \return        FALSE
 *                Satellite data could not be written due to modification
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteSat_SyncSetSatelliteData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  );


/* ****************************************************************************
 * Dem_SatelliteSat_SyncSetSatelliteExtendedData
 *****************************************************************************/
/*!
 * \brief         Tries to write the satellite extended data of the given event to the
 *                communication buffer.
 *
 * \details       Write is only performed, if the current communication buffer
 *                content is identical to the the given parameter
 *                'OldSatelliteExtendedData'.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id whose data is updated
 *
 * \param[in]     OldSatelliteExtendedData
 *                The data before modification
 *                (returned by Dem_Satellite_GetSatelliteData()).
 *
 * \param[in]     NewSatelliteExtendedData
 *                The modified data to write.
 *
 * \return        TRUE
 *                Either Satellite extended data was successfully written
 *                Or MonitorId / SatelliteId are out of bounds to avoid
 *                endless loops
 * \return        FALSE
 *                Satellite extended data could not be written due to modification
 *
 * \pre           Function should only be invoked when features "Prestorage of 
 *                freeze frames" and "multiple satellites" are supported.
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteSat_SyncSetSatelliteExtendedData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  OldSatelliteExtendedData,
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  NewSatelliteExtendedData
  );


/* ****************************************************************************
 * Dem_SatelliteCore_SyncSetSatelliteData
 *****************************************************************************/
/*!
 * \brief         Tries to write the satellite data of the given event to the
 *                communication buffer.
 *
 * \details       Write is only performed, if the current communication buffer
 *                content is identical to the the given parameter
 *                'OldSatelliteData'.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id whose data is updated
 *
 * \param[in]     OldSatelliteData
 *                The data before modification
 *                (returned by Dem_Satellite_GetSatelliteData()).
 *
 * \param[in]     NewSatelliteData
 *                The modified data to write.
 *
 * \return        TRUE
 *                Either Satellite data was successfully written
 *                Or MonitorId / SatelliteId are out of bounds to avoid
 *                endless loops
 * \return        FALSE
 *                Satellite data could not be written due to modification
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteCore_SyncSetSatelliteData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  );


/* ****************************************************************************
 * Dem_SatelliteSat_SetEventQueueUpdated
 *****************************************************************************/
/*!
 * \brief         Sets the event queue update flag of the given satellite.
 *
 * \details       Sets the update flag of the given satellite.
 *
 * \param[in]     SatelliteId
 *                Satellite Index
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetEventQueueUpdated(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );


/* ****************************************************************************
 * Dem_Satellite_TestSimilarConditionsChanged
 *****************************************************************************/
/*!
 * \brief         Test if reported similar conditions differs from current state.
 *
 * \details       Test if reported similar conditions differs from current state.
 *
 * \param[in]     OldSatelliteData
 *                Satellite data before the update
 * \param[in]     NewSatelliteData
 *                Satellite data after the update
 *
 * \return        TRUE
 *                Similar condition changed.
 * \return        FALSE
 *                Similar condition did not changed.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_TestSimilarConditionsChanged(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  );


/* ****************************************************************************
 * Dem_SatelliteSat_SetInitState
 *****************************************************************************/
/*!
 * \brief         Set the initialization state of the Satellite.
 *
 * \details       Set the initialization state of the Satellite.
 *
 * \param[in]     SatelliteId
 *                Satellite Index
 * \param[in]     InitState
 *                The initialization state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetInitState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(uint8, AUTOMATIC) InitState
  );


/* ****************************************************************************
 * Dem_Satellite_TestMonitorQualificationNeeded
 *****************************************************************************/
/*!
 * \brief         Test whether a monitor qualification is needed.
 *
 * \details       Test whether a monitor qualification is needed.
 *
 * \param[in]     OldSatelliteData
 *                Satellite data before the update
 * \param[in]     NewSatelliteData
 *                Satellite data after update
 * \param[in]     DebounceInfoPtr
 *                The debounce object to read from.
 *
 * \return        TRUE
 *                Monitor qualification needed
 * \return        FALSE
 *                Monitor qualification not needed
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_TestMonitorQualificationNeeded(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData,
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  );


/* ****************************************************************************
 * Dem_Satellite_UpdateSatelliteData
 *****************************************************************************/
/*!
 * \brief         Update the queue state of an event
 *
 * \details       Update the queue state of an event based on the reported
 *                change stored in the given debounce object.
 *
 * \param[in]     OldSatelliteData
 *                The current satellite data
 * \param[in]     DebounceInfoPtr
 *                The debounce object to read from.
 *
 * \return        SatelliteData with the changes applied
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Satellite_UpdateSatelliteData(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );


/* ****************************************************************************
 * Dem_Satellite_UpdateSimilarConditions
 *****************************************************************************/
/*!
 * \brief         Update the similar condition state of an event
 *
 * \details       Update the similar condition state of an event
 *
 * \param[in]     OldSatelliteData
 *                The current satellite data
 * \param[in]     MonitorTrigger
 *                The monitor result
 *
 * \return        SatelliteData with the changes applied
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Satellite_UpdateSimilarConditions(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_EventStatusType, AUTOMATIC)         MonitorTrigger
  );


/* ****************************************************************************
 * Dem_Satellite_TestQueueStatusUpdated
 *****************************************************************************/
/*!
 * \brief         Test whether a new queue entry was created
 *
 * \details       Test whether a new queue entry was created
 *
 * \param[in]     OldSatelliteData
 *                Satellite data before the update
 * \param[in]     NewSatelliteData
 *                Satellite data after the update
 *
 * \return        TRUE
 *                The queue state in the satellite data was created
 * \return        FALSE
 *                The queue state in the satellite data was not changed or an
 *                existing state was updated
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_TestQueueStatusUpdated(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  );


/* ****************************************************************************
 * Dem_SatelliteSat_ProcessTimeBasedDebouncing
 *****************************************************************************/
/*!
 * \brief         Processes the timer based debouncing of an event.
 *
 * \details       Updates the debouncing state and monitor status of the event
 *                using time based debouncing.
 *                Any resulting event processing is deferred to the
 *                context of the Dem task.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \pre           The given SatelliteId is the ID of the caller satellite.
 *                Low res time debouncing is supported.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_ProcessTimeBasedDebouncing(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

 /* ****************************************************************************
 % Dem_Satellite_DebounceHiResIterExists
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_DebounceHiResIterExists(
  CONSTP2CONST(Dem_Satellite_DebounceHiResIterType, AUTOMATIC, AUTOMATIC) IterPtr
)
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}

/* ****************************************************************************
 % Dem_Satellite_DebounceHiResIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Satellite_DebounceHiResIterGet(
  CONSTP2CONST(Dem_Satellite_DebounceHiResIterType, AUTOMATIC, AUTOMATIC) IterPtr
)
{
  Dem_EventIdType lReturnValue;

  lReturnValue = DEM_EVENT_INVALID;

  if (Dem_SatelliteSat_IsHRTimeDebouncingEnabled() == TRUE)
  {
      Dem_Internal_AssertReturnValue(IterPtr->mIdx < Dem_Cfg_GetSizeOfDebounceHiResTable(), DEM_E_INCONSISTENT_STATE, lReturnValue)
      lReturnValue = Dem_Cfg_GetDebounceHiResTable(IterPtr->mIdx);
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Satellite_DebounceHiResIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Satellite_DebounceHiResIterInit(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONSTP2VAR(Dem_Satellite_DebounceHiResIterType, AUTOMATIC, AUTOMATIC) IterPtr
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  if (Dem_SatelliteSat_IsHRTimeDebouncingEnabled() == TRUE)
  {
    IterPtr->mIdx = (uint16_least)Dem_Cfg_GetDebounceHiResTableStartIdxOfSatelliteTimeDebounceInfo(SatelliteId);                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    IterPtr->mEndIdx = (uint16_least)Dem_Cfg_GetDebounceHiResTableEndIdxOfSatelliteTimeDebounceInfo(SatelliteId);               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  else
  {
  IterPtr->mIdx = 0u;                                                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = 0u;                                                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}

/* ****************************************************************************
 % Dem_Satellite_DebounceHiResIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Satellite_DebounceHiResIterNext(
  CONSTP2VAR(Dem_Satellite_DebounceHiResIterType, AUTOMATIC, AUTOMATIC) IterPtr
)
{
  IterPtr->mIdx += 1u;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Satellite_DebounceLoResIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_DebounceLoResIterExists(
  CONSTP2CONST(Dem_Satellite_DebounceLoResIterType, AUTOMATIC, AUTOMATIC) IterPtr
)
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}

/* ****************************************************************************
 % Dem_Satellite_DebounceLoResIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Satellite_DebounceLoResIterGet(
  CONSTP2CONST(Dem_Satellite_DebounceLoResIterType, AUTOMATIC, AUTOMATIC) IterPtr
)
{
  Dem_EventIdType lReturnValue;

  lReturnValue = DEM_EVENT_INVALID;

  if (Dem_SatelliteSat_IsLRTimeDebouncingEnabled() == TRUE)
  {
    Dem_Internal_AssertReturnValue(IterPtr->mIdx < Dem_Cfg_GetSizeOfDebounceLoResTable(), DEM_E_INCONSISTENT_STATE, lReturnValue)
    lReturnValue = Dem_Cfg_GetDebounceLoResTable(IterPtr->mIdx);
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Satellite_DebounceLoResIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Satellite_DebounceLoResIterInit(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONSTP2VAR(Dem_Satellite_DebounceLoResIterType, AUTOMATIC, AUTOMATIC) IterPtr
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */

  if (Dem_SatelliteSat_IsLRTimeDebouncingEnabled() == TRUE)
  {
    IterPtr->mIdx = (uint16_least)Dem_Cfg_GetDebounceLoResTableStartIdxOfSatelliteTimeDebounceInfo(SatelliteId);                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    IterPtr->mEndIdx = (uint16_least)Dem_Cfg_GetDebounceLoResTableEndIdxOfSatelliteTimeDebounceInfo(SatelliteId);                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  else
  {
  IterPtr->mIdx = 0u;                                                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = 0u;                                                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}

/* ****************************************************************************
 % Dem_Satellite_DebounceLoResIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Satellite_DebounceLoResIterNext(
  CONSTP2VAR(Dem_Satellite_DebounceLoResIterType, AUTOMATIC, AUTOMATIC) IterPtr
)
{
  IterPtr->mIdx += 1u;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Satellite_GetSatelliteInfo
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_Satellite_GetSatelliteInfo(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  Dem_SatelliteInfo_Type lReturnValue;                                                                                           /* PRQA S 0759 */ /* MD_MSR_Union */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue.Raw = (Dem_Com_ProcessorWordType) *(Dem_Cfg_GetSatelliteStatusOfSatelliteInfo(SatelliteId));
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteSat_SetSatelliteInfo
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetSatelliteInfo(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  NewSatelliteInfo
  )
{
  if ((Dem_Error_isDevRunTimeChecksEnabled() == TRUE)
    && (SatelliteId >= Dem_Cfg_GetSizeOfSatelliteInfo()))
  {
    Dem_Error_RunTimeCheckFailed(DEM_SATELLITEIF_IMPLEMENTATION_FILENAME, __LINE__);                                               /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
  {
    *Dem_Cfg_GetSatelliteStatusOfSatelliteInfo(SatelliteId) = NewSatelliteInfo.Raw;                                              /* PRQA S 0404 */ /* MD_DEM_13.2_Order_Read_Accesses_Volatile */ /* SBSW_DEM_WRITE_SATELLITEINFO */
  }
}

/* ****************************************************************************
 % Dem_SatelliteSat_SyncSetSatelliteInfo
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteSat_SyncSetSatelliteInfo(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC) OldSatelliteInfo,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC) NewSatelliteInfo
  )
{
  boolean lReturnValue;

  if ( (Dem_Error_isDevRunTimeChecksEnabled() == TRUE)
    && (SatelliteId >= Dem_Cfg_GetSizeOfSatelliteInfo()))                                                                        
  {
    Dem_Error_RunTimeCheckFailed(DEM_SATELLITEIF_IMPLEMENTATION_FILENAME, __LINE__);                                               /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = TRUE;
  }
  else
  {
    lReturnValue = Dem_Com_SyncCompareAndSwap(                                                                                   /* PRQA S 0404 */ /* MD_DEM_13.2_Order_Read_Accesses_Volatile */ /* SBSW_DEM_CALL_SYNC_COMPARE_AND_SWAP_SATELLITEINFO */
        Dem_Cfg_GetSatelliteStatusOfSatelliteInfo(SatelliteId),
        OldSatelliteInfo.Raw,
        NewSatelliteInfo.Raw);
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteCore_SyncSetSatelliteInfo
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteCore_SyncSetSatelliteInfo(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC) OldSatelliteInfo,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC) NewSatelliteInfo
  )
{
  return Dem_SatelliteSat_SyncSetSatelliteInfo(SatelliteId, OldSatelliteInfo, NewSatelliteInfo);
}

/* ****************************************************************************
 % Dem_Satellite_GetSatelliteData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Satellite_GetSatelliteData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (Dem_Cfg_GetSatelliteDataOfSatelliteInfo(SatelliteId))[MonitorId];
}

/* ****************************************************************************
 % Dem_Satellite_GetSatelliteExtendedData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_ExtendedDataType, DEM_CODE)
Dem_Satellite_GetSatelliteExtendedData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_ExtendedDataType lSatelliteExtendedData;                                                                     /* PRQA S 0759 */ /* MD_MSR_Union */

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lSatelliteExtendedData.Raw = (Dem_Com_ProcessorWordType)0;

  if (((Dem_Prestore_isPrestoreFFEnabled() == TRUE) && (Dem_Satellite_IsMultipleSatellitesEnabled() == TRUE))
    || (Dem_StatusIndicator_IsExtendedFimEnabled() == TRUE))
  {
    Dem_Cfg_SatelliteExtendedDataConstPtrType lSatExtendedDataPtr;
    lSatExtendedDataPtr = (Dem_Cfg_SatelliteExtendedDataConstPtrType)Dem_Cfg_GetSatelliteExtendedDataOfSatelliteInfo(SatelliteId);
    Dem_Internal_AssertReturnValue(lSatExtendedDataPtr != NULL_PTR, DEM_E_INCONSISTENT_STATE, lSatelliteExtendedData)

    lSatelliteExtendedData = lSatExtendedDataPtr[MonitorId];
  }

  return lSatelliteExtendedData;
}

/* ****************************************************************************
 % Dem_SatelliteSat_SetSatelliteData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetSatelliteData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  )
{
  if ( (Dem_Error_isDevRunTimeChecksEnabled() == TRUE)
    && ( (SatelliteId >= Dem_Cfg_GetSizeOfSatelliteInfo())                                                                       
      || (MonitorId >= (Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId)))))                                                    
  {
    Dem_Error_RunTimeCheckFailed(DEM_SATELLITEIF_IMPLEMENTATION_FILENAME, __LINE__);                                               /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
  {
    (Dem_Cfg_GetSatelliteDataOfSatelliteInfo(SatelliteId))[MonitorId] = NewSatelliteData;                                        /* SBSW_DEM_WRITE_SATELLITEINFO_SATELLITEDATA */
  }
}

/* ****************************************************************************
 % Dem_SatelliteSat_SetSatelliteExtendedData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetSatelliteExtendedData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  NewSatelliteExtendedData
  )
{
  Dem_Cfg_SatelliteExtendedDataPtrType lSatExtendedDataPtr;
  lSatExtendedDataPtr = (Dem_Cfg_SatelliteExtendedDataPtrType)Dem_Cfg_GetSatelliteExtendedDataOfSatelliteInfo(SatelliteId);      /* PRQA S 2842 */ /* MD_DEM_Dir4.1_SatelliteInfoStructPointers */

  /* ----- Config Checks ------------------------------------------------ */
  if ( ((Dem_Prestore_isPrestoreFFEnabled() == FALSE)
       || (Dem_Satellite_IsMultipleSatellitesEnabled() == FALSE))
       && (Dem_StatusIndicator_IsExtendedFimEnabled() == FALSE))
  {
    /* Valid scenario - do nothing */
  }
  else
  if (lSatExtendedDataPtr == NULL_PTR)
  {
    Dem_Error_RunTimeCheckFailed(DEM_SATELLITEIF_IMPLEMENTATION_FILENAME, __LINE__);                                               /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
  /* ----- Runtime Checks ------------------------------------------------ */
  if ( (Dem_Error_isDevRunTimeChecksEnabled() == TRUE)                                                                           
    && ( (SatelliteId >= Dem_Cfg_GetSizeOfSatelliteInfo())
      || (MonitorId >= (Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId))) ))
  {
    Dem_Error_RunTimeCheckFailed(DEM_SATELLITEIF_IMPLEMENTATION_FILENAME, __LINE__);                                               /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
  {
    lSatExtendedDataPtr[MonitorId] = NewSatelliteExtendedData;                                                                   /* SBSW_DEM_WRITE_SATELLITEINFO_SATELLITE_EXTENDEDDATA */
  }
}

/* ****************************************************************************
 % Dem_SatelliteSat_SyncSetSatelliteData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteSat_SyncSetSatelliteData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  )
{
  boolean lReturnValue;

  if ( (Dem_Error_isDevRunTimeChecksEnabled() == TRUE)
    && ( (SatelliteId >= Dem_Cfg_GetSizeOfSatelliteInfo())                                                                       
      || (MonitorId >= (Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId))) ))                                                   
  {
    Dem_Error_RunTimeCheckFailed(DEM_SATELLITEIF_IMPLEMENTATION_FILENAME, __LINE__);                                               /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = TRUE;
  }
  else
  {
    /* Swap the new data into the buffer if the buffer's value is identical to the old data.
     * Return whether operation succeeded. */
    lReturnValue = Dem_Com_SyncCompareAndSwap(&((Dem_Cfg_GetSatelliteDataOfSatelliteInfo(SatelliteId))[MonitorId].Raw),          /* PRQA S 0404 */ /* MD_DEM_13.2_Order_Read_Accesses_Volatile */ /* SBSW_DEM_CALL_SYNC_COMPARE_AND_SWAP_SATELLITEDATA */
      OldSatelliteData.Raw, NewSatelliteData.Raw);
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteSat_SyncSetSatelliteExtendedData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteSat_SyncSetSatelliteExtendedData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  OldSatelliteExtendedData,
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  NewSatelliteExtendedData
  )
{
  boolean lReturnValue;

  lReturnValue = TRUE;

  if (((Dem_Prestore_isPrestoreFFEnabled() == TRUE)                                                                               
       && (Dem_Satellite_IsMultipleSatellitesEnabled() == TRUE))
      || (Dem_StatusIndicator_IsExtendedFimEnabled() == TRUE))
  {
    Dem_Cfg_SatelliteExtendedDataPtrType lSatExtendedDataPtr;
    lSatExtendedDataPtr = (Dem_Cfg_SatelliteExtendedDataPtrType)Dem_Cfg_GetSatelliteExtendedDataOfSatelliteInfo(SatelliteId);    /* PRQA S 2842, 2843 */ /* MD_DEM_Dir4.1_SatelliteInfoStructPointers, MD_DEM_Dir4.1_SatelliteInfoStructPointers */

    /* ----- Runtime Checks ------------------------------------------------ */
    if ((Dem_Error_isDevRunTimeChecksEnabled() == TRUE)
      && ((SatelliteId >= Dem_Cfg_GetSizeOfSatelliteInfo())
      || (MonitorId >= (Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId)))
      || (lSatExtendedDataPtr == NULL_PTR))
      )
    {
      Dem_Error_RunTimeCheckFailed(DEM_SATELLITEIF_IMPLEMENTATION_FILENAME, __LINE__);                                             /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    }
    else
    {
      lReturnValue = Dem_Com_SyncCompareAndSwap(&((lSatExtendedDataPtr)[MonitorId].Raw),                                         /* PRQA S 0404 */ /* MD_DEM_13.2_Order_Read_Accesses_Volatile */ /* SBSW_DEM_CALL_SYNC_COMPARE_AND_SWAP_SATELLITE_EXTENDEDDATA */
        OldSatelliteExtendedData.Raw, NewSatelliteExtendedData.Raw);
    }
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteCore_SyncSetSatelliteData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteCore_SyncSetSatelliteData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  )
{
  /* Behavior is identical for core and satellite --> use satellite method. */
  return Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, OldSatelliteData, NewSatelliteData);
}

/* ****************************************************************************
 % Dem_SatelliteSat_SetEventQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetEventQueueUpdated(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  Dem_SatelliteInfo_Type lOldSatelliteInfo;                                                                                      /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_SatelliteInfo_Type lNewSatelliteInfo;                                                                                      /* PRQA S 0759 */ /* MD_MSR_Union */
  do
  {
    lOldSatelliteInfo = Dem_Satellite_GetSatelliteInfo(SatelliteId);
    lNewSatelliteInfo = Dem_SatelliteInfo_SetEventQueueUpdated(lOldSatelliteInfo);
  }
  while (Dem_SatelliteSat_SyncSetSatelliteInfo(SatelliteId, lOldSatelliteInfo, lNewSatelliteInfo) == FALSE);
}

/* ****************************************************************************
 % Dem_Satellite_TestSimilarConditionsChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_TestSimilarConditionsChanged(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  )
{
  boolean lReturnValue;
  lReturnValue =
    (Dem_SatelliteData_TestSimilarConditionStatus(OldSatelliteData) != Dem_SatelliteData_TestSimilarConditionStatus(NewSatelliteData));
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Satellite_UpdateSimilarConditions
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Satellite_UpdateSimilarConditions(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_EventStatusType, AUTOMATIC)         MonitorTrigger
  )
{
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  if (MonitorTrigger >= DEM_EVENT_STATUS_PASSED_CONDITIONS_NOT_FULFILLED)
  {
    lNewSatelliteData = Dem_SatelliteData_ResetSimilarConditionStatus(OldSatelliteData);
  }
  else
  {
    lNewSatelliteData = Dem_SatelliteData_SetSimilarConditionStatus(OldSatelliteData);
  }

  if (Dem_Satellite_TestSimilarConditionsChanged(OldSatelliteData, lNewSatelliteData) == TRUE)
  {
    Dem_EventQueue_StatusType lOldQueueStatus;
    Dem_EventQueue_StatusType lNewQueueStatus;
    lOldQueueStatus = Dem_SatelliteData_GetQueueStatus(lNewSatelliteData);
    lNewQueueStatus = Dem_EventQueue_SetSimilarConditionStatusChanged(lOldQueueStatus);
    lNewSatelliteData = Dem_SatelliteData_SetQueueStatus(lNewSatelliteData, lNewQueueStatus);
  }

  return lNewSatelliteData;
}

/* ****************************************************************************
 % Dem_Satellite_UpdateSatelliteData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Satellite_UpdateSatelliteData(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_EventQueue_StatusType lOldQueueStatus;
  Dem_EventQueue_StatusType lNewQueueStatus;
  Dem_MonitorStatusType lMonitorStatus;

  lNewSatelliteData = OldSatelliteData;

  lOldQueueStatus = Dem_SatelliteData_GetQueueStatus(OldSatelliteData);
  lNewQueueStatus = Dem_EventQueue_CalculateQueueStatus(lOldQueueStatus, Dem_Debounce_GetMonitorTrigger(DebounceInfoPtr));       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  lMonitorStatus = Dem_SatelliteData_GetMonitorStatus(OldSatelliteData);
  lMonitorStatus = Dem_Monitor_CalculateMonitorStatus(lMonitorStatus, Dem_Debounce_GetMonitorTrigger(DebounceInfoPtr),           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                                      Dem_Debounce_GetEventId(DebounceInfoPtr));                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  if (Dem_Debounce_TestRequestFdcProcessing(DebounceInfoPtr) == TRUE)                                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  { /* update event entry with a new max value > pre-confirmation limit on task level */
    lNewQueueStatus = Dem_EventQueue_SetFdcProcessingStatus(lNewQueueStatus);
  }
  if (Dem_Debounce_TestFdcThresholdExceeded(DebounceInfoPtr) == TRUE)                                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    lNewQueueStatus = Dem_EventQueue_SetFdcTripStatus(lNewQueueStatus);

    Dem_ExtCom_FimDemTriggerOnUnconfirmed(DebounceInfoPtr->EventId);
  }
  if (Dem_Debounce_TestMaximumFdcExceeded(DebounceInfoPtr) == TRUE)                                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    lNewQueueStatus = Dem_EventQueue_SetFdcMaxSLCStatus(lNewQueueStatus);
  }
  lNewSatelliteData = Dem_Debounce_GetDebouncingResult(DebounceInfoPtr, lNewSatelliteData);                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lNewSatelliteData = Dem_SatelliteData_SetMonitorStatus(lNewSatelliteData, lMonitorStatus);
  lNewSatelliteData = Dem_SatelliteData_SetQueueStatus(lNewSatelliteData, lNewQueueStatus);

  return lNewSatelliteData;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Satellite_TestQueueStatusUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_TestQueueStatusUpdated(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  )
{
  Dem_EventQueue_StatusType lOldQueueStatus;
  Dem_EventQueue_StatusType lNewQueueStatus;
  lOldQueueStatus = Dem_SatelliteData_GetQueueStatus(OldSatelliteData);
  lNewQueueStatus = Dem_SatelliteData_GetQueueStatus(NewSatelliteData);

  return (boolean)( (lOldQueueStatus == DEM_EVENTQUEUE_STATE_INITIAL)
                 && (lNewQueueStatus != DEM_EVENTQUEUE_STATE_INITIAL) );
}

/* ****************************************************************************
 % Dem_SatelliteSat_ProcessTimeBasedDebouncing
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_ProcessTimeBasedDebouncing(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_EventIdType lEventId;
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_Union */

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
  lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                             /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

  if (Dem_DebounceTimeBasedSat_IsTimerActive(lDebounceInfoPtr) == TRUE)                                                          /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
  {
    do
    {
      lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
      lNewSatelliteData = lOldSatelliteData;
      lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                         /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
      Dem_DebounceTimeBasedSat_ProcessDebounce(lDebounceInfoPtr);                                                                /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */

      lNewSatelliteData = Dem_Satellite_UpdateSatelliteData(lNewSatelliteData, lDebounceInfoPtr);                                /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */

    } while (Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData) == FALSE);

    if (Dem_Debounce_TestMaximumFdcExceeded(lDebounceInfoPtr) == TRUE)                                                           /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
    {
      Dem_DebounceBaseSat_UpdateDebounceValueMax(lDebounceInfoPtr);                                                              /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
    }
    if (Dem_Satellite_TestQueueStatusUpdated(lOldSatelliteData, lNewSatelliteData) == TRUE)
    {
      Dem_SatelliteSat_SetEventQueueUpdated(SatelliteId);
    }
    /* Notify monitor status change */
    if (Dem_SatelliteData_GetMonitorStatus(lOldSatelliteData) != Dem_SatelliteData_GetMonitorStatus(lNewSatelliteData))
    {
      Dem_Notifications_MonitorStatusChanged(lEventId);
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_SatelliteSat_SetInitState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetInitState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(uint8, AUTOMATIC) InitState
  )
{
  Dem_SatelliteInfo_Type lOldSatelliteInfo;                                                                                      /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_SatelliteInfo_Type lNewSatelliteInfo;                                                                                      /* PRQA S 0759 */ /* MD_MSR_Union */
  do
  {
    lOldSatelliteInfo = Dem_Satellite_GetSatelliteInfo(SatelliteId);
    lNewSatelliteInfo = Dem_SatelliteInfo_SetInitStatus(lOldSatelliteInfo, InitState);
  }
  while (Dem_SatelliteSat_SyncSetSatelliteInfo(SatelliteId, lOldSatelliteInfo, lNewSatelliteInfo) == FALSE);
}

/* ****************************************************************************
 % Dem_Satellite_TestMonitorQualificationNeeded
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_TestMonitorQualificationNeeded(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData,
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  )
{
  boolean lReturn;
  lReturn = FALSE;

  if (Dem_Cfg_EventDebounceContinuous(DebounceInfoPtr->EventId) == TRUE)
  {
    Dem_MonitorStatusType lMonitorStatus;
    lMonitorStatus = Dem_SatelliteData_GetMonitorStatus(OldSatelliteData);
    if (((Dem_Debounce_TestQualifiedResult(DebounceInfoPtr) == TRUE)                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      && (Dem_Monitor_TestMonitorStatusTNCTOC(lMonitorStatus) == TRUE))                                                          
      || ((Dem_Debounce_GetMonitorTrigger(DebounceInfoPtr) == DEM_EVENT_STATUS_FAILED)                                            /* PRQA S 3415 */ /* MD_DEM_13.5_cf */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      && (Dem_Monitor_TestMonitorStatusTF(lMonitorStatus) == FALSE))                                                             
      || ((Dem_Debounce_GetMonitorTrigger(DebounceInfoPtr) == DEM_EVENT_STATUS_PASSED)                                            /* PRQA S 3415 */ /* MD_DEM_13.5_cf */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      && (Dem_Monitor_TestMonitorStatusTF(lMonitorStatus) == TRUE)))                                                             
    {
      lReturn = TRUE;
    }
  }

  if ( (Dem_Satellite_TestSimilarConditionsChanged(OldSatelliteData, NewSatelliteData) == TRUE)
    && (Dem_Debounce_GetMonitorTrigger(DebounceInfoPtr) == DEM_EVENT_STATUS_PASSED)                                               /* PRQA S 3415 */ /* MD_DEM_13.5_cf */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    && (Dem_Cfg_EventHealingTarget(DebounceInfoPtr->EventId) == 0u) )                                                             
  {
    lReturn = TRUE;
  }

  return lReturn;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_SatelliteSat_SetStatusIndicatorSymptomActionQueue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
*/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetStatusIndicatorSymptomActionQueue(
  Dem_Satellite_IdType SatelliteId,
  Dem_Satellite_MonitorIdType MonitorId
  )
{
  boolean lProcessingDone;

  do
  {
    Dem_SatelliteData_ExtendedDataType lOldSatelliteExtendedData;                                                                /* PRQA S 0759 */ /* MD_MSR_Union */
    Dem_SatelliteData_ExtendedDataType lNewSatelliteExtendedData;                                                                /* PRQA S 0759 */ /* MD_MSR_Union */
    Dem_StatusIndicator_QueueActionType lOldQueuedAction;

    lOldSatelliteExtendedData = Dem_Satellite_GetSatelliteExtendedData(SatelliteId, MonitorId);
    lOldQueuedAction = Dem_SatelliteData_GetStatusIndicatorActionsQueued(lOldSatelliteExtendedData);

    if (lOldQueuedAction != DEM_STATUSINDICATOR_QUEUE_SYMPTOM_REACHED)
    {
      lNewSatelliteExtendedData = Dem_SatelliteData_QueueStatusIndicatorSymptomAction(lOldSatelliteExtendedData);
      lProcessingDone = Dem_SatelliteSat_SyncSetSatelliteExtendedData(SatelliteId, MonitorId, lOldSatelliteExtendedData, lNewSatelliteExtendedData);
    }
    else
    {
      /* Setting the StatusIndicator symptom of event is already queued */
      lProcessingDone = TRUE;
    }
  } while (lProcessingDone == FALSE);                                                                                              /* PRQA S 2993 */ /* MD_DEM_2993 */

  Dem_SatelliteSat_SetStatusIndicatorQueueUpdated(SatelliteId);
}

/* ****************************************************************************
 % Dem_SatelliteSat_SetStatusIndicatorQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetStatusIndicatorQueueUpdated(
  Dem_Satellite_IdType SatelliteId
  )
{
  Dem_SatelliteInfo_Type lOldSatelliteInfo;                                                                                    /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_SatelliteInfo_Type lNewSatelliteInfo;                                                                                    /* PRQA S 0759 */ /* MD_MSR_Union */

  do
  {
    lOldSatelliteInfo = Dem_Satellite_GetSatelliteInfo(SatelliteId);
    lNewSatelliteInfo = Dem_SatelliteInfo_SetStatusIndicatorQueueUpdated(lOldSatelliteInfo);
  } while (Dem_SatelliteSat_SyncSetSatelliteInfo(SatelliteId, lOldSatelliteInfo, lNewSatelliteInfo) == FALSE);
}

 /* ****************************************************************************
 % Dem_Satellite_DecrementAndTestLoResTimerElapsed
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_DecrementAndTestLoResTimerElapsed(
  Dem_Satellite_IdType  SatelliteId
)
{
  boolean lReturnValue;
  if (Dem_SatelliteSat_IsLRTimeDebouncingEnabled() == TRUE)
  {
    Dem_Satellite_DebounceLoResTimerType lLoResTimer;
    lLoResTimer = Dem_Satellite_GetCurrentDebounceLoResTimer(SatelliteId);

    lLoResTimer--;

    if (lLoResTimer == 0u)
    {
      lReturnValue = TRUE;
      /* restart low resolution timer */
      lLoResTimer = Dem_Satellite_GetDebounceLoResTimeBase();
    }
    else
    {
      lReturnValue = FALSE;
    }
    Dem_Satellite_SetDebounceLoResTimer(SatelliteId, lLoResTimer);
  }
  else
  {
    lReturnValue = FALSE;
  }
  return lReturnValue;
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*!
 * \addtogroup Dem_Satellite_Public
 * \{
 */

/* ****************************************************************************
 % Dem_SatelliteSat_SetPrestoreQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetPrestoreQueueUpdated(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  if (Dem_Satellite_IsMultipleSatellitesEnabled() == TRUE)
  {
    Dem_SatelliteInfo_Type lOldSatelliteInfo;                                                                                    /* PRQA S 0759 */ /* MD_MSR_Union */
    Dem_SatelliteInfo_Type lNewSatelliteInfo;                                                                                    /* PRQA S 0759 */ /* MD_MSR_Union */
    do
    {
      lOldSatelliteInfo = Dem_Satellite_GetSatelliteInfo(SatelliteId);
      lNewSatelliteInfo = Dem_SatelliteInfo_SetPrestoreQueueUpdated(lOldSatelliteInfo);
    }
    while (Dem_SatelliteSat_SyncSetSatelliteInfo(SatelliteId, lOldSatelliteInfo, lNewSatelliteInfo) == FALSE);
  }
  else
  {
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
  }
}

/* ****************************************************************************
 % Dem_SatelliteSat_FreezeDebounceStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_FreezeDebounceStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_EventIdType lEventId;
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  do
  {
    lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
    lNewSatelliteData = lOldSatelliteData;
    lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                           /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

    lNewSatelliteData = Dem_Debounce_FreezeDebouncing(lDebounceInfoPtr, lNewSatelliteData);                                      /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
  }
  while (Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData) == FALSE);
}

/* ****************************************************************************
 % Dem_SatelliteCore_FreezeDebounceStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteCore_FreezeDebounceStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteSat_FreezeDebounceStatus(SatelliteId, MonitorId);
}

/* ****************************************************************************
 % Dem_SatelliteSat_GetDebouncingState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_SatelliteSat_GetDebouncingState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_EventIdType lEventId;
  Dem_SatelliteData_DataType lSatelliteData;                                                                                     /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_DebounceBase_ConstInfoPtrType lDebounceInfoPtr;

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  lSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
  lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lSatelliteData);                                /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

  return Dem_Debounce_GetDebouncingState(lDebounceInfoPtr);                                                                      /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
}

/* ****************************************************************************
 % Dem_SatelliteSat_ResetMonitorStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_SatelliteSat_ResetMonitorStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Std_ReturnType lReturnValue;
  boolean lProcessingDone;
  Dem_EventIdType lEventId;

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  lReturnValue = E_NOT_OK;

  do
  {
    Dem_SatelliteData_DataType lOldSatelliteData;                                                                                /* PRQA S 0759 */ /* MD_MSR_Union */
    Dem_SatelliteData_DataType lNewSatelliteData;                                                                                /* PRQA S 0759 */ /* MD_MSR_Union */
    Dem_EventQueue_StatusType lQueueStatus;

    lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
    lNewSatelliteData = lOldSatelliteData;

    lQueueStatus = Dem_SatelliteData_GetQueueStatus(lOldSatelliteData);
    if ( (lQueueStatus & DEM_EVENTQUEUE_SIMILAR_CONDITIONS_MASK) == DEM_EVENTQUEUE_STATE_INITIAL)
    {
      Dem_Debounce_InfoType lDebounceInfoData;                                                                                   /* PRQA S 0759 */ /* MD_MSR_Union */
      Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;

      lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                         /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
      lNewSatelliteData = Dem_Debounce_ResetDebouncing(lDebounceInfoPtr, lNewSatelliteData);                                     /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */

      lQueueStatus = Dem_EventQueue_SetResetTestFailedRequested(lQueueStatus);

      lNewSatelliteData = Dem_SatelliteData_SetQueueStatus(lNewSatelliteData, lQueueStatus);
      lProcessingDone = Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData);
      if (lProcessingDone == TRUE)
      {
        lReturnValue = E_OK;
        Dem_SatelliteSat_SetEventQueueUpdated(SatelliteId);
      }
    }
    else
    {
      /* Event is already queued, so there was a qualified result. Technically, reseteventstatus is not
        * allowed to interrupt seteventstatus, so the queue status should not change in this loop - better be
        * paranoid though */
      lProcessingDone = TRUE;
    }
  }
  while (lProcessingDone == FALSE);

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_SatelliteSat_UpdateMonitorTrigger
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_SatelliteSat_UpdateMonitorTrigger(
  CONST(Dem_Satellite_IdType, AUTOMATIC)        SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC) MonitorId,
  CONST(Dem_EventStatusType, AUTOMATIC)         MonitorTrigger
  )
{
  Std_ReturnType lReturnValue;
  Dem_EventIdType lEventId;
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */

  lReturnValue = E_OK;
  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);

  /* Possible concurrent modification :
     ClearEvent
     ResetEventStatus
     Displacement
     Aging */

  do
  {
    lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
    lNewSatelliteData = lOldSatelliteData;
    lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                           /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

    Dem_Debounce_SetMonitorTrigger(lDebounceInfoPtr, MonitorTrigger);                                                            /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
    if (Dem_Debounce_CalculateDebouncing(lDebounceInfoPtr) == TRUE)                                                              /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
    {
      if (Dem_Cfg_EventObdRelated(lEventId) == TRUE)
      {
        lNewSatelliteData = Dem_Satellite_UpdateSimilarConditions(lNewSatelliteData, MonitorTrigger);
      }

      if ( (Dem_Debounce_TestDebouncingChanged(lDebounceInfoPtr) == TRUE)                                                        /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
        || (Dem_Satellite_TestMonitorQualificationNeeded(lOldSatelliteData, lNewSatelliteData, lDebounceInfoPtr)  == TRUE) )     /* PRQA S 3415 */ /* MD_DEM_13.5_cf */ /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
      {
        boolean lOverflow;
        lOverflow = Dem_EventQueue_TestQueueOverflow(
          Dem_SatelliteData_GetQueueStatus(lOldSatelliteData),
          Dem_Debounce_GetMonitorTrigger(lDebounceInfoPtr));                                                                     /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
        if (lOverflow == FALSE)
        {
          lReturnValue = E_OK;
          lNewSatelliteData = Dem_Satellite_UpdateSatelliteData(lNewSatelliteData, lDebounceInfoPtr);                            /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
        }
        else
        {
          /* Event update must be discarded due to queue overflow */
          lReturnValue = E_NOT_OK;
          break;
        }
      }
    }
    else
    {
      lReturnValue = E_NOT_OK;
    }

  }
  while (Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData) == FALSE);

  if (Dem_Debounce_TestMaximumFdcExceeded(lDebounceInfoPtr) == TRUE)                                                             /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
  {
    Dem_DebounceBaseSat_UpdateDebounceValueMax(lDebounceInfoPtr);                                                                /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
  }
  if (Dem_Satellite_TestQueueStatusUpdated(lOldSatelliteData, lNewSatelliteData) == TRUE)
  {
    Dem_SatelliteSat_SetEventQueueUpdated(SatelliteId);
  }

  /* Notify monitor status change */
  if (Dem_SatelliteData_GetMonitorStatus(lOldSatelliteData) != Dem_SatelliteData_GetMonitorStatus(lNewSatelliteData))
  {
    Dem_Notifications_MonitorStatusChanged(lEventId);
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_SatelliteSat_UpdatePrestoreActionQueue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_UpdatePrestoreActionQueue(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_Prestore_QueueActionType, AUTOMATIC)  NewPrestoreAction
  )
{
  boolean lProcessingDone;

  do
  {
    Dem_SatelliteData_ExtendedDataType lOldSatelliteExtendedData;                                                                /* PRQA S 0759 */ /* MD_MSR_Union */
    Dem_SatelliteData_ExtendedDataType lNewSatelliteExtendedData;                                                                /* PRQA S 0759 */ /* MD_MSR_Union */
    Dem_Prestore_QueueActionType       lOldPrestoreAction;

    lOldSatelliteExtendedData = Dem_Satellite_GetSatelliteExtendedData(SatelliteId, MonitorId);
    lOldPrestoreAction = Dem_SatelliteData_GetPrestoreActionsQueued(lOldSatelliteExtendedData);

    if (lOldPrestoreAction != NewPrestoreAction)
    {
      if (NewPrestoreAction == DEM_PRESTORE_QUEUE_PRESTOREFF)
      {
        lNewSatelliteExtendedData = Dem_SatelliteData_QueuePrestoreFF(lOldSatelliteExtendedData);
      }
      else
      {
        lNewSatelliteExtendedData = Dem_SatelliteData_QueueClearPrestoredFF(lOldSatelliteExtendedData);
      }
      lProcessingDone = Dem_SatelliteSat_SyncSetSatelliteExtendedData(SatelliteId, MonitorId, lOldSatelliteExtendedData, lNewSatelliteExtendedData);
    }
    else
    {
      /* Prestorage of freeze frame is already queued */
      lProcessingDone = TRUE;
    }
  }
  while (lProcessingDone == FALSE);                                                                                              /* PRQA S 2993 */ /* MD_DEM_2993 */

  Dem_SatelliteSat_SetPrestoreQueueUpdated(SatelliteId);
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_SatelliteSat_MainFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_MainFunction(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  if (Dem_SatelliteSat_IsHRTimeDebouncingEnabled() == TRUE)
  {
    Dem_Satellite_DebounceHiResIterType lIter;

    /* Process Time Based Debounce Events assigned to current satellite which use the high resolution timer */
    for (Dem_Satellite_DebounceHiResIterInit(SatelliteId, &lIter);                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Satellite_DebounceHiResIterExists(&lIter) == TRUE;                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Satellite_DebounceHiResIterNext(&lIter))                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_SatelliteSat_ProcessTimeBasedDebouncing(SatelliteId,
                                                  Dem_Cfg_EventSatelliteEventId(Dem_Satellite_DebounceHiResIterGet(&lIter)));    /* SBSW_DEM_CALL_ITERATOR_POINTER */
    }
  }

  if (Dem_Satellite_DecrementAndTestLoResTimerElapsed(SatelliteId) == TRUE)
  {
    Dem_Satellite_DebounceLoResIterType lIter;
    /* Process Time Based Debounce Events assigned to current satellite which use the low resolution timer */
    for (Dem_Satellite_DebounceLoResIterInit(SatelliteId, &lIter);                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Satellite_DebounceLoResIterExists(&lIter) == TRUE;                                                                     /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Satellite_DebounceLoResIterNext(&lIter))                                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_SatelliteSat_ProcessTimeBasedDebouncing(SatelliteId,
                                                  Dem_Cfg_EventSatelliteEventId(Dem_Satellite_DebounceLoResIterGet(&lIter)));    /* SBSW_DEM_CALL_ITERATOR_POINTER */
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_SatelliteSat_ResetDebounceStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_ResetDebounceStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_EventIdType lEventId;
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  do
  {
    lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
    lNewSatelliteData = lOldSatelliteData;
    lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                           /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

    lNewSatelliteData = Dem_Debounce_ResetDebouncing(lDebounceInfoPtr, lNewSatelliteData);                                       /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
  }
  while (Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData) == FALSE);
}


/* ****************************************************************************
 % Dem_SatelliteCore_ResetDebounceStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_ResetDebounceStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteSat_ResetDebounceStatus(SatelliteId, MonitorId);
}

/* ****************************************************************************
 % Dem_SatelliteCore_RestartEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_RestartEvent(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;
  Dem_EventIdType lEventId;

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  do
  {
    lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
    lNewSatelliteData = lOldSatelliteData;
    lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                           /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

    lNewSatelliteData = Dem_Debounce_ResetDebouncing(lDebounceInfoPtr, lNewSatelliteData);                                       /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */

    lNewSatelliteData = Dem_SatelliteData_SetQueueStatus(lNewSatelliteData, Dem_EventQueue_GetInitialQueueStatus());

    lNewSatelliteData = Dem_Monitor_ResetTNCTOC(lNewSatelliteData);
    lNewSatelliteData = Dem_SatelliteData_ResetSimilarConditionStatus(lNewSatelliteData);
  }
  while (Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData) == FALSE);
  Dem_DebounceBaseCore_ResetDebounceValueMax(lDebounceInfoPtr);                                                                  /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */

  /* Notify monitor status change */
  if (Dem_SatelliteData_GetMonitorStatus(lOldSatelliteData) != Dem_SatelliteData_GetMonitorStatus(lNewSatelliteData))
  {
    Dem_Notifications_MonitorStatusChanged(lEventId);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_SatelliteCore_ClearEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_ClearEvent(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;
  Dem_EventIdType lEventId;

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  do
  {
    lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
    lNewSatelliteData = lOldSatelliteData;

    lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                           /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

    lNewSatelliteData = Dem_Debounce_ResetDebouncing(lDebounceInfoPtr, lNewSatelliteData);                                       /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */

    lNewSatelliteData = Dem_SatelliteData_SetQueueStatus(lNewSatelliteData, Dem_EventQueue_GetInitialQueueStatus());

    lNewSatelliteData = Dem_SatelliteData_ResetMonitorStatus(lNewSatelliteData);

    lNewSatelliteData = Dem_SatelliteData_ResetSimilarConditionStatus(lNewSatelliteData);
  }
  while (Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData) == FALSE);
  Dem_DebounceBaseCore_ResetDebounceValueMax(lDebounceInfoPtr);                                                                  /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */

  /* Notify monitor status change */
  if (Dem_SatelliteData_GetMonitorStatus(lOldSatelliteData) != Dem_SatelliteData_GetMonitorStatus(lNewSatelliteData))
  {
    Dem_Notifications_MonitorStatusChanged(lEventId);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_SatelliteCore_TestAndClearEventQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteCore_TestAndClearEventQueueUpdated(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  Dem_SatelliteInfo_Type lOldSatelliteInfo;                                                                                      /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_SatelliteInfo_Type lNewSatelliteInfo;                                                                                      /* PRQA S 0759 */ /* MD_MSR_Union */
  do
  {
    lOldSatelliteInfo = Dem_Satellite_GetSatelliteInfo(SatelliteId);
    lNewSatelliteInfo = Dem_SatelliteInfo_ResetEventQueueUpdated(lOldSatelliteInfo);
  }
  while (Dem_SatelliteCore_SyncSetSatelliteInfo(SatelliteId, lOldSatelliteInfo, lNewSatelliteInfo) == FALSE);
  return Dem_SatelliteInfo_GetEventQueueUpdated(lOldSatelliteInfo);
}

/* ****************************************************************************
 % Dem_SatelliteCore_TestAndClearPrestoreQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteCore_TestAndClearPrestoreQueueUpdated(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  boolean lQueueUpdateStatus;

  if ( (Dem_Satellite_IsMultipleSatellitesEnabled() == TRUE)
    && (Dem_Prestore_isPrestoreFFEnabled() == TRUE))                                                                             
  {
    Dem_SatelliteInfo_Type lOldSatelliteInfo;                                                                                    /* PRQA S 0759 */ /* MD_MSR_Union */
    Dem_SatelliteInfo_Type lNewSatelliteInfo;                                                                                    /* PRQA S 0759 */ /* MD_MSR_Union */
    do
    {
      lOldSatelliteInfo = Dem_Satellite_GetSatelliteInfo(SatelliteId);
      lNewSatelliteInfo = Dem_SatelliteInfo_ResetPrestoreQueueUpdated(lOldSatelliteInfo);
    }
    while (Dem_SatelliteCore_SyncSetSatelliteInfo(SatelliteId, lOldSatelliteInfo, lNewSatelliteInfo) == FALSE);
    lQueueUpdateStatus = Dem_SatelliteInfo_GetPrestoreQueueUpdated(lOldSatelliteInfo);
  }
  else
  {
    lQueueUpdateStatus = FALSE;
  }

  return lQueueUpdateStatus;
}

/* ****************************************************************************
 % Dem_Satellite_PeekEventQueueStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_Satellite_PeekEventQueueStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
  return Dem_SatelliteData_GetQueueStatus(lOldSatelliteData);
}

/* ****************************************************************************
 % Dem_SatelliteCore_ConsumeEventQueueStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_SatelliteCore_ConsumeEventQueueStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_EventQueue_StatusType  lOldEventQueueStatus;

  do
  {
    lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
    lOldEventQueueStatus = Dem_SatelliteData_GetQueueStatus(lOldSatelliteData);
    lNewSatelliteData = Dem_SatelliteData_SetQueueStatus(lOldSatelliteData, Dem_EventQueue_GetInitialQueueStatus());
  }
  while (Dem_SatelliteCore_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData) == FALSE);

  return lOldEventQueueStatus;
}

/* ****************************************************************************
 % Dem_Satellite_PeekPrestoreActionQueue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Prestore_QueueActionType, DEM_CODE)
Dem_Satellite_PeekPrestoreActionQueue(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_ExtendedDataType lOldSatelliteExtendedData;                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  lOldSatelliteExtendedData = Dem_Satellite_GetSatelliteExtendedData(SatelliteId, MonitorId);
  return Dem_SatelliteData_GetPrestoreActionsQueued(lOldSatelliteExtendedData);
}

/* ****************************************************************************
 % Dem_Satellite_ConsumePrestoreActionQueue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Prestore_QueueActionType, DEM_CODE)
Dem_Satellite_ConsumePrestoreActionQueue(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_ExtendedDataType lOldSatelliteExtendedData;                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_SatelliteData_ExtendedDataType lNewSatelliteExtendedData;                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  do
  {
    lOldSatelliteExtendedData = Dem_Satellite_GetSatelliteExtendedData(SatelliteId, MonitorId);
    lNewSatelliteExtendedData = Dem_SatelliteData_DequeuePrestoreActions(lOldSatelliteExtendedData);
  } while (Dem_SatelliteSat_SyncSetSatelliteExtendedData(SatelliteId, MonitorId, lOldSatelliteExtendedData, lNewSatelliteExtendedData) == FALSE);  /* PRQA S 2993 */ /* MD_DEM_2993 */
  return Dem_SatelliteData_GetPrestoreActionsQueued(lOldSatelliteExtendedData);
}


/* ****************************************************************************
 % Dem_SatelliteCore_MemoryInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_MemoryInit(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  Dem_SatelliteInfo_Type lSatelliteInfo = { 0 };                                                                                 /* PRQA S 0759 */ /* MD_MSR_Union */
  lSatelliteInfo.Data.InitStatus = DEM_INITSTATE_UNINITIALIZED;
  Dem_SatelliteSat_SetSatelliteInfo(SatelliteId, lSatelliteInfo);
}

/* ****************************************************************************
 % Dem_SatelliteSat_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_PreInit(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  {
    Dem_Satellite_MonitorIdType lMonitorId;
    Dem_SatelliteData_DataType lSatelliteData;                                                                                   /* PRQA S 0759 */ /* MD_MSR_Union */
    Dem_SatelliteData_ExtendedDataType lSatelliteExtendedData;                                                                   /* PRQA S 0759 */ /* MD_MSR_Union */

    lSatelliteData = Dem_SatelliteData_GetInitValue();
    lSatelliteExtendedData.Raw  = 0u;

    for (lMonitorId = 0u;
         lMonitorId < Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId);
         ++lMonitorId)
    {
      Dem_SatelliteSat_SetSatelliteData(SatelliteId, lMonitorId, lSatelliteData);
      Dem_SatelliteSat_SetSatelliteExtendedData(SatelliteId, lMonitorId, lSatelliteExtendedData);
      Dem_Debounce_PreInit(SatelliteId, lMonitorId);
    }
  }

  if (Dem_SatelliteSat_IsLRTimeDebouncingEnabled() == TRUE)
  {
    Dem_Satellite_SetDebounceLoResTimer(SatelliteId, Dem_Satellite_GetDebounceLoResTimeBase());                                  /* PRQA S 2843 */ /* MD_DEM_Dir4.1_SatelliteInfoStructPointers */
  }

  {
    Dem_SatelliteInfo_Type lSatelliteInfo;                                                                                       /* PRQA S 0759 */ /* MD_MSR_Union */
    lSatelliteInfo = Dem_Satellite_GetSatelliteInfo(SatelliteId);
    lSatelliteInfo = Dem_SatelliteInfo_SetInitStatus(lSatelliteInfo, DEM_INITSTATE_PREINITIALIZED);
    Dem_SatelliteSat_SetSatelliteInfo(SatelliteId, lSatelliteInfo);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_SatelliteSat_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_Init(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  Dem_SatelliteSat_SetInitState(SatelliteId, DEM_INITSTATE_INITIALIZED);

  Dem_ExtCom_FimInitSatellite(Dem_Satellite_GetApplicationId(SatelliteId));
}

/* ****************************************************************************
 % Dem_Satellite_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Satellite_GetFaultDetectionCounter(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter                                                             /* PRQA S 3673 */ /* MD_DEM_8.13 */
  )
{
  Dem_EventIdType lEventId;
  Dem_SatelliteData_DataType lSatelliteData;                                                                                     /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_DebounceBase_ConstInfoPtrType lDebounceInfoPtr;
  Std_ReturnType lReturnValue;

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  lSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
  lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lSatelliteData);                                /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
  lReturnValue = Dem_Debounce_GetFaultDetectionCounter(lDebounceInfoPtr, FaultDetectionCounter);                                 /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Satellite_GetMaxFaultDetectionCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Satellite_GetMaxFaultDetectionCounter(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_EventIdType lEventId;
  Dem_SatelliteData_DataType lSatelliteData;                                                                                     /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_DebounceBase_ConstInfoPtrType lDebounceInfoPtr;
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_Union */

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  lSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
  lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lSatelliteData);                                /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
  return Dem_Debounce_GetMaxFaultDetectionCounter(lDebounceInfoPtr);                                                             /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
}

/* ****************************************************************************
 % Dem_SatelliteCore_RestoreDebounceValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_RestoreDebounceValue(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(sint16, AUTOMATIC) Value,
  CONST(boolean, AUTOMATIC) ExpectedThreshold
  )
{
  Dem_EventIdType lEventId;
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_DebounceBase_ConstInfoPtrType lDebounceInfoPtr;

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  do
  {
    lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
    lNewSatelliteData = lOldSatelliteData;
    lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                           /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

    lNewSatelliteData = Dem_Debounce_RestoreDebounceValue(lDebounceInfoPtr, lNewSatelliteData, Value, ExpectedThreshold);        /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
    lNewSatelliteData = Dem_SatelliteData_SetQueueStatus(lNewSatelliteData, Dem_EventQueue_GetInitialQueueStatus());
  }
  while (Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData) == FALSE);
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */


/* ****************************************************************************
 % Dem_Satellite_GetDebounceValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Debounce_DataType, DEM_CODE)
Dem_Satellite_GetDebounceValue(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_DataType lSatelliteData;                                                                                     /* PRQA S 0759 */ /* MD_MSR_Union */

  lSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
  return Dem_SatelliteData_GetDebounceData(lSatelliteData);
}

/* ****************************************************************************
 % Dem_Satellite_GetInitState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Satellite_GetInitState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  Dem_SatelliteInfo_Type lSatelliteInfo;                                                                                         /* PRQA S 0759 */ /* MD_MSR_Union */

  lSatelliteInfo = Dem_Satellite_GetSatelliteInfo(SatelliteId);
  return Dem_SatelliteInfo_GetInitStatus(lSatelliteInfo);
}

/* ****************************************************************************
 % Dem_Satellite_GetMonitorStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Satellite_GetMonitorStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_DataType lSatelliteData;                                                                                     /* PRQA S 0759 */ /* MD_MSR_Union */

  lSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
  return Dem_SatelliteData_GetMonitorStatus(lSatelliteData);
}

/* ****************************************************************************
 % Dem_Satellite_GetCurrentSatelliteId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Satellite_IdType, DEM_CODE)
Dem_Satellite_GetCurrentSatelliteId(
  void
  )
{
  Dem_Satellite_IdType lSatelliteId;

  if(Dem_Satellite_IsMultipleSatellitesEnabled() == TRUE)
  {
    Dem_Satellite_ApplicationType lCurrentApplication;
    lCurrentApplication = Dem_ExtCom_GetCurrentApplicationId();

    for (lSatelliteId = 0u;
         lSatelliteId < Dem_Cfg_GlobalSatelliteCount();
         ++lSatelliteId)
    {
      if (Dem_Satellite_GetApplicationId(lSatelliteId) == lCurrentApplication)
      {
        break;
      }
    }
    Dem_Internal_AssertReturnValue(lSatelliteId  < Dem_Cfg_GlobalSatelliteCount(), DEM_E_INCONSISTENT_STATE, DEM_SATELLITE_APPLICATION_ZERO)
  }
  else
  {
    lSatelliteId = DEM_SATELLITE_APPLICATION_ZERO;
  }
  return lSatelliteId;
}

/* ****************************************************************************
 % Dem_Satellite_GetSimilarConditionStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_GetSimilarConditionStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  return Dem_SatelliteData_TestSimilarConditionStatus(Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId));
}

/* ****************************************************************************
 % Dem_SatelliteCore_TestAndClearStatusIndicatorQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteCore_TestAndClearStatusIndicatorQueueUpdated(
  Dem_Satellite_IdType SatelliteId
  )
{
  Dem_SatelliteInfo_Type lOldSatelliteInfo;                                                                                    /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_SatelliteInfo_Type lNewSatelliteInfo;                                                                                    /* PRQA S 0759 */ /* MD_MSR_Union */

  do
  {
    lOldSatelliteInfo = Dem_Satellite_GetSatelliteInfo(SatelliteId);
    lNewSatelliteInfo = Dem_SatelliteInfo_ResetStatusIndicatorQueueUpdated(lOldSatelliteInfo);
  } 
  while (Dem_SatelliteCore_SyncSetSatelliteInfo(SatelliteId, lOldSatelliteInfo, lNewSatelliteInfo) == FALSE);

  return Dem_SatelliteInfo_GetStatusIndicatorQueueUpdated(lOldSatelliteInfo);
}

/* ****************************************************************************
 % Dem_Satellite_PeekStatusIndicatorActionQueue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_QueueActionType, DEM_CODE)
Dem_Satellite_PeekStatusIndicatorActionQueue(
  Dem_Satellite_IdType SatelliteId,
  Dem_Satellite_MonitorIdType MonitorId
  )
{
  Dem_SatelliteData_ExtendedDataType lOldSatelliteExtendedData;                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  lOldSatelliteExtendedData = Dem_Satellite_GetSatelliteExtendedData(SatelliteId, MonitorId);
  return Dem_SatelliteData_GetStatusIndicatorActionsQueued(lOldSatelliteExtendedData);
}

/* ****************************************************************************
 % Dem_Satellite_SetStatusIndicatorSymptom
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Satellite_SetStatusIndicatorSymptom(
  Dem_EventIdType EventId
  )
{
  if (Dem_StatusIndicator_IsExtendedFimEnabled() == TRUE)
  {
    Dem_Satellite_IdType lSatelliteId;
    Dem_EventIdType lSatelliteEventId;

    lSatelliteId = Dem_Cfg_EventSatelliteId(EventId);
    lSatelliteEventId = Dem_Cfg_EventSatelliteEventId(EventId);

    if (Dem_Satellite_GetDebounceValue(lSatelliteId, lSatelliteEventId) >= Dem_Cfg_EventStorageTarget(EventId))
    {
      Dem_SatelliteSat_SetStatusIndicatorSymptomActionQueue(lSatelliteId, lSatelliteEventId);
    }
  }
}

/* ****************************************************************************
 % Dem_Satellite_ConsumeStatusIndicatorActionQueue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_StatusIndicator_QueueActionType, DEM_CODE)
Dem_Satellite_ConsumeStatusIndicatorActionQueue(
  Dem_Satellite_IdType SatelliteId,
  Dem_Satellite_MonitorIdType MonitorId
  )
{
  Dem_SatelliteData_ExtendedDataType lOldSatelliteExtendedData;                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  Dem_SatelliteData_ExtendedDataType lNewSatelliteExtendedData;                                                                  /* PRQA S 0759 */ /* MD_MSR_Union */
  do
  {
    lOldSatelliteExtendedData = Dem_Satellite_GetSatelliteExtendedData(SatelliteId, MonitorId);
    lNewSatelliteExtendedData = Dem_SatelliteData_DequeueStatusIndicatorActions(lOldSatelliteExtendedData);
  }
  while (Dem_SatelliteSat_SyncSetSatelliteExtendedData(SatelliteId, MonitorId, lOldSatelliteExtendedData, 
    lNewSatelliteExtendedData) == FALSE);                                                                                        /* PRQA S 2993 */ /* MD_DEM_2993 */

  return Dem_SatelliteData_GetStatusIndicatorActionsQueued(lOldSatelliteExtendedData);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_SATELLITEIF_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_SatelliteIF_Implementation.h
 *********************************************************************************************************************/
