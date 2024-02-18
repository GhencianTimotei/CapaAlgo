
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
/*!  Project    MICROSAR Diagnostic Event Manager (Dem)
 *
 *  \addtogroup Dem_Main
 *  \{
 *  \file       Dem.c
 *  \brief      Implementation header file for the MICROSAR Dem
 *  \details    Implementation of DEM module
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/
#define DEM_SOURCE

/* ********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

                                                       /* Dem module headers */
/* ------------------------------------------------------------------------- */
#include "Dem.h"
#include "Dem_Cbk.h"
#include "SchM_Dem.h" /* Patch, moved above Dem_Int in order to avoid compiler warninigs */
#include "Dem_Int.h"

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
# include "Dem_Dcm.h"
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
# include "Dem_J1939Dcm.h"
# include "J1939Nm.h"
#endif

                            /* Development error tracer, for Det_ReportError */
/* ------------------------------------------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif
/* ------------------------------------------------------------------------- */

                   /* Diagnostic Logger and Tracer, for callback declaration */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_NOTIFY_DLT == STD_ON)
# include "Dlt.h"
#endif
/* ------------------------------------------------------------------------- */

      /* Fault inhibition manager, for callbacks and IUMPR inhibition matrix */
/* ------------------------------------------------------------------------- */
#if (((DEM_CFG_SUPPORT_OBDII == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)) \
   && (DEM_CFG_SUPPORT_IUMPR == STD_ON)) || (DEM_CFG_NOTIFY_EVENT_STATUS_FIM == STD_ON) \
   || (DEM_CFG_NOTIFY_MONITOR_STATUS_FIM == STD_ON)
# include "FiM.h"
#endif
/* ------------------------------------------------------------------------- */

                                  /* Schedule Manager, for critical sections */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */

                               /* Rte for forward global callback prototypes */
/* ------------------------------------------------------------------------- */
#include "Dem_Swc.h"
/* ------------------------------------------------------------------------- */

                                            /* Dcm for notification callback */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_NOTIFY_DCM == STD_ON)
# include "Dcm.h"
#endif
/* ------------------------------------------------------------------------- */

                                       /* J1939Dcm for notification callback */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_NOTIFY_J1939DCM == STD_ON)
# include "J1939Dcm.h"
#endif
/* ------------------------------------------------------------------------- */


                                                          /* NvM for its API */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_USE_NVM == STD_ON)
# include "NvM.h"
#endif
/* ------------------------------------------------------------------------- */

                                                       /* EcuM for ErrorHook */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON)
# include "EcuM_Error.h"
#endif

/* ------------------------------------------------------------------------- */

#if (DEM_CFG_DATA_EXTENDED_ENV_DATA == STD_ON) && (DEM_CFG_USE_OHDS == STD_ON)
# include "OHDS_Dem.h"
#endif

/* ********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* vendor specific version information is decimal coded */
#if ( (DEM_SW_MAJOR_VERSION != 20) \
   || (DEM_SW_MINOR_VERSION !=  6) \
   || (DEM_SW_PATCH_VERSION !=  0) )
# error "Vendor specific version numbers of Dem.c and Dem.h are inconsistent"
#endif

/* versions of all included configuration header files shall be checked */
#if ( (DEM_CFG_SW_MAJOR_VERSION != 20) \
   || (DEM_CFG_SW_MINOR_VERSION !=  6) )
# error "Version numbers of Dem.c and Dem_Cfg.h are inconsistent!"
#endif

#if (DEM_CFG_GEN_MAJOR_VERSION != 20)
# error "Incompatible configuration file version used!"
#endif


                                                            /* Logical Units */
/* ------------------------------------------------------------------------- */
#include "Dem_Cfg_Definitions.h"
#include "Dem_AdditionalIncludeCfg.h"
#include "Dem_Satellite_Implementation.h"
#include "Dem_RecordReader_Implementation.h"
#include "Dem_Infrastructure_Implementation.h"
#include "Dem_GlobalDiagnostics_Implementation.h"
#include "Dem_FaultMemory_Implementation.h"
#include "Dem_DiagnosticObserver_Implementation.h"
#include "Dem_Core_Implementation.h"
#include "Dem_Client_Implementation.h"

/*!
 * \}
 */

/* module specific MISRA deviations:

   MD_DEM_1.1_612
     Description: Rule 1.1
                  All code shall conform to ISO 9899:1990 C programming language, ISO 9899, amended and corrected by
                  ISO/IEC 9899/COR1:1995, ISO/IEC 9899/AMD1:1995, and ISO/IEC 9899/COR2: 1996
     Reason:      Depending on the configuration size the generated tables can
                  exceed the C90 limit of 32767 bytes
     Risk:        Compilation error.
     Prevention:  Compiler compatibility must be tested during integration.

     MD_DEM_Dir1.1
     Description: MISRA2012-Dir1.1
                  Any implementation-defined behaviour on which the output of the program 
                  depends shall be documented and understood.
     Reason:      QAC itself states: A 'pointer-to-object' can always be converted safely to a 'pointer-to-void'.
     Risk:        None.
     Prevention:  Only used in context of null pointer checks.

     MD_DEM_Dir1.1_WriteIndexInitialization
     Description: Dir1.1
                  Apparent: Negative value cast to an unsigned type.
     Reason:      This is a false positive. 
                  Write index is initialized to zero each time the external API is invoked. Directly afterwards, the 
                  subtraction operation is done which ensures that the difference between Buffer Size and Write Index can 
                  never be negative. 
     Risk:        The DEM does not return "DEM_BUFFER_TOO_SMALL" in case the buffer is smaller than required size.
     Prevention:  Ensured through code reviews that the write index is not bigger than buffer size at the point of 
                  evaluation.

   MD_DEM_8.6:
     Description: Rule 8.6
                  An identifier with external linkage shall have exactly one external definition.
     Reason:      Subcomponent structure is implemented in header files. The implementation files can be identified by
                  their name ending in _Implementation.h
     Risk:        None.
     Prevention:  None.

   MD_DEM_8.7:
     Description: Rule 8.7
                  Objects shall be defined at block scope if they are only accessed from within a single function.
     Reason:      Vector style guide prevents usage of static variables in function scope
     Risk:        None.
     Prevention:  None.

   MD_DEM_8.5_dcm:
     Description: Rule 8.5
                  An external object or function shall be declared in one and only one file.
     Reason:      MICROSAR Dcm generates all prototypes of functions used. This leads to duplicate definitions.
     Risk:        None.
     Prevention:  None.

   MD_DEM_8.5_schm:
     Description: Rule 8.5
                  An external object or function shall be declared in one and only one file.
     Reason:      MICROSAR SchM generates prototypes of Dem_<X>MainFunction(). This leads to duplicate definitions.
     Risk:        None.
     Prevention:  None.

   MD_DEM_8.5_rte:
     Description: Rule 8.5
                  An external object or function shall be declared in one and only one file.
     Reason:      MICROSAR Rte generates prototypes for callbacks. Some callbacks are also contained in a replacement
                  header in case no Rte is used.This leads to duplicate definitions.
     Risk:        None.
     Prevention:  None.

   MD_DEM_Rule10.5_Enum
     Description: MISRA2012-Rule10.5
                  The value of an expression should not be cast to an inappropriate essential type
     Reason:      The cast is required for converion of interger value. Integer value required for bitwise operation. 
                  Using essential type instead of enum gives no advantage. Enum range is far smaller than provided by essential base type.
     Risk:        Data corruption due to miscast.
     Prevention:  Covered by descriptive enum type definition and code review of the correct usage.

   MD_DEM_10.8_DTRFloatToInteger:
     Description:  Rule10.8
                   A composite expression of 'essentially floating' type is being cast to a different type category.
     Reason:       The cast is required, since DTR values shall be calculated with floating point precision, but are 
                   reported in form of integer values.
     Risk:         Data corruption due to miscast.
     Prevention:    None.

   MD_DEM_10.8_TdFloatToInteger:
     Description:  Rule10.8
                   A composite expression of 'essentially floating' type is being cast to a different type category.
     Reason:       Time since last sample collection (Td) must be calculated with floating point precision,
                   since the DEM Main function task time allows using values with floating point precision.
                   The cast is required, since the Td must be reported in form of a 16 bit
                   integer value as per OEM requirement.
                   The maximum possible value of Td is less than the sampling rate (which is limited to 0xFFFF). This
                   ensures that the Td can fit inside the 16 bit integer value.
                   However, if a floating point DEM Main function task time is used, then data could be lost on
                   conversion.
     Risk:         Data corruption due to miscast.
     Prevention:   None.

   MD_DEM_10.8_TdIntermediateIntegerToFloat:
     Description:  Rule10.8
                   The value of a composite expression shall not be cast to a different essential type category or a wider essential type
     Reason:       Time since last sample collection (Td) must be calculated with floating point precision,
                   since the DEM Main function task time allows using values with floating point precision.
                   The intermediate must be cast to float32 before multiplying with the Dem Main function
                   cycle time since it itself is a floating point value.
     Risk:         Data corruption due to miscast.
     Prevention:   None.

   MD_DEM_11.1:
     Decription:  Rule 11.1
                  Conversions shall not be performed between a pointer to a function and any type other than an integral type.
     Reason:      Different types of callback functions need to be supported through a generic mechanism
     Risk:        Functions are cast to the wrong type before calling.
     Prevention:  The correct function type is indicated by type tagging. The correct cast is verified during code review.

   MD_DEM_11.4_cpy:
     Description: Rule 11.4
                  A cast should not be performed between a pointer to object type and a different pointer to object
                  type.
     Reason:      Use of memcopy/memset requires common pointer type.
     Risk:        Data corruption due to miscast.
     Prevention:  Covered by descriptive pointer types and code review for correct usage.

   MD_DEM_11.4_inh:
     Description: Rule 11.4
                  A cast should not be performed between a pointer to object type and a different pointer to object
                  type.
     Reason:      Use of inheritance pattern requires cast to specific class type.
     Risk:        Data corruption due to miscast.
     Prevention:  Covered by descriptive pointer types and code review for correct usage.

   MD_DEM_11.4_nvm:
     Description: Rule 11.4
                  A cast should not be performed between a pointer to object type and a different pointer to object
                  type.
     Reason:      Mechanism for Nv handling requires common pointer type
     Risk:        None. Pointers are initially aligned and only cast due to common API later on.
     Prevention:  Covered by descriptive pointer types and code review for correct usage.

   MD_DEM_11.4_sr:
     Description: Rule 11.4
                  A cast should not be performed between a pointer to object type and a different pointer to object
                  type.
     Reason:      Serialization of typed data.
     Risk:        Data corruption due to miscast.
     Prevention:  Covered by descriptive pointer types and code review for correct usage.

   MD_DEM_11.8:
     Description: Rule 11.8
                  A cast shall not be performed that removes any const or volatile qualification from the type
                  addressed by a pointer.
     Reason:      MemSet and MemCpy are defined as taking an unqualified pointer.
     Risk:        None.
     Prevention:  Safe access of shared data is verified during code review.

   MD_DEM_13.5_cf:
     Description: Rule 13.5
                  The right hand operand of a logical && or || operator shall not contain persistent side effects
     Reason:      The function called on the right hand side has no persistent side effects.
     Risk:        The function may introduce side effects at a later time.
     Prevention:  Code analysis (e.g. MISRA).

   MD_DEM_13.5_volatile:
     Description: Rule 13.5
                  The right hand operand of a logical && or || operator shall not contain persistent side effects
     Reason:      The function's side effect is restricted to readout of 'volatile' RAM value (causing changed hardware registers)
                  Dem's functionality does not rely on register states.
     Risk:        The function may introduce side effects at a later time.
     Prevention:  Code analysis (e.g. MISRA).

   MD_DEM_13.2_Order_Read_Accesses_Volatile
     Description: Rule 13.2
                  The value of an expression and its persistent side-effects shall be the same under all permitted
                  evaluation orders
     Reason:      The order of read accesses to the volatile variables is not significant.
     Risk:        None.
     Prevention:  None.

   MD_DEM_13.3:
     Description: Rule 13.3
                  Floating-point expressions shall not be tested for equality or inequality.
     Reason:      Test for generatad special value.
     Risk:        None
     Prevention:  Correctness is ensured in test suite.

   MD_DEM_14.1_ACCESSOR
     Description: Rule 14.1
                  Static function '%s()' is not used within this translation unit.
     Reason:      Accessor function ('getter', 'setter') is present although no code is actively using it.
                  Accessor functions do not provide functionality, and are not conditionally compiled to increase
                  maintainability.
     Risk:        Compiler warnings depending on configuration.
                  No reduced code size with a special configuration, not realized optimization.
     Prevention:  None.

   MD_DEM_14.1_LIB
     Description: Rule 14.1
                  Static function '%s()' is not used within this translation unit.
     Reason:      Function is present although no code is actively using it. Function is used as library function
                  and is therefore always available.
     Risk:        Compiler warnings depending on configuration.
                  No reduced code size with a special configuration, not realized optimization.
     Prevention:  None.

   MD_DEM_2.1_UNREACHABLE_STATEMENT:
     Description: Rule 2.1
                  This code is unreachable.
     Reason:      In specific configurations, the comparison evaluates to a constant expression.
                  When an 'if' condition works on the constant expression which always evaluates
                  to true, the code within the the 'else' part cannot be reached, and vice versa.
     Risk:        Compiler warnings or compiler errors depending on configuration.
                  Unreachable code cannot be tested in specific configurations.
     Prevention:  None.

   MD_DEM_14.1_CONFIGURATION_SWITCH:
     Description: Rule 14.1
                  This function is unreachable
     Reason:      In specific configurations, preprocessor configuration switches encapsule all function calls.
                  Which means, that the corresponding function is never called in specific configurations and can be
                  omitted within the compile process.
                  This justification shall only be used, until all configuration dependent preprocessor switches are removed.
     Risk:        Compiler warnings or compiler errors depending on configuration.
                  Unreachable code cannot be tested in specific configurations.
     Prevention:  None.

   MD_DEM_14.2:
     Description: Rule 14.2
                  All non-null statements shall either (i) have at least one side-effect however executed, or
                  (ii) cause control flow to change
     Reason:      This statement is used to avoid warnings caused by unused parameters. Parameters are defined by
                  standardized API requirements, and not needed in case a feature is disabled by configuration.
                  It is either impossible due to API standardization or necessary code duplication (severe maintenance
                  increase) to provide feature dependent APIs with different signatures.
     Risk:        Unavoidable compiler warning or error because of either unused statements or unused parameter.
     Prevention:  None.

   MD_DEM_14.2_CONFIGURATION_SWITCH:
     Description: Rule 14.2
                  All non-null statements shall either (i) have at least one side-effect however executed, or
                  (ii) cause control flow to change
     Reason:      This statement is used to avoid warnings caused by unused parameters. Parameters are defined by
                  standardized API requirements, and not needed in case a feature is disabled by configuration.
                  It is either impossible due to API standardization or necessary code duplication (severe maintenance
                  increase) to provide feature dependent APIs with different signatures.
                  This justificiation shall only be used, until all configuration dependent preprocessor switches are removed.
     Risk:        Unavoidable compiler warning or error because of either unused statements or unused parameter.
     Prevention:  None.

  MD_DEM_14.2_LoopControl
    Description: Rule 14.2
                 Loop control variable in this 'for' statement, %s, is not modified inside loop.
                 No variable appears to be incremented in the third expression of this 'for' statement (control variable
                 identified as %1s).
    Reason:      As long as Dem is not in a consistent state, the loop control variable is always modified inside the loop.
                 If Dem is in an unconsistent state the loop is terminated immediately.
    Risk:        Loop could execute indefinitely.
    Prevention:  Verified by review that loop will be terminated, if Dem is in an unconsistent state.

   MD_DEM_15.4_opt:
     Description: Rule 15.4
                  More than one 'break' statement has been used to terminate this iteration statement.
     Reason:      Increased efficiency on the time critical path.
     Risk:        Maintainability is adversely affected.
     Prevention:  The break statement is documented.

   MD_DEM_15.5:
     Description: Rule 15.5
                  A function should have a single point of exit at the end.
     Reason:      Due to maintainability problems the control flow through the function shall not be complicated even
                  further.
     Risk:        Maintainability is adversely affected.
     Prevention:  None.

   MD_DEM_15.2:
     Description: Rule 15.2
                  An unconditional break statement shall terminate every non-empty switch clause.
     Reason:      The fall-through is preferred to an if-else cascade to avoid code duplication in this particular
                  circumstance.
     Risk:        Adverse effect on maintainability.
     Prevention:  The fall-through is documented.

   MD_DEM_16.3_Continue:
     Description: Rule 16.3
                  Final 'switch' clause ends with a 'jump' statement other than 'break'.
     Reason:      The continue statement is used in a circumstance where a different approach would reduce efficiency
                  or maintainability due to increased complexity.
     Risk:        None.
     Prevention:  None.

   MD_DEM_8.3_dcm:
     Description: Rule 8.3
                  All declarations of an object or function shall use the same names and type qualifiers.
     Reason:      Dcm generates its own prototypes based on a generic algorithm.
     Risk:        Dcm prototypes can deviate from the implementation.
     Prevention:  Verify compatibility during integraton tests.

   MD_DEM_8.3_rte:
     Description: Rule 8.3
                  All declarations of an object or function shall use the same names and type qualifiers.
     Reason:      Port-Defined arguments are not generated with the correct name. This can currently not be influenced
                  due to the RTE being a third party module.
     Risk:        None. The generated prototypes are never used directly but only from generated RTE code.
     Prevention:  None.

   MD_DEM_8.13:
     Description: Rule 8.13
                  A pointer should point to a const-qualified type whenever possible.
     Reason:      The API is standardized and a change would break compliance.
     Risk:        None.
     Prevention:  None.

   MD_DEM_8.13_fp:
     Description: Rule 8.13
                  A pointer should point to a const-qualified type whenever possible.
     Reason:      The data behind the pointer is modified, or modified in some configurations. This is a false positive.
     Risk:        None.
     Prevention:  None.

   MD_DEM_8.13_Internal:
     Description: Rule 8.13
                  A pointer should point to a const-qualified type whenever possible.
     Reason:      The API has to be compatible to a common prototype
     Risk:        None.
     Prevention:  None.

   MD_DEM_8.13_Design:
     Description: Rule 8.13
                  A pointer should point to a const-qualified type whenever possible.
     Reason:      The function has write access to shared state. The caller may not rely on constancy. Even if the
                  current implementation does not need write access, this is allowed to change. A stable interface is
                  preferred to adhering to this rule.
     Risk:        None.
     Prevention:  None.

   MD_DEM_16.9_fp:
     Description: Rule 16.9
                  A function identifier shall only be used with either a preceding &, or with a parenthesised parameter
                  list, which may be empty.
     Reason:      There is a preceeding &, and the use as a function pointer is intended
     Risk:        None.
     Prevention:  None.

   MD_DEM_19.13:
     Description: Rule 19.13
                  K&R compilers do not support the ISO glue operator '##'.
     Reason:      This kind of implementation creates the least MISRA warnings.
     Risk:        K&R compilers will not work.
     Prevention:  Integration test using target compiler, error directives to detect evaluation errors.

   MD_DEM_19.15:
     Description: Rule 19.15
                  Precautions shall be taken in order to prevent the contents of a header file being included twice.
     Reason:      Precautions HAVE been taken, this violation is a false positive.
     Risk:        None.
     Prevention:  None.

   MD_DEM_20.2:
     Description: Rule 20.2
                  The names of standard library macros, objects and functions shall not be reused.
     Reason:      Included from vector standard library.
     Risk:        Name collision with different standard library.
     Prevention:  None.

   MD_DEM_14.2_LoopControlHandledInternally:
     Description: Rule 14.2
                  The variable identified as the control variable in this 'for' loop has been modified inside the body of the loop.
     Reason:      Incrementation of the control variable inside the loop is necessary to realize certain functionality or better readibility.
     Risk:        Increased complexity of the code.
     Prevention:  Correctness of code verified by code review and testcases.

   MD_DEM_14.2_FalsePositive:
     Description: Rule 14.2
     The variable identified as the control variable in this 'for' loop has been modified inside the body of the loop.
     Reason:      False positive, a structure containing the loop control variable is modified but not the loop control variable.
     Risk:        Increased complexity of the code.
     Prevention:  Correctness of code verified by code review and testcases.

   MD_DEM_14.2_LoopInitialisation:
     Description: Rule 14.2
                  No variable appears to be initialised in the first expression of this 'for loop'.
     Reason:      False positive, in the first expression of the for loop the loop control variable is passed as an argument to a
                  function which initializes it.
     Risk:        None.
     Prevention:  None.

  MD_DEM_18.1_ComputingOfInvalidPointer:
    Description: Rule 18.1
                 Apparent: Computing an invalid pointer value.
    Reason:      This is a False positive. 
    Risk:        Read operation outside of the Dem memory region.
    Prevention:  Verified by review that only read operations are performed with the pointer.
                 Verified by review and testing that the ReadoutBufferId, which is used as an Index to the array
                 is always valid.

   MD_DEM_2983:
     Description: Rule 2.2
                  This assignment is redundant. The value of this object is never subsequently used.
     Reason:      The function argument cannot be removed, because it is either used in a different configuration,
                  or required by design.
     Risk:        None.
     Prevention:  None.

   MD_DEM_2987:
    Description: Rule 2.2
                 This function call produces no side effects and is redundant.
    Reason:      In specific configurations, the function contains no code.
    Risk:        None.
    Prevention:  None.

   MD_DEM_3203:
     Description: Rule N/A
                  The variable '%s' is set but never used.
     Reason:      The variable cannot be removed, because it is used in a different configuration.
     Risk:        None.
     Prevention:  None.

   MD_DEM_3206:
     Description: Rule N/A
                  The parameter '%s' is not used in this function.
     Reason:      API / Standardized API is not adapted based on configuration
     Risk:        None.
     Prevention:  None.

   MD_DEM_3305:
     Description: Rule N/A
                  Pointer cast to stricter alignment
     Reason:      Already aligned pointers are handled in a generic way.
     Risk:        None.
     Prevention:  None.

   MD_DEM_Dir4.1_RunTimeCheckWriteOperation
     Description: Rule Dir4.1
                  Definite/Apparent/Suspicious: Dereference of an invalid pointer value.
     Reason:      This is a False Positive. The access is protected by runtime checks, which assert the array bounds.
     Risk:        Write access outside the bounds of an array, if runtime checks is disabled.
     Prevention:  Runtime checks prevent access, if enabled.

   MD_DEM_Dir4.1_MemoryEntryPointerAccess
     Description: Rule Dir4.1
     Definite/Apparent/Suspicious: Dereference of an invalid pointer value.
     Reason:      This is a False Positive. 
                  The runtime check and Safety Manual item referenced in 
                  SBSW_DEM_POINTER_WRITE_MEMORYENTRY ensures that the accesses are always within bounds.
     Risk:        Read/ Write access outside the bounds of an array.
     Prevention:  Runtime checks and Safety Manual item prevent write access, if enabled.

   MD_DEM_Dir4.1_SatelliteInfoStructPointers
     Description: Rule Dir4.1
                  Apparent/Suspicious: Dereference of an invalid pointer value.
     Reason:      This is a False Positive. 
     Risk:        The DEM reads from an invalid memory location.
     Prevention:  The validity of macros pointing to the contents of SatelliteInfo structure is ensured through the 
                  Safety Manual Items CM_DEM_S_SIZEOF_SATELLITEINFOTYPE_ARRAYS, CM_DEM_S_SIZEOF_SATELLITEINFOTYPE_POINTER.
                  As per the SMIs, if the pointers are invalid, they must be defined as NULL_PTR. 
                  In case of an invalid configuration, the implementation reads a behind an invalid pointer, which is harmless.
                  The implementation verfies for NULL_PTR, a valid Satellite Id and Monitor Id before any write operation.

  MD_DEM_Dir4.1_NullPointerDereference
     Description: Rule Dir4.1
                  Definite/Apparent/Suspicious: Arithmetic operation on NULL pointer.
     Reason:      It appears that a Null pointer is dereferenced in some configurations. 
                  This is only true if a limited scope is evaluated by a limited tool. In fact the scope is never active 
                  in this configuration.
     Risk:        Read access to memory that does not belong to Dem.
     Prevention:  Verified by review, that the read access is valid if done.

  MD_DEM_Dir4.1_ReadOperation
     Description: Rule Dir4.1
                  Definite/Apparent/Suspicious: Dereference of an invalid pointer value.
                  Definite/Apparent/Suspicious: Arithmetic operation on NULL pointer.
     Reason:      This is a False Positive.
     Risk:        Read access outside the bounds of an array.
                  Undefined behavior, due to incorrect read value.
     Prevention:  Verified by review, that the read accesses are valid.

  MD_DEM_Dir4.1_NullFunctionPointerCheck
     Description: Rule Dir4.1
                  Apparent: Dereference of NULL pointer.
     Reason:      This is a False Positive.
                  Before function pointer is dereferenced it is checked for NULL pointer.
     Risk:        None
     Prevention:  None

  MD_DEM_Dir4.1_NullPointerDereference
     Description: Rule Dir4.1
                  Apparent: Dereference of NULL pointer.
     Reason:      This is a False Positive.
                  The Global Config pointer is initialized during Dem Initialization.
     Risk:        Read access outside the bounds of an array.
                  Undefined behavior, due to incorrect read value.
     Prevention:  Verified by review, that the read accesses are valid.

  MD_DEM_Dir4.1_ReadOperationLoopExit
     Description: Rule Dir4.1
                  Definite: Dereference of an invalid pointer value.
     Reason:      This is a false positive. The read operation is called in a loop. The loop exit condition
                  prevents the confirmed chronology index from being outside the bounds of the array.
     Risk:        Read Access outside the bounds of an array.
     Prevention:  Correct loop exit condition is verified during code review.

  MD_DEM_2982
     Description: Rule 2.2
                  This assignment is redundant. The value of this object is never used before being modified.
     Reason:      In specific configurations, the variable might not be used.
     Risk:        None.
     Prevention:  None.
  
  MD_DEM_2985:
    Description: Rule 2.2
                 This operation is redundant. The value of the result is always that of the left-hand operand.
    Reason:      In specific configurations, the right-hand operand can affect the value.
    Risk:        None.
    Prevention:  None.

  MD_DEM_2986:
    Description: Rule 2.2
                 This operation is redundant. The value of the result is always that of the right-hand operand.
    Reason:      In specific configurations, the left-hand operand can affect the value.
    Risk:        None.
    Prevention:  None.
  
  MD_DEM_2897:
    Description: Rule 2.2
                 Apparent: Negative value cast to an unsigned type.
    Reason:      Signed data values are stored in unsigned buffer or variable.
                 Nevertheless, no data loss occurs since casting to unsign do not change the bit values. Re-interpreting the 
                 buffer/variable content as signed values at a later point in time, gives original signed values.
    Risk:        Data corruption due to miscast.
    Prevention:  None.

   MD_DEM_2994:
     Description: Rule 2.2
                  The value of this 'while' or 'for' loop controlling expression is always 'false'. The loop will not be entered.
     Reason:      In specific configurations, the expression is true and the loop will be entered.
     Risk:        None.
     Prevention:  None.

   MD_DEM_2995:
     Description: Rule 2.2
                  The result of this logical operation is always 'true'.
     Reason:      In specific configurations, the comparison evaluates a constant expression
     Risk:        None.
     Prevention:  None.

   MD_DEM_2996:
     Description: Rule 2.2
                  The result of this logical operation is always 'false'.
     Reason:      In specific configurations, the comparison evaluates a constant expression
     Risk:        None.
     Prevention:  None.

   MD_DEM_2990:
     Description: Rule 14.3
                  The value of this 'if' controlling expression is always 'true'.
     Reason:      In specific configurations, the comparison evaluates a constant expression
     Risk:        None.
     Prevention:  None.

   MD_DEM_2991:
     Description: Rule 14.3
                  The value of this 'if' controlling expression is always 'true'.
     Reason:      In specific configurations, the comparison evaluates a constant expression
     Risk:        None.
     Prevention:  None.

   MD_DEM_2992:
     Description: Rule 14.3
                  The value of this 'if' controlling expression is always 'false'.
     Reason:      In specific configurations, the comparison evaluates a constant expression
     Risk:        None.
     Prevention:  None.

   MD_DEM_2993:
     Description: Rule 14.3
                  The value of this 'do - while' loop controlling expression is always 'false'.
                  The loop will only be executed once. 
     Reason:      In specific configurations, the comparison evaluates a constant expression
     Risk:        None.
     Prevention:  None.

   MD_DEM_6050_CONFIGURATION:
     Description: Metrics
                  Number of distinct function calls defined by HIS shall be in range 0..7
     Reason:      Depending on the configuration a different function is called to access similar configuration data.
     Risk:        Stack usage and runtime too high for target uC. Understandability and testability might become too complex.
     Prevention:  Use of inline functions and code review.

 *********************************************************************************************************************/

/* START_COVERAGE_JUSTIFICATION
  \ID COV_DEM_ORGANI_COMMENT
    \REASON This section only contains commentaries that are removed from the source before delivery.

  \ID COV_DEM_TESTCODE
    \REASON This section only contains code to help test the software. It has no influence on the actual code. All such
            code is removed from the source before delivery.

  \ID COV_DEM_RTE_TYPEDEFS
    \REASON Those preprocessor defines are a protection against double defines.

  \ID COV_DEM_UNSUPPORTED_FEATURE
    \REASON This feature is (currently) not supported. Activating the feature is prohibited by an #error directive.

  \ID COV_DEM_FAILED_RUNTIME_CHECKS
    \REASON This preprocessor switch can be enabled by a user configuration file in order to prevent un-initialization of
            the DEM in case of a failed run-time check. Using user configuration files is not allowed in silent configuration.

  \ID COV_DEM_USER_MACROS
    \REASON The condition checks whether a macro is defined and conditionally assigns a default implementation.
            When using an own macro implementation, the customer is responsible to ensure its safety.

  \ID COV_DEM_PREPROCESSOR_DEFINE
    \REASON The condition checks whether a preprocessor macro is defined and conditionally assigns a default value.

  \ID COV_DEM_UNSUPPORTED_TESTED_FEATURE
    \REASON The use of this features (preprocessor combinations) is for the customer prohibited by an #error directive.
            Nevertheless, as testing the features during component development shall be possible, compilation errors have to be
            suppressed during component tests.

  \ID COV_DEM_UNSUPPORTED_FEATURE_COMBINATION
    \REASON The use of this features combination is (currently) not supported. The encapsulated code indicates that the function has
            to be reworked if this changes in the future.

END_COVERAGE_JUSTIFICATION
*/
/*********************************************************************************************************************/
/* COV_JUSTIFICATION_BEGIN

\ID COV_DEM_GENERATED_EVENTID
\ACCEPT TF tf xf tf
\REASON Verified by inspection: EventIds are generated that way that the first event Id is always assigned to primary memory.

\ID COV_DEM_UNSUPPORTED_COMBINATION_GLOBAL_SRECS
\ACCEPT TF tf xf tx
\REASON For feature Global Snapshot Records, handling of all storage triggers and update status is implemented
but not tested. Currently the update status is limited to 'FALSE' and storage trigger is limited
to 'Confirmed' through configuration.

\ID COV_DEM_SWITCH_DEFAULT_SET_READINESSGROUP_DISABLED
\ACCEPT XX
\REASON Testing framework cannot reach the default handling of this switch() case with a meaningful testcase. 
 All readiness groups except "DEM_CFG_READINESS_NONE" are handled in the switch() operation. The caller function
 ensures that function Dem_Util_SetReadinessGroupDisabled() is not called with readiness group "DEM_CFG_READINESS_NONE".
 The default case is required to handle any incorrect generation by Cfg5.

COV_JUSTIFICATION_END */
/*********************************************************************************************************************/
/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_DEM_POINTER_WRITE_API
  \DESCRIPTION    In an API function, data is written through a pointer passed as function argument.
  \COUNTERMEASURE \N The caller ensures the pointers passed to this function are valid.

\ID SBSW_DEM_POINTER_WRITE_ARGUMENT
  \DESCRIPTION    In an internal function, data is written through a pointer passed as function argument.
  \COUNTERMEASURE \N The caller ensures the pointers passed to this function are valid.

\ID SBSW_DEM_POINTER_FORWARD_ARGUMENT
  \DESCRIPTION    A pointer parameter is received as argument and forwarded to another function expecting a valid
                  pointer. The called function does not store its pointer parameters.
  \COUNTERMEASURE \N The pointer is used unmodified, as such it is still valid.

\ID SBSW_DEM_POINTER_FORWARD_ARGUMENT_STRUCT_MEMBER
  \DESCRIPTION    A pointer to struct is received as argument and a pointer to one of the struct members is forwarded
                  to another function expecting a valid pointer. The struct member itself is not a pointer.
                  The called function does not store its pointer parameters.
  \COUNTERMEASURE \N The pointer is used unmodified, as such the pointer to the struct and its member is valid.

\ID SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER
  \DESCRIPTION    A pointer parameter and buffer size are received as argument. The function writes to the buffer,
                  or forwards the buffer and buffer size to another function which will write data to the buffer.
                  The called function will only write up to the number of bytes received as argument.
  \COUNTERMEASURE \R [CM_DEM_R_CHECK_REMAINING_BUFFER]

\ID SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER
  \DESCRIPTION    A pointer parameter to a buffer from a API function and the corresponding buffer size are forwarded
                  to a another function expecting a valid pointer. The called function does not store its pointer
                  parameters. The called function will only write up to the number of bytes received as argument.
  \COUNTERMEASURE \N The caller of the API ensures that the pointer and the buffer size are valid.

\ID SBSW_DEM_POINTER_FORWARD_STACK
  \DESCRIPTION    A pointer is passed to a function expecting a valid pointer. The called function does not store its
                  pointer parameter.
  \COUNTERMEASURE \N The pointer is taken from a local variable, as such it is always valid.

\ID SBSW_DEM_CALL_POINTER_FORWARD_STACK
  \DESCRIPTION    In a function, a configured function pointer is dereferenced. The dereferenced function expects a valid
                  pointer argument and does not store the passed pointer. A pointer to a local stack variable is passed
                  to the dereferenced function, so the pointer argument is always valid.
  \COUNTERMEASURE \R [CM_DEM_R_SIZEOF_DATAELEMENT_TABLE]
                  \R [CM_DEM_R_CHECK_DATAELEMENT_TYPE]
                  \S [CM_DEM_S_DATA_CALLBACK_FPTR]
                  \S [CM_DEM_S_CALL_DESTINATIONBUFFER]

\ID SBSW_DEM_POINTER_FORWARD_GLOBAL
  \DESCRIPTION    A pointer is passed to a function expecting a valid pointer.
  \COUNTERMEASURE \N The pointer is taken from a global variable, as such it is always valid.

\ID SBSW_DEM_POINTER_FORWARD_API
  \DESCRIPTION    One or multiple pointer(s) received in the API function are passed to a function expecting one or
                  more valid pointers.
  \COUNTERMEASURE \N The caller ensures that pointers passed to this function are valid.

\ID SBSW_DEM_POINTER_NULLPTR_CHECKING
\DESCRIPTION    Pointer received in the API function is tested to be no null pointer.
\COUNTERMEASURE \N None required. The pointer is compared against null only.

\ID SBSW_DEM_POINTER_RUNTIME_CHECK
  \DESCRIPTION    A pointer is passed to function Dem_Error_RunTimeCheckFailed(). Dem_Error_RunTimeCheckFailed() copies
                  only pointer adress to global variable Dem_FileOfRuntimeError as debug information in case of runtime
                  errors. Value of passed pointer is not modified.
  \COUNTERMEASURE \N No write acccess to Dem_FileOfRuntimeError which is a pointer to const.

\ID SBSW_DEM_NVM_WRITEBLOCK
  \DESCRIPTION    A NvMBlockId and a source pointer is passed to NvM_WriteBlock.
  \COUNTERMEASURE \R [CM_DEM_R_CHECK_NVBLOCKID]
                  \S [CM_DEM_S_CHECK_NVBLOCKID]
                  \S [CM_DEM_S_CHECK_NVBLOCK_LENGTH]
                  \S [CM_DEM_M_SIZEOF_MEMORYBLOCKID]

\ID SBSW_DEM_POINTER_MEMCPY_TIMESERIESENTRY
  \DESCRIPTION    In an internal function, a memory area is copied through a pointer to a memory entry. The entry
                  pointer is initialized by Dem_Memory_TimeSeries_GetEntrySafe which will always return a pointer to a valid memory
                  entry. The number of bytes copied is the size of the target buffer.
  \COUNTERMEASURE \R [CM_DEM_R_TIMESERIES_GET_ENTRY]
                  \M [CM_DEM_M_TIMESERIESINDEX_LIMITS]
                  \M [CM_DEM_M_SIZEOF_MEMORYDATAPTR]
                  \S [CM_DEM_S_TIMESERIESINDEX_TYPE]

\ID SBSW_DEM_POINTER_MEMCPY_PRIMARYENTRY
  \DESCRIPTION    In an internal function, data is copied into a Dem_Cfg_PrimaryEntryType structure using memcpy. The destination pointer
                  is initialized using Dem_MemoryEntry_GetEntry() and is therefore always valid. The buffer size to copy is
                  derived by sizeof(Dem_Cfg_PrimaryEntryType).
  \COUNTERMEASURE \N The memory area is always valid.

\ID SBSW_DEM_CALL_FOREACH_FUNCPTR
  \DESCRIPTION    In an internal function, a pointer passed as function argument is called, with a pointer argument as argument.
  \COUNTERMEASURE \N The caller ensures that both pointers passed to this function are valid, and the argument pointer is a valid
                     argument for the function pointer.

\ID SBSW_DEM_CALL_FUNCPTR_FOR_EVENT
  \DESCRIPTION    In an internal function to aid reusability, event specific operations are done by invoking a passed function pointer
                  with the respective Event Id and additional parameters passed as a second pointer argument.
  \COUNTERMEASURE \N The caller ensures that both pointers passed to this function are valid, and the argument pointer is a valid
                     argument for the function pointer.

\ID SBSW_DEM_CALL_ITERATOR_POINTER
  \DESCRIPTION    The iterator pattern works like this:
                  The functions Dem_<X>IterInit, Dem_<X>IterResume, Dem_<X>IterExists, Dem_<X>IterNext, Dem_<X>IterGet
                  receive a pointer to an iterator variable Dem_<X>IterType.
                  Dem_<X>IterInit or Dem_<X>IterResume initializes the iterator variable, so it is valid to be used
                  by the other functions. Those functions expect a reference to a valid iterator variable.
                  The iterator variable is still valid when those functions return.
  \COUNTERMEASURE \N The iterator variable is initialized using the appropriate Init function before passing its reference
                     to Dem_<X>IterExists/Dem_<X>IterNext/Dem_<X>IterGet.

\ID SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER
  \DESCRIPTION    The iterator pattern works like this:
                  The functions Dem_Cfg_<X>IterInit, Dem_Cfg_<X>IterExists, Dem_Cfg_<X>IterNext, Dem_Cfg_<X>IterGet
                  receive a pointer to an iterator variable Dem_Cfg_<X>IterType.
                  The Dem_Cfg_<X>IterInit initializes the iterator variable, so it is valid to be used by the other three
                  functions. Those functions expect a reference to a valid iterator variable. The iterator variable is still
                  valid when those functions return.
                  Dem_Cfg_<X>IterGet will verify the iterator is still in range of the target table to prevent
                  returning a table row with invalid pointer contents.
  \COUNTERMEASURE \R [CM_DEM_R_INIT_MONITOR_FOR_FUNCTION_INDEX]
                  \R [CM_DEM_R_EVENT_CBK_STATUS_INDEX]
                  \R [CM_DEM_R_DTC_CBK_STATUS_INDEX]
                  \R [CM_DEM_R_J1939_DTC_CBK_STATUS_INDEX]

\ID SBSW_DEM_CALL_MEMORYINFO_POINTER
  \DESCRIPTION    The memory info pointer is passed to a function that expects a valid pointer.
                  The pointer is locally allocated and initialized using Dem_MemState_MemoryInfoInit.
                  Dem_MemState_MemoryInfoInit returns a pointer to a global struct variable that is always valid.
                  The Global struct variable contains the pointers ChronoPtr and SizePtr.
                  ChronoPtr is initialized with a reference to a global RAM variable with corresponding size or to 
                  the NULL_POINTER. Additional runtime check is needed before writing through ChronoPtr (refer to 
                  SBSW_DEM_ARRAY_WRITE_MEMORYCHRONOLOGY and CM_DEM_R_CHRONOLOGY_NULLPTR).
                  SizePtr references a global variable and therefore is always valid.
                  The memory info struct variable contains the function pointers TestEntryForEventFctPtr and FreeEntryFctPtr.
                  In the embedded code, the TestEntryForEventFctPtr and FreeEntryFctPtr are assigned to to funtions 
                  that are always available if the struct variable is defined. So the function pointers are always valid.
  \COUNTERMEASURE \M [CM_DEM_M_SIZEOF_PRIMARYCHRONOLOGY]
                  \M [CM_DEM_M_SIZEOF_SECONDARYCHRONOLOGY]
                  \M [CM_DEM_M_SIZEOF_TIMESERIES_CHRONOLOGY]

\ID SBSW_DEM_CALL_FUNCPTR_MEMORYINFO_POINTER
  \DESCRIPTION    A pointer to a memory info is received as argument in a function and the function pointer referenced in the memory info
                  is called. The memory info pointer was initialized using Dem_MemState_MemoryInfoInit, which will always
                  initialize it to point to an existing (global) memory info struct. This also initializes the function pointer, 
                  so the dereferenced function pointer is always valid (see also SBSW_DEM_CALL_FUNCPTR_MEMORYINFO_POINTER).
  \COUNTERMEASURE \R [CM_DEM_R_DEBOUNCEINFO_INIT]

\ID SBSW_DEM_POINTER_FORWARD_READOUTBUFFER_OBDFREEZEFRAME
  \DESCRIPTION    A pointer to OBD FreezeFrame buffer and buffer size are forwarded to another function. The function writes to the buffer,
                  or forwards the buffer and buffer size to another function which will write data to the buffer.
                  The called function will only write up to the number of bytes received as argument.
  \COUNTERMEASURE \R [CM_DEM_R_GET_READOUTBUFFER_OBDFREEZEFRAME]
                  \M [CM_DEM_M_SIZEOF_READOUTBUFFER_OBDFREEZEFRAME]

\ID SBSW_DEM_CALL_DEBOUNCEINFO_INIT
  \DESCRIPTION    A Dem_Debounce_InfoType union is locally defined and a pointer to the same is passed to the
                  Dem_Debounce_DebounceInfoInit function for initializing the Dem_Debounce<DEBOUNCING_ALGORITHM>_InfoType structure,
                  corresponding to the configured debouncing algorithm.
                  In the Dem_Debounce_DebounceInfoInit function, the debouncing algorithm specific initialization functions
                  Dem_Debounce<DEBOUNCING_ALGORITHM>_InfoInit are invoked with a pointer to the debouncing algorithm specific
                  Dem_Debounce<DEBOUNCING_ALGORITHM>_InfoType structure. In these functions, the Dem_Debounce<ALGORITHM_SPECIFIC>_InfoType
                  structure is completely initialized.
                  For initializing the Dem_DebounceBase_InfoType structure contained within the Dem_Debounce<ALGORITHM_SPECIFIC>_InfoType
                  structure, the Dem_DebounceBase_InfoInitDefault function is invoked with a valid pointer to this
                  Dem_DebounceBase_InfoType structure. The Dem_DebounceBase_InfoInitDefault function initializes all
                  elements of the Dem_DebounceBase_InfoType structure.
                  The pointer to the initialized Dem_DebounceBase_InfoType structure which implicitly also points to the
                  Dem_Debounce<DEBOUNCING_ALGORITHM>_InfoType structure is therefore always valid and hence can be passed
                  to and used by other functions.
  \COUNTERMEASURE \N The pointer is always valid.

\ID SBSW_DEM_CALL_DEBOUNCEINFO_POINTER
  \DESCRIPTION    A debounce info pointer is locally allocated and passed as argument to other functions.
                  As a reference to a local stack variable the pointer itself is always valid.
                  The pointer is initialized using Dem_Debounce_DebounceInfoInit, which will always initialize it to point
                  to an existing debounce info struct.
  \COUNTERMEASURE \R [CM_DEM_R_DEBOUNCEINFO_INIT]

\ID SBSW_DEM_CALL_FUNCPTR_DEBOUNCEINFO_POINTER
  \DESCRIPTION    A pointer to a debounce info is received as argument in a function and the function pointer referenced in the debounce info
                  is called. The debounce info pointer was initialized using Dem_Debounce_DebounceInfoInit, which will always
                  initialize it to point to an existing debounce info struct. This also initializes the function pointer table, so the dereferenced
                  function pointer is always valid (see also SBSW_DEM_CALL_DEBOUNCEINFO_INIT).
  \COUNTERMEASURE \R [CM_DEM_R_DEBOUNCEINFO_INIT]

\ID SBSW_DEM_CALL_DEBOUNCETIMEBASED_INFOPTR_INIT
  \DESCRIPTION     The structure Dem_DebounceTimeBased_InfoType is initialized in the function Dem_Debounce_DebounceInfoInit.
                   A function receives a pointer to the Base class object of the structure, which is cast to the
                   corresponding parent class structure in the function. Since the Base class object is the first element
                   of the structure, casting this pointer to the parent structure always yields a valid pointer.
                   (see also SBSW_DEM_CALL_DEBOUNCEINFO_INIT)
  \COUNTERMEASURE \R CM_DEM_R_CHECK_TIMEBASED_DEBOUNCEINFO_PTR

\ID SBSW_DEM_DEBOUNCETIMEBASED_INFOPTR_FORWARD_ARGUMENT
  \DESCRIPTION     A pointer to the structure Dem_DebounceTimeBased_InfoType is locally allocated and passed as argument
                   to other functions. As a reference to a local stack variable the pointer itself is always valid.
                   This pointer is initialized using Dem_DebounceTimeBased_Base2TimeBased.
                   (see also SBSW_DEM_CALL_DEBOUNCETIMEBASED_INFOPTR_INIT)
  \COUNTERMEASURE \N The pointer is always valid because it is initialized by casting a valid base class pointer.

\ID SBSW_DEM_DEBOUNCETIMEBASED_INFOPTR_WRITE_STACK
  \DESCRIPTION     Data is written through a pointer that is locally allocated and initialized by casting a valid
                   Dem_DebounceBase_InfoType pointer using Dem_DebounceTimeBased_Base2TimeBased.
                   (see also SBSW_DEM_CALL_DEBOUNCETIMEBASED_INFOPTR_INIT)
  \COUNTERMEASURE \N The pointer is always valid because it is initialized by casting a valid base class pointer.

\ID SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR
  \DESCRIPTION     A pointer to the Dem_DebounceBase_InfoType structure of a Dem_DebounceTimeBased_InfoType structure is
                   passed as argument to a function expecting a valid pointer. The structure Dem_DebounceTimeBased_InfoType
                   is initialized in the function Dem_Debounce_DebounceInfoInit.
                   (see also SBSW_DEM_CALL_DEBOUNCETIMEBASED_INFOPTR_INIT, SBSW_DEM_DEBOUNCETIMEBASED_INFOPTR_FORWARD_ARGUMENT)
  \COUNTERMEASURE \N The pointer is always valid.

\ID SBSW_DEM_CALL_DEBOUNCECOUNTERBASED_INFOPTR_INIT
  \DESCRIPTION     The structure Dem_DebounceCounterBased_InfoType is initialized in the function Dem_Debounce_DebounceInfoInit.
                   A function receives a pointer to the Base class object of the structure, which is cast to the
                   corresponding parent class structure in the function. Since the Base class object is the first element
                   of the structure, casting this pointer to the parent structure always yields a valid pointer.
                   (see also SBSW_DEM_CALL_DEBOUNCEINFO_INIT)
  \COUNTERMEASURE \R CM_DEM_R_CHECK_COUNTERBASED_DEBOUNCEINFO_PTR

\ID SBSW_DEM_DEBOUNCECOUNTERBASED_INFOPTR_FORWARD_ARGUMENT
  \DESCRIPTION     A pointer to the structure Dem_DebounceCounterBased_InfoType is locally allocated and passed as argument
                   to other functions. As a reference to a local stack variable the pointer itself is always valid.
                   This pointer is initialized using Dem_DebounceCounterBased_Base2CounterBased.
                   (see also SBSW_DEM_CALL_DEBOUNCECOUNTERBASED_INFOPTR_INIT)
  \COUNTERMEASURE \N The pointer is always valid because it is initialized by casting valid base class pointer.

\ID SBSW_DEM_DEBOUNCECOUNTERBASED_INFOPTR_WRITE_STACK
  \DESCRIPTION     Data is written through a pointer that is locally allocated and initialized by casting a valid
                   Dem_DebounceBase_InfoType pointer using Dem_DebounceCounterBased_Base2CounterBased.
                   (see also SBSW_DEM_CALL_DEBOUNCECOUNTERBASED_INFOPTR_INIT)
  \COUNTERMEASURE \N The pointer is always valid because it is initialized by casting a valid base class pointer.

\ID SBSW_DEM_DEBOUNCECOUNTERBASED_INFO_BASE_PTR
  \DESCRIPTION     A pointer to the Dem_DebounceBase_InfoType structure of a Dem_DebounceCounterBased_InfoType structure is
                   passed as argument to a function expecting a valid pointer. The structure Dem_DebounceCounterBased_InfoType
                   is initialized in the function Dem_Debounce_DebounceInfoInit.
                   (see also SBSW_DEM_CALL_DEBOUNCECOUNTERBASED_INFOPTR_INIT, SBSW_DEM_DEBOUNCECOUNTERBASED_INFOPTR_FORWARD_ARGUMENT)
  \COUNTERMEASURE \N The pointer is always valid.

\ID SBSW_DEM_CALL_DEBOUNCEMONITORINTERNAL_INFOPTR_INIT
  \DESCRIPTION     The structure Dem_DebounceMonitorInternal_InfoType is initialized in the function Dem_Debounce_DebounceInfoInit.
                   A function receives s pointer to the Base class object of the structure, which is cast to the
                   corresponding parent class structure in the function. Since the Base class object is the first element
                   of the structure, casting this pointer to the parent structure always yields a valid pointer.
                   (see also SBSW_DEM_CALL_DEBOUNCEINFO_INIT)
  \COUNTERMEASURE \R CM_DEM_R_CHECK_MONITORINTERNAL_DEBOUNCEINFO_PTR

\ID SBSW_DEM_DEBOUNCEMONITORINTERNAL_INFOPTR_FORWARD_ARGUMENT
  \DESCRIPTION     A pointer to the structure Dem_DebounceMonitorInternal_InfoType is locally allocated and passed as argument
                   to other functions. As a reference to a local stack variable the pointer itself is always valid.
                   This pointer is initialized using Dem_DebounceMonitorInternal_Base2MonitorInternal.
                   (see also SBSW_DEM_CALL_DEBOUNCEMONITORINTERNAL_INFOPTR_INIT)
  \COUNTERMEASURE \N The pointer is always valid because it is initialized by casting valid base class pointer.

\ID SBSW_DEM_DEBOUNCEMONITORINTERNAL_INFOPTR_WRITE_STACK
  \DESCRIPTION     Data is written through a pointer that is locally allocated and initialized by casting a valid
                   Dem_DebounceBase_InfoType pointer using Dem_DebounceMonitorInternal_Base2MonitorInternal.
                   (see also SBSW_DEM_CALL_DEBOUNCEMONITORINTERNAL_INFOPTR_INIT)
  \COUNTERMEASURE \N The pointer is always valid because it is initialized by casting a valid base class pointer.

\ID SBSW_DEM_DEBOUNCEMONITORINTERNAL_INFO_BASE_PTR
  \DESCRIPTION     A pointer to the Dem_DebounceBase_InfoType structure of a Dem_DebounceMonitorInternal_InfoType structure is
                   passed as argument to a function expecting a valid pointer. The structure Dem_DebounceMonitorInternal_InfoType
                   is initialized in the function Dem_Debounce_DebounceInfoInit.
                   (see also SBSW_DEM_CALL_DEBOUNCEMONITORINTERNAL_INFOPTR_INIT, SBSW_DEM_DEBOUNCEMONITORINTERNAL_INFOPTR_FORWARD_ARGUMENT)
  \COUNTERMEASURE \N The pointer is always valid.

\ID SBSW_DEM_CALL_LOCAL_DESTINATIONBUFFER
  \DESCRIPTION    An application callback is invoked to write to a data buffer that is locally allocated. The caller is
                  responsible that buffer pointer and buffer length are correct.
  \COUNTERMEASURE \R [CM_DEM_R_CHECK_REMAINING_BUFFER]
                  \R [CM_DEM_R_SIZEOF_DATAELEMENT_TABLE]
                  \R [CM_DEM_R_CHECK_DATAELEMENT_TYPE]
                  \S [CM_DEM_S_DATA_CALLBACK_FPTR]
                  \S [CM_DEM_S_CALL_DESTINATIONBUFFER]

\ID SBSW_DEM_CALL_DESTINATIONBUFFER_INIT
  \DESCRIPTION    A pointer to a DestinationBuffer structure is locally allocated and passed to Dem_Data_InitDestinationBuffer
                  for initialization. The write index of the DestinationBuffer structure is initialized to 0. The buffer size is
                  initialized to the corresponding buffer size.
                  The buffer pointer can be received
                  - via a *Dcm API. It is the responsibility of the Dcm
                    to pass a valid destination buffer and matching size.
                  - from an application API with size information. It is the responsibility of the application to pass a valid
                    destination buffer and matching size.
                  - from internal function Dem_MemoryEntry_GetExtendedRecordDataPtr(). This function will always return a valid pointer.
                    In this case the corresponding size is queried with function Dem_Cfg_GlobalERecMaxRawSize().
                  - from internal function Dem_Memory_TimeSeries_RingBuffer_GetNormalSlot(). This function will always return a valid pointer.
                    In this case the corresponding size is queried with function Dem_Cfg_GlobalTimeSeriesNormalBufferSize().
                  - from internal function Dem_Memory_TimeSeries_RingBuffer_GetFastSlot(). This function will always return a valid pointer.
                    In this case the corresponding size is queried with function Dem_Cfg_GlobalTimeSeriesFastBufferSize().
                  - as argument with corresponding size in an internal function. The internal function passes the pointer to destination buffer
                    and size without modifying to function Dem_Data_InitDestinationBuffer. The caller of the internal function ensures that pointer
                    and size of buffer are valid.
  \COUNTERMEASURE \R [CM_DEM_R_MEMORY_GET_ERECDATAPTR]
                  \R [CM_DEM_R_RINGBUFFER_NORMALRATEPTR]
                  \R [CM_DEM_R_RINGBUFFER_FASTRATEPTR]
                  \M [CM_DEM_M_SIZEOF_FAST_RATE_RINGBUFFER]
                  \M [CM_DEM_M_SIZEOF_NORMAL_RATE_RINGBUFFER]
                  \M [CM_DEM_M_SIZEOF_MEMORYENTRY_EXTENDEDDATA]

\ID SBSW_DEM_CALL_DIDCOPYINFO_INIT
  \DESCRIPTION    A pointer to a locally allocated DidCopyInfo structure is passed to Dem_DataReport_InitDidCopyInfo
                  for initialization. The DestinationBuffer structure is initialized before passing it to Dem_DataReport_InitDidCopyInfo.
                  If a pointer to a DestinationBuffer structure is received as argument the caller ensures that DestinationBuffer is initialized.
                  The remaining fields do not influence the write location by design (see also
                  SBSW_DEM_CALL_DESTINATIONBUFFER_INIT, SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER).
  \COUNTERMEASURE \R [CM_DEM_R_INIT_DESTINATIONBUFFER]

\ID SBSW_DEM_CALL_DIDSOURCEBUFFERREADINFO_INIT
  \DESCRIPTION    A pointer to a locally allocated DidSourceBufferReadInfo structure is passed to Dem_DataReport_InitDidSourceBufferReadInfo
                  for initialization. 
  \COUNTERMEASURE \N The pointer is always valid.

\ID SBSW_DEM_CALL_COLLECTDIDINFO_INIT
  \DESCRIPTION    A pointer to a locally allocated CollectDidInfo structure is passed to Dem_ExtDataElement_InitCollectDidInfo
                  for initialization. The DestinationBuffer structure is initialized before passing it to Dem_ExtDataElement_InitCollectDidInfo.
                  If a pointer to a DestinationBuffer structure is received as argument the caller ensures that DestinationBuffer is initialized.
                  The remaining fields do not influence the write location by design (see also
                  SBSW_DEM_CALL_DESTINATIONBUFFER_INIT, SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER).
  \COUNTERMEASURE \R [CM_DEM_R_INIT_DESTINATIONBUFFER]

\ID SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER
  \DESCRIPTION    A pointer to a DestinationBuffer structure is passed to a function expecting a valid pointer.
                  The pointer is allocated and initialized locally and thus it is always valid (see also
                  SBSW_DEM_CALL_DESTINATIONBUFFER_INIT).
  \COUNTERMEASURE \R [CM_DEM_R_INIT_DESTINATIONBUFFER]

\ID SBSW_DEM_POINTER_DESTINATIONBUFFER_SOURCEBUFFER
  \DESCRIPTION    A pointer to a DestinationBuffer structure and a source buffer is passed to a function expecting valid pointers.
                  The pointer to the Destination buffer is allocated and initialized locally and thus it is always valid (see also
                  SBSW_DEM_CALL_DESTINATIONBUFFER_INIT). The pointer to source buffer is a pointer to const. The called function
                  does not store its pointer parameter and it does not write through the pointer.
  \COUNTERMEASURE \R [CM_DEM_R_INIT_DESTINATIONBUFFER]

\ID SBSW_DEM_POINTER_LOCAL_DIDCOPYINFO
  \DESCRIPTION    A pointer to a DidCopyInfo structure is passed to a function expecting a valid DidCopyInfo. The pointer of the
                  DidCopyInfo is allocated and initialized locally and thus it is always valid (see also
                  SBSW_DEM_CALL_DIDCOPYINFO_INIT).
  \COUNTERMEASURE \R [CM_DEM_R_INIT_DIDCOPYINFO]

\ID SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO
  \DESCRIPTION    A pointer to a CollectDidInfo structure is passed to a function expecting a valid CollectDidInfo. The pointer
                  of the CollectDidInfo is allocated and initialized locally and thus it is always valid
                  (see also SBSW_DEM_CALL_COLLECTDIDINFO_INIT).
  \COUNTERMEASURE \R [CM_DEM_R_INIT_COLLECTDIDINFO]

\ID SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER
  \DESCRIPTION    A pointer to a DestinationBuffer structure of a DidCopyInfo is passed to a function expecting a valid
                  pointer. The pointer of the DidCopyInfo is allocated and initialized locally and thus it is always
                  valid (see also SBSW_DEM_CALL_DIDCOPYINFO_INIT).
  \COUNTERMEASURE \R [CM_DEM_R_INIT_DIDCOPYINFO]

\ID SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO_DESTINATIONBUFFER
  \DESCRIPTION    A pointer to a DestinationBuffer structure of a CollectDidInfo is passed to a function expecting a valid
                  pointer. The pointer of the CollectDidInfo is allocated and initialized locally and thus it is always
                  valid (see also SBSW_DEM_CALL_COLLECTDIDINFO_INIT).
  \COUNTERMEASURE \R [CM_DEM_R_INIT_COLLECTDIDINFO]

\ID SBSW_DEM_DESTINATIONBUFFER_WRITEINDEX
  \DESCRIPTION    The WriteIndex of a DestinationBuffer structure, received as pointer argument, is incremented or reset.
                  The caller is responsible that the pointer to the DestinationBuffer is valid
                  (see also SBSW_DEM_CALL_DESTINATIONBUFFER_INIT).
                  Modifying WriteIndex is valid.
  \COUNTERMEASURE \R [CM_DEM_R_CHECK_DESTINATIONBUFFER_WRITEINDEX]

\ID SBSW_DEM_WRITE_DESTINATIONBUFFER
  \DESCRIPTION    An amount of data is written into the buffer of a DestinationBuffer structure. (see also
                  SBSW_DEM_CALL_DESTINATIONBUFFER_INIT, SBSW_DEM_DESTINATIONBUFFER_WRITEINDEX).
  \COUNTERMEASURE \R [CM_DEM_R_CHECK_REMAINING_DESTINATIONBUFFER]

\ID SBSW_DEM_WRITE_DESTINATIONBUFFER_AT_INDEX
  \DESCRIPTION    One byte data is written into the buffer of a DestinationBuffer structure. (see also
                  SBSW_DEM_CALL_DESTINATIONBUFFER_INIT, SBSW_DEM_DESTINATIONBUFFER_WRITEINDEX).
  \COUNTERMEASURE \R [CM_DEM_R_CHECK_DESTINATIONBUFFER_WRITEPOSITION]

\ID SBSW_DEM_MEMSET_DESTINATIONBUFFER
  \DESCRIPTION    An amount of data is written into the buffer of a DestinationBuffer structure using memset. (see also
                  SBSW_DEM_CALL_DESTINATIONBUFFER_INIT, SBSW_DEM_DESTINATIONBUFFER_WRITEINDEX).
  \COUNTERMEASURE \R [CM_DEM_R_CHECK_REMAINING_DESTINATIONBUFFER]

\ID SBSW_DEM_CALL_DESTINATIONBUFFER
  \DESCRIPTION    An application callback is invoked to write data into the buffer of a DestinationBuffer structure.
                  The caller is responsible that buffer pointer and buffer length are correct (see also
                  SBSW_DEM_CALL_DESTINATIONBUFFER_INIT, SBSW_DEM_DESTINATIONBUFFER_WRITEINDEX).
  \COUNTERMEASURE \R [CM_DEM_R_CHECK_REMAINING_DESTINATIONBUFFER]
                  \R [CM_DEM_R_SIZEOF_DATAELEMENT_TABLE]
                  \R [CM_DEM_R_CHECK_DATAELEMENT_TYPE]
                  \S [CM_DEM_S_DATA_CALLBACK_FPTR]
                  \S [CM_DEM_S_CALL_DESTINATIONBUFFER]

\ID SBSW_DEM_POINTER_GLOBAL_SNAPSHOT_BUFFER
  \DESCRIPTION    A destination buffer pointer and buffer size is passed into a function that will write to the passed
                  memory area. The pointer argument is returned from Dem_MemoryEntry_GetGlobalSnapshotRecordDataPtr() which will always
                  return a valid pointer. The corresponding buffer size is received with function Dem_Cfg_GlobalSRecMaxRawSize().
  \COUNTERMEASURE \M [CM_DEM_M_SIZEOF_MEMORYENTRY_GLOBALSNAPSHOTDATA]

\ID SBSW_DEM_POINTER_SNAPSHOT_BUFFER
  \DESCRIPTION    A destination buffer pointer and buffer size is passed into a function that will write to the passed
                  memory area. The pointer argument is returned from Dem_MemoryEntry_GetSnapshotRecordDataPtr() which will always
                  return a valid pointer. The corresponding buffer size is received with function Dem_Cfg_EventSRecMaxRawSize().
  \COUNTERMEASURE \R [CM_DEM_R_MEMORY_GET_SRECDATAPTR]
                  \M [CM_DEM_M_SIZEOF_MEMORYENTRY_SNAPSHOTDATA]

\ID SBSW_DEM_POINTER_OBD_FREEZEFRAME_BUFFER
  \DESCRIPTION    A destination buffer pointer and buffer size is passed into a function that will write to the passed
                  memory area. The pointer argument is returned from Dem_Mem_FreezeFrameObdIIGetDataPtr() which will always
                  return a valid pointer. The corresponding buffer size is received with function Dem_Cfg_GlobalObdFreezeFrameMaxSize().
  \COUNTERMEASURE \R [CM_DEM_R_MEMORY_GET_OBDDATAPTR]
                  \M [CM_DEM_M_SIZEOF_FREEZEFRAME]

\ID SBSW_DEM_POINTER_J1939FREEZEFRAME_BUFFER
  \DESCRIPTION    A destination buffer pointer and buffer size is passed into a function that will write to the passed
                  memory area. The pointer argument is returned from Dem_MemoryEntry_GetJ1939FreezeFramePtr() which will always
                  return a valid pointer. The corresponding buffer size is received with function Dem_Cfg_GlobalJ1939FFTotalRawSize().
  \COUNTERMEASURE \M [CM_DEM_M_SIZEOF_MEMORYENTRY_J1939FREEZEFRAME]

\ID SBSW_DEM_POINTER_WWHOBDFREEZEFRAME_BUFFER
  \DESCRIPTION    A destination buffer pointer and buffer size is passed into a function that will write to the passed
                  memory area. The pointer argument is returned from Dem_MemoryEntry_GetWwhObdFreezeFrameDataPtr() which will always
                  return a valid pointer. The corresponding buffer size is received with function Dem_Cfg_GlobalWwhobdFreezeFrameDataSize().
  \COUNTERMEASURE \N The pointer is always valid.

\ID SBSW_DEM_POINTER_PRESTORAGE_GLOBAL_SNAPSHOT_BUFFER
  \DESCRIPTION    A destination buffer pointer and buffer size is passed into a function that will write to the passed
                  memory area. The pointer argument is returned from Dem_Prestore_PrestorageEntryGetGlobalSRecDataPtr()
                  which will always return a valid pointer. The corresponding buffer size is received with function
                  Dem_Cfg_GlobalSRecMaxRawSize().
  \COUNTERMEASURE \R [CM_DEM_R_PRESTORAGE_GET_GLOBALSRECPTR]
                  \M [CM_DEM_M_SIZEOF_PRESTORED_GLOBALSNAPSHOTDATA]
                  \M [CM_DEM_M_SIZEOF_PRESTORAGE]

\ID SBSW_DEM_POINTER_PRESTORAGE_SNAPSHOT_BUFFER
  \DESCRIPTION    A destination buffer pointer and buffer size is passed into a function that will write to the passed
                  memory area. The pointer argument is returned from Dem_Prestore_PrestorageEntryGetSRecDataPtr()
                  which will always return a valid pointer. The corresponding buffer size is received with function
                  Dem_Cfg_EventSRecMaxRawSize().
  \COUNTERMEASURE \R [CM_DEM_R_PRESTORAGE_GET_SRECPTR]
                  \M [CM_DEM_M_SIZEOF_PRESTORED_SNAPSHOT]
                  \M [CM_DEM_M_SIZEOF_PRESTORAGE]

\ID SBSW_DEM_POINTER_PRESTORAGE_OBD_FREEZEFRAME_BUFFER
  \DESCRIPTION    A destination buffer pointer and buffer size is passed into a function that will write to the passed
                  memory area. The pointer argument is returned from Dem_Prestore_PrestorageEntryGetObdIIFFDataPtr()
                  which will always return a valid pointer. The corresponding buffer size is received with function
                  Dem_Cfg_GlobalObdFreezeFrameMaxSize().
  \COUNTERMEASURE \R [CM_DEM_R_PRESTORAGE_GET_OBDFFPTR]
                  \M [CM_DEM_M_SIZEOF_PRESTORED_OBDFREEZEFRAME]
                  \M [CM_DEM_M_SIZEOF_PRESTORAGE]

\ID SBSW_DEM_POINTER_PRESTORAGE_J1939FREEZEFRAME_BUFFER
  \DESCRIPTION    A destination buffer pointer and buffer size is passed into a function that will write to the passed
                  memory area. The pointer argument is returned from Dem_Prestore_PrestorageEntryGetJ1939FFDataPtr()
                  which will always return a valid pointer. The corresponding buffer size is received with function
                  Dem_Cfg_GlobalJ1939FFTotalRawSize().
  \COUNTERMEASURE \R [CM_DEM_R_PRESTORAGE_GET_J1939FFPTR]
                  \M [CM_DEM_M_SIZEOF_PRESTORED_J1939FREEZEFRAME]
                  \M [CM_DEM_M_SIZEOF_PRESTORAGE]

\ID SBSW_DEM_POINTER_PRESTORAGE_WWHOBDFREEZEFRAME_BUFFER
  \DESCRIPTION    A destination buffer pointer and buffer size is passed into a function that will write to the passed
                  memory area. The pointer argument is returned from Dem_Prestore_PrestorageEntryGetWwhObdFFDataPtr()
                  which will always return a valid pointer. The corresponding buffer size is received with function
                  Dem_Cfg_GlobalPrestoredWwhobdFreezeFrameDataSize().
  \COUNTERMEASURE \R [CM_DEM_R_PRESTORAGE_GET_WWHOBDFFPTR]
                  \M [CM_DEM_M_SIZEOF_PRESTORAGE]

\ID SBSW_DEM_POINTER_WRITE_TIMESERIESENTRY
  \DESCRIPTION    In an internal function, data is written through a pointer to a time series entry, or the pointer is
                  passed to a function expecting a valid reference to a time series entry.
                  The memory entry pointer is initialized by Dem_Memory_TimeSeries_GetEntrySafe which will always return a pointer
                  to a valid time series entry.
  \COUNTERMEASURE \R [CM_DEM_R_TIMESERIES_GET_ENTRY]
                  \M [CM_DEM_M_TIMESERIESINDEX_LIMITS]
                  \M [CM_DEM_M_SIZEOF_MEMORYDATAPTR]
                  \S [CM_DEM_S_TIMESERIESINDEX_TYPE]

\ID SBSW_DEM_POINTER_WRITE_TIMESERIESENTRYCOMPANION
  \DESCRIPTION    In an internal function, data is written through a pointer to a time series entry companion, or the pointer is
                  passed to a function expecting a valid reference to a time series entry companion.
                  The memory entry pointer is initialized by Dem_Memory_TimeSeries_GetEntryCompanionSafe which will always return a pointer
                  to a valid time series entry companion.
  \COUNTERMEASURE \R [CM_DEM_R_TIMESERIES_GET_ENTRY_COMPANION]
                  \M [CM_DEM_M_TIMESERIESENTRYCOMPANIONINDEX_LIMITS]

\ID SBSW_DEM_POINTER_TIMESERIESENTRY_NORMALBUFFER
  \DESCRIPTION    A destination buffer pointer and buffer size is passed into a function that will write to the passed
                  memory area.
                  The pointer argument is returned from Dem_Memory_TimeSeries_EntryManager_GetNormalDataPtr() which will always
                  return a valid pointer. The corresponding buffer size is received with function
                  Dem_Cfg_EventSRecMaxRawSize().
  \COUNTERMEASURE \R [CM_DEM_R_TIMESERIES_GET_NORMALDATAPTR]
                  \R [CM_DEM_R_TIMESERIES_GET_DATAPTR]
                  \M [CM_DEM_M_SIZEOF_SERIESENTRY_NORMAL_SNAPSHOTDATA]
                  \M [CM_DEM_M_SIZEOF_SERIESENTRY_SNAPSHOTDATA]

\ID SBSW_DEM_POINTER_TIMESERIESENTRY_FASTBUFFER
  \DESCRIPTION    A destination buffer pointer and buffer size is passed into a function that will write to the passed
                  memory area.
                  The pointer argument is returned from Dem_Memory_TimeSeries_EntryManager_GetFastDataPtr() which will always
                  return a valid pointer. The corresponding buffer size is received with function
                  Dem_Cfg_EventSRecMaxRawSize().
  \COUNTERMEASURE \R [CM_DEM_R_TIMESERIES_GET_FASTDATAPTR]
                  \R [CM_DEM_R_TIMESERIES_GET_DATAPTR]
                  \M [CM_DEM_M_SIZEOF_SERIESENTRY_FAST_SNAPSHOTDATA]
                  \M [CM_DEM_M_SIZEOF_SERIESENTRY_SNAPSHOTDATA]

\ID SBSW_DEM_CALL_SYNC_COMPARE_AND_SWAP
  \DESCRIPTION    A function passes a pointer with new value to be set to function Dem_Com_SyncCompareAndSwap().
                  Pointer and value to be set have same data type. Dem_Com_SyncCompareAndSwap() only sets passed
                  value at passed pointer position. Caller of function ensures that pointer is valid.
  \COUNTERMEASURE \R [CM_DEM_R_WORDPOSITION_CHECK]

\ID SBSW_DEM_WRITE_SATELLITEINFO_MAXDEBOUNCE_VALUE
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_SatelliteInfoType<X>.MaxDebounceValues[] using
                  a pointer to Dem_Cfg_SatelliteInfoType<X> and function argument monitor id as index. The pointer is accessed 
                  by a function like macro that returns a valid pointer to a global variable or NULL_PTR. In a multi satellite configuration the 
                  pointer is taken from the Dem_Cfg_SatelliteInfo table.
  \COUNTERMEASURE \R [CM_DEM_R_SATELLITE_INDEX]
                  \R [CM_DEM_R_MAXDEBOUNCE_VALUE_INDEX]
                  \R [CM_DEM_R_SATELLITE_NULLPTR]
                  \R [CM_DEM_R_APPLICATIONID_CHECK]
                  \S [CM_DEM_S_SIZEOF_SATELLITEINFOTYPE_ARRAYS]
                  \S [CM_DEM_S_MEMMAP_SATELLITEINFO]
                  \S [CM_DEM_S_CHECK_OSAPPLICATION_IN_SATELLITEINFOTABLE]

\ID SBSW_DEM_WRITE_SATELLITEINFO_SATELLITEDATA
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_SatelliteInfoType<X>.SatelliteData[] using
                  a pointer to Dem_Cfg_SatelliteInfoType<X> and function argument monitor id as index. The pointer
                  references a global variable and is always valid. In a multi satellite configuration the pointer is
                  taken from the Dem_Cfg_SatelliteInfo table.
  \COUNTERMEASURE \R [CM_DEM_R_SATELLITE_INDEX]
                  \R [CM_DEM_R_SATELLITEDATA_INDEX]
                  \R [CM_DEM_R_APPLICATIONID_CHECK]
                  \S [CM_DEM_S_SIZEOF_SATELLITEINFOTYPE_ARRAYS]
                  \S [CM_DEM_S_MEMMAP_SATELLITEINFO]
                  \S [CM_DEM_S_CHECK_OSAPPLICATION_IN_SATELLITEINFOTABLE]

\ID SBSW_DEM_WRITE_SATELLITEINFO_SATELLITE_EXTENDEDDATA
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_SatelliteInfoType<X>.SatelliteExtendedData[] using
                  a pointer to Dem_Cfg_SatelliteInfoType<X> and function argument monitor id as index. The pointer is accessed 
                  by a function like macro that returns a valid pointer to a global variable or NULL_PTR. In a multi satellite configuration the pointer is
                  taken from the Dem_Cfg_SatelliteInfo table.
  \COUNTERMEASURE \R [CM_DEM_R_SATELLITE_INDEX]
                  \R [CM_DEM_R_SATELLITE_EXTENDEDDATA_INDEX]
                  \R [CM_DEM_R_SATELLITE_NULLPTR]
                  \R [CM_DEM_R_APPLICATIONID_CHECK]
                  \S [CM_DEM_S_SIZEOF_SATELLITEINFOTYPE_ARRAYS]
                  \S [CM_DEM_S_MEMMAP_SATELLITEINFO]
                  \S [CM_DEM_S_CHECK_OSAPPLICATION_IN_SATELLITEINFOTABLE]

\ID SBSW_DEM_WRITE_SATELLITEINFO
  \DESCRIPTION    In a function, data is written through a pointer to Dem_Cfg_SatelliteInfoType<X>. The pointer references
                  a member of the global struct variable Dem_Cfg_SatelliteInfoType<X> and therefore is always valid. In a multi
                  satellite configuration the pointer is taken from the Dem_Cfg_SatelliteInfo table.
  \COUNTERMEASURE \R [CM_DEM_R_SATELLITE_INDEX]
                  \R [CM_DEM_R_APPLICATIONID_CHECK]
                  \S [CM_DEM_S_MEMMAP_SATELLITEINFO]
                  \S [CM_DEM_S_SIZEOF_SATELLITEINFOTYPE_POINTER]
                  \S [CM_DEM_S_CHECK_OSAPPLICATION_IN_SATELLITEINFOTABLE]

\ID SBSW_DEM_WRITE_SATELLITEINFO_OPTIONAL_MEMBER
  \DESCRIPTION    In a function, data is written through a pointer to Dem_Cfg_SatelliteInfoType<X>. The pointer references
                  an optional member of the global struct variable Dem_Cfg_SatelliteInfoType<X>. The pointer is accessed by a function
                  like macro that returns a reference to a member of the global struct variable Dem_Cfg_SatelliteInfoType<X>
                  or the NULL_PTR. In a multi satellite configuration the pointer is taken 
                  from the Dem_Cfg_SatelliteInfo table.
  \COUNTERMEASURE \R [CM_DEM_R_SATELLITE_INDEX]
                  \R [CM_DEM_R_SATELLITE_NULLPTR]
                  \R [CM_DEM_R_APPLICATIONID_CHECK]
                  \S [CM_DEM_S_MEMMAP_SATELLITEINFO]
                  \S [CM_DEM_S_SIZEOF_SATELLITEINFOTYPE_POINTER]
                  \S [CM_DEM_S_CHECK_OSAPPLICATION_IN_SATELLITEINFOTABLE]

\ID SBSW_DEM_CALL_SYNC_COMPARE_AND_SWAP_SATELLITEINFO
  \DESCRIPTION    A function passes a pointer and a new value to be set to function Dem_Com_SyncCompareAndSwap().
                  Pointer and value to be set have the same data type. Dem_Com_SyncCompareAndSwap() only sets the passed value at the passed
                  pointer position. The pointer references a member of the global struct variable Dem_Cfg_SatelliteInfoType<X> and
                  therefore is always valid. In a multi satellite configuration the pointer is taken from the Dem_Cfg_SatelliteInfo table.
  \COUNTERMEASURE \R [CM_DEM_R_SATELLITE_INDEX]
                  \R [CM_DEM_R_APPLICATIONID_CHECK]
                  \S [CM_DEM_S_MEMMAP_SATELLITEINFO]
                  \S [CM_DEM_S_SIZEOF_SATELLITEINFOTYPE_POINTER]
                  \S [CM_DEM_S_CHECK_OSAPPLICATION_IN_SATELLITEINFOTABLE]

\ID SBSW_DEM_CALL_SYNC_COMPARE_AND_SWAP_SATELLITEDATA
  \DESCRIPTION    A function passes a pointer to an element in array Dem_Cfg_SatelliteInfoType<X>.SatelliteData[] and a new value to be
                  set to function Dem_Com_SyncCompareAndSwap(). Pointer and value to be set have the same data type. Dem_Com_SyncCompareAndSwap()
                  only sets the passed value at the passed pointer position. The pointer references a member of the global struct variable
                  Dem_Cfg_SatelliteInfoType<X> and therefore is always valid. In a multi satellite configuration the pointer is taken
                  from the Dem_Cfg_SatelliteInfo table.
  \COUNTERMEASURE \R [CM_DEM_R_SATELLITE_INDEX]
                  \R [CM_DEM_R_SATELLITEDATA_INDEX]
                  \R [CM_DEM_R_APPLICATIONID_CHECK]
                  \S [CM_DEM_S_SIZEOF_SATELLITEINFOTYPE_ARRAYS]
                  \S [CM_DEM_S_MEMMAP_SATELLITEINFO]
                  \S [CM_DEM_S_CHECK_OSAPPLICATION_IN_SATELLITEINFOTABLE]

\ID SBSW_DEM_CALL_SYNC_COMPARE_AND_SWAP_SATELLITE_EXTENDEDDATA
  \DESCRIPTION    A function passes a pointer to an element in array Dem_Cfg_SatelliteInfoType<X>.SatelliteExtendedData[] and a new value to be
                  set to function Dem_Com_SyncCompareAndSwap(). Pointer and value to be set have the same data type. Dem_Com_SyncCompareAndSwap()
                  only sets the passed value at the passed pointer position. The pointer is accessed by a function like macro that returns a 
                  valid pointer to a member of the global struct variable Dem_Cfg_SatelliteInfoType<X> or NULL_PTR. In a multi 
                  satellite configuration the pointer is taken from the Dem_Cfg_SatelliteInfo table.
  \COUNTERMEASURE \R [CM_DEM_R_SATELLITE_INDEX]
                  \R [CM_DEM_R_SATELLITE_EXTENDEDDATA_INDEX]
                  \R [CM_DEM_R_SATELLITE_NULLPTR]
                  \R [CM_DEM_R_APPLICATIONID_CHECK]
                  \S [CM_DEM_S_SIZEOF_SATELLITEINFOTYPE_ARRAYS]
                  \S [CM_DEM_S_MEMMAP_SATELLITEINFO]
                  \S [CM_DEM_S_CHECK_OSAPPLICATION_IN_SATELLITEINFOTABLE]

\ID SBSW_DEM_CALL_FOREACH_COMBINED_EVENT
  \DESCRIPTION    A function passes a function pointer and argument struct to Dem_DTC_ForEachCombinedSubEvent. The function
                  is a function label, as such it is always valid. The argument struct is a reference to a local stack
                  variable.
  \COUNTERMEASURE \N The pointers are always valid.

\ID SBSW_DEM_CALL_OPERATION_FOR_EVENT
  \DESCRIPTION    A function passes pointer to a function implementing an event specific operation and pointer to a structure
                  for handling function arguments to Dem_DTC_ProcessOperation.
                  The function pointer is derived from a function label, as such it is always valid. The argument struct
                  is a reference to a local stack variable.
  \COUNTERMEASURE \N The pointers are always valid.

\ID SBSW_DEM_CALL_DTCFILTER_FPTR
  \DESCRIPTION    A function calls the function pointer retrieved using the function Dem_FilterData_GetDTCFilterFunction.
                  This function always returns a valid function pointer.
                  A memory info pointer is passed as argument to the function pointer. The pointer is initialized with
                  Dem_MemState_MemoryInfoInit. As Dem_MemState_MemoryInfoInit returns a pointer to a global
                  variable, the memory info pointer is always valid.
  \COUNTERMEASURE \N The pointers are always valid.

\ID SBSW_DEM_MEMCOPY_MEMORY_DATA
  \DESCRIPTION    A function copies data into Dem_Cfg_CommitBuffer using memcopy.
  \COUNTERMEASURE \R [CM_DEM_R_MEMORYDATA_INDEX]
                  \R [CM_DEM_R_SIZEOF_COMMITBUFFER]
                  \M [CM_DEM_M_SIZEOF_MEMORYDATAPTR]
                  \S [CM_DEM_S_CHECK_NVBLOCK_LENGTH]
                  \S [CM_DEM_M_SIZEOF_MEMORYBLOCKID]
                  \S [CM_DEM_M_SIZEOF_MEMORYDATASIZE]

\ID SBSW_DEM_ARRAY_WRITE_ADMINDATA_CYCLECOUNTER
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_AdminData.CycleCounter[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEM_CFG_ADMINDATA_CYCLECOUNTER_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_ADMINDATA_CYCLECOUNTER]

\ID SBSW_DEM_ARRAY_WRITE_STATUSDATA_EVENTSTATUS
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_StatusData.EventStatus[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEM_CFG_STATUSDATA_EVENTSTATUS_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_STATUSDATA_EVENTSTATUS]

\ID SBSW_DEM_ARRAY_WRITE_STATUSDATA_STATE
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_StatusData.State[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEM_CFG_STATUSDATA_STATE_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_STATUSDATA_STATE]

\ID SBSW_DEM_ARRAY_WRITE_STATUSDATA_TRIPCOUNT
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_StatusData.TripCount[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEM_CFG_STATUSDATA_TRIPCOUNT_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_STATUSDATA_TRIPCOUNT]

\ID SBSW_DEM_ARRAY_WRITE_STATUSDATA_MILGROUPTRIPCOUNT
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_StatusData.MilGroupTripCount[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEM_CFG_STATUSDATA_MILGROUPTRIPCOUNT_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_STATUSDATA_MILGROUPTRIPCOUNT]

\ID SBSW_DEM_ARRAY_WRITE_STATUSDATA_MILGROUPACTIVEEVENTS
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_StatusData.MilGroupActiveEvents[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEM_CFG_STATUSDATA_MILGROUPACTIVEEVENTS_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_STATUSDATA_MILGROUPACTIVEEVENTS]

\ID SBSW_DEM_ARRAY_WRITE_STATUSDATA_CONFIRMEDCHRONOLOGY
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_StatusData.ConfirmedChronology[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEM_CFG_STATUSDATA_CONFIRMEDCHRONOLOGY_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_STATUSDATA_CONFIRMEDCHRONOLOGY]

\ID SBSW_DEM_ARRAY_WRITE_STATUSDATA_EXTENDEDEVENTSTATUS
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_StatusData.ExtendedEventStatus[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEM_CFG_STATUSDATA_EXTENDEDEVENTSTATUS_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_STATUSDATA_EXTENDEDEVENTSTATUS]

\ID SBSW_DEM_ARRAY_WRITE_FREEZEFRAMEDATA
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_FreezeFrameData[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEM_CFG_FREEZEFRAMEDATA_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_FREEZEFRAME]

\ID SBSW_DEM_ARRAY_WRITE_PERMANENTDATA_PERMANENTDATAENTRY
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_PermanentData.PermanentDataEntry[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEM_CFG_PERMANENTDATA_PERMANENTDATAENTRY_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_PERMANENT_PERMANENTDATAENTRY]

\ID SBSW_DEM_ARRAY_WRITE_DTRDATA_TESTVALUE
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_DtrData.TestValue[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEM_CFG_DTRDATA_TESTVALUE_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_DTRDATA]

 \ID SBSW_DEM_ARRAY_WRITE_DTRDATA_LOWLIMVALUE
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_DtrData.LowLimValue[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEM_CFG_DTRDATA_LOWLIMVALUE_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_DTRDATA]

\ID SBSW_DEM_ARRAY_WRITE_DTRDATA_UPPLIMVALUE
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_DtrData.UppLimValue[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEM_CFG_DTRDATA_UPPLIMVALUE_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_DTRDATA]

\ID SBSW_DEM_ARRAY_WRITE_OBDIUMPRDATA_DENOMINATOR
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_ObdIumprData.Denominator[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEM_CFG_OBDIUMPRDATA_DENOMINATOR_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_OBDIUMPRDATA]

\ID SBSW_DEM_ARRAY_WRITE_OBDIUMPRDATA_STATUS
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_ObdIumprData.Status[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEM_CFG_OBDIUMPRDATA_STATUS_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_OBDIUMPRDATA]

\ID SBSW_DEM_ARRAY_WRITE_OBDIUMPRDATA_NUMERATOR
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_ObdIumprData.Numerator[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEM_CFG_OBDIUMPRDATA_NUMERATOR_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_OBDIUMPRDATA]

\ID SBSW_DEM_ARRAY_POINTER_READOUTBUFFER
  \DESCRIPTION    In a function, data is written through a pointer to array Dem_Cfg_ReadoutBuffer[] using a function argument as index.
                  The pointer is initialized using Dem_DTCReadoutBuffer_GetReadoutBufferSafe() which will always return a pointer
                  to a valid readout buffer entry.
  \COUNTERMEASURE \R [CM_DEM_R_READOUTBUFFER_GET_ENTRY]

\ID SBSW_DEM_ARRAY_POINTER_READOUTBUFFER_READOUTBUFFERDATA
  \DESCRIPTION    In a function, data is written through a pointer to inner array Dem_Cfg_ReadoutBuffer[].ReadOutBufferData[] using function
                  arguments as indexes. It is verified that both indexes are within bounds before writing to the inner array.
  \COUNTERMEASURE \R [CM_DEM_R_GET_READOUTBUFFER_READOUTBUFFERDATA]
                  \M [CM_DEM_M_SIZEOF_READOUTBUFFER_READOUTBUFFERDATA]

\ID SBSW_DEM_ARRAY_POINTER_FILTERDATA
  \DESCRIPTION    In a function, data is written through a pointer to array Dem_Cfg_FilterInfoTable[] using a function argument as index.
                  The pointer is initialized using Dem_Client_FilterData_GetFilterDataPtrSafe() which will always return a pointer
                  to a valid readout buffer entry.
  \COUNTERMEASURE \R [CM_DEM_R_GET_FILTERDATA]

\ID SBSW_DEM_ARRAY_POINTER_READOUTBUFFER_CSL
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_ReadoutBuffer[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_POINTER_DTCSELECTORTABLE
  \DESCRIPTION    In a function, data is written through a pointer to array Dem_Cfg_DTCSelectorTable[]. The pointer is
                  retrieved using a function argument as index. The runtime check ensures that data is not written to array
                  Dem_Cfg_DTCSelectorTable[] when index is invalid.
  \COUNTERMEASURE \R [CM_DEM_R_DTCSELECTORTABLE_GET_ENTRY]

\ID SBSW_DEM_ARRAY_WRITE_EVENTINTERNALSTATUS
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_EventInternalStatus[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_MEMSET_EVENTINTERNALSTATUS
  \DESCRIPTION    Dem_Cfg_EventInternalStatus[] is initialized using memset. The array size is multiplied with the array base
                  size type to make sure the initialized memory area is correct.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_EVENTCYCLESTATUS
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_EventCycleStatus[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_COMBINEDGROUPSTATUS
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_CombinedGroupStatus[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_COMBINEDGROUPINTERNALSTATUS
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_CombinedGroupInternalStatus[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_CLEARDTCTABLE
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_ClearDTCTable[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_DTCSELECTORTABLE
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_DTCSelectorTable[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_FILTERINFOTABLE
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_FilterInfoTable[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_FREEZEFRAMEITERATORTABLE
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_FreezeFrameIteratorTable[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

  \ID SBSW_DEM_ARRAY_WRITE_EXTENDEDDATARECORDITERATORTABLE
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_ExtendedDataRecordIteratorTable[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_ENABLECONDITIONFULFILLED
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_EnableConditionFulfilled[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_ENABLECONDITIONGROUPSTATE
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_EnableConditionGroupState[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_ENABLECONDITIONGROUPCOUNTER
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_EnableConditionGroupCounter[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_STORAGECONDITIONGROUPCOUNTER
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_StorageConditionGroupCounter[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_POINTER_WRITE_MEMORYENTRY
  \DESCRIPTION    In a function, data is written through a pointer stored in the table Dem_Cfg_MemoryEntry[]. The pointer is retrieved 
                  from the table using function Dem_MemoryEntry_GetEntry() which uses Comstack lib to ensure that content from a valid 
                  index is always returned. The safety manual entry ensures that the pointer stored in Dem_Cfg_MemoryEntry(), which 
                  is retrieved through Dem_Cfg_GetMemoryEntry() is always valid.
  \COUNTERMEASURE \S [CM_DEM_S_CHECK_MEMORYENTRYTABLE]

\ID SBSW_DEM_ARRAY_WRITE_STORAGECONDITIONFULFILLED
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_StorageConditionFulfilled[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_DTRSTATUS
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_DtrStatus[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_OBDIUMPRRUPDATEPENDING
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_ObdIumprUpdatePending[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_DEBOUNCEDATA
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_DebounceData[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_DEBOUNCEDATA_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_DEBOUNCEDATA]

\ID SBSW_DEM_MEMSET_DEBOUNCEDATA
  \DESCRIPTION    Dem_Cfg_DebounceData[] is initialized using memset. The array size is multiplied with the array base
                  size type to make sure the initialized memory area is correct.
  \COUNTERMEASURE \M [CM_DEM_M_SIZEOF_DEBOUNCEDATA]

\ID SBSW_DEM_MEMSET_ENABLECONDITIONGROUPCOUNTER
  \DESCRIPTION    Dem_Cfg_EnableConditionGroupCounter[] is initialized using memset. The array size is multiplied with the array base
                  size type to make sure the initialized memory area is correct.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_MEMSET_ENABLECONDITIONGROUPSTATE
  \DESCRIPTION    Dem_Cfg_EnableConditionGroupState[] is initialized using memset. The array size is multiplied with the array base
                  size type to make sure the initialized memory area is correct.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_MEMSET_STORAGECONDITIONGROUPCOUNTER
  \DESCRIPTION    Dem_Cfg_StorageConditionGroupCounter[] is initialized using memset. The array size is multiplied with the array base
                  size type to make sure the initialized memory area is correct.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_MEMSET_DTRSTATUS
  \DESCRIPTION    Dem_Cfg_DtrStatus[] is initialized using memset. The array size is multiplied with the array base
                  size type to make sure the initialized memory area is correct.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_MEMSET_AGINGDATA_AGINGCOUNTER
  \DESCRIPTION    Dem_Cfg_AgingData.AgingCounter[] is initialized using memset. The array size is multiplied with the array base
                  size type to make sure the initialized memory area is correct.
  \COUNTERMEASURE \M [CM_DEM_M_SIZEOF_AGINGDATA_AGINGCOUNTER]

\ID SBSW_DEM_MEMSET_AGINGDATA_AGEDCOUNTER
  \DESCRIPTION    Dem_Cfg_AgingData.AgedCounter[] is initialized using memset. The array size is multiplied with the array base
                  size type to make sure the initialized memory area is correct.
  \COUNTERMEASURE \M [CM_DEM_M_SIZEOF_AGINGDATA_AGEDCOUNTER]

  \ID SBSW_DEM_MEMSET_CYCLECOUNTERDATA_FAULTPENDINGCOUNTER
  \DESCRIPTION    Dem_Cfg_CycleCounterData.FaultPendingCounter[] is initialized using memset. The array size is multiplied with 
  the array base size type to make sure the initialized memory area is correct.
  \COUNTERMEASURE \M [CM_DEM_M_SIZEOF_CYCLECOUNTERDATA_FAULTPENDINGCOUNTER]

  \ID SBSW_DEM_MEMSET_CYCLECOUNTERDATA_FAILEDCYCLECOUNTER
  \DESCRIPTION    Dem_Cfg_CycleCounterData.FailedCycleCounter[] is initialized using memset. The array size is multiplied with 
  the array base size type to make sure the initialized memory area is correct.
  \COUNTERMEASURE \M [CM_DEM_M_SIZEOF_CYCLECOUNTERDATA_FAILEDCYCLECOUNTER]

\ID SBSW_DEM_ARRAY_WRITE_EVENTAVAILABLEDATA
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_EventAvailableData[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_AVAILABLEDATA_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_EVENTAVAILABLEDATA]

\ID SBSW_DEM_MEMSET_EVENTAVAILABLEDATA
  \DESCRIPTION    Dem_Cfg_EventAvailableData[] is initialized using memset. The array size is multiplied with the array base
                  size type to make sure the initialized memory area is correct.
  \COUNTERMEASURE \M [CM_DEM_M_SIZEOF_EVENTAVAILABLEDATA]

\ID SBSW_DEM_ARRAY_WRITE_PRESTORAGEINDEX
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_PrestorageIndex[] using a configured index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_PRESTORAGE
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_Prestorage[] using a function argument as index.
  \COUNTERMEASURE \R [CM_DEM_R_PRESTORAGE_CHECK]
                  \M [CM_DEM_M_SIZEOF_PRESTORAGE]

\ID SBSW_DEM_ARRAY_WRITE_EVENTDATACOMMITNUMBER
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_EventDataCommitNumber[] using an index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_MEMSET_EVENTDATACOMMITNUMBER
  \DESCRIPTION    Dem_Cfg_EventDataCommitNumber[] is initialized using memset. The array size is multiplied with the array base
                  size type to make sure the initialized memory area is correct.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_TIMESERIESENTRYCOMPANION
  \DESCRIPTION    In a function, data is written to address of array Dem_Cfg_TimeSeriesEntryCompanion[] using an index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_ARRAY_WRITE_MEMORYCHRONOLOGY
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_PrimaryChronology[], Dem_Cfg_SecondaryChronology[] or
                  Dem_Cfg_TimeSeriesChronology[] using a function argument as index. A valid MemoryInfo structure must
                  be provided by the caller (see also SBSW_DEM_CALL_MEMORYINFO_POINTER).
  \COUNTERMEASURE \R [CM_DEM_R_MEMORYCHRONOLOGY_INDEX_CHECK]
                  \R [CM_DEM_R_CHRONOLOGY_NULLPTR]
                  \M [CM_DEM_M_SIZEOF_PRIMARYCHRONOLOGY]
                  \M [CM_DEM_M_SIZEOF_SECONDARYCHRONOLOGY]
                  \M [CM_DEM_M_SIZEOF_TIMESERIES_CHRONOLOGY]

\ID SBSW_DEM_ARRAY_WRITE_INDICATORCONTINUOUS
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_IndicatorContinuous[][] using function arguments as indices.
  \COUNTERMEASURE \R [CM_DEM_R_INDICATORCONTINUOUS_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_INDICATORCONTINUOUS]

\ID SBSW_DEM_ARRAY_WRITE_INDICATORBLINKING
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_IndicatorBlinking[][] using function arguments as indices.
  \COUNTERMEASURE \R [CM_DEM_R_INDICATORBLINKING_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_INDICATORBLINKING]

\ID SBSW_DEM_ARRAY_WRITE_INDICATORFASTFLASH
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_IndicatorFastFlash[][] using function arguments as indices.
  \COUNTERMEASURE \R [CM_DEM_R_INDICATORFASTFLASH_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_INDICATORFASTFLASH]

\ID SBSW_DEM_ARRAY_WRITE_INDICATORSLOWFLASH
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_IndicatorFastFlash[][] using function arguments as indices.
  \COUNTERMEASURE \R [CM_DEM_R_INDICATORFASTSLOWFLASH_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_INDICATORSLOWFLASH]

\ID SBSW_DEM_ARRAY_WRITE_QUALIFIEDACTIVEEVENTCOUNT
  \DESCRIPTION    In a function, data is written to array Dem_Esm_QualifiedActiveEventCount[] using function arguments as indices.
                  The array Dem_Esm_QualifiedActiveEventCount[] has constant size.
  \COUNTERMEASURE \R [CM_DEM_R_QUALIFIEDACTIVEEVENTCOUNT_INDEX_CHECK]

\ID SBSW_DEM_ARRAY_WRITE_DTCCLASSMILCOUNT
  \DESCRIPTION    In a function, data is written to array Dem_Esm_DtcClassMILCount[] using function arguments as indices.
                  The array Dem_Esm_DtcClassMILCount[] has constant size.
  \COUNTERMEASURE \R [CM_DEM_R_DTCCLASSMILCOUNT_INDEX_CHECK]

\ID SBSW_DEM_ARRAY_WRITE_SUPPORTEDMIDMASK
  \DESCRIPTION    In a function, data is written to array Dem_MidLookup_SupportedMidMask[] using function arguments as indices.
                  The array Dem_MidLookup_SupportedMidMask[] has constant size.
  \COUNTERMEASURE \R [CM_DEM_R_SUPPORTEDMIDMASK_INDEX_CHECK]

\ID SBSW_DEM_ARRAY_WRITE_PROCESSEDCOMBINEDDTCGROUP
  \DESCRIPTION    In a function, data is written to an array of type Dem_Cfg_ProcessedCombinedDTCGroupType using function
                  arguments as indices. The array of type Dem_Cfg_ProcessedCombinedDTCGroupType has constant size.
  \COUNTERMEASURE \R [CM_DEM_R_PROCESSEDCOMBINEDDTCGROUP_INDEX_CHECK]
                  \S [CM_DEM_S_SIZEOF_PROCESSEDCOMBINEDDTCGROUP]

\ID SBSW_DEM_ARRAY_WRITE_GLOBALINDICATORSTATES
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_GlobalIndicatorStates[][] using function arguments as indices.
                  The ComStackLib guarantees that the IndicatorId received as a function argument is within range.
  \COUNTERMEASURE \R [CM_DEM_R_GLOBALINDICATORSTATES_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_GLOBALINDICATORSTATES]

\ID SBSW_DEM_ARRAY_WRITE_REPORTEDEVENTSOFFILTER
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_ReportedEventsOfFilter[][] using function arguments as indices.
                  The ComStackLib guarantees that the size of the outer array Dem_Cfg_ReportedEventsOfFilter[] is correctly
                  returned by the GetSize access macro.
  \COUNTERMEASURE \R [CM_DEM_R_REPORTEDEVENTSOFFILTER_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_REPORTEDEVENTSOFFILTER]

\ID SBSW_DEM_ARRAY_WRITE_MEMORYSTATUS
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_MemoryStatus[] using a function argument as index.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_MEMSET_MEMORYSTATUS
  \DESCRIPTION    Dem_Cfg_MemoryStatus[] is initialized using memset. The array size is multiplied with the array base
                  size type to make sure the initialized memory area is correct.
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_DEM_WRITE_MEMENTRY_STDENVDATA
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_PrimaryEntryType.StdEnvData[] using function arguments as index
                  to StdEnvData and a pointer to a memory entry. The pointer is initialized using Dem_MemoryEntry_GetEntry() and is
                  always valid (see also SBSW_DEM_POINTER_WRITE_MEMORYENTRY).
  \COUNTERMEASURE \R [CM_DEM_R_MEMENTRY_STDENVDATA_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_STDENVDATA]

\ID SBSW_DEM_CLEARALLOWED_FPTR
  \DESCRIPTION    In a function, a configured function pointer is dereferenced. The configured function writes only a byte to the 
                  passed pointer. The dereferenced function expects a valid pointer argument and does not store the passed pointer. 
                  A pointer to a local stack variable is passed to the dereferenced function, so the pointer argument is always valid.
  \COUNTERMEASURE \R [CM_DEM_R_CLEAR_EVENT_ALLOWED_INDEX]
                  \R [CM_DEM_R_OPTIONAL_CALLBACK]
                  \S [CM_DEM_S_CLEAR_EVENT_ALLOWED_FPTR]
                  \S [CM_DEM_S_CALL_EXTERNAL_FUNCTIONTABLE_WRITE_DATAPTR]

\ID SBSW_DEM_INITMONITORFOREVENT_FPTR
  \DESCRIPTION    In a function, a configured function pointer is dereferenced.
  \COUNTERMEASURE \R [CM_DEM_R_INIT_MONITOR_FOR_EVENT_INDEX]
                  \R [CM_DEM_R_OPTIONAL_CALLBACK]
                  \S [CM_DEM_S_INIT_MONITOR_FOR_EVENT_FPTR]

\ID SBSW_DEM_INITMONITORFORFUNCTION_FPTR
  \DESCRIPTION    In a function, a configured function pointer is dereferenced.
  \COUNTERMEASURE \R [CM_DEM_R_OPTIONAL_CALLBACK]
                  \S [CM_DEM_S_INIT_MONITOR_FOR_FUNCTION_FPTR]

\ID SBSW_DEM_GLOBALCBKDTCSTATUS_FPTR
  \DESCRIPTION    In a function, a configured function pointer is dereferenced.
  \COUNTERMEASURE \R [CM_DEM_R_OPTIONAL_CALLBACK]
                  \S [CM_DEM_S_GLOBAL_CBK_DTC_STATUS_FPTR]

\ID SBSW_DEM_GLOBALCBKJ1939DTCSTATUS_FPTR
  \DESCRIPTION    In a function, a configured function pointer is dereferenced.
  \COUNTERMEASURE \R [CM_DEM_R_OPTIONAL_CALLBACK]
                  \S [CM_DEM_S_GLOBAL_CBK_J1939_DTC_STATUS_FPTR]

\ID SBSW_DEM_EVENTCBKSTATUS_FPTR
  \DESCRIPTION    In a function, a configured function pointer is dereferenced.
  \COUNTERMEASURE \R [CM_DEM_R_OPTIONAL_CALLBACK]
                  \S [CM_DEM_S_EVENT_CBK_STATUS_FPTR]

\ID SBSW_DEM_EVENTCBKDATA_FPTR
  \DESCRIPTION    In a function, a configured function pointer is dereferenced.
  \COUNTERMEASURE \R [CM_DEM_R_OPTIONAL_CALLBACK]
                  \S [CM_DEM_S_EVENT_CBK_DATA_FPTR]

\ID SBSW_DEM_EVENTCBKGETFDC_FPTR
  \DESCRIPTION    In a function, a configured function pointer is dereferenced. The configured function writes only a byte to the 
                  passed pointer. The dereferenced function expects a valid pointer argument and does not store the passed pointer. 
                  A pointer to a local stack variable is passed to the dereferenced function, so the pointer argument is always valid.
  \COUNTERMEASURE \R [CM_DEM_R_EVENT_CALLBACK_GET_FDC_INDEX]
                  \R [CM_DEM_R_OPTIONAL_CALLBACK]
                  \S [CM_DEM_S_EVENT_CALLBACK_GET_FDC_FPTR]
                  \S [CM_DEM_S_CALL_EXTERNAL_FUNCTIONTABLE_WRITE_DATAPTR]

\ID SBSW_DEM_GLOBALCBKEVENTSTATUS_FPTR
  \DESCRIPTION    In a function, a configured function pointer is dereferenced.
  \COUNTERMEASURE \R [CM_DEM_R_OPTIONAL_CALLBACK]
                  \S [CM_DEM_S_GLOBAL_CBK_EVENT_STATUS_FPTR]

\ID SBSW_DEM_GLOBALCBKEVENTDATA_FPTR
  \DESCRIPTION    In a function, a configured function pointer is dereferenced.
  \COUNTERMEASURE \R [CM_DEM_R_OPTIONAL_CALLBACK]
                  \S [CM_DEM_S_GLOBAL_CBK_EVENT_DATA_FPTR]

\ID SBSW_DEM_GLOBALCBKCONTROLDTCSETTING_FPTR
  \DESCRIPTION    In a function, a configured function pointer is dereferenced.
  \COUNTERMEASURE \R [CM_DEM_R_OPTIONAL_CALLBACK]
                  \S [CM_DEM_S_GLOBAL_CBK_CONTROL_DTC_SETTING_FPTR]

\ID SBSW_DEM_GLOBALTRIGGERONMONITORSTATUS_FPTR
  \DESCRIPTION    In a function, a configured function pointer is dereferenced.
  \COUNTERMEASURE \R [CM_DEM_R_OPTIONAL_CALLBACK]
                  \S [CM_DEM_S_GLOBAL_CBK_MONITOR_STATUS_FPTR]

\ID SBSW_DEM_OEMEXTERNALTESTERSTATUS_FPTR
  \DESCRIPTION    In a function, a configured function pointer is dereferenced. The dereferenced function expects a valid
                  pointer argument and does not store the passed pointer. A pointer to a local stack variable is passed
                  to the dereferenced function, so the pointer argument is always valid.
  \COUNTERMEASURE \R [CM_DEM_R_OPTIONAL_CALLBACK]
                  \S [CM_DEM_S_GET_EXTERNAL_TESTER_STATUS_FPTR]
                  \S [CM_DEM_S_CALL_EXTERNAL_FUNCTION_WRITE_DATAPTR]

\ID SBSW_DEM_GETCURRENTODOMETER_FPTR
  \DESCRIPTION    In a function, a configured function pointer is dereferenced. The dereferenced function expects a valid
                  pointer argument and does not store the passed pointer. A pointer to a local stack variable is passed
                  to the dereferenced function, so the pointer argument is always valid.
  \COUNTERMEASURE \R [CM_DEM_R_OPTIONAL_CALLBACK]
                  \S [CM_DEM_S_GET_CURRENT_ODOMETER_FPTR]
                  \S [CM_DEM_S_CALL_EXTERNAL_FUNCTION_WRITE_DATAPTR]

\ID SBSW_DEM_CLEARDTCNOTIFICATIONSTARTFUNCTION_FPTR
  \DESCRIPTION    In a function, a configured function pointer is dereferenced.
  \COUNTERMEASURE \R [CM_DEM_R_OPTIONAL_CALLBACK]
                  \S [CM_DEM_S_CLEAR_DTC_NOTIFICATION_START_FPTR]

\ID SBSW_DEM_CLEARDTCNOTIFICATIONFINISHFUNCTION_FPTR
  \DESCRIPTION    In a function, a configured function pointer is dereferenced.
  \COUNTERMEASURE \R [CM_DEM_R_OPTIONAL_CALLBACK]
                  \S [CM_DEM_S_CLEAR_DTC_NOTIFICATION_FINISH_FPTR]

\ID SBSW_DEM_POINTER_FORWARD_REPORTED_EVENTS_OF_FILTER
  \DESCRIPTION    A pointer to the inner array of Dem_Cfg_ReportedEventsOfFilter is passed with its corrresponding size to a
                  function expecting a valid pointer and size.
                  The structure array is generated from ComStackLib and the pointer is validated using ComStackLib function
                  before usage. Hence the pointer is always valid.
  \COUNTERMEASURE \M [CM_DEM_M_SIZEOF_REPORTEDEVENTSOFFILTER]

\ID SBSW_DEM_ARRAY_FORWARD_PROCESSEDCOMBINEDDTCGROUP
  \DESCRIPTION    A pointer to an array of type Dem_Cfg_ProcessedCombinedDTCGroupType is forwarded with its corrresponding size
                  to a function expecting a valid pointer and size.
                  The array of type Dem_Cfg_ProcessedCombinedDTCGroupType has constant size.
  \COUNTERMEASURE \R [CM_DEM_R_PROCESSEDCOMBINEDDTCGROUP_INDEX_CHECK]
                  \S [CM_DEM_S_SIZEOF_PROCESSEDCOMBINEDDTCGROUP]

\ID SBSW_DEM_POINTER_WRITE_BIT_POSITION
  \DESCRIPTION    In a function the bit at a requested index is modified inside a bitfield that is recieved as pointer argument
                  with its corresponding size. The caller of the function ensures that size of bitfield is correct and pointer
                  to bitfield is valid.
  \COUNTERMEASURE \R [CM_DEM_R_BITPOSITION_CHECK]

\ID SBSW_DEM_ARRAY_WRITE_AGINGDATA_AGINGCOUNTER
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_AgingData.AgingCounter[] at an index generated from
                  the function argument. Data is only written to the array if the generated index is within the array
                  bounds.
  \COUNTERMEASURE \R [CM_DEM_R_AGINGDATA_AGINGCOUNTER_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_AGINGDATA_AGINGCOUNTER]

\ID SBSW_DEM_ARRAY_WRITE_CYCLECOUNTERDATA_FAULTPENDINGCOUNTER
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_CycleCounterData.FaultPendingCounter[] at an index generated from
                  the function argument. Data is only written to the array if the generated index is within the array
                  bounds.
  \COUNTERMEASURE \R [CM_DEM_R_CYCLECOUNTERDATA_FAULTPENDINGCOUNTER_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_CYCLECOUNTERDATA_FAULTPENDINGCOUNTER]

\ID SBSW_DEM_ARRAY_WRITE_CYCLECOUNTERDATA_FAILEDCYCLECOUNTER
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_CycleCounterData.FailedCycleCounter[] at an index generated from
                  the function argument. Data is only written to the array if the generated index is within the array
                  bounds.
  \COUNTERMEASURE \R [CM_DEM_R_CYCLECOUNTERDATA_FAILEDCYCLECOUNTER_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_CYCLECOUNTERDATA_FAILEDCYCLECOUNTER]

\ID SBSW_DEM_ARRAY_WRITE_AGINGDATA_AGEDCOUNTER
  \DESCRIPTION    In a function, data is written to array Dem_Cfg_AgingData.AgedCounter[] at an index generated from
                  the function argument. Data is only written to the array if the generated index is within the array
                  bounds.
  \COUNTERMEASURE \R [CM_DEM_R_AGINGDATA_AGEDCOUNTER_INDEX_CHECK]
                  \M [CM_DEM_M_SIZEOF_AGINGDATA_AGEDCOUNTER]

\ID SBSW_DEM_ORGANI_TESTCODE_COMMENT_UNDEFINED
  \DESCRIPTION    It is ensure that the test code can never be active in customer configuration..
  \COUNTERMEASURE \M [CM_DEM_M_ORGANI_TESTCODE_COMMENT_UNDEFINED]

SBSW_JUSTIFICATION_END */
/* ********************************************************************************************************************
 Silent BSW Countermeasures
 ----------------------------------------------------------------------------------------------------------------------
 \CM CM_DEM_M_ORGANI_TESTCODE_COMMENT_UNDEFINED
 Verify that DEM_ORGANI_TESTCODE_COMMENT is never defined.

 \CM CM_DEM_M_SIZEOF_CYCLECOUNTERDATA_FAILEDCYCLECOUNTER
  Verify Dem_Cfg_CycleCounterData.FailedCycleCounter[] is defined for each index in range [0..DEM_CFG_MAX_NUMBER_FAILED_CYCLE_DTCS[ .

 \CM CM_DEM_M_SIZEOF_CYCLECOUNTERDATA_FAULTPENDINGCOUNTER
 Verify Dem_Cfg_CycleCounterData.FaultPendingCounter[] is defined for each index in range [0..DEM_CFG_MAX_NUMBER_FAULT_PENDING_DTCS[ .
 
\CM CM_DEM_M_SIZEOF_ADMINDATA_CYCLECOUNTER
  Verify Dem_Cfg_AdminData.CycleCounter[] is defined for each index in range [0..DEM_CFG_GLOBAL_CYCLE_COUNT[ .

\CM CM_DEM_M_SIZEOF_STATUSDATA_EVENTSTATUS
  Verify Dem_Cfg_StatusData.EventStatus[] is defined for each index in the event table.

\CM CM_DEM_M_SIZEOF_STATUSDATA_STATE
  Verify Dem_Cfg_StatusData.State[] is defined for each index in the event table.

\CM CM_DEM_M_SIZEOF_STATUSDATA_TRIPCOUNT
  Verify Dem_Cfg_StatusData.TripCount[] is defined for each index in the event table.

\CM CM_DEM_M_SIZEOF_STATUSDATA_MILGROUPTRIPCOUNT
  Verify Dem_Cfg_StatusData.MilGroupTripCount[] is defined for each index in range [0..DEM_CFG_GLOBAL_MIL_GROUP_COUNT[ .

\CM CM_DEM_M_SIZEOF_STATUSDATA_MILGROUPACTIVEEVENTS
  Verify Dem_Cfg_StatusData.MilGroupActiveEvents[] is defined for each index in range [0..DEM_CFG_GLOBAL_MIL_GROUP_COUNT[ .

\CM CM_DEM_M_SIZEOF_STATUSDATA_CONFIRMEDCHRONOLOGY
  Verify Dem_Cfg_StatusData.ConfirmedChronology[] is defined for each index in range [0..DEM_CFG_MAX_NUMBER_PERMANENT_CHRONOLOGY[ .

\CM CM_DEM_M_SIZEOF_STATUSDATA_EXTENDEDEVENTSTATUS
  Verify Dem_Cfg_StatusData.ExtendedEventStatus[] is defined for each index in the event table.

\CM CM_DEM_M_SIZEOF_FREEZEFRAME
  Verify Dem_Cfg_FreezeFrameData[] is defined for each index in range [0..max(1, DEM_CFG_GLOBAL_FREEZEFRAME_SIZE)[ .
  Verify Dem_Cfg_FreezeFrameData[].FreezeFrameData[] is defined for each index in range [0..max(1,DEM_CFG_MAX_SIZE_OBDFREEZEFRAME)[ .

\CM CM_DEM_M_SIZEOF_DTRDATA
  Verify that Dem_Cfg_DtrData.TestValue[], Dem_Cfg_DtrData.LowLimValue[], and Dem_Cfg_DtrData.UppLimValue[] is defined for
  each index in range [0.. DEM_CFG_MAX_NUMBER_CONFIGURABLE_DTRS[

\CM CM_DEM_M_SIZEOF_PERMANENT_PERMANENTDATAENTRY
  Verify Dem_Cfg_PermanentData.PermanentDataEntry[] is defined for each index in range [0..DEM_CFG_GLOBAL_PERMANENT_SIZE[ .

\CM CM_DEM_M_SIZEOF_EVENTAVAILABLEDATA
  Verify Dem_Cfg_EventAvailableData[] is defined for each index in range [0..DEM_CFG_EVENTAVAILABLEDATATYPE_SIZE[ .

\CM CM_DEM_M_SIZEOF_DEBOUNCEDATA
  Verify Dem_Cfg_DebounceData[] is defined for each index in range [0..DEM_CFG_GLOBAL_DEBOUNCE_STORAGE_EVENT_COUNT[ .

\CM CM_DEM_M_SIZEOF_PRESTORAGE
  Verify Dem_Cfg_Prestorage[] is defined for each index in range [0..DEM_CFG_GLOBAL_PRESTORED_FF_SIZE] .

\CM CM_DEM_M_SIZEOF_PRIMARYCHRONOLOGY
  Verify Dem_Cfg_PrimaryChronology[] is defined for each index in range [0..DEM_CFG_GLOBAL_PRIMARY_SIZE[ .

\CM CM_DEM_M_SIZEOF_SECONDARYCHRONOLOGY
  Verify Dem_Cfg_SecondaryChronology[] is defined for each index in range [0..DEM_CFG_GLOBAL_SECONDARY_SIZE[ .

\CM CM_DEM_M_SIZEOF_TIMESERIES_CHRONOLOGY
  Verify Dem_Cfg_TimeSeriesChronology[] is defined for each index in range [0..DEM_CFG_GLOBAL_TIMESERIES_SNAPSHOTS_SIZE[ .

\CM CM_DEM_M_SIZEOF_INDICATORCONTINUOUS
  Verify Dem_Cfg_IndicatorContinuous[] is defined for each index in range [0..DEM_CFG_GLOBAL_INDICATOR_COUNT[ .
  Verify Dem_Cfg_IndicatorContinuous[][] is defined for each index in range [0..max(1, DEM_G_MAX_NUMBER_J1939_NODES)[ .

\CM CM_DEM_M_SIZEOF_INDICATORBLINKING
  Verify Dem_Cfg_IndicatorBlinking[] is defined for each index in range [0..DEM_CFG_GLOBAL_INDICATOR_COUNT[ .
  Verify Dem_Cfg_IndicatorBlinking[][] is defined for each index in range [0..max(1, DEM_G_MAX_NUMBER_J1939_NODES)[ .

\CM CM_DEM_M_SIZEOF_INDICATORFASTFLASH
  Verify Dem_Cfg_IndicatorFastFlash[] is defined for each index in range [0..DEM_CFG_GLOBAL_INDICATOR_COUNT[ .
  Verify Dem_Cfg_IndicatorFastFlash[][] is defined for each index in range [0..max(1, DEM_G_MAX_NUMBER_J1939_NODES)[ .

\CM CM_DEM_M_SIZEOF_INDICATORSLOWFLASH
  Verify Dem_Cfg_IndicatorSlowFlash[] is defined for each index in range [0..DEM_CFG_GLOBAL_INDICATOR_COUNT[ .
  Verify Dem_Cfg_IndicatorSlowFlash[][] is defined for each index in range [0..max(1, DEM_G_MAX_NUMBER_J1939_NODES)[ .

\CM CM_DEM_M_SIZEOF_GLOBALINDICATORSTATES
  Verify Dem_Cfg_GlobalIndicatorStates[][] is defined for each index in range [0..max(1, DEM_G_MAX_NUMBER_J1939_NODES)[ .

\CM CM_DEM_M_SIZEOF_REPORTEDEVENTSOFFILTER
  Verify Dem_Cfg_ReportedEventsOfFilter[][] is defined for each index in range [0..DEM_CFG_GLOBAL_PROCESSORWORDS_PER_REPORTEDEVENTSTYPE[ .

\CM CM_DEM_M_SIZEOF_MEMORYDATAPTR
  Verify Dem_Cfg_MemoryDataPtr[] is defined for each index in range [0..DEM_CFG_GLOBAL_NV_BLOCK_COUNT[ .

\CM CM_DEM_M_SIZEOF_OBDIUMPRDATA
  Verify that Dem_Cfg_ObdIumprData.Numerator[], Dem_Cfg_ObdIumprData.Denominator[], and Dem_Cfg_ObdIumprData.Status[] is defined for 
  each index in range [0.. DEM_G_NUMBER_OF_RATIO_IDS[

\CM CM_DEM_M_SIZEOF_MEMORYBLOCKID
  Verify that Dem_Cfg_MemoryBlockId[] is defined for each index in range [0.. DEM_CFG_GLOBAL_NV_BLOCK_COUNT[ .

\CM CM_DEM_M_SIZEOF_MEMORYDATASIZE
  Verify that Dem_Cfg_MemoryDataSize[] is defined for each index in range [0.. DEM_CFG_GLOBAL_NV_BLOCK_COUNT[ .

\CM CM_DEM_M_SIZEOF_MISSINGTIMESERIESNORMALRATE
  Verify Dem_Cfg_MissingTimeSeriesNormalRate[] is defined for each index in range [0..DEM_CFG_GLOBAL_TIMESERIES_SNAPSHOTS_SIZE[ .

\CM CM_DEM_M_SIZEOF_MISSINGTIMESERIESFASTRATE
  Verify Dem_Cfg_MissingTimeSeriesFastRate[] is defined for each index in range [0..DEM_CFG_GLOBAL_TIMESERIES_SNAPSHOTS_SIZE[ .

\CM CM_DEM_M_SIZEOF_STDENVDATA
  Verify Dem_Cfg_PrimaryEntryType.StdEnvData[] is defined for each index in range [0..DEM_MEMORYENTRY_STD_ENV_DATA_SIZE[, if DEM_CFG_DATA_STANDARD_ENV_DATA == STD_ON.
  Verify Dem_Cfg_PrimaryEntryType.StdEnvData[] is defined for each index in range [0..DEM_MEMORYENTRY_EXT_ENV_DATA_SIZE[, if DEM_CFG_DATA_EXTENDED_ENV_DATA == STD_ON.

\CM CM_DEM_M_TIMESERIESINDEX_LIMITS
  Verify DEM_CFG_MEMORY_TIME_SERIES_INDEX + DEM_CFG_GLOBAL_TIMESERIES_SNAPSHOTS_SIZE <= DEM_CFG_GLOBAL_NV_BLOCK_COUNT, with
  DEM_CFG_GLOBAL_TIMESERIES_SNAPSHOTS_SIZE > 0.

\CM CM_DEM_M_TIMESERIESENTRYCOMPANIONINDEX_LIMITS
  Verify Dem_Cfg_TimeSeriesEntryCompanion[] is defined for each index in range [0..DEM_CFG_GLOBAL_TIMESERIES_SNAPSHOTS_SIZE[ .

\CM CM_DEM_M_SIZEOF_PRESTORED_SNAPSHOT
  Verify that Dem_Cfg_PrestorageEntryType.SnapshotData[] has at least DEM_CFG_MAX_SIZE_SNAPSHOT elements.

\CM CM_DEM_M_SIZEOF_PRESTORED_OBDFREEZEFRAME
  Verify that Dem_Cfg_PrestorageEntryType.ObdFreezeFrame[] has at least DEM_CFG_MAX_SIZE_OBDFREEZEFRAME elements if OBD is supported.

\CM CM_DEM_M_SIZEOF_PRESTORED_J1939FREEZEFRAME
  Verify that Dem_Cfg_PrestorageEntryType.J1939FreezeFrame[] has at least (DEM_CFG_MAX_J1939_FF_SIZE + DEM_CFG_MAX_J1939_EXP_FF_SIZE)
  elements, if J1939 freezeframe or J1939Expanded freezeframe is supported.

\CM CM_DEM_M_SIZEOF_MEMORYENTRY_EXTENDEDDATA
  Verify that Dem_Cfg_PrimaryEntryType.ExtendedData[] is valid for values in range [0..DEM_CFG_MAX_NUM_EXT_RECORDS[ .
  Verify that Dem_Cfg_PrimaryEntryType.ExtendedData[][] has at least DEM_CFG_MAX_SIZE_EXT_RECORD elements .

\CM CM_DEM_M_SIZEOF_MEMORYENTRY_SNAPSHOTDATA
  Verify that Dem_Cfg_PrimaryEntryType.SnapshotData[] is valid for values in range [0..DEM_CFG_MAX_NUM_SNAPSHOTS[ .
  Verify that Dem_Cfg_PrimaryEntryType.SnapshotData[][] has at least DEM_CFG_MAX_SIZE_SNAPSHOT elements.

\CM CM_DEM_M_SIZEOF_MEMORYENTRY_J1939FREEZEFRAME
  Verify that Dem_Cfg_PrimaryEntryType.J1939FreezeFrame[] is valid for values in range [0..(DEM_CFG_MAX_J1939_FF_SIZE + DEM_CFG_MAX_J1939_EXP_FF_SIZE)[,
  if J1939 freezeframe or J1939Expanded freezeframe is supported.

\CM CM_DEM_M_SIZEOF_NORMAL_RATE_RINGBUFFER
  Verify that Dem_Cfg_RingBufferNormalRateType.Buffer[] is valid for indices in range [0..max(1, DEM_CFG_TIMESERIES_NORMAL_PAST_SAMPLES)[ .
  Verify that Dem_Cfg_RingBufferNormalRateType.Buffer[][] is valid for indices in range [0..DEM_CFG_TIMESERIES_NORMAL_BUFFER_SIZE[ .

\CM CM_DEM_M_SIZEOF_FAST_RATE_RINGBUFFER
  Verify that Dem_Cfg_RingBufferFastRateType.Buffer[] is valid for indices in range [0..max(1, DEM_CFG_TIMESERIES_FAST_PAST_SAMPLES)[ .
  Verify that Dem_Cfg_RingBufferFastRateType.Buffer[][] is valid for indices in range [0..DEM_CFG_TIMESERIES_FAST_BUFFER_SIZE[ .

\CM CM_DEM_M_SIZEOF_SERIESENTRY_NORMAL_SNAPSHOTDATA
  Verify that Dem_Cfg_TimeSeriesEntryType.SnapshotData_NormalRate[] is valid for values in range [0..(DEM_CFG_TIMESERIES_NORMAL_FUTURE_SAMPLES + DEM_CFG_TIMESERIES_NORMAL_PAST_SAMPLES)[ .
  Verify that Dem_Cfg_TimeSeriesEntryType.SnapshotData_NormalRate[][] has at least DEM_CFG_MAX_SIZE_TIMESERIESSNAPSHOT elements.

\CM CM_DEM_M_SIZEOF_SERIESENTRY_FAST_SNAPSHOTDATA
  Verify that Dem_Cfg_TimeSeriesEntryType.SnapshotData_FastRate[] is valid for values in range [0..(DEM_CFG_TIMESERIES_FAST_FUTURE_SAMPLES + DEM_CFG_TIMESERIES_FAST_PAST_SAMPLES)[ .
  Verify that Dem_Cfg_TimeSeriesEntryType.SnapshotData_FastRate[][] has at least DEM_CFG_MAX_SIZE_TIMESERIESSNAPSHOT elements.

\CM CM_DEM_M_SIZEOF_SERIESENTRY_SNAPSHOTDATA
  Verify that Dem_Cfg_TimeSeriesEntryType.SnapshotData[] is valid for values in range [0..(Ceiling of (DEM_CFG_TIMESERIES_NORMAL_PAST_SAMPLES and DEM_CFG_TIMESERIES_FAST_PAST_SAMPLES)[
  Verify that Dem_Cfg_TimeSeriesEntryType.SnapshotData[][] has at least DEM_CFG_MAX_SIZE_TIMESERIESSNAPSHOT elements

\CM CM_DEM_M_SIZEOF_MEMORYENTRY_GLOBALSNAPSHOTDATA
  Verify Dem_Cfg_PrimaryEntryType.GlobalSnapshotData[] is defined for each index in range [0..DEM_CFG_MAX_SIZE_GLOBAL_SNAPSHOT[ if
  global snapshot records are supported.

\CM CM_DEM_M_SIZEOF_PRESTORED_GLOBALSNAPSHOTDATA
  Verify Dem_Cfg_PrestorageEntryType.GlobalSnapshotData[] is defined for each index in range [0..DEM_CFG_MAX_SIZE_GLOBAL_SNAPSHOT[
  if prestorage of global snapshot records is supported.

\CM CM_DEM_M_SIZEOF_AGINGDATA_AGINGCOUNTER
  Verify Dem_Cfg_AgingData.AgingCounter[] is defined for each index in range [0..DEM_CFG_MAX_NUMBER_AGING_DTCS[ if memory independent aging for DTCs is enabled.

\CM CM_DEM_M_SIZEOF_AGINGDATA_AGEDCOUNTER
  Verify Dem_Cfg_AgingData.AgedCounter[] is defined for each index in range [0..DEM_CFG_MAX_NUMBER_AGED_DTCS[ if the aged counter is used as internal data element.

\CM CM_DEM_M_SIZEOF_READOUTBUFFER_OBDFREEZEFRAME
  Verify that Dem_Cfg_ReadoutBufferEntryType.OBDFreezeFrameData.ObdFreezeFrame[] is defined for each index in range
  [0.. DEM_CFG_MAX_SIZE_OBDFREEZEFRAME[ if reading OBDII freeze frames through Service 0x19-04 is supported.

\CM CM_DEM_M_SIZEOF_READOUTBUFFER_READOUTBUFFERDATA
  Verify that Dem_Cfg_ReadoutBufferEntryType.ReadOutBufferData[] is defined for each index in range
  [0.. DEM_CFG_NUMBER_OF_SUBEVENT_DATA_READOUTBUFFERS[.

\CM CM_DEM_R_DEBOUNCEINFO_INIT
  Dem_Debounce_DebounceInfoInit will always initialize the function pointer table with valid function pointers even when
  the passed event index is not a handle to an event, or the passed event does not have a valid debounce algorithm
  configured.

\CM CM_DEM_R_TIMESERIES_GET_ENTRY
  Dem_Memory_TimeSeries_GetEntrySafe will always return a valid time series entry even when the passed memory index is not a handle to a time series entry.

\CM CM_DEM_R_TIMESERIES_GET_ENTRY_COMPANION
  Dem_Memory_TimeSeries_GetEntryCompanionSafe will always return a valid time series entry even when the passed memory index is not a handle to a time series entry companion.

\CM CM_DEM_R_READOUTBUFFER_GET_ENTRY
  Dem_DTCReadoutBuffer_GetReadoutBufferSafe() will always return a valid readout buffer entry even when the passed index is not a
  handle to a readout buffer entry. Dem_DTCReadoutBuffer_GetReadoutBufferSafe() uses ComStackLib functions Dem_Cfg_GetSizeOfReadoutBuffer()
  and Dem_Cfg_GetAddrReadoutBuffer to check if passed index is valid. Therefore no further CM needed.

\CM CM_DEM_R_GET_READOUTBUFFER_READOUTBUFFERDATA
  Dem_DTCReadoutBuffer_GetReadoutBufferDataSafe() will always return a pointer to a valid ReadOutBufferData even when the passed indexes
  are not valid. Dem_DTCReadoutBuffer_GetReadoutBufferDataSafe() uses ComStackLib functions Dem_Cfg_GetSizeOfReadoutBuffer()
  and Dem_Cfg_GetReadoutBuffer() to check if outer array index is valid. The validity of inner array index is verified through
  runtime checks before accessing it.

\CM CM_DEM_R_GET_FILTERDATA
  Dem_Client_FilterData_GetFilterDataPtrSafe() will always return a valid filter data entry even when the passed index is not a
  handle to a filter data entry. Dem_Client_FilterData_GetFilterDataPtrSafe() uses ComStackLib functions Dem_Cfg_GetSizeOfFilterInfoTable()
  and Dem_Cfg_GetFilterInfoTable() to check if passed index is valid. Therefore no further CM needed.

\CM CM_DEM_R_DTCSELECTORTABLE_GET_ENTRY
  Verify that the functions Dem_DTCSelector_SetSelectionData() and Dem_DTCSelector_SetSelectionData_ActiveAsyncOps()
  does not write to Dem_Cfg_DTCSelectorTable[] when the passed index is not handle to a Dem_Cfg_DTCSelectorTable entry.
  The ComStackLib functions Dem_Cfg_GetSizeOfDTCSelectorTable() and Dem_Cfg_GetAddrDTCSelectorTable() are used to
  check if passed index is valid. Therefore no further CM needed.

\CM CM_DEM_R_OPTIONAL_CALLBACK
  Optional Callbacks can be NULL_PTR, so the code must explicitly verify that the function called is not NULL_PTR.

\CM CM_DEM_R_CHECK_NVBLOCKID
  Before passing an NV block ID to the NvM, verify that the Dem memory index is valid. This is necessary for SMI-22 and SMI-23.

\CM CM_DEM_R_SIZEOF_DATAELEMENT_TABLE
  Verify that the data element index used to access Dem_Cfg_DataElementTable is valid.

\CM CM_DEM_R_CHECK_DATAELEMENT_TYPE
  Verify that the function pointer called is configured to have the expected data element type.

\CM CM_DEM_R_MEMORY_GET_ERECDATAPTR
  Dem_MemoryEntry_GetExtendedRecordDataPtr will always return a valid pointer even when the passed record index is not valid.

\CM CM_DEM_R_MEMORY_GET_SRECDATAPTR
  Dem_MemoryEntry_GetSnapshotRecordDataPtr will always return a valid pointer even when the passed record index is not valid.

\CM CM_DEM_R_PRESTORAGE_GET_GLOBALSRECPTR
  Dem_Prestore_PrestorageEntryGetGlobalSRecDataPtr will always return a valid pointer even when the passed prestorage index is not valid.

\CM CM_DEM_R_PRESTORAGE_GET_SRECPTR
  Dem_Prestore_PrestorageEntryGetSRecDataPtr will always return a valid pointer even when the passed prestorage index is not valid.

\CM CM_DEM_R_PRESTORAGE_GET_OBDFFPTR
  Dem_Prestore_PrestorageEntryGetObdIIFFDataPtr will always return a valid pointer even when the passed prestorage index is not valid.

\CM CM_DEM_R_PRESTORAGE_GET_J1939FFPTR
  Dem_Prestore_PrestorageEntryGetJ1939FFDataPtr will always return a valid pointer even when the passed prestorage index is not valid.

\CM CM_DEM_R_PRESTORAGE_GET_WWHOBDFFPTR
  Dem_Prestore_PrestorageEntryGetWwhObdFFDataPtr will always return a valid pointer even when the passed prestorage index is not valid.

\CM CM_DEM_R_MEMORY_GET_OBDDATAPTR
  Dem_Mem_FreezeFrameObdIIGetDataPtr will always return a valid pointer even when the passed record index is not valid.

\CM CM_DEM_R_RINGBUFFER_NORMALRATEPTR
  Dem_Memory_TimeSeries_RingBuffer_GetNormalSlot will always return a valid pointer even when the passed buffer index is not valid.

\CM CM_DEM_R_RINGBUFFER_FASTRATEPTR
  Dem_Memory_TimeSeries_RingBuffer_GetFastSlot will always return a valid pointer even when the passed record index is not valid.

\CM CM_DEM_R_TIMESERIES_GET_NORMALDATAPTR
  Dem_Memory_TimeSeries_EntryManager_GetNormalDataPtr will always return a valid pointer even when the passed series index is not valid.

\CM CM_DEM_R_TIMESERIES_GET_DATAPTR
  Dem_Memory_TimeSeries_EntryManager_GetDataPtr will always return a valid pointer even when the passed series index is not valid.

\CM CM_DEM_R_TIMESERIES_GET_FASTDATAPTR
  Dem_Memory_TimeSeries_EntryManager_GetFastDataPtr will always return a valid pointer even when the passed series index is not valid.

\CM CM_DEM_R_CHECK_REMAINING_BUFFER
  Before writing data to a buffer, check that the buffer is large enough for the data written to it.

\CM CM_DEM_R_GET_READOUTBUFFER_OBDFREEZEFRAME
  Dem_DTCReadoutBuffer_GetPtrToOBDFreezeFrameBuffer will always return a valid pointer to a OBD FreezeFrame buffer. Dem_Cfg_GlobalObdFreezeFrameMaxSize()
  will always return the size of the buffer.

\CM CM_DEM_R_INIT_DESTINATIONBUFFER
  Before using a locally allocated DestinationBuffer structure or passing it as pointer to another function initialize it with Dem_Data_InitDestinationBuffer.

\CM CM_DEM_R_INIT_DIDCOPYINFO
  Before using a locally allocated DidCopyInfo structure or passing it as pointer to another function initialize it with Dem_DataReport_InitDidCopyInfo.

\CM CM_DEM_R_INIT_COLLECTDIDINFO
  Before using a locally allocated CollectDidInfo structure or passing it as pointer to another function initialize it with Dem_ExtDataElement_InitCollectDidInfo.

\CM CM_DEM_R_CHECK_DESTINATIONBUFFER_WRITEINDEX
  Before incrementing WriteIndex by value X, check that (WriteIndex+X) <= BufferSize.

\CM CM_DEM_R_CHECK_DESTINATIONBUFFER_WRITEPOSITION
  Before writing data to a buffer in DestinationBuffer, check that the write index is in range.

\CM CM_DEM_R_CHECK_REMAINING_DESTINATIONBUFFER
  Before writing data to a buffer in DestinationBuffer, check that the buffer is large enough by calling Dem_Data_IncrementWriteIndexDestinationBuffer.

\CM CM_DEM_R_CLEAR_EVENT_ALLOWED_INDEX
  Verify that the table index is in range before accessing Dem_Cfg_CallbackClearEventAllowed.

\CM CM_DEM_R_INIT_MONITOR_FOR_EVENT_INDEX
  Verify that the table index is in range before accessing Dem_Cfg_InitMonitorForEvent.

\CM CM_DEM_R_INIT_MONITOR_FOR_FUNCTION_INDEX
  Verify that the table index is in range before accessing Dem_Cfg_InitMonitorsForFunc.

\CM CM_DEM_R_EVENT_CBK_STATUS_INDEX
  Verify that the table index is in range before accessing Dem_Cfg_EventStatusChanged.

\CM CM_DEM_R_DTC_CBK_STATUS_INDEX
  Verify that the table index is in range before accessing Dem_Cfg_CallbackDtcStatusChanged.

\CM CM_DEM_R_J1939_DTC_CBK_STATUS_INDEX
  Verify that the table index is in range before accessing Dem_Cfg_CallbackJ1939DtcStatusChanged.

\CM CM_DEM_R_EVENT_CALLBACK_GET_FDC_INDEX
  Verify that the table index is in range before accessing Dem_Cfg_CallbackGetFdc.

\CM CM_DEM_R_SIZEOF_COMMITBUFFER
  Verify that the Commit buffer is big enough to hold the block before copying the data.

\CM CM_DEM_R_MEMORYDATA_INDEX
  Verify that the table index is in range before accessing Dem_Cfg_MemoryDataPtr and Dem_Cfg_MemoryDataSize.

\CM CM_DEM_R_DEM_CFG_ADMINDATA_CYCLECOUNTER_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_AdminData.CycleCounter.

\CM CM_DEM_R_DEM_CFG_STATUSDATA_EVENTSTATUS_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_StatusData.EventStatus.

\CM CM_DEM_R_DEM_CFG_STATUSDATA_STATE_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_StatusData.State.

\CM CM_DEM_R_DEM_CFG_STATUSDATA_TRIPCOUNT_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_StatusData.TripCount.

\CM CM_DEM_R_DEM_CFG_STATUSDATA_MILGROUPTRIPCOUNT_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_StatusData.MilGroupTripCount.

\CM CM_DEM_R_DEM_CFG_STATUSDATA_MILGROUPACTIVEEVENTS_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_StatusData.MilGroupActiveEvents.

\CM CM_DEM_R_DEM_CFG_STATUSDATA_CONFIRMEDCHRONOLOGY_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_StatusData.ConfirmedChronology.

\CM CM_DEM_R_DEM_CFG_STATUSDATA_EXTENDEDEVENTSTATUS_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_StatusData.ExtendedEventStatus.

\CM CM_DEM_R_DEM_CFG_FREEZEFRAMEDATA_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_FreezeFrameData.

\CM CM_DEM_R_DEM_CFG_PERMANENTDATA_PERMANENTDATAENTRY_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_PermanentData.PermanentDataEntry.

\CM CM_DEM_R_DEM_CFG_DTRDATA_TESTVALUE_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_DtrData.TestValue.

\CM CM_DEM_R_DEM_CFG_DTRDATA_LOWLIMVALUE_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_DtrData.LowLimValue.

\CM CM_DEM_R_DEM_CFG_DTRDATA_UPPLIMVALUE_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_DtrData.UppLimValue.

\CM CM_DEM_R_DEM_CFG_OBDIUMPRDATA_DENOMINATOR_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_ObdIumprData.Denominator.

\CM CM_DEM_R_DEM_CFG_OBDIUMPRDATA_STATUS_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_ObdIumprData.Status.

\CM CM_DEM_R_DEM_CFG_OBDIUMPRDATA_NUMERATOR_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_ObdIumprData.Numerator.

\CM CM_DEM_R_DEBOUNCEDATA_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_DebounceData.

\CM CM_DEM_R_AVAILABLEDATA_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_EventAvailableData.

\CM CM_DEM_R_PRESTORAGE_CHECK
  Verify with function Dem_Prestore_PrestorageEntry_Checked() that the array index is in range before writing to
  Dem_Cfg_Prestorage.

\CM CM_DEM_R_MEMORYCHRONOLOGY_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_PrimaryChronology.
  Verify that the array index is in range before writing to Dem_Cfg_SecondaryChronology.
  Verify that the array index is in range before writing to Dem_Cfg_TimeSeriesChronology.

\CM CM_DEM_R_INDICATORCONTINUOUS_INDEX_CHECK
  Verify that all array indices are in range before writing to Dem_Cfg_IndicatorContinuous[][] .

\CM CM_DEM_R_INDICATORBLINKING_INDEX_CHECK
  Verify that all array indices are in range before writing to Dem_Cfg_IndicatorBlinking[][] .

\CM CM_DEM_R_INDICATORFASTFLASH_INDEX_CHECK
  Verify that all array indices are in range before writing to Dem_Cfg_IndicatorBlinking[][] .

\CM CM_DEM_R_INDICATORFASTSLOWFLASH_INDEX_CHECK
  Verify that all array indices are in range before writing to Dem_Cfg_IndicatorFastFlash[][] .

\CM CM_DEM_R_QUALIFIEDACTIVEEVENTCOUNT_INDEX_CHECK
  Verify that all array indices are in range before writing to Dem_Esm_QualifiedActiveEventCount[][] .

\CM CM_DEM_R_DTCCLASSMILCOUNT_INDEX_CHECK
  Verify that all array indices are in range before writing to Dem_Esm_DtcClassMILCount[][] .

\CM CM_DEM_R_SUPPORTEDMIDMASK_INDEX_CHECK
  Verify that all array indices are in range before writing to Dem_MidLookup_SupportedMidMask[][] .

\CM CM_DEM_R_PROCESSEDCOMBINEDDTCGROUP_INDEX_CHECK
  Verify that all array indices are in range before writing to an array of type Dem_Cfg_ProcessedCombinedDTCGroupType.
  The size of an array of type Dem_Cfg_ProcessedCombinedDTCGroupType is constant,
  and defined by DEM_CFG_PROCESSEDCOMBINEDDTCGROUP_SIZE.

\CM CM_DEM_R_GLOBALINDICATORSTATES_INDEX_CHECK
  Verify that all array indices are in range before writing to Dem_Cfg_GlobalIndicatorStates[][] .

\CM CM_DEM_R_REPORTEDEVENTSOFFILTER_INDEX_CHECK
  Verify that all array indices are in range before writing to Dem_Cfg_GetReportedEventsOfFilter[][] .

\CM CM_DEM_R_MISSINGTIMESERIESNORMALRATE_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_MissingTimeSeriesNormalRate.

\CM CM_DEM_R_MISSINGTIMESERIESFASTRATE_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_MissingTimeSeriesFastRate.

\CM CM_DEM_R_SATELLITE_NULLPTR
  Verify that pointer is not equal to NULL_PTR before writing to memory.

\CM CM_DEM_R_CHRONOLOGY_NULLPTR
  Verify that pointer is not equal to NULL_PTR before writing to memory.

\CM CM_DEM_R_SATELLITE_INDEX
  Verify that the satellite Id is in range [0..Dem_Cfg_GetSizeOfSatelliteInfo()[ before writing through a pointer taken from Dem_Cfg_SatelliteInfo.
  The ComStackLib guarantees that Dem_Cfg_SatelliteInfo is defined for all indices in this range.

\CM CM_DEM_R_MAXDEBOUNCE_VALUE_INDEX
  Verify that the monitor Id is in range before writing to Dem_Cfg_SatelliteInfoType<X>.MaxDebounceValues[].

\CM CM_DEM_R_SATELLITEDATA_INDEX
  Verify that the monitor Id is in range before writing to Dem_Cfg_SatelliteInfoType<X>.SatelliteData[].

\CM CM_DEM_R_SATELLITE_EXTENDEDDATA_INDEX
  Verify that the monitor Id is in range before writing to Dem_Cfg_SatelliteInfoType<X>.SatelliteExtendedData[].

\CM CM_DEM_R_MEMENTRY_STDENVDATA_INDEX_CHECK
  Verify that the array index is in range before writing to Dem_Cfg_PrimaryEntryType.StdEnvData[].

\CM CM_DEM_R_BITPOSITION_CHECK
  Verify that requested bit position is valid before setting or resetting the bit in the passed bitfield.

\CM CM_DEM_R_CHECK_TIMEBASED_DEBOUNCEINFO_PTR
  Verify that input DebounceInfoPointer is initialized for time based debouncing.

\CM CM_DEM_R_CHECK_COUNTERBASED_DEBOUNCEINFO_PTR
  Verify that input DebounceInfoPointer is initialized for counter based debouncing.

\CM CM_DEM_R_CHECK_MONITORINTERNAL_DEBOUNCEINFO_PTR
  Verify that input DebounceInfoPointer is initialized for monitor internal debouncing.

\CM CM_DEM_R_WORDPOSITION_CHECK
  Verify that passed word position is in range.

\CM CM_DEM_R_APPLICATIONID_CHECK
  Verify that the current ApplicationId is equal to the ApplicationId corresponding to the calculated SatelliteId.

\CM CM_DEM_R_AGINGDATA_AGINGCOUNTER_INDEX_CHECK
  Verify that array index is in range before writing to Dem_Cfg_AgingData.AgingCounter[].

\CM CM_DEM_R_AGINGDATA_AGEDCOUNTER_INDEX_CHECK
  Verify that array index is in range before writing to Dem_Cfg_AgingData.AgedCounter[].

\CM CM_DEM_R_CYCLECOUNTERDATA_FAULTPENDINGCOUNTER_INDEX_CHECK
  Verify that array index is in range before writing to Dem_Cfg_CycleCounterData.FaultPendingCounter[].

\CM CM_DEM_R_CYCLECOUNTERDATA_FAILEDCYCLECOUNTER_INDEX_CHECK
  Verify that array index is in range before writing to Dem_Cfg_CycleCounterData.FailedCycleCounter[].

\CM CM_DEM_S_CLEAR_EVENT_ALLOWED_FPTR
  [SMI-105853] Verify that all function pointers stored in table Dem_Cfg_CallbackClearEventAllowed are compatible to
  Dem_ClearEventAllowedFPtrType. The value NULL_PTR is valid for this callback type.

\CM CM_DEM_S_INIT_MONITOR_FOR_EVENT_FPTR
  [SMI-105853] Verify that all function pointers stored in table Dem_Cfg_InitMonitorForEvent are compatible to
  Dem_InitMonitorForEventFPtrType. The value NULL_PTR is valid for this callback type.

\CM CM_DEM_S_INIT_MONITOR_FOR_FUNCTION_FPTR
  [SMI-105853] Verify that all function pointers stored in table Dem_Cfg_InitMonitorsForFunc are compatible to
  Dem_InitMonitorForFuncFPtrType. The value NULL_PTR is valid for this callback type.

\CM CM_DEM_S_GLOBAL_CBK_DTC_STATUS_FPTR
  [SMI-105853] Verify that all function pointers stored in table Dem_Cfg_CallbackDtcStatusChanged are compatible to
  Dem_DtcStatusChangedFPtrType. The value NULL_PTR is valid for this callback type.

\CM CM_DEM_S_EVENT_CBK_STATUS_FPTR
  [SMI-105853] Verify that all function pointers stored in table Dem_Cfg_EventStatusChanged are compatible to
  Dem_EventStatusChangedFPtrType. The value NULL_PTR is valid for this callback type.

\CM CM_DEM_S_EVENT_CBK_DATA_FPTR
  [SMI-105853] Verify that all function pointers stored in table Dem_Cfg_EventDataChanged are compatible to
  Dem_EventDataChangedFPtrType. The value NULL_PTR is valid for this callback type.

\CM CM_DEM_S_EVENT_CALLBACK_GET_FDC_FPTR
  [SMI-105853] Verify that all function pointers stored in table Dem_Cfg_CallbackGetFdc are compatible to
  Dem_GetFDCFPtrType. The value NULL_PTR is valid for this callback type.

\CM CM_DEM_S_CLEAR_DTC_NOTIFICATION_START_FPTR
  [SMI-123681] Verify that all function pointers stored in table Dem_Cfg_ClearDtcNotificationStartTable are compatible to
  Dem_ClearDtcNotificationFPtrType. The value NULL_PTR is not valid for this callback type.

\CM CM_DEM_S_CLEAR_DTC_NOTIFICATION_FINISH_FPTR
  [SMI-123681] Verify that all function pointers stored in table Dem_Cfg_ClearDtcNotificationFinishTable are compatible to
  Dem_ClearDtcNotificationFPtrType. The value NULL_PTR is not valid for this callback type.

\CM CM_DEM_S_GLOBAL_CBK_J1939_DTC_STATUS_FPTR
  [SMI-123681] Verify that all function pointers stored in table Dem_Cfg_CallbackJ1939DtcStatusChanged are compatible to
  Dem_DtcStatusChangedFPtrType. The value NULL_PTR is not valid for this callback type.

\CM CM_DEM_S_GLOBAL_CBK_EVENT_STATUS_FPTR
  [SMI-105854] Verify that the function pointer defined as macro DEM_CFG_GLOBALCBKSTATUS_FUNC is compatible to
  Dem_GlobalStatusChangedFPtrType. The value NULL_PTR is valid for this callback.

\CM CM_DEM_S_GLOBAL_CBK_EVENT_DATA_FPTR
  [SMI-105854] Verify that the function pointer defined as macro DEM_CFG_GLOBALCBKDATA_FUNC is compatible to
  Dem_GlobalDataChangedFPtrType. The value NULL_PTR is valid for this callback.

\CM CM_DEM_S_GLOBAL_CBK_CONTROL_DTC_SETTING_FPTR
  [SMI-105854] Verify that the function pointer defined as macro DEM_CFG_GLOBALCBKCONTROLDTCSETTING_FUNC is compatible to
  Dem_ControlDtcSettingChangedFPtrType. The value NULL_PTR is valid for this callback.

\CM CM_DEM_S_GLOBAL_CBK_MONITOR_STATUS_FPTR
  [SMI-105854] Verify that the function pointer defined as macro DEM_CFG_GLOBALTRIGGERONMONITORSTATUS_FUNC is compatible to
  Dem_GlobalTriggerOnMonitorStatusFPtrType. The value NULL_PTR is valid for this callback.

\CM CM_DEM_S_GET_EXTERNAL_TESTER_STATUS_FPTR
  [SMI-105854] Verify that the function pointer defined as macro DEM_CFG_OEMCBKGETEXTERNALTESTERSTATUS_FUNC is compatible to
  Dem_OemCbkGetExternalTesterStatusFptrType. The value NULL_PTR is valid for this callback.

\CM CM_DEM_S_GET_CURRENT_ODOMETER_FPTR
  [SMI-105854] Verify that the function pointer defined as macro DEM_CFG_OEMCBKGETCURRENTODOMETER_FUNC is compatible to
  Dem_OemCbkGetCurrentOdometerFptrType. The value NULL_PTR is valid for this callback.

\CM CM_DEM_S_CALL_EXTERNAL_FUNCTION_WRITE_DATAPTR
  [SMI-106376] Verify that the configured functions only writes the corresponding size to the data pointer.
  The value NULL_PTR is valid for this callback.

\CM CM_DEM_S_DATA_CALLBACK_FPTR
  [SMI-105855] The user of MICROSAR Safe shall verify for all function pointers stored in table Dem_Cfg_DataElementTable:
  - If ElementKind is DEM_CFG_DATA_FROM_CBK, verify that the callback function ReadDataFunc is compatible to
    Dem_ReadDataStandardFPtrType.
  - If ElementKind is DEM_CFG_DATA_FROM_CBK_WITH_EVENTID, verify that the callback function ReadDataFunc is
    compatible to Dem_ReadDataExtendedFPtrType.
  - If ElementKind is DEM_CFG_DATA_FROM_SR_PORT_BOOLEAN, verify that the callback function ReadDataFunc is
    compatible to Dem_ReadDataSRBooleanFPtrType.
  - If ElementKind is DEM_CFG_DATA_FROM_SR_PORT_SINT8, verify that the callback function ReadDataFunc is
    compatible to Dem_ReadDataSRSint8FPtrType.
  - If ElementKind is DEM_CFG_DATA_FROM_SR_PORT_SINT16, verify that the callback function ReadDataFunc is
    compatible to Dem_ReadDataSRSint16FPtrType.
  - If ElementKind is DEM_CFG_DATA_FROM_SR_PORT_SINT32, verify that the callback function ReadDataFunc is
    compatible to Dem_ReadDataSRSint32FPtrType.
  - If ElementKind is DEM_CFG_DATA_FROM_SR_PORT_SINT16_INTEL, verify that the callback function ReadDataFunc is
    compatible to Dem_ReadDataSRSint16FPtrType.
  - If ElementKind is DEM_CFG_DATA_FROM_SR_PORT_SINT32_INTEL, verify that the callback function ReadDataFunc is
    compatible to Dem_ReadDataSRSint32FPtrType.
  - If ElementKind is DEM_CFG_DATA_FROM_SR_PORT_SINT8_N, verify that the callback function ReadDataFunc is
    compatible to Dem_ReadDataSRSint8FPtrType.
  - If ElementKind is DEM_CFG_DATA_FROM_SR_PORT_UINT8, verify that the callback function ReadDataFunc is
    compatible to Dem_ReadDataStandardFPtrType.
  - If ElementKind is DEM_CFG_DATA_FROM_SR_PORT_UINT16, verify that the callback function ReadDataFunc is
    compatible to Dem_ReadDataSRUint16FPtrType.
  - If ElementKind is DEM_CFG_DATA_FROM_SR_PORT_UINT32, verify that the callback function ReadDataFunc is
    compatible to Dem_ReadDataSRUint32FPtrType.
  - If ElementKind is DEM_CFG_DATA_FROM_SR_PORT_UINT16_INTEL, verify that the callback function ReadDataFunc is
    compatible to Dem_ReadDataSRUint16FPtrType.
  - If ElementKind is DEM_CFG_DATA_FROM_SR_PORT_UINT32_INTEL, verify that the callback function ReadDataFunc is
    compatible to Dem_ReadDataSRUint32FPtrType.
  - If ElementKind is DEM_CFG_DATA_FROM_SR_PORT_UINT8_N, verify that the callback function ReadDataFunc is
    compatible to Dem_ReadDataStandardFPtrType.
  - Verify that all other callback functions ReadDataFunc in the table are set to NULL_PTR.
  The function pointer types are defined in Dem_Types.h. The table is generated into Dem_Lcfg.c.

\CM CM_DEM_S_CALL_DESTINATIONBUFFER
  [SMI-105856] The user of MICROSAR Safe shall verify that all function callbacks configured in table
  Dem_Cfg_DataElementTable write at most ElementSize bytes.
  E.g. for a line {  DEM_CFG_DATA_FROM_CBK, 4U, (Dem_ReadDataFPtrType)Rte_Call_CBReadData_DemExternalCSDataElementClass_ReadData }
  verify that the application runnable triggered by the Rte when the Dem invokes operation 'ReadData' on PortPrototype
  'DemExternalCSDataElementClass' will at most write 4 bytes.
  The table is generated into Dem_Lcfg.c.

\CM CM_DEM_S_CALL_EXTERNAL_FUNCTIONMACRO_WRITE_DATAPTR
  [SMI-106376] If the following macros are not defined to a NULL_PTR, the user of MICROSAR Safe shall verify that the configured 
  function only writes the corresponding size to the data pointer.
  DEM_CFG_OEMCBKGETEXTERNALTESTERSTATUS_FUNC: Verify that only one byte (a boolean value) is written by the referenced function.
  DEM_CFG_OEMCBKGETCURRENTODOMETER_FUNC: Verify that at most 4 bytes (uint32 odometer value) are written by the referenced function.

\CM CM_DEM_S_CALL_EXTERNAL_FUNCTIONTABLE_WRITE_DATAPTR
  [SMI-623276] The user of MICROSAR Safe shall verify that if the function callbacks configured in table _Dem_Cfg__{{<CallbackType>}} or by the 
  constant access macro _Dem_Cfg_Get_{{<CallbackType>}} are not defined as NULL_PTR, they only write the corresponding size to the data pointer.
  CallbackClearEventAllowed: Verify that only one byte (a boolean value) is written by the referenced functions.
  CallbackGetFdc: Verify that only one byte (a signed integer value) is written by the referenced functions.

\CM CM_DEM_S_CHECK_NVBLOCKID
  [SMI-2196] The user of MICROSAR Safe shall verify that the NV Block IDs listed in table Dem_Cfg_MemoryBlockId are
  intended to be used exclusively by Dem. This is required for SMI-22.
  The table is generated into Dem_Lcfg.c.

\CM CM_DEM_S_CHECK_NVBLOCK_LENGTH
  [SMI-2197] The user of MICROSAR Safe shall verify that the configured NvM block size of the NV blocks referenced
  in table Dem_Cfg_MemoryBlockId is equal to the data size in table Dem_Cfg_MemoryDataSize for the same index.
  The user of MICROSAR Safe shall verify that the NV block is also configured to use the RAM buffer referenced in
  Dem_Cfg_MemoryDataPtr for the same index. This is required for SMI-23.
  E.g. Verify that the NvM block descriptor referenced in Dem_Cfg_MemoryBlockId[1] is configured with data length
  Dem_Cfg_MemoryDataSize[1] and RAM buffer Dem_Cfg_MemoryDataPtr[1].
  The tables Dem_Cfg_MemoryBlockId, Dem_Cfg_MemoryDataSize and Dem_Cfg_MemoryDataPtr are generated into Dem_Lcfg.c.
  Refer to the NvM for the location of the tables generated by the NvM to verify the correct configuration.

\CM CM_DEM_S_TIMESERIESINDEX_TYPE
  [SMI-2200] Verify that for each index in [DEM_CFG_MEMORY_TIME_SERIES_INDEX .. DEM_CFG_MEMORY_TIME_SERIES_INDEX + DEM_CFG_GLOBAL_TIMESERIES_SNAPSHOTS_SIZE[
  there is a timeseries entry pointer (Dem_Cfg_TimeSeriesEntry_XX) configured in Dem_Cfg_MemoryDataPtr[index] .
  Reason for SMI: MSSV cannot evaluate function like macros - needed to get the type of the initializer

\CM CM_DEM_S_CHECK_OSAPPLICATION_IN_SATELLITEINFOTABLE
  [SMI-166740] In a multi satellite configuration the user of MICROSAR Safe shall verify that the table Dem_Cfg_SatelliteInfo is
  generated into Dem_Lcfg.c. Furthermore, the user of MICROSAR Safe shall verify that all entries in the same line of this table
  are assigned to the same OsApplication. E.g. for OsApplication with short name OsApplication_Sat1 the corresponding line in
  table _Dem_Cfg_SatelliteInfo_ has to be composed in the following way:
  { ..., OsApplication_Sat1, &Dem_Cfg_SatelliteInfoOsApplication_Sat1.MaxDebounceValues[0],
  &Dem_Cfg_SatelliteInfoOsApplication_Sat1.DebounceLoResTimer, &Dem_Cfg_SatelliteInfoOsApplication_Sat1.SatelliteStatus,
  &Dem_Cfg_SatelliteInfoOsApplication_Sat1.SatelliteData[0], &Dem_Cfg_SatelliteInfoOsApplication_Sat1.SatelliteExtendedData[0] }

\CM CM_DEM_S_SIZEOF_SATELLITEINFOTYPE_ARRAYS
  [SMI-105857] The user of MICROSAR Safe shall verify that, if the following arrays are generated and referenced in table Dem_Cfg_SatelliteInfo, the
  size of each array is equal to Dem_Cfg_SatelliteInfo[].EventCount in same line:
  - Dem_Cfg_SatelliteInfoType<X>.SatelliteData[]
  - Dem_Cfg_SatelliteInfoType<X>.SatelliteExtendedData[]
  - Dem_Cfg_SatelliteInfoType<X>.MaxDebounceValues[]

  E.g. for a line in table Dem_Cfg_SatelliteInfo
  { 37U, ..., &Dem_Cfg_SatelliteInfoOsApplication_Master.MaxDebounceValues[0], ...,
  &Dem_Cfg_SatelliteInfoOsApplication_Master.SatelliteData[0], &Dem_Cfg_SatelliteInfoOsApplication_Master.SatelliteExtendedData[0] },
  where 37 is the EventCount, the structure Dem_Cfg_SatelliteInfoTypeOsApplication_Master should be generated as follows:
  typedef struct Dem_Cfg_SatelliteInfoTypeOsApplication_Master_s {
  volatile Dem_SatelliteData_DataType         SatelliteData[ 37 ];
  volatile Dem_SatelliteData_ExtendedDataType SatelliteExtendedData[ 37 ];
  volatile Dem_Cfg_MaxDebounceValuesType      MaxDebounceValues[ 37 ];
  }                                                                     Dem_Cfg_SatelliteInfoTypeOsApplication_Master;

  In a single satellite configuration the user shall verify that the size of the arrays referenced by the pointers returned by the function
  like macros Dem_Cfg_GetMaxDebounceValuesOfSatelliteInfo(), Dem_Cfg_GetSatelliteExtendedDataOfSatelliteInfo() and Dem_Cfg_GetSatelliteDataOfSatelliteInfo()
  is equal to the value returned by function like macro Dem_Cfg_GetEventCountOfSatelliteInfo().

  The user shall also verify that the above mentioned pointers returned by the function like macros and the pointers listed in
  the table Dem_Cfg_SatelliteInfo always point to the first element in the corresponding array.

  The user of MICROSAR Safe shall verify that if the pointer returned by the function like macro Dem_Cfg_GetMaxDebounceValuesOfSatelliteInfo()
  does not point to _Dem_Cfg_SatelliteInfo0.MaxDebounceValues[0], the function like macro is defined to NULL_PTR.

  The user of MICROSAR Safe shall verify that if the pointer returned by the function like macro _Dem_Cfg_GetSatelliteExtendedDataOfSatelliteInfo()
  does not point to _Dem_Cfg_SatelliteInfo0.SatelliteExtendedData[0], the function like macro is defined to NULL_PTR.

\CM CM_DEM_S_SIZEOF_SATELLITEINFOTYPE_POINTER
  [SMI-105858] The user of MICROSAR Safe shall verify that in a multi satellite configuration the following pointers in table 
  Dem_Cfg_SatelliteInfo in Dem_Lcfg.c, if they are generated, reference the corresponding member of Dem_Cfg_SatelliteInfo<X>:
  - &Dem_Cfg_SatelliteInfoType<X>.DebounceLoResTimer
  - &Dem_Cfg_SatelliteInfoType<X>.SatelliteStatus

  I.e. verify that the pointers in table Dem_Cfg_SatelliteInfo are generated the following way for all satellites:
 { ..., &Dem_Cfg_SatelliteInfo<X>.DebounceLoResTimer, &Dem_Cfg_SatelliteInfo<X>.SatelliteStatus, ... }
 and the structures Dem_Cfg_SatelliteInfo<X> are generated as follows into Dem_Lcfg.h:
 
 typedef struct Dem_Cfg_SatelliteInfo<X>_s {
 ...
 volatile Dem_Com_ProcessorWordType SatelliteStatus;
 Dem_Cfg_DebounceLoResTimerType DebounceLoResTimer;
 ...
 } Dem_Cfg_SatelliteInfoType<X>;

 The user of MICROSAR Safe shall verify that the pointer returned by the function like macro 
 Dem_Cfg_GetSatelliteStatusOfSatelliteInfo() always points to member Dem_Cfg_SatelliteInfo<X>.SatelliteStatus.

 The user of MICROSAR Safe shall verify that the pointer returned by the function like macro either points to 
 to Dem_Cfg_SatelliteInfo<X>.DebounceLoResTimer or the function like macro is defined to NULL_PTR.


\CM CM_DEM_S_MEMMAP_SATELLITEINFO
  [SMI-105859] The user of MICROSAR Safe has to ensure that the struct variables Dem_Cfg_SatelliteInfo<X> in Dem_Lcfg.c are
  encapsulated by the related memory mapping sections DEM_START_SEC_<X>_VAR_ZERO_INIT_UNSPECIFIED and
  DEM_STOP_SEC_<X>_VAR_ZERO_INIT_UNSPECIFIED.

  Furthermore, the user of MICROSAR Safe shall ensure by a customized memory mapping that in a multi satellite configuration each
  DemSatellite has Read/Write access to the memory sections belonging to its own partition and only Read access to those of other
  partitions. Write access to the memory sections of other partitions must be denied. Only the DemMaster has Read and Write
  access to the memory sections of all partitions.

  The memory mapping sections DEM_START_SEC_<Short name of respective /Os/OsApplication>_VAR_ZERO_INIT_UNSPECIFIED and
  DEM_STOP_SEC_<Short name of respective /Os/OsApplication>_VAR_ZERO_INIT_UNSPECIFIED have to be linked to the related
  OsApplication.

\CM CM_DEM_S_SIZEOF_PROCESSEDCOMBINEDDTCGROUP
  [SMI-376150] The user of MICROSAR Safe shall verify that the array type Dem_Cfg_ProcessedCombinedDTCGroupType is
  defined for each index in range [0..DEM_CFG_PROCESSEDCOMBINEDDTCGROUP_SIZE[ .

\CM CM_DEM_S_CHECK_MEMORYENTRYTABLE
  [SMI-524392] The user of MICROSAR Safe must verify that each entry in table Dem_Cfg_MemoryEntry is a valid pointer to a 
  global variable with data type Dem_Cfg_PrimaryEntryType, defined by the DEM.
  In a configuration variant wherein the aforementioned table does not exist, the user of MICROSAR Safe must ensure that 
  the macro Dem_Cfg_GetMemoryEntry(Id) always returns a valid pointer to a global variable with data type
  Dem_Cfg_PrimaryEntryType defined by the DEM, for Id in [0, Dem_Cfg_GetSizeOfMemoryEntry()[.
  The table Dem_Cfg_MemoryEntry is generated in Dem_Lcfg.c and the macro Dem_Cfg_GetMemoryEntry(Id) is defined in Dem_Lcfg.h

*/

/*!
 * \}
 */


/* ********************************************************************************************************************
 *  END OF FILE: DEM.C
 *********************************************************************************************************************/
