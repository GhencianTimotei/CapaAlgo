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
/*! \addtogroup Dem_RingBuffer
 *  \{
 *  \file       Dem_RingBuffer_Implementation.h
 *  \brief      Manages ring buffer.
 *  \details    Manages access to ring buffers and ring buffer state handling.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_RINGBUFFER_IMPLEMENTATION_H)
#define DEM_RINGBUFFER_IMPLEMENTATION_H

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
/* PRQA S 3415 EOF */ /* MD_DEM_13.5_cf */

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_RingBuffer_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_TimeSeriesIF_Interface.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

  /*! Filename declaration */
#define DEM_RINGBUFFER_IMPLEMENTATION_FILENAME "Dem_RingBuffer_Implementation.h"

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
 * \defgroup Dem_RingBuffer_PrivateProperties Private Properties
 * \{
 */

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_RingBuffer_SetNormalSampleCount
 *****************************************************************************/
/*!
 * \brief         Set number of stored samples in normal rate ring buffer
 *
 * \details       Set number of stored samples in normal rate ring buffer
 *
 * \param[in]     SampleCount
 *                Sample count to write in normal rate ringbuffer
 *
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_SetNormalSampleCount(
  uint8 SampleCount
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_RingBuffer_SetFastSampleCount
 *****************************************************************************/
/*!
 * \brief         Set number of stored samples in fast rate ring buffer
 *
 * \details       Set number of stored samples in fast rate ring buffer
 *
 * \param[in]     SampleCount
 *                Sample count to write in fast rate ringbuffer
 *
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_SetFastSampleCount(
  uint8 SampleCount
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_RingBuffer_SetCurrentIndexNormal
 *****************************************************************************/
/*!
 * \brief         Set index of current sample slot for normal rate ring buffer
 *
 * \details       Set index of current sample slot for normal rate ring buffer
 *
 * \param[in]     Index
 *                Index to write in normal rate ringbuffer
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
 DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_SetCurrentIndexNormal(
  uint8 Index
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
 /* ****************************************************************************
 * Dem_Memory_TimeSeries_RingBuffer_SetCurrentIndexFast
 *****************************************************************************/
/*!
 * \brief         Set index of current sample slot for fast rate ring buffer
 *
 * \details       Set index of current sample slot for fast rate ring buffer
 *
 * \param[in]     Index
 *                Index to write in fast rate ringbuffer
 *
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
 DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_SetCurrentIndexFast(
  uint8 Index
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 /* ****************************************************************************
 % Dem_Memory_TimeSeries_RingBuffer_SetCurrentIndexNormal
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_SetCurrentIndexNormal(
  uint8 Index
  )
{
  Dem_Cfg_RingBufferNormalRate.CurrentIndex = Index;
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_RingBuffer_SetCurrentIndexFast
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_SetCurrentIndexFast(
  uint8 Index
  )
{
  Dem_Cfg_RingBufferFastRate.CurrentIndex = Index;
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 /* ****************************************************************************
 % Dem_Memory_TimeSeries_RingBuffer_SetNormalSampleCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
 DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
 Dem_Memory_TimeSeries_RingBuffer_SetNormalSampleCount(
   uint8 SampleCount
   )
{
Dem_Cfg_RingBufferNormalRate.SampleCount = SampleCount;
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_RingBuffer_SetFastSampleCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
 DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
 Dem_Memory_TimeSeries_RingBuffer_SetFastSampleCount(
   uint8 SampleCount
   )
{
Dem_Cfg_RingBufferFastRate.SampleCount = SampleCount;
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
 * \addtogroup Dem_RingBuffer_PublicProperties
 * \{
 */
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_RingBuffer_GetCurrentIndexNormal
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_GetCurrentIndexNormal(
  void
  )
{
  return Dem_Cfg_RingBufferNormalRate.CurrentIndex;
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_RingBuffer_GetCurrentIndexFast
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_GetCurrentIndexFast(
  void
)
{
  return Dem_Cfg_RingBufferFastRate.CurrentIndex;
}
#endif

#if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_RingBuffer_GetNormalSampleCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_GetNormalSampleCount(
  void
  )
 {
  return Dem_Cfg_RingBufferNormalRate.SampleCount;
 }
#endif

#if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_RingBuffer_GetFastSampleCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_GetFastSampleCount(
  void
  )
{
return Dem_Cfg_RingBufferFastRate.SampleCount;
}
#endif

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
 * \defgroup Dem_RingBuffer_Private Private Methods
 * \{
 */

/*********************************************************************************************************************
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
 * \addtogroup Dem_RingBuffer_Public
 * \{
 */

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
% Dem_Memory_TimeSeries_RingBuffer_GetNormalSlot
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
Dem_Memory_TimeSeries_RingBuffer_GetNormalSlot(
uint8  BufferIndex
)
{
  Dem_DataPtrType lReturnValue;
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (BufferIndex >= Dem_Cfg_TimeSeriesBufferCountNormal())
  {
    Dem_Error_RunTimeCheckFailed(DEM_RINGBUFFER_IMPLEMENTATION_FILENAME, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = Dem_Cfg_RingBufferNormalRate.Buffer[0];
  }
  else
# endif
  {
    lReturnValue = Dem_Cfg_RingBufferNormalRate.Buffer[BufferIndex];
  }
  return lReturnValue;
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_RingBuffer_GetNormalSampleSlotAndRotate
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
Dem_Memory_TimeSeries_RingBuffer_GetNormalSampleSlotAndRotate(
  void
  )
{
  Dem_DataPtrType lNormalSampleSlot;
  uint8 lCurrentIndex;

  lCurrentIndex = Dem_Memory_TimeSeries_RingBuffer_GetCurrentIndexNormal();

  lNormalSampleSlot = Dem_Memory_TimeSeries_RingBuffer_GetNormalSlot(lCurrentIndex);

# if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL == STD_ON)
  /* update current index of ring buffer */
  lCurrentIndex = ((lCurrentIndex + 1u) % Dem_Cfg_TimeSeriesPastSamplesNormal());
  Dem_Memory_TimeSeries_RingBuffer_SetCurrentIndexNormal(lCurrentIndex);

  /* update number of written samples in ring buffer */
  if (Dem_Memory_TimeSeries_RingBuffer_GetNormalSampleCount() < Dem_Cfg_TimeSeriesPastSamplesNormal())
  {
    Dem_Memory_TimeSeries_RingBuffer_SetNormalSampleCount(Dem_Memory_TimeSeries_RingBuffer_GetNormalSampleCount() + 1u);
  }
# endif

  return lNormalSampleSlot;
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
% Dem_Memory_TimeSeries_RingBuffer_GetFastSlot
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
Dem_Memory_TimeSeries_RingBuffer_GetFastSlot(
uint8 BufferIndex
)
{
  Dem_DataPtrType lReturnValue;
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (BufferIndex >= Dem_Cfg_TimeSeriesBufferCountFast())
  {
    Dem_Error_RunTimeCheckFailed(DEM_RINGBUFFER_IMPLEMENTATION_FILENAME, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = Dem_Cfg_RingBufferFastRate.Buffer[0];
  }
  else
# endif
  {
    lReturnValue = Dem_Cfg_RingBufferFastRate.Buffer[BufferIndex];
  }
  return lReturnValue;
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_RingBuffer_GetFastSampleSlotAndRotate
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
Dem_Memory_TimeSeries_RingBuffer_GetFastSampleSlotAndRotate(
  void
  )
{
  Dem_DataPtrType lFastSampleSlot;
  uint8 lCurrentIndex;

  lCurrentIndex = Dem_Memory_TimeSeries_RingBuffer_GetCurrentIndexFast();

  lFastSampleSlot = Dem_Memory_TimeSeries_RingBuffer_GetFastSlot(lCurrentIndex);

# if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_ON)
  /* update current index of ring buffer */
  lCurrentIndex = ((lCurrentIndex + 1u) % Dem_Cfg_TimeSeriesPastSamplesFast());
  Dem_Memory_TimeSeries_RingBuffer_SetCurrentIndexFast(lCurrentIndex);

  /* update number of written samples in ring buffer */
  if (Dem_Memory_TimeSeries_RingBuffer_GetFastSampleCount() < Dem_Cfg_TimeSeriesPastSamplesFast())
  {
    Dem_Memory_TimeSeries_RingBuffer_SetFastSampleCount(Dem_Memory_TimeSeries_RingBuffer_GetFastSampleCount() + 1u);
  }
# endif

  return lFastSampleSlot;
}
#endif

/* ****************************************************************************
 % Dem_Memory_TimeSeries_RingBuffer_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_Init(
  void
)
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  Dem_Memory_TimeSeries_RingBuffer_SetCurrentIndexNormal(0);
  Dem_Memory_TimeSeries_RingBuffer_SetNormalSampleCount(0);
# if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
  Dem_Memory_TimeSeries_RingBuffer_SetCurrentIndexFast(0);
  Dem_Memory_TimeSeries_RingBuffer_SetFastSampleCount(0);
# endif
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_RINGBUFFER_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_RingBuffer_Implementation.h
 *********************************************************************************************************************/
