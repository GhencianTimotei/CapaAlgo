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
/*! \addtogroup Dem_EventInternalStatus
 *  \{
 *  \file       Dem_EventInternalStatus_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of EventInternalStatus subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_EVENTINTERNALSTATUS_IMPLEMENTATION_H)
#define DEM_EVENTINTERNALSTATUS_IMPLEMENTATION_H

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

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_EventInternalStatus_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_UDSStatus_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_EVENTINTERNALSTATUS_IMPLEMENTATION_FILENAME "Dem_EventInternalStatus_Implementation.h"

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
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_EventInternalStatus_PrivateProperties Private Properties
 * \{
 */

/* Internal status bit 'event available' ----------------------------------- */
#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_GetMilGroupTripCountRaw
 *****************************************************************************/
/*!
 * \brief         Get the trip count of the MIL group
 *
 * \details       Get the trip count of the MIL group. There is additional
 *                information encoded in the value, so it cannot be used
 *                directly
 *
 * \param[in]     MilGroupIndex
 *                Unique handle of the MIL group
 *
 * \return        Trip count of the MIL group (raw)
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_MIL_GROUPS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EventInternalStatus_GetMilGroupTripCountRaw(
  CONST(uint16, AUTOMATIC)  MilGroupIndex
  );
#endif
#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_SetMilGroupTripCount
 *****************************************************************************/
/*!
 * \brief         Set the trip count of the MIL group
 *
 * \details       Set the trip count of the MIL group.
 *
 * \param[in]     MilGroupIndex
 *                Unique handle of the MIL group
 * \param[in]     TripCount
 *                New trip count
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_MIL_GROUPS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventInternalStatus_SetMilGroupTripCount(
  CONST(uint16, AUTOMATIC)  MilGroupIndex,
  CONST(uint8, AUTOMATIC)  TripCount
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_GetMilGroupTripCountRaw
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EventInternalStatus_GetMilGroupTripCountRaw(
  CONST(uint16, AUTOMATIC)  MilGroupIndex
  )
{
  return (Dem_Cfg_StatusData.MilGroupTripCount[MilGroupIndex]);
}
#endif
#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_SetMilGroupTripCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventInternalStatus_SetMilGroupTripCount(
  CONST(uint16, AUTOMATIC)  MilGroupIndex,
  CONST(uint8, AUTOMATIC)  TripCount
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (MilGroupIndex >= Dem_Cfg_GlobalMilGroupCount())
  {
    Dem_Error_RunTimeCheckFailed(DEM_EVENTINTERNALSTATUS_IMPLEMENTATION_FILENAME, __LINE__);                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_StatusData.MilGroupTripCount[MilGroupIndex] = TripCount;                                                             /* SBSW_DEM_ARRAY_WRITE_STATUSDATA_MILGROUPTRIPCOUNT */
  }
}
#endif
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
 * \addtogroup Dem_EventInternalStatus_PublicProperties
 * \{
 */


/* ****************************************************************************
 % Dem_EventInternalStatus_TestEventDisconnected
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_TestEventDisconnected(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus                                                                 /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(InternalStatus)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
  return (boolean)((InternalStatus & DEM_EVENTINTERNALSTATUS_DISCONNECTED_EVENT) != 0u);
#else
  return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_EventInternalStatus_SetEventDisconnected
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_SetEventDisconnected(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
  return (Dem_Event_InternalStatusType)(InternalStatus | DEM_EVENTINTERNALSTATUS_DISCONNECTED_EVENT);
#else
  return InternalStatus;
#endif
}

#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON) || (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_ResetEventDisconnected
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_ResetEventDisconnected(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
  return (Dem_Event_InternalStatusType)(InternalStatus & DEM_EVENTINTERNALSTATUS_DISCONNECTED_EVENT_MASK);
}
#endif

/* Internal status bit 'event suppressed' ---------------------------------- */

/* ****************************************************************************
 % Dem_EventInternalStatus_TestAvailabilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_TestAvailabilityChanged(                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus                                                                 /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(InternalStatus)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (boolean)((InternalStatus & DEM_EVENTINTERNALSTATUS_AVAILABILITY_CHANGED) != 0u);
}

/* ****************************************************************************
 % Dem_EventInternalStatus_SetAvailabilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_SetAvailabilityChanged(                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
  return (Dem_Event_InternalStatusType)(InternalStatus | DEM_EVENTINTERNALSTATUS_AVAILABILITY_CHANGED);
}

/* ****************************************************************************
 % Dem_EventInternalStatus_ResetAvailabilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_ResetAvailabilityChanged(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
  return (Dem_Event_InternalStatusType)(InternalStatus & DEM_EVENTINTERNALSTATUS_AVAILABILITY_CHANGED_MASK);
}


/* Internal status bit 'DTC disabled by PB selectable' --------------------- */

/* ****************************************************************************
 % Dem_EventInternalStatus_TestAvailableInVariant
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_TestAvailableInVariant(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus                                                                 /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(InternalStatus)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_ISCONST_AVAILABLEINVARIANT == STD_OFF) && (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
  return (boolean)((InternalStatus & DEM_EVENTINTERNALSTATUS_AVAILABLEINVARIANT) != 0u);
#else
  return TRUE;
#endif
}

#if (DEM_FEATURE_SUPPORT_EVENTCOMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_SetAvailableInVariant
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_SetAvailableInVariant(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
# if (DEM_CFG_ISCONST_AVAILABLEINVARIANT == STD_OFF)
  return (Dem_Event_InternalStatusType)(InternalStatus | DEM_EVENTINTERNALSTATUS_AVAILABLEINVARIANT);
# else
  return InternalStatus;
# endif
}
#endif

/* ****************************************************************************
 % Dem_EventInternalStatus_TestSimilarConditions
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_TestSimilarConditions(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  ExtendedStatus
  )
{
  return (boolean)((ExtendedStatus & DEM_EXT_STATUS_SIMILAR_CONDITIONS) != 0u);
}

/* ****************************************************************************
 % Dem_EventInternalStatus_SetSimilarConditions
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_ExtendedStatusType, DEM_CODE)
Dem_EventInternalStatus_SetSimilarConditions(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  ExtendedStatus
  )
{
  return (Dem_Event_ExtendedStatusType)(ExtendedStatus | DEM_EXT_STATUS_SIMILAR_CONDITIONS);
}

/* ****************************************************************************
 % Dem_EventInternalStatus_ResetSimilarConditions
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_ExtendedStatusType, DEM_CODE)
Dem_EventInternalStatus_ResetSimilarConditions(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  ExtendedStatus
  )
{
  return (Dem_Event_ExtendedStatusType)(ExtendedStatus & DEM_EXT_STATUS_SIMILAR_CONDITIONS_MASK);
}





#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_GetMilGroupPendingCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_EventInternalStatus_GetMilGroupPendingCount(
  CONST(uint16, AUTOMATIC)  MilGroupIndex
  )
{
  return Dem_Cfg_StatusData.MilGroupActiveEvents[MilGroupIndex];
}
#endif

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_SetMilGroupPendingCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventInternalStatus_SetMilGroupPendingCount(
  CONST(uint16, AUTOMATIC)  MilGroupIndex,
  CONST(uint16, AUTOMATIC)  PendingCount
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (MilGroupIndex >= Dem_Cfg_GlobalMilGroupCount())
    || (PendingCount > 0xffU) )
  {
    Dem_Error_RunTimeCheckFailed(DEM_EVENTINTERNALSTATUS_IMPLEMENTATION_FILENAME, __LINE__);                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_StatusData.MilGroupActiveEvents[MilGroupIndex] = (uint8)PendingCount;                                                /* SBSW_DEM_ARRAY_WRITE_STATUSDATA_MILGROUPACTIVEEVENTS */
  }
}
#endif

 /* ****************************************************************************
 % Dem_EventInternalStatus_Test_QualifyStatus_CDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_Test_QualifyStatus_CDTC(                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_CDTC) != 0u);
}

/* ****************************************************************************
 % Dem_EventInternalStatus_Set_QualifyStatus_CDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_Set_QualifyStatus_CDTC(                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  )
{
  return (Dem_Event_InternalStatusType)((Status) | DEM_UDS_STATUS_CDTC);
}

/* ****************************************************************************
 % Dem_EventInternalStatus_Reset_QualifyStatus_CDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_Reset_QualifyStatus_CDTC(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  )
{
  return (Dem_Event_InternalStatusType)((Status) & DEM_UDS_STATUS_CDTC_MASK);
}

 /* ****************************************************************************
 % Dem_EventInternalStatus_Test_QualifyStatus_WIR()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_Test_QualifyStatus_WIR(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_WIR) != 0u);
}

/* ****************************************************************************
 % Dem_EventInternalStatus_Set_QualifyStatus_WIR()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_Set_QualifyStatus_WIR(                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  )
{
  return (Dem_Event_InternalStatusType)((Status) | DEM_UDS_STATUS_WIR);
}

/* ****************************************************************************
 % Dem_EventInternalStatus_Reset_QualifyStatus_WIR()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_Reset_QualifyStatus_WIR(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  )
{
  return (Dem_Event_InternalStatusType)((Status)& DEM_UDS_STATUS_WIR_MASK);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#endif /* DEM_EVENTINTERNALSTATUS_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EventInternalStatus_Implementation.h
 *********************************************************************************************************************/
