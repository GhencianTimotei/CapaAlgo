/*!
 * \defgroup <module_group (sensor_algo.c) Module purpose>
 * \{
 ******************************************************************************
 * \image html "Kopf_oZusatz_A4hoch_4C.jpg"
 *
 * \par Module Owner:
 *   Huf H&uuml;lsbeck & F&uuml;rst GmbH & Co. KG \n
 *   Steeger Str. 17 \n
 *   42551 Velbert \n
 *   Department PDE-S
 *
 * \par Initial Project:
 *    0678.005 VW_Vip
 *
 ******************************************************************************
 * \par Description:
 *  after performs the capacitive measurement of all enabled sensors,
 * The measured signals for each sensor are then processed to
 * check for user touches, releases.
 *
 *
 ******************************************************************************
 *
 *  $Workfile:   sensor_algo.h $
 *  $Revision:   1.3  $
 *  $Date:   Apr 09 2019 15:59:10  $
 *  $Author:   hlehman2  $
 *
 ******************************************************************************
 * Change history:
 *
 *
 *
 * Add new lines above
 ******************************************************************************
 *
 * \par Purpose:
 *    i.e Operating System, Service Layer
 *
 * \par Compiler:
 *    ANSI
 *
 * \par Controller:
 *    independant
 *
 * \par Resources:
 *    | Resource      | Amount    | Remarks     |
 *    | ------------- | --------: | ----------- |
 *    | ROM           |  X Byte   |             |
 *    | RAM           |  X Byte   |             |
 *    | EEPROM        |  X Byte   |             |
 *    | Runtime Init  |    X ms   |             |
 *    | Runtime Task  |    X ms   |             |
 *
 * \par Quality:
 *    | Factor            | Excl  | Good  | Fair  | Poor  |
 *    | ----------------- | ----: | ----: | ----: | ----: |
 *    | _Maintainability_ |   0 % |   0 % |   0 % |   0 % |
 *    | Analyzability     |   0 % |   0 % |   0 % |   0 % |
 *    | Changeability     |   0 % |   0 % |   0 % |   0 % |
 *    | Stability         |   0 % |   0 % |   0 % |   0 % |
 *    | Testability       |   0 % |   0 % |   0 % |   0 % |
 *
 * \par MISRA rules violations:
 *     \li none(?)
 *
 ******************************************************************************
 *
 * \attention
 *   \li text for Information, to do ..
 *
 ******************************************************************************
*/

#ifndef SENSOR_ALGO_H
#define SENSOR_ALGO_H

#ifndef INTEGRATE_FROM_V4
#include "Platform_Types.h"
#endif
#include "sensor_algo.hc"
#include "sensor_algo.ha"
#include "sensor_algo.hi"
#include "sensor_algo.hm"


typedef enum
{
    EN_ASM_SX_IDLE = 0,                                         /*Sensor is still Idle No Thres*/
    EN_ASM_SX_DEBOUNCE,                                         /*Sensor cross the Approach threshold */
    EN_ASM_SX_APPROACH,                                         /*sensor still crossing the approach threshold*/
    EN_ASM_SX_TOUCH,                                            /*sensor cross the TOUCH threshold*/
    EN_ASM_SX_OFF_DELAY                                         /*sensor calculate a new baseline behaviour going back to idle */

} ENUM_ALGO_SM_STATE_TYPE;

typedef enum {
    Cx0_keine_Deaktivierung = 0U,
    Cx1_Deaktivierung       = 1U
}NFC_TSG_Kapa_deaktivieren_CAN_Signal_values;

/* polyspace+10 MISRA-C3:8.5 [Not a defect:Low] "function is declared here oance" */
extern NEAR ENUM_ALGO_SM_STATE_TYPE EN_ER_AlgoStateSM;          /* active-mode unlock sensor states */
extern NEAR ENUM_ALGO_SM_STATE_TYPE EN_VR_AlgoStateSM;          /* active-mode lock sensor states */
extern void CAPA_publishCanSignals(void);
extern void Algo_getVrState(U8 *U8_algoState);
extern void Algo_getErState(U8 *U8_algoState);
extern void get_sensor_algo_state_result(U8 *U8_algo_state_arg);

#endif /* SENSOR_H */


/* Automatic logging by PVCS ***********************************************
$Log:   J:/vmfs/VW/1508.008_380_ODH/archives/3_Coding/ECU_NFC_STACK-NXP/MCU_RL78/MOD_SERV_CAPA_SENSOR/MOD_SERV_SENSOR_ALGO/Source/sensor_algo.h-arc  $
 * 
 *    Rev 1.3   Apr 09 2019 15:59:10   hlehman2
 * Several Misra fixes
 * 
 *    Rev 1.2   Apr 04 2019 11:08:00   hlehman2
 * MISRA fix
 * 
 *    Rev 1.1   06 Apr 2018 08:07:26   ybadal
 * HIS and Misra partialy fixed, based on algo from VW 511 project actual version.
 * 
 *    Rev 1.3   14 Dec 2015 16:00:48   ybadal
 * moduls and functions Headers changed to HUF standard header.
 * 
 *    Rev 1.2   Jan 26 2015 15:07:36   mstei
 * Changes for compliance with CSpec-095 Rev. 01 - Guideline for Software Coding.pdf:
 * - name of the project changed in the header of the file
 * - change to add PVCS history

*********************************************************** end of comment */
