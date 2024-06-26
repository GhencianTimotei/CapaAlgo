#ifndef APPL_SENSOR_C
#define  APPL_SENSOR_C       /* FileName_C */

#include "Platform_Types.h"

#include "Os.h"
#include "sensor_mcvd.h"
#include "sensor_aquisition.h"
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


seq_export void sequencer_sensor_init_Task( void )
{
	 Sensor_aquisition_init();
    sensor_mcvd_init();
	 algo_init();

	 SET_APPL_SENSOR_STATE(EN_APPL_SENSOR_PON_STATE);

}


seq_export void sequncer_set_sensor_PonState(void)
{
	SET_APPL_SENSOR_STATE(EN_APPL_SENSOR_PON_STATE);

}


static void sequncer_sensor_active_task( void )
{
    sequencer_Task_Do_Sensor_On_Active(); 
}


void sequncer_sensor_handle_task( EN_SENSOR_MODE mode )
{
	static U8 u8ModeChanged = 0;

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
            
        }
    }
}


static void sequencer_Task_Do_Sensor_On_Active( void )
{
    static U8 U8_filter_recal_response_time; /* pon recalibration to warm up the filter*/

    if (PON_CALIBRATION_TIME <= U8_filter_recal_response_time )
    {

        SuspendAllInterrupts();
        Sensor_Scan_Both(); 
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



static void sequencer_Task_Do_Sensor_On_Sleep( EN_SENSOR_MODE mode )
{
    SuspendAllInterrupts();
    (void)Sensor_Scan_Both_LP(); 
    ResumeAllInterrupts();
    sensor_perform_acquisition_filter(mode);

    algorithmus();  

}


#endif
