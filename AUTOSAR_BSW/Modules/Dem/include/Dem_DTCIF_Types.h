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
/*! \addtogroup Dem_DTCIF
 *  \{
 *  \file       Dem_DTCIF_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Typedefinitions of DTCIF subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_DTCIF_TYPES_H)
#define DEM_DTCIF_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*! Maximum value internal data element 'aged counter' can reach before it is latched' */
#define DEM_DTC_AGED_COUNTER_MAX_VALUE                     (0xFFU)
/*! Initial value of internal data element 'aged counter' */
#define DEM_DTC_AGED_COUNTER_INIT_VALUE                    (0x00U)
/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/
/* Pre-confirmed status bit 'unconfirmedDTC' ------------------------------- */
/*! Test pre-confirmed DTC state of SI.30 status */
#define DEM_DTC_TEST_PC_STATUS_UDTC(Status)      (((Status) & 0x01U) != 0u)
/*! Set pre-confirmed DTC state of SI.30 status */
#define DEM_DTC_SET_PC_STATUS_UDTC(Status)       ((uint8)((Status) | 0x01U))
/*! Reset pre-confirmed DTC state of SI.30 status */
#define DEM_DTC_RESET_PC_STATUS_UDTC(Status)     ((uint8)((Status) & 0xfeU))

/* Pre-confirmed status bit 'unconfirmedDTCThisOperationCycle' ------------- */
/*! Test pre-confirmed DTC this operating cycle state of SI.30 status */
#define DEM_DTC_TEST_PC_STATUS_UDTCTOC(Status)   (((Status) & 0x02U) != 0u)
/*! Set pre-confirmed DTC this operating cycle state of SI.30 status */
#define DEM_DTC_SET_PC_STATUS_UDTCTOC(Status)    ((uint8)((Status) | 0x02U))
/*! Reset pre-confirmed DTC this operating cycle state of SI.30 status */
#define DEM_DTC_RESET_PC_STATUS_UDTCTOC(Status)  ((uint8)((Status) & 0xfdU))

/* Pre-confirmed status bit 'unconfirmedDTCSinceLastClear' ----------------- */
/*! Test pre-confirmed DTC since last clear state of SI.30 status */
#define DEM_DTC_TEST_PC_STATUS_UDTCSLC(Status)   (((Status) & 0x04U) != 0u)
/*! Set pre-confirmed DTC since last clear state of SI.30 status */
#define DEM_DTC_SET_PC_STATUS_UDTCSLC(Status)    ((uint8)((Status) | 0x04U))
/*! Reset pre-confirmed DTC since last clear state of SI.30 status */
#define DEM_DTC_RESET_PC_STATUS_UDTCSLC(Status)  ((uint8)((Status) & 0xfbU))

/* Pre-confirmed status bit 'agedDTC' -------------------------------------- */
/*! Test aged DTC state of SI.30 status */
#define DEM_DTC_TEST_PC_STATUS_ADTC(Status)      (((Status) & 0x08U) != 0u)
/*! Set aged DTC state of SI.30 status */
#define DEM_DTC_SET_PC_STATUS_ADTC(Status)       ((uint8)((Status) | 0x08U))
/*! Reset aged DTC state of SI.30 status */
#define DEM_DTC_RESET_PC_STATUS_ADTC(Status)     ((uint8)((Status) & 0xf7U))

/* Pre-confirmed status bit 'symptomSinceLastClear' ------------------------ */
/*! Test symptom since last clear state of SI.30 status */
#define DEM_DTC_TEST_PC_STATUS_SSLC(Status)      (((Status) & 0x10U) != 0u)
/*! Set symptom since last clear state of SI.30 status */
#define DEM_DTC_SET_PC_STATUS_SSLC(Status)       ((uint8)((Status) | 0x10U))
/*! Reset symptom since last clear state of SI.30 status */
#define DEM_DTC_RESET_PC_STATUS_SSLC(Status)     ((uint8)((Status) & 0xefU))

/* Pre-confirmed status bit 'warningIndicatorRequestedSinceLastClear' ------ */
/*! Test warning indicator requested since last clear state of SI.30 status */
#define DEM_DTC_TEST_PC_STATUS_WIRSLC(Status)    (((Status) & 0x20U) != 0u)
/*! Set warning indicator requested since last clear state of SI.30 status */
#define DEM_DTC_SET_PC_STATUS_WIRSLC(Status)     ((uint8)((Status) | 0x20U))
/*! Reset warning indicator requested since last clear state of SI.30 status */
#define DEM_DTC_RESET_PC_STATUS_WIRSLC(Status)   ((uint8)((Status) & 0xdfU))

/* Pre-confirmed status bit 'emissionRelatedDTC' --------------------------- */
/*! Test emission related DTC state of SI.30 status */
#define DEM_DTC_TEST_PC_STATUS_ODBDTC(Status)    (((Status) & 0x40U) != 0u)
/*! Set emission related DTC state of SI.30 status */
#define DEM_DTC_SET_PC_STATUS_ODBDTC(Status)     ((uint8)((Status) | 0x40U))
/*! Reset emission related DTC state of SI.30 status */
#define DEM_DTC_RESET_PC_STATUS_ODBDTC(Status)   ((uint8)((Status) & 0xbfU))

/* Pre-confirmed status bit 'testFailedSinceLastClear' --------------------- */
/*! Test test failed since last clear state of SI.30 status */
#define DEM_DTC_TEST_PC_STATUS_TFSLC(Status)     (((Status) & 0x80U) != 0u)
/*! Set test failed since last clear state of SI.30 status */
#define DEM_DTC_SET_PC_STATUS_TFSLC(Status)      ((uint8)((Status) | 0x80U))
/*! Reset test failed since last clear state of SI.30 status */
#define DEM_DTC_RESET_PC_STATUS_TFSLC(Status)    ((uint8)((Status) & 0x7fU))

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Type to store the UDS status of an DTC */
typedef uint8 Dem_DTC_UDSStatusType;

/*! Type to depict the currently processing Operation */
typedef uint8 Dem_DTC_OperationType;

  /*! DTC status processing data */
struct Dem_DTC_Context_s
{
  Dem_EventIdType EventId;  /*!< Handle of processed DTC */
  Dem_Cfg_CombinedGroupIndexType GroupId;  /*!< [in] combination group of the DTC */
  Dem_DTC_UDSStatusType OldDtcStatus;  /*!< [in] DTC status before processing */
  Dem_DTC_UDSStatusType OldExternalDtcStatus;  /*!< [in] external DTC status before processing */
  Dem_DTC_UDSStatusType NewDtcStatus;  /*!< [in,out] DTC status after processing */
  Dem_Cfg_StorageTriggerType DtcEffects;  /*!< [in,out] status change triggers resulting from DTC status changes */
  boolean QualifyDTC;                     /*!< [in,out] Qualify single DTC without driving cycle qualification */
};

/*! DTC status processing data type */
typedef struct Dem_DTC_Context_s Dem_DTC_ContextType;

/*! Structure used as argument type for Dem_DTC_ForEachCombinedSubEvent functions */
struct Dem_DTC_ForEachCombinedArgType_s
{
  /*! Function arguments common to all functions */
  struct
  {
    uint8 OldDtcStatus;  /*!< [in] DtcStatus before the call */
    uint8 NewDtcStatus;  /*!< [out] DtcStatus after the call */
  } Common;
  /*! Function arguments specific to the called function */
  union
  {                                                                                                                              /* PRQA S 0750 */ /* MD_MSR_Union */
    /*! Function arguments specific to Dem_Event_Cleared */
    struct
    {
      uint8 unused;  /*!< no specific arguments, dummy only */
    } EventClearState;
#if (DEM_FEATURE_NEED_CUSTOMIZED_MEMORY_PROCESSING == STD_ON)
    /*! Function arguments specific to Dem_Event_CustomizedDisplacement */
    struct
    {
      uint8 SI30;  /*!< [in,out] In: SI30 value before the call, Out: SI30 value after the call */
    } Event_CustomizedDisplacement_Internal;
#else
    /*! Function arguments specific to Dem_Event_Displaced */
    struct
    {
      uint8 unused;  /*!< no specific arguments, dummy only */
    } EventDisplaced_Internal;
#endif
    /*! Function arguments specific to Dem_Event_OpCycle */
    struct
    {
      uint8 CycleStatus;  /*!< [in] CycleStatus to set */
    } EventOpCycle_Internal;
    /*! Function arguments specific to Dem_Event_AgingCycle_Internal */
    struct
    {
      uint8 unused;  /*!< no specific arguments, dummy only */
    } EventAgingCycle_Internal;
    /*!function arguments specific to Dem_Event_CycleQualifyDcy */
    struct
    {
      boolean SuppressNotifications;  /*!< [in] Dem shall suppress event and dtc status change notifications on event aging */
#if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
      boolean IsAgingOnlyEntry; /*!< [in] New state of event internal status depends on stored status */
#endif
    } Event_Aged;
    /*!function arguments specific to DemEvent_Aged */
    struct
    {
      uint8 unused;  /*!< no specific arguments, dummy only */
    } CycleQualifyDcy_Internal;
  } Specific;
};

/*! Argument type used for Dem_DTC_ForEachCombinedSubEvent functions */
typedef struct Dem_DTC_ForEachCombinedArgType_s Dem_DTC_ForEachCombinedArgType;

/*! Reference to argument struct used for Dem_DTC_ForEachCombinedSubEvent functions */
typedef P2VAR(Dem_DTC_ForEachCombinedArgType, TYPEDEF, DEM_VAR_NOINIT) Dem_DTC_ForEachCombinedArgPtrType;

/*! Function pointer type for Dem_DTC_ForEachCombinedSubEvent functions */
typedef P2FUNC(void, DEM_CODE, Dem_Util_ForEachCombinedFuncType)(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );

/*! Enum encapsulated current aging status of DTCs, only used when DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON */
typedef enum
{
  Dem_DTC_AgingStatusNone,       /*!< Aging is not currently in progress */
  Dem_DTC_AgingStatusInProgress, /*!< Aging is currently in progress */
  Dem_DTC_AgingStatusAged        /*!< Aging is finished, event is currently aged */
} Dem_DTC_AgingStatusType;

#endif /* DEM_DTCIF_TYPES_H */
/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCIF_Types.h
 *********************************************************************************************************************/
