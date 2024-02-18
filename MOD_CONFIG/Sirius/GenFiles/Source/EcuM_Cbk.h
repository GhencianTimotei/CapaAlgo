/*
 ******************************************************************************
 * \image html "Kopf_oZusatz_A4hoch_4C.jpg"
 *
 * \par Module Owner:
 *  Huf Huelsbeck & Fuerst GmbH & Co.KG \n
 *  Steeger Str. 17 \n
 *  42551 Velbert \n
 *  Department PDE-S
 *
******************************************************************************
 *  \par Description:
 *  Generated header file for Ecu Manager callback functions
 *  Implementation based on Autosar 4.2 specifications   \n
 *
 * %PCMS_HEADER_SUBSTITUTION_START:%
 ******************************************************************************
 * Document Management Information Log(generated by Dimensions CM)
 *
 *
 *  CM Item:   %PID:%
 *  Itemname:  %PM:%
 *  Location:  %ARCHIVE:%
 *  Revision:  %PR:%
 *  Date:      %DATE:%
 *  Author:    %AUTHOR:%
 *
 * %PCMS_HEADER_SUBSTITUTION_END:%
 *
 ******************************************************************************/
/* [SWS_EcuM_02677] */

#ifndef  ECUM_CBK_H_             /* To avoid double inclusion */
#define  ECUM_CBK_H_

#include "Std_Types.h"

/* [SWS_EcuMf_00049]  */
typedef U32 EcuM_WakeupSourceType;

/* [SWS_EcuM_02810] */
/* [SWS_EcuMf_00046] */
/* holds the post-build configuration parameters for the ECU State Manager Fixed module
 * as well as pointers to all ConfigType structures of modules that are initialized by the ECU State Manager */
/* polyspace +2 MISRA-C3:D4.8 [Justified:Unset] "No impact on functionality, just code encapsulation related." */ 
typedef struct
{
     const U8  *EcuM_UndefinedConfigSettings;
}EcuM_ConfigType;

extern const EcuM_ConfigType EcuM_Config_Set;
/* polyspace-begin MISRA-C3:5.1 [Justified:Unset] "C99 standard is used to compile, Autosar naming convention." */

/*!
 ******************************************************************************
 * \brief
 * This callout is called by the EcuM to poll a wake up source.
 *
 * \details
 * It shall also be called by the ISR of a wake up source to set up the PLL
 * and check other wake up sources that may be connected to the same interrupt.
 *
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      wakeupSource – wakeup source(s) bit field(s) that needs to be checked
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 * This function is not called for this release because polling on wake up sources
 * is not implemented. Wake up sources do not need to call this function when a wake up occurs,
 * it is sufficient to call only EcuM_SetWakeupEvent.
 ******************************************************************************/
extern void EcuM_CheckWakeup(EcuM_WakeupSourceType wakeupSource);

/*!
 ******************************************************************************
 * \brief
 * Callback used to set a wake up event.
 *
 * \details
 * If the wake up event is not a single bit mask, in the valid range and in the
 * selected sleep mode then the wake up event is ignored and ECUM_E_UNKNOWN_WAKEUP_SOURCE
 * error is send to DET.
 * If the wake up event was already set in the actual session it will be ignored.
 * If the wake up event has passed the above filters and it needs validation,
 * the validation timer will be started/prolonged if already started with the validation
 * timeout of the wake up source established into the configuration.
 * If the wake up event does not need validation it will be automatically validated by calling EcuM_ValidateWakeupEvent.
 * Non interruptible function
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]    void
 * \param[in]     sources – wake up source id
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns       void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_SetWakeupEvent(EcuM_WakeupSourceType sources);

/*!
 ******************************************************************************
 * \brief
 * Callback used to validate a wake up event.
 *
 * \details
 * After wake up, the ECU State Manager will stop the process during the
 * WAKEUP VALIDATION state/sequence to wait for validation of the wake up event.
 * This API service is used to indicate to the ECU Manager module that the wake up
 * event indicated in the sources parameter has been validated.
 * If the wake up event is not a single bit mask, in the valid range and the
 * corresponding wake up was not set before then the wake up event is ignored
 * and ECUM_E_UNKNOWN_WAKEUP_SOURCE error is send to DET.
 * If ComM is integrated and validation is successful, ComM will be informed about the
 * wakeup event if the wakeup source was a communication channel
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]    void
 * \param[in]     sources – event that have been validated
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns       void
 *
 ******************************************************************************
 *
 * \author        PES-SWPS
 * \version       1.1
 * \date          12.05.2021
 *
 ******************************************************************************
 *
 * \par Change history:
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_ValidateWakeupEvent(EcuM_WakeupSourceType source);

/*!
 ******************************************************************************
 * \brief
 * This callout shall provide driver initialization and other hardware-related
 * startup activities for loading the post-build configuration data.
 *
 * \details
 * Beware: Here only pre-compile and link-time configurable modules which do not
 * use post-build configuration parameters may be used.
 * Usually this function is used to initialize DET module.
 * This function is active only if ECUM_CALLOUT_DRIVER_INIT_ZERO is set to ECUM_TRUE.
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      void
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_AL_DriverInitZero(void);

/*!
 ******************************************************************************
 * \brief
 * This callout shall provide driver initialization and other hardware-related
 * startup activities in case of a power on reset.
 *
 * \details
 * This function is active only if ECUM_CALLOUT_DRIVER_INIT_ONE is set to ECUM_TRUE.
 * Usually this function is used to initialize MCU, PORT, DEM pre-initialization,
 * GPT, Watchdog Driver (internal watchdogs only, external ones may need SPI),
 * WDG Manager, SchM, BswM, ADC Driver, ICU Driver, PWM Driver, OCU Driver modules and
 * to start DET.
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      ConfigPtr - Pointer to the EcuM post-build configuration which
 *                 contains pointers to all other BSW module post-build configurations.
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_AL_DriverInitOne(const EcuM_ConfigType* ConfigPtr);

/*!
 ******************************************************************************
 * \brief
 * This callout shall provide driver initialization of drivers which need OS
 * and do not need to wait for the NvM_ReadAll job to finish.
 *
 * \details
 * This function is active only if ECUM_CALLOUT_DRIVER_INIT_TWO is set to ECUM_TRUE.
 * Usually this function is used to initialize communication drivers, EEPROM Driver,
 * Flash Driver, NVRAM Manager (initialization and run NvM_ReadAll job).
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      ConfigPtr - Pointer to the EcuM post-build configuration which
 *                 contains pointers to all other BSW module post-build configurations.
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_AL_DriverInitTwo(const EcuM_ConfigType* ConfigPtr);

/*!
 ******************************************************************************
 * \brief
 * This callout shall provide driver initialization of drivers which need OS
 * and need to wait for the NvM_ReadAll job to finish.
 *
 * \details
 * This function is called at startup only if ECUM_CALLOUT_DRIVER_INIT_THREE is set to ECUM_TRUE.
 * Usually this function is used to initialize Comunication Manager, Network Management,
 * DEM full initialization, Huf timing system.
 * This function is called into the Wakeup Two state too.
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      ConfigPtr - Pointer to the EcuM post-build configuration which
 *                 contains pointers to all other BSW module post-build configurations.
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_AL_DriverInitThree(const EcuM_ConfigType* ConfigPtr);

/*!
 ******************************************************************************
 * \brief
 * This callout is called just after the startup when entering to RUN state.
 *
 * \details
 * This callout allows the system designer to notify that RUN state has been reached,
 * so please add the project specific code manually.
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      void
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_OnEnterRun(void);

/*!
 ******************************************************************************
 * \brief
 * This callout is called just before the RUN state is left.
 *
 * \details
 * This callout allows the system designer to notify that RUN state is about to be
 * left, so please add the project specific code manually.
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      void
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_OnExitRun(void);

/*!
 ******************************************************************************
 * \brief
 * This callout is called just before the POST RUN state is left.
 *
 * \details
 * This callout allows the system designer to notify that POST RUN state is about to be
 * left, so please add the project specific code manually.
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      void
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_OnExitPostRun(void);

/*!
 ******************************************************************************
 * \brief
 * This callout is called when entering to PREP SHUTODOWN state
 *
 * \details
 * This callout allows the system designer to notify that PREP SHUTDOWN state is
 * about to be entered, so please add the project specific code manually.
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      void
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_OnPrepShutdown(void);

/*!
 ******************************************************************************
 * \brief
 * This callout is called when entering to GO SLEEP state
 *
 * \details
 * This callout allows the system designer to notify that GO SLEEP state is about
 * to be entered, so please add the project specific code manually.
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      void
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_OnGoSleep(void);

/*!
 ******************************************************************************
 * \brief
 * This callout is called when entering to GO OFF I state
 *
 * \details
 * This callout allows the system designer to notify that GO OFF I state is about
 * to be entered, so please add the project specific code manually.
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      void
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_OnGoOffOne(void);

/*!
 ******************************************************************************
 * \brief
 * This callout is called when entering to GO OFF II state
 *
 * \details
 * This callout allows the system designer to notify that GO OFF II state is about
 * to be entered, so please add the project specific code manually.
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      void
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_OnGoOffTwo(void);

/*!
 ******************************************************************************
 * \brief
 * This callout is called into GO SLEEP state for enabling the wake up sources
 *
 * \details
 * The ECU Manager Module calls EcuM_EnableWakeupSource to allow the system designer
 * to notify wake up sources defined in the wakeupSource bit field that SLEEP will
 * be entered and to adjust their source accordingly, so please add the project specific
 * code manually. EcuM enables only wakeup sources that are active in actual target sleep
 * mode provided by EcuM_S_SleepModeSet.
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      wakeupSource – wakeup source(s) bit field(s) that will be enabled
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_EnableWakeupSources(EcuM_WakeupSourceType wakeupSource);

/*!
 ******************************************************************************
 * \brief
 * This callout shall switch off the ECU
 *
 * \details
 * This callout shall contain the code for shutting off the power supply of the ECU.
 * If the ECU cannot unpower itself, a reset may be an adequate reaction.
 * Please make sure that this function never returns.

 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      void
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_AL_SwitchOff(void);

/*!
 ******************************************************************************
 * \brief
 * This callout is called to disable the wake up sources
 *
 * \details
 * The ECU Manager Module calls EcuM_DisableWakeupSource to set the wake up source(s)
 * defined in the parameter bit field so that they are not able to wake up the Ecu.
 * The function is called into the Wakeup One state and are disabled only wake up sources
 * that waked up the Ecu and the others are left armed so that later wake ups are possible.
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      wakeupSource – wakeup source(s) bit field(s) that will be disabled
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_DisableWakeupSources(EcuM_WakeupSourceType wakeupSource);

/*!
 ******************************************************************************
 * \brief
 * This callout shall provide driver initialization and other hardware-related
 * startup activities in the wake up case.
 *
 * \details
 * It is called into Wakeup One state after restoring MCU to normal mode and just
 * before starting the tasks again.
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      ConfigPtr - Pointer to the EcuM post-build configuration which
 *                 contains pointers to all other BSW module post-build configurations.
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_AL_DriverRestart(const EcuM_ConfigType* ConfigPtr);

/*!
 ******************************************************************************
 * \brief
 * This callout shall start the given wake up source(s) so that they are ready
 * to perform wake up validation.
 *
 * \details
 *
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      wakeupSource – wakeup source(s) bit field(s) that will be started
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_StartWakeupSources(EcuM_WakeupSourceType wakeupSource);

/*!
 ******************************************************************************
 * \brief
 * This callout is called by EcuM to validate a wakeup source.
 *
 * \details
 * If a valid wakeup has been detected, it shall be reported to EcuM via EcuM_ValidateWakeupEvent.
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      wakeupSource – wake up source(s) bit field(s) that will be checked
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_CheckValidation(EcuM_WakeupSourceType wakeupSource);

/*!
 ******************************************************************************
 * \brief
 * This callout shall stop the given wake up source(s) after unsuccessful wake up validation.
 *
 * \details
 *
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      wakeupSource – wake up source(s) bit field(s) that will be stopped
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_StopWakeupSources(EcuM_WakeupSourceType wakeupSource);

/*!
 ******************************************************************************
 * \brief
 * This callout is invoked periodically in all reduced clock sleep modes.
 *
 * \details
 * It is explicitly allowed to poll wakeup sources from this callout and to call
 * wakeup notification functions to indicate the end of the sleep state to the ECU State Manager.
 * This function is called, when Sleep Sequence II is executing, into a while loop
 * until a wakeup occurs. For activating Sleep Sequence II the selected sleep mode shall
 * have EcuM_SleepModeSuspended parameter set to ECUM_FALSE. Into this function user can
 * add project specific code where can put the Ecu into sleep again if it is needed.
 *
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      void
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_SleepActivity(void);

/*!
 ******************************************************************************
 * \brief
 * This callout is called by the EcuM to set MCU to a needed configuration.
 *
 * \details
 * Usually MCU mode and clock need to be set.
 * It is mandatory to implement modes:
 * - ECUM_NORMAL_MCU_MODE -it is invoked by EcuM into Wakeup One state just after
 *   waking up from sleep, usually here the clock is re-initialized for high power mode
 * - ECUM_POLLING_MODE -it is invoked just before going to Sleep state when
 *   Sleep Sequence II is active, usually here the clock is initialized for low power mode
 * - all the sleep modes provided by EcuM that can be invoked and which are listed into
 *   EcuM_Cfg.h sleep modes list -EcuM_McuSetMode with active shutdown mode send as
 *   parameter is called just before going to Sleep state when Sleep Sequence I is active,
 *   usually here the clock is set to low power mode and MCU is set with corresponding sleep mode
 * Please use the provided function and adapt it to the project requirements.
 * Before entering into low/high power mode and after exiting from low/high power mode callout
 * functions are called where user can add project specific code.
 *
 *
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         non reentrant
 *
 * \pre           all must be initialized.
 * \post          process is started
 *
 * \param[out]     void
 * \param[in]      EcuM_Mode_U8 – mode that needs to be set
 *
 * \glob_start
 *   \glob_item{in,  U8_GlobA, global variable used}
 *   \glob_item{out, U8_GlobB, global variable used}
 * \glob_end
 *
 * \returns        void
 *
 ******************************************************************************
 *
 * \author        nmicule, PDES-BSW
 * \version       1.0
 * \date          12.01.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 12.01.2018, nmicule:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void EcuM_McuSetMode(U8 EcuM_Mode_U8);
/* polyspace-end MISRA-C3:5.1 [Justified:Unset] "C99 standard is used to compile, Autosar naming convention." */

#endif   /* ECUM_CBK_H_ */


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