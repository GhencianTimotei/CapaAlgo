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
/*! \addtogroup Dem_ClientData
 *  \{
 *  \file       Dem_ClientData_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) Implementation file
 *  \details    -
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_CLIENTDATA_IMPLEMENTATION_H)
#define DEM_CLIENTDATA_IMPLEMENTATION_H

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
#include "Dem_ClientData_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_RecordReader_Interface.h"
#include "Dem_ClientAccessIF_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_CLIENTDATA_IMPLEMENTATION_FILENAME "Dem_ClientData_Implementation.h"

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
 *  SUBCOMPONENT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


/*!
 * \addtogroup Dem_ClientData_PublicProperties
 * \{
 */

/* ****************************************************************************
 % Dem_ClientData_GetDTCSelector()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_HandleType, DEM_CODE)
Dem_ClientData_GetDTCSelector(
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  Dem_DTCSelector_HandleType lReturnValue;

  if (ClientId < Dem_Cfg_GetSizeOfClientTable())
  {
    lReturnValue = (Dem_DTCSelector_HandleType) Dem_Cfg_GetSelectorIndexOfClientTable(ClientId);
  }
  else
  {
    lReturnValue = DEM_CFG_DTCSELECTOR_INVALID;
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_ClientData_GetFilterId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FilterData_HandleType, DEM_CODE)
Dem_ClientData_GetFilterId(
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  Dem_FilterData_HandleType lReturnValue;

  if (ClientId < Dem_Cfg_GetSizeOfClientTable())
  {
    lReturnValue = (Dem_FilterData_HandleType) Dem_Cfg_GetFilterIndexOfClientTable(ClientId);
  }
  else
  {
    lReturnValue = DEM_CFG_FILTER_INVALID;
  }

  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_ClientData_GetFreezeFrameIteratorId
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FreezeFrameIterator_HandleType, DEM_CODE)
Dem_ClientData_GetFreezeFrameIteratorId(
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  Dem_FreezeFrameIterator_HandleType lReturnValue;

  if (ClientId < Dem_Cfg_GetSizeOfClientTable())
  {
    lReturnValue = (Dem_FreezeFrameIterator_HandleType)Dem_Cfg_GetFreezeFrameIteratorIndexOfClientTable(ClientId);
  }
  else
  {
    lReturnValue = DEM_CFG_FREEZEFRAMEITERATOR_INVALID;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_ClientData_GetReadoutBufferId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCReadoutBuffer_HandleType, DEM_CODE)
Dem_ClientData_GetReadoutBufferId(
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  Dem_DTCReadoutBuffer_HandleType lReturnValue;

  if (ClientId < Dem_Cfg_GetSizeOfClientTable())
  {
    lReturnValue = (Dem_DTCReadoutBuffer_HandleType) Dem_Cfg_GetReadoutBufferIndexOfClientTable(ClientId);
  }
  else
  {
    lReturnValue = DEM_CFG_READOUTBUFFER_INVALID;
  }

  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_ClientData_GetClearDTCStatusHandle()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ClearDTC_HandleType, DEM_CODE)
Dem_ClientData_GetClearDTCStatusHandle(
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  Dem_ClearDTC_HandleType lReturnValue;

  if (ClientId < Dem_Cfg_GetSizeOfClientTable())
  {
    lReturnValue = (Dem_ClearDTC_HandleType)Dem_Cfg_GetClearDTCIndexOfClientTable(ClientId);
  }
  else
  {
    lReturnValue = DEM_CLEARDTC_HANDLE_INVALID;
  }

  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_ClientData_GetNodeId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_ClientData_GetNodeId(
  uint8 ClientId
  )
{
  uint16 lReturnValue;

  if (ClientId < Dem_Cfg_GetSizeOfClientTable())
  {
    lReturnValue = Dem_Cfg_GetNmNodeIdOfClientTable(ClientId);
  }
  else
  {
    lReturnValue = DEM_CFG_NMNODEID_INVALID;
  }

  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_ClientData_GetExtendedDataFilterId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC( Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType, DEM_CODE)
Dem_ClientData_GetExtendedDataFilterId(
  uint8 ClientId
)
{
   Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType lReturnValue;

  if (ClientId < Dem_Client_ClientAccess_GlobalClientCount())
  {
    lReturnValue = ( Dem_Dcm_ERec_0x1916_RecordNumberFilter_HandleType)ClientId;
  }
  else
  {
    lReturnValue = DEM_CFG_FILTER_INVALID;
  }

  return lReturnValue;
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* DEM_CLIENTDATA_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ClientData_Implementation.h
 *********************************************************************************************************************/
