/*
 * \defgroup main_os (senor.c) Main Program
 * \{
 ******************************************************************************
 * \image html
 *
 * \par Module Owner:
 *   Huf H&uuml;lsbeck & F&uuml;rst GmbH & Co. KG \n
 *   Steeger Str. 17 \n
 *   42551 Velbert \n
 *   Department PDES
 *
 * \par Initial Project:
 *   - 1256.001_TAG_PE
 *
 ******************************************************************************
 * \par Description:
 * performs a capacitive measurement on all enabled
 * sensors. The measured signals for each sensor are then processed to
 * check for user touches, releases,
 *
 ******************************************************************************
 *
 *  $Workfile:   sensor_mcvd.ha  $
 *  $Revision:   1.0  $
 *  $Date:   Sep 22 2017 16:12:04  $
 *  $Author:   Sbhanda  $
 *
 ******************************************************************************
 *
 * \par Purpose:
 *    OS, main part of operation system
 *
 * \par Compiler:
 *    ANSI, GHS specific pragmas for interrupt handling
 *
 * \par Controller:
 *    -
 *
 * \res_start
 *    \res_item{ROM,             0 kByte, }
 *    \res_item{RAM,             0  Byte, }
 *    \res_item{EEPROM,          0 Byte , }
 *    \res_item{Runtime Init,    X ms   , }
 *    \res_item{Runtime Task,    X ms   , }
 * \res_end
 *
 *
 * \qual_start
 *    \qual_item{Maintainability,   0,  0,  0,  0}
 *    \qual_item{Analyzeability ,   0,  0,  0,  0}
 *    \qual_item{Changeability  ,   0,  0,  0,  0}
 *    \qual_item{Stability      ,   0,  0,  0,  0}
 *    \qual_item{Testability    ,   0,  0,  0,  0}
 * \qual_end
 *
 * \par MISRA rules violations:
 *   \li t.b.d.
 *
 ******************************************************************************
 *
 * \attention
 *   \li -
 *
 ******************************************************************************
 *
 * \par Changes:
 *   \li 08.03.99 - DBO first version
 *   \li 06.05.10 - DBO Module vip_signal_hdl added
 ******************************************************************************/
#ifndef SENSOR_MCVD_HA
#define SENSOR_MCVD_HA











#endif


    




/* Automatic logging by PVCS ***********************************************

$Log::   J:/vmfs/VW/1508.008_380_ODH/archives/3_Coding/ECU_NFC_STACK-NXP/MCU_RL78/MOD_SERV_CAPA_SENSOR/MOD_SERV_MCVD_$
 * 
 *    Rev 1.0   Sep 22 2017 16:12:04   Sbhanda
 * Initial revision.
 * 
 *    Rev 1.0   Aug 07 2017 12:26:00   ybadal
 * Initial revision.
 * 
 *    Rev 1.15   Jun 16 2017 12:43:16   ybadal
 * - filter initialization sequence implemented.
 * 
 *    Rev 1.14   Jun 07 2017 17:08:40   ybadal
 * bug fix for por false detection.
 * 
 *    Rev 1.13   May 19 2017 16:10:54   ybadal
 * - subfunctions ensor_lock_iir_filter  anf sensor_unlock_fir_filter for better his metrics
 * 
 *    Rev 1.12   May 17 2017 12:06:08   ybadal
 * - 3 cascade Levels for FIR filter for unlock sensor.
 * 
 *    Rev 1.11   May 16 2017 14:45:20   ybadal
 * - bug fix when TIMING_IRQ_MODE is defined.
 * - remove used variables in the sensor structure.
 * 
 *    Rev 1.10   May 12 2017 15:20:50   ybadal
 * -some misra and his topics fixed.
 * 
 *    Rev 1.9   May 02 2017 15:23:56   ybadal
 * - change the parameter U8_PON_FILTER_RESPONCE_LOOP  to 16.
 *  - call Task_plc_handler() before filter process to correct the plc pulse time.
 * 
 *    Rev 1.8   21 Apr 2017 14:17:22   ybadal
 * - for unlock sensor a new 1 order iir low pass filter.
 *  - for lock sensor a new exponential average   iir  filter.
 * 
 *    Rev 1.7   19 Jan 2017 16:25:02   ybadal
 * -  no interrupt disable is allowed due to lf requirement immediatly handling.
 * - some HIS points are fixed.
 * 
 *    Rev 1.6   16 Jan 2017 18:01:40   ybadal
 * -  bug fix for lf interrupt when 31khz time is active that the the requirement of 15ms restart time not fulfilled.
 * - fix some misra and his rules.
 * 
 *    Rev 1.5   09 Dec 2016 10:23:08   ybadal
 *  - some code change for matlab mex process.
 *  - disturbance detection implemented but is not active( to activate it you shall define "DISTURBANCE_ACTIVE"   in config.h or in makefile) 
 * 
 *    Rev 1.4   26 Sep 2016 16:46:08   rmunizv
 *  - added variable 
 * 
 *    Rev 1.3   29 Aug 2016 15:42:48   ybadal
 * - bug fix for diverse misra rules.
 * 
 *    Rev 1.2   18 Aug 2016 15:44:42   ybadal
 * - new algo implemened according to HIS and Misra rules .
 * - SW architecture improvement.
 * 
 *    Rev 1.1   15 Aug 2016 16:02:00   ybadal
 * - new iir filter implemended.
 * - new filter structure according to the sensor design implemented.
 * 
 *    Rev 1.6   29 Jun 2016 13:32:46   ybadal
 * -  plausibility check window is changed from 30 to 170 for unlock sensor.
 *  -  plausibility check window is changed from 30 to 50 for lock sensor.
 *  -  plausibility check will stop anymore the filter if implausible sensor data is     
 *    detected , but when the algo is active the plausibility check result is ignored and the   
 *    filter shall resume with the new sensor data.(no filter recalibration).
 *  -   debounce time of 10 samples is needed when the plausibility check is not active after activation.
 * 
 *    Rev 1.5   10 Jun 2016 09:40:04   ybadal
 *  - Bug fix for not stoping filter by LF detection.
 *  - Bug fix for not stoping filter by disturbance .
 * 
 *    Rev 1.16   22 Dec 2015 16:39:22   ybadal
 * moduls and functions Headers changed to HUF standard header.
 * 
 *    Rev 1.15   10 Nov 2015 11:28:34   ybadal
 * rain detection improved.
 * 
 *    Rev 1.14   04 Nov 2015 08:55:58   ybadal
 * general noise detection implemented.
 * 
 *    Rev 1.13   22 Oct 2015 12:19:38   ybadal
 * - SW Umstellung für unterschiedlische Daten Ausgabe implementiert.
 * 
 *    Rev 1.12   19 Oct 2015 09:38:26   ybadal
 * 1) VW Stand 09.09 auf Toyota portiert.
 * 2) ECVD Stand 15.09. realisiert (Dithering -> 11Bit, Carrier -> 2048, Preselector ohne Loop)
 * - DAC Spannung für den Comparator auf 500 mV eigestellt
 * - Comparator Output aktiviert.
 * 
 *    Rev 1.11   09 Jul 2015 09:33:08   ybadal
 * - die richtigen Dateien für die Änderungen sind jetzt eingecheckt.
 * - neues Komunnikationsmodul implementiert.
 * - bug fix for TT punkte 10331 / 10539 / 10550 / 10552 / 10558 /10551.
 * 
 *    Rev 1.9   30 Apr 2015 15:44:50   ybadal
 * Verzugszeit für die Regelung.
 * Neues LF-Erkennung Verfahren basiert auf Messwert Analayse.
 * 
 *    Rev 1.8   23 Feb 2015 11:08:44   ybadal
 * - 9 Bytes Daten Ausgabe für CA Diagnose mit dem Define CA_DIAGNOSE_OUTPUT zu aktivieren.
 * 
 *    Rev 1.7   18 Feb 2015 17:50:46   ybadal
 * - Rauschanalyse wurde ausgeschaltet.
 * - Sensor Regelung implementiert.
 *
 *    Rev 1.6   Feb 11 2015 16:44:00   jyomkil
 * RA0 wird nach jedem CCT Sample erst auf Low und danach als Input gesetzt.
 *
 *    Rev 1.5   11 Feb 2015 13:27:04   ybadal
 * - Data debug Pin (RA0) als Reference spannungspin für den internen kondensator.
 * - Rauschflag bei 3  Entprellungen erst aktivierbar.
 * - Bugfix für Desaktivierung des Rauschoffsets am Referenzwert.
 *
 *    Rev 1.4   Feb 06 2015 13:49:44   jyomkil
 * Noise Threshold geändert.
 *
 *    Rev 1.3   03 Feb 2015 14:22:40   ybadal
 * - Auslöseschwelle auf 100 gesetzt.
 * - Umladezeit auf 4  gesetzt.
 * - Rauschmodusgrenze ist von 5 auf 10 geändert.
 * - OVS Messwert durch 2 für den VR Sensor dividiert.
 * - OVS Messwert durch 4 für den ER Sensor dividiert.
 *
 *    Rev 1.2   02 Feb 2015 11:09:30   ybadal
 * - LF Signal Mechanismus implemtiert.
 * - Power Line kommunikation mit dem Sensor Task synchronisiert.
 *
 *    Rev 1.1   11 Dec 2014 09:58:54   ybadal
 * - Toyota Power Kommunikation implementiert.
 * - neues Messwerk auf die neue HW Angepoasst,es wurden    Makros für die HW spezifischen Elemente erstellt .
 * -72h Low Power Mode entfernt.
 *
 *
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
 * Variable für Schaltschwelle eingefügt.
 *
 *    Rev 1.1   22 Apr 2014 14:53:58   ybadal
 * algo flags erweitert
 *
 *    Rev 1.0   28 Mar 2014 14:10:06   ybadal
 * Initial revision.
 *
 *    Rev 1.3   07 Jan 2014 12:18:32   ybadal
 * - NFC Karten Erkennung wird über eine State Machine durchlaufen.
 * - NFC Antennen Rekalibrierung bei grössen Phasen Änderungen  implementiert.
 * - NFC Part mit dem Compiler Switches "NFC_PART_AKTIV" zu aktivieren.
 *
 *    Rev 1.2   13 Dec 2013 12:48:32   ybadal
 * - NFC Phasen Messung korrigiert.
 * -NFC Funktionalität wird über den Parameter (E_EEP_VR_Par_Mirr_6 == 1 ) aktiviert
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
 * -weitere Code Optimierungen im Sensor_algo.c Cas_appl.c
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
 * Flag Definition für EEP_Write_Access_u8 hinzu
 *
 *    Rev 1.0   Sep 06 2011 11:45:20   dhansen
 * Initial revision.
 *
 *    Rev 1.8   Feb 28 2011 09:13:08   dbotsch
 * - SW 03.03 vom 28.02.2011
 * - Anpassung CAS-Timing am F01 Variante V. 06.00
 *
 *    Rev 1.7   Oct 16 2009 08:14:30   pgastel
 * Verriegelung ER bei VR-Auslösung
 * SW-Index auf 206 in config.h gesetzt
 * 16.10.2009
 *
 *    Rev 1.6   Oct 07 2009 13:54:58   pgastel
 * Ergänzungen. serielle Ausgabe Senswerte und Regelparameter für Tage Monitor umgesetzt
 *
 *    Rev 1.5   Oct 02 2009 09:22:18   pgastel
 * keine Aenderungen zur vorhergehenden Revision
 *
 *    Rev 1.4   Oct 02 2009 08:06:36   pgastel
 * 02.10.09
 * EEPROM-Parameter angepaßt
 *
 *    Rev 1.3   Sep 30 2009 10:34:22   pgastel
 * Parametrierung über Diagnosetool umgesetzt
 * Initialisierungswerte angepaßt
 * Bedämpfung VR bei Snapback-Funktion überarbeitet
 *
 *    Rev 1.2   Sep 14 2009 08:50:10   pgastel
 * Bedämpfung VR-Sensor bei Snap-Back
 *
 *    Rev 1.1   Sep 02 2009 13:56:12   pgastel
 * Verzugszeit VR auf 300 ms geändert
 * Gegenseitige Verriegelungen VR und ER entfernt
 *
 *    Rev 1.0   Aug 27 2009 08:35:16   dbotsch
 * Initial revision.
*
 *

*********************************************************** end of comment */

