/*!
 * \defgroup MOD_SERV_OS (Os_Private.h)
 * \{
 ******************************************************************************
 * \image html "Kopf_oZusatz_A4hoch_4C.jpg"
 *
 * \par Module Owner:
 * Huf Group
 *
 * \par Initial Project:
 * 1656.001 BSW
 *
 ******************************************************************************
 * \par Description:
 * Header file for OS module. Contains private functions declaration.
 *
 ******************************************************************************
 *
 * %PCMS_HEADER_SUBSTITUTION_START:%
 *
 * Configuration Management Information Log (generated by Dimensions CM)
 *
 *
 * CM Item: %PID:%
 * Item name: %PM:%
 * Location: %ARCHIVE:%
 * Revision: %PR:%
 * Date: %DATE:%
 * Author: %AUTHOR:%
 *
 * %PCMS_HEADER_SUBSTITUTION_END:% *
 ******************************************************************************
 *
 * \par Layer:
 * Operating System, Service Layer
 *
 * \par Compiler dialect:
 * C99
 *
 * \par Controller:
 * Independent
 *
 * \par Estimated resources:
 * | Resource | Amount   | Remarks         |
 * | ---------| -------- | ----------------|
 * | ROM      | x Byte   | on x controller |
 * | RAM      | y Byte   | on x controller |
 * | NVRAM    | z Byte   | on x controller |
 * | Runtime Init | X ms |                 |
 * | Runtime Task | X ms |                 |
 *
 ******************************************************************************/
#ifndef OS_PRIVATE_H_							/* To avoid double inclusion */
#define OS_PRIVATE_H_

/**[SWPS_SWS_SERVOS_00001]*/
#include "Os_Types.h"
#include "Os_Cfg.h"

/*!
 ******************************************************************************
 * \brief
 * Error hook
 *
 * \details
 * This hook routine is called by the operating system at the end of a system service which
 * returns Os_StatusType not equal E_OK. It is called before returning to the task level.
 * This hook routine is called when an alarm expires and an error is detected during
 * task activation or event setting. The ErrorHook is not called, if a system service called
 * from ErrorHook does not return E_OK as status value. Any error by calling of system services
 * from the ErrorHook can only be detected by evaluating the status value.
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         Non Reentrant
 *
 * \pre           -
 * \post          -
 *
 * \param[out]     void
 * \param[in]      Error error code
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
 * \author        mpurece, PDES-BSW
 * \version       1.0
 * \date          26.06.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 26.06.2018, mpurece:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void ErrorHook(Os_StatusType Error);

#if (STD_ON == OS_ENABLE_TASK_HOOKS)
/*!
 ******************************************************************************
 * \brief
 * Pre-task hook
 *
 * \details
 * This hook routine is called by the operating system before executing a new task,
 * but after the transition of the task to the running state (to allow evaluation
 * of the TaskID by GetTaskID).
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         Non Reentrant
 *
 * \pre           -
 * \post          -
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
 * \author        mpurece, PDES-BSW
 * \version       1.0
 * \date          26.06.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 26.06.2018, mpurece:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
 /* polyspace +1 MISRA-C3:8.5 [Not a defect:Unset] "PreTaskHook is part of the OS and was decided to be declared externally in OS private header file." */
extern void PreTaskHook(void);

/*!
 ******************************************************************************
 * \brief
 * Post-task hook
 *
 * \details
 * This hook routine is called by the operating system after executing the current task,
 * but before leaving the task's running state (to allow evaluation of the TaskID by GetTaskID).
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         Non Reentrant
 *
 * \pre           -
 * \post          -
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
 * \author        mpurece, PDES-BSW
 * \version       1.0
 * \date          26.06.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 26.06.2018, mpurece:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/* polyspace +1 MISRA-C3:8.5 [Not a defect:Unset] "PostTaskHook is part of the OS and was decided to be declared externally in OS private header file." */
extern void PostTaskHook(void);
#endif  /*(STD_ON == OS_ENABLE_TASK_HOOKS)*/

#if(STD_ON == OS_ENABLE_STARTUP_HOOK)

/*!
 ******************************************************************************
 * \brief
 * Startup hook
 *
 * \details
 * This hook routine is called by the operating system at the end of the operating system
 * initialization and before the scheduler is running. At this time the application can
 * initialize device drivers etc.
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         Non Reentrant
 *
 * \pre           -
 * \post          -
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
 * \author        mpurece, PDES-BSW
 * \version       1.0
 * \date          26.06.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 26.06.2018, mpurece:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
extern void StartupHook(void);
#endif /* (STD_ON == OS_ENABLE_STARTUP_HOOK) */

/*!
 ******************************************************************************
 * \brief
 * Shutdown hook
 *
 * \details
 * This hook routine is called by the operating system when the OS service ShutdownOS
 * has been called. This routine is called during the operating system shut down.
 ******************************************************************************
 *
 * \sync          synchronous (function done in one pass)
 * \reent         Non Reentrant
 *
 * \pre           -
 * \post          -
 *
 * \param[out]     void
 * \param[in]      Error error code
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
 * \author        mpurece, PDES-BSW
 * \version       1.0
 * \date          26.06.2018
 *
 ******************************************************************************
 *
 * \par Change history:
 *    \li 26.06.2018, mpurece:
 *       - initial revision
 *
 ******************************************************************************
 *
 * \par Remarks:
 *
 ******************************************************************************/
/* polyspace +1 MISRA-C3:5.1 [Not a defect:Unset] "OSEK naming convention" */
extern void ShutdownHook(Os_StatusType Error);
extern void OsSetFastNvm(boolean FastNvm);

#endif /* OS_PRIVATE_H_ */

/* %PCMS_HEADER_SUBSTITUTION_START:%
 ******************************************************************************
 * Document Management Information Log (generated by Dimensions CM)
 *
 * Description:
 * %PD:%
 *
 * Used by Baselines:
 * %PIRB:%
 *
 * Used by Dimensions CM Projects:
 * %PIRW:%
 *
 * Change History:
 * %PL:%
 *
 * %PCMS_HEADER_SUBSTITUTION_END:%
 */