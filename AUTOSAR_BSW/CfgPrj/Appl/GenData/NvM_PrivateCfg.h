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
 *              File: NvM_PrivateCfg.h
 *   Generation Time: 2022-05-18 16:27:19
 *           Project: DaVinciConfigurationS32K144 - Version 1.0
 *          Delivery: CBD2100188_D01
 *      Tool Version: DaVinci Configurator  5.23.45 SP4
 *
 *
 *********************************************************************************************************************/


/* PRQA S 5087 MemMap */ /* MD_MSR_MemMap */

/* Do not modify the following parts. */
/* Modification is only allowed in the described parts */

/* ---- private section of configuration ---------------------------------- */
/* ---- used as interface to all submodules of the NvM -------------------- */

/**********************************************************************************************************************
 * PROTECTION AGAINST MULTIPLE INCLUSION
 *********************************************************************************************************************/
#if (!defined NVM_CFG_H_PRIVATE)
# define NVM_CFG_H_PRIVATE

/**********************************************************************************************************************
 *  CONFIGURATION TYPES, VARIABLES, DEFINES...
 *********************************************************************************************************************/


/* production error configuration */


#define NvM_DemReportErrorReqFailed()         
#define NvM_DemReportErrorIntegrityFailed()   
#define NvM_DemReportErrorLossOfRedundancy()  
#define NvM_DemReportErrorQueueOverflow()     
#define NvM_DemReportErrorWriteProtected()    


/* macro to mask out the DCM_BLOCK info bit (block aliasing) to obtain original BlockId */
# define NVM_BLOCK_FROM_DCM_ID(blockId)   ((NvM_BlockIdType)((blockId) & ((NVM_DCM_BLOCK_OFFSET) ^ 0xFFFFu))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#if (!defined NVM_CFG_SOURCE)
/* in NvM_Cfg.c we don't need the following definitions and includes */

/* Configurations for Development mode */

/* Report development errors */
# define NVM_DEV_ERROR_REPORT (STD_OFF)

# if (NVM_DEV_ERROR_REPORT == STD_ON)
/* Include-File, which contains Errorhook-Function */
#  include "Det.h"

/* DET Errorhook 
 * macro will only be needed, if reporting is enabled */
#  define NvM_Errorhook(ServiceId, ErrorCode) ((void)Det_ReportError((NVM_MODULE_ID), (0u), (ServiceId), (ErrorCode))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

# endif /* (NVM_DEV_ERROR_REPORT == STD_ON) */
#endif /* NVM_CFG_SOURCE */

/* includes, we only need internally */
/* ---- Include of the interface of the MemIf module ---------------------- */
#include "MemIf.h"

typedef unsigned int NvM_BitFieldType;

typedef struct
{
    NvM_BitFieldType CalcRamBlockCrcEnabled : 1;
    NvM_BitFieldType BlockWriteProtEnabled : 1;
    NvM_BitFieldType BlockWriteBlockOnceEnabled : 1;
    NvM_BitFieldType ResistantToChangedSwEnabled : 1;
    NvM_BitFieldType SelectBlockForReadAllEnabled : 1;
    NvM_BitFieldType SelectBlockForWriteAllEnabled : 1;
    NvM_BitFieldType InvokeCallbacksForReadAllEnabled : 1;
    NvM_BitFieldType InvokeCallbacksForWriteAllEnabled : 1;
    NvM_BitFieldType BlockUseSetRamBlockStatusEnabled : 1;
    NvM_BitFieldType BlockCheckLossOfRedundancyEnabled : 1;
    NvM_BitFieldType NotifyBswM : 1;
} NvM_BlockDescriptorFlagsType /*!< Type, which contains all flags a configured block can have */;

/* CRC type. Kept as a bitfield to reduce storage size. */
typedef NvM_BitFieldType NvM_CrcType; 

/* Block Management Types */
#define NVM_BLOCK_NATIVE        0x00u
#define NVM_BLOCK_REDUNDANT     0x01u
#define NVM_BLOCK_DATASET       0x02u

/* type of a callback function for the asynchronous job end callbacks (standard) */
typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvM_JobEndCbkPtrType) (NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);

/* type of a callback function for the asynchronous job end callbacks with extended information */
typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvM_JobEndCbkExtPtrType) (NvM_BlockIdType BlockId, NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);

/* type of a block init callback function pointer
 * type changed thanks to Bugzilla 11982; we use return type void,
 * because since the original return value is useless to us           */
typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvM_InitCbkPtrType)(void);

/* type of a block init callback function pointer with  */
typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvM_InitCbkExtPtrType)(NvM_BlockIdType BlockId, P2VAR(void, AUTOMATIC, NVM_APPL_DATA) BufferPtr, uint16 Length);

/* types of the synchronisation mechanism callback function pointer */
typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvM_WriteRamToNvMCbkPtrType)(P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvMBuffer);
typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvM_ReadRamFromNvMCbkPtrType)(P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvMBuffer);

/* pre write and post read transformation callback function pointer types */
typedef P2FUNC(void, NVM_APPL_CODE, NvM_PreWriteTransformCbkPtrType)(NvM_BlockIdType BlockId, P2VAR(void, AUTOMATIC, NVM_APPL_DATA) BufferPtr, uint16 Length);
typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvM_PostReadTransformCbkPtrType)(NvM_BlockIdType BlockId, P2VAR(void, AUTOMATIC, NVM_APPL_DATA) BufferPtr, uint16 Length);

/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
#define NvM_invokeCurrentBlockMode(id, res)  /*  if any block has NotifyBswM == TRUE  */ 

/* pointer type referencing a block of Application's RAM/ROM/CRC data,
 * the pointer itself doesn't have any memmclass assigned, at this point
 */
typedef P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) NvM_RamAddressType;

typedef P2CONST(uint8, AUTOMATIC, NVM_APPL_CONST) NvM_RomAddressType;

/* switch the Calc RAM Crc functionality on or off */
#define NVM_CALC_RAM_CRC_USED STD_OFF 


typedef P2VAR(uint8, AUTOMATIC, NVM_PRIVATE_DATA) NvM_RamCrcAddressType;

/* Block's Flag bit mask, used in the block descriptor element "Flags".
 * Note: CRC_8 not used (not supported) but define kept for completeness. */
#define NVM_BLOCK_USE_CRC_OFF                    (0u)
#define NVM_BLOCK_CRC_8_ON                       (1u)
#define NVM_BLOCK_CRC_16_ON                      (2u)
#define NVM_BLOCK_CRC_32_ON                      (3u)

#define NVM_CALC_RAM_BLOCK_CRC_ON                (1u)
#define NVM_CALC_RAM_BLOCK_CRC_OFF               (0u)
#define NVM_BLOCK_WRITE_PROT_ON                  (1u)
#define NVM_BLOCK_WRITE_PROT_OFF                 (0u)
#define NVM_BLOCK_WRITE_BLOCK_ONCE_ON            (1u)
#define NVM_BLOCK_WRITE_BLOCK_ONCE_OFF           (0u)
#define NVM_RESISTANT_TO_CHANGED_SW_ON           (1u)
#define NVM_RESISTANT_TO_CHANGED_SW_OFF          (0u)
#define NVM_SELECT_BLOCK_FOR_READALL_ON          (1u)
#define NVM_SELECT_BLOCK_FOR_READALL_OFF         (0u)
#define NVM_SELECT_BLOCK_FOR_WRITEALL_ON         (1u)
#define NVM_SELECT_BLOCK_FOR_WRITEALL_OFF        (0u)
#define NVM_INVOKE_CALLBACKS_FOR_READALL_ON      (1u)
#define NVM_INVOKE_CALLBACKS_FOR_READALL_OFF     (0u)
#define NVM_INVOKE_CALLBACKS_FOR_WRITEALL_ON     (1u)
#define NVM_INVOKE_CALLBACKS_FOR_WRITEALL_OFF    (0u)
#define NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_ON    (1u)
#define NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS_OFF   (0u)
#define NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_ON    (1u)
#define NVM_BLOCK_CHECK_LOSS_OF_REDUNDANCY_OFF   (0u)
#define NVM_BLOCK_NOTIFY_BSWM_ON                 (1u)
#define NVM_BLOCK_NOTIFY_BSWM_OFF                (0u)

/* NvRam block descriptor type */
typedef struct
{
    NvM_RamAddressType              RamBlockDataAddr_t;
    NvM_RomAddressType              RomBlockDataAddr_pt;
    NvM_InitCbkPtrType              InitCbkFunc_pt;
    NvM_InitCbkExtPtrType           InitCbkExtFunc_pt;
    NvM_JobEndCbkPtrType            JobEndCbkFunc_pt;
    NvM_JobEndCbkExtPtrType         JobEndCbkExtFunc_pt;
    NvM_ReadRamFromNvMCbkPtrType    CbkGetMirrorFunc_pt;
    NvM_WriteRamToNvMCbkPtrType     CbkSetMirrorFunc_pt;
    NvM_PreWriteTransformCbkPtrType CbkPreWriteTransform;
    NvM_PostReadTransformCbkPtrType CbkPostReadTransform;
#if (NVM_CRC_INT_BUFFER == STD_ON)
    NvM_RamCrcAddressType           RamBlockCrcAddr_t;            /* CRC for consistency checks */
#endif
    NvM_RamCrcAddressType           CRCCompMechanismCrcAddr_t;    /* CRC for write avoiding mechanism */
    NvM_BlockDescriptorFlagsType    Flags;
    uint16                          NvIdentifier_u16;
    uint16                          NvBlockLength_u16;
    uint16                          NvBlockNVRAMDataLength;
    uint8                           NvCryptoReference;
    uint8                           NvBlockCount_u8;
    uint8                           BlockPrio_u8;
    NvM_BitFieldType                DeviceId_u8     :4;
    NvM_BitFieldType                MngmtType_t     :2;
    NvM_CrcType                     CrcSettings     :2;
} NvM_BlockDescriptorType;

/* CSM related part: include, defines (configuration dependent) and types. */

#define NVM_USE_CSM        STD_OFF 
#define NVM_NR_OF_CSM_JOBS 0u 


typedef uint32 NvM_CsmJobIdType; /*!< Type of the CSM job identifier. */

typedef struct
{
  NvM_CsmJobIdType EncryptJobId; /*!< Encryption job identfier forwarded to the CSM. */
  NvM_CsmJobIdType DecryptJobId; /*!< Decryption job identfier forwarded to the CSM. */
} NvM_CsmJobType; /*!< Type to store all relevant values of a NvM CSM reference. */

/* pointer type to the BlockDescriptor Table or one of its entries, with the correct distance */
typedef P2CONST(NvM_BlockDescriptorType, AUTOMATIC, NVM_CONFIG_CONST) NvM_BlockDescrPtrType;

/* Internal Service Ids of the different services of the NVM */
typedef enum
{
    NVM_INT_FID_WRITE_BLOCK = 0u,
    NVM_INT_FID_READ_BLOCK,
    NVM_INT_FID_RESTORE_DEFAULTS,
    NVM_INT_FID_INVALIDATE_NV_BLOCK,
    NVM_INT_FID_ERASE_BLOCK,
    NVM_INT_FID_WRITE_ALL,
    NVM_INT_FID_READ_ALL,
    NVM_INT_FID_REPAIR_REDUNDANT_BLOCKS,
    NVM_INT_FID_NO_JOB_PENDING /* additionally denotes idle state oif NVM */
} NvM_InternalServiceIdType;

/* reference (pointer) to a queue element, actually it is just an index */
typedef uint8 NvM_QueueEntryRefType;

/* type of a queue element */
typedef struct
{
    NvM_RamAddressType          RamAddr_t;
    NvM_BlockIdType             BlockId;
    NvM_InternalServiceIdType   ServiceId;
    NvM_QueueEntryRefType       NextEntry;
    NvM_QueueEntryRefType       PrevEntry;
#if (NVM_JOB_PRIORISATION == STD_ON)
    uint8                       JobPrio;
#endif
} NvM_QueueEntryType;

#define NVM_SIZE_STANDARD_JOB_QUEUE  (8u) 
#define NVM_SIZE_IMMEDIATE_JOB_QUEUE (0u) 


#define NVM_USE_BLOCK_ID_CHECK STD_OFF 


#define NVM_START_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 * NvM_EnterCriticalSection
 *********************************************************************************************************************/
/*! \brief Invoke the SchM API to enter NvM's critical section.
 *  \details Invoke the SchM API to enter NvM's critical section.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
extern FUNC(void, NVM_PRIVATE_CODE) NvM_EnterCriticalSection(void);

/**********************************************************************************************************************
 * NvM_ExitCriticalSection
 *********************************************************************************************************************/
/*! \brief Invoke the SchM API to exit NvM's critical section.
 *  \details Invoke the SchM API to exit NvM's critical section.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
extern FUNC(void, NVM_PRIVATE_CODE) NvM_ExitCriticalSection(void);

/**********************************************************************************************************************
 * NvM_MultiBlockCbk
 *********************************************************************************************************************/
/*! \brief Invokes multi block job end and BSWM notifications, if there are any.
 *  \details Invokes multi block job end and BSWM notifications, if there are any.
 *  \param[in] ServiceId as a request type. Caller has to ensure validity.
 *  \param[in] JobResult as the current job result of the block with BlockId. Must be in range [0,8]. Caller has to ensure validity.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
extern FUNC(void, NVM_PRIVATE_CODE) NvM_MultiBlockCbk(NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult);

/**********************************************************************************************************************
 *  NvM_NotifyLossOfRedundancy
 *********************************************************************************************************************/
/*!
 * \brief           Invokes configured callback for a detected loss of redundancy.
 * \details         If no callback is configured, this function will do nothing and in best case gets optimized out of
 *                  the binary from the compiler.
 * \param[in]       BlockId   Id of the block that lost its redundancy
 * \pre             -
 * \context         TASK
 * \reentrant       FALSE
 * \synchronous     TRUE
 */
extern FUNC(void, NVM_PRIVATE_CODE) NvM_NotifyLossOfRedundancy(NvM_BlockIdType BlockId);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#define NVM_START_SEC_VAR_NO_INIT_8
#include "MemMap.h"

#if ((NVM_CRC_INT_BUFFER == STD_ON) || (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON))
/* create the internal buffer */
extern VAR(uint8, NVM_PRIVATE_DATA) NvM_InternalBuffer_au8[]; /* PRQA S 3684 */ /* MD_NvM_Cfg_8.11 */
#endif



#define NVM_STOP_SEC_VAR_NO_INIT_8
#include "MemMap.h"

#if(NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
# define NVM_START_SEC_VAR_NO_INIT_UNSPECIFIED
# include "MemMap.h"

/* Job Queue used for normal and high prio jobs */
extern VAR(NvM_QueueEntryType, NVM_PRIVATE_DATA) NvM_JobQueue_at[]; /* PRQA S 3684 */ /* MD_NvM_Cfg_8.11 */

# define NVM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
# include "MemMap.h"
#endif

#define NVM_NOOFWRITEATTEMPTS 1u

#define NVM_START_SEC_CONST_16
#include "MemMap.h"

/* number of crc bytes per call of NvM_MainFunction() */
extern CONST(uint16, NVM_CONFIG_CONST) NvM_NoOfCrcBytes_u16;

/* constant holding Crc quueue size value */
extern CONST(uint16, NVM_PRIVATE_CONST) NvM_CrcQueueSize_u16;
    
#define NVM_STOP_SEC_CONST_16
#include "MemMap.h"

/**********************************************************************************************************************
 * CRC CONFIGURATION
 *********************************************************************************************************************/
#include "Crc.h" /* always needed, since the config Block has a CRC */
#define NVM_USE_CRC16 STD_OFF 
#define NVM_USE_CRC32 STD_ON 


/**********************************************************************************************************************
 * ALL BLOCK RELATED SETTINGS
 *********************************************************************************************************************/

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


extern CONST(NvM_BlockDescriptorType, NVM_CONFIG_CONST) NvM_BlockDescriptorTable_at[]; /* PRQA S 3684 */ /* MD_NvM_Cfg_8.11 */

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* ---- end private configuration section --------------------------------- */
#endif /* NVM_CFG_PRIVATE */

/* PRQA L:MemMap */

/**********************************************************************************************************************
 *  END OF FILE: NvM_PrivateCfg.h
 *********************************************************************************************************************/
    
