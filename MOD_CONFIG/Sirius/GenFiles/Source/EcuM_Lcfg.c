/*
*!
* \defgroup <module_group (MOD_) Module purpose>
* \{
******************************************************************************
* \image html "Kopf_oZusatz_A4hoch_4C.jpg"
*
* \par Module Owner:
* Huf Huelsbeck & Fuerst GmbH & Co.KG \n
* Steeger Str. 17 \n
* 42551 Velbert \n
* Department PDE - S
*
******************************************************************************
*
* \par Purpose:
* Linktime configuration file for EcuM
* Service Layer(AUTOSAR 4.2)
*
* \par Compiler:

*IAR
*
* \par Controller:

*Independent
*
* \par Resources:

*    | Resource     | Amount    | Remarks|
*    | -------------| ----------| -------|
*    | ROM          | x Byte    |        |
*    | CODE         | x Byte    |        |
*    | RAM          | x Byte    |        |
*    | EEPROM       | x Byte    |        |
*    | Runtime Init | X ms      |        |
*    | Runtime Task | X ms      |        |
*
* \par Quality:

*    | Factor            | Excl  | Good  | Fair  | Poor  |
*    | ----------------- | ----: | ----: | ----: | ----: |
*    | _Maintainability_ | 0 %   | 0 %   | 0 %   | 0 %   |  
*    | Analyzability     | 0 %   | 0 %   | 0 %   | 0 %   |
*    | Changeability     | 0 %   | 0 %   | 0 %   | 0 %   |
*    | Stability         | 0 %   | 0 %   | 0 %   | 0 %   |
*    | Testability       | 0 %   | 0 %   | 0 %   | 0 %   |
*
* \par MISRA rules violations:

*     \li none
*
******************************************************************************
*
* \attention
*   \li This file is generated from the configuration tool
*
******************************************************************************
* % PCMS_HEADER_SUBSTITUTION_START:%
*
*Document Management Information Log(generated by Dimensions CM)
*
*
*CM Item:   % PID:%
*Itemname:  % PM:%
*Location:  % ARCHIVE:%
*Revision:  % PR:%
*Date:      % DATE:%
*Author:    % AUTHOR:%
*
* % PCMS_HEADER_SUBSTITUTION_END:%
*
******************************************************************************/

/*!
 \defgroup module_group_det Details
 \ingroup module_group
 \{
*/

#include "EcuM.h"
#include "ComM.h"

/* SWR_667 */
const EcuM_SleepModeSettingsType EcuM_S_SleepModeSet[ECUM_NO_OF_SLEEP_MODES] = {
     /* ECUM_SLEEP_LPM */
      {
            MCU_VLPR_MODE,
            ECUM_WKSOURCE_POWER | ECUM_WKSOURCE_INTERNAL_RESET | ECUM_WAKEUP_CAN | ECUM_WAKEUP_ALGO | ECUM_WAKEUP_LED | ECUM_WAKEUP_NFC_LIB | ECUM_WAKEUP_NFC_APP ,
            STD_OFF
      },
};


/* [SWS_EcuM_02625] */
const EcuM_WakeupSourceValidationType EcuM_WkpSourceValidation[ECUM_NO_OF_WAKEUP_SOURCES] = {
      {ECUM_WKSOURCE_POWER,                 ECUM_NO_VALIDATION_TIMEOUT,   ECUM_UNDEFINED_COMM_CHANNEL},
      {ECUM_WKSOURCE_RESET,                 ECUM_NO_VALIDATION_TIMEOUT,   ECUM_UNDEFINED_COMM_CHANNEL},
      {ECUM_WKSOURCE_INTERNAL_RESET,        ECUM_NO_VALIDATION_TIMEOUT,   ECUM_UNDEFINED_COMM_CHANNEL},
      {ECUM_WKSOURCE_INTERNAL_WDG,          ECUM_NO_VALIDATION_TIMEOUT,   ECUM_UNDEFINED_COMM_CHANNEL},
      {ECUM_WKSOURCE_EXTERNAL_WDG,          ECUM_NO_VALIDATION_TIMEOUT,   ECUM_UNDEFINED_COMM_CHANNEL},
      {ECUM_WAKEUP_CAN,          ECUM_NO_VALIDATION_TIMEOUT,   ECUM_UNDEFINED_COMM_CHANNEL},
      {ECUM_WAKEUP_ALGO,          ECUM_NO_VALIDATION_TIMEOUT,   ECUM_UNDEFINED_COMM_CHANNEL},
      {ECUM_WAKEUP_LED,          ECUM_NO_VALIDATION_TIMEOUT,   ECUM_UNDEFINED_COMM_CHANNEL},
      {ECUM_WAKEUP_NFC_LIB,          ECUM_NO_VALIDATION_TIMEOUT,   ECUM_UNDEFINED_COMM_CHANNEL},
      {ECUM_WAKEUP_NFC_APP,          ECUM_NO_VALIDATION_TIMEOUT,   ECUM_UNDEFINED_COMM_CHANNEL}
};

const ECUM_COMMCHANNELS_TYPE EcuM_ComMChannels[ECUM_NO_OF_COMM_CHANNELS] = {ComMConf_ComMChannel_CN_HCP4_CANFD01_152fd6c6};

/* %PCMS_HEADER_SUBSTITUTION_START:%
 ******************************************************************************
 * Document Management Information Log (generated by Dimensions CM)
 *
 *  Description:
 *  %PD:%
 *
 *  Used by Baselines:
 *  %PIRB:%
 *
 *  Used by Dimensions CM Projects:
 *  %PIRW:%
 *
 *  Change History:
 *  %PL:%
 *
 * %PCMS_HEADER_SUBSTITUTION_END:%
 */
