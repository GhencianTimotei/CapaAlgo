/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  NvM_IntTypes.h
 *        \brief  NvM internal types header file.
 *      \details  Holding the internal and external NvM types and value defines.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (NVM_INTTYPES_H_)
# define NVM_INTTYPES_H_

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* defines for internal flags */
# define NVM_INTFLAG_WAIT_SET           (0x01u)
# define NVM_INTFLAG_WAIT_CL            (0xFEu)
# define NVM_INTFLAG_ERROR_SET          (0x10u)
# define NVM_INTFLAG_ERROR_CL           (0xEFu)
# define NVM_INTFLAG_DYN_MISMATCH_SET   (0x20u)
# define NVM_INTFLAG_DYN_MISMATCH_CL    (0xDFu)
# define NVM_INTFLAG_ROM_RESTORED_SET   (0x40u)
# define NVM_INTFLAG_ROM_RESTORED_CL    (0xBFu)

/* defines for internal flags, controlled via API) */
# define NVM_APIFLAG_WRITE_ALL_SET               (0x02u)
# define NVM_APIFLAG_WRITE_ALL_CL                (0xFDu)
# define NVM_APIFLAG_READ_ALL_SET                (0x04u)
# define NVM_APIFLAG_READ_ALL_CL                 (0xFBu)
# define NVM_APIFLAG_REPAIR_REDUNDANT_BLOCKS_SET (0x08u)
# define NVM_APIFLAG_REPAIR_REDUNDANT_BLOCKS_CL  (0xF7u)
# define NVM_APIFLAG_CANCEL_WR_ALL_SET           (0x10u)
# define NVM_APIFLAG_CANCEL_WR_ALL_CL            (0xEFu)
# define NVM_APIFLAG_KILL_WR_ALL_SET             (0x20u)
# define NVM_APIFLAG_KILL_WR_ALL_CL              (0xDFu)
# define NVM_APIFLAG_KILL_READ_ALL_SET           (0x40u)
# define NVM_APIFLAG_KILL_READ_ALL_CL            (0xBFu)

/* defines for the block ram attribute states */
# define NVM_STATE_VALID_SET    (0x01u)
# define NVM_STATE_VALID_CL     (0xFEu)
# define NVM_STATE_CHANGED_SET  (0x02u)
# define NVM_STATE_CHANGED_CL   (0xFDu)

# define NVM_WR_PROT_SET        (0x80u)
# define NVM_WR_PROT_CL         (0x7Fu)
# define NVM_LOCK_STAT_SET      (0x40u)
# define NVM_LOCK_STAT_CL       (0xBFu)

/* defines the possible states of an NV Block, which can be determined.
 *  They are necessary for write processing of redundant NVRAM Blocks.          */
# define NVM_NVBLOCK_STATE_UPTODATE (0x00u)
# define NVM_NVBLOCK_STATE_OUTDATED (0x01u)
# define NVM_NVBLOCK_STATE_DEFECT   (0x02u)
# define NVM_NVBLOCK_STATE_UNKNOWN  (0x03u)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Pointer to a constant RAM buffer. */
typedef P2CONST(uint8, AUTOMATIC, NVM_APPL_DATA) NvM_ConstRamAddressType;

typedef struct
{
    uint8                   NvDataIndex_t; /*!< Current NvM block data index. Only relevant for dataset blocks. */
    NvM_RequestResultType   NvRamErrorStatus_u8; /*!< Current NvM block error status (PENDING or the result of the latest request). */
    uint8                   NvRamAttributes_u8; /*!< Current NvM block RAM state (valid, changed, protected, etc.) */
} NvM_RamMngmtAreaType; /*!< Structure holding all runtime NvM block management information. */

/*! Pointer to a RAM management area structure. */
typedef P2VAR(NvM_RamMngmtAreaType, AUTOMATIC, NVM_PRIVATE_DATA) NvM_RamMngmtPtrType;
/*! Constant pointer to a constant RAM management area structure (read only). */
typedef CONSTP2CONST(NvM_RamMngmtAreaType, AUTOMATIC, NVM_PRIVATE_DATA) NvM_RamMngmtConstPtrToConstType;

#endif /* NVM_INTTYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: NvM_IntTypes.h
 *********************************************************************************************************************/
