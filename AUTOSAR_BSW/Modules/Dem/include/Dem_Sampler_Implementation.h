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
/*! \addtogroup Dem_Sampler
 *  \{
 *  \file       Dem_Sampler_Implementation.h
 *  \brief      Manages time series sampling timer.
 *  \details    Manages time series sampling timer.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_SAMPLER_IMPLEMENTATION_H)
#define DEM_SAMPLER_IMPLEMENTATION_H

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
#include "Dem_Sampler_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_EntryManager_Interface.h"
#include "Dem_RingBuffer_Interface.h"
#include "Dem_TimeSeriesIF_Interface.h"
#include "Dem_DataStorage_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

  /*! Filename declaration */
#define DEM_SAMPLER_IMPLEMENTATION_FILENAME "Dem_Sampler_Implementation.h"

 /* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/*! Normal rate time-series update request flag */
DEM_LOCAL VAR(boolean, DEM_VAR_NOINIT)           Dem_Memory_TimeSeries_Sampler_FetchNormalRate;
# if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/*! Fast rate time-series update request flag */
DEM_LOCAL VAR(boolean, DEM_VAR_NOINIT)           Dem_Memory_TimeSeries_Sampler_FetchFastRate;
# endif
#endif
#define DEM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define DEM_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/*! Normal rate time-series snapshot record update poll timer */
DEM_LOCAL VAR(uint32, DEM_VAR_NOINIT)            Dem_Memory_TimeSeries_Sampler_NormalRateTimer;
# if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/*! Fast rate time-series snapshot record update poll timer */
DEM_LOCAL VAR(uint32, DEM_VAR_NOINIT)            Dem_Memory_TimeSeries_Sampler_FastRateTimer;
# endif
#endif

#define DEM_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
 
/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Sampler_PrivateProperties Private Properties
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
 * \addtogroup Dem_Sampler_PublicProperties
 * \{
 */

/* ****************************************************************************
 % Dem_Memory_TimeSeries_Sampler_GetNormalRateTimer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Memory_TimeSeries_Sampler_GetNormalRateTimer(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  return Dem_Memory_TimeSeries_Sampler_NormalRateTimer;
#else
  return 0x00;
#endif
}

/* ****************************************************************************
 % Dem_Memory_TimeSeries_Sampler_GetFastRateTimer
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Memory_TimeSeries_Sampler_GetFastRateTimer(                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
  return Dem_Memory_TimeSeries_Sampler_FastRateTimer;
#else
  return 0x00;
#endif
}

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
 * \defgroup Dem_Sampler_Private Private Methods
 * \{
 */

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_Sampler_CollectPastNormalSamples
 *****************************************************************************/
/*!
 * \brief         Collect time series samples of normal rate
 *
 * \details       Collect time series samples of normal rate
 *
 * \pre           timer for normal rate has expired
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_Sampler_CollectPastNormalSamples(
  void
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_Sampler_CollectPastFastSamples
 *****************************************************************************/
/*!
 * \brief         Collect time series samples of fast rate
 *
 * \details       Collect time series samples of fast rate
 *
 * \pre           timer for fast rate has expired
 * \config        DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_Sampler_CollectPastFastSamples(
  void
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_Sampler_CollectPastNormalSamples
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_Sampler_CollectPastNormalSamples(
  void
  )
{
  Dem_Data_DestinationBuffer lDestinationBuffer;
  Dem_DataPtrType lSampleSlot;

  /* Get sample slot to persist data and update internal ringbuffer state*/
  lSampleSlot = Dem_Memory_TimeSeries_RingBuffer_GetNormalSampleSlotAndRotate();
  /* Collect all DIDs used in normal rate time series snapshot records and store them into ring buffer */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, lSampleSlot, Dem_Cfg_GlobalTimeSeriesNormalBufferSize());                  /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */

  Dem_DataStorage_CollectTimeSeriesNormalSamples(&lDestinationBuffer);                                                         /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 % Dem_Memory_TimeSeries_Sampler_CollectPastFastSamples
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_Sampler_CollectPastFastSamples(
  void
  )
{
  Dem_Data_DestinationBuffer lDestinationBuffer;
  Dem_DataPtrType lSampleSlot;

  /* Get sample slot to persist data and update internal ringbuffer state*/
  lSampleSlot = Dem_Memory_TimeSeries_RingBuffer_GetFastSampleSlotAndRotate();

  /* Collect all DIDs used in fast rate time series snapshot records and store them into ring buffer */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, lSampleSlot, Dem_Cfg_GlobalTimeSeriesFastBufferSize());                    /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */

  Dem_DataStorage_CollectTimeSeriesFastSamples(&lDestinationBuffer);                                                           /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */

}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

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
 * \addtogroup Dem_Sampler_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Memory_TimeSeries_Sampler_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_Sampler_Init(
  void
)
{
# if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  Dem_Memory_TimeSeries_Sampler_FetchNormalRate = FALSE;
  Dem_Memory_TimeSeries_Sampler_NormalRateTimer = Dem_Cfg_TimeSeriesNormalRate();
#  if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
  Dem_Memory_TimeSeries_Sampler_FetchFastRate = FALSE;
  Dem_Memory_TimeSeries_Sampler_FastRateTimer = Dem_Cfg_TimeSeriesFastRate();
#  endif
# endif
}

 /* ****************************************************************************
 % Dem_Memory_TimeSeries_Sampler_ProcessTimerTask
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
Dem_Memory_TimeSeries_Sampler_ProcessTimerTask(
  void
  )
{
# if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  --Dem_Memory_TimeSeries_Sampler_NormalRateTimer;

  if (Dem_Memory_TimeSeries_Sampler_NormalRateTimer == 0u)
  {
    Dem_Memory_TimeSeries_Sampler_FetchNormalRate = TRUE;
    Dem_Memory_TimeSeries_Sampler_NormalRateTimer = Dem_Cfg_TimeSeriesNormalRate();
  }

#  if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
  --Dem_Memory_TimeSeries_Sampler_FastRateTimer;

  if (Dem_Memory_TimeSeries_Sampler_FastRateTimer == 0u)
  {
    Dem_Memory_TimeSeries_Sampler_FetchFastRate = TRUE;
    Dem_Memory_TimeSeries_Sampler_FastRateTimer = Dem_Cfg_TimeSeriesFastRate();
  }
#  endif
# endif
}

/* ****************************************************************************
 % Dem_Memory_TimeSeries_Sampler_ProcessWorkerTask
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
Dem_Memory_TimeSeries_Sampler_ProcessWorkerTask(
  void
  )
{
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  if (Dem_Memory_TimeSeries_Sampler_FetchNormalRate == TRUE)
  {
    Dem_Memory_TimeSeries_Sampler_FetchNormalRate = FALSE;

    Dem_Memory_TimeSeries_Sampler_CollectPastNormalSamples();

    Dem_Memory_TimeSeries_UpdateNormalFutureSamples();
  }

# if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
  if (Dem_Memory_TimeSeries_Sampler_FetchFastRate == TRUE)
  {
    Dem_Memory_TimeSeries_Sampler_FetchFastRate = FALSE;

    Dem_Memory_TimeSeries_Sampler_CollectPastFastSamples();

    Dem_Memory_TimeSeries_UpdateFastFutureSamples();
  }
# endif
#endif
}
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_SAMPLER_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Sampler_Implementation.h
 *********************************************************************************************************************/
