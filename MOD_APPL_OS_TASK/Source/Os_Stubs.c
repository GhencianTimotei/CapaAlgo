/* polyspace MISRA-C3:1.1 [Justified:Unset] "All macro definitions are needed." */
/*------------------------------------------------------------------------------------------------+
| File: Os_Stubs.c                                                                          |
+-------------------------------------------------------------------------------------------------+
| Project: Audi eTab                                                                              |
+-------------------------------------------------------------------------------------------------+
| Short description: In OS Task module is handled the implementation of all tasks which are       |
|				     running in ACTIVE mode.           											  |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
+------------------------------------------------------------------------------------------------*/

#include "Os_Private.h"
#include "Os.h"
#include "Os_Mcal.h"
#include "IntegrationTests.h"
#include "Dio.h"
#include "Fls.h"
#include "Fee.h"
#include "NvM.h"
#include "EcuM.h"
#include "ComM.h"
#include "CanIf.h"
#include "CanSM_EcuM.h"
#include "Can.h"
#include "Com.h"
#include "config.h"
#include "BatterySupervisor.h"
#include "Adc.h"
#include "sensor_sequencer.h"
#include "sensor_diag.h"
#include "ComStack_Types.h"
#include "NvmMng.h"
#include "can_appl.h"
#include "LDC3114.h"
#include "Rte_Dcm.h"
#include "EmergencyAccess.h"
#include "SchM_Com.h"
#include "SchM_CanSM.h"
#include "SchM_BswM.h"
#include "VA_Led.h"
#include "PlayProtection.h"
#include "SchM_CanNM.h"
#include "TimeService.h"
#include "Appl_Custom_ISO_TP.h"
#include "Dem_Lcfg.h"
#include "Dem_Cfg_Types.h"
#include "Dem_Dtc.h"
#include "WdgIf.h"
#include "CAN_DiagUsr.h"

/* polyspace < MISRA-C3:8.9 : Not a defect : Justify with annotations > No impact if the static variable declaration remains in file scope. */
static volatile StatusType ErrorCode;
static U8 U8_DTCsOnCANTestingTime = 0u;
static boolean FastNvmTasks = FALSE;
/* polyspace+1 MISRA-C3:8.9 [Justified:Low] "Variable is declared once here" */
static U8 LDC3114_interruptCounter = 0u;
/* polyspace+10 MISRA-C3:8.5 [Justified:Low] "functions imported here" */
extern FUNC(void, DEM_CODE) Dem_MainFunction(void);
extern FUNC(void, CANTP_CODE) CanTp_MainFunctionRx(void);
extern FUNC(void, CANTP_CODE) CanTp_MainFunctionTx(void);
 
/* polyspace < MISRA-C3:8.5 : Not a defect : Justify with annotations > Function is declared once here */
void vHandleLDCChStates(void);
TASK(Task_2_5ms)
{
    LDC3114_CyclicTask();
    LDC3114_syncErrorHandleLDC(LDC3114_E_NORMAL_POWER);

    /* call capacitive sensor task in case of LDC interrupt */
    if(bLdcIsrTriggered == LDC_INTERRUPT_OCCURRED)
    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    {
        LDC3114_SyncTimeout.U8_SyncTimeout_ACTIVE = 0;
        LDC3114_interruptCounter++;
        bLdcIsrTriggered = LDC_INTERRUPT_WAIT;
        #ifdef RS232_ON
            sensor_diag_data_out_UART();
        #endif
    }
    else
    {
        /* LDC interrupt does not occurred. SWR_657 */
        if(LDC3114_SyncTimeout.U8_SyncTimeout_ACTIVE >= U8_SYNC_TIMEOUT_ACTIVE_MS)
       /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
        {
            /* call capacitive sensor task in case of LDC interrupt does not occurred after extra delay */
            sequncer_sensor_handle_task(EN_ACTIVE_SENSOR_MODE);

            LDC3114_SyncTimeout.U8_SyncTimeout_ACTIVE = 0;
        }
        else
        {
            /*do nothing*/
        }
        LDC3114_SyncTimeout.U8_SyncTimeout_ACTIVE++;
    }

    if ((LDC3114_interruptCounter >= 4u) && (LDC3114_SyncTimeout.U8_SyncTimeout_ACTIVE >= 1u))
    {
        sequncer_sensor_handle_task(EN_ACTIVE_SENSOR_MODE);
        LDC3114_interruptCounter = 0u;
    }
    (void)TerminateTask();
}
TASK(Task_5ms)
{
    /* polyspace < MISRA-C3:2.2 : Not a defect : Justify with annotations > Should be kept for future usage */
    IntegrationTests_5ms();
    if(FastNvmTasks == FALSE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
        NvM_MainFunction();
    }

    vHandleLDCChStates();

    (void)TerminateTask();
}

TASK(Task_10ms)
{
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations> This function has no return */
    BswM_MainFunction(); /* PRQA S 2987 */ /* MD_Rte_2987 */
    EcuM_MainFunction();
    /* call schedulable entity */
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations> This function has no return */
    Can_MainFunction_Read();
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations> This function has no return */
    Can_MainFunction_Write();
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations> This function has no return */
    Com_MainFunctionRx();
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations> This function has no return */
    Com_MainFunctionTx();
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations> This function has no return */
    CanSM_MainFunction();
    /* call schedulable entity */
    ComM_MainFunction_0();
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations> This function has no return */
    /* polyspace < MISRA-C3:17.3: Not a defect : Justify with annotations > Function prototype is in Can.c */
    /* polyspace MISRA-C3:D4.4 [Justified:Unset] "For future use" */
    /*Nm_MainFunction();*/

    /* call schedulable entity */
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations> This function has no return */
    Can_MainFunction_BusOff();
    /* call schedulable entity */
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations> This function has no return */
    Can_MainFunction_Mode();
    /* call schedulable entity */
    /* call schedulable entity */
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations> This function has no return */
    Can_MainFunction_Wakeup();
    /* polyspace < MISRA-C3:17.3: Not a defect : Justify with annotations > Function prototype is in Can.c */
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations > Returned value not needed */
    CanTp_MainFunctionRx();
    /* polyspace < MISRA-C3:8.5 : Not a defect : Justify with annotations > Function is declared once here. */
    /* polyspace < MISRA-C3:8.3 :  Not a defect : Justify with annotations > Function use the same names and type */
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations > Return type is not needed here. */
    Dem_MainFunction();
    Dcm_MainFunction();
    CANDiagUsr_CyclicTask();
    /* polyspace < MISRA-C3:17.3: Not a defect : Justify with annotations > Function prototype is in Can.c */
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations>> Return type is not needed here. */
    CanTp_MainFunctionTx();
    /* polyspace+1 MISRA-C3:17.3 [Justified:Low] "This function will be taken from an extern library." */

    /* NM Timeout Handling */
    Com_Appl_NmTimeoutHandling();

    /* DemDtc main function */
    DemDtc_MainFunction();
    NfcDevMsg_SendMessage();
    (void)TerminateTask();
}

TASK(Task_25ms)
{
    ComM_MainFunction_0();
    BatSup_fastTask();
    PlayProt_mainRunnable();
    /* Play protection should be called before COM APP since signal publishing is play protection dependent */
    Com_Appl_CyclicTask();
	CanNM_Appl_CyclicTask();
    EmergencyAccess_Task();
    Tm_MainFunction();
    VA_LED_Task();
    (void)TerminateTask();
}

TASK(Task_100ms)
{
    WdgIf_setTrigger();
    (void)BatSup_idleTask();
    ComM_MainFunction_0();
    (void)Reset_SecAccBlockedFlag_after10Min();
    (void)TerminateTask();
}


/*************************************************************************************************************
 *  Name                 : TEST_Ipdu_DoorFunctions_FS_01
 *  Description          : Function callback called every time when frame DoorFunctions_FS_01 is received
 *  Return               : Always TRUE - to be able to take actions on frame received
 *  Critical/explanation : -
 *  Author               : bbarlea
 *************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
BOOL TEST_Ipdu_DoorFunctions_FS_01(PduIdType PduId, const PduInfoType* PduInfoPtr)
{
    return TRUE;
}

/*************************************************************************************************************
 *  Name                 : NFC_FS_Resp_development_message
 *  Description          : Function callback called every time when frame NFC_FS_Resp is transmitted
 *  Return               : TRUE - when development switch from NVM is 0x55 55
 *                          FALSE - otherwise
 *  Critical/explanation : -
 *  Author               : lmilita
 *************************************************************************************************************/
BOOL NFC_FS_Resp_development_message(PduIdType PduId, PduInfoType* PduInfoPtr)
{
    return DID_NFC_debugSwitch_NVM_param.U8_BYTE1;
}


void BackgroundTask(void)
{
    EcuM_LowPowerManager();
    EcuM_LowPowerManager();

    if(FastNvmTasks == TRUE)
    {
        Fls_MainFunction();
        Fee_MainFunction();
        NvM_MainFunction();
    }
}

void ErrorHook (Os_StatusType Error )
{
    ErrorCode = Error;
    switch (Error)
    {
        case E_OS_ACCESS:
            /* Handle error then return. */
            break;
        case E_OS_CALLEVEL:
            break;
        case E_OS_ID:
            /* task, resource or alarm parameter is invalid */
            break;
        case E_OS_LIMIT:
            /* Terminate. */
            /* ShutdownOS(Error);*/
            break;
        case   E_OS_NOFUNC:
            break;
        case E_OS_RESOURCE:
            break;
        case E_OS_STATE:
            break;
        case E_OS_VALUE:
            break;
        case E_OS_SYS_MTA:
            /*Multiple task activation*/
            break;
        case E_OS_SYS_TSK_Q_FULL:
            /* Task queue is full*/
            break;
        case E_OS_PARAM_POINTER:
            /*A null pointer was given as argument*/
            break;
        default:
	{
	    /*do nothing*/
	}
            break;
    }
}
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
void ShutdownHook ( Os_StatusType Error )
{
   EcuM_Shutdown();
}

void OsSetFastNvm(boolean FastNvm)
{
    FastNvmTasks = FastNvm;
}
