/*!
 * \defgroup main_os (sensor_mcvd.c) Main Program
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
 * performs a mcvd capacitive measurement on all enabled
 * sensors. The measured signals for each sensor are then processed to
 * check for user touches, releases,
 *
 ******************************************************************************
 *
 *  $Workfile:   sensor_mcvd.c  $
 *  $Revision:   1.3  $
 *  $Date:   Jun 11 2018 17:08:56  $
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
 *   \li 08.03.99 - DBO first version
 *   \li 06.05.10 - DBO Module vip_signal_hdl added
 ******************************************************************************/
#ifndef SENSOR_MCVD_C
#define SENSOR_MCVD_C

#ifdef INTEGRATE_FROM_V4
#include "std_inc.h"         /* Standard include files */
#endif
#ifndef INTEGRATE_FROM_V4
#include "Platform_Types.h"
#endif
#include "sensor_algo.h"
/* polyspace <MISRA-C3:D4.4 : Not a defect: Justify with annotations > Should be kept for future usage */
//#include "timing.h"
#include "Os.h"
#ifdef INTEGRATE_FROM_V4
#include "DirectDataFlash.h"
#endif

#include "sensor_aquisition.h"
#include "sensor_mcvd.h"
#include "NvmMng.h"
#ifdef RAIN_MODE_DETECTION
#include "sensor_rain_algo.h"
#endif

/* DC values for UNLOCK (ER)/LOCK (VR) filter */
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
U16 U16_ER_filter_dfc;
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
U16 U16_VR_filter_dfc;
/* polyspace:end < MISRA-C3:8.7: Not a defect : Justify with annotations > External Usage dependent on project setup*/

#define U16_IIR_WARME_UP_CONSTANT_NOISE ST_unlock_sensor_NVM_params.U16_P_CARRIER_VALUE

typedef void (*FILTER_FUNC)(TASK_SENSOR_VAR_T * Sensor_Var,U16 NewSample_u16);
typedef SENSOR_MEASURE_VALUE_T* (*SCAN_SENSOR_FUNC)(void);
typedef void (*NOISE_DET_FUNC)(TASK_SENSOR_VAR_T * Sensor_Var,U16 NewSample_u16);

typedef  struct
{

    EN_SENSOR_ID   SensorID_EN; /*sensor id */
    FILTER_FUNC fnc_filter; /* function pointer to the sensor filter  */
    NOISE_DET_FUNC fnc_noiseDet; /* function pointer to the noise detector */
    SCAN_SENSOR_FUNC fnc_get_sensor_aquis ;/* function pointer to the get values sensor aquisiton interface*/
    U8 U8_filter_fill_init; /* window for filter warm up  */
    U8 U8_filter_init_recall; /* number of filter call during init time */

}SENSOR_PARAMETER_T;

  /*------------------------------------------------------------------------
Function    : ST_sensor_unit_par
Author      : ybadal
Input       :
Description :  sensor  main structur  content the variables for each sensor used from the sensor module.
------------------------------------------------------------------------*/
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
TASK_SENSOR_VAR_T   Sensor_Var_Str[SENSOR_MAX]; /*! sensor  main structur  content the variables for each sensor used from the sensor module.*/
  /*------------------------------------------------------------------------
Function    : ST_sensor_unit_par
Author      : ybadal
Input       :
Description :  sensor  main parameter structur  content the paramters for each sensor used from the sensor module.
------------------------------------------------------------------------*/
STATIC READONLY SENSOR_PARAMETER_T   ST_sensor_unit_par[SENSOR_MAX] ;
/*------------------------------------------------------------------------
MACRO       : U8_LOCK_FILTER_FILL_LOOP
Author      : ybadal
Input       :
Description : Specify the number of fill loop to warm up the filter for lock sensor after pon
              SWR-730
------------------------------------------------------------------------*/
#define U8_LOCK_FILTER_FILL_LOOP    ((U8)3)
/*------------------------------------------------------------------------
MACRO       : U8_UNLOCK_FILTER_FILL_LOOP
Author      : ybadal
Input       :
Description : Specify the number of fill loop to warm up the filter for unlock sensor after pon
              SWR-731
------------------------------------------------------------------------*/
#define U8_UNLOCK_FILTER_FILL_LOOP  ((U8)3)
/*------------------------------------------------------------------------
MACRO       : U8_LOCK_FILTER_INIT_RECALL
Author      : ybadal
Input       :
Description : Specify the number of consecutive filter call during init time for lock sensor
              SWR-730
------------------------------------------------------------------------*/
#define U8_LOCK_FILTER_INIT_RECALL    ((U8)4)
/*------------------------------------------------------------------------
MACRO       : U8_UNLOCK_FILTER_INIT_RECALL
Author      : ybadal
Input       :
Description :  Specify the number of consecutive filter call during init time for unlock sensor
               SWR-731
------------------------------------------------------------------------*/
#define U8_UNLOCK_FILTER_INIT_RECALL  ((U8)4)

/*------------------------------------------------------------------------
MACRO       : U16_SAMPLEA_INIT_VALUE
Author      : ybadal
Input       :
Description :  Specify initiale value for sample A 
------------------------------------------------------------------------*/
/* polyspace < MISRA-C3:2.5 : Not a defect > Justify with annotations > should be kept for future usage */
#define  U16_SAMPLEA_INIT_VALUE                  ((U16)647)
/*------------------------------------------------------------------------
MACRO       : U16_SAMPLEB_INIT_VALUE
Author      : ybadal
Input       :
Description :  Specify initiale value for sample B  
------------------------------------------------------------------------*/
/* polyspace < MISRA-C3:2.5 : Not a defect > Justify with annotations > should be kept for future usage */
#define  U16_SAMPLEB_INIT_VALUE                  ((U16)376)

/* noise detector */
/*------------------------------------------------------------------------
Function    : sensor_noise_detect
Author      : ybadal
Input       : TASK_SENSOR_VAR_T * Sensor_Var : pointer to the main sensor structure
              U16 U16_filter_input : filter input to must  be filtered
Description : noise detector
------------------------------------------------------------------------*/
STATIC void sensor_noise_detect(TASK_SENSOR_VAR_T * Sensor_Var,U16 U16_filter_input);
/*------------------------------------------------------------------------
Function    : sensor_filter_unit
Author      : ybadal
Input       : READONLY SENSOR_MEASURE_VALUE_T * sensor_raw_buffer : pointer to the sensor raw values buffer
              TASK_SENSOR_VAR_T * Sensor_Var : pointer to the main sensor structur
Description : process for all sensor signal analyse (preselector ,filter)  
------------------------------------------------------------------------*/
STATIC void sensor_filter_unit(READONLY SENSOR_MEASURE_VALUE_T * sensor_raw_buffer,TASK_SENSOR_VAR_T * Sensor_Var);
STATIC void sensor_filter_unit_LP(READONLY SENSOR_MEASURE_VALUE_T * sensor_raw_buffer,TASK_SENSOR_VAR_T * Sensor_Var);
/*------------------------------------------------------------------------
Function       : sensor_unlock_iir_filter
Author      : ybadal
Input       : TASK_SENSOR_VAR_T * Sensor_Var : pointer to the main sensor structur
              U16 U16_filter_input :  filter input to must  be filtered
Description : three cascaded FIR Filter for unlock sensor, every FIR output is used as input for the next 
              FIR filter, the equations of the filter are followed:  
------------------------------------------------------------------------*/
STATIC void sensor_unlock_iir_filter (TASK_SENSOR_VAR_T * Sensor_Var,U16 U16_filter_input);
/*------------------------------------------------------------------------
Function       : sensor_lock_iir_filter
Author      : ybadal
Input       :
Description : two cascaded IIR Filter 1er Order for lock sensor, the first IIR output divided with 2  is used as input for the next 
              IIR filter, the equations of the filter are followed  
------------------------------------------------------------------------*/
STATIC void sensor_lock_iir_filter (TASK_SENSOR_VAR_T * Sensor_Var,U16 U16_filter_input);
/******************************************************************************/
/* polyspace:begin<MISRA-C3:8.6,8.7 : Not a defect : Justify with annotations > the stuctur ST_algo_param_var is need for mex process, for this reason it is global defined */

/*stores general informations about each of the active sensors:
* sensor id, function pointer to sensor filter, function pointer to sensor aquisition, pon fill loop, pon filter recall  */
STATIC READONLY SENSOR_PARAMETER_T   ST_sensor_unit_par[SENSOR_MAX] = {
                                                                          #ifndef VARIANT_1
                                                                            {SENSOR_LOCK,&sensor_lock_iir_filter,&sensor_noise_detect,&Get_Sensor_Scan_VR,U8_LOCK_FILTER_FILL_LOOP,U8_LOCK_FILTER_INIT_RECALL},
                                                                          #endif
                                                                            {SENSOR_UNLOCK,&sensor_unlock_iir_filter,&sensor_noise_detect,&Get_Sensor_Scan_ER,U8_UNLOCK_FILTER_FILL_LOOP,U8_UNLOCK_FILTER_INIT_RECALL}
                                                                          };
/* polyspace:end<MISRA-C3:8.6 ,8.7 : Not a defect : Justify with annotations > */
#ifdef STANDARD_DEVIATION
/*!
******************************************************************************
* \brief
* sensors_recal_averages
*
* \details
* @ingroup sensor signal analyse
*  function to recalculate the average
******************************************************************************
* \ Author        : ybadal
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started.
*
* \param[in]     void
* \param[out]    U8
*
* \glob_start	 ST_Sensor_Var
                 Sensor_Bits 
                 U16_ER_Sigma_Delta_Win
                 U16_VR_Sigma_Delta_Win
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
* \par Remarks:
* CallFunct:  task_Sensor
*             
*
******************************************************************************/
STATIC  void sensors_recal_average(TASK_SENSOR_VAR_T * Sensor_Var )
{
    Sensor_Var->U24_Filter_Average_summe =  (U8)0;
    Sensor_Var->U16_Filter_Average = Sensor_Var->U16_filter_unit_result;
    Sensor_Var->U8_avg_counter  = (U8)0;
    Sensor_Var->U16_max_standard_deviation = (U8)0;
    
}

#endif

/*!
*******************************************************************************
* \brief
* sensor_sampleB_init
*
* \details
* @ingroup sensor signal analyse
*  sensor sample B  initialisation function after PON reset
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           .
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start	 Sensor_Var[SENSOR_LOCK].sensor_aquisiton_fnc
                 Sensor_Var[SENSOR_UNLOCK].sensor_aquisiton_fnc 
                 ADC, Port C and Port A SFR register
* \glob_end
*
* \retval         void
******************************************************************************
*
* \author        Y.Badal
* \version       1.0
* \date          17.01.2017
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:
*
******************************************************************************/
STATIC inline void sensor_sampleAB_init(void)
{
    U8 sensor_id;

    SuspendAllInterrupts();
    Sensor_Scan_Both();/*call sensor aquisition*/
    ResumeAllInterrupts();
    for( sensor_id = (U8)0 ;sensor_id < (U8)SENSOR_MAX;sensor_id +=(U8)1)
    {
      AU_sensor_raw_buffer[sensor_id] = ST_sensor_unit_par[sensor_id].fnc_get_sensor_aquis(); /*get sensor aquisition result*/
      Sensor_Var_Str[sensor_id].U16_last_sampleA = AU_sensor_raw_buffer[sensor_id]->U16_Sensor_SA_Value; /* initialize th lock Sample (A-1)*/
      Sensor_Var_Str[sensor_id].U16_last_sampleB = AU_sensor_raw_buffer[sensor_id]->U16_Sensor_SB_Value; /* initialize th lock Sample (B-1)*/
    }
    

}
/*!
*******************************************************************************
* \brief
* sensor_init
*
* \details
* @ingroup sensor signal analyse
*  sensor initialisation function after PON reset
*  SWR-612, SWR-642, SWR-900, SWR-901
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           .
* \post          process is started
*
* \param[in]     void
* \param[in]
*
* \glob_start	 ST_Sensor_Var[SENSOR_LOCK].sensor_aquisiton_fnc
                 ST_Sensor_Var[SENSOR_UNLOCK].sensor_aquisiton_fnc 
                 ADC, Port C and Port A SFR register
                 sensor_noise_detect
* \glob_end
*
* \retval         void
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
* \par Remarks:
* CallFunct:
*
******************************************************************************/
REF_SENSOR void sensor_mcvd_init(void)
{
    U8 sensor_id ;

#ifndef MEX

    U8  U8_power_up_loop ;

    for( sensor_id = 0u ;sensor_id < (U8)SENSOR_MAX;sensor_id +=1u)
    {
    
      /*! initialization  of sensor id */
       /* polyspace < MISRA-C3:10.5,10.3 : Not a defect : Justify with annotations >  The value of sensor_id fits an EN_SENSOR_ID type */
      Sensor_Var_Str[sensor_id].en_sensor_id = (EN_SENSOR_ID) sensor_id;
      
      /*explicit initialization of filter memory*/
      Sensor_Var_Str[sensor_id].S32_Filt_FeedbackBuffer[MEMORY_DEPTH_1]=0;
      Sensor_Var_Str[sensor_id].S32_Filt_FeedbackBuffer[MEMORY_DEPTH_2]=0;
      Sensor_Var_Str[sensor_id].S16_NoiseDet_FeedbackBuffer[MEMORY_DEPTH_1]=0;
      Sensor_Var_Str[sensor_id].S16_NoiseDet_FeedbackBuffer[MEMORY_DEPTH_2]=0;

    }

     Sensor_Var_Str[SENSOR_UNLOCK].U16_NoiseThresh = ST_unlock_sensor_NVM_params.U16_P_ER_NOISE_THRESHOLD;
     Sensor_Var_Str[SENSOR_LOCK].U16_NoiseThresh = ST_lock_sensor_NVM_params.U16_P_VR_NOISE_THRESHOLD;

   /*first sensor sample initialisation */
    sensor_sampleAB_init();

    /* initialisation of the filter with constant value for all active sensors*/
    for( sensor_id = (U8)0 ;sensor_id < (U8)SENSOR_MAX;sensor_id +=(U8)1)
    {
        for( U8_power_up_loop = (U8)0;U8_power_up_loop < ST_sensor_unit_par[sensor_id].U8_filter_fill_init;U8_power_up_loop++)
        {
          ST_sensor_unit_par[sensor_id].fnc_filter(&Sensor_Var_Str[sensor_id],U16_IIR_WARME_UP_CONSTANT);/*call the filter function for each sensor*/
          (void)ST_sensor_unit_par[sensor_id].fnc_noiseDet(&Sensor_Var_Str[sensor_id],U16_IIR_WARME_UP_CONSTANT_NOISE);/*call the noise detect function for each sensor*/
        }
    }
    
    
#endif
#ifdef STANDARD_DEVIATION
    for( sensor_id = (U8)0 ;sensor_id < (U8)SENSOR_MAX;sensor_id +=(U8)1)
    {
        sensors_recal_average(&Sensor_Var_Str[sensor_id]);
    }
#endif   
}
#ifdef STANDARD_DEVIATION

/*!
******************************************************************************
* \brief
* sensors_average
*
* \details
* @ingroup sensor signal analyse
* the mean of the accumulated sensor value  along the time U8_AVERAGE_WINDOW
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started.
*
* \param[in]     void
* \param[out]    U8
*
* \glob_start	 ST_Sensor_Var                 
* \glob_end
*
* \retval         
******************************************************************************
*
* \author        Y.Badal
* \version       1.0
* \date          15.06.2016
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:  task_Sensor
*             
*
******************************************************************************/
STATIC  void sensors_average(TASK_SENSOR_VAR_T * Sensor_Var )
{        
#define U8_DEVIATION_AVERAGE_FACTOR ((U8)2) /* reduce factor*/
    Sensor_Var->U8_avg_counter++;           /* increment the average window counter */
    if (U8_AVERAGE_WINDOW < Sensor_Var->U8_avg_counter) /* window is reached*/
    {
        if (FALSE == Sensor_Var->BO_sensor_algo_active) /* check is algo is active , no new standard devation is added the threshold*/
        {
            if (Sensor_Var->U16_standard_deviation < Sensor_Var->U16_max_standard_deviation) /* check if the new calculated deviation is grether then the current deviation*/
            {
                Sensor_Var->U16_standard_deviation = Sensor_Var->U16_max_standard_deviation; /*the new calculated deviation is  the current deviation*/
            }
            else
            {
                U16 temp = Sensor_Var->U16_standard_deviation / U8_DEVIATION_AVERAGE_FACTOR;      /* we get just the half  of the current deviation*/
                U16 temp2 = Sensor_Var->U16_max_standard_deviation / U8_DEVIATION_AVERAGE_FACTOR; /* we get just the half  of the new deviation*/

                Sensor_Var->U16_standard_deviation = temp + temp2; /* get the current deviation */
            }
        }
        else
        {
            /*do nothing*/
        }
        Sensor_Var->U16_max_standard_deviation = (U8)0;                                            /* reset the new deviation for the next calculation*/
        Sensor_Var->U8_avg_counter = (U8)1;                                                        /*reset the average counter */
        Sensor_Var->U16_Filter_Average = Sensor_Var->U24_Filter_Average_summe / U8_AVERAGE_WINDOW; /* calculate the average*/
        Sensor_Var->U24_Filter_Average_summe = (U24)(U8)0;                                         /* reset the average accumulator*/
    }
    else
    {
        /*do nothing*/
    }
    Sensor_Var->U24_Filter_Average_summe += Sensor_Var->U16_filter_unit_result; /* update the average acuumulator with the current sensor value*/
                   
}

/*!
******************************************************************************
* \brief
* sensors_standard_abweichung
*
* \details
* @ingroup sensor signal analyse
*  calculate a standard deviation from average.
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started.
*
* \param[in]     void
* \param[out]    void
*
* \glob_start	 TASK_SENSOR_VAR_T * Sensor_Var
* \glob_end
*
* \retval         void
******************************************************************************
*
* \author        Y.Badal
* \version       1.0
* \date          15.06.2017
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:  task_Sensor
*             
*
******************************************************************************/
STATIC  void sensors_standard_abweichung(TASK_SENSOR_VAR_T * Sensor_Var)
{
  
    U16 Temp = (U8)0;
    
    
    Temp =   sensor_absolut_calculation(Sensor_Var->U16_filter_unit_result - Sensor_Var->U16_Filter_Average) ;      /*get the deviation from average*/
    
    if(Sensor_Var->U16_max_standard_deviation == 0 ) /* check for the beginning of the calculation*/
    {
       Sensor_Var->U16_max_standard_deviation  =  Temp; /*restart the */
    }
    else if (Sensor_Var->U16_max_standard_deviation < Temp)
    {
        Sensor_Var->U16_max_standard_deviation = Temp;
    }
    else
    {
        /*do nothing*/
    }
}
/*!
******************************************************************************
* \brief
* sensor_standard_deviation_OnHandling
*
* \details
* @ingroup sub function to manage the average ,standard deviation calculation: after
 *         sensor activation a debounce time is started, when the time is expired the average will recalculated based on the 
 *         current sensor value. 
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started.
*
* \param[in]     TASK_SENSOR_VAR_T * ST_Sensor_Var : sensor main structur
* \param[out]    void
*
* \glob_start	 ST_Sensor_Var
                 
* \glob_end
*
* \retval         void
******************************************************************************
*
* \author        Y.Badal
* \version       1.0
* \date          22.06.2016
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
 * 
******************************************************************************/
STATIC void sensor_standard_deviation_OnHandling(TASK_SENSOR_VAR_T * Sensor_Var)
{
    if (FALSE == Sensor_Var->BO_sensor_algo_active) /*check if sensor algo is active*/
    {
        if (Sensor_Var->U8_avg_recal_time == (U8)0)  /*check if sensor recal time  is running out */
        {
          sensors_standard_abweichung(Sensor_Var); /*calculate a standard deviation from average*/
          sensors_average(Sensor_Var); /*calculate a  average*/
        }
        else
        {
          Sensor_Var->U8_avg_recal_time--; /*decrement a recal time after sensor activation */
          if (Sensor_Var->U8_avg_recal_time == (U8)0) /*check if sensor recal time  is running out */
          {
              sensors_recal_average(Sensor_Var); /* make a recalibration of the average and */
          }
          else
          {
              /*do nothing*/
          }
        }
    }
    else
    {
        Sensor_Var->U8_avg_recal_time = U8_RECAL_AVG_DELAY;
    }
}
#endif


#ifdef DISTURBANCE_ACTIVE
/*!
******************************************************************************
* \brief
* sensor_disturbance_detection
*
* \details
* @ingroup sensor signal analyse
*  if the sensor raw values summe is  outside a defined boundary the threshold
*  will be adapted with 
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started.
*
* \param[in]     void
* \param[out]    U8
*
* \glob_start	 ST_Sensor_Var
                 Sensor_Bits 
                 U16_ER_Sigma_Delta_Win
                 U16_VR_Sigma_Delta_Win
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
* \par Remarks:
* CallFunct:  task_Sensor
*             
*
******************************************************************************/
STATIC void sensor_disturbance_detection(READONLY SENSOR_MEASURE_VALUE_T * sensor_raw_buffer,TASK_SENSOR_VAR_T * Sensor_Var,READONLY SENSOR_PARAMETER_T *Sensor_Par)
{
    U16 Summe = sensor_raw_buffer[0].U16_Sensor_SA_Value +  sensor_raw_buffer[0].U16_Sensor_SB_Value;  /*get sample A */

    if ((Summe < Sensor_Par->U16_disturbance_down_bound) ||
        (Summe > Sensor_Par->U16_disturbance_up_bound))
    {
        Sensor_Var->U8_disturbance_delay = 20;
    }
    else
    {
        /*do nothing*/
    }
    /*plausibiltycheck stop the filter process, but when the algo is active the filter will resume.*/
    if (Sensor_Var->U8_disturbance_delay > (U8)0)
    {
        Sensor_Var->U8_disturbance_delay--;
    }
    else
    {
        /*do nothing*/
    }
}
#endif
/*!
******************************************************************************
* \brief
* sensor_perform_OnInit
*
* \details
* @ingroup sensor signal analyse
*  sensor main handling interface to the application,process the both sensor by aquisition,filtering and error analyse
*  this function shall be call at firt on pon to calibrate the filter with real values
*  SWR-730, SWR-731
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started.
*
* \param[in]     void
* \param[out]    void
*
* \glob_start	 ST_Sensor_Var
                 Sensor_Bits 
* \glob_end
*
* \retval         
******************************************************************************
*
* \author        Y.Badal
* \version       1.0
* \date          14.09.2017
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:  task_Sensor
*             
*
******************************************************************************/
REF_SENSOR void sensor_perform_OnInit(void)
{
U8 U8_power_up_loop = (U8)0;    
U8 sensor_id;

    SuspendAllInterrupts();
    Sensor_Scan_Both();/*call sensor aquisition*/
    ResumeAllInterrupts();

    for( sensor_id = (U8)0 ;sensor_id < (U8)SENSOR_MAX;sensor_id +=(U8)1)
    {
        AU_sensor_raw_buffer[sensor_id] = ST_sensor_unit_par[sensor_id].fnc_get_sensor_aquis(); /*get sensor aquisition result*/
    }

    /* perform OnInit for unlock sensor - 3x measured value */
    sensor_filter_unit(AU_sensor_raw_buffer[SENSOR_UNLOCK],&Sensor_Var_Str[SENSOR_UNLOCK]);/* call consecutive filter unit*/
    (void)ST_sensor_unit_par[SENSOR_UNLOCK].fnc_noiseDet(&Sensor_Var_Str[SENSOR_UNLOCK],AU_sensor_raw_buffer[SENSOR_UNLOCK]->U16_Sensor_SB_Value);/*call the noise detect function for each sensor*/

   /* perform OnInit for lock sensor - 3x measured value * 4 times per measured value */
    for( U8_power_up_loop = (U8)0;((U8_power_up_loop < ST_sensor_unit_par[SENSOR_LOCK].U8_filter_init_recall)&&((BOOL)FALSE == BO_LF_Signal_detected));U8_power_up_loop++)
    {
        sensor_filter_unit(AU_sensor_raw_buffer[SENSOR_LOCK],&Sensor_Var_Str[SENSOR_LOCK]);/* call consecutive filter unit*/
        (void)ST_sensor_unit_par[SENSOR_LOCK].fnc_noiseDet(&Sensor_Var_Str[SENSOR_LOCK],AU_sensor_raw_buffer[SENSOR_LOCK]->U16_Sensor_SB_Value);/*call the noise detect function for each sensor*/
    }
}
#if 0
/*!
******************************************************************************
* \brief
* sensor_update_activation_state
*
* \details
* @ingroup sensor signal analyse
* update the sensor activation state depend on result from upper application layer.
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started.
*
* \param[in]     void
* \param[out]    void
*
* \glob_start	 ST_Sensor_Var
                 Sensor_Bits
* \glob_end
*
* \retval
******************************************************************************
*
* \author        Y.Badal
* \version       1.0
* \date          14.09.2017
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks:
* CallFunct:  task_Sensor
*
*
******************************************************************************/
STATIC void sensor_update_activation_state(void)
{
	    if (FALSE == EcuM_unlock_sensor_blocking())  /* in deep sleep mode lock sensor is disabled */
		{
			Sensor_Var_Str[SENSOR_UNLOCK].BO_sensor_active = TRUE;
		}
		else
		{
			Sensor_Var_Str[SENSOR_UNLOCK].BO_sensor_active = FALSE;
		}
		if (FALSE == EcuM_lock_sensor_blocking())  /* check if sen */
		{
			Sensor_Var_Str[SENSOR_LOCK].BO_sensor_active = TRUE;
		}
		else
		{
			Sensor_Var_Str[SENSOR_LOCK].BO_sensor_active = FALSE;
		}
}
#endif
/*!
******************************************************************************
* \brief
* sensor_perform_acquisition_filter
*
* \details
* @ingroup sensor signal analyse
*  sensor main handling interface to the application,process the both sensor by aquisition,filtering and error analyse
*  this funtkion must be call in active  and sleep mode    
*  SWR-613, SWR-643, SWR-615, SWR-646
******************************************************************************
* \ Author        : ybadal
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started.
*
* \param[in]     void
* \param[out]    U8
*
* \glob_start	 ST_Sensor_Var
                 Sensor_Bits 
                 U16_ER_Sigma_Delta_Win
                 U16_VR_Sigma_Delta_Win
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
* \par Remarks:
* CallFunct:  task_Sensor
*             
*
******************************************************************************/
REF_SENSOR void sensor_perform_acquisition_filter(EN_SENSOR_MODE mode)
{
U8 sensor_id;

#if 0
	sensor_update_activation_state();
  #endif

    
    for( sensor_id = (U8)0 ;((sensor_id < (U8)SENSOR_MAX) && ((BOOL)FALSE == BO_LF_Signal_detected ));sensor_id +=(U8)1)
    {
      #if 0
    	if(FALSE != Sensor_Var_Str[sensor_id].BO_sensor_active)
    	{
       #endif

			AU_sensor_raw_buffer[sensor_id] = ST_sensor_unit_par[sensor_id].fnc_get_sensor_aquis(); /*get sensor aquisition result*/
            if (EN_LOWPOWER_SENSOR_MODE == mode)
            {
                /* If we are in Low power mode call filter unit twice. */
                sensor_filter_unit_LP(AU_sensor_raw_buffer[sensor_id],&Sensor_Var_Str[sensor_id]);/* call  filter unit*/
            } else{
                sensor_filter_unit(AU_sensor_raw_buffer[sensor_id],&Sensor_Var_Str[sensor_id]);/* call  filter unit*/
            }
			ST_sensor_unit_par[sensor_id].fnc_noiseDet(&Sensor_Var_Str[sensor_id],AU_sensor_raw_buffer[sensor_id]->U16_Sensor_SB_Value);/*call the noise detect function for each sensor*/

			U16_ER_MeasValue = Sensor_Var_Str[SENSOR_UNLOCK].U16_filter_unit_result;/*calculate a new average that will be the result to the sigma delta and algo*/
            U16_VR_MeasValue = Sensor_Var_Str[SENSOR_LOCK].U16_filter_unit_result;/*calculate a new average that will be the result to the sigma delta and algo*/
            /* polyspace+2 MISRA-C3:10.5 [Justified:Low] "Cast from bool to u8 is needed in this case" */
            Sensor_Bits.ER_Noiseflag_u1 = (U8)Sensor_Var_Str[SENSOR_UNLOCK].BO_noise_detected;
            Sensor_Bits.VR_Noiseflag_u1 = (U8)Sensor_Var_Str[SENSOR_LOCK].BO_noise_detected;

			#ifdef DISTURBANCE_ACTIVE
				 sensor_disturbance_detection(&AU_sensor_raw_buffer[SENSOR_UNLOCK],&Sensor_Var_Str[SENSOR_UNLOCK],&ST_sensor_unit_par[SENSOR_UNLOCK]);
			#endif
    	//}
    }
       #ifdef RAIN_MODE_DETECTION
             Sensor_Bits._Bit.ER_Noiseflag_u1      = Sensor_Var_Str[SENSOR_UNLOCK].BO_rain_Hand_detect;
             #ifndef VARIANT_1
             Sensor_Bits._Bit.VR_Noiseflag_u1      = Sensor_Var_Str[SENSOR_LOCK].BO_rain_Hand_detect;
             #endif
        #endif
     
#ifdef MCVD_NOISE_DEBUG
    #ifndef VARIANT_1
    Com_SendSignal(E_HUF_DEBUG_DATA_4_1_LIN, &Sensor_Var_Str[SENSOR_LOCK].HP_Out);
    #endif
    Com_SendSignal(E_HUF_DEBUG_DATA_4_2_LIN, &Sensor_Var_Str[SENSOR_UNLOCK].HP_Out);
#endif

}

/*!
******************************************************************************
* \brief
* sensor_filter_unit
*
* \details
* process for all sensor signal analyse (preselector ,filter)
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started.
*
* \param[in]     SENSOR_MEASURE_VALUE_T * sensor_raw_buffer : pointer to the sensor raw values buffer.
                 TASK_SENSOR_VAR_T * ST_Sensor_Var : sensor main structur
 * 
* \param[out]    void
*
* \glob_start	 ST_Sensor_Var
                 
* \glob_end
*
* \retval        
******************************************************************************
*
* \author        Y.Badal
* \version       1.0
* \date          15.09.2016
*
******************************************************************************
*
* \par Change history:
*       -
*
******************************************************************************
*
* \par Remarks: 
******************************************************************************/
STATIC void sensor_filter_unit(READONLY SENSOR_MEASURE_VALUE_T * sensor_raw_buffer,TASK_SENSOR_VAR_T * Sensor_Var)
{
    U16 U16_dc_filter_input;
    U16 Temp_SampleA;
    U16 Temp_SampleB;
 
    /*preselector*/   
    Temp_SampleA = sensor_raw_buffer[0].U16_Sensor_SA_Value;                    /*get current sample A */
    Temp_SampleB = sensor_raw_buffer[0].U16_Sensor_SB_Value;            /*get current sample B */

    Temp_SampleA += ST_unlock_sensor_NVM_params.U16_P_CARRIER_VALUE;
   
    Sensor_Var->U16_last_sampleA = sensor_raw_buffer[0].U16_Sensor_SA_Value;    /* save current values for next cycle */ 
    Sensor_Var->U16_last_sampleB = sensor_raw_buffer[0].U16_Sensor_SB_Value;   
    
    if(Temp_SampleA >= Temp_SampleB)
    {
        U16_dc_filter_input = Temp_SampleA - Temp_SampleB;   /*! calculate DC value*/
    }
    else
    {
    	U16_dc_filter_input = Temp_SampleB - Temp_SampleA;
    }

  
    if(SENSOR_UNLOCK == Sensor_Var->en_sensor_id)
    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    {
        U16_ER_filter_dfc = U16_dc_filter_input;
    }
    else
    {
        U16_VR_filter_dfc = U16_dc_filter_input;
    }
    /* polyspace < RTE:OBAI : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
    /* polyspace < MISRA-C3:D4.1,18.1 : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
    ST_sensor_unit_par[Sensor_Var->en_sensor_id].fnc_filter(Sensor_Var, U16_dc_filter_input ); /* call  filter function for each sensor  */  

#ifdef STANDARD_DEVIATION
  /*handle sensor standard deviation */
    sensor_standard_deviation_OnHandling(Sensor_Var);    
#endif
#ifdef RAIN_MODE_DETECTION
    sensor_rain_algo_drop_detector(Sensor_Var);
#endif

}

STATIC void sensor_filter_unit_LP(READONLY SENSOR_MEASURE_VALUE_T * sensor_raw_buffer,TASK_SENSOR_VAR_T * Sensor_Var)
{
    U16 U16_dc_filter_input;
    U16 Temp_SampleA;
    U16 Temp_SampleB;
 
    /*preselector*/   
    Temp_SampleA = sensor_raw_buffer[0].U16_Sensor_SA_Value;                    /*get current sample A */
    Temp_SampleB = sensor_raw_buffer[0].U16_Sensor_SB_Value;            /*get current sample B */

    Temp_SampleA += ST_unlock_sensor_NVM_params.U16_P_CARRIER_VALUE;
   
    Sensor_Var->U16_last_sampleA = sensor_raw_buffer[0].U16_Sensor_SA_Value;    /* save current values for next cycle */ 
    Sensor_Var->U16_last_sampleB = sensor_raw_buffer[0].U16_Sensor_SB_Value;   
    
    if(Temp_SampleA >= Temp_SampleB)
    {
        U16_dc_filter_input = Temp_SampleA - Temp_SampleB;   /*! calculate DC value*/
    }
    else
    {
    	U16_dc_filter_input = Temp_SampleB - Temp_SampleA;
    }

  
    if(SENSOR_UNLOCK == Sensor_Var->en_sensor_id)
    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    {
        U16_ER_filter_dfc = U16_dc_filter_input;
    }
    else
    {
        U16_VR_filter_dfc = U16_dc_filter_input;
    }
    /* polyspace < RTE:OBAI : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
    /* polyspace < MISRA-C3:D4.1,18.1 : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
    ST_sensor_unit_par[Sensor_Var->en_sensor_id].fnc_filter(Sensor_Var, U16_dc_filter_input ); /* call  filter function for each sensor  */  
    ST_sensor_unit_par[Sensor_Var->en_sensor_id].fnc_filter(Sensor_Var, U16_dc_filter_input ); /* call  filter function for each sensor  */

#ifdef STANDARD_DEVIATION
  /*handle sensor standard deviation */
    sensor_standard_deviation_OnHandling(Sensor_Var);    
#endif
#ifdef RAIN_MODE_DETECTION
    sensor_rain_algo_drop_detector(Sensor_Var);
#endif

}
/*!
 ******************************************************************************
 * \brief
 * Implements a second order IIR filter in transposed direct form 2
 *
 * \details
 * Implements a second order IIR filter in transposed direct form 2 with the factors:
 * b0 = 1
 * b1 = 2
 * b2 = 1
 * -a1=0.625
 * -a2=-0.25
 * resulting in  Gain=6.4
 *
 * Deviation of Memory and Output values from simulation
 * BMW_IIR-TP-2ord-BW_21_04_2020.CIR should not exceed 1%
 *
 ******************************************************************************
 *
 * \par Reentrance:
 *   Not_Reentrant
 * \par ASIL:
 *   QM  - does not realize safety critical features
 *
 * \par Safety Goal:
 *   Unspecified
 *
 * \pre
 *
 *
 * \param Sensor_var: [InOut]   TASK_SENSOR_VAR_T* - Sensors variable structure offering feedback buffers for the filter
 * \param U16_filter_input: [In]    U16 - Last preprocessed measurement value
 *
 * \par Used global variables:
 * \parblock
 * __Read:__
 *
 *
 * __Write:__
 *
 *
 * __Read/Write:__
 *
 * \endparblock
 *
 * \par Called functions:
 *
 *
 * \returns
 *  void :
 *
 ******************************************************************************
 *
 * \par Developer:
 *  omuelle
 * \par Tester:
 *
 *
 ******************************************************************************/
STATIC void sensor_unlock_iir_filter (TASK_SENSOR_VAR_T * Sensor_Var,U16 U16_filter_input)
{  
    S32 S32_FeedbackSum;
    U16 U16_ShiftTemp;
    U32 U32_ShiftTemp;

    S32* PS32_ptr_FeedBack = Sensor_Var->S32_Filt_FeedbackBuffer;/*get feedback buffer pointer*/

    /* polyspace:begin < RTE: OVFL : Not a defect: Justify with annotations > No Error: Filter was simulated to have no intermediate gain above 200 so with inputs of 16Bit there can be no overflow */
    /* polyspace:begin < MISRA-C3:D4.1: Not a defect : Justify with annotations > Filter was simulated to have no intermediate gain above 200 so with inputs of 16Bit there can be no overflow*/
    /* B0 = 1; A0=1*/
    S32_FeedbackSum=(S32)U16_filter_input + PS32_ptr_FeedBack[CASCADE_LEVEL1];
    /* make sure output does not overflow*/
    if(0 > S32_FeedbackSum)
    {
        Sensor_Var->U16_filter_unit_result = 0;
    }
    else if((S32)U16_MAX < S32_FeedbackSum)
    {
        Sensor_Var->U16_filter_unit_result = U16_MAX;
    }
    else
    {
        Sensor_Var->U16_filter_unit_result = (U16)S32_FeedbackSum;
    }

    /* B1 = 2 */
    U32_ShiftTemp = ((U32)U16_filter_input)<<1u;
    PS32_ptr_FeedBack[CASCADE_LEVEL1] = (S32)U32_ShiftTemp;
    /* A1 = 0.625 =  1/2+ 1/8  */
    U16_ShiftTemp = Sensor_Var->U16_filter_unit_result>>1u;
    PS32_ptr_FeedBack[CASCADE_LEVEL1] += (S32)U16_ShiftTemp;
    U16_ShiftTemp >>=2u;
    PS32_ptr_FeedBack[CASCADE_LEVEL1] += (S32)U16_ShiftTemp;
    /* polyspace < MISRA-C3:D4.1 : Not a defect : Justify with annotations > */
    PS32_ptr_FeedBack[CASCADE_LEVEL1] += PS32_ptr_FeedBack[CASCADE_LEVEL2];

    /* B2 = 1  */
    PS32_ptr_FeedBack[CASCADE_LEVEL2] = (S32)U16_filter_input;
    /* A2 = -0.25 = -(1/4)   */
    U16_ShiftTemp = Sensor_Var->U16_filter_unit_result >> 2u;
    PS32_ptr_FeedBack[CASCADE_LEVEL2] -= (S32)U16_ShiftTemp;

    /* polyspace:end < MISRA-C3:D4.1 : Not a defect : Justify with annotations > */
    /* polyspace:end < RTE: OVFL : Not a defect: Justify with annotations >  */

    

}
/*!
 ******************************************************************************
 * \brief
 * Implements a second order IIR filter in transposed direct form 2
 *
 * \details
 * Implements a second order IIR filter in transposed direct form 2 with the factors:
 * b0 = 1
 * b1 = 2
 * b2 = 1
 * -a1=1.625
 * -a2=-0.6875
 * resulting in  Gain=64
 *
 * Deviation of Memory and Output values from simulation
 * BMW_IIR-TP-2ord-BW_21_04_2020.CIR should not exceed 1%
 *
 * the output value will be divided by 8 before returning
 *
 ******************************************************************************
 *
 * \par Reentrance:
 *   Not_Reentrant
 * \par ASIL:
 *   QM  - does not realize safety critical features
 *
 * \par Safety Goal:
 *   Unspecified
 *
 * \pre
 *
 *
 * \param Sensor_var: [InOut]   TASK_SENSOR_VAR_T* - Sensors variable structure offering feedback buffers for the filter
 * \param U16_filter_input: [In]    U16 - Last preprocessed measurement value
 * 
 * \par Used global variables:
 * \parblock
 * __Read:__
 *
 *
 * __Write:__
 *
 *
 * __Read/Write:__
 *
 * \endparblock
 *
 * \par Called functions:
 *
 *
 * \returns
 *  void :
 *
 ******************************************************************************
 *
 * \par Developer:
 *  omuelle
 * \par Tester:
 *
 *
 ******************************************************************************/
STATIC void sensor_lock_iir_filter (TASK_SENSOR_VAR_T * Sensor_Var,U16 U16_filter_input)
{  
    S32 S32_FeedbackSum;
    U32 U32_ShiftTemp;

    S32* PS32_ptr_FeedBack = Sensor_Var->S32_Filt_FeedbackBuffer;/*get feedback buffer pointer*/

    /* polyspace:begin < RTE: OVFL : Not a defect: Justify with annotations > No Error: Filter was simulated to have no intermediate gain above so with inputs of 16Bit there can be no overflow */
    /* polyspace:begin < MISRA-C3:D4.1: Not a defect : Justify with annotations > Filter was simulated to have no intermediate gain above so with inputs of 16Bit there can be no overflow*/
    /* B0 = 1; A0=1*/
    S32_FeedbackSum=(S32)U16_filter_input + PS32_ptr_FeedBack[CASCADE_LEVEL1];
    if(0 > S32_FeedbackSum)
    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    {
        S32_FeedbackSum = 0;
    }
    else
    {
        /* value is ok */
    }
    /* B1 = 2 */
    U32_ShiftTemp = ((U32)U16_filter_input)<<1u;
    PS32_ptr_FeedBack[CASCADE_LEVEL1] = (S32) U32_ShiftTemp;
    /* A1 = 1.625 = 1 + 1/2+ 1/8  */

    PS32_ptr_FeedBack[CASCADE_LEVEL1] += S32_FeedbackSum;
    U32_ShiftTemp = ((U32)S32_FeedbackSum)>>1u;
    PS32_ptr_FeedBack[CASCADE_LEVEL1] += (S32)U32_ShiftTemp;
    U32_ShiftTemp >>=2u;
    PS32_ptr_FeedBack[CASCADE_LEVEL1] += (S32)U32_ShiftTemp;

    PS32_ptr_FeedBack[CASCADE_LEVEL1] += PS32_ptr_FeedBack[CASCADE_LEVEL2];

    /* B2 = 1  */
    PS32_ptr_FeedBack[CASCADE_LEVEL2] = (S32)U16_filter_input;
    /* A2 = -0.6875 = -(1/2 + 1/8 + 1/16)   */
    U32_ShiftTemp = ((U32)S32_FeedbackSum)>>1u;
    PS32_ptr_FeedBack[CASCADE_LEVEL2] -= (S32)U32_ShiftTemp;
    U32_ShiftTemp >>=2u;
    PS32_ptr_FeedBack[CASCADE_LEVEL2] -= (S32)U32_ShiftTemp;
    U32_ShiftTemp >>=1u;
    PS32_ptr_FeedBack[CASCADE_LEVEL2] -= (S32)U32_ShiftTemp;

    /* need to reduce result to prevent overflows*/

    U32_ShiftTemp= ((U32)S32_FeedbackSum)>>3u;

    /* polyspace:end < MISRA-C3:D4.1 : Not a defect : Justify with annotations > */
    /* polyspace:end < RTE: OVFL : Not a defect: Justify with annotations > */

    /* make sure output does not overflow*/
    if((U32)U16_MAX < U32_ShiftTemp) /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    {
        Sensor_Var->U16_filter_unit_result = U16_MAX;
    }
    else
    {
        Sensor_Var->U16_filter_unit_result = (U16)U32_ShiftTemp;
    }
      
}

/*!
 ******************************************************************************
 * \brief
 * Sets the Noise detected flag of Sensor_Var to True if a big change in the signal is detected.
 *
 * \details
 * Sets the Noise detected flag of Sensor_Var to True if a big change in the signal is detected.
 * Input is filtered with a FIR highpass filter which consist of two consecutive differences (=cascaded first order).
 * Noise is then defined as the absolute value of the filter output being above a threshold.
 *
 ******************************************************************************
 *
 * \par Reentrance:
 *   Not_Reentrant
 * \par ASIL:
 *   QM  - Does not realize safety critical features
 *
 * \par Safety Goal:
 *   Unspecified
 *
 * \pre
 *   none
 *
 * \param Sensor_Var: [InOut]   TASK_SENSOR_VAR_T* -
 * \param U16_filter_input: [In]    U16 -
 *
 * \par Used global variables:
 * \parblock
 * __Read:__
 *
 *
 * __Write:__
 *
 *
 * __Read/Write:__
 *
 * \endparblock
 *
 * \par Called functions:
 *
 *
 * \returns
 *  void :
 *
 ******************************************************************************
 *
 * \par Developer:
 *  omuelle
 * \par Tester:
 *
 *
 ******************************************************************************/
/*## operation sensor_noise_detect(TASK_SENSOR_VAR_T,U16) */
STATIC void sensor_noise_detect(TASK_SENSOR_VAR_T * Sensor_Var,U16 U16_filter_input)
{
    S16 S16_Diff1;
    S16 S16_Diff2;
    S16* PS16_ptr_FeedBack = Sensor_Var->S16_NoiseDet_FeedbackBuffer;/*get feedback buffer pointer*/
    /* polyspace:begin < RTE: OVFL : Not a defect: Justify with annotations > No Error: Input is 10Bit ADC value, so two gains of 2 remain in the range of S16 */
    /* polyspace:begin < MISRA-C3:D4.1: Not a defect : Justify with annotations > No Error: Input is 10Bit ADC value, so two gains of 2 remain in the range of S16 */
    /* do serial differences */
    S16_Diff1 = (S16)U16_filter_input - PS16_ptr_FeedBack[MEMORY_DEPTH_1];
    S16_Diff2 = S16_Diff1 - PS16_ptr_FeedBack[MEMORY_DEPTH_2];

    /* forward memory */
    PS16_ptr_FeedBack[MEMORY_DEPTH_2] = S16_Diff1;
    PS16_ptr_FeedBack[MEMORY_DEPTH_1] = (S16)U16_filter_input;

    /* take absolute*/
    if(0 > S16_Diff2) /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    {
        S16_Diff2 = -S16_Diff2;
    }
    else
    {
        /* is already absolute */
    }
#ifdef MCVD_NOISE_DEBUG
    Sensor_Var->HP_Out = S16_Diff2;
#endif
    /* test against threshold */
    if( ((U16)S16_Diff2) > Sensor_Var->U16_NoiseThresh) /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
    {
        Sensor_Var->BO_noise_detected = TRUE;
    }
    else
    {
        Sensor_Var->BO_noise_detected = FALSE;
    }

    /* polyspace:end < MISRA-C3:D4.1 : Not a defect : Justify with annotations > */
    /* polyspace:end < RTE: OVFL : Not a defect: Justify with annotations >  */
}

#endif

/* Automatic logging by PVCS ***********************************************

$Log::   J:/vmfs/VW/1508.008_380_ODH/archives/3_Coding/ECU_NFC_STACK-NXP/MCU_RL78/MOD_SERV_CAPA_SENSOR$
 * 
 *    Rev 1.3   Jun 11 2018 17:08:56   ybadal
 * bug fix for reset rain algo flag
 * 
 *    Rev 1.2   Jun 07 2018 15:59:50   ybadal
 * implement new functions for functionality keep unlock sensor  active by NFC Field.
 * 
 *    Rev 1.1   May 24 2018 17:14:12   ybadal
 * - implement rain algo.
 * - the main sensor structur is defined for cvd and mcvd with the same name.
 * 
 *    Rev 1.0   Sep 22 2017 16:12:04   Sbhanda
 * Initial revision.
 * 
 *    Rev 1.0   Aug 07 2017 12:25:58   ybadal
 * Initial revision.
 * 
 *    Rev 1.25   Jul 06 2017 09:52:18   ybadal
 * - change the parameter filter recall at init from 4 to 6
 * 
 *    Rev 1.24   Jun 19 2017 13:58:08   ybadal
 * - bug fix for sensor id missing initialisation.
 * 
 *    Rev 1.23   Jun 16 2017 12:43:16   ybadal
 * - filter initialization sequence implemented.
 * 
 *    Rev 1.22   Jun 07 2017 17:08:40   ybadal
 * bug fix for por false detection.
 * 
 *    Rev 1.21   Jun 01 2017 18:08:38   ybadal
 * - Bug fix for TT 15025 and 15165
 * 
 *    Rev 1.20   May 19 2017 16:10:54   ybadal
 * - subfunctions ensor_lock_iir_filter  anf sensor_unlock_fir_filter for better his metrics
 * 
 *    Rev 1.19   May 17 2017 12:06:08   ybadal
 * - 3 cascade Levels for FIR filter for unlock sensor.
 * 
 *    Rev 1.18   May 16 2017 14:45:20   ybadal
 * - bug fix when TIMING_IRQ_MODE is defined.
 * - remove used variables in the sensor structure.
 * 
 *    Rev 1.17   May 15 2017 17:40:42   ybadal
 * - new cascaded FIR filter for unlock sensor.
 * 
 *    Rev 1.16   May 12 2017 15:20:50   ybadal
 * -some misra and his topics fixed.
 * 
 *    Rev 1.15   May 02 2017 15:23:56   ybadal
 * - change the parameter U8_PON_FILTER_RESPONCE_LOOP  to 16.
 *  - call Task_plc_handler() before filter process to correct the plc pulse time.
 * 
 *    Rev 1.14   21 Apr 2017 14:17:22   ybadal
 * - for unlock sensor a new 1 order iir low pass filter.
 *  - for lock sensor a new exponential average   iir  filter.
 * 
 *    Rev 1.13   19 Jan 2017 16:25:02   ybadal
 * -  no interrupt disable is allowed due to lf requirement immediatly handling.
 * - some HIS points are fixed.
 * 
 *    Rev 1.12   18 Jan 2017 17:50:10   ybadal
 * - some HIS points has been enhanced.
 * 
 *    Rev 1.11   12 Dec 2016 11:33:24   ybadal
 * - protokoll times has been corrected  by colling the plc_send function in different location in code.
 * 
 *    Rev 1.10   09 Dec 2016 10:23:06   ybadal
 *  - some code change for matlab mex process.
 *  - disturbance detection implemented but is not active( to activate it you shall define "DISTURBANCE_ACTIVE"   in config.h or in makefile) 
 * 
 *    Rev 1.9   24 Nov 2016 17:05:06   ybadal
 *  -  no more disabling timing system interrupt before sensor aquisition due to  change ths timing System from interrupt to  polling mode
 * 
 *    Rev 1.8   17 Nov 2016 16:07:22   ybadal
 * - remove timer 1 from code.
 * 
 *    Rev 1.7   04 Nov 2016 11:35:10   ybadal
 * - new  Paramter calculated from Matlab Simulation.
 * - bug fix for false activation after pon.
 * 
 *    Rev 1.6   26 Sep 2016 16:07:06   rmunizv
 *  - Removed pseudo-dithering (shifting operation) for Unlock Sensor (ECVD Measurement Principle)
 *  - Physical Dithering for Lock Sensor
 * 
 *    Rev 1.4   29 Aug 2016 15:42:48   ybadal
 * - bug fix for diverse misra rules.
 * 
 *    Rev 1.3   23 Aug 2016 17:49:56   ybadal
 * - new coefficient for the iir filter implented.
 * - cariier B is for each sensor adjustable
 * - new parameter structur implemnted  SENSOR_PARAMETER_T   ST_sensor_unit_par
 * 
 *    Rev 1.2   18 Aug 2016 15:44:42   ybadal
 * - new algo implemened according to HIS and Misra rules .
 * - SW architecture improvement.
 * 
 *    Rev 1.1   15 Aug 2016 16:02:00   ybadal
 * - new iir filter implemended.
 * - new filter structure according to the sensor design implemented.
 * 
 *    Rev 1.7   29 Jun 2016 13:32:46   ybadal
 * -  plausibility check window is changed from 30 to 170 for unlock sensor.
 *  -  plausibility check window is changed from 30 to 50 for lock sensor.
 *  -  plausibility check will stop anymore the filter if implausible sensor data is     
 *    detected , but when the algo is active the plausibility check result is ignored and the   
 *    filter shall resume with the new sensor data.(no filter recalibration).
 *  -   debounce time of 10 samples is needed when the plausibility check is not active after activation.
 * 
 *    Rev 1.6   10 Jun 2016 09:55:20   ybadal
 * bugfix for TT 12573 : Absolute variables in RAM cannot be initialized when they are defined. Define the
 * absolute variables, then assign them a value at a suitable point in your main-line code
 * 
 *    Rev 1.5   10 Jun 2016 09:40:04   ybadal
 *  - Bug fix for not stoping filter by LF detection.
 *  - Bug fix for not stoping filter by disturbance .
 * 
 *    Rev 1.28   23 Mar 2016 17:01:00   ybadal
 * - Bug fix for not stoping filter by LF detection.
 * - Bug fix for not stoping filter by disturbance .
 * 
 *    Rev 1.27   18 Mar 2016 10:35:22   ybadal
 * new parameter for rain jump detection.
 * 
 *    Rev 1.26   25 Jan 2016 16:45:54   ybadal
 * DAC for regen test modified.
 * 
 *    Rev 1.25   13 Jan 2016 14:08:32   ybadal
 * - brown out and pon time out reset bit must be set after pon reset occured.
 * - sensor restart time to operation is reduced from 400 ms to 160ms.
 * -rain mode is for yaris not active.
 * - algo threshold for yaris HW modified.
 * 
 *    Rev 1.24   22 Dec 2015 16:39:22   ybadal
 * moduls and functions Headers changed to HUF standard header.
 * 
 *    Rev 1.23   17 Nov 2015 14:42:04   omuelle
 * corrected comments
 * 
 *    Rev 1.22   10 Nov 2015 11:28:34   ybadal
 * rain detection improved.
 * 
 *    Rev 1.21   04 Nov 2015 08:55:56   ybadal
 * general noise detection implemented.
 * 
 *    Rev 1.20   28 Oct 2015 15:11:34   ybadal
 * - Bug fix for ADC On Time.
 * - new disturbance analyse :
 *    - examination of delta A - B
 *    - examination of delta A +B
 *    - examination of A+B 
 * 
 *    Rev 1.19   23 Oct 2015 12:47:12   ybadal
 * Toleranz Fenstern f�r die st�rdetection angepasst.
 * 
 *    Rev 1.18   22 Oct 2015 17:03:18   ybadal
 * due to IIR overflow :
 * - Dittering disabled.
 * - carrier value from 2049 to 1024 changed.
 * - new disturbance detection.
 * - bugfix to compiler warning.
 * - new algo threshold  due to dittering disactivation.
 * 
 *    Rev 1.17   22 Oct 2015 12:19:38   ybadal
 * - SW Umstellung f�r unterschiedlische Daten Ausgabe implementiert.
 * 
 *    Rev 1.16   20 Oct 2015 10:09:44   ybadal
 * - Messung wird unterbrochen wenn LF erkannt ist.
 * 
 *    Rev 1.15   19 Oct 2015 17:00:18   ybadal
 * - Mittelwert loop zusammengefasst.
 * - Mittelwert Variable auf 24 bit reduziert.
 * 
 *    Rev 1.14   19 Oct 2015 16:51:34   ybadal
 * - 8ms in normal Mode.
 * - fenster Mittelwert anstatt gewichter Mittelwert.
 * 
 *    Rev 1.13   19 Oct 2015 09:38:26   ybadal
 * 1) VW Stand 09.09 auf Toyota portiert.
 * 2) ECVD Stand 15.09. realisiert (Dithering -> 11Bit, Carrier -> 2048, Preselector ohne Loop)
 * - DAC Spannung f�r den Comparator auf 500 mV eigestellt
 * - Comparator Output aktiviert.
 * 
 *    Rev 1.12   09 Jul 2015 09:33:08   ybadal
 * - die richtigen Dateien f�r die �nderungen sind jetzt eingecheckt.
 * - neues Komunnikationsmodul implementiert.
 * - bug fix for TT punkte 10331 / 10539 / 10550 / 10552 / 10558 /10551.
 * 
 *    Rev 1.10   30 Apr 2015 15:44:22   ybadal
 * Verzugszeit f�r die Regelung.
 * Neues LF-Erkennung Verfahren basiert auf Messwert Analayse.
 * 
 *    Rev 1.7   19 Feb 2015 13:01:34   ybadal
 * - Rauschanalyse wieder aktiviert.
 * - Ausl�seschwelle wurde von 40 auf 100 angepasst.
 * 
 *    Rev 1.6   18 Feb 2015 17:50:46   ybadal
 * - Rauschanalyse wurde ausgeschaltet.
 * - Sensor Regelung implementiert.
 *
 *    Rev 1.5   Feb 11 2015 16:38:50   jyomkil
 * RA0 wird als Digital IO initialisiert. RA0 wird f�r die Aufladung des internen Kondensator verwendet.
 *
 *    Rev 1.4   11 Feb 2015 13:27:04   ybadal
 * - Data debug Pin (RA0) als Reference spannungspin f�r den internen kondensator.
 * - Rauschflag bei 3  Entprellungen erst aktivierbar.
 * - Bugfix f�r Desaktivierung des Rauschoffsets am Referenzwert.
 *
 *    Rev 1.3   03 Feb 2015 14:22:36   ybadal
 * - Ausl�seschwelle auf 100 gesetzt.
 * - Umladezeit auf 4  gesetzt.
 * - Rauschmodusgrenze ist von 5 auf 10 ge�ndert.
 * - OVS Messwert durch 2 f�r den VR Sensor dividiert.
 * - OVS Messwert durch 4 f�r den ER Sensor dividiert.
 *
 *    Rev 1.2   02 Feb 2015 11:09:30   ybadal
 * - LF Signal Mechanismus implemtiert.
 * - Power Line kommunikation mit dem Sensor Task synchronisiert.
 *
 *    Rev 1.1   11 Dec 2014 09:58:54   ybadal
 * - Toyota Power Kommunikation implementiert.
 * - neues Messwerk auf die neue HW Angepoasst,es wurden    Makros f�r die HW spezifischen Elemente erstellt .
 * -72h Low Power Mode entfernt.
 *
 *
 *
 *    Rev 1.16   24 Sep 2014 10:22:10   apeschl
 * RS232 Datenausgabe: Kompilerschalter Fehler behoben
 *
 *    Rev 1.14   19 Sep 2014 13:15:20   apeschl
 * ER & VR Rauschwert (Addwert) Kalibrierung im laufenden Betrieb hinzu
 *
 *    Rev 1.13   15 Sep 2014 15:28:58   ybadal
 * Rausch Analyse wird nicht bei ausgel�sten Sensor ausgef�hrt.
 *
 *    Rev 1.12   11 Sep 2014 15:03:42   ybadal
 * - Bug zum nicht wieder Verlassen des Rausch Modus behoben.
 * - Wechseln zum  Activ Mode wenn der Sensor anf�ngt zu Rauschen.
 *
 *    Rev 1.11   09 Sep 2014 14:04:54   apeschl
 * Ersetzen bei Interrupt korrigiert
 * Er_noise_counter_lock_u8 & Vr_noise_counter_lock_u8 wird bei RS232_ON global definiert
 *
 *    Rev 1.10   29 Aug 2014 08:51:42   ybadal
 * Bug fixed for TT  8644  und TT 8913
 *
 *    Rev 1.9   19 Aug 2014 15:10:28   apeschl
 * RS232 Ausgabe korrigiert.
 * _ADD_BOUNDARY angepasst
 *
 *    Rev 1.8   17 Jul 2014 10:12:56   ybadal
 * Code Umsetzung zum Review  von 15.07.2014
 *
 *    Rev 1.7   28 May 2014 09:50:34   apeschl
 * Invertierte Datenausgabe f�r EMV Messungen hinzu.
 * Sensormessung und Berechnung zeitoptimiert.
 *
 *    Rev 1.5   22 May 2014 16:41:04   ybadal
 * - Bug Fixed for Team Track Error : TT8640 ,TT8623 und TT8621.
 * -72 Hours Low Power Message implementiert.
 * -Power up Message implementiert.
 *
 *    Rev 1.4   12 May 2014 17:15:30   ybadal
 * -VW Kommunication implementiert.
 * - Bug Fix for TT 8621
 *
 *    Rev 1.3   30 Apr 2014 09:03:10   apeschl
 * task_er/vr & SensorAcq_lock_scan/ER optimiert
 *
 *    Rev 1.2   24 Apr 2014 11:37:06   ybadal
 * ER Sperrung  aufgehoben.
 *
 *    Rev 1.1   23 Apr 2014 12:15:24   apeschl
 * div. Optimierungen
 * Zeiten ER/VR Sensor angepasst
 *
 *    Rev 1.0   28 Mar 2014 14:10:06   ybadal
 * Initial revision.
 *
 *    Rev 1.7   15 Jan 2014 15:32:02   apeschl
 * Oversampling Spike Detection ER hinzu.
 * Grenzwerte f�r Spizenwerte in EEPROM definiert.
 *
 *    Rev 1.6   07 Jan 2014 12:18:28   ybadal
 * - NFC Karten Erkennung wird �ber eine State Machine durchlaufen.
 * - NFC Antennen Rekalibrierung bei gr�ssen Phasen �nderungen  implementiert.
 * - NFC Part mit dem Compiler Switches "NFC_PART_AKTIV" zu aktivieren.
 *
 *    Rev 1.5   13 Dec 2013 13:44:08   apeschl
 * Einige Defines bereinigt, Spike detection VR hinzu, muss aber noch verifiziert werden.
 *
 *    Rev 1.4   13 Dec 2013 12:48:30   ybadal
 * - NFC Phasen Messung korrigiert.
 * -NFC Funktionalit�t wird �ber den Parameter (E_EEP_VR_Par_Mirr_6 == 1 ) aktiviert
 *
 *    Rev 1.3   09 Dec 2013 16:21:06   ybadal
 * NFC Part implementiert.
 *
 *    Rev 1.2   29 Nov 2013 11:14:30   apeschl
 * Inkompatibilit�ten in  Sensor_Abort_IRQ_Handler f�r CVD beseitigt.
 *
 *    Rev 1.1   29 Nov 2013 09:46:48   apeschl
 * Erste Implementierung des CVD Sensorverfahrens. Deaktivierung der Regelung.
 *
 *    Rev 1.0   25 Nov 2013 09:44:10   ufalkne
 * Initial revision.


*********************************************************** end of comment */

