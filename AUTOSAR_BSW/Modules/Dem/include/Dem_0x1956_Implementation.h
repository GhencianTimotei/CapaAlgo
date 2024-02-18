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
/*! \addtogroup Dem_0x1956
 *  \{
 *  \file       Dem_0x1956_Implementation.h
 *  \brief      Subcomponent for handling Service 0x19 Subfunction 0x56.
 *  \details    Subcomponent for handling Service 0x19 Subfunction 0x56, which filters DTCs and their UDS status that are part of a client requested readiness group.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_0X1956_IMPLEMENTATION_H)
#define DEM_0X1956_IMPLEMENTATION_H

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
#include "Dem_0x1956_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Core_Interface.h"
#include "Dem_Infrastructure_Interface.h"
#include "Dem_FilterDataIF_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

  /*! Filename declaration */
#define DEM_0X1956_IMPLEMENTATION_FILENAME "Dem_0x1956_Implementation.h"

 /* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
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
 * \defgroup Dem_0x1956_PrivateProperties Private Properties
 * \{
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

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
 * \addtogroup Dem_0x1956_PublicProperties
 * \{
 */

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
 * \defgroup Dem_0x1956_Private Private Methods
 * \{
 */


 /* ****************************************************************************
 * Dem_FilterData_0x1956_ReadinessTableIter_Exists
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
 *                Return value of Dem_FilterData_0x1956_ReadinessTableIter_Get() is valid
 * \return        FALSE
 *                Return value of Dem_FilterData_0x1956_ReadinessTableIter_Get() is invalid
 *
 * \pre           IterPtr has been initialized
 *                Feature Service 0x19 56 is enabled and DCM support is enabled
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_0x1956_ReadinessTableIter_Exists(
  CONSTP2CONST(Dem_FilterData_0x1956_ReadinessGroupIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_FilterData_0x1956_ReadinessTableIter_Get
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator
 *
 * \details       Get the element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        ReadinessGroup identifier
 *
 * \pre           IterPtr has been initialized
 *                Feature Service 0x19 56 is enabled and DCM support is enabled
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_ReadinessGroupOfReadinessGroupTableType, DEM_CODE)
Dem_FilterData_0x1956_ReadinessTableIter_Get(
  CONSTP2CONST(Dem_FilterData_0x1956_ReadinessGroupIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_FilterData_0x1956_ReadinessTableIter_Init
 *****************************************************************************/
/*!
 * \brief         Initialize the iterator
 *
 * \details       Initializes the iterator to enumerate data elements
 *
 * \param[out]    IterPtr
 *                Pointer to the iterator
 *
 * \pre           Feature Service 0x19 56 is enabled and DCM support is enabled
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_0x1956_ReadinessTableIter_Init(
  CONSTP2VAR(Dem_FilterData_0x1956_ReadinessGroupIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_FilterData_0x1956_ReadinessTableIter_Next
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
 *                Feature Service 0x19 56 is enabled and DCM support is enabled
 * \config        -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_0x1956_ReadinessTableIter_Next(
  CONSTP2VAR(Dem_FilterData_0x1956_ReadinessGroupIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);


/* ****************************************************************************
 * Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Exists
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
 *                Return value of Dem_FilterData_0x1956_ReadinessTableIter_Get() is valid
 * \return        FALSE
 *                Return value of Dem_FilterData_0x1956_ReadinessTableIter_Get() is invalid
 *
 * \pre           IterPtr has been initialized
 *                Feature Service 0x19 56 is enabled and DCM support is enabled
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Exists(
  CONSTP2CONST(Dem_FilterData_0x1956_ReadinessGroupIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Get
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator
 *
 * \details       Get the element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Event Id that has the Record Number Configured
 *                configured
 *
 * \pre           IterPtr has been initialized
 *                Feature Service 0x19 56 is enabled and DCM support is enabled
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Get(
  CONSTP2CONST(Dem_FilterData_0x1956_ReadinessGroupIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Init
 *****************************************************************************/
/*!
 * \brief         Initialize the iterator
 *
 * \details       Initializes the iterator to enumerate data elements
 *
 * \param[in]     ReadinessGroupIdx
 *                The index of the readiness group in the readiness group table
 * \param[out]    IterPtr
 *                Pointer to the iterator
 *
 * \pre           Feature Service 0x19 56 is enabled and DCM support is enabled
 *
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Init(
  uint8 ReadinessGroupIdx,
  CONSTP2VAR(Dem_FilterData_0x1956_ReadinessGroupIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_FilterData_0x1956_ReadinessTableIter_Next
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
 *                Feature Service 0x19 56 is enabled and DCM support is enabled
 * \config        -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Next(
  CONSTP2VAR(Dem_FilterData_0x1956_ReadinessGroupIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);


/* ****************************************************************************
 * Dem_FilterData_0x1956_FindReadinessGroupIndexByReadinessGroup
 *****************************************************************************/
/*!
 * \brief         Find a certain readiness group identifier in the readiness group table.
 *
 * \details       Find a certain readiness group identifier in the readiness group table.
 *
 * \param[in]     ReadinessGroup
 *                Readiness geoup identifier to find in readiness group table
 * \param[out]    ReadinessGroupTableIndex
 *                Index of the readiness group in readiness group table
 *
 * \pre           IterPtr has been initialized
 *                Feature Service 0x19 56 is enabled and DCM support is enabled
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_0x1956_FindReadinessGroupIndexByReadinessGroup(
  Dem_Cfg_ReadinessGroupOfReadinessGroupTableType ReadinessGroup,
  CONSTP2VAR(uint8, AUTOMATIC, AUTOMATIC) ReadinessGroupTableIndex
);

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/


 /* ****************************************************************************
 % Dem_FilterData_0x1956_ReadinessTableIter_Exists
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_0x1956_ReadinessTableIter_Exists(                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_FilterData_0x1956_ReadinessGroupIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}

/* ****************************************************************************
 % Dem_FilterData_0x1956_ReadinessTableIter_Get
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_ReadinessGroupOfReadinessGroupTableType, DEM_CODE)
Dem_FilterData_0x1956_ReadinessTableIter_Get(
  CONSTP2CONST(Dem_FilterData_0x1956_ReadinessGroupIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr);                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetReadinessGroupOfReadinessGroupTable(IterPtr->mIdx);
}

/* ****************************************************************************
 % Dem_FilterData_0x1956_ReadinessTableIter_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_0x1956_ReadinessTableIter_Init(
  CONSTP2VAR(Dem_FilterData_0x1956_ReadinessGroupIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  IterPtr->mIdx = 0u;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetSizeOfReadinessGroupTable();                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_FilterData_0x1956_ReadinessTableIter_Next
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_0x1956_ReadinessTableIter_Next(                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_FilterData_0x1956_ReadinessGroupIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                        /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
)
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Exists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Exists(                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_FilterData_0x1956_ReadinessGroupIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}

/* ****************************************************************************
 % Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Get
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Get(
  CONSTP2CONST(Dem_FilterData_0x1956_ReadinessGroupIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr);                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if DEM_CFG_SUPPORT_SVC19_56 == STD_ON
  return Dem_Cfg_GetEventTable_ObdRdyGroup2EventIdInd(IterPtr->mIdx);
#else
  return DEM_EVENT_INVALID;
#endif

}

/* ****************************************************************************
 % Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Init(
  uint8 ReadinessGroupIdx,
  CONSTP2VAR(Dem_FilterData_0x1956_ReadinessGroupIterType, AUTOMATIC, AUTOMATIC)  IterPtr
)
{
  
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ReadinessGroupIdx);                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */
  IterPtr->mIdx =    Dem_Cfg_GetEventTable_ObdRdyGroup2EventIdIndStartIdxOfReadinessGroupTable(ReadinessGroupIdx);               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetEventTable_ObdRdyGroup2EventIdIndEndIdxOfReadinessGroupTable(ReadinessGroupIdx);                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Next
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Next(                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_FilterData_0x1956_ReadinessGroupIterType, AUTOMATIC, AUTOMATIC)  IterPtr                                        /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
)
{
  IterPtr->mIdx += 1u;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}


/* ****************************************************************************
 % Dem_FilterData_0x1956_FindReadinessGroupIndexByReadinessGroup
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_0x1956_FindReadinessGroupIndexByReadinessGroup(
  Dem_Cfg_ReadinessGroupOfReadinessGroupTableType ReadinessGroup,
  CONSTP2VAR(uint8, AUTOMATIC, AUTOMATIC) ReadinessGroupTableIndex
)
{
  Dem_FilterData_0x1956_ReadinessGroupIterType lReadinessGroupTableIter;
  *ReadinessGroupTableIndex = 0u;                                                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

  /* Find the requested record */
  for (Dem_FilterData_0x1956_ReadinessTableIter_Init(&lReadinessGroupTableIter);                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_FilterData_0x1956_ReadinessTableIter_Exists(&lReadinessGroupTableIter) == TRUE;                                          /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_FilterData_0x1956_ReadinessTableIter_Next(&lReadinessGroupTableIter))                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    if (ReadinessGroup == Dem_FilterData_0x1956_ReadinessTableIter_Get(&lReadinessGroupTableIter))                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      *ReadinessGroupTableIndex = (uint8)lReadinessGroupTableIter.mIdx;                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      break;
    }
  }
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
 * \addtogroup Dem_0x1956_Public
 * \{
 */

 /* ****************************************************************************
 % Dem_FilterData_0x1956_IsService0x1956Enabled
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_0x1956_IsService0x1956Enabled(
  void
)
{
  return (boolean)(DEM_CFG_SUPPORT_SVC19_56 == STD_ON);
}


/* ****************************************************************************
 % Dem_FilterData_0x1956_SetDtcFilterByReadinessGroup
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_0x1956_SetDtcFilterByReadinessGroup(
  Dem_FilterData_HandleType DTCFilterId,
  Dem_Cfg_ReadinessGroupOfReadinessGroupTableType ReadinessGroup
)
{
  Dem_Cfg_FilterInfoTablePtrType lFilterDataPtr;
  lFilterDataPtr = Dem_Client_FilterData_GetFilterDataPtrSafe(DTCFilterId);

  lFilterDataPtr->FilterDtcStrategy = Dem_FilterData_FilterEventBased_ReadinessGroup;                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT_STRUCT_MEMBER */
  
  Dem_FilterData_0x1956_FindReadinessGroupIndexByReadinessGroup(ReadinessGroup, &lFilterDataPtr->TableIndex.ReadinessGroupIdx);  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT_STRUCT_MEMBER */
  Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Init(lFilterDataPtr->TableIndex.ReadinessGroupIdx,                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT_STRUCT_MEMBER */
                                                           &lFilterDataPtr->Iterator.ReadinessGroupIter);                          
                                                                                                                                 
  Dem_Client_FilterData_InitCombinedGroupProcessed(lFilterDataPtr);                                                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}


/* ****************************************************************************
 % Dem_FilterData_0x1956_GetNumberOfFilteredDTCsByReadinessGroup
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_FilterData_0x1956_GetNumberOfFilteredDTCsByReadinessGroup(                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  uint8 ReadinessGroupIdx
)
{
  uint16 lCount;
  Dem_FilterData_0x1956_ReadinessGroupIterType lReadinessGroupIter;
  Dem_Cfg_ProcessedCombinedDTCGroupType lProcessedCombinedDTCGroups;
  
  lCount = 0;
  Dem_DTC_InitCombinedGroupProcessed(lProcessedCombinedDTCGroups);                                                               /* SBSW_DEM_POINTER_FORWARD_STACK */


  for (Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Init(ReadinessGroupIdx, &lReadinessGroupIter);                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
    (Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Exists(&lReadinessGroupIter) == TRUE);                                 /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Next(&lReadinessGroupIter))                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lEventId;
    lEventId = Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Get(&lReadinessGroupIter);                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if ( (Dem_DTC_TestCombinedGroupProcessed(Dem_Cfg_EventCombinedGroup(lEventId), lProcessedCombinedDTCGroups) == FALSE )       /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */ /* SBSW_DEM_POINTER_FORWARD_STACK */
      && (Dem_Cfg_GetMemoryRepresentative(lEventId) == lEventId)
      && (Dem_Cfg_EventObdRelated(lEventId) == TRUE)
      && (Dem_DTC_TestSuppressionByRepresentiveEvent(lEventId) == FALSE))                                                        /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
    {
      Dem_DTC_SetCombinedGroupProcessed(Dem_Cfg_EventCombinedGroup(lEventId), lProcessedCombinedDTCGroups);                      /* SBSW_DEM_POINTER_FORWARD_STACK */
      lCount++;
    }
  }

  return lCount;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_FilterData_0x1956_FilterDTCByReadinessGroup
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
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_FilterData_0x1956_FilterDTCByReadinessGroup(                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  CONSTP2VAR(Dem_Cfg_FilterData_InfoType, AUTOMATIC, AUTOMATIC)  DTCFilterPtr                                                    /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  Dem_EventIdType lReturnEventIdValue;

  lReturnEventIdValue = DEM_EVENT_INVALID;

  for (/*Already initialzed on SetFilter - */;                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    (Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Exists(&DTCFilterPtr->Iterator.ReadinessGroupIter) == TRUE);           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Next(&DTCFilterPtr->Iterator.ReadinessGroupIter))                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {                                                                                                                              
    Dem_EventIdType lEventId;                                                                                                    
    lEventId = Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Get(&DTCFilterPtr->Iterator.ReadinessGroupIter);             /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if ( (Dem_Client_FilterData_TestCombinedGroupProcessed(Dem_Cfg_EventCombinedGroup(lEventId), DTCFilterPtr) == FALSE)                /* PRQA S 3415 */ /* MD_DEM_13.5_volatile */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      && (Dem_Cfg_GetMemoryRepresentative(lEventId) == lEventId)
      && (Dem_Cfg_EventObdRelated(lEventId) == TRUE)
      && (Dem_DTC_TestSuppressionByRepresentiveEvent(lEventId) == FALSE))                                                        /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
    {
      lReturnEventIdValue = lEventId;   
      Dem_Client_FilterData_SetCombinedGroupProcessed(Dem_Cfg_EventCombinedGroup(lEventId), DTCFilterPtr);                              /* PRQA S 2469 */ /* MD_DEM_14.2_FalsePositive */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      Dem_FilterData_0x1956_ReadinessGroupToEventTableIter_Next(&DTCFilterPtr->Iterator.ReadinessGroupIter);                     /* PRQA S 2469 */ /* MD_DEM_14.2_LoopControlHandledInternally */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
      break;
    }
  }

  return lReturnEventIdValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_0X1956_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_0x1956_Implementation.h
 *********************************************************************************************************************/
