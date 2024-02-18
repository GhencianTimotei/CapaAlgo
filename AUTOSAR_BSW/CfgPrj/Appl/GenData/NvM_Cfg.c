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
 *              File: NvM_Cfg.c
 *   Generation Time: 2024-01-27 22:55:12
 *           Project: DaVinciConfigurationS32K144 - Version 1.0
 *          Delivery: CBD2100188_D01
 *      Tool Version: DaVinci Configurator  5.23.45 SP4
 *
 *
 *********************************************************************************************************************/

	
/* PRQA S 5087 MemMap */ /* MD_MSR_MemMap */
    
/**********************************************************************************************************************
 *  MODULE SWITCH
 *********************************************************************************************************************/
/* this switch enables the header file(s) to hide some parts. */
#define NVM_CFG_SOURCE

/* multiple inclusion protection */
#define NVM_H_

/* Required for RTE ROM block definitions */
#define RTE_MICROSAR_PIM_EXPORT

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/* This tag will only be replaced, if one or more callbacks via Service Ports had been configured */


/**********************************************************************************************************************
 *  MODULE HEADER INCLUDES
 *********************************************************************************************************************/
/* only includes the public part of config */
#include "NvM_Cfg.h"
#include "NvM_PrivateCfg.h"



/**********************************************************************************************************************
 *  VERSION CHECKS
 *********************************************************************************************************************/
#if ((NVM_CFG_MAJOR_VERSION != (8u)) \
        || (NVM_CFG_MINOR_VERSION != (0u)))
# error "Version numbers of NvM_Cfg.c and NvM_Cfg.h are inconsistent!"
#endif

/* include list of the callback definitions */
#include "NvmMng.h" 
#include "Dem_Lcfg.h" 
#include "Dem_Cbk.h" 
#include "PDL.h" 
#include "CAN_DiagUsr.h" 


/* include configured file declaring or defining resource (un)locking service(s) */
#include "SchM_NvM.h"

/**********************************************************************************************************************
 *  PUBLIC CONSTANTS
 *********************************************************************************************************************/
#define NVM_START_SEC_CONST_16
#include "MemMap.h"

/* maximum number of bytes to be processed in one crc calculation step */
CONST(uint16, NVM_CONFIG_CONST) NvM_NoOfCrcBytes_u16 = 64u;

/* constant holding Crc queue size value */
CONST(uint16, NVM_PRIVATE_CONST) NvM_CrcQueueSize_u16 = NVM_TOTAL_NUM_OF_NVRAM_BLOCKS;

#define NVM_STOP_SEC_CONST_16
#include "MemMap.h"

/* 8Bit Data section containing the CRC buffers, as well as the internal buffer */
#define NVM_START_SEC_VAR_NO_INIT_8
#include "MemMap.h"

static VAR(uint8, NVM_PRIVATE_DATA) NvMConfigBlock_RamBlock_au8[6u];

#if ((NVM_CRC_INT_BUFFER == STD_ON) || (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON))
static VAR(uint8, NVM_PRIVATE_DATA) NvM_UNLOCK_SENSOR_BLOCK_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_LOCK_SENSOR_BLOCK_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_Other_HUF_BLOCK_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_INDUCTIVE_SENSOR_BLOCK_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_EMERGENCY_ACCESS_BLOCK_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_FD02_SPARE_BLOCK_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_AUDI_PARAMS_BLOCK_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_BATTERY_SUPERVISOR_BLOCK_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) DemAdminDataBlock_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) DemPrimaryDataBlock0_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) DemPrimaryDataBlock6_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) DemPrimaryDataBlock2_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) DemPrimaryDataBlock3_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) DemPrimaryDataBlock4_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) DemPrimaryDataBlock5_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) DemPrimaryDataBlock7_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) DemStatusDataBlock_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) DemPrimaryDataBlock1_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_NFC_FS_debug_switch_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_VW_System_Name_Or_Engine_Type_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_VW_Data_Set_Number_Or_ECU_Data_Container_Number_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_VW_Data_Set_Version_Number_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_VW_Workshop_System_Name_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_Huf_EOL_Done_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_NFC_Homologation_mode_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_Programming_preconditions_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_TIME_NFC_DIAG_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DIGIT_NFC_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_HUF_Production_Date_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_Katek_EOL_Done_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_Sfd_Test_Mode_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_Fingerprint_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_Fingerprint_BL_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_AswProgAttemtsCnt_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_Other_Sw_Version_Number_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_VEHICLE_IDENTIFIER_NFC_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_VEHICLE_IDENTIFIER_VALIDITY_NFC_Crc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_AswProgAttemtsCnt_BL_Crc[4uL]; 


/* create the internal buffer of size NVM_INTERNAL_BUFFER_LENGTH */
VAR(uint8, NVM_PRIVATE_DATA) NvM_InternalBuffer_au8[NVM_INTERNAL_BUFFER_LENGTH]; /* PRQA S 1533 */ /* MD_NvM_Cfg_8.9_InternalBuffer */
#endif


 /*  CRC buffers for CRCCompareMechanism  */ 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_UNLOCK_SENSOR_BLOCK_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_LOCK_SENSOR_BLOCK_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_Other_HUF_BLOCK_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_INDUCTIVE_SENSOR_BLOCK_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_EMERGENCY_ACCESS_BLOCK_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_FD02_SPARE_BLOCK_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_AUDI_PARAMS_BLOCK_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_BATTERY_SUPERVISOR_BLOCK_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_NFC_FS_debug_switch_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_VW_Coding_Value_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_VW_System_Name_Or_Engine_Type_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_VW_Data_Set_Number_Or_ECU_Data_Container_Number_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_VW_Data_Set_Version_Number_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_VW_Workshop_System_Name_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_Huf_EOL_Done_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_NFC_Homologation_mode_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_OBD_Driving_Cycle_set_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_Programming_preconditions_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_TIME_NFC_DIAG_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DIGIT_NFC_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_HUF_Production_Date_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_DID_Katek_EOL_Done_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_Sfd_Test_Mode_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_Other_Sw_Version_Number_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_VEHICLE_IDENTIFIER_NFC_CompCrc[4uL]; 
static VAR(uint8, NVM_PRIVATE_DATA) NvM_VEHICLE_IDENTIFIER_VALIDITY_NFC_CompCrc[4uL]; 



#define NVM_STOP_SEC_VAR_NO_INIT_8
#include "MemMap.h"

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

CONST(NvM_BlockIdType, NVM_PUBLIC_CONST) NvM_NoOfBlockIds_t = NVM_TOTAL_NUM_OF_NVRAM_BLOCKS;

CONST(NvM_CompiledConfigIdType, NVM_PUBLIC_CONST) NvM_CompiledConfigId_t = {(uint16)NVM_COMPILED_CONFIG_ID}; /* PRQA S 0759 */ /* MD_MSR_Union */
 
 
/* block descriptor table that holds the static configuration parameters of the RAM, ROM and NVBlocks.
* This table has to be adjusted according to the configuration of the NVManager.
*/

CONST(NvM_BlockDescriptorType, NVM_CONFIG_CONST) NvM_BlockDescriptorTable_at[NVM_TOTAL_NUM_OF_NVRAM_BLOCKS] =
    {
      { /*  MultiBlockRequest  */ 
        NULL_PTR /*  NvMRamBlockDataAddress  */ , 
        NULL_PTR /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NULL_PTR /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
        { 0u } /*  Flags  */ , 
        0x0001u /*  NV block Base number (defined by FEE/EA)  */ , 
        0U /*  NvMNvBlockLength  */ , 
        0U /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        0u /*  NvBlockCount  */ , 
        255u /*  NvMBlockJobPriority  */ , 
        0u /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_USE_CRC_OFF /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvMConfigBlock  */ 
        (NvM_RamAddressType)NvMConfigBlock_RamBlock_au8 /*  NvMRamBlockDataAddress  */ , 
        NULL_PTR /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NULL_PTR /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_OFF, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_ON, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0A40u /*  NV block Base number (defined by FEE/EA)  */ , 
        2u /*  NvMNvBlockLength  */ , 
        2u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        2u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_REDUNDANT /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_LED_DUTY  */ 
        NULL_PTR /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&PDL.LED_DUTY /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NULL_PTR /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_OFF, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0300u /*  NV block Base number (defined by FEE/EA)  */ , 
        1u /*  NvMNvBlockLength  */ , 
        1u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_UNLOCK_SENSOR_BLOCK  */ 
        (NvM_RamAddressType)&ST_unlock_sensor_NVM_params /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&PDL.UNLOCK_SENSOR_BLOCK_DEFAULT /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        Unlock_BlockOperation_Callback /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_UNLOCK_SENSOR_BLOCK_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_UNLOCK_SENSOR_BLOCK_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0400u /*  NV block Base number (defined by FEE/EA)  */ , 
        36u /*  NvMNvBlockLength  */ , 
        36u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_LOCK_SENSOR_BLOCK  */ 
        (NvM_RamAddressType)&ST_lock_sensor_NVM_params /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&PDL.LOCK_SENSOR_BLOCK_DEFAULT /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        Lock_BlockOperation_Callback /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_LOCK_SENSOR_BLOCK_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_LOCK_SENSOR_BLOCK_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0040u /*  NV block Base number (defined by FEE/EA)  */ , 
        36u /*  NvMNvBlockLength  */ , 
        36u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_Other_HUF_BLOCK  */ 
        (NvM_RamAddressType)&ST_Other_HUF_NVM_params /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&ST_Other_HUF_NVM_default_params /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        Other_HUF_BlockOperation_Callback /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_Other_HUF_BLOCK_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_Other_HUF_BLOCK_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0440u /*  NV block Base number (defined by FEE/EA)  */ , 
        20u /*  NvMNvBlockLength  */ , 
        20u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_INDUCTIVE_SENSOR_BLOCK  */ 
        (NvM_RamAddressType)&ST_inductive_sensor_NVM_params /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&PDL.INDUCTIVE_SENSOR_BLOCK_DEFAULT /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        Inductive_BlockOperation_Callback /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_INDUCTIVE_SENSOR_BLOCK_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_INDUCTIVE_SENSOR_BLOCK_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0480u /*  NV block Base number (defined by FEE/EA)  */ , 
        28u /*  NvMNvBlockLength  */ , 
        28u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_EMERGENCY_ACCESS_BLOCK  */ 
        (NvM_RamAddressType)&ST_emergency_access_NVM_params /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&PDL.EMERGENCY_ACCESS_BLOCK_DEFAULT /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        Emergency_BlockOperation_Callback /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_EMERGENCY_ACCESS_BLOCK_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_EMERGENCY_ACCESS_BLOCK_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0080u /*  NV block Base number (defined by FEE/EA)  */ , 
        12u /*  NvMNvBlockLength  */ , 
        12u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_FD02_SPARE_BLOCK  */ 
        (NvM_RamAddressType)&ST_FD02_spare_NVM_params /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&PDL.FD02_SPARE_BLOCK_DEFAULT /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        FD02Spare_BlockOperation_Callback /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_FD02_SPARE_BLOCK_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_FD02_SPARE_BLOCK_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0900u /*  NV block Base number (defined by FEE/EA)  */ , 
        44u /*  NvMNvBlockLength  */ , 
        44u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_AUDI_PARAMS_BLOCK  */ 
        (NvM_RamAddressType)&ST_AUDI_NVM_params /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&PDL.AUDI_PARAMS_BLOCK_DEFAULT /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        Audi_Params_BlockOperation_Callback /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_AUDI_PARAMS_BLOCK_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_AUDI_PARAMS_BLOCK_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0500u /*  NV block Base number (defined by FEE/EA)  */ , 
        50u /*  NvMNvBlockLength  */ , 
        50u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_BATTERY_SUPERVISOR_BLOCK  */ 
        (NvM_RamAddressType)&ST_battery_supervisor_NVM_params /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&PDL.BATTERY_SUPERVISOR_BLOCK_DEFAULT /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        Battery_BlockOperation_Callback /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_BATTERY_SUPERVISOR_BLOCK_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_BATTERY_SUPERVISOR_BLOCK_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0540u /*  NV block Base number (defined by FEE/EA)  */ , 
        12u /*  NvMNvBlockLength  */ , 
        12u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  DemAdminDataBlock  */ 
        (NvM_RamAddressType)&Dem_Cfg_AdminData /*  NvMRamBlockDataAddress  */ , 
        NULL_PTR /*  NvMRomBlockDataAddress  */ , 
        Dem_NvM_InitAdminData /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        Dem_NvM_JobFinished /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        DemAdminDataBlock_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_ON, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x04C0u /*  NV block Base number (defined by FEE/EA)  */ , 
        (uint16)sizeof(Dem_Cfg_AdminData) /*  NvMNvBlockLength  */ , 
        (uint16)sizeof(Dem_Cfg_AdminData) /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  DemPrimaryDataBlock0  */ 
        (NvM_RamAddressType)&Dem_Cfg_PrimaryEntry_0 /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&Dem_Cfg_MemoryEntryInit /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        Dem_NvM_JobFinished /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        DemPrimaryDataBlock0_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_ON, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0580u /*  NV block Base number (defined by FEE/EA)  */ , 
        (uint16)sizeof(Dem_Cfg_PrimaryEntry_0) /*  NvMNvBlockLength  */ , 
        (uint16)sizeof(Dem_Cfg_PrimaryEntry_0) /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  DemPrimaryDataBlock6  */ 
        (NvM_RamAddressType)&Dem_Cfg_PrimaryEntry_6 /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&Dem_Cfg_MemoryEntryInit /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        Dem_NvM_JobFinished /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        DemPrimaryDataBlock6_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_ON, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x00C0u /*  NV block Base number (defined by FEE/EA)  */ , 
        (uint16)sizeof(Dem_Cfg_PrimaryEntry_6) /*  NvMNvBlockLength  */ , 
        (uint16)sizeof(Dem_Cfg_PrimaryEntry_6) /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  DemPrimaryDataBlock2  */ 
        (NvM_RamAddressType)&Dem_Cfg_PrimaryEntry_2 /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&Dem_Cfg_MemoryEntryInit /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        Dem_NvM_JobFinished /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        DemPrimaryDataBlock2_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_ON, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x05C0u /*  NV block Base number (defined by FEE/EA)  */ , 
        (uint16)sizeof(Dem_Cfg_PrimaryEntry_2) /*  NvMNvBlockLength  */ , 
        (uint16)sizeof(Dem_Cfg_PrimaryEntry_2) /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  DemPrimaryDataBlock3  */ 
        (NvM_RamAddressType)&Dem_Cfg_PrimaryEntry_3 /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&Dem_Cfg_MemoryEntryInit /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        Dem_NvM_JobFinished /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        DemPrimaryDataBlock3_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_ON, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0600u /*  NV block Base number (defined by FEE/EA)  */ , 
        (uint16)sizeof(Dem_Cfg_PrimaryEntry_3) /*  NvMNvBlockLength  */ , 
        (uint16)sizeof(Dem_Cfg_PrimaryEntry_3) /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  DemPrimaryDataBlock4  */ 
        (NvM_RamAddressType)&Dem_Cfg_PrimaryEntry_4 /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&Dem_Cfg_MemoryEntryInit /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        Dem_NvM_JobFinished /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        DemPrimaryDataBlock4_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_ON, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0640u /*  NV block Base number (defined by FEE/EA)  */ , 
        (uint16)sizeof(Dem_Cfg_PrimaryEntry_4) /*  NvMNvBlockLength  */ , 
        (uint16)sizeof(Dem_Cfg_PrimaryEntry_4) /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  DemPrimaryDataBlock5  */ 
        (NvM_RamAddressType)&Dem_Cfg_PrimaryEntry_5 /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&Dem_Cfg_MemoryEntryInit /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        Dem_NvM_JobFinished /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        DemPrimaryDataBlock5_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_ON, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0100u /*  NV block Base number (defined by FEE/EA)  */ , 
        (uint16)sizeof(Dem_Cfg_PrimaryEntry_5) /*  NvMNvBlockLength  */ , 
        (uint16)sizeof(Dem_Cfg_PrimaryEntry_5) /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  DemPrimaryDataBlock7  */ 
        (NvM_RamAddressType)&Dem_Cfg_PrimaryEntry_7 /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&Dem_Cfg_MemoryEntryInit /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        Dem_NvM_JobFinished /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        DemPrimaryDataBlock7_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_ON, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0680u /*  NV block Base number (defined by FEE/EA)  */ , 
        (uint16)sizeof(Dem_Cfg_PrimaryEntry_7) /*  NvMNvBlockLength  */ , 
        (uint16)sizeof(Dem_Cfg_PrimaryEntry_7) /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  DemStatusDataBlock  */ 
        (NvM_RamAddressType)&Dem_Cfg_StatusData /*  NvMRamBlockDataAddress  */ , 
        NULL_PTR /*  NvMRomBlockDataAddress  */ , 
        Dem_NvM_InitStatusData /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        Dem_NvM_JobFinished /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        DemStatusDataBlock_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_ON, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x06C0u /*  NV block Base number (defined by FEE/EA)  */ , 
        (uint16)sizeof(Dem_Cfg_StatusData) /*  NvMNvBlockLength  */ , 
        (uint16)sizeof(Dem_Cfg_StatusData) /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  DemPrimaryDataBlock1  */ 
        (NvM_RamAddressType)&Dem_Cfg_PrimaryEntry_1 /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&Dem_Cfg_MemoryEntryInit /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        Dem_NvM_JobFinished /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        DemPrimaryDataBlock1_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_ON, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0700u /*  NV block Base number (defined by FEE/EA)  */ , 
        (uint16)sizeof(Dem_Cfg_PrimaryEntry_1) /*  NvMNvBlockLength  */ , 
        (uint16)sizeof(Dem_Cfg_PrimaryEntry_1) /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_NFC_FS_debug_switch  */ 
        (NvM_RamAddressType)&DID_NFC_debugSwitch_NVM_param /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&DID_NFC_debugSwitch_NVM_default_param /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NFC_FS_DebugSwitch_BlockOperation_Callback /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_NFC_FS_debug_switch_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_NFC_FS_debug_switch_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0180u /*  NV block Base number (defined by FEE/EA)  */ , 
        1u /*  NvMNvBlockLength  */ , 
        1u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_DID_VW_Coding_Value  */ 
        NULL_PTR /*  NvMRamBlockDataAddress  */ , 
        NULL_PTR /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NULL_PTR /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_DID_VW_Coding_Value_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_OFF, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0740u /*  NV block Base number (defined by FEE/EA)  */ , 
        100u /*  NvMNvBlockLength  */ , 
        100u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_DID_VW_System_Name_Or_Engine_Type  */ 
        (NvM_RamAddressType)&ST_DID_SysNameOrEngineType_NVM_params /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&ST_DID_SysNameOrEngineType_NVM_default_params /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_DID_VW_System_Name_Or_Engine_Type_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_DID_VW_System_Name_Or_Engine_Type_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0AC0u /*  NV block Base number (defined by FEE/EA)  */ , 
        13u /*  NvMNvBlockLength  */ , 
        13u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_DID_VW_Data_Set_Number_Or_ECU_Data_Container_Number  */ 
        (NvM_RamAddressType)&ST_DID_DataSetNr_NVM_params /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&ST_DID_DataSetNr_NVM_default_params /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_DID_VW_Data_Set_Number_Or_ECU_Data_Container_Number_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_DID_VW_Data_Set_Number_Or_ECU_Data_Container_Number_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0280u /*  NV block Base number (defined by FEE/EA)  */ , 
        11u /*  NvMNvBlockLength  */ , 
        11u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_DID_VW_Data_Set_Version_Number  */ 
        (NvM_RamAddressType)&ST_DID_DataSetVersionNr_NVM_params /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&ST_DID_DataSetVersionNr_NVM_default_params /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_DID_VW_Data_Set_Version_Number_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_DID_VW_Data_Set_Version_Number_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0880u /*  NV block Base number (defined by FEE/EA)  */ , 
        4u /*  NvMNvBlockLength  */ , 
        4u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_DID_VW_Workshop_System_Name  */ 
        (NvM_RamAddressType)&ST_DID_WorkshopSystemName_NVM_params /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&ST_DID_WorkshopSystemName_NVM_default_params /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_DID_VW_Workshop_System_Name_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_DID_VW_Workshop_System_Name_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0B00u /*  NV block Base number (defined by FEE/EA)  */ , 
        5u /*  NvMNvBlockLength  */ , 
        5u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_DID_Huf_EOL_Done  */ 
        (NvM_RamAddressType)&DID_Huf_EOL_Done_NVM_param /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&DID_Huf_EOL_Done_NVM_default_param /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_DID_Huf_EOL_Done_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_DID_Huf_EOL_Done_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0340u /*  NV block Base number (defined by FEE/EA)  */ , 
        1u /*  NvMNvBlockLength  */ , 
        1u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_DID_NFC_Homologation_mode  */ 
        (NvM_RamAddressType)&DID_HomologationMode_NVM_param /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&DID_HomologationMode_NVM_default_param /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NFC_HomologationModes_BlockOperation_Callback /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_DID_NFC_Homologation_mode_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_DID_NFC_Homologation_mode_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x08C0u /*  NV block Base number (defined by FEE/EA)  */ , 
        1u /*  NvMNvBlockLength  */ , 
        1u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_DID_OBD_Driving_Cycle_set  */ 
        NULL_PTR /*  NvMRamBlockDataAddress  */ , 
        NULL_PTR /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NULL_PTR /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_DID_OBD_Driving_Cycle_set_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_OFF, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0380u /*  NV block Base number (defined by FEE/EA)  */ , 
        1u /*  NvMNvBlockLength  */ , 
        1u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_DID_Programming_preconditions  */ 
        (NvM_RamAddressType)&ST_DID_ProgrammingPreconditions_NVM_params /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&ST_DID_ProgrammingPreconditions_NVM_default_params /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_DID_Programming_preconditions_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_DID_Programming_preconditions_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x03C0u /*  NV block Base number (defined by FEE/EA)  */ , 
        4u /*  NvMNvBlockLength  */ , 
        4u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_TIME_NFC_DIAG  */ 
        (NvM_RamAddressType)&ST_TIME_NFC_DIAG_NVM_params /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&PDL.TIME_NFC_DIAG /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_TIME_NFC_DIAG_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_TIME_NFC_DIAG_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0A80u /*  NV block Base number (defined by FEE/EA)  */ , 
        20u /*  NvMNvBlockLength  */ , 
        20u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_DIGIT_NFC  */ 
        (NvM_RamAddressType)&ST_DIGIT_NFC_NVM_params /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&PDL.ST_DIGIT_NFC_NVM_params_DEFAULT /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_DIGIT_NFC_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_DIGIT_NFC_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0980u /*  NV block Base number (defined by FEE/EA)  */ , 
        25u /*  NvMNvBlockLength  */ , 
        25u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_0xF18F  */ 
        NULL_PTR /*  NvMRamBlockDataAddress  */ , 
        NULL_PTR /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NULL_PTR /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_OFF, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0780u /*  NV block Base number (defined by FEE/EA)  */ , 
        32u /*  NvMNvBlockLength  */ , 
        32u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_0x0250  */ 
        NULL_PTR /*  NvMRamBlockDataAddress  */ , 
        NULL_PTR /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NULL_PTR /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_OFF, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x07C0u /*  NV block Base number (defined by FEE/EA)  */ , 
        32u /*  NvMNvBlockLength  */ , 
        32u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        2u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_REDUNDANT /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_Sfd_PersistentData  */ 
        NULL_PTR /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&SFD_PersistentBuffer_Default_params /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NULL_PTR /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_OFF, 
          NVM_SELECT_BLOCK_FOR_READALL_OFF, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x01C0u /*  NV block Base number (defined by FEE/EA)  */ , 
        30u /*  NvMNvBlockLength  */ , 
        30u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        64u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_Sfd_LogData  */ 
        NULL_PTR /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&SFD_LogData_Default_params /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NULL_PTR /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_OFF, 
          NVM_SELECT_BLOCK_FOR_READALL_OFF, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x09C0u /*  NV block Base number (defined by FEE/EA)  */ , 
        19u /*  NvMNvBlockLength  */ , 
        19u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        54u /*  NvBlockCount  */ , 
        64u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_DATASET /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_Sfd_ConfigurationFingerprintData  */ 
        NULL_PTR /*  NvMRamBlockDataAddress  */ , 
        NULL_PTR /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NULL_PTR /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_OFF, 
          NVM_SELECT_BLOCK_FOR_READALL_OFF, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0A00u /*  NV block Base number (defined by FEE/EA)  */ , 
        514u /*  NvMNvBlockLength  */ , 
        514u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        64u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_DID_HUF_Production_Date  */ 
        (NvM_RamAddressType)&DID_HUF_Production_Date_NVM_param /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&DID_HUF_Production_Date_NVM_default_param /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_DID_HUF_Production_Date_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_DID_HUF_Production_Date_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_OFF, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0200u /*  NV block Base number (defined by FEE/EA)  */ , 
        15u /*  NvMNvBlockLength  */ , 
        15u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_DID_Katek_EOL_Done  */ 
        (NvM_RamAddressType)&DID_Katek_EOL_Done_NVM_param /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&DID_Katek_EOL_Done_NVM_default_param /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_DID_Katek_EOL_Done_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_DID_Katek_EOL_Done_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_OFF, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0800u /*  NV block Base number (defined by FEE/EA)  */ , 
        2u /*  NvMNvBlockLength  */ , 
        2u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_Sfd_Test_Mode  */ 
        (NvM_RamAddressType)&NVM_Sfd_Test_Mode_RAM /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&NVM_Sfd_Test_Mode_Default /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_Sfd_Test_Mode_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_Sfd_Test_Mode_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0840u /*  NV block Base number (defined by FEE/EA)  */ , 
        1u /*  NvMNvBlockLength  */ , 
        1u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_Fingerprint  */ 
        (NvM_RamAddressType)&AU8_NVM_Fingerprint /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&AU8_NVM_FingerprintDefault /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_Fingerprint_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0940u /*  NV block Base number (defined by FEE/EA)  */ , 
        9u /*  NvMNvBlockLength  */ , 
        9u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_Fingerprint_BL  */ 
        (NvM_RamAddressType)&AU8_NVM_Fingerprint_BL /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&AU8_NVM_FingerprintDefault /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_Fingerprint_BL_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0C80u /*  NV block Base number (defined by FEE/EA)  */ , 
        9u /*  NvMNvBlockLength  */ , 
        9u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_AswProgAttemtsCnt  */ 
        (NvM_RamAddressType)&AU8_NVM_AswProgAttemtsCnt /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&AU8_NVM_AswProgAttemtsCntDefault /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_AswProgAttemtsCnt_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0BC0u /*  NV block Base number (defined by FEE/EA)  */ , 
        2u /*  NvMNvBlockLength  */ , 
        2u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_Other_Sw_Version_Number  */ 
        (NvM_RamAddressType)&NVM_Other_Sw_Version_Number_RAM /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&NVM_Other_Sw_Version_Number_Default /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_Other_Sw_Version_Number_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_Other_Sw_Version_Number_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0B40u /*  NV block Base number (defined by FEE/EA)  */ , 
        4u /*  NvMNvBlockLength  */ , 
        4u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_VEHICLE_IDENTIFIER_NFC  */ 
        (NvM_RamAddressType)&ST_vehicle_identifier_NFC_NvM /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&ST_vehicle_identifier_NFC_NvM_Default /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_VEHICLE_IDENTIFIER_NFC_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_VEHICLE_IDENTIFIER_NFC_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0C00u /*  NV block Base number (defined by FEE/EA)  */ , 
        8u /*  NvMNvBlockLength  */ , 
        8u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_VEHICLE_IDENTIFIER_VALIDITY_NFC  */ 
        (NvM_RamAddressType)&ST_vehicle_identifier_validity_NFC_NvM /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&ST_vehicle_identifier_validirty_NFC_NvM_Default /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_VEHICLE_IDENTIFIER_VALIDITY_NFC_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NvM_VEHICLE_IDENTIFIER_VALIDITY_NFC_CompCrc /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_ON, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0C40u /*  NV block Base number (defined by FEE/EA)  */ , 
        1u /*  NvMNvBlockLength  */ , 
        1u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }, 
      { /*  NvM_AswProgAttemtsCnt_BL  */ 
        (NvM_RamAddressType)&AU8_NVM_AswProgAttemtsCnt_BL /*  NvMRamBlockDataAddress  */ , 
        (NvM_RomAddressType)&AU8_NVM_AswProgAttemtsCntDefault /*  NvMRomBlockDataAddress  */ , 
        NULL_PTR /*  NvMInitBlockCallback  */ , 
        NULL_PTR /*  NvMInitBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMSingleBlockCallback  */ , 
        NULL_PTR /*  NvMSingleBlockCallback (extended)  */ , 
        NULL_PTR /*  NvMReadRamBlockFromNvCallback  */ , 
        NULL_PTR /*  NvMWriteRamBlockToNvCallback  */ , 
        NULL_PTR /*  NvMBlockPreWriteTransformCallback  */ , 
        NULL_PTR /*  NvMBlockPostReadTransformCallback  */ , 
        NvM_AswProgAttemtsCnt_BL_Crc /*  RamBlockCRC data buffer (defined by NvM)  */ , 
        NULL_PTR /*  CRCCompMechanism CRC data (defined by NvM)  */ , 
                {
          NVM_CALC_RAM_BLOCK_CRC_OFF, 
          NVM_BLOCK_WRITE_PROT_OFF, 
          NVM_BLOCK_WRITE_BLOCK_ONCE_OFF, 
          NVM_RESISTANT_TO_CHANGED_SW_ON, 
          NVM_SELECT_BLOCK_FOR_READALL_ON, 
          NVM_SELECT_BLOCK_FOR_WRITEALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_READALL_OFF, 
          NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF, 
          NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF, 
          NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF, 
          NVM_BLOCK_NOTIFY_BSWM_OFF
        } /*  Flags  */ , 
        0x0CC0u /*  NV block Base number (defined by FEE/EA)  */ , 
        2u /*  NvMNvBlockLength  */ , 
        2u /*  NvMNvBlockNVRAMDataLength  */ , 
        0u /*  NvCryptoReference  */ , 
        1u /*  NvBlockCount  */ , 
        127u /*  NvMBlockJobPriority  */ , 
        MEMIF_Fee /*  Device Id (defined by MemIf)  */ , 
        NVM_BLOCK_NATIVE /*  NvMBlockManagementType  */ , 
        NVM_BLOCK_CRC_32_ON /*  NvMBlockCrcType  */ 
      }
    };

/* Permanent RAM and ROM block length checks - compile time (only available for blocks with enabled length check */

/* PRQA S 3494, 3213, 1755 BlockLengthChecks */ /* MD_NvM_Cfg_14.3, MD_NvM_Cfg_2.4 */

/* How does it work:
 * data length = sizeof(ramBlock - CrcLength 
 *     - CRC internal buffer enabled: CRC length == 0, RAM blocks store only data, CRC is handles internally
 *     - CRC internal buffer disabled: CRC length is the number of CRC bytes, for blocks without CRC the length == 0
 *     - for ROM blocks the CRC does not matter
 * Data length has to be > or < or == to configured NvM block length, depending on configuration (see above). 
 * In case the lengths do not match a bitfield with length -1 will be created and shall cause a compiler error.
 * The compiler error shall mark the line with invalid bitfield (bitfield length == -1) - the line includes all required information:
 *     - Block_ + NvM block name
 *     - length error description
 *     - RAM block name, CRC length and configured NvM block length
 */

typedef unsigned int NvM_LengthCheck;
 
/* Block Length Check and Automatic Block Length enabled: error if sizeof RAM block is greater than the configured block length */
#define SizeOfRamBlockGreaterThanConfiguredLength(ramBlock, crcLength, blockLength) (((sizeof(ramBlock) - (crcLength)) > (blockLength)) ? -1 : 1) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/* Block Length Check and Strict Length Check enabled: error if the sizeof RAM block does not match the configured block length */
#define SizeOfRamBlockDoesNotMatchConfiguredLength(ramBlock, crcLength, blockLength) (((sizeof(ramBlock) - (crcLength)) != (blockLength)) ? -1 : 1) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/* Block Length Check enabled and Strict Length Check disabled: error if the sizeof RAM block is less than the configured block length */
#define SizeOfRamBlockLessThanConfiguredLength(ramBlock, crcLength, blockLength) (((sizeof(ramBlock) - (crcLength)) < (blockLength)) ? -1 : 1) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* RAM block length checks */
struct PermanentRamBlockLengthChecks {
  NvM_LengthCheck Block_DemAdminDataBlock : SizeOfRamBlockGreaterThanConfiguredLength(Dem_Cfg_AdminData, 0u, 12u);
};

/* Block Length Check and Automatic Block Length enabled: error if sizeof ROM block is less than sizeof RAM block */
#define SizeOfRomBlockLessThanSizeOfRamBlock(romBlock, ramBlock) ((sizeof(romBlock) < sizeof(ramBlock)) ? -1 : 1) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/* Block Length Check and Strict Length Check enabled: error if the sizeof ROM block does not match the configured block length */
#define SizeOfRomBlockDoesNotMatchConfiguredLength(romBlock, blockLength) ((sizeof(romBlock) != (blockLength)) ? -1 : 1) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/* Block Length Check enabled, Strict Length disabled: error if the sizeof ROM block is less than the configured block length */
#define SizeOfRomBlockLessThanConfiguredLength(romBlock, blockLength) ((sizeof(romBlock) < (blockLength)) ? -1 : 1) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* ROM block length checks */



/* PRQA L:BlockLengthChecks */

/* Permanent RAM and ROM block length checks - END */

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#if(NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
/* Job Queue used for normal and high prio jobs */
VAR(NvM_QueueEntryType, NVM_PRIVATE_DATA) NvM_JobQueue_at[NVM_SIZE_STANDARD_JOB_QUEUE + NVM_SIZE_IMMEDIATE_JOB_QUEUE];
#endif

#define NVM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************
*  NvM_EnterCriticalSection
**********************************************************************************************************************/
/*!
 * \internal
 *  - #10 enter SchM exclusive area for NvM 
 * \endinternal
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_EnterCriticalSection(void)
{
  /* do what ever was defined to do for locking the resources */
  SchM_Enter_NvM_NVM_EXCLUSIVE_AREA_0();
}

/**********************************************************************************************************************
*  NvM_ExitCriticalSection
**********************************************************************************************************************/
/*!
 * \internal
 *  - #10 exit SchM exclusive area for NvM 
 * \endinternal
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_ExitCriticalSection(void)
{
  /* do what ever was defined to do for unlocking the resources */
  SchM_Exit_NvM_NVM_EXCLUSIVE_AREA_0();
}

/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
#define NvM_invokeMultiBlockMode(serv, res)  /*  if NvMBswMMultiBlockJobStatusInformation is TRUE  */

/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
#define NvM_invokeMultiCbk(serv, res)   /*  if Multi Block Callback is configured  */

/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
#define NvM_invokeDetectedLossOfRedundancyCallback(blockId) NVM_DUMMY_STATEMENT((blockId))

/**********************************************************************************************************************
*  NvM_MultiBlockCbk
**********************************************************************************************************************/
/*!
 * \internal
 *  - #10 invoke the BSWM notification if any is configured
 *  - #20 in case the given job result isn't set to pending, invoke the multi block job end notification
 * \endinternal
 */
/* PRQA S 3206 1 */ /* MD_NvM_Cfg_2.7 */
FUNC(void, NVM_PRIVATE_CODE) NvM_MultiBlockCbk(NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult)
{
  /* The complete function body is designed to be optimized away by the compiler, if it is not needed    *
   * If the used macro is empty, the compiler may decide to remove code because it would contain         *
   * empty execution blocks (it does not matter whether conditions were TRUE or FALSE                    */
  NvM_invokeMultiBlockMode(ServiceId, JobResult);

  if(JobResult != NVM_REQ_PENDING)
  {
    NvM_invokeMultiCbk(ServiceId, JobResult);
  }   
}

/**********************************************************************************************************************
*  NvM_NotifyLossOfRedundancy
**********************************************************************************************************************/
/*!
 * \internal
 *  - invoke the notification callback if any is configured
 * \endinternal
 */
/* PRQA S 3206 1 */ /* MD_NvM_Cfg_2.7 */
FUNC(void, NVM_PRIVATE_CODE) NvM_NotifyLossOfRedundancy(NvM_BlockIdType BlockId)
{
  NvM_invokeDetectedLossOfRedundancyCallback(BlockId);
}

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/* PRQA L:MemMap */

/* Justification for module specific MISRA deviations:

MD_NvM_Cfg_2.4
Reason: NvM provides compile time block length checks via structures with bitfields with positive or negative length -
        the negative length lead to compiler errors. It is possible to use == or even >= check, if only one is used,
        the other one will never be used. The macros are always available. The created structures will never be used by NvM.
Risk: No risk.
Prevention: No prevention.

MD_NvM_Cfg_2.7:
Reason: The function NvM_MultiBlockCbk gets all needed parameters to invoke the BSWM and multi block job end callback.
        If both are disabled, the function is empty and does nothing - the passed parameters remain unused.
Risk: No risk.
Prevention: No prevention.

MD_NvM_Cfg_8.9_InternalBuffer:
Reason: NvM uses an internal buffer for explicit synchronization, in internal CRC buffer use case and for repair redundant blocks.
        Depending on configuration all, one or even none of the uses is enabled - therefore sometimes the internal buffer is
        used only once.
Risk: No risk.
Prevention: No prevention.

MD_NvM_Cfg_8.11:
Reason: Array of unknown size is used in order to reduce dependencies.
Risk: In case the array size shall be determined it would be incorrect.
Prevention: No prevention.

MD_NvM_Cfg_14.3:
Reason: NvM provides compile time block length checks via bitfields with positive or negative length - the negative length
        lead to compiler errors. With valid configuration (all block length are configured correctly), all checks are false.
Risk: No risk.
Prevention: No prevention. If needed the compile time checks can be disabled via configuration.

 */

/**********************************************************************************************************************
 *  END OF FILE: NvM_Cfg.c
 *********************************************************************************************************************/


