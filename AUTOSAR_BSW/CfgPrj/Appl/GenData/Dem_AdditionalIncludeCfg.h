/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Dem
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: Huf H_lsbeck & F_rst GmbH & Co. KG
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: S32K144
 *    License Scope : The usage is restricted to CBD2100188_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Dem_AdditionalIncludeCfg.h
 *   Generation Time: 2023-01-16 14:01:26
 *           Project: DaVinciConfigurationS32K144 - Version 1.0
 *          Delivery: CBD2100188_D01
 *      Tool Version: DaVinci Configurator  5.23.45 SP4
 *
 *
 *********************************************************************************************************************/


/* configuration, interrupt handling and callback headers use different names
 * for the multiple inclusion protection define, shown in this example. The
 * appropriate names for these files can be taken from this list:
 *
 * Dem_Cfg.h:                   DEM_CFG_H
 * Dem_Lcfg.h:                  DEM_LCFG_H
 * Dem_PBcfg.h:                 DEM_PBFG_H
 * Dem_AdditionalIncludeCfg.h:  DEM_ADDITIONALINCLUDECFG_H
 */
#if !defined (DEM_ADDITIONALINCLUDECFG_H)
# define DEM_ADDITIONALINCLUDECFG_H


/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/

/* From configuration parameter /Dem/DemGeneral/DemHeaderFileInclusion: */
#include "Dcm.h"
#include "Dem_Dtc.h"


#endif  /* DEM_ADDITIONALINCLUDECFG_H */
/**********************************************************************************************************************
  END OF FILE: Dem_AdditionalIncludeCfg.h     [Vag (Vector), VARIANT-PRE-COMPILE, 20.06.01.133983]
**********************************************************************************************************************/

