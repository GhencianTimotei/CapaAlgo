/*------------------------------------------------------------------------------------------------+
| File: Dem_Dtc.c                                                                          |
+-------------------------------------------------------------------------------------------------+
| Project: Audi eTab                                                                              |
+-------------------------------------------------------------------------------------------------+
| Short description: In this file is handled the implementation of all DTCs.                                                      |
+------------------------------------------------------------------------------------------------*/

#ifndef DEM_DTC_H_
#define DEM_DTC_H_

typedef enum
{
    WUC_Init = 0u,
    WUC_Unqualified,
    WUC_Qualified
} te_WucStateType;

/* polyspace+16 MISRA-C3:2.5 [Justified:Low] "Macro should be kept for future usage" */
#define U8_500ms_T_DIAG_START           ((U8)50)
#define U8_1000ms_DTC_TIME              ((U8)100)
#define U8_2500ms_DTC_TIME              ((U8)200)
#define U16_5000ms_DTC_TIME             ((U16)500)
#define U16_10000ms_DTC_TIME            ((U16)800)
#define U16_90000ms_DTC_TIME            ((U16)7200)

#define U16_230ms_DTC_TIME              ((U16)23)
#define U16_120ms_DTC_TIME              ((U16)12)
#define U16_1770ms_DTC_TIME             ((U16)177)
#define U16_880ms_DTC_TIME              ((U16)88)
#define U16_5s_DTC_TIME                 ((U16)500)
#define U16_10s_DTC_TIME                ((U16)1000)

#define U16_BAT_VOLT_9_25V              ((U16)9250)
#define U16_BAT_VOLT_16_55V             ((U16)16550)

/* polyspace+1 MISRA-C3:D4.9 [Justified:Low] "This macro is used to facilitate an easy adaptation" */
#define Set_WUCState(value)             (U8_WUCState = value)

extern U8 U8_LDC_StatusReg;
extern BOOL BO_ResetHealInhStatus;
extern te_WucStateType U8_WUCState;

/*********************************************************************************************************
 *  Name                   : DemDtc_ClearDTCInformationActions
 *  Description            : Resets variables for dequalification in case of service 0x14 execution 
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
extern void DemDtc_ClearDTCInformationActions(void);

/*********************************************************************************************************
 *  Name                   : DemDtc_GetTimestamp
 *  Description            : SnapshotDataRecord timestemp information 
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
extern Std_ReturnType DemDtc_GetTimestamp(uint8* Buffer);

/*********************************************************************************************************
 *  Name                   : DemDtc_GetSupplyVoltage
 *  Description            : SnapshotDataRecord supply voltage information 
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
extern Std_ReturnType DemDtc_GetSupplyVoltage(uint8* Buffer);

/*********************************************************************************************************
 *  Name                   : DemDtc_GetKmReading
 *  Description            : SnapshotDataRecord KM reading information 
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
extern Std_ReturnType DemDtc_GetKmReading(uint8* Buffer);

/*********************************************************************************************************
 *  Name                   : DemDtc_GetVehicleSpeed
 *  Description            : SnapshotDataRecord vehicle speed information 
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
extern Std_ReturnType DemDtc_GetVehicleSpeed(uint8* Buffer);

/*********************************************************************************************************
 *  Name                   : DemDtc_KL15Status
 *  Description            : SnapshotDataRecord KL15 information 
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
extern Std_ReturnType DemDtc_KL15Status(uint8* Buffer);

/*********************************************************************************************************
 *  Name                   : DemDtc_TimeIndicationRead
 *  Description            : SnapshotDataRecord TimeIndication information 
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
extern Std_ReturnType DemDtc_TimeIndicationRead(uint8* Buffer);

/*********************************************************************************************************
 *  Name                   : DTC_0x010000_ClearEventAllowedCbk
 *  Description            : ClearEventAllowed callback for DTC 0x010000
 *  Parameters             : boolean*
 *  Return                 : none
 *********************************************************************************************************/
extern Std_ReturnType DTC_0x010000_ClearEventAllowedCbk(boolean* ClearAllowed);

/*********************************************************************************************************
 *  Name                   : DTC_0x010007_ClearEventAllowedCbk
 *  Description            : ClearEventAllowed callback for DTC 0x010007
 *  Parameters             : boolean*
 *  Return                 : none
 *********************************************************************************************************/
extern Std_ReturnType DTC_0x010007_ClearEventAllowedCbk(boolean* ClearAllowed);

/*********************************************************************************************************
 *  Name                   : DTC_0x010008_ClearEventAllowedCbk
 *  Description            : ClearEventAllowed callback for DTC 0x010008
 *  Parameters             : boolean*
 *  Return                 : none
 *********************************************************************************************************/
extern Std_ReturnType DTC_0x010008_ClearEventAllowedCbk(boolean* ClearAllowed);

/*********************************************************************************************************
 *  Name                   : DTC_0x010009_ClearEventAllowedCbk
 *  Description            : ClearEventAllowed callback for DTC 0x010009
 *  Parameters             : boolean*
 *  Return                 : none
 *********************************************************************************************************/
extern Std_ReturnType DTC_0x010009_ClearEventAllowedCbk(boolean* ClearAllowed);

/*********************************************************************************************************
 *  Name                   : DemDtc_GetEventIdPermission
 *  Description            : Checks if there is permission to set a DTC (based on the Failure Inhibition Matrix)
 *  Parameters             : Dem_EventIdType
 *  Return                 : BOOL
 *  Critical/explanation   : -
 *  Author                 : fmusteata
 *********************************************************************************************************/
/* polyspace+1 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
extern BOOL DemDtc_GetEventIdPermission(U16 eventId);

/*********************************************************************************************************
 *  Name                   : DemDtc_MainFunction
 *  Description            : Calls all the private functions of DemDtc module
 *  Parameters             : U16_ADC
 *  Return                 : U16 - voltage physical value (mV)
 *********************************************************************************************************/
extern void DemDtc_MainFunction(void);

/*********************************************************************************************************
 *  Name                   : DemDtc_NvM_JobErrorNotification
 *  Description            : DemDtc job error notification function (called by Fee)
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
extern void DemDtc_NvM_JobErrorNotification(void);

#endif /* DEM_DTC_H_ */


