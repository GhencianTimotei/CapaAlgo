/*!
 * \defgroup  (sensor_aquistion.ha) Main Program
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
 *
 * sensor acquisition layer ,depend on  Which measurement unit is active perform the cvd
 * or the mcvd measurement.
 *
 ******************************************************************************
 *
 *  $Workfile:   sensor_aquisition.ha  $
 *  $Revision:   1.0  $
 *  $Date::   Sep 22 2017 16:12:14  $
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
 ******************************************************************************/
#ifndef SENSOR_AQUISITION_HA
#define SENSOR_AQUISITION_HA

/* polyspace < MISRA-C3:2.5 : Not a defect > Justify with annotations > should be kept for future usage */
#define U8_ER_MITTEL_ADD_COUNT          ((U8) 32)   /* count of samples for mean value (ER) */
/* polyspace < MISRA-C3:2.5 : Not a defect > Justify with annotations > should be kept for future usage */
#define U8_VR_MITTEL_ADD_COUNT          ((U8) 32)   /* count of samples for mean value (ER) */
/* polyspace < MISRA-C3:2.5 : Not a defect > Justify with annotations > should be kept for future usage */
#define U8_SENSORCALIBRATION_NOT_DONE   ((U8) 0)   /* count of samples for mean value (ER) */
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define U8_SENSORCALIBRATION_DONE       ((U8) 1)   /* count of samples for mean value (ER) */

/* Automatic logging by PVCS ***********************************************

$Log:   J:/vmfs/VW/1508.008_380_ODH/archives/3_Coding/ECU_NFC_STACK-NXP/MCU_RL78/MOD_SERV_CAPA_SENSOR/MOD_SERV_SENSOR_AQUISITION/Source/sensor_aquisition.ha-arc  $
 * 
 *    Rev 1.0   Sep 22 2017 16:12:14   Sbhanda
 * Initial revision.
 * 
 *    Rev 1.0   Aug 07 2017 15:49:34   ybadal
 * Initial revision.
 * 
 *    Rev 1.0   19 Oct 2015 12:25:00   ybadal
 * Initial revision.
 * 
 *********************************************************** end of comment */
#endif /*SENSOR_AQUISITION_CA*/


