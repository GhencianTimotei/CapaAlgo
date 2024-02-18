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
/*! \ingroup    Dem_Master
 *  \defgroup   Dem_Nvm Nvm
 *  \{
 *  \file       Dem_Nvm_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Control modification state of NV blocks and background synchronization with NvM
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_NVM_INTERFACE_H)
#define DEM_NVM_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Nvm_Types.h"

#if (DEM_CFG_USE_NVM == STD_ON)
#include "NvM.h"
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Nvm_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Nvm_GetSingleBlockId
 *****************************************************************************/
/*!
 * \brief         Get the index of a memory block.
 *
 * \details       Get the index of a memory block (from which type only one
 *                block exists).
 *
 * \param[in]     BlockType
 *                Type of the memory block.
 *
 * \return        Block index of the given NvRAM block type.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Nvm_GetSingleBlockId(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Nvm_BlockType, AUTOMATIC)  BlockType
  );

/* ****************************************************************************
 % Dem_Nvm_SetAllBlocksDirty
 *****************************************************************************/
/*!
 * \brief         Sets the block state of all NV blocks 'Dirty'
 *
 * \details       Sets the block state of all NV blocks 'Dirty'
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetAllBlocksDirty(
  void
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_Nvm_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Nvm_SetSingleBlockState
 *****************************************************************************/
/*!
 * \brief         Set the status of a memory block.
 *
 * \details       Set the status of a memory block (from which type only one
 *                block exists).
 *
 * \param[in]     BlockIndex
 *                NvRAM block index.
 * \param[in]     Status
 *                New status of the memory block.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Nvm_SetSingleBlockState(
CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
CONST(uint8, AUTOMATIC)  Status
);

/* ****************************************************************************
 * Dem_Nvm_SetEventMemoryBlockState
 *****************************************************************************/
/*!
 * \brief         Set the status of an event memory block.
 *
 * \details       Set the status of an event memory block.
 *
 * \param[in]     BlockIndex
 *                NvRAM block index.
 * \param[in]     Status
 *                New status of the memory block.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Nvm_SetEventMemoryBlockState(
CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
CONST(uint8, AUTOMATIC)  Status
);

/* ****************************************************************************
 * Dem_Nvm_SetTimeSeriesMemoryBlockState
 *****************************************************************************/
/*!
 * \brief         Set the status of a time series memory block.
 *
 * \details       Set the status of a time series memory block.
 *
 * \param[in]     BlockIndex
 *                NvRAM block index.
 * \param[in]     Status
 *                New status of the memory block.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Nvm_SetTimeSeriesMemoryBlockState(
CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
CONST(uint8, AUTOMATIC)  Status
);

#if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_WRITELIMIT == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_TestAndSetBlockStateImmediate
 *****************************************************************************/
/*!
 * \brief         Evaluates, if immediate Nv-Updates are possible and sets the
 *                block state accordingly.
 *
 * \details       Evaluates, if immediate Nv-Updates are possible and sets the
 *                block state accordingly.
 *
 * \param[in]     BlockIndex
 *                NvRAM block index.
 * \param[in]     OldOccCounter
 *                Old occurrence counter.
 * \param[in]     NewOccCounter
 *                New occurrence counter.
 *
 * \pre           -
 * \config        DEM_CFG_USE_NVM == STD_ON &&
 *                DEM_CFG_SUPPORT_NVM_WRITELIMIT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_TestAndSetBlockStateImmediate(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex,
  CONST(uint16, AUTOMATIC)  OldOccCounter,
  CONST(uint16, AUTOMATIC)  NewOccCounter
  );
#endif

/* ****************************************************************************
 * Dem_Nvm_SetStatusBlockChanged
 *****************************************************************************/
/*!
 * \brief         Set event-status memory block to changed
 *
 * \details       Set event-status memory block to changed
 *
 * \pre           DEM_CFG_USE_NVM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetStatusBlockChanged(
  void
  );

#if (DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_IsCurrentlyWrittenBlockModified
 *****************************************************************************/
/*!
 * \brief         Tests if if the Dem is waiting for an NV write request
 *                and the NV same data block is also marked 'MODIFIED'
 *
 * \details       Tests if if the Dem is waiting for an NV write request
 *                and the NV same data block is also marked 'MODIFIED'
 *
 * \return        TRUE
 *                Dem is waiting for an NV write request and the same data
 *                block is marked 'MODIFIED'
 *                FALSE
 *                Dem is not waiting for an NV write request or written block
 *                is not marked 'MODIFIED'
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_NVM_IMMEDIATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Nvm_IsCurrentlyWrittenBlockModified(
  void
  );
#endif

#if ((DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_POLLING == STD_OFF))
/* ****************************************************************************
 * Dem_Nvm_ChangeNVWriteState
 *****************************************************************************/
/*!
 * \brief         Change the NV write state according to the NV job result
 *
 * \details       Change the NV write state according to the NV job result
 *
 * \param[in]     JobResult
 *                Result of the NV job
 *
 * \pre           -
 * \config        DEM_CFG_USE_NVM == STD_ON &&
 *                DEM_CFG_SUPPORT_NVM_POLLING == STD_OFF
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_ChangeNVWriteState(
  CONST(NvM_RequestResultType, AUTOMATIC)  JobResult
  );
#endif

/* ****************************************************************************
 * Dem_Nvm_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the NvM management
 *
 * \details       Initializes the NvM management
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_Init(
  void
  );

#if (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_Shutdown
 *****************************************************************************/
/*!
 * \brief         Finalize NvM block status
 *
 * \details       All pending Nv updates are reported as modified block for the
 *                NvM. (NvM_SetRamBlockStatus). The Dem assumes that all such
 *                marked blocks are persisted in NV-Ram using NvM_WriteAll
 *                following the Dem shutdown. This is not in scope of the Dem
 *                module however.
 *                If Dem_Shutdown is ever called without a following
 *                NvM_WriteAll, data will be lost.
 *
 * \pre           May be called only during module shutdown
 * \config        DEM_CFG_USE_NVM == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_Shutdown(
  void
  );
#endif

/* ****************************************************************************
 * Dem_Nvm_MainFunction
 *****************************************************************************/
/*!
 * \brief         Processes NvM synchronization
 *
 * \details       The function controls NvM commits. Modified blocks are passed
 *                to the NvM to write back, and once the write operation has
 *                finished the next modified block is processed.
 *                In case of polling, NvM job results are updated here as well.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_MainFunction(
  void
  );

# if (DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON) && (DEM_CFG_USE_NVM == STD_ON)
/* ****************************************************************************
 * Dem_Nvm_SetSynchronizationFlag
 *****************************************************************************/
/*!
 * \brief         Sets a flag for NvM synchronization
 *
 * \details       Sets a flag for NvM synchronization.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON &&
 *                DEM_CFG_USE_NVM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Nvm_SetSynchronizationFlag(
  void
  );
#endif /* (DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON) && (DEM_CFG_USE_NVM == STD_ON) */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_NVM_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Nvm_Interface.h
 *********************************************************************************************************************/
