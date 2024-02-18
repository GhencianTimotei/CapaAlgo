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
/*! \addtogroup Dem_Prestore
 *  \{
 *  \file       Dem_Prestore_Implementation.h
 *  \brief      Stores and manages 'prestored freezeframes'.
 *  \details    Pre-store snapshot data for an event, in order to freeze that data set when the event is stored later.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_PRESTORE_IMPLEMENTATION_H)
#define DEM_PRESTORE_IMPLEMENTATION_H

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
#include "Dem_Prestore_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Core_Interface.h"
#include "Dem_Infrastructure_Interface.h"
#include "Dem_Satellite_Interface.h"
#include "Dem_DataStorage_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_PRESTORE_IMPLEMENTATION_FILENAME "Dem_Prestore_Implementation.h"

/*!
 * \defgroup  Dem_Prestored_PrestoredStatus  Macros encoding prestored status states
 * Macros encoding prestored status states
 * \{
 */
#define DEM_PRESTORE_STATUS_FREE                                               (0x00U)  /*!< Prestored entry is free */
#define DEM_PRESTORE_STATUS_READY                                              (0x01U)  /*!< Prestored entry contains valid data */
#define DEM_PRESTORE_STATUS_UPDATING                                           (0x02U)  /*!< Prestored entry is updating data */
#define DEM_PRESTORE_STATUS_LOCKED                                             (0x03U)  /*!< Prestored entry is locked */
#define DEM_PRESTORE_STATUS_DISCARDED                                          (0x04U)  /*!< Prestored entry is locked and needs to be freed */
/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/*! Start of prestorage entry free list - index of first free buffer (linked list) or DEM_PRESTORE_INVALID_BUFFER_ENTRY with empty free list */
DEM_LOCAL VAR(Dem_Cfg_PrestorageIndexType, DEM_VAR_NOINIT)  Dem_Prestore_FreeListHeadIndex;
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/*! Prestorage entry locked for status processing */
DEM_LOCAL VAR(Dem_Cfg_PrestorageIndexType, DEM_VAR_NOINIT)  Dem_Prestore_LockedIndex;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_Prestore_PublicProperties
 * \{
 */

 /* ****************************************************************************
 % Dem_Prestore_isPrestoreFFEnabled()
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Prestore_isPrestoreFFEnabled(void)
{
  return (boolean)(DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON);
}

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_GetLockedIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_PrestorageIndexType, DEM_CODE)
Dem_Prestore_GetLockedIndex(                                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return Dem_Prestore_LockedIndex;
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_PrestorageEntryGetGlobalSRecDataPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetGlobalSRecDataPtr(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  )
{
  Dem_DataPtrType lPrestorageSnapshot;

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (PrestorageEntry > Dem_Cfg_GlobalPrestorageSize())
  {
    Dem_Error_RunTimeCheckFailed(DEM_PRESTORE_IMPLEMENTATION_FILENAME, __LINE__);                                                /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lPrestorageSnapshot = &(Dem_Cfg_GetPrestorage()[0].GlobalSnapshotData[0]);
  }
  else
# endif
  {
    lPrestorageSnapshot = &(Dem_Cfg_GetPrestorage()[PrestorageEntry].GlobalSnapshotData[0]);
  }

  return lPrestorageSnapshot;
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_PrestorageEntryGetSRecDataPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetSRecDataPtr(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  )
{
  Dem_DataPtrType lPrestorageSnapshot;

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (PrestorageEntry > Dem_Cfg_GlobalPrestorageSize())
  {
    Dem_Error_RunTimeCheckFailed(DEM_PRESTORE_IMPLEMENTATION_FILENAME, __LINE__);                                                /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lPrestorageSnapshot = &(Dem_Cfg_GetPrestorage()[0].SnapshotData[0]);
  }
  else
# endif
  {
    lPrestorageSnapshot = &(Dem_Cfg_GetPrestorage()[PrestorageEntry].SnapshotData[0]);
  }

  return lPrestorageSnapshot;
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_PrestorageEntryGetObdIIFFDataPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetObdIIFFDataPtr(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  )
{
  Dem_DataPtrType lPrestorageOBDIIFreezeFrame;

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (PrestorageEntry > Dem_Cfg_GlobalPrestorageSize())
  {
    Dem_Error_RunTimeCheckFailed(DEM_PRESTORE_IMPLEMENTATION_FILENAME, __LINE__);                                                /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lPrestorageOBDIIFreezeFrame = &(Dem_Cfg_GetPrestorage()[0].ObdFreezeFrame[0]);
  }
  else
# endif
  {
    lPrestorageOBDIIFreezeFrame = &(Dem_Cfg_GetPrestorage()[PrestorageEntry].ObdFreezeFrame[0]);
  }

  return lPrestorageOBDIIFreezeFrame;
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) && ((DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON) || (DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON))
/* ****************************************************************************
 % Dem_Prestore_PrestorageEntryGetJ1939FFDataPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetJ1939FFDataPtr(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  )
{
  Dem_DataPtrType lReturnValue;

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (PrestorageEntry > Dem_Cfg_GlobalPrestorageSize())
  {
    Dem_Error_RunTimeCheckFailed(DEM_PRESTORE_IMPLEMENTATION_FILENAME, __LINE__);                                                /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = &(Dem_Cfg_GetPrestorage()[0].J1939FreezeFrame[0]);
  }
  else
# endif
  {
    lReturnValue = &(Dem_Cfg_GetPrestorage()[PrestorageEntry].J1939FreezeFrame[0]);
  }
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) && (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_PrestorageEntryGetWwhObdFFDataPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetWwhObdFFDataPtr(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  )
{
  Dem_DataPtrType lPrestorageSnapshot;
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (PrestorageEntry > Dem_Cfg_GlobalPrestorageSize())
  {
    Dem_Error_RunTimeCheckFailed(DEM_PRESTORE_IMPLEMENTATION_FILENAME, __LINE__);                                                /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lPrestorageSnapshot = &(Dem_Cfg_GetPrestorage()[0].ObdFreezeFrameData[0]);
  }
  else
# endif
  {
    lPrestorageSnapshot = &(Dem_Cfg_GetPrestorage()[PrestorageEntry].ObdFreezeFrameData[0]);
  }
  return lPrestorageSnapshot;
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Prestore_Private Private Methods
 * \{
 */


#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntry_Checked
 *****************************************************************************/
/*!
 * \brief         Check position 'PrestorageEntry' for being a valid index.
 *
 * \details       If run-time checks are enabled, check index 'PrestorageEntry'. 
 *                When the check fails, return the 'invalid' prestorage entry
 *                that points to an existing temporary buffer element.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        Without runtime checks: argument 'PrestorageEntry'.
 * \return        With runtime checks: 'PrestorageEntry' for valid positions,
 *                otherwise DEM_PRESTORE_INVALID_BUFFER_ENTRY (which is the
 *                position of the temporary buffer element).
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_PrestorageIndexType, DEM_CODE)
Dem_Prestore_PrestorageEntry_Checked(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC) PrestorageEntry
  );
#endif


#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntryGetEventId
 *****************************************************************************/
/*!
 * \brief         Get the EventId of a prestored entry.
 *
 * \details       Get the EventId of a prestored entry. The requested entry
 *                must be allocated and not be part of the free list.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        EventId that has set this prestored entry.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetEventId(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );
#endif


#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntrySetEventId
 *****************************************************************************/
/*!
 * \brief         Set the EventId of a prestored entry.
 *
 * \details       Set EventId of a prestored entry.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 * \param[in]     EventId
 *                New EventId for the entry.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_PrestorageEntrySetEventId(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_FreeListGetNext
 *****************************************************************************/
/*!
 * \brief         Get the next prestorage entry from the list of free buffers.
 *
 * \details       Get the immediate following entry from the linked list of
 *                free buffers.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        Next prestored entry.
 * \return        DEM_PRESTORE_INVALID_BUFFER_ENTRY
 *                No next prestorage entry.
 *
 * \pre           'PrestorageEntry' is part of the free list.
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_PrestorageIndexType, DEM_CODE)
Dem_Prestore_FreeListGetNext(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );
#endif


#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_FreeListSetNext
 *****************************************************************************/
/*!
 * \brief         Set the 'next' prestorage entry (for list of free buffers).
 *
 * \details       Set the 'PrestorageEntry' to link to the
 *                'NextPrestorageEntry'. This inserts this entry in the list of
 *                free buffers.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 * \param[in]     NextPrestorageEntry
 *                Next free prestorage entry after 'PrestorageEntry'. Use
 *                DEM_PRESTORE_INVALID_BUFFER_ENTRY for no-next-element.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_FreeListSetNext(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry,
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  NextPrestorageEntry
  );
#endif


#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntryGetState
 *****************************************************************************/
/*!
 * \brief         Get the state of a prestored entry.
 *
 * \details       Get the state of a prestored entry.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        DEM_PRESTORE_STATUS_FREE
 *                Prestored entry is free.
 * \return        DEM_PRESTORE_STATUS_READY
 *                Prestored entry contains valid data.
 * \return        DEM_PRESTORE_STATUS_UPDATING
 *                Prestored entry is updating data.
 * \return        DEM_PRESTORE_STATUS_LOCKED
 *                Prestored entry is locked.
 * \return        DEM_PRESTORE_STATUS_DISCARDED
 *                Prestored entry needs to be freed.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Prestore_PrestorageEntryGetState(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );
#endif


#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntrySetState
 *****************************************************************************/
/*!
 * \brief         Set the state of a prestored entry.
 *
 * \details       Set state of a prestored entry.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 * \param[in]     State
 *                New state for the entry.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_PrestorageEntrySetState(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry,
  CONST(uint8, AUTOMATIC)  State
  );
#endif


#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_SetPrestorageEntry
 *****************************************************************************/
/*!
 * \brief         Set the prestorage buffer slot, allocated to the event.
 *
 * \details       Set the prestorage buffer, that is allocated to the event.
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \param[in]     PrestorageEntry
 *                Prestorage buffer slot (currently) allocated to the event.
 *                DEM_PRESTORE_INVALID_BUFFER_ENTRY is '(currently) no buffer'.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_SetPrestorageEntry(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );
#endif


#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntryUpdate
 *****************************************************************************/
/*!
 * \brief         Samples all event related data into a prestorage entry
 *
 * \details       Samples all event related data into a prestorage entry
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     PrestorageEntry
 *                Position of the prestorage entry.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_PrestorageEntryUpdate(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );
#endif


#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_GetPrestorageEntry
 *****************************************************************************/
/*!
 * \brief         Locates the prestored data entry of an event.
 *
 * \details       This function looks up the prestorage entry for the given
 *                event, and returns its handle (position in buffer).
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *                The event must have configured prestorage.
 *
 * \return        Position in Prestorage buffer.
 *
 * \pre           The event must support prestorage, always proove that before
 *                by calling Dem_Cfg_EventPrestorageIndex(EventId). If run-time
 *                checks are enabled, a violation of this precondition will
 *                return DEM_PRESTORE_INVALID_BUFFER_ENTRY.
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_PrestorageIndexType, DEM_CODE)
Dem_Prestore_GetPrestorageEntry(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_AllocatePrestorageEntry
 *****************************************************************************/
/*!
 * \brief         Allocates a new prestored entry for an event
 *
 * \details       This function consumes the next free prestorage entry (if
 *                available) and allocates it to the given event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Index into Prestorage area, if one was found.
 *                DEM_PRESTORE_INVALID_BUFFER_ENTRY otherwise.
 *
 * \pre           The event must support prestorage
 * \pre           The event must not have a prestored entry
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_PrestorageIndexType, DEM_CODE)
Dem_Prestore_AllocatePrestorageEntry(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_FreePrestorageEntry
 *****************************************************************************/
/*!
 * \brief         Free a prestored entry
 *
 * \details       This function removes the ownership of the prestored entry
 *                buffer and returns it to the free list.
 *
 * \param[in]     PrestorageEntry
 *                Prestored entry to free
 *
 * \pre           Must be called within critical section 'DiagMonitor'
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_FreePrestorageEntry(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );
#endif


/* ****************************************************************************
 * Dem_Prestore_EventPrestorageUpdate
 *****************************************************************************/
/*!
 * \brief         Store prestored data for an event
 *
 * \details       This function tries to find a prestorage entry for the given
 *                event, allocating a new one if needed.
 *                If a prestorage entry is found, it is updated with sample
 *                data.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        E_OK
 *                Prestored data was successfully collected
 * \return        E_NOT_OK
 *                No data was collected
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Prestore_EventPrestorageUpdate(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );


/* ****************************************************************************
 * Dem_Prestore_ProcessSatelliteQueueActions
 *****************************************************************************/
/*!
 * \brief         Processes all queued prestore actions.
 *
 * \details       This function processes queued prestore actions for all
 *                events of the given satellite.
 *
 * \param[in]     SatelliteId
 *                Unique handle of the Satellite.
 *                The SatelliteId must be in range [1..Dem_Cfg_GlobalSatelliteCount()[.
 *
 * \pre           Function must only be invoked when the features "Prestorage of
 *                freeze frames" and "Multiple Satellites" are supported.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_ProcessSatelliteQueueActions(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );


#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_PrestorageEntry_Checked
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_PrestorageIndexType, DEM_CODE)
Dem_Prestore_PrestorageEntry_Checked(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  )
{
  Dem_Cfg_PrestorageIndexType lReturnValue;

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (PrestorageEntry > Dem_Cfg_GlobalPrestorageSize())
  {
    Dem_Error_RunTimeCheckFailed(DEM_PRESTORE_IMPLEMENTATION_FILENAME, __LINE__);                                                /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    /* return index of the temporary buffer */
    lReturnValue = Dem_Cfg_GlobalPrestorageSize();
  }
  else
# endif
  {
    lReturnValue = PrestorageEntry;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_PrestorageEntryGetEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetEventId(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  )
{
  return Dem_Cfg_GetPrestorage()[PrestorageEntry].EventId;
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_PrestorageEntrySetEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_PrestorageEntrySetEventId(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Cfg_GetPrestorage()[Dem_Prestore_PrestorageEntry_Checked(PrestorageEntry)].EventId = EventId;                              /* SBSW_DEM_ARRAY_WRITE_PRESTORAGE */
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_FreeListGetNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_PrestorageIndexType, DEM_CODE)
Dem_Prestore_FreeListGetNext(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  )
{
  return (Dem_Cfg_PrestorageIndexType) Dem_Cfg_GetPrestorage()[PrestorageEntry].EventId;
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_FreeListSetNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_FreeListSetNext(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry,
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  NextPrestorageEntry
  )
{
  Dem_Cfg_GetPrestorage()[Dem_Prestore_PrestorageEntry_Checked(PrestorageEntry)].EventId = (Dem_EventIdType)NextPrestorageEntry; /* SBSW_DEM_ARRAY_WRITE_PRESTORAGE */
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_PrestorageEntryGetState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Prestore_PrestorageEntryGetState(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  )
{
  return Dem_Cfg_GetPrestorage()[PrestorageEntry].State;
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_PrestorageEntrySetState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_PrestorageEntrySetState(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry,
  CONST(uint8, AUTOMATIC)  State
  )
{
  Dem_Cfg_GetPrestorage()[ Dem_Prestore_PrestorageEntry_Checked(PrestorageEntry) ].State = State;                                /* SBSW_DEM_ARRAY_WRITE_PRESTORAGE */
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_SetPrestorageEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_SetPrestorageEntry(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (Dem_Cfg_EventPrestorageIndex(EventId) >= Dem_Cfg_GetSizeOfPrestorageIndex())
  {
    Dem_Error_RunTimeCheckFailed(DEM_PRESTORE_IMPLEMENTATION_FILENAME, __LINE__);                                                /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_SetPrestorageIndex(Dem_Cfg_EventPrestorageIndex(EventId), PrestorageEntry);                                          /* SBSW_DEM_ARRAY_WRITE_PRESTORAGEINDEX */
  }
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_PrestorageEntryUpdate
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_PrestorageEntryUpdate(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry                                                                 /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(PrestorageEntry)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
  /* Collect a global snapshot record into the prestorage buffer */
  Dem_DataStorage_CollectGlobalSnapshot(EventId,                                                                               /* SBSW_DEM_POINTER_PRESTORAGE_GLOBAL_SNAPSHOT_BUFFER */
                                          Dem_Prestore_PrestorageEntryGetGlobalSRecDataPtr(PrestorageEntry),
                                          Dem_Cfg_GlobalSRecMaxRawSize());
#endif
# if (DEM_CFG_SUPPORT_SRECS == STD_ON)
  /* Sample a UDS snapshot into the prestorage buffer */
  Dem_DataStorage_CollectSnapshot(EventId,                                                                                     
                                    Dem_Prestore_PrestorageEntryGetSRecDataPtr(PrestorageEntry),                                 /* SBSW_DEM_POINTER_PRESTORAGE_SNAPSHOT_BUFFER */
                                    Dem_Cfg_EventSRecMaxRawSize());
# endif

  if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
  {
    /* If the event is OBD relevant, sample an OBD freeze frame into the prestorage buffer */
#  if (DEM_CFG_SUPPORT_OBDII == STD_ON)
    if (Dem_Cfg_IsObdIISupportedInVariant() == TRUE)
    {
      Dem_DataStorage_CollectObdIIFreezeFrame(EventId,
        Dem_Prestore_PrestorageEntryGetObdIIFFDataPtr(PrestorageEntry),                                                          /* SBSW_DEM_POINTER_PRESTORAGE_OBD_FREEZEFRAME_BUFFER */
        Dem_Cfg_GlobalObdFreezeFrameMaxSize());
    }
#  endif
    /* If the event is WWH-OBD relevant, sample a WWH-OBD freeze frame into the prestorage buffer */
#  if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
    if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
    {
      Dem_DataStorage_CollectWwhObdFreezeFrame(EventId,                                                                        /* SBSW_DEM_POINTER_PRESTORAGE_WWHOBDFREEZEFRAME_BUFFER */
        Dem_Prestore_PrestorageEntryGetWwhObdFFDataPtr(PrestorageEntry),
        Dem_Cfg_GlobalPrestoredWwhobdFreezeFrameDataSize());
    }
#  endif
  }

# if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
  /* If the event has a J1939 DTC, sample the SPNs into the prestorage buffer */
  if (Dem_Cfg_EventJ1939Dtc(EventId) != DEM_CFG_DTC_J1939_INVALID)
  {
    Dem_DataStorage_CollectJ1939FreezeFrame(EventId,                                                                           /* SBSW_DEM_POINTER_PRESTORAGE_J1939FREEZEFRAME_BUFFER */
                                              Dem_Prestore_PrestorageEntryGetJ1939FFDataPtr(PrestorageEntry),
                                              Dem_Cfg_GlobalJ1939FFTotalRawSize());
  }
# endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_GetPrestorageEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_PrestorageIndexType, DEM_CODE)
Dem_Prestore_GetPrestorageEntry(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Internal_AssertReturnValue(DEM_PRESTORE_NOT_CONFIGURED_FOR_EVENT != Dem_Cfg_EventPrestorageIndex(EventId), DEM_E_PARAM_DATA, DEM_PRESTORE_INVALID_BUFFER_ENTRY)
  return Dem_Cfg_GetPrestorageIndex(Dem_Cfg_EventPrestorageIndex(EventId));
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_AllocatePrestorageEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_PrestorageIndexType, DEM_CODE)
Dem_Prestore_AllocatePrestorageEntry(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Cfg_PrestorageIndexType lPrestorageEntryFirstUnused;
  Dem_Internal_AssertReturnValue((DEM_PRESTORE_INVALID_BUFFER_ENTRY <= Dem_Prestore_GetPrestorageEntry(EventId)), DEM_E_PARAM_DATA, DEM_PRESTORE_INVALID_BUFFER_ENTRY)

  lPrestorageEntryFirstUnused = Dem_Prestore_FreeListHeadIndex;
  if (lPrestorageEntryFirstUnused != DEM_PRESTORE_INVALID_BUFFER_ENTRY)
  {
    /* shorten the free list by removing its first element */
    Dem_Prestore_FreeListHeadIndex = Dem_Prestore_FreeListGetNext(lPrestorageEntryFirstUnused);
    /* connect the event with the buffer slot */
    Dem_Prestore_SetPrestorageEntry(EventId, lPrestorageEntryFirstUnused);
    /* fill the buffer slot with the EventId */
    Dem_Prestore_PrestorageEntrySetEventId(lPrestorageEntryFirstUnused, EventId);
  }

  return lPrestorageEntryFirstUnused;
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_FreePrestorageEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_FreePrestorageEntry(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  )
{
  Dem_Internal_AssertReturnVoid(DEM_PRESTORE_INVALID_BUFFER_ENTRY != PrestorageEntry, DEM_E_PARAM_DATA)

  /* un-connect the event from the buffer slot */
  Dem_Prestore_SetPrestorageEntry(Dem_Prestore_PrestorageEntryGetEventId(PrestorageEntry), DEM_PRESTORE_INVALID_BUFFER_ENTRY);

  /* enqueue the buffer slot as first element in the free list */
  Dem_Prestore_FreeListSetNext(PrestorageEntry, Dem_Prestore_FreeListHeadIndex);
  Dem_Prestore_FreeListHeadIndex = PrestorageEntry;
}
#endif

/* ****************************************************************************
 % Dem_Prestore_EventPrestorageUpdate
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Prestore_EventPrestorageUpdate(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Std_ReturnType lReturnValue;

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
  Dem_Cfg_PrestorageIndexType lPrestorageEntry;

/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
  Dem_EnterCritical_DiagMonitor();

  lPrestorageEntry = Dem_Prestore_GetPrestorageEntry(EventId);
  if (lPrestorageEntry < DEM_PRESTORE_INVALID_BUFFER_ENTRY)
  { /* there already is an entry allocated to this event */
    Dem_Prestore_PrestorageEntrySetState(lPrestorageEntry, DEM_PRESTORE_STATUS_UPDATING);
  }
  else
  { /* try to find a free entry for this event */
    lPrestorageEntry = Dem_Prestore_AllocatePrestorageEntry(EventId);
    if (lPrestorageEntry != DEM_PRESTORE_INVALID_BUFFER_ENTRY)
    {
      Dem_Prestore_PrestorageEntrySetState(lPrestorageEntry, DEM_PRESTORE_STATUS_UPDATING);
    }
  }

  Dem_LeaveCritical_DiagMonitor();
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

  if (lPrestorageEntry < DEM_PRESTORE_INVALID_BUFFER_ENTRY)
  {
    Dem_Prestore_PrestorageEntryUpdate(EventId, lPrestorageEntry);
    Dem_Prestore_PrestorageEntrySetState(lPrestorageEntry, DEM_PRESTORE_STATUS_READY);
    lReturnValue = E_OK;
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }

#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = E_NOT_OK;
#endif

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Prestore_ProcessSatelliteQueueActions
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_ProcessSatelliteQueueActions(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  Dem_Satellite_MonitorIdType lMonitorId;

  for (lMonitorId = 0u;
       lMonitorId < Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId);
       ++lMonitorId)
  {
    if (Dem_Satellite_PeekPrestoreActionQueue(SatelliteId, lMonitorId) != DEM_PRESTORE_QUEUE_INITIAL)
    {
      Dem_Prestore_QueueActionType lPrestoreQueueStatus;                                                                         /* PRQA S 0759 */ /* MD_MSR_Union */
      Dem_EventIdType lEventId;

      lEventId = Dem_Satellite_GetEventId(SatelliteId, lMonitorId);
      lPrestoreQueueStatus = Dem_Satellite_ConsumePrestoreActionQueue(SatelliteId, lMonitorId);

# if (DEM_DEV_ERROR_REPORT == STD_ON)
      /*Only events configured for prestorage should be processed here*/
      Dem_Internal_AssertContinue((Dem_Cfg_EventPrestorageIndex(lEventId) != DEM_PRESTORE_NOT_CONFIGURED_FOR_EVENT), DEM_E_INCONSISTENT_STATE)
      /*Only events not assigned to the master partition should be processed here*/
      Dem_Internal_AssertContinue((Dem_Satellite_CheckEventApplicationId(lEventId) == FALSE), DEM_E_INCONSISTENT_STATE)
# endif

      if (lPrestoreQueueStatus == DEM_PRESTORE_QUEUE_PRESTOREFF)
      {
        (void)Dem_Prestore_EventPrestorageUpdate(lEventId);
      }
      else
      {
        (void)Dem_Prestore_EventPrestorageClear(lEventId);
      }
      
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
 * \addtogroup Dem_Prestore_Public
 * \{
 */

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_Init
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
Dem_Prestore_Init(
  void
  )
{
  Dem_Cfg_PrestorageIndexType lPrestorageEntry;
  uint16_least lPrestorageIndex;

  /* here: initialize the temporary element too, so DEM_PRESTORE_INVALID_BUFFER_ENTRY is the last valid index */
  for (lPrestorageEntry = 0u; lPrestorageEntry < DEM_PRESTORE_INVALID_BUFFER_ENTRY; ++lPrestorageEntry)
  { /* Chain the blocks */
    Dem_Prestore_PrestorageEntrySetState(lPrestorageEntry, DEM_PRESTORE_STATUS_FREE);
    Dem_Prestore_FreeListSetNext(lPrestorageEntry, (Dem_Cfg_PrestorageIndexType)(lPrestorageEntry + 1u));
  }
  /* Last block points to end, head points to first block */
  Dem_Prestore_PrestorageEntrySetState(DEM_PRESTORE_INVALID_BUFFER_ENTRY, DEM_PRESTORE_STATUS_FREE);
  Dem_Prestore_FreeListSetNext(DEM_PRESTORE_INVALID_BUFFER_ENTRY, DEM_PRESTORE_INVALID_BUFFER_ENTRY);
  Dem_Prestore_FreeListHeadIndex = 0u;

  /* no event has currantly allocated a buffer */
  for (lPrestorageIndex = 0u; lPrestorageIndex < Dem_Cfg_GetSizeOfPrestorageIndex(); ++lPrestorageIndex)
  {
    Dem_Cfg_SetPrestorageIndex(lPrestorageIndex, DEM_PRESTORE_INVALID_BUFFER_ENTRY);                                             /* SBSW_DEM_ARRAY_WRITE_PRESTORAGEINDEX */
  }

  /* Initialize the prestorage lock state */
  Dem_Prestore_LockedIndex = DEM_PRESTORE_INVALID_BUFFER_ENTRY;

  /* Set prestorage tasks on scheduler to enabled*/
  Dem_Scheduler_EnableTask(Dem_Scheduler_Task_Prestorage);
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_StateSetDiscard
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_StateSetDiscard(
  void
  )
{
  if (Dem_Prestore_LockedIndex != DEM_PRESTORE_INVALID_BUFFER_ENTRY)
  {
    Dem_Prestore_PrestorageEntrySetState(Dem_Prestore_LockedIndex, DEM_PRESTORE_STATUS_DISCARDED);
  }
}
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_EventPrestorageLock
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
Dem_Prestore_EventPrestorageLock(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Cfg_PrestorageIndexType lPrestoredEntry;

  if (Dem_Cfg_EventPrestorageIndex(EventId) != DEM_PRESTORE_NOT_CONFIGURED_FOR_EVENT)
  {
    lPrestoredEntry = Dem_Prestore_GetPrestorageEntry(EventId);
    if (lPrestoredEntry < DEM_PRESTORE_INVALID_BUFFER_ENTRY)
    {
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
      Dem_EnterCritical_DiagMonitor();

      if (Dem_Prestore_PrestorageEntryGetState(lPrestoredEntry) == DEM_PRESTORE_STATUS_READY)
      {
        Dem_Prestore_PrestorageEntrySetState(lPrestoredEntry, DEM_PRESTORE_STATUS_LOCKED);
        Dem_Prestore_SetPrestorageEntry(EventId, DEM_PRESTORE_INVALID_BUFFER_ENTRY);
        Dem_Prestore_LockedIndex = lPrestoredEntry;
      }

      Dem_LeaveCritical_DiagMonitor();
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_Prestore_EventPrestorageRelease
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_EventPrestorageRelease(
  void
  )
{
  if (Dem_Prestore_LockedIndex != DEM_PRESTORE_INVALID_BUFFER_ENTRY)
  {
    Dem_Cfg_PrestorageIndexType lPrestorageEntry;
    Dem_EventIdType lEventId;

    lPrestorageEntry = Dem_Prestore_LockedIndex;
    lEventId = Dem_Prestore_PrestorageEntryGetEventId(lPrestorageEntry);

/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();

    if (Dem_Prestore_PrestorageEntryGetState(lPrestorageEntry) == DEM_PRESTORE_STATUS_LOCKED)
    { /* Entry unused, return it to the event */
      Dem_Cfg_PrestorageIndexType lPrestorageIndex;
      lPrestorageIndex = Dem_Prestore_GetPrestorageEntry(lEventId);
      if (lPrestorageIndex < DEM_PRESTORE_INVALID_BUFFER_ENTRY)
      { /* Event has created a new prestored slot since locking the old, so free the locked entry */
        Dem_Prestore_PrestorageEntrySetState(lPrestorageEntry, DEM_PRESTORE_STATUS_FREE);
        Dem_Prestore_FreePrestorageEntry(lPrestorageEntry);
        /* FreeEntry removes the prestored block from the event, repair the link */
        Dem_Prestore_SetPrestorageEntry(lEventId, lPrestorageIndex);
      }
      else
      { /* Return the unused prestorage entry to the event*/
        Dem_Prestore_PrestorageEntrySetState(lPrestorageEntry, DEM_PRESTORE_STATUS_READY);
        Dem_Prestore_SetPrestorageEntry(lEventId, lPrestorageEntry);
      }
    }
    else
    {
      /* Prestorage entry has been discarded */
      Dem_Prestore_PrestorageEntrySetState(lPrestorageEntry, DEM_PRESTORE_STATUS_FREE);
      Dem_Prestore_FreePrestorageEntry(lPrestorageEntry);
    }

    Dem_LeaveCritical_DiagMonitor();
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

    Dem_Prestore_LockedIndex = DEM_PRESTORE_INVALID_BUFFER_ENTRY;
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_Prestore_EventPrestorageClear
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Prestore_EventPrestorageClear(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Std_ReturnType lReturnValue;
#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
  Dem_Cfg_PrestorageIndexType lPrestorageEntry;
#endif
  
  lReturnValue = E_NOT_OK;

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
  lPrestorageEntry = Dem_Prestore_GetPrestorageEntry(EventId);

  if (lPrestorageEntry < DEM_PRESTORE_INVALID_BUFFER_ENTRY)
  {
    /* there already is an entry allocated to this event */
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();

    if (Dem_Prestore_PrestorageEntryGetState(lPrestorageEntry) != DEM_PRESTORE_STATUS_LOCKED)
    {
      Dem_Prestore_PrestorageEntrySetState(lPrestorageEntry, DEM_PRESTORE_STATUS_FREE);
      Dem_Prestore_FreePrestorageEntry(lPrestorageEntry);
      lReturnValue = E_OK;
    }

    Dem_LeaveCritical_DiagMonitor();
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Prestore_EventPrestoreFreezeFrame
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Prestore_EventPrestoreFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Std_ReturnType lReturnValue;

  /* Only pre-store for externally visible Events that support prestorage */
  if (Dem_ExtCom_TestCurrentPartitionIsMaster() == FALSE)
  {
    Dem_SatelliteSat_UpdatePrestoreActionQueue(Dem_Cfg_EventSatelliteId(EventId), Dem_Cfg_EventSatelliteEventId(EventId), DEM_PRESTORE_QUEUE_PRESTOREFF);
    lReturnValue = E_OK;
  }
  else
  {
    lReturnValue = Dem_Prestore_EventPrestorageUpdate(EventId);
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Prestore_EventClearPrestoredFreezeFrame
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Prestore_EventClearPrestoredFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Std_ReturnType lReturnValue;

  if (Dem_ExtCom_TestCurrentPartitionIsMaster() == FALSE)
  {
    Dem_SatelliteSat_UpdatePrestoreActionQueue(Dem_Cfg_EventSatelliteId(EventId), Dem_Cfg_EventSatelliteEventId(EventId), DEM_PRESTORE_QUEUE_CLEAR);
    lReturnValue = E_OK;
  }
  else
  {
    lReturnValue = Dem_Prestore_EventPrestorageClear(EventId);
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Prestore_MainFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_MainFunction(
  void
  )
{
  Dem_Satellite_IdType lSatelliteId;
  for (lSatelliteId = 0u; lSatelliteId < Dem_Cfg_GlobalSatelliteCount(); ++lSatelliteId)
  {
    if (Dem_SatelliteCore_TestAndClearPrestoreQueueUpdated(lSatelliteId) == TRUE)
    {
      Dem_Prestore_ProcessSatelliteQueueActions(lSatelliteId);
    }
  }
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_PRESTORE_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Prestore_Implementation.h
 *********************************************************************************************************************/
