/*!
 * \defgroup <sensor_diag.c>
 * \{
 ******************************************************************************
 * \image html ""
 *
 * \par Module Owner:
 *   Huf H&uuml;lsbeck & F&uuml;rst GmbH & Co. KG \n
 *   Steeger Str. 17 \n
 *   42551 Velbert \n
 *   Department PDE-S
 *
 * \par Initial Project:
 *   1508.008_380_ODH
 *
 ******************************************************************************
 * \par Description:
 * during develepement time(rain / EMC tests)   a sensor data (filter result, threshold, raw data, touch state....)will be send over UART interafce to the HUF monitor for later analyse with the tools matlab
 * the UART communication is based on Software UART, the communication speed is to configure with the define BAUDRATE (38Kb or 115100kb)
 * and the controller pin is to configure with the define RS232_PIN.
 ******************************************************************************
 *
 *  $Workfile:   sensor_diag.h  $
 *  $Revision:   1.0  $
 *  $Date:   Sep 22 2017 16:12:18  $
 *  $Author:   Sbhanda  $
 *
 ******************************************************************************
 * Change history:
 * see PVCS History at the end of the file
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
 ******************************************************************************/

#ifndef SENSOR_DIAG_H
#define SENSOR_DIAG_H


#ifdef SENSOR_DIAG_C
	#define SENSOR_DIAG_EXPORT
#else
	#define SENSOR_DIAG_EXPORT extern
#endif



#include "sensor_diag.hc"
#include "sensor_diag.ha"
#include "sensor_diag.hi"
#include "sensor_diag.hm"
#include "S32K144.h"
/* polyspace:begin < MISRA-C3:D4.9 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */
/* polyspace:begin < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define SET_PTA_RS232_OUTPUT()    { PTA->PDDR |= RS232_MASK; }
#define SET_PTA_RS232_INPUT()     { PTA->PDDR &= ~(RS232_MASK); }

#define SET_PTA_RS232_LOW()      { PTA->PDOR &= ~(RS232_MASK); }
#define SET_PTA_RS232_HIGH()     { PTA->PDOR |= (RS232_MASK); }

#define SET_PTA_RS232_PCOR()     { PTA->PCOR |= (RS232_MASK); }
#define SET_PORTA_RS232()        { PORTA->PCR[4] |= 0x100; }
extern void NfcDevMsg_SendMessage();
/* polyspace:end < MISRA-C3:D4.9 : Not a defect : Justify with annotations > This macro is used to facilitate an easy adaptation */
/* polyspace:end < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#endif



/* Automatic logging by PVCS ***********************************************

$Log::   J:/vmfs/VW/1508.008_380_ODH/archives/3_Coding/ECU_NFC_STACK-NXP/MCU_RL78/MOD_SERV_CAPA_SENSOR/MOD_SERV_SENS$
 * 
 *    Rev 1.0   Sep 22 2017 16:12:18   Sbhanda
 * Initial revision.
 * 
 *    Rev 1.0   Aug 07 2017 10:28:32   ybadal
 * Initial revision.
 * 
 *    Rev 1.0   Apr 13 2017 13:24:58   ufalkne
 * Initial revision.
 * 
 *    Rev 1.22   18 Sep 2015 07:55:52   ybadal
 * New Structure implementiert.(neues messwerk und signal analyse)siehe Prog Info von v04.01
 * 
 *    Rev 1.21   09 Sep 2015 10:57:52   umuelle3
 * MISRA changes proposed by Polyspace.
 * 
 *    Rev 1.20   08 Jul 2015 08:55:10   ybadal
 * - new Filter implemented in sensor.c.
 * - Variablen f�r Set_ss werden auf absoluten Adressen im Bank0 verlinkt.
 * - bugsfix to Review Punkte mit den Whiteboxtester aus Polen Olejnik, Piotr / Dulski, Mariusz .sehe Exel Datei sensor_algo_V03.03_issues_review.
 * -Oversampling  f�r die Rohr Sensor Messerung implementiert.
 * 
 *    Rev 1.19   10 Jun 2015 08:52:08   ybadal
 * - Powerup Kalibration wurde ersetzt.
 * - weitere Misra Rules gefixt.
 * 
 * 
 *    Rev 1.18   02 Jun 2015 13:12:12   ybadal
 * Diverse TT Punkte und Review Punkte.
 * 
 *    Rev 1.17   29 May 2015 14:24:40   ybadal
 * - Diverse TT Reviews weiter implementiert.
 * - einige Misra Violation behoben.
 * 
 *    Rev 1.16   28 May 2015 10:52:24   ybadal
 * Huf Guidline SW Coding implementiert.
 * 
 *    Rev 1.15   20 May 2015 16:27:02   ybadal
 * - Diverse Misra Rules behoben.
 * - Abstraction betwenn  sensor aquisition sensor analyse.
 * 
 *    Rev 1.14   19 May 2015 11:31:00   ybadal
 * Misra Rules "Macro 'XX' does not expand to compliant construct. (required)" fixed
 * 
 *    Rev 1.13   13 May 2015 15:19:46   ybadal
 * Bug fix for TT 10412  ,TT 10402 and TT 10397
 * 
 *    Rev 1.12   12 May 2015 15:45:34   ybadal
 *  - MISRA RULES : Assembly language shall be encapsulated and isolated.
 * -Dezimation filter implemented to activate with the Define DECIMATION_FILTER
 * 
 *    Rev 1.11   Feb 04 2015 09:27:44   mstei
 * Naming convention for macros according to CSpec-095 Rev. 01 - Guideline for Software Coding.pdf.
 * 
 *    Rev 1.10   Feb 02 2015 15:12:16   mstei
 * Naming convention for enums according to CSpec-095 Rev. 01 - Guideline for Software Coding.pdf.
 * 
 *    Rev 1.9   Jan 30 2015 16:40:12   mstei
 * Naming convention for preprocessor defines according to CSpec-095 Rev. 01 - Guideline for Software Coding.pdf
 * 
 *    Rev 1.8   Jan 29 2015 13:11:48   mstei
 * Naming convention for variables. There should no changes in the hex file.
 * 
 *    Rev 1.7   Jan 26 2015 15:05:02   mstei
 * Changes for compliance with CSpec-095 Rev. 01 - Guideline for Software Coding.pdf:
 * - changes in the header of the file
 * 
 *    Rev 1.6   29 Aug 2014 08:51:42   ybadal
 * Bug fixed for TT  8644  und TT 8913
 * 
 *    Rev 1.5   17 Jul 2014 10:12:58   ybadal
 * Code Umsetzung zum Review  von 15.07.2014
 * 
 *    Rev 1.4   22 May 2014 16:41:04   ybadal
 * - Bug Fixed for Team Track Error : TT8640 ,TT8623 und TT8621.
 * -72 Hours Low Power Message implementiert.
 * -Power up Message implementiert.
 * 
 *    Rev 1.3   12 May 2014 17:15:30   ybadal
 * -VW Kommunication implementiert.
 * - Bug Fix for TT 8621
 * 
 *    Rev 1.2   22 Apr 2014 14:58:08   ybadal
 * Variable f�r Schaltschwelle eingef�gt.
 * 
 *    Rev 1.1   22 Apr 2014 14:53:58   ybadal
 * algo flags erweitert
 * 
 *    Rev 1.0   28 Mar 2014 14:10:06   ybadal
 * Initial revision.
 * 
 *    Rev 1.3   07 Jan 2014 12:18:32   ybadal
 * - NFC Karten Erkennung wird �ber eine State Machine durchlaufen.
 * - NFC Antennen Rekalibrierung bei gr�ssen Phasen �nderungen  implementiert.
 * - NFC Part mit dem Compiler Switches "NFC_PART_AKTIV" zu aktivieren.
 * 
 *    Rev 1.2   13 Dec 2013 12:48:32   ybadal
 * - NFC Phasen Messung korrigiert.
 * -NFC Funktionalit�t wird �ber den Parameter (E_EEP_VR_Par_Mirr_6 == 1 ) aktiviert
 * 
 *    Rev 1.1   09 Dec 2013 16:21:08   ybadal
 * NFC Part implementiert.
 * 
 *    Rev 1.0   25 Nov 2013 09:44:10   ufalkne
 * Initial revision.
 * 
 *    Rev 1.7   19 Nov 2013 11:30:06   ybadal
 * - Umsetzung des Code Reviews von 07.11.13.
 * (Siehe Proginfo von 19.11.2013 v01.04 )
 * 
 *    Rev 1.6   06 Nov 2013 17:10:22   ybadal
 * -weitere Code Optimierungen im Sensor_algo.c APPL_SENSOR.c
 * 
 *    Rev 1.4   Oct 24 2013 15:51:04   pclemen
 * Algo-Implementierung
 * 
 *    Rev 1.3   02 Oct 2013 08:08:58   ybadal
 * weitere Umsetzung des Code Reviews von 11.09.2013.
 * 
 *    Rev 1.2   11 Sep 2013 13:45:16   ybadal
 * - mechanismus zur korrektur des Timinsystems implementiert (aktiv mit dem Define "CALTCULATE_MEASURE")
 * 
 *    Rev 1.0   28 May 2013 09:30:30   dwippic
 * Initial revision.
 * 
 *    Rev 1.1   24 Jan 2012 11:41:16   apeschl
 * Flag Definition f�r EEP_Write_Access_u8 hinzu
 *
 *    Rev 1.0   Sep 06 2011 11:45:20   dhansen
 * Initial revision.
 *
 *    Rev 1.8   Feb 28 2011 09:13:08   dbotsch
 * - SW 03.03 vom 28.02.2011
 * - Anpassung CAS-Timing am F01 Variante V. 06.00
 *
 *    Rev 1.7   Oct 16 2009 08:14:30   pgastel
 * Verriegelung ER bei VR-Ausl�sung
 * SW-Index auf 206 in config.h gesetzt
 * 16.10.2009
 *
 *    Rev 1.6   Oct 07 2009 13:54:58   pgastel
 * Erg�nzungen. serielle Ausgabe Senswerte und Regelparameter f�r Tage Monitor umgesetzt
 *
 *    Rev 1.5   Oct 02 2009 09:22:18   pgastel
 * keine Aenderungen zur vorhergehenden Revision
 *
 *    Rev 1.4   Oct 02 2009 08:06:36   pgastel
 * 02.10.09
 * EEPROM-Parameter angepa�t
 *
 *    Rev 1.3   Sep 30 2009 10:34:22   pgastel
 * Parametrierung �ber Diagnosetool umgesetzt
 * Initialisierungswerte angepa�t
 * Bed�mpfung VR bei Snapback-Funktion �berarbeitet
 *
 *    Rev 1.2   Sep 14 2009 08:50:10   pgastel
 * Bed�mpfung VR-Sensor bei Snap-Back
 *
 *    Rev 1.1   Sep 02 2009 13:56:12   pgastel
 * Verzugszeit VR auf 300 ms ge�ndert
 * Gegenseitige Verriegelungen VR und ER entfernt
 *
 *    Rev 1.0   Aug 27 2009 08:35:16   dbotsch
 * Initial revision.
*
 *

*********************************************************** end of comment */
