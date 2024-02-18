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
 *            Module: ComM
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: Huf H_lsbeck & F_rst GmbH & Co. KG
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: S32K144
 *    License Scope : The usage is restricted to CBD2100188_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: ComM_Private_Cfg.h
 *   Generation Time: 2024-02-05 15:58:30
 *           Project: DaVinciConfigurationS32K144 - Version 1.0
 *          Delivery: CBD2100188_D01
 *      Tool Version: DaVinci Configurator  5.23.45 SP4
 *
 *
 *********************************************************************************************************************/


#if !defined(COMM_PRIVATE_CFG_H)
#define COMM_PRIVATE_CFG_H
/* -----------------------------------------------------------------------------
    &&&~ INCLUDE
 ----------------------------------------------------------------------------- */
#include "ComM.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  ComMPCGetConstantDuplicatedRootDataMacros  ComM Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define ComM_GetChannelOfPCConfig()                                   ComM_Channel  /**< the pointer to ComM_Channel */
#define ComM_GetChannelPbOfPCConfig()                                 ComM_ChannelPb  /**< the pointer to ComM_ChannelPb */
#define ComM_GetDcmRequestActiveOfPCConfig()                          ComM_DcmRequestActive.raw  /**< the pointer to ComM_DcmRequestActive */
#define ComM_GetLastStateChangeOfPCConfig()                           ComM_LastStateChange  /**< the pointer to ComM_LastStateChange */
#define ComM_GetMinFullComModeTimerOfPCConfig()                       ComM_MinFullComModeTimer.raw  /**< the pointer to ComM_MinFullComModeTimer */
#define ComM_GetSizeOfChannelOfPCConfig()                             1u  /**< the number of accomplishable value elements in ComM_Channel */
#define ComM_GetSizeOfChannelPbOfPCConfig()                           1u  /**< the number of accomplishable value elements in ComM_ChannelPb */
#define ComM_GetSizeOfUserByteMaskOfPCConfig()                        3u  /**< the number of accomplishable value elements in ComM_UserByteMask */
#define ComM_GetSizeOfUserModeNotiFuncOfPCConfig()                    3u  /**< the number of accomplishable value elements in ComM_UserModeNotiFunc */
#define ComM_GetSizeOfUserOfPCConfig()                                3u  /**< the number of accomplishable value elements in ComM_User */
#define ComM_GetSizeOfUserReqFullComOfPCConfig()                      1u  /**< the number of accomplishable value elements in ComM_UserReqFullCom */
#define ComM_GetUserByteMaskOfPCConfig()                              ComM_UserByteMask  /**< the pointer to ComM_UserByteMask */
#define ComM_GetUserModeNotiFuncOfPCConfig()                          ComM_UserModeNotiFunc  /**< the pointer to ComM_UserModeNotiFunc */
#define ComM_GetUserOfPCConfig()                                      ComM_User  /**< the pointer to ComM_User */
#define ComM_GetUserReqFullComOfPCConfig()                            ComM_UserReqFullCom  /**< the pointer to ComM_UserReqFullCom */
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCGetDuplicatedRootDataMacros  ComM Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define ComM_GetSizeOfDcmRequestActiveOfPCConfig()                    ComM_GetSizeOfChannelOfPCConfig()  /**< the number of accomplishable value elements in ComM_DcmRequestActive */
#define ComM_GetSizeOfLastStateChangeOfPCConfig()                     ComM_GetSizeOfUserOfPCConfig()  /**< the number of accomplishable value elements in ComM_LastStateChange */
#define ComM_GetSizeOfMinFullComModeTimerOfPCConfig()                 ComM_GetSizeOfChannelOfPCConfig()  /**< the number of accomplishable value elements in ComM_MinFullComModeTimer */
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCGetDataMacros  ComM Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define ComM_IsDcmRequestActive(Index)                                ((ComM_GetDcmRequestActiveOfPCConfig()[(Index)]) != FALSE)
#define ComM_GetLastStateChange(Index)                                (ComM_GetLastStateChangeOfPCConfig()[(Index)])
#define ComM_GetMinFullComModeTimer(Index)                            (ComM_GetMinFullComModeTimerOfPCConfig()[(Index)])
#define ComM_IsPncUserOfUser(Index)                                   ((ComM_GetUserOfPCConfig()[(Index)].PncUserOfUser) != FALSE)
#define ComM_GetUserByteMaskEndIdxOfUser(Index)                       (ComM_GetUserOfPCConfig()[(Index)].UserByteMaskEndIdxOfUser)
#define ComM_GetUserByteMaskStartIdxOfUser(Index)                     (ComM_GetUserOfPCConfig()[(Index)].UserByteMaskStartIdxOfUser)
#define ComM_GetClearMaskOfUserByteMask(Index)                        (ComM_GetUserByteMaskOfPCConfig()[(Index)].ClearMaskOfUserByteMask)
#define ComM_GetSetMaskOfUserByteMask(Index)                          (ComM_GetUserByteMaskOfPCConfig()[(Index)].SetMaskOfUserByteMask)
#define ComM_GetUserModeNotiFunc(Index)                               (ComM_GetUserModeNotiFuncOfPCConfig()[(Index)])
#define ComM_GetUserReqFullCom(Index)                                 (ComM_GetUserReqFullComOfPCConfig()[(Index)])
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCGetDeduplicatedDataMacros  ComM Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define ComM_GetBusTypeOfChannel(Index)                               COMM_BUS_TYPE_CAN  /**< The channel bus type */
#define ComM_GetGwTypeOfChannel(Index)                                COMM_GATEWAY_TYPE_NONE  /**< The partial network gateway type, relevant for channels attached to coordinated partial networks */
#define ComM_GetInhibitionInitValueOfChannel(Index)                   0x00u  /**< Initial value of the inhibition status of the channel */
#define ComM_GetMinFullComTimeOfChannel(Index)                        250u  /**< Minimal full communication time for the channel, relevant for NmTypes LIGHT and FULL */
#define ComM_GetNmTypeOfChannel(Index)                                COMM_LIGHT_NMTYPEOFCHANNEL  /**< The Network Management type of the channel */
#define ComM_GetWakeupStateOfChannel(Index)                           COMM_FULL_COM_NETWORK_REQUESTED  /**< Target channel state after a Passive Wake-up */
#define ComM_GetUserReqFullComEndIdxOfChannelPb(Index)                1u  /**< the end index of the 0:n relation pointing to ComM_UserReqFullCom */
#define ComM_GetUserReqFullComStartIdxOfChannelPb(Index)              0u  /**< the start index of the 0:n relation pointing to ComM_UserReqFullCom */
#define ComM_IsUserReqFullComUsedOfChannelPb(Index)                   (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to ComM_UserReqFullCom */
#define ComM_GetSizeOfChannel()                                       ComM_GetSizeOfChannelOfPCConfig()
#define ComM_GetSizeOfChannelPb()                                     ComM_GetSizeOfChannelPbOfPCConfig()
#define ComM_GetSizeOfDcmRequestActive()                              ComM_GetSizeOfDcmRequestActiveOfPCConfig()
#define ComM_GetSizeOfLastStateChange()                               ComM_GetSizeOfLastStateChangeOfPCConfig()
#define ComM_GetSizeOfMinFullComModeTimer()                           ComM_GetSizeOfMinFullComModeTimerOfPCConfig()
#define ComM_GetSizeOfUser()                                          ComM_GetSizeOfUserOfPCConfig()
#define ComM_GetSizeOfUserByteMask()                                  ComM_GetSizeOfUserByteMaskOfPCConfig()
#define ComM_GetSizeOfUserModeNotiFunc()                              ComM_GetSizeOfUserModeNotiFuncOfPCConfig()
#define ComM_GetSizeOfUserReqFullCom()                                ComM_GetSizeOfUserReqFullComOfPCConfig()
#define ComM_IsUserByteMaskUsedOfUser(Index)                          (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to ComM_UserByteMask */
#define ComM_GetChannelOfUserByteMask(Index)                          0u  /**< ID of the channel which is requested by this entry. */
#define ComM_GetUserReqFullComIdxOfUserByteMask(Index)                0u  /**< the index of the 1:1 relation pointing to ComM_UserReqFullCom */
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCSetDataMacros  ComM Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define ComM_SetDcmRequestActive(Index, Value)                        ComM_GetDcmRequestActiveOfPCConfig()[(Index)] = (Value)
#define ComM_SetLastStateChange(Index, Value)                         ComM_GetLastStateChangeOfPCConfig()[(Index)] = (Value)
#define ComM_SetMinFullComModeTimer(Index, Value)                     ComM_GetMinFullComModeTimerOfPCConfig()[(Index)] = (Value)
#define ComM_SetUserReqFullCom(Index, Value)                          ComM_GetUserReqFullComOfPCConfig()[(Index)] = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCHasMacros  ComM Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define ComM_HasChannel()                                             (TRUE != FALSE)
#define ComM_HasBusTypeOfChannel()                                    (TRUE != FALSE)
#define ComM_HasGwTypeOfChannel()                                     (TRUE != FALSE)
#define ComM_HasInhibitionInitValueOfChannel()                        (TRUE != FALSE)
#define ComM_HasMinFullComTimeOfChannel()                             (TRUE != FALSE)
#define ComM_HasNmTypeOfChannel()                                     (TRUE != FALSE)
#define ComM_HasWakeupStateOfChannel()                                (TRUE != FALSE)
#define ComM_HasChannelPb()                                           (TRUE != FALSE)
#define ComM_HasUserReqFullComEndIdxOfChannelPb()                     (TRUE != FALSE)
#define ComM_HasUserReqFullComStartIdxOfChannelPb()                   (TRUE != FALSE)
#define ComM_HasUserReqFullComUsedOfChannelPb()                       (TRUE != FALSE)
#define ComM_HasDcmRequestActive()                                    (TRUE != FALSE)
#define ComM_HasLastStateChange()                                     (TRUE != FALSE)
#define ComM_HasMinFullComModeTimer()                                 (TRUE != FALSE)
#define ComM_HasSizeOfChannel()                                       (TRUE != FALSE)
#define ComM_HasSizeOfChannelPb()                                     (TRUE != FALSE)
#define ComM_HasSizeOfDcmRequestActive()                              (TRUE != FALSE)
#define ComM_HasSizeOfLastStateChange()                               (TRUE != FALSE)
#define ComM_HasSizeOfMinFullComModeTimer()                           (TRUE != FALSE)
#define ComM_HasSizeOfUser()                                          (TRUE != FALSE)
#define ComM_HasSizeOfUserByteMask()                                  (TRUE != FALSE)
#define ComM_HasSizeOfUserModeNotiFunc()                              (TRUE != FALSE)
#define ComM_HasSizeOfUserReqFullCom()                                (TRUE != FALSE)
#define ComM_HasUser()                                                (TRUE != FALSE)
#define ComM_HasPncUserOfUser()                                       (TRUE != FALSE)
#define ComM_HasUserByteMaskEndIdxOfUser()                            (TRUE != FALSE)
#define ComM_HasUserByteMaskStartIdxOfUser()                          (TRUE != FALSE)
#define ComM_HasUserByteMaskUsedOfUser()                              (TRUE != FALSE)
#define ComM_HasUserByteMask()                                        (TRUE != FALSE)
#define ComM_HasChannelOfUserByteMask()                               (TRUE != FALSE)
#define ComM_HasClearMaskOfUserByteMask()                             (TRUE != FALSE)
#define ComM_HasSetMaskOfUserByteMask()                               (TRUE != FALSE)
#define ComM_HasUserReqFullComIdxOfUserByteMask()                     (TRUE != FALSE)
#define ComM_HasUserModeNotiFunc()                                    (TRUE != FALSE)
#define ComM_HasUserReqFullCom()                                      (TRUE != FALSE)
#define ComM_HasPCConfig()                                            (TRUE != FALSE)
#define ComM_HasChannelOfPCConfig()                                   (TRUE != FALSE)
#define ComM_HasChannelPbOfPCConfig()                                 (TRUE != FALSE)
#define ComM_HasDcmRequestActiveOfPCConfig()                          (TRUE != FALSE)
#define ComM_HasLastStateChangeOfPCConfig()                           (TRUE != FALSE)
#define ComM_HasMinFullComModeTimerOfPCConfig()                       (TRUE != FALSE)
#define ComM_HasSizeOfChannelOfPCConfig()                             (TRUE != FALSE)
#define ComM_HasSizeOfChannelPbOfPCConfig()                           (TRUE != FALSE)
#define ComM_HasSizeOfDcmRequestActiveOfPCConfig()                    (TRUE != FALSE)
#define ComM_HasSizeOfLastStateChangeOfPCConfig()                     (TRUE != FALSE)
#define ComM_HasSizeOfMinFullComModeTimerOfPCConfig()                 (TRUE != FALSE)
#define ComM_HasSizeOfUserByteMaskOfPCConfig()                        (TRUE != FALSE)
#define ComM_HasSizeOfUserModeNotiFuncOfPCConfig()                    (TRUE != FALSE)
#define ComM_HasSizeOfUserOfPCConfig()                                (TRUE != FALSE)
#define ComM_HasSizeOfUserReqFullComOfPCConfig()                      (TRUE != FALSE)
#define ComM_HasUserByteMaskOfPCConfig()                              (TRUE != FALSE)
#define ComM_HasUserModeNotiFuncOfPCConfig()                          (TRUE != FALSE)
#define ComM_HasUserOfPCConfig()                                      (TRUE != FALSE)
#define ComM_HasUserReqFullComOfPCConfig()                            (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCIncrementDataMacros  ComM Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/ 
#define ComM_IncLastStateChange(Index)                                ComM_GetLastStateChange(Index)++
#define ComM_IncMinFullComModeTimer(Index)                            ComM_GetMinFullComModeTimer(Index)++
#define ComM_IncUserReqFullCom(Index)                                 ComM_GetUserReqFullCom(Index)++
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCDecrementDataMacros  ComM Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/ 
#define ComM_DecLastStateChange(Index)                                ComM_GetLastStateChange(Index)--
#define ComM_DecMinFullComModeTimer(Index)                            ComM_GetMinFullComModeTimer(Index)--
#define ComM_DecUserReqFullCom(Index)                                 ComM_GetUserReqFullCom(Index)--
/** 
  \}
*/ 

  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/


/* Postbuild */
/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/


/* Macros for stored PNC signal data manipulation:*/

/* Evaluate if the bit for InternalPncId is set in the stored data for signal specified by InternalSignalId */
#define ComM_IsSignalStoredPncBitSet(InternalSignalId, InternalPncId) ((ComM_GetPncSignalValues(ComM_GetPncSignalValuesStartIdxOfPncSignal(InternalSignalId) + ComM_GetSignalByteIndexOfPncPb(InternalPncId)) & ComM_GetSetMaskOfPnc(InternalPncId)) > 0u) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/* PRQA S 3451 EXTERNDECLARATIONS */ /* MD_ComM_3451_3449 */ 
/* PRQA S 3449 EXTERNALDECLARATIONS_3449 */ /* MD_ComM_3451_3449 */ 
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  ComM_User
**********************************************************************************************************************/
/** 
  \var    ComM_User
  \brief  Information about ComM users
  \details
  Element                 Description
  PncUser                 decides if a user is a partial network user or a direct channel user
  UserByteMaskEndIdx      the end index of the 0:n relation pointing to ComM_UserByteMask
  UserByteMaskStartIdx    the start index of the 0:n relation pointing to ComM_UserByteMask
*/ 
#define COMM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(ComM_UserType, COMM_CONST) ComM_User[3];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  ComM_UserByteMask
**********************************************************************************************************************/
/** 
  \var    ComM_UserByteMask
  \brief  Each user has N entries in this array (N = # channels attached to this user, directly or through PNC). Each entry describes a Byte Position and a Mask for storing/clearing the user request in UserReqFullCom
  \details
  Element      Description
  ClearMask    Clear-mask for clearing the bit which corresponds to this user
  SetMask      Set-mask for setting the bit which corresponds to this user
*/ 
#define COMM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(ComM_UserByteMaskType, COMM_CONST) ComM_UserByteMask[3];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  ComM_UserModeNotiFunc
**********************************************************************************************************************/
/** 
  \var    ComM_UserModeNotiFunc
  \brief  User Mode Notification Functions (RTE Mode-Switch Interface)
*/ 
#define COMM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(ComM_StateNotiFuncPtrType, COMM_CONST) ComM_UserModeNotiFunc[3];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  ComM_DcmRequestActive
**********************************************************************************************************************/
/** 
  \var    ComM_DcmRequestActive
  \brief  Status of Dcm active diagnostic request, TRUE if requested, FALSE otherwise
*/ 
#define COMM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(ComM_DcmRequestActiveUType, COMM_VAR_NOINIT) ComM_DcmRequestActive;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define COMM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  ComM_LastStateChange
**********************************************************************************************************************/
/** 
  \var    ComM_LastStateChange
  \brief  Variables for storing the last notified user mode
*/ 
#define COMM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(ComM_ModeType, COMM_VAR_NOINIT) ComM_LastStateChange[3];
#define COMM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  ComM_MinFullComModeTimer
**********************************************************************************************************************/
/** 
  \var    ComM_MinFullComModeTimer
  \brief  The current value of Min Full Com Mode timer
*/ 
#define COMM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(ComM_MinFullComModeTimerUType, COMM_VAR_NOINIT) ComM_MinFullComModeTimer;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define COMM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  ComM_UserReqFullCom
**********************************************************************************************************************/
/** 
  \var    ComM_UserReqFullCom
  \brief  RAM array used to store user requests for channels as bitmasks. Each channel 'owns' 1..n bytes in this array, depending on the number of users assigned to it.
*/ 
#define COMM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(ComM_UserReqFullComType, COMM_VAR_NOINIT) ComM_UserReqFullCom[1];
#define COMM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/* PRQA L:EXTERNALDECLARATIONS_3449 */
/* PRQA L:EXTERNDECLARATIONS */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
  INTERNAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIG POINTER
**********************************************************************************************************************/
#if (COMM_USE_INIT_POINTER == STD_ON)
# define COMM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
# include "MemMap.h"

extern P2CONST(ComM_ConfigType, AUTOMATIC, COMM_INIT_DATA) ComM_ConfigPtr;

# define COMM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
# include "MemMap.h"
#endif

#endif /* COMM_PRIVATE_CFG_H */

