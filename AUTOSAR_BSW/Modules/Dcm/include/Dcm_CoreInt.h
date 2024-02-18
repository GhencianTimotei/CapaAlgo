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
/**        \file  Dcm_CoreInt.h
 *        \brief  Private data type definition and interface of DCM
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
#if !defined(DCM_COREINT_H)
# define DCM_COREINT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# if (((DCM_SVC_02_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_03_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_04_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_07_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_0A_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_14_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_19_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_85_SUPPORT_ENABLED == STD_ON)) && ((DCM_DEM_API_430_ENABLED == STD_ON) || (DCM_DEM_API_431_ENABLED == STD_ON)))
#  include "Dem.h"
# endif /* (((DCM_SVC_02_SUPPORT_ENABLED == STD_ON) || \
 (DCM_SVC_03_SUPPORT_ENABLED == STD_ON) || \
 (DCM_SVC_04_SUPPORT_ENABLED == STD_ON) || \
 (DCM_SVC_07_SUPPORT_ENABLED == STD_ON) || \
 (DCM_SVC_0A_SUPPORT_ENABLED == STD_ON) || \
 (DCM_SVC_14_SUPPORT_ENABLED == STD_ON) || \
 (DCM_SVC_19_SUPPORT_ENABLED == STD_ON) || \
 (DCM_SVC_85_SUPPORT_ENABLED == STD_ON)) && ((DCM_DEM_API_430_ENABLED == STD_ON) || (DCM_DEM_API_431_ENABLED == STD_ON))) */
# if (((DCM_SVC_02_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_03_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_04_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_07_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_0A_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_14_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_19_SUPPORT_ENABLED == STD_ON) || \
     (DCM_SVC_85_SUPPORT_ENABLED == STD_ON)) && ((DCM_DEM_API_421_ENABLED == STD_ON) || (DCM_DEM_API_430_ENABLED == STD_ON) || (DCM_DEM_API_431_ENABLED == STD_ON)))
#  include "Dem_Dcm.h"
# endif /* (((DCM_SVC_02_SUPPORT_ENABLED == STD_ON) || \
 (DCM_SVC_03_SUPPORT_ENABLED == STD_ON) || \
 (DCM_SVC_04_SUPPORT_ENABLED == STD_ON) || \
 (DCM_SVC_07_SUPPORT_ENABLED == STD_ON) || \
 (DCM_SVC_0A_SUPPORT_ENABLED == STD_ON) || \
 (DCM_SVC_14_SUPPORT_ENABLED == STD_ON) || \
 (DCM_SVC_19_SUPPORT_ENABLED == STD_ON) || \
 (DCM_SVC_85_SUPPORT_ENABLED == STD_ON)) && ((DCM_DEM_API_421_ENABLED == STD_ON) || (DCM_DEM_API_430_ENABLED == STD_ON) || (DCM_DEM_API_431_ENABLED == STD_ON))) */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) || \
     (DCM_DIAG_VIRTUAL_REQUEST_ENABLED == STD_ON)
#  define DCM_NET_INTERNAL_REQ_ENABLED                               STD_ON
# else
#  define DCM_NET_INTERNAL_REQ_ENABLED                               STD_OFF
# endif
# if (DCM_MODE_CTRLDTCSETTING_MONITOR_ENABLED == STD_ON) || \
     (DCM_MODE_COMMCTRL_MONITOR_ENABLED == STD_ON)
#  define DCM_MODEMGR_MONITORING_ENABLED                             STD_ON
# else
#  define DCM_MODEMGR_MONITORING_ENABLED                             STD_OFF
# endif
# if (DCM_DEM_API_421_ENABLED == STD_ON) || (DCM_DEM_API_430_ENABLED == STD_ON) || (DCM_DEM_API_431_ENABLED == STD_ON)
#  if (DCM_SVC_14_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_UDS_CLEAR_DTC_ENABLED                          STD_ON
#  else
#   define DCM_DEMAPI_UDS_CLEAR_DTC_ENABLED                          STD_OFF
#  endif

#  if (DCM_SVC_04_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_OBD_CLEAR_DTC_ENABLED                          STD_ON
#  else
#   define DCM_DEMAPI_OBD_CLEAR_DTC_ENABLED                          STD_OFF
#  endif

#  if (DCM_SVC_19_01_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_07_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_11_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_12_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED     STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED     STD_OFF
#  endif

#  if (DCM_SVC_19_02_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0A_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0F_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_13_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_15_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_17_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_READ_DTC_BY_STATUS_MASK_ENABLED         STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_READ_DTC_BY_STATUS_MASK_ENABLED         STD_OFF
#  endif

#  if (DCM_SVC_19_06_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_10_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_19_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_READ_DTC_EXT_DATA_BY_DTC_NUM_ENABLED    STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_READ_DTC_EXT_DATA_BY_DTC_NUM_ENABLED    STD_OFF
#  endif

#  if (DCM_SVC_19_0B_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0C_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0D_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0E_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_READ_DTC_BY_OCCUR_TIME_ENABLED          STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_READ_DTC_BY_OCCUR_TIME_ENABLED          STD_OFF
#  endif

#  if (DCM_SVC_19_04_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_18_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_READ_DTC_FFR_BY_DTC_ENABLED             STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_READ_DTC_FFR_BY_DTC_ENABLED             STD_OFF
#  endif

/* DEM API usage optimization */
#  if (DCM_DEMAPI_SVC_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_BY_STATUS_MASK_ENABLED     == STD_ON) || \
      (DCM_SVC_19_08_SUPPORT_ENABLED                  == STD_ON) || \
      (DCM_SVC_19_14_SUPPORT_ENABLED                  == STD_ON) || \
      (DCM_SVC_19_1A_SUPPORT_ENABLED                  == STD_ON) || \
      (DCM_SVC_19_55_SUPPORT_ENABLED                  == STD_ON) || \
      (DCM_SVC_19_56_SUPPORT_ENABLED                  == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETNUMFILTEREDDTC_ENABLED               STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETNUMFILTEREDDTC_ENABLED               STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_BY_STATUS_MASK_ENABLED     == STD_ON) || \
      (DCM_SVC_19_14_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_08_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_42_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_55_SUPPORT_ENABLED == STD_ON)
#   define DCM_SVC_19_SETDTCFILTER_INFO_CLASS_ENABLED                STD_ON
#  else
#   define DCM_SVC_19_SETDTCFILTER_INFO_CLASS_ENABLED                STD_OFF
#  endif

#  if (DCM_SVC_19_09_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETSEVERITYOFDTC_ENABLED                STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETSEVERITYOFDTC_ENABLED                STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_FFR_BY_DTC_ENABLED          == STD_ON) || \
      (DCM_SVC_19_05_SUPPORT_ENABLED                   == STD_ON) || \
      (DCM_SVC_19_09_SUPPORT_ENABLED                   == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_BY_OCCUR_TIME_ENABLED       == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_EXT_DATA_BY_DTC_NUM_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETSTATUSOFDTC_ENABLED                  STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETSTATUSOFDTC_ENABLED                  STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_EXT_DATA_BY_DTC_NUM_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETSIZEOFEXTRECORD_ENABLED              STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETSIZEOFEXTRECORD_ENABLED              STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_EXT_DATA_BY_DTC_NUM_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETEXTRECORD_ENABLED                    STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETEXTRECORD_ENABLED                    STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_FFR_BY_DTC_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETSIZEOFFFRECORD_ENABLED               STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETSIZEOFFFRECORD_ENABLED               STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_FFR_BY_DTC_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETFFRECORD_ENABLED                     STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETFFRECORD_ENABLED                     STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_FFR_BY_DTC_ENABLED          == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_EXT_DATA_BY_DTC_NUM_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_ANYABLERECORDUPDATE_ENABLED             STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_ANYABLERECORDUPDATE_ENABLED             STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_BY_STATUS_MASK_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_BY_OCCUR_TIME_ENABLED == STD_ON) || \
      (DCM_SVC_19_14_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_08_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_09_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_1A_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_55_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_56_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETDTCSAM_ENABLED                       STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETDTCSAM_ENABLED                       STD_OFF
#  endif

#  if (DCM_SVC_19_42_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETDTCSEVAM_ENABLED                     STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETDTCSEVAM_ENABLED                     STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_BY_STATUS_MASK_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED == STD_ON) || \
      (DCM_SVC_19_14_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_08_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_42_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_55_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_SETDTCFILTER_ENABLED                    STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_SETDTCFILTER_ENABLED                    STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_BY_STATUS_MASK_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_BY_OCCUR_TIME_ENABLED     == STD_ON) || \
      (DCM_SVC_19_08_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_09_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_1A_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_42_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_55_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_56_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETDTCSTATUSAVAILABILITYMASK_ENABLED    STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETDTCSTATUSAVAILABILITYMASK_ENABLED    STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_BY_STATUS_MASK_ENABLED == STD_ON) || \
      (DCM_SVC_19_1A_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_55_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_56_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTC_ENABLED              STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTC_ENABLED              STD_OFF
#  endif

#  if (DCM_OBDDTCMGR_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_OBD_GETNEXTFILTEREDDTC_ENABLED                 STD_ON
#  else
#   define DCM_DEMAPI_OBD_GETNEXTFILTEREDDTC_ENABLED                 STD_OFF
#  endif

#  if (DCM_SVC_19_08_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_42_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTCANDSEV_ENABLED        STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTCANDSEV_ENABLED        STD_OFF
#  endif

#  if (DCM_SVC_19_14_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTCANDFDC_ENABLED        STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTCANDFDC_ENABLED        STD_OFF
#  endif

#  if (DCM_SVC_19_03_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETNEXTFILTEREDRECORD_ENABLED           STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETNEXTFILTEREDRECORD_ENABLED           STD_OFF
#  endif

#  if (DCM_SVC_19_03_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_SETFFRECORDFILTER_ENABLED               STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_SETFFRECORDFILTER_ENABLED               STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_BY_OCCUR_TIME_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETDTCOCCURTIME_ENABLED                 STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETDTCOCCURTIME_ENABLED                 STD_OFF
#  endif

#  if (DCM_OBDDTCMGR_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_OBD_SETDTCFILTER_ENABLED                       STD_ON
#  else
#   define DCM_DEMAPI_OBD_SETDTCFILTER_ENABLED                       STD_OFF
#  endif

#  if (DCM_DEMAPI_UDS_CLEAR_DTC_ENABLED == STD_ON) || \
      (DCM_DEMAPI_OBD_CLEAR_DTC_ENABLED == STD_ON)
#   define DCM_DEMAPI_CLEAR_DTC_ENABLED                              STD_ON
#  else
#   define DCM_DEMAPI_CLEAR_DTC_ENABLED                              STD_OFF
#  endif

#  if ((DCM_DEM_API_430_ENABLED == STD_ON) || \
      (DCM_DEM_API_431_ENABLED == STD_ON)) && \
      ((DCM_SVC_04_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_14_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_04_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_05_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_06_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_09_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0B_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0C_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0D_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0E_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_10_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_18_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_19_SUPPORT_ENABLED == STD_ON))
#   define DCM_DEM_API_SELECT_DTC_ENABLED                            STD_ON
#  else
#   define DCM_DEM_API_SELECT_DTC_ENABLED                            STD_OFF
#  endif

#  if ((DCM_DEM_API_430_ENABLED == STD_ON) || \
      (DCM_DEM_API_431_ENABLED == STD_ON)) && \
      (DCM_DEMAPI_SVC_19_GETFFRECORD_ENABLED == STD_ON)
#   define DCM_DEM_API_SELECT_FFR_ENABLED                            STD_ON
#  else
#   define DCM_DEM_API_SELECT_FFR_ENABLED                            STD_OFF
#  endif

#  if ((DCM_DEM_API_430_ENABLED == STD_ON) || \
      (DCM_DEM_API_431_ENABLED == STD_ON)) && \
      (DCM_DEMAPI_SVC_19_GETSIZEOFEXTRECORD_ENABLED == STD_ON)
#   define DCM_DEM_API_SELECT_EDR_ENABLED                            STD_ON
#  else
#   define DCM_DEM_API_SELECT_EDR_ENABLED                            STD_OFF
#  endif

#  if (DCM_DEMAPI_CLEAR_DTC_ENABLED == STD_ON) || \
      (DCM_DEMAPI_OBD_SETDTCFILTER_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_SETDTCFILTER_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_SETFFRECORDFILTER_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_ANYABLERECORDUPDATE_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETDTCOCCURTIME_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETDTCSAM_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETDTCSTATUSAVAILABILITYMASK_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETSTATUSOFDTC_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETSIZEOFFFRECORD_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETSIZEOFEXTRECORD_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETSEVERITYOFDTC_ENABLED == STD_ON)  || \
      (DCM_DEMAPI_SVC_19_GETFFRECORD_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETEXTRECORD_ENABLED == STD_ON)
#   define DCM_DEMAPI_RETVAL_TO_NRC_MAP_ENABLED                      STD_ON
#  else
#   define DCM_DEMAPI_RETVAL_TO_NRC_MAP_ENABLED                      STD_OFF
#  endif

#  if (DCM_DEMAPI_OBD_GETNEXTFILTEREDDTC_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTC_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTCANDSEV_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTCANDFDC_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETNEXTFILTEREDRECORD_ENABLED == STD_ON)
#   define DCM_DEMAPI_GETNEXTFILTEREDITEM_ENABLED                    STD_ON
#  else
#   define DCM_DEMAPI_GETNEXTFILTEREDITEM_ENABLED                    STD_OFF
#  endif
# endif /* (DCM_DEM_API_421_ENABLED == STD_ON) || (DCM_DEM_API_430_ENABLED == STD_ON) || (DCM_DEM_API_431_ENABLED == STD_ON) */
# if (DCM_SVC_19_SUPPORT_ENABLED == STD_ON)
#  if (DCM_DEMAPI_SVC_19_GETFFRECORD_ENABLED  == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETEXTRECORD_ENABLED == STD_ON)
#   define DCM_SVC_19_RECORD_ITER_ENABLED                            STD_ON
#  else
#   define DCM_SVC_19_RECORD_ITER_ENABLED                            STD_OFF
#  endif
# endif /* (DCM_SVC_19_SUPPORT_ENABLED == STD_ON) */

/*! Calculate the maximum number of events related to USDT transport objects, needed by a network related task */
# if (DCM_VARMGR_MODE_POSTBUILD_LOAD_ENABLED == STD_ON)
#  define DCM_NET_MAX_NUM_EVENT_TRANSP_OBJECTS                       32u                            /*!< Take the worst case, limited to 32 for a bit mask usage (i.e. task events) */
# else
#  define DCM_NET_MAX_NUM_EVENT_TRANSP_OBJECTS                       DCM_NET_MAX_NUM_TRANSP_OBJECTS /*!< Allocate as many as needed by the concrete configuration */
# endif

/*! Network variant/non-variant configuration abstraction */
# if (DCM_VARMGR_MULTI_COM_ENABLED == STD_ON)
#  define Dcm_NetCfgGetNumRxPduIds(comVariant)                       ((comVariant)->NumRxPduIds)                                                     /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumTxPduIds(comVariant)                       ((comVariant)->NumTxPduIds)                                                     /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetMinCanTpRxPduId(comVariant)                   ((comVariant)->CanTpRxPduIdMin)                                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetMaxCanTpRxPduId(comVariant)                   ((comVariant)->CanTpRxPduIdMax)                                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumCanRxPduIds(comVariant)                    ((comVariant)->NumCanTpRxPduIds)                                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumPerTxObjects(comVariant)                   ((comVariant)->NumPerTxObjects)                                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumConnections(comVariant)                    ((comVariant)->NumConnections)                                                  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumProtocols(comVariant)                      ((comVariant)->NumProtocols)                                                    /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumComMChannels(comVariant)                   ((comVariant)->NumComMChannels)                                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumBuffers(comVariant)                        ((comVariant)->NumBuffers)                                                      /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumTranspObjects(comVariant)                  ((comVariant)->NumTranspObjects)                                                /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNumAllComMChannels(comVariant)                ((comVariant)->NumAllComMChannels)                                              /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

#  define Dcm_NetCfgGetRxPduInfo(comVariant)                         ((comVariant)->RxPduIdTable)                                                    /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetConnectionInfo(comVariant)                    ((comVariant)->ConnectionTable)                                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetProtocolInfo(comVariant)                      ((comVariant)->ProtocolTable)                                                   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNetConnComMChannelMap(comVariant)             ((comVariant)->NetConnComMChannelMap)                                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNetworkHdlLookUp(comVariant)                  ((comVariant)->NetworkHandleLookUpTable)                                        /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetTxPdu2ConnMap(comVariant)                     ((comVariant)->TxPduIdMap)                                                      /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetPerTxPdu2RsrsMap(comVariant)                  ((comVariant)->PerTxPduIdMap)                                                   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetPerTxPduIdInfo(comVariant)                    ((comVariant)->PerTxPduIdTable)                                                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetComCtrlChannelListAll(comVariant)             ((comVariant)->ComCtrlChannelListAll)                                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetNetAllComMChannelMap(comVariant)              ((comVariant)->NetAllComMChannelMap)                                            /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define Dcm_NetCfgGetCanTp2DcmRxPduIdMap(comVariant)               ((comVariant)->CanTp2DcmRxPduIdMap)                                             /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# else
#  define Dcm_NetCfgGetNumRxPduIds(comVariant)                       DCM_NET_NUM_RX_PDUIDS
#  define Dcm_NetCfgGetNumTxPduIds(comVariant)                       DCM_NET_NUM_TX_PDUIDS
#  define Dcm_NetCfgGetMinCanTpRxPduId(comVariant)                   DCM_NET_CANTP_RX_PDUID_MIN
#  define Dcm_NetCfgGetMaxCanTpRxPduId(comVariant)                   DCM_NET_CANTP_RX_PDUID_MAX
#  define Dcm_NetCfgGetNumCanRxPduIds(comVariant)                    DCM_NET_NUM_CANTP_RX_PDUIDS
#  define Dcm_NetCfgGetNumPerTxObjects(comVariant)                   DCM_NET_MAX_NUM_PERIODIC_TX_OBJ
#  define Dcm_NetCfgGetNumConnections(comVariant)                    DCM_NET_MAX_NUM_CONNECTIONS
#  define Dcm_NetCfgGetNumProtocols(comVariant)                      DCM_NET_NUM_PROTOCOLS
#  define Dcm_NetCfgGetNumComMChannels(comVariant)                   DCM_NET_MAX_NUM_COMM_CHANNELS
#  define Dcm_NetCfgGetNumBuffers(comVariant)                        DCM_NET_NUM_BUFFERS
#  define Dcm_NetCfgGetNumTranspObjects(comVariant)                  DCM_NET_MAX_NUM_TRANSP_OBJECTS
#  define Dcm_NetCfgGetNumAllComMChannels(comVariant)                DCM_NET_MAX_NUM_ALL_COMM_CHANNELS

#  define Dcm_NetCfgGetRxPduInfo(comVariant)                         Dcm_CfgNetRxPduInfo
#  define Dcm_NetCfgGetConnectionInfo(comVariant)                    Dcm_CfgNetConnectionInfo
#  define Dcm_NetCfgGetProtocolInfo(comVariant)                      Dcm_CfgNetProtocolInfo
#  define Dcm_NetCfgGetNetConnComMChannelMap(comVariant)             Dcm_CfgNetConnComMChannelMap
#  define Dcm_NetCfgGetNetworkHdlLookUp(comVariant)                  Dcm_CfgNetNetworkHandleLookUpTable
#  define Dcm_NetCfgGetTxPdu2ConnMap(comVariant)                     Dcm_CfgNetTxPduInfo
#  define Dcm_NetCfgGetPerTxPdu2RsrsMap(comVariant)                  Dcm_CfgNetPeriodicTxPduInfo
#  define Dcm_NetCfgGetPerTxPduIdInfo(comVariant)                    Dcm_CfgNetPeriodicTxPduIds
#  define Dcm_NetCfgGetComCtrlChannelListAll(comVariant)             Dcm_CfgNetComCtrlChannelListAll
#  define Dcm_NetCfgGetNetAllComMChannelMap(comVariant)              Dcm_CfgNetAllComMChannelMap
#  define Dcm_NetCfgGetCanTp2DcmRxPduIdMap(comVariant)               Dcm_CfgNetCanTp2DcmRxPduIdMap
# endif

/*! Returns the diagnostic client connection ID from a DcmRxPduID */
# define Dcm_NetCfgGetConnHdlOfRxPduId(comVariant, rxPduId)          (Dcm_NetCfgGetRxPduInfo(comVariant)[(rxPduId)].ConnRef)                         /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns the diagnostic client's network address from its connection ID */
# define Dcm_NetCfgGetTesterAddressOfConnHdl(comVariant, connHdl)    (Dcm_NetCfgGetConnectionInfo(comVariant)[(connHdl)].ClientSrcAddr)              /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Provides the ECUs network address of a specific client connection */
# define Dcm_NetCfgGetEcuAddressOfConnHdl(comVariant, connHdl)       (Dcm_NetCfgGetConnectionInfo(comVariant)[(connHdl)].EcuAddress)                 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

# if (DCM_NET_GENERIC_CONNECTION_ENABLED == STD_ON)
/*! Indicates whether a connection is generic */
#  define Dcm_NetCfgIsGenericConnection(comVariant, connHdl)         (Dcm_NetCfgGetConnectionInfo(comVariant)[(connHdl)].MetaDataLength == DCM_NET_METADATA_LENGTH) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# endif

/*! Returns the diagnostic client's network address from one of its DcmRxPduIDs */
# define Dcm_NetCfgGetTesterAddressOfRxPduId(comVariant, rxPduId)    (Dcm_NetCfgGetTesterAddressOfConnHdl((comVariant), Dcm_NetCfgGetConnHdlOfRxPduId((comVariant), (rxPduId)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns the ECUs network address of a specific client connection from one of its DcmRxPduIDs */
# define Dcm_NetCfgGetEcuAddressOfRxPduId(comVariant, rxPduId)       (Dcm_NetCfgGetEcuAddressOfConnHdl((comVariant), Dcm_NetCfgGetConnHdlOfRxPduId((comVariant), (rxPduId)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! ComM channel message communication ability states */
# define DCM_NET_COMM_STATE_FLAG_RX_DIS                              ((Dcm_NetComMStateType)0x00u ) /*!< Message reception is disabled */
# define DCM_NET_COMM_STATE_FLAG_TX_DIS                              ((Dcm_NetComMStateType)0x00u ) /*!< Message transmission is disabled */
# define DCM_NET_COMM_STATE_FLAG_TX_EN                               ((Dcm_NetComMStateType)0x01u ) /*!< Message transmission is enabled */
# define DCM_NET_COMM_STATE_FLAG_RX_EN                               ((Dcm_NetComMStateType)0x02u ) /*!< Message reception is enabled */

/*! Calculates a combined reception and transmission message communication state */
# define DCM_NET_COMM_STATE_COMPOSER(rx,tx)                          ((Dcm_NetComMStateType)((rx)|(tx)))                                             /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Presets of all possible message communication states in both directions (Rx and Tx) */
# define DCM_NET_COMM_STATE_RX_DIS_TX_DIS                            (DCM_NET_COMM_STATE_COMPOSER(DCM_NET_COMM_STATE_FLAG_RX_DIS,DCM_NET_COMM_STATE_FLAG_TX_DIS)) /*!< Message reception and transmission are disabled (NoCommunicationMode) */
# define DCM_NET_COMM_STATE_RX_DIS_TX_EN                             (DCM_NET_COMM_STATE_COMPOSER(DCM_NET_COMM_STATE_FLAG_RX_DIS,DCM_NET_COMM_STATE_FLAG_TX_EN))  /*!< Message reception is disabled, but transmission is enabled */
# define DCM_NET_COMM_STATE_RX_EN_TX_DIS                             (DCM_NET_COMM_STATE_COMPOSER(DCM_NET_COMM_STATE_FLAG_RX_EN, DCM_NET_COMM_STATE_FLAG_TX_DIS)) /*!< Message reception is enabled, but transmission is disabled (SilentCommunicationMode) */
# define DCM_NET_COMM_STATE_RX_EN_TX_EN                              (DCM_NET_COMM_STATE_COMPOSER(DCM_NET_COMM_STATE_FLAG_RX_EN, DCM_NET_COMM_STATE_FLAG_TX_EN))  /*!< Message reception and transmission are enabled (FullCommunicationMode) */
# define DCM_REPEATER_PROGRESS_INITIAL                               ((Dcm_RepeaterProgressType)0)

# define DCM_REPEATER_PROGRESS_USERS_FIRST                           ((Dcm_RepeaterProgressType)1)
# define DCM_REPEATER_PROGRESS_USERS_LAST                            ((Dcm_RepeaterProgressType)254)
# define DCM_REPEATER_PROGRESS_INVALID                               ((Dcm_RepeaterProgressType)255)
/* all other progress types are client /service processor specific and shall start with DCM_REPEATER_PROGRESS_USERS_FIRST and end with DCM_REPEATER_PROGRESS_USERS_LAST */
/*! Represents the initial (default) value of the diagnostic state group "DiagnosticSession": "DefaultSession" */
# define DCM_STATE_VALUE_SESSION_INIT                                ((Dcm_CfgStateGroupMemType)0x01u)
/*! Represents the initial (default) value of the diagnostic state group "SecurityAccess": "Locked" */
# define DCM_STATE_VALUE_SECURITY_INIT                               ((Dcm_CfgStateGroupMemType)0x01u)
/*! Calculation of all system timer IDs.
  Note: The same order defined here must be kept during the initialization of the table Dcm_TmrTimerInfo */
# define DCM_TMR_ID_P2                                               ((Dcm_TmrTimerIdMemType)(0u + 0u))                                                                 /*!< The timer ID of the P2 timer */
# define DCM_TMR_ID_S3                                               ((Dcm_TmrTimerIdMemType)(DCM_TMR_ID_P2 + DCM_TMR_NUM_P2))                                          /*!< The timer ID of the S3 timer */
# define DCM_TMR_ID_FBLRES                                           ((Dcm_TmrTimerIdMemType)(DCM_TMR_ID_S3 + DCM_TMR_NUM_S3))                                          /*!< The timer ID of the ComM going to FullCommMode after ECU power-on/reset timer */
# define DCM_TMR_ID_SECURITY                                         ((Dcm_TmrTimerIdMemType)(DCM_TMR_ID_FBLRES + DCM_TMR_NUM_FBLRES))                                  /*!< The timer ID of the diagnostic service 0x27 failed attempt delay base timer */
# define DCM_TMR_ID_PERIODIC_TX                                      ((Dcm_TmrTimerIdMemType)(DCM_TMR_ID_SECURITY + DCM_TMR_NUM_SECURITY))                              /*!< The timer ID of the periodic message transmission base timer */
# define DCM_TMR_ID_SVC2A_SCHEDULER                                  ((Dcm_TmrTimerIdMemType)(DCM_TMR_ID_PERIODIC_TX + DCM_TMR_NUM_PERIODIC_TX))                        /*!< The timer ID of the diagnostic service 0x2A periodic DID scheduler base timer */
# define DCM_TMR_ID_SVC86_SCHEDULER                                  ((Dcm_TmrTimerIdMemType)(DCM_TMR_ID_SVC2A_SCHEDULER + DCM_TMR_NUM_SVC2A_SCHEDULER))                /*!< The timer ID of the diagnostic service 0x86 intermessage timer */
# define DCM_TMR_ID_KEEP_ALIVE                                       ((Dcm_TmrTimerIdMemType)(DCM_TMR_ID_SVC86_SCHEDULER + DCM_TMR_NUM_SVC86_SCHEDULER))  /*!< The timer ID of the extended keep-alive timer */
# define DCM_TMR_ID_AUTHENTICATION                                   ((Dcm_TmrTimerIdMemType)(DCM_TMR_ID_KEEP_ALIVE + DCM_TMR_NUM_KEEP_ALIVE))                          /*!< The timer ID of the authentication manager connection session base timer */

/*! Calculation of all timer context IDs */
# define DCM_TMR_CONTEXT_ID_P2                                       ((Dcm_TmrTimerIdMemType)(0u + 0u))                                                                 /*!< The timer context ID of the P2 timer */
# define DCM_TMR_CONTEXT_ID_S3                                       ((Dcm_TmrTimerIdMemType)(DCM_TMR_CONTEXT_ID_P2 + DCM_TMR_CONTEXT_NUM_P2))                          /*!< The timer context ID of the S3 timer */
# define DCM_TMR_CONTEXT_ID_FBLRES                                   ((Dcm_TmrTimerIdMemType)(DCM_TMR_CONTEXT_ID_S3 + DCM_TMR_CONTEXT_NUM_S3))                          /*!< The timer context ID of the ComM going to FullCommMode after ECU power-on/reset timer */
# define DCM_TMR_CONTEXT_ID_SECURITY                                 ((Dcm_TmrTimerIdMemType)(DCM_TMR_CONTEXT_ID_FBLRES + DCM_TMR_CONTEXT_NUM_FBLRES))                  /*!< The timer context ID of the diagnostic service 0x27 failed attempt delay base timer */
# define DCM_TMR_CONTEXT_ID_PERIODIC_TX                              ((Dcm_TmrTimerIdMemType)(DCM_TMR_CONTEXT_ID_SECURITY + DCM_TMR_CONTEXT_NUM_SECURITY))              /*!< The timer context ID of the periodic message transmission base timer */
# define DCM_TMR_CONTEXT_ID_SVC2A_SCHEDULER                          ((Dcm_TmrTimerIdMemType)(DCM_TMR_CONTEXT_ID_PERIODIC_TX + DCM_TMR_CONTEXT_NUM_PERIODIC_TX))        /*!< The timer context ID of the diagnostic service 0x2A periodic DID scheduler base timer */
# define DCM_TMR_CONTEXT_ID_SVC86_SCHEDULER                          ((Dcm_TmrTimerIdMemType)(DCM_TMR_CONTEXT_ID_SVC2A_SCHEDULER + DCM_TMR_CONTEXT_NUM_SVC2A_SCHEDULER)) /*!< The timer context ID of the diagnostic service 0x86 intermessage timer */
# define DCM_TMR_CONTEXT_ID_KEEP_ALIVE                               ((Dcm_TmrTimerIdMemType)(DCM_TMR_CONTEXT_ID_SVC86_SCHEDULER + DCM_TMR_CONTEXT_NUM_SVC86_SCHEDULER)) /*!< The timer context ID of the extended keep-alive timer */
# define DCM_TMR_CONTEXT_ID_AUTHENTICATION                           ((Dcm_TmrTimerIdMemType)(DCM_TMR_CONTEXT_ID_KEEP_ALIVE + DCM_TMR_CONTEXT_NUM_KEEP_ALIVE))          /*!< The timer context ID of the extended keep-alive timer */

/*
 * Definition and calculation the total number of system timers
 */
/*! A single timer for P2 monitoring is always needed and thread specific */
# define DCM_TMR_NUM_P2                                              1u
# define DCM_TMR_CONTEXT_NUM_P2                                      (DCM_TMR_NUM_P2 * DCM_NUM_THREADS)

/*! A single timer for S3 monitoring is needed */
# define DCM_TMR_NUM_S3                                              1u
# define DCM_TMR_CONTEXT_NUM_S3                                      (DCM_TMR_NUM_S3 * 1u)

/*! A single timer for monitoring the time between ECU start up and ComM going into FullComMode is needed */
# if (DCM_DIAG_JUMPFROMFBL_ENABLED == STD_ON)
#  define DCM_TMR_NUM_FBLRES                                         1u
# else
#  define DCM_TMR_NUM_FBLRES                                         0u /*!< Just a bridge to accomplish the amount of timers calculation */
# endif
# define DCM_TMR_CONTEXT_NUM_FBLRES                                  (DCM_TMR_NUM_FBLRES * 1u)

/*! A single timer for monitoring all security access delay times is needed */
# if (DCM_SVC_27_SUPPORT_ENABLED == STD_ON)
#  define DCM_TMR_NUM_SECURITY                                       1u
# else
#  define DCM_TMR_NUM_SECURITY                                       0u
# endif
# define DCM_TMR_CONTEXT_NUM_SECURITY                                (DCM_TMR_NUM_SECURITY * 1u)

/*! A single timer for monitoring all periodic message transmission times is needed */
# if (DCM_NET_PERIODIC_TX_ENABLED == STD_ON)
#  define DCM_TMR_NUM_PERIODIC_TX                                    1u
# else
#  define DCM_TMR_NUM_PERIODIC_TX                                    0u /*!< Just a bridge to accomplish the amount of timers calculation */
# endif
# define DCM_TMR_CONTEXT_NUM_PERIODIC_TX                             (DCM_TMR_NUM_PERIODIC_TX * 1u)

/*! A single timer for monitoring periodic DID scheduler timers is needed */
# if (DCM_SVC_2A_SUPPORT_ENABLED == STD_ON) && \
     (DCM_SPLIT_TASKS_ENABLED    == STD_ON)
#  define DCM_TMR_NUM_SVC2A_SCHEDULER                                1u
# else
#  define DCM_TMR_NUM_SVC2A_SCHEDULER                                0u /*!< Just a bridge to accomplish the amount of timers calculation */
# endif
# define DCM_TMR_CONTEXT_NUM_SVC2A_SCHEDULER                         (DCM_TMR_NUM_SVC2A_SCHEDULER * 1u)

/*! A single timer for managing the RoE transmission intermessage time is needed */
# if (DCM_SVC_86_TIMER_ENABLED == STD_ON)
#  define DCM_TMR_NUM_SVC86_SCHEDULER                                1u
# else
#  define DCM_TMR_NUM_SVC86_SCHEDULER                                0u /*!< Just a bridge to accomplish the amount of timers calculation */
# endif
# define DCM_TMR_CONTEXT_NUM_SVC86_SCHEDULER                         (DCM_TMR_NUM_SVC86_SCHEDULER * 1u)

/*! A single timer for monitoring the extended keep-alive delay time is needed */
# if (DCM_NET_KEEP_ALIVE_TIME_ENABLED == STD_ON)
#  define DCM_TMR_NUM_KEEP_ALIVE                                     1u
# else
#  define DCM_TMR_NUM_KEEP_ALIVE                                     0u /*!< Just a bridge to accomplish the amount of timers calculation */
# endif
# define DCM_TMR_CONTEXT_NUM_KEEP_ALIVE                              (DCM_TMR_NUM_KEEP_ALIVE * 1u)

/*! A single timer for monitoring all authentication session time is needed */
# if (DCM_AUTHMGR_DEFAULT_SESSION_TIMEOUT_ENABLED == STD_ON)
#  define DCM_TMR_NUM_AUTHENTICATION                                 1u
# else
#  define DCM_TMR_NUM_AUTHENTICATION                                 0u /*!< Just a bridge to accomplish the amount of timers calculation */
# endif
# define DCM_TMR_CONTEXT_NUM_AUTHENTICATION                          (DCM_TMR_NUM_AUTHENTICATION * 1u)

/*! Pre-compile total number of system timers calculation.
    Note: Do not cast the sum, since it is used within a pre-processor arithmetic expression (refer to Dcm_TmrMaskMemType definition section) */
# define DCM_TMR_NUM_TIMERS                                          ( DCM_TMR_NUM_P2 \
                                                                     + DCM_TMR_NUM_S3 \
                                                                     + DCM_TMR_NUM_FBLRES \
                                                                     + DCM_TMR_NUM_SECURITY \
                                                                     + DCM_TMR_NUM_PERIODIC_TX \
                                                                     + DCM_TMR_NUM_SVC2A_SCHEDULER \
                                                                     + DCM_TMR_NUM_SVC86_SCHEDULER \
                                                                     + DCM_TMR_NUM_KEEP_ALIVE \
                                                                     + DCM_TMR_NUM_AUTHENTICATION)

/*! Pre-compile total number of timer contexts calculation.
    Note: Do not cast the sum, since it is used within a pre-processor arithmetic expression (refer to Dcm_TmrMaskMemType definition section) */
# define DCM_TMR_NUM_TIMER_CONTEXTS                                  ( DCM_TMR_CONTEXT_NUM_P2 \
                                                                     + DCM_TMR_CONTEXT_NUM_S3 \
                                                                     + DCM_TMR_CONTEXT_NUM_FBLRES \
                                                                     + DCM_TMR_CONTEXT_NUM_SECURITY \
                                                                     + DCM_TMR_CONTEXT_NUM_PERIODIC_TX \
                                                                     + DCM_TMR_CONTEXT_NUM_SVC2A_SCHEDULER \
                                                                     + DCM_TMR_CONTEXT_NUM_SVC86_SCHEDULER \
                                                                     + DCM_TMR_CONTEXT_NUM_KEEP_ALIVE \
                                                                     + DCM_TMR_CONTEXT_NUM_AUTHENTICATION)

/*! The casted version of the DCM_TMR_NUM_TIMERS within the C-code */
# define DCM_TMR_NUM_TIMERS_CASTED                                   ((Dcm_TmrTimerIdMemType) DCM_TMR_NUM_TIMERS)
# define DCM_TMR_NUM_TIMER_CONTEXTS_CASTED                           ((Dcm_TmrTimerIdMemType) DCM_TMR_NUM_TIMER_CONTEXTS)
# if (DCM_DEM_API_421_ENABLED == STD_ON) || (DCM_DEM_API_430_ENABLED == STD_ON) || (DCM_DEM_API_431_ENABLED == STD_ON)
/*! Standard ISO 14229-1:2013 (UDS) DTC status bit representation */
#  define DCM_DTC_BIT_DONT_CARE                                      ((uint8)0x00u)
#  define DCM_DTC_BIT_TST_FLD                                        ((uint8)0x01u)
#  define DCM_DTC_BIT_TST_FLD_CYCL                                   ((uint8)0x02u)
#  define DCM_DTC_BIT_PNDG_DTC                                       ((uint8)0x04u)
#  define DCM_DTC_BIT_CONF_DTC                                       ((uint8)0x08u)
#  define DCM_DTC_BIT_TST_NOT_COMPL_CLR                              ((uint8)0x10u)
#  define DCM_DTC_BIT_TST_FLD_CLR                                    ((uint8)0x20u)
#  define DCM_DTC_BIT_TST_NOT_COMPL_CYCL                             ((uint8)0x40u)
#  define DCM_DTC_BIT_WARN_IND_REQ                                   ((uint8)0x80u)
# endif /* (DCM_DEM_API_421_ENABLED == STD_ON) || (DCM_DEM_API_430_ENABLED == STD_ON) || (DCM_DEM_API_431_ENABLED == STD_ON) */
/*! Basic thread ID used for thread independent processes */
# define DCM_THREAD_ID_BASIC                                         ((Dcm_ThreadIdMemType)0u)             /*!< Thread ID which shall be used for thread independent processes */
/*
 * Definition and calculation the total number of system tasks
 */
/*!< A single timer task (Dcm_TmrTaskTimer()) is always needed (manages all system timers) */
# define DCM_TSK_NUM_TIMER                                           1u
# define DCM_TSK_CONTEXT_NUM_TIMER                                   (DCM_TSK_NUM_TIMER * 1u)

/*!< A network tasks for managing the message transmission is always available */
# define DCM_TSK_NUM_NET_TX                                          1u
# define DCM_TSK_CONTEXT_NUM_NET_TX                                  (DCM_TSK_NUM_NET_TX * 1u)

/*!< A diagnostic tasks for managing the response message preparation is always available */
# define DCM_TSK_NUM_DIAG_TX                                         1u
# define DCM_TSK_CONTEXT_NUM_DIAG_TX                                 (DCM_TSK_NUM_DIAG_TX * DCM_NUM_THREADS)

/*!< A message reception network task (Dcm_NetTaskRx) is needed (i.e. for message prioritization before starting its processing) */
# define DCM_TSK_NUM_NET_RX                                          1u
# define DCM_TSK_CONTEXT_NUM_NET_RX                                  (DCM_TSK_NUM_NET_RX * DCM_NUM_THREADS)

/*! Dcm_ExtSvc86Task() configuration */
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
#  if defined (DCM_EXT_TSK_NUM_ROE)
#   define DCM_TSK_NUM_ROE                                           DCM_EXT_TSK_NUM_ROE       /*!< Inherits the Diagnostic service 0x86 needs for a dedicated task (Dcm_ExtSvc86Task()) for additional jobs to be executed out of service execution context */
#   if defined (DCM_EXT_TSK_ATR_ROE_EXEC)
#    define DCM_TSK_ATR_ROE_EXEC                                     DCM_EXT_TSK_ATR_ROE_EXEC  /*!< Inherits the attributes of the external RoE task */
#   else
#    error "Missing DCM extension value: DCM_EXT_TSK_ATR_ROE_EXEC!"
#   endif
#  else
#   error "Missing DCM extension value: DCM_EXT_TSK_NUM_ROE!"
#  endif

#  if defined (DCM_EXT_TSK_EV_ROE_MSB)
#   define DCM_TSK_EV_ROE_MSB                                        DCM_EXT_TSK_EV_ROE_MSB  /*!< Inherits the event register width of the external RoE task */
#  else
#   error "Missing DCM extension value: DCM_EXT_TSK_EV_ROE_MSB!"
#  endif
# else
#  define DCM_TSK_NUM_ROE                                            0u      /*!< Just a bridge to accomplish the amount of tasks calculation */
#  define DCM_TSK_EV_ROE_MSB                                         0x00u  /*!< No RoE task, no events, no MSB of the events available */
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
# define DCM_TSK_CONTEXT_NUM_ROE                                     (DCM_TSK_NUM_ROE * 1u)

/*! The paged-buffer task (Dcm_PagedBufferTask()) is required */
# if (DCM_PAGED_BUFFER_ENABLED == STD_ON)
#  define DCM_TSK_NUM_PGDBUF                                         1u
# else
#  define DCM_TSK_NUM_PGDBUF                                         0u  /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif
# define DCM_TSK_CONTEXT_NUM_PGDBUF                                  (DCM_TSK_NUM_PGDBUF * DCM_NUM_THREADS)

/*! A diagnostic tasks (Dcm_DiagTaskWorker()) for diagnostic service processing is always available */
# define DCM_TSK_NUM_DIAG_WORK                                       1u
# define DCM_TSK_CONTEXT_NUM_DIAG_WORK                               (DCM_TSK_NUM_DIAG_WORK * DCM_NUM_THREADS)

/*! Diagnostic service 0x27 needs dedicated task (Dcm_Svc27Task()) for additional jobs to be executed out of service execution context */
# if (DCM_SVC_27_SUPPORT_ENABLED == STD_ON) && \
     (DCM_STATE_SEC_ATT_CNTR_EXT_STORAGE_ENABLED == STD_ON)
#  define DCM_TSK_NUM_SVC27                                          1u
# else
#  define DCM_TSK_NUM_SVC27                                          0u  /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif
# define DCM_TSK_CONTEXT_NUM_SVC27                                   (DCM_TSK_NUM_SVC27 * 1u)

/*! One task (Dcm_DiagTaskFblRes()) for the final response after an FBL to APPL and vice versa transition */
# if (DCM_DIAG_JUMPFROMFBL_ENABLED == STD_ON)
#  define DCM_TSK_NUM_DIAG_FBLRES                                    1u  /*!< One task (Dcm_DiagTaskFblRes()) for the final response after an FBL to APPL and vice versa transition */
# else
#  define DCM_TSK_NUM_DIAG_FBLRES                                    0u  /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif
# define DCM_TSK_CONTEXT_NUM_DIAG_FBLRES                             (DCM_TSK_NUM_DIAG_FBLRES * 1u)

/*! One task (Dcm_ModeTaskMonitor()) for the background monitoring of mode changes that shall reset the ECU to its default state */
# if (DCM_MODEMGR_MONITORING_ENABLED == STD_ON)
#  define DCM_TSK_NUM_MODE_MONITOR                                   1u
# else
#  define DCM_TSK_NUM_MODE_MONITOR                                   0u  /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif
# define DCM_TSK_CONTEXT_NUM_MODE_MONITOR                            (DCM_TSK_NUM_MODE_MONITOR * 1u)

/*! Diagnostic service 0x2A needs dedicated task (Dcm_Svc2ATaskSchdProcess()) for additional jobs to be executed out of service execution context */
# if (DCM_SVC_2A_SUPPORT_ENABLED == STD_ON)
#  define DCM_TSK_NUM_SVC2A_SCHEDULER                                1u
# else
#  define DCM_TSK_NUM_SVC2A_SCHEDULER                                0u  /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif
# define DCM_TSK_CONTEXT_NUM_SVC2A_SCHEDULER                         (DCM_TSK_NUM_SVC2A_SCHEDULER * 1u)

/*! One task (Dcm_DiagTaskRx()) for the diagnostic message reception synchronization is always required */
# define DCM_TSK_NUM_DIAG_RX                                         1u
# define DCM_TSK_CONTEXT_NUM_DIAG_RX                                 (DCM_TSK_NUM_DIAG_RX * DCM_NUM_THREADS)

/*! One task (Dcm_ModeTaskMonitor()) for the background monitoring of diagnostic requests to other ECUs */
# if (DCM_NET_MONITOR_FOREIGN_N_TA_ENABLED == STD_ON)
#  define DCM_TSK_NUM_NET_TA_MONITOR                                 1u
# else
#  define DCM_TSK_NUM_NET_TA_MONITOR                                 0u  /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif
# define DCM_TSK_CONTEXT_NUM_NET_TA_MONITOR                          (DCM_TSK_NUM_NET_TA_MONITOR * 1u)

/*! One task (Dcm_DiagTaskRecovery()) for the full diagnostic state recovery after ECU reset /power down */
# if (DCM_DIAG_STATE_RECOVERY_ENABLED == STD_ON)
#  define DCM_TSK_NUM_DIAG_RECOVERY                                  1u
# else
#  define DCM_TSK_NUM_DIAG_RECOVERY                                  0u  /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif
# define DCM_TSK_CONTEXT_NUM_DIAG_RECOVERY                           (DCM_TSK_NUM_DIAG_RECOVERY * 1u)

/*! One task (Dcm_DiagTaskGarbageCollector()) for Releasing all obsolete transport objects after prioritization */
# if (DCM_DIAG_GARB_COL_ENABLED == STD_ON)
#  define DCM_TSK_NUM_DIAG_GARB_COL                                  1u
# else
#  define DCM_TSK_NUM_DIAG_GARB_COL                                  0u /* just a bridge */
# endif
# define DCM_TSK_CONTEXT_NUM_DIAG_GARB_COL                           (DCM_TSK_NUM_DIAG_GARB_COL * DCM_NUM_THREADS)

/*! Pre-compile total number of system tasks calculation */
# define DCM_TSK_NUM_TASKS                                           ((Dcm_TskTaskIdMemType)( DCM_TSK_NUM_TIMER \
                                                                     + DCM_TSK_NUM_DIAG_RX \
                                                                     + DCM_TSK_NUM_MODE_MONITOR \
                                                                     + DCM_TSK_NUM_DIAG_FBLRES \
                                                                     + DCM_TSK_NUM_DIAG_WORK \
                                                                     + DCM_TSK_NUM_PGDBUF \
                                                                     + DCM_TSK_NUM_SVC27 \
                                                                     + DCM_TSK_NUM_ROE \
                                                                     + DCM_TSK_NUM_DIAG_TX \
                                                                     + DCM_TSK_NUM_NET_TX \
                                                                     + DCM_TSK_NUM_NET_RX \
                                                                     + DCM_TSK_NUM_SVC2A_SCHEDULER \
                                                                     + DCM_TSK_NUM_NET_TA_MONITOR \
                                                                     + DCM_TSK_NUM_DIAG_RECOVERY \
                                                                     + DCM_TSK_NUM_DIAG_GARB_COL) )

/*! The casted version of the DCM_TSK_NUM_TASKS within the C-code */
# define DCM_TSK_NUM_TASKS_CONTEXT                                   ((Dcm_TskTaskIdMemType)( DCM_TSK_CONTEXT_NUM_TIMER \
                                                                     + DCM_TSK_CONTEXT_NUM_DIAG_RX \
                                                                     + DCM_TSK_CONTEXT_NUM_MODE_MONITOR \
                                                                     + DCM_TSK_CONTEXT_NUM_DIAG_FBLRES \
                                                                     + DCM_TSK_CONTEXT_NUM_DIAG_WORK \
                                                                     + DCM_TSK_CONTEXT_NUM_PGDBUF \
                                                                     + DCM_TSK_CONTEXT_NUM_SVC27 \
                                                                     + DCM_TSK_CONTEXT_NUM_ROE \
                                                                     + DCM_TSK_CONTEXT_NUM_DIAG_TX \
                                                                     + DCM_TSK_CONTEXT_NUM_NET_TX \
                                                                     + DCM_TSK_CONTEXT_NUM_NET_RX \
                                                                     + DCM_TSK_CONTEXT_NUM_SVC2A_SCHEDULER \
                                                                     + DCM_TSK_CONTEXT_NUM_NET_TA_MONITOR \
                                                                     + DCM_TSK_CONTEXT_NUM_DIAG_RECOVERY \
                                                                     + DCM_TSK_CONTEXT_NUM_DIAG_GARB_COL) )

/*! Calculation of all system tasks IDs.
  Note: The order is important since it determines the order of task activations in the corresponding scheduler! Lowest Id will be executed first.
        The same order defined here must be kept during the initialization of the table Dcm_TskTaskInfo */
# define DCM_TSK_ID_DIAG_RECOVERY                                    ((Dcm_TskTaskIdMemType)(0u + 0u))                                                  /*!< The task ID of the Dcm_DiagTaskRecovery() task */
# define DCM_TSK_ID_NET_TA_MONITOR                                   ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_DIAG_RECOVERY + DCM_TSK_NUM_DIAG_RECOVERY))     /*!< The task ID of the Dcm_NetTaskTaMonitor() task */
# define DCM_TSK_ID_NET_RX                                           ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_NET_TA_MONITOR + DCM_TSK_NUM_NET_TA_MONITOR))   /*!< The task ID of the Dcm_NetTaskRx task() */
# define DCM_TSK_ID_TIMER                                            ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_NET_RX + DCM_TSK_NUM_NET_RX))                   /*!< The task ID of the Dcm_TmrTaskTimer() task */
# define DCM_TSK_ID_DIAG_RX                                          ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_TIMER + DCM_TSK_NUM_TIMER))                     /*!< The task ID of the Dcm_DiagTaskRx() task */
# define DCM_TSK_ID_MODE_MONITOR                                     ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_DIAG_RX + DCM_TSK_NUM_DIAG_RX))                 /*!< The task ID of the Dcm_ModeTaskMonitor() task */
# define DCM_TSK_ID_DIAG_FBLRES                                      ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_MODE_MONITOR + DCM_TSK_NUM_MODE_MONITOR))       /*!< The task ID of the Dcm_DiagTaskFblRes() task */
# define DCM_TSK_ID_SVC27                                            ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_DIAG_FBLRES + DCM_TSK_NUM_DIAG_FBLRES))         /*!< The task ID of the Dcm_Svc27Task() task */
# define DCM_TSK_ID_DIAG_WORK                                        ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_SVC27 + DCM_TSK_NUM_SVC27))                     /*!< The task ID of the Dcm_DiagTaskWorker() task */
# define DCM_TSK_ID_PGDBUF                                           ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_DIAG_WORK + DCM_TSK_NUM_DIAG_WORK))             /*!< The task ID of the Dcm_PagedBufferTask() task */
# define DCM_TSK_ID_ROE                                              ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_PGDBUF + DCM_TSK_NUM_PGDBUF))
# define DCM_TSK_ID_DIAG_GARB_COL                                    ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_ROE + DCM_TSK_NUM_ROE))
# define DCM_TSK_ID_DIAG_TX                                          ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_DIAG_GARB_COL + DCM_TSK_NUM_DIAG_GARB_COL))     /*!< The task ID of the Dcm_DiagTaskTx() task */
# define DCM_TSK_ID_SVC2A_SCHEDULER                                  ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_DIAG_TX + DCM_TSK_NUM_DIAG_TX))
# define DCM_TSK_ID_NET_TX                                           ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_SVC2A_SCHEDULER + DCM_TSK_NUM_SVC2A_SCHEDULER)) /*!< The task ID of the Dcm_NetTaskTx() task */

/*! Calculation of all timer context IDs */
# define DCM_TSK_CONTEXT_ID_DIAG_RECOVERY                            ((Dcm_TskTaskIdMemType)(0u + 0u))                                                                  /*!< The task context of the Dcm_DiagTaskRecovery() task */
# define DCM_TSK_CONTEXT_ID_NET_TA_MONITOR                           ((Dcm_TskTaskIdMemType)(DCM_TSK_CONTEXT_ID_DIAG_RECOVERY + DCM_TSK_CONTEXT_NUM_DIAG_RECOVERY))     /*!< The task context of the Dcm_NetTaskTaMonitor() task */
# define DCM_TSK_CONTEXT_ID_NET_RX                                   ((Dcm_TskTaskIdMemType)(DCM_TSK_CONTEXT_ID_NET_TA_MONITOR + DCM_TSK_CONTEXT_NUM_NET_TA_MONITOR))   /*!< The task context of the Dcm_NetTaskRx task() */
# define DCM_TSK_CONTEXT_ID_TIMER                                    ((Dcm_TskTaskIdMemType)(DCM_TSK_CONTEXT_ID_NET_RX + DCM_TSK_CONTEXT_NUM_NET_RX))                   /*!< The task context of the Dcm_TmrTaskTimer() task */
# define DCM_TSK_CONTEXT_ID_DIAG_RX                                  ((Dcm_TskTaskIdMemType)(DCM_TSK_CONTEXT_ID_TIMER + DCM_TSK_CONTEXT_NUM_TIMER))                     /*!< The task context of the Dcm_DiagTaskRx() task */
# define DCM_TSK_CONTEXT_ID_MODE_MONITOR                             ((Dcm_TskTaskIdMemType)(DCM_TSK_CONTEXT_ID_DIAG_RX + DCM_TSK_CONTEXT_NUM_DIAG_RX))                 /*!< The task context of the Dcm_ModeTaskMonitor() task */
# define DCM_TSK_CONTEXT_ID_DIAG_FBLRES                              ((Dcm_TskTaskIdMemType)(DCM_TSK_CONTEXT_ID_MODE_MONITOR + DCM_TSK_CONTEXT_NUM_MODE_MONITOR))       /*!< The task context of the Dcm_DiagTaskFblRes() task */
# define DCM_TSK_CONTEXT_ID_SVC27                                    ((Dcm_TskTaskIdMemType)(DCM_TSK_CONTEXT_ID_DIAG_FBLRES + DCM_TSK_CONTEXT_NUM_DIAG_FBLRES))         /*!< The task context of the Dcm_Svc27Task() task */
# define DCM_TSK_CONTEXT_ID_DIAG_WORK                                ((Dcm_TskTaskIdMemType)(DCM_TSK_CONTEXT_ID_SVC27 + DCM_TSK_CONTEXT_NUM_SVC27))                     /*!< The task context of the Dcm_DiagTaskWorker() task */
# define DCM_TSK_CONTEXT_ID_PGDBUF                                   ((Dcm_TskTaskIdMemType)(DCM_TSK_CONTEXT_ID_DIAG_WORK + DCM_TSK_CONTEXT_NUM_DIAG_WORK))             /*!< The task context of the Dcm_PagedBufferTask() task */
# define DCM_TSK_CONTEXT_ID_ROE                                      ((Dcm_TskTaskIdMemType)(DCM_TSK_CONTEXT_ID_PGDBUF + DCM_TSK_CONTEXT_NUM_PGDBUF))
# define DCM_TSK_CONTEXT_ID_DIAG_GARB_COL                            ((Dcm_TskTaskIdMemType)(DCM_TSK_CONTEXT_ID_ROE + DCM_TSK_CONTEXT_NUM_ROE))
# define DCM_TSK_CONTEXT_ID_DIAG_TX                                  ((Dcm_TskTaskIdMemType)(DCM_TSK_CONTEXT_ID_DIAG_GARB_COL + DCM_TSK_CONTEXT_NUM_DIAG_GARB_COL))     /*!< The task context of the Dcm_DiagTaskTx() task */
# define DCM_TSK_CONTEXT_ID_SVC2A_SCHEDULER                          ((Dcm_TskTaskIdMemType)(DCM_TSK_CONTEXT_ID_DIAG_TX + DCM_TSK_CONTEXT_NUM_DIAG_TX))
# define DCM_TSK_CONTEXT_ID_NET_TX                                   ((Dcm_TskTaskIdMemType)(DCM_TSK_CONTEXT_ID_SVC2A_SCHEDULER + DCM_TSK_CONTEXT_NUM_SVC2A_SCHEDULER)) /*!< The task context of the Dcm_NetTaskTx() task */

/*
 * Definition of all sub-components' tasks related events
 */

/*! Events of the Dcm_TmrTaskTimer() */
# define DCM_TSK_EV_TIMER_ACTIVE                                     ((Dcm_TskTaskEvMemType)0x01u)  /*!< Activate the task (on any timer activation and as long as a timer is running) */

/*! Registers the most significant bit in the event mask of the Dcm_TmrTaskTimer() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
# define DCM_TSK_EV_TIMER_MSB                                        0x01u

/*! Events of the Dcm_DiagTaskRx() */
# define DCM_TSK_EV_DIAG_RX_TMR_P2_TO                                ((Dcm_TskTaskEvMemType)0x01u)  /*!< Time-out of the P2 timer occurred */
# define DCM_TSK_EV_DIAG_RX_NEW_REQ                                  ((Dcm_TskTaskEvMemType)0x02u)  /*!< New request has been received and is ready for processing */

/*! Registers the most significant bit in the event mask of the Dcm_DiagTaskRx() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
# define DCM_TSK_EV_DIAG_RX_MSB                                      0x02u

/*! Events of the Dcm_DiagTaskWorker() */
# define DCM_TSK_EV_DIAG_WORK_TX_END_FINAL                           ((Dcm_TskTaskEvMemType)0x0001u)  /*!< Current diagnostic service processing just finished */
# define DCM_TSK_EV_DIAG_WORK_TX_END_RCRRP                           ((Dcm_TskTaskEvMemType)0x0002u)  /*!< A RCR-RP response transmission just finished */
# define DCM_TSK_EV_DIAG_WORK_EXT_SET2DEF                            ((Dcm_TskTaskEvMemType)0x0004u)  /*!< An external request for entering default-session (via Dcm_ResetToDefaultSession()) */
# define DCM_TSK_EV_DIAG_WORK_INT_SET2DEF                            ((Dcm_TskTaskEvMemType)0x0008u)  /*!< An internal request for entering default session (e.g. on protocol preemption) */
# define DCM_TSK_EV_DIAG_WORK_REPEAT                                 ((Dcm_TskTaskEvMemType)0x0010u)  /*!< A diagnostic request operation needs to be (re-)executed */
# define DCM_TSK_EV_DIAG_WORK_NEW_REQ                                ((Dcm_TskTaskEvMemType)0x0020u)  /*!< A new diagnostic request is to be processed */
# define DCM_TSK_EV_DIAG_WORK_CANCEL_OP                              ((Dcm_TskTaskEvMemType)0x0040u)  /*!< A background diagnostic request operation (e.g. PagedBuffer processing) cancelation */
# define DCM_TSK_EV_DIAG_WORK_EXT_SETSECBYPASS                       ((Dcm_TskTaskEvMemType)0x0080u)  /*!< An external request for enabling security bypass (via Dcm_SetSecurityBypass()) */
# define DCM_TSK_EV_DIAG_WORK_KILL_JOBS                              ((Dcm_TskTaskEvMemType)0x0100u)  /*!< Any diagnostic service processing currently in progress has to be terminated */
# define DCM_TSK_EV_DIAG_WORK_IDLE_CONN                              ((Dcm_TskTaskEvMemType)0x0200u)  /*!< A diagnostic client is idle and shall be deauthenticated */
# define DCM_TSK_EV_DIAG_WORK_EXT_SETROLE                            ((Dcm_TskTaskEvMemType)0x0400u)  /*!< An external request for setting the deauthenticated role (via Dcm_SetDeauthenticatedRole()) */

/*! Registers the most significant bit in the event mask of the Dcm_DiagTaskWorker() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
# define DCM_TSK_EV_DIAG_WORK_MSB                                    0x0400u

/*! Events of the Dcm_Svc27Task() */
# define DCM_TSK_EV_SVC_27_ATTEMPT_CNTR_READ                         ((Dcm_TskTaskEvMemType)0x01u)  /*!< Initiate attempt counter reading */
# define DCM_TSK_EV_SVC_27_ATTEMPT_CNTR_WRITE                        ((Dcm_TskTaskEvMemType)0x02u)  /*!< Initiate attempt counter writing */

/*! Registers the most significant bit in the event mask of the Dcm_Svc27Task() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
# define DCM_TSK_EV_SVC_27_MSB                                       0x02u

/*! Events of the Dcm_PagedBufferTask() */
# if (DCM_TSK_NUM_PGDBUF > 0u)
#  define DCM_TSK_EV_PGDBUF_UPDATE_PAGE                              ((Dcm_TskTaskEvMemType)0x01u)  /*!< Request of next data portion of the paged-buffer response */
/*! Registers the most significant bit in the event mask of the Dcm_PagedBufferTask() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
#  define DCM_TSK_EV_PGDBUF_MSB                                      0x01u
# else
#  define DCM_TSK_EV_PGDBUF_MSB                                      0x00u
# endif

/*! Events of the Dcm_DiagTaskRecovery() */
# if (DCM_TSK_NUM_DIAG_RECOVERY > 0u)
#  define DCM_TSK_EV_DIAG_RECOVERY_GETSTATE                          ((Dcm_TskTaskEvMemType)0x01u)  /*!< Initiate recovery state retrieval */
#  define DCM_TSK_EV_DIAG_RECOVERY_PROCESS                           ((Dcm_TskTaskEvMemType)0x02u)  /*!< Processing of recovery info */
#  define DCM_TSK_EV_DIAG_RECOVERY_FINISH                            ((Dcm_TskTaskEvMemType)0x04u)  /*!< Gathering recovery information finished */

/*! Registers the most significant bit in the event mask of the Dcm_DiagTaskRecovery() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
#  define DCM_TSK_EV_DIAG_RECOVERY_MSB                               0x02u
# else
#  define DCM_TSK_EV_DIAG_RECOVERY_MSB                               0x00u
# endif

/*! Events of the Dcm_DiagTaskFblRes() */
# if (DCM_TSK_NUM_DIAG_FBLRES > 0u)
#  define DCM_TSK_EV_DIAG_FBLRES_SEND                                ((Dcm_TskTaskEvMemType)0x01u)  /*!< Initiate FBL/APPL final response activity processing */
#  define DCM_TSK_EV_DIAG_FBLRES_CANCEL                              ((Dcm_TskTaskEvMemType)0x02u)  /*!< Cancels any further final response processing */
#  define DCM_TSK_EV_DIAG_FBLRES_WAITTXCOMM                          ((Dcm_TskTaskEvMemType)0x04u)  /*!< Waiting for ComM feedback */
#  define DCM_TSK_EV_DIAG_FBLRES_RSTFLAGS                            ((Dcm_TskTaskEvMemType)0x08u)  /*!< Reset the relevant flags to avoid re-sending of the response next boot */
#  define DCM_TSK_EV_DIAG_FBLRES_TXCONF                              ((Dcm_TskTaskEvMemType)0x10u)  /*!< Final response is sent */
/*! Registers the most significant bit in the event mask of the Dcm_DiagTaskFblRes() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
#  define DCM_TSK_EV_DIAG_FBLRES_MSB                                 0x10u
# else
#  define DCM_TSK_EV_DIAG_FBLRES_MSB                                 0x00u
# endif

/*! Events of the Dcm_DiagTaskTx() */
# define DCM_TSK_EV_DIAG_TX_SEND_LINEAR                              ((Dcm_TskTaskEvMemType)0x01u)  /*!< Initiate final positive response using linear buffer data provision */
# define DCM_TSK_EV_DIAG_TX_SEND_PAGED                               ((Dcm_TskTaskEvMemType)0x02u)  /*!< Initiate final positive response using paged-buffer data provision */
# define DCM_TSK_EV_DIAG_TX_SEND_RCRRP                               ((Dcm_TskTaskEvMemType)0x04u)  /*!< Initiate RCR-RP response transmission */
/*! Registers the most significant bit in the event mask of the Dcm_DiagTaskTx() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
# define DCM_TSK_EV_DIAG_TX_MSB                                      0x04u

/*! Events of the Dcm_NetTaskTx() */
# define DCM_TSK_EV_NET_TX_SEND_USDT                                 ((Dcm_TskTaskEvMemType)0x01u)  /*!< Activate the task by notifying at least one USDT response transmission request is available */
# define DCM_TSK_EV_NET_TX_SEND_UUDT                                 ((Dcm_TskTaskEvMemType)0x02u)  /*!< Activate the task by notifying at least one UUDT response transmission request is available */
/*! Registers the most significant bit in the event mask of the Dcm_NetTaskTx() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
# define DCM_TSK_EV_NET_TX_MSB                                       0x02u

/*! Events of the Dcm_NetTaskRx() */
/*! Registers the most significant bit in the event mask of the Dcm_NetTaskRx() (used by the DCM core to determine the width of the task event registers)
    The MSB depends on the number of transport objects that receive diagnostic messages simultaneously.
    Note: Since used in a preprocessor calculation, do not use casted values */
# define DCM_TSK_EV_NET_RX_MSB                                       (0x01uL << (DCM_NET_MAX_NUM_EVENT_TRANSP_OBJECTS - 1u))

/* DiagGarbCol Task - identical  to Dcm_NetRxTask() */
# define DCM_TSK_EV_DIAG_GARB_COL_MSB                                DCM_TSK_EV_NET_RX_MSB
# define DCM_TSK_EV_DIAG_GARB_COL_MASK                               DCM_TSK_EV_NET_RX_MASK

/*! Events of the Dcm_ModeTaskMonitor() */
# if (DCM_TSK_NUM_MODE_MONITOR > 0u)
#  define DCM_TSK_EV_MODE_MON_SVC85                                  ((Dcm_TskTaskEvMemType)0x01u)  /*!< Initiate monitoring on the auto-recovery mode rule for diagnostic service 0x85 */
#  define DCM_TSK_EV_MODE_MON_SVC28                                  ((Dcm_TskTaskEvMemType)0x02u)  /*!< Initiate monitoring on the auto-recovery mode rule for diagnostic service 0x28 */
/*! Registers the most significant bit in the event mask of the Dcm_ModeTaskMonitor() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
#  define DCM_TSK_EV_MODE_MON_MSB                                    0x02u
# else
#  define DCM_TSK_EV_MODE_MON_MSB                                    0x00u
# endif

/*! Events of the Dcm_Svc2ATaskSchdProcess() */
# if (DCM_TSK_NUM_SVC2A_SCHEDULER > 0u)
#  define DCM_TSK_EV_SVC2A_SCHEDULER_PROCESS                         ((Dcm_TskTaskEvMemType)0x01u)  /*!< At lest one periodic DID timed out and shall be processed */
#  define DCM_TSK_EV_SVC2A_SCHEDULER_TMR_UPD                         ((Dcm_TskTaskEvMemType)0x02u)  /*!< All periodic DID timers shall be updated by one tick */
/*! Registers the most significant bit in the event mask of the Dcm_Svc2ATaskSchdProcess() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
#  define DCM_TSK_EV_SVC2A_SCHEDULER_MSB                             0x02u
# else
#  define DCM_TSK_EV_SVC2A_SCHEDULER_MSB                             0x00u
# endif

/*! Summary of all tasks' event MSB used to calculated the optimal event mask data type (Dcm_TskTaskEvMemType/Dcm_TskTaskEvOptType) */
# define DCM_TSK_EV_SUM_OF_MSB                                       (DCM_TSK_EV_TIMER_MSB | \
                                                                     DCM_TSK_EV_ROE_MSB | \
                                                                     DCM_TSK_EV_DIAG_RX_MSB | \
                                                                     DCM_TSK_EV_DIAG_WORK_MSB | \
                                                                     DCM_TSK_EV_SVC_27_MSB | \
                                                                     DCM_TSK_EV_PGDBUF_MSB | \
                                                                     DCM_TSK_EV_DIAG_FBLRES_MSB |\
                                                                     DCM_TSK_EV_DIAG_TX_MSB | \
                                                                     DCM_TSK_EV_NET_TX_MSB | \
                                                                     DCM_TSK_EV_MODE_MON_MSB | \
                                                                     DCM_TSK_EV_SVC2A_SCHEDULER_MSB | \
                                                                     DCM_TSK_EV_NET_RX_MSB | \
                                                                     DCM_TSK_EV_DIAG_GARB_COL_MSB)

# if (DCM_TSK_EV_SUM_OF_MSB < 0x10000UL)                                                                                                             /* COV_DCM_SUPPORT_ALWAYS TX */
/*! System task event register mask value for up to 16 bits */
#  define DCM_TSK_EV_MASK                                            ((Dcm_TskTaskEvMemType)0xFFFFu)
# else
/*! 64bit platforms not yet considered! */
/*! System task event register mask value for up to 32 bits */
#  define DCM_TSK_EV_MASK                                            ((Dcm_TskTaskEvMemType)0xFFFFFFFFUL)
# endif

/*! All events of a system task event register (e.g. can be used for clearing all events of a task without exactly knowing which task and which events it supports) */
# define DCM_TSK_EV_ALL_EVENTS                                       DCM_TSK_EV_MASK
/*! The diagnostic sub-component internal states
  Note: Bit-mapped states chose, since multiple states can be active at a time (e.g. an still in processing and on transmission for paged-buffer responses) */
# define DCM_DIAG_STATE_IDLE                                         ((Dcm_DiagProcessorStateType)0x00u) /*!< No diagnostic service processing in progress (yet) */
# define DCM_DIAG_STATE_PROCESS                                      ((Dcm_DiagProcessorStateType)0x01u) /*!< A diagnostic request is in processing */
# define DCM_DIAG_STATE_ON_TX                                        ((Dcm_DiagProcessorStateType)0x02u) /*!< A diagnostic response is on transmission */
# define DCM_DIAG_STATE_POST_PROCESS                                 ((Dcm_DiagProcessorStateType)0x04u) /*!< A diagnostic request is in the post-processing phase */
# if (DCM_SVC_19_SUPPORT_ENABLED == STD_ON)
/*! Per default - no patching of DTC status masks required */
#  if !defined(DCM_EXT_SVC19_PATCH_CONTEXT)
#   define DCM_EXT_SVC19_PATCH_CONTEXT                               /* not used */
#  endif
# endif /* (DCM_SVC_19_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
#  if (DCM_DCM_AR_VERSION == DCM_DCM_AR_VERSION_421) || \
      (DCM_DCM_AR_VERSION == DCM_DCM_AR_VERSION_422)
#   define DCM_ROE_AR_STATE_ACTIVE                                   RTE_MODE_DcmResponseOnEvent_EVENT_STARTED
#   define DCM_ROE_AR_STATE_INACTIVE                                 RTE_MODE_DcmResponseOnEvent_EVENT_STOPPED
#   define DCM_ROE_AR_STATE_CLEARED                                  RTE_MODE_DcmResponseOnEvent_EVENT_CLEARED
#   define Dcm_RoEOnEventStateChange(eventId, state)                 (Dcm_ModeSwitchRoE((eventId), (state)))                                         /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  else
#   error "Not supported AR version for RoE!"
#  endif
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
# define Dcm_RepeaterSetUser(pContext, repUser)                      (pContext->Thread->Repeater.Contexts.User = (repUser))                          /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_RepeaterResetOpStatus(pContext)                         (pContext->Thread->Repeater.Contexts.OpStatus = DCM_INITIAL)                    /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

# define Dcm_RepeaterGetProgress(pContext)                           (pContext->Thread->Repeater.Contexts.Progress)                                  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_RepeaterGetSubProgress(pContext)                        (pContext->Thread->Repeater.Contexts.SubProgress)                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_TmrSetTimer(timerId, timerTicks)                        (Dcm_TmrSetTimerByThread((timerId), (timerTicks), DCM_THREAD_ID_BASIC))         /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_TmrStartTimer(timerId, timerTicks)                      (Dcm_TmrStartTimerByThread((timerId), (timerTicks), DCM_THREAD_ID_BASIC))       /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_TmrStopTimer(timerId)                                   (Dcm_TmrStopTimerByThread((timerId), DCM_THREAD_ID_BASIC))                      /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Dcm_TmrResumeTimer(timerId)                                 (Dcm_TmrResumeTimerByThread((timerId), DCM_THREAD_ID_BASIC))                    /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# if (DCM_DEM_API_421_ENABLED == STD_ON) || (DCM_DEM_API_430_ENABLED == STD_ON) || (DCM_DEM_API_431_ENABLED == STD_ON)
#  if (DCM_DEM_API_421_ENABLED == STD_ON)
/*! AR 4.2.1+ DEM API compliant return values */

/*! Return values for Dem_ReturnGetFreezeFrameByDTCType */
#   define DCM_DEM_RET_FFDATABYDTC_OK                                DEM_GET_FFDATABYDTC_OK
#   define DCM_DEM_RET_FFDATABYDTC_W_DTC                             DEM_GET_FFDATABYDTC_WRONG_DTC
#   define DCM_DEM_RET_FFDATABYDTC_W_ORIGIN                          DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN
#   define DCM_DEM_RET_FFDATABYDTC_W_RNUM                            DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER
#   define DCM_DEM_RET_FFDATABYDTC_W_BUFSIZE                         DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE
#   define DCM_DEM_RET_FFDATABYDTC_PENDING                           DEM_GET_FFDATABYDTC_PENDING

/*! Return values for Dcm_DemReturnGetFreezeFrameDataByRecordType */
#   define DCM_DEM_RET_FFBYRECORD_OK                                 E_OK
#   define DCM_DEM_RET_FFBYRECORD_NO_DTC                             E_NOT_OK

/*! Return values for Dcm_DemReturnGetSizeOfFFRByDTCType (ED) */
#   define DCM_DEM_RET_SIZEOFEDR_OK                                  DEM_GETSIZEBYDTC_OK
#   define DCM_DEM_RET_SIZEOFEDR_W_DTC                               DEM_GETSIZEBYDTC_WRONG_DTC
#   define DCM_DEM_RET_SIZEOFEDR_W_ORIGIN                            DEM_GETSIZEBYDTC_WRONG_DTCORIGIN
#   define DCM_DEM_RET_SIZEOFEDR_W_RNUM                              DEM_GETSIZEBYDTC_WRONG_RECNUM
#   define DCM_DEM_RET_SIZEOFEDR_PENDING                             DEM_GETSIZEBYDTC_PENDING

/*! Return values for Dcm_DemReturnGetSizeOfFFRByDTCType (FF) */
#   define DCM_DEM_RET_SIZEOFFFR_OK                                  DEM_GETSIZEBYDTC_OK
#   define DCM_DEM_RET_SIZEOFFFR_W_DTC                               DEM_GETSIZEBYDTC_WRONG_DTC
#   define DCM_DEM_RET_SIZEOFFFR_W_ORIGIN                            DEM_GETSIZEBYDTC_WRONG_DTCORIGIN
#   define DCM_DEM_RET_SIZEOFFFR_W_RNUM                              DEM_GETSIZEBYDTC_WRONG_RECNUM
#   define DCM_DEM_RET_SIZEOFFFR_PENDING                             DEM_GETSIZEBYDTC_PENDING

/*! Return values for Dem_ReturnGetDTCByOccurrenceType */
#   define DCM_DEM_RET_OCCURR_OK                                     DEM_OCCURR_OK
#   define DCM_DEM_RET_OCCURR_NOT_AVAILABLE                          DEM_OCCURR_NOT_AVAILABLE

/*! Return values for Dcm_DemReturnGetNextFilteredElementType */
#   define DCM_DEM_RET_FILTERED_OK                                   DEM_FILTERED_OK
#   define DCM_DEM_RET_FILTERED_NO_ITEMS                             DEM_FILTERED_NO_MATCHING_ELEMENT
#   define DCM_DEM_RET_FILTERED_PENDING                              DEM_FILTERED_PENDING
#   define DCM_DEM_RET_FILTERED_BUFFER_TOO_SMALL                     DEM_FILTERED_BUFFER_TOO_SMALL

/*! Return values for Dcm_DemReturnGetSeverityOfDTCType */
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_OK                        DEM_GET_SEVERITYOFDTC_OK
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_WRONG_DTC                 DEM_GET_SEVERITYOFDTC_WRONG_DTC
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_NOSEVERITY                DEM_GET_SEVERITYOFDTC_NOSEVERITY
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_PENDING                   DEM_GET_SEVERITYOFDTC_PENDING

/*! Return values for Dcm_DemReturnGetFunctionalUnitOfDTCType */
#   define DCM_DEM_RET_GET_FUNCTIONALUNITOFDTC_OK                    DEM_GET_FUNCTIONALUNITOFDTC_OK
#   define DCM_DEM_RET_GET_FUNCTIONALUNITOFDTC_WRONG_DTC             DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC

/*! Return values for Dcm_DemReturnSetFilterType */
#   define DCM_DEM_RET_FILTER_ACCEPTED                               DEM_FILTER_ACCEPTED
#   define DCM_DEM_RET_WRONG_FILTER                                  DEM_WRONG_FILTER

/*! Return values for Dem_ReturnClearDTCType */
#   define DCM_DEM_RET_CLEAR_OK                                      DEM_CLEAR_OK
#   define DCM_DEM_RET_CLEAR_W_DTC                                   DEM_CLEAR_WRONG_DTC
#   define DCM_DEM_RET_CLEAR_W_ORIGIN                                DEM_CLEAR_WRONG_DTCORIGIN
#   define DCM_DEM_RET_CLEAR_FAILED                                  DEM_CLEAR_FAILED
#   define DCM_DEM_RET_CLEAR_PENDING                                 DEM_CLEAR_PENDING
#   define DCM_DEM_RET_CLEAR_CLEAR_BUSY                              DEM_CLEAR_BUSY
#   define DCM_DEM_RET_CLEAR_MEMORY_ERROR                            DEM_CLEAR_MEMORY_ERROR

/*! Return values for Dem_GetStatusOfDTCType */
#   define DCM_DEM_RET_STATUS_OK                                     DEM_STATUS_OK
#   define DCM_DEM_RET_STATUS_PENDING                                DEM_STATUS_PENDING
#   define DCM_DEM_RET_STATUS_WRONG_DTC                              DEM_STATUS_WRONG_DTC
#   define DCM_DEM_RET_STATUS_FAILED                                 DEM_STATUS_FAILED
#   define DCM_DEM_RET_STATUS_WRONG_DTCORIGIN                        DEM_STATUS_WRONG_DTCORIGIN

/* Std_ReturnType */
#   define DCM_DEM_RET_NUMBER_OK                                     DEM_NUMBER_OK
#   define DCM_DEM_RET_NUMBER_PENDING                                DEM_NUMBER_PENDING

/* Dem_ReturnControlDTCSettingType */
#   define DCM_DEM_RET_CONTROL_DTC_SETTING_OK                        DEM_CONTROL_DTC_SETTING_OK
#   define DCM_DEM_RET_CONTROL_DTC_SETTING_N_OK                      DEM_CONTROL_DTC_SETTING_N_OK
#   define DCM_DEM_RET_CONTROL_DTC_WRONG_DTCGROUP                    DEM_CONTROL_DTC_WRONG_DTCGROUP

/* Return values for Dem_ReturnGetExtendedDataRecoredByDTCType */
#   define DCM_DEM_RET_GET_EXT_DATA_REC_OK                           DEM_RECORD_OK
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_DTC                    DEM_RECORD_WRONG_DTC
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_DTCORIGIN              DEM_RECORD_WRONG_DTCORIGIN
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_NUMBER                 DEM_RECORD_WRONG_NUMBER
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_BUFFERSIZE             DEM_RECORD_WRONG_BUFFERSIZE
#   define DCM_DEM_RET_GET_EXT_DATA_REC_PENDING                      DEM_RECORD_PENDING

#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_OK                         DEM_DISABLE_DTCRECUP_OK
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_WRONG_DTC                  DEM_DISABLE_DTCRECUP_WRONG_DTC
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_WRONG_DTCORIGIN            DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_PENDING                    DEM_DISABLE_DTCRECUP_PENDING

#   define DCM_DEM_FILTER_FOR_FDC_NO                                 DEM_FILTER_FOR_FDC_NO
#   define DCM_DEM_FILTER_FOR_FDC_YES                                DEM_FILTER_FOR_FDC_YES
#   define DCM_DEM_FILTER_WITH_SEVERITY_NO                           DEM_FILTER_WITH_SEVERITY_NO
#   define DCM_DEM_FILTER_WITH_SEVERITY_YES                          DEM_FILTER_WITH_SEVERITY_YES

/*! AR 4.2.1 DEM API compliant return types */
#   define Dcm_DemFilterForFDCType                                   Dem_FilterForFDCType
#   define Dcm_DemFilterWithSeverityType                             Dem_FilterWithSeverityType
#   define Dcm_DemReturnClearDTCType                                 Dem_ReturnClearDTCType
#   define Dcm_DemReturnControlDTCSettingType                        Dem_ReturnControlDTCSettingType
#   define Dcm_DemReturnDisableDTCRecordUpdateType                   Dem_ReturnDisableDTCRecordUpdateType
#   define Dcm_DemReturnGetDTCByOccurrenceTimeType                   Dem_ReturnGetDTCByOccurrenceTimeType
#   define Dcm_DemReturnGetFreezeFrameDataByRecordType               Std_ReturnType
#   define Dcm_DemReturnGetFunctionalUnitOfDTCType                   Dem_ReturnGetFunctionalUnitOfDTCType
#   define Dcm_DemReturnGetNextFilteredElementType                   Dem_ReturnGetNextFilteredElementType
#   define Dcm_DemReturnGetNextFilteredItemType                      Dem_ReturnGetNextFilteredElementType
#   define Dcm_DemReturnGetNumberOfFilteredDTCType                   Dem_ReturnGetNumberOfFilteredDTCType
#   define Dcm_DemReturnGetSeverityOfDTCType                         Dem_ReturnGetSeverityOfDTCType
#   define Dcm_DemReturnGetSizeOfDataByDTCType                       Dem_ReturnGetSizeOfDataByDTCType
#   define Dcm_DemReturnGetSizeOfEDRByDTCType                        Dem_ReturnGetSizeOfDataByDTCType
#   define Dcm_DemReturnGetSizeOfFFRByDTCType                        Dem_ReturnGetSizeOfDataByDTCType
#   define Dcm_DemReturnGetStatusOfDTCType                           Dem_ReturnGetStatusOfDTCType
#   define Dcm_DemReturnSetFilterType                                Dem_ReturnSetFilterType

/*! AR 4.2.1 DEM API function name substitutions - generic rename */
#   define Dcm_DemAPI(name)                                          Dem_Dcm ## name                                                                 /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */

/*! AR 4.2.1 DEM API function name substitutions - special cases */
#   define Dcm_DemAPI_CancelOperation                                Dem_DcmCancelOperation
#   define Dcm_DemAPI_GetOBDFreezeFrameData(recNum, dtcOrigin, dtc, buffer, bufferSize) (Dem_DcmGetOBDFreezeFrameData((dtc), (buffer), (bufferSize))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#   define Dcm_DemAPI_ControlDTCStatusChangedNotification(active)    Dem_DcmControlDTCStatusChangedNotification((active))                            /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  elif (DCM_DEM_API_430_ENABLED == STD_ON) || (DCM_DEM_API_431_ENABLED == STD_ON)                                                                   /* COV_DCM_SUPPORT_ALWAYS TX tf tf*/
/* return values */

/* Define DEM_BUSY here, because DEM_BUSY is not supported by older versions of MICROSAR DEM. */
#   ifndef DEM_BUSY
#    define DEM_BUSY                                                 ((Std_ReturnType)(22U))
#   endif

/* Std_ReturnType */
#   define DCM_DEM_RET_FFDATABYDTC_OK                                E_OK
#   define DCM_DEM_RET_FFDATABYDTC_W_DTC                             DEM_WRONG_DTC
#   define DCM_DEM_RET_FFDATABYDTC_W_ORIGIN                          DEM_WRONG_DTCORIGIN
#   define DCM_DEM_RET_FFDATABYDTC_W_RNUM                            DEM_NO_SUCH_ELEMENT
#   define DCM_DEM_RET_FFDATABYDTC_W_BUFSIZE                         DEM_BUFFER_TOO_SMALL
#   define DCM_DEM_RET_FFDATABYDTC_PENDING                           DEM_PENDING

/* Std_ReturnType */
#   define DCM_DEM_RET_FFBYRECORD_OK                                 E_OK
#   define DCM_DEM_RET_FFBYRECORD_NO_DTC                             E_NOT_OK

/* Std_ReturnType */
#   define DCM_DEM_RET_SIZEOFEDR_OK                                  E_OK
#   define DCM_DEM_RET_SIZEOFEDR_N_OK                                E_NOT_OK
#   define DCM_DEM_RET_SIZEOFEDR_W_DTC                               DEM_WRONG_DTC
#   define DCM_DEM_RET_SIZEOFEDR_W_ORIGIN                            DEM_WRONG_DTCORIGIN
#   define DCM_DEM_RET_SIZEOFEDR_W_RNUM                              DEM_NO_SUCH_ELEMENT
#   define DCM_DEM_RET_SIZEOFEDR_PENDING                             DEM_PENDING

/* Std_ReturnType */
#   define DCM_DEM_RET_SIZEOFFFR_OK                                  E_OK
#   define DCM_DEM_RET_SIZEOFFFR_N_OK                                E_NOT_OK
#   define DCM_DEM_RET_SIZEOFFFR_W_DTC                               DEM_WRONG_DTC
#   define DCM_DEM_RET_SIZEOFFFR_W_ORIGIN                            DEM_WRONG_DTCORIGIN
#   define DCM_DEM_RET_SIZEOFFFR_W_RNUM                              DEM_NO_SUCH_ELEMENT
#   define DCM_DEM_RET_SIZEOFFFR_PENDING                             DEM_PENDING

/* Std_ReturnType */
#   define DCM_DEM_RET_OCCURR_OK                                     E_OK
#   define DCM_DEM_RET_OCCURR_N_OK                                   E_NOT_OK
#   define DCM_DEM_RET_OCCURR_NO_SUCH_ELEMENT                        DEM_NO_SUCH_ELEMENT

/* Std_ReturnType */
#   define DCM_DEM_RET_FILTERED_OK                                   E_OK
#   define DCM_DEM_RET_FILTERED_NO_ITEMS                             DEM_NO_SUCH_ELEMENT
#   define DCM_DEM_RET_FILTERED_PENDING                              DEM_PENDING
#   define DCM_DEM_RET_FILTERED_BUFFER_TOO_SMALL                     DEM_BUFFER_TOO_SMALL

/* Std_ReturnType */
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_OK                        E_OK
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_WRONG_DTC                 DEM_WRONG_DTC
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_WRONG_DTCORIGIN           DEM_WRONG_DTCORIGIN
/* # define DCM_DEM_RET_GET_SEVERITY_OF_DTC_NOSEVERITY */            /* not used anymore */
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_PENDING                   DEM_PENDING
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_BUSY                      DEM_BUSY

/* Std_ReturnType */
#   define DCM_DEM_RET_GET_FUNCTIONALUNITOFDTC_OK                    E_OK
#   define DCM_DEM_RET_GET_FUNCTIONALUNITOFDTC_PENDING               DEM_PENDING
#   define DCM_DEM_RET_GET_FUNCTIONALUNITOFDTC_WRONG_DTC             DEM_WRONG_DTC
#   define DCM_DEM_RET_GET_FUNCTIONALUNITOFDTC_WRONG_DTCORIGIN       DEM_WRONG_DTCORIGIN
#   define DCM_DEM_RET_GET_FUNCTIONALUNITOFDTC_BUSY                  DEM_BUSY

/* Std_ReturnType */
#   define DCM_DEM_RET_FILTER_ACCEPTED                               E_OK
#   define DCM_DEM_RET_WRONG_FILTER                                  E_NOT_OK

/* Std_ReturnType */
#   define DCM_DEM_RET_SELECT_BUSY                                   DEM_BUSY

/* Std_ReturnType */
#   define DCM_DEM_RET_SELECT_EXT_DATAREC_OK                         E_OK
#   define DCM_DEM_RET_SELECT_EXT_DATAREC_BUSY                       DEM_BUSY

/* Std_ReturnType */
#   define DCM_DEM_RET_SELECT_FF_DATA_OK                             E_OK
#   define DCM_DEM_RET_SELECT_FF_DATA_BUSY                           DEM_BUSY

/* Std_ReturnType */
#   define DCM_DEM_RET_CLEAR_OK                                      E_OK
#   define DCM_DEM_RET_CLEAR_PENDING                                 DEM_PENDING
#   define DCM_DEM_RET_CLEAR_CLEAR_BUSY                              DEM_CLEAR_BUSY
#   define DCM_DEM_RET_CLEAR_BUSY                                    DEM_BUSY
#   define DCM_DEM_RET_CLEAR_MEMORY_ERROR                            DEM_CLEAR_MEMORY_ERROR
#   define DCM_DEM_RET_CLEAR_FAILED                                  DEM_CLEAR_FAILED
#   define DCM_DEM_RET_CLEAR_W_DTC                                   DEM_WRONG_DTC
#   define DCM_DEM_RET_CLEAR_W_ORIGIN                                DEM_WRONG_DTCORIGIN

/* Std_ReturnType */
#   define DCM_DEM_RET_STATUS_OK                                     E_OK
#   define DCM_DEM_RET_STATUS_PENDING                                DEM_PENDING
#   define DCM_DEM_RET_STATUS_WRONG_DTC                              DEM_WRONG_DTC
#   define DCM_DEM_RET_STATUS_WRONG_DTCORIGIN                        DEM_WRONG_DTCORIGIN
#   define DCM_DEM_RET_STATUS_NO_SUCH_ELEMENT                        DEM_NO_SUCH_ELEMENT
#   define DCM_DEM_RET_STATUS_BUSY                                   DEM_BUSY
/* # define DCM_DEM_RET_STATUS_FAILED */                             /* not used anymore */

/* Std_ReturnType */
#   define DCM_DEM_RET_NUMBER_OK                                     E_OK
#   define DCM_DEM_RET_NUMBER_PENDING                                DEM_PENDING

/* Std_ReturnType */
#   define DCM_DEM_RET_CONTROL_DTC_SETTING_OK                        E_OK
#   define DCM_DEM_RET_CONTROL_DTC_SETTING_PENDING                   DEM_PENDING

/* Return values for Dem_ReturnGetExtendedDataRecoredByDTCType */
#   define DCM_DEM_RET_GET_EXT_DATA_REC_OK                           E_OK
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_DTC                    DEM_WRONG_DTC
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_DTCORIGIN              DEM_WRONG_DTCORIGIN
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_NUMBER                 DEM_NO_SUCH_ELEMENT
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_BUFFERSIZE             DEM_BUFFER_TOO_SMALL
#   define DCM_DEM_RET_GET_EXT_DATA_REC_PENDING                      DEM_PENDING

#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_OK                         E_OK
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_WRONG_CONDITION            DEM_E_WRONG_CONDITION
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_WRONG_DTC                  DEM_WRONG_DTC
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_WRONG_DTCORIGIN            DEM_WRONG_DTCORIGIN
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_PENDING                    DEM_PENDING
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_BUSY                       DEM_BUSY

#   define DCM_DEM_FILTER_FOR_FDC_NO                                 FALSE
#   define DCM_DEM_FILTER_FOR_FDC_YES                                TRUE
#   define DCM_DEM_FILTER_WITH_SEVERITY_NO                           FALSE
#   define DCM_DEM_FILTER_WITH_SEVERITY_YES                          TRUE

/* types */
#   define Dcm_DemFilterForFDCType                                   boolean
#   define Dcm_DemFilterWithSeverityType                             boolean
#   define Dcm_DemReturnClearDTCType                                 Std_ReturnType
#   define Dcm_DemReturnControlDTCSettingType                        Std_ReturnType
#   define Dcm_DemReturnDisableDTCRecordUpdateType                   Std_ReturnType
#   define Dcm_DemReturnGetDTCByOccurrenceTimeType                   Std_ReturnType
#   define Dcm_DemReturnGetFreezeFrameDataByRecordType               Std_ReturnType
#   define Dcm_DemReturnGetFunctionalUnitOfDTCType                   Std_ReturnType
#   define Dcm_DemReturnGetNextFilteredElementType                   Std_ReturnType
#   define Dcm_DemReturnGetNextFilteredItemType                      Std_ReturnType
#   define Dcm_DemReturnGetNumberOfFilteredDTCType                   Std_ReturnType
#   define Dcm_DemReturnGetSeverityOfDTCType                         Std_ReturnType
#   define Dcm_DemReturnGetSizeOfDataByDTCType                       Std_ReturnType
#   define Dcm_DemReturnGetSizeOfEDRByDTCType                        Dcm_DemReturnGetSizeOfDataByDTCType
#   define Dcm_DemReturnGetSizeOfFFRByDTCType                        Dcm_DemReturnGetSizeOfDataByDTCType
#   define Dcm_DemReturnGetStatusOfDTCType                           Std_ReturnType
#   define Dcm_DemReturnSetFilterType                                Std_ReturnType
#   define Dcm_DemReturnSelectExtRecordType                          Std_ReturnType
#   define Dcm_DemReturnSelectFFDataType                             Std_ReturnType

/* functions - generic rename */
#   define Dcm_DemAPI(name)                                          Dem_ ## name                                                                    /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */

/* functions - special cases */
#   define Dcm_DemAPI_CancelOperation()                              /* Not used */
#   define Dcm_DemAPI_GetOBDFreezeFrameData(recNum, dtcOrigin, dtc, buffer, bufferSize) (Dem_DcmGetOBDFreezeFrameData((dtc), (buffer), (bufferSize))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#   define Dcm_DemAPI_ControlDTCStatusChangedNotification(active)    /* Not used */
#  else
#   error "Unknown DEM AR API interface!"
#  endif
# endif /* (DCM_DEM_API_421_ENABLED == STD_ON) || (DCM_DEM_API_430_ENABLED == STD_ON) || (DCM_DEM_API_431_ENABLED == STD_ON) */
/*! Tests whether at least one event specified by ev is set in task local register evReg */
# define Dcm_TskIsLocalEventSet(evReg, ev)                           (Dcm_UtiBitOpTest(Dcm_TskTaskEvMemType, (evReg), (ev)))                         /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Sets task local event(s) (for global setting use Dcm_TskSetEvent()) */
# define Dcm_TskSetLocalEvent(evReg, ev)                             (Dcm_UtiBitOpSet( Dcm_TskTaskEvMemType, (evReg), (ev)))                         /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Clears task local event(s) (for global clearing use Dcm_TskClrEvent()) */
# define Dcm_TskClrLocalEvent(evReg, ev)                             (Dcm_UtiBitOpClr( Dcm_TskTaskEvMemType, (evReg), (ev)))                         /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! A generic task event scanner/iterator */
# define DCM_TSK_EVENT_SCAN_LOOP(evReg)                              DCM_UTI_LOOP_BIT_SCAN(evReg)                                                    /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Sets task event(s) but with thread 0 as its attribute is DCM_TSK_ATR_THREAD_SINGLE */
# define Dcm_TskSetEvent(taskId, ev)                                 (Dcm_TskSetEventByThread((taskId), (ev), DCM_THREAD_ID_BASIC))                  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Clears task event(s) but with thread 0 as its attribute is DCM_TSK_ATR_THREAD_SINGLE */
# define Dcm_TskClrEvent(taskId, ev)                                 (Dcm_TskClrEventByThread((taskId), (ev), DCM_THREAD_ID_BASIC))                  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Returns the current events of a specific task but with thread 0 */
# define Dcm_TskGetEvent(taskId)                                     (Dcm_TskGetEventByThread((taskId), DCM_THREAD_ID_BASIC))                        /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Pointer to a execution precondition reference index located in the DCM ROM data */
typedef P2CONST(Dcm_CfgStateRefMemType, TYPEDEF, DCM_CONST)  Dcm_CfgStateRefMemPtrType;

/*! Control data of the sub-component state manager */
struct DCM_STATECONTEXTTYPE_TAG
{
  Dcm_CfgStateDiagStateInfoType Preconditions;   /*!< Current (active) state of all diagnostic state related execution pre-conditions */
  Dcm_CfgStateGroupMemType      PendingSession;  /*!< Pending diagnostic session, still in transition, waiting for the diagnostic service processing confirmation */
};
typedef struct DCM_STATECONTEXTTYPE_TAG Dcm_StateContextType;
/*! Variant reference data type (derived from the execution precondition references since it is part of the pre-conditions and located in the same table) */
typedef Dcm_CfgStateRefMemPtrType  Dcm_VarRefMemPtrType;
# if (DCM_STATE_SECURITY_FIXED_BYTES_ENABLED == STD_ON)  &&  \
     (DCM_VARMGR_MULTI_SVC_INCLUSIVE_ENABLED == STD_ON)
typedef uint32 Dcm_VsgSizeType;
# endif

# if (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON)
typedef uint8 Dcm_MemMgrMemoryOpType;
# endif /* (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON) */
# if (DCM_FBLMGR_SUPPORT_ENABLED == STD_ON)
/* Download control data */
typedef uint8 Dcm_FblMgrMidType;
typedef uint8 Dcm_FblMgrDownloadStateType;
typedef uint8 Dcm_FblMgrBlockSequenceCounterType;
typedef uint8 Dcm_FblMgrDataFormatIdType;
typedef uint32 Dcm_FblMgrBlockLengthType;
typedef uint32 Dcm_FblMgrMemoryAddressType;
typedef uint32 Dcm_FblMgrMemorySizeType;

struct DCM_FBLMGRMEMBLOCKTYPE_TAG
{
  Dcm_FblMgrMemoryAddressType  Address;  /*!< The address to access */
  Dcm_FblMgrMemorySizeType     Length;   /*!< The number of bytes requested */
  Dcm_FblMgrMidType            Mid;      /*!< The memory identifier */
};
typedef struct DCM_FBLMGRMEMBLOCKTYPE_TAG Dcm_FblMgrMemBlockType;
typedef P2VAR(Dcm_FblMgrMemBlockType, TYPEDEF, DCM_VAR_NOINIT)   Dcm_FblMgrMemBlockPtrType;
# endif /* (DCM_FBLMGR_SUPPORT_ENABLED == STD_ON) */
# if (DCM_OBDIDMGR_SUPPORT_ENABLED == STD_ON)
/*! Request parser temporary processing context */
struct DCM_OBDIDMGRDESCTYPE_TAG
{
  Dcm_Uint8ConstDataPtrType    LookUpTable;         /*!< IN: The OBD ID lookup table */
  Dcm_VarRefMemPtrType         LookUpFilterTable;   /*!< IN: List of OBD ID related filters */
  Dcm_ObdMaskConstDataPtrType  MaskData;            /*!< IN: The calibrated OBD ID mask */
  Dcm_ObdIdMgrHandleMemType    Handle;              /*!< OUT: ID specific handle */
};
typedef struct DCM_OBDIDMGRDESCTYPE_TAG Dcm_ObdIdMgrDescType;
typedef P2VAR(Dcm_ObdIdMgrDescType, TYPEDEF, DCM_VAR_NOINIT) Dcm_ObdIdMgrDescPtrType;
# endif /* (DCM_OBDIDMGR_SUPPORT_ENABLED == STD_ON) */
typedef uint8 Dcm_RepeaterProgressType;
typedef uint8 Dcm_RepeaterUserType;
# if (DCM_OBDDTCMGR_SUPPORT_ENABLED == STD_ON)
/*! OBD DTC manager temporary processing context */
struct DCM_OBDDTCMANAGERCONTEXTTYPE_TAG
{
  Dcm_RepeaterProgressType  DcmObdDtcManagerProgress; /*!< Repeater progress state */
  uint8                     DemClientId;              /*!< DEM ClientId */
};
typedef struct DCM_OBDDTCMANAGERCONTEXTTYPE_TAG Dcm_ObdDtcManagerContextType;
typedef P2VAR(Dcm_ObdDtcManagerContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_ObdDtcManagerContextPtrType;
# endif /* (DCM_OBDDTCMGR_SUPPORT_ENABLED == STD_ON) */
/*! Control data for diagnostic service post-processing */
struct DCM_DIAGPOSTPROCESSORCONTEXTTYPE_TAG
{
  uint16 SrcAddr; /*!< Source address */
  uint8  Sid;     /*!< Service identifier */
  uint8  ReqType; /*!< Request type (physical/functional) */
};
typedef struct DCM_DIAGPOSTPROCESSORCONTEXTTYPE_TAG Dcm_DiagPostProcessorContextType;
/*! A sub-service length (i.e. sub-function and eventually some data byte) must always fit the linear buffer size (no paged-buffer request reception) */
typedef Dcm_CfgNetBufferSizeMemType Dcm_DiagSubServiceLengthType;
typedef P2VAR(Dcm_DiagSubServiceRefOptType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_DiagSubServiceRefOptPtrType;
/*! Base data type for the diagnostic sub-component internal state machine */
typedef uint8 Dcm_DiagProcessorStateType;
# if (DCM_SVC_01_SUPPORT_ENABLED == STD_ON)
/*! Service 0x01 temporary processing context */
struct DCM_SVC01REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_ObdIdMgrDescType    ParserDesc;  /*!< Parser Descriptor */
};
typedef struct DCM_SVC01REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc01RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc01RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_Svc01RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_01_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_02_SUPPORT_ENABLED == STD_ON)
/*! Service 0x02 temporary processing context */
struct DCM_SVC02REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_ObdIdMgrDescType      ParserDesc;   /*!< Parser Descriptor */
  uint8                     DemClientId;  /*!< DEM ClientId */
};
typedef struct DCM_SVC02REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc02RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc02RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc02RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_02_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_03_SUPPORT_ENABLED == STD_ON)
/*! Service 0x03 temporary processing context */
struct DCM_SVC03REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_ObdDtcManagerContextType  ReadDtcContext; /*!< OBD DTC manager processing context */
};
typedef struct DCM_SVC03REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc03RepeaterProxyContextType;
# endif /* (DCM_SVC_03_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_04_SUPPORT_ENABLED == STD_ON)
/*! Service 0x04 temporary processing context */
struct DCM_SVC04REPEATERPROXYCONTEXTTYPE_TAG
{
  uint8 DemClientId;  /*!< Dem Client Id */
};
typedef struct DCM_SVC04REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc04RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc04RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc04RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_04_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_06_SUPPORT_ENABLED == STD_ON) && (DCM_OBDIDMGR_OBDMID_SUPPORT_BY_DEM_ENABLED == STD_ON)
/*! Service 0x06 temporary processing context */
struct DCM_SVC06REPEATERPROXYCONTEXTTYPE_TAG
{
  uint8 Spare; /*!< Currently not used */
};
typedef struct DCM_SVC06REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc06RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc06RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc06RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_06_SUPPORT_ENABLED == STD_ON) && (DCM_OBDIDMGR_OBDMID_SUPPORT_BY_DEM_ENABLED == STD_ON) */
# if (DCM_SVC_06_SUPPORT_ENABLED == STD_ON) && (DCM_OBDIDMGR_OBDMID_SUPPORT_BY_DCM_ENABLED == STD_ON)
/*! Service 0x06 temporary processing context */
struct DCM_SVC06REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_ObdIdMgrDescType    ParserDesc; /*!< OBD request parser context */
};
typedef struct DCM_SVC06REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc06RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc06RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc06RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_06_SUPPORT_ENABLED == STD_ON) && (DCM_OBDIDMGR_OBDMID_SUPPORT_BY_DCM_ENABLED == STD_ON) */
# if (DCM_SVC_07_SUPPORT_ENABLED == STD_ON)
/*! Service 0x07 temporary processing context */
struct DCM_SVC07REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_ObdDtcManagerContextType  ReadDtcContext;  /*!< OBD DTC manager processing context */
};
typedef struct DCM_SVC07REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc07RepeaterProxyContextType;
# endif /* (DCM_SVC_07_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_08_SUPPORT_ENABLED == STD_ON)
/*! Service 0x08 temporary processing context */
struct DCM_SVC08REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_ObdIdMgrDescType    ParserDesc;  /*!< Request parser processing context data */
};
typedef struct DCM_SVC08REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc08RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc08RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_Svc08RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_08_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_09_SUPPORT_ENABLED == STD_ON)
/*! Service 0x09 temporary processing context */
struct DCM_SVC09REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_ObdIdMgrDescType ParserDesc; /*!< Parser Descriptor */
};
typedef struct DCM_SVC09REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc09RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc09RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc09RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_09_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_0A_SUPPORT_ENABLED == STD_ON)
/*! Service 0x0A temporary processing context */
struct DCM_SVC0AREPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_ObdDtcManagerContextType  ReadDtcContext;  /*!< OBD DTC manager processing context */
};
typedef struct DCM_SVC0AREPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc0ARepeaterProxyContextType;
# endif /* (DCM_SVC_0A_SUPPORT_ENABLED == STD_ON) */
/*! Service 0x10 temporary processing context */
struct DCM_SVC10REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_StateIndexMemType     SesStateIdx;             /*!< Requested new Session State to execute transition in post processor */
# if (DCM_SVC_10_JMP2BOOT_ENABLED == STD_ON)
  Dcm_ProgConditionsType    ProgConditions;          /*!< Programming condition for further processing steps */
  Rte_ModeType_DcmEcuReset  ResetMode;               /*!< Reset mode for Ecu reset */
# endif
};
typedef struct DCM_SVC10REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc10RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc10RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc10RepeaterProxyContextPtrType;
# if (DCM_SVC_11_SUPPORT_ENABLED == STD_ON)
/*! Service 0x11 temporary processing context */
struct DCM_SVC11REPEATERPROXYCONTEXTTYPE_TAG
{
  uint8                          SubFuncId;  /*!< Sub-function ID of the current request */
  Dcm_DiagSubServiceRefMemType   SubSvcRef;  /*!< Reference to Dcm_CfgSvc11SubFuncInfo[] entry */
};
typedef struct DCM_SVC11REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc11RepeaterProxyContextType;

typedef P2CONST(Dcm_CfgSvc11SubFuncInfoType, TYPEDEF, DCM_CONST)   Dcm_CfgSvc11SubFuncInfoPtrType;
typedef P2VAR(Dcm_Svc11RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc11RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_11_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_14_SUPPORT_ENABLED == STD_ON)
/*! Service 0x14 temporary processing context */
struct DCM_SVC14REPEATERPROXYCONTEXTTYPE_TAG
{
  uint32   Dtc;         /*!< Requested DTC for futher DEM interaction */
  uint8    DemClientId; /*!< DEM ClientId */
};
typedef struct DCM_SVC14REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc14RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc14RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc14RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_14_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_19_SUPPORT_ENABLED == STD_ON)
/*! Service 0x19 temporary processing context */
struct DCM_19_REPEATERPROXYCONTEXTTYPE_TAG
{
  P2CONST(Dcm_RepeaterProgressType, TYPEDEF, DCM_CONST)  FuncChain;     /*!< Pointer to valid list of processing DEM API list */
#  if (DCM_SVC_19_RECORD_ITER_ENABLED == STD_ON)
  Dcm_Uint8ConstDataPtrType                              RecordNumList; /*!< Pointer to DEM (extended/freeze-frame) record list */
#  endif
  uint32                                                 Dtc;           /*!< Requested DTC for futher DEM interaction */
  uint16                                                 NumDtc;        /*!< Read number of DTCs reported by DEM to be passed to next processing stage */
  Dem_DTCOriginType                                      Origin;        /*!< Requested DTC origin */
  uint8                                                  SubUpdater;    /*!< Current paged-buffer updater within this diagnostic service */
  uint8                                                  RecordNum;     /*!< Either the requested or next record number to be read out from DEM */
  Dcm_DiagSubServiceRefMemType                           SubSvcRef;     /*!< A validly dispatched sub-function requested for this diagnostic service */
  uint8                                                  DemClientId;   /*!< DEM ClientId */
  DCM_EXT_SVC19_PATCH_CONTEXT                                           /*!< A placeholder for optional on the fly DTC report patching (applicable in some specific customer requirements) */
};
typedef struct DCM_19_REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc19RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc19RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc19RepeaterProxyContextPtrType;
typedef P2CONST(Dcm_Svc19RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc19RepeaterProxyContextConstPtrType;
# endif /* (DCM_SVC_19_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_22_SUPPORT_ENABLED == STD_ON)
/*! Service 0x22 temporary processing context */
struct DCM_SVC22REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_DidMgrDidInfoContextType     DidInfoContextList[DCM_SVC_22_MAX_DID_LIST_LEN];  /*!< Array of DidInfoContext */
  Dcm_DidMgrDidOpTypeContextType   DidOpTypeContext;                                 /*!< Did configuration operation context */
  Dcm_MsgLenType                   ActualLength;                                     /*!< Actual response data length  */
  Dcm_MsgLenType                   ReservedLength;                                   /*!< Reserved buffer size needed for reading the data */
  uint8                            DidInfoContextIdx;                                /*!< Reference to DidInfoContextList[] entry */
  uint8                            NumDids;                                          /*!< Number of Dids to process */
  uint8                            DidIter;                                          /*!< Current Did to process */
};
typedef struct DCM_SVC22REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc22RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc22RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc22RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_22_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_23_SUPPORT_ENABLED == STD_ON)
/*! Service 0x23 temporary processing context */
struct DCM_SVC23REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_MemMgrMemBlockType  MemBlock;  /*!< Memory block descriptor */
};
typedef struct DCM_SVC23REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc23RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc23RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)    Dcm_Svc23RepeaterProxyContextPtrType;
typedef P2CONST(Dcm_Svc23RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc23RepeaterProxyContextConstPtrType;
# endif /* (DCM_SVC_23_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_24_SUPPORT_ENABLED == STD_ON)
/*! Service 0x24 temporary processing context */
struct DCM_SVC24REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_DidMgrDidInfoContextType      DidInfoContext;    /*!< DidInfoContext */
  Dcm_DidMgrDidOpTypeContextType    DidOpTypeContext;  /*!< Did configuration operation context */
};
typedef struct DCM_SVC24REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc24RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc24RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc24RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_24_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_27_SUPPORT_ENABLED == STD_ON)
/*! Service 0x27 temporary processing context */
struct DCM_SVC27REPEATERPROXYCONTEXTTYPE_TAG
{
  boolean                       IsZeroSeed;  /*!< Inidication for zero seed (unloced security level) */
  Dcm_DiagSubServiceRefMemType  SubSvcRef;   /*!< Reference to Dcm_CfgSvc27SubFuncInfo[] entry */
  uint8                         SecLvlRef;   /*!< Reference to Dcm_CfgSvc27SecLevelInfo[] entry */
  Dcm_NegativeResponseCodeType  ErrorCode;   /*!< Error code */
};
typedef struct DCM_SVC27REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc27RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc27RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc27RepeaterProxyContextPtrType;
typedef P2CONST(Dcm_Svc27RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc27RepeaterProxyContextConstPtrType;
# endif /* (DCM_SVC_27_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_28_SUPPORT_ENABLED == STD_ON)
/*! Service 0x28 temporary processing context */
struct DCM_SVC28REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_CommunicationModeType     ComMode;               /*!< Calculated CommunicationControl ModeDeclarationGroup mode value of the current service request */
  Dcm_CfgNetNetIdRefMemType     NetworkRef;            /*!< ComM channel of the current service request */
  uint8                         SubServiceId;          /*!< Sub-function ID of the current service request */
  boolean                       IsInternallyProcessed; /*!< Specifies whether the processed sub-function is internally handled (TRUE) or within application code (FALSE)*/
  Dcm_DiagSubServiceRefMemType  SubSvcRef;             /*!< A validly dispatched sub-function requested for this diagnostic service */
};
typedef struct DCM_SVC28REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc28RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc28RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc28RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_28_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_29_SUPPORT_ENABLED == STD_ON)
/*! Service 0x29 temporary processing context */
struct DCM_SVC29REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_AuthMgrConnContextType    ConnContext;          /*!< Connection specific context */
  KeyM_CertElementIteratorType  CertElementIterator;  /*!< Iteratorator for accessing certificate elements */
  Dcm_DiagSubServiceRefMemType  SubSvcRef;            /*!< Reference to Dcm_CfgSvc29SubFuncInfo[] entry */
  Dcm_CfgNetAuthInfoRefMemType  AuthInfoHdl;          /*!< Reference to Dcm_CfgAuthMgrNetConnInfo[] entry */
  uint8                         SubFuncId;            /*!< Subfunction id for this context */
};
typedef struct DCM_SVC29REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc29RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc29RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc29RepeaterProxyContextPtrType;
typedef P2CONST(Dcm_Svc29RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc29RepeaterProxyContextConstPtrType;
# endif /* (DCM_SVC_29_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_2A_SUPPORT_ENABLED == STD_ON)
typedef uint8 Dcm_Svc2ATransmissionModeType;

/*! Service 0x2A temporary processing context */
struct DCM_SVC2AREPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_DidMgrDidInfoContextType    DidInfoContext;          /*!< Info context of the currently requested DID */
  Dcm_DidMgrDidOpTypeContextType  DidOpTypeContext;        /*!< Operation type context of the currently requested DID */
  Dcm_NetConnRefMemType           ConnHdl;                 /*!< Reference to Dcm_CfgNetConnectionInfo[] entry */
  Dcm_Svc2ATransmissionModeType   UdsRate;                 /*!< Requested UDS rate */
  boolean                         HasAnySupportedDids;     /*!< Flag whether current request contains a supported DID */
};
typedef struct DCM_SVC2AREPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc2ARepeaterProxyContextType;
typedef P2VAR(Dcm_Svc2ARepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_Svc2ARepeaterProxyContextPtrType;
# endif /* (DCM_SVC_2A_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_2C_SUPPORT_ENABLED == STD_ON)
/*! Service 0x2C temporary processing context */
struct DCM_SVC2CREPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_DidMgrDidInfoContextType           DynDidInfoContext;      /*!< DynDID info context */
  Dcm_DidMgrDidInfoContextType           SrcItemDidInfoContext;  /*!< Source item DID info context */
  Dcm_DidMgrDidOpTypeContextType         DynDidOpTypeContext;    /*!< DynDID operation type context */
  Dcm_CfgDidMgrDynDidSrcItemIdxMemType   SrcItemIndex;           /*!< Index of currently processed source item */
  Dcm_CfgDidMgrDynDidHandleMemType       DynDidHandle;           /*!< Handle of the currently processed DynDID */
  Dcm_DidMgrDidLengthType                MaxAllowedLength;       /*!< Maximum allowed response length (depending on the protocol) */
  Dcm_DidMgrDidLengthType                DynDidLength;           /*!< Length of the DynDID */
  uint8                                  DynDidItemCount;        /*!< Number of source items in current request */
  uint8                                  ReqNumOfItems;          /*!< Number of requested items that are not yet processed */
  Dcm_DiagSubServiceRefMemType           SubSvcRef;              /*!< Index of the requested subfunction */
};
typedef struct DCM_SVC2CREPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc2CRepeaterProxyContextType;
typedef P2VAR(Dcm_Svc2CRepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_Svc2CRepeaterProxyContextPtrType;
typedef P2CONST(Dcm_Svc2CRepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_Svc2CRepeaterProxyContextConstPtrType;
# endif /* (DCM_SVC_2C_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_2E_SUPPORT_ENABLED == STD_ON)
/*! Service 0x2E temporary processing context */
struct DCM_SVC2EREPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_DidMgrDidInfoContextType       DidInfoContext;     /*!< Did configuration information context */
  Dcm_DidMgrDidOpTypeContextType     DidOpTypeContext;   /*!< Did configuration operation context */
};
typedef struct DCM_SVC2EREPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc2ERepeaterProxyContextType;
typedef P2VAR(Dcm_Svc2ERepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc2ERepeaterProxyContextPtrType;
# endif /* (DCM_SVC_2E_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_2F_SUPPORT_ENABLED == STD_ON)
/*! Repeater context for the handling of a 2F request */
struct DCM_SVC2FREPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_DidMgrDidInfoContextType    DidInfoContext;   /*!< DID information context */
  Dcm_DidMgrDidOpTypeContextType  DidOpTypeContext; /*!< DID operation type context */
  Dcm_DidMgrOpMemType             OpType;           /*!< Requested operation type */
};
typedef struct DCM_SVC2FREPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc2FRepeaterProxyContextType;
typedef P2VAR(Dcm_Svc2FRepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc2FRepeaterProxyContextPtrType;
# endif /* (DCM_SVC_2F_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_31_SUPPORT_ENABLED == STD_ON)
/*! Service 0x31 temporary processing context */
struct DCM_SVC31REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_CfgRidMgrInfoHandleOptType RidInfoIdx;      /*!< Reference to Dcm_CfgRidMgrRidInfo[] entry */
  Dcm_CfgRidMgrOpHandleOptType   RidOpInfoIdx;    /*!< Reference to Dcm_CfgRidMgrOpInfo[] entry */
};
typedef struct DCM_SVC31REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc31RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc31RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc31RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_31_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_34_SUPPORT_ENABLED == STD_ON)
/*! Service 0x34 temporary processing context */
struct DCM_SVC34REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_FblMgrMemBlockType      MemoryBlock;     /*!< Address, length and MID */
  Dcm_FblMgrBlockLengthType   MaxBlockLength;  /*!< Maximum number of block length */
  Dcm_FblMgrDataFormatIdType  DataFormatId;    /*!< Format identifier */
};
typedef struct DCM_SVC34REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc34RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc34RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_Svc34RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_34_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_36_SUPPORT_ENABLED == STD_ON)
/*! Service 0x36 temporary processing context */
struct DCM_SVC36REPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_FblMgrBlockSequenceCounterType  BlockSequenceCounterNew;  /*!< New block sequence counter */
};
typedef struct DCM_SVC36REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc36RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc36RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc36RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_36_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_37_SUPPORT_ENABLED == STD_ON)
/*! Service 0x37 temporary processing context */
struct DCM_SVC37REPEATERPROXYCONTEXTTYPE_TAG
{
  uint8 Spare; /*!< Currently not used */
};
typedef struct DCM_SVC37REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc37RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc37RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc37RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_37_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_3D_SUPPORT_ENABLED == STD_ON)
/*! Service 0x3D temporary processing context */
struct DCM_SVC3DREPEATERPROXYCONTEXTTYPE_TAG
{
  Dcm_MemMgrMemBlockType  MemBlock; /*!< Shared memory block information */
};
typedef struct DCM_SVC3DREPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc3DRepeaterProxyContextType;
typedef P2VAR(Dcm_Svc3DRepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)    Dcm_Svc3DRepeaterProxyContextPtrType;
typedef P2CONST(Dcm_Svc3DRepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc3DRepeaterProxyContextConstPtrType;
# endif /* (DCM_SVC_3D_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_85_SUPPORT_ENABLED == STD_ON)
/*! Service 0x85 temporary processing context */
struct DCM_SVC85_REPEATERPROXYCONTEXTTYPE_TAG
/*! Service 0x85 temporary processing context */
{
  uint32                             DTCGroup;    /*!< Requested DTC for the ModeSwitch operation during the post-processing */
  Rte_ModeType_DcmControlDtcSetting  ReqMode;     /*!< Requested mode for the ModeSwitch operation during the post-processing */
  Dcm_DiagSubServiceRefOptType       SubSvcRef;   /*!< Reference to Dcm_CfgSvc85SubFuncInfo[] entry */
  uint8                              DemClientId; /*!< DEM ClientId */
};
typedef struct DCM_SVC85_REPEATERPROXYCONTEXTTYPE_TAG Dcm_Svc85RepeaterProxyContextType;
typedef P2VAR(Dcm_Svc85RepeaterProxyContextType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_Svc85RepeaterProxyContextPtrType;
# endif /* (DCM_SVC_85_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
typedef P2CONST(Dcm_CfgSvc86SubFuncInfoType, TYPEDEF, DCM_CONST)   Dcm_CfgSvc86SubFuncInfoPtrType;
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */

typedef Std_ReturnType Dcm_NetTransmissionResultType;
/*! Base data type for a task identifier (Valid values: DCM_TSK_ID_*) */
typedef uint8        Dcm_TskTaskIdMemType;
typedef uint8_least  Dcm_TskTaskIdOptType;

/*! Base data type for a task event (Valid values: DCM_TSK_EV_*)  */
typedef uint32        Dcm_TskTaskEvMemType;
typedef uint32_least  Dcm_TskTaskEvOptType;

/*! Base data type for a generic pointer to a task event register */
typedef P2VAR(Dcm_TskTaskEvMemType, TYPEDEF, AUTOMATIC) Dcm_TskTaskEvPtrType;
/*! Base data type for the application notification levels */
typedef uint8 Dcm_DiagApplNotificationType;

/*! Base data type for the diagnostic kernel processing state flags */
typedef uint8 Dcm_DiagProcessorFlagType;

/*! Diagnostic kernel synchronization data */
struct DCM_DIAGSYNCHDATATYPE_TAG
{
  Dcm_CfgNetTObjHandleMemType      TObjHdl;        /*!< A single element queue for the transport object handle that holds the request data to be processed at next Dcm_DiagTaskWorker() activation */
# if (DCM_DIAG_GARB_COL_ENABLED == STD_ON)
  Dcm_TskTaskEvMemType             QueuedTObjects; /*!< Bitmask of queued transport objects */
# endif
  Dcm_DiagProcessorFlagType        Flags;          /*!< The diagnostic kernel status flags (Valid values: DCM_DIAG_QUEUE_FLAG_*) */
};
typedef struct DCM_DIAGSYNCHDATATYPE_TAG Dcm_DiagSynchDataType;

/*! Control thread specific data of the sub-component diagnostic kernel */
struct DCM_DIAGTHREADCONTEXTTYPE_TAG
{
  Dcm_MsgContextType               MsgContext;            /*!< The diagnostic service/sub-service processor message context */
  volatile Dcm_DiagSynchDataType   QueuedSet;             /*!< Diagnostic kernel processing synchronization data */
  Dcm_DiagPostProcessorContextType PostProcessorContext;  /*!< Post-processing context */
  Dcm_CfgNetTObjHandleMemType      TObjHdl;               /*!< The transport object handle of the diagnostic request in processing */
  Dcm_DiagP2TimingsType            P2Timings;             /*!< Currently active set of the P2/P2* timings */
  Dcm_NetTransmissionResultType    TxStatus;              /*!< Transports the (RCR-RP and final) USDT response transmission result to the Dcm_DiagTaskWorker() */
  Dcm_DiagApplNotificationType     ApplNotification;      /*!< Application notification level reached for current diagnostic request (Valid values: DCM_DIAG_APPL_NOTIFICATION_*) */
  volatile Dcm_DiagProcessorStateType State;              /*!< Keeps track of the diagnostic kernel processing state per diagnostic request */
  Dcm_NegativeResponseCodeType     ErrorRegister;         /*!< Keeps the NRC for the current diagnostic service in processing */
  uint8                            SidIndex;              /*!< Reference to Dcm_CfgDiagServiceInfo[] entry */
# if (DCM_DIAG_RCRRP_LIMIT_ENABLED == STD_ON)
  uint8                            NumRcrRpTimeouts;      /*!< Keeps track of the number of RCR-RPs sent for the current diagnostic service processing */
# endif
  boolean                          ProcessServiceExtern;  /*!< Diagnostic service dispatching */
  boolean                          DoSuppressResponse;    /*!< Used dedicated flag instead of "NRC 0x11 and func_req" combination with the same effect, because of possible application confirmation functions! */
# if (DCM_NET_INTERNAL_REQ_ENABLED == STD_ON)
  boolean                          IsInternRequest;       /*!< Specifies whether current request in processing is internal i.e. send via Dcm_ProcessVirtualRequest() or internal Dcm_NetRxIndInternal() API (TRUE - internal, FALSE - external (normal)) */
# endif
};
typedef struct DCM_DIAGTHREADCONTEXTTYPE_TAG Dcm_DiagThreadContextType;

/*! Context information of service processor repeater of each service processor */
union DCM_REPEATERPROXYSVCCONTEXTTYPE_TAG
{                                                                                                                                                    /* PRQA S 0750 */ /* MD_Dcm_Rule19.2 */
# if (DCM_SVC_01_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc01RepeaterProxyContextType Svc01;     /*!< Service 0x01 temporary processing context */
# endif
# if (DCM_SVC_02_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc02RepeaterProxyContextType Svc02;     /*!< Service 0x02 temporary processing context */
# endif
# if (DCM_SVC_03_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc03RepeaterProxyContextType Svc03;     /*!< Service 0x03 temporary processing context */
# endif
# if (DCM_SVC_04_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc04RepeaterProxyContextType Svc04;     /*!< Service 0x04 temporary processing context */
# endif
# if (DCM_SVC_06_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc06RepeaterProxyContextType Svc06;     /*!< Service 0x06 temporary processing context */
# endif
# if (DCM_SVC_07_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc07RepeaterProxyContextType Svc07;     /*!< Service 0x07 temporary processing context */
# endif
# if (DCM_SVC_08_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc08RepeaterProxyContextType Svc08;     /*!< Service 0x08 temporary processing context */
# endif
# if (DCM_SVC_09_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc09RepeaterProxyContextType Svc09;     /*!< Service 0x09 temporary processing context */
# endif
# if (DCM_SVC_0A_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc0ARepeaterProxyContextType Svc0A;     /*!< Service 0x0A temporary processing context */
# endif
# if (DCM_SVC_10_SUPPORT_ENABLED == STD_ON)                                                                                                          /* COV_DCM_SUPPORT_ALWAYS TX */
  Dcm_Svc10RepeaterProxyContextType Svc10;     /*!< Service 0x10 temporary processing context */
# endif
# if (DCM_SVC_11_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc11RepeaterProxyContextType Svc11;     /*!< Service 0x11 temporary processing context */
# endif
# if (DCM_SVC_14_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc14RepeaterProxyContextType Svc14;     /*!< Service 0x14 temporary processing context */
# endif
# if (DCM_SVC_19_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc19RepeaterProxyContextType Svc19;     /*!< Service 0x19 temporary processing context */
# endif
# if (DCM_SVC_22_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc22RepeaterProxyContextType Svc22;     /*!< Service 0x22 temporary processing context */
# endif
# if (DCM_SVC_23_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc23RepeaterProxyContextType Svc23;     /*!< Service 0x23 temporary processing context */
# endif
# if (DCM_SVC_24_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc24RepeaterProxyContextType Svc24;     /*!< Service 0x24 temporary processing context */
# endif
# if (DCM_SVC_27_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc27RepeaterProxyContextType Svc27;     /*!< Service 0x27 temporary processing context */
# endif
# if (DCM_SVC_28_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc28RepeaterProxyContextType Svc28;     /*!< Service 0x28 temporary processing context */
# endif
# if (DCM_SVC_29_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc29RepeaterProxyContextType Svc29;     /*!< Service 0x29 temporary processing context */
# endif
# if (DCM_SVC_2A_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc2ARepeaterProxyContextType Svc2A;     /*!< Service 0x2A temporary processing context */
# endif
# if (DCM_SVC_2C_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc2CRepeaterProxyContextType Svc2C;     /*!< Service 0x2C temporary processing context */
# endif
# if (DCM_SVC_2E_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc2ERepeaterProxyContextType Svc2E;     /*!< Service 0x2E temporary processing context */
# endif
# if (DCM_SVC_2F_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc2FRepeaterProxyContextType Svc2F;     /*!< Service 0x2F temporary processing context */
# endif
# if (DCM_SVC_31_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc31RepeaterProxyContextType Svc31;     /*!< Service 0x31 temporary processing context */
# endif
# if (DCM_SVC_34_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc34RepeaterProxyContextType Svc34;     /*!< Service 0x34 temporary processing context */
# endif
# if (DCM_SVC_36_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc36RepeaterProxyContextType Svc36;     /*!< Service 0x36 temporary processing context */
# endif
# if (DCM_SVC_37_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc37RepeaterProxyContextType Svc37;     /*!< Service 0x37 temporary processing context */
# endif
# if (DCM_SVC_3D_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc3DRepeaterProxyContextType Svc3D;     /*!< Service 0x3D temporary processing context */
# endif
# if (DCM_SVC_85_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc85RepeaterProxyContextType Svc85;     /*!< Service 0x85 temporary processing context */
# endif
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
  Dcm_Svc86RepeaterProxyContextType Svc86;     /*!< Service 0x86 temporary processing context */
# endif
};
typedef union DCM_REPEATERPROXYSVCCONTEXTTYPE_TAG Dcm_RepeaterProxySvcContextType;

/*! Service processor repeater state */
struct DCM_REPEATERPROXYCONTEXTPOOLTYPE_TAG
{
  Dcm_RepeaterProxySvcContextType Context;     /*!< Service specific repeater contexts */
  Dcm_OpStatusType                OpStatus;    /*!< Current operation status */
  Dcm_RepeaterProgressType        Progress;    /*!< Progress of the repeater */
  Dcm_RepeaterProgressType        SubProgress; /*!< Progress of a sub-repeater */
  Dcm_RepeaterUserType            User;        /*!< Current user of the repeater */
};
typedef struct DCM_REPEATERPROXYCONTEXTPOOLTYPE_TAG Dcm_RepeaterProxyContextPoolType;

/*! Diagnostic service processor repeater context */
struct DCM_REPEATERCONTEXTTYPE_TAG
{
  uint8                            CalleeIdx; /*!< Index of the next function to call */
  Dcm_RepeaterProxyContextPoolType Contexts;  /*!< Current state of the repeater including service specific contexts */
};
typedef struct DCM_REPEATERCONTEXTTYPE_TAG Dcm_RepeaterContextType;
/*! Base data type for system timer handles  (no more than 32 timers supported for now: see Dcm_TmrMaskMemType definition section) */
typedef uint8        Dcm_TmrTimerIdMemType;
typedef uint8_least  Dcm_TmrTimerIdOptType;

# if (DCM_TMR_NUM_TIMER_CONTEXTS <= 8u)
/*! Base data type (memory consumption and runtime optimized) for a timer-pool bitmap when no more than 8 system timers are needed */
typedef uint8        Dcm_TmrMaskMemType;
typedef uint8_least  Dcm_TmrMaskOptType;
# elif (DCM_TMR_NUM_TIMER_CONTEXTS <= 16u)                                                                                                           /* COV_DCM_SUPPORT_ALWAYS TX */
/*! Base data type (memory consumption and runtime optimized) for a timer-pool bitmap when no more than 16 system timers are needed */
typedef uint16        Dcm_TmrMaskMemType;
typedef uint16_least  Dcm_TmrMaskOptType;
# elif (DCM_TMR_NUM_TIMER_CONTEXTS <= 32u)
/*! Base data type (memory consumption and runtime optimized) for a timer-pool bitmap when no more than 32 system timers are needed */
typedef uint32        Dcm_TmrMaskMemType;
typedef uint32_least  Dcm_TmrMaskOptType;
# else
#  error "Too many system timers!"
# endif
/*! Data container with all thread specific elements (i.e. for parallel Diagnostic service handling)  */
struct DCM_THREADCONTEXTTYPE_TAG
{
# if (DCM_PAGED_BUFFER_ENABLED == STD_ON)
  Dcm_PagedBufferContextType  PagedBuffer;    /*!< Paged-buffer manager sub-component per-instance memory */
# endif
  Dcm_DiagThreadContextType   Diag;           /*!< Diagnostic kernel sub-component per-thread memory */
  Dcm_RepeaterContextType     Repeater;       /*!< Diagnostic service processor repeater sub-component per-thread memory */
  Dcm_ThreadIdMemType         ThreadId;       /*!< Active thread */
};
typedef struct DCM_THREADCONTEXTTYPE_TAG Dcm_ThreadContextType;
typedef P2VAR(Dcm_ThreadContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_ThreadContextPtrType;
typedef P2CONST(Dcm_ThreadContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_ThreadContextConstPtrType;

/*! General processing context */
struct DCM_CONTEXTTYPE_TAG
{
  Dcm_ThreadContextPtrType  Thread;    /*!< Points to thread specific processing context */
};
/*! Single task context configuration data */
struct DCM_TSKEVENTCONTEXTTYPE_TAG
{
  Dcm_TskTaskEvMemType  Ev;     /*!< Currently active events */
  Dcm_TskTaskEvMemType  PostEv; /*!< Events to be activated at next main-function cycle */
};
typedef struct DCM_TSKEVENTCONTEXTTYPE_TAG Dcm_TskEventContextType;

/*! Base data type for a generic pointer to a task event context register */
typedef P2VAR(Dcm_TskEventContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_TskEventContextPtrType;

/*! Function pointer prototype for a system task handler */
typedef P2FUNC(void, DCM_CODE, Dcm_TskTaskFuncType) (
  Dcm_ContextPtrType pContext,  /* IN: Pointer to context */
  Dcm_TskEventContextPtrType pEventContext  /* INOUT: Events to be activated at the current and the next main-function cycle */
  );

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_RepeaterNextSubStep()
 *********************************************************************************************************************/
/*! \brief          Sets next step of repeater proxy.
 *  \details        -
 *  \param[in]      pContext    Pointer to the context
 *  \param[in]      nextSubStep Next step to be processed
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
*********************************************************************************************************************/
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_RepeaterNextSubStep(                                                                                      /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_ContextPtrType pContext,
  Dcm_RepeaterProgressType nextSubStep
  );
# define DCM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define DCM_START_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
# if (DCM_NET_INTERNAL_REQ_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_NetRxIndInternal()
 *********************************************************************************************************************/
/*! \brief          Provides a means for virtual/internal diagnostic request.
 *  \details        This API is generally used for RoE (SID 0x86) purposes.
 *  \param[in]      rxPduId            The RxPDUID of the request
 *  \param[in]      sourceAddress      Client or tester address
 *  \param[in]      data               The data of the request
 *  \param[in]      length             The length of the request
 *  \return         DCM_E_OK           Reception was successful
 *  \return         DCM_E_NOT_OK       Reception was not successful
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_NetRxIndInternal(
  PduIdType rxPduId,
  uint16 sourceAddress,
  Dcm_MsgType data,
  PduLengthType length
  );
# endif

/**********************************************************************************************************************
 *  Dcm_NetGetComState()
 *********************************************************************************************************************/
/*! \brief          Returns the communication state for the given RxPduId.
 *  \details        -
 *  \param[in]      rxPduId    The RxPDUID of the request
 *  \return         The communication state
 *  \context        ISR1|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_NetComMStateType, DCM_CODE) Dcm_NetGetComState(
  PduIdType rxPduId
  );
# if (DCM_MODE_ROE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ModeSwitchRoE()
 *********************************************************************************************************************/
/*! \brief          Mode switching for RoE activation state change.
 *  \details        -
 *  \param[in]      eventId    The id used for triggering RoE events
 *  \param[in]      mode       The mode
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_ModeSwitchRoE(
  uint8 eventId,
  Rte_ModeType_DcmResponseOnEvent mode
  );
# endif
/**********************************************************************************************************************
 *  Dcm_TmrSetTimerByThread()
 *********************************************************************************************************************/
/*! \brief          Sets the value of a timer of the given index.
 *  \details        -
 *  \param[in]      timerId      The timer ID
 *  \param[in]      timeTicks    The concrete time to elapse
 *  \param[in]      threadId     The thread ID
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_TmrSetTimerByThread(
  Dcm_TmrTimerIdOptType timerId,
  Dcm_TmrTimerCntrMemType timeTicks,
  Dcm_ThreadIdOptType threadId
  );

/**********************************************************************************************************************
 *  Dcm_TmrStartTimerByThread()
 *********************************************************************************************************************/
/*! \brief          Starts a timer with a given time value.
 *  \details        Starts a timer with the given timer ID with the given time value.
 *  \param[in]      timerId      The timer ID
 *  \param[in]      timeTicks    The concrete time to elapse
 *  \param[in]      threadId     The thread ID
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_TmrStartTimerByThread(
  Dcm_TmrTimerIdOptType timerId,
  Dcm_TmrTimerCntrMemType timeTicks,
  Dcm_ThreadIdOptType threadId
  );

/**********************************************************************************************************************
 *  Dcm_TmrStopTimerByThread()
 *********************************************************************************************************************/
/*! \brief          Stops a timer.
 *  \details        Stops a timer with the given timer ID.
 *  \param[in]      timerId    The timer ID
 *  \param[in]      threadId     The thread ID
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_TmrStopTimerByThread(
  Dcm_TmrTimerIdOptType timerId,
  Dcm_ThreadIdOptType threadId
  );

/**********************************************************************************************************************
 *  Dcm_TmrResumeTimerByThread()
 *********************************************************************************************************************/
/*! \brief          Resumes a timer.
 *  \details        Resumes a timer with the given timer ID.
 *  \param[in]      timerId    The timer ID
 *  \param[in]      threadId     The thread ID
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_TmrResumeTimerByThread(
  Dcm_TmrTimerIdOptType timerId,
  Dcm_ThreadIdOptType threadId
  );
# if (DCM_TMR_NUM_SVC86_SCHEDULER > 0u)
/**********************************************************************************************************************
 *  Dcm_ExtOnTimeoutSvc86Scheduler()
 *********************************************************************************************************************/
/*! \brief          Service 0x86 timer function to trigger sampling for onDTCStatusChange events.
 *  \details        -
 *  \param[in]      ThreadId  Active thread
 *  \return         Number of reload ticks
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_TmrTimerCntrMemType, DCM_CODE) Dcm_ExtOnTimeoutSvc86Scheduler(
  Dcm_ThreadIdMemType threadId
  );
# endif
# if (DCM_TSK_NUM_ROE > 0u)
/**********************************************************************************************************************
 *  Dcm_ExtSvc86Task()
 *********************************************************************************************************************/
/*! \brief          Service 0x86 task.
 *  \details        Low priority task of the RoE sub-module.
 *  \param[in,out]  pEventContext  Pointer to the event context
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_ExtSvc86Task(
  Dcm_ContextPtrType pContext,
  Dcm_TskEventContextPtrType pEventContext
  );
# endif

/**********************************************************************************************************************
 *  Dcm_TskClrEventByThread()
 *********************************************************************************************************************/
/*! \brief          Clears event(s) of a task.
 *  \details        Clears the given events for a specific task.
 *  \param[in]      taskId    The task handle
 *  \param[in]      ev        The event(s) to be cleared
 *  \param[in]      ThreadId  Active thread
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_TskClrEventByThread(
  Dcm_TskTaskIdOptType taskId,
  Dcm_TskTaskEvMemType ev,
  Dcm_ThreadIdOptType threadId
  );

/**********************************************************************************************************************
 *  Dcm_TskGetEventByThread()
 *********************************************************************************************************************/
/*! \brief          get event(s) of a task.
 *  \details        Return the given event for a specific task.
 *  \param[in]      taskId    The task handle
 *  \param[in]      ThreadId  Active thread
 *  \return         Event of the specified task
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_TskTaskEvMemType, DCM_CODE) Dcm_TskGetEventByThread(
  Dcm_TskTaskIdOptType taskId,
  Dcm_ThreadIdOptType threadId
  );

/**********************************************************************************************************************
 *  Dcm_TskSetEventByThread()
 *********************************************************************************************************************/
/*! \brief          Notifies a task for events.
 *  \details        Sets an event for a specific task.
 *  \param[in]      taskId    The task handle
 *  \param[in]      ev        The event(s) to be cleared
 *  \param[in]      ThreadId  Active thread
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_TskSetEventByThread(
  Dcm_TskTaskIdOptType taskId,
  Dcm_TskTaskEvMemType ev,
  Dcm_ThreadIdOptType threadId
  );
# if (DCM_VARMGR_MULTI_COM_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_VarMgrGetActiveComVariant()
 *********************************************************************************************************************/
/*! \brief          Returns currently set variant.
 *  \details        Returns currently active communication variant.
 *  \return         Operation result
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC (Dcm_CfgVarMgrComVariantType, DCM_CODE) Dcm_VarMgrGetActiveComVariant(void);
# endif

/**********************************************************************************************************************
 *  Dcm_VarMgrGetActiveCfgVariantId()
 *********************************************************************************************************************/
/*! \brief          Returns currently set variant.
 *  \details        Returns currently active config variant id.
 *  \return         Operation result
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC (Dcm_CfgVarMgrDiagVariantIdMemType, DCM_CODE) Dcm_VarMgrGetActiveCfgVariantId(void);
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)
#  if (DCM_SVC_86_RST_ON_DSC_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtSvc86OnChangeSession()
 *********************************************************************************************************************/
/*! \brief          Service 0x86 utility function to notify RoE about a session change.
 *  \details        -
 *  \param[in]      oldSession    The old session
 *  \param[in]      newSession    The old session
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_ExtSvc86OnChangeSession(
  Dcm_CfgStateGroupOptType oldSession,
  Dcm_CfgStateGroupOptType newSession
  );
#  endif

/**********************************************************************************************************************
 *  Dcm_Svc86IsStorageStateBitPartOfSubFunc()
 *********************************************************************************************************************/
/*! \brief          Returns whether the storageState Bit 6 is part of the sub-function or not
 *  \details        -
 *  \return         TRUE         storageState is part of the sub-function
 *  \return         FALSE        storageState is not part of the sub-function
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_Svc86IsStorageStateBitPartOfSubFunc(
  void
  );
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
# define DCM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
# define DCM_START_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/**********************************************************************************************************************
 *  Dcm_RepeaterNextSubStep()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DCM_GLOBAL_INLINE FUNC(void, DCM_CODE) Dcm_RepeaterNextSubStep(                                                                                      /* PRQA S 3219 */ /* MD_MSR_Unreachable */
  Dcm_ContextPtrType pContext,                                                                                                                       /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
  Dcm_RepeaterProgressType nextSubStep
  )
{
  pContext->Thread->Repeater.Contexts.SubProgress = nextSubStep;                                                                                     /* SBSW_DCM_PARAM_PTR_WRITE */
  Dcm_RepeaterResetOpStatus(pContext);                                                                                                               /* SBSW_DCM_PARAM_PTR_FORWARD */
}
# define DCM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* !defined(DCM_COREINT_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_CoreInt.h
 *********************************************************************************************************************/
