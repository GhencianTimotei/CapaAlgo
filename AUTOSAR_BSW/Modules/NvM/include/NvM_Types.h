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
/*!        \file  NvM_Types.h
 *        \brief  NvM public types header file.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if (!defined NVM_TYPES_H_)
#define NVM_TYPES_H_

/***********************************************************************************************************************
 * INCLUDES
 **********************************************************************************************************************/
#include "Std_Types.h"
#include "Rte_NvM_Type.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS AND TYPES
 *********************************************************************************************************************/
/* Result types and values of asynchronous requests are also defined by the RTE, since these are the important values
 * for an SW-C. Do not overwrite them, if already defined! */

#ifndef Rte_TypeDef_NvM_RequestResultType
typedef uint8 NvM_RequestResultType; /*!< Type used to store a job result. Published via GetErrorStatus API. */
#endif

#ifndef Rte_TypeDef_NvM_BlockIdType
typedef uint16 NvM_BlockIdType; /*!< Type used to store a block identifier. User as parameter for public APIs. */
#endif

#ifndef NVM_REQ_OK
# define NVM_REQ_OK               (0u)  /*!< The last asynchronous request has been finished successfully. */
#endif
#ifndef NVM_REQ_NOT_OK
# define NVM_REQ_NOT_OK           (1u)  /*!< The last asynchronous request has been finished unsuccessfully. */
#endif
#ifndef NVM_REQ_PENDING
# define NVM_REQ_PENDING          (2u)  /*!< An asynchronous request is currently being processed. */
#endif
#ifndef NVM_REQ_INTEGRITY_FAILED
# define NVM_REQ_INTEGRITY_FAILED (3u)  /*!< Result of the last NvM_ReadBlock or NvM_ReadAll is an integrity failure. */
#endif
#ifndef NVM_REQ_BLOCK_SKIPPED
# define NVM_REQ_BLOCK_SKIPPED    (4u)  /*!< The referenced block was skipped during a multi block request. */
#endif
#ifndef NVM_REQ_NV_INVALIDATED
# define NVM_REQ_NV_INVALIDATED   (5u)  /*!< The NV block is invalidated. */
#endif
#ifndef NVM_REQ_CANCELED
# define NVM_REQ_CANCELED        (6u)  /*!< A WriteAll was cancelled. */
#endif
#ifndef NVM_REQ_REDUNDANCY_FAILED
# define NVM_REQ_REDUNDANCY_FAILED  (7u) /*!< A redundant block lost its redundancy. */
#endif
#ifndef NVM_REQ_RESTORED_FROM_ROM
# define NVM_REQ_RESTORED_FROM_ROM  (8u) /*!< Default data from ROM are restored. */
#endif

#ifndef Rte_TypeDef_NvM_ServiceIdType
typedef uint8 NvM_ServiceIdType;   /*!< Type used to store a service identifier. */
#endif

/* These Service Ids are important to an SW-C, as they can be passed to it in the "single block job end notification"
 *  callback. Therefore they are also defined by the RTE. */

#ifndef NVM_READ_BLOCK
# define NVM_READ_BLOCK             (6u) /*!< Service ID NvM_ReadBlock(). */
#endif
#ifndef NVM_WRITE_BLOCK
# define NVM_WRITE_BLOCK            (7u) /*!< Service ID NvM_WriteBlock(). */
#endif
#ifndef NVM_RESTORE_BLOCK_DEFAULTS
# define NVM_RESTORE_BLOCK_DEFAULTS (8u) /*!< Service ID NvM_RestoreBlockDefaults(). */
#endif
#ifndef NVM_ERASE_BLOCK
# define NVM_ERASE_BLOCK            (9u) /*!< Service ID NvM_EraseNvBlock(). */
#endif
#ifndef NVM_INVALIDATE_NV_BLOCK
# define NVM_INVALIDATE_NV_BLOCK   (11u) /*!< Service ID NvM_InvalidateNvBlock(). */
#endif
#ifndef NVM_READ_ALL
# define NVM_READ_ALL              (12u) /*!< Service ID NvM_ReadAll(). */
#endif

/* These Service Ids will not be published via callbacks etc. (job end callbacks won't be called during WriteAll, etc.),
 * they shall never be defined by the RTE. However, it doesn't hurt to protect them ... */

#ifndef NVM_INIT
# define NVM_INIT                   (0u) /*!< Service ID NvM_Init(). */
#endif
#ifndef NVM_SET_DATA_INDEX
# define NVM_SET_DATA_INDEX         (1u) /*!< Service ID NvM_SetDataIndex(). */
#endif
#ifndef NVM_GET_DATA_INDEX
# define NVM_GET_DATA_INDEX         (2u) /*!< Service ID NvM_GetDataIndex(). */
#endif
#ifndef NVM_SET_BLOCK_PROTECTION
# define NVM_SET_BLOCK_PROTECTION   (3u) /*!< Service ID NvM_SetBlockProtection(). */
#endif
#ifndef NVM_GET_ERROR_STATUS
# define NVM_GET_ERROR_STATUS       (4u) /*!< Service ID NvM_GetErrorStatus(). */
#endif
#ifndef NVM_SET_RAM_BLOCK_STATUS
# define NVM_SET_RAM_BLOCK_STATUS   (5u) /*!< Service ID NvM_SetRamBlockStatus(). */
#endif

#ifndef NVM_CANCEL_WRITE_ALL
# define NVM_CANCEL_WRITE_ALL      (10u) /*!< Service ID NvM_CancelRequest(). */
#endif

#ifndef NVM_WRITE_ALL
# define NVM_WRITE_ALL             (13u) /*!< Service ID NvM_WriteAll(). */
#endif
#ifndef NVM_MAINFUNCTION
# define NVM_MAINFUNCTION          (14u) /*!< Service ID NvM_MainFunction(). */
#endif
#ifndef NVM_GET_VERSION_INFO
# define NVM_GET_VERSION_INFO      (15u) /*!< Service ID NvM_GetVersionInfo(). */
#endif

#ifndef NVM_CANCEL_JOBS
# define NVM_CANCEL_JOBS           (16u) /*!< Service ID NvM_CancelJobs(). */
#endif
#ifndef NVM_SET_BLOCK_LOCK_STATUS
# define NVM_SET_BLOCK_LOCK_STATUS (19u) /*!< Service ID NvM_SetBlockProtection(). */
#endif
#ifndef NVM_KILL_WRITE_ALL
# define NVM_KILL_WRITE_ALL        (20u) /*!< Service ID NvM_KillWriteAll(). */
#endif

#ifndef NVM_REPAIR_REDUNDANT_BLOCKS
# define NVM_REPAIR_REDUNDANT_BLOCKS (21u) /*!< Service ID NvM_RepairRedundantBlocks(). */
#endif

#ifndef NVM_KILL_READ_ALL
# define NVM_KILL_READ_ALL           (22u) /*!< Service ID NvM_KillReadAll(). */
#endif

#endif /* NVM_TYPES_H_ */

/**********************************************************************************************************************
 *  END OF FILE: NvM_Types.h
 *********************************************************************************************************************/
