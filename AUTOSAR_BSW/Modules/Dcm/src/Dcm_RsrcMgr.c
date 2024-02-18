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
/**        \file  Dcm_RsrcMgr.c
 *        \brief  Contains the implementation of RsrcMgr unit.
 *
 *      \details  MICROSAR DCM based on AR 4.0.3
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
#define DCM_RSRCMGR_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Dcm_RsrcMgr.h"
#include "Dcm_Debug.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Lock information of the resource manager */
struct DCM_RSRCMGRDIDLOCKTYPE_TAG
{
  uint16                       Did;    /*!< Identifier value of a resource */
  Dcm_RsrcMgrDidLockOwnerType  Owner;  /*!< Lock owner */
};
typedef struct DCM_RSRCMGRDIDLOCKTYPE_TAG Dcm_RsrcMgrDidLockType;

/*! Lock information of the resource manager */
struct DCM_RSRCMGRMEMLOCKTYPE_TAG
{
  Dcm_RsrcMgrMemLockOwnerType  Owner;  /*!< Lock owner */
};
typedef struct DCM_RSRCMGRMEMLOCKTYPE_TAG Dcm_RsrcMgrMemLockType;

/*! Context information of the resource manager */
struct DCM_RSRCMGRSINGLETONCONTEXTTYPE_TAG
{
  Dcm_RsrcMgrDidLockType  DidLockList[DCM_RSRCMGR_DID_LOCK_LIST_SIZE];  /*!< List of Dids which can be handled in parallel */
  Dcm_RsrcMgrMemLockType  MemLock;                                      /*!< Lock for the memory resource */
};
typedef struct DCM_RSRCMGRSINGLETONCONTEXTTYPE_TAG Dcm_RsrcMgrSingletonContextType;

/**********************************************************************************************************************
 *  LOCAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_RsrcMgrIsMemLockFree()
 *********************************************************************************************************************/
/*! \brief          Checks whether the memory resource can be locked or not.
 *  \details        -
 *  \return         TRUE     Memory resource is free
 *  \return         FALSE    Memory resource is locked
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(boolean, DCM_CODE) Dcm_RsrcMgrIsMemLockFree(
  void
  );
#define DCM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL DATA DECLARATIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! Singleton context of RsrcMgr unit */
DCM_LOCAL VAR(Dcm_RsrcMgrSingletonContextType, DCM_VAR_NOINIT) Dcm_RsrcMgrSingletonContext;
#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_RsrcMgrIsMemLockFree()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DCM_LOCAL_INLINE FUNC(boolean, DCM_CODE) Dcm_RsrcMgrIsMemLockFree(
  void
  )
{
  return Dcm_RsrcMgrHasMemLock(DCM_RSRCMGR_MEM_ACCESS_NONE);
}
#define DCM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_RsrcMgrInit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, DCM_CODE) Dcm_RsrcMgrInit(
  void
  )
{
  uint8_least lIter;

  for(lIter = 0; lIter < DCM_RSRCMGR_DID_LOCK_LIST_SIZE; ++lIter)
  {
    Dcm_RsrcMgrSingletonContext.DidLockList[lIter].Did = 0u;                                                                                         /* SBSW_DCM_POINTER_WRITE_DIDLOCKLIST */
    Dcm_RsrcMgrSingletonContext.DidLockList[lIter].Owner = DCM_RSRCMGR_DIDLOCK_OWNER_NONE;                                                           /* SBSW_DCM_POINTER_WRITE_DIDLOCKLIST */
  }

  Dcm_RsrcMgrSingletonContext.MemLock.Owner = DCM_RSRCMGR_MEM_ACCESS_NONE;
}

/**********************************************************************************************************************
 *  Dcm_RsrcMgrHasMemLock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(boolean, DCM_CODE) Dcm_RsrcMgrHasMemLock(
  Dcm_RsrcMgrMemLockOwnerType owner
  )
{
  boolean lResult = FALSE;

  if (Dcm_RsrcMgrSingletonContext.MemLock.Owner == owner)
  {
    lResult = TRUE;
  }

  return lResult;
}

/**********************************************************************************************************************
 *  Dcm_RsrcMgrGetMemLock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_RsrcMgrGetMemLock(
  Dcm_OpStatusType opStatus,
  Dcm_RsrcMgrMemLockOwnerType owner
  )
{
  Std_ReturnType lStdResult = DCM_E_PENDING;

  if(opStatus == DCM_CANCEL)
  {
    lStdResult = DCM_E_NOT_OK;
  }
  else
  {
    if(Dcm_RsrcMgrIsMemLockFree() == TRUE)
    {
      Dcm_RsrcMgrSingletonContext.MemLock.Owner = owner;
      lStdResult = DCM_E_OK;
    }
  }

  return lStdResult;
}

/**********************************************************************************************************************
 *  Dcm_RsrcMgrReleaseMemLock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, DCM_CODE) Dcm_RsrcMgrReleaseMemLock(
  void
  )
{
  Dcm_RsrcMgrSingletonContext.MemLock.Owner = DCM_RSRCMGR_MEM_ACCESS_NONE;
}

/**********************************************************************************************************************
 *  Dcm_RsrcMgrHasDidLock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(boolean, DCM_CODE) Dcm_RsrcMgrHasDidLock(
  Dcm_RsrcMgrDidLockOwnerType owner
  )
{
  boolean     lResult = FALSE;
  uint8_least lIter;

  for(lIter = 0; lIter < DCM_RSRCMGR_DID_LOCK_LIST_SIZE; ++lIter)
  {
    if(Dcm_RsrcMgrSingletonContext.DidLockList[lIter].Owner == owner)
    {
      lResult = TRUE;
      break;
    }
  }

  return lResult;
}

/**********************************************************************************************************************
 *  Dcm_RsrcMgrIsDidFree()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(boolean, DCM_CODE) Dcm_RsrcMgrIsDidFree(
  uint16 did
  )
{
  boolean      lResult = TRUE;
  uint8_least  lIter;

  for(lIter = 0; lIter < DCM_RSRCMGR_DID_LOCK_LIST_SIZE; ++lIter)
  {
    if(Dcm_RsrcMgrSingletonContext.DidLockList[lIter].Did == did)
    {
      lResult = FALSE;
      break;
    }
  }

  return lResult;
}

/**********************************************************************************************************************
 *  Dcm_RsrcMgrGetDidLock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_RsrcMgrGetDidLock(
  Dcm_OpStatusType opStatus,
  uint16 did,
  Dcm_RsrcMgrDidLockOwnerType owner
  )
{
  Std_ReturnType lStdResult = DCM_E_PENDING;
  uint8_least    lIter;

  Dcm_DebugAssert((Dcm_RsrcMgrHasDidLock(owner) == FALSE), DCM_SID_INTERNAL, DCM_E_ILLEGAL_STATE);                                                   /* COV_DCM_RTM_DEV_DEBUG XF */

  if(opStatus == DCM_CANCEL)
  {
    lStdResult = DCM_E_NOT_OK;
  }
  else
  {
    if(Dcm_RsrcMgrIsDidFree(did) == TRUE)
    {
      for(lIter = 0; lIter < DCM_RSRCMGR_DID_LOCK_LIST_SIZE; ++lIter)
      {
        if(Dcm_RsrcMgrSingletonContext.DidLockList[lIter].Owner == DCM_RSRCMGR_DIDLOCK_OWNER_NONE)
        {
          Dcm_RsrcMgrSingletonContext.DidLockList[lIter].Did = did;                                                                                  /* SBSW_DCM_POINTER_WRITE_DIDLOCKLIST */
          Dcm_RsrcMgrSingletonContext.DidLockList[lIter].Owner = owner;                                                                              /* SBSW_DCM_POINTER_WRITE_DIDLOCKLIST */

          lStdResult = DCM_E_OK;
          break;
        }
      }

      /* Assert that DidLockList is large enough */
      Dcm_DebugAssert((lStdResult == DCM_E_OK), DCM_SID_INTERNAL, DCM_E_ILLEGAL_STATE);                                                              /* COV_DCM_RTM_DEV_DEBUG XF */
    }
  }

  return lStdResult;
}

/**********************************************************************************************************************
 *  Dcm_RsrcMgrReleaseDidLock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, DCM_CODE) Dcm_RsrcMgrReleaseDidLock(
  Dcm_RsrcMgrDidLockOwnerType owner
  )
{
  uint8_least lIter;

  for(lIter = 0; lIter < DCM_RSRCMGR_DID_LOCK_LIST_SIZE; ++lIter)
  {
    if(Dcm_RsrcMgrSingletonContext.DidLockList[lIter].Owner == owner)
    {
      Dcm_RsrcMgrSingletonContext.DidLockList[lIter].Did = 0u;                                                                                       /* SBSW_DCM_POINTER_WRITE_DIDLOCKLIST */
      Dcm_RsrcMgrSingletonContext.DidLockList[lIter].Owner = DCM_RSRCMGR_DIDLOCK_OWNER_NONE;                                                         /* SBSW_DCM_POINTER_WRITE_DIDLOCKLIST */
      break;
    }
  }
}
#define DCM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_RsrcMgr.c
 *********************************************************************************************************************/
