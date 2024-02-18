/**
*   @file    Fls_PBcfg.c
*   @implements Fls_PBcfg.c_Artifact
*   @version 1.0.1
*
*   @brief   AUTOSAR Fls - AUTOSAR Module Flash Driver.
*   @details Definitions of all post-build configuration structures.
*
*   @addtogroup FLS
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.3 MCAL
*   Platform             : ARM
*   Peripheral           : IPV_FTFE
*   Dependencies         : 
*
*   Autosar Version      : 4.3.1
*   Autosar Revision     : ASR_REL_4_3_REV_0001
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : S32K14x_MCAL_1_0_1_RTM_ASR_REL_4_3_REV_0001_20190621
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2019 NXP
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section fls_pbcfg_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before 
* '#include'
* Because of Autosar requirement MEMMAP003 of memory mapping.
* 
* @section fls_pbcfg_c_REF_2
* Violates MISRA 2004 Required Rule 11.1, Conversions involing function pointers must be to/from integral types.
* This violation is due to FLS213.
* 
* @section fls_pbcfg_c_REF_3
* Violates MISRA 2004 Advisory Rule 11.4, A cast should not be performed between a pointer to object type
* and a different pointer to object type.
* This violation is due to FLS213.
* 
* @section fls_pbcfg_c_REF_4
* Violates MISRA 2004 Required Rule 8.8, Object/function previously declared.
* The rule 8.8 requires that 'An external object or function shall be declared in one and only one file'.
* This requirement is fulfilled since the function is declared as external in and only in one configuration 
* C file (Fls_Cfg.c or Fls_PBcfg.c). There is no need to put the declaration into Fls_Cfg.h and made it 
* accessible for all modules which includes Fls.h/Fls_Cfg.h.
* 
* @section fls_pbcfg_c_REF_5
* Violates MISRA 2004 Required Rule 8.10, Could be made static.  
* Making FlsConfigSet_0 static would make it unaccessible to the application.
*
* @section fls_pbcfg_c_REF_6
* Violates MISRA 2004 Required Rule 20.2, Re-use of C90 identifier pattern.
* This is just a matter of a symbol specified in the configuration.
* 
* @section fls_pbcfg_c_REF_7
* Violates MISRA 2004 Required Rule 8.8,
* An external object or function shall be declared in one and only one file.
* Possible MISRA error if the same callback function or variable name is used in multiple configuration variants. 
* Callback function/variable name is set by the driver user so this cannot be fixed by updating the driver code.
*
* @section fls_pbcfg_c_REF_8
* Violates MISRA 2004 Advisory Rule 11.3, A cast should not be performed between a pointer type and
* an integral type.
* This violation is due to FLS213.
* 
* @section [global]
* Violates MISRA 2004 Required Rule 5.1,
* Identifiers (internal and external) shall not rely on the significance of more than 31 characters. 
* The used compilers use more than 31 chars for identifiers.
*
* @section [global]
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure that
* 31 character significance and case sensitivity are supported for external identifiers
* This violation is due to the requirement that requests to have a file version check.
*
* @section [global]
* Violates MISRA 2004 Required Rule 19.15, Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
*  
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Fls.h"
#include "Reg_eSys_QSPI.h"
#include "Reg_eSys_FLASHC.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLS_VENDOR_ID_CFG_C                      43
#define FLS_AR_RELEASE_MAJOR_VERSION_CFG_C       4
#define FLS_AR_RELEASE_MINOR_VERSION_CFG_C       3
#define FLS_AR_RELEASE_REVISION_VERSION_CFG_C    1
#define FLS_SW_MAJOR_VERSION_CFG_C               1
#define FLS_SW_MINOR_VERSION_CFG_C               0
#define FLS_SW_PATCH_VERSION_CFG_C               1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Fls header file are of the same vendor */
#if (FLS_VENDOR_ID_CFG_C != FLS_VENDOR_ID)
    #error "Fls_PBcfg.c and Fls.h have different vendor ids"
#endif
/* Check if current file and Fls header file are of the same Autosar version */
#if ((FLS_AR_RELEASE_MAJOR_VERSION_CFG_C    != FLS_AR_RELEASE_MAJOR_VERSION) || \
     (FLS_AR_RELEASE_MINOR_VERSION_CFG_C    != FLS_AR_RELEASE_MINOR_VERSION) || \
     (FLS_AR_RELEASE_REVISION_VERSION_CFG_C != FLS_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Fls_PBcfg.c and Fls.h are different"
#endif
/* Check if current file and Fls header file are of the same Software version */
#if ((FLS_SW_MAJOR_VERSION_CFG_C != FLS_SW_MAJOR_VERSION) || \
     (FLS_SW_MINOR_VERSION_CFG_C != FLS_SW_MINOR_VERSION) || \
     (FLS_SW_PATCH_VERSION_CFG_C != FLS_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Fls_PBcfg.c and Fls.h are different"
#endif

/* Check if current file and Reg_eSys_QSPI header file are of the same vendor */
#if (FLS_VENDOR_ID_CFG_C != ESYS_QSPI_VENDOR_ID)
    #error "Fls_PBcfg.c and Reg_eSys_QSPI.h have different vendor ids"
#endif
/* Check if current file and Reg_eSys_QSPI header file are of the same Autosar version */
#if ((FLS_AR_RELEASE_MAJOR_VERSION_CFG_C    != ESYS_QSPI_AR_RELEASE_MAJOR_VERSION) || \
     (FLS_AR_RELEASE_MINOR_VERSION_CFG_C    != ESYS_QSPI_AR_RELEASE_MINOR_VERSION) || \
     (FLS_AR_RELEASE_REVISION_VERSION_CFG_C != ESYS_QSPI_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Fls_PBcfg.c and Reg_eSys_QSPI.h are different"
#endif
/* Check if current file and Reg_eSys_QSPI header file are of the same Software version */
#if ((FLS_SW_MAJOR_VERSION_CFG_C != ESYS_QSPI_SW_MAJOR_VERSION) || \
     (FLS_SW_MINOR_VERSION_CFG_C != ESYS_QSPI_SW_MINOR_VERSION) || \
     (FLS_SW_PATCH_VERSION_CFG_C != ESYS_QSPI_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Fls_PBcfg.c and Reg_eSys_QSPI.h are different"
#endif

/* Check if current file and Reg_eSys_FLASHC header file are of the same vendor */
#if (FLS_VENDOR_ID_CFG_C != ESYS_FLASHC_VENDOR_ID)
    #error "Fls_PBcfg.c and Reg_eSys_FLASHC.h have different vendor ids"
#endif
/* Check if current file and Reg_eSys_FLASHC header file are of the same Autosar version */
#if ((FLS_AR_RELEASE_MAJOR_VERSION_CFG_C    != ESYS_FLASHC_AR_RELEASE_MAJOR_VERSION) || \
     (FLS_AR_RELEASE_MINOR_VERSION_CFG_C    != ESYS_FLASHC_AR_RELEASE_MINOR_VERSION) || \
     (FLS_AR_RELEASE_REVISION_VERSION_CFG_C != ESYS_FLASHC_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Fls_PBcfg.c and Reg_eSys_FLASHC.h are different"
#endif
/* Check if current file and Reg_eSys_FLASHC header file are of the same Software version */
#if ((FLS_SW_MAJOR_VERSION_CFG_C != ESYS_FLASHC_SW_MAJOR_VERSION) || \
     (FLS_SW_MINOR_VERSION_CFG_C != ESYS_FLASHC_SW_MINOR_VERSION) || \
     (FLS_SW_PATCH_VERSION_CFG_C != ESYS_FLASHC_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Fls_PBcfg.c and Reg_eSys_FLASHC.h are different"
#endif


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define FLS_START_SEC_CODE
/* 
* @violates @ref fls_pbcfg_c_REF_1 Only preprocessor statements
* and comments before '#include'
*/
#include "Fls_MemMap.h"        
/* Declaration of Fls notification function (Fee_JobEndNotification())*/
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern FUNC( void, FLS_CODE ) Fee_JobEndNotification( void );
/* Declaration of Fls notification function (Fee_JobErrorNotification())*/
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern FUNC( void, FLS_CODE ) Fee_JobErrorNotification( void );
/* Declaration of Fls notification function (FlsQspiInitCallout())*/
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern FUNC( void, FLS_CODE ) FlsQspiInitCallout( void );
/* Declaration of Fls notification function (FlsQspiResetCallout())*/
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern FUNC( void, FLS_CODE ) FlsQspiResetCallout( void );
/* Declaration of Fls notification function (Fls_AC_Callback_Test())*/
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern FUNC( void, FLS_CODE ) Fls_AC_Callback_Test( void );
/* Declaration of Fls notification function (Fls_FinishedFlashAccessNotif())*/
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern FUNC( void, FLS_CODE ) Fls_FinishedFlashAccessNotif( void );
/* Declaration of Fls notification function (Fls_StartFlashAccessNotif())*/
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern FUNC( void, FLS_CODE ) Fls_StartFlashAccessNotif( void );
/* Declaration of Fls notification function (MODULE-CONFIGURATION())*/
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern FUNC(Std_ReturnType, FLS_CODE ) FlsQspiErrorCheckCallout
(
VAR(Fls_QspiSectorChType, AUTOMATIC) eQspiSectorChannel
/* @violates @ref fls_pbcfg_c_REF_7 External object should be declared in a single file */     
);
/* Declaration of Fls notification function (MODULE-CONFIGURATION())*/
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern FUNC(Std_ReturnType, FLS_CODE ) FlsQspiEccCheckCallout
(
VAR(Fls_QspiSectorChType, AUTOMATIC) eQspiSectorChannel,
VAR(Fls_AddressType, AUTOMATIC) u32StartAddr,
VAR(Fls_LengthType, AUTOMATIC)  u32DataLength
/* @violates @ref fls_pbcfg_c_REF_7 External object should be declared in a single file */
);
#define FLS_STOP_SEC_CODE
/* 
* @violates @ref fls_pbcfg_c_REF_1 Only preprocessor statements
* and comments before '#include'
*/
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE_AC
/* 
* @violates @ref fls_pbcfg_c_REF_1 Only preprocessor statements
* and comments before '#include'
*/
#include "Fls_MemMap.h"

#ifdef _LINARO_C_S32K14x_ 
#if (FLS_HW_OPERATION_ABORT_SUPPORTED == STD_ON)
#if (FLS_TIMEOUT_HANDLING == STD_ON)
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern void Fls_Flash_AccessCode( CONST(uint32, AUTOMATIC) u32RegBaseAddr, P2FUNC(void, FLS_CODE, CallBack)( void ), P2VAR(uint32, AUTOMATIC, FLS_CODE) pTimerCounterAC, P2VAR(uint32, AUTOMATIC, FLS_CODE) pTimerCounterAbort ) __attribute__ ((section (".acfls_code_rom")));
#else
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern void Fls_Flash_AccessCode( CONST(uint32, AUTOMATIC) u32RegBaseAddr, P2FUNC(void, FLS_CODE, CallBack)( void ) ) __attribute__ ((section (".acfls_code_rom")));
#endif /* FLS_TIMEOUT_HANDLING == STD_ON */
#else   /* FLS_HW_OPERATION_ABORT_SUPPORTED == STD_OFF */
#if (FLS_TIMEOUT_HANDLING == STD_ON)
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern void Fls_Flash_AccessCode( CONST(uint32, AUTOMATIC) u32RegBaseAddr, P2FUNC(void, FLS_CODE, CallBack)( void ), P2VAR(uint32, AUTOMATIC, FLS_CODE) pTimerCounterAC ) __attribute__ ((section (".acfls_code_rom")));
#else
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern void Fls_Flash_AccessCode( CONST(uint32, AUTOMATIC) u32RegBaseAddr, P2FUNC(void, FLS_CODE, CallBack)( void ) ) __attribute__ ((section (".acfls_code_rom")));
#endif /* FLS_TIMEOUT_HANDLING == STD_ON */
#endif  /* FLS_HW_OPERATION_ABORT_SUPPORTED == STD_ON */
#else
#if (FLS_HW_OPERATION_ABORT_SUPPORTED == STD_ON)
#if (FLS_TIMEOUT_HANDLING == STD_ON)
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern void Fls_Flash_AccessCode(CONST(uint32, AUTOMATIC) u32RegBaseAddr, P2FUNC(void, FLS_CODE, CallBack)( void ), P2VAR(uint32, AUTOMATIC, FLS_CODE) pTimerCounterAC, P2VAR(uint32, AUTOMATIC, FLS_CODE) pTimerCounterAbort );
#else
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern void Fls_Flash_AccessCode( CONST(uint32, AUTOMATIC) u32RegBaseAddr, P2FUNC(void, FLS_CODE, CallBack)( void ) );
#endif /* FLS_TIMEOUT_HANDLING == STD_ON */
#else   /* FLS_HW_OPERATION_ABORT_SUPPORTED == STD_OFF */
#if (FLS_TIMEOUT_HANDLING == STD_ON)
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern void Fls_Flash_AccessCode(CONST(uint32, AUTOMATIC) u32RegBaseAddr, P2FUNC(void, FLS_CODE, CallBack)( void ), P2VAR(uint32, AUTOMATIC, FLS_CODE) pTimerCounterAC );
#else
/* @violates @ref fls_pbcfg_c_REF_4 Object/function previously declared */
extern void Fls_Flash_AccessCode( CONST(uint32, AUTOMATIC) u32RegBaseAddr, P2FUNC(void, FLS_CODE, CallBack)( void ) );
#endif /* FLS_TIMEOUT_HANDLING == STD_ON */
#endif  /* FLS_HW_OPERATION_ABORT_SUPPORTED == STD_ON */
#endif /* #ifdef _LINARO_C_S32K14x_ */

#define FLS_STOP_SEC_CODE_AC
/* 
* @violates @ref fls_pbcfg_c_REF_1 Only preprocessor statements
* and comments before '#include'
*/
#include "Fls_MemMap.h"

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


                                                                                                                                                                                
            
                



#define FLS_START_SEC_CONFIG_DATA_8
/* 
* @violates @ref fls_pbcfg_c_REF_1 Only preprocessor statements
* and comments before '#include'
*/
#include "Fls_MemMap.h"
/* aFlsSectorFlags[] (FlsConfigSet) */
static CONST(uint8, FLS_CONST) FlsConfigSet_aFlsSectorFlags[16] =
{
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector) */
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector_001) */
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector_002) */
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector_003) */
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector_004) */
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector_005) */
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector_006) */
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector_007) */
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector_008) */
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector_009) */
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector_010) */
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector_011) */
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector_012) */
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector_013) */
    FLS_SECTOR_ERASE_ASYNCH, /* (FlsSector_014) */
    FLS_SECTOR_ERASE_ASYNCH /* (FlsSector_015) */
};
/* aFlsSectorUnlock[] (FlsConfigSet) */
static CONST(uint8, FLS_CONST) FlsConfigSet_aFlsSectorUnlock[16] =
{
    1U, /* (FlsSector) */
    1U, /* (FlsSector_001) */
    1U, /* (FlsSector_002) */
    1U, /* (FlsSector_003) */
    1U, /* (FlsSector_004) */
    1U, /* (FlsSector_005) */
    1U, /* (FlsSector_006) */
    1U, /* (FlsSector_007) */
    1U, /* (FlsSector_008) */
    1U, /* (FlsSector_009) */
    1U, /* (FlsSector_010) */
    1U, /* (FlsSector_011) */
    1U, /* (FlsSector_012) */
    1U, /* (FlsSector_013) */
    1U, /* (FlsSector_014) */
    1U /* (FlsSector_015) */
};
#define FLS_STOP_SEC_CONFIG_DATA_8
/* 
* @violates @ref fls_pbcfg_c_REF_1 Only preprocessor statements
* and comments before '#include'
*/
#include "Fls_MemMap.h"

#define FLS_START_SEC_CONFIG_DATA_UNSPECIFIED
/* 
* @violates @ref fls_pbcfg_c_REF_1 Only preprocessor statements
* and comments before '#include'
*/
#include "Fls_MemMap.h"
/* aFlsSectorEndAddr[] (FlsConfigSet) */
static CONST(Fls_AddressType, FLS_CONST) FlsConfigSet_aFlsSectorEndAddr[16] =
{
    (Fls_AddressType)2047U, /* FlsSectorEndAddr (FlsSector)*/
    (Fls_AddressType)4095U, /* FlsSectorEndAddr (FlsSector_001)*/
    (Fls_AddressType)6143U, /* FlsSectorEndAddr (FlsSector_002)*/
    (Fls_AddressType)8191U, /* FlsSectorEndAddr (FlsSector_003)*/
    (Fls_AddressType)10239U, /* FlsSectorEndAddr (FlsSector_004)*/
    (Fls_AddressType)12287U, /* FlsSectorEndAddr (FlsSector_005)*/
    (Fls_AddressType)14335U, /* FlsSectorEndAddr (FlsSector_006)*/
    (Fls_AddressType)16383U, /* FlsSectorEndAddr (FlsSector_007)*/
    (Fls_AddressType)18431U, /* FlsSectorEndAddr (FlsSector_008)*/
    (Fls_AddressType)20479U, /* FlsSectorEndAddr (FlsSector_009)*/
    (Fls_AddressType)22527U, /* FlsSectorEndAddr (FlsSector_010)*/
    (Fls_AddressType)24575U, /* FlsSectorEndAddr (FlsSector_011)*/
    (Fls_AddressType)26623U, /* FlsSectorEndAddr (FlsSector_012)*/
    (Fls_AddressType)28671U, /* FlsSectorEndAddr (FlsSector_013)*/
    (Fls_AddressType)30719U, /* FlsSectorEndAddr (FlsSector_014)*/
    (Fls_AddressType)32767U /* FlsSectorEndAddr (FlsSector_015)*/
};

/* paSectorProgSize[] (FlsConfigSet) */
static CONST(Fls_LengthType, FLS_CONST) FlsConfigSet_aFlsProgSize[16] =
{
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD, /* FlsProgrammingSize (FlsSector) */
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD, /* FlsProgrammingSize (FlsSector_001) */
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD, /* FlsProgrammingSize (FlsSector_002) */
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD, /* FlsProgrammingSize (FlsSector_003) */
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD, /* FlsProgrammingSize (FlsSector_004) */
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD, /* FlsProgrammingSize (FlsSector_005) */
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD, /* FlsProgrammingSize (FlsSector_006) */
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD, /* FlsProgrammingSize (FlsSector_007) */
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD, /* FlsProgrammingSize (FlsSector_008) */
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD, /* FlsProgrammingSize (FlsSector_009) */
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD, /* FlsProgrammingSize (FlsSector_010) */
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD, /* FlsProgrammingSize (FlsSector_011) */
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD, /* FlsProgrammingSize (FlsSector_012) */
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD, /* FlsProgrammingSize (FlsSector_013) */
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD, /* FlsProgrammingSize (FlsSector_014) */
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD /* FlsProgrammingSize (FlsSector_015) */
};


/* paSectorPageSize[] (FlsConfigSet) */
static CONST(Fls_LengthType, FLS_CONST) FlsConfigSet_aFlsSectorPageSize[16] =
{
    (Fls_LengthType)8U, /* FlsPageSize (FlsSector) */
    (Fls_LengthType)8U, /* FlsPageSize (FlsSector_001) */
    (Fls_LengthType)8U, /* FlsPageSize (FlsSector_002) */
    (Fls_LengthType)8U, /* FlsPageSize (FlsSector_003) */
    (Fls_LengthType)8U, /* FlsPageSize (FlsSector_004) */
    (Fls_LengthType)8U, /* FlsPageSize (FlsSector_005) */
    (Fls_LengthType)8U, /* FlsPageSize (FlsSector_006) */
    (Fls_LengthType)8U, /* FlsPageSize (FlsSector_007) */
    (Fls_LengthType)8U, /* FlsPageSize (FlsSector_008) */
    (Fls_LengthType)8U, /* FlsPageSize (FlsSector_009) */
    (Fls_LengthType)8U, /* FlsPageSize (FlsSector_010) */
    (Fls_LengthType)8U, /* FlsPageSize (FlsSector_011) */
    (Fls_LengthType)8U, /* FlsPageSize (FlsSector_012) */
    (Fls_LengthType)8U, /* FlsPageSize (FlsSector_013) */
    (Fls_LengthType)8U, /* FlsPageSize (FlsSector_014) */
    (Fls_LengthType)8U /* FlsPageSize (FlsSector_015) */
};



static CONST(Fls_Flash_InternalSectorInfoType, FLS_CONST) FlsSector_FlsConfigSet_sInternalSectorInfo =
{
    /* 
    * @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types 
    * @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.
    */
    (volatile uint32*)(D_FLASH_BASE_ADDR + 0x000000UL),    /* sectorStartAddressPtr */
    0U  /* Sector location to calculate cfgCRC */              
};
static CONST(Fls_Flash_InternalSectorInfoType, FLS_CONST) FlsSector_001_FlsConfigSet_sInternalSectorInfo =
{
    /* 
    * @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types 
    * @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.
    */
    (volatile uint32*)(D_FLASH_BASE_ADDR + 0x000800UL),    /* sectorStartAddressPtr */
    1U  /* Sector location to calculate cfgCRC */              
};
static CONST(Fls_Flash_InternalSectorInfoType, FLS_CONST) FlsSector_002_FlsConfigSet_sInternalSectorInfo =
{
    /* 
    * @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types 
    * @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.
    */
    (volatile uint32*)(D_FLASH_BASE_ADDR + 0x001000UL),    /* sectorStartAddressPtr */
    2U  /* Sector location to calculate cfgCRC */              
};
static CONST(Fls_Flash_InternalSectorInfoType, FLS_CONST) FlsSector_003_FlsConfigSet_sInternalSectorInfo =
{
    /* 
    * @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types 
    * @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.
    */
    (volatile uint32*)(D_FLASH_BASE_ADDR + 0x001800UL),    /* sectorStartAddressPtr */
    3U  /* Sector location to calculate cfgCRC */              
};
static CONST(Fls_Flash_InternalSectorInfoType, FLS_CONST) FlsSector_004_FlsConfigSet_sInternalSectorInfo =
{
    /* 
    * @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types 
    * @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.
    */
    (volatile uint32*)(D_FLASH_BASE_ADDR + 0x002000UL),    /* sectorStartAddressPtr */
    4U  /* Sector location to calculate cfgCRC */              
};
static CONST(Fls_Flash_InternalSectorInfoType, FLS_CONST) FlsSector_005_FlsConfigSet_sInternalSectorInfo =
{
    /* 
    * @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types 
    * @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.
    */
    (volatile uint32*)(D_FLASH_BASE_ADDR + 0x002800UL),    /* sectorStartAddressPtr */
    5U  /* Sector location to calculate cfgCRC */              
};
static CONST(Fls_Flash_InternalSectorInfoType, FLS_CONST) FlsSector_006_FlsConfigSet_sInternalSectorInfo =
{
    /* 
    * @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types 
    * @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.
    */
    (volatile uint32*)(D_FLASH_BASE_ADDR + 0x003000UL),    /* sectorStartAddressPtr */
    6U  /* Sector location to calculate cfgCRC */              
};
static CONST(Fls_Flash_InternalSectorInfoType, FLS_CONST) FlsSector_007_FlsConfigSet_sInternalSectorInfo =
{
    /* 
    * @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types 
    * @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.
    */
    (volatile uint32*)(D_FLASH_BASE_ADDR + 0x003800UL),    /* sectorStartAddressPtr */
    7U  /* Sector location to calculate cfgCRC */              
};
static CONST(Fls_Flash_InternalSectorInfoType, FLS_CONST) FlsSector_008_FlsConfigSet_sInternalSectorInfo =
{
    /* 
    * @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types 
    * @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.
    */
    (volatile uint32*)(D_FLASH_BASE_ADDR + 0x004000UL),    /* sectorStartAddressPtr */
    8U  /* Sector location to calculate cfgCRC */              
};
static CONST(Fls_Flash_InternalSectorInfoType, FLS_CONST) FlsSector_009_FlsConfigSet_sInternalSectorInfo =
{
    /* 
    * @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types 
    * @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.
    */
    (volatile uint32*)(D_FLASH_BASE_ADDR + 0x004800UL),    /* sectorStartAddressPtr */
    9U  /* Sector location to calculate cfgCRC */              
};
static CONST(Fls_Flash_InternalSectorInfoType, FLS_CONST) FlsSector_010_FlsConfigSet_sInternalSectorInfo =
{
    /* 
    * @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types 
    * @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.
    */
    (volatile uint32*)(D_FLASH_BASE_ADDR + 0x005000UL),    /* sectorStartAddressPtr */
    10U  /* Sector location to calculate cfgCRC */              
};
static CONST(Fls_Flash_InternalSectorInfoType, FLS_CONST) FlsSector_011_FlsConfigSet_sInternalSectorInfo =
{
    /* 
    * @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types 
    * @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.
    */
    (volatile uint32*)(D_FLASH_BASE_ADDR + 0x005800UL),    /* sectorStartAddressPtr */
    11U  /* Sector location to calculate cfgCRC */              
};
static CONST(Fls_Flash_InternalSectorInfoType, FLS_CONST) FlsSector_012_FlsConfigSet_sInternalSectorInfo =
{
    /* 
    * @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types 
    * @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.
    */
    (volatile uint32*)(D_FLASH_BASE_ADDR + 0x006000UL),    /* sectorStartAddressPtr */
    12U  /* Sector location to calculate cfgCRC */              
};
static CONST(Fls_Flash_InternalSectorInfoType, FLS_CONST) FlsSector_013_FlsConfigSet_sInternalSectorInfo =
{
    /* 
    * @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types 
    * @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.
    */
    (volatile uint32*)(D_FLASH_BASE_ADDR + 0x006800UL),    /* sectorStartAddressPtr */
    13U  /* Sector location to calculate cfgCRC */              
};
static CONST(Fls_Flash_InternalSectorInfoType, FLS_CONST) FlsSector_014_FlsConfigSet_sInternalSectorInfo =
{
    /* 
    * @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types 
    * @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.
    */
    (volatile uint32*)(D_FLASH_BASE_ADDR + 0x007000UL),    /* sectorStartAddressPtr */
    14U  /* Sector location to calculate cfgCRC */              
};
static CONST(Fls_Flash_InternalSectorInfoType, FLS_CONST) FlsSector_015_FlsConfigSet_sInternalSectorInfo =
{
    /* 
    * @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types 
    * @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.
    */
    (volatile uint32*)(D_FLASH_BASE_ADDR + 0x007800UL),    /* sectorStartAddressPtr */
    15U  /* Sector location to calculate cfgCRC */              
};

/*  FLASH physical sectorization description */
static CONSTP2CONST(Fls_Flash_InternalSectorInfoType, FLS_VAR, FLS_APPL_CONST) FlsConfigSet_aSectorList[16] =
{
    /* FLS_DATA_ARRAY_0_BLOCK_1_S000 */
    &FlsSector_FlsConfigSet_sInternalSectorInfo
    ,    /* FLS_DATA_ARRAY_0_BLOCK_1_S001 */
    &FlsSector_001_FlsConfigSet_sInternalSectorInfo
    ,    /* FLS_DATA_ARRAY_0_BLOCK_1_S002 */
    &FlsSector_002_FlsConfigSet_sInternalSectorInfo
    ,    /* FLS_DATA_ARRAY_0_BLOCK_1_S003 */
    &FlsSector_003_FlsConfigSet_sInternalSectorInfo
    ,    /* FLS_DATA_ARRAY_0_BLOCK_1_S004 */
    &FlsSector_004_FlsConfigSet_sInternalSectorInfo
    ,    /* FLS_DATA_ARRAY_0_BLOCK_1_S005 */
    &FlsSector_005_FlsConfigSet_sInternalSectorInfo
    ,    /* FLS_DATA_ARRAY_0_BLOCK_1_S006 */
    &FlsSector_006_FlsConfigSet_sInternalSectorInfo
    ,    /* FLS_DATA_ARRAY_0_BLOCK_1_S007 */
    &FlsSector_007_FlsConfigSet_sInternalSectorInfo
    ,    /* FLS_DATA_ARRAY_0_BLOCK_1_S008 */
    &FlsSector_008_FlsConfigSet_sInternalSectorInfo
    ,    /* FLS_DATA_ARRAY_0_BLOCK_1_S009 */
    &FlsSector_009_FlsConfigSet_sInternalSectorInfo
    ,    /* FLS_DATA_ARRAY_0_BLOCK_1_S010 */
    &FlsSector_010_FlsConfigSet_sInternalSectorInfo
    ,    /* FLS_DATA_ARRAY_0_BLOCK_1_S011 */
    &FlsSector_011_FlsConfigSet_sInternalSectorInfo
    ,    /* FLS_DATA_ARRAY_0_BLOCK_1_S012 */
    &FlsSector_012_FlsConfigSet_sInternalSectorInfo
    ,    /* FLS_DATA_ARRAY_0_BLOCK_1_S013 */
    &FlsSector_013_FlsConfigSet_sInternalSectorInfo
    ,    /* FLS_DATA_ARRAY_0_BLOCK_1_S014 */
    &FlsSector_014_FlsConfigSet_sInternalSectorInfo
    ,    /* FLS_DATA_ARRAY_0_BLOCK_1_S015 */
    &FlsSector_015_FlsConfigSet_sInternalSectorInfo
};


/* External QSPI flash parameters. */

/* paHwCh[] (FlsConfigSet) */
static CONST(Fls_HwChType, FLS_CONST) FlsConfigSet_paHwCh[16] =
{
    FLS_CH_INTERN, /* (FlsSector) */
    FLS_CH_INTERN, /* (FlsSector_001) */
    FLS_CH_INTERN, /* (FlsSector_002) */
    FLS_CH_INTERN, /* (FlsSector_003) */
    FLS_CH_INTERN, /* (FlsSector_004) */
    FLS_CH_INTERN, /* (FlsSector_005) */
    FLS_CH_INTERN, /* (FlsSector_006) */
    FLS_CH_INTERN, /* (FlsSector_007) */
    FLS_CH_INTERN, /* (FlsSector_008) */
    FLS_CH_INTERN, /* (FlsSector_009) */
    FLS_CH_INTERN, /* (FlsSector_010) */
    FLS_CH_INTERN, /* (FlsSector_011) */
    FLS_CH_INTERN, /* (FlsSector_012) */
    FLS_CH_INTERN, /* (FlsSector_013) */
    FLS_CH_INTERN, /* (FlsSector_014) */
    FLS_CH_INTERN /* (FlsSector_015) */
};

/* paSectorHwAddress[] (FlsConfigSet) */
static CONST(Fls_AddressType, FLS_CONST) FlsConfigSet_paSectorHwAddress[16] =
{
    (Fls_AddressType)0U, /* (FlsSector) */
    (Fls_AddressType)0U, /* (FlsSector_001) */
    (Fls_AddressType)0U, /* (FlsSector_002) */
    (Fls_AddressType)0U, /* (FlsSector_003) */
    (Fls_AddressType)0U, /* (FlsSector_004) */
    (Fls_AddressType)0U, /* (FlsSector_005) */
    (Fls_AddressType)0U, /* (FlsSector_006) */
    (Fls_AddressType)0U, /* (FlsSector_007) */
    (Fls_AddressType)0U, /* (FlsSector_008) */
    (Fls_AddressType)0U, /* (FlsSector_009) */
    (Fls_AddressType)0U, /* (FlsSector_010) */
    (Fls_AddressType)0U, /* (FlsSector_011) */
    (Fls_AddressType)0U, /* (FlsSector_012) */
    (Fls_AddressType)0U, /* (FlsSector_013) */
    (Fls_AddressType)0U, /* (FlsSector_014) */
    (Fls_AddressType)0U /* (FlsSector_015) */
};




/**
* @brief        Structure used to set function pointers notification, working mode
*/
/* Fls module initialization data (FlsConfigSet)*/
/* @violates @ref fls_pbcfg_c_REF_5 Could be made static */

CONST(Fls_ConfigType, FLS_CONST) FlsConfigSet=
{
    /* @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types */
    /* @violates @ref fls_pbcfg_c_REF_3 Cast from pointer to pointer */
    /* @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.*/
    (Fls_AcErasePtrType)&Fls_Flash_AccessCode, /* FlsAcErase */
    /* @violates @ref fls_pbcfg_c_REF_2 Conversions involing function pointers must be to/from integral types */
    /* @violates @ref fls_pbcfg_c_REF_3 Cast from pointer to pointer */
    /* @violates @ref fls_pbcfg_c_REF_8 A cast should not be performed between a pointer type and an integral type.*/
    (Fls_AcWritePtrType)&Fls_Flash_AccessCode, /* FlsAcWrite */
    &Fls_AC_Callback_Test, /* FlsACCallback */  
    &Fee_JobEndNotification, /* FlsJobEndNotification */
    &Fee_JobErrorNotification, /* FlsJobErrorNotification */  
    &Fls_StartFlashAccessNotif, /* FlsStartFlashAccessNotif */
    &Fls_FinishedFlashAccessNotif, /* FlsFinishedFlashAccessNotif */
    MEMIF_MODE_SLOW, /* FlsDefaultMode */
    48U, /* FlsMaxReadFastMode */
    24U, /* FlsMaxReadNormalMode */
    256U, /* FlsMaxWriteFastMode */
    32U, /* FlsMaxWriteNormalMode */
    16U, /* FlsSectorCount */
    &FlsConfigSet_aFlsSectorEndAddr,                /* (*paSectorEndAddr)[]  */
    &FlsConfigSet_aSectorList,                      /* (*pSectorList)[] */
    &FlsConfigSet_aFlsSectorFlags,                  /* (*paSectorFlags)[] */
    &FlsConfigSet_aFlsProgSize,                     /* (*paSectorProgSize)[] */
    &FlsConfigSet_aFlsSectorPageSize,               /* (*paSectorPageSize)[] */    
    &FlsConfigSet_aFlsSectorUnlock,                 /* (*paSectorUnlock)[] */
    &FlsConfigSet_paHwCh,                           /* (*paHwCh)[] */
    &FlsConfigSet_paSectorHwAddress,                /* (*paSectorHwAddress)[] */
    NULL_PTR, /* pFlsQspiCfgConfig */
    14038U /* configCrc */
};
#define FLS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/* 
* @violates @ref fls_pbcfg_c_REF_1 Only preprocessor statements
* and comments before '#include'
*/
#include "Fls_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @}*/
