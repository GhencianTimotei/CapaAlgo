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
 *            Module: NvM
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: Huf H_lsbeck & F_rst GmbH & Co. KG
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: S32K144
 *    License Scope : The usage is restricted to CBD2100188_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: NvM_Cfg.h
 *   Generation Time: 2024-01-27 22:50:07
 *           Project: DaVinciConfigurationS32K144 - Version 1.0
 *          Delivery: CBD2100188_D01
 *      Tool Version: DaVinci Configurator  5.23.45 SP4
 *
 *
 *********************************************************************************************************************/

	
/* PRQA S 5087 MemMap */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * PROTECTION AGAINST MULTIPLE INCLUSION
 *********************************************************************************************************************/
/* public section - to be used by NvM itself and its users */
#if (!defined NVM_CFG_H_PUBLIC)
#define NVM_CFG_H_PUBLIC

/**********************************************************************************************************************
 * VERSION IDENTIFICATION
 *********************************************************************************************************************/
#define NVM_CFG_MAJOR_VERSION    (8u)
#define NVM_CFG_MINOR_VERSION    (0u)
#define NVM_CFG_PATCH_VERSION    (0u)

/**********************************************************************************************************************
 * NVM API TYPE INCLUDES
 *********************************************************************************************************************/
#include "NvM_Types.h"

/**********************************************************************************************************************
 * API CFG TYPE DEFINITIONS
 *********************************************************************************************************************/
/* Type for an the additional published parameter Compiled Configuration ID (see CompiledConfigurationId in NvM.h). */
/* Compiled Config Id Type */
typedef union
{ /* PRQA S 0750 */ /* MD_MSR_Union */
    uint16 Word_u16;
    uint8  Bytes_au8[2u];
} NvM_CompiledConfigIdType;

/**********************************************************************************************************************
 * CFG COMMON PARAMETER
 *********************************************************************************************************************/
/* --------------------  DEVELOPMENT / PRODUCTION MODE -------------------- */
/* switch between Debug- or Production-Mode */
#define NVM_DEV_ERROR_DETECT                  (STD_OFF)

/* Preprocessor switch that is used in NvM_ReadAll() */
#define NVM_DYNAMIC_CONFIGURATION             (STD_OFF)

#define NVM_API_CONFIG_CLASS_1                (1u)
#define NVM_API_CONFIG_CLASS_2                (3u)
#define NVM_API_CONFIG_CLASS_3                (7u)

#define NVM_API_CONFIG_CLASS                  (NVM_API_CONFIG_CLASS_3)

#define NVM_JOB_PRIORISATION                  STD_OFF

/* define compiled Block ID */
#define NVM_COMPILED_CONFIG_ID                (1u)

/* switch for enablinig fast mode during multi block requests */
#define NVM_DRV_MODE_SWITCH                   (STD_ON)

/* switch for enablinig polling mode and disabling notifications */
#define NVM_POLLING_MODE                      (STD_OFF)

/* switch for enabling the internal buffer for Crc handling */
#define NVM_CRC_INT_BUFFER                    (STD_ON)

/* number of defined NV blocks */
#define NVM_TOTAL_NUM_OF_NVRAM_BLOCKS         (48u)

/* internal buffer size */
#define NVM_INTERNAL_BUFFER_LENGTH            518uL

/* version info api switch */
#define NVM_VERSION_INFO_API                  (STD_ON)

/* switch to enable the ram block status api */
#define NVM_SET_RAM_BLOCK_STATUS_API          (STD_ON)

/* switch that gives the user (EcuM) the possibility to time-out WriteAll cancellation */
#define NVM_KILL_WRITEALL_API                 (STD_ON)

/* enabled or disable the whole repair redundant blocks feature */
#define NVM_REPAIR_REDUNDANT_BLOCKS_API       (STD_OFF)

/* NVM does not need this macro. It is intended for underlying modules,
 * relying on its existence
 */
#define NVM_DATASET_SELECTION_BITS            (6u)

/* block offset for DCM blocks */
#define NVM_DCM_BLOCK_OFFSET                  0x8000u

/* Enabled if at least one block used NvMCalcRamblockCrc and ExplicitSync mechanisms */
#define NVM_CRC_USE_INTERNAL_EXPLICIT_SYNC_BUFFER (STD_OFF)


/* returns corresponding DCM BlockId of an original NVRAM Block */
#define NvM_GetDcmBlockId(MyApplBlockId)      ((MyApplBlockId) | NVM_DCM_BLOCK_OFFSET) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* BlockId's:
 * Note: The numbers of the following list must meet the configured blocks in the NvM_BlockDescriptorTable_at
 *
 * Alignment of the handles of all blocks
 * Id 0 is reserved for multiblock calls
 * Id 1 is reserved for config ID
 */
#define NvMConf___MultiBlockRequest (0u) 
#define NvMConf_NvMBlockDescriptor_NvMConfigBlock (1u) 
#define NvMConf_NvMBlockDescriptor_NvM_LED_DUTY (2u) 
#define NvMConf_NvMBlockDescriptor_NvM_UNLOCK_SENSOR_BLOCK (3u) 
#define NvMConf_NvMBlockDescriptor_NvM_LOCK_SENSOR_BLOCK (4u) 
#define NvMConf_NvMBlockDescriptor_NvM_Other_HUF_BLOCK (5u) 
#define NvMConf_NvMBlockDescriptor_NvM_INDUCTIVE_SENSOR_BLOCK (6u) 
#define NvMConf_NvMBlockDescriptor_NvM_EMERGENCY_ACCESS_BLOCK (7u) 
#define NvMConf_NvMBlockDescriptor_NvM_FD02_SPARE_BLOCK (8u) 
#define NvMConf_NvMBlockDescriptor_NvM_AUDI_PARAMS_BLOCK (9u) 
#define NvMConf_NvMBlockDescriptor_NvM_BATTERY_SUPERVISOR_BLOCK (10u) 
#define NvMConf_NvMBlockDescriptor_DemAdminDataBlock (11u) 
#define NvMConf_NvMBlockDescriptor_DemPrimaryDataBlock0 (12u) 
#define NvMConf_NvMBlockDescriptor_DemPrimaryDataBlock6 (13u) 
#define NvMConf_NvMBlockDescriptor_DemPrimaryDataBlock2 (14u) 
#define NvMConf_NvMBlockDescriptor_DemPrimaryDataBlock3 (15u) 
#define NvMConf_NvMBlockDescriptor_DemPrimaryDataBlock4 (16u) 
#define NvMConf_NvMBlockDescriptor_DemPrimaryDataBlock5 (17u) 
#define NvMConf_NvMBlockDescriptor_DemPrimaryDataBlock7 (18u) 
#define NvMConf_NvMBlockDescriptor_DemStatusDataBlock (19u) 
#define NvMConf_NvMBlockDescriptor_DemPrimaryDataBlock1 (20u) 
#define NvMConf_NvMBlockDescriptor_NvM_NFC_FS_debug_switch (21u) 
#define NvMConf_NvMBlockDescriptor_NvM_DID_VW_Coding_Value (22u) 
#define NvMConf_NvMBlockDescriptor_NvM_DID_VW_System_Name_Or_Engine_Type (23u) 
#define NvMConf_NvMBlockDescriptor_NvM_DID_VW_Data_Set_Number_Or_ECU_Data_Container_Number (24u) 
#define NvMConf_NvMBlockDescriptor_NvM_DID_VW_Data_Set_Version_Number (25u) 
#define NvMConf_NvMBlockDescriptor_NvM_DID_VW_Workshop_System_Name (26u) 
#define NvMConf_NvMBlockDescriptor_NvM_DID_Huf_EOL_Done (27u) 
#define NvMConf_NvMBlockDescriptor_NvM_DID_NFC_Homologation_mode (28u) 
#define NvMConf_NvMBlockDescriptor_NvM_DID_OBD_Driving_Cycle_set (29u) 
#define NvMConf_NvMBlockDescriptor_NvM_DID_Programming_preconditions (30u) 
#define NvMConf_NvMBlockDescriptor_NvM_TIME_NFC_DIAG (31u) 
#define NvMConf_NvMBlockDescriptor_NvM_DIGIT_NFC (32u) 
#define NvMConf_NvMBlockDescriptor_NvM_0xF18F (33u) 
#define NvMConf_NvMBlockDescriptor_NvM_0x0250 (34u) 
#define NvMConf_NvMBlockDescriptor_NvM_Sfd_PersistentData (35u) 
#define NvMConf_NvMBlockDescriptor_NvM_Sfd_LogData (36u) 
#define NvMConf_NvMBlockDescriptor_NvM_Sfd_ConfigurationFingerprintData (37u) 
#define NvMConf_NvMBlockDescriptor_NvM_DID_HUF_Production_Date (38u) 
#define NvMConf_NvMBlockDescriptor_NvM_DID_Katek_EOL_Done (39u) 
#define NvMConf_NvMBlockDescriptor_NvM_Sfd_Test_Mode (40u) 
#define NvMConf_NvMBlockDescriptor_NvM_Fingerprint (41u) 
#define NvMConf_NvMBlockDescriptor_NvM_Fingerprint_BL (42u) 
#define NvMConf_NvMBlockDescriptor_NvM_AswProgAttemtsCnt (43u) 
#define NvMConf_NvMBlockDescriptor_NvM_Other_Sw_Version_Number (44u) 
#define NvMConf_NvMBlockDescriptor_NvM_VEHICLE_IDENTIFIER_NFC (45u) 
#define NvMConf_NvMBlockDescriptor_NvM_VEHICLE_IDENTIFIER_VALIDITY_NFC (46u) 
#define NvMConf_NvMBlockDescriptor_NvM_AswProgAttemtsCnt_BL (47u) 


/* CONST_DESCRIPTOR_TABLE contains all block relevant data, including the compiled config ID
 */
#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* Additional published parameter because e.g. in case of validate all RAM
 * Blocks it is nice to know the number of Blocks. But take care: this number
 * of Blocks includes Block 0 and Block 1, which are the MultiBlock and the
 * Configuration Block - user Blocks start wiht index 2!
 */
extern CONST(NvM_BlockIdType, NVM_PUBLIC_CONST) NvM_NoOfBlockIds_t;

/* Additional published parameter because in case of a clear EEPROM, it is
 * necessary, to write the Configuration Block containing this Compiled
 * Configuration ID to EEPROM
 */
/* Compiled Configuration ID as defined in NvM_Cfg.c */
extern CONST(NvM_CompiledConfigIdType, NVM_PUBLIC_CONST) NvM_CompiledConfigId_t; /* PRQA S 0759 */ /* MD_MSR_Union */

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* Component define block (available, if EcuC module is active, otherwise only NVM_DUMMY_STATEMENTs are defined*/
#ifndef NVM_USE_DUMMY_STATEMENT
#define NVM_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef NVM_DUMMY_STATEMENT
#define NVM_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef NVM_DUMMY_STATEMENT_CONST
#define NVM_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef NVM_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define NVM_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef NVM_ATOMIC_VARIABLE_ACCESS
#define NVM_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef NVM_PROCESSOR_S32K144
#define NVM_PROCESSOR_S32K144
#endif
#ifndef NVM_COMP_IAR
#define NVM_COMP_IAR
#endif
#ifndef NVM_GEN_GENERATOR_MSR
#define NVM_GEN_GENERATOR_MSR
#endif
#ifndef NVM_CPUTYPE_BITORDER_LSB2MSB
#define NVM_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef NVM_CONFIGURATION_VARIANT_PRECOMPILE
#define NVM_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef NVM_CONFIGURATION_VARIANT_LINKTIME
#define NVM_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef NVM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define NVM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef NVM_CONFIGURATION_VARIANT
#define NVM_CONFIGURATION_VARIANT NVM_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef NVM_POSTBUILD_VARIANT_SUPPORT
#define NVM_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif


/* ---- end public configuration section ---------------------------------- */
#endif /* NVM_CFG_H_PUBLIC */

/* PRQA L:MemMap */

/**********************************************************************************************************************
 *  END OF FILE: NvM_Cfg.h
 *********************************************************************************************************************/

