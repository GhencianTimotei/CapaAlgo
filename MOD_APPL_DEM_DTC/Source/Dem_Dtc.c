/* polyspace+1 MISRA-C3:1.1 [Justified:Low] "All macro definitions are needed." */
/*------------------------------------------------------------------------------------------------+
| File: Dem_Dtc.c                                                                          |
+-------------------------------------------------------------------------------------------------+
| Project: Audi eTab                                                                              |
+-------------------------------------------------------------------------------------------------+
| Short description: In this file is handled the implementation of all DTCs.                                                      |
+------------------------------------------------------------------------------------------------*/

/*===============================================================================================*/
/* Include files */
/*===============================================================================================*/

#include "Dem.h"
#include "Com.h"
#include "Dem_Dtc.h"
#include "BatterySupervisor.h"
#include "Com_Cfg.h"
#include "Appl_Cbk.h"
#include "MeasureSupply.h"
#include "Rte_DemSatellite_0.h"
#include "CanSM_Cfg.h"
#include "ComM.h"
#include "string.h"
#include "BatterySupervisor.h"
#include "MemIf.h"
#include "NvM_Cbk.h"
#include "Dcm.h"

/*===============================================================================================*/
/* Macro definitions */
/*===============================================================================================*/

#define KD_BIT_DTC_STATUS_MASK                      0x2Cu
#define DTC_TEST_FAILED_BIT                         0x01u
#define LDC_STATUS_REG_LC_FSM_WD                    0x0Cu   /* Mask used to substract bit 2 (LC_WD) and bit 3 (FSM_WD) of LDC status register */
#define PAR_TIME_LDC_WD_ERROR_MAX_OCCURRENCE        50u
#define MEMIF_DEVICE_ID                             0u

#define ADC2VOLT_NO_OF_AXIS_POINTS  (13u)

/*===============================================================================================*/
/* Constant and types */
/*===============================================================================================*/

typedef enum
{
    StartUp = 0u,
    KdBitActive,
    KdBitInactive
} te_KdBitStatusType;

/*===============================================================================================*/
/* Variable declarations */
/*===============================================================================================*/
/* polyspace+16 MISRA-C3:8.9 [Justified:Low] "Variable is declared once here" */
static BOOL BO_NVEM_Abschaltstufe_Timeout = FALSE;
static BOOL BO_MDK_Function_State_Timeout = FALSE;
static BOOL BO_ToutMonEnabled = TRUE;
static BOOL BO_ToutMonEnabledOld = TRUE;
static BOOL BO_tDiagStartCntEnabled = FALSE;
static U8 U8_tDiagStartCnt = U8_500ms_T_DIAG_START;
static U8 U8_KL15StateOld = 0u;
static U8 U8_l_CanNmStateActiveOld = 0u;
static BOOL BO_BusOffState = FALSE;
static BOOL BO_BusOffStateCanSM = FALSE;
static te_KdBitStatusType KdBitStatus = StartUp;
static U8 BusOffStateOld = 0u;
static U16 BusOffDebounce = 0u;

/* polyspace+3 MISRA-C3:8.7 [Justified:Low] "Variable may be referenced from internal or external" */
U8 U8_LDC_StatusReg = 0;
BOOL BO_ResetHealInhStatus = FALSE;
te_WucStateType U8_WUCState = WUC_Unqualified;

/*===============================================================================================*/
/* Private Functions */
/*===============================================================================================*/

/*********************************************************************************************************
 *  Name                   : DemDtc_GetEventIdPermission
 *  Description            : Checks if there is permission to set a DTC (based on the Failure Inhibition Matrix)
 *  Parameters             : Dem_EventIdType
 *  Return                 : BOOL
 *  Critical/explanation   : Failure inhibition matrix - if any of the DEM events from arrDemEvents is active, all other events shall be inhibited.
 * 							 Requirements: SSR_1622, SSR_1623, SSR_1627, SSR_1628, SSR_1624, SSR_1625, SSR_1626
 *  Author                 : fmusteata
 *********************************************************************************************************/
/* polyspace+2 MISRA-C3:8.7 [Justified:Low] "Function may be referenced from internal or external" */
/* polyspace+1 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
BOOL DemDtc_GetEventIdPermission(U16 eventId)
{
    U8 arrDemEvents[6] = {DemConf_DemEventParameter_DTC_0x010000, DemConf_DemEventParameter_DTC_0x010001, DemConf_DemEventParameter_DTC_0x010002, 
                          DemConf_DemEventParameter_DTC_0x010007, DemConf_DemEventParameter_DTC_0x010008, DemConf_DemEventParameter_DTC_0x010009};
    U8 tmpDTCStatus, i;
    BOOL ret = TRUE;

    for(i = 0u; i < 6u; i++)
    {
        if(eventId != arrDemEvents[i])
        {
            (void)Dem_GetEventStatus(arrDemEvents[i], &tmpDTCStatus);

            if((tmpDTCStatus & DTC_TEST_FAILED_BIT) != 0u)
            {
                ret = FALSE;
                break;
            }
        }
    }

    return ret;           
}

/*********************************************************************************************************
 *  Name                   : DTC_0x010000_Implementation
 *  Description            : Handling of DTC_0x010000 (ODHE is faulty)
 *  Requirement            : SubSR_eTab_1263
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *  Author                 : fmusteata
 *********************************************************************************************************/
static void DTC_0x010000_Implementation(void)
{
    /* Locals */
    static U8 LCD_DiagDebCnt = 0u;

    /* Check for permission */
    if(DemDtc_GetEventIdPermission(DemConf_DemEventParameter_DTC_0x010000))
    {
        /* Check for error - Extract bit 2 (LC_WD) and bit 3 (FSM_WD) of LDC status register */
        if((U8_LDC_StatusReg & LDC_STATUS_REG_LC_FSM_WD) != 0u)
        {
            /* Call Dem_SetEventStatus() if the test fails for 20 consecutive times */
            if(LCD_DiagDebCnt == PAR_TIME_LDC_WD_ERROR_MAX_OCCURRENCE)
            {
                /* Dem call() - IF THIS POINT IS REACHED, THE ODHE MUST BE CHANGED IN SERVICE */
                (void)Dem_SetEventStatus(DemConf_DemEventParameter_DTC_0x010000, DEM_EVENT_STATUS_FAILED);
            }
            else
            {
                /* debouncing... */
                LCD_DiagDebCnt++;
            }
        }
        else
        {
            /* No symptom - keep the debounce counter at 0 */
            LCD_DiagDebCnt = 0u;
        }
    }
}

/*********************************************************************************************************
 *  Name                   : DTC_0x010001_Implementation
 *  Description            : Handling of DTC_0x010001 for overvoltage.
 *                           SWR-2348
 *                         :
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *  Author                 : grovent
 *********************************************************************************************************/
/* polyspace+3 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
static void DTC_0x010001_Implementation(void)
{
    BatSup_voltageStateType voltage_State = BatSup_getVoltageState();

    /* Check for permission */
    if(DemDtc_GetEventIdPermission(DemConf_DemEventParameter_DTC_0x010001))
    {
        if (voltage_State == BATSUP_OVERVOLTAGE)
        {
            (void)Dem_SetEventStatus(DemConf_DemEventParameter_DTC_0x010001, DEM_EVENT_STATUS_PREFAILED);
        }
        else if (voltage_State == BATSUP_NOMAL)
        {
            (void)Dem_SetEventStatus(DemConf_DemEventParameter_DTC_0x010001, DEM_EVENT_STATUS_PREPASSED);
        }
        else
        {
            /* do nothing*/
        }
    }
}

/*********************************************************************************************************
 *  Name                   : DTC_0x010003_Implementation
 *  Description            : Handling of DTC_0x010003 for overvoltage.
 *                           SWR-2364
 *                         :
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *  Author                 : grovent
 *********************************************************************************************************/
/* polyspace+3 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
static void DTC_0x010003_Implementation(void)
{
    BatSup_voltageStateType voltage_State = BatSup_getVoltageState();
    
    /* Check for permission */
    if(DemDtc_GetEventIdPermission(DemConf_DemEventParameter_DTC_0x010003))
    {
        if (voltage_State == BATSUP_OVERVOLTAGE)
        {
            (void)Dem_SetEventStatus(DemConf_DemEventParameter_DTC_0x010003, DEM_EVENT_STATUS_PREFAILED);
        }
        else if (voltage_State == BATSUP_NOMAL)
        {
            (void)Dem_SetEventStatus(DemConf_DemEventParameter_DTC_0x010003, DEM_EVENT_STATUS_PREPASSED);
        }
        else
        {
            /* do nothing */
        }
    }
}

/*********************************************************************************************************
 *  Name                   : DTC_0x010002_Implementation
 *  Description            : Handling of DTC_0x010002 for undervoltage.
 *                           SWR-2363
 *                         :
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *  Author                 : grovent
 *********************************************************************************************************/
 /* polyspace+3 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
static void DTC_0x010002_Implementation(void)
{
    BatSup_voltageStateType voltage_State = BatSup_getVoltageState();

    /* Check for permission */
    if(DemDtc_GetEventIdPermission(DemConf_DemEventParameter_DTC_0x010002))
    {
        if (voltage_State == BATSUP_UNDERVOLTAGE)
        {
            (void)Dem_SetEventStatus(DemConf_DemEventParameter_DTC_0x010002, DEM_EVENT_STATUS_PREFAILED);
        }
        else if (voltage_State == BATSUP_NOMAL)
        {
            (void)Dem_SetEventStatus(DemConf_DemEventParameter_DTC_0x010002, DEM_EVENT_STATUS_PREPASSED);
        }
        else
        {
            /* do nothing*/
        }
    }
}

/*********************************************************************************************************
 *  Name                   : DTC_0x010004_Implementation
 *  Description            : Handling of DTC_0x010004 for undervoltage.
 *                           SWR-2365
 *                         :
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *  Author                 : grovent
 *********************************************************************************************************/
/* polyspace+3 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
static void DTC_0x010004_Implementation(void)
{
    BatSup_voltageStateType voltage_State = BatSup_getVoltageState();
    
    /* Check for permission */
    if(DemDtc_GetEventIdPermission(DemConf_DemEventParameter_DTC_0x010004))
    {
        if (voltage_State == BATSUP_UNDERVOLTAGE)
        {
            (void)Dem_SetEventStatus(DemConf_DemEventParameter_DTC_0x010004, DEM_EVENT_STATUS_PREFAILED);
        }
        else if (voltage_State == BATSUP_NOMAL)
        {
            (void)Dem_SetEventStatus(DemConf_DemEventParameter_DTC_0x010004, DEM_EVENT_STATUS_PREPASSED);
        }
        else
        {
            /* do nothing*/
        }
    }
}

/*********************************************************************************************************
 *  Name                   : DTC_0x010005_Implementation
 *  Description            : Handling of DTC_0x010005 for NFC antenna fail.
 *                           SWR-2398
 *                         :
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *  Author                 : grovent
 *********************************************************************************************************/
static void DTC_0x010005_Implementation(void)
{
#ifdef NFC_DIAGNOSTICS_PRESENT
    /* Check for permission */
    if(DemDtc_GetEventIdPermission(DemConf_DemEventParameter_DTC_0x010005))
    {
        if (TRUE == NfcFuncDiag_GetNfcAntennaFailureStatus())
        {
            Dem_SetEventStatus(DemConf_DemEventParameter_DTC_0x010005, DEM_EVENT_STATUS_PREFAILED);
        }
        else
        {
            Dem_SetEventStatus(DemConf_DemEventParameter_DTC_0x010005, DEM_EVENT_STATUS_PREPASSED);
        }
    }
#endif
}

/*********************************************************************************************************
 *  Name                   : DTC_0x010011_Implementation
 *  Description            : Handling of DTC_0x010011 for NVEM_Abschaltstufe.
 *                           SWR-2423
 *                         :
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *  Author                 : grovent
 *********************************************************************************************************/
static void DTC_0x010011_Implementation(void)
{
    /* Check for permission */
    if(DemDtc_GetEventIdPermission(DemConf_DemEventParameter_DTC_0x010011))
    {
        /* evaluate DTC_0x010011 */
        if (BO_NVEM_Abschaltstufe_Timeout == TRUE)
        {
            (void)Dem_SetEventStatus(DemConf_DemEventParameter_DTC_0x010011, DEM_EVENT_STATUS_PREFAILED);
        }
        else
        {
            (void)Dem_SetEventStatus(DemConf_DemEventParameter_DTC_0x010011, DEM_EVENT_STATUS_PREPASSED);
        }

    }
}




/*********************************************************************************************************
 *  Name                   : DTC_0x010013_Implementation
 *  Description            : Handling of DTC_0x010013 for MDK_Function_State.
 *                           SWR-2461
 *                         :
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *  Author                 : grovent
 *********************************************************************************************************/
static void DTC_0x010013_Implementation(void)
{
    /* Check for permission */
    if(DemDtc_GetEventIdPermission(DemConf_DemEventParameter_DTC_0x010013))
    {
        /* evaluate DTC_0x010013 */
        if (BO_MDK_Function_State_Timeout == TRUE)
        {
            (void)Dem_SetEventStatus(DemConf_DemEventParameter_DTC_0x010013, DEM_EVENT_STATUS_PREFAILED);
        }
        else
        {
            (void)Dem_SetEventStatus(DemConf_DemEventParameter_DTC_0x010013, DEM_EVENT_STATUS_PREPASSED);
        }
    }
}

/*********************************************************************************************************
 *  Name                   : AdcToVoltage
 *  Description            : Converts ADC count input to physical value (mV) 
 *  Parameters             : U16_ADC
 *  Return                 : U16 - voltage physical value (mV)
 *********************************************************************************************************/
static U16 AdcToVoltage(U16 U16_ADC)
{
    U16 U16_AX_ADC[ADC2VOLT_NO_OF_AXIS_POINTS]  = {247,  285,  324,  362,   400,   438,   476,   514,   552,   590,   628,   666,   705};    /* ADC Value */
    U16 U16_AY_Ubat[ADC2VOLT_NO_OF_AXIS_POINTS] = {7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000};  /* Voltage in mV */
    U8 i = 0;           /* Interval index [0...11] */
    U16 U16_Ramp = 0;   /* Resolution 0.001 mV/ADCcount */
    S32 S32_Ubat = 0;

    /* Voltage is lower than minimum axis value */
    if (U16_ADC < U16_AX_ADC[0])
    {
        i = 0;
    }
    else
    {
        /* Voltage is grater than maximum axis value */
        if (U16_ADC >= U16_AX_ADC[ADC2VOLT_NO_OF_AXIS_POINTS - 1])
        {
            i = ADC2VOLT_NO_OF_AXIS_POINTS - 2;
        }
        else
        {
            /* Find the voltage interval */
            for (i = 0; i < (ADC2VOLT_NO_OF_AXIS_POINTS - 1); i++)
            {
                if ((U16_ADC >= U16_AX_ADC[i]) && (U16_ADC < U16_AX_ADC[i + 1]))
                {
                    /* Stop when interval is found */
                    break;
                }
            }
        }
    }
    /* polyspace+2 MISRA-C3:10.8 [Justified:Low] "The value is converted to U16 to not overflow." */
    /* Ramp calculation: Ramp = (V1-V0) / (ADC1-ADC0) */
    U16_Ramp = (U16)((U32)(U16_AY_Ubat[i + 1] - U16_AY_Ubat[i]) * (U32)1000 / (U32)(U16_AX_ADC[i + 1] - U16_AX_ADC[i]));
    
    /* polyspace+3 MISRA-C3:12.1 [Justified:Low] "does not affect the functionality" */
    /* polyspace+2 MISRA-C3:D2.1 [Justified:Low] "U16_ADC is a function parameter" */
    /* Value calculation: V = (ADC-ADC0) * Ramp + V0 */
    S32_Ubat = (((S32)U16_ADC - (S32)U16_AX_ADC[i]) * (S32)U16_Ramp) / (S32)1000 + (S32)U16_AY_Ubat[i];
   
    /* polyspace+7 MISRA-C3:D2.1 [Justified:Low] "S32_Ubat is declared" */
    /* Saturation of negative values */
    if (S32_Ubat < 0)
    {
        S32_Ubat = 0;
    }

    return (U16)S32_Ubat;
}

/*********************************************************************************************************
 *  Name                   : CanAppl_BusOffBegin
 *  Description            : BusOff begin application callback
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
static void CanAppl_BusOffBegin(void)
{
    BO_BusOffState = TRUE;

    /* Reset BusOff Enable Condition */
    (void)Dem_SetEnableCondition(DemConf_DemEnableCondition_DemEnableCondition_BusOff, FALSE);

    /* Request COMM_FULL_COMMUNICATION in case of BusOff (to avoid BUS_SLEEP) */
    (void)ComM_RequestComMode(ComMConf_ComMUser_BusOff, COMM_FULL_COMMUNICATION);
}

/*********************************************************************************************************
 *  Name                   : CanAppl_BusOffEnd
 *  Description            : BusOff end application callback
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
static void CanAppl_BusOffEnd(void)
{
    BO_BusOffState = FALSE;

    /* Set BusOff Enable Condition */
    (void)Dem_SetEnableCondition(DemConf_DemEnableCondition_DemEnableCondition_BusOff, TRUE);

    /* Request COMM_NO_COMMUNICATION when BusOff symptom is gone*/
    (void)ComM_RequestComMode(ComMConf_ComMUser_BusOff, COMM_NO_COMMUNICATION);
}

/*********************************************************************************************************
 *  Name                   : DemDtc_BusOffHandling
 *  Description            : Handling of BusOff event (application side)
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
static void DemDtc_BusOffHandling(void)
{
    U8 BusOffState;
    
    /* Get the actual statis of DEM BusOff event */
    (void)Dem_GetEventStatus(DemConf_DemEventParameter_DTC_0x010014, &BusOffState);

    /* Substract only the TEST FAILED bit */
    BusOffState &= DTC_TEST_FAILED_BIT;

    /* If the new BusOffState differs from the old one -> trigger the CanAppl callbacks */
    if(BusOffState != BusOffStateOld)
    {
        if(BusOffState == 1)
        {
            /* BusOff active */
            CanAppl_BusOffBegin();
        }
        else
        {
            /* BusOff not active */
            CanAppl_BusOffEnd();
        }
    }

    /* Save the current state for next check */
    BusOffStateOld = BusOffState;

    /* When BusOff occurrs, we prevent sleep and the CAN controller enough time to recover from BusOff Error.
     * In case the BusOff error persists for more than 10s, we consider that the error cannot be healed, 
     * therefore we reset the ComM request in order to allow sleep. */
    /* polyspace+1 MISRA-C3:D2.1 [Justified:Low] "No declaration needed" */
    if(BO_BusOffState == TRUE)
    {
        if(BusOffDebounce < 1000)
        {
            BusOffDebounce++;
        }

        if(BusOffDebounce == 1000)
        {
            /* Request COMM_NO_COMMUNICATION when BusOff symptom is gone*/
            (void)ComM_RequestComMode(ComMConf_ComMUser_BusOff, COMM_NO_COMMUNICATION);
        }
    }
    else
    {
        BusOffDebounce = 0;
    }
}

/*===============================================================================================*/
/* Public Functions */
/*===============================================================================================*/

/*********************************************************************************************************
 *  Name                   : DemDtc_MainFunction
 *  Description            : Calls all the private functions of DemDtc module
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
/* polyspace+10 MISRA-C3:2.2 [Justified:Low] "Function DTC_0x010005_Implementation() is called when NFC_DIAGNOSTICS_PRESENT is defined" */
void DemDtc_MainFunction(void)
{
    DTC_0x010000_Implementation();
    DTC_0x010001_Implementation();
    DTC_0x010003_Implementation();
    DTC_0x010002_Implementation();
    DTC_0x010004_Implementation();
    DTC_0x010005_Implementation();
    DTC_0x010011_Implementation();
    DTC_0x010013_Implementation();
    DemDtc_BusOffHandling();
}

/*********************************************************************************************************
 *  Name                   : Com_Callback_NVEM_Abschaltstufe_Timeout
 *  Description            : COM timeout indication
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
/* polyspace+30 MISRA-C3:5.1 [Not a defect:Low] "the name of functions is clearly different" */
FUNC(void, COM_APPL_CODE) Com_Callback_NVEM_Abschaltstufe_Timeout(void)
{
    BO_NVEM_Abschaltstufe_Timeout = TRUE;
}

/*********************************************************************************************************
 *  Name                   : Com_Callback_NVEM_Abschaltstufe_Rx_Indication
 *  Description            : COM timeout indication
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
FUNC(void, COM_APPL_CODE) Com_Callback_NVEM_Abschaltstufe_Rx_Indication(void)
{
    BO_NVEM_Abschaltstufe_Timeout = FALSE;
}

/*********************************************************************************************************
 *  Name                   : Com_Callback_MDK_Function_State_Rx_Indication
 *  Description            : COM timeout indication
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
FUNC(void, COM_APPL_CODE) Com_Callback_MDK_Function_State_Rx_Indication(void)
{
    BO_MDK_Function_State_Timeout = FALSE;
}

/*********************************************************************************************************
 *  Name                   : Com_Callback_MDK_Function_State_Timeout
 *  Description            : COM timeout indication
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
/* polyspace+1 MISRA-C3:5.1 [Not a defect:Low] "C99 standard is used to compile, Huf naming convention" */
FUNC(void, COM_APPL_CODE) Com_Callback_MDK_Function_State_Timeout(void)
{
    BO_MDK_Function_State_Timeout = TRUE;
}

/*********************************************************************************************************
 *  Name                   : CanSM_BusOffEnd
 *  Description            : BusOff end CanSM callback
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
FUNC(void, CANSM_APPL_CODE) CanSM_BusOffEnd( NetworkHandleType  NetworkHandle )
{
    (void)NetworkHandle;

    /* Trigger the sennding of the fastest PDU to indicate that the BusOff event is gone */
    Com_TriggerIPDUSend(ComConf_ComIPdu_NFC_TGS_01_XIX_HCP4_CANFD01_6816bdec_Tx);

	/* Reset BusOff flag */ 
    BO_BusOffStateCanSM = FALSE;
}

/*********************************************************************************************************
 *  Name                   : CanSM_BusOffBegin
 *  Description            : BusOff begin CanSM callback
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
/* polyspace+1 MISRA-C3:8.13 [Justified:Low] "A const pointer not possible here" */
FUNC(void, CANSM_APPL_CODE) CanSM_BusOffBegin( NetworkHandleType  NetworkHandle, P2VAR(uint8, AUTOMATIC, CANSM_APPL_VAR) OnlineDelayCyclesPtr )
{
	(void)NetworkHandle;
	(void)OnlineDelayCyclesPtr;
	
	/* Set BusOff flag for tDiagStart timer activation */ 
    BO_BusOffStateCanSM = TRUE;
}

/* ****************************************************************************
 * Appl_Dem_GeneralCBStatusEvt_GeneralCallbackEventUdsStatusChanged
 *****************************************************************************/
/*!
 * \brief         Global event status change notification
 *
 * \details       Notification that the UDS status of an event has changed.
 * \note          Since the event status can change concurrently, the status
 *                values passed by this function are not necessarily correct.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[in]     EventUdsStatusOld
 *                UDS status before the status change
 * \param[in]     EventUdsStatusNew
 *                UDS status after the status change
 *
 * \return        The return value is ignored
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DEM_APPL_CODE) Appl_Dem_GeneralCBStatusEvt_GeneralCallbackEventUdsStatusChanged(
    Dem_EventIdType EventId,
    Dem_UdsStatusByteType EventUdsStatusOld,
    Dem_UdsStatusByteType EventUdsStatusNew)
{
    (void)EventId;
    (void)EventUdsStatusOld;

    /* Change the KD bit status to active if any DTC gets the TEST FAILED bit set */
    if ((EventUdsStatusNew & DTC_TEST_FAILED_BIT) != 0u)
    {
        KdBitStatus = KdBitActive;
    }
    return E_OK;
}

/*********************************************************************************************************
 *  Name                   : DTC_0x010000_ClearEventAllowedCbk
 *  Description            : ClearEventAllowed callback for DTC 0x010000
 *  Parameters             : boolean*
 *  Return                 : none
 *********************************************************************************************************/
Std_ReturnType DTC_0x010000_ClearEventAllowedCbk(boolean* ClearAllowed)
{
    if(BO_ResetHealInhStatus == TRUE)
    {
        /* The DTC can be cleared */
        *ClearAllowed = TRUE;
    }
    else
    {
        /* The DTC cannot be cleared */
        *ClearAllowed = FALSE;
    }
    
    return E_OK;
}

/*********************************************************************************************************
 *  Name                   : DTC_0x010007_ClearEventAllowedCbk
 *  Description            : ClearEventAllowed callback for DTC 0x010007
 *  Parameters             : boolean*
 *  Return                 : none
 *********************************************************************************************************/
Std_ReturnType DTC_0x010007_ClearEventAllowedCbk(boolean* ClearAllowed)
{
    if(BO_ResetHealInhStatus == TRUE)
    {
        /* The DTC can be cleared */
        *ClearAllowed = TRUE;
    }
    else
    {
        /* The DTC cannot be cleared */
        *ClearAllowed = FALSE;
    }
    
    return E_OK;
}

/*********************************************************************************************************
 *  Name                   : DTC_0x010008_ClearEventAllowedCbk
 *  Description            : ClearEventAllowed callback for DTC 0x010008
 *  Parameters             : boolean*
 *  Return                 : none
 *********************************************************************************************************/
Std_ReturnType DTC_0x010008_ClearEventAllowedCbk(boolean* ClearAllowed)
{
    if(BO_ResetHealInhStatus == TRUE)
    {
        /* The DTC can be cleared */
        *ClearAllowed = TRUE;
    }
    else
    {
        /* The DTC cannot be cleared */
        *ClearAllowed = FALSE;
    }
    
    return E_OK;
}
/*********************************************************************************************************
 *  Name                   : DTC_0x010009_ClearEventAllowedCbk
 *  Description            : ClearEventAllowed callback for DTC 0x010009
 *  Parameters             : boolean*
 *  Return                 : none
 *********************************************************************************************************/
Std_ReturnType DTC_0x010009_ClearEventAllowedCbk(boolean* ClearAllowed)
{
    if(BO_ResetHealInhStatus == TRUE)
    {
        /* The DTC can be cleared */
        *ClearAllowed = TRUE;
    }
    else
    {
        /* The DTC cannot be cleared */
        *ClearAllowed = FALSE;
    }
    
    return E_OK;
}

/*********************************************************************************************************
 *  Name                   : DemDtc_ClearDTCInformationActions
 *  Description            : Resets variables for dequalification in case of service 0x14 execution 
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
void DemDtc_ClearDTCInformationActions(void)
{
    /* Reset the tDiagStart counter */
    U8_tDiagStartCnt = 0;

    /* Change KD Bit status to inactive */
    KdBitStatus = KdBitInactive;
}

/*********************************************************************************************************
 *  Name                   : DemDtc_GetTimestamp
 *  Description            : SnapshotDataRecord timestemp information 
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
Std_ReturnType DemDtc_GetTimestamp(uint8* Buffer)
{
    /* Locals */
    U8 year, month, day, hour, minute, second, i;
    
    /* Initialize DEM buffer with 0 */
    for(i = 0; i < 5; i++)
    {
        Buffer[i] = 0;
    }

    /* Populate DEM buffer */
    Buffer[0] = year >> 6;
    Buffer[1] = (year << 2) | (month >> 2);
    Buffer[2] = (month << 6) | (day << 1) | (hour >> 4);
    Buffer[3] = (hour << 4) | (minute >> 2);
    Buffer[4] = (minute << 6) | second; 

    return E_OK;
}

/*********************************************************************************************************
 *  Name                   : DemDtc_GetSupplyVoltage
 *  Description            : SnapshotDataRecord supply voltage information 
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
Std_ReturnType DemDtc_GetSupplyVoltage(uint8* Buffer)
{
    /* Calculate the physical value of the battey voltage, with a resolution of 0.1 */
    *Buffer = (U8)(AdcToVoltage(BatSup_getVoltageValue()) / (U16)100);
    
    return E_OK;
}

/*********************************************************************************************************
 *  Name                   : DemDtc_GetKmReading
 *  Description            : SnapshotDataRecord KM reading information 
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
Std_ReturnType DemDtc_GetKmReading(uint8* Buffer)
{
    U32 KmReadingTemp;
    U8 tmpArray[3];

    /* Get the CAN value */ 

    /* Convert the 20 bit signal into an array */
    tmpArray[0] = (U8)((KmReadingTemp & (U32)0xF0000) >> 16);
    tmpArray[1] = (U8)((KmReadingTemp & (U32)0xFF00) >> 8);
    tmpArray[2] = (U8)(KmReadingTemp & (U32)0xFF);

    /* Populate DEM buffer */
    (void)memcpy(Buffer, &tmpArray[0], 3);

    return E_OK;
}

/*********************************************************************************************************
 *  Name                   : DemDtc_GetVehicleSpeed
 *  Description            : SnapshotDataRecord vehicle speed information 
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
Std_ReturnType DemDtc_GetVehicleSpeed(uint8* Buffer)
{
    U16 VehicleSpeedTemp;
    U8 tmpArray[2];

    /* Get the CAN value */ 

    /* Convert the 20 bit signal into an array */
    tmpArray[0] = (U8)((VehicleSpeedTemp & (U16)0xFF00) >> 8);
    tmpArray[1] = (U8)(VehicleSpeedTemp & (U16)0xFF);

    /* Populate DEM buffer */
    (void)memcpy(Buffer, &tmpArray[0], 2);

    return E_OK;
}

/*********************************************************************************************************
 *  Name                   : DemDtc_KL15Status
 *  Description            : SnapshotDataRecord KL15 information 
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
Std_ReturnType DemDtc_KL15Status(uint8* Buffer)
{
    /* Get the CAN value */ 

    return E_OK;
}

/*********************************************************************************************************
 *  Name                   : DemDtc_TimeIndicationRead
 *  Description            : SnapshotDataRecord TimeIndication information 
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
Std_ReturnType DemDtc_TimeIndicationRead(uint8* Buffer)
{
    /* Always return 0 */ 
    *Buffer = 0u;

    return E_OK;
}

/*********************************************************************************************************
 *  Name                   : DemDtc_NvM_JobErrorNotification
 *  Description            : DemDtc job error notification function (called by Fee)
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
void DemDtc_NvM_JobErrorNotification(void)
{
    switch(MemIf_GetJobResult(MEMIF_DEVICE_ID))
    {
        case MEMIF_JOB_FAILED:
        (void)Dem_SetEventStatus(DemConf_DemEventParameter_DTC_0x010008, DEM_EVENT_STATUS_FAILED);
        break;

        default:
            /*do nothing*/
        break;
    }

    /* Call the NvM Job error notification callback */
    NvM_JobErrorNotification();
}

/*===============================================================================================*/
/* End of file */
/*===============================================================================================*/