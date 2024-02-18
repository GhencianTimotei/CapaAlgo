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
 *  $Workfile:   sensor_algo.ha  $
 *  $Revision:   1.12  $
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

#ifndef SENSOR_ALGO_HA
#define SENSOR_ALGO_HA


/* polyspace:begin<MISRA-C3:2.5 : Not a defect : Justify with annotations > usage of macros is configuration dependent */

/* XX_THRESHOLD_MAX_PP for all variants */
#define U16_REF_VALUE_MAX_PP           (64000u)        /* for deactivation, the reference value is pulled down to this level */
#define U8_ER_REF_VAL_COUNT            (13u)           /* number of values used to calculate the reference value for unlock sensor */
#define U8_VR_REF_VAL_COUNT            (13u)           /* number of values used to calculate the reference value for lock sensor */
#define U16_SENSOR_CYCLE_TIME          ((U16)10)
#define U16_PARAMETER_CORRECTUR        ((U16)10)

#define U16_REF_VALUE_MAX  ((U16)(U16_REF_VALUE_MAX_PP))

#define U16_ER_THRESHOLD_MIN_PP        (210u)           /* threshold value for unlock approach */
#define U16_VR_THRESHOLD_MIN_PP        (56u)           /* threshold value for lock approach */
#define U16_ER_THRESHOLD_MAX_PP        (110u)          /* threshold value for unlock touch */
#define U16_VR_THRESHOLD_MAX_PP        (80u)           /* threshold value for lock touch */
#define U8_ER_DEBOUNCE_EEP             (2u)            /* debounce counter to creating enough consecutive positive shifts of the reading above the baseline by at least the unlock APPROACH threshold*/
#define U8_VR_DEBOUNCE_EEP             (8u)            /* debounce counter to creating enough consecutive positive shifts of the reading above the baseline by at least the lock APPROACH threshold*/
#define U16_ER_ACTIVATION_TIME		   (1600u)		  /* maximum activation time for unlock sensor */
#define U16_VR_ACTIVATION_TIME		   (1600u)		  /* maximum activation time for lock sensor */

#define U16_ER_NOISE_DEBOUNCE          (10u)           /* additional debounce steps in case of noise */
#define U16_VR_NOISE_DEBOUNCE          (15u)           /* additional debounce steps in case of noise */
#define U16_ER_NOISE_ACTIVE_TIME       (48u)           /* number of samples the noise detection is kept active */
#define U16_VR_NOISE_ACTIVE_TIME       (96u)           /* number of samples the noise detection is kept active */
#define U16_ER_NOISE_SENSIVITY_PP      (25u)           /* offset for the approach in case of increased noise */
#define U16_VR_NOISE_SENSIVITY_PP      (75u)           /* offset for the approach in case of increased noise */
#define U16_ER_NOISE_THRESHOLD         (50u)           /* threshold to detect noise */
#define U16_VR_NOISE_THRESHOLD         (50u)           /* threshold to detect noise */

#define MASK_FOR_cp_ESMdisableKessy                    0x10U           /* mask for ESMdisableKessy bit */

#define U16_ER_SENSIVITY_APPROACH      ((U16)U16_ER_THRESHOLD_MIN_PP)       /* trigger threshold for the unlock approach  */
#define U16_ER_SENSIVITY_TOUCH         ((U16)U16_ER_THRESHOLD_MAX_PP)       /* trigger threshold for the unlock touch */
#define U16_ER_NOISE_SENSIVITY         ((U16)U16_ER_NOISE_SENSIVITY_PP)     /* offset for approximation of increased noise */


#define U16_VR_SENSIVITY_APPROACH      ((U16)U16_VR_THRESHOLD_MIN_PP)      /* trigger threshold for the lock approach */
#define U16_VR_SENSIVITY_TOUCH         ((U16)U16_VR_THRESHOLD_MAX_PP)      /* trigger threshold for the lock touch */
#define U16_VR_NOISE_SENSIVITY         ((U16)U16_VR_NOISE_SENSIVITY_PP)    /* offset for approximation of increased noise */

#define U16_ER_REF_TRACKING_CONS       ((U16)4)                            /* multiplicator of difference between touch threshold and reference value to update during tracking*/
#define U16_VR_REF_TRACKING_CONS       ((U16)4)                            /* multiplicator of difference between touch threshold and reference value to update during tracking*/

#define U16_ER_OFF_DELAY_CONS          ((U16)10)                           /*250 ms*/
#define U16_VR_OFF_DELAY_CONS          ((U16)10)                           /*250 ms*/

#define U16_ER_DEACTIVATION_DEBOUNCE   ((U16)2)
#define U16_VR_DEACTIVATION_DEBOUNCE   ((U16)2)

#define U16_ER_ACTIVE_MAX_TIME         ((U16)(((U16)30000   )/U16_SENSOR_CYCLE_TIME) / U16_PARAMETER_CORRECTUR)      /* 4 seconds*/
#define U16_VR_ACTIVE_MAX_TIME         ((U16)(((U16)30000  )/U16_SENSOR_CYCLE_TIME) /  U16_PARAMETER_CORRECTUR)      /* 4 seconds*/
#define U16_ER_AKTIVATION_400MS        ((U16)390)/U16_SENSOR_CYCLE_TIME  /* 400 ms */


#define U16_ER_SGD_NOT_DESTROY_ENV     ((U16)80)                           /*ER Maximum Signal update with noise free environment */
#define U16_ER_SGD_DESTROY_ENV         ((U16)10)                           /*ER Maximum Signal update with destroyed environment */
#define U16_VR_SGD_NOT_DESTROY_ENV     ((U16)130)                          /*VR Maximum Signal update with noise free environment */
#define U16_VR_SGD_DESTROY_ENV         ((U16)10)                           /*VR Maximum Signal update with destroyed environment */

#define U16_ER_FREEZE_THRESHOLD_NVM_DEF   (U16)73                          /* Freeze threshold calculation base */
#define U16_ER_FREEZE_CANCEL_NVM_DEF      (U16)80                          /* Debounce time for freeze (in samples) */
#define U16_VR_FREEZE_THRESHOLD_NVM_DEF   (U16)35                          /* Freeze threshold calculation base */
#define U16_VR_FREEZE_CANCEL_NVM_DEF      (U16)80                          /* Debounce time for freeze (in samples) */
/* polyspace:end<MISRA-C3:2.5 : Not a defect : Justify with annotations > */

#endif /* SENSOR_ALGO_HA */
 
/* Automatic logging by PVCS ***********************************************

$Log::   J:/vmfs/VW/1508.008_380_ODH/archives/3_Coding/ECU_NFC_STACK-NXP/MCU_RL78/MOD_SERV_CAPA_SENSOR/MOD_SERV_SENSOR_ALGO/Source/senso$
 * 
 *    Rev 1.12   Apr 09 2019 15:59:10   hlehman2
 * Several Misra fixes
 * 
 *    Rev 1.11   Apr 04 2019 11:08:00   hlehman2
 * MISRA fix
 * 
 *    Rev 1.10   28 Mar 2019 12:06:18   sbhanda
 * a define to select default AUDI parameter has been added.
 * 
 *    Rev 1.9   25 Mar 2019 17:03:30   sbhanda
 * Parameter for AUDI
 * 
 *    Rev 1.8   Feb 01 2019 11:10:16   ybadal
 * changes from the visit by Audi.
 * 
 *    Rev 1.6   Nov 27 2018 10:11:48   ybadal
 * add parameter check. 
 * - handle system wakeup by sensor approach detection from EcuM
 * 
 *    Rev 1.5   Jul 27 2018 07:20:24   ybadal
 * -get the parameters from Preference manager.
 * 
 *    Rev 1.4   May 30 2018 15:05:24   ybadal
 * hall sensor activation time  changed to 400ms
 * 
 *    Rev 1.3   06 Apr 2018 08:07:26   ybadal
 * HIS and Misra partialy fixed, based on algo from VW 511 project actual version.
 * 
 *    Rev 1.34   11 Feb 2016 14:56:10   ybadal
 * U16_VR_SGD_NO_DESTROY_ENV  von 130 auf 140.
 * 
 *    Rev 1.33   21 Dec 2015 16:32:26   ybadal
 * misra justifications added.
 * 
 *    Rev 1.32   14 Dec 2015 16:00:48   ybadal
 * moduls and functions Headers changed to HUF standard header.
 * 
 *    Rev 1.31   14 Dec 2015 15:22:06   ybadal
 * moduls and functions Headers changed to HUF standard header.
 * 
 *    Rev 1.28   Nov 16 2015 09:25:00   pclemen
 * some code qualitiy improvements
 * 
 *    Rev 1.27   14 Oct 2015 15:53:58   apeschl
 * Fix for TT 11197
 * 
 *    Rev 1.26   22 Sep 2015 08:26:40   ybadal
 * new threshold defined.
 * 
 *    Rev 1.25   18 Sep 2015 07:55:56   ybadal
 * New Structure implementiert.(neues messwerk und signal analyse)siehe Prog Info von v04.01
 * 
 *    Rev 1.24   09 Sep 2015 15:51:06   apeschl
 * Modification of  U16_ER_THRESHOLD_MIN_PP, VR_THRESHOLD_MIN_PP, U16_VR_THRESHOLD_MAX_PP; 
 * bugfix for TT 11197
 * 
 *    Rev 1.23   24 Aug 2015 13:49:58   ybadal
 * SW Change siehe proginfo 24.08.2015
 * 
 *    Rev 1.22   08 Jul 2015 08:55:12   ybadal
 * - new Filter implemented in sensor.c.
 * - Variablen fÃ¼r Set_ss werden auf absoluten Adressen im Bank0 verlinkt.
 * - bugsfix to Review Punkte mit den Whiteboxtester aus Polen Olejnik, Piotr / Dulski, Mariusz .sehe Exel Datei sensor_algo_V03.03_issues_review.
 * -Oversampling  fÃ¼r die Rohr Sensor Messerung implementiert.
 * 
 *    Rev 1.21   02 Jun 2015 13:12:12   ybadal
 * Diverse TT Punkte und Review Punkte.
 * 
 *    Rev 1.20   28 May 2015 10:52:26   ybadal
 * Huf Guidline SW Coding implementiert.
 * 
 *    Rev 1.19   20 May 2015 16:27:08   ybadal
 * - Diverse Misra Rules behoben.
 * - Abstraction betwenn  sensor aquisition sensor analyse.
 * 
 *    Rev 1.18   19 May 2015 11:31:02   ybadal
 * Misra Rules "Macro 'XX' does not expand to compliant construct. (required)" fixed
 * 
 *    Rev 1.17   12 May 2015 15:48:36   ybadal
 * - Diverse TeamTrack Punkte implementiert.
 * -neue Debouce Zeiten sind jetzt mit dem Timing System realisiert.
 * 
 *    Rev 1.16   13 Feb 2015 13:01:22   ybadal
 * - add comments to the sensor_algo module.
 * -bugfix for TT 9361.
 * 
 *    Rev 1.15   Feb 04 2015 09:41:30   mstei
 * Naming convention for constants (preprocessor defines) according to CSpec-095 Rev. 01 - Guideline for Software Coding.pdf.
 * 
 *    Rev 1.14   Feb 02 2015 15:13:52   mstei
 * Naming convention for enums according to CSpec-095 Rev. 01 - Guideline for Software Coding.pdf.
 * 
 *    Rev 1.13   Jan 30 2015 16:41:08   mstei
 * Naming convention for preprocessor defines according to CSpec-095 Rev. 01 - Guideline for Software Coding.pdf
 * 
 *    Rev 1.12   Jan 26 2015 16:48:24   mstei
 * Changes for compliance with CSpec-095 Rev. 01 - Guideline for Software Coding.pdf:
 * - comments from C++ were modified to C comments
 * - name of the project changed in the header of the file
 * 
 *    Rev 1.11   26 Jan 2015 14:15:54   apeschl
 * Sensor parameter changed
 * 
 *    Rev 1.10   23 Oct 2014 13:36:00   apeschl
 * ER_APPROACH_200MS_U16 auf 1 zur Verbesserung der Hall Simulation
 * 
 *    Rev 1.9   24 Sep 2014 08:44:20   ybadal
 * - Sensor Maximale AuslÃ¶se Zeit auf 3Sekunden fÃ¼r den Entriegeln Sensor und auf 35 Sekunden FÃ¼r den Verriegeln Sensor angepasst.
 * - ER_NOISE_OCCUR_COUNTER und VR_NOISE_OCCUR_COUNTER  auf 50.
 * - LOCK_ADD_BOUNDARY und UNLOCK_ADD_BOUNDARY auf 3  eingestellt.
 * - Sensor  Entprellzeit von einem sample auf 2 Samples geÃ¤ndert (ER_DEBOUNCE_EEP_U8 & VR_DEBOUNCE_EEP_U8).
 * 
 *    Rev 1.8   19 Sep 2014 13:15:50   apeschl
 * Sensorparameter an Griff angepasst
 * 
 *    Rev 1.7   11 Sep 2014 11:57:16   apeschl
 * adjustment of sensor thresholds
 * 
 *    Rev 1.6   29 Aug 2014 08:51:46   ybadal
 * Bug fixed for TT  8644  und TT 8913
 * 
 *    Rev 1.5   25 Aug 2014 16:15:52   ybadal
 * Sensor EmpfÃ¤ndlichkeit Ã¼ber das Define U16_ER_SENSIVITY_APPROACH und U16_ER_SENSIVITY_TOUCH  einzustellen.
 * 
 *    Rev 1.4   17 Jul 2014 10:12:58   ybadal
 * Code Umsetzung zum Review  von 15.07.2014
 * 
 *    Rev 1.3   15 Jul 2014 15:09:20   ybadal
 * - Diverse SW Ã„nderungen unter anderen Review Punkten (siehe Prog_info von SW Version 02.01).
 * 
 *    Rev 1.1   12 May 2014 17:15:32   ybadal
 * -VW Kommunication implementiert.
 * - Bug Fix for TT 8621
 * 
 *    Rev 1.0   28 Mar 2014 14:10:44   ybadal
 * Initial revision.
 * 
 *    Rev 1.1   09 Dec 2013 16:21:14   ybadal
 * NFC Part implementiert.
 * 
 *    Rev 1.0   25 Nov 2013 09:44:20   ufalkne
 * Initial revision.
 * 
 *    Rev 1.1   29 Oct 2013 14:56:48   ybadal
 * - Sensor Abtastrate im Diagnose Mode Output (MeasureValueRequest)korrigiert. (von 10 ms auf  5ms). 
 * -weiteren Code Optimierungen.
 * 
 *    Rev 1.0   Oct 24 2013 15:48:00   pclemen
 * Initial revision.
 * 
*********************************************************** end of comment */
