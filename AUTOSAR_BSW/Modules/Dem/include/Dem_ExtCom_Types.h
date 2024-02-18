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
/*! \addtogroup Dem_ExternalCommunication
 *  \{
 *  \file       Dem_ExtCom_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public types of external communication subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_EXTCOM_TYPES_H)
#define DEM_EXTCOM_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#if ((DEM_CFG_NOTIFY_MONITOR_STATUS_FIM == STD_ON) && (DEM_CFG_USE_MULTI_PARTITION_FIM == STD_ON))
#include "FiM.h"
#endif

#if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
# include "Os.h"
#endif
                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if defined(FIM_TYPES_H)
/*! FiM Application type wrapper. The type must be provided by the FiM */
typedef FiM_FunctionIdType Dem_ExtCom_FiMFunctionIdType;
#else
/*! FiM Application type wrapper. The type is probably not provided by the FiM, so substitute a replacement */
typedef uint16 Dem_ExtCom_FiMFunctionIdType;
#endif

#if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
 /*! OS Application type wrapper. The type must be provided by the Os */
typedef ApplicationType Dem_ExtCom_ApplicationType;
#else
 /*! OS Application type wrapper. The type is probably not provided by the Os, so substitute a replacement */
typedef uint32 Dem_ExtCom_ApplicationType;
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/


/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

#endif /* DEM_EXTCOM_TYPES_H */
/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ExtCom_Types.h
 *********************************************************************************************************************/
