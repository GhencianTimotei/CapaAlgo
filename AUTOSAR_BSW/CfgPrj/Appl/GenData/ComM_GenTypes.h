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
 *            Module: ComM
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: Huf H_lsbeck & F_rst GmbH & Co. KG
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: S32K144
 *    License Scope : The usage is restricted to CBD2100188_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: ComM_GenTypes.h
 *   Generation Time: 2022-11-10 14:15:51
 *           Project: DaVinciConfigurationS32K144 - Version 1.0
 *          Delivery: CBD2100188_D01
 *      Tool Version: DaVinci Configurator  5.23.45 SP4
 *
 *
 *********************************************************************************************************************/



#if !defined(COMM_GENTYPES_H)
#define COMM_GENTYPES_H

/* -----------------------------------------------------------------------------
    &&&~ GENERATED COMM DATA TYPES
 ----------------------------------------------------------------------------- */
/* types generated by Rte */
#include "Rte_ComM_Type.h"

typedef struct ComM_InhibitionTypeTag
{
  ComM_InhibitionStatusType ComM_ECUGroupClassification;
  uint16 ComM_InhibitCnt;
  ComM_InhibitionStatusType ComM_InhibitionStatus[1uL]; /* PRQA S 1039 */ /* MD_ComM_1039 */
} ComM_InhibitionType;

#endif /* COMM_GENTYPES_H */

