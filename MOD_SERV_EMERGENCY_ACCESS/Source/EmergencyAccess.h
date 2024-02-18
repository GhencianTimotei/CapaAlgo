/*------------------------------------------------------------------------------------------------+
| File: EmergencyAccess.h                                                                         |
+-------------------------------------------------------------------------------------------------+
| Project: Audi eTab                                                                              |
+-------------------------------------------------------------------------------------------------+
| Short description: The file contains the header file of the Emergency Access module             |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
+------------------------------------------------------------------------------------------------*/

#ifndef EMERGENCYACCESS_H
#define EMERGENCYACCESS_H
/* polyspace+1 MISRA-C3:2.4 [Justified:Low] "Added for further implementation." */
typedef enum state {
    EmergencyAccess_IDLE = 0u,
    EmergencyAccess_HIGH,
    EmergencyAccess_LOW
} EmergencyAccess_stateType;

#define U16_ACTUATOR_SUPPLY_HIGH_VOLT_NVM   (6u)
#define U16_ACTUATOR_SUPPLY_LOW_VOLT_NVM    (12u)
#define U16_TIME_ACTUATOR_COOLDOWN_NVM      (80u)
#define U16_ACTUATOR_RETRIES_NVM            (10u)

/****************************************************************************************************
 *  Name                   : EmergencyAccess_Task
 *  Description            : Handle the task of Emergency Access
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *  Author                 : hcostin
 ****************************************************************************************************/
extern void EmergencyAccess_Task(void);

/****************************************************************************************************
 *  Name                   : EmergencyAccess_RequestSfdTestMode
 *  Description            : Request SFD Test Mode
 *  Parameters             : none
 *  Return                 : none
 ****************************************************************************************************/
extern void EmergencyAccess_RequestSfdTestMode(void);

/****************************************************************************************************
 *  Name                   : EmergencyAccess_checkParameters
 *  Description            : Checks values from NVM
 *  Parameters             : none
 *  Return                 : none
 ****************************************************************************************************/
extern void EmergencyAccess_checkParameters(void);

/****************************************************************************************************
 *  Name                   : EmergencyAccess_goToSleep
 *  Description            : Clears all states, when ECU goes to Normal state
 *  Parameters             : none
 *  Return                 : none
 ****************************************************************************************************/
extern void EmergencyAccess_goToSleep(void);

/****************************************************************************************************
 *  Name                   : EmergencyAccess_getState
 *  Description            : Get actuator state
 *  Parameters             : none
 *  Return                 : none
 ****************************************************************************************************/
extern EmergencyAccess_stateType EmergencyAccess_getState(void);

extern void EmergencyAccess_signalReceived(void);

#endif /* EMERGENCYACCESS_H */
