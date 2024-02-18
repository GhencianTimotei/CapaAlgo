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
/**        \file  Dcm_Ext.h
 *        \brief  Public interface of DCM extensions for other components
 *
 *      \details  MICROSAR DCM based on AR 4.0.3
 *
 *********************************************************************************************************************/
/* *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author     Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2012-08-20                           No relevant changes
 *  01.01.00  2012-09-20                           No relevant changes
 *  01.01.01  2012-10-12                           No relevant changes
 *  01.02.00  2013-01-31                           No relevant changes
 *  01.03.00  2013-04-17                           No relevant changes
 *  01.03.01  2013-05-28                           No relevant changes
 *  01.04.00  2013-06-17                           No relevant changes
 *  01.05.00  2013-07-26                           No relevant changes
 *  02.00.00  2013-07-18                           No relevant changes
 *  02.00.01  2013-12-05                           No relevant changes
 *  02.01.00  2013-12-03                           No relevant changes
 *  02.02.00  2014-04-11                           No relevant changes
 *  02.02.01  2014-07-31                           No relevant changes
 *  02.02.02  2014-08-11                           No relevant changes
 *  03.00.00  2014-10-30                           No relevant changes
 *  03.01.00  2014-11-11                           No relevant changes
 *  04.00.00  2015-01-30                           No relevant changes
 *  04.01.00  2015-04-07                           No relevant changes
 *  04.01.01  2015-09-10                           No relevant changes
 *  05.00.00  2015-11-27                           No relevant changes
 *  05.01.00  2016-02-28  vissat     ESCAN00087636 FEAT-1472: Implement Service 0x86 (RoE)
 *  05.02.00  2016-04-07                           No relevant changes
 *  07.00.00  2016-05-02  vissat     ESCAN00090614 Service 0x86: No RoE message is sent
 *  07.01.00  2016-09-22                           No relevant changes
 *  07.02.00  2017-01-03                           No relevant changes
 *  08.00.00  2017-04-04                           No relevant changes
 *  08.01.00  2017-04-19                           No relevant changes
 *  08.02.00  2017-05-19                           No relevant changes
 *  08.03.00  2017-06-19                           No relevant changes
 *  08.04.00  2017-07-13                           No relevant changes
 *  08.05.00  2017-08-07                           No relevant changes
 *  08.06.00  2017-09-20                           No relevant changes
 *  09.00.00  2017-10-25                           No relevant changes
 *  09.01.00  2017-11-06                           No relevant changes
 *  09.02.00  2017-11-29                           No relevant changes
 *  09.03.00  2018-01-05                           No relevant changes
 *  09.04.00  2018-01-23  visahe     STORYC-3192   DCM: RoE - Release
 *  09.05.00  2018-02-19                           No relevant changes
 *  10.00.00  2018-03-29                           No relevant changes
 *  10.01.00  2018-05-09                           No relevant changes
 *  10.02.00  2018-06-14                           No relevant changes
 *  10.03.00  2018-07-09                           No relevant changes
 *  10.04.00  2018-08-06                           No relevant changes
 *  11.00.00  2018-09-03                           No relevant changes
 *  11.01.00  2018-10-01                           No relevant changes
 *  11.02.00  2018-10-26                           No relevant changes
 *  11.03.00  2018-11-23                           No relevant changes
 *  11.04.00  2018-12-20                           No relevant changes
 *  11.05.00  2019-01-18  visahe     STORY-6107    Parallel OBD/UDS protocol processing - Multi thread handling
 *  11.06.00  2019-02-18                           No relevant changes
 *  12.00.00  2019-03-15                           No relevant changes
 *  12.01.00  2019-04-15                           No relevant changes
 *  12.02.00  2019-05-13                           No relevant changes
 *  12.03.00  2019-06-11                           No relevant changes
 *  12.04.00  2019-07-08                           No relevant changes
 *  12.05.00  2019-08-02                           No relevant changes
 *  13.00.00  2019-08-30                           No relevant changes
 *  13.01.00  2019-09-27                           No relevant changes
 *  13.02.00  2019-10-25                           No relevant changes
 *  13.03.00  2019-11-22                           No relevant changes
 *  13.04.00  2020-01-16                           No relevant changes
 *  13.05.00  2020-02-14                           No relevant changes
 *  14.00.00  2020-03-13                           No relevant changes
 *  14.01.00  2020-04-20                           No relevant changes
 *  14.02.00  2020-05-11                           No relevant changes
 *  14.03.00  2020-06-05                           No relevant changes
 *  14.04.00  2020-06-26                           No relevant changes
 *  14.05.00  2020-08-03                           No relevant changes
 *  15.00.00  2020-08-31                           No relevant changes
 *  15.01.00  2020-10-01                           No relevant changes
 *  15.02.00  2020-10-23                           No relevant changes
 *  15.03.00  2020-10-29                           No relevant changes
 *  15.04.00  2020-11-23                           No relevant changes
 *  15.05.00  2020-11-23  visahe     DCM-2594      Service 0x86: Support new start/stop behavior according to ISO14229-1:2020
 *                        visvkr     DCM-3638      Service 0x86: Support new start/stop behavior according to ISO14229-1:2020 - Part II
 *  15.06.00  2020-12-22                           No relevant changes
 *  15.07.00  2021-01-21                           No relevant changes
 *  15.08.00  2021-02-15                           No relevant changes
 *********************************************************************************************************************/
#if !defined(DCM_EXT_H)
# define DCM_EXT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

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
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
#  if (DCM_SVC_86_EVTYPE_ONCHGDTC_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_DemTriggerOnDTCStatus()
 *********************************************************************************************************************/
/*! \brief          Notifies DCM RoE handler for a DTC status change.
 *  \details        Triggers a ROE event for sub-service OnDTCStatusChanged if the requested DTCStatusMask is matched.
 *  \param[in]      DTC               This is the DTC the change is assigned to
 *  \param[in]      DTCStatusOld      DTC status before change
 *  \param[in]      DTCStatusNew      DTC status after change
 *  \return         DCM_E_OK          This value is always returned (also in error case)
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_SVC_86_EVTYPE_ONCHGDTC_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DemTriggerOnDTCStatus(
  uint32 DTC,
  uint8 DTCStatusOld,
  uint8 DTCStatusNew
  );
#  endif

#  if (DCM_SVC_86_EVTYPE_ONCHGDID_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_TriggerOnEvent()
 *********************************************************************************************************************/
/*! \brief          Triggers service to respond to.
 *  \details        Triggers service to respond to which was previously defined via service 0x86 request.
 *  \param[in]      RoeEventId
 *  \return         DCM_E_OK        RoeEventId value is valid
 *  \return         DCM_E_NOT_OK    RoeEventId value is not valid or the DCM is currently processing another request
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_SVC_86_EVTYPE_ONCHGDID_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_TriggerOnEvent(                                                                                                   /* PRQA S 3449, 3451 */ /* MD_Dcm_8.5_Rte */
  uint8 RoeEventId
  );
#  endif
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
# define DCM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CONST_UNSPECIFIED
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
extern CONST(Dcm_ExtSvc86NvMDataType, DCM_CONST) DcmExtSvc86DefaultNvMData;
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
# define DCM_STOP_SEC_CONST_UNSPECIFIED
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#endif /* !defined(DCM_EXT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_Ext.h
 *********************************************************************************************************************/
