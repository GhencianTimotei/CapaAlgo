/*
 ******************************************************************************
 * \image html "Kopf_oZusatz_A4hoch_4C.jpg"
 *
 * \par Module Owner:
 *   Huf H&uuml;lsbeck & F&uuml;rst GmbH & Co. KG \n
 *   Steeger Str. 17 \n
 *   42551 Velbert \n
 *   Department PDE-S
 *
 ******************************************************************************
 * \par Description:
 *   Generated configuration file for TimeService
 * Implementation based on Huf BSW specifications  \n
 *
 *
 * %PCMS_HEADER_SUBSTITUTION_START:%
 ******************************************************************************
 * Document Management Information Log (generated by Dimensions CM)
 *
 *
 *  CM Item:   %PID:%
 *  Itemname:   %PM:%
 *  Location:  %ARCHIVE:%
 *  Revision:  %PR:%
 *  Date:      %DATE:%
 *  Author:    %AUTHOR:%
 *
 * %PCMS_HEADER_SUBSTITUTION_END:%
 *
 ******************************************************************************/

#ifndef TIME_SERVICE_H_                   /* To avoid double inclusion */
#define TIME_SERVICE_H_

#include "TimeService_Cfg.h"
#include "Os.h"

/* polyspace-begin MISRA-C3:D4.8 [Not a defect:Unset] "No impact on functionality, just code encapsulation related" */
typedef struct
{
   Tm_PredefTimerType Channel;
   Tm_PredefTimerRefTimeType ReferenceTime;
}Tm_PredefTimer1us16bitType;

#if( TM_16BIT_TIMER_ENABLE == STD_ON )
typedef struct
{
   U16 HWRTicks;
   U16 Value;
   U8 TimerState;
}Tm_SoftwareTimer1us16bitType;
#endif /* TM_16BIT_TIMER_ENABLE == STD_ON  */

#if( TM_32BIT_TIMER_ENABLE == STD_ON )
typedef struct
{
   U32 HWRTicks;
   U32 Value;
   U8 TimerState;
}Tm_SoftwareTimer1us32bitType;
#endif /* TM_32BIT_TIMER_ENABLE == STD_ON */

#if( TM_SLOW_TIMER_ENABLE == STD_ON )
typedef struct
{
   U32 Value;
   U8 TimerState;
}Tm_SoftwareTimerSlow1msType;

typedef struct
{
   U32 CurrentTime;
   TickType Os_Tick;
   BOOL Tm_LPM_Entered;
}Tm_1ms_Type;
#endif /* TM_SLOW_TIMER_ENABLE == STD_ON */
/* polyspace-end MISRA-C3:D4.8 [Not a defect:Unset] "No impact on functionality, just code encapsulation related" */

/* define timer states */
#define TM_RUNNING 0u
#define TM_READY   1u
#define TM_STOPPED 2u

/* polyspace-begin MISRA-C3:5.1 [Not a defect:Unset] "Functions are named according to Autosar and Huf Specifications" */
/******************************************************************************
 * \brief
 * Resets a timer instance (user point of view).
 *
 * \details
 * The function resets a timer by saving the current value of the predefined hardware timer.
 *
 ******************************************************************************
 *
 * \sync          Synchronous
 * \reent         Reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[in]              none
 * \param[out]              TimerPtr: [Out] Tm_PredefTimer1us16bitType * - : Pointer to a timer instance defined by the user.
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \retval        Std_ReturnType  - E_OK: The underlying GPT driver service has returned E_OK
 *                                           and no development error has been detected
 *                                - E_NOT_OK: The underlying GPT driver service has returned E_NOT_OK,
 *                                           or a development error has been detected
 *
 ******************************************************************************
 *
 * \author        BSW
 * \version       1.0
 * \date          29.01.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 22.05.2020, BSW:
 *       -
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/* [BSW_SWS_TimeService_005],[BSW_SWS_TimeService_047] */
extern Std_ReturnType Tm_ResetTimer1us16bit(Tm_PredefTimer1us16bitType* TimerPtr );

/******************************************************************************
 * \brief
 * Delivers the time difference (current time - reference time).
 *
 * \details
 * The function reads the current value of the predefined hardware timer an returns the difference between current time and reference time.
 *
 ******************************************************************************
 *
 * \sync          Synchronous
 * \reent         Reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[in]              TimerPtr: [In] Tm_PredefTimer1us16bitType * - : Pointer to a timer instance defined by the user.
 * \param[out]             TimeSpanPtr: [Out]  U16 * - Pointer to time span destination data in RAM.

 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \retval        Std_ReturnType  - E_OK: The underlying GPT driver service has returned E_OK
 *                                           and no development error has been detected
 *                                - E_NOT_OK: The underlying GPT driver service has returned E_NOT_OK,
 *                                           or a development error has been detected
 *
 ******************************************************************************
 *
 * \author        BSW
 * \version       1.0
 * \date          29.01.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 22.05.2020, BSW:
 *       -
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/*[BSW_SWS_TimeService_009],[BSW_SWS_TimeService_048] */
extern Std_ReturnType Tm_GetTimeSpan1us16bit(const Tm_PredefTimer1us16bitType* TimerPtr, U16 *TimeSpanPtr );

/******************************************************************************
 * \brief
 * Shifts the reference time of the timer instance.
 *
 * \details
 * The function adds to the reference time the time span given by the user.
 *
 ******************************************************************************
 *
 * \sync          Synchronous
 * \reent         Reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[in]              TimerPtr: [In] Tm_PredefTimer1us16bitType * - : Pointer to a timer instance defined by the user.
 * \param[in]              TimeValue : [In] U16 - : Time value in �s, the reference time has to be shifted.
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \retval        Std_ReturnType  - E_OK: The underlying GPT driver service has returned E_OK
 *                                           and no development error has been detected
 *                                - E_NOT_OK: The underlying GPT driver service has returned E_NOT_OK,
 *                                           or a development error has been detected
 *
 ******************************************************************************
 *
 * \author        BSW
 * \version       1.0
 * \date          29.01.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 22.05.2020, BSW:
 *       -
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/*[BSW_SWS_TimeService_049] */
extern void Tm_ShiftTimer1us16bit( Tm_PredefTimer1us16bitType* TimerPtr, U16 TimeValue ) ;

/******************************************************************************
 * \brief
 * Synchronizes two timer instances.
 *
 * \details
 * The function copies the reference time from the source timer to the destination timer.
 *
 ******************************************************************************
 *
 * \sync          Synchronous
 * \reent         Reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[in]              TimerSrcPtr: [In] const Tm_PredefTimer1us16bitTyp - : Pointer to the source timer instance defined by the user.
 * \param[out]             TimerDstPtr : [Out] Tm_PredefTimer1us16bitType* - : Pointer to the destination timer instance defined by the user.
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \retval     void
 *
 ******************************************************************************
 *
 * \author        BSW
 * \version       1.0
 * \date          29.01.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 22.05.2020, BSW:
 *       -
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/* [BSW_SWS_TimeService_050] */
extern void Tm_SyncTimer1us16bit( Tm_PredefTimer1us16bitType* TimerDstPtr,const Tm_PredefTimer1us16bitType* TimerSrcPtr ) ;


/******************************************************************************
 * \brief
 * Performs busy waiting by polling with a guaranteed minimum waiting time.
 *
 * \details
 * The function reads the current value of the predefined hardware timer in a loop, waiting for a minimum time to pass.
 *
 ******************************************************************************
 *
 * \sync          Synchronous
 * \reent         Reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[in]              WaitingTimeMin  [In] U8 - : Minimum waiting time in microseconds
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \retval     Std_ReturnType  - E_OK: The underlying GPT driver service has returned E_OK
 *                                           and no development error has been detected
 *                             - E_NOT_OK: The underlying GPT driver service has returned E_NOT_OK,
 *                                           or a development error has been detected
 *
 ******************************************************************************
 *
 * \author        BSW
 * \version       1.0
 * \date          29.01.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 22.05.2020, BSW:
 *       -
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/*[BSW_SWS_TimeService_016],[BSW_SWS_TimeService_017],[BSW_SWS_TimeService_018],[BSW_SWS_TimeService_051] */
extern Std_ReturnType Tm_BusyWait1us16bit( U8 WaitingTimeMin );

#if( TM_16BIT_TIMER_ENABLE == STD_ON )
/******************************************************************************
 * \brief
 * Starts a timer instance with set value
 *
 * \details
 * The function changes the selected timer to TM_RUNNING MODE. Also it sets the minimum time in microseconds that
 * the timer must run before being set to TM_READY.
 *
 ******************************************************************************
 *
 * \sync          Synchronous
 * \reent         Reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[in]              TimerIdx_U8  [In] U8 - : The index of the timer that the user wants to start
 * \param[in]              Value_U16  [In] U16 - : The time in microseconds that the timer must run.
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \retval     Std_ReturnType  - E_OK: The underlying GPT driver service has returned E_OK
 *                                           and no development error has been detected
 *                             - E_NOT_OK: The underlying GPT driver service has returned E_NOT_OK,
 *                                           or a development error has been detected
 *
 ******************************************************************************
 *
 * \author        BSW
 * \version       1.0
 * \date          29.01.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 22.05.2020, BSW:
 *       -
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/*[BSW_SWS_TimeService_023],[BSW_SWS_TimeService_052]*/
extern Std_ReturnType Tm_StartTimer16bit( U8 TimerIdx_U8, U16 Value_U16 );

/******************************************************************************
 * \brief
 * Stops a timer instance.
 *
 * \details
 * The function changes the timer instance status to TM_STOPPED.
 *
 ******************************************************************************
 *
 * \sync          Synchronous
 * \reent         Reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[in]              TimerIdx_U8  [In] U8 - : The index of the timer that the user wants to start
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \retval     Std_ReturnType  - E_OK: No development error has been detected
 *                             - E_NOT_OK: A development error has been detected
 *
 ******************************************************************************
 *
 * \author        BSW
 * \version       1.0
 * \date          29.01.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 22.05.2020, BSW:
 *       -
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/* [BSW_SWS_TimeService_027],[BSW_SWS_TimeService_053]*/
extern Std_ReturnType Tm_StopTimer16bit( U8 TimerIdx_U8 );

/******************************************************************************
 * \brief
 * Gets the status of a timer instance.
 *
 * \details
 * The function returns the timer's status through the TimerStatus_PU8 parameter.
 *
 ******************************************************************************
 *
 * \sync          Synchronous
 * \reent         Reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[in]              TimerIdx_U8  [In] U8 - : The index of the timer that the user wants to check.
 * \param[out]             TimerStatus_PU8  [Out] U8 * - : The status of the timer instance.
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \retval     Std_ReturnType  - E_OK: The underlying GPT driver service has returned E_OK
 *                                           and no development error has been detected
 *                             - E_NOT_OK: The underlying GPT driver service has returned E_NOT_OK,
 *                                           or a development error has been detected
 *
 ******************************************************************************
 *
 * \author        BSW
 * \version       1.0
 * \date          29.01.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 22.05.2020, BSW:
 *       -
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/* [BSW_SWS_TimeService_031],[BSW_SWS_TimeService_054] */
extern Std_ReturnType Tm_GetStatus16bit( U8 TimerIdx_U8 , U8 * TimerStatus_PU8 );

/******************************************************************************
 * \brief
 * Changes the status of a 16bit timer instance in TM_READY .
 *
 * \details
 *
 *
 ******************************************************************************
 *
 * \sync          Synchronous
 * \reent         Reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[in]              TimerIdx_U8  [In] U8 - : The index of the timer that the user wants to set to TM_READY.
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \retval     Std_ReturnType  - E_OK: No development error has been detected
 *                             - E_NOT_OK: A development error has been detected
 *
 ******************************************************************************
 *
 * \author        BSW
 * \version       1.0
 * \date          29.01.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 22.05.2020, BSW:
 *       -
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/*[BSW_SWS_TimeService_035],[BSW_SWS_TimeService_055] */
extern Std_ReturnType Tm_SetReady16bit( U8 TimerIdx_U8 );
#endif /* TM_16BIT_TIMER_ENABLE == STD_ON */

#if( TM_32BIT_TIMER_ENABLE == STD_ON )
/******************************************************************************
 * \brief
 * Starts a timer instance with set value
 *
 * \details
 * The function changes the selected timer to TM_RUNNING MODE. Also it sets the minimum time in microseconds that
 * the timer must run before being set to TM_READY.
 *
 ******************************************************************************
 *
 * \sync          Synchronous
 * \reent         Reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[in]              TimerIdx_U8  [In] U8 - : The index of the timer that the user wants to start
 * \param[in]              Value_U32  [In] U32 - : The time in microseconds that the timer must run.
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \retval     Std_ReturnType  - E_OK: The underlying GPT driver service has returned E_OK
 *                                           and no development error has been detected
 *                             - E_NOT_OK: The underlying GPT driver service has returned E_NOT_OK,
 *                                           or a development error has been detected
 *
 ******************************************************************************
 *
 * \author        BSW
 * \version       1.0
 * \date          29.01.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 22.05.2020, BSW:
 *       -
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/*[BSW_SWS_TimeService_023],[BSW_SWS_TimeService_056]*/
extern Std_ReturnType Tm_StartTimer32bit( U8 TimerIdx_U8, U32 Value_U32 );

/******************************************************************************
 * \brief
 * Stops a timer instance.
 *
 * \details
 * The function changes the timer instance status to TM_STOPPED.
 *
 ******************************************************************************
 *
 * \sync          Synchronous
 * \reent         Reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[in]              TimerIdx_U8  [In] U8 - : The index of the timer that the user wants to start
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \retval     Std_ReturnType  - E_OK: No development error has been detected
 *                             - E_NOT_OK: A development error has been detected
 *
 ******************************************************************************
 *
 * \author        BSW
 * \version       1.0
 * \date          29.01.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 22.05.2020, BSW:
 *       -
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/* [BSW_SWS_TimeService_027],[BSW_SWS_TimeService_057]*/
extern Std_ReturnType Tm_StopTimer32bit( U8 TimerIdx_U8 );

/******************************************************************************
 * \brief
 * Gets the status of a timer instance.
 *
 * \details
 * The function returns the timer's status through the TimerStatus_PU8 parameter.
 *
 ******************************************************************************
 *
 * \sync          Synchronous
 * \reent         Reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[in]              TimerIdx_U8  [In] U8 - : The index of the timer that the user wants to check.
 * \param[out]             TimerStatus_PU8  [Out] U8 * - : The status of the timer instance.
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \retval     Std_ReturnType  - E_OK: The underlying GPT driver service has returned E_OK
 *                                           and no development error has been detected
 *                             - E_NOT_OK: The underlying GPT driver service has returned E_NOT_OK,
 *                                           or a development error has been detected
 *
 ******************************************************************************
 *
 * \author        BSW
 * \version       1.0
 * \date          29.01.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 22.05.2020, BSW:
 *       -
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/* [BSW_SWS_TimeService_031],[BSW_SWS_TimeService_058] */
extern Std_ReturnType Tm_GetStatus32bit( U8 TimerIdx_U8 , U8 * TimerStatus_PU8 );

/******************************************************************************
 * \brief
 * Changes the status of a 32bit timer instance in TM_READY .
 *
 * \details
 *
 *
 ******************************************************************************
 *
 * \sync          Synchronous
 * \reent         Reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[in]              TimerIdx_U8  [In] U8 - : The index of the timer that the user wants to set to TM_READY.
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \retval     Std_ReturnType  - E_OK: No development error has been detected
 *                             - E_NOT_OK: A development error has been detected
 *
 ******************************************************************************
 *
 * \author        BSW
 * \version       1.0
 * \date          29.01.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 22.05.2020, BSW:
 *       -
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/*[BSW_SWS_TimeService_035],[BSW_SWS_TimeService_059] */
extern Std_ReturnType Tm_SetReady32bit( U8 TimerIdx_U8 );
#endif /* TM_32BIT_TIMER_ENABLE == STD_ON */

#if (TM_SLOW_TIMER_ENABLE == STD_ON)
/*!
****************************************************************************
* \brief
* Updates the Tm_1ms_UT counter variable that the slow timers use.
*
* \details
* The function updates the counter which is based on the OS tick;
* also updates the current time passed in ms.
*
****************************************************************************
*
* \par Reentrance:
* Non Reentrant
* \par ASIL:
* QM
* \pre
* Module is initialized
*
* \param[IN] none
* \param[OUT] none
* \param[IN/OUT] none
*
* \par Used global variables:
* \parblock
* __Read:__
*
* __Write:__
*
* __Read/Write:__
* Tm_1ms_UT
*
* \endparblock
*
* \par Called functions:
* GetCounterValue
*
* \returns
* void
*
****************************************************************************
*
* \par Developer:
* PES-SWPS
* \par Tester:
* PES-SWPS
*
****************************************************************************/
extern void  Tm_UpdateTimer1ms(void);
/*!
****************************************************************************
* \brief
* Starts a timer instance with set value.
*
* \details
* The function changes the selected timer to TM_RUNNING MODE. Also it sets the minimum time in milliseconds that
* the timer must run before being set to TM_READY.
*
****************************************************************************
*
* \par Reentrance:
* Reentrant
* \par ASIL:
* QM
* \pre
* Module is initialized
* \param[IN] TimerIdx_U8: The index of the timer that the user wants to start
*            Value_U32: The time in milliseconds that the timer must run.
* \param[OUT] none
* \param[IN/OUT] none
*
* \par Used global variables:
* \parblock
* __Read:__
* Tm_1ms_UT
*
* __Write:__
* Tm_GlobalTimers1ms_AS
*
* __Read/Write:__
*
* \endparblock
*
* \par Called functions:
* Tm_UpdateTimer1ms()
* SuspendAllInterrupts()
* ResumeAllInterrupts()
*
* \returns
* Std_ReturnType - E_OK - no error detected
*                  E_NOT_OK - aborted due to errors
*
****************************************************************************
*
* \par Developer:
* PES-SWPS
* \par Tester:
* PES-SWPS
*
****************************************************************************/
extern Std_ReturnType Tm_StartTimer_SlowTimer( U8 TimerIdx_U8, U32 Value_U32 );
/*!
****************************************************************************
* \brief
* Stops a timer instance.
*
* \details
* The function changes the timer instance status to TM_STOPPED.
*
****************************************************************************
*
* \par Reentrance:
* Reentrant
* \par ASIL:
* QM
* \pre
* Module is initialized
* \param[IN] TimerIdx_U8: The index of the timer that the user wants to stop
* \param[OUT] none
* \param[IN/OUT] none
*
* \par Used global variables:
* \parblock
* __Read:__
*
* __Write:__
* Tm_GlobalTimers1ms_AS
*
* __Read/Write:__
*
* \endparblock
*
* \par Called functions:
* SuspendAllInterrupts()
* ResumeAllInterrupts()
*
* \returns
* Std_ReturnType - E_OK - no error detected
*                  E_NOT_OK - aborted due to errors
*
****************************************************************************
*
* \par Developer:
* PES-SWPS
* \par Tester:
* PES-SWPS
*
****************************************************************************/
extern Std_ReturnType Tm_StopTimer_SlowTimer( U8 TimerIdx_U8 );
/*!
****************************************************************************
* \brief
* Gets the status of a timer instance.
*
* \details
* The function returns the timer's status through the TimerStatus_PU8 parameter.
*
****************************************************************************
*
* \par Reentrance:
* Reentrant
* \par ASIL:
* QM
* \pre
* Module is initialized
* \param[IN] TimerIdx_U8: The index of the timer that the user wants to check
* \param[OUT] none
* \param[IN/OUT] TimerStatus_PU8: The status of the timer instance.
*
* \par Used global variables:
* \parblock
* __Read:__
* Tm_1ms_UT
*
* __Write:__
*
* __Read/Write:__
* Tm_GlobalTimers1ms_AS
*
* \endparblock
*
* \par Called functions:
* Tm_UpdateTimer1ms()
* SuspendAllInterrupts()
* ResumeAllInterrupts()
*
* \returns
* Std_ReturnType - E_OK - no error detected
*                  E_NOT_OK - aborted due to errors
*
****************************************************************************
*
* \par Developer:
* PES-SWPS
* \par Tester:
* PES-SWPS
*
****************************************************************************/
extern Std_ReturnType Tm_GetStatus_SlowTimer( U8 TimerIdx_U8 , U8 * TimerStatus_PU8 );
/*!
****************************************************************************
* \brief
* Changes the status of a slow timer instance in TM_READY.
*
* \details
*
****************************************************************************
*
* \par Reentrance:
* Reentrant
* \par ASIL:
* QM
* \pre
* Module is initialized
* \param[IN] TimerIdx_U8: The index of the timer that the user wants to set to TM_READY.
* \param[OUT] none
* \param[IN/OUT] none
*
* \par Used global variables:
* \parblock
* __Read:__
*
* __Write:__
* Tm_GlobalTimers1ms_AS
*
* __Read/Write:__
*
* \endparblock
*
* \par Called functions:
* SuspendAllInterrupts()
* ResumeAllInterrupts()
*
* \returns
* Std_ReturnType - E_OK - no error detected
*                  E_NOT_OK - aborted due to errors
*
****************************************************************************
*
* \par Developer:
* PES-SWPS
* \par Tester:
* PES-SWPS
*
****************************************************************************/
extern Std_ReturnType Tm_SetReady_SlowTimer( U8 TimerIdx_U8 );
/*!
****************************************************************************
* \brief
* Function used to change the Tm_1ms_UT.Tm_LPM_Entered to TRUE. It needs to be
* called when entering LPM
*
* \details
*
****************************************************************************
*
* \par Reentrance:
* Reentrant
* \par ASIL:
* QM
* \pre
* Module is initialized
* \param[IN] none
* \param[OUT] none
* \param[IN/OUT] none
*
* \par Used global variables:
* \parblock
* __Read:__
*
* __Write:__
* Tm_1ms_UT
*
* __Read/Write:__
*
* \endparblock
*
* \par Called functions:
*
* \returns
* void
*
****************************************************************************
*
* \par Developer:
* PES-SWPS
* \par Tester:
* PES-SWPS
*
****************************************************************************/
extern void Tm_EnterLPM(void);
/*!
****************************************************************************
* \brief
* Function used to change the Tm_1ms_UT.Tm_LPM_Entered to FALSE and sets the last
* tick counter to 0. It needs to be called when exiting LPM
*
* \details
*
****************************************************************************
*
* \par Reentrance:
* Reentrant
* \par ASIL:
* QM
* \pre
* Module is initialized
* \param[IN] none
* \param[OUT] none
* \param[IN/OUT] none
*
* \par Used global variables:
* \parblock
* __Read:__
*
* __Write:__
* Tm_1ms_UT
*
* __Read/Write:__
*
* \endparblock
*
* \par Called functions:
*
* \returns
* void
*
****************************************************************************
*
* \par Developer:
* PES-SWPS
* \par Tester:
* PES-SWPS
*
****************************************************************************/
extern void Tm_ExitLPM(void);
/*!
****************************************************************************
* \brief
* Function used to update the slow timer's time when in LPM. It needs to be called periodically
* in LPM.
*
* \details
*
****************************************************************************
*
* \par Reentrance:
* Reentrant
* \par ASIL:
* QM
* \pre
* Module is initialized
* \param[IN] CountMs_U8 - the number of milliseconds to add to the current time
* \param[OUT] none
* \param[IN/OUT] none
*
* \par Used global variables:
* \parblock
* __Read:__
*
* __Write:__
* Tm_1ms_UT
*
* __Read/Write:__
*
* \endparblock
*
* \par Called functions:
*
* \returns
* void
*
****************************************************************************
*
* \par Developer:
* PES-SWPS
* \par Tester:
* PES-SWPS
*
****************************************************************************/
extern void Tm_UpdateSlowTimer_LPM(U8 CountMs_U8);
#endif /* #if (TM_SLOW_TIMER_ENABLE == STD_ON) */
/******************************************************************************
 * \brief
 * Check the status for each running timer and update the software timer on 32 bit - task should be called periodical
 *
 * \details
 * The function checks the status of the TM_RUNNING timers, both on 16bit and 32bit and updates
 * the software timer on 32 bits - CheckTime(). If a timer is expired, it's status changes in TM_READY.
 *
 ******************************************************************************
 *
 * \sync          Synchronous
 * \reent         Non Reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[in]              void
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \retval     void
 *
 ******************************************************************************
 *
 * \author        BSW
 * \version       1.0
 * \date          29.01.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 22.05.2020, BSW:
 *       -
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/*[BSW_SWS_TimeService_040],[BSW_SWS_TimeService_061]*/
extern void Tm_MainFunction (void );

/******************************************************************************
 * \brief
 * Initialize each timer defined by the user.
 *
 * \details
 * The function sets each timer's status on TM_STOPPED.
 *
 ******************************************************************************
 *
 * \sync          Synchronous
 * \reent         Non Reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[in]              void
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \retval     void
 *
 ******************************************************************************
 *
 * \author        BSW
 * \version       1.0
 * \date          29.01.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 22.05.2020, BSW:
 *       -
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/*[BSW_SWS_TimeService_060]*/
extern void Tm_InitTimers ( void );
/* polyspace-end MISRA-C3:5.1 [Not a defect:Unset] "Functions are named according to Autosar and Huf Specifications" */
/******************************************************************************
 * \brief
 * Return the current value of the software timer on 32 bits
 *
 * \details
 * The function reads the value of the predefined free running timer, checks it�s flag
 *  and calculates the current time of the 32 bits timer.
 *
 ******************************************************************************
 *
 * \sync          Synchronous
 * \reent         Reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]      CurrentSoftwareTime [out] U32* - The current time in microseconds fot the free running
 *                                                    32 bits software timer.
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \retval     Std_ReturnType  - E_OK: The underlying GPT driver service has returned E_OK
 *                                           and no development error has been detected
 *                             - E_NOT_OK: The underlying GPT driver service has returned E_NOT_OK,
 *                                           or a development error has been detected
 *
 ******************************************************************************
 *
 * \author        BSW
 * \version       1.0
 * \date          29.01.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 22.05.2020, BSW:
 *       -
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern Std_ReturnType Tm_GetCurrentSoftwareTimer32bit ( U32* CurrentSoftwareTime );

#endif /* TIME_SERVICE_H_  */

/* %PCMS_HEADER_SUBSTITUTION_START:%
 ******************************************************************************
 * Document Management Information Log (generated by Dimensions CM)
 *
 *  Description:
 *  %PD:%
 *
 *  Used by Baselines:
 *  %PIRB:%
 *
 *  Used by Dimensions CM Projects:
 *  %PIRW:%
 *
 *  Change History:
 *  %PL:%
 *
 * %PCMS_HEADER_SUBSTITUTION_END:%
 */