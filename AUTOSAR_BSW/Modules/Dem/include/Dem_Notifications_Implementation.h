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
/*! \addtogroup Dem_Notifications
 *  \{
 *  \file       Dem_Notifications_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_NOTIFICATIONS_IMPLEMENTATION_H)
#define DEM_NOTIFICATIONS_IMPLEMENTATION_H

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
                                                   /* External component header */
 /* ------------------------------------------------------------------------- */
#if (DEM_CFG_NOTIFY_EVENT_STATUS_FIM == STD_ON) || (DEM_CFG_NOTIFY_MONITOR_STATUS_FIM == STD_ON)
#include "FiM.h"
#endif

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Notifications_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Core_Interface.h"
#include "Dem_Infrastructure_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_NOTIFICATIONS_IMPLEMENTATION_FILENAME "Dem_Notifications_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Notifications_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Notifications_GlobalTriggerOnMonitorStatusFPtr
 *****************************************************************************/
 /*!
 * \brief         Get the global notification function for
 *                TriggerOnMonitorStatus.
 *
 * \details       Get the global notification function for
 *                TriggerOnMonitorStatus.
 *
 * \return        Function pointer to call
 *                NULL_PTR if no such notification is configured
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_GlobalTriggerOnMonitorStatusFPtrType, DEM_CODE)
Dem_Notifications_GlobalTriggerOnMonitorStatusFPtr(
  void
);


# if (DEM_CFG_NOTIFY_J1939DCM == STD_ON)
/* ****************************************************************************
 * Dem_Notifications_CallJ1939NotificationForConcernedClients
 *****************************************************************************/
/*!
 * \brief         Call the J1939 notification callback for all clients assigned
 *                to a node
 *
 * \details       Call the J1939 notification callback for all clients assigned
 *                to a node
 *
 * \param[in]     J1939DTC
 *                J1939 DTC number
 * \param[in]     NmNodeId
 *                Nm Node Id of the node
 *
 * \pre           -
 * \config        DEM_CFG_NOTIFY_J1939DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Notifications_CallJ1939NotificationForConcernedClients(
  CONST(uint32, AUTOMATIC)  J1939DTC,
  CONST(uint16, AUTOMATIC)  NmNodeId
  );
#endif


/* ****************************************************************************
 * Dem_Notifications_J1939DtcStatusChanged
 *****************************************************************************/
/*!
 * \brief         Call all J1939 notification callbacks relevant for DTC 
 *                status changes
 *
 * \details       The following callbacks are called here:
 *                - J1939DcmDtcStatusChanged(1...*)
 *                - J1939Dcm_DemTriggerOnDTCStatus
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     DtcStatusOld
 *                The old DTC status
 * \param[in]     DtcStatusNew
 *                The new DTC status
 *
 * \pre           EventStatusOld must be different from EventStatusNew.
 * \pre           The external only status modifications must have been applied
 *                to the passed status bytes.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Notifications_J1939DtcStatusChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  DtcStatusOld,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  DtcStatusNew
  );

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

 /* ****************************************************************************
 % Dem_Notifications_GlobalTriggerOnMonitorStatusFPtr
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_GlobalTriggerOnMonitorStatusFPtrType, DEM_CODE)
Dem_Notifications_GlobalTriggerOnMonitorStatusFPtr(
  void
)
{
  return (Dem_GlobalTriggerOnMonitorStatusFPtrType)DEM_CFG_GLOBALTRIGGERONMONITORSTATUS_FUNC;                                    /* PRQA S 0428 */ /* MD_DEM_16.9_fp */
}

# if (DEM_CFG_NOTIFY_J1939DCM == STD_ON)
/* ****************************************************************************
 % Dem_Notifications_CallJ1939NotificationForConcernedClients
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Notifications_CallJ1939NotificationForConcernedClients(
  CONST(uint32, AUTOMATIC)  J1939DTC,
  CONST(uint16, AUTOMATIC)  NmNodeId
  )
{
  uint8 lClientId;
              
  for (lClientId = 0u; lClientId < Dem_Cfg_GetSizeOfClientTable(); lClientId++)
  {
    if (NmNodeId == Dem_Cfg_GetNmNodeIdOfClientTable(lClientId))
    {
      J1939Dcm_DemTriggerOnDTCStatus(J1939DTC, lClientId);
    }
  }
}
#endif

/* ****************************************************************************
 % Dem_Notifications_J1939DtcStatusChanged
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Notifications_J1939DtcStatusChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  DtcStatusOld,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  DtcStatusNew
  )
{
#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
  uint32 lJ1939Dtc;

  lJ1939Dtc = Dem_Cfg_EventJ1939Dtc(EventId);

  if (lJ1939Dtc != DEM_CFG_DTC_J1939_INVALID)
  {
    Dem_Cfg_GlobalCbkJ1939DtcIterType lIter;

    /* Call all configured status change callbacks */
    for (Dem_Cfg_GlobalCbkJ1939DtcIterInit(&lIter);                                                                              /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
         Dem_Cfg_GlobalCbkJ1939DtcIterExists(&lIter) == TRUE;                                                                    /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */ /* PRQA S 2994 */ /* MD_DEM_2994 */
         Dem_Cfg_GlobalCbkJ1939DtcIterNext(&lIter))                                                                              /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
    {
      Dem_DtcStatusChangedFPtrType lpDtcStatusFunc;
      lpDtcStatusFunc = Dem_Cfg_GlobalCbkJ1939DtcIterGet(&lIter);                                                                /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
      if (lpDtcStatusFunc != NULL_PTR)
      {
        (void)lpDtcStatusFunc(lJ1939Dtc, DtcStatusOld, DtcStatusNew);                                                            /* SBSW_DEM_GLOBALCBKJ1939DTCSTATUS_FPTR */
      }
    }
# if (DEM_CFG_NOTIFY_J1939DCM == STD_ON)
    if (Dem_UDSStatus_Test_TF((Dem_UDSStatus_Type) (DtcStatusOld ^ DtcStatusNew)) == TRUE)
    { /* J1939Dcm is only triggered if testFailed bit changes */
      Dem_Cfg_EventJ1939NodeIterType lNodeIter;
      for (Dem_Cfg_EventJ1939NodeIterInit(EventId, &lNodeIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE;                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_EventJ1939NodeIterNext(&lNodeIter))                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        Dem_Notifications_CallJ1939NotificationForConcernedClients(lJ1939Dtc, 
                                                         Dem_Cfg_J1939NmNodeId(Dem_Cfg_EventJ1939NodeIterGet(&lNodeIter)));      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      }
    }
# endif
  }
#endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtcStatusOld)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtcStatusNew)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


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
 * \addtogroup Dem_Notifications_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Notifications_EventDataChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Notifications_EventDataChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  if (Dem_Cfg_EventCbkData(EventId) != NULL_PTR)
  {
    (void)(*Dem_Cfg_EventCbkData(EventId))();                                                                                    /* PRQA S 2812 */ /* MD_DEM_Dir4.1_NullFunctionPointerCheck */ /* SBSW_DEM_EVENTCBKDATA_FPTR */
  }
  if (Dem_Cfg_GlobalCbkData() != NULL_PTR)
  {
    (void)(*Dem_Cfg_GlobalCbkData())(EventId);                                                                                   /* SBSW_DEM_GLOBALCBKEVENTDATA_FPTR */
  }
}

/* ****************************************************************************
 % Dem_Notifications_InitMonitorForEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Notifications_InitMonitorForEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_InitMonitorReasonType, AUTOMATIC)  InitReason
  )
{
  Dem_InitMonitorForEventFPtrType lpInitMonitorForEventFunc;

  lpInitMonitorForEventFunc = Dem_Cfg_EventCbkInitMonitor(EventId);

  if (lpInitMonitorForEventFunc != NULL_PTR)
  {
    (void)(*lpInitMonitorForEventFunc)(InitReason);                                                                              /* SBSW_DEM_INITMONITORFOREVENT_FPTR */
  }
}

/* ****************************************************************************
 % Dem_Notifications_InitMonitorForFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Notifications_InitMonitorForFunction(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Cfg_EventCbkInitFuncIterType lIter;

  for (Dem_Cfg_EventCbkInitFuncIterInit(EventId, &lIter);                                                                        /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
       Dem_Cfg_EventCbkInitFuncIterExists(&lIter) == TRUE;                                                                       /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */ /* PRQA S 2994 */ /* MD_DEM_2994 */
       Dem_Cfg_EventCbkInitFuncIterNext(&lIter))                                                                                 /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
  {
    Dem_InitMonitorForFuncFPtrType lpInitMonitorForFuncFunc;

    lpInitMonitorForFuncFunc = Dem_Cfg_EventCbkInitFuncIterGet(&lIter);                                                          /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
    if (lpInitMonitorForFuncFunc != NULL_PTR)
    {
      (void)(lpInitMonitorForFuncFunc());                                                                                        /* SBSW_DEM_INITMONITORFORFUNCTION_FPTR */
    }
  }
}

/* ****************************************************************************
 % Dem_Notifications_DtcStatusChanged
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Notifications_DtcStatusChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  DtcStatusOld,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  DtcStatusNew,
  CONST(uint8, AUTOMATIC)  NotificationReason                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NotificationReason)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */

  if (Dem_DTC_TestSuppressionOnDtcRetrieval(EventId) == FALSE)
  {
    uint8 lDtcStatusOld;
    uint8 lDtcStatusNew;

    lDtcStatusOld = (uint8)(DtcStatusOld & Dem_Cfg_GlobalStatusMask());                                                          
    lDtcStatusNew = (uint8)(DtcStatusNew & Dem_Cfg_GlobalStatusMask());                                                          

    if (lDtcStatusOld != lDtcStatusNew)
    {
      uint32 lUdsDtc;

      lUdsDtc = Dem_Cfg_EventUdsDtc(EventId);

      if (lUdsDtc != DEM_CFG_DTC_UDS_INVALID)
      {
        Dem_Cfg_GlobalCbkDtcIterType lIter;
        for (Dem_Cfg_GlobalCbkDtcIterInit(&lIter);                                                                               /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
             Dem_Cfg_GlobalCbkDtcIterExists(&lIter) == TRUE;                                                                     /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */ /* PRQA S 2994 */ /* MD_DEM_2994 */
             Dem_Cfg_GlobalCbkDtcIterNext(&lIter))                                                                               /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
        {
          Dem_DtcStatusChangedFPtrType lpDtcStatusFunc;
          lpDtcStatusFunc = Dem_Cfg_GlobalCbkDtcIterGet(&lIter);                                                                 /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
          if (lpDtcStatusFunc != NULL_PTR)
          {
            (void)lpDtcStatusFunc(lUdsDtc, lDtcStatusOld, lDtcStatusNew);                                                        /* SBSW_DEM_GLOBALCBKDTCSTATUS_FPTR */
          }
        }

#if (DEM_CFG_NOTIFY_DCM == STD_ON)
        if (NotificationReason != DEM_NOTIFICATIONS_DTC_CLEAR)
        {
          /* Call Dcm Dtc status change callback */
          (void)Dcm_DemTriggerOnDTCStatus(lUdsDtc, lDtcStatusOld, lDtcStatusNew);
        }
#endif
      } /* if (DEM_CFG_DTC_UDS_INVALID != lUdsDtc) */

      Dem_Notifications_J1939DtcStatusChanged(EventId, lDtcStatusOld, lDtcStatusNew);
    } /* if DTC Status has changed */
  } /* if DTC is not suppressed */
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Notifications_EventStatusChanged
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
Dem_Notifications_EventStatusChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  EventUdsStatusOld,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  EventUdsStatusNew
  )
{
  if (EventUdsStatusOld != EventUdsStatusNew)
  {
#if (DEM_CFG_NOTIFY_EVENT_STATUS_FIM == STD_ON)
    /* Call FiM event status change callback */
    (void)FiM_DemTriggerOnEventStatus(EventId, EventUdsStatusOld, EventUdsStatusNew);
#endif

#if (DEM_CFG_NOTIFY_DLT == STD_ON)
    /* Call Dlt event status change callback */
    Dlt_DemTriggerOnEventStatus(EventId, EventUdsStatusOld, EventUdsStatusNew);
#endif
    {
      Dem_Cfg_EventCbkStatusIterType lIter;
      /* Call all configured status change callbacks for this event */
      for (Dem_Cfg_EventCbkStatusIterInit(EventId, &lIter);                                                                      /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
           Dem_Cfg_EventCbkStatusIterExists(&lIter) == TRUE;                                                                     /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */ /* PRQA S 2994 */ /* MD_DEM_2994 */
           Dem_Cfg_EventCbkStatusIterNext(&lIter))                                                                               /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
      {
        Dem_EventStatusChangedFPtrType lpEventCbkStatusFunc;
        lpEventCbkStatusFunc = Dem_Cfg_EventCbkStatusIterGet(&lIter);                                                            /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
        if (lpEventCbkStatusFunc != NULL_PTR)
        {
          (void)(lpEventCbkStatusFunc(EventUdsStatusOld, EventUdsStatusNew));                                                    /* SBSW_DEM_EVENTCBKSTATUS_FPTR */
        }
      }
    }

    /* Call general event status changed callback */
    if (Dem_Cfg_GlobalCbkStatus() != NULL_PTR)
    {
      (void)(*Dem_Cfg_GlobalCbkStatus())(EventId, EventUdsStatusOld, EventUdsStatusNew);                                         /* SBSW_DEM_GLOBALCBKEVENTSTATUS_FPTR */
    }
  }
}

/* ****************************************************************************
 % Dem_Notifications_MonitorStatusChanged
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
Dem_Notifications_MonitorStatusChanged(
  CONST(Dem_EventIdType, AUTOMATIC)   EventId
  )
{
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
  {
    if (Dem_Notifications_GlobalTriggerOnMonitorStatusFPtr() != NULL_PTR)
    {
      (void)(*Dem_Notifications_GlobalTriggerOnMonitorStatusFPtr())(EventId);                                                    /* SBSW_DEM_GLOBALTRIGGERONMONITORSTATUS_FPTR */
    }
#if (DEM_CFG_NOTIFY_MONITOR_STATUS_FIM == STD_ON)
    (void)FiM_DemTriggerOnMonitorStatus(EventId);
#endif
  }
}

/* ****************************************************************************
 % Dem_Notifications_ClearDTCStart()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_Notifications_ClearDTCStart(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin
  )
{
#if (Dem_Cfg_HasClearDtcNotificationStartTable() == STD_ON)
  Dem_SimpleIterType lClearNotificationIter;

  for (lClearNotificationIter = 0u;
       lClearNotificationIter < Dem_Cfg_GetSizeOfClearDtcNotificationStartTable();
       ++lClearNotificationIter)
  {
    Dem_ClearDtcNotificationFPtrType lpClearDtcNotificationStartFunc;

    lpClearDtcNotificationStartFunc = Dem_Cfg_GetClearDtcNotificationStartTable(lClearNotificationIter);
    if (lpClearDtcNotificationStartFunc != NULL_PTR)
    {
      (void)lpClearDtcNotificationStartFunc(DTC, DTCFormat, DTCOrigin);                                                          /* SBSW_DEM_CLEARDTCNOTIFICATIONSTARTFUNCTION_FPTR */
    }
  }
#endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTC)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCFormat)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCOrigin)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
}

/* ****************************************************************************
 % Dem_Notifications_ClearDTCEnd()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_Notifications_ClearDTCEnd(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin
  )
{
#if (Dem_Cfg_HasClearDtcNotificationFinishTable() == STD_ON)
  Dem_SimpleIterType lClearNotificationIter;

  for (lClearNotificationIter = 0u;
       lClearNotificationIter < Dem_Cfg_GetSizeOfClearDtcNotificationFinishTable();
       ++lClearNotificationIter)
  {
    Dem_ClearDtcNotificationFPtrType lpClearDtcNotificationFinishFunc;

    lpClearDtcNotificationFinishFunc = Dem_Cfg_GetClearDtcNotificationFinishTable(lClearNotificationIter);
    if (lpClearDtcNotificationFinishFunc != NULL_PTR)
    {
      (void)lpClearDtcNotificationFinishFunc(DTC, DTCFormat, DTCOrigin);                                                         /* SBSW_DEM_CLEARDTCNOTIFICATIONFINISHFUNCTION_FPTR */
    }
  }
#endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTC)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCFormat)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCOrigin)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
}

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_Notifications_EventAvailabilityChanged()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Notifications_EventAvailabilityChanged(
  CONST(Dem_EventIdType, AUTOMATIC)   EventId,
  CONST(boolean, AUTOMATIC)   DisconnectedStatus
  )
{
# if (DEM_CFG_NOTIFY_EVENT_STATUS_FIM == STD_ON)
  if (DisconnectedStatus == TRUE)
  {
    (void)FiM_DemTriggerOnEventStatus(EventId, 0x50U, 0x00U);
  }
  else
  {
    (void)FiM_DemTriggerOnEventStatus(EventId, 0x00U, 0x50U);
  }
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DisconnectedStatus)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_Notifications_ControlDtcSettingChanged()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Notifications_ControlDtcSettingChanged(
CONST(boolean, AUTOMATIC)   Enabled
)
{
  if (Dem_Cfg_GlobalCbkControlDtcSetting() != NULL_PTR)
  {
    (void)(*Dem_Cfg_GlobalCbkControlDtcSetting())(Enabled);                                                                      /* SBSW_DEM_GLOBALCBKCONTROLDTCSETTING_FPTR */
  }
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_NOTIFICATIONS_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Notifications_Implementation.h
 *********************************************************************************************************************/
