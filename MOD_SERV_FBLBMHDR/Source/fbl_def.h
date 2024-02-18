/***********************************************************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief        Main definitions for the Flash Boot Loader
 *
 *  --------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  --------------------------------------------------------------------------------------------------------------------
 *  Achim Strobelt                Ach           Vector Informatik GmbH
 *  Daniel Moessner               DlM           Vector Informatik GmbH
 *  Torben Stoessel               TnS           Vector Informatik GmbH
 *  Christian Baeuerle            CB            Vector Informatik GmbH
 *  Joern Herwig                  JHg           Vector Informatik GmbH
 *  Marco Riedl                   Rie           Vector Informatik GmbH
 *  Daniel Koebel                 DKl           Vector Informatik GmbH
 *  Dan Jiga                      JDn           Vector Informatik GmbH
 *  Thomas Bezold                 TBe           Vector Informatik GmbH
 *  Matteo Trovo                  TMo           Vector Informatik GmbH
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  04.00.00   2016-02-26  Ach     ESCAN00088307    Rework to support FblMain 3.xx
 *                                 ESCAN00088433    Moved assertion specific code to fbl_assert.h
 *  04.00.01   2016-07-15  DlM     ESCAN00091011    Added programming voltage check defines
 *  04.01.00   2016-08-18  TnS     ESCAN00091531    Updated support of HMC
 *  04.02.00   2016-10-31  CB      ESCAN00092597    Added support for SYMC SLP2
 *  04.02.01   2017-05-09  JHg     ESCAN00095090    Include upper-case Fbl_Cfg.h for DaVinci Configurator use-case
 *                         Rie     ESCAN00095204    No changes
 *  04.03.00   2017-07-28  CB      ESCAN00095458    Removed unneeded client switches
 *                         Ach     ESCAN00096096    Added fallback activation of NV-Wrapper and Vector SecMod
 *  04.04.00   2018-02-26  DKl     ESCAN00098503    Updated support of Toyota SLP4
 *  04.04.01   2018-07-06  DKl     ESCAN00099860    Compiler error: shift count is too large
 *  04.05.00   2018-09-13  Rie     ESCAN00100731    Added additional flags for BootManager use-case
 *             2018-11-20  DKl     ESCAN00101393    Removed support for Ford SLP6
 *  04.06.00   2019-12-03  JDn     FBL-999          Add define V_ENABLE_USE_DUMMY_STATEMENTS
 *  05.00.00   2020-03-02  TBe     FBL-949          Add include for FblBm_Cfg.h
 *                                 ESCAN00105231    Compiler error: define syntax
 *  05.01.00   2020-04-29  TMo     FBL-1584         Adding OTA startup support
 *  05.02.00   2020-05-08  Rie     FBL-1414         Adding One-Step-Updater support
 *  05.03.00   2020-07-16  Rie     FBL-2021         Adding OTA response after reset support
 **********************************************************************************************************************/

#ifndef FBL_DEF_H
#define FBL_DEF_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/

/* Basic configurations */
#include "v_cfg.h"

#if defined( VGEN_GENY ) && !defined( VGEN_ENABLE_CANFBL )
/* This file was obviously not included in FBL, so it's used in user application
   check if MAGIC_NUMBER was generated. In this case we have to remove the check for the
   following include because FBL generation use different number than application */
# if defined( MAGIC_NUMBER )
#  undef MAGIC_NUMBER
# endif
#endif

#include "FblBm_Cfg.h"

/* Configuration file for flash boot loader */
#if defined( V_GEN_GENERATOR_MSR )
# include "Fbl_Cfg.h"
#else /* VGEN_GENY */
# include "fbl_cfg.h"
#endif /* VGEN_GENY */
#if defined( VGEN_GENY ) && !defined( VGEN_ENABLE_CANFBL )
/* The last include redefined MAGIC_NUMBER, which is not relevant for application so
   invalidate it */
# if defined( MAGIC_NUMBER )
#  undef MAGIC_NUMBER
# endif
#endif

/* Basic type definitions */
#include "v_def.h"

#if defined( FBL_ENABLE_SECMOD_VECTOR )
# include "SecM_cfg.h"
#endif

/* In application either remove FBL_ENABLE_ASSERTION switch or provide fbl_assert.h */
# include "fbl_assert.h"

/* PRQA S 3453 EOF */ /* MD_MSR_19.7 */
/* PRQA S 3458 EOF */ /* MD_MSR_19.4 */

/***********************************************************************************************************************
 *  VERSION
 **********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : FblDef CQComponent : Implementation */
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define FBLDEF_VERSION          0x0503u
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define FBLDEF_RELEASE_VERSION  0x00u

/***********************************************************************************************************************
 *  DEFINES
 **********************************************************************************************************************/

/* Select usage of unified main interface */
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define FBL_DEF_ENABLE_NON_KB_MAIN

#ifndef NULL
# define NULL ((void *)0)
#endif

   /* Activate NV-Wrapper if not explicitly configured */
# if !defined( FBL_ENABLE_WRAPPER_NV ) && \
     !defined( FBL_DISABLE_WRAPPER_NV )
#  define FBL_ENABLE_WRAPPER_NV
# endif
   /* Activate Vector SecMod if not explicitly configured */
# if !defined( FBL_ENABLE_SECMOD_VECTOR ) && \
     !defined( FBL_DISABLE_SECMOD_VECTOR )
#  define FBL_ENABLE_SECMOD_VECTOR
# endif

/* Define return code of several functions   */
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define kFblOk                0x00u
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define kFblFailed            0x01u

/* Defines for programming voltage check */
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define kFblVoltageTooLow     0x01u
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define kFblVoltageTooHigh    0x02u

/* Programming request flag */
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define kProgRequest             0x00u    /**< Diagnostic programming request is reported to main */
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define kProgRequestXcp          0x01u    /**< XCP programming request is reported to main */
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define kProgRequestOta          0x02u    /**< OTA programming request is reported to main */
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define kNoProgRequest           0xFFu    /**< No programming request */

/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define kCheckStayInBootRequest  0x10u    /**< Check for stay in boot message */
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define kInitKeysRequest         0x11u    /**< Initialize crypto keys */
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define kInitMacsRequest         0x12u    /**< Initialize MACs */

/* Application validation  */
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
# define kApplValid            1u /* Application is fully programmed */
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
# define kApplInvalid          0u /* Operational software is missing */

/* Memory status (flash erased detection) */
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */     
# define kFlashErased          1u
     /* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
# define kFlashNotErased       0u


#if !defined( FBL_REPEAT_CALL_CYCLE )
/* Set default to 1ms for repeat time of main loop */
# define FBL_REPEAT_CALL_CYCLE 1u
#endif

#if defined( FBL_ENABLE_BANKING )
#else
# define FBL_CALL_TYPE
#endif /* FBL_ENABLE_BANKING */

#ifndef V_CALLBACK_NEAR
# define V_CALLBACK_NEAR
#endif
#ifndef V_API_NEAR
# define V_API_NEAR
#endif



/* Defines to convert BigEndian bytes into short or long values ********************/
# if defined( C_CPUTYPE_BIGENDIAN )
#  if defined( C_CPUTYPE_32BIT )
#   define FblBytesToShort(hi,lo)            (((vuint16)(hi) << 8) | ((vuint16)(lo) ))
#  else
#   define FblBytesToShort(hi,lo)            (vuint16)*(V_MEMRAM1_FAR vuint16 V_MEMRAM2_FAR *)(&(hi))
#  endif
# endif
# if defined( C_CPUTYPE_LITTLEENDIAN )
#  define FblBytesToShort(hi,lo)              (((vuint16)(hi) << 8) | ((vuint16)(lo) ))
# endif

# if defined( C_CPUTYPE_BIGENDIAN )
#  if defined( C_CPUTYPE_32BIT )
#   define FblBytesToLong(hiWrd_hiByt,hiWrd_loByt,loWrd_hiByt,loWrd_loByt)  \
                                         (((vuint32)(hiWrd_hiByt) << 24) |  \
                                          ((vuint32)(hiWrd_loByt) << 16) |  \
                                          ((vuint32)(loWrd_hiByt) <<  8) |  \
                                          ((vuint32)(loWrd_loByt)      )  )
#  else
#   define FblBytesToLong(hiWrd_hiByt,hiWrd_loByt,loWrd_hiByt, loWrd_loByt)  \
            (vuint32)*(V_MEMRAM1_FAR vuint32 V_MEMRAM2_FAR *)(&(hiWrd_hiByt))
#  endif
# endif
# if defined( C_CPUTYPE_LITTLEENDIAN )
#  define FblBytesToLong(hiWrd_hiByt,hiWrd_loByt,loWrd_hiByt,loWrd_loByt)  \
                                        (((vuint32)(hiWrd_hiByt) << 24) |  \
                                         ((vuint32)(hiWrd_loByt) << 16) |  \
                                         ((vuint32)(loWrd_hiByt) <<  8) |  \
                                         ((vuint32)(loWrd_loByt)      )  )
# endif
/* polyspace:begin < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define FBL_BIT0   0x01u
#define FBL_BIT1   0x02u
#define FBL_BIT2   0x04u
#define FBL_BIT3   0x08u
#define FBL_BIT4   0x10u
#define FBL_BIT5   0x20u
#define FBL_BIT6   0x40u
#define FBL_BIT7   0x80u

/* Defines for response after reset */
#define RESET_RESPONSE_NOT_REQUIRED             0x00u    /**< No response required */
#define RESET_RESPONSE_SDS_REQUIRED             0x01u    /**< Response to SesseionControl-DefaultSession required */
#define RESET_RESPONSE_ECURESET_REQUIRED        0x02u    /**< Response to EcuReset-HardReset required */
#define RESET_RESPONSE_KEYOFFON_REQUIRED        0x03u    /**< Response to EcuReset-KeyOffOnReset required */
#define RESET_RESPONSE_OSU_REQUIRED             0x04u    /**< Response to One-Step-Updater required */
#define RESET_RESPONSE_OTA_REQUIRED             0x05u    /**< Response to OTA required */
/* polyspace:end < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
/* Macros to harmonize type casts for inverting bits */
/* polyspace:begin < MISRA-C3:D4.9,2.5 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */					 
#define FblInvertBits(x,type)    ((type)~((type)(x))) /* PRQA S 0277 */ /* MD_FblDef_Invert */
#define FblInvert8Bit(x)         ((vuint8) ((x) ^ ((vuint8)0xFFu)))
#define FblInvert16Bit(x)        ((vuint16)((x) ^ ((vuint16)0xFFFFu)))
#define FblInvert32Bit(x)        ((vuint32)((x) ^ ((vuint32)0xFFFFFFFFul)))
/* polyspace:end < MISRA-C3:D4.9 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */



# define kFblDiagTimeP2             FBL_DIAG_TIME_P2MAX
# define kFblDiagTimeP2Star         FBL_DIAG_TIME_P3MAX


#define kEepFblReprogram        0xB5u

#define kEepWriteData           1u
#define kEepReadData            2u

/* Error code defines for ApplFblErrorNotification */
#define kFblErrTypeAppl         0x10u
#define kFblErrTypeFlash        0x20u
#define kFblErrTypeEeprom       0x30u
#define kFblErrTypeSec          0x40u
#define kFblErrTypeVectorTPMC   0x50u





#if defined( FBL_USE_DUMMY_STATEMENT )
# if !defined( V_ENABLE_USE_DUMMY_STATEMENT )
#  define V_ENABLE_USE_DUMMY_STATEMENT
# endif
#endif

/***********************************************************************************************************************
 *  State handling framework
 **********************************************************************************************************************/

/* State array settings */
#if defined( C_CPUTYPE_8BIT )
typedef vuint8 tFblStateBitmap;
# define FBL_STATE_BITS             8u
# define kFblStateMaskNone          0x00u
# define kFblStateMaskAll           0xFFu
# define FblInvertStates(x)         FblInvert8Bit(x)  /* PRQA S 3453 */ /* MD_MSR_19.7 */
#elif defined( C_CPUTYPE_16BIT )
typedef vuint16 tFblStateBitmap;
# define FBL_STATE_BITS             16u
# define kFblStateMaskNone          0x0000u
# define kFblStateMaskAll           0xFFFFu
# define FblInvertStates(x)         FblInvert16Bit(x) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#elif defined( C_CPUTYPE_32BIT )
/* polyspace:begin < MISRA-C3:2.3 : Not a defect : Justify with annotations > Should be kept for future usage */
typedef vuint32 tFblStateBitmap;
# define FBL_STATE_BITS             32u
# define kFblStateMaskNone          0x00000000ul
# define kFblStateMaskAll           0xFFFFFFFFul
/* polyspace < MISRA-C3:D4.9 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */
# define FblInvertStates(x)         FblInvert32Bit(x) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#else
# error "Bit count of CPU not supported."
#endif

/* State mask build macros */
/* PRQA S 3453 10 */ /* MD_MSR_19.7 */
/* polyspace:begin < MISRA-C3:D4.9 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */
#define FBL_STATE_MASK(bit)               ((tFblStateBitmap)(1ul << ((bit) % FBL_STATE_BITS)))
#define FBL_STATE_MULTIMASK(min, max)     ((((kFblStateMaskAll) >> ((min) % FBL_STATE_BITS)) << ((min) % FBL_STATE_BITS)) ^ (((kFblStateMaskAll) >> (((max) + 1u) % FBL_STATE_BITS)) << (((max) + 1u) % FBL_STATE_BITS)))
#define FBL_STATE_MASKLONG(bit)           (1ul << (bit))
#define FBL_STATE_MULTIMASKLONG(min, max) ((((~0ul) >> (min)) << (min)) ^ (((max) < (STATE_BITS - 1u)) ? (((~0ul) >> ((max) + 1u)) << ((max) + 1u)) : 0ul))
#define FBL_STATE_INDEX(bit)              ((bit) / FBL_STATE_BITS)
#define FBL_STATE_SET(arr, bit)           ((arr)[FBL_STATE_INDEX(bit)] |= FBL_STATE_MASK(bit))
#define FBL_STATE_CLR(arr, bit)           ((arr)[FBL_STATE_INDEX(bit)] &= FblInvertStates(FBL_STATE_MASK(bit)))
#define FBL_STATE_MULTICLR(arr, min, max) ((arr)[FBL_STATE_INDEX(min)] &= FblInvertStates(FBL_STATE_MULTIMASK((min), (max))))
#define FBL_STATE_TEST(arr, bit)          (((arr)[FBL_STATE_INDEX(bit)] & FBL_STATE_MASK(bit)) == FBL_STATE_MASK(bit))
/* polyspace:end < MISRA-C3:D4.9 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */

/***********************************************************************************************************************
 *  TYPEDEFS (basic types)
 **********************************************************************************************************************/
/* polyspace:begin < MISRA-C3:2.3 : Not a defect : Justify with annotations > Should be kept for future usage */
typedef vuint8  tFblErrorType;
typedef vuint16 tFblErrorCode;

typedef vuint8 tFblResult;                    /**< FBL result codes */
typedef vuint8 tFblProgStatus;                /**< Status of reprogramming flag */
typedef vuint8 tApplStatus;                   /**< Application valid status */
typedef vuint8 tMagicFlag;                    /**< Application valid flag */
typedef vuint8 tFlashStatus;                  /**< Flash erased status flag */
/* polyspace:end < MISRA-C3:2.3 : Not a defect : Justify with annotations > Should be kept for future usage */
/* The below bootloader address types always define logical addresses.              */
/* This is important for those platforms which provide a paged physical memory      */
/* address space. For those platforms with linear physical address space, logical   */
/* and physical addresses are identical.                                            */
#if defined( C_CPUTYPE_8BIT ) && !defined( FBL_PROCESSOR_BANKED )
typedef vuint16 FBL_ADDR_TYPE;
typedef vuint16 FBL_MEMSIZE_TYPE;
# define MEMSIZE_OK
#else
typedef vuint32 FBL_ADDR_TYPE;
typedef vuint32 FBL_MEMSIZE_TYPE;
# define MEMSIZE_OK
#endif
#if defined( MEMSIZE_OK )
#else
# error "Error in FBL_DEF.H: C_CPUTYPE_ not defined."
#endif

typedef vuint8 FBL_MEMID_TYPE;
/* polyspace:begin < MISRA-C3:2.3 : Not a defect : Justify with annotations > Should be kept for future usage */
typedef FBL_ADDR_TYPE       tFblAddress;
typedef FBL_MEMSIZE_TYPE    tFblLength;
typedef FBL_ADDR_TYPE       tMtabAddress;
typedef FBL_MEMSIZE_TYPE    tMtabLength;
typedef FBL_MEMID_TYPE      tMtabMemId;

typedef vuint16 tChecksum;
/* polyspace:end < MISRA-C3:2.3 : Not a defect : Justify with annotations > Should be kept for future usage */
/***********************************************************************************************************************
 *  TYPEDEFS (function pointers)
 **********************************************************************************************************************/

/* Function pointer for FBL-exported functions */
#if defined( FBL_ENABLE_BANKING )
typedef FBL_CALL_TYPE void (*FBL_CALL_TYPE tExportFct)(void); /* PRQA S 0313 */ /* MD_FblDef_Export */
#else
/* polyspace < MISRA-C3:2.3 : Not a defect : Justify with annotations > tExportFct Should be kept for future usage */
typedef MEMORY_FAR void (*tExportFct)(void); /* PRQA S 0313 */ /* MD_FblDef_Export */
#endif /* FBL_ENABLE_BANKING */
/* polyspace < MISRA-C3:2.3 : Not a defect : Justify with annotations > Should be kept for future usage */
typedef FBL_CALL_TYPE vuint8 (* tFblRealtimeFct)(void);

/** Function pointer to read memory */
/* polyspace < MISRA-C3:2.3 : Not a defect : Justify with annotations > tReadMemoryFct Should be kept for future usage */
typedef FBL_CALL_TYPE tFblLength (* tReadMemoryFct)(tFblAddress address, V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * buffer, tFblLength length);

/***********************************************************************************************************************
 *  TYPEDEFS (other)
 **********************************************************************************************************************/

#if defined( FBL_ENABLE_DATA_PROCESSING )
/* polyspace:begin < MISRA-C3:2.3,2.4 : Not a defect : Justify with annotations > struct should be kept for future usage */
typedef struct tagProcParam
{
   V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * dataBuffer;
   vuint16        dataLength;
   V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * dataOutBuffer;
   vuint16        dataOutLength;
   vuint16        dataOutMaxLength;
   vuint8         (* wdTriggerFct)(void);
   vuint8         mode;
} tProcParam;
/* polyspace:end < MISRA-C3:2.3 : Not a defect : Justify with annotations > Should be kept for future usage */
#endif

/** Structure for address and length information of segments */
/* polyspace < MISRA-C3:2.4 : Not a defect : Justify with annotations > Tag declaration should be kept for future usage */
typedef struct tagSegmentInfo
{
   tFblAddress targetAddress;
   tFblLength  length;
} tSegmentInfo;

/** Segment data structure */
/* polyspace:begin < MISRA-C3:2.3,2.4 : Not a defect : Justify with annotations > struct should be kept for future usage */
typedef struct tagSegmentList
{
   vuint8         nrOfSegments;
   tSegmentInfo   segmentInfo[SWM_DATA_MAX_NOAR];
} tSegmentList;
/* polyspace:end < MISRA-C3:2.3 : Not a defect : Justify with annotations > Should be kept for future usage */
#endif /* FBL_DEF_H */

/* Module specific MISRA deviations:

   MD_FblDef_Export:
     Reason: Verify interface functions are stored as void pointers as actual type is not known at configuration time.
             The software that uses these functions has to take care that a cast to the correct function type is being done before usage
     Risk: The software that uses this elements does not correctly cast before usage.
     Prevention: Review of implementations and testing of the functionality.

   MD_FblDef_Invert:
     Reason: Usage of FblInvert.. macros implies usage of ~ operator and appropriate casts. This includes a cast from
             negative integer to unsigned value. The integer is only an intermediate type that occurs because of
             integer promotion while using ~ operator, though only a bit mask is operated on.
     Risk: No risk.
     Prevention: No prevention defined.

*/

/***********************************************************************************************************************
 *  END OF FILE: FBL_DEF.H
 **********************************************************************************************************************/

