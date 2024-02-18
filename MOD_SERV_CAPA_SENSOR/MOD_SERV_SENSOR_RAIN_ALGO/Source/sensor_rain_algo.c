/*!
 * \defgroup  (sensor_aquistion.c) Main Program
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
 *  $Workfile:   sensor_rain_algo.c  $
 *  $Revision:   1.2  $
 *  $Date::   Jul 26 2018 06:45:50  $
 *  $Author:   ybadal  $
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
#ifndef SENSOR_ALGO_RAIN_C
#define SENSOR_ALGO_RAIN_C

#ifdef INTEGRATE_FROM_V4
#include "std_inc.h"          /* Standard include files */
#endif
#ifndef INTEGRATE_FROM_V4
#include "Platform_Types.h"
#endif
#include "sensor_aquisition.h"
/* Provide own interface*/
#include "sensor_rain_algo.h"

#ifdef RAIN_MODE_DETECTION
/* locale constant 
 NOTE: both sensor use the same Parameter: for this reason are not added to the structur SENSOR_PARAMETER_T   ST_sensor_unit_par to save code*/

/*!
******************************************************************************
* \brief
* sensor_rain_drop_detector
*
* \details
* @ingroup sensor.c
 * if a sensor value has a jump in compare to the last sensor value the rain drop flag will be set
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started.
*
* \param[in]     U8 U8_Sample_counter : Sample number is used to calculate the moving average for predefined sample number
                 TASK_SENSOR_VAR_T * ST_Sensor_Var : sensor main structur
                 U16 U16_ADD_BOUNDARY : boundary window for the error detection analyse
* \param[out]    void
*
* \glob_start	 ST_Sensor_Var
                 
* \glob_end
*
* \retval         U8 PON_counter_flag
******************************************************************************
*
* \author        Y.Badal
* \version       1.0
* \date          15.09.2015
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks: the weighed average is followed calculated
 * 
 *   _______________________________
	| a	| b | c | d	| e | f | g | h |
    |___|___|___|___|___|___|___|___|
*                
*
******************************************************************************/
void sensor_rain_algo_drop_detector(TASK_SENSOR_VAR_T * Sensor_Var)
{
    U16 Temp_Diff,Temp_Diff_Ref;
    
    
    /* <editor-fold defaultstate="collapsed" desc="rain mode examination">*/  
        Temp_Diff = Sensor_Var->U16_filter_unit_result;
        Temp_Diff_Ref = Sensor_Var->U16_rain_old_value;
        Sensor_Var->BO_rain_Hand_detect = (U8)0;
        Sensor_Var->BO_rain_flag = (U8)0;
       
        if (FALSE != Sensor_Var->BO_rain_dist_detect)
        {
            if ((Temp_Diff >= (Temp_Diff_Ref)) && ((U8_RAIN_THRESHOLD > Sensor_Var->U8_peak_counter))) 
            {
                Sensor_Var->U8_peak_counter++;
            }
            else
            {
                if( U8_RAIN_THRESHOLD > Sensor_Var->U8_peak_counter )
                {
                    Sensor_Var->BO_rain_flag = (U8)1;
                }
                else
                {
                    Sensor_Var->BO_rain_Hand_detect = (U8)1;
                }
                Sensor_Var->BO_rain_dist_detect = FALSE;
                Sensor_Var->U8_peak_counter =(U8)0;
            }
        }
        else 
        {                     
            if ((Temp_Diff_Ref > (U16)0) && ((Temp_Diff > (Temp_Diff_Ref + U16_SENSOR_BOUNDARY))))
            {
             Sensor_Var->BO_rain_dist_detect = TRUE;
            }
        }  
        Sensor_Var->U16_rain_old_value = Temp_Diff;
        /* </editor-fold>*/
}
#endif


#endif 
/* Automatic logging by PVCS ***********************************************

$Log::   J:/vmfs/VW/1508.008_380_ODH/archives/3_Coding/ECU_NFC_STACK-NXP/MCU_RL78/MOD_SERV_CAPA_SENSOR/MOD_SERV_SENSOR_RAIN_ALGO/Source/se$
 * 
 *    Rev 1.2   Jul 26 2018 06:45:50   ybadal
 * remove Parameters to header Files
 * 
 *    Rev 1.1   Jun 11 2018 17:08:56   ybadal
 * bug fix for reset rain algo flag
 * 
 *    Rev 1.0   May 22 2018 12:11:50   ybadal
 * Initial revision.
 * 
 * 
*********************************************************** end of comment */
