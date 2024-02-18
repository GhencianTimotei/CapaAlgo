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
/*! \ingroup    Dem_Iumpr
 *  \defgroup   Dem_Iumpr_FimFid Dem_Iumpr_FimFid
 *  \{
 *  \file       Dem_FimFid_Interface.h
 *  \brief      IUMPR Fim Fid subcomponent.
 *  \details    Provides functionality to access FIM Fid specific information.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_FIMFID_INTERFACE_H)
#define DEM_FIMFID_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_FimFid_Types.h"
#include "Dem_Infrastructure_Types.h"
#include "Dem_Cfg_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_FimFid_Public Public Methods
 * \{
 */

 /* ****************************************************************************
 * Dem_FimFid_QueryPendingState
 *****************************************************************************/
 /*!
 * \brief         Get the pending state of a FiM FID
 *
 * \details       Outgoing API-Call to the FiM FID, to query the FID pending state.
 *
 * \param[in]     FID
 *                FiM FID identifier
 *
 * \return        E_OK
 *                Request was accepted and FimFaultPending state was written.
 * \return        E_NOT_OK
 *                Request was not accepted and FimFaultPending state was not writtern.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FimFid_PendingStateType, DEM_CODE)
Dem_FimFid_QueryPendingState(
  CONST(Dem_ExtCom_FiMFunctionIdType, AUTOMATIC) FID
);


/* ****************************************************************************
 * Dem_FimFidIter_Exists
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
 *                Dem_FimFidIter_Get() will return a valid element
 *                on this iterator
 * \return        FALSE
 *                Dem_FimFidIter_Get() is undefined on this iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FimFidIter_Exists(
CONSTP2CONST(Dem_Cfg_ObdFimFidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_FimFidIter_Get
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator
 *
 * \details       Get the element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        FiM Function ID
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ExtCom_FiMFunctionIdType, DEM_CODE)
Dem_FimFidIter_Get(
CONSTP2CONST(Dem_Cfg_ObdFimFidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_FimFidIter_Init
 *****************************************************************************/
/*!
 * \brief         Init the iterator
 *
 * \details       Initializes the iterator to enumerate FiM Function IDs
 *                configured to block the ratio
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 * \param[out]    IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FimFidIter_Init(
CONST(Dem_RatioIdIndexType, AUTOMATIC) RatioIndex,
CONSTP2VAR(Dem_Cfg_ObdFimFidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_FimFidIter_Next
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
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FimFidIter_Next(
CONSTP2VAR(Dem_Cfg_ObdFimFidIterType, AUTOMATIC, AUTOMATIC)  IterPtr
);

/* ****************************************************************************
 * Dem_FimFid_GetIgnitionCycle
 *****************************************************************************/
/*!
 * \brief         Get the FiM Function ID blocking the ignition cycle
 *
 * \details       Get the FiM Function ID blocking the ignition cycle
 *
 * \return        Unique handle of the FID
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ExtCom_FiMFunctionIdType, DEM_CODE)
Dem_FimFid_GetIgnitionCycle(
void
);

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_FIMFID_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_FimFid_Interface.h
 *********************************************************************************************************************/
