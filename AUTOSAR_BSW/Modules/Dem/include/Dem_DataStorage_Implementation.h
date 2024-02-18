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
/*! \addtogroup Dem_DataStorage
 *  \{
 *  \file       Dem_DataStorage_Implementation.h
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

#if !defined (DEM_DATASTORAGE_IMPLEMENTATION_H)
#define DEM_DATASTORAGE_IMPLEMENTATION_H

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
#include "Dem_DataStorage_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_Client_Interface.h"
#include "Dem_Prestore_Interface.h"
#include "Dem_ExtDataElement_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_DATASTORAGE_IMPLEMENTATION_FILENAME "Dem_DataStorage_Implementation.h"

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
 * \defgroup Dem_DataStorageIF_Private Private Methods
 * \{
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

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
 * \addtogroup Dem_DataStorageIF_Public
 * \{
 */

/* ****************************************************************************
 % Dem_DataStorage_GetDidNVSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_DataStorage_GetDidNVSize(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex
  )
{
  uint8 lDidTotalSize;

  Dem_Cfg_DataIndexType lDataIndex;
  Dem_Cfg_DidDataIterType lDataIter;

  lDidTotalSize = 0u;
  for (Dem_Cfg_DidDataIterInit(DidIndex, &lDataIter);                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_DidDataIterExists(&lDataIter) == TRUE;                                                                            /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_DidDataIterNext(&lDataIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    lDataIndex = Dem_Cfg_DidDataIterGet(&lDataIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DataIsStoredInNV(lDataIndex) == TRUE)
    {
      switch (Dem_Cfg_DataCallbackType(lDataIndex))
      {
      case DEM_CFG_DATA_FROM_ROOTCAUSE_EVENTID:
      case DEM_CFG_DATA_FROM_CBK:
      case DEM_CFG_DATA_FROM_CBK_WITH_EVENTID:
      case DEM_CFG_DATA_FROM_SR_PORT_BOOLEAN:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT8:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT8:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT16:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT16_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT16:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT16_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT32:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT32_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT32:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT32_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT8_N:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT8_N:
          lDidTotalSize += Dem_Cfg_DataSize(lDataIndex);
          break;

      default:                                                                                                                   /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
        /* Do nothing */
          break;
      }
    }
  }

  return lDidTotalSize;
}


#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_DataStorage_PrestorageApplyGlobalSRec
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataStorage_PrestorageApplyGlobalSRec(
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  boolean lReturnValue;
  Dem_Cfg_PrestorageIndexType lPrestoreLockedIndex;

  lReturnValue = FALSE;

  lPrestoreLockedIndex = Dem_Prestore_GetLockedIndex();
  if (DEM_PRESTORE_INVALID_BUFFER_ENTRY != lPrestoreLockedIndex)
  {
    Dem_MemCpy(DestinationBuffer,                                                                                                /* PRQA S 0310, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_20.2 */ /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
               Dem_Prestore_PrestorageEntryGetGlobalSRecDataPtr(lPrestoreLockedIndex),
               BufferSize);

    lReturnValue = TRUE;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_DataStorage_PrestorageApplySRec
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataStorage_PrestorageApplySRec(
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  boolean lReturnValue;
  Dem_Cfg_PrestorageIndexType lPrestoreLockedIndex;

  lReturnValue = FALSE;

  lPrestoreLockedIndex = Dem_Prestore_GetLockedIndex();
  if (DEM_PRESTORE_INVALID_BUFFER_ENTRY != lPrestoreLockedIndex)
  {
    Dem_ConstDataPtrType lPrestorageBuffer;
    lPrestorageBuffer = Dem_Prestore_PrestorageEntryGetSRecDataPtr(lPrestoreLockedIndex);
    Dem_MemCpy(DestinationBuffer,                                                                                                /* PRQA S 0310, 0602, 0311 */ /* MD_DEM_11.4_cpy, MD_DEM_20.2, MD_DEM_11.8 */ /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
               lPrestorageBuffer,
               BufferSize);

    lReturnValue = TRUE;
  }

  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_DataStorage_PrestorageApplyObdIIFF
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataStorage_PrestorageApplyObdIIFF(
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  boolean lReturnValue;
  Dem_Cfg_PrestorageIndexType lPrestoreLockedIndex;

  lReturnValue = FALSE;

  lPrestoreLockedIndex = Dem_Prestore_GetLockedIndex();
  if (DEM_PRESTORE_INVALID_BUFFER_ENTRY != lPrestoreLockedIndex)
  {
    Dem_MemCpy(DestinationBuffer,                                                                                                /* PRQA S 0310, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_20.2 */ /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
               Dem_Prestore_PrestorageEntryGetObdIIFFDataPtr(lPrestoreLockedIndex),
               BufferSize);

    lReturnValue = TRUE;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_DataStorage_PrestorageApplyWwhObdFF
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataStorage_PrestorageApplyWwhObdFF(
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  boolean lReturnValue;
  Dem_Cfg_PrestorageIndexType lPrestoreLockedIndex;

  lReturnValue = FALSE;

  lPrestoreLockedIndex = Dem_Prestore_GetLockedIndex();
  if (DEM_PRESTORE_INVALID_BUFFER_ENTRY != lPrestoreLockedIndex)
  {
    Dem_MemCpy(DestinationBuffer,                                                                                                /* PRQA S 0310, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_20.2 */ /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
               Dem_Prestore_PrestorageEntryGetWwhObdFFDataPtr(lPrestoreLockedIndex),
               BufferSize);

    lReturnValue = TRUE;
  }

  return lReturnValue;
}
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_DataStorage_PrestorageApplyJ1939FF
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataStorage_PrestorageApplyJ1939FF(
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  boolean lReturnValue;
  Dem_Cfg_PrestorageIndexType lPrestoreLockedIndex;

  lReturnValue = FALSE;

  lPrestoreLockedIndex = Dem_Prestore_GetLockedIndex();
  if (DEM_PRESTORE_INVALID_BUFFER_ENTRY != lPrestoreLockedIndex)
  {
    Dem_MemCpy(DestinationBuffer,                                                                                                /* PRQA S 0310, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_20.2 */ /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
               Dem_Prestore_PrestorageEntryGetJ1939FFDataPtr(lPrestoreLockedIndex),
               BufferSize);

    lReturnValue = TRUE;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_DataStorage_CollectObdIIFreezeFrame
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorage_CollectObdIIFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  Dem_ExtDataElement_CollectDidInfoType lCollectDidInfo;
  Dem_Cfg_GlobalPidIterType lPidIter;
  Dem_Data_DestinationBuffer lDestinationBuffer;

  /* Initialize collection context */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestinationBuffer, BufferSize);                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
  Dem_ExtDataElement_InitCollectDidInfo(&lCollectDidInfo                                                                       /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */                                                          
                                         ,&lDestinationBuffer
                                         ,EventId);

  for (Dem_Cfg_GlobalPidIterInit(&lPidIter);                                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_GlobalPidIterExists(&lPidIter) == TRUE;                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_GlobalPidIterNext(&lPidIter))                                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_GlobalPidIterGet(&lPidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_ExtDataElement_CollectStoredDid(&lCollectDidInfo, lDidIndex);                                                          /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO */
  }
}
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_DataStorage_CollectWwhObdFreezeFrame
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorage_CollectWwhObdFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  Dem_ExtDataElement_CollectDidInfoType lCollectDidInfo;
  Dem_Data_DestinationBuffer lDestinationBuffer;
  Dem_Cfg_EventObdDidIterType lDidIter;

  /* Initialize collection context */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestinationBuffer, BufferSize);                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
  Dem_ExtDataElement_InitCollectDidInfo(&lCollectDidInfo                                                                       /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */  
                                         , &lDestinationBuffer
                                         , EventId);

  for (Dem_Cfg_EventObdDidIterInit(EventId, &lDidIter);                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventObdDidIterExists(&lDidIter) == TRUE;                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventObdDidIterNext(&lDidIter))                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_EventObdDidIterGet(&lDidIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_ExtDataElement_CollectStoredDid(&lCollectDidInfo, lDidIndex);                                                          /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO */
  }
}
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_DataStorage_CollectJ1939FreezeFrame
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorage_CollectJ1939FreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  Dem_ExtDataElement_CollectDidInfoType lCollectDidInfo;
  Dem_Data_DestinationBuffer lDestinationBuffer;
  Dem_Cfg_EventSPNIterType lSpnIter;

  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestinationBuffer, BufferSize);                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
  Dem_ExtDataElement_InitCollectDidInfo(&lCollectDidInfo                                                                       /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */  
                                         ,&lDestinationBuffer
                                         , EventId);

  if (Dem_Cfg_EventJ1939FFExists(EventId) == FALSE)
  { /* skip the buffer area reserved for standard FreezeFrame */
    (void)  Dem_Data_IncrementWriteIndexDestinationBuffer(lCollectDidInfo.DestinationBuffer, Dem_Cfg_GlobalJ1939FFRawSize());    /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO_DESTINATIONBUFFER */
  }

  for (Dem_Cfg_EventSPNIterInit(EventId, &lSpnIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventSPNIterExists(&lSpnIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventSPNIterNext(&lSpnIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_EventSPNIterGet(&lSpnIter);                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_ExtDataElement_CollectStoredDid(&lCollectDidInfo, lDidIndex);                                                          /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_DataStorage_CollectGlobalSnapshot
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorage_CollectGlobalSnapshot(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  Dem_ExtDataElement_CollectDidInfoType lCollectDidInfo;
  Dem_Cfg_GlobalSnapshotDidIterType lDidIter;
  Dem_Data_DestinationBuffer lDestinationBuffer;

  /* Initialize collection context */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestinationBuffer, BufferSize);                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
  Dem_ExtDataElement_InitCollectDidInfo(&lCollectDidInfo                                                                       /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */
                                         ,&lDestinationBuffer
                                         ,EventId);

  for (Dem_Cfg_GlobalSnapshotDidIterInit(&lDidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_GlobalSnapshotDidIterExists(&lDidIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_GlobalSnapshotDidIterNext(&lDidIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_GlobalSnapshotDidIterGet(&lDidIter);                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_ExtDataElement_CollectStoredDid(&lCollectDidInfo, lDidIndex);                                                          /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO */
  }
}
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_DataStorage_CollectSnapshot
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorage_CollectSnapshot(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  Dem_ExtDataElement_CollectDidInfoType lCollectDidInfo;
  Dem_Cfg_EventDidIterType lDidIter;
  Dem_Data_DestinationBuffer lDestinationBuffer;

  /* Initialize collection context */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestinationBuffer, BufferSize);                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
  Dem_ExtDataElement_InitCollectDidInfo(&lCollectDidInfo                                                                       /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */
                                         ,&lDestinationBuffer
                                         , EventId);

  for (Dem_Cfg_EventDidIterInit(EventId, &lDidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventDidIterExists(&lDidIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventDidIterNext(&lDidIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_EventDidIterGet(&lDidIter);                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_ExtDataElement_CollectStoredDid(&lCollectDidInfo, lDidIndex);                                                          /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO */
  }
}
#endif

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_DataStorage_CollectERec
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorage_CollectERec(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_DidIndexType,AUTOMATIC) DidIndex,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Dem_ExtDataElement_CollectDidInfoType lCollectDidInfo;

  Dem_ExtDataElement_InitCollectDidInfo(&lCollectDidInfo                                                                       /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */
                                         ,DestinationBuffer
                                         ,EventId);

  Dem_ExtDataElement_CollectStoredDid(&lCollectDidInfo, DidIndex);                                                             /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO */
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_DataStorage_CollectTimeSeriesNormalSamples
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorage_CollectTimeSeriesNormalSamples(
  Dem_Data_DestinationBufferPtrType DestinationBuffer
  )
{
  Dem_Cfg_TimeSeriesDidNormalIterType lDidIter;
  Dem_ExtDataElement_CollectDidInfoType lCollectDidInfo;

  Dem_ExtDataElement_InitCollectDidInfo( &lCollectDidInfo                                                                      /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */
                                         , DestinationBuffer
                                         , DEM_EVENT_INVALID);

  for (Dem_Cfg_TimeSeriesDidNormalIterInit(&lDidIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_TimeSeriesDidNormalIterExists(&lDidIter) == TRUE;                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_TimeSeriesDidNormalIterNext(&lDidIter))                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_TimeSeriesDidNormalIterGet(&lDidIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_ExtDataElement_CollectStoredDid(&lCollectDidInfo, lDidIndex);                                                          /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO */
  }
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 % Dem_DataStorage_CollectTimeSeriesFastSamples
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorage_CollectTimeSeriesFastSamples(
  Dem_Data_DestinationBufferPtrType DestinationBuffer
  )
{
  Dem_Cfg_TimeSeriesDidFastIterType lDidIter;
  Dem_ExtDataElement_CollectDidInfoType lCollectDidInfo;

  Dem_ExtDataElement_InitCollectDidInfo(&lCollectDidInfo                                                                       /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */
                                         , DestinationBuffer
                                         , DEM_EVENT_INVALID);

  for (Dem_Cfg_TimeSeriesDidFastIterInit(&lDidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_TimeSeriesDidFastIterExists(&lDidIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_TimeSeriesDidFastIterNext(&lDidIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_TimeSeriesDidFastIterGet(&lDidIter);                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_ExtDataElement_CollectStoredDid(&lCollectDidInfo, lDidIndex);                                                          /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DATASTORAGE_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DataStorage_Implementation.h
 *********************************************************************************************************************/
