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
/*! \ingroup    Dem_RecordReader
 *  \defgroup   Dem_IntDataElement IntDataElement
 *  \{
 *  \file       Dem_IntDataElement_Interface.h
 *  \brief      Module fetches internal data elements during an on-going read operation.
 *  \details    Module fetches the values for specific internal data elements. The statistical data are calculated 
 *              'live' and provided for an on-going read operation.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_INTDATAELEMENT_INTERFACE_H)
#define DEM_INTDATAELEMENT_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_IntDataElement_Types.h"

/* Includes for Other Types used by the Implementation */
/* ------------------------------------------------------------------------- */
#include "Dem_DataReport_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_IntDataElementIF_PublicProperties Public Properties
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
 * \defgroup Dem_IntDataElementIF_Public Public Methods
 * \{
 */

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElement_CopyInternalDataElement
 *****************************************************************************/
/*!
 * \brief         Copies an internal data element into the destination buffer.
 *
 * \details       Copies an internal data element into the destination buffer.
 *
 * \param[in,out] DidCopyInfoPtr
 *                CopyDid context
 * \param[in,out] DidSourceBufferReadInfoPtr
 *                Information on current source buffer read position.
 * \param[in]     DataIndex
 *                Index of requested data element
 *
 * \return        TRUE
 *                Data element was copied.
 * \return        FALSE
 *                Data element was not copied.
 *
 * \pre           A memory entry has to be locked for Dcm readout.
 * \config        DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElement_CopyInternalDataElement(
  CONST(Dem_DataReport_DidCopyInfoPtrType, AUTOMATIC)  DidCopyInfoPtr,
  CONST(Dem_DataReport_DidSourceBufferReadInfoPtrType, AUTOMATIC)  DidSourceBufferReadInfoPtr,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_INTDATAELEMENT_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_IntDataElement_Interface.h
 *********************************************************************************************************************/
