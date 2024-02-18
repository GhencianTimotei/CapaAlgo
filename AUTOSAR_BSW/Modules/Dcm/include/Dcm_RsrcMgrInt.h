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
/**        \file  Dcm_RsrcMgrInt.h
 *        \brief  Contains public function declarations and complex type definitions of RsrcMgr unit.
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
#if !defined(DCM_RSRCMGRINT_H)
# define DCM_RSRCMGRINT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Dcm_RsrcMgrTypes.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! Memory access types, used for locking the memory manager to protect from concurrent access */
# define DCM_RSRCMGR_MEM_ACCESS_NONE                                 ((Dcm_RsrcMgrMemLockOwnerType)0u)  /*!< The access to the memory is not locked */
# define DCM_RSRCMGR_MEM_ACCESS_REQ_EXT                              ((Dcm_RsrcMgrMemLockOwnerType)1u)  /*!< The access to the memory is locked by SVC 0x23/0x3D */
# define DCM_RSRCMGR_MEM_ACCESS_REQ_INT                              ((Dcm_RsrcMgrMemLockOwnerType)2u)  /*!< The access to the memory is locked by SVC 0x2C */

/*! DID/VID access types, used for locking the DID/VID to protect from concurrent access */
# define DCM_RSRCMGR_DIDLOCK_OWNER_NONE                              ((Dcm_RsrcMgrDidLockOwnerType)0)  /*!< The access to the DID is not locked */
# define DCM_RSRCMGR_DIDLOCK_OWNER_SID09                             ((Dcm_RsrcMgrDidLockOwnerType)1)  /*!< The access to the DID/VID is locked by SVC 0x09 */
# define DCM_RSRCMGR_DIDLOCK_OWNER_SID22                             ((Dcm_RsrcMgrDidLockOwnerType)2)  /*!< The access to the DID is locked by SVC 0x22 */
# define DCM_RSRCMGR_DIDLOCK_OWNER_SID2A                             ((Dcm_RsrcMgrDidLockOwnerType)3)  /*!< The access to the DID is locked by SVC 0x2A */
# define DCM_RSRCMGR_DIDLOCK_OWNER_SID2C                             ((Dcm_RsrcMgrDidLockOwnerType)4)  /*!< The access to the DID is locked by SVC 0x2C */
# define DCM_RSRCMGR_DIDLOCK_OWNER_SID2E                             ((Dcm_RsrcMgrDidLockOwnerType)5)  /*!< The access to the DID is locked by SVC 0x2E */
# define DCM_RSRCMGR_DIDLOCK_OWNER_SID2F                             ((Dcm_RsrcMgrDidLockOwnerType)6)  /*!< The access to the DID is locked by SVC 0x2F */
# define DCM_RSRCMGR_DIDLOCK_OWNER_SID86                             ((Dcm_RsrcMgrDidLockOwnerType)7)  /*!< The access to the DID is locked by SVC 0x86 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_RsrcMgrInit()
 *********************************************************************************************************************/
/*! \brief          Initializes the resource manager sub-component.
 *  \details        -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            Global interrupts shall be disabled.
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_RsrcMgrInit(
  void
  );

/**********************************************************************************************************************
 *  Dcm_RsrcMgrHasMemLock()
 *********************************************************************************************************************/
/*! \brief          Checks whether the given owner has locked the memory resource.
 *  \details        -
 *  \param[in]      owner    Service specific owner
 *  \return         TRUE     Memory resource is already locked by the given owner
 *  \return         FALSE    Memory resource is not locked by the given owner
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_RsrcMgrHasMemLock(
  Dcm_RsrcMgrMemLockOwnerType owner
  );

/**********************************************************************************************************************
 *  Dcm_RsrcMgrGetMemLock()
 *********************************************************************************************************************/
/*! \brief          Tries to lock the memory resource.
 *  \details        -
 *  \param[in]      opStatus         Current operation status
 *  \param[in]      owner            Service specific owner
 *  \return         DCM_E_OK         Memory resource was successfully locked
 *  \return         DCM_E_PENDING    Memory resource is locked
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_RsrcMgrGetMemLock(
  Dcm_OpStatusType opStatus,
  Dcm_RsrcMgrMemLockOwnerType owner
  );

/**********************************************************************************************************************
 *  Dcm_RsrcMgrReleaseMemLock()
 *********************************************************************************************************************/
/*! \brief          Releases the lock of the memory resource.
 *  \details        -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_RsrcMgrReleaseMemLock(
  void
  );

/**********************************************************************************************************************
 *  Dcm_RsrcMgrHasDidLock()
 *********************************************************************************************************************/
/*! \brief          Checks whether the given owner has locked any Did.
 *  \details        -
 *  \param[in]      owner    Service specific owner of the to be locked Did
 *  \return         TRUE     Did is already locked by the given owner
 *  \return         FALSE    Did is not locked by the given owner
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_RsrcMgrHasDidLock(
  Dcm_RsrcMgrDidLockOwnerType owner
  );

/**********************************************************************************************************************
 *  Dcm_RsrcMgrIsDidFree()
 *********************************************************************************************************************/
/*! \brief          Checks whether a Did can be locked or not.
 *  \details        -
 *  \param[in]      did      Did to be locked
 *  \return         TRUE     Did is free
 *  \return         FALSE    Did is locked
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_RsrcMgrIsDidFree(
  uint16 did
  );

/**********************************************************************************************************************
 *  Dcm_RsrcMgrGetDidLock()
 *********************************************************************************************************************/
/*! \brief          Tries to lock a given Did.
 *  \details        -
 *  \param[in]      opStatus         Current operation status
 *  \param[in]      did              Did to be locked
 *  \param[in]      owner            Service specific owner of the to be locked Did
 *  \return         DCM_E_OK         Did was successfully locked or owner has already a lock for that Did
 *  \return         DCM_E_PENDING    Did is locked
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_RsrcMgrGetDidLock(
  Dcm_OpStatusType opStatus,
  uint16 did,
  Dcm_RsrcMgrDidLockOwnerType owner
  );

/**********************************************************************************************************************
 *  Dcm_RsrcMgrReleaseDidLock()
 *********************************************************************************************************************/
/*! \brief          Releases a Did locked by the given owner.
 *  \details        -
 *  \param[in]      owner    Service specific owner of the to be released Did
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_RsrcMgrReleaseDidLock(
  Dcm_RsrcMgrDidLockOwnerType owner
  );
# define DCM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#endif /* !defined(DCM_RSRCMGRINT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_RsrcMgrInt.h
 *********************************************************************************************************************/
