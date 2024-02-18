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
/*! \ingroup    Dem_Iumpr_Ratio
 *  \defgroup   Dem_Iumpr_RatioIF Dem_Iumpr_RatioIF
 *  \{
 *  \file       Dem_RatioIF_Interface.h
 *  \brief      IUMPR RatioIF subcomponent.
 *  \details    Public Interfaces of Ratio subcomponent which provides functionality to manipulate IUMPR ratios for 
 *              the Dem_Iumpr subcomponent.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_RATIOIF_INTERFACE_H)
#define DEM_RATIOIF_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_RatioIF_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Iumpr_Ratio_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Numerator_Lock
 *****************************************************************************/
/*!
 * \brief         Set numerators locked state in global iumpr state
 *
 * \details       Set numerators locked state in global iumpr state
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_Lock(
  void
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Numerator_ReleaseLock
 *****************************************************************************/
/*!
 * \brief         Reset numerators locked state in global iumpr state
 *
 * \details       Reset numerators locked state in global iumpr state
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Numerator_ReleaseLock(
  void
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_ResetFidPending
 *****************************************************************************/
/*!
 * \brief         Set the ratio as not blocked by a FiD
 *
 * \details       Set the ratio as not blocked by a FiD
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_ResetFidPending(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Disconnect
 *****************************************************************************/
/*!
 * \brief         Set ratio disconnected state of a ratio
 *
 * \details       Set ratio disconnected state of a ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Disconnect(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );


/* ****************************************************************************
 * Dem_Iumpr_Ratio_Reconnect
 *****************************************************************************/
/*!
 * \brief         Reset ratio disconnected state of a ratio
 *
 * \details       Reset ratio disconnected state of a ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Reconnect(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

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
 * \defgroup Dem_Iumpr_Ratio_Public Public Methods
 * \{
 */
 
/* ****************************************************************************
 * Dem_Iumpr_Ratio_TestAndClearAnyUpdatePending()
 *****************************************************************************/
/*!
 * \brief         Returns TRUE if any ratio needs to be updated and clears the
 *                flag.
 *
 * \details       -
 *
 * \return        TRUE   Update Pending flag was set
 * \return        FALSE  Update Pending flag was not set
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_TestAndClearAnyUpdatePending(
  void
);

/* ****************************************************************************
 * Dem_Iumpr_Ratio_SetAnyUpdatePending()
 *****************************************************************************/
 /*!
  * \brief         Sets the flag indicating that any ratio needs to be
  *                processed from the IUMPR MainFunction
  *
  * \details       -
  *
  * \pre           -
  *
  * \context       TASK|ISR2
  * \synchronous   TRUE
  * \reentrant     TRUE
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_SetAnyUpdatePending(
  void
);

/* ****************************************************************************
 * Dem_Iumpr_Ratio_GetReadinessGroupType
 *****************************************************************************/
/*!
 * \brief         Get the readiness group type of the ratio
 *
 * \details       Get the readiness group type (e.g. Cat1, Cat2, BoostPr, ...)
 *                of the ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 * \return        The readiness group type of the ratio
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_IumprReadinessGroupType, DEM_CODE)
Dem_Iumpr_Ratio_GetReadinessGroupType(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_QueueUpdate
 *****************************************************************************/
/*!
 * \brief         Set the update state of the ratio
 *
 * \details       Set the update state of the ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 * \param[in]     Value
 *                New update state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_QueueUpdate(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex,
  CONST(boolean, AUTOMATIC) Value
  );


/* ****************************************************************************
 * Dem_Iumpr_Ratio_GetRatioStatusUtil
 *****************************************************************************/
/*!
 * \brief         Get the status of the ratio
 *
 * \details       Get the status of the ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 *
 * \return        The status of the ratio
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Iumpr_Ratio_GetRatioStatusUtil(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_SetRatioStatusUtil
 *****************************************************************************/
/*!
 * \brief         Set the status of the ratio
 *
 * \details       Set the status of the ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 * \param[in]     Value
 *                New status of the ratio
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_SetRatioStatusUtil(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex,
  CONST(uint8, AUTOMATIC) Value
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_OpCycleStart
 *****************************************************************************/
/*!
 * \brief         Perform all actions relevant on OBD DCY restart
 *
 * \details       -
 *
 * \param[in]     RatioIndex
 *                Unique handle of the ratio
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_OpCycleStart(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );


/* ****************************************************************************
 * Dem_Iumpr_Ratio_ProcessUpdate
 *****************************************************************************/
/*!
 * \brief         Performs scheduled IUMPR calculations for a pending ratio.
 *
 * \details       Performs scheduled IUMPR calculations for a pending ratio.
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 * \return        TRUE
 *                Ratio status has changed, and needs a NvM update
 * \return        FALSE
 *                Ratio status hasn't changed, and needs no NvM update
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_ProcessUpdate(
  Dem_RatioIdIndexType RatioIndex
  );


/* ****************************************************************************
 * Dem_Iumpr_Ratio_InitNv
 *****************************************************************************/
/*!
 * \brief         Initalize ratio specific information that is persisted to NvM
 *
 * \details       Used when the IUMPR Nv-Block needs to be re-initialized.
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 * \pre           Feature IUMPR is supported
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different RatioIndex
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_InitNv(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_ReportRatioFault
 *****************************************************************************/
/*!
 * \brief         Queue ratio processing for an event
 *
 * \details       This function will set up IUMPR processing of the event's
 *                ratio, if the numerator has not been incremented yet.
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 * \param[in]     FaultOrigin
 *                Information whether the fault was reported by API or by an
 *                event report
 *
 * \pre           Feature IUMPR is supported
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_ReportRatioFault(
  Dem_RatioIdIndexType RatioIndex,
  Dem_Iumpr_FaultOriginType FaultOrigin
  );

/* ****************************************************************************
 * Dem_Iumpr_Ratio_GetRatio
 *****************************************************************************/
/*!
 * \brief         Get numerator and denominator
 *
 * \details       Get numerator and denominator
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_GetRatio(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex,
  CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) Numerator,
  CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) Denominator
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_RATIOIF_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_RatioIF_Interface.h
 *********************************************************************************************************************/
