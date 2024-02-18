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
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  PduR_Lock.c
 *      Project:  Gw_AsrPduRCfg5
 *       Module:  MICROSAR PDU Router
 *    Generator:  Configurator 5
 *
 *  Description:  Vector implementation of AUTOSAR PDU Router
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/


#define PDUR_LOCK_SOURCE
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "PduR.h"
#include "PduR_Lock.h"
#include "SchM_PduR.h"
#if (PDUR_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif
#if (PDUR_SPINLOCKRAM == STD_ON)
# include "Os.h"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#if !defined (PDUR_LOCAL_INLINE)
# define PDUR_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * PduR_Lock_Lock
 *********************************************************************************************************************/
/*! \brief      PduR Lock function.
 *  \details    -
 *  \param[in]  lockIdx  instance Idx.
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Lock_Lock(PduR_LockRomIterType lockIdx, PduR_MemIdxType memIdx);

/**********************************************************************************************************************
 * PduR_Lock_Unlock
 *********************************************************************************************************************/
/*! \brief      PduR Unlock function.
 *  \details    -
 *  \param[in]  lockIdx  instance Idx.
 *  \pre        -
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Lock_Unlock(PduR_LockRomIterType lockIdx, PduR_MemIdxType memIdx);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if (PDUR_SPINLOCKRAM == STD_ON)
/**********************************************************************************************************************
 * PduR_Lock_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Lock_Init(PduR_MemIdxType memIdx)
{
  PduR_SpinlockRamIterType spinlockRamIdx;
  uint32 spinLockInitValue = Appl_GetSpinlockInitVal();

  for(spinlockRamIdx = 0u; spinlockRamIdx < PduR_GetSizeOfSpinlockRam(memIdx); spinlockRamIdx++)
  {
    VStdLib_MemClr(PduR_GetAddrCounterOfSpinlockRam(spinlockRamIdx, memIdx), PDUR_MAX_NUMBER_OF_CORES); /* SBSW_PDUR_CSL01 */ /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */
    PduR_SetLockVariableOfSpinlockRam(spinlockRamIdx, spinLockInitValue, memIdx);       /* SBSW_PDUR_CSL01 */
  }
}
#endif
/**********************************************************************************************************************
 * PduR_Lock_Lock
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Lock_Lock(PduR_LockRomIterType lockIdx, PduR_MemIdxType memIdx)
{
#if (PDUR_SPINLOCKRAM == STD_ON)
  if(!PduR_IsExclusiveAreaRomUsedOfLockRom(lockIdx))
  {
    SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();
    {
      uint8 core_id = (uint8) GetCoreID();
      if(core_id < (uint8) PDUR_MAX_NUMBER_OF_CORES)
      {
        PduR_SpinlockRamIterType spinlockIdx = PduR_GetSpinlockRamIdxOfLockRom(lockIdx);
        if(0u == PduR_GetCounterOfSpinlockRam(spinlockIdx, memIdx)[core_id])
        {
          uint32 retryCounter = 0;
          uint32 retryCounterValue = PduR_GetSpinlockRetryCounterOfGeneralPropertiesRom(0);

          while((Appl_TryToGetSpinlock(PduR_GetAddrLockVariableOfSpinlockRam(spinlockIdx, memIdx)) != E_OK) && (retryCounter < retryCounterValue))  /* COV_PDUR_SPINLOCK_TIMEOUT */ /* SBSW_PDUR_CSL03 */
          {
            retryCounter++;
          }
          /* Report DET error if timeout elapsed */
          if(retryCounter >= retryCounterValue) /* COV_PDUR_SPINLOCK_TIMEOUT */
          {
            PduR_ReportRuntimeDetError(PDUR_LOCK_LOCK, PDUR_E_SPINLOCKTIMEOUT);
          }
        }
        PduR_GetCounterOfSpinlockRam(spinlockIdx, memIdx)[core_id]++;       /* SBSW_PDUR_CORE_ID_RTCHECK */
      }
      else
      {
        PduR_Det_ReportError(PDUR_LOCK_LOCK, PDUR_E_FATAL);
      }
    }
  }
  else
#endif
  {
    PduR_GetLockOfExclusiveAreaRom(PduR_GetExclusiveAreaRomIdxOfLockRom(lockIdx)) ();   /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
  }
  PDUR_DUMMY_STATEMENT(lockIdx);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(memIdx);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

/**********************************************************************************************************************
 * PduR_Lock_Unlock
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
PDUR_LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_Lock_Unlock(PduR_LockRomIterType lockIdx, PduR_MemIdxType memIdx)
{
#if (PDUR_SPINLOCKRAM == STD_ON)
  if(!PduR_IsExclusiveAreaRomUsedOfLockRom(lockIdx))
  {
    {
      uint8 core_id = (uint8) GetCoreID();
      if(core_id < (uint8) PDUR_MAX_NUMBER_OF_CORES)
      {
        PduR_SpinlockRamIterType spinlockIdx = PduR_GetSpinlockRamIdxOfLockRom(lockIdx);
        if(1u == PduR_GetCounterOfSpinlockRam(spinlockIdx, memIdx)[core_id])
        {
          if(E_OK != Appl_ReleaseSpinlock(PduR_GetAddrLockVariableOfSpinlockRam(spinlockIdx, memIdx)))     /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */ /* COV_PDUR_FATAL_ERROR */
          {
            PduR_Det_ReportError(PDUR_LOCK_UNLOCK, PDUR_E_FATAL);
          }
        }
        PduR_GetCounterOfSpinlockRam(spinlockIdx, memIdx)[core_id]--;       /* SBSW_PDUR_CORE_ID_RTCHECK */
      }
      else
      {
        PduR_Det_ReportError(PDUR_LOCK_UNLOCK, PDUR_E_FATAL);
      }
    }
    SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();
  }
  else
#endif
  {
    PduR_GetUnlockOfExclusiveAreaRom(PduR_GetExclusiveAreaRomIdxOfLockRom(lockIdx)) (); /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
  }
  PDUR_DUMMY_STATEMENT(lockIdx);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(memIdx);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * PduR_Lock_LockRoutingPathBySrcPdu
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Lock_LockRoutingPathBySrcPdu(PduR_RmSrcRomIterType rmSrcIdx) /* COV_PDUR_WRAPPER_FUNC */
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);

  PduR_Lock_Lock(PduR_GetLockRomIdxOfRmSrcRom(rmSrcIdx), memIdx);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

/**********************************************************************************************************************
 * PduR_Lock_UnlockRoutingPathBySrcPdu
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Lock_UnlockRoutingPathBySrcPdu(PduR_RmSrcRomIterType rmSrcIdx)       /* COV_PDUR_WRAPPER_FUNC */
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmSrcRom(rmSrcIdx);

  PduR_Lock_Unlock(PduR_GetLockRomIdxOfRmSrcRom(rmSrcIdx), memIdx);
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

/**********************************************************************************************************************
 * PduR_Lock_LockRoutingPathByDestPdu
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Lock_LockRoutingPathByDestPdu(PduR_RmDestRomIterType rmDestIdx)      /* COV_PDUR_WRAPPER_FUNC */
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmDestRom(rmDestIdx);

  PduR_Lock_Lock(PduR_GetLockRomIdxOfRmGDestRom(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx)), memIdx);
  PDUR_DUMMY_STATEMENT(rmDestIdx);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

/**********************************************************************************************************************
 * PduR_Lock_UnlockRoutingPathByDestPdu
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Lock_UnlockRoutingPathByDestPdu(PduR_RmDestRomIterType rmDestIdx)    /* COV_PDUR_WRAPPER_FUNC */
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmDestRom(rmDestIdx);

  PduR_Lock_Unlock(PduR_GetLockRomIdxOfRmGDestRom(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx)), memIdx);
  PDUR_DUMMY_STATEMENT(rmDestIdx);      /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

/**********************************************************************************************************************
 * PduR_Lock_LockRoutingPathByGDestPdu
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Lock_LockRoutingPathByGDestPdu(PduR_RmGDestRomIterType rmGDestIdx)   /* COV_PDUR_WRAPPER_FUNC */
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestIdx);

  PduR_Lock_Lock(PduR_GetLockRomIdxOfRmGDestRom(rmGDestIdx), memIdx);
  PDUR_DUMMY_STATEMENT(rmGDestIdx);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

/**********************************************************************************************************************
 * PduR_Lock_UnlockRoutingPathByGDestPdu
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Lock_UnlockRoutingPathByGDestPdu(PduR_RmGDestRomIterType rmGDestIdx) /* COV_PDUR_WRAPPER_FUNC */
{
  PduR_MemIdxType memIdx = PduR_GetPartitionIndexOfCslOfRmGDestRom(rmGDestIdx);

  PduR_Lock_Unlock(PduR_GetLockRomIdxOfRmGDestRom(rmGDestIdx), memIdx);
  PDUR_DUMMY_STATEMENT(rmGDestIdx);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}

#if (PDUR_LOCKROMUSEDOFFMFIFOROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Lock_LockBuffersByFmFifo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Lock_LockBuffersByFmFifo(PduR_FmFifoRomIterType fmFifoRomIdx, PduR_MemIdxType memIdx)
{
  if(PduR_IsLockRomUsedOfFmFifoRom(fmFifoRomIdx, memIdx))
  {
    PduR_Lock_Lock(PduR_GetLockRomIdxOfFmFifoRom(fmFifoRomIdx, memIdx), memIdx);
  }
  PDUR_DUMMY_STATEMENT(fmFifoRomIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#if (PDUR_LOCKROMUSEDOFFMFIFOROM == STD_ON)
/**********************************************************************************************************************
 * PduR_Lock_UnlockBuffersByFmFifo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Lock_UnlockBuffersByFmFifo(PduR_FmFifoRomIterType fmFifoRomIdx, PduR_MemIdxType memIdx)
{
  if(PduR_IsLockRomUsedOfFmFifoRom(fmFifoRomIdx, memIdx))
  {
    PduR_Lock_Unlock(PduR_GetLockRomIdxOfFmFifoRom(fmFifoRomIdx, memIdx), memIdx);
  }
  PDUR_DUMMY_STATEMENT(fmFifoRomIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}
#endif

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: PduR_Lock.c
 *********************************************************************************************************************/
