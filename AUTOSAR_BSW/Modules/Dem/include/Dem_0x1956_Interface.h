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
/*! \ingroup    Dem_FilterData
 *  \defgroup   Dem_0x1956 0x1956
 *  \{
 *  \file       Dem_0x1956_Interface.h
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

#if !defined (DEM_0X1956_INTERFACE_H)
#define DEM_0X1956_INTERFACE_H

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
#include "Dem_0x1956_Types.h"
#include "Dem_FilterDataIF_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_0x1956_PublicProperties Public Properties
 * \{
 */

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
 * \defgroup Dem_0x1956_Public Public Methods
 * \{
 */

 /* ****************************************************************************
 *  Dem_FilterData_0x1956_IsService0x1956Enabled
 *****************************************************************************/
 /*!
 * \brief         Returns true if service 19 56 is enabled
 * \details       Returns true if service 19 subfunction 56 is enabled
 *
 * \return        TRUE
 *                Support for service 19 subfunction 56
 * \return        FALSE
 *                No support for service 19 56
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_0x1956_IsService0x1956Enabled(
  void
);

/* ****************************************************************************
 *  Dem_FilterData_0x1956_SetDtcFilterByReadinessGroup
 *****************************************************************************/
/*!
 * \brief         Initialize the DTC filter for readiness group filtering.
 *
 * \details       Initialize the DTC filter for readiness group filtering.
 *
 * \param[in]     DTCFilterId
 *                The DTC filter handle.
 * \param[in]     ReadinessGroup
 *                Readiness group number.
 *
 * \pre           Feature Service 0x19 56 is enabled and DCM support is enabled
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different DTCFilterIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_0x1956_SetDtcFilterByReadinessGroup(
  Dem_FilterData_HandleType DTCFilterId,
  Dem_Cfg_ReadinessGroupOfReadinessGroupTableType ReadinessGroup
);

/* ****************************************************************************
 *  Dem_FilterData_0x1956_GetNumberOfFilteredDTCsByReadinessGroup
 *****************************************************************************/
/*!
 * \brief         Calculate number of DTCs of a certain readiness group
 *
 * \details       Calculate number of DTCs of a certain readiness group
 *
 * \param[in]     ReadinessGroupIdx
 *                Index of the Readiness Group Table.
 *
 * \return        Number of DTCs
 *
 * \pre           Feature Service 0x19 56 is enabled and DCM support is enabled
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_FilterData_0x1956_GetNumberOfFilteredDTCsByReadinessGroup(
  uint8 ReadinessGroupIdx
);


/* ****************************************************************************
 * Dem_FilterData_0x1956_FilterDTCByReadinessGroup
 *****************************************************************************/
/*!
 * \brief         Iterates over events of a certain readiness group.
 *
 * \details       Iterates over events of a certain readiness group.
 *                The readiness group is specified in DTC Filter.
 *                
 *
 * \param[in]     DTCFilterPtr
 *                Pointer to a DTC filter.
 *
 * \return        EventId of the next event maching the readiness group filter criteria.
 *
 * \pre           Feature Service 0x19 56 is enabled and DCM support is enabled
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different DTCFilterIds
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_FilterData_0x1956_FilterDTCByReadinessGroup(
  CONSTP2VAR(Dem_Cfg_FilterData_InfoType, AUTOMATIC, AUTOMATIC)  DTCFilterPtr
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_0X1956_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_0x1956_Interface.h
 *********************************************************************************************************************/
