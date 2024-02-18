/*
 * \defgroup  (sensor_aquisition.h) Main Program
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
 *   - 1508.008_380_ODH
 *
 ******************************************************************************
 * \par Description:
 * sensor acquisition layer ,depend on  Which measurement unit is active perform the cvd
 * or the mcvd measurement.
 ******************************************************************************
 *
 *  $Workfile:   sensor_aquisition.h  $
 *  $Revision:   1.0  $
 *  $Date:   Sep 22 2017 16:12:14  $
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


#ifndef SENSOR_AQUISITION_H
#define SENSOR_AQUISITION_H


#include "sensor_aquisition.hc"
#include "sensor_aquisition.ha"
#include "sensor_aquisition.hi"
#include "sensor_aquisition.hm"


#endif


/* Automatic logging by PVCS ***********************************************

$Log::   J:/vmfs/VW/1508.008_380_ODH/archives/3_Coding/ECU_NFC_STACK-NXP/MCU_RL78/MOD_SERV_CAPA_SENSOR/MOD_SERV_SENSOR$
 * 
 *    Rev 1.0   Sep 22 2017 16:12:14   Sbhanda
 * Initial revision.
 * 
 *    Rev 1.1   Aug 08 2017 09:29:52   ybadal
 * - functions for cvd measurement for lock and unlock are moved to the module MOD_SERV_CVD_SENSOR_AQUISITION
 * - the both measurement principal cvd and mcvd are now implemented and can be activated by the define USED_SENSOR_MEASUREMENT_PRINCIPLE
 * - rename some functions to identify the cvd from mcvd measurement process.
 * 
 *    Rev 1.7   22 Dec 2015 16:39:28   ybadal
 * moduls and functions Headers changed to HUF standard header.
 * 
 *    Rev 1.6   17 Nov 2015 14:43:02   omuelle
 * forced correct timings by forcing memory addresses
 * 
 *    Rev 1.5   12 Nov 2015 16:58:22   omuelle
 * corrected order of time slices
 * 
 *    Rev 1.4   10 Nov 2015 11:28:36   ybadal
 * rain detection improved.
 * 
 *    Rev 1.3   04 Nov 2015 08:56:02   ybadal
 * general noise detection implemented.
 * 
 *    Rev 1.2   22 Oct 2015 17:03:18   ybadal
 * due to IIR overflow :
 * - Dittering disabled.
 * - carrier value from 2049 to 1024 changed.
 * - new disturbance detection.
 * - bugfix to compiler warning.
 * - new algo threshold  due to dittering disactivation.
 * 
 *    Rev 1.1   22 Oct 2015 12:19:40   ybadal
 * - SW Umstellung f�r unterschiedlische Daten Ausgabe implementiert.
 * 
 *    Rev 1.0   19 Oct 2015 09:43:26   ybadal
 * Initial revision.
 * 
 *    Rev 1.1   18 Sep 2015 07:55:56   ybadal
 * New Structure implementiert.(neues messwerk und signal analyse)siehe Prog Info von v04.01
 * 
 *    Rev 1.0   20 May 2015 16:25:00   ybadal
 * Initial revision.
 * 
 *    Rev 1.14   19 May 2015 11:31:00   ybadal
 ********************************************************* end of comment */
