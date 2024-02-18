/* polyspace+1 MISRA-C3:1.1 [Justified:Low] "All macro definitions are needed." */
/*******************************************************************************
 * File: can_appl.c
 *******************************************************************************
 * Project: Audi eTab
 *******************************************************************************
 * Description:
 *      The file contains the implementation for CAN application and the NM messages
 *      that have to be sent on CAN.
 *******************************************************************************
 * Note:
 *******************************************************************************/


#include "EcuM.h"

/* Used interfaces from other modules */
#include "Mcu.h"
#include "Port.h"
#include "IntegrationTests.h"
#include "Os_Mcal.h"
#include "Dio.h"
#include "CanIf.h"
// #include "CanNm.h"
#include "CanSM_EcuM.h"
#include "Can.h"
#include "ComM.h"
#include "Com.h"
#include "Det.h"
// #include "Nm.h"
#include "PduR.h"
#include "BswM.h"
#include "Gpt.h"
#include "Fls.h"
#include "Fee.h"
#include "NvM.h"
#include "LPSPI.h"
#include "CDD_I2c.h"
#include "nvic.h"
#include "LDC3114.h"
#include "sensor_sequencer.h"
#include "EmergencyAccess.h"
#include "BatterySupervisor.h"
#include "MeasureSupply.h"
#include "S32K144.h"
#include "inductive_sensor_algo.h"
#include "sensor_algo.h"
#include "CDD_Mcl.h"
#include "NvmMng.h"
#include "can_appl.h"
#include "config.h"
#include "Dcm.h"
#include "Gpt_Lptmr.h"
#include "Icu.h"
#include "VA_Led.h"
#include "Pwm.h"
#include "TimeService.h"
#include "PlayProtection.h"
#include "Icu_Port_Ci.h"
#include "Icu_Reg_eSys_Port_Ci.h"
#include "WdgIf.h"
#include "Wdg.h"
#include "EcuM_Callout_Stubs.h"
#include "CAN_DiagUsr.h"
#include "Dem_Dtc.h"

/* PRIVATE MACROS AND CONSTANTS DEFINITION TO BE DONE IN THE CONFIG HEADER */
U16 GO_TO_RUN = 0;
#define BO_UNINITIALIZED  2u  /* tri-state boolean. uninitialized, false and true. */
/* how many capacitive measurements should be performed between two inductive measurements. */
#define NO_OF_CAPAS_BETWEEN_LDCS_NORMAL     8u 
#define NO_OF_CAPAS_BETWEEN_LDCS_ULPM       4u
#define NO_2 2u

/* polyspace+5 MISRA-C3:2.5 [Justified:Low] "Macro should be kept for future usage" */
#define ECUM_AUTHENTIF_VALUE    0x05u
#define ECUM_BASEFUNCTION_COMFORTLIGHT  32u
#define ECUM_DOORS_HATCHES  4u
#define ECUMCALL_100_MS_TASK_LP_PERIOD_U16          100U
#define ECUMCALL_200_MS_TASK_LP_PERIOD_U16          200U
#define ECUMCALL_500_MS_TASK_LP_PERIOD_U16          500U
#ifndef TESSY
/* polyspace+1 MISRA-C3:D4.9 [Justified:Low] "Macro used to facilitate easier configuration." */
#define HWREG(x)    (*((volatile unsigned long *)(x)))
#else
unsigned long HWREG_val;
unsigned long * HWREG_adr = &HWREG_val;
#define HWREG(x) *HWREG_adr
#endif
/* period time for wakeupda in LPM */
#define PERIODIC_WAKEUPS_NORMAL             25u
#define PERIODIC_WAKEUPS_ULTRA_LOW_POWER    50u
/* Private data-types */

/* Variable definition */
#ifdef RS232_ON
static U32 U32_Normal_Timing = 21u; /* basic timer value to generate 25ms (set by BSW) */
#else
static U32 U32_Normal_Timing = 23u; /* basic timer value to generate 25ms (set by BSW) */
#endif
static U8 U8_Task_Counter = 0u;
/* polyspace+2 MISRA-C3:8.5 [Justified:Low] "added here for the ease of code" */
extern const I2c_ConfigType I2c_PBCfgVariantPredefined;
static EcuM_WakeupSourceType EcuM_WakeupSource = 0u;
U8 EcuM_WakeUpLogged = EcuM_WAKE_UP_ENTER_SLEEP;
/* signal has a length of 56 bits */
U8 EcuM_calloutCanSignalNM_NFC_FS_FCAB[7] = {0u, 0u, 0u, 0u, 0u, 0u, 0u};

static U16 EcuMCall_200msTaskLpCounter_U16 = 0U;
static U8 EcuM_u8PeriodicWakeUp = 25u; 
static U16 EcuM_u16NormalLowTicks = 0u;
static U16 EcuM_u16normalHighTicks = 0u;
U8 EcuM_BusSleepActive = 0U;
wakeUpType EcuM_WakeUpType;

/* Private functions declaration */
static void EcuM_OnEnterSleep(void);
static void EcuM_OnSleepEntered(void);
static void EcuM_OnExitSleep(void);
static void EcuM_OnSleepExited(void);
static void EcuM_CANWakeUpIcuDisable(void);
static void EcuM_ClearNMsignals(void);
static void EcuM_EnableCanComByCAN(void);
static void EcuM_LPTMR0_EnableBypass(void);
static void ECUM_validWakeUpNotification(void);
static void EcuM_disableCanWakeUp(void);


/*--------------------------------------------------------
-------------  FUNCTIONS IMPLEMENTATION  -----------------
--------------------------------------------------------*/

#if(ECUM_CALLOUT_DRIVER_INIT_ZERO == STD_ON)
/*******************************************************************************
 * Name:        
 * Description: 
 * Parameters:  void
 * Return:      void
 *******************************************************************************/
void EcuM_AL_DriverInitZero(void)
{
    /*enable bus, memory and usage faults*/
    /* polyspace < MISRA-C3:10.1 : Not a defect : Justify with annotations > Left and right operand has same type */
    HWREG(0xE000ED24u) |= 0x00070000u;
    (void)CanIf_InitMemory();
    CanSM_InitMemory();
    (void)Can_InitMemory();
    ComM_InitMemory();
    Com_InitMemory();
    (void)PduR_InitMemory();
    /* polyspace < MISRA-C3:8.3, 8.5 : Not a defect : Justify with annotations > Function use the same names and type */
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations > Returened value is not needed here */
    Dcm_InitMemory();
    EcuM_SetWakeupEvent(ECUM_WKSOURCE_POWER);
}
#endif

#if(ECUM_CALLOUT_DRIVER_INIT_ONE == STD_ON)
/*******************************************************************************
 * Name:        
 * Description: 
 * Parameters:  void
 * Return:      void
 *******************************************************************************/
/* polyspace <MISRA-C3:D4.5 : Not a defect: Justify with annotations > no overlapping visibility */
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
void EcuM_AL_DriverInitOne(const EcuM_ConfigType* ConfigPtr)
{
    /* Initialise MCU Driver */
    Mcu_Init(&McuModuleConfiguration);
    /* Set the CPU Clock to the PLL */
    (void)Mcu_InitClock(McuClockSettingConfig_RUN);
    /* Wait until the PLL is locked */
    /* polyspace < MISRA-C3:15.6 : Not a defect : Justify with annotations> Does not affect the functionality, it works like a delay */
    while (Mcu_GetPllStatus() != MCU_PLL_LOCKED);
    /* Activate the PLL Clock */
    (void)Mcu_DistributePllClock();
    Wdg_init();
    /*Initialize port*/
    Port_Init(&PortConfigSet);
    /* Initialize GPT */

    (void)PduR_PreInit( PduR_Config_Ptr );
    BswM_PreInit( BswM_Config_Ptr );

    Dio_WriteChannel(DioConf_DioChannel_Dio_PTD0_CAN_SLP, STD_LOW);

    /* Initialize PWM */
    Pwm_Init(NULL);

    /*lint -restore */
    /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations > Returened value is not needed here */
    (void)Can_Init(Can_Config_Ptr);
    /*lint -restore */
    /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
    (void)CanIf_Init(CanIf_Config_Ptr);

    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations > Returened value is not needed here */
    CanTp_Init(CanTp_Config_Ptr);
    /*lint -restore */
    /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
    CanSM_Init(CanSM_Config_Ptr);
    //CanTp
    /*lint -restore */
    /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
    (void)PduR_Init(PduR_Config_Ptr);
    /*lint -restore */
    /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
    /*lint -restore */
    /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */    /*lint -restore */
    /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
    Com_Init(Com_Config_Ptr);
    //IpduM_Init(NULL_PTR);
    /*lint -restore */
    /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
    ComM_Init();

    Com_IpduGroupStart(ComConf_ComIPduGroup_CommunicationControlRx, TRUE);
    Com_IpduGroupStart(ComConf_ComIPduGroup_CommunicationControlTx, TRUE);
    Com_IpduGroupStart(ComConf_ComIPduGroup_AlwaysOnRx, TRUE);
    Com_IpduGroupStart(ComConf_ComIPduGroup_AlwaysOnTx, TRUE);

    Mcl_Init(&MclConfigSet_0 );
    /*lint -restore */
    /*lint -save -e534 *//* PRQA S 3109, 3200 1 */ /* MD_MSR_14.3, MD_BSWM_3200 */
    BswM_Init(NULL_PTR);
    Gpt_Init(&GptChannelConfigSet);
    /* Initialize ADC */
    Adc_init();
    /* Pre Initialize Dem */
    Dem_PreInit(NULL_PTR);
    /* Initialize FLS */
    Fls_Init(NULL_PTR);
    /* Initialize SPI */
    LPSPI0_init_master();
    /* polyspace < MISRA-C3:8.3, 8.5 : Not a defect : Justify with annotations > Function use the same names and type */
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations > Returened value is not needed here */
    Dcm_Init(NULL_PTR);
    (void)Icu_Init( NULL_PTR );

    EcuM_CANWakeUpIcuDisable();

    CAN_ApplInit();
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations > Tm_InitTimers function have void type */
    Tm_InitTimers();
}
#endif

#if(ECUM_CALLOUT_DRIVER_INIT_TWO == STD_ON)
/*******************************************************************************
 * Name:        
 * Description: 
 * Parameters:  void
 * Return:      void
 *******************************************************************************/
/* polyspace <MISRA-C3:D4.5 : Not a defect: Justify with annotations > no overlapping visibility */
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
void EcuM_AL_DriverInitTwo(const EcuM_ConfigType* ConfigPtr)
{
	MemIf_StatusType fee_status;
	NvM_RequestResultType NvMStatus;

    NVIC_EnableIRQ((uint8)48);
    NVIC_EnableIRQ((uint8)NVIC_PORTE_INT);
    NVIC_EnableIRQ((uint8)NVIC_CAN0_BUSOFF);
    NVIC_EnableIRQ((uint8)NVIC_CAN0_ERR);
    NVIC_EnableIRQ((uint8)NVIC_CAN0_PRETENDED_NTW);
    NVIC_EnableIRQ((uint8)NVIC_CAN0_MSGBUFF_0_15);
    NVIC_EnableIRQ((uint8)NVIC_CAN0_MSGBUFF_16_31);
    NVIC_EnableIRQ((uint8)NVIC_CAN0_MSGBUFF_32_47);
    NVIC_EnableIRQ((uint8)NVIC_CAN0_MSGBUFF_48_63);
    NVIC_EnableIRQ((uint8)NVIC_FTM0_CH0CH1);
    NVIC_EnableIRQ((uint8)NVIC_PORTC_INT);

	Fee_Init( NULL_PTR );

    /* polyspace < MISRA-C3:2.2 : Not a defect : Justify with annotations > Variable should be kept for future usage */
	fee_status = Fee_GetStatus();
    /* Trigger watchdog */
    WdgIf_setTrigger();
	do
	{
        Fee_MainFunction();
        Fls_MainFunction();
        fee_status = Fee_GetStatus();
	}while (fee_status!= MEMIF_IDLE);
	NvM_Init();
	NvM_ReadAll();
	do
	{
		NvM_MainFunction();
		Fee_MainFunction();
		Fls_MainFunction();

		(void)NvM_GetErrorStatus(NvMConf___MultiBlockRequest, &NvMStatus);
	/* polyspace < MISRA-C3:9.1 : Not a defect : Justify with annotations > Variable is read in do while cycle*/	
	/* polyspace < RTE:NIV : Not a defect : Justify with annotations > Variable is read in do while cycle*/
	}while(NvMStatus == NVM_REQ_PENDING);
    /* Trigger watchdog */
    WdgIf_setTrigger();
    /* Must be called after NvM_ReadAll, but before Os_TimerStart */
    EmergencyAccess_checkParameters();
    ComM_CommunicationAllowed(0, TRUE);
    (void)ComM_RequestComMode(0, COMM_FULL_COMMUNICATION);

    /* Initialize I2C */
    I2c_Init(NULL_PTR);

    LDC3114_Init();
    Dio_WriteChannel(DioConf_DioChannel_Dio_PTD2_Ind_Sensor_IO, 1u);

    BatSup_initTask();
    SwVersionNumber_Updater();

    sequencer_sensor_init_Task();
    
    /*Initialize SysTick timer*/
    Os_TimerInit();
    /*Start SysTick timer*/
    Os_TimerStart();
    /* polyspace <MISRA-C3:D4.4 : Not a defect: Justify with annotations > Should be kept for future usage */
    /*EcuM_RequestRUN(ECUM_USER_KEEP_RUN_STATE);*/
    VA_LED_Init();
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations> This function has no return */
    /* polyspace < MISRA-C3:8.3,8.5 : Not a defect : Justify with annotations > Function use the same names and type */
    PlayProt_init();
#ifdef RS232_ON
    OC_SignalMng_Init_V();
#endif
}
#endif

/*******************************************************************************
 * Name:        
 * Description: 
 * Parameters:  void
 * Return:      void
 *******************************************************************************/
/* polyspace <MISRA-C3:D4.5 : Not a defect: Justify with annotations > no overlapping visibility */
void EcuM_AL_DriverInitThree(const EcuM_ConfigType* ConfigPtr)
{
    /* polyspace MISRA-C3:D4.4 [Justified:Unset] "Should be kept for future usage" */
    /* called after NVM_ReadAll(); */
	Dem_Init(NULL_PTR);
}

/*******************************************************************************
 * Name:        
 * Description: 
 * Parameters:  void
 * Return:      void
 *******************************************************************************/
void EcuM_OnEnterRun(void)
{
   
}

/*******************************************************************************
 * Name:        
 * Description: 
 * Parameters:  void
 * Return:      void
 *******************************************************************************/
void EcuM_OnGoSleep(void)
{
    NvM_RequestResultType NvMStatus;

    /* Indicate end of current WarmUpCycle / PowerCycle */
    (void)Dem_SetOperationCycleState(DemConf_DemOperationCycle_PowerCycle, DEM_CYCLE_STATE_END);
    (void)Dem_SetOperationCycleState(DemConf_DemOperationCycle_WarmUpCycle, DEM_CYCLE_STATE_END);
    Set_WUCState(WUC_Init);

    /* Shutdown Dem before NvM_WriteAll call */
    Dem_Shutdown();

    NvM_WriteAll();
    /* Trigger watchdog */
    WdgIf_setTrigger();
    do
    {
        NvM_MainFunction();
        Fee_MainFunction();
        Fls_MainFunction();

        (void)NvM_GetErrorStatus(NvMConf___MultiBlockRequest, &NvMStatus);
        /* polyspace < MISRA-C3:9.1 : Not a defect : Justify with annotations > Variable is read in do while cycle*/
        /* polyspace < RTE:NIV : Not a defect : Justify with annotations > Variable is read in do while cycle*/
    }while(NvMStatus == NVM_REQ_PENDING);
}

/*******************************************************************************
 * Name:        
 * Description: 
 * Parameters:  void
 * Return:      void
 *******************************************************************************/
void EcuM_OnGoOffOne(void)
{
   Dem_Shutdown();
}

/*******************************************************************************
 * Name:        
 * Description: 
 * Parameters:  void
 * Return:      void
 *******************************************************************************/
EcuM_WakeupReactionType EcuM_OnWakeupReaction(EcuM_WakeupReactionType wact)
{
   /* todo nmicule dummy implementation to solve compiler warning */
   EcuM_WakeupReactionType RetVal;

   RetVal = wact;

   return RetVal;
}
/* LPTMR0, clock disable prescalar, 1 tick is 1ms*/
static void EcuM_LPTMR0_EnableBypass(void) 
{
	LPTMR0->PSR |= (U32) (LPTMR_PSR_PBYP_MASK);
}
/*******************************************************************************
 * Name:        
 * Description: 
 * Parameters:  void
 * Return:      void
 *******************************************************************************/
void EcuM_SleepActivity(void)
{
    BOOL BO_PIF0_Valid = BO_UNINITIALIZED;
    U8 EcuM_ultraLowPowerMode = 0;
    U8 EcuM_nrOfCapaMeasBetweenLDCS = NO_OF_CAPAS_BETWEEN_LDCS_ULPM;
    U32 U32_LDC_Elapsed_Time = 0u;
    U32 U32_Half_LDC_Normal_Time = 0u;
    EN_SENSOR_MODE EN_SENSOR_MODE_Capa_ESM_Active = EN_NORMAL_SENSOR_MODE;

    /* Trigger watchdog */
    WdgIf_setTrigger();
        // EcuM_ultraLowPowerMode = NfcFuncGateway__GetESMStatus();
    if(EcuM_ultraLowPowerMode == 0)
    {
        /* normal state*/
        EcuM_u8PeriodicWakeUp = PERIODIC_WAKEUPS_NORMAL;
        EcuM_u16NormalLowTicks = U16_Normal_Low_Ticks;
        EcuM_u16normalHighTicks = U16_Normal_High_Ticks;
        EcuM_nrOfCapaMeasBetweenLDCS = NO_OF_CAPAS_BETWEEN_LDCS_NORMAL; 
        EN_SENSOR_MODE_Capa_ESM_Active = EN_NORMAL_SENSOR_MODE;
        /* First time in normal coming from ULP */
        if (U32_Normal_Timing > U16_Normal_High_Ticks) 
        {
            U32_Normal_Timing = 23u;
        }
    }
    else
    {
        /* ultra low power mode */
        EcuM_u8PeriodicWakeUp = PERIODIC_WAKEUPS_ULTRA_LOW_POWER;
        EcuM_u16NormalLowTicks = U16_Normal_Low_Ticks * 2u;
        EcuM_u16normalHighTicks = U16_Normal_High_Ticks * 2u;
        EcuM_nrOfCapaMeasBetweenLDCS = NO_OF_CAPAS_BETWEEN_LDCS_ULPM; 
        EN_SENSOR_MODE_Capa_ESM_Active = EN_LOWPOWER_SENSOR_MODE;
        /* First time in ULP coming from normal */
        if (U32_Normal_Timing < U16_Normal_Low_Ticks * 2u) 
        {
            U32_Normal_Timing = 46u;
        }
    }

    if ((ECUM_WKSOURCE_NONE == EcuM_GetValidatedWakeupEvents())
#if (ECUM_VALIDATION_TIMEOUT_ENABLED == STD_ON)
            && (ECUM_WKSOURCE_NONE == EcuM_GetPendingWakeupEvents())
#endif
    )
    {
        ECUM_DISABLE_ALL_INTERRUPTS();        /*According to AUTOSAR procedure, Mcu_SetMode should be called in protected session */
        Mcu_SetMode(MCU_MODE_VLPS);

        /* check if exited deep sleep because of LDC interrupt*/
        if( LDC_INTERRUPT_OCCURRED == bLdcIsrTriggered)
        {
            /* In case of LDC interrupt. */
            BO_PIF0_Valid = TRUE;
            /* implementation of SWR_1713*/
            /* Store the elapsed time value from timer. | +1 -> assuming that LDC interrupt takes 1.something ms*/
            U32_LDC_Elapsed_Time = U32_Normal_Timing - U32_LDC_Remaining_Time + 1u;
            /* Store the half of value which was loaded in timer at the beginning. */
            U32_Half_LDC_Normal_Time = U32_Normal_Timing / NO_2;
            /* Verify we are doing EcuM_nrOfCapaMeasBetweenLDCS tasks, not more or less */
            if (U8_Task_Counter > EcuM_nrOfCapaMeasBetweenLDCS)
            {
                U32_Normal_Timing += 1u;
                /* Apply the timing correction and keep the value between thresholds. SWR_1716*/
                U32_Normal_Timing = ((U32_Normal_Timing > EcuM_u16normalHighTicks)?EcuM_u16normalHighTicks:U32_Normal_Timing);
            }
            else if (U8_Task_Counter < EcuM_nrOfCapaMeasBetweenLDCS)
            {
                U32_Normal_Timing -= 1;
                /* Apply the timing correction and keep the value between thresholds. SWR_656*/
                U32_Normal_Timing = ((U32_Normal_Timing < EcuM_u16NormalLowTicks)?EcuM_u16NormalLowTicks:U32_Normal_Timing);
            }
            else if(U32_Half_LDC_Normal_Time  > U32_LDC_Elapsed_Time)
            {
                /* Take the difference between half of period and elapsed period for timer and spread it to next 8 samples. SWR_1718*/
                /* Round up the computation. Workaround for the bad timer resolution (1ms) */
                U32_Normal_Timing -= (U32)((U32_Half_LDC_Normal_Time - U32_LDC_Elapsed_Time + (U32)(EcuM_nrOfCapaMeasBetweenLDCS / NO_2)) / EcuM_nrOfCapaMeasBetweenLDCS);
                /* Apply the timing correction and keep the value between thresholds. SWR_656*/
                U32_Normal_Timing = ((U32_Normal_Timing < EcuM_u16NormalLowTicks)?EcuM_u16NormalLowTicks:U32_Normal_Timing);
            }
            else
            {
                /* Take the difference between half of period and elapsed period for timer and spread it to next 8 samples. SWR_1718*/
                /* if the computation is bigger than 0.5 decrease 1 from the sleep period. Workaround for the bad timer resolution (1ms) */
                U32_Normal_Timing += (U32)((U32_LDC_Elapsed_Time - U32_Half_LDC_Normal_Time + (U32)(EcuM_nrOfCapaMeasBetweenLDCS / NO_2)) / EcuM_nrOfCapaMeasBetweenLDCS);
                /* Apply the timing correction and keep the value between thresholds. SWR_1716*/
                U32_Normal_Timing = ((U32_Normal_Timing > EcuM_u16normalHighTicks)?EcuM_u16normalHighTicks:U32_Normal_Timing);
            }
            U8_Task_Counter = 0u;
        }
        else
        {  
            /* In case of timer interrupt. */
            BO_PIF0_Valid = FALSE;
            /* Set the timer for a normal period */
            Gpt_StopTimer(GptConf_GptChannelConfiguration_GptChannelConfiguration_LPTMR);
            Gpt_StartTimer(GptConf_GptChannelConfiguration_GptChannelConfiguration_LPTMR, U32_Normal_Timing);
        }

        ECUM_ENABLE_ALL_INTERRUPTS();

        /* check if the wake up reason was the timer */
        if(FALSE == BO_PIF0_Valid)
        {
            U8_Task_Counter++;
            /* Execute 25ms sample time tasks. SWR_654*/
            EcuMCall_200msTaskLpCounter_U16 += EcuM_u8PeriodicWakeUp;
            

            PlayProt_mainRunSleep();
            sequncer_sensor_handle_task(EN_SENSOR_MODE_Capa_ESM_Active);

            NVIC_EnableIRQ(39);

            vHandleLDCChStates();
            NVIC_DisableIRQ(39);


            if(EcuMCall_200msTaskLpCounter_U16 >= ECUMCALL_200_MS_TASK_LP_PERIOD_U16)
            {
                EcuMCall_200msTaskLpCounter_U16 = 0U;

                LDC3114_syncErrorHandleLDC(LDC3114_E_LOW_POWER);
                /* Inc 3196 for same issue in V4 */
                /* Since in normal we don't have an OS, if idle was not called we have to call fast*/
                if(BatSup_idleTask() == 0u)
                {
                    BatSup_fastTask();
                }
            }
            else
            {
                BatSup_fastTask();
            }

            /* polyspace < MISRA-C3:13.5 : Not a defect : Justify with annotations> operator not contain side effects*/
            if (TRUE == isAlgoActive())
            {
                EcuM_SetWakeupEvent(ECUM_WAKEUP_ALGO);
                EcuM_setWakeUpSource(ECUM_WAKEUP_ALGO);
            }
            else
            {
                /*do nothing*/
            }
        }
        /* polyspace < MISRA-C3:14.3 : Not a defect : Justify with annotations> Condition always true. Should be kept for future usage */
	    else if(TRUE == BO_PIF0_Valid)
        {
            /* set the timer for the next half period until the capacitive acquisition */
            /* Wake up reason was LDC. Execute LDC Task. SWR_653*/
            LDC3114_CyclicTask();
            Gpt_StopTimer(GptConf_GptChannelConfiguration_GptChannelConfiguration_LPTMR);
            Gpt_StartTimer(GptConf_GptChannelConfiguration_GptChannelConfiguration_LPTMR, (U32_Normal_Timing/2u) - 1u); /* assuming that LDC interrupt takes 1.something ms */
            /* After LDC task we have to clear flag which was set in ISR. */
            bLdcIsrTriggered = LDC_INTERRUPT_WAIT;
        }
        else
        {
            /* Other reason of wake up. Possible error. */
            /* do nothing and go back in deep sleep. */
        }
    }
    else
    {
        /*do nothing*/
    }
}


/*******************************************************************************
 * Name:        
 * Description: 
 * Parameters:  void
 * Return:      void
 *******************************************************************************/
/* polyspace <MISRA-C3:D4.5 : Not a defect: Justify with annotations > no overlapping visibility */
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
void EcuM_CheckWakeup(EcuM_WakeupSourceType wakeupSource)
{
   /* dummy implementation */
   return;
}

/*******************************************************************************
 * Name:        
 * Description: 
 * Parameters:  void
 * Return:      void
 *******************************************************************************/
/* polyspace <MISRA-C3:D4.5 : Not a defect: Justify with annotations > no overlapping visibility */
/* polyspace < MISRA-C3:8.3 : Not a defect : Justify with annotations > Function use the same names and type */
void EcuM_McuSetMode(U8 mode)
{
    /* SWS_1242 */
    /* example of implementation for RL78 controller - needs to be adapted by integrator
    * more states can be added depending of the defined sleep modes, ECUM_NORMAL_MCU_MODE is mandatory for all sleep modes
    * and ECUM_POLLING_MODE is mandatory for Sleep Seq II */
    switch (mode)
    {
        case ECUM_POLLING_MODE:
        {
            /* Trigger watchdog */
            WdgIf_setTrigger();
            EcuM_OnEnterSleep();
            (void)Mcu_InitClock(McuClockSettingConfig_VLPR);
            EcuM_OnSleepEntered();
            WdgIf_setModeVLPR();
        }
        break;

        case ECUM_NORMAL_MCU_MODE:
        {
            WdgIf_setModeRun();
            /* Trigger watchdog */
            WdgIf_setTrigger();
            EcuM_OnExitSleep();
            /* Set the CPU Clock to the PLL */
            (void)Mcu_InitClock(McuClockSettingConfig_RUN);

            /* polyspace < MISRA-C3:15.6 : Not a defect : Justify with annotations> Does not affect the functionality, it works like a delay */
            while (Mcu_GetPllStatus() != MCU_PLL_LOCKED);
            /* Activate the PLL Clock */
            (void)Mcu_DistributePllClock();
            EcuM_OnSleepExited();
        }
        break;

        default:
            /* do nothing */
            break;
    }
}



/************************ Local Function Definition ************************/

/*******************************************************************************
 * Name:        
 * Description: 
 * Parameters:  void
 * Return:      void
 *******************************************************************************/
static void EcuM_OnEnterSleep(void)
{
    (void)LDC3114_SetLdcPowerMode(LDC3114_E_LOW_POWER);
    Induictive_Algo_Set_Debounce_Normal();
    /* Has to be one of the first steps inthe sleep enter process, since it needs PWM */
    VA_LED_turnOffLED();
    LDC3114_SyncTimeout.U8_SyncTimeout_ACTIVE = 0;
    EcuM_resetWakeUpSource();
}

/*******************************************************************************
 * Name:        
 * Description: 
 * Parameters:  void
 * Return:      void
 *******************************************************************************/
static void EcuM_OnSleepEntered(void)
{
    EcuMCall_200msTaskLpCounter_U16 = 0U;
    /* Icu_Init is called here because we want to reactivate the Icu channel for CAN Wakeup (needed only in normal mode) */
    (void)Icu_Init( NULL_PTR );
    /* Disable SysTick */
    Os_TimerStop();
    Tm_EnterLPM();
    LPSPI0_ChangePeripheralClockInput(LPSPI0_CLOCK_4_MHZ_E);
    /* set the timer for a full (25ms). */
    Gpt_StopTimer(GptConf_GptChannelConfiguration_GptChannelConfiguration_LPTMR);
	EcuM_LPTMR0_EnableBypass();
    Gpt_StartTimer(GptConf_GptChannelConfiguration_GptChannelConfiguration_LPTMR, U32_Normal_Timing);
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations > Returened value is not needed here */
    (void)Gpt_Lptmr_EnableInterrupt();
    Gpt_EnableWakeup(GptConf_GptChannelConfiguration_GptChannelConfiguration_LPTMR);
    Gpt_SetMode(GPT_MODE_SLEEP);
    /* Enable the LPTMR ISR at the NVIC level. */ 
    NVIC_EnableIRQ((uint8)NVIC_LPTIMER);
    NVIC_EnableIRQ((uint8)NVIC_LPUART0_INT);
    /* NVIC_PORTE_INT is already enabled, needed for CAN wake-up ISR */
    NVIC_DisableIRQ((uint8)NVIC_CAN0_BUSOFF);
    NVIC_DisableIRQ((uint8)NVIC_CAN0_ERR);
    NVIC_DisableIRQ((uint8)NVIC_CAN0_PRETENDED_NTW);
    NVIC_DisableIRQ((uint8)NVIC_CAN0_MSGBUFF_0_15);
    NVIC_DisableIRQ((uint8)NVIC_CAN0_MSGBUFF_16_31);
    NVIC_DisableIRQ((uint8)NVIC_CAN0_MSGBUFF_32_47);
    NVIC_DisableIRQ((uint8)NVIC_CAN0_MSGBUFF_48_63);

    /* Enable again LDC and NFC channels because we reinitialized the ICU */
    /* If another ICU channel will be created it shall be enabled here also! */
    Icu_EnableNotification(IcuChannel_LDC_INTB_Interrupt);
    Icu_DisableEdgeDetection(IcuConf_IcuChannel_IcuChannel_NFC_REQ_Interrupt);
    Icu_DisableNotification(IcuConf_IcuChannel_IcuChannel_NFC_REQ_Interrupt);

    EmergencyAccess_goToSleep();
    (void)ComM_RequestComMode(0, COMM_NO_COMMUNICATION);
    Dio_WriteChannel(DioConf_DioChannel_Dio_PTD0_CAN_SLP, STD_HIGH);
	/* Lets Clear obsolete wake-up values */
    EcuM_ClearNMsignals();

    ECUM_DISABLE_ALL_INTERRUPTS();
    Mcu_SetMode(MCU_MODE_VLPR);
    ECUM_ENABLE_ALL_INTERRUPTS();

    Port_SetPinMode(PortConfigSet_PORT_E_PTE4_CAN_RX, PORT_GPIO_MODE);
    Icu_EnableNotification(IcuChannel_CanWakeup);
    /* nfcevtlog_addEvt(E_NFCEVT_BSW_LOW_PWR_ALLOW); */
	/* Change the normal time to include half more of 25ms (capa) sample between two 200ms (LDC) samples. */
    Gpt_StopTimer(GptConf_GptChannelConfiguration_GptChannelConfiguration_LPTMR);
    Gpt_StartTimer(GptConf_GptChannelConfiguration_GptChannelConfiguration_LPTMR, (U32_Normal_Timing / 2u));
#ifdef RS232_ON
    OC_SignalMng_Init_V();
#endif
}


/*******************************************************************************
 * Name:        
 * Description: 
 * Parameters:  void
 * Return:      void
 *******************************************************************************/
static void EcuM_OnExitSleep(void)
{
    Dio_WriteChannel(DioConf_DioChannel_Dio_PTD0_CAN_SLP, STD_LOW);
    ECUM_DISABLE_ALL_INTERRUPTS();
    Mcu_SetMode(MCU_MODE_RUN);
    ECUM_ENABLE_ALL_INTERRUPTS();
    NVIC_EnableIRQ((uint8)NVIC_CAN0_BUSOFF);
    NVIC_EnableIRQ((uint8)NVIC_CAN0_ERR);
    NVIC_EnableIRQ((uint8)NVIC_CAN0_PRETENDED_NTW);
    NVIC_EnableIRQ((uint8)NVIC_CAN0_MSGBUFF_0_15);
    NVIC_EnableIRQ((uint8)NVIC_CAN0_MSGBUFF_16_31);
    NVIC_EnableIRQ((uint8)NVIC_CAN0_MSGBUFF_32_47);
    NVIC_EnableIRQ((uint8)NVIC_CAN0_MSGBUFF_48_63);

    NVIC_DisableIRQ((uint8)NVIC_LPUART0_INT);
    NVIC_DisableIRQ((uint8)NVIC_LPTIMER);
    Gpt_StopTimer(GptConf_GptChannelConfiguration_GptChannelConfiguration_LPTMR);
    Gpt_SetMode(GPT_MODE_NORMAL);
    /* Enable notification for GPT configured timer interrupt */
    Gpt_EnableNotification(GptConf_GptChannelConfiguration_GptChannelConfiguration_Timer);
    Gpt_StartTimer(GptConf_GptChannelConfiguration_GptChannelConfiguration_Timer, 1000u);
    /* Enable NFC ISR notification */
    Icu_EnableEdgeDetection(IcuConf_IcuChannel_IcuChannel_NFC_REQ_Interrupt);
    Icu_EnableNotification(IcuConf_IcuChannel_IcuChannel_NFC_REQ_Interrupt);

    Set_WUCState(WUC_Unqualified);
}


/* polyspace:begin MISRA-C3:15.7 [Not a defect:Low] else block is not needed here */
/*******************************************************************************
 * Name:        
 * Description: 
 * Parameters:  void
 * Return:      void
 *******************************************************************************/
static void EcuM_OnSleepExited(void)
{
    EcuM_WakeupSourceType wakeUpReason;

    LPSPI0_ChangePeripheralClockInput(LPSPI0_CLOCK_24_MHZ_E);
    /* Re-enable ISR for the ADC conversion */ 
    NVIC_EnableIRQ(39);
    Tm_ExitLPM();
    Os_TimerInit();
    Os_TimerStart();
    (void)LDC3114_SetLdcPowerMode(LDC3114_E_NORMAL_POWER);
    Induictive_Algo_Set_Debounce_Active();

    wakeUpReason = EcuM_getWakeUpSource();
    EcuM_WakeUpLogged = EcuM_WAKE_UP_EXIT_SLEEP; 
    if(wakeUpReason != 0u)
    {
        /* Is CAN one of the wake-up sources ? */
        if ((wakeUpReason & ECUM_WAKEUP_CAN)!=0U)
        {
            EcuM_EnableCanComByCAN();
        }
        if ((wakeUpReason & ECUM_WAKEUP_ALGO)!=0U)
        {
            U8 u8SignalKY_Oeffnen_BetaetigungSignal = 0u;
            U8 algoStateEcum = 0u;
            /* ER_APPROACH reflects KY_Oeffnen_Annaeherung */
            u8SignalKY_Oeffnen_BetaetigungSignal = InductiveAlgo_getInductiveValue();
            PlayProt_writeInductiveValue(&u8SignalKY_Oeffnen_BetaetigungSignal);
            Algo_getErState(&algoStateEcum);
            PlayProt_writeUnlockValue(&algoStateEcum);

            if ( algoStateEcum != 0U || u8SignalKY_Oeffnen_BetaetigungSignal != 0U)
            {
                EcuM_EnableCanComByCAPA();
            }
            else
            {
                if(NvmMng_getEnableWakeUpByKessy())
                {
                        Algo_getVrState(&algoStateEcum);
                        PlayProt_writeLockValue(&algoStateEcum);
                        if(algoStateEcum != 0U)
                        {
                            EcuM_EnableCanComByCAPA();
                        }
                }
            }
        }
    }
#ifdef RS232_ON
    OC_SignalMng_Init_V();
#endif
}
/* polyspace:end MISRA-C3:15.7 [Not a defect:Low] else block is not needed here */

void REG_RMW32_func(U32 address, U32 mask, U32 value)
{
  REG_RMW32(address, mask, value);
}

static void EcuM_CANWakeUpIcuDisable(void)
{
    /* logical channel */
    VAR(Icu_Port_Ci_ChannelType, AUTOMATIC)   hwChannel;
    VAR(uint16,                  AUTOMATIC)   u16port; 
    VAR(uint16,                  AUTOMATIC)   u16pin;
    VAR(uint32,                  AUTOMATIC)   u32pinMask; 

    /* only handle Port_Ci channels */
    hwChannel = (Icu_Port_Ci_ChannelType)ICU_PORT_CI_CHANNELS(ICU_PORT_4_CH_4);
    u16port = (uint16)(PORT_CI_PORT_MASK((uint16)hwChannel));
    u16pin  = (uint16)(PORT_CI_PIN_MASK((uint16)hwChannel));
    u32pinMask = (uint32)(BIT0 << u16pin);
    
    
    /* Clear edge event enable registers */
    REG_RMW32_func(ICU_PORT_CI_PCR_ADDR32(u16port,(uint32)u16pin), ICU_PORT_CI_PCR_IRQC_U32, (uint32)0U);
        
    /* Clear Interrupt Filter Enable Register */
    REG_RMW32_func(ICU_PORT_CI_DFER_ADDR32(u16port), u32pinMask, (uint32)0U);
}

/* polyspace < MISRA-C3:8.4 : Not a defect : Justify with annotations > External Usage dependent on project setup */
void Gpt_LPTIMR_ISR(void)
{
    Gpt_Lptmr_ProcessCommonInterrupt();
    Tm_UpdateSlowTimer_LPM(EcuM_u8PeriodicWakeUp);
}

static void EcuM_disableCanWakeUp(void)
{
    EcuM_CANWakeUpIcuDisable();
    Icu_DisableNotification(IcuChannel_CanWakeup);
    Port_SetPinMode(PortConfigSet_PORT_E_PTE4_CAN_RX, PORT132_CAN0_RX);
}

void EcuM_CanWakeUp(void)
{
    /* ECU un active but no wake-up */
    if(EcuM_WakeUpLogged == EcuM_WAKE_UP_EXIT_SLEEP)
    {
        EcuM_EnableCanComByCAN();
    }
    else
    {
        EcuM_SetWakeupEvent(ECUM_WAKEUP_CAN);
        EcuM_setWakeUpSource(ECUM_WAKEUP_CAN);
    }

    if(EcuM_GetValidatedWakeupEvents() & ECUM_WAKEUP_CAN)
    {
        EcuM_disableCanWakeUp();
    }
}
void Nfc_NfcChipIrqIsr(void)
{
    /* TO BE REMOVED */
}

void Nfc_TimerTickPeriodicalTask(void)
{
    /* TO BE REMOVED */
}

void EcuM_setWakeUpSource(EcuM_WakeupSourceType wupSource)
{
    EcuM_WakeupSource |= wupSource;
}


void EcuM_resetWakeUpSource(void)
{
    EcuM_WakeupSource = 0u;
}


EcuM_WakeupSourceType EcuM_getWakeUpSource(void)
{
    return EcuM_WakeupSource;
}

static void EcuM_ClearNMsignals(void)
{
    U8 i;
    EcuM_WakeUpLogged = EcuM_WAKE_UP_ENTER_SLEEP; 
    /* clear all NM signals */
    U8 u8SignalValue = 0u;

    // (void)Com_SendSignal(ComConf_ComSignal_NM_NFC_FS_Wakeup_V12_XIX_NM_NFC_FS_XIX_HCP4_CANFD01_fc33eaf2_Tx, &u8SignalValue);
    
    for(i = 0u; i < sizeof(EcuM_calloutCanSignalNM_NFC_FS_FCAB); i++)
    {
        EcuM_calloutCanSignalNM_NFC_FS_FCAB[i] = 0u; /* Motorola Endian */
    }
    
    // (void)Com_SendSignal(ComConf_ComSignal_NM_NFC_FS_FCAB_XIX_NM_NFC_FS_XIX_HCP4_CANFD01_50b0119e_Tx, &EcuM_calloutCanSignalNM_NFC_FS_FCAB);
    // (void)Com_SendSignal(ComConf_ComSignal_NM_aktiv_Key_Authentifiz_NFC_XIX_NM_NFC_FS_XIX_HCP4_CANFD01_0d57fa8a_Tx, &u8SignalValue);

    /* Clear NmFastCycle variables for next wake-up */
    Com_Appl_NmFastCycleResetVariables();
}


static void EcuM_EnableCanComByCAN(void)
{
    EcuM_disableCanWakeUp();
    EcuM_WakeUpLogged = EcuM_WAKE_UP_CAN;
    /* set passive cpmmunication */
    U8 u8SignalValue = 0u;
    /* Bus wake-up */
    u8SignalValue = NM_NFC_FS_WAKEUP_V12_BUS_WAKEUP;
    // (void)Com_SendSignal(ComConf_ComSignal_NM_NFC_FS_Wakeup_V12_XIX_NM_NFC_FS_XIX_HCP4_CANFD01_fc33eaf2_Tx, &u8SignalValue);
    /* If there is a NFC wakeup in paralel, FCAB will be set in the EcuM_EnableCanComByNFC */
    EcuM_calloutCanSignalNM_NFC_FS_FCAB[0] = 0u; /* Motorola Endian */
    // (void)Com_SendSignal(ComConf_ComSignal_NM_NFC_FS_FCAB_XIX_NM_NFC_FS_XIX_HCP4_CANFD01_50b0119e_Tx, &EcuM_calloutCanSignalNM_NFC_FS_FCAB);
    u8SignalValue = 0u;
    // (void)Com_SendSignal(ComConf_ComSignal_NM_aktiv_Key_Authentifiz_NFC_XIX_NM_NFC_FS_XIX_HCP4_CANFD01_0d57fa8a_Tx, &u8SignalValue);
    ECUM_validWakeUpNotification();

    /* This is a passive wake-up */
    EcuM_WakeUpType = PassiveWakeUp;
}

void EcuM_EnableCanComByNFC(void)
{
    if(NvmMng_getEnableWakeUpByNfc())
    {
        EcuM_disableCanWakeUp();
        U8 u8SignalValue = 1u;
        // (void)Com_SendSignal(ComConf_ComSignal_NM_aktiv_Key_Authentifiz_NFC_XIX_NM_NFC_FS_XIX_HCP4_CANFD01_0d57fa8a_Tx, &u8SignalValue);
        /* set active communication, wake-up source is internal */
        // (void)Com_SendSignal(ComConf_ComSignal_NM_NFC_FS_CBV_AWB_XIX_NM_NFC_FS_XIX_HCP4_CANFD01, &u8SignalValue);
        if(EcuM_WakeUpLogged != EcuM_WAKE_UP_CAN)
        {
            u8SignalValue = NM_NFC_FS_WAKEUP_V12_NFC;
            // (void)Com_SendSignal(ComConf_ComSignal_NM_NFC_FS_Wakeup_V12_XIX_NM_NFC_FS_XIX_HCP4_CANFD01_fc33eaf2_Tx, &u8SignalValue);
        }
        EcuM_WakeUpLogged = EcuM_WAKE_UP_NFC;
        /* Motorola Endian */
        EcuM_calloutCanSignalNM_NFC_FS_FCAB[0] = ECUM_BASEFUNCTION_COMFORTLIGHT;
        // (void)Com_SendSignal(ComConf_ComSignal_NM_NFC_FS_FCAB_XIX_NM_NFC_FS_XIX_HCP4_CANFD01_50b0119e_Tx, &EcuM_calloutCanSignalNM_NFC_FS_FCAB);
        ECUM_validWakeUpNotification();

        /* This is a active wake-up */
        EcuM_WakeUpType = ActiveWakeUp;
    }
}

void EcuM_EnableCanComByCAPA(void)
{
    EcuM_disableCanWakeUp();
    U8 u8SignalValue = 1u;
    // (void)Com_SendSignal(ComConf_ComSignal_NM_aktiv_Key_Authentifiz_NFC_XIX_NM_NFC_FS_XIX_HCP4_CANFD01_0d57fa8a_Tx, &u8SignalValue);
    /* set active communication, wake-up source is internal */
    // (void)Com_SendSignal(ComConf_ComSignal_NM_NFC_FS_CBV_AWB_XIX_NM_NFC_FS_XIX_HCP4_CANFD01, &u8SignalValue);
    if(EcuM_WakeUpLogged != EcuM_WAKE_UP_CAN)
    {
        u8SignalValue = NM_NFC_FS_WAKEUP_V12_SENSOR;
        // (void)Com_SendSignal(ComConf_ComSignal_NM_NFC_FS_Wakeup_V12_XIX_NM_NFC_FS_XIX_HCP4_CANFD01_fc33eaf2_Tx, &u8SignalValue);
    }
    EcuM_WakeUpLogged = EcuM_WAKE_UP_CAPA;
    /* Motorola Endian */
    EcuM_calloutCanSignalNM_NFC_FS_FCAB[0] = ECUM_BASEFUNCTION_COMFORTLIGHT;
    EcuM_calloutCanSignalNM_NFC_FS_FCAB[2] = ECUM_DOORS_HATCHES;
    // (void)Com_SendSignal(ComConf_ComSignal_NM_NFC_FS_FCAB_XIX_NM_NFC_FS_XIX_HCP4_CANFD01_50b0119e_Tx, &EcuM_calloutCanSignalNM_NFC_FS_FCAB);
    ECUM_validWakeUpNotification();

    /* This is a active wake-up */
    EcuM_WakeUpType = ActiveWakeUp;
}

static void ECUM_validWakeUpNotification(void)
{
    /* Start the CAN communication */
    ComM_CommunicationAllowed(0, TRUE);
    (void)ComM_RequestComMode(0, COMM_FULL_COMMUNICATION);
}

void Fls_AC_Callback_Test(void) {}
void Fls_StartFlashAccessNotif(void) {}
void Fls_FinishedFlashAccessNotif(void) {}
void Fee_ClusterFormatNotif(void) {}
void EcuM_OnGoOffTwo(void) {}
void EcuM_EnableWakeupSources(EcuM_WakeupSourceType wakeupSource) {}
void EcuM_AL_SwitchOff(void) {}
void EcuM_DisableWakeupSources(EcuM_WakeupSourceType wakeupSource) {}
void EcuM_AL_DriverRestart(const EcuM_ConfigType* ConfigPtr) {}
void EcuM_StartWakeupSources(EcuM_WakeupSourceType wakeupSource) {}
void EcuM_CheckValidation(EcuM_WakeupSourceType wakeupSource) {}
void EcuM_StopWakeupSources(EcuM_WakeupSourceType wakeupSource) {}
void EcuM_OnExitRun(void) {}
void EcuM_OnExitPostRun(void) {}
void EcuM_OnPrepShutdown(void) {}

