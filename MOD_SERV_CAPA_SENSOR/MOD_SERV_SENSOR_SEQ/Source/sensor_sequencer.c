/* polyspace MISRA-C3:1.1 [Justified:Unset] "All macro definitions are needed." */
/*!
 * \defgroup <sensor_sequencer.c>
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
 *  sensor application layer ,performs all the sensor function aquisition ,filtering,signal
 *  process and pc debug report
 *
 *
 *
 ******************************************************************************
 *
 *  $Workfile:   sensor_sequencer.c  $
 *  $Revision:   1.21  $
 *  $Date:   Dec 20 2018 09:49:40  $
 *  $Author:   sbhanda  $
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
 ******************************************************************************
*/

#ifndef APPL_SENSOR_C
#define  APPL_SENSOR_C       /* FileName_C */

#ifdef INTEGRATE_FROM_V4
#include "std_inc.h"         /* Standard include files */
#endif
#ifndef INTEGRATE_FROM_V4
#include "Platform_Types.h"
#endif
/* #include "timing.h"        *//*   Timing interface */
#include "Os.h"
#include "sensor_mcvd.h"
#include "sensor_aquisition.h"          /* Sensor module      */
#include "sensor_sequencer.h"
#include "sensor_algo.h"
#include "sensor_diag.h"
#include "Dio.h"
#include "BatterySupervisor.h"
#include "EcuM.h"
#include "config.h"
enum
{
  EN_IDLE                     					   =(U8)0x00u,
  EN_UNLOCK_SENSOR_APPROACH                        =(U8)0x01u,
  EN_UNLOCK_SENSOR_TOUCH                          	 =(U8)0x02u,
  EN_LOCK_SENSOR_APPROACH                       	  	  =(U8)0x04u,
  EN_LOCK_SENSOR_TOUCH                       	  	  =(U8)0x08u,
  EN_UNLOCK_SENSOR_APPROACH_LOCK_TOUCH             =(U8)0x09u,
  EN_UNLOCK_SENSOR_TOUCH_LOCK_TOUCH                  =(U8)0x0Au,
  EN_LOCK_SENSOR_DIAG_REQUEST                        =(U8)0x10u,
  EN_UNLOCK_SENSOR_DIAG_REQUEST                      =(U8)0x30u,

};

static void sequencer_Task_Do_Sensor_On_Active( void );
static void sequencer_Task_Do_Sensor_On_Sleep( EN_SENSOR_MODE mode );
static APPL_SENSOR_STATE_LIST_T  CasAppl_EN_SciState = EN_APPL_SENSOR_PON_STATE;

/*--------------------------------------------------------------------------
Function: sequencer_sensor_init_Task
Owner   : PDES

Input   : void
Output  : void

Local   : -
Global  : -

Description: Initialisiert den CAS Signal Handler nach PON-Reset
---------------------------------------------------------- end of comment */
seq_export void sequencer_sensor_init_Task( void )
{
	 /* Initialization SENSOR functions*/
    /* polyspace < MISRA-C3:2.2 : Not a defect : Justify with annotations > Should be kept for future usage */
	 Sensor_aquisition_init();
    sensor_mcvd_init();
	 algo_init();

	 SET_APPL_SENSOR_STATE(EN_APPL_SENSOR_PON_STATE);

}

/*!
******************************************************************************
* \brief
* sequncer_sensor_handle_task
*
* \details
* @ingroup sensor_sequencer.c
*  State machine of the main task of the sensor system which controls the calling of
*  sensors in the active and sleep  mode. The switch between both modes is also undertaken here.
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[out]    void
*
* \glob_start
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
*
*
******************************************************************************/
seq_export void sequncer_set_sensor_PonState(void)
{
	SET_APPL_SENSOR_STATE(EN_APPL_SENSOR_PON_STATE);

}

/*!
******************************************************************************
* \brief
* sequncer_sensor_active_task
*
* \details
* @ingroup sensor_sequencer.c
*  call sensor main sequencer
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[out]    void
*
* \glob_start
* \glob_end
*
* \retval         void
******************************************************************************
*
* \author        Y.Badal
* \version       1.0
* \date          06.04.2018
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
*
******************************************************************************/
static void sequncer_sensor_active_task( void )
{
    sequencer_Task_Do_Sensor_On_Active(); /*call sensor functions(acquisition, filter, algo)*/
}
/*!
******************************************************************************
* \brief
* sequncer_sensor_handle_task
*
* \details
* @ingroup sensor_sequencer.c
*  State machine of the main task of the sensor system which controls the calling of 
*  sensors in the active and sleep  mode. The switch between both modes is also undertaken here.
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[out]    void
*
* \glob_start
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
* 
*
******************************************************************************/
void sequncer_sensor_handle_task( EN_SENSOR_MODE mode )
{
	static U8 u8ModeChanged = 0;
	/* If the power supply is in correct operating state */
    if(BatSup_isVoltageInNormal() != 0U)
    {
    	if(EN_ACTIVE_SENSOR_MODE == mode)
    	{
            sequncer_sensor_active_task();
    	}
        else
        {
            sequencer_Task_Do_Sensor_On_Sleep(mode);
        }
        u8ModeChanged = 1;
    }
    else
    {
        if((0 == u8ModeChanged) ||
           (1 == u8ModeChanged))
        {
            algo_init();
            u8ModeChanged = 2;
            (void)EcuM_ReleaseRUN(E_ECUM_VR_SENSOR);
            (void)EcuM_ReleaseRUN(E_ECUM_ER_SENSOR);
        }
        else
        {
            /* refuz*/
        }
    }
}


/*!
******************************************************************************
* \brief
* sequencer_Task_Do_Sensor_On_Active
*
* \details
* @ingroup sensor_sequencer.c
*  main task handler :call of all the sensor functions.: this is a under function
*  of appl_sequencer_task_handler for better HIS Rules. 
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[out]    void
*
* \glob_start
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
* 
*
******************************************************************************/
static void sequencer_Task_Do_Sensor_On_Active( void )
{
    /* polyspace < CERT-C:CON43-C : Not a defect : Justify with annotations > No concurrency on this variable */
    static U8 U8_filter_recal_response_time; /* pon recalibration to warm up the filter*/

    /* polyspace < MISRA-C3:14.3 : Not a defect : Justify with annotations > Condition checked by developer*/
    if (PON_CALIBRATION_TIME <= U8_filter_recal_response_time )
    {
        /*call sensor activity(aquisition, filter)*/
        SuspendAllInterrupts();
        Sensor_Scan_Both(); /*call sensor aquisition*/
        ResumeAllInterrupts();
        sensor_perform_acquisition_filter(EN_ACTIVE_SENSOR_MODE);
        algorithmus();


    }
    else
    {
        sensor_perform_OnInit();
        U8_filter_recal_response_time++;
        algo_init();
    }

}

/*!
******************************************************************************
* \brief
* sequencer_Task_Do_Sensor_On_Sleep
*
* \details
* @ingroup sensor_sequencer.c
*  calls of all the sensor functions in sleep  mode: this is a under function
*  of sequncer_sensor_handle_task for better HIS Rules. 
******************************************************************************
*
* \sync          synchronous (function done in one pass)
* \reent         non reentrant
*
* \pre           all must be initialized.
* \post          process is started
*
* \param[in]     void
* \param[out]    void
*
* \glob_start
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
* 
*
******************************************************************************/
static void sequencer_Task_Do_Sensor_On_Sleep( EN_SENSOR_MODE mode )
{
     /*call sensor activity(aquisition, filter)*/
    SuspendAllInterrupts();
    /* polyspace < MISRA-C3:8.3 : Not a defect : Justify with annotations > Function use the same names and type */
    /* polyspace < MISRA-C3:17.3 : Not a defect : Justify with annotations > Function prototype is already declared.*/
    (void)Sensor_Scan_Both_LP(); /*call sensor aquisition*/
    ResumeAllInterrupts();
    sensor_perform_acquisition_filter(mode);

    algorithmus();  
#ifdef RS232_ON
    sensor_diag_data_out_UART();
#endif
}


#endif
/* Automatic logging by PVCS ***********************************************

$Log::   J:/vmfs/VW/1508.008_380_ODH/archives/3_Coding/ECU_NFC_STACK-NXP$
 * 
 *    Rev 1.21   Dec 20 2018 09:49:40   sbhanda
 * CAN set and release channel has been commented out as NMH will wake the Bus up
 * 
 *    Rev 1.20   Nov 30 2018 15:00:42   sbhanda
 * CAN wake up due to kessy added if respective bit has been set in coding parameter
 * 
 *    Rev 1.19   Nov 23 2018 11:57:34   ybadal
 * - add lock sensor approach for can signal.
 * -some HIS metrics improved.
 * 
 *    Rev 1.18   Oct 25 2018 13:11:06   ybadal
 * functional redesign to control  sensor  activity when disabled.
 * 
 *    Rev 1.17   Oct 17 2018 15:11:02   ybadal
 * kessy playprotection flow implemented.
 * 
 *    Rev 1.16   Oct 01 2018 15:28:42   ybadal
 * - new 50 bytes parameter partially implemented.
 * - add playprotection for kessy.
 * 
 *    Rev 1.15   Aug 03 2018 13:34:40   ybadal
 * mask algo result for plc in case of sensor disabled.
 * 
 *    Rev 1.14   Aug 03 2018 12:55:10   ybadal
 * disable PLC by NFC active from upper layer.(TT 19621  fix).
 * 
 *    Rev 1.13   Jul 27 2018 07:20:58   ybadal
 * - get the parameters from Preference manager.
 * 
 *    Rev 1.12   Jun 07 2018 16:01:32   ybadal
 * change raw value output.
 * 
 *    Rev 1.11   Jun 07 2018 14:57:26   ybadal
 * Parameter to switch sensor raw values or sensor filter values output.
 * 
 *    Rev 1.10   May 08 2018 11:03:22   ybadal
 * due to compiler error the function get_sensor_algo_state_result chengeg from returned argument to input argument.
 * 
 *    Rev 1.9   Apr 25 2018 11:36:06   ybadal
 * handle  system wake up from upper layer ECU manager.
 * 
 *    Rev 1.8   18 Apr 2018 12:25:06   sbhanda
 * EcuManager function names changed.
 * 
 *    Rev 1.7   06 Apr 2018 14:07:48   ybadal
 * - bug fix TT 17867
 * - HIS and Misra enhanced.
 * 
 *    Rev 1.6   Feb 16 2018 11:24:42   ybadal
 * -  sensor will be now disabled from the ECUM when Uplc undervoltage detected.
 *  -  stop sending IL Can Frame if service not started.
 * 
 *    Rev 1.5   Feb 01 2018 09:13:22   cpascal
 * Interfaces from Vector CAN stack called instead of the ones from local CAN stack.
 * 
 *    Rev 1.4   22 Jan 2018 15:16:50   ybadal
 * voltage monitoring inhibit when algo is active.
 * 
 *    Rev 1.3   16 Jan 2018 09:36:26   ybadal
 * implement the voltage monitoring for PLC input to control the sensor flow by undervoltage
 * 
 *    Rev 1.2   18 Dec 2017 11:16:30   ybadal
 *  initialize the variable CasAppl_EN_SciState with EN_APPL_SENSOR_PON_STATE
 * 
 *    Rev 1.0   Sep 22 2017 16:12:22   Sbhanda
 * Initial revision.
 * 
 *    Rev 1.3   Aug 07 2017 15:50:50   ybadal
 * - call the new sequence for mcvd or cvd.
 * 
 *    Rev 1.2   Jul 24 2017 15:37:24   ybadal
 * sequencer_Task_Do_Sensor_On_Active for active mode
 * 
 *    Rev 1.1   Jul 24 2017 14:15:02   ybadal
 * sleep mode deactivated.
 * 
 *    Rev 1.0   Apr 13 2017 13:24:48   ufalkne
 * Initial revision.
 * 
 *    Rev 1.29   18 Sep 2015 07:54:34   ybadal
 * New Structure implementiert.(neues messwerk und signal analyse)siehe Prog Info von v04.01
 * 
 *    Rev 1.28   10 Sep 2015 14:14:16   umuelle3
 * Misra Test
 * 
 *    Rev 1.27   10 Sep 2015 13:32:46   umuelle3
 * Misra Test
 * 
 *    Rev 1.26   09 Sep 2015 16:16:34   umuelle3
 * Check JANKINS
 * 
 *    Rev 1.25   09 Sep 2015 10:54:18   umuelle3
 * MISRA changes proposed by Polyspace.
 * 
 *    Rev 1.24   05 Aug 2015 15:26:30   dwippic
 * MISRA changes proposed by Polyspace	
 * 
 *    Rev 1.22   10 Jun 2015 08:51:38   ybadal
 * - Powerup Kalibration wurde ersetzt.
 * - weitere Misra Rules gefixt.
 * 
 * 
 *    Rev 1.21   03 Jun 2015 09:45:02   ybadal
 * GPIO Modul eingefügt.
 * 
 *    Rev 1.20   29 May 2015 09:45:16   ybadal
 * Bug fix for TT10411
 * - Diverse TT Review Punkte abgeschlossen.
 * 
 *    Rev 1.19   22 May 2015 11:08:04   ybadal
 * - Redesign des Mechanismus mit dem Aktive Mode.
 * 
 *    Rev 1.18   20 May 2015 16:27:02   ybadal
 * - Diverse Misra Rules behoben.
 * - Abstraction betwenn  sensor aquisition sensor analyse.
 * 
 *    Rev 1.17   19 May 2015 11:30:58   ybadal
 * Misra Rules "Macro 'XX' does not expand to compliant construct. (required)" fixed
 * 
 *    Rev 1.16   13 May 2015 15:19:44   ybadal
 * Bug fix for TT 10412  ,TT 10402 and TT 10397
 * 
 *    Rev 1.15   12 May 2015 15:49:08   ybadal
 * - Diverse TeamTrack Punkte realisiert.
 * 
 *    Rev 1.13   13 Feb 2015 13:01:20   ybadal
 * - add comments to the sensor_algo module.
 * -bugfix for TT 9361.
 * 
 *    Rev 1.12   Feb 06 2015 15:03:44   mstei
 * Changes for compliance with CSpec-095 Rev. 01 - Guideline for Software Coding.pdf:
 * - curly brackets are separately positioned in the next line after an instruction. The code between two brackets must be indented.
 * 
 *    Rev 1.11   Feb 05 2015 09:53:48   mstei
 * Changes for compliance with "CSpec-095 Rev. 01 - Guideline for Software Coding.pdf" for switch statement.
 * 
 *    Rev 1.10   Feb 04 2015 08:50:02   mstei
 * Naming convention for constants (preprocessor defines) according to CSpec-095 Rev. 01 - Guideline for Software Coding.pdf.
 * 
 *    Rev 1.9   Feb 02 2015 14:59:36   mstei
 * Naming convention for enums according to CSpec-095 Rev. 01 - Guideline for Software Coding.pdf.
 * 
 *    Rev 1.8   Jan 30 2015 16:28:40   mstei
 * Naming convention for preprocessor defines according to CSpec-095 Rev. 01 - Guideline for Software Coding.pdf
 * 
 *    Rev 1.7   Jan 26 2015 10:25:48   mstei
 * Changes for compliance with CSpec95:
 * - changes in header file
 * - naming convention for variables
 * 
 *    Rev 1.6   15 Jul 2014 15:09:16   ybadal
 * - Diverse SW Änderungen unter anderen Review Punkten (siehe Prog_info von SW Version 02.01).
 * 
 *    Rev 1.4   06 Jun 2014 11:29:54   ybadal
 * - powerline Interface message nok -Unlock Release + Hall message bug fixed.
 * -powerline Interface message nok - Unlock Release+lock message bug fixed.
 * - powerline Interface message has now higher priority as Sensor in Timing Schedule.
 * 
 *    Rev 1.3   22 May 2014 16:40:58   ybadal
 * - Bug Fixed for Team Track Error : TT8640 ,TT8623 und TT8621.
 * -72 Hours Low Power Message implementiert.
 * -Power up Message implementiert.
 * 
 *    Rev 1.2   12 May 2014 17:15:28   ybadal
 * -VW Kommunication implementiert.
 * - Bug Fix for TT 8621
*
*
*
*
*
*********************************************************** end of comment */
