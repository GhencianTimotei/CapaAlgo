/*------------------------------------------------------------------------------------------------+
| Modul: APPL_SENSOR.ha                                                                              |
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
| $Revision:   1.3  $                                                                             |
|                                                                                                 |
+------------------------------------------------------------------------------------------------*/
#ifndef  APPL_SENSOR_HA
#define  APPL_SENSOR_HA       /* FileName_C */

/* SCI machine states */
typedef enum
{
       EN_APPL_SENSOR_ACTIVE_MODE_STATE,
       EN_APPL_SENSOR_PON_STATE,
       EN_APPL_SENSOR_DISABLE_STATE,
       EN_CAS_MAX_STATE
} APPL_SENSOR_STATE_LIST_T;




#endif
/* Automatic logging by PVCS ***********************************************
$Log:   J:/vmfs/VW/1508.008_380_ODH/archives/3_Coding/ECU_NFC_STACK-NXP/MCU_RL78/MOD_SERV_CAPA_SENSOR/MOD_SERV_SENSOR_SEQ/Source/sensor_sequencer.ha-arc  $
 * 
 *    Rev 1.3   Oct 25 2018 13:11:06   ybadal
 * functional redesign to control  sensor  activity when disabled.
 * 
 *    Rev 1.2   06 Apr 2018 14:07:50   ybadal
 * - bug fix TT 17867
 * - HIS and Misra enhanced.
 * 
 *    Rev 1.1   Nov 29 2017 10:26:36   ybadal
 * - add can message 
 * - implement sleep mode
 * 
 *    Rev 1.0   Sep 22 2017 16:12:22   Sbhanda
 * Initial revision.
 * 
 *    Rev 1.1   Aug 07 2017 15:50:50   ybadal
 * - call the new sequence for mcvd or cvd.
 * 
 *    Rev 1.0   Apr 13 2017 13:24:50   ufalkne
 * Initial revision.
 * 
 *    Rev 1.12   09 Sep 2015 16:16:36   umuelle3
 * Check JANKINS
 * 
 *    Rev 1.11   09 Sep 2015 10:54:40   umuelle3
 * MISRA changes proposed by Polyspace.
 * 
 *    Rev 1.10   29 May 2015 09:45:18   ybadal
 * Bug fix for TT10411
 * - Diverse TT Review Punkte abgeschlossen.
 * 
 *    Rev 1.9   22 May 2015 11:08:04   ybadal
 * - Redesign des Mechanismus mit dem Aktive Mode.
 * 
 *    Rev 1.8   19 May 2015 11:30:58   ybadal
 * Misra Rules "Macro 'XX' does not expand to compliant construct. (required)" fixed
 * 
 *    Rev 1.7   Feb 04 2015 08:51:18   mstei
 * Naming convention for constants (preprocessor defines) according to CSpec-095 Rev. 01 - Guideline for Software Coding.pdf.
 * 
 *    Rev 1.6   Feb 02 2015 15:00:30   mstei
 * Naming convention for enums according to CSpec-095 Rev. 01 - Guideline for Software Coding.pdf.
 * 
 *    Rev 1.5   Jan 30 2015 16:29:36   mstei
 * Naming convention for preprocessor defines according to CSpec-095 Rev. 01 - Guideline for Software Coding.pdf
 * 
 *    Rev 1.4   Jan 26 2015 12:42:26   mstei
 * Changes for compliance with CSpec-095 Rev. 01 - Guideline for Software Coding.pdf:
 * - changes in the header of the file
 * - change to add PVCS history

*********************************************************** end of comment */
