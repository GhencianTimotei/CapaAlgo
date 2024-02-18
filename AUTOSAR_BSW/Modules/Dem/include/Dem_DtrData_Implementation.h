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
/*! \addtogroup Dem_Dtr
 *  \{
 *  \file       Dem_DtrData_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) Implementation file
 *  \details    Implementation of DtrData subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DTRDATA_IMPLEMENTATION_H)
#define DEM_DTRDATA_IMPLEMENTATION_H

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
#include "Dem_DtrData_Interface.h"

/* Includes to access public functions belonging to other (top level)/ (logical)/- units to be used by this Unit */
/* ------------------------------------------------------------------------- */
#include "Dem_Infrastructure_Interface.h"
#include "Dem_Core_Interface.h"
#include "Dem_Satellite_Interface.h"
#include "Dem_MidLookup_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_DTRDATA_IMPLEMENTATION_FILENAME "Dem_DtrData_Implementation.h"

/*!
 * \defgroup  Dem_Dtr_Validity  Macro indicating an invalid DTR Id
 * Macro indicating an invalid DTR Id
 * \{
 */
#define DEM_DTR_INVALIDDTRID                          Dem_DtrData_GetGlobalDtrCount()  /*!< Invalid DTR Id */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Dtr_ConversionStatus  Macros encoding DTR conversion status values
 * Macros encoding DTR conversion status values
 * \{
 */
#define DEM_DTR_CONVERSION_OK                         (0x00U)  /*!< DTR conversion OK */
#define DEM_DTR_CONVERSION_UNDERFLOW                  (0x01U)  /*!< DTR conversion undeflow */
#define DEM_DTR_CONVERSION_OVERFLOW                   (0x02U)  /*!< DTR conversion overflow */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Dtr_TestValueProperties  Macros encoding test value properties
 * Macros encoding test value properties
 * \{
 */
#define DEM_DTR_TEST_VALUE_WITHIN_LIMITS              (0x00U)  /*!< test value within limits */
#define DEM_DTR_TEST_VALUE_VIOLATES_LOWER_LIMIT       (0x01U)  /*!< test value exceeds the upper limit */
#define DEM_DTR_TEST_VALUE_VIOLATES_UPPER_LIMIT       (0x02U)  /*!< test value is under the lower limit */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Dtr_Visibility  Macros encoding DTR visibility values
 * Macros encoding DTR visibility values
 * \{
 */
#define DEM_DTR_VISIBLE                               (0x00U)  /*!< DTR is visible */
#define DEM_DTR_INVISIBLE                             (0x01U)  /*!< DTR is invisible */
/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/*! Variable to indicate a DTR modification. Used to serialize NvM calls, */
DEM_LOCAL volatile VAR(boolean, DEM_VAR_NOINIT)  Dem_Dtr_DataChanged;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITION
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT PUBLIC PROPERTIES DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_Dtr_PublicProperties
 * \{
 */

/* ****************************************************************************
 % Dem_DtrData_GetGlobalDtrCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(DTRIdType, DEM_CODE)
Dem_DtrData_GetGlobalDtrCount(
  void
  )
{
  uint16 lReturnValue;
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  lReturnValue = Dem_Cfg_GetSizeOfDtrTable();
#else
  lReturnValue = 0u;
#endif
  return lReturnValue;
}

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
 * \defgroup Dem_Dtr_Private Private Methods
 * \{
 */


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_EventDtrIterExists
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
 *                Dem_DtrData_EventDtrIterGet() will return a valid element
 *                on this iterator
 * \return        FALSE
 *                Dem_DtrData_EventDtrIterGet() is undefined on this iterator
 *
 * \pre           IterPtr has been initialized
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DtrData_EventDtrIterExists(
  CONSTP2CONST(Dem_Cfg_EventDtrIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_EventDtrIterGet
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator
 *
 * \details       Get the element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Handle to Dtr Id descriptor table
 *
 * \pre           IterPtr has been initialized
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(DTRIdType, DEM_CODE)
Dem_DtrData_EventDtrIterGet(
  CONSTP2CONST(Dem_Cfg_EventDtrIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_EventDtrIterInit
 *****************************************************************************/
/*!
 * \brief         Init the iterator
 *
 * \details       Initializes the iterator to enumerate Dtr Ids
 *                configured for an event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_EventDtrIterInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(Dem_Cfg_EventDtrIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_EventDtrIterNext
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next element
 *
 * \details       Move the iterator to the next element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_EventDtrIterNext(
  CONSTP2VAR(Dem_Cfg_EventDtrIterType, AUTOMATIC, AUTOMATIC)  IterPtr
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_RoundFloatToInt
 *****************************************************************************/
/*!
 * \brief         Round a floating number to the nearest integer
 *
 * \details       Round a floating number to the nearest integer
 *
 * \param[in]     Value
 *                Float32 value
 *
 * \return        Rounded sint32 value
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint32, DEM_CODE)
Dem_DtrData_RoundFloatToInt(
  CONST(float32, AUTOMATIC)  Value
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_GetUpdateKind
 *****************************************************************************/
/*!
 * \brief         Get the Update Kind for the Dtr
 *
 * \details       Get the Update Kind for the Dtr
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr.
 *                The DtrId must be in range [0..Dem_DtrData_GetGlobalDtrCount()-1[.
 *
 * \return        Update Kind for the Dtr.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DtrData_GetUpdateKind(
  CONST(DTRIdType, AUTOMATIC) DtrId
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_GetDivisor
 *****************************************************************************/
/*!
 * \brief         Get the Divisor for the Dtr
 *
 * \details       Get the Divisor for the linear conversion of the Dtr data
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr.
 *                The DtrId must be in range [0..Dem_DtrData_GetGlobalDtrCount()-1[.
 *
 * \return        Divisor for the Dtr.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(float32, DEM_CODE)
Dem_DtrData_GetDivisor(
  CONST(DTRIdType, AUTOMATIC) DtrId
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_GetLinearFactor
 *****************************************************************************/
/*!
 * \brief         Get the Linear Factor for the Dtr
 *
 * \details       Get the Linear Factor for the linear conversion of the Dtr data
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr.
 *                The DtrId must be in range [0..Dem_DtrData_GetGlobalDtrCount()-1[.
 *
 * \return        Linear Factor for the Dtr.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(float32, DEM_CODE)
Dem_DtrData_GetLinearFactor(
  CONST(DTRIdType, AUTOMATIC) DtrId
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_GetOffset
 *****************************************************************************/
/*!
 * \brief         Get the Offset for the Dtr
 *
 * \details       Get the Offset for the linear conversion of the Dtr data
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr.
 *                The DtrId must be in range [0..Dem_DtrData_GetGlobalDtrCount()-1[.
 *
 * \return        Offset for the Dtr.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(float32, DEM_CODE)
Dem_DtrData_GetOffset(
  CONST(DTRIdType, AUTOMATIC) DtrId
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_GetStatus
 *****************************************************************************/
/*!
 * \brief         Get current status of Dtr
 *
 * \details       Get current status of Dtr
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr.
 *                The DtrId must be in range [0..Dem_DtrData_GetGlobalDtrCount()-1[.
 *
 * \return        The current status of Dtr
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DtrData_GetStatus(
  CONST(DTRIdType, AUTOMATIC) DtrId
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_SetStatus
 *****************************************************************************/
/*!
 * \brief         Set current status of Dtr
 *
 * \details       Set current status of Dtr
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr.
 *                The DtrId must be in range [0..Dem_DtrData_GetGlobalDtrCount()-1[.
 * \param[in]     Status
 *                New status of Dtr
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_SetStatus(
  CONST(DTRIdType, AUTOMATIC) DtrId,
  CONST(uint8, AUTOMATIC) Status
  );
#endif


/* ****************************************************************************
 * Dem_DtrData_TestWriteOnShutdown
 *****************************************************************************/
/*!
 * \brief         Read the WriteOnShutdown flag
 *
 * \details       Read the WriteOnShutdown flag
 *
 * \return        State of the bit
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DtrData_TestWriteOnShutdown(
  void
  );


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_SetWriteOnShutdown
 *****************************************************************************/
/*!
 * \brief         Set the WriteOnShutdown flag
 *
 * \details       Set the WriteOnShutdown flag
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_SetWriteOnShutdown(
  void
  );
#endif


/* ****************************************************************************
 * Dem_DtrData_ResetWriteOnShutdown
 *****************************************************************************/
/*!
 * \brief         Reset the WriteOnShutdown flag
 *
 * \details       Reset the WriteOnShutdown flag
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_ResetWriteOnShutdown(
  void
  );


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_SetTestValue
 *****************************************************************************/
/*!
 * \brief         Set the test value of the Dtr
 *
 * \details       Set the test value of the Dtr
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr
 *                The DtrId must be in range [0..Dem_DtrData_GetGlobalDtrCount()[.
 * \param[in]     Value
 *                New test value
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_SetTestValue(
  CONST(DTRIdType, AUTOMATIC)  DtrId,
  CONST(uint16, AUTOMATIC)  Value
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_SetLowerLimit
 *****************************************************************************/
/*!
 * \brief         Set the lower limit of the Dtr
 *
 * \details       Set the lower limit of the Dtr
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr
 *                The DtrId must be in range [0..Dem_DtrData_GetGlobalDtrCount()[.
 * \param[in]     Value
 *                New lower limit
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_SetLowerLimit(
  CONST(DTRIdType, AUTOMATIC)  DtrId,
  CONST(uint16, AUTOMATIC)  Value
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_SetUpperLimit
 *****************************************************************************/
/*!
 * \brief         Set the upper limit of the Dtr
 *
 * \details       Set the upper limit of the Dtr
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr
 *                The DtrId must be in range [0..Dem_DtrData_GetGlobalDtrCount()[.
 * \param[in]     Value
 *                New upper limit
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_SetUpperLimit(
  CONST(DTRIdType, AUTOMATIC)  DtrId,
  CONST(uint16, AUTOMATIC)  Value
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_IsTestResultInLimits
 *****************************************************************************/
/*!
 * \brief         Tests whether a test result is valid
 *
 * \details       Tests whether a test result is within the limits
 *
 * \param[in]     TestResult
 *                Test Result
 * \param[in]     LowerLimit
 *                Lower Limit
 * \param[in]     UpperLimit
 *                Upper Limit
 * \param[in]     Ctrlval
 *                Dtr Control Value
 *
 * \return        TRUE
 *                The Test result is valid
 * \return        FALSE
 *                The Test result is not valid
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DtrData_IsTestResultInLimits(
  CONST(sint32, AUTOMATIC)  TestResult,
  CONST(sint32, AUTOMATIC)  LowerLimit,
  CONST(sint32, AUTOMATIC)  UpperLimit,
  CONST(Dem_DTRControlType, AUTOMATIC)  Ctrlval
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_IsProcessable
 *****************************************************************************/
/*!
 * \brief         Tests whether a Dtr is processable
 *
 * \details       Tests whether a Dtr is processable
 *
 * \param[in]     DTRId
 *                Unique handle of the Dtr.
 * \param[in]     TestResult
 *                Test Result
 * \param[in]     LowerLimit
 *                Lower Limit
 * \param[in]     UpperLimit
 *                Upper Limit
 * \param[in]     Ctrlval
 *                Dtr Control Value (values DEM_DTR_CTL_INVISIBLE and
 *                                   DEM_DTR_CTL_RESET are invalid)
 *
 * \return        TRUE
 *                The Dtr shall be processed
 * \return        FALSE
 *                The Dtr shall not be processed
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DtrData_IsProcessable(
  CONST(DTRIdType, AUTOMATIC)  DTRId,
  CONST(sint32, AUTOMATIC)  TestResult,
  CONST(sint32, AUTOMATIC)  LowerLimit,
  CONST(sint32, AUTOMATIC)  UpperLimit,
  CONST(Dem_DTRControlType, AUTOMATIC)  Ctrlval
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_ConvertValue
 *****************************************************************************/
/*!
 * \brief         Converts the input value using the conversion formula and
 *                configured coefficients.
 *
 * \details       Converts the input value using the conversion formula and
 *                configured coefficients taking overflow and underflow into 
 *                consideration.
 *
 * \param[in]     DTRId
 *                Unique handle of the Dtr
 * \param[in]     InitialValue
 *                Initial value to be converted
 * \param[in]     GlobalLowerLimit
 *                Allowed lower limit after conversion as per legislation
 * \param[in]     GlobalUpperLimit
 *                Allowed upper limit limit after conversion as per legislation
 * \param[out]    ConvertedValue
 *                Converted value
 *
 * \return        DEM_DTR_CONVERSION_OK
 *                Initial value was converted correctly to sint32 value
 * \return        DEM_DTR_CONVERSION_UNDERFLOW
 *                Converted value underran the allowed lower limit and was 
 *                latched at the lower limit
 * \return        DEM_DTR_CONVERSION_OVERFLOW
 *                Converted value overran the allowed upper limit and was
 *                latched at the upper limit
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DtrData_ConvertValue(
  CONST(DTRIdType, AUTOMATIC) DTRId,
  CONST(sint32, AUTOMATIC) InitialValue,
  CONST(sint32, AUTOMATIC) GlobalLowerLimit,
  CONST(sint32, AUTOMATIC) GlobalUpperLimit,
  CONSTP2VAR(sint32, AUTOMATIC, AUTOMATIC) ConvertedValue
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_ShiftThresholds
 *****************************************************************************/
/*!
 * \brief         Shifts Thresholds if necessary
 *
 * \details       If thresholds are (not) violated prior to the conversion, they
 *                shall (not) be violated after the conversion. Therefore
 *                thresholds can be shifted by one if meaning has changed.
 *
 * \param[in]     TestValue
 *                Test Value
 * \param[in]     LimitViolation
 *                Indicates if test value was within thresholds or if lower or upper 
 *                limit was violated before the conversion
 * \param[in]     GlobalLowerLimit
 *                Allowed lower limit as per legislation based on UaSID
 * \param[in]     GlobalUpperLimit
 *                Allowed upper limit as per legislation based on UaSID
 * \param[in,out] LowerLimit
 *                Shifted Lower limit
 * \param[in,out] UpperLimit
 *                Shifted Upper limit
 *
 * \return        E_OK
 *                Lower and upper limits have been corrected
 * \return        E_NOT_OK
 *                Lower and upper limits would have been shifted by more than one
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DtrData_ShiftThresholds(
  CONST(sint32, AUTOMATIC) TestValue,
  CONST(uint8, AUTOMATIC) LimitViolation,
  CONST(sint32, AUTOMATIC) GlobalLowerLimit,
  CONST(sint32, AUTOMATIC) GlobalUpperLimit,
  CONSTP2VAR(sint32, AUTOMATIC, AUTOMATIC) LowerLimit,
  CONSTP2VAR(sint32, AUTOMATIC, AUTOMATIC) UpperLimit
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_ProcessDtrValues
 *****************************************************************************/
/*!
 * \brief         Processes the Dtr values
 *
 * \details       Processes the Dtr values
 *
 * \param[in]     DTRId
 *                Unique handle of the Dtr.
 * \param[in]     TestResult
 *                Test Result
 * \param[in]     LowerLimit
 *                Lower Limit
 * \param[in]     UpperLimit
 *                Upper Limit
 * \param[in]     Ctrlval
 *                Dtr Control Value (values DEM_DTR_CTL_INVISIBLE and
 *                                   DEM_DTR_CTL_RESET are invalid)
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_ProcessDtrValues(
  CONST(DTRIdType, AUTOMATIC)  DTRId,
  CONST(sint32, AUTOMATIC)  TestResult,
  CONST(sint32, AUTOMATIC)  LowerLimit,
  CONST(sint32, AUTOMATIC)  UpperLimit,
  CONST(Dem_DTRControlType, AUTOMATIC)  Ctrlval
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_GetRelatedEvent
 *****************************************************************************/
/*!
 * \brief         Get the event mapped to a Dtr.
 *
 * \details       Get the event mapped to a Dtr.
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr.
 *                The DtrId must be in range [0..Dem_DtrData_GetGlobalDtrCount()-1[.
 *
 * \return        Event Id of the configured event.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DtrData_GetRelatedEvent(
  CONST(DTRIdType, AUTOMATIC) DtrId
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_IsEventAvailable
 *****************************************************************************/
/*!
 * \brief         Tests whether the event assigned to the DTR is available
 *
 * \details       Tests whether the event assigned to the DTR is available by
 *                configuration and during runtime
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr.
 *
 * \return        TRUE
 *                No event assigned to DTR or assigned event is available
 *                FALSE
 *                DTR feature not supported or unavailable event assigned 
 *                to DTR
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DtrData_IsEventAvailable(
  CONST(DTRIdType, AUTOMATIC) DtrId
  );
#endif


#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 * Dem_DtrData_IsDTCSuppressed
 *****************************************************************************/
/*!
 * \brief         Tests whether the DTC of the event assigned to the Dtr is 
 *                suppressed
 *
 * \details       Tests whether the DTC of the event assigned to the Dtr is 
 *                suppressed
 *
 * \param[in]     DtrId
 *                Unique handle of the Dtr.
 *
 * \return        TRUE
 *                DTC feature not supported or DTC of event assigned to 
 *                the Dtr is suppressed
 *                FALSE
 *                No event assigned to DTR or DTC of assigned event 
 *                not suppressed
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DtrData_IsDTCSuppressed(
  CONST(DTRIdType, AUTOMATIC) DtrId
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_EventDtrIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DtrData_EventDtrIterExists(
  CONSTP2CONST(Dem_Cfg_EventDtrIterType, AUTOMATIC, AUTOMATIC) IterPtr
)
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_EventDtrIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(DTRIdType, DEM_CODE)
Dem_DtrData_EventDtrIterGet(
  CONSTP2CONST(Dem_Cfg_EventDtrIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  boolean lDTRsHaveEvent;
  DTRIdType lDTRId;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  /* Reassign macro to avoid compiler warnings */
  lDTRsHaveEvent = Dem_Cfg_HasDtrTableInd();
  if (lDTRsHaveEvent == TRUE)
  {
    lDTRId = Dem_Cfg_GetDtrTableInd(IterPtr->mIdx);
  }
  else
  {
    lDTRId = DEM_DTR_INVALIDDTRID;
  }

  return lDTRId;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_EventDtrIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_EventDtrIterInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(Dem_Cfg_EventDtrIterType, AUTOMATIC, AUTOMATIC) IterPtr                                                             /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  boolean lDTRsHaveEvent;
  /* Reassign macro to avoid compiler warnings */
  lDTRsHaveEvent = Dem_Cfg_HasDtrTableInd();
  if (lDTRsHaveEvent  == TRUE)
  {
    IterPtr->mIdx = Dem_Cfg_GetDtrTableIndStartIdxOfEventTable(EventId);                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    IterPtr->mEndIdx = Dem_Cfg_GetDtrTableIndEndIdxOfEventTable(EventId);                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  else
  {
    IterPtr->mIdx = 0u;                                                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    IterPtr->mEndIdx = 0u;                                                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_EventDtrIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_EventDtrIterNext(
  CONSTP2VAR(Dem_Cfg_EventDtrIterType, AUTOMATIC, AUTOMATIC) IterPtr                                                             /* PRQA S 3673 */ /* MD_DEM_8.13_fp */
  )
{
  IterPtr->mIdx += 1u;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_RoundFloatToInt
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(sint32, DEM_CODE)
Dem_DtrData_RoundFloatToInt(
  CONST(float32, AUTOMATIC)  Value
  )
{
  sint32 lConvertedValue;

  if (Value > 0.0f)
  {
    lConvertedValue = (sint32)(Value + 0.5f);                                                                                    /* PRQA S 4395 */ /* MD_DEM_10.8_DTRFloatToInteger */
  }
  else
  {
    lConvertedValue = (sint32)(Value - 0.5f);                                                                                    /* PRQA S 4395 */ /* MD_DEM_10.8_DTRFloatToInteger */
  }

  return  lConvertedValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_GetRelatedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DtrData_GetRelatedEvent(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  Dem_EventIdType lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = ((Dem_EventIdType)(Dem_Cfg_GetEventTableIdxOfDtrTable(DtrId)));
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_GetUpdateKind
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DtrData_GetUpdateKind(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  uint8 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = (uint8)(Dem_Cfg_GetUpdateKindOfDtrTable(DtrId));
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_GetDivisor
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(float32, DEM_CODE)
Dem_DtrData_GetDivisor(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  float32 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_Cfg_GetDivisorOfDtrTable(DtrId);
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_GetLinearFactor
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(float32, DEM_CODE)
Dem_DtrData_GetLinearFactor(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  float32 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_Cfg_GetLinearFactorOfDtrTable(DtrId);
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_GetOffset
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(float32, DEM_CODE)
Dem_DtrData_GetOffset(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  float32 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_Cfg_GetOffsetOfDtrTable(DtrId);
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_GetStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DtrData_GetStatus(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  uint8 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_Cfg_GetDtrStatus(DtrId);
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_SetStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_SetStatus(
  CONST(DTRIdType, AUTOMATIC) DtrId,
  CONST(uint8, AUTOMATIC) Status
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (DtrId >= Dem_Cfg_GetSizeOfDtrStatus())
  {
    Dem_Error_RunTimeCheckFailed(DEM_DTRDATA_IMPLEMENTATION_FILENAME, __LINE__);                                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_SetDtrStatus(DtrId, Status);                                                                                         /* SBSW_DEM_ARRAY_WRITE_DTRSTATUS */
  }
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_SetTestValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_SetTestValue(                                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(DTRIdType, AUTOMATIC)  DtrId,
  CONST(uint16, AUTOMATIC)  Value
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (DtrId >= DEM_CFG_MAX_NUMBER_CONFIGURABLE_DTRS)
  {
    Dem_Error_RunTimeCheckFailed(DEM_DTRDATA_IMPLEMENTATION_FILENAME, __LINE__);                                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_GetDtrData().TestValue[DtrId] = Value;                                                                               /* SBSW_DEM_ARRAY_WRITE_DTRDATA_TESTVALUE */
  }
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_SetLowerLimit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_SetLowerLimit(                                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(DTRIdType, AUTOMATIC)  DtrId,
  CONST(uint16, AUTOMATIC)  Value
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (DtrId >= DEM_CFG_MAX_NUMBER_CONFIGURABLE_DTRS)
  {
    Dem_Error_RunTimeCheckFailed(DEM_DTRDATA_IMPLEMENTATION_FILENAME, __LINE__);                                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_GetDtrData().LowLimValue[DtrId] = Value;                                                                             /* SBSW_DEM_ARRAY_WRITE_DTRDATA_LOWLIMVALUE */
  }
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_SetUpperLimit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_SetUpperLimit(                                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(DTRIdType, AUTOMATIC)  DtrId,
  CONST(uint16, AUTOMATIC)  Value
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (DtrId >= DEM_CFG_MAX_NUMBER_CONFIGURABLE_DTRS)
  {
    Dem_Error_RunTimeCheckFailed(DEM_DTRDATA_IMPLEMENTATION_FILENAME, __LINE__);                                                     /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_GetDtrData().UppLimValue[DtrId] = Value;                                                                             /* SBSW_DEM_ARRAY_WRITE_DTRDATA_UPPLIMVALUE */
  }
}
#endif

/* ****************************************************************************
 % Dem_DtrData_TestWriteOnShutdown
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DtrData_TestWriteOnShutdown(
  void
  )
{
  boolean lReturnValue;
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  lReturnValue = Dem_Dtr_DataChanged;
#else
  lReturnValue = FALSE;
#endif
  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_SetWriteOnShutdown
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_SetWriteOnShutdown(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  Dem_Dtr_DataChanged = TRUE;
  Dem_Scheduler_EnableTask(Dem_Scheduler_Task_Dtr);
}
#endif

/* ****************************************************************************
 % Dem_DtrData_ResetWriteOnShutdown
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_ResetWriteOnShutdown(
  void
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_Dtr_DataChanged = FALSE;
#endif
}

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_IsTestResultInLimits
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DtrData_IsTestResultInLimits(
  CONST(sint32, AUTOMATIC) TestResult,
  CONST(sint32, AUTOMATIC) LowerLimit,
  CONST(sint32, AUTOMATIC) UpperLimit,
  CONST(Dem_DTRControlType, AUTOMATIC) Ctrlval
  )
{
  boolean lTestResultInLimits;

  lTestResultInLimits = TRUE;

  if (TestResult < LowerLimit)
  {
    if (Ctrlval != DEM_DTR_CTL_NO_MIN)
    {
      lTestResultInLimits = FALSE;
    }
  }
  else if (TestResult > UpperLimit)
  {
    if (Ctrlval != DEM_DTR_CTL_NO_MAX)
    {
      lTestResultInLimits = FALSE;
    }
  }
  else
  {
    /* Misra */
  }

  return lTestResultInLimits;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_IsProcessable
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DtrData_IsProcessable(
  CONST(DTRIdType, AUTOMATIC) DTRId,
  CONST(sint32, AUTOMATIC) TestResult,
  CONST(sint32, AUTOMATIC) LowerLimit,
  CONST(sint32, AUTOMATIC) UpperLimit,
  CONST(Dem_DTRControlType, AUTOMATIC) Ctrlval
  )
{
  boolean lDtrProcessed;

  lDtrProcessed = FALSE;

  if (Dem_DtrData_GetUpdateKind(DTRId) == DEM_DTR_UPDATE_ALWAYS)
  {
    lDtrProcessed = TRUE;
  }
  else
  {
    Dem_EventIdType lEventId;
    Dem_DebouncingStateType lDebouncingState;

    lEventId = Dem_DtrData_GetRelatedEvent(DTRId);
    lDebouncingState = Dem_SatelliteSat_GetDebouncingState(Dem_Cfg_EventSatelliteId(lEventId), 
                                                            Dem_Cfg_EventSatelliteEventId(lEventId));

    /* event is tested and storage and enable conditions are fulfilled */
    if (Dem_DebouncingState_TestDtrUpdate(lDebouncingState) == TRUE)
    {
      /* event is tested failed */
      if (Dem_DebouncingState_TestFinallyDefective(lDebouncingState) == TRUE)
      {
        lDtrProcessed = TRUE;
      }
      /* event is tested passed */
      else
      {
        /* Test result doesn't violate the limits */
        if (Dem_DtrData_IsTestResultInLimits(TestResult, LowerLimit, UpperLimit, Ctrlval) == TRUE)
        {
          lDtrProcessed = TRUE;
        }
      }
    }
  }

  return lDtrProcessed;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_ConvertValue
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
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DtrData_ConvertValue(
  CONST(DTRIdType, AUTOMATIC) DTRId,
  CONST(sint32, AUTOMATIC) InitialValue,
  CONST(sint32, AUTOMATIC) GlobalLowerLimit,
  CONST(sint32, AUTOMATIC) GlobalUpperLimit,
  CONSTP2VAR(sint32, AUTOMATIC, AUTOMATIC) ConvertedValue
  )
{
  Std_ReturnType lReturnValue;
  float32 lDivisor, lLinFactor, lOffset, lConvertedValue;

  lDivisor = Dem_DtrData_GetDivisor(DTRId);
  lLinFactor = Dem_DtrData_GetLinearFactor(DTRId);
  lOffset = Dem_DtrData_GetOffset(DTRId);

  lConvertedValue = ((lLinFactor * (float32)InitialValue) + lOffset) / lDivisor;

  if ((sint32)lConvertedValue < GlobalLowerLimit)
  {
    *ConvertedValue = GlobalLowerLimit;                                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = DEM_DTR_CONVERSION_UNDERFLOW;
  }
  else if ((sint32)lConvertedValue > GlobalUpperLimit)
  {
    *ConvertedValue = GlobalUpperLimit;                                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = DEM_DTR_CONVERSION_OVERFLOW;
  }
  else
  {
    *ConvertedValue = Dem_DtrData_RoundFloatToInt(lConvertedValue);                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = DEM_DTR_CONVERSION_OK;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_ShiftThresholds
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
 */
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DtrData_ShiftThresholds(
  CONST(sint32, AUTOMATIC) TestValue,
  CONST(uint8, AUTOMATIC) LimitViolation,
  CONST(sint32, AUTOMATIC) GlobalLowerLimit,
  CONST(sint32, AUTOMATIC) GlobalUpperLimit,
  CONSTP2VAR(sint32, AUTOMATIC, AUTOMATIC) LowerLimit,
  CONSTP2VAR(sint32, AUTOMATIC, AUTOMATIC) UpperLimit
  )
{
  Std_ReturnType lReturnValue;
  sint32 lLowerLimit;
  sint32 lUpperLimit;

  lReturnValue = E_OK;
  lLowerLimit = *LowerLimit;
  lUpperLimit = *UpperLimit;

  switch (LimitViolation)
  {
  case DEM_DTR_TEST_VALUE_VIOLATES_LOWER_LIMIT:
    /* test value doesn't violate lower limit */
    if (TestValue >= lLowerLimit)
    {
      /* lower limit has to be shifted by more than one or lower limit is already at the global upper limit */
      if ((TestValue > lLowerLimit) || (lLowerLimit == GlobalUpperLimit))
      {
        lReturnValue = E_NOT_OK;
      }
      else
      {
        lLowerLimit++;
        if (lLowerLimit > lUpperLimit)
        {
          lUpperLimit++;
        }
      }
    }
    break;
  case DEM_DTR_TEST_VALUE_VIOLATES_UPPER_LIMIT:
    /* test value doesn't violate upper limit */
    if (TestValue <= lUpperLimit)
    {
      /* upper limit has to be shifted by more than one  or upper limit is already at the global lower limit */
      if ((TestValue < lUpperLimit) || (lUpperLimit == GlobalLowerLimit))
      {
        lReturnValue = E_NOT_OK;
      }
      else
      {
        lUpperLimit--;
        if (lLowerLimit > lUpperLimit)
        {
          (lLowerLimit)--;
        }
      }
    }
    break;
  case DEM_DTR_TEST_VALUE_WITHIN_LIMITS:
    /* test value violates lower limit */
    if (TestValue < lLowerLimit)
    {
      /* Test value violates lower limit by more than one. */
      if ((lLowerLimit - TestValue) > 1)
      {
        lReturnValue = E_NOT_OK;
      }
      else
      {
        /* from if: TestValue < lLowerLimit:
        => lLowerLimit > TestValue

        with max(TestValue) = GlobalLowerLimit
        => lLowerLimit > GlobalLowerLimit
        => Underflow may not occur.
        */
        lLowerLimit--;
      }
    }
    /* test value violates upper limit */
    else if (TestValue > lUpperLimit)
    {
      /* test value violates upper limit by more than one */
      if ((TestValue - lUpperLimit) > 1)
      {
        lReturnValue = E_NOT_OK;
      }
      else
      {
        /* from if(TestValue > lUpperLimit):
        => lUpperLimit < TestValue

        with max(TestValue) = GlobalUpperLimit
        => lUpperLimit < GlobalUpperLimit
        => Overflow may not occur.
        */
        lUpperLimit++;
      }
    }
    else
    {
      /* MISRA */
    }
    break;
  default:
    /* Misra */
    lReturnValue = E_NOT_OK;
    break;
  }

  *LowerLimit = lLowerLimit;                                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  *UpperLimit = lUpperLimit;                                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6060 */ /* MD_MSR_STCYC, MD_MSR_STPAR */
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_ProcessDtrValues
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_ProcessDtrValues(
  CONST(DTRIdType, AUTOMATIC) DTRId,
  CONST(sint32, AUTOMATIC) TestResult,
  CONST(sint32, AUTOMATIC) LowerLimit,
  CONST(sint32, AUTOMATIC) UpperLimit,
  CONST(Dem_DTRControlType, AUTOMATIC) Ctrlval
  )
{
  Std_ReturnType lDTRProcessingStatus;
  sint32 lConvLowerLimit;
  sint32 lConvUpperLimit;
  sint32 lConvTestResult;
  sint32 lGlobalLowerLimit;
  sint32 lGlobalUpperLimit;

  Dem_Det_ErrorRegisterDefine()
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  lDTRProcessingStatus = E_OK;
  lConvTestResult = 0x00;

  if (Dem_DtrData_GetUaSId(DTRId) < 0x80U)
  {
    lGlobalLowerLimit = 0;      /* 0x00000000 */
    lGlobalUpperLimit = 65535;  /* 0x0000FFFF */
  }
  else
  {
    lGlobalLowerLimit = -32768; /* 0xFFFF8000 */
    lGlobalUpperLimit = 32767;  /* 0x00007FFF */
  }

  /* Convert lower limit */
  if (Ctrlval == DEM_DTR_CTL_NO_MIN)
  {
    lConvLowerLimit = lGlobalLowerLimit;
  }
  else
  {
    if (Dem_DtrData_ConvertValue(DTRId, LowerLimit, lGlobalLowerLimit, lGlobalUpperLimit, &lConvLowerLimit) != DEM_DTR_CONVERSION_OK)/* SBSW_DEM_POINTER_FORWARD_STACK */
    {
      lDTRProcessingStatus = E_NOT_OK;
    }
  }

  /* Convert upper limit */
  if (Ctrlval == DEM_DTR_CTL_NO_MAX)
  {
    lConvUpperLimit = lGlobalUpperLimit;
  }
  else
  {
    if (Dem_DtrData_ConvertValue(DTRId, UpperLimit, lGlobalLowerLimit, lGlobalUpperLimit, &lConvUpperLimit) != DEM_DTR_CONVERSION_OK)/* SBSW_DEM_POINTER_FORWARD_STACK */
    {
      lDTRProcessingStatus = E_NOT_OK;
    }
  }
  

  /* Convert test result and if necessary shift limits */
  if (lDTRProcessingStatus == E_OK)
  {
    Std_ReturnType lGlobalLimitResult;

    /* Test the test result value against global limits */
    lGlobalLimitResult = Dem_DtrData_ConvertValue(DTRId, TestResult, lGlobalLowerLimit, lGlobalUpperLimit, &lConvTestResult);        /* SBSW_DEM_POINTER_FORWARD_STACK */

    switch (lGlobalLimitResult)
    {
    case DEM_DTR_CONVERSION_UNDERFLOW:
      if (Ctrlval != DEM_DTR_CTL_NO_MIN)
      {
        lDTRProcessingStatus = Dem_DtrData_ShiftThresholds(lConvTestResult,                                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
          DEM_DTR_TEST_VALUE_VIOLATES_LOWER_LIMIT,
          lGlobalLowerLimit,
          lGlobalUpperLimit,
          &lConvLowerLimit,
          &lConvUpperLimit);
      }
      break;

    case DEM_DTR_CONVERSION_OVERFLOW:
      if (Ctrlval != DEM_DTR_CTL_NO_MAX)
      {
        lDTRProcessingStatus = Dem_DtrData_ShiftThresholds(lConvTestResult,                                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
          DEM_DTR_TEST_VALUE_VIOLATES_UPPER_LIMIT,
          lGlobalLowerLimit,
          lGlobalUpperLimit,
          &lConvLowerLimit,
          &lConvUpperLimit);
      }
      break;

    case DEM_DTR_CONVERSION_OK:
      if ((TestResult < LowerLimit) && (Ctrlval != DEM_DTR_CTL_NO_MIN))
      {
        lDTRProcessingStatus = Dem_DtrData_ShiftThresholds(lConvTestResult,                                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
          DEM_DTR_TEST_VALUE_VIOLATES_LOWER_LIMIT,
          lGlobalLowerLimit,
          lGlobalUpperLimit,
          &lConvLowerLimit,
          &lConvUpperLimit);
      }
      else if ((TestResult > UpperLimit) && (Ctrlval != DEM_DTR_CTL_NO_MAX))
      {
        lDTRProcessingStatus = Dem_DtrData_ShiftThresholds(lConvTestResult,                                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
          DEM_DTR_TEST_VALUE_VIOLATES_UPPER_LIMIT,
          lGlobalLowerLimit,
          lGlobalUpperLimit,
          &lConvLowerLimit,
          &lConvUpperLimit);
      }
      else
      {
        lDTRProcessingStatus = Dem_DtrData_ShiftThresholds(lConvTestResult,                                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
          DEM_DTR_TEST_VALUE_WITHIN_LIMITS,
          lGlobalLowerLimit,
          lGlobalUpperLimit,
          &lConvLowerLimit,
          &lConvUpperLimit);
      }
      break;

    default:
      /* MISRA */
      lDTRProcessingStatus = E_NOT_OK;
      break;
    }
  }

  /* Setting DTR was successful */
  if (lDTRProcessingStatus == E_OK)
  {
    Dem_DtrData_SetDtrValues(DTRId, (uint16)lConvTestResult, (uint16)lConvLowerLimit, (uint16)lConvUpperLimit);                      /* PRQA S 2897 */ /* MD_DEM_2897 */
  }
  /* Global limits have been exceeded or at least one thresholds has to be shifted by more than one --> reset Dtr values */
  else
  {
# if (DEM_DEV_ERROR_DETECT == STD_ON)
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_CONFIG)
# endif
    Dem_DtrData_SetDtrValues(DTRId, 0u, 0u, 0u);
  }
  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETDTR_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif
}                                                                                                                                /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_IsEventAvailable
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
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DtrData_IsEventAvailable(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  boolean lEventAvailable;
  Dem_EventIdType lEventId;

  lEventAvailable = TRUE;
  lEventId = Dem_DtrData_GetRelatedEvent(DtrId);
  if (lEventId != DEM_EVENT_INVALID)
  {
    if ( (Dem_Cfg_EventAvailableByVariant(lEventId) == FALSE)
      || (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lEventId)) == TRUE) )                        
    {
      lEventAvailable = FALSE;
    }
  }
  return lEventAvailable;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_IsDTCSuppressed
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
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DtrData_IsDTCSuppressed(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  boolean lDTCSuppressed;
  Dem_EventIdType lEventId;

  lDTCSuppressed = FALSE;
  lEventId = Dem_DtrData_GetRelatedEvent(DtrId);
  if (lEventId != DEM_EVENT_INVALID)
  {
    if (Dem_DTC_TestDtcSuppression(lEventId) == TRUE)
    {
      lDTCSuppressed = TRUE;
    }
  }
  return lDTCSuppressed;
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
 * \addtogroup Dem_Dtr_Public
 * \{
 */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_SetDtrValues
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_SetDtrValues(
  CONST(DTRIdType, AUTOMATIC) DTRId,
  CONST(uint16, AUTOMATIC) TestValue,
  CONST(uint16, AUTOMATIC) LowerLimit,
  CONST(uint16, AUTOMATIC) UpperLimit
  )
{
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
  Dem_EnterCritical_DiagMonitor();

  Dem_DtrData_SetTestValue(DTRId, TestValue);
  Dem_DtrData_SetLowerLimit(DTRId, LowerLimit);
  Dem_DtrData_SetUpperLimit(DTRId, UpperLimit);

  Dem_LeaveCritical_DiagMonitor();
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

  Dem_DtrData_SetWriteOnShutdown();
}
#endif

/* ****************************************************************************
 % Dem_DtrData_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_Init(
  void
  )
{
  Dem_DtrData_ResetWriteOnShutdown();
}

/* ****************************************************************************
 % Dem_DtrData_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_PreInit(
  void
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_MemSet((Dem_DataPtrType)(&Dem_Cfg_GetDtrStatus(0)),                                                                        /* PRQA S 0310, 0312, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_11.8, MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_DTRSTATUS */
             DEM_DTR_VISIBLE,
             Dem_Cfg_GetSizeOfDtrStatus() * sizeof(Dem_Cfg_GetDtrStatus(0)));
#endif
}

/* ****************************************************************************
 % Dem_DtrData_MainFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_MainFunction(
  void
  )
{
  Dem_DtrData_ResetWriteOnShutdown();
  Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_DTR), 
                              DEM_NVM_BLOCKSTATE_DIRTY);
}

/* ****************************************************************************
 % Dem_DtrData_Shutdown
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_Shutdown(
  void
  )
{
  if (Dem_DtrData_TestWriteOnShutdown() == TRUE)
  {
    Dem_DtrData_ResetWriteOnShutdown();
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_DTR), 
                                DEM_NVM_BLOCKSTATE_DIRTY);
  }
}

/* ****************************************************************************
 % Dem_DtrData_IsValidHandle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DtrData_IsValidHandle(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  boolean lDtrValid;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
    
  lDtrValid = FALSE;
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  if (DtrId < Dem_DtrData_GetGlobalDtrCount())
  {
    if (Dem_DtrData_GetDivisor(DtrId) != 0.0f)                                                                                       /* PRQA S 3341 */ /* MD_DEM_13.3 */
    {
      lDtrValid = TRUE;
    }
  }
#endif
  return lDtrValid;
}

/* ****************************************************************************
 % Dem_DtrData_EventAvailabilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_EventAvailabilityChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_Cfg_EventDtrIterType lDtrIter;
  Dem_DtrData_EventDtrIterInit(EventId, &lDtrIter);                                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
  if (Dem_DtrData_EventDtrIterExists(&lDtrIter) == TRUE)                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_MidLookup_NotifyVisibilityChanged();
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_DTCSuppressionChanged
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
Dem_DtrData_DTCSuppressionChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);

  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_Cfg_CombinedGroupIterType lCombinedIter;

    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_EventIdType lSubEventId;
      Dem_Cfg_EventDtrIterType lDtrIter;
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_DtrData_EventDtrIterInit(lSubEventId, &lDtrIter);                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
      if (Dem_DtrData_EventDtrIterExists(&lDtrIter) == TRUE)                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        Dem_MidLookup_NotifyVisibilityChanged();
        /* if one event has been found, flag is already set */
        break;
      }
    }
  }
  else
  {
    Dem_Cfg_EventDtrIterType lDtrIter;
    Dem_DtrData_EventDtrIterInit(EventId, &lDtrIter);                                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
    if (Dem_DtrData_EventDtrIterExists(&lDtrIter) == TRUE)                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_MidLookup_NotifyVisibilityChanged();
    }
  }
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_DtrData_ResetDtrsOfEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_ResetDtrsOfEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_Cfg_EventDtrIterType lDtrIter;
  for (Dem_DtrData_EventDtrIterInit(EventId, &lDtrIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_DtrData_EventDtrIterExists(&lDtrIter) == TRUE;                                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */ /* PRQA S 2994 */ /* MD_DEM_2994 */
    Dem_DtrData_EventDtrIterNext(&lDtrIter))                                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    DTRIdType lDtrId;
    lDtrId = Dem_DtrData_EventDtrIterGet(&lDtrIter);                                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_DtrData_SetDtrValues(lDtrId, 0, 0, 0);
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_DtrData_ResetDtrsWithoutEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrData_ResetDtrsWithoutEvent(
  void
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  DTRIdType lDtrId;
  /* reset Dtr values of Dtrs not referencing an event */
  for (lDtrId = 0u; lDtrId < Dem_DtrData_GetGlobalDtrCount(); lDtrId++)
  {
    if (Dem_DtrData_GetRelatedEvent(lDtrId) == DEM_EVENT_INVALID)
    {
      Dem_DtrData_SetDtrValues(lDtrId, 0, 0, 0);
    }
  }
#endif
}

/* ****************************************************************************
 % Dem_DtrData_SetDtr
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
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DtrData_SetDtr(
  CONST(DTRIdType, AUTOMATIC) DTRId,                                                                                             /* PRQA S 1330 */ /* MD_DEM_8.3_rte */
  CONST(sint32, AUTOMATIC) TestResult,
  CONST(sint32, AUTOMATIC) LowerLimit,
  CONST(sint32, AUTOMATIC) UpperLimit,
  CONST(Dem_DTRControlType, AUTOMATIC) Ctrlval
  )
{
  Std_ReturnType lReturnValue;

  lReturnValue = E_NOT_OK;
#if (DEM_CFG_SUPPORT_DTR == STD_ON)

  if ( (Dem_DtrData_IsValidHandle(DTRId) == TRUE)
    && (Dem_DtrData_IsEventAvailable(DTRId) == TRUE) )                                                                               /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
  {
    switch (Ctrlval)
    {
    case DEM_DTR_CTL_INVISIBLE:
      /* Set state of Dtr to invisible. Dtr result and limits are ignored */
      if (Dem_DtrData_GetStatus(DTRId) == DEM_DTR_VISIBLE)
      {
        Dem_DtrData_SetStatus(DTRId, DEM_DTR_INVISIBLE);
        Dem_MidLookup_NotifyVisibilityChanged();
      }
      break;
    case DEM_DTR_CTL_RESET:
      /* Set state of Dtr to visible. Reset Dtr values */
      if (Dem_DtrData_GetStatus(DTRId) == DEM_DTR_INVISIBLE)
      {
        Dem_DtrData_SetStatus(DTRId, DEM_DTR_VISIBLE);
        Dem_MidLookup_NotifyVisibilityChanged();
      }
      /* reset Dtr values */
      Dem_DtrData_SetDtrValues(DTRId, 0, 0, 0);
      break;
    case DEM_DTR_CTL_NORMAL:
    case DEM_DTR_CTL_NO_MAX:
    case DEM_DTR_CTL_NO_MIN:
      /* Set state of Dtr to visible. Process Dtr values if Dtr result is valid */
      if (Dem_DtrData_GetStatus(DTRId) == DEM_DTR_INVISIBLE)
      {
        Dem_DtrData_SetStatus(DTRId, DEM_DTR_VISIBLE);
        Dem_MidLookup_NotifyVisibilityChanged();
      }
      /* Dtr result is valid --> process Dtr values */
      if (Dem_DtrData_IsProcessable(DTRId, TestResult, LowerLimit, UpperLimit, Ctrlval) == TRUE)
      {
        Dem_DtrData_ProcessDtrValues(DTRId, TestResult, LowerLimit, UpperLimit, Ctrlval);
      }
      break;
    default:                                                                                                                     /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      /* Do nothing */
      break;
    }
    lReturnValue = E_OK;
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTRId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(TestResult)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(LowerLimit)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(UpperLimit)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Ctrlval)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrData_TestDtrVisibility
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DtrData_TestDtrVisibility(
  CONST(DTRIdType, AUTOMATIC) DTRId
  )
{
  return (boolean)( (Dem_DtrData_GetStatus(DTRId) == DEM_DTR_VISIBLE)
                 && (Dem_DtrData_IsEventAvailable(DTRId) == TRUE)                                                                    /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
                 && (Dem_DtrData_IsDTCSuppressed(DTRId) == FALSE) );                                                                 /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
}
#endif

/* ****************************************************************************
 % Dem_DtrData_GetUaSId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DtrData_GetUaSId(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  uint8 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  lReturnValue = Dem_Cfg_GetUasidOfDtrTable(DtrId);
#else
  lReturnValue = 0u;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DtrData_GetTestValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_DtrData_GetTestValue(
  CONST(DTRIdType, AUTOMATIC)  DtrId
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_OFF)
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return 0;
#else
  return Dem_Cfg_GetDtrData().TestValue[DtrId];
#endif
}

/* ****************************************************************************
 % Dem_DtrData_GetLowerLimit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_DtrData_GetLowerLimit(
  CONST(DTRIdType, AUTOMATIC)  DtrId
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_OFF)
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return 0;
#else
  return Dem_Cfg_GetDtrData().LowLimValue[DtrId];
#endif
}

/* ****************************************************************************
 % Dem_DtrData_GetUpperLimit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_DtrData_GetUpperLimit(
  CONST(DTRIdType, AUTOMATIC)  DtrId
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_OFF)
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return 0;
#else
  return Dem_Cfg_GetDtrData().UppLimValue[DtrId];
#endif
}

/*!
 * \}
 */

#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* DEM_DTRDATA_IMPLEMENTATION_H */
/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DtrData_Implementation.h
 *********************************************************************************************************************/
