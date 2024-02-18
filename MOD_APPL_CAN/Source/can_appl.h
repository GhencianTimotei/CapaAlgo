/*
 * can_appl.h
 *
 *  Created on: 27 Sep 2021
 *      Author: grovent
 */

#ifndef CAN_APPL_H_
#define CAN_APPL_H_

#include "Platform_Types.h"

/* Defines for NM_NFC_FS_Wakeup_V12_XIX_NM_NFC_FS_XIX_HCP4_CANFD01 signal values */
/* polyspace+5 MISRA-C3:2.5 [Justified:Low] "Macro should be kept for future usage" */
#define NM_NFC_FS_WAKEUP_V12_UNKNOWN                    ((U8)0u)
#define NM_NFC_FS_WAKEUP_V12_BUS_WAKEUP                 ((U8)1u)
#define NM_NFC_FS_WAKEUP_V12_NFC                        ((U8)5u)
#define NM_NFC_FS_WAKEUP_V12_SENSOR                     ((U8)6u)

/*
 * Status of the condition
*/
/* polyspace+13 MISRA-C3:2.3 [Justified:Low] "Added for further implementation." */
typedef enum
{
  EN_CAN_CONDITION_NOT_ACTIVE,
  EN_CAN_CONDITION_ACTIVE
}EN_CAN_ACTIVE_CONDITION_STATE;

typedef enum
{
EN_Active_Condition_Auth,
EN_Active_Condition_Tmin,
EN_Active_Condition_Diagnose,
EN_Active_Condition_Klemme_15
}EN_CAN_ACTIVE_CONDITION;

extern void CANAPP_setAntennaError(void);
extern void CANAPP_setUndervoltageError(void);
extern void CANAPP_setOvervoltageError(void);
extern void CANAPP_clearAntennaError(void);
extern void CANAPP_clearUndervoltageError(void);
extern void CANAPP_clearOvervoltageError(void);

/*
 * Contains the flags for request of normal operation
 * If any of the flags is set, NM should be in normal operation
*/
/* polyspace:begin < MISRA-C3:6.1 : Not a defect : Justify with annotations > Bit field type is unsigned int. */
typedef struct
{
    U8 u8ActiveDiagnose:1;
    U8 u8ActiveKlemme_15:1;
    /* u8ActiveTmin is obsolete */
    U8 u8ActiveTmin:1;
    U8 u8ActiveAuth:1;
}S_NM_NORMAL_OP_FLAGS;
/* polyspace:end < MISRA-C3:6.1 : Not a defect : Justify with annotations > Bit field type is unsigned int. */

/********************************** global variables **********************************************/
extern BOOL BO_VehSpeedCondFulfilled;
/**************************************************************************************************/

/******************************************************************************
 * Name         :  CAN_ApplInit
 * Called by    :
 * Preconditions:
 * Parameters   :
 * Return code  :
 * Description  :  This function is called during CclInit(). It can be used
 * to re-initialize the following components:
 *                         - ISO TP
 *                         - Diagnostic
 *                         - and others than the standard CANbedded components .
 * Caution      :
 ******************************************************************************/
extern void  CAN_ApplInit(void);

/******************************************************************************
 * Name         :  CanNM_Appl_CyclicTask
 * Called by    :
 * Preconditions:
 * Parameters   :  none
 * Return code  :  none
 * Description  :  This function will be called cyclic at every 25ms.
 * If any of the flags will be set, NM normal operation will be called, or released if all flags are cleared.
 * Caution      :
 ******************************************************************************/
/* polyspace < MISRA-C3:8.2, 8.3, 8.4 : Not a defect : Justify with annotations > The function type is same as in prototype form */
extern void CanNM_Appl_CyclicTask(void);

/******************************************************************************
 * Name         :  Com_Appl_CyclicTask
 * Called by    :
 * Preconditions:
 * Parameters   :  none
 * Return code  :  none
 * Description  :  This function will be called cyclic at every 5ms.
 * Caution      :
 ******************************************************************************/
extern void Com_Appl_CyclicTask(void);

/******************************************************************************
 * Name         :  Com_Appl_NmTimeoutHandling
 * Called by    :
 * Preconditions:
 * Parameters   :  none
 * Return code  :  none
 * Description  :  This function will be called cyclic at every 10ms.
 * Caution      :
 ******************************************************************************/
extern void Com_Appl_NmTimeoutHandling(void);

/******************************************************************************
 * Name         :  Com_Appl_NmFastCycleResetVariables
 * Called by    :
 * Preconditions:
 * Parameters   :  none
 * Return code  :  none
 * Description  :  This function will be called on transition to sleep
 * Caution      :
 ******************************************************************************/
void Com_Appl_NmFastCycleResetVariables(void);
extern void Com_Appl_NmRxIndication(NetworkHandleType nmNetworkHandle);
extern BOOL BO_ActiveDiag;
extern uint16 U16_DiagSesCounter;

S_NM_NORMAL_OP_FLAGS CANAPP_get_Normal_OP_Request(void);
void VDO_Handle_ActiveDiag(void);

#endif /* CAN_APPL_H_ */
