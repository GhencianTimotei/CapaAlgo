/**********************************************************************************************************************
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
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  VStdLib_Cfg.h
 *        \brief  Configuration of the generic Vector Standard Library (VStdLib_GenericAsr)
 *
 *      \details  This file contains the project specific configuration of the generic Vector Standard Library.
 *                It provides also the possibility of overwriting the public APIs with project specific optimized 
 *                implementations.
 *
 *********************************************************************************************************************/

#if !defined (VSTDLIB_CFG_H)
# define VSTDLIB_CFG_H

/**
 * Additional include files
 *
 * If necessary include additional files below (e.g. if VSTDLIB_USE_LIBRARY_FUNCTIONS is defined to STD_ON).
 */
/* # include ... */

/**********************************************************************************************************************
 *  General configuration
 *********************************************************************************************************************/

/**
 * VSTDLIB_USE_LIBRARY_FUNCTIONS
 *
 * If set to STD_ON the memory initialization and memory copy APIs are mapped to external functions (e.g. compiler
 * libraries or other implementations that are optimized for the target platform). As the generic VStdLib implementation
 * provides optimized routines only for 32bit platforms, this is recommended when using MCUs with other architectures.
 *
 * Values:
 * STD_ON  - Use external memory manipulation functions - requires additional configuration, see below.
 * STD_OFF - Use generic memory manipulation functions provided by VStdLib
 *
 * Default:
 * STD_OFF
 */
# define VSTDLIB_USE_LIBRARY_FUNCTIONS STD_OFF

/**
 * VSTDLIB_RUNTIME_OPTIMIZATION
 *
 * If set to STD_ON optimized routines are used to increase the performance of the memory manipulation functions.
 * The setting of this define is only relevant if VSTDLIB_USE_LIBRARY_FUNCTIONS == STD_OFF.
 *
 * Values:
 * STD_ON  - Use optimized routines for memory operations (runtime efficient, but increases code size)
 * STD_OFF - Use simple routines for memory operations (code efficient, but significantly increases runtime)
 *
 * Default:
 * STD_ON
 */
# define VSTDLIB_RUNTIME_OPTIMIZATION STD_ON

/**
 * VSTDLIB_USE_JUMPTABLES
 *
 * If set to STD_ON jump tables are used to increase the performance of the memory manipulation functions.
 * The setting of this define is only relevant if VSTDLIB_USE_LIBRARY_FUNCTIONS == STD_OFF and
 * VSTDLIB_RUNTIME_OPTIMIZATION == STD_ON.
 *
 * Values:
 * STD_ON  - Use jump tables for memory operations (runtime efficient in general, but may depend on compiler)
 * STD_OFF - Use loops for memory operations (code efficient, also use this if the compiler generates no efficient
 *           code for the jump tables)
 *
 * Default:
 * STD_ON
 */
# define VSTDLIB_USE_JUMPTABLES STD_ON

/**
 * VSTDLIB_DEV_ERROR_DETECT
 *
 * If set to STD_ON the development error detection is enabled. In this case the pointer arguments of all global
 * module functions are checked. If any NULL_PTR is passed, these functions return without performing any action.
 * Please note that this setting has no influence on MICROSAR SafeBSW.
 *
 * Values:
 * STD_ON  - Check function arguments
 * STD_OFF - Disable development error detection
 *
 * Default:
 * STD_OFF
 */
# define VSTDLIB_DEV_ERROR_DETECT STD_OFF

/**
 * VSTDLIB_DEV_ERROR_REPORT
 *
 * If set to STD_ON the development error reporting is enabled. In this case Det_ReportError() is called if any
 * development error is detected.
 *
 * Values:
 * STD_ON  - Enable calls of Det_ReportError() - requires VSTDLIB_DEV_ERROR_DETECT also to be defined to STD_ON
 * STD_OFF - Disable development error reporting
 *
 * Default:
 * STD_OFF
 */
# define VSTDLIB_DEV_ERROR_REPORT STD_OFF

/**
 * VSTDLIB_VERSION_INFO_API
 *
 * If set to STD_ON the API VStdLib_GetVersionInfo() is provided.
 *
 * Values:
 * STD_ON  - Provide the version info API
 * STD_OFF - Do not provide the version info API
 *
 * Default:
 * STD_OFF
 */
# define VSTDLIB_VERSION_INFO_API STD_OFF

/**
 * VSTDLIB_DUMMY_STATEMENT
 *
 * Expression that is used for dummy statements to avoid compile warnings about unused identifiers.
 *
 * Example values:
 * (void)(v)
 * (v)=(v)
 * or leave the definition empty to disable the usage of dummy statements
 *
 * Default:
 * (void)(v)
 */
# define VSTDLIB_DUMMY_STATEMENT(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/**
 * VSTDLIB_USE_8BIT_SEARCH_LIBRARY_FUNCTIONS
 *
 * If set to STD_ON all 8-bit bit search APIs are mapped to external functions (e.g. compiler libraries or
 * other implementations that are optimized for the target platform).
 *
 * Values:
 * STD_ON  - Use external bit search functions - requires additional configuration, see below.
 * STD_OFF - Use generic 8-bit bit search functions provided by VStdLib
 *
 * Default:
 * STD_OFF
 */
# define VSTDLIB_USE_8BIT_SEARCH_LIBRARY_FUNCTIONS STD_OFF

/**
 * VSTDLIB_USE_16BIT_SEARCH_LIBRARY_FUNCTIONS
 *
 * If set to STD_ON all 16-bit bit search APIs are mapped to external functions (e.g. compiler libraries or
 * other implementations that are optimized for the target platform).
 *
 * Values:
 * STD_ON  - Use external bit search functions - requires additional configuration, see below.
 * STD_OFF - Use generic 16-bit bit search functions provided by VStdLib
 *
 * Default:
 * STD_OFF
 */
# define VSTDLIB_USE_16BIT_SEARCH_LIBRARY_FUNCTIONS STD_OFF

/**
 * VSTDLIB_USE_32BIT_SEARCH_LIBRARY_FUNCTIONS
 *
 * If set to STD_ON all 32-bit bit search APIs are mapped to external functions (e.g. compiler libraries or
 * other implementations that are optimized for the target platform).
 *
 * Values:
 * STD_ON  - Use external bit search functions - requires additional configuration, see below.
 * STD_OFF - Use generic 32-bit bit search functions provided by VStdLib
 *
 * Default:
 * STD_OFF
 */
# define VSTDLIB_USE_32BIT_SEARCH_LIBRARY_FUNCTIONS STD_OFF

/**
 * VSTDLIB_USE_64BIT_SEARCH_LIBRARY_FUNCTIONS
 *
 * If set to STD_ON all 64-bit bit search APIs are mapped to external functions (e.g. compiler libraries or
 * other implementations that are optimized for the target platform).
 * The setting of this define is only allowed if PLATFORM_SUPPORT_SINT64_UINT64 is defined.
 *
 * Values:
 * STD_ON  - Use external bit search functions - requires additional configuration, see below.
 * STD_OFF - Use generic 64-bit bit search functions provided by VStdLib
 *
 * Default:
 * STD_OFF
 */
# define VSTDLIB_USE_64BIT_SEARCH_LIBRARY_FUNCTIONS STD_OFF

/**********************************************************************************************************************
 *  Additional configuration if VSTDLIB_USE_LIBRARY_FUNCTIONS == STD_ON
 *********************************************************************************************************************/

# if (VSTDLIB_USE_LIBRARY_FUNCTIONS == STD_ON)
/**
 * Memory manipulation library functions.
 *
 * If VSTDLIB_USE_LIBRARY_FUNCTIONS is set to STD_ON it is necessary to specify the memory initialization and memory 
 * copy APIs by overwriting the definitions below. The error directive has to be removed.
 *
 * NOTE:
 * - If the external functionality is not able to handle more than 65535 bytes it is necessary to define
 *   VSTDLIB_SUPPORT_LARGE_DATA to STD_OFF.
 * - It has to be ensured that the specified functions are able to copy from and to all memory locations independently
 *   of the pointer length. The specified functions must behave synchronously.
 */
#  error "Verify the setting for VSTDLIB_SUPPORT_LARGE_DATA and fill the macros in this section with correct values!"

#  define VSTDLIB_SUPPORT_LARGE_DATA             STD_ON

/* PRQA S 3453 FUNCTION_LIKE_MACRO */ /* MD_MSR_FctLikeMacro */

/* Set nCnt bytes to zero at pDst (any alignment) */
#  define VStdLib_MemClr(pDst, nCnt)             memset((pDst), 0, (nCnt))

/* Set nCnt bytes to the character nPattern at pDst (any alignment) */
#  define VStdLib_MemSet(pDst, nPattern, nCnt)   memset((pDst), (nPattern), (nCnt))

/* Copy nCnt bytes from pSrc to pDst (any alignment) */
#  define VStdLib_MemCpy(pDst, pSrc, nCnt)       memcpy((pDst), (pSrc), (nCnt))

/* Copy nCnt 16bit blocks from pSrc to pDst (both pointers 16-bit aligned) */
#  define VStdLib_MemCpy16(pDst, pSrc, nCnt)     memcpy((pDst), (pSrc), ((nCnt)<<1))

/* Copy nCnt 32bit blocks from pSrc to pDst (both pointers 32-bit aligned) */
#  define VStdLib_MemCpy32(pDst, pSrc, nCnt)     memcpy((pDst), (pSrc), ((nCnt)<<2))

/* PRQA L:FUNCTION_LIKE_MACRO */

# endif /* VSTDLIB_USE_LIBRARY_FUNCTIONS == STD_ON */

/**********************************************************************************************************************
 *  Additional configuration if VSTDLIB_USE_8BIT_SEARCH_LIBRARY_FUNCTIONS == STD_ON
 *********************************************************************************************************************/

# if (VSTDLIB_USE_8BIT_SEARCH_LIBRARY_FUNCTIONS == STD_ON)
/**
 * Bit search library functions.
 *
 * If VSTDLIB_USE_8BIT_SEARCH_LIBRARY_FUNCTIONS is set to STD_ON it is necessary to specify 8-bit bit search APIs by
 * overwriting the definitions below. The error directive has to be removed.
 *
 * The 8-bit search APIs to get the highest/lowest bit position of a set/unset bit have to use the return value
 * VSTDLIB_BITPOS_NA, if the value contains no set/unset bit.
 *
 * The 8-bit search APIs to get the bit count of leading/trailing ones/zeros have to use the return value
 * VSTDLIB_BITCNT_NA, if the value contains no unset/set bit.
 *
 */
#  error "Fill the macros in this section with correct values!"

/* PRQA S 3453 FUNCTION_LIKE_MACRO */ /* MD_MSR_FctLikeMacro */

/* Returns the highest bit position of a set bit in the specified 8-bit value */
#  define VStdLib_GetHighestBitPosOne8(value)

/* Returns the highest bit position of an unset bit in the specified 8-bit value */
#  define VStdLib_GetHighestBitPosZero8(value)

/* Returns the lowest bit position of a set bit in the specified 8-bit value */
#  define VStdLib_GetLowestBitPosOne8(value)

/* Returns the lowest bit position of an unset bit in the specified 8-bit value */
#  define VStdLib_GetLowestBitPosZero8(value)

/* Returns the count of set bits preceding the highest unset bit in the specified 8-bit value */
#  define VStdLib_GetCountLeadingOnes8(value)

/* Returns the count of unset bits preceding the highest set bit in the specified 8-bit value */
#  define VStdLib_GetCountLeadingZeros8(value)

/* Returns the count of set bits following the lowest unset bit in the specified 8-bit value */
#  define VStdLib_GetCountTrailingOnes8(value)

/* Returns the count of unset bits following the lowest set bit in the specified 8-bit value */
#  define VStdLib_GetCountTrailingZeros8(value)

/* PRQA L:FUNCTION_LIKE_MACRO */

# endif /* VSTDLIB_USE_8BIT_SEARCH_LIBRARY_FUNCTIONS == STD_ON */

/**********************************************************************************************************************
 *  Additional configuration if VSTDLIB_USE_16BIT_SEARCH_LIBRARY_FUNCTIONS == STD_ON
 *********************************************************************************************************************/

# if (VSTDLIB_USE_16BIT_SEARCH_LIBRARY_FUNCTIONS == STD_ON)
/**
 * Bit search library functions.
 *
 * If VSTDLIB_USE_16BIT_SEARCH_LIBRARY_FUNCTIONS is set to STD_ON it is necessary to specify 16-bit bit search APIs by
 * overwriting the definitions below. The error directive has to be removed.
 *
 * The 16-bit search APIs to get the highest/lowest bit position of a set/unset bit have to use the return value
 * VSTDLIB_BITPOS_NA, if the value contains no set/unset bit.
 *
 * The 16-bit search APIs to get the bit count of leading/trailing ones/zeros have to use the return value
 * VSTDLIB_BITCNT_NA, if the value contains no unset/set bit.
 *
 */
#  error "Fill the macros in this section with correct values!"

/* PRQA S 3453 FUNCTION_LIKE_MACRO */ /* MD_MSR_FctLikeMacro */

/* Returns the highest bit position of a set bit in the specified 16-bit value */
#  define VStdLib_GetHighestBitPosOne16(value)

/* Returns the highest bit position of an unset bit in the specified 16-bit value */
#  define VStdLib_GetHighestBitPosZero16(value)

/* Returns the lowest bit position of a set bit in the specified 16-bit value */
#  define VStdLib_GetLowestBitPosOne16(value)

/* Returns the lowest bit position of an unset bit in the specified 16-bit value */
#  define VStdLib_GetLowestBitPosZero16(value)

/* Returns the count of set bits preceding the highest unset bit in the specified 16-bit value */
#  define VStdLib_GetCountLeadingOnes16(value)

/* Returns the count of unset bits preceding the highest set bit in the specified 16-bit value */
#  define VStdLib_GetCountLeadingZeros16(value)

/* Returns the count of set bits following the lowest unset bit in the specified 16-bit value */
#  define VStdLib_GetCountTrailingOnes16(value)

/* Returns the count of unset bits following the lowest set bit in the specified 16-bit value */
#  define VStdLib_GetCountTrailingZeros16(value)

/* PRQA L:FUNCTION_LIKE_MACRO */

# endif /* VSTDLIB_USE_16BIT_SEARCH_LIBRARY_FUNCTIONS == STD_ON */

/**********************************************************************************************************************
 *  Additional configuration if VSTDLIB_USE_32BIT_SEARCH_LIBRARY_FUNCTIONS == STD_ON
 *********************************************************************************************************************/

# if (VSTDLIB_USE_32BIT_SEARCH_LIBRARY_FUNCTIONS == STD_ON)
/**
 * Bit search library functions.
 *
 * If VSTDLIB_USE_32BIT_SEARCH_LIBRARY_FUNCTIONS is set to STD_ON it is necessary to specify 32-bit bit search APIs by
 * overwriting the definitions below. The error directive has to be removed.
 *
 * The 32-bit search APIs to get the highest/lowest bit position of a set/unset bit have to use the return value
 * VSTDLIB_BITPOS_NA, if the value contains no set/unset bit.
 *
 * The 32-bit search APIs to get the bit count of leading/trailing ones/zeros have to use the return value
 * VSTDLIB_BITCNT_NA, if the value contains no unset/set bit.
 *
 */
#  error "Fill the macros in this section with correct values!"

/* PRQA S 3453 FUNCTION_LIKE_MACRO */ /* MD_MSR_FctLikeMacro */

/* Returns the highest bit position of a set bit in the specified 32-bit value */
#  define VStdLib_GetHighestBitPosOne32(value)

/* Returns the highest bit position of an unset bit in the specified 32-bit value */
#  define VStdLib_GetHighestBitPosZero32(value)

/* Returns the lowest bit position of a set bit in the specified 32-bit value */
#  define VStdLib_GetLowestBitPosOne32(value)

/* Returns the lowest bit position of an unset bit in the specified 32-bit value */
#  define VStdLib_GetLowestBitPosZero32(value)

/* Returns the count of set bits preceding the highest unset bit in the specified 32-bit value */
#  define VStdLib_GetCountLeadingOnes32(value)

/* Returns the count of unset bits preceding the highest set bit in the specified 32-bit value */
#  define VStdLib_GetCountLeadingZeros32(value)

/* Returns the count of set bits following the lowest unset bit in the specified 32-bit value */
#  define VStdLib_GetCountTrailingOnes32(value)

/* Returns the count of unset bits following the lowest set bit in the specified 32-bit value */
#  define VStdLib_GetCountTrailingZeros32(value)

/* PRQA L:FUNCTION_LIKE_MACRO */

# endif /* VSTDLIB_USE_32BIT_SEARCH_LIBRARY_FUNCTIONS == STD_ON */

/**********************************************************************************************************************
 *  Additional configuration if VSTDLIB_USE_64BIT_SEARCH_LIBRARY_FUNCTIONS == STD_ON
 *********************************************************************************************************************/

# if ((defined PLATFORM_SUPPORT_SINT64_UINT64) && (VSTDLIB_USE_64BIT_SEARCH_LIBRARY_FUNCTIONS == STD_ON))
/**
 * Bit search library functions.
 *
 * If VSTDLIB_USE_64BIT_SEARCH_LIBRARY_FUNCTIONS is set to STD_ON it is necessary to specify 64-bit bit search APIs by
 * overwriting the definitions below. The error directive has to be removed.
 *
 * The 64-bit search APIs to get the highest/lowest bit position of a set/unset bit have to use the return value
 * VSTDLIB_BITPOS_NA, if the value contains no set/unset bit.
 *
 * The 64-bit search APIs to get the bit count of leading/trailing ones/zeros have to use the return value
 * VSTDLIB_BITCNT_NA, if the value contains no unset/set bit.
 *
 */
#  error "Fill the macros in this section with correct values!"

/* PRQA S 3453 FUNCTION_LIKE_MACRO */ /* MD_MSR_FctLikeMacro */

/* Returns the highest bit position of a set bit in the specified 64-bit value */
#  define VStdLib_GetHighestBitPosOne64(value)

/* Returns the highest bit position of an unset bit in the specified 64-bit value */
#  define VStdLib_GetHighestBitPosZero64(value)

/* Returns the lowest bit position of a set bit in the specified 64-bit value */
#  define VStdLib_GetLowestBitPosOne64(value)

/* Returns the lowest bit position of an unset bit in the specified 64-bit value */
#  define VStdLib_GetLowestBitPosZero64(value)

/* Returns the count of set bits preceding the highest unset bit in the specified 64-bit value */
#  define VStdLib_GetCountLeadingOnes64(value)

/* Returns the count of unset bits preceding the highest set bit in the specified 64-bit value */
#  define VStdLib_GetCountLeadingZeros64(value)

/* Returns the count of set bits following the lowest unset bit in the specified 64-bit value */
#  define VStdLib_GetCountTrailingOnes64(value)

/* Returns the count of unset bits following the lowest set bit in the specified 64-bit value */
#  define VStdLib_GetCountTrailingZeros64(value)

/* PRQA L:FUNCTION_LIKE_MACRO */

# endif /* (defined PLATFORM_SUPPORT_SINT64_UINT64) && (VSTDLIB_USE_64BIT_SEARCH_LIBRARY_FUNCTIONS == STD_ON) */

/**********************************************************************************************************************
 * Compatibility for legacy Vector modules
 *********************************************************************************************************************/

# if defined(VSTD_ENABLE_INTCTRL_HANDLING) || defined(VSTD_ENABLE_DEFAULT_INTCTRL) || \
     defined(VSTD_ENABLE_OSEK_INTCTRL) || defined(VSTD_ENABLE_APPL_INTCTRL)
/**
 * Compatibility for legacy Vector modules.
 *
 * Legacy Vector modules that are used in a MICROSAR stack might rely on interrupt handling functionalities that are
 * no longer supported by VStdLib. Map relevant calls to functionalities that are provided by the MICROSAR stack or
 * application and remove the error directive. VStdSuspendAllInterrupts() and VStdResumeAllInterrupts() can be mapped
 * to OS services or an exclusive area that is provided by the BSW scheduler for example.
 */
#  error "VStdLib_GenericAsr does not support interrupt control handling, provide a mapping in this section!"

# endif

/**********************************************************************************************************************
 *  Do not modify anything below
 *********************************************************************************************************************/

# define VSTDLIB_CFG_MAJOR_VERSION     (3u)
# define VSTDLIB_CFG_MINOR_VERSION     (0u)

#endif /* VSTDLIB_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: VStdLib_Cfg.h
 *********************************************************************************************************************/
