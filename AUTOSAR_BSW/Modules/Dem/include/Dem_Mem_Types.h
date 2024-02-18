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
/*! \addtogroup Dem_Mem
 *  \{
 *  \file       Dem_Mem_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEM_TYPES_H)
#define DEM_MEM_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*! Aging counter threshold for PID aging */
#define DEM_MEM_PID_AGING_COUNTER_THRESHOLD      0x28U


/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* Entry->State currently used bits: 0x89 */
/*! Set not qualified status bits  */
#define DEM_MEM_SET_NON_QUALIFIED_STATUS_BITS(Reg)            ((uint8)((Reg) | 0x77U))
/*! Applies qualified status to memory entry status byte */
#define DEM_MEM_APPLY_QUALIFIED_STATUS(State, QualifyStatus)  ((uint8)(((State) & 0x77U) | ((QualifyStatus) & 0x88U)))

/*! Test aging only state of memory entry status byte */
#define DEM_MEM_TEST_AGING_ONLY(State)           ((uint8)((State) & 0x01U) == 0x01U)
/*! Set aging only state of memory entry status byte */
#define DEM_MEM_SET_AGING_ONLY(State)            ((uint8)((State) | 0x01U))
/*! Reset aging only state of memory entry status byte */
#define DEM_MEM_RESET_AGING_ONLY(State)          ((uint8)((State) & 0xfeU))

#if (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
/*! Get the PID41 disabled mask state */
# define Dem_Mem_GetPid41DisabledMask()          (Dem_Cfg_AdminData.Pid41DisabledMask)
/*! Set the PID41 disabled mask state */
# define Dem_Mem_SetPid41DisabledMask(Value)     (Dem_Cfg_AdminData.Pid41DisabledMask = (Value))
#endif

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
/*! Get the PID01 completed mask state */
# define Dem_Mem_GetPid01CompletedMask()         (Dem_Cfg_StatusData.Pid01CompletedMask)
/*! Set the PID01 completed mask state */
# define Dem_Mem_SetPid01CompletedMask(Value)    (Dem_Cfg_StatusData.Pid01CompletedMask = (Value))
#endif

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
#  if (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
/*! Get the permanent DTC storage activation state */
#  define Dem_Mem_GetPermanentActivationState()         ((boolean)(Dem_Cfg_AdminData.PermanentActivationState))
/*! Set the permanent DTC storage activation state */
#  define Dem_Mem_SetPermanentActivationState(Value)    (Dem_Cfg_AdminData.PermanentActivationState = (Value))
/*! Get the permanent DTC storage activation distance */
#  define Dem_Mem_GetPermanentActivationDistance()      (Dem_Cfg_AdminData.PermanentActivationDistance)
/*! Set the permanent DTC storage activation distance */
#  define Dem_Mem_SetPermanentActivationDistance(Value) (Dem_Cfg_AdminData.PermanentActivationDistance = (Value))
# endif
/*! Initialization pattern for permanent DTC memory */
# define DEM_MEM_PERMANENT_INIT_PATTERN          (0x4cb9U)
#endif

#if (DEM_CFG_SUPPORT_PID21 == STD_ON)
/*! Get the odometer with MIL on */
# define Dem_Mem_GetOdometerMilOn()              (Dem_Cfg_AdminData.OdometerMilOn)
/*! Set the odometer with MIL on */
# define Dem_Mem_SetOdometerMilOn(Value)         (Dem_Cfg_AdminData.OdometerMilOn = (Value))
#endif

#if (DEM_CFG_SUPPORT_PID30 == STD_ON)
/*! Get the warmup count since clear */
# define Dem_Mem_GetWarmUpCountSinceClear()      (Dem_Cfg_AdminData.WarmUpCountAtClear)
/*! Set the warmup count since clear */
# define Dem_Mem_SetWarmUpCountSinceClear(Value)  (Dem_Cfg_AdminData.WarmUpCountAtClear = (Value))
#endif

#if (DEM_CFG_SUPPORT_PID31 == STD_ON)
/*! Get the odometer at clear */
# define Dem_Mem_GetOdometerAtClear()            (Dem_Cfg_AdminData.OdometerAtClear)
/*! Set the odometer at clear */
# define Dem_Mem_SetOdometerAtClear(Value)       (Dem_Cfg_AdminData.OdometerAtClear = (Value))
#endif

#if (DEM_CFG_SUPPORT_PID4D == STD_ON)
/*! Get the engine time with MIL on */
# define Dem_Mem_GetEngineTimeMilOn()            (Dem_Cfg_AdminData.EngineRunTimeMilOn)
/*! Set the engine time with MIL on */
# define Dem_Mem_SetEngineTimeMilOn(Value)       (Dem_Cfg_AdminData.EngineRunTimeMilOn = (Value))
#endif

#if (DEM_CFG_SUPPORT_PID4E == STD_ON)
/*! Get the engine time since clear */
# define Dem_Mem_GetEngineTimeSinceClear()       (Dem_Cfg_AdminData.EngineRunTimeSinceDtcClear)
/*! Set the engine time since clear */
# define Dem_Mem_SetEngineTimeSinceClear(Value)  (Dem_Cfg_AdminData.EngineRunTimeSinceDtcClear = (Value))
#endif

#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
/*! Get the PID aging counter */
# define Dem_Mem_GetPidAgingCounter()            (Dem_Cfg_AdminData.PidAgingCounter)
/*! Set the PID aging counter */
# define Dem_Mem_SetPidAgingCounter(Value)       (Dem_Cfg_AdminData.PidAgingCounter = (Value))
#endif

/*! Test if an OBD odometer value is invalid */
#define DEM_MEM_TEST_ODOMETER_ISINVALID(Odometer)  ((Dem_GetHiHiByte(Odometer) & 0x80U) != 0u)
/*! Set OBD odometer value invalid */
#define DEM_MEM_SET_ODOMETER_INVALID(Odometer)     ((uint32)((Odometer) | 0x80000000UL))
/*! Reset OBD odometer value invalid */
#define DEM_MEM_RESET_ODOMETER_INVALID(Odometer)   ((uint32)((Odometer) & 0x7fffffffUL))

/*! Test if an OBD engine runtime value is invalid */
#define DEM_MEM_TEST_ENGRUNTIME_ISINVALID(EngRunTime)  ((Dem_GetHiHiByte(EngRunTime) & 0x80U) != 0u)
/*! Set OBD engine runtime value invalid */
#define DEM_MEM_SET_ENGRUNTIME_INVALID(EngRunTime)     ((uint32)((EngRunTime) | 0x80000000UL))
/*! Reset OBD engine runtime value invalid */
#define DEM_MEM_RESET_ENGRUNTIME_INVALID(EngRunTime)   ((uint32)((EngRunTime) & 0x7fffffffUL))

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/*! Get the global B1 counter */
# define Dem_Mem_GetB1Counter()                  (Dem_Cfg_AdminData.B1Counter)
/*! Set the global B1 counter */
# define Dem_Mem_SetB1Counter(Value)             (Dem_Cfg_AdminData.B1Counter = (Value))

/*! Get the global B1 healing counter */
# define Dem_Mem_GetB1HealingCounter()           (Dem_Cfg_AdminData.B1HealingCounter)
/*! Set the global B1 healing counter */
# define Dem_Mem_SetB1HealingCounter(Value)      (Dem_Cfg_AdminData.B1HealingCounter = (Value))

/*! Get the continuous MI counter */
# define Dem_Mem_GetContinuousMiCounter()        (Dem_Cfg_AdminData.ContinuousMiCounter)
/*! Set the continuous MI counter */
# define Dem_Mem_SetContinuousMiCounter(Value)   (Dem_Cfg_AdminData.ContinuousMiCounter = (Value))

/*! Get the continuous MI aging timer */
# define Dem_Mem_GetContinuousMiAgingTimer()     (Dem_Cfg_AdminData.ContinuousMiAgingTimer)
/*! Set the continuous MI aging timer */
# define Dem_Mem_SetContinuousMiAgingTimer(Value)  (Dem_Cfg_AdminData.ContinuousMiAgingTimer = (Value))

/*! Get the continuous MI healing counter */
# define Dem_Mem_GetContinuousMiHealingCounter()  (Dem_Cfg_AdminData.ContinuousMiHealingCounter)
/*! Set the continuous MI healing counter */
# define Dem_Mem_SetContinuousMiHealingCounter(Value)  (Dem_Cfg_AdminData.ContinuousMiHealingCounter = (Value))

/*! Get the continuous MI aging counter */
# define Dem_Mem_GetContinuousMiAgingCounter()   (Dem_Cfg_AdminData.ContinuousMiAgingCounter)
/*! Set the continuous MI aging counter */
# define Dem_Mem_SetContinuousMiAgingCounter(Value)  (Dem_Cfg_AdminData.ContinuousMiAgingCounter = (Value))

/*! Get the cumulative OBD engine runtime */
# define Dem_Mem_GetCumulativeEngRuntime()       (Dem_Cfg_AdminData.CumulativeEngineRunTime)
/*! Set the cumulative OBD engine runtime */
# define Dem_Mem_SetCumulativeEngRuntime(Value)  (Dem_Cfg_AdminData.CumulativeEngineRunTime = (Value))
#endif

#if (DEM_FEATURE_NEED_MIL_GROUPS)
/*! Initialize a MIL group trip counter */
# define Dem_Mem_InitMilGroupTripCount(MilGroupIdx)            (Dem_EventInternalStatus_SetMilGroupTripCount(MilGroupIdx, 0x00U))
/*! Get a MIL group trip counter */
# define Dem_Mem_GetMilGroupTripCount(MilGroupIdx)             (Dem_EventInternalStatus_GetMilGroupTripCountRaw(MilGroupIdx) & 0x7Fu)
/*! Increment a MIL group trip counter */
# define Dem_Mem_IncrementMilGroupTripCount(MilGroupIdx)       (Dem_EventInternalStatus_SetMilGroupTripCount(MilGroupIdx, (uint8)(Dem_EventInternalStatus_GetMilGroupTripCountRaw(MilGroupIdx) + 1u)))
/*! Set a MIL group trip counter to 0 */
# define Dem_Mem_ResetMilGroupTripCount(MilGroupIdx)           (Dem_EventInternalStatus_SetMilGroupTripCount(MilGroupIdx, (Dem_EventInternalStatus_GetMilGroupTripCountRaw(MilGroupIdx) & 0x80U)))

/*! Get MIL group incremented this DCY */
# define Dem_Mem_GetMilGroupIncremented(MilGroupIdx)           (Dem_EventInternalStatus_GetMilGroupTripCountRaw(MilGroupIdx) & 0x80U)
/*! Set MIL group incremented this DCY */
# define Dem_Mem_SetMilGroupIncremented(MilGroupIdx)           (Dem_EventInternalStatus_SetMilGroupTripCount(MilGroupIdx, (Dem_EventInternalStatus_GetMilGroupTripCountRaw(MilGroupIdx) | 0x80U)))
/*! Reset MIL group incremented this DCY */
# define Dem_Mem_ResetMilGroupIncremented(MilGroupIdx)         (Dem_EventInternalStatus_SetMilGroupTripCount(MilGroupIdx, (Dem_EventInternalStatus_GetMilGroupTripCountRaw(MilGroupIdx) & 0x7fU)))

/*! Increment pending DTC count */
# define Dem_Mem_IncrementMilGroupPendingCount(MilGroupIdx)    (Dem_EventInternalStatus_SetMilGroupPendingCount(MilGroupIdx, (uint16)(Dem_EventInternalStatus_GetMilGroupPendingCount(MilGroupIdx) + 1u)))
/*! Decrement pending DTC count */
# define Dem_Mem_DecrementMilGroupPendingCount(MilGroupIdx)    (Dem_EventInternalStatus_SetMilGroupPendingCount(MilGroupIdx, (uint16)(Dem_EventInternalStatus_GetMilGroupPendingCount(MilGroupIdx) - 1u)))
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


#endif /* DEM_MEM_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Mem_Types.h
 *********************************************************************************************************************/
