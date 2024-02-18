/* polyspace+1 MISRA-C3:1.1 [Justified:Low] "All macro definitions are needed." */
/*------------------------------------------------------------------------------------------------+
| File: can_appl.c                                                                   |
+-------------------------------------------------------------------------------------------------+
| Project: Audi eTab                                                                              |
+-------------------------------------------------------------------------------------------------+
| Short description: The file contains the implementation for CAN application and the NM messages
                     that have to be sent on CAN.
+-------------------------------------------------------------------------------------------------+
| Created on: 27 Sep 2021                                                                         |
|                                                                                                 |
|                                                                                                 |
+------------------------------------------------------------------------------------------------*/

#include "Platform_Types.h"
#include "Com.h"
#include "Rte_ComM_Type.h"
#include "ComM.h"
#include "sensor_algo.h"
#include "NvmMng.h"
#include "can_appl.h"
#include "BatterySupervisor.h"
#include "EcuM_Callout_Stubs.h"
#include "Dem.h"

/********************************** local defines ************************************************/

/* Macros used for CAN signal NFC_TGS_FEHLER */
#define CANAPP_ANTENNA_ERROR            (2u) /* Bit1 */
#define CANAPP_UNDERVOLTAGE_ERROR       (4u) /* Bit2 */
#define CANAPP_OVERVOLTAGE_ERROR        (8u) /* Bit3 */
#define CANAPP_CLR_ANTENNA_ERROR        (0xFDu) /* Bit1 */
#define CANAPP_CLR_UNDERVOLTAGE_ERROR   (0xFBu) /* Bit2 */
#define CANAPP_CLR_OVERVOLTAGE_ERROR    (0xF7u) /* Bit3 */

#define VEH_SPEED_5_KM_H                0x8164U
#define VEH_SPEED_MINUS_5_KM_H          0x7E9CU
#define DIAG_NOT_ACTIVE                 0U
#define DIAG_ACTIVE_DEFAULT_SESION      1U
#define DIAG_ACTIVE_EXTENDED_SESION     2U
#define EXTENDED_DIAG_SESSION           3U
#define DEFAULT_SESSION                 1U
/* NM timeout time = 250ms (define is used in 10ms task) */
#define NM_TIMEOUT_TIME                 (25u)

/********************************** local types **************************************************/

/********************************** local variables **********************************************/


/********************************** global variables **********************************************/

/* This global variable contains the flags requesting NM Normal operation */
BOOL BO_ActiveDiag = FALSE;
uint16 U16_DiagSesCounter;
/* polyspace < MISRA-C3:8.4,8.7: Not a defect : Justify with annotations > External Usage dependent on project setup*/
/* polyspace < CERT-C:CON32-C : Not a defect : Justify with annotations > No concurrency on this structure */
/* polyspace < CERT-C:POS49-C : Not a defect : Justify with annotations > No concurrency on this structure */
/* polyspace+5 MISRA-C3:8.9 [Justified:Low] "Variable is declared once here" */
S_NM_NORMAL_OP_FLAGS S_NORMAL_OP_Request;
static U8 U8_NFC_TGS_Fehler = 0u;
BOOL BO_VehSpeedCondFulfilled = TRUE;
static BOOL BO_VehSpeedCondFulfilledOld = TRUE;
static U8 U8_NmTxCyclesNo = 0u;
static U8 U8_NmTimeoutCnt = 0;
static BOOL BO_NmTimeout = FALSE;

/********************************** public functions  ***************************************************/

/******************************************************************************
 * Name         :  CAN_ApplInit
 * Called by    :
 * Preconditions:
 * Parameters   :
 * Return code  :
 * Description  :  This function is called after POR. It can be used
 * to re-initialize the active reasons for NM frame.
 * Caution      :
 ******************************************************************************/
void  CAN_ApplInit(void)
{
   /*Initialize global variable with no flag set */
   S_NORMAL_OP_Request.u8ActiveAuth = 0u;
   S_NORMAL_OP_Request.u8ActiveDiagnose = 0u;
   S_NORMAL_OP_Request.u8ActiveKlemme_15 = 0u;
   S_NORMAL_OP_Request.u8ActiveTmin = 0u;
}

/******************************************************************************
 * Name         :  CanNM_Appl_CyclicTask
 * Called by    :
 * Preconditions:
 * Parameters   :  none
 * Return code  :  none
 * Description  :  This function will be called cyclic at every 5ms.
 * If any of the flags will be set, NM normal operation will be called, or released if all flags are cleared.
 *               SWR-845
 * Caution      :
 ******************************************************************************/
/* polyspace < MISRA-C3:8.2 : Not a defect : Justify with annotations > The function type is same as in prototype form */
void CanNM_Appl_CyclicTask(void)
{
    U8 U8_NM_activeReasons = 0u;
    U8 U8_receivedSignalValue = 0u;
    boolean boIsAlgoActive = isAlgoActive();
    U8 requestedComMode;
    static U8 U8_DummyNmSimulationCnt = 0; /* Counter used to simulate a Rx dummy NM message every 500ms */

    (void)Com_ReceiveSignal(ComConf_ComSignal_B_ActiveMode, &U8_receivedSignalValue);
    if(U8_receivedSignalValue > 1u )
    {
        U8_receivedSignalValue = 1u;
    }
    else
    {
        /*do nothing*/    
    }
    S_NORMAL_OP_Request.u8ActiveKlemme_15 = U8_receivedSignalValue;
   
    /* Communication requested if:
        - KL15 CAN signal si 1
        - Diagnostic is active
        - NFC application requests EcuM RUN */
    /* polyspace+1 MISRA-C3:10.5 [Justified:Low] "will not affect the code" */
    U8_NM_activeReasons = S_NORMAL_OP_Request.u8ActiveKlemme_15 + S_NORMAL_OP_Request.u8ActiveDiagnose;

    if (((U8_NM_activeReasons != 0U) || (boIsAlgoActive != 0U)) && (BatSup_isComOff() == 0u))
    {
        /* wake-up source not triggered, NM message is not filled with proper values */
        if(EcuM_WakeUpLogged == EcuM_WAKE_UP_EXIT_SLEEP)
        {
            if(boIsAlgoActive==TRUE)
            {
                EcuM_EnableCanComByCAPA();
            }
        }
        else
        {
            /* Start the CAN communication */
            (void)ComM_RequestComMode(0, COMM_FULL_COMMUNICATION);
        }
    }
    else
    {
        /* Stop the CAN communication */
        (void)ComM_RequestComMode(0, COMM_NO_COMMUNICATION);
    }

    /* Get the current requested ComM mode */
    (void)ComM_GetRequestedComMode(0, &requestedComMode);
    
    /* Simulate a dummy NM every 500ms in order to keep the internal bus active if the following conditions are fulfulled: 
     - there is at least one EcuM user which request RUN 
       AND
     - the current requested ComM mode is COMM_NO_COMMUNICATION (no internal request)
       AND
     - there is no NM message received (no external request) */

}

/******************************************************************************
 * Name         :  Com_Appl_CyclicTask
 * Called by    :
 * Preconditions:
 * Parameters   :  none
 * Return code  :  none
 * Description  :  This function will be called cyclic at every 10ms.
 * Caution      :
 ******************************************************************************/
void Com_Appl_CyclicTask(void)
{
    /* Capa sensor CAN signals handling */
    CAPA_publishCanSignals();

	/* Handling of the activ fiag signal */
    VDO_Handle_ActiveDiag();

}

/************************************************************************)******
 * Name         :  Com_Appl_NmTimeoutHandling
 * Called by    :
 * Preconditions:
 * Parameters   :  none
 * Return code  :  none
 * Description  :  This function will be called cyclic at every 10ms.
 * Caution      :
 ******************************************************************************/
void Com_Appl_NmTimeoutHandling(void)
{
    /* Monitor the NN timeout (250ms) */
    U8_NmTimeoutCnt++;

    if(U8_NmTimeoutCnt > NM_TIMEOUT_TIME)
    {
        BO_NmTimeout = TRUE;
        U8_NmTimeoutCnt = 0;
    }
}
/******************************************************************************
 * Name         :  Com_Appl_NmFastCycleResetVariables
 * Called by    :
 * Preconditions:
 * Parameters   :  none
 * Return code  :  none
 * Description  :  This function will be called on transition to sleep
 * Caution      :
 ******************************************************************************/
void Com_Appl_NmFastCycleResetVariables(void)
{
    EcuM_WakeUpType = PassiveWakeUp;
    U8_NmTxCyclesNo = 0;
}

void CANAPP_setAntennaError(void)
{
    U8_NFC_TGS_Fehler |= CANAPP_ANTENNA_ERROR;
}

void CANAPP_setUndervoltageError(void)
{
    U8_NFC_TGS_Fehler |= CANAPP_UNDERVOLTAGE_ERROR;
}

void CANAPP_setOvervoltageError(void)
{
    U8_NFC_TGS_Fehler |= CANAPP_OVERVOLTAGE_ERROR;
}

void CANAPP_clearAntennaError(void)
{
    U8_NFC_TGS_Fehler &= CANAPP_CLR_ANTENNA_ERROR;
}

void CANAPP_clearUndervoltageError(void)
{
    U8_NFC_TGS_Fehler &= CANAPP_CLR_UNDERVOLTAGE_ERROR;
}

void CANAPP_clearOvervoltageError(void)
{
    U8_NFC_TGS_Fehler &= CANAPP_CLR_OVERVOLTAGE_ERROR;
}

S_NM_NORMAL_OP_FLAGS CANAPP_get_Normal_OP_Request(void)
{
    return S_NORMAL_OP_Request;
}
/******************************************************************************
 * Name         :  Com_Appl_NmRxIndication
 * Called by    :  Each time a NM message is received 
 * Preconditions:
 * Parameters   :  NetworkHandleType
 * Return code  :  none
 * Caution      :
 ******************************************************************************/
/* polyspace+1 MISRA-C3:2.7 [Justified:Low] "future implementation" */
void Com_Appl_NmRxIndication(NetworkHandleType nmNetworkHandle)
{
    /* NM message received -> reset the NM timeout counter */
    U8_NmTimeoutCnt = 0;
    BO_NmTimeout = FALSE;
}
/******************************************************************************
 * Name         :  VDO_Handle_ActiveDiag
 * Called by    :  
 * Preconditions:
 * Parameters   :  
 * Return code  :  none
 * Caution      :
 ******************************************************************************/
void VDO_Handle_ActiveDiag(void)
{
    static uint8 DiagActiveState;
    BOOL U8_receivedSignalValue;  

    Dcm_SesCtrlType sesCtrlType;
    Dcm_GetSesCtrlType(&sesCtrlType); /*  Get session state   */

    switch (DiagActiveState)
    {
    case DIAG_NOT_ACTIVE: /*  Idle state of the state machine */

        if (sesCtrlType == EXTENDED_DIAG_SESSION) /*  If the current session is EXTENDED_DIAG_SESSION then set the SignalValue to TRUE and set CanSignalNM_NFC_FS_FCAB to 64    */
        {
            U8_receivedSignalValue = TRUE;
            EcuM_calloutCanSignalNM_NFC_FS_FCAB[0] |= 0x40;
            DiagActiveState = DIAG_ACTIVE_EXTENDED_SESION; /*  Go to DIAG_ACTIVE_EXTENDED_SESION and wait for session to change    */
        }
        else if (BO_ActiveDiag) /*  If a diag request is called set SignalValue to TRUE */
        {
            U8_receivedSignalValue = TRUE;
            EcuM_calloutCanSignalNM_NFC_FS_FCAB[0] |= 0x40;
            DiagActiveState = DIAG_ACTIVE_DEFAULT_SESION; /*  Go to DIAG_ACTIVE_DEFAULT_SESION and start the counter for 10s  */
            U16_DiagSesCounter = 0;                       /*  Reset Counter   */
        }
        break;

    case DIAG_ACTIVE_DEFAULT_SESION: /* 10s counter that resets the SignalValue to FALSE if no other diag_request is triggered */

        if (U16_DiagSesCounter < 400)
        {
            U16_DiagSesCounter++;
        }
        else if (sesCtrlType == DEFAULT_SESSION) /* If the counter is elapsed and current session is default -> reset the signal, set CanSignalNM_NFC_FS_FCAB to 0 and swich to DIAG_NOT_ACTIVE */
        {
            BO_ActiveDiag = FALSE;
            DiagActiveState = DIAG_NOT_ACTIVE;
            U8_receivedSignalValue = FALSE;
            EcuM_calloutCanSignalNM_NFC_FS_FCAB[0] &= 0xBF;
        }
        else /* If the counter is elapsed and current session is extended -> reset the signal and swich to DIAG_ACTIVE_EXTENDED_SESION */
        {
            DiagActiveState = DIAG_ACTIVE_EXTENDED_SESION;
        }

        break;

    case DIAG_ACTIVE_EXTENDED_SESION: /* SignalValue TRUE until session is changed to DEFAULT_SESSION */

        if (sesCtrlType == DEFAULT_SESSION)
        {
            DiagActiveState = DIAG_ACTIVE_DEFAULT_SESION;
            U16_DiagSesCounter = 0; /*  Reset Counter   */
        }
        break;

    default:
        break;
    }
}