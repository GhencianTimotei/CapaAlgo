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
/*! \addtogroup Dem_UDSStatus
 *  \{
 *  \file       Dem_UDSStatus_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of EventUDSStatus subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_EVENTUDSSTATUS_IMPLEMENTATION_H)
#define DEM_EVENTUDSSTATUS_IMPLEMENTATION_H

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
#include "Dem_UDSStatus_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_UDSSTATUS_IMPLEMENTATION_FILENAME "Dem_UDSStatus_Implementation.h"

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
 * \defgroup Dem_UDSStatus_PrivateProperties Private Properties
 * \{
 */
/* ****************************************************************************
 * Dem_UDSStatus_Test_TNCSLC
 *****************************************************************************/
/*!
 * \brief         Test test not completed since last clear state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        TRUE
 *                The TNCSLC bit is set
 * \return        FALSE
 *                The TNCSLC bit is not set
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_TNCSLC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );


/* ****************************************************************************
 * Dem_UDSStatus_Set_TNCSLC
 *****************************************************************************/
/*!
 * \brief         Set test not completed since last clear state of UDS status byte
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current UDS status of the event
 *
 * \return        Status with test TNCSLC bit set

 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_TNCSLC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  );


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
 

/* ****************************************************************************
 % Dem_UDSStatus_Test_TNCSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_TNCSLC(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_TNCSLC) != 0u);
}

 

/* ****************************************************************************
 % Dem_UDSStatus_Set_TNCSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_TNCSLC(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) | DEM_UDS_STATUS_TNCSLC);
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
 * \addtogroup Dem_UDSStatus_PublicProperties
 * \{
 */


 /* ****************************************************************************
 % Dem_UDSStatus_Test_TF()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_TF(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_TF) != 0u);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Set_TF()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_TF(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) | DEM_UDS_STATUS_TF);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Reset_TF()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_TF(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) & DEM_UDS_STATUS_TF_MASK);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Test_TFTOC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_TFTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_TFTOC) != 0u);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Set_TFTOC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_TFTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) | DEM_UDS_STATUS_TFTOC);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Reset_TFTOC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_TFTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) & DEM_UDS_STATUS_TFTOC_MASK);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Test_PDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_PDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_PDTC) != 0u);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Set_PDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_PDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) | DEM_UDS_STATUS_PDTC);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Reset_PDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_PDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) & DEM_UDS_STATUS_PDTC_MASK);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Test_CDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_CDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_CDTC) != 0u);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Set_CDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_CDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) | DEM_UDS_STATUS_CDTC);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Reset_CDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_CDTC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) & DEM_UDS_STATUS_CDTC_MASK);
}
 

/* ****************************************************************************
 % DemDem_UDSStatus_Reset_TNCSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_TNCSLC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) & DEM_UDS_STATUS_TNCSLC_MASK);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Test_TFSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_TFSLC(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_TFSLC) != 0u);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Set_TFSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_TFSLC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) | DEM_UDS_STATUS_TFSLC);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Reset_TFSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_TFSLC(                                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) & DEM_UDS_STATUS_TFSLC_MASK);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Test_TNCTOC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_TNCTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_TNCTOC) != 0u);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Set_TNCTOC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_TNCTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) | DEM_UDS_STATUS_TNCTOC);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Reset_TNCTOC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_TNCTOC(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) & DEM_UDS_STATUS_TNCTOC_MASK);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Test_WIR()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_Test_WIR(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_WIR) != 0u);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Set_WIR()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Set_WIR(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
  return (Dem_UDSStatus_Type)((Status) | DEM_UDS_STATUS_WIR);
}
 

/* ****************************************************************************
 % Dem_UDSStatus_Reset_WIR()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_UDSStatus_Reset_WIR(
CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
)
{
  return (Dem_UDSStatus_Type)((Status)& DEM_UDS_STATUS_WIR_MASK);
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
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_UDSStatus_Public
 * \{
 */

/* ****************************************************************************
 % Dem_UDSStatus_IsNvRelevantStatusChange
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_UDSStatus_IsNvRelevantStatusChange(
  CONST(uint8, AUTOMATIC)  OldEventStatus,
  CONST(uint8, AUTOMATIC)  NewEventStatus
  )
{
  boolean returnValue;

#if (DEM_CFG_USE_NVM == STD_OFF)                                                                                                 /* PRQA S 0883 */ /* MD_DEM_19.15 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(OldEventStatus)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NewEventStatus)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */

  returnValue = FALSE;
#elif (DEM_CFG_SUPPORT_TESTFAILED_STORAGE == STD_ON)
  returnValue = OldEventStatus != NewEventStatus;
#else
   /* Ignore TF bit */
  returnValue = ((OldEventStatus ^ NewEventStatus) & (uint8)DEM_UDS_STATUS_TF_MASK) != 0u;
#endif

  return returnValue;
}


/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* DEM_EVENTUDSSTATUS_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_UDSStatus_Implementation.h
 *********************************************************************************************************************/
