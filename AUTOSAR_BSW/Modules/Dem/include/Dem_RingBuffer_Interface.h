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
/*! \ingroup    Dem_TimeSeries
 *  \defgroup   Dem_RingBuffer RingBuffer
 *  \{
 *  \file       Dem_RingBuffer_Interface.h
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

#if !defined (DEM_RINGBUFFER_INTERFACE_H)
#define DEM_RINGBUFFER_INTERFACE_H

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
#include "Dem_RingBuffer_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_RingBuffer_PublicProperties Public Properties
 * \{
 */

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_RingBuffer_GetCurrentIndexNormal
 *****************************************************************************/
/*!
 * \brief         Return index to current sample slot in normal rate ring buffer
 *
 * \details       Return index to current sample slot in normal rate ring buffer
 *
 * \return        Index to current sample slot in normal rate ring buffer
 *
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_GetCurrentIndexNormal(
  void
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
 /* ****************************************************************************
 * Dem_Memory_TimeSeries_RingBuffer_GetCurrentIndexFast
 *****************************************************************************/
/*!
 * \brief         Return index to current sample slot in fast rate ring buffer
 *
 * \details       Return index to current sample slot in fast rate ring buffer
 *
 * \return        Index to current sample slot
 *
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
 DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_GetCurrentIndexFast(
  void
);
#endif

#if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL == STD_ON)
 /* ****************************************************************************
 * Dem_Memory_TimeSeries_RingBuffer_GetNormalSampleCount
 *****************************************************************************/
 /*!
 * \brief         Get number of stored samples in normal rate ring buffer
 *
 * \details       Get number of stored samples in normal rate ring buffer
 *
 *
 * \return        Number of stored samples in normal rate ring buffer
 *
 * \pre           -
 *
 * \config        DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_GetNormalSampleCount(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_RingBuffer_GetFastSampleCount
 *****************************************************************************/
/*!
 * \brief         Get number of stored samples in fast rate ring buffer
 *
 * \details       Get number of stored samples in fast rate ring buffer
 *
 *
 * \return        Number of stored samples in fast rate ring buffer
 *
 * \pre           -
 *
 * \config        DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_GetFastSampleCount(
  void
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_RingBuffer_Public Public Methods
 * \{
 */

/* ****************************************************************************
* Dem_Memory_TimeSeries_RingBuffer_GetNormalSlot
*****************************************************************************/
/*!
* \brief         Get the indexed ringbuffer slot from normal rate ring buffer
*
* \details       Get the indexed ringbuffer slot from normal rate ring buffer
*
* \param[in]     BufferIndex
*                Index of the buffer
*
* \return        Pointer to the ringbuffer slot
*
* \pre           -
* \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_GetNormalSlot(
  uint8  BufferIndex
  );

 #if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_RingBuffer_GetNormalSampleSlotAndRotate
 *****************************************************************************/
/*!
 * \brief         Returns current normal sample slot. 
 *                Ringbuffer internally shifts to next slot.
 *
 * \details       Returns current normal sample slot
 *                Ringbuffer internally shifts to next slot.
 *
 * \return        Pointer to sample slot to fill with normal samples
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_GetNormalSampleSlotAndRotate(
  void
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
* Dem_Memory_TimeSeries_RingBuffer_GetFastSlot
*****************************************************************************/
/*!
* \brief         Get the indexed ringbuffer slot from fast rate time series DIDs
*
* \details       Get the indexed ringbuffer slot from fast rate time series DIDs
*
* \param[in]     BufferIndex
*                Index of the buffer
*
* \return        Pointer to the buffer
*
* \pre           -
* \config        DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_GetFastSlot(
  uint8  BufferIndex
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 * Dem_Memory_TimeSeries_RingBuffer_GetFastSampleSlotAndRotate
 *****************************************************************************/
/*!
 * \brief         Returns current fast sample slot. 
 *                Ringbuffer internally shifts to next slot.
 *
 * \details       Returns current fast sample slot
 *                Ringbuffer internally shifts to next slot.
 *
 * \return        Pointer to sample slot to fill with fast samples
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_GetFastSampleSlotAndRotate(
  void
  );
#endif 

/* ****************************************************************************
 * Dem_Memory_TimeSeries_RingBuffer_Init
 *****************************************************************************/
/*!
 * \brief         Initializes time series ring buffer
 *
 * \details       Initializes time series ring buffer
 *
 * \pre           NvM must have restored NV mirrors
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_TimeSeries_RingBuffer_Init(
  void
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_RINGBUFFER_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_RingBuffer_Interface.h
 *********************************************************************************************************************/
