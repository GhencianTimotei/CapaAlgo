/*
 * CAN_DiagUsr.h
 *
 *  Created on: Sep 14, 2021
 *      Author: ijovano
 */

#ifndef CAN_DIAGUSR_H
#define CAN_DIAGUSR_H

#include "Platform_Types.h"
#include "Dcm.h"
/* polyspace+7 MISRA-C3:2.4 [Justified:Low] "Added for further implementation" */
typedef enum state28hex {
	CanDiagUsr_EnTxEnRx = 0u,
	CanDiagUsr_DisTxEnRx,
	CanDiagUsr_EnTxDisRx,
	CanDiagUsr_DisTxDisRx
} CanDiagUsr_comControlStateType;

/*  State machine for Service 2E DID FD02 (async).
	States transition in sequential order from WDBI_FD02_IDLE (start point) to WDBI_FD02_SPARE_DONE (exit point).
	Any error during writing to NVM causes transition to WDBI_FD02_ERROR (exit point). */
typedef enum {
	WDBI_FD02_IDLE = 0u,  /* Entry point */
	WDBI_FD02_UNLOCK_WRITING,
	WDBI_FD02_UNLOCK_DONE,
	WDBI_FD02_LOCK_WRITING,
	WDBI_FD02_LOCK_DONE,
	WDBI_FD02_INDUCTIVE_WRITING,
	WDBI_FD02_INDUCTIVE_DONE,
	WDBI_FD02_BATTERY_WRITING,
	WDBI_FD02_BATTERY_DONE,
	WDBI_FD02_EMERGENCY_WRITING,
	WDBI_FD02_EMERGENCY_DONE,
	WDBI_FD02_SPARE_WRITING,
	WDBI_FD02_SPARE_DONE,  /* Exit point for normal operation */
	WDBI_FD02_ERROR  /* Exit point for NVM writing error */
} CanDiagUsr_WDBI_FD02_State;


/*
Offset Data                      Size
--------------------------------------
    00  ProgReqFlag                  1 -+
    01  ValidityFlags                1  |
    02  ResetResponseFlag            1  |
    03  ApplValidity                 1  |
    04  ProgMarker                   1  +--- 11
    05  SecAccessDelayFlag           1  |
    06  SecAccessInvalidCount        1  |
    07  BSBlockSizeActive            1  |
    08  BSBlockSize                  1  |
    09  DcmDslRxTesterSourceAddr     2 -+ 
        Metadata (x8)
    11  Fingerprint                  9 -+
    20  ProgAttempts                 2  |
    22  CRCValue                     4  |
    26  CRCStart                     4  |
    30  CRCLength                    4  +--- 36 (x8)
    34  EraseState                   1  |
    35  SegmentLengthList            4  |
    39  DowngradeProtectionCurrent   4  |
    43  DowngradeProtectionMinimum   4 -+
   ...
   299 EEP Init Flag                 1 ----- 1
*/

/*## attribute DIAG__EEP_BUFFER_SIZE */
/* polyspace+15 MISRA-C3:2.5 [Justified:Low] "Macro should be kept for future usage" */
#define DIAG__EEP_BUFFER_SIZE           ((U16)300U)  /* Reset-safe RAM area for data exchange between bootloader and application; structure is detailed in bootloader (size is 11+8*36+1=300 bytes). */
#define DIAG__EEP_TESTER_ADDR           ((U8)10U)
#define DIAG__EEP_PROG_MARKER_ADDR      ((U8)4U)
#define DIAG__EEP_SEC_ACC_DELAY_ADDR    ((U8)5U)
#define DIAG__EEP_TP_BLOCK_SIZE_ACTIVE  ((U8)7U)
#define DIAG__EEP_TP_BLOCK_SIZE         ((U8)8U)
#define DIAG__EEP_FINGERPRINT_ADDR      ((U8)83U)  /* 11 + 2*36 + 0 */
#define DIAG__EEP_PROG_ATTEMPTS_ADDR    ((U8)92U)  /* 11 + 2*36 + 9 */

#define LOGICAL_BLOCK_VALID           (U8)0x00
#define LOGICAL_BLOCK_INVALID         (U8)0x01
#define FINGEPRINT_SIZE               (U8)0x09
#define KEEP_SEC_ACCESS_DELAY_ACTIVE  (U8)0xA7


#define TEN_MINUTES_COUNT_100MS_TASK  (U16)6000

/* polyspace+1 MISRA-C3:8.6 [Justified:Low] "External declaration is needed" */
extern U8 Diag__EepData_AU8[DIAG__EEP_BUFFER_SIZE];

/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Routine0x06a8_Start(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode
  );

/*********************************************************************************************************
 *  Name                   : CAN_DiagUsr_0x06A8_ResetHealInhStatus
 *  Description            : Routine 0x6A8 - Reset healing inhibition status  
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
extern Std_ReturnType CAN_DiagUsr_0x06A8_ResetHealInhStatus(
      uint8 DataIn,
      P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) DataOut,
      P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

/*********************************************************************************************************
 *  Name                   : CANDiagUsr_CyclicTask
 *  Description            : Cyclic task for CAN_DiagUsr 
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
extern void CANDiagUsr_CyclicTask(void);

/*********************************************************************************************************
 *  Name                   : ResetSecAccBlockedFlag_after10Min
 *  Description            : If Security Access Blocked Flag reset it in 10 minutes
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
void Reset_SecAccBlockedFlag_after10Min(void);

#endif /* CAN_DIAGUSR_H */
