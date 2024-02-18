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
/*! \addtogroup Dem_Indicator
 *  \{
 *  \file       Dem_Indicator_Implementation.h
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

#if !defined (DEM_INDICATOR_IMPLEMENTATION_H)
#define DEM_INDICATOR_IMPLEMENTATION_H

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
#include "Dem_Indicator_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Core_Interface.h"
#include "Dem_Infrastructure_Interface.h"
#include "Dem_FaultMemory_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_INDICATOR_IMPLEMENTATION_FILENAME "Dem_Indicator_Implementation.h"
/*!
 * \defgroup  Dem_J1939_LampStates Macros encoding J1939 lamp states
 * \{
 */
#define DEM_J1939_LAMP_NA              (0x03U)  /*!< Indicator not configured */
#define DEM_J1939_LAMP_OFF             (0x00U)  /*!< Indicator off */
#define DEM_J1939_LAMP_ON              (0x01U)  /*!< Indicator on */

#define DEM_J1939_LAMP_MIL_NA          (DEM_J1939_LAMP_NA << 6u)  /*!< Bitmask for MIL indicator */
#define DEM_J1939_LAMP_RSL_NA          (DEM_J1939_LAMP_NA << 4u)  /*!< Bitmask for RSL indicator */
#define DEM_J1939_LAMP_AWL_NA          (DEM_J1939_LAMP_NA << 2u)  /*!< Bitmask for AWL indicator */
#define DEM_J1939_LAMP_PL_NA           (DEM_J1939_LAMP_NA)       /*!< Bitmask for PL indicator */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_J1939_FlashLampStates Macros encoding J1939 flash lamp states
 * \{
 */
#define DEM_J1939_FLASHLAMP_FAST_FLASH      (0x01U)  /*!< Indicator fast flashing */
#define DEM_J1939_FLASHLAMP_SLOW_FLASH      (0x00U)  /*!< Indicator slow flashing */
#define DEM_J1939_FLASHLAMP_NO_FLASH        (0x03U)  /*!< Indicator not flashing (either not configured, off or continuous) */

#define DEM_J1939_FLASHLAMP_MIL_NO_FLASH    (DEM_J1939_FLASHLAMP_NO_FLASH << 6u)  /*!< Bitmask for MIL flashing */
#define DEM_J1939_FLASHLAMP_RSL_NO_FLASH    (DEM_J1939_FLASHLAMP_NO_FLASH << 4u)  /*!< Bitmask for RSL flashing */
#define DEM_J1939_FLASHLAMP_AWL_NO_FLASH    (DEM_J1939_FLASHLAMP_NO_FLASH << 2u)  /*!< Bitmask for AWL flashing */
#define DEM_J1939_FLASHLAMP_PL_NO_FLASH     (DEM_J1939_FLASHLAMP_NO_FLASH)       /*!< Bitmask for PL flashing */
/*!
 * \}
 */
/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

#define DEM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/*! Number of qualified active and failed events per WWHO-OBD class. Index 0 (no class) is unused. */
DEM_LOCAL VAR(Dem_EventIdType, DEM_VAR_NOINIT)   Dem_Esm_QualifiedActiveEventCount[DEM_ESM_WWHOBD_NUMBER_DTCCLASS];
/*! Number of MIL requests per WWHO-OBD class. Index 0 (no class) is unused. */
DEM_LOCAL VAR(Dem_EventIdType, DEM_VAR_NOINIT)   Dem_Esm_DtcClassMILCount[DEM_ESM_WWHOBD_NUMBER_DTCCLASS];
#endif

#define DEM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Indicator_PrivateProperties Private Properties
 * \{
 */
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_SetDtcClassMILCount
 *****************************************************************************/
/*!
 * \brief         Set the number of MIL requests for the WWH-OBD DTC class
 *
 * \details       Set the number of MIL requests for the WWH-OBD DTC class
 *
 * \param[in]     WwhObdDtcClass
 *                Unique handle of the WWH-OBD DTC class
 * \param[in]     DtcClassMILCount
 *                The new number of MIL requests
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetDtcClassMILCount(
  CONST(uint8, AUTOMATIC)  WwhObdDtcClass,
  CONST(Dem_EventIdType, AUTOMATIC)  DtcClassMILCount
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_SetDtcClassMILCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetDtcClassMILCount(
  CONST(uint8, AUTOMATIC)  WwhObdDtcClass,
  CONST(Dem_EventIdType, AUTOMATIC)  DtcClassMILCount
  )
{

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (WwhObdDtcClass >= DEM_ESM_WWHOBD_NUMBER_DTCCLASS)
  {
    Dem_Error_RunTimeCheckFailed(DEM_INDICATOR_IMPLEMENTATION_FILENAME, __LINE__);                                               /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Esm_DtcClassMILCount[WwhObdDtcClass] = DtcClassMILCount;                                                                 /* SBSW_DEM_ARRAY_WRITE_DTCCLASSMILCOUNT */
  }
}
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_Indicator_PublicProperties
 * \{
 */


/* ****************************************************************************
 % Dem_Indicator_TestHasIndicator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Indicator_TestHasIndicator(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  boolean lReturnValue;
#if ((DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON) || (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON))
  lReturnValue = TRUE;
#endif
  {
#if (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON)
    Dem_Cfg_EventNormalIndicatorIterType lIndicatorIter;
    Dem_Cfg_EventNormalIndicatorIterInit(EventId, &lIndicatorIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
    if (Dem_Cfg_EventNormalIndicatorIterExists(&lIndicatorIter) == FALSE)                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
#endif
    {
#if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
      Dem_Cfg_EventSpecialIndicatorIterType lSpecialIndicatorIter;
      Dem_Cfg_EventSpecialIndicatorIterInit(EventId, &lSpecialIndicatorIter);                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
      if ((Dem_Cfg_EventSpecialIndicatorIterExists(&lSpecialIndicatorIter) == FALSE))                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
#endif
      {
        lReturnValue = FALSE;
      }
    }
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_GetQualifiedActiveEventCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Indicator_GetQualifiedActiveEventCount(
  CONST(uint8, AUTOMATIC)  WwhObdDtcClass
  )
{
  return Dem_Esm_QualifiedActiveEventCount[WwhObdDtcClass];
}
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_SetQualifiedActiveEventCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetQualifiedActiveEventCount(
  CONST(uint8, AUTOMATIC)  WwhObdDtcClass,
  CONST(Dem_EventIdType, AUTOMATIC)  QualifiedActiveEventCount
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (WwhObdDtcClass >= DEM_ESM_WWHOBD_NUMBER_DTCCLASS)
  {
    Dem_Error_RunTimeCheckFailed(DEM_INDICATOR_IMPLEMENTATION_FILENAME, __LINE__);                                               /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Esm_QualifiedActiveEventCount[WwhObdDtcClass] = QualifiedActiveEventCount;                                               /* SBSW_DEM_ARRAY_WRITE_QUALIFIEDACTIVEEVENTCOUNT */
  }
}
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_GetDtcClassMILCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Indicator_GetDtcClassMILCount(
  CONST(uint8, AUTOMATIC)  WwhObdDtcClass
  )
{
  return Dem_Esm_DtcClassMILCount[WwhObdDtcClass];
}
#endif



/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Indicator_Private Private Methods
 * \{
 */


/* ****************************************************************************
 * Dem_Indicator_SetGlobalIndicatorState
 *****************************************************************************/
/*!
 * \brief         Sets the global indicator state.
 *
 * \details       Sets the global indicator state.
 *
 * \param[in]     IndicatorId
 *                Unique handle of the indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the NmNode
 * \param[in]     IndicatorState
 *                Indicator state to set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetGlobalIndicatorState(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex,
  CONST(uint8, AUTOMATIC)  IndicatorState
  );


/* ****************************************************************************
 * Dem_Indicator_GetGlobalIndicatorState
 *****************************************************************************/
/*!
 * \brief         Gets the global indicator state.
 *
 * \details       Gets the global indicator state.
 *
 * \param[in]     IndicatorId
 *                Unique handle of the indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the NmNode
 *
 * \return        The indicator state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_GetGlobalIndicatorState(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex
  );


#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_J1939PriorityOfIndicatorState
 *****************************************************************************/
/*!
 * \brief         Gets the priority of an indicator state.
 *
 * \details       Gets the priority of an indicator state.
 *
 * \param[in]     ConfigIndicatorState
 *                The state of a J1939 related indicator.
 *
 * \return        The priority value associated with the indicator state
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939PriorityOfIndicatorState(
  CONST(uint8, AUTOMATIC)  ConfigIndicatorState
  );
#endif


#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_J1939IndicatorStateFromPriority
 *****************************************************************************/
/*!
 * \brief         Gets the indicator state from a priority value.
 *
 * \details       Gets the indicator state from a priority value.
 *
 * \param[in]     Priority
 *                The priority of a J1939 indicator state
 *
 * \return        The indicator state associated with the priority value
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939IndicatorStateFromPriority(
  CONST(uint8, AUTOMATIC)  Priority
  );
#endif


#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_J1939GlobalIndicatorState
 *****************************************************************************/
/*!
 * \brief         Gets the accumulated global indicator state over all nodes
 *
 * \details       Gets the accumulated global indicator state over all nodes
 *
 * \param[in]     IndicatorId
 *                Unique handle of the indicator
 *
 * \return        Current indicator state of the indicator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939GlobalIndicatorState(
  CONST(uint8, AUTOMATIC)  IndicatorId
  );
#endif


#if (DEM_CFG_SUPPORT_PID21 == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_GlobalMilStateDisable
 *****************************************************************************/
/*!
 * \brief         Hook function called when the MIL is deactivated
 *
 * \details       The Mil status has changed from On to Off, the current
 *                Odometer value (relative) may be reset
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PID21 == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_GlobalMilStateDisable(
  void
  );
#endif


/* ****************************************************************************
 * Dem_Indicator_GetEventCountContinuous
 *****************************************************************************/
/*!
 * \brief         Get the number of events requesting the indicator in continuous
 *                mode, relative to the J1939 node
 *
 * \details       Get the number of events requesting the indicator in continuous
 *                mode, relative to the J1939 node
 *
 * \param[in]     IndicatorId
 *                Unique handle of indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the J1939 node
 *
 * \return        The number of events requesting the indicator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Indicator_GetEventCountContinuous(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex
  );


/* ****************************************************************************
 * Dem_Indicator_SetEventCountContinuous
 *****************************************************************************/
/*!
 * \brief         Set the number of events requesting the indicator in continuous
 *                mode, relative to the J1939 node
 *
 * \details       Set the number of events requesting the indicator in continuous
 *                mode, relative to the J1939 node
 *
 * \param[in]     IndicatorId
 *                Unique handle of indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the J1939 node
 * \param[in]     ActiveEventCount
 *                New number of events
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetEventCountContinuous(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex,
  CONST(uint16, AUTOMATIC)  ActiveEventCount
  );


/* ****************************************************************************
 * Dem_Indicator_GetEventCountBlinking
 *****************************************************************************/
/*!
 * \brief         Get the number of events requesting the indicator in blinking
 *                mode, relative to the J1939 node
 *
 * \details       Get the number of events requesting the indicator in blinking
 *                mode, relative to the J1939 node
 *
 * \param[in]     IndicatorId
 *                Unique handle of indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the J1939 node
 *
 * \return        The number of events requesting the indicator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Indicator_GetEventCountBlinking(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex
  );


/* ****************************************************************************
 * Dem_Indicator_SetEventCountBlinking
 *****************************************************************************/
/*!
 * \brief         Set the number of events requesting the indicator in blinking
 *                mode, relative to the J1939 node
 *
 * \details       Set the number of events requesting the indicator in blinking
 *                mode, relative to the J1939 node
 *
 * \param[in]     IndicatorId
 *                Unique handle of indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the J1939 node
 * \param[in]     ActiveEventCount
 *                New number of events
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetEventCountBlinking(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex,
  CONST(uint16, AUTOMATIC)  ActiveEventCount
  );


/* ****************************************************************************
 * Dem_Indicator_GetEventCountFastFlash
 *****************************************************************************/
/*!
 * \brief         Get the number of events requesting the indicator in 'fast
 *                flash' mode, relative to the J1939 node
 *
 * \details       Get the number of events requesting the indicator in 'fast
 *                flash' mode, relative to the J1939 node
 *
 * \param[in]     IndicatorId
 *                Unique handle of indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the J1939 node
 *
 * \return        The number of events requesting the indicator in 'fast flash'
 *                mode
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Indicator_GetEventCountFastFlash(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex
  );


/* ****************************************************************************
 * Dem_Indicator_SetEventCountFastFlash
 *****************************************************************************/
/*!
 * \brief         Set the number of events requesting the indicator in 'fast
 *                flash' mode, relative to the J1939 node
 *
 * \details       Set the number of events requesting the indicator in 'fast
 *                flash' mode, relative to the J1939 node
 *
 * \param[in]     IndicatorId
 *                Unique handle of indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the J1939 node
 * \param[in]     ActiveEventCount
 *                New number of events requesting the indicator in 'fast flash'
 *                mode
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetEventCountFastFlash(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex,
  CONST(uint16, AUTOMATIC)  ActiveEventCount
  );


/* ****************************************************************************
 * Dem_Indicator_GetEventCountSlowFlash
 *****************************************************************************/
/*!
 * \brief         Get the number of events requesting the indicator in 'slow
 *                flash' mode, relative to the J1939 node
 *
 * \details       Get the number of events requesting the indicator in 'slow
 *                flash' mode, relative to the J1939 node
 *
 * \param[in]     IndicatorId
 *                Unique handle of indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the J1939 node
 *
 * \return        The number of events requesting the indicator in 'slow flash'
 *                mode
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Indicator_GetEventCountSlowFlash(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex
  );


/* ****************************************************************************
 * Dem_Indicator_SetEventCountSlowFlash
 *****************************************************************************/
/*!
 * \brief         Set the number of events requesting the indicator in 'slow
 *                flash' mode, relative to the J1939 node
 *
 * \details       Set the number of events requesting the indicator in 'slow
 *                flash' mode, relative to the J1939 node
 *
 * \param[in]     IndicatorId
 *                Unique handle of indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the J1939 node
 * \param[in]     ActiveEventCount
 *                New number of events requesting the indicator in 'slow flash'
 *                mode
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetEventCountSlowFlash(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex,
  CONST(uint16, AUTOMATIC)  ActiveEventCount
  );


#if (((DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)) \
    && (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON))
/* ****************************************************************************
 * Dem_Indicator_J1939LampStatus
 *****************************************************************************/
/*!
 * \brief         Maps indicator behavior to J1939 lamp status
 *
 * \details       This function maps the internal indicator behavior to the
 *                external lamp status bit mask used by J1939.
 *
 *                The J1939 representation is not bit-shifted for a specific
 *                indicator. To use the returned value in DM messages the
 *                caller needs to shift the result to the correct position
 *                first.
 *
 *                The state map only includes states used by J1939 indicators,
 *                other indicators states will not work with this function.
 *
 * \param[in]     ConfigIndicatorState
 *                The state of a J1939 related indicator.
 *
 * \return        J1939 lamp status of the passed indicator state.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON ||
 *                 DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) 
 *                && DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939LampStatus(
  CONST(uint8, AUTOMATIC)  ConfigIndicatorState
  );
#endif


#if (((DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)) \
    && (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON))
/* ****************************************************************************
 * Dem_Indicator_J1939FlashLampStatus
 *****************************************************************************/
/*!
 * \brief         Maps indicator behavior to J1939 flash lamp status
 *
 * \details       This function maps the internal indicator behavior to the
 *                external flash lamp bit mask used by J1939.
 *
 *                The J1939 representation is not bit-shifted for a specific
 *                indicator. To use the returned value in DM messages the
 *                caller needs to shift the result to the correct position
 *                first.
 *
 *                The state map only includes states used by J1939 indicators,
 *                other indicators states will not work with this function.
 *
 * \param[in]     ConfigIndicatorState
 *                The state of a J1939 related indicator.
 *
 * \return        J1939 flash amp status of the passed indicator state.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON ||
 *                 DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) 
 *                && DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939FlashLampStatus(
  CONST(uint8, AUTOMATIC)  ConfigIndicatorState
  );
#endif


/* ****************************************************************************
 * Dem_Indicator_UpdateGlobalUserIndicatorStates
 *****************************************************************************/
/*!
 * \brief         Update the global indicator state of a user defined indicator
 *
 * \details       Update the global indicator state of a user defined indicator
 *
 * \param[in]     IndicatorId
 *                Unique handle of the user defined indicator
 *
 * \pre           IndicatorId must be a user defined indicator
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdateGlobalUserIndicatorStates(
  CONST(uint8, AUTOMATIC)  IndicatorId
  );

# if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_CalculateEventJ1939LampStatusForIndicator
 *****************************************************************************/
 /*!
  * \brief         Calculate J1939 LampStatus from indicator specific lamp status
  *
  * \details       Integrates the indicator and event specific lamp status and
  *                flash lamp status into the J1939 LampStatus
  *
  * \param[in]     IndicatorId
  *                Unique handle of the user defined indicator
  * \param[in]     LampStatus
  *                Indicator specific lamp status
  * \param[in]     FlashLampStatus
  *                Indicator specific lamp status
  * \param[out]    FilterResult
  *                Pointer to receive the next matching event.
  *                The function modifies FilterResult->LampStatus
  *
  * \pre           IndicatorId must be a special indicator
  * \config        DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON
  *
  * \context       TASK|ISR2
  * \synchronous   TRUE
  * \reentrant     TRUE
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_CalculateEventJ1939LampStatusForIndicator(
  uint8 IndicatorId,
  uint8 LampStatus,
  uint8 FlashLampStatus,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
);
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ****************************************************************************
 % Dem_Indicator_SetGlobalIndicatorState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetGlobalIndicatorState(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex,
  CONST(uint8, AUTOMATIC)  IndicatorState
  )
{
#if (DEM_CFG_SUPPORT_INDICATORS == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (IndicatorId >= Dem_Cfg_GetSizeOfGlobalIndicatorStates())
    || (NmNodeIndex >= Dem_Cfg_GlobalJ1939NodeCount()))                                                                          
  {
    Dem_Error_RunTimeCheckFailed(DEM_INDICATOR_IMPLEMENTATION_FILENAME, __LINE__);                                               /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_GlobalIndicatorStates[IndicatorId][NmNodeIndex] = IndicatorState;                                                    /* SBSW_DEM_ARRAY_WRITE_GLOBALINDICATORSTATES */
  }
#else
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorState)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Indicator_GetGlobalIndicatorState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_GetGlobalIndicatorState(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex
  )
{
  uint8 lReturnValue;
#if (DEM_CFG_SUPPORT_INDICATORS == STD_ON)
  lReturnValue = Dem_Cfg_GlobalIndicatorStates[IndicatorId][NmNodeIndex];                                                        /* PRQA S 2841, 2842, 2843 */ /* MD_DEM_Dir4.1_ReadOperation, MD_DEM_Dir4.1_ReadOperation, MD_DEM_Dir4.1_ReadOperation */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = DEM_INDICATOR_OFF;
#endif
  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_J1939PriorityOfIndicatorState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939PriorityOfIndicatorState(
  CONST(uint8, AUTOMATIC)  ConfigIndicatorState
  )
{
  uint8 lReturnValue;
  switch(ConfigIndicatorState)
  {
  case DEM_INDICATOR_OFF:
    lReturnValue = 0x00U;
    break;
  case DEM_INDICATOR_SLOW_FLASH:
    lReturnValue = 0x01U;
    break;
  case DEM_INDICATOR_FAST_FLASH:
    lReturnValue = 0x02U;
    break;
  case DEM_INDICATOR_CONTINUOUS:
    lReturnValue = 0x03U;
    break;

  default:
    Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_INCONSISTENT_STATE);
    lReturnValue = 0x00U;
    break;
  }
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_J1939IndicatorStateFromPriority
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939IndicatorStateFromPriority(
  CONST(uint8, AUTOMATIC)  Priority
  )
{
  uint8 lReturnValue;
  switch(Priority)
  {
  case 0x00U:
    lReturnValue = DEM_INDICATOR_OFF;
    break;
  case 0x01U:
    lReturnValue = DEM_INDICATOR_SLOW_FLASH;
    break;
  case 0x02U:
    lReturnValue = DEM_INDICATOR_FAST_FLASH;
    break;
  case 0x03U:
    lReturnValue = DEM_INDICATOR_CONTINUOUS;
    break;

  default:
    Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_INCONSISTENT_STATE);
    lReturnValue = DEM_INDICATOR_OFF;
    break;
  }
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_J1939GlobalIndicatorState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939GlobalIndicatorState(
  CONST(uint8, AUTOMATIC)  IndicatorId
  )
{
  uint8 lGlobalIndicatorState;
  uint8 lNmNodeIndex;

  lGlobalIndicatorState = 0u;
  lNmNodeIndex = Dem_Cfg_GlobalJ1939NodeCount();

  if ( (Dem_Cfg_GlobalMilIndicator() == IndicatorId)
    || (Dem_Cfg_GlobalRslIndicator() == IndicatorId)                                                                             
    || (Dem_Cfg_GlobalAwlIndicator() == IndicatorId)                                                                             
    || (Dem_Cfg_GlobalPlIndicator() == IndicatorId))                                                                             
  {
    /*Requested indicator is J1939 special indicator, search across all nodes for state with highest priority*/
    uint8 lSpecialIndicatorPriority;
    lSpecialIndicatorPriority = 0u;
    while (lNmNodeIndex != 0u)
    {
      uint8 lTempPriority;

      --lNmNodeIndex;
      lTempPriority = Dem_Indicator_J1939PriorityOfIndicatorState(Dem_Indicator_GetGlobalIndicatorState(IndicatorId, lNmNodeIndex));

      if (lSpecialIndicatorPriority < lTempPriority)
      {
        lSpecialIndicatorPriority = lTempPriority;
      }
    }

    lGlobalIndicatorState = Dem_Indicator_J1939IndicatorStateFromPriority(lSpecialIndicatorPriority);
  }
  else
  {
    /*Requested indicator is user indicator*/
    while (lNmNodeIndex != 0u)
    {
      --lNmNodeIndex;
      lGlobalIndicatorState = (uint8)(Dem_Indicator_GetGlobalIndicatorState(IndicatorId, lNmNodeIndex) | lGlobalIndicatorState);
    }
  }
  return lGlobalIndicatorState;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_SUPPORT_J1939 == STD_ON)*/

#if (DEM_CFG_SUPPORT_PID21 == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_GlobalMilStateDisable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_GlobalMilStateDisable(
  void
  )
{
  /* If the Indicator state changes from on to off, the current Odometer value is set to invalid */
/* >>>> -------------------------------- Enter Critical Section: NonAtomic32bit */
  Dem_EnterCritical_NonAtomic32bit();

  Dem_Mem_SetOdometerMilOn(DEM_MEM_SET_ODOMETER_INVALID(Dem_Mem_GetOdometerMilOn()));

  Dem_LeaveCritical_NonAtomic32bit();
/* <<<< -------------------------------- Leave Critical Section: NonAtomic32bit */
}
#endif /* (DEM_CFG_SUPPORT_PID21 == STD_ON) */

/* ****************************************************************************
 % Dem_Indicator_GetEventCountContinuous
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Indicator_GetEventCountContinuous(
  CONST(uint8, AUTOMATIC)  IndicatorId,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  NmNodeIndex                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (DEM_CFG_SUPPORT_INDICATORS == STD_ON)
  return Dem_Cfg_IndicatorContinuous[IndicatorId][NmNodeIndex];                                                                  /* PRQA S 2841, 2843 */ /* MD_DEM_Dir4.1_ReadOperation, MD_DEM_Dir4.1_ReadOperation */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return 0;
#endif
}

/* ****************************************************************************
 % Dem_Indicator_SetEventCountContinuous
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetEventCountContinuous(
  CONST(uint8, AUTOMATIC)  IndicatorId,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  NmNodeIndex,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint16, AUTOMATIC)  ActiveEventCount                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (DEM_CFG_SUPPORT_INDICATORS == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (IndicatorId >= Dem_Cfg_GlobalIndicatorCount())
    || (NmNodeIndex >= Dem_Cfg_GlobalJ1939NodeCount()))                                                                          
  {
    Dem_Error_RunTimeCheckFailed(DEM_INDICATOR_IMPLEMENTATION_FILENAME, __LINE__);                                               /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_IndicatorContinuous[IndicatorId][NmNodeIndex] = ActiveEventCount;                                                    /* PRQA S 2842 */ /* MD_DEM_Dir4.1_RunTimeCheckWriteOperation */ /* SBSW_DEM_ARRAY_WRITE_INDICATORCONTINUOUS */ 
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ActiveEventCount)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Indicator_GetEventCountBlinking
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Indicator_GetEventCountBlinking(
  CONST(uint8, AUTOMATIC)  IndicatorId,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  NmNodeIndex                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (DEM_CFG_SUPPORT_INDICATORS == STD_ON)
  return Dem_Cfg_IndicatorBlinking[IndicatorId][NmNodeIndex];                                                                    /* PRQA S 2842, 2843 */ /* MD_DEM_Dir4.1_ReadOperation, MD_DEM_Dir4.1_ReadOperation */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return 0;
#endif
}

/* ****************************************************************************
 % Dem_Indicator_SetEventCountBlinking
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetEventCountBlinking(
  CONST(uint8, AUTOMATIC)  IndicatorId,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  NmNodeIndex,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint16, AUTOMATIC)  ActiveEventCount                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (DEM_CFG_SUPPORT_INDICATORS == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (IndicatorId >= Dem_Cfg_GlobalIndicatorCount())
    || (NmNodeIndex >= Dem_Cfg_GlobalJ1939NodeCount()) )                                                                         
  {
    Dem_Error_RunTimeCheckFailed(DEM_INDICATOR_IMPLEMENTATION_FILENAME, __LINE__);                                               /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_IndicatorBlinking[IndicatorId][NmNodeIndex] = ActiveEventCount;                                                      /* PRQA S 2842, 2843 */ /* MD_DEM_Dir4.1_RunTimeCheckWriteOperation, MD_DEM_Dir4.1_RunTimeCheckWriteOperation */ /* SBSW_DEM_ARRAY_WRITE_INDICATORBLINKING */
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ActiveEventCount)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Indicator_GetEventCountFastFlash
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Indicator_GetEventCountFastFlash(                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  IndicatorId,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  NmNodeIndex                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (Dem_Cfg_HasIndicatorFastFlash() == TRUE)
  return Dem_Cfg_IndicatorFastFlash[IndicatorId][NmNodeIndex];
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return 0;
#endif
}

/* ****************************************************************************
 % Dem_Indicator_SetEventCountFastFlash
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetEventCountFastFlash(                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  IndicatorId,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  NmNodeIndex,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint16, AUTOMATIC)  ActiveEventCount                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (Dem_Cfg_HasIndicatorFastFlash() == TRUE)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (IndicatorId >= Dem_Cfg_GlobalIndicatorCount())
    || (NmNodeIndex >= Dem_Cfg_GlobalJ1939NodeCount()) )                                                                         
  {
    Dem_Error_RunTimeCheckFailed(DEM_INDICATOR_IMPLEMENTATION_FILENAME, __LINE__);                                               /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_IndicatorFastFlash[IndicatorId][NmNodeIndex] = ActiveEventCount;                                                     /* SBSW_DEM_ARRAY_WRITE_INDICATORFASTFLASH */
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ActiveEventCount)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Indicator_GetEventCountSlowFlash
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Indicator_GetEventCountSlowFlash(                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  IndicatorId,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  NmNodeIndex                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (Dem_Cfg_HasIndicatorSlowFlash() == TRUE)
  return Dem_Cfg_IndicatorSlowFlash[IndicatorId][NmNodeIndex];
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return 0;
#endif
}

/* ****************************************************************************
 % Dem_Indicator_SetEventCountSlowFlash
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetEventCountSlowFlash(                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  IndicatorId,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  NmNodeIndex,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint16, AUTOMATIC)  ActiveEventCount                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (Dem_Cfg_HasIndicatorSlowFlash() == TRUE)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (IndicatorId >= Dem_Cfg_GlobalIndicatorCount())
    || (NmNodeIndex >= Dem_Cfg_GlobalJ1939NodeCount()) )                                                                         
  {
    Dem_Error_RunTimeCheckFailed(DEM_INDICATOR_IMPLEMENTATION_FILENAME, __LINE__);                                               /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_IndicatorSlowFlash[IndicatorId][NmNodeIndex] = ActiveEventCount;                                                     /* SBSW_DEM_ARRAY_WRITE_INDICATORSLOWFLASH */
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ActiveEventCount)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

#if (((DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)) \
    && (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON))
/* ****************************************************************************
 % Dem_Indicator_J1939LampStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939LampStatus(
  CONST(uint8, AUTOMATIC)  ConfigIndicatorState
  )
{
  uint8 lReturnValue;
  switch(ConfigIndicatorState)
  {
  case DEM_INDICATOR_OFF:
    lReturnValue = DEM_J1939_LAMP_OFF;
    break;
  case DEM_INDICATOR_FAST_FLASH:
  case DEM_INDICATOR_SLOW_FLASH:
  case DEM_INDICATOR_CONTINUOUS:
    lReturnValue = DEM_J1939_LAMP_ON;
    break;
  default:
    Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_INCONSISTENT_STATE);
    lReturnValue = DEM_J1939_LAMP_OFF;
    break;
  }
  return lReturnValue;
}
#endif

#if (((DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)) \
    && (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON))
/* ****************************************************************************
 % Dem_Indicator_J1939FlashLampStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939FlashLampStatus(
  CONST(uint8, AUTOMATIC)  ConfigIndicatorState
  )
{
  uint8 lReturnValue;
  switch(ConfigIndicatorState)
  {
  case DEM_INDICATOR_OFF:
    lReturnValue = DEM_J1939_FLASHLAMP_NO_FLASH;
    break;
  case DEM_INDICATOR_FAST_FLASH:
    lReturnValue = DEM_J1939_FLASHLAMP_FAST_FLASH;
    break;
  case DEM_INDICATOR_SLOW_FLASH:
    lReturnValue = DEM_J1939_FLASHLAMP_SLOW_FLASH;
    break;
  case DEM_INDICATOR_CONTINUOUS:
    lReturnValue = DEM_J1939_FLASHLAMP_NO_FLASH;
    break;
  default:
    Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_INCONSISTENT_STATE);
    lReturnValue = DEM_J1939_FLASHLAMP_NO_FLASH;
    break;
  }
  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_Indicator_UpdateGlobalUserIndicatorStates
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdateGlobalUserIndicatorStates(
  CONST(uint8, AUTOMATIC)  IndicatorId
  )
{
  uint8 lNmNodeIndex;
  
  for (lNmNodeIndex = 0u; lNmNodeIndex < Dem_Cfg_GlobalJ1939NodeCount(); ++lNmNodeIndex)
  {
    Dem_IndicatorStatusType lIndicatorState;
    lIndicatorState = DEM_INDICATOR_OFF;

    if (Dem_Indicator_GetEventCountContinuous(IndicatorId, lNmNodeIndex) > 0u)
    {
      lIndicatorState = DEM_INDICATOR_CONTINUOUS;
    }

    if (Dem_Indicator_GetEventCountBlinking(IndicatorId, lNmNodeIndex) > 0u)
    {
      lIndicatorState |= DEM_INDICATOR_BLINKING;
    }
    Dem_Indicator_SetGlobalIndicatorState(IndicatorId, lNmNodeIndex, lIndicatorState);
  }
}

#if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_CalculateEventJ1939LampStatusForIndicator
 *****************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
  */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_CalculateEventJ1939LampStatusForIndicator(                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_CONFIGURATION_SWITCH */
  uint8 IndicatorId,
  uint8 LampStatus,
  uint8 FlashLampStatus,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
)
{
  uint8 lTempLampStatus;
  uint8 lTempFlashLampStatus;

  /* Each indicator exists at most one time for the event, so calculate composite lamp status by bitwise OR operation */
  if ( (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
    && (IndicatorId == Dem_Cfg_GlobalMilIndicator()))
  {
    lTempLampStatus = (uint8)(DEM_J1939_LAMP_RSL_NA | DEM_J1939_LAMP_AWL_NA | DEM_J1939_LAMP_PL_NA | (LampStatus << 6u));
    (FilterResult->LampStatus).LampStatus =                                                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      (FilterResult->LampStatus).LampStatus & lTempLampStatus;

    lTempFlashLampStatus = (uint8)(DEM_J1939_FLASHLAMP_RSL_NO_FLASH | DEM_J1939_FLASHLAMP_AWL_NO_FLASH | DEM_J1939_FLASHLAMP_PL_NO_FLASH | (FlashLampStatus << 6u));
    (FilterResult->LampStatus).FlashLampStatus =                                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      (FilterResult->LampStatus).FlashLampStatus & lTempFlashLampStatus;
  }
  else
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    if (IndicatorId == Dem_Cfg_GlobalRslIndicator())
    {
      lTempLampStatus = (uint8)(DEM_J1939_LAMP_MIL_NA | DEM_J1939_LAMP_AWL_NA | DEM_J1939_LAMP_PL_NA | (LampStatus << 4u));
      (FilterResult->LampStatus).LampStatus =                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        (FilterResult->LampStatus).LampStatus & lTempLampStatus;

      lTempFlashLampStatus = (uint8)(DEM_J1939_FLASHLAMP_MIL_NO_FLASH | DEM_J1939_FLASHLAMP_AWL_NO_FLASH | DEM_J1939_FLASHLAMP_PL_NO_FLASH | (FlashLampStatus << 4u));
      (FilterResult->LampStatus).FlashLampStatus =                                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        (FilterResult->LampStatus).FlashLampStatus & lTempFlashLampStatus;
    }
    else if (IndicatorId == Dem_Cfg_GlobalAwlIndicator())
    {
      lTempLampStatus = (uint8)(DEM_J1939_LAMP_MIL_NA | DEM_J1939_LAMP_RSL_NA | DEM_J1939_LAMP_PL_NA | (LampStatus << 2u));
      (FilterResult->LampStatus).LampStatus =                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        (FilterResult->LampStatus).LampStatus & lTempLampStatus;

      lTempFlashLampStatus = (uint8)(DEM_J1939_FLASHLAMP_MIL_NO_FLASH | DEM_J1939_FLASHLAMP_RSL_NO_FLASH | DEM_J1939_FLASHLAMP_PL_NO_FLASH | (FlashLampStatus << 2u));
      (FilterResult->LampStatus).FlashLampStatus =                                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        (FilterResult->LampStatus).FlashLampStatus & lTempFlashLampStatus;
    }
    else if (IndicatorId == Dem_Cfg_GlobalPlIndicator())
    {
      lTempLampStatus = (uint8)(DEM_J1939_LAMP_MIL_NA | DEM_J1939_LAMP_RSL_NA | DEM_J1939_LAMP_AWL_NA | LampStatus);
      (FilterResult->LampStatus).LampStatus =                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        (FilterResult->LampStatus).LampStatus & lTempLampStatus;

      lTempFlashLampStatus = (uint8)(DEM_J1939_FLASHLAMP_MIL_NO_FLASH | DEM_J1939_FLASHLAMP_RSL_NO_FLASH | DEM_J1939_FLASHLAMP_AWL_NO_FLASH | FlashLampStatus);
      (FilterResult->LampStatus).FlashLampStatus =                                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        (FilterResult->LampStatus).FlashLampStatus & lTempFlashLampStatus;

    }
    else
# endif
    {
      Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);
    }
}
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_Indicator_Public
 * \{
 */

#if (DEM_FEATURE_NEED_REPORTED_MIL_STATE == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_TestMilReportedActive
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Indicator_TestMilReportedActive(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  boolean lReturnValue;
  uint8 lMilState;

  lReturnValue = FALSE;
  if(Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    lMilState = Dem_Indicator_J1939GlobalIndicatorState(Dem_Cfg_GlobalMilIndicator());
#else
    /* there is only one node in Dem_Cfg_GlobalIndicatorState */
    lMilState = Dem_Indicator_GetGlobalIndicatorState(Dem_Cfg_GlobalMilIndicator(), 0);
# endif

# if (DEM_CFG_REPORT_BLINKING_MIL_AS_ACTIVE == STD_ON)
    if ((lMilState != DEM_INDICATOR_OFF))
#else
    if ((lMilState == DEM_INDICATOR_CONTINUOUS) || (lMilState == DEM_INDICATOR_BLINK_CONT))
# endif
    {
      lReturnValue = TRUE;
    }
  }
  return lReturnValue;
}
#endif

#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_UpdatePIDsMilEnabled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdatePIDsMilEnabled(
  void
  )
{
  /* The MIL Indicator state has changed from FALSE to TRUE, the current Odometer value shall be fetched */
# if (DEM_CFG_SUPPORT_PID21 == STD_ON)
/* >>>> -------------------------------- Enter Critical Section: NonAtomic32bit */
  Dem_EnterCritical_NonAtomic32bit();

  Dem_Mem_SetOdometerMilOn(DEM_MEM_SET_ODOMETER_INVALID(0u));
  Dem_LeaveCritical_NonAtomic32bit();
/* <<<< -------------------------------- Leave Critical Section: NonAtomic32bit */
# endif
# if (DEM_CFG_SUPPORT_PID4D == STD_ON)
  Dem_Mem_SetEngineTimeMilOn(0);
# endif
}
#endif /* (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON) */

/* ****************************************************************************
 % Dem_Indicator_UserIndicatorEnable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UserIndicatorEnable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON)
  Dem_Cfg_EventNormalIndicatorIterType lIndicatorIter;

  for (Dem_Cfg_EventNormalIndicatorIterInit(EventId, &lIndicatorIter);                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_EventNormalIndicatorIterExists(&lIndicatorIter) == TRUE;                                                             /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_EventNormalIndicatorIterNext(&lIndicatorIter))                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_NormalIndicatorIndexType lIndicatorIndex;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    Dem_Cfg_EventJ1939NodeIterType lNodeIter;
# endif
    lIndicatorIndex = Dem_Cfg_EventNormalIndicatorIterGet(&lIndicatorIter);                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */

# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    for (Dem_Cfg_EventJ1939NodeIterInit(EventId, &lNodeIter);                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterNext(&lNodeIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
# endif
    {
      /* Increment the (node specific) indicator counter for continuous or blinking, according to configuration */
      uint8 lNmNodeIndex;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
      lNmNodeIndex = Dem_Cfg_EventJ1939NodeIterGet(&lNodeIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
# else
      lNmNodeIndex = 0u;
# endif
      if ((DEM_INDICATOR_CONTINUOUS & Dem_Cfg_IndicatorBehavior(lIndicatorIndex)) != 0u)
      {
        Dem_Indicator_SetEventCountContinuous(Dem_Cfg_IndicatorId(lIndicatorIndex), lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountContinuous(Dem_Cfg_IndicatorId(lIndicatorIndex), lNmNodeIndex) + 1u));
      }
      if ((DEM_INDICATOR_BLINKING & Dem_Cfg_IndicatorBehavior(lIndicatorIndex)) != 0u)
      {
        Dem_Indicator_SetEventCountBlinking(Dem_Cfg_IndicatorId(lIndicatorIndex), lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountBlinking(Dem_Cfg_IndicatorId(lIndicatorIndex), lNmNodeIndex) + 1u));
      }
    }
  }
#endif /* (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON) */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Indicator_SpecialIndicatorEnable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SpecialIndicatorEnable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
  uint8 lSpecialIndicatorId;
  Dem_Cfg_EventSpecialIndicatorIterType lSpecialIndicatorIter;
  for (Dem_Cfg_EventSpecialIndicatorIterInit(EventId, &lSpecialIndicatorIter);                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_EventSpecialIndicatorIterExists(&lSpecialIndicatorIter) == TRUE;                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */ /* PRQA S 2994 */ /* MD_DEM_2994 */
    Dem_Cfg_EventSpecialIndicatorIterNext(&lSpecialIndicatorIter))                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    Dem_Cfg_EventJ1939NodeIterType lNodeIter;

    for (Dem_Cfg_EventJ1939NodeIterInit(EventId, &lNodeIter);                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterNext(&lNodeIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
# endif
    {
      uint8 lNmNodeIndex;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
      lNmNodeIndex = Dem_Cfg_EventJ1939NodeIterGet(&lNodeIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
# else
      lNmNodeIndex = 0u;
# endif
      lSpecialIndicatorId = Dem_Cfg_EventSpecialIndicatorIterGetId(&lSpecialIndicatorIter);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      switch (Dem_Cfg_GetSpecialIndicatorBehavior(&lSpecialIndicatorIter))                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
      case DEM_INDICATOR_CONTINUOUS:
        Dem_Indicator_SetEventCountContinuous(lSpecialIndicatorId, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountContinuous(lSpecialIndicatorId, lNmNodeIndex) + 1u));
        break;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
      case DEM_INDICATOR_FAST_FLASH:
        Dem_Indicator_SetEventCountFastFlash(lSpecialIndicatorId, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountFastFlash(lSpecialIndicatorId, lNmNodeIndex) + 1u));
        break;
      case DEM_INDICATOR_SLOW_FLASH:
        Dem_Indicator_SetEventCountSlowFlash(lSpecialIndicatorId, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountSlowFlash(lSpecialIndicatorId, lNmNodeIndex) + 1u));
        break;
# endif /* (DEM_CFG_SUPPORT_J1939 == STD_ON) */
# if (DEM_CFG_SUPPORT_J1939 != STD_ON)
      case DEM_INDICATOR_BLINKING:
        Dem_Indicator_SetEventCountBlinking(lSpecialIndicatorId, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountBlinking(lSpecialIndicatorId, lNmNodeIndex) + 1u));
        break;
      case DEM_INDICATOR_BLINK_CONT:
        Dem_Indicator_SetEventCountContinuous(lSpecialIndicatorId, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountContinuous(lSpecialIndicatorId, lNmNodeIndex) + 1u));
        Dem_Indicator_SetEventCountBlinking(lSpecialIndicatorId, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountBlinking(lSpecialIndicatorId, lNmNodeIndex) + 1u));
        break;
# endif
      default:
        Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_INCONSISTENT_STATE);
        break;
      }
    }
# if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
    if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
    {
      if (lSpecialIndicatorId == Dem_Cfg_GlobalMilIndicator())
      {
        uint8 lWwhObdDtcClass;
        lWwhObdDtcClass = Dem_Util_SeverityWwhObdDtcClass(Dem_Cfg_EventSeverity(EventId));
        Dem_Indicator_SetDtcClassMILCount(lWwhObdDtcClass, Dem_Indicator_GetDtcClassMILCount(lWwhObdDtcClass) + 1u);
      }
    }
# endif
  }
#endif
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Indicator_UserIndicatorDisable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UserIndicatorDisable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON)
  Dem_Cfg_EventNormalIndicatorIterType lIndicatorIter;

  for (Dem_Cfg_EventNormalIndicatorIterInit(EventId, &lIndicatorIter);                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_EventNormalIndicatorIterExists(&lIndicatorIter) == TRUE;                                                             /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_EventNormalIndicatorIterNext(&lIndicatorIter))                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_NormalIndicatorIndexType lIndicatorIndex;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    Dem_Cfg_EventJ1939NodeIterType lNodeIter;
# endif

    lIndicatorIndex = Dem_Cfg_EventNormalIndicatorIterGet(&lIndicatorIter);                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
    DEM_IGNORE_UNUSED_VARIABLE(lIndicatorIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */

# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    /* Process all nodes linked to the event */
    for (Dem_Cfg_EventJ1939NodeIterInit(EventId, &lNodeIter);                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterNext(&lNodeIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
# endif
    {
      uint8 lNmNodeIndex;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
      lNmNodeIndex = Dem_Cfg_EventJ1939NodeIterGet(&lNodeIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
# else
      lNmNodeIndex = 0u;
# endif
      if ((Dem_Cfg_IndicatorBehavior(lIndicatorIndex) & DEM_INDICATOR_CONTINUOUS) != 0u)
      {
        Dem_Indicator_SetEventCountContinuous(Dem_Cfg_IndicatorId(lIndicatorIndex), lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountContinuous(Dem_Cfg_IndicatorId(lIndicatorIndex), lNmNodeIndex) - 1u));
      }
      if ((Dem_Cfg_IndicatorBehavior(lIndicatorIndex) & DEM_INDICATOR_BLINKING) != 0u)
      {
        Dem_Indicator_SetEventCountBlinking(Dem_Cfg_IndicatorId(lIndicatorIndex), lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountBlinking(Dem_Cfg_IndicatorId(lIndicatorIndex), lNmNodeIndex) - 1u));
      }
    }
  }
#endif /* DEM_CFG_SUPPORT_USER_INDICATORS */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Indicator_SpecialIndicatorDisable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SpecialIndicatorDisable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{

#if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
  uint8 lSpecialIndicatorId;
  Dem_Cfg_EventSpecialIndicatorIterType lSpecialIndicatorIter;                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */

  for (Dem_Cfg_EventSpecialIndicatorIterInit(EventId, &lSpecialIndicatorIter);                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_EventSpecialIndicatorIterExists(&lSpecialIndicatorIter) == TRUE;                                                     /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_EventSpecialIndicatorIterNext(&lSpecialIndicatorIter))                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    Dem_Cfg_EventJ1939NodeIterType lNodeIter;

    for (Dem_Cfg_EventJ1939NodeIterInit(EventId, &lNodeIter);                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterNext(&lNodeIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
# endif
    {
      uint8 lNmNodeIndex;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
      lNmNodeIndex = Dem_Cfg_EventJ1939NodeIterGet(&lNodeIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
# else
      lNmNodeIndex = 0u;
# endif
      lSpecialIndicatorId = Dem_Cfg_EventSpecialIndicatorIterGetId(&lSpecialIndicatorIter);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      switch (Dem_Cfg_GetSpecialIndicatorBehavior(&lSpecialIndicatorIter))                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
      case DEM_INDICATOR_CONTINUOUS:
        Dem_Indicator_SetEventCountContinuous(lSpecialIndicatorId, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountContinuous(lSpecialIndicatorId, lNmNodeIndex) - 1u));
        break;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
      case DEM_INDICATOR_FAST_FLASH:
        Dem_Indicator_SetEventCountFastFlash(lSpecialIndicatorId, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountFastFlash(lSpecialIndicatorId, lNmNodeIndex) - 1u));
        break;
      case DEM_INDICATOR_SLOW_FLASH:
        Dem_Indicator_SetEventCountSlowFlash(lSpecialIndicatorId, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountSlowFlash(lSpecialIndicatorId, lNmNodeIndex) - 1u));
        break;
# endif /* (DEM_CFG_SUPPORT_J1939 == STD_ON) */
# if (DEM_CFG_SUPPORT_J1939 != STD_ON)
      case DEM_INDICATOR_BLINKING:
        Dem_Indicator_SetEventCountBlinking(lSpecialIndicatorId, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountBlinking(lSpecialIndicatorId, lNmNodeIndex) - 1u));
        break;
      case DEM_INDICATOR_BLINK_CONT:
        Dem_Indicator_SetEventCountContinuous(lSpecialIndicatorId, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountContinuous(lSpecialIndicatorId, lNmNodeIndex) - 1u));
        Dem_Indicator_SetEventCountBlinking(lSpecialIndicatorId, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountBlinking(lSpecialIndicatorId, lNmNodeIndex) - 1u));
        break;
# endif
      default:
        Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_INCONSISTENT_STATE);
        break;
      }
    }
# if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
    if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
    {
      if (lSpecialIndicatorId == Dem_Cfg_GlobalMilIndicator())
      {
        uint8 lWwhObdDtcClass;
        lWwhObdDtcClass = Dem_Util_SeverityWwhObdDtcClass(Dem_Cfg_EventSeverity(EventId));
        Dem_Indicator_SetDtcClassMILCount(lWwhObdDtcClass, Dem_Indicator_GetDtcClassMILCount(lWwhObdDtcClass) - 1u);
      }
    }
# endif
  }
#endif /* (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON) */
  /* EventId might not be used depending on configuration */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}                                                                                                                                /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */


/* ****************************************************************************
 % Dem_Indicator_IndicatorDisable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_IndicatorDisable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
)
{
  uint8 lSpecialIndicatorId;
  Dem_Cfg_EventSpecialIndicatorIterType lSpecialIndicatorIter;
# if (DEM_CFG_SUPPORT_PID21 == STD_ON)
  boolean lOldMilIsActive;
  boolean UpdateGlobalMilState;
# endif

  Dem_Indicator_UserIndicatorDisable(EventId);
  Dem_Indicator_UpdateGlobalUserIndicatorForEvent(EventId);
  Dem_Indicator_SpecialIndicatorDisable(EventId);

# if (DEM_CFG_SUPPORT_PID21 == STD_ON)
  UpdateGlobalMilState = FALSE;
  lOldMilIsActive = Dem_Indicator_TestMilReportedActive();
# endif

  for (Dem_Cfg_EventSpecialIndicatorIterInit(EventId, &lSpecialIndicatorIter);                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_EventSpecialIndicatorIterExists(&lSpecialIndicatorIter) == TRUE;                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */ /* PRQA S 2994 */ /* MD_DEM_2994 */
    Dem_Cfg_EventSpecialIndicatorIterNext(&lSpecialIndicatorIter))                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    lSpecialIndicatorId = Dem_Cfg_EventSpecialIndicatorIterGetId(&lSpecialIndicatorIter);                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
    /* Special indicator was modified, recalculate new state */
    Dem_Indicator_UpdateGlobalSpecialIndicatorStates(lSpecialIndicatorId);
# if (DEM_CFG_SUPPORT_PID21 == STD_ON)
    if (lSpecialIndicatorId == Dem_Cfg_GlobalMilIndicator())
    {
      UpdateGlobalMilState = TRUE;
    }
# endif 
  }
# if (DEM_CFG_SUPPORT_PID21 == STD_ON)
  if (UpdateGlobalMilState == TRUE)
  {
    if ((lOldMilIsActive == TRUE)
      && (Dem_Indicator_TestMilReportedActive() == FALSE))                                                                       /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
    { /* MIL indicator has changed to OFF */
      Dem_Indicator_GlobalMilStateDisable();
    }
  }
# endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Indicator_IndicatorEnable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_IndicatorEnable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
)
{
  Dem_Indicator_UserIndicatorEnable(EventId);
  Dem_Indicator_UpdateGlobalUserIndicatorForEvent(EventId);
  Dem_Indicator_SpecialIndicatorEnable(EventId);

  {
    uint8 lSpecialIndicatorId;
    Dem_Cfg_EventSpecialIndicatorIterType lSpecialIndicatorIter;                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */

# if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
    boolean lOldMilIsActive;
    boolean UpdateGlobalMilState;
    UpdateGlobalMilState = FALSE;
    lOldMilIsActive = Dem_Indicator_TestMilReportedActive();
# endif
    for (Dem_Cfg_EventSpecialIndicatorIterInit(EventId, &lSpecialIndicatorIter);                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_EventSpecialIndicatorIterExists(&lSpecialIndicatorIter) == TRUE;                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */ /* PRQA S 2994 */ /* MD_DEM_2994 */
      Dem_Cfg_EventSpecialIndicatorIterNext(&lSpecialIndicatorIter))                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      lSpecialIndicatorId = Dem_Cfg_EventSpecialIndicatorIterGetId(&lSpecialIndicatorIter);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      /* Special indicator was modified, recalculate new state */
      Dem_Indicator_UpdateGlobalSpecialIndicatorStates(lSpecialIndicatorId);
# if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
      if (lSpecialIndicatorId == Dem_Cfg_GlobalMilIndicator())
      {
        UpdateGlobalMilState = TRUE;
      }
#endif 
    }
#  if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
    if (UpdateGlobalMilState == TRUE)
    {
      if ((lOldMilIsActive == FALSE)
        && (Dem_Indicator_TestMilReportedActive() == TRUE))                                                                      /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
      { /* MIL indicator has changed to ON */
        Dem_Indicator_UpdatePIDsMilEnabled();
      }
    }
#  endif
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Indicator_UpdateSpecialIndicators
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdateSpecialIndicators(
  void
  )
{
#if (DEM_CFG_SUPPORT_MIL == STD_ON)
  if (Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    Dem_Indicator_UpdateGlobalSpecialIndicatorStates(Dem_Cfg_GlobalMilIndicator());
  }
#endif
# if (DEM_CFG_SUPPORT_RSL == STD_ON)
  Dem_Indicator_UpdateGlobalSpecialIndicatorStates(Dem_Cfg_GlobalRslIndicator());
# endif
# if (DEM_CFG_SUPPORT_AWL == STD_ON)
  Dem_Indicator_UpdateGlobalSpecialIndicatorStates(Dem_Cfg_GlobalAwlIndicator());
# endif
# if (DEM_CFG_SUPPORT_PL == STD_ON)
  Dem_Indicator_UpdateGlobalSpecialIndicatorStates(Dem_Cfg_GlobalPlIndicator());
# endif
}                                                                                                                                /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Indicator_UpdateUserIndicators
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdateUserIndicators(
  void
  )
{
  uint8 lUserIndicatorId;

  /*configuration of indicator ids:
    0 <= special indicator id < user indicator id < number of all indicators*/
  lUserIndicatorId = Dem_Cfg_SpecialIndicatorCount();

  for (; lUserIndicatorId < Dem_Cfg_GlobalIndicatorCount(); lUserIndicatorId++)                                                  /* PRQA S 2994 */ /* MD_DEM_2994 */
  {
    Dem_Indicator_UpdateGlobalUserIndicatorStates(lUserIndicatorId);
  }
}


/* ****************************************************************************
 % Dem_Indicator_GetIndicatorStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_IndicatorStatusType, DEM_CODE)
Dem_Indicator_GetIndicatorStatus(
  CONST(uint8, AUTOMATIC)  IndicatorId
  )
{
  Dem_IndicatorStatusType lIndicatorStatus;
#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
  lIndicatorStatus = Dem_Indicator_J1939GlobalIndicatorState(IndicatorId);
#else
# if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  if ( (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
    && (Dem_Cfg_GlobalMilIndicator() == IndicatorId) )
  {
    lIndicatorStatus = Dem_Indicator_GlobalIndicatorActivationMode();
  }
  else
# endif
  {
    lIndicatorStatus = Dem_Indicator_GetGlobalIndicatorState(IndicatorId, 0);
  }
#endif
  return lIndicatorStatus;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */


/* ****************************************************************************
 % Dem_Indicator_InitWwhObdStatistics
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_InitWwhObdStatistics(
  void
  )
{
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  if (Dem_Cfg_IsWwhObdSupportedInVariant() == TRUE)
  {
    uint8 lDtcClassIndex;

    lDtcClassIndex = DEM_ESM_WWHOBD_NUMBER_DTCCLASS;

    while (lDtcClassIndex != 0u)
    {
      --lDtcClassIndex;

      Dem_Indicator_SetQualifiedActiveEventCount(lDtcClassIndex, 0);
      Dem_Indicator_SetDtcClassMILCount(lDtcClassIndex, 0);
    }
  }
#endif
}

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_GlobalIndicatorActivationMode
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_IndicatorStatusType, DEM_CODE)
Dem_Indicator_GlobalIndicatorActivationMode(
  void
  )
{
  Dem_IndicatorStatusType lReturnValue;

  /* calculate the current activation mode */
  if ( (Dem_Indicator_GetQualifiedActiveEventCount(DEM_ESM_WWHOBD_DTCCLASS_A) != 0u)
    || (DEM_DATA_B1COUNTER_200H <= Dem_Mem_GetB1Counter()) )
  { /* Class A event currently active or B1 counter exceeds threshold */
    lReturnValue = DEM_INDICATOR_CONTINUOUS;
  }
  else if ( (Dem_Indicator_GetDtcClassMILCount(DEM_ESM_WWHOBD_DTCCLASS_A) != 0u) 
         || (Dem_Indicator_GetDtcClassMILCount(DEM_ESM_WWHOBD_DTCCLASS_B1) != 0u)                                                                                                  
         || (Dem_Indicator_GetDtcClassMILCount(DEM_ESM_WWHOBD_DTCCLASS_B2) != 0u) )                                               
  {
    lReturnValue = DEM_INDICATOR_SHORT;
  }
  else if (Dem_Indicator_GetDtcClassMILCount(DEM_ESM_WWHOBD_DTCCLASS_C) != 0u)
  {
    lReturnValue = DEM_INDICATOR_ON_DEMAND;
  }
  else /* DEM_ESM_WWHOBD_DTCCLASS_NO */
  {
    lReturnValue = DEM_INDICATOR_OFF;
  }
  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_Indicator_UpdateGlobalSpecialIndicatorStates
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdateGlobalSpecialIndicatorStates(
  CONST(uint8, AUTOMATIC)  IndicatorId
  )
{
#if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
  uint8 lNmNodeIndex;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
  lNmNodeIndex = Dem_Cfg_GlobalJ1939NodeCount();

  while (lNmNodeIndex != 0u)
# else
  lNmNodeIndex = 0u;
# endif
  {
    Dem_IndicatorStatusType lIndicatorState;

# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    --lNmNodeIndex;
# endif
    lIndicatorState = DEM_INDICATOR_OFF;

    if (Dem_Indicator_GetEventCountContinuous(IndicatorId, lNmNodeIndex) > 0u)
    {
      lIndicatorState = DEM_INDICATOR_CONTINUOUS;
    }
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    else
    if (Dem_Indicator_GetEventCountFastFlash(IndicatorId, lNmNodeIndex) > 0u)
    {
      lIndicatorState = DEM_INDICATOR_FAST_FLASH;
    }
    else
    if (Dem_Indicator_GetEventCountSlowFlash(IndicatorId, lNmNodeIndex) > 0u)
    {
      lIndicatorState = DEM_INDICATOR_SLOW_FLASH;
    }
# endif
    else
    {
      /* MISRA*/
    }

# if (DEM_CFG_SUPPORT_J1939 != STD_ON)
    if (Dem_Indicator_GetEventCountBlinking(IndicatorId, lNmNodeIndex) > 0u)
    {
      lIndicatorState |= DEM_INDICATOR_BLINKING;
    }
# endif
    Dem_Indicator_SetGlobalIndicatorState(IndicatorId, lNmNodeIndex, lIndicatorState);
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Indicator_UpdateGlobalUserIndicatorForEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdateGlobalUserIndicatorForEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON)
  Dem_Cfg_EventNormalIndicatorIterType lIndicatorIter;

  for (Dem_Cfg_EventNormalIndicatorIterInit(EventId, &lIndicatorIter);                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_EventNormalIndicatorIterExists(&lIndicatorIter) == TRUE;                                                             /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_EventNormalIndicatorIterNext(&lIndicatorIter))                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_NormalIndicatorIndexType lIndicatorIndex;
    uint8 lIndicatorId;

    lIndicatorIndex = Dem_Cfg_EventNormalIndicatorIterGet(&lIndicatorIter);                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lIndicatorId = Dem_Cfg_IndicatorId(lIndicatorIndex);

    Dem_Indicator_UpdateGlobalUserIndicatorStates(lIndicatorId);
  }
#endif
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}

/* ****************************************************************************
 % Dem_Indicator_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_Init(void)
{
  /* If indicators are configured, initialize all indicator state counters */
  uint8 lIndicatorId;
  for (lIndicatorId = 0u; lIndicatorId < Dem_Cfg_GlobalIndicatorCount(); ++lIndicatorId)                                         /* PRQA S 2994 */ /* MD_DEM_2994 */
  {
    uint8 lNmNodeIndex;
    for (lNmNodeIndex = 0u; lNmNodeIndex < Dem_Cfg_GlobalJ1939NodeCount(); ++lNmNodeIndex)
    {
      Dem_Indicator_SetEventCountContinuous(lIndicatorId, lNmNodeIndex, 0);
      Dem_Indicator_SetEventCountBlinking(lIndicatorId, lNmNodeIndex, 0);
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
      Dem_Indicator_SetEventCountFastFlash(lIndicatorId, lNmNodeIndex, 0);
      Dem_Indicator_SetEventCountSlowFlash(lIndicatorId, lNmNodeIndex, 0);
# endif
    }
  }
}

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_CalculateGlobalJ1939LampStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_J1939DcmLampStatusType, DEM_CODE)
Dem_Indicator_CalculateGlobalJ1939LampStatus(
  CONST(uint8, AUTOMATIC)  NodeId
  )
{
  Dem_J1939DcmLampStatusType lLampStatus;

# if (DEM_CFG_SUPPORT_MIL == STD_ON)
  uint8 lGlobalMilState;
# endif
# if (DEM_CFG_SUPPORT_RSL == STD_ON)
  uint8 lGlobalRslState;
# endif
# if (DEM_CFG_SUPPORT_AWL == STD_ON)
  uint8 lGlobalAwlState;
#endif
# if (DEM_CFG_SUPPORT_PL == STD_ON)
  uint8 lGlobalPlState;
# endif

# if (DEM_CFG_SUPPORT_MIL == STD_ON)
  if(Dem_Cfg_IsObdSupportedInVariant() == TRUE)
  {
    lGlobalMilState = Dem_Indicator_GetGlobalIndicatorState(Dem_Cfg_GlobalMilIndicator(), NodeId);
  }
  else
  {
    /* Mil is always reported OFF */
    lGlobalMilState = DEM_INDICATOR_OFF;
  }
# endif
# if (DEM_CFG_SUPPORT_RSL == STD_ON)
  lGlobalRslState = Dem_Indicator_GetGlobalIndicatorState(Dem_Cfg_GlobalRslIndicator(), NodeId);
# endif
# if (DEM_CFG_SUPPORT_AWL == STD_ON)
  lGlobalAwlState = Dem_Indicator_GetGlobalIndicatorState(Dem_Cfg_GlobalAwlIndicator(), NodeId);
#endif
# if (DEM_CFG_SUPPORT_PL == STD_ON)
  lGlobalPlState = Dem_Indicator_GetGlobalIndicatorState(Dem_Cfg_GlobalPlIndicator(), NodeId);
# endif

  /* calculate node related lamp status */
  lLampStatus.LampStatus = (uint8)(Dem_GetHiByte(Dem_Cfg_J1939NodeIndicatorReadiness(NodeId))
# if (DEM_CFG_SUPPORT_MIL == STD_ON)
    | (Dem_Indicator_J1939LampStatus(lGlobalMilState) << 6u)
# endif
# if (DEM_CFG_SUPPORT_RSL == STD_ON)
    | (Dem_Indicator_J1939LampStatus(lGlobalRslState) << 4u)
# endif
# if (DEM_CFG_SUPPORT_AWL == STD_ON)
    | (Dem_Indicator_J1939LampStatus(lGlobalAwlState) << 2u)
# endif
# if (DEM_CFG_SUPPORT_PL == STD_ON)
    | (Dem_Indicator_J1939LampStatus(lGlobalPlState))
# endif
    );

  /* calculate node related flash lamp status */
  lLampStatus.FlashLampStatus = (uint8)(Dem_GetLoByte(Dem_Cfg_J1939NodeIndicatorReadiness(NodeId))
# if (DEM_CFG_SUPPORT_MIL == STD_ON)
    | (Dem_Indicator_J1939FlashLampStatus(lGlobalMilState) << 6u)
# endif
# if (DEM_CFG_SUPPORT_RSL == STD_ON)
    | (Dem_Indicator_J1939FlashLampStatus(lGlobalRslState) << 4u)
# endif
# if (DEM_CFG_SUPPORT_AWL == STD_ON)
    | (Dem_Indicator_J1939FlashLampStatus(lGlobalAwlState) << 2u)
# endif
# if (DEM_CFG_SUPPORT_PL == STD_ON)
    | (Dem_Indicator_J1939FlashLampStatus(lGlobalPlState))
# endif
    );
  return lLampStatus;
}                                                                                                                                /* PRQA S 6050 */ /* MD_DEM_6050_CONFIGURATION */
#endif

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_CalculateEventJ1939LampStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Indicator_CalculateEventJ1939LampStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  NodeId,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
)
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_EventJ1939NodeIterType lNodeIter;
# if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
  uint8 lSpecialIndicatorId;
  Dem_Cfg_EventSpecialIndicatorIterType lSpecialIndicatorIter;
#endif

  lReturnValue = DEM_NO_SUCH_ELEMENT;

  for (Dem_Cfg_EventJ1939NodeIterInit(EventId, &lNodeIter);                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE;                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventJ1939NodeIterNext(&lNodeIter))                                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    if (Dem_Cfg_EventJ1939NodeIterGet(&lNodeIter) == NodeId)                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      break;
    }
  }
  if (Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE)                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    /* Match only events belonging to the requested node */
    lReturnValue = E_OK;

    /* Initialize Lamp status */
    (FilterResult->LampStatus).LampStatus =                                                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      (uint8)(DEM_J1939_LAMP_MIL_NA | DEM_J1939_LAMP_RSL_NA | DEM_J1939_LAMP_AWL_NA | DEM_J1939_LAMP_PL_NA);
    (FilterResult->LampStatus).FlashLampStatus =                                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      (uint8)(DEM_J1939_FLASHLAMP_MIL_NO_FLASH | DEM_J1939_FLASHLAMP_RSL_NO_FLASH | DEM_J1939_FLASHLAMP_AWL_NO_FLASH | DEM_J1939_FLASHLAMP_PL_NO_FLASH);

    /* Iterate over all special indicators for the event */
# if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
    for (Dem_Cfg_EventSpecialIndicatorIterInit(EventId, &lSpecialIndicatorIter);                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_EventSpecialIndicatorIterExists(&lSpecialIndicatorIter) == TRUE;                                                   /* PRQA S 2994 */ /* MD_DEM_2994 */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_EventSpecialIndicatorIterNext(&lSpecialIndicatorIter))                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      uint8 lEventStatus;
      uint8 lLampStatus;
      uint8 lFlashLampStatus;

      lEventStatus = Dem_DTC_GenerateExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));
      lSpecialIndicatorId = Dem_Cfg_EventSpecialIndicatorIterGetId(&lSpecialIndicatorIter);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      if (Dem_UDSStatus_Test_WIR(lEventStatus) == TRUE)
      {
        /* indicator requested/active */
        lLampStatus = Dem_Indicator_J1939LampStatus(Dem_Cfg_GetSpecialIndicatorBehavior(&lSpecialIndicatorIter));                /* SBSW_DEM_CALL_ITERATOR_POINTER */
        lFlashLampStatus = Dem_Indicator_J1939FlashLampStatus(Dem_Cfg_GetSpecialIndicatorBehavior(&lSpecialIndicatorIter));      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      }
      else
      {
        lLampStatus = DEM_J1939_LAMP_OFF;
        lFlashLampStatus = DEM_J1939_FLASHLAMP_NO_FLASH;
      }
      Dem_Indicator_CalculateEventJ1939LampStatusForIndicator(lSpecialIndicatorId, lLampStatus, lFlashLampStatus, FilterResult); /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
# endif /* (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON) */
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STPTH */

#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_INDICATOR_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Indicator_Implementation.h
 *********************************************************************************************************************/
