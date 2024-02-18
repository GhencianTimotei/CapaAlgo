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
/*! \addtogroup Dem_SatelliteInfo
 *  \{
 *  \file       Dem_SatelliteInfo_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of SatelliteInfo subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_SATELLITEINFO_IMPLEMENTATION_H)
#define DEM_SATELLITEINFO_IMPLEMENTATION_H

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
#include "Dem_SatelliteInfo_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_SATELLITEINFO_IMPLEMENTATION_FILENAME "Dem_SatelliteInfo_Implementation.h"

/*! Initial satellite info value */
#define DEM_SATELLITEINFO_INIT_VALUE           0u

#define DEM_SATELLITEINFO_SATELLITE_STATUS_SIZE          DEM_1BYTE      /*!< Size of the satellite status type */
#define DEM_SATELLITEINFO_EVENTQUEUE_STATUS_POS          0u              /*!< Bit offset of the event queue status */
#define DEM_SATELLITEINFO_EVENTQUEUE_STATUS_SIZE         1u              /*!< Size of event queue status flag*/

#define DEM_SATELLITEINFO_EVENTQUEUE_STATUS              DEM_NBIT(DEM_SATELLITEINFO_EVENTQUEUE_STATUS_SIZE, DEM_SATELLITEINFO_EVENTQUEUE_STATUS_POS)  /*!< Bit mask for queue status bit(s) */
#define DEM_SATELLITEINFO_EVENTQUEUE_STATUS_MASK         DEM_NBIT_MASK(DEM_SATELLITEINFO_EVENTQUEUE_STATUS_SIZE, DEM_SATELLITEINFO_EVENTQUEUE_STATUS_POS,DEM_SATELLITEINFO_SATELLITE_STATUS_SIZE)  /*!< Negated bit mask for queue status bit(s) */

#define DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS_POS       1u              /*!< Bit offset of the prestore queue status */
#define DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS_SIZE      1u              /*!< Size of prestore queue status flag*/

#define DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS           DEM_NBIT(DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS_SIZE, DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS_POS)  /*!< Bit mask for queue status bit(s) */
#define DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS_MASK      DEM_NBIT_MASK(DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS_SIZE, DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS_POS,DEM_SATELLITEINFO_SATELLITE_STATUS_SIZE)  /*!< Negated bit mask for queue status bit(s) */

#define DEM_SATELLITEINFO_STATUSINDICATOR_STATUS_POS     2u              /*!< Bit offset of the prestore queue status */
#define DEM_SATELLITEINFO_STATUSINDICATOR_STATUS_SIZE    1u              /*!< Size of prestore queue status flag*/

#define DEM_SATELLITEINFO_STATUSINDICATOR_STATUS         DEM_NBIT(DEM_SATELLITEINFO_STATUSINDICATOR_STATUS_SIZE, DEM_SATELLITEINFO_STATUSINDICATOR_STATUS_POS)  /*!< Bit mask for queue status bit(s) */

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
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_SatelliteInfo_PublicProperties
 * \{
 */

/* ****************************************************************************
 % Dem_SatelliteInfo_SetInitStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_SetInitStatus(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo,
  CONST(uint8, AUTOMATIC) InitStatus
  )
{
  Dem_SatelliteInfo_Type lReturnValue;                                                                                           /* PRQA S 0759 */ /* MD_MSR_Union */
  lReturnValue = SatelliteInfo;
  lReturnValue.Data.InitStatus = InitStatus;
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteInfo_GetInitStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_SatelliteInfo_GetInitStatus(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo
  )
{
  return SatelliteInfo.Data.InitStatus;
}

/* ****************************************************************************
 % Dem_SatelliteInfo_SetEventQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_SetEventQueueUpdated(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo)
{
  Dem_SatelliteInfo_Type lReturnValue;                                                                                           /* PRQA S 0759 */ /* MD_MSR_Union */
  lReturnValue = SatelliteInfo;
  lReturnValue.Data.SatelliteStatus = (uint8)(lReturnValue.Data.SatelliteStatus | DEM_SATELLITEINFO_EVENTQUEUE_STATUS);
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteInfo_ResetEventQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_ResetEventQueueUpdated(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo  )
{
  Dem_SatelliteInfo_Type lReturnValue;                                                                                           /* PRQA S 0759 */ /* MD_MSR_Union */
  lReturnValue = SatelliteInfo;
  lReturnValue.Data.SatelliteStatus = (uint8)(lReturnValue.Data.SatelliteStatus & ~DEM_SATELLITEINFO_EVENTQUEUE_STATUS);
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteInfo_GetEventQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteInfo_GetEventQueueUpdated(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo
  )
{
  return (boolean)((SatelliteInfo.Data.SatelliteStatus & DEM_SATELLITEINFO_EVENTQUEUE_STATUS) != 0u);
}

/* ****************************************************************************
 % Dem_SatelliteInfo_SetPrestoreQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_SetPrestoreQueueUpdated(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo
  )
{
  Dem_SatelliteInfo_Type lReturnValue;                                                                                           /* PRQA S 0759 */ /* MD_MSR_Union */

  lReturnValue = SatelliteInfo;
  lReturnValue.Data.SatelliteStatus = (uint8)(lReturnValue.Data.SatelliteStatus | DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS);

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteInfo_ResetPrestoreQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_ResetPrestoreQueueUpdated(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo
  )
{
  Dem_SatelliteInfo_Type lReturnValue;                                                                                           /* PRQA S 0759 */ /* MD_MSR_Union */

  lReturnValue = SatelliteInfo;
  lReturnValue.Data.SatelliteStatus = (uint8)(lReturnValue.Data.SatelliteStatus & ~DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS);

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteInfo_GetPrestoreQueueUpdated
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
Dem_SatelliteInfo_GetPrestoreQueueUpdated(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo
  )
{
  boolean lReturnValue;

  lReturnValue = (boolean)((SatelliteInfo.Data.SatelliteStatus & DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS) != 0u);

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteInfo_SetStatusIndicatorQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_SetStatusIndicatorQueueUpdated(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_SatelliteInfo_Type SatelliteInfo
  )
{
  Dem_SatelliteInfo_Type lReturnValue;                                                                                           /* PRQA S 0759 */ /* MD_MSR_Union */

  lReturnValue = SatelliteInfo;
  lReturnValue.Data.SatelliteStatus = (uint8)(lReturnValue.Data.SatelliteStatus | DEM_SATELLITEINFO_STATUSINDICATOR_STATUS);

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteInfo_ResetStatusIndicatorQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_ResetStatusIndicatorQueueUpdated(                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_SatelliteInfo_Type SatelliteInfo
  )
{
  Dem_SatelliteInfo_Type lReturnValue;                                                                                           /* PRQA S 0759 */ /* MD_MSR_Union */

  lReturnValue = SatelliteInfo;
  lReturnValue.Data.SatelliteStatus = (uint8)(lReturnValue.Data.SatelliteStatus & ~DEM_SATELLITEINFO_STATUSINDICATOR_STATUS);

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteInfo_GetStatusIndicatorQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteInfo_GetStatusIndicatorQueueUpdated(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_SatelliteInfo_Type SatelliteInfo
  )
{
  return (boolean)((SatelliteInfo.Data.SatelliteStatus & DEM_SATELLITEINFO_STATUSINDICATOR_STATUS) != 0u);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_SATELLITEINFO_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_SatelliteInfo_Implementation.h
 *********************************************************************************************************************/
