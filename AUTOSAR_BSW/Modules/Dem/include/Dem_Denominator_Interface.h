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
/*! \ingroup    Dem_Ratio
 *  \defgroup   Dem_Denominator Denominator
 *  \{
 *  \file       Dem_Denominator_Interface.h
 *  \brief      IUMPR Ratio Denominator subcomponent.
 *  \details    Provides functionality to manipulate IUMPR ratio denominators, and react to denominator condition changes.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DENOMINATOR_INTERFACE_H)
#define DEM_DENOMINATOR_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Denominator_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_ClearDTC_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_GetValue
 *****************************************************************************/
/*!
 * \brief         Get the denominator group of the ratio
 *
 * \details       Get the denominator group of the ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 * \return        The Denominator group \ref Dem_Cfg_DenominatorGroupType
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_GetValue(
CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
);

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_TestIncremented
 *****************************************************************************/
/*!
 * \brief         Test denominator incremented state of the ratio
 *
 * \details       Test denominator incremented state of the ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 * \return        TRUE
 *                Denominator was incremented in the current operation cycle
 * \return        FALSE
 *                Denominator was not incremented in the current operation cycle
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_TestIncremented(
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
 * \defgroup Dem_Iumpr_Ratio_Denominator_Public Public Methods
 * \{
 */


/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_Increment
 *****************************************************************************/
/*!
 * \brief         Increment ratio
 *
 * \details       Increment ratio, if all conditions for its denominator group
 *                are fulfilled.
 *
 * \param[in]     RatioIndex
 *                Ratio identifier
 *
 * \return        TRUE
 *                Ratio has changed
 * \return        FALSE
 *                Ratio hasn't changed
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_Increment(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex);

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_HandleOverflow
 *****************************************************************************/
/*!
 * \brief         Overflow handling of the denominator
 *
 * \details       Overflow handling of the denominator
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_HandleOverflow(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex);

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_Lock
 *****************************************************************************/
/*!
 * \brief         Lock denominator ratio
 *
 * \details       Lock denominator ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_Lock(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex);

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_Release
 *****************************************************************************/
/*!
 * \brief         Release denominator ratio lock
 *
 * \details       Release denominator ratio lock
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 * \return        TRUE
 *                Denominator of the ratio was already incremented this cycle
 * \return        FALSE
 *                Denominator of the ratio was not incremented this cycle
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_Release(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex);


/* ****************************************************************************
* Dem_Iumpr_Ratio_Denominator_UpdateRatioStatus
*****************************************************************************/
/*!
* \brief         Stores Ratio specific information
*
* \details       Stores Ratio specific information.
*                - Currently only relevant for 500mi denominator group
*
* \param[in]     RatioIndex
*                Unique handle of the Ratio
*
* \return        TRUE
*                Ratio status has changed
* \return        FALSE
*                Ratio status hasn't changed
*
* \pre           -
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     FALSE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_UpdateRatioStatus(CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex);

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_GetDenominatorGroup
 *****************************************************************************/
/*!
 * \brief         Get the denominator group of the ratio
 *
 * \details       Get the denominator group of the ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 * \return        The Denominator group \ref Dem_Cfg_DenominatorGroupType
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_GetDenominatorGroup(
CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
);

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_InitNv
 *****************************************************************************/
/*!
 * \brief         Initalize denominator status bits and counter value
 *
 * \details       Initalize denominator status bits and counter value
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
Dem_Iumpr_Ratio_Denominator_InitNv(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
);

/* ****************************************************************************
 * Dem_Iumpr_Ratio_Denominator_OpCycleStart
 *****************************************************************************/
/*!
 * \brief         Initalize denominator status bits relevant to OpCycle Start
 *
 * \details       -
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio*
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Iumpr_Ratio_Denominator_OpCycleStart(
  CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex
);


/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_DENOMINATOR_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Denominator_Interface.h
 *********************************************************************************************************************/
