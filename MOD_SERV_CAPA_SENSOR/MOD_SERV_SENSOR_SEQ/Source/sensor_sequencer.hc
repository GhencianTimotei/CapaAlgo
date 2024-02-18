/*------------------------------------------------------------------------------------------------+
| Modul: APPL_SENSOR.hc                                                                              |
+-------------------------------------------------------------------------------------------------+
| Project: VW511CS                                                                                |
|          Huf Huelsbeck und Fuerst                                                               |
|          (Name des Programmierers), PDES                                                        |
+-------------------------------------------------------------------------------------------------+
| Short description:                                                                              |
| CAS Signal Handler, Handler for the CAS SCI IO-Signals and the logic combinations               |
|                                                                                                 |
+-------------------------------------------------------------------------------------------------+
| Changes:                                                                                        |
| 10.09.13 - DBO first version                                                                    |
|                                                                                                 |
+-------------------------------------------------------------------------------------------------+
| for Information, to do:                                                                         |
|                                                                                                 |
+-------------------------------------------------------------------------------------------------+
| $Revision:   1.0  $                                                                             |
|                                                                                                 |
+------------------------------------------------------------------------------------------------*/
#ifndef  APPL_SENSOR_HC
#define  APPL_SENSOR_HC       /* FileName_C */

#ifdef APPL_SENSOR_C                        /*  FileName_C */
  #define seq_export
#else
  #define seq_export extern
#endif

/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > should be keept for future usage*/
#define U16_SENSOR_CYCLE_TIME ((U16)10)

#endif
/* Automatic logging by PVCS ***********************************************
$Log:   J:/vmfs/VW/1508.008_380_ODH/archives/3_Coding/ECU_NFC_STACK-NXP/MCU_RL78/MOD_SERV_CAPA_SENSOR/MOD_SERV_SENSOR_SEQ/Source/sensor_sequencer.hc-arc  $
 * 
 *    Rev 1.0   Sep 22 2017 16:12:24   Sbhanda
 * Initial revision.
 * 
 *    Rev 1.1   Aug 07 2017 15:50:52   ybadal
 * - call the new sequence for mcvd or cvd.
 * 
 *    Rev 1.0   Apr 13 2017 13:24:50   ufalkne
 * Initial revision.
 * 
 *    Rev 1.5   09 Sep 2015 10:54:40   umuelle3
 * MISRA changes proposed by Polyspace.
 * 
 *    Rev 1.4   Jan 26 2015 13:00:20   mstei
 * Changes for compliance with CSpec-095 Rev. 01 - Guideline for Software Coding.pdf:
 * - changes in the header of the file
 * - change to add PVCS history

*********************************************************** end of comment */
