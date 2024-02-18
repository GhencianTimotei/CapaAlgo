/* polyspace MISRA-C3:1.1 [Justified:Unset] "All macros are needed" */
/*
 * CAN_DiagUsr.c
 *
 *  Created on: Sep 14, 2021
 *      Author: ijovano
 */

#include "CAN_DiagUsr.h"
#include "config.h"
#include "std_inc.h"
#include "Dcm.h"
#include "Dem_Dtc.h"
#include "Std_Types.h"
#include "Dem.h"
#include "Dem_Dcm.h"
#include "NvM_Cfg.h"
#include "NvmMng.h"
#include "NvM.h"
#include "PlayProtection.h"
#include "Com.h"
#include "BswM_Dcm.h"
#include "Fbl_Cfg.h"
#include "config.h"
#include "PDL.h"
#include "VA_Led.h"
#include <string.h>
#include "BatterySupervisor.h"
#include "EmergencyAccess.h"
#include "can_appl.h"

/* Define macro for getting high/low byte from 16-bit integer */
/* polyspace+6 MISRA-C3:D4.9 [Justified:Low] "Macro used to facilitate easier configuration." */
#define EXTRACT_HIGH_BYTE_U16(x)  ((U8)(((U16)x & (U16)0xFF00) >> 8))
#define EXTRACT_LOW_BYTE_U16(x)   ((U8)((U16)x & (U16)0x00FF))
/* polyspace+3 MISRA-C3:12.1 [Justified:Low] "does not affect the functionality" */
/* polyspace+2 MISRA-C3:14.3 [Justified:Low] "does not affect the functionality" */
/* Define macro for converting integer value to BCD (binary coded decimal) */
#define BYTE_TO_BCD(x)            ((U8)x<(U8)100 ? (((U8)x/(U8)10)<<4)|((U8)x%(U8)10) : (U8)0xFF)

/* Define macro for CommCtrl 0x28 service length */
#define COMM_CTRL_STANDARD_REQUEST_LENGTH 2u
#define COMM_CTRL_EXTENDED_REQUEST_LENGTH 5u

/* SPEED VALUES */
/* polyspace+2 MISRA-C3:2.5 [Justified:Low] "Macro should be kept for future usage" */
#define SPEED_LOW_VALUE 0x7E9CU
#define SPEED_HIGH_VALUE 0x8164U

/* Define pattern for magic flags used for UDS reprogramming indication */
#  define kFblBmFblStartMagicByte0        0x50u /* 'P' */
#  define kFblBmFblStartMagicByte1        0x72u /* 'r' */
#  define kFblBmFblStartMagicByte2        0x6Fu /* 'o' */
#  define kFblBmFblStartMagicByte3        0x67u /* 'g' */
#  define kFblBmFblStartMagicByte4        0x53u /* 'S' */
#  define kFblBmFblStartMagicByte5        0x69u /* 'i' */
#  define kFblBmFblStartMagicByte6        0x67u /* 'g' */
#  define kFblBmFblStartMagicByte7        0x6Eu /* 'n' */
/* polyspace < MISRA-C3:D4.9  : Not a defect : Justify with annotations >  "This macro is used to facilitate an easy adaptation." */
#  define FblBmSetFblStartMagicFlag()     FblBmSetMagicFlag(FblStart)
/* polyspace <MISRA-C3:D4.9  : Not a defect : Justify with annotations >  "This macro is used to facilitate an easy adaptation." */
/* polyspace <MISRA-C3:2.5  : Not a defect : Justify with annotations >  "For future usage." */
#  define FblBmChkFblStartMagicFlag()     FblBmChkMagicFlag(FblStart)

/* PRQA S 0342 11 */ /* MD_MSR_Rule20.10_0342 */
/* polyspace <MISRA-C3:D4.9  : Not a defect : Justify with annotations >  "This macro is used to facilitate an easy adaptation." */
/* polyspace:begin <MISRA-C3:20.10 : Not a defect : Justify with annotations >  "Preprocessor ##  is used during compilation to join  strings, it part of HUF Library" */
# define FblBmSetMagicFlag(infix)                        \
{                                                        \
   fblBmMagicFlag[0u] = kFblBm ## infix ## MagicByte0;   \
   fblBmMagicFlag[1u] = kFblBm ## infix ## MagicByte1;   \
   fblBmMagicFlag[2u] = kFblBm ## infix ## MagicByte2;   \
   fblBmMagicFlag[3u] = kFblBm ## infix ## MagicByte3;   \
   fblBmMagicFlag[4u] = kFblBm ## infix ## MagicByte4;   \
   fblBmMagicFlag[5u] = kFblBm ## infix ## MagicByte5;   \
   fblBmMagicFlag[6u] = kFblBm ## infix ## MagicByte6;   \
   fblBmMagicFlag[7u] = kFblBm ## infix ## MagicByte7;   \
}
/* polyspace:end <MISRA-C3:20.10  : Not a defect : Justify with annotations >  "Preprocessor ##  is used during compilation to join  strings, it part of HUF Library" */
# define kFblBmNoOfMagicBytes          8u

# define FBLBM_MAIN_MAGICFLAG_START_SEC_VAR_NOINIT
/* polyspace MISRA-C3:20.1 [Justified:Unset] "The file inclusion is used for memory mapping." */
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/** Reprogramming request storage variable */
/* polyspace < MISRA-C3:8.4: Not a defect : Justify with annotations > External Usage dependent on project setup*/
/* polyspace <MISRA-C3:8.7 : Not a defect : Justify with annotations >"External Usage dependent on project setup" */
volatile uint8  fblBmMagicFlag[kFblBmNoOfMagicBytes];

#define FBLBM_MAIN_MAGICFLAG_STOP_SEC_VAR_NOINIT
/* polyspace <MISRA-C3:20.1 : Not a defect : Justify with annotations > "The file inclusion is used for memory mapping." */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define DIAG__FBL_MAGIC_FLAG_SIZE         (U8)8U

/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define DIAG__EEP_PROG_REQ_FLAG           ((U8)0U)
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define DIAG__EEP_VALIDITY_FLAGS          ((U8)1U)
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define DIAG__EEP_RESET_RESPONSE_FLAG     ((U8)2U)
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define DIAG__EEP_PROG_MARKER             ((U8)4U)
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define DIAG__EEP_SEC_DELAY_FLAG          ((U8)5U)
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define DIAG__EEP_BS_BLOCK_SIZE_ACTIVE    ((U8)7U)
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define DIAG__EEP_BS_BLOCK_SIZE           ((U8)8U)

#define FBLBM_EEPNVDATA_START_SEC_VAR_NOINIT
/* polyspace <MISRA-C3:20.1 : Not a defect : Justify with annotations > "The file inclusion is used for memory mapping." */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* EEP buffer for shared data with FBL   */
/*## attribute Diag__EepData_AU8 */
/*#[ ignore */
U8 Diag__EepData_AU8[DIAG__EEP_BUFFER_SIZE];

#define FBLBM_EEPNVDATA_STOP_SEC_VAR_NOINIT
/* polyspace <MISRA-C3:20.1 : Not a defect : Justify with annotations > "The file inclusion is used for memory mapping." */
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* polyspace+6 MISRA-C3:2.5 [Justified:Low] "Macro should be kept for future usage" */
#define SPI_ERROR_MASK 			(U8)0x01
#define TRCV_ERROR_MASK 		(U8)0x02
#define OSC_ERROR_MASK 			(U8)0x04
#define ANTSHORT_ERROR_MASK 	(U8)0x08
#define ANTOPEN_ERROR_MASK		(U8)0x10
#define ANT_HEAV_DETUNED_MASK 	(U8)0x20

#define TP_BLOCK_SIZE_DEFAULT   (U8)0x0Fu
#define TP_BLOCK_SIZE_ACTIVE    (U8)0xA4u
#define DEFAULT_SESSION         (U8)1u

/* polyspace+3 MISRA-C3:2.4 [Justified:Low] "Added for further implementation." */
typedef enum tstAsynchWriteSts {
    REQ_WRITE,
    REQ_CHECK,
}tstAsynchWriteSts;

/* polyspace:begin < MISRA-C3:8.4,8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup */
U8 Basic_Settings_Status = 0x00;
U8 Unlock_status_of_ECU_of_protection_of_vehicle_diagnosis[4] = {0xFF, 0xFF, 0xFF, 0xFF};
U8 Near_field_communication_status[2]={0xFF, 0xEC};
U8 VWLogicalSoftwareBlockLockValue[4]={0x00, 0x01, 0x00, 0x00};
U8 BootloaderTPBlocksize = TP_BLOCK_SIZE_DEFAULT;
U8 Mode_of_protection_of_vehicle_diagnosis=0xFF;
/* polyspace < CERT-C:CON43-C : Not a defect : Justify with annotations > No concurrency on this structure */
U8 Near_field_communication_control_module_1_status[2]={0x18, 0xFF};

U8 Active_Diagnostic_Session= 0x00;

U8 System_Supplier_ECU_Software_Version_Number[4]= {0x05, 0x02, 0x02, 0x00};

U8 ASAM_ODX_File_Identifier[26]="EV_NFCDriveSideAU41X";

U8 ASAM_ODX_File_Version[6]={0x30, 0x30, 0x31, 0x30, 0x30, 0x31};

U8 VW_Logical_Software_Block_Version[8]={0xFF, 0xFF, 0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF};

U8 Technical_specifications_version[26]={
		0x05, 0x09, 0x02, 0x09, 0x05, 0x09, 0x02, 0x0A, 0x05, 0x09,
		0x04, 0x06, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00,
		0x02, 0x02, 0x00, 0x00, 0x00, 0x00
};

U8 System_identification[4]= {0x00, 0x00, 0x81, 0x36};

U8 VW_system_firmware_versions[5]={0xFF,0xFF,0xFF,0xFF,0xFF};

ST_EEPROM_VERSION_NVM_parameters_T ST_EEPROM_VERSION_NVM_params;
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
ST_DID_System_Supplier_ECU_Software_Number_parameters_T ST_DID_System_Supplier_ECU_Software_Number_params;
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
ST_DID_FAZIT_ID_NVM_parameters_T ST_DID_FAZIT_ID_NVM_params;
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
ST_DID_SparePart_parameters_T ST_DID_SparePartNr_NVM_params;
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
ST_DID_ECU_SerialNr_parameters_T ST_DID_ECU_SerialNr_NVM_params;
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
ST_DID_ECU_HardwareNr_parameters_T ST_DID_ECU_HardwareNr_NVM_params;
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
ST_DID_SysSupplier_ECU_HardwareNr_parameters_T ST_DID_SysSupplier_ECU_HardwareNr_NVM_params;
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
ST_DID_SysNameOrEngineType_parameters_T ST_DID_SysNameOrEngineType_NVM_params;
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
ST_DID_DataSetNr_parameters_T ST_DID_DataSetNr_NVM_params;
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
ST_DID_DataSetVersionNr_parameters_T ST_DID_DataSetVersionNr_NVM_params;
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
ST_DID_ECU_HardwareVersionNr_parameters_T ST_DID_ECU_HardwareVersionNr_NVM_params;
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
ST_DID_WorkshopSystemName_parameters_T ST_DID_WorkshopSystemName_NVM_params;
/* polyspace < MISRA-C3:5.1,8.7 : Not a defect : Justify with annotations > C99 standard is used to compile, Huf naming convention */
ST_DID_SysSupplier_ECU_HardwareVersionNr_parameters_T ST_DID_SysSupplier_ECU_HardwareVersionNr_NVM_params;
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
ST_DID_ProgrammingPreconditions_parameters_T ST_DID_ProgrammingPreconditions_NVM_params;
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
ST_DID_Huf_EOL_Done_parameters_T DID_Huf_EOL_Done_NVM_param;
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
ST_DID_Homologation_parameters_T DID_HomologationMode_NVM_param;
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
ST_DID_NFC_debugSwitch_parameters_T DID_NFC_debugSwitch_NVM_param;
ST_DID_HUF_Production_Date_parameters_T DID_HUF_Production_Date_NVM_param;
ST_DID_Katek_EOL_Done_parameters_T DID_Katek_EOL_Done_NVM_param;
/* polyspace+10 MISRA-C3:8.5 [Not a defect:Low] "added here for the ease of code" */
extern ST_lock_sensor_NVM_parameters_T ST_lock_sensor_NVM_params;
extern ST_unlock_sensor_NVM_parameters_T ST_unlock_sensor_NVM_params;
extern ST_inductive_sensor_NVM_parameters_T ST_inductive_sensor_NVM_params;
extern ST_BATTERY_SUPERVISIOR_NVM_parameters_T ST_battery_supervisor_NVM_params;
extern ST_EMERGENCY_ACCESS_NVM_parameters_T ST_emergency_access_NVM_params;
extern ST_TIME_NFC_DIAG_parameters_T ST_TIME_NFC_DIAG_NVM_params;
extern ST_DIGIT_NFC_parameters_T ST_DIGIT_NFC_NVM_params;
ST_FD02_SPARE_NVM_parameters_T ST_FD02_spare_NVM_params;

/* polyspace+1 MISRA-C3:8.5 [Justified:Low] "these declarations will never meet" */
extern void EmergencyAccess_RequestSfdTestMode(void);

  FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CAN_DiagUsr_CheckReprogrammingPreconditions(
  P2VAR(boolean, AUTOMATIC, DCM_VAR_NOINIT) resetAllowed
  );

/* Info about licensed AUTOSAR modules for service 22 DID F1AF */
/* Note: FDS is a functionality spread amongst multiple components and there are no defines for module/vendor/version in the code, therefore the information is hard-coded here. */
#define FDS_VENDOR_ID           0x3A    /* ESCRYPT */
#define FDS_MODULE_ID           0xFF    /* CDD, temporary */
#define FDS_MAJOR_VERSION       4u
#define FDS_MINOR_VERSION       8u
#define FDS_PATCH_VERSION       0u
static const U8 U8_AUTOSARModuleInfo[21] =   /* 3*7 bytes */
{
  EXTRACT_HIGH_BYTE_U16(FDS_MODULE_ID),      EXTRACT_LOW_BYTE_U16(FDS_MODULE_ID),      EXTRACT_HIGH_BYTE_U16(FDS_VENDOR_ID),      EXTRACT_LOW_BYTE_U16(FDS_VENDOR_ID),      BYTE_TO_BCD(FDS_MAJOR_VERSION),         BYTE_TO_BCD(FDS_MINOR_VERSION),         BYTE_TO_BCD(FDS_PATCH_VERSION),         /* FDS */
};

#ifdef TESSY
    void work_task()
    {

    }
#endif


/* polyspace+1 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_Dcm_DcmControlDtcSetting_DcmControlDtcSetting(Dcm_ControlDtcSettingType nextMode)
{
	return E_OK;
}

/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
/* polyspace < MISRA-C3:8.2 :  Not a defect : Justify with annotations > The function type is same as in prototype form. */
/* polyspace < MISRA-C3:8.4,8.5: Not a defect : Justify with annotations > External Usage dependent on project setup*/
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_Dcm_DcmDiagnosticSessionControl_DcmDiagnosticSessionControl(Dcm_DiagnosticSessionControlType nextMode) {
    return E_OK;
}
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
/* polyspace < MISRA-C3:8.4: Not a defect : Justify with annotations > External Usage dependent on project setup*/
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_Dcm_DcmEcuReset_DcmEcuReset(Dcm_EcuResetType nextMode){

  /* polyspace < MISRA-C3:8.5 :Justified : Unset >The extern is used for backwards compatibility */
  /* polyspace < MISRA-C3:17.3 : Not a defect : Justify with annotations > Mcu_PerformReset is an external function that is called. */
  /* polyspace < MISRA-C3:17.7 : Justified : Unset > This function performs a micro-controller reset by using the hardware feature of the micro-controller. In case the function returns, the user must reset the platform using an alternate reset mechanism */
  /* polyspace < MISRA-C3:8.3 : Not a defect : Justify with annotations > Function use the same names and type */
  Std_ReturnType ret = DCM_E_OK;

  if (nextMode == RTE_MODE_DcmEcuReset_EXECUTE)
  {
    SuspendAllInterrupts();
    Mcu_PerformReset();
  }
  else
  {
	/*do nothing*/
  }

  return ret;
}
/* polyspace < MISRA-C3:8.13 : Not a defect : Justify with annotations> A const pointer not possible here */
/* polyspace < MISRA-C3:8.4 : Not a defect : Justify with annotations > External Usage dependent on project setup */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Rte_SwitchAck_Dcm_DcmEcuReset_DcmEcuReset(void) {
    return RTE_E_TRANSMIT_ACK;
}

/* polyspace < MISRA-C3:8.4,8.5,8.13 : Not a defect : Justify with annotations > External Usage dependent on project setup */
/* polyspace <MISRA-C3:2.7 : Not a defect : Justify with annotations > "Paremeter should be kept for future usage" */    
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_SetProgConditions(Dcm_ProgConditionsPtrType progConditions)
{


    if(progConditions->TesterSourceAddr == 0x217)
    {
        /* Tp layer address for FBL */
        Diag__EepData_AU8[DIAG__EEP_TESTER_ADDR] = 0x01U;
    }
    else
    {
        /* Tp layer address for FBL */
        Diag__EepData_AU8[DIAG__EEP_TESTER_ADDR] = 0x00U;
    }
    /* This Callout is called during first call of Dcm_Mainfunction().
       If it returns DCM_E_NOT_OK, a Det-Error would be hit (0x35,0x00,0xf0,0x06) */
    if (progConditions->ReprogrammingRequest == TRUE)
    {
        FblBmSetFblStartMagicFlag();
        (void)Mcu_PerformReset();
    }

    return DCM_E_OK;
}

/***************************************************** **************************
 *                   READ BY IDENTIFIER READ FUNCTIONS                    *
 * ******************************************************************************/
/***********************************************************************************************************************
 *  CanDiagUsr_0x0102_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0x0102_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
	/* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */ 
   	Data[0]=Basic_Settings_Status;
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0x0174_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0x0174_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
  
  /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
  /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	U8 U8_index;
	for(U8_index=0; U8_index<4; U8_index++){
		Data[U8_index]=Unlock_status_of_ECU_of_protection_of_vehicle_diagnosis[U8_index];
	}
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0x0261_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[in]     OpStatus            The operation status
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \return        DCM_E_PENDING       The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+5 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0x0261_Read_Function(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations> Cast to void does not affect the functionality */
  	static Std_ReturnType returnValue = E_OK;
  	Std_ReturnType returnReadNvMBlock = E_NOT_OK;
  	if (returnValue != DCM_E_PENDING)
  	{
  	  returnReadNvMBlock = NvM_ReadBlock(NvMConf_NvMBlockDescriptor_NvM_DID_OBD_Driving_Cycle_set, Data);
  	}
  	else
  	{
  	  returnReadNvMBlock = E_OK;
  	}
  	NvM_RequestResultType NvMStatus;
  	if (E_OK == returnReadNvMBlock)
  	{
  	  (void)NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_DID_OBD_Driving_Cycle_set, &NvMStatus);
  	  if (NVM_REQ_PENDING == NvMStatus)
  	  {
  	    returnValue = DCM_E_PENDING;
  	  }
  	  else
  	  {
  	    returnValue = E_OK;
  	  }
  	}
	else
	{
		/*do nothing*/
	}

	return returnValue;
}
/***********************************************************************************************************************
 *  CanDiagUsr_0x0301_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0x0301_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
	U8 U8_index;
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */

	for(U8_index=0; U8_index<2; U8_index++){
		Data[U8_index]=Near_field_communication_status[U8_index];
	}

	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0x0407_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0x0407_Read_Function(P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data)
{
  (void)memcpy(&Data[0], &AU8_NVM_AswProgAttemtsCnt_BL[0], sizeof(AU8_NVM_AswProgAttemtsCnt_BL));         /* BL Prog Attemtps Coutner - fixed value 00 01 */
  (void)memcpy(&Data[2], &AU8_NVM_AswProgAttemtsCnt[0], sizeof(AU8_NVM_AswProgAttemtsCnt)); /* ASW Prog Attemtps Coutner - value read from NvM */
  
  return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0x040F_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0x040F_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
	U8 U8_index;
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */

	for(U8_index=0; U8_index<4; U8_index++){
		Data[U8_index]=VWLogicalSoftwareBlockLockValue[U8_index];
	}

	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0x0410_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0x0410_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	Data[0] = BootloaderTPBlocksize;
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0x0410_Write_Function()
 ***********************************************************************************************************************/
/*! \brief         Writes the data element of the DID.
 *  \details       This function is a request from the DCM to the application to set  data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \param[out]    ErrorCode           Negative response code
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0x0410_Write_Function(
  P2CONST(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode
  )
  {
    BootloaderTPBlocksize = Data[0];
    *ErrorCode = E_OK;
    return E_OK;
  }

/***********************************************************************************************************************
 *  CanDiagUsr_0x05F0_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[in]     OpStatus            The operation status
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \return        DCM_E_PENDING       The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+5 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0x05F0_Read_Function(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	Data[0] = DID_NFC_debugSwitch_NVM_param.U8_BYTE1;

  	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0x0600_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[in]     OpStatus            The operation status
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \return        DCM_E_PENDING       The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
/* polyspace+5 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0x0600_Read_Function(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  )
  {
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */

	Data[0]=ST_AUDI_NVM_params.U8_Byte_0_Audi_param_NVM;
	Data[1]=ST_AUDI_NVM_params.U8_Byte_1_Audi_param_NVM;
	Data[2]=ST_AUDI_NVM_params.U8_Byte_2_Audi_param_NVM;
	Data[3]=ST_AUDI_NVM_params.U8_Byte_3_Audi_param_NVM;
	Data[4]=ST_AUDI_NVM_params.U8_Byte_4_Audi_param_NVM;
	Data[5]=ST_AUDI_NVM_params.U8_Byte_5_Audi_param_NVM;
	Data[6]=ST_AUDI_NVM_params.U8_Byte_6_Audi_param_NVM;
	Data[7]=ST_AUDI_NVM_params.U8_Byte_7_Audi_param_NVM;
	Data[8]=ST_AUDI_NVM_params.U8_Byte_8_Audi_param_NVM;
	Data[9]=ST_AUDI_NVM_params.U8_Byte_9_Audi_param_NVM;
	Data[10]=ST_AUDI_NVM_params.U8_Byte_10_Audi_param_NVM;
	Data[11]=ST_AUDI_NVM_params.U8_Byte_11_Audi_param_NVM;
	Data[12]=ST_AUDI_NVM_params.U8_Byte_12_Audi_param_NVM;
	Data[13]=ST_AUDI_NVM_params.U8_Byte_13_Audi_param_NVM;
	Data[14]=ST_AUDI_NVM_params.U8_Byte_14_Audi_param_NVM;
	Data[15]=ST_AUDI_NVM_params.U8_Byte_15_Audi_param_NVM;
	Data[16]=ST_AUDI_NVM_params.U8_Byte_16_Audi_param_NVM;
	Data[17]=ST_AUDI_NVM_params.U8_Byte_17_Audi_param_NVM;
	Data[18]=ST_AUDI_NVM_params.U8_Byte_18_Audi_param_NVM;
	Data[19]=ST_AUDI_NVM_params.U8_Byte_19_Audi_param_NVM;
	Data[20]=ST_AUDI_NVM_params.U8_Byte_20_Audi_param_NVM;
	Data[21]=ST_AUDI_NVM_params.U8_Byte_21_Audi_param_NVM;
	Data[22]=ST_AUDI_NVM_params.U8_Byte_22_Audi_param_NVM;
	Data[23]=ST_AUDI_NVM_params.U8_Byte_23_Audi_param_NVM;
	Data[24]=ST_AUDI_NVM_params.U8_Byte_24_Audi_param_NVM;
	Data[25]=ST_AUDI_NVM_params.U8_Byte_25_Audi_param_NVM;
	Data[26]=ST_AUDI_NVM_params.U8_Byte_26_Audi_param_NVM;
	Data[27]=ST_AUDI_NVM_params.U8_Byte_27_Audi_param_NVM;
	Data[28]=ST_AUDI_NVM_params.U8_Byte_28_Audi_param_NVM;
	Data[29]=ST_AUDI_NVM_params.U8_Byte_29_Audi_param_NVM;
	Data[30]=ST_AUDI_NVM_params.U8_Byte_30_Audi_param_NVM;
	Data[31]=ST_AUDI_NVM_params.U8_Byte_31_Audi_param_NVM;
	Data[32]=ST_AUDI_NVM_params.U8_Byte_32_Audi_param_NVM;
	Data[33]=ST_AUDI_NVM_params.U8_Byte_33_Audi_param_NVM;
	Data[34]=ST_AUDI_NVM_params.U8_Byte_34_Audi_param_NVM;
	Data[35]=ST_AUDI_NVM_params.U8_Byte_35_Audi_param_NVM;
	Data[36]=ST_AUDI_NVM_params.U8_Byte_36_Audi_param_NVM;
	Data[37]=ST_AUDI_NVM_params.U8_Byte_37_Audi_param_NVM;
	Data[38]=ST_AUDI_NVM_params.U8_Byte_38_Audi_param_NVM;
	Data[39]=ST_AUDI_NVM_params.U8_Byte_39_Audi_param_NVM;
	Data[40]=ST_AUDI_NVM_params.U8_Byte_40_Audi_param_NVM;
	Data[41]=ST_AUDI_NVM_params.U8_Byte_41_Audi_param_NVM;
	Data[42]=ST_AUDI_NVM_params.U8_Byte_42_Audi_param_NVM;
	Data[43]=ST_AUDI_NVM_params.U8_Byte_43_Audi_param_NVM;
	Data[44]=ST_AUDI_NVM_params.U8_Byte_44_Audi_param_NVM;
	Data[45]=ST_AUDI_NVM_params.U8_Byte_45_Audi_param_NVM;
	Data[46]=ST_AUDI_NVM_params.U8_Byte_46_Audi_param_NVM;
	Data[47]=ST_AUDI_NVM_params.U8_Byte_47_Audi_param_NVM;
	Data[48]=ST_AUDI_NVM_params.U8_Byte_48_Audi_param_NVM;
	Data[49]=ST_AUDI_NVM_params.U8_Byte_49_Audi_param_NVM;


	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0x3C0E_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0x3C0E_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	Data[0]=Mode_of_protection_of_vehicle_diagnosis;
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0x523E_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0x523E_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
)
{
    BatSup_voltageStateType voltState = BatSup_getVoltageState();
    U8 PlayProt_active = PlayProt_getActiveState(PlayProt_inductive);

    /* Clear bits 3 and 4 for under/overvoltage */
    Near_field_communication_control_module_1_status[0] &= 0xE7u;
    if (voltState == BATSUP_UNDERVOLTAGE)
    {
        Near_field_communication_control_module_1_status[0] |= 0x08u;
    }
    else
    {
        if(voltState == BATSUP_OVERVOLTAGE)
        {
            Near_field_communication_control_module_1_status[0] |= 0x10u;
        }
    }
    if(PlayProt_active != 0u)
    {
        Near_field_communication_control_module_1_status[0] |= 0x20u;
    }
    else
    {
        Near_field_communication_control_module_1_status[0] &= 0xDFu;
    }
	Data[0] = Near_field_communication_control_module_1_status[0];
	Data[1] = PlayProt_getActivationCounter(PlayProt_inductive);

	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0x7802_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[in]     OpStatus            The operation status
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \return        DCM_E_PENDING       The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+5 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+3 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0x7802_Read_Function(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
	Data[0] = VA_LED_GetLightInfo();
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF15B_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF15B_Read_Function(P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data) 
{
	/* First return fingerprint information of Bootloader block */
    (void)memcpy(&Data[0], &AU8_NVM_Fingerprint_BL[0], FINGEPRINT_SIZE);

    /* FBL State - always valid, otherwise this code would not be executed */
    Data[9] = LOGICAL_BLOCK_VALID;

	/* Second return fingerprint information of Application block
	 * This information is written by the tester in the reset safe RAM while reprogramming */
	(void)memcpy(&Data[10], &AU8_NVM_Fingerprint[0], FINGEPRINT_SIZE);

    /* APPL State - always valid, otherwise this code would not be executed */
    Data[19] = LOGICAL_BLOCK_VALID;

	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF17C_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF17C_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	Data[0]=PDL.VW_FAZIT_Identification_String[0];
	Data[1]=PDL.VW_FAZIT_Identification_String[1];
	Data[2]=PDL.VW_FAZIT_Identification_String[2];
	Data[3]=PDL.VW_FAZIT_Identification_String[3];
	Data[4]=PDL.VW_FAZIT_Identification_String[4];
	Data[5]=PDL.VW_FAZIT_Identification_String[5];
	Data[6]=PDL.VW_FAZIT_Identification_String[6];
	Data[7]=PDL.VW_FAZIT_Identification_String[7];
	Data[8]=PDL.VW_FAZIT_Identification_String[8];
	Data[9]=PDL.VW_FAZIT_Identification_String[9];
	Data[10]=PDL.VW_FAZIT_Identification_String[10];
	Data[11]=PDL.VW_FAZIT_Identification_String[11];
	Data[12]=PDL.VW_FAZIT_Identification_String[12];
	Data[13]=PDL.VW_FAZIT_Identification_String[13];
	Data[14]=PDL.VW_FAZIT_Identification_String[14];
	Data[15]=PDL.VW_FAZIT_Identification_String[15];
	Data[16]=PDL.VW_FAZIT_Identification_String[16];
	Data[17]=PDL.VW_FAZIT_Identification_String[17];;
	Data[18]=PDL.VW_FAZIT_Identification_String[18];
	Data[19]=PDL.VW_FAZIT_Identification_String[19];
	Data[20]=PDL.VW_FAZIT_Identification_String[20];
	Data[21]=PDL.VW_FAZIT_Identification_String[21];
	Data[22]=PDL.VW_FAZIT_Identification_String[22];

	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF186_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF186_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  )
{
	Dcm_SesCtrlType sesCtrlType;
	(void) Dcm_GetSesCtrlType(&sesCtrlType);
	Data[0]= (U8)sesCtrlType;
	return E_OK;
}


/***********************************************************************************************************************
 *  CanDiagUsr_0xF189_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF189_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
	U8 U8_index;

	for(U8_index = 0; U8_index < 4; U8_index++)
	{
		Data[U8_index] = VW_Logical_Software_Block_Version_ASW[U8_index];
	}
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF18C_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF18C_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
    Data[0]=PDL.ECU_Serial_Number[0];
    Data[1]=PDL.ECU_Serial_Number[1];
    Data[2]=PDL.ECU_Serial_Number[2];
    Data[3]=PDL.ECU_Serial_Number[3];
    Data[4]=PDL.ECU_Serial_Number[4];
    Data[5]=PDL.ECU_Serial_Number[5];
    Data[6]=PDL.ECU_Serial_Number[6];
    Data[7]=PDL.ECU_Serial_Number[7];
    Data[8]=PDL.ECU_Serial_Number[8];
    Data[9]=PDL.ECU_Serial_Number[9];
    Data[10]=PDL.ECU_Serial_Number[10];
    Data[11]=PDL.ECU_Serial_Number[11];
    Data[12]=PDL.ECU_Serial_Number[12];
    Data[13]=PDL.ECU_Serial_Number[13];
    Data[14]=PDL.ECU_Serial_Number[14];
    Data[15]=PDL.ECU_Serial_Number[15];
    Data[16]=PDL.ECU_Serial_Number[16];
    Data[17]=PDL.ECU_Serial_Number[17];
    Data[18]=PDL.ECU_Serial_Number[18];
    Data[19]=PDL.ECU_Serial_Number[19];

	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF191_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF191_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	Data[0]=PDL.VW_ECU_Hardware_Number[0];
	Data[1]=PDL.VW_ECU_Hardware_Number[1];
	Data[2]=PDL.VW_ECU_Hardware_Number[2];
	Data[3]=PDL.VW_ECU_Hardware_Number[3];
	Data[4]=PDL.VW_ECU_Hardware_Number[4];
	Data[5]=PDL.VW_ECU_Hardware_Number[5];
	Data[6]=PDL.VW_ECU_Hardware_Number[6];
	Data[7]=PDL.VW_ECU_Hardware_Number[7];
	Data[8]=PDL.VW_ECU_Hardware_Number[8];
	Data[9]=PDL.VW_ECU_Hardware_Number[9];
	Data[10]=PDL.VW_ECU_Hardware_Number[10];

	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF192_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF192_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	Data[0]=PDL.System_Supplier_ECU_Hardware_Number[0];
	Data[1]=PDL.System_Supplier_ECU_Hardware_Number[1];
	Data[2]=PDL.System_Supplier_ECU_Hardware_Number[2];
	Data[3]=PDL.System_Supplier_ECU_Hardware_Number[3];
	Data[4]=PDL.System_Supplier_ECU_Hardware_Number[4];
	Data[5]=PDL.System_Supplier_ECU_Hardware_Number[5];
	Data[6]=PDL.System_Supplier_ECU_Hardware_Number[6];
	Data[7]=PDL.System_Supplier_ECU_Hardware_Number[7];
	Data[8]=PDL.System_Supplier_ECU_Hardware_Number[8];
	Data[9]=PDL.System_Supplier_ECU_Hardware_Number[9];
	Data[10]=PDL.System_Supplier_ECU_Hardware_Number[10];

	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF193_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace MISRA-C3:2.7, 8.13 [Justified:Unset] "Paremeter should be kept for future usage. A const pointer not possible here" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF193_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
	Data[0]=PDL.System_Supplier_ECU_Hardware_Version_Number[0];
	Data[1]=PDL.System_Supplier_ECU_Hardware_Version_Number[1];
	Data[2]=PDL.System_Supplier_ECU_Hardware_Version_Number[2];
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF194_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF194_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
	Data[0]=(U8)PDL.System_Supplier_ECU_Software_Number[0];
	Data[1]=(U8)PDL.System_Supplier_ECU_Software_Number[1];
	Data[2]=(U8)PDL.System_Supplier_ECU_Software_Number[2];
	Data[3]=(U8)PDL.System_Supplier_ECU_Software_Number[3];
	Data[4]=(U8)PDL.System_Supplier_ECU_Software_Number[4];
	Data[5]=(U8)PDL.System_Supplier_ECU_Software_Number[5];
	Data[6]=(U8)PDL.System_Supplier_ECU_Software_Number[6];
	Data[7]=(U8)PDL.System_Supplier_ECU_Software_Number[7];
	Data[8]=(U8)PDL.System_Supplier_ECU_Software_Number[8];
	Data[9]=(U8)PDL.System_Supplier_ECU_Software_Number[9];
	Data[10]=(U8)PDL.System_Supplier_ECU_Software_Number[10];

	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF195_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF195_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	Data[0] = PARAM_VER_BYTE_EL_VAR;
	Data[1] = PARAM_VER_BYTE_SW_PREFIX;
	Data[2] = PARAM_VER_BYTE_SW_SUFFIX;
	Data[3] = PARAM_VER_BYTE_SW_ENG_DROP;

	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF197_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF197_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	Data[0]=ST_DID_SysNameOrEngineType_NVM_params.U8_BYTE1;
	Data[1]=ST_DID_SysNameOrEngineType_NVM_params.U8_BYTE2;
	Data[2]=ST_DID_SysNameOrEngineType_NVM_params.U8_BYTE3;
	Data[3]=ST_DID_SysNameOrEngineType_NVM_params.U8_BYTE4;
	Data[4]=ST_DID_SysNameOrEngineType_NVM_params.U8_BYTE5;
	Data[5]=ST_DID_SysNameOrEngineType_NVM_params.U8_BYTE6;
	Data[6]=ST_DID_SysNameOrEngineType_NVM_params.U8_BYTE7;
	Data[7]=ST_DID_SysNameOrEngineType_NVM_params.U8_BYTE8;
	Data[8]=ST_DID_SysNameOrEngineType_NVM_params.U8_BYTE9;
	Data[9]=ST_DID_SysNameOrEngineType_NVM_params.U8_BYTE10;
	Data[10]=ST_DID_SysNameOrEngineType_NVM_params.U8_BYTE11;
	Data[11]=ST_DID_SysNameOrEngineType_NVM_params.U8_BYTE12;
	Data[12]=ST_DID_SysNameOrEngineType_NVM_params.U8_BYTE13;

	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF19E_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF19E_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
	U8 U8_index;
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */

	for(U8_index=0; U8_index<26; U8_index++){
		Data[U8_index]=ASAM_ODX_File_Identifier[U8_index];
	}
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF19E_GetDataLength_Function()
 ***********************************************************************************************************************/
/*! \brief         Gets data length of the data element.
 *  \details       This function is a request from the DCM to the application to return the data length of a data 
 *                 element. The concrete name of the callout is defined by the configuration parameter 
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadDataLengthFnc.
 *  \param[in,out] DataLength     Data length
 *  \return        E_OK           Read operation succeeded
 *  \return        E_NOT_OK       The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF19E_GetDataLength_Function(
  P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) DataLength
  ){
    *DataLength = 0;
    while ( (ASAM_ODX_File_Identifier[*DataLength] != 0x00) && (*DataLength < 25) )  /* max string length is 26 characters including null termination (SWR_1191) */
    {
      *DataLength += 1;
    }
    *DataLength += 1;  /* add size of null termination */
    return E_OK;
  }

/***********************************************************************************************************************
 *  CanDiagUsr_0xF1A0_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[in]     OpStatus            The operation status
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \return        DCM_E_PENDING       The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+5 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF1A0_Read_Function(
  Dcm_OpStatusType OpStatus,	
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	Data[0]=ST_DID_DataSetNr_NVM_params.U8_BYTE1;
	Data[1]=ST_DID_DataSetNr_NVM_params.U8_BYTE2;
	Data[2]=ST_DID_DataSetNr_NVM_params.U8_BYTE3;
	Data[3]=ST_DID_DataSetNr_NVM_params.U8_BYTE4;
	Data[4]=ST_DID_DataSetNr_NVM_params.U8_BYTE5;
	Data[5]=ST_DID_DataSetNr_NVM_params.U8_BYTE6;
	Data[6]=ST_DID_DataSetNr_NVM_params.U8_BYTE7;
	Data[7]=ST_DID_DataSetNr_NVM_params.U8_BYTE8;
	Data[8]=ST_DID_DataSetNr_NVM_params.U8_BYTE9;
	Data[9]=ST_DID_DataSetNr_NVM_params.U8_BYTE10;
	Data[10]=ST_DID_DataSetNr_NVM_params.U8_BYTE11;

	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF1A1_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+5 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF1A1_Read_Function(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	Data[0]=ST_DID_DataSetVersionNr_NVM_params.U8_BYTE1;
	Data[1]=ST_DID_DataSetVersionNr_NVM_params.U8_BYTE2;
	Data[2]=ST_DID_DataSetVersionNr_NVM_params.U8_BYTE3;
	Data[3]=ST_DID_DataSetVersionNr_NVM_params.U8_BYTE4;
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF1A2_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF1A2_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
	U8 U8_index;
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */

	for(U8_index=0; U8_index<6; U8_index++){
		Data[U8_index]=ASAM_ODX_File_Version[U8_index];
	}
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF1A3_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF1A3_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	Data[0]=PDL.VW_ECU_Hardware_Version_Number[0];
	Data[1]=PDL.VW_ECU_Hardware_Version_Number[1];
	Data[2]=PDL.VW_ECU_Hardware_Version_Number[2];
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF1AA_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF1AA_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	Data[0]=ST_DID_WorkshopSystemName_NVM_params.U8_BYTE1;
	Data[1]=ST_DID_WorkshopSystemName_NVM_params.U8_BYTE2;
	Data[2]=ST_DID_WorkshopSystemName_NVM_params.U8_BYTE3;
	Data[3]=ST_DID_WorkshopSystemName_NVM_params.U8_BYTE4;
	Data[4]=ST_DID_WorkshopSystemName_NVM_params.U8_BYTE5;

	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF1AB_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF1AB_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
	memcpy((void *)&Data[0], (const void *)GetFblCommonDataPtr(), FBL_HEADER_COMMON_DATA_FBL_VERSION_SIZE);
	memcpy(&Data[4], VW_Logical_Software_Block_Version_ASW, 4);

	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF1AF_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF1AF_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
	U8 U8_index;
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
    
	for(U8_index=0; U8_index<sizeof(U8_AUTOSARModuleInfo); U8_index++){
		Data[U8_index] = U8_AUTOSARModuleInfo[U8_index];
	}

	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF1B4_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF1B4_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */

	U8 U8_index;

	for(U8_index=0; U8_index<26; U8_index++){
		Data[U8_index]=Technical_specifications_version[U8_index];
	}
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF1B6_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace <MISRA-C3:D4.5 : Not a defect: Justify with annotations > Function name will not be changed because it contains the DID number */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF1B6_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
	U8 U8_index;
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */

	for(U8_index=0; U8_index<4; U8_index++){
		Data[U8_index]=System_identification[U8_index];
	}
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF1B8_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF1B8_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
	U8 U8_index;
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */

	for(U8_index=0; U8_index<5; U8_index++){
		Data[U8_index]=VW_system_firmware_versions[U8_index];
	}
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF1DF_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF1DF_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	Data[0]=0x40;
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xFD01_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+5 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xFD01_Read_Function(
    Dcm_OpStatusType OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data)
{
    Std_ReturnType returnVal = DCM_E_OK;
    if(Data != NULL)
    {
        Data[0] = DID_Katek_EOL_Done_NVM_param.U8_BYTE1;
		Data[1] = DID_Katek_EOL_Done_NVM_param.U8_BYTE2;
    }
    else
    {
        returnVal = DCM_E_NOT_OK;
    }
    return returnVal;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xFD02_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[in]     OpStatus            The operation status
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \return        DCM_E_PENDING       The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+20 MISRA-C3:18.4 [Justified:Low] "The operators are applied to an expression of pointer type" */
/* polyspace+20 MISRA-C3:17.8 [Justified:Low] "A function parameter is changed" */
/* polyspace+5 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xFD02_Read_Function(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
	memcpy((void *)Data, (const void *)&ST_unlock_sensor_NVM_params, sizeof(ST_unlock_sensor_NVM_params));
	Data += sizeof(ST_unlock_sensor_NVM_params);
	memcpy((void *)Data, (const void *)&ST_lock_sensor_NVM_params, sizeof(ST_lock_sensor_NVM_params));
	Data += sizeof(ST_lock_sensor_NVM_params);
	memcpy((void *)Data, (const void *)&ST_inductive_sensor_NVM_params, sizeof(ST_inductive_sensor_NVM_params));
	Data += sizeof(ST_inductive_sensor_NVM_params);
	memcpy((void *)Data, (const void *)&ST_battery_supervisor_NVM_params, sizeof(ST_battery_supervisor_NVM_params));
	Data  += sizeof(ST_battery_supervisor_NVM_params);
	memcpy((void *)Data, (const void *)&ST_emergency_access_NVM_params, sizeof(ST_emergency_access_NVM_params));
	Data  += sizeof(ST_emergency_access_NVM_params);
	memcpy((void *)Data, (const void *)&ST_FD02_spare_NVM_params, sizeof(ST_FD02_spare_NVM_params));
	Data  += sizeof(ST_FD02_spare_NVM_params);
	/* polyspace:end < MISRA-C3:18.4 : Not a defect : Justify with annotations > Pointer arithmetic is necessary here. */
    /* polyspace:end < MISRA-C3:17.7,17.8 : Not a defect : Justify with annotations > */
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xFD03_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[in]     OpStatus            The operation status
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \return        DCM_E_PENDING       The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+5 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xFD03_Read_Function(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	Data[0] = DID_Huf_EOL_Done_NVM_param.U8_BYTE1;

  	return E_OK;
}	

/***********************************************************************************************************************
 *  CanDiagUsr_0xFD04_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[in]     OpStatus            The operation status
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \return        DCM_E_PENDING       The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+5 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xFD04_Read_Function(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */ 
  Data[0] = DID_HomologationMode_NVM_param.U8_BYTE1;

  return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xFD05_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[in]     OpStatus            The operation status
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \return        DCM_E_PENDING       The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+3 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xFD05_Read_Function(
  Dcm_OpStatusType OpStatus,
/* polyspace < MISRA-C3:8.13 : Not a defect : Justify with annotations> A const pointer not possible here */
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  )
{
	Std_ReturnType retVal = E_OK;
	U8 U8_byteZero = 0;
#ifdef NFC_DIAGNOSTICS_PRESENT

	if (NfcFuncDiag_FD05_Nvm_Data.SPI_ErrorCounter_u8 >= ST_DIGIT_NFC_NVM_params.PAR_DIGIT_NFC_DEBOUCE_SPI_NOK)
	{
		U8_byteZero = U8_byteZero | SPI_ERROR_MASK;
	}
	else
	{
		/*do nothing*/
	}
	if (NfcFuncDiag_FD05_Nvm_Data.TRCV_ErrorCounter_u8 >= ST_DIGIT_NFC_NVM_params.PAR_DIGIT_NFC_DEBOUCE_TRCV_NOK)
	{
		U8_byteZero = U8_byteZero | TRCV_ERROR_MASK;
	}
	else
	{
		/*do nothing*/
	}
	if (NfcFuncDiag_FD05_Nvm_Data.OSC_ErrorCounter_u8 >= ST_DIGIT_NFC_NVM_params.PAR_DIGIT_NFC_DEBOUCE_OSC_NOK)
	{
		U8_byteZero = U8_byteZero | OSC_ERROR_MASK;
	}
	else
	{
		/*do nothing*/
	}
	if (NfcFuncDiag_FD05_Nvm_Data.AntShort_ErrorCounter_u8 >= ST_DIGIT_NFC_NVM_params.PAR_DIGIT_NFC_DEBOUCE_ANT_SHORT)
	{
		U8_byteZero = U8_byteZero | ANTSHORT_ERROR_MASK;
	}
	else
	{
		/*do nothing*/
	}
	if (NfcFuncDiag_FD05_Nvm_Data.AntOpen_ErrorCounter_u8 >= ST_DIGIT_NFC_NVM_params.PAR_DIGIT_NFC_DEBOUCE_ANT_OPEN)
	{
		U8_byteZero = U8_byteZero | ANTOPEN_ERROR_MASK;
	}
	else
	{
		/*do nothing*/
	}
	if (NfcFuncDiag_FD05_Nvm_Data.AntHeavDeTuned_ErrorCounter_u8 >= ST_DIGIT_NFC_NVM_params.PAR_DIGIT_NFC_DEBOUCE_ANT_HEAV_DETUNED)
	{
		U8_byteZero = U8_byteZero | ANT_HEAV_DETUNED_MASK;
	}
	else
	{
		/*do nothing*/
	}

	NfcFuncDiag_FD05_Nvm_Data.NFC_Diag_Error = U8_byteZero;
	
	Data[0]=NfcFuncDiag_FD05_Nvm_Data.NFC_Diag_Error;
	Data[1]=NfcFuncDiag_FD05_Nvm_Data.SPI_ErrorCounter_u8;
	Data[2]=NfcFuncDiag_FD05_Nvm_Data.TRCV_ErrorCounter_u8;
	Data[3]=NfcFuncDiag_FD05_Nvm_Data.OSC_ErrorCounter_u8;
	Data[4]=NfcFuncDiag_FD05_Nvm_Data.AntShort_ErrorCounter_u8;
	Data[5]=NfcFuncDiag_FD05_Nvm_Data.AntOpen_ErrorCounter_u8;
	Data[6]=NfcFuncDiag_FD05_Nvm_Data.AntHeavDeTuned_ErrorCounter_u8;
  	Data[7]=NfcFuncDiag_FD05_Nvm_Data.DebCnt_NFC_ANT_OPEN_u8;
  	Data[8]=NfcFuncDiag_FD05_Nvm_Data.DebCnt_NFC_ANT_SHORT_u8;
  	Data[9]=NfcFuncDiag_FD05_Nvm_Data.DebCnt_NFC_ANT_HEAV_DETUNED_u8;

#else
	Data[0]=U8_byteZero;
	Data[1]=U8_byteZero;
	Data[2]=U8_byteZero;
	Data[3]=U8_byteZero;
	Data[4]=U8_byteZero;
	Data[5]=U8_byteZero;
	Data[6]=U8_byteZero;
  	Data[7]=U8_byteZero;
  	Data[8]=U8_byteZero;
  	Data[9]=U8_byteZero;
	retVal = E_NOT_OK;
#endif

	return retVal;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xFD07_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+5 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xFD07_Read_Function(
    Dcm_OpStatusType OpStatus,
    P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data)
{
    Std_ReturnType returnVal = DCM_E_OK;
    if(Data != NULL)
    {
        Data[0u] = DID_HUF_Production_Date_NVM_param.U8_BYTE1;
        Data[1u] = DID_HUF_Production_Date_NVM_param.U8_BYTE2;
        Data[2u] = DID_HUF_Production_Date_NVM_param.U8_BYTE3;
        Data[3u] = DID_HUF_Production_Date_NVM_param.U8_BYTE4;
        Data[4u] = DID_HUF_Production_Date_NVM_param.U8_BYTE5;
        Data[5u] = DID_HUF_Production_Date_NVM_param.U8_BYTE6;
        Data[6u] = DID_HUF_Production_Date_NVM_param.U8_BYTE7;
        Data[7u] = DID_HUF_Production_Date_NVM_param.U8_BYTE8;
        Data[8u] = DID_HUF_Production_Date_NVM_param.U8_BYTE9;
        Data[9u] = DID_HUF_Production_Date_NVM_param.U8_BYTE10;
        Data[10u] = DID_HUF_Production_Date_NVM_param.U8_BYTE11;
        Data[11u] = DID_HUF_Production_Date_NVM_param.U8_BYTE12;
        Data[12u] = DID_HUF_Production_Date_NVM_param.U8_BYTE13;
        Data[13u] = DID_HUF_Production_Date_NVM_param.U8_BYTE14;
        Data[14u] = DID_HUF_Production_Date_NVM_param.U8_BYTE15;
    }
    else
    {
        returnVal = DCM_E_NOT_OK;
    }
    return returnVal;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0x0448_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0x0448_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    Data[0] = 4;  /* number of preconditions */
	Data[1]= 0x81;   /* blocking time for programmming active */
	Data[2]= 0x83;   /* maximum number of programming reached */
	Data[3]= 0x95;   /* Electricar drive readiness not off */
	Data[4]= 0x5;    /* vehicle speed > 5km/h */
	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xF18A_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+6 MISRA-C3:11.8 [Justified:Low] "Cast to type 'const void *' removes qualifiers is as expected." */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF18A_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){

    (void)memcpy((void *)&Data[0], (const void *)PDL.System_Supplier_Identifier, sizeof(PDL.System_Supplier_Identifier));

	return E_OK;
}
/***********************************************************************************************************************
 *  CanDiagUsr_0xF1D5_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF1D5_Read_Function(
    /* polyspace < MISRA-C3:8.13 : Not a defect : Justify with annotations> A const pointer not possible here */
    P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data)
{
  Data[0] = 0x01; /* Response does not include hash value (SWR_1201)*/
  Data[1] = 0x00; /* FDS project ID (SWR_1201) */
  Data[2] = 0x00; /* FDS project ID (SWR_1201) */
  Data[3] = 0x09; /* FDS project ID (SWR_1201) */
  Data[4] = 0x3A; /* FDS project ID (SWR_1201) */
  Data[5] = 0x00; /* Length of hash value - 0 byte (SWR_1201) */
  Data[6] = 0x00; /* Length of hash value - 0 byte (SWR_1201) */

  return E_OK;
}

/***********************************************************************************************************************
 *  DID_ReadByID_Test()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace <MISRA-C3:2.7, 8.13 : Not a defect : Justify with annotations >"Paremeter should be kept for future usage. A const pointer not possible here" */ /* polyspace < MISRA-C3:8.4: Not a defect : Justify with annotations > External Usage dependent on project setup*/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) DID_ReadByID_Test(
/* polyspace < MISRA-C3:8.13 : Not a defect : Justify with annotations> A const pointer not possible here */
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
	return E_OK;
}


/********************************************************************************
 *                   WRITE BY IDENTIFIER READ FUNCTIONS                    		*
 * ******************************************************************************/

/***********************************************************************************************************************
 *  CanDiagUsr_0xFD01_Write_Function()
 ***********************************************************************************************************************/
/*! \brief         Writes data element of a DID.
 *  \details       This function is a request from the DCM to the application to write in a DID. The concrete name of
 *                 the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataWriteFnc.
 *  \param[in]     Data           Data buffer
 *  \param[out]    ErrorCode      Negative response code
 *  \return        E_OK           The operation is finished
 *  \return        E_NOT_OK       The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+8 MISRA-C3:8.13 [Justified:Low] "A const pointer not possible here" */
/* polyspace+7 MISRA-C3:5.9 [Justified:Low] "variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace+5 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+3 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xFD01_Write_Function(
    P2CONST(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data,
    Dcm_OpStatusType OpStatus,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode
)
{
    static Std_ReturnType returnValue = E_OK;
    Std_ReturnType returnWriteNvMBlock = E_NOT_OK;
	NvM_RequestResultType NvMStatus;
	
    if (returnValue != DCM_E_PENDING)
    {
        returnWriteNvMBlock = NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_DID_Katek_EOL_Done, Data);
    }
    else
    {
        returnWriteNvMBlock = E_OK;
    }
    if (E_OK == returnWriteNvMBlock)
    {
        (void)NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_DID_Katek_EOL_Done, &NvMStatus);
        if (NVM_REQ_PENDING == NvMStatus)
        {
            returnValue = DCM_E_PENDING;
        }
        else
        {
            returnValue = E_OK;
            DID_Katek_EOL_Done_NVM_param.U8_BYTE1 = Data[0u];
            DID_Katek_EOL_Done_NVM_param.U8_BYTE2 = Data[1u];
        }
    }
    return returnValue;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xFD02_Write_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[in]     OpStatus            The operation status
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \return        DCM_E_PENDING       The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace <MISRA-C3:2.7, 5.9, 8.13 : Not a defect : Justify with annotations > "Paremeter should be kept for future usage. This identifier is static. A const pointer not possible here" */
/* polyspace+3 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xFD02_Write_Function(
  P2CONST(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data,
  Dcm_OpStatusType OpStatus,
/* polyspace <MISRA-C3:5.9 : Not a defect : Justify with annotations > Variable ErrorCode is static in Os_Stubs.c */
/* polyspace < MISRA-C3:8.13 : Not a defect : Justify with annotations> A const pointer not possible here */
	P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode
  ){
    /* polyspace:begin < MISRA-C3:17.8,17.7,18.4 : Not a defect : Justify with annotations> "This function does not modify the parameter." */
	static CanDiagUsr_WDBI_FD02_State WDBI_FD02_State = WDBI_FD02_IDLE;
	static uint8 Idx = 0u;
	NvM_RequestResultType NvmStatus = NVM_REQ_NOT_OK;
	Std_ReturnType RetVal = DCM_E_NOT_OK;

	/* Write UNLOCK sensor block in NVM, then update parameters in RAM  */
	if (WDBI_FD02_State == WDBI_FD02_IDLE)
	{
		Idx = 0u;  /* Reset data index */

		if ( NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_UNLOCK_SENSOR_BLOCK, &Data[Idx]) == E_OK )
		{
			WDBI_FD02_State = WDBI_FD02_UNLOCK_WRITING;
		}
		else
		{
			WDBI_FD02_State = WDBI_FD02_ERROR;
		}
	} else
	{
		/* Do nothing */
	}

	if (WDBI_FD02_State == WDBI_FD02_UNLOCK_WRITING)
	{
        (void)NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_UNLOCK_SENSOR_BLOCK, &NvmStatus);
        if (NvmStatus == NVM_REQ_OK)
        {
            (void)memcpy((void *)&ST_unlock_sensor_NVM_params, (const void *)&Data[Idx], sizeof(ST_unlock_sensor_NVM_params));
            Idx += (U8)sizeof(ST_unlock_sensor_NVM_params);
            WDBI_FD02_State = WDBI_FD02_UNLOCK_DONE;
        }
        else
        {
            if (NvmStatus != NVM_REQ_PENDING)
            {
                WDBI_FD02_State = WDBI_FD02_ERROR;
            }
			else
			{
				/*do nothing*/
			}
        }
	}
	else
	{
		/*do nothing*/
	}

	/* Write LOCK sensor block in NVM, then update parameters in RAM  */
	if (WDBI_FD02_State == WDBI_FD02_UNLOCK_DONE)
	{
		if ( NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_LOCK_SENSOR_BLOCK, &Data[Idx]) == E_OK )
		{
			WDBI_FD02_State = WDBI_FD02_LOCK_WRITING;
		}
		else
		{
			WDBI_FD02_State = WDBI_FD02_ERROR;
		}
	} else
	{
		/* Do nothing */
	}

	if (WDBI_FD02_State == WDBI_FD02_LOCK_WRITING)
	{
        (void)NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_LOCK_SENSOR_BLOCK, &NvmStatus);
        if (NvmStatus == NVM_REQ_OK)
        {
            (void)memcpy((void *)&ST_lock_sensor_NVM_params, (const void *)&Data[Idx], sizeof(ST_lock_sensor_NVM_params));
            Idx += (U8)sizeof(ST_lock_sensor_NVM_params);
            WDBI_FD02_State = WDBI_FD02_LOCK_DONE;
        }
        else
        {
            if (NvmStatus != NVM_REQ_PENDING)
            {
                WDBI_FD02_State = WDBI_FD02_ERROR;
            }
			else
			{
				/*do nothing*/
			}
        }
	}
	else
	{
		/*do nothing*/
	}

	/* Write INDUCTIVE sensor block in NVM, then update parameters in RAM  */
	if (WDBI_FD02_State == WDBI_FD02_LOCK_DONE)
	{
		if ( NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_INDUCTIVE_SENSOR_BLOCK, &Data[Idx]) == E_OK )
		{
			WDBI_FD02_State = WDBI_FD02_INDUCTIVE_WRITING;
		}
		else
		{
			WDBI_FD02_State = WDBI_FD02_ERROR;
		}
	} else 
	{
		/* Do nothing */
	}

	if (WDBI_FD02_State == WDBI_FD02_INDUCTIVE_WRITING)
	{
        (void)NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_INDUCTIVE_SENSOR_BLOCK, &NvmStatus);
        if (NvmStatus == NVM_REQ_OK)
        {
            (void)memcpy((void *)&ST_inductive_sensor_NVM_params, (const void *)&Data[Idx], sizeof(ST_inductive_sensor_NVM_params));
            Idx += (U8)sizeof(ST_inductive_sensor_NVM_params);
            WDBI_FD02_State = WDBI_FD02_INDUCTIVE_DONE;
        }
        else
        {
            if (NvmStatus != NVM_REQ_PENDING)
            {
                WDBI_FD02_State = WDBI_FD02_ERROR;
            }
        }
	}

	/* Write BATTERY SUPERVISOR block in NVM, then update parameters in RAM  */
	if (WDBI_FD02_State == WDBI_FD02_INDUCTIVE_DONE)
	{
		if ( NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_BATTERY_SUPERVISOR_BLOCK, &Data[Idx]) == E_OK )
		{
			WDBI_FD02_State = WDBI_FD02_BATTERY_WRITING;
		}
		else
		{
			WDBI_FD02_State = WDBI_FD02_ERROR;
		}
	} else
	{
		/* Do nothing */
	}

	if (WDBI_FD02_State == WDBI_FD02_BATTERY_WRITING)
	{
			NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_BATTERY_SUPERVISOR_BLOCK, &NvmStatus);
			if (NvmStatus == E_OK)
			{
				memcpy((void *)&ST_battery_supervisor_NVM_params, (const void *)&Data[Idx], sizeof(ST_battery_supervisor_NVM_params));
				Idx += (U8)sizeof(ST_battery_supervisor_NVM_params);
				WDBI_FD02_State = WDBI_FD02_BATTERY_DONE;
			}
			else
			{
				if (NvmStatus != NVM_REQ_PENDING)
				{
					WDBI_FD02_State = WDBI_FD02_ERROR;
				}
				else
				{
					/*do nothing*/
				}
			}
	}
	else
	{
		/*do nothing*/
	}

	/* Write EMERGENCY ACCESS block in NVM, then update parameters in RAM */
	if (WDBI_FD02_State == WDBI_FD02_BATTERY_DONE)
	{
		if ( NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_EMERGENCY_ACCESS_BLOCK, &Data[Idx]) == E_OK )
		{
			WDBI_FD02_State = WDBI_FD02_EMERGENCY_WRITING;
		}
		else
		{
			WDBI_FD02_State = WDBI_FD02_ERROR;
		}
	} else
	{
		/* Do nothing */
	}

	if (WDBI_FD02_State == WDBI_FD02_EMERGENCY_WRITING)
	{
        (void)NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_EMERGENCY_ACCESS_BLOCK, &NvmStatus);
        if (NvmStatus == NVM_REQ_OK)
        {
            (void)memcpy((void *)&ST_emergency_access_NVM_params, (const void *)&Data[Idx], sizeof(ST_emergency_access_NVM_params));
            Idx += (U8)sizeof(ST_emergency_access_NVM_params);
            WDBI_FD02_State = WDBI_FD02_EMERGENCY_DONE;
        }
        else
        {
            if (NvmStatus != NVM_REQ_PENDING)
            {
                WDBI_FD02_State = WDBI_FD02_ERROR;
			}
			else
			{
				/* Do nothing */
			}
		}
	}
	else
	{
		/* Do nothing */
	}

	/* Write spare block in NVM, then update parameters in RAM */
	if (WDBI_FD02_State == WDBI_FD02_EMERGENCY_DONE)
	{
		if ( NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_FD02_SPARE_BLOCK, &Data[Idx]) == E_OK )
		{
			WDBI_FD02_State = WDBI_FD02_SPARE_WRITING;
		}
		else
		{
			WDBI_FD02_State = WDBI_FD02_ERROR;
		}
	}

	if (WDBI_FD02_State == WDBI_FD02_SPARE_WRITING)
	{
        (void)NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_FD02_SPARE_BLOCK, &NvmStatus);
        if (NvmStatus == NVM_REQ_OK)
        {
            (void)memcpy((void*)&ST_FD02_spare_NVM_params, (const void*)&Data[Idx], sizeof(ST_FD02_spare_NVM_params));
            Idx += (U8)sizeof(ST_FD02_spare_NVM_params);
            WDBI_FD02_State = WDBI_FD02_SPARE_DONE;
        }
        else
        {
            if (NvmStatus != NVM_REQ_PENDING)
            {
                WDBI_FD02_State = WDBI_FD02_ERROR;
            }
        }
    }
    /* Send response (and reset state to idle if there is no pending work) */
    if (WDBI_FD02_State == WDBI_FD02_SPARE_DONE)  /* All done (last block written) -> positive response */
    {
        RetVal = DCM_E_OK;
        WDBI_FD02_State = WDBI_FD02_IDLE;
        EmergencyAccess_checkParameters();
    }
    else
    {
        if (WDBI_FD02_State ==  WDBI_FD02_ERROR)  /* NVM error -> negative response */
        {
            RetVal = DCM_E_NOT_OK;
            *ErrorCode = DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION;  /* Failure prevents execution of requested action */
            WDBI_FD02_State = WDBI_FD02_IDLE;
        }
        else
        {
            RetVal = DCM_E_PENDING;  /* Work (writing) in progress -> pending */
        }
    }
    return RetVal;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xFD03_Write_Function()
 ***********************************************************************************************************************/
/*! \brief         Writes data element of a DID.
 *  \details       This function is a request from the DCM to the application to write in a DID. The concrete name of
 *                 the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataWriteFnc.
 *  \param[in]     Data           Data buffer
 *  \param[in]     OpStatus       The operation status
 *  \param[out]    ErrorCode      Negative response code
 *  \return        E_OK           The operation is finished
 *  \return        E_NOT_OK       The operation has failed
 *  \return        DCM_E_PENDING  The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace <MISRA-C3:2.7, 5.9, 8.13 : Not a defect : Justify with annotations > "Paremeter should be kept for future usage. This identifier is static. A const pointer not possible here" */
/* polyspace+3 MISRA-C3:8.9 [Justified:Low] "Function is declared once here" */
/* polyspace+2 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
static Std_ReturnType returnWriteNvMBlock1 = E_NOT_OK;
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xFD03_Write_Function(
/* polyspace < MISRA-C3:8.13 : Not a defect : Justify with annotations> A const pointer not possible here */
/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
  P2CONST(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data,
  Dcm_OpStatusType OpStatus,
/* polyspace <MISRA-C3:5.9 : Not a defect : Justify with annotations > Variable ErrorCode is static in Os_Stubs.c */
/* polyspace < MISRA-C3:8.13 : Not a defect : Justify with annotations> A const pointer not possible here */
P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	static Std_ReturnType returnValue = E_OK;
  	Std_ReturnType returnWriteNvMBlock = E_NOT_OK;
  	if (returnValue != DCM_E_PENDING)
  	{
  	  returnWriteNvMBlock = NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_DID_Huf_EOL_Done, Data);
  	}
  	else
  	{
  	  returnWriteNvMBlock = E_OK;
  	}
	returnWriteNvMBlock1 = returnWriteNvMBlock;
  	NvM_RequestResultType NvMStatus;
  	if (E_OK == returnWriteNvMBlock)
  	{
  	  (void)NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_DID_Huf_EOL_Done, &NvMStatus);
  	  if (NVM_REQ_PENDING == NvMStatus)
  	  {
  	    returnValue = DCM_E_PENDING;
  	  }
  	  else
  	  {
  	    returnValue = E_OK;
  	    DID_Huf_EOL_Done_NVM_param.U8_BYTE1 = Data[0];
  	  }
	}
	else
	{
		/*do nothing*/
	}
	return returnValue;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xFD04_Write_Function()
 ***********************************************************************************************************************/
/*! \brief         Writes data element of a DID.
 *  \details       This function is a request from the DCM to the application to write in a DID. The concrete name of
 *                 the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataWriteFnc.
 *  \param[in]     Data           Data buffer
 *  \param[in]     OpStatus       The operation status
 *  \param[out]    ErrorCode      Negative response code
 *  \return        E_OK           The operation is finished
 *  \return        E_NOT_OK       The operation has failed
 *  \return        DCM_E_PENDING  The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace <MISRA-C3:2.7, 5.9, 8.13: Not a defect : Justify with annotations > "Paremeter should be kept for future usage. This identifier is static. A const pointer not possible here" */
/* polyspace+4 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xFD04_Write_Function(
/* polyspace < MISRA-C3:8.13 : Not a defect : Justify with annotations> A const pointer not possible here */
  P2CONST(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data,
  Dcm_OpStatusType OpStatus,
/* polyspace <MISRA-C3:5.9 : Not a defect : Justify with annotations > Variable ErrorCode is static in Os_Stubs.c */
/* polyspace < MISRA-C3:8.13 : Not a defect : Justify with annotations> A const pointer not possible here */
P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
  static Std_ReturnType returnValue = E_OK;
  Std_ReturnType returnWriteNvMBlock = E_NOT_OK;
  if (returnValue != DCM_E_PENDING)
  {
    returnWriteNvMBlock = NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_DID_NFC_Homologation_mode, Data);
  }
  else
  {
    returnWriteNvMBlock = E_OK;
  }
  NvM_RequestResultType NvMStatus;
  if (E_OK == returnWriteNvMBlock)
  {
    (void)NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_DID_NFC_Homologation_mode, &NvMStatus);
    if (NVM_REQ_PENDING == NvMStatus)
    {
      returnValue = DCM_E_PENDING;
    }
    else
    {
      returnValue = E_OK;
	  DID_HomologationMode_NVM_param.U8_BYTE1 = Data[0];
	}
  }
  else
  {
	  /*do nothing*/
  }
  return returnValue;
}


/***********************************************************************************************************************
 *  CanDiagUsr_0xFD07_Write_Function()
 ***********************************************************************************************************************/
/*! \brief         Writes data element of a DID.
 *  \details       This function is a request from the DCM to the application to write in a DID. The concrete name of
 *                 the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataWriteFnc.
 *  \param[in]     Data           Data buffer
 *  \param[out]    ErrorCode      Negative response code
 *  \return        E_OK           The operation is finished
 *  \return        E_NOT_OK       The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+8 MISRA-C3:8.13 [Justified:Low] "A const pointer not possible here" */
/* polyspace+7 MISRA-C3:5.9 [Justified:Low] "variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace+5 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+3 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xFD07_Write_Function(
    P2CONST(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data,
    Dcm_OpStatusType OpStatus,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode
)
{
    static Std_ReturnType returnValue = E_OK;
    Std_ReturnType returnWriteNvMBlock = E_NOT_OK;
	NvM_RequestResultType NvMStatus;
	
    if (returnValue != DCM_E_PENDING)
    {
        returnWriteNvMBlock = NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_DID_HUF_Production_Date, Data);
    }
    else
    {
        returnWriteNvMBlock = E_OK;
    }
    if (E_OK == returnWriteNvMBlock)
    {
        (void)NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_DID_HUF_Production_Date, &NvMStatus);
        if (NVM_REQ_PENDING == NvMStatus)
        {
            returnValue = DCM_E_PENDING;
        }
        else
        {
            returnValue = E_OK;
            DID_HUF_Production_Date_NVM_param.U8_BYTE1 = Data[0u];
            DID_HUF_Production_Date_NVM_param.U8_BYTE2 = Data[1u];
            DID_HUF_Production_Date_NVM_param.U8_BYTE3 = Data[2u];
            DID_HUF_Production_Date_NVM_param.U8_BYTE4 = Data[3u];
            DID_HUF_Production_Date_NVM_param.U8_BYTE5 = Data[4u];
            DID_HUF_Production_Date_NVM_param.U8_BYTE6 = Data[5u];
            DID_HUF_Production_Date_NVM_param.U8_BYTE7 = Data[6u];
            DID_HUF_Production_Date_NVM_param.U8_BYTE8 = Data[7u];
            DID_HUF_Production_Date_NVM_param.U8_BYTE9 = Data[8u];
            DID_HUF_Production_Date_NVM_param.U8_BYTE10 = Data[9u];
            DID_HUF_Production_Date_NVM_param.U8_BYTE11 = Data[10u];
            DID_HUF_Production_Date_NVM_param.U8_BYTE12 = Data[11u];
            DID_HUF_Production_Date_NVM_param.U8_BYTE13 = Data[12u];
            DID_HUF_Production_Date_NVM_param.U8_BYTE14 = Data[13u];
            DID_HUF_Production_Date_NVM_param.U8_BYTE15 = Data[14u];
        }
	}
	else
	{
		/*do nothing*/
	}
	return returnValue;
}


/***********************************************************************************************************************
 *  CanDiagUsr_0x05F0_Write_Function()
 ***********************************************************************************************************************/
/*! \brief         Writes data element of a DID.
 *  \details       This function is a request from the DCM to the application to write in a DID. The concrete name of
 *                 the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataWriteFnc.
 *  \param[in]     Data           Data buffer
 *  \param[out]    ErrorCode      Negative response code
 *  \return        E_OK           The operation is finished
 *  \return        E_NOT_OK       The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace< MISRA-C3:2.7, 5.9, 8.13 : Not a defect : Justify with annotations >"Paremeter should be kept for future usage. This identifier is static. A const pointer not possible here" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0x05F0_Write_Function(
/* polyspace < MISRA-C3:8.13 : Not a defect : Justify with annotations> A const pointer not possible here */
  P2CONST(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data,
/* polyspace <MISRA-C3:5.9 : Not a defect : Justify with annotations > Variable ErrorCode is static in Os_Stubs.c */
/* polyspace+1 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
  Dcm_OpStatusType OpStatus,
/* polyspace < MISRA-C3:8.13 : Not a defect : Justify with annotations> A const pointer not possible here */
/* polyspace+1 MISRA-C3:5.9 [Justified:Low] "variable ErrorCode is static from Os_Stubs.c is static" */
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	static Std_ReturnType returnValue = E_OK;
  Std_ReturnType returnWriteNvMBlock = E_NOT_OK;
  if (returnValue != DCM_E_PENDING)
  {
    returnWriteNvMBlock = NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_NFC_FS_debug_switch, Data);
  }
  else
  {
    returnWriteNvMBlock = E_OK;
  }
  NvM_RequestResultType NvMStatus;
  if (E_OK == returnWriteNvMBlock)
  {
    (void)NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_NFC_FS_debug_switch, &NvMStatus);
    if (NVM_REQ_PENDING == NvMStatus)
    {
      returnValue = DCM_E_PENDING;
    }
    else
    {
      returnValue = E_OK;
      DID_NFC_debugSwitch_NVM_param.U8_BYTE1 = Data[0];
    }
  }
  else
  {
	  /*do nothing*/
  }
  return returnValue;
}


/***********************************************************************************************************************
 *  CanDiagUsr_0xF187_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF187_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  ){
    /* polyspace MISRA-C3:17.8 [Justified:Unset] "This function does not modify the parameter." */
    /* polyspace < MISRA-C3:17.7 :  Not a defect : Justify with annotations > This function service is to copy the data of the NV block to its corresponding RAM block. Returned value is not needed. */
	Data[0]=PDL.VW_Spare_Part_Number[0];
	Data[1]=PDL.VW_Spare_Part_Number[1];
	Data[2]=PDL.VW_Spare_Part_Number[2];
	Data[3]=PDL.VW_Spare_Part_Number[3];
	Data[4]=PDL.VW_Spare_Part_Number[4];
	Data[5]=PDL.VW_Spare_Part_Number[5];
	Data[6]=PDL.VW_Spare_Part_Number[6];
	Data[7]=PDL.VW_Spare_Part_Number[7];
	Data[8]=PDL.VW_Spare_Part_Number[8];
	Data[9]=PDL.VW_Spare_Part_Number[9];
	Data[10]=PDL.VW_Spare_Part_Number[10];

	return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0x0600_Write_Function()
 ***********************************************************************************************************************/
/*! \brief         Writes data element of a DID.
 *  \details       This function is a request from the DCM to the application to write in a DID. The concrete name of
 *                 the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataWriteFnc.
 *  \param[in]     Data           Data buffer
 *  \param[in]     OpStatus       The operation status
 *  \param[out]    ErrorCode      Negative response code
 *  \return        E_OK           The operation is finished
 *  \return        E_NOT_OK       The operation has failed
 *  \return        DCM_E_PENDING  The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0x0600_Write_Function(
  P2CONST(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data,
  /* polyspace <MISRA-C3:5.9,8.13 : Not a defect : Justify with annotations > Variable ErrorCode is static from Os_Stubs.c is static */
  /* polyspace+1 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
  Dcm_OpStatusType OpStatus,
  /* polyspace+2 MISRA-C3:8.13 [Justified:Low] "A const pointer not possible here" */
  /* polyspace+1 MISRA-C3:5.9 [Justified:Low] "variable ErrorCode is static from Os_Stubs.c is static" */
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode
  ){
    /* polyspace < MISRA-C3:17.7 : Not a defect : Justify with annotations> Cast to void does not affect the functionality */
	static Std_ReturnType returnValue = E_OK;
  	Std_ReturnType returnWriteNvMBlock = E_NOT_OK;
  	if (returnValue != DCM_E_PENDING)
  	{
  	  returnWriteNvMBlock = NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_AUDI_PARAMS_BLOCK, Data);
  	}
  	else
  	{
  	  returnWriteNvMBlock = E_OK;
  	}
  	NvM_RequestResultType NvMStatus;
  	if (E_OK == returnWriteNvMBlock)
  	{
  	  (void)NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_AUDI_PARAMS_BLOCK, &NvMStatus);
  	  if (NVM_REQ_PENDING == NvMStatus)
  	  {
  	    returnValue = DCM_E_PENDING;
  	  }
  	  else
  	  {
        returnValue = E_OK;
        memcpy((void *)&ST_AUDI_NVM_params, (const void *)Data, sizeof(ST_AUDI_NVM_params));
        PlayProt_updateParameter();
      }
	}
	else
	{
		/*do nothing*/
	}
	return returnValue;
}

/***********************************************************************************************************************
 *  Diagnostic_Session_Change_Callback()
***********************************************************************************************************************/
/*! \brief         This function will be called at a diagnostic session state transition.
 *  \details       -
 *  \param[in]     formerState  Specifies the former diagnostic session ID (source state of transition)
 *  \param[in]     newState     Specifies the new diagnostic session ID (target state of transition)
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \note          The function argument values have the same definition as the ones returned by the API
 *                 Dcm_GetSesCtrlType().
***********************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
FUNC(void, DCM_CALLOUT_CODE) Diagnostic_Session_Change_Callback(Dcm_SesCtrlType formerState, Dcm_SesCtrlType newState)
{
    /* Reset TpBlockSize in case of transition to Default Session */
	if(newState == DEFAULT_SESSION)
    {
      BootloaderTPBlocksize = TP_BLOCK_SIZE_DEFAULT;
    }
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xFD06_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[in]     OpStatus            The operation status
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \return        DCM_E_PENDING       The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+5 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xFD06_Read_Function(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  )
  {
	  memcpy( (void *) Data, (const void *) &ST_TIME_NFC_DIAG_NVM_params, sizeof(ST_TIME_NFC_DIAG_NVM_params));
	  memcpy((void *)(Data + sizeof(ST_TIME_NFC_DIAG_NVM_params)), (const void *) &ST_DIGIT_NFC_NVM_params,     sizeof(ST_DIGIT_NFC_NVM_params));

	  return E_OK;
  }

/***********************************************************************************************************************
 *  CanDiagUsr_0xFD06_Write_Function()
 ***********************************************************************************************************************/
/*! \brief         Writes data element of a DID.
 *  \details       This function is a request from the DCM to the application to write in a DID. The concrete name of
 *                 the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataWriteFnc.
 *  \param[in]     Data           Data buffer
 *  \param[in]     OpStatus       The operation status
 *  \param[out]    ErrorCode      Negative response code
 *  \return        E_OK           The operation is finished
 *  \return        E_NOT_OK       The operation has failed
 *  \return        DCM_E_PENDING  The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+8 MISRA-C3:8.13 [Justified:Low] "A const pointer not possible here" */
/* polyspace+7 MISRA-C3:5.9 [Justified:Low] "variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace+6 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+3 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xFD06_Write_Function(
  P2CONST(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode
  )
{
    static Std_ReturnType returnValue_0 = E_NOT_OK;
    static Std_ReturnType returnValue_1 = E_NOT_OK;
    NvM_RequestResultType NvMStatus;
    Std_ReturnType returnValue;

    Std_ReturnType returnWriteNvMBlock = E_NOT_OK;
    if ((returnValue_0 != DCM_E_PENDING) && (returnValue_0 != E_OK))
    {
        returnWriteNvMBlock = NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_TIME_NFC_DIAG, Data);
    }
    else
    {
        returnWriteNvMBlock = E_OK;
    }
    if (E_OK == returnWriteNvMBlock)
    {
        (void)NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_TIME_NFC_DIAG, &NvMStatus);
        if (NVM_REQ_PENDING == NvMStatus)
        {
            returnValue_0 = DCM_E_PENDING;
        }
        else
        {
            returnValue_0 = E_OK;
            memcpy((void *)&ST_TIME_NFC_DIAG_NVM_params, (const void *)Data, sizeof(ST_TIME_NFC_DIAG_NVM_params));
        }
    }
	else
	{
		/*do nothing*/
	}
    
    if((returnValue_1 != DCM_E_PENDING) && (returnValue_1 != E_OK))
    {
        returnWriteNvMBlock = NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_DIGIT_NFC, Data + sizeof(ST_TIME_NFC_DIAG_NVM_params));
    }
    else
    {
        returnWriteNvMBlock = E_OK;
    }
    if (E_OK == returnWriteNvMBlock)
    {
        (void)NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_DIGIT_NFC, &NvMStatus);
        if (NVM_REQ_PENDING == NvMStatus)
        {
            returnValue_1 = DCM_E_PENDING;
        }
        else
        {
            returnValue_1 = E_OK;
            memcpy((void *)&ST_DIGIT_NFC_NVM_params, (const void *)(Data + sizeof(ST_TIME_NFC_DIAG_NVM_params)), sizeof(ST_DIGIT_NFC_NVM_params));
        }
    }
	else
	{
		/*do nothing*/
	}
    if((returnValue_0 == E_OK) && (returnValue_1 == E_OK))
    {
        returnValue = E_OK;
        returnValue_0 = E_NOT_OK;
        returnValue_1 = E_NOT_OK;
    }
    else 
    {
        if((returnValue_0 == DCM_E_PENDING) || (returnValue_1 == DCM_E_PENDING))
        {
            returnValue = DCM_E_PENDING;
        }
        else
        {
            returnValue = E_NOT_OK;
        }
    }
    return returnValue;
}


#if (DCM_DIAG_SERVICE_DISPATCHER_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_HandleServiceExtern()
 *********************************************************************************************************************/
/*! \brief         Returns the service implementation type for dispatching.
 *  \details        This call-out is used during service request processing, if the service is configured to be
 *                  dispatchable.
 *                  Note: This call-out is only invoked, if a DCM service handler has been configured accordingly.
 *  \param[in]      SID                   The service identifier of the request
 *  \param[in]      RequestData           The request data (behind SID byte)
 *  \param[in]      DataSize              The request data length
 *  \param[in]      ReqType               The request type (0 - physical, 1- functional)
 *  \param[in]      SourceAddress         The tester source address
 *  \return         TRUE              The service processing is done by the application
 *  \return         FALSE             The service processing is done by DCM
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         This function is only available if DCM_DIAG_SERVICE_DISPATCHER_ENABLED = STD_ON.
 *  \pre            -
 *********************************************************************************************************************/
FUNC(boolean, DCM_CALLOUT_CODE) Dcm_HandleServiceExtern(
  uint8 SID,
  Dcm_ReadOnlyMsgType RequestData,
  uint16 DataSize,
  uint8 ReqType,
  uint16 SourceAddress
  )
{

}
#endif
/***********************************************************************************************************************
 *  CanDiagUsr_CommControl0x28()
 ***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSidTabFnc.
 *  \param[in]     opStatus              The operation status
 *  \param[in,out] pMsgContext           Message-related information for one diagnostic protocol identifier
 *                                       The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode             Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK              Job processing finished, send positive response
 *  \return        DCM_E_PENDING         Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP     (Vendor extension) Forces a RCR-RP response.
 *                                       The call out will called again once the response is sent. The OpStatus
 *                                       parameter will contain the transmission result
 *  \return        DCM_E_PROCESSINGDONE  (Vendor extension) Can be returned instead of calling Dcm_ProcessingDone() for
 *                                       the current pMsgContext.
 *                                       Saves application code and stack usage.
 *  \return        DCM_E_STOP_REPEATER   Stops the repeater proxy
 *  \return        DCM_E_NOT_OK          Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+7 MISRA-C3:5.9 [Justified:Low] "variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace+12 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
/* polyspace+10 MISRA-C3:2.2 [Justified:Low] "kept here for the ease of code" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_CommControl0x28(
  Dcm_OpStatusType opStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodePtrType ErrorCode
  )
{
    Std_ReturnType returnVal =  DCM_E_OK;
    opStatus |= opStatus;
    uint8 u8SignalValue;
    uint8 *Data;
    static CanDiagUsr_comControlStateType CanDiagUsr_ComControlState28hex = CanDiagUsr_EnTxEnRx;
    U16 vehSpeed;
    BOOL nm_propulsionSystem = FALSE;


    if((ErrorCode != NULL) && (pMsgContext != NULL))
    {
		  if(((pMsgContext->reqDataLen == COMM_CTRL_STANDARD_REQUEST_LENGTH) || (pMsgContext->reqDataLen == COMM_CTRL_EXTENDED_REQUEST_LENGTH)) && ((vehSpeed < SPEED_HIGH_VALUE) && (vehSpeed > SPEED_LOW_VALUE))
      && (nm_propulsionSystem == FALSE))
		  {
		  	/* TODO add velocity and rpm conditions if needed
		  		   DCM_E_RPMTOOHIGH, DCM_E_VEHICLESPEEDTOOHIGH */
		  	Data = pMsgContext->reqData;
		  	/* comm and network type */
		  	if (Data[1] == 0x01)
		  	{
		  			switch (Data[0])
		  			{
		  			/* Q-LAH_80124-9922 */
		  			case DCM_ENABLE_RX_TX_NORM:
		  				Com_IpduGroupStart(ComConf_ComIPduGroup_CommunicationControlRx, TRUE);
		  				Com_IpduGroupStart(ComConf_ComIPduGroup_CommunicationControlTx, TRUE);
		  				CanDiagUsr_ComControlState28hex = CanDiagUsr_EnTxEnRx;
		  				break;
		  			case DCM_ENABLE_RX_DISABLE_TX_NORM:
		  				Com_IpduGroupStart(ComConf_ComIPduGroup_CommunicationControlRx, TRUE);
		  				Com_IpduGroupStop(ComConf_ComIPduGroup_CommunicationControlTx);
		  				CanDiagUsr_ComControlState28hex = CanDiagUsr_DisTxEnRx;
		  				break;
		  			case DCM_DISABLE_RX_ENABLE_TX_NORM:
		  				Com_IpduGroupStart(ComConf_ComIPduGroup_CommunicationControlTx, TRUE);
		  				Com_IpduGroupStop(ComConf_ComIPduGroup_CommunicationControlRx);
		  				CanDiagUsr_ComControlState28hex = CanDiagUsr_EnTxDisRx;
		  				break;
		  			case DCM_DISABLE_RX_TX_NORMAL:
		  				Com_IpduGroupStop(ComConf_ComIPduGroup_CommunicationControlTx);
		  				Com_IpduGroupStop(ComConf_ComIPduGroup_CommunicationControlRx);
		  				CanDiagUsr_ComControlState28hex = CanDiagUsr_DisTxDisRx;
		  				break;
		  			default:
		  				returnVal = DCM_E_NOT_OK;
		  				*ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
		  				break;
		  			}
		  			/* Control type */
		  			pMsgContext->resData[0] = (U8)CanDiagUsr_ComControlState28hex;
		  			pMsgContext->resDataLen = 0x01u;
		  	}
		  	else
		  	{
		  			returnVal = DCM_E_NOT_OK;
		  			*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
		  	}
		  	if ((returnVal != DCM_E_OK) && (CanDiagUsr_ComControlState28hex != CanDiagUsr_EnTxEnRx))
		  	{
		  			/* There is a precondition violation and resume Tx and Rx */
		  			Com_IpduGroupStart(ComConf_ComIPduGroup_CommunicationControlRx, TRUE);
		  			Com_IpduGroupStart(ComConf_ComIPduGroup_CommunicationControlTx, TRUE);
		  			/* Q-LAH_80124-10002 */
		  			CanDiagUsr_ComControlState28hex = CanDiagUsr_EnTxEnRx;
		  			/* Control type */
		  			pMsgContext->resData[0] = (U8)CanDiagUsr_ComControlState28hex;
		  			pMsgContext->resDataLen = 0x01u;
		  	}
		  	if (CanDiagUsr_ComControlState28hex != CanDiagUsr_EnTxEnRx)
		  	{
		  			u8SignalValue = 1u;
		  	}
		  	else
		  	{
		  			u8SignalValue = 0u;
		  	}
		  }
      else if ((vehSpeed > SPEED_HIGH_VALUE) || (vehSpeed < SPEED_LOW_VALUE))
      {
          returnVal = DCM_E_NOT_OK;
		  		*ErrorCode = DCM_E_VEHICLESPEEDTOOHIGH;
      }
      else if (nm_propulsionSystem == TRUE)
      {
          returnVal = DCM_E_NOT_OK;
          *ErrorCode = DCM_E_RPMTOOHIGH;
      }
		  else
		  {
		  	returnVal = DCM_E_NOT_OK;
              *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
		  }
	}
    return returnVal;
}


/***********************************************************************************************************************
 *  CanDiagUsr_0xF1A0_Write_Function()
 ***********************************************************************************************************************/
/*! \brief         Writes data element of a NvM_DID_VW_Data_Set_Number_Or_ECU_Data_Container_Number.
 *  \details       This function is a request from the DCM to the application to write in a DID. The concrete name of
 *                 the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataWriteFnc.
 *  \param[in]     Data           Data buffer
 *  \param[in]     OpStatus       The operation status
 *  \param[out]    ErrorCode      Negative response code
 *  \return        E_OK           The operation is finished
 *  \return        E_NOT_OK       The operation has failed
 *  \return        DCM_E_PENDING  The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace <MISRA-C3:2.7, 5.9, 8.13 : Not a defect : Justify with annotations > "Paremeter should be kept for future usage. This identifier is static. A const pointer not possible here" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF1A0_Write_Function(
  P2CONST(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data,
/* polyspace <MISRA-C3:5.9 : Not a defect : Justify with annotations > Variable ErrorCode is static in Os_Stubs.c */
/* polyspace < MISRA-C3:8.13 : Not a defect : Justify with annotations> A const pointer not possible here */
/* polyspace+3 MISRA-C3:5.9 [Justified:Low] "variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace+1 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
    Dcm_OpStatusType OpStatus,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode
  ){

    static tstAsynchWriteSts WriteSts = REQ_WRITE;
    Std_ReturnType retSts = DCM_E_PENDING;
    NvM_RequestResultType NvMStatus = E_NOT_OK;
	/* polyspace+10 MISRA-C3:16.3 [Not a defect:Low] "Intentionally not added !" */
	/* polyspace+10 MISRA-C3:16.1 [Not a defect:Low] "break not needed here" */
    switch (WriteSts){
        case REQ_WRITE:
            if (E_OK != NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_DID_VW_Data_Set_Number_Or_ECU_Data_Container_Number, Data)) {
                WriteSts = REQ_WRITE;
                *ErrorCode = DCM_E_GENERALREJECT;
                retSts = DCM_E_NOT_OK;
                break;
            } else {
                WriteSts = REQ_CHECK;
            }
            /* FALLTHROUGH */
        case REQ_CHECK:
            if (E_OK ==  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_DID_VW_Data_Set_Number_Or_ECU_Data_Container_Number, &NvMStatus))
            {
                if (NVM_REQ_PENDING == NvMStatus) { /* Do nothing, we're still wating for the result */}
                else if (NVM_REQ_OK == NvMStatus) {
                    memcpy((void*)&ST_DID_DataSetNr_NVM_params, (const void*)Data, sizeof(ST_DID_DataSetNr_NVM_params));
                    WriteSts = REQ_WRITE;
                    retSts = DCM_E_OK;
                } else {
                    WriteSts = REQ_WRITE;
                    *ErrorCode = DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION;
                    retSts = DCM_E_NOT_OK;
                }
            } else {
                WriteSts = REQ_WRITE;
                *ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
                retSts = DCM_E_NOT_OK;
            }
            break;
        default:
            WriteSts = REQ_WRITE;
            *ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
            retSts = DCM_E_NOT_OK;
            break;
    }
    return retSts;
}


/***********************************************************************************************************************
 *  CanDiagUsr_0xF1A1_Write_Function()
 ***********************************************************************************************************************/
/*! \brief         Writes data element of a DID.
 *  \details       This function is a request from the DCM to the application to write in a DID. The concrete name of
 *                 the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataWriteFnc.
 *  \param[in]     Data           Data buffer
 *  \param[in]     OpStatus       The operation status
 *  \param[out]    ErrorCode      Negative response code
 *  \return        E_OK           The operation is finished
 *  \return        E_NOT_OK       The operation has failed
 *  \return        DCM_E_PENDING  The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace <MISRA-C3:2.7, 5.9, 8.13 : Not a defect : Justify with annotations > "Paremeter should be kept for future usage. This identifier is static. A const pointer not possible here" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xF1A1_Write_Function(
  P2CONST(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data,
/* polyspace <MISRA-C3:5.9 : Not a defect : Justify with annotations > Variable ErrorCode is static in Os_Stubs.c */
/* polyspace < MISRA-C3:8.13 : Not a defect : Justify with annotations> A const pointer not possible here */
/* polyspace+4 MISRA-C3:5.9 [Justified:Low] "variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace+1 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
	Dcm_OpStatusType OpStatus,
	P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode
  ){


    static tstAsynchWriteSts WriteSts = REQ_WRITE;
    Std_ReturnType retSts = DCM_E_PENDING;
    NvM_RequestResultType NvMStatus = E_NOT_OK;
	/* polyspace+10 MISRA-C3:16.1 [Not a defect:Low] "break not needed here" */
	/* polyspace+5 MISRA-C3:16.3 [Not a defect:Low] "Intentionally not added !" */
    switch (WriteSts){
        case REQ_WRITE:
            if (E_OK != NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_DID_VW_Data_Set_Version_Number, Data)) {
                WriteSts = REQ_WRITE;
                *ErrorCode = DCM_E_GENERALREJECT;
                retSts = DCM_E_NOT_OK;
                break;
            } else {
                WriteSts = REQ_CHECK;
            }
            /* FALLTHROUGH */
        case REQ_CHECK:
            if (E_OK ==  NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_DID_VW_Data_Set_Version_Number, &NvMStatus))
            {
                if (NVM_REQ_PENDING == NvMStatus) { /* Do nothing, we're still wating for the result */}
                else if (NVM_REQ_OK == NvMStatus) {
                    memcpy((void*)&ST_DID_DataSetVersionNr_NVM_params, (const void*)Data, sizeof(ST_DID_DataSetVersionNr_NVM_params));
                    WriteSts = REQ_WRITE;
                    retSts = DCM_E_OK;
                } else {
                    WriteSts = REQ_WRITE;
                    *ErrorCode = DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION;
                    retSts = DCM_E_NOT_OK;
                }
            } else {
                WriteSts = REQ_WRITE;
                *ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
                retSts = DCM_E_NOT_OK;
            }
            break;
        default:
            WriteSts = REQ_WRITE;
            *ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
            retSts = DCM_E_NOT_OK;
            break;
    }
    return retSts;
}

/***********************************************************************************************************************
 *  CanDiagUsr_Routine_0x065E_ClearDowngradeProtection_Start()
 ***********************************************************************************************************************/
/*! \brief         Starts a routine execution.
 *  \details       This function is a request from DCM to the application to start a routine execution.
 *  \param[in]     OpStatus           The operation status
 *  \return        E_OK               The operation is finished
 *  \return        DCM_E_PENDING      The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  Forces a RCR-RP response
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        E_NOT_OK           The operation has failed. A concrete NRC shall be set, otherwise the DCM sends NRC
 *                                    0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+5 MISRA-C3:5.9 [Justified:Low] "variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_Routine_0x065E_ClearDowngradeProtection_Start(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode
  )
  {
	(void)OpStatus;
	*ErrorCode = DCM_E_OK;
	return DCM_E_OK;
  }

/***********************************************************************************************************************
 *  CanDiagUsr_0xFD13_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xFD13_Read_Function(
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  )
  {
    Data[0] = PlayProt_getActivationCounter(PlayProt_capaLock);
    Data[1] = PlayProt_getActiveState(PlayProt_capaLock);

    return E_OK;
  }

/***********************************************************************************************************************
 *  CanDiagUsr_0xFD42_Read_Function()
 ***********************************************************************************************************************/
/*! \brief         Reads the data element of the DID.
 *  \details       This function is a request from the DCM to the application to get a data value of a DID/PID. The
 *                 concrete name of the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataReadFnc.
 *  \param[in]     OpStatus            The operation status
 *  \param[out]    Data                Data buffer
 *  \return        E_OK                Read operation succeeded
 *  \return        E_NOT_OK            The operation has failed
 *  \return        DCM_E_PENDING       The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+5 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+2 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xFD42_Read_Function(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data
  )
{
    Data[0] = NVM_Sfd_Test_Mode_RAM;

    return E_OK;
}

/***********************************************************************************************************************
 *  CanDiagUsr_0xFD42_Write_Function()
 ***********************************************************************************************************************/
/*! \brief         Writes data element of a DID.
 *  \details       This function is a request from the DCM to the application to write in a DID. The concrete name of
 *                 the callout is defined by the configuration parameter
 *                 /Dcm/DcmConfigSet/DcmDsp/DcmDspData/DcmDspDataWriteFnc.
 *  \param[in]     Data           Data buffer
 *  \param[in]     OpStatus       The operation status
 *  \param[out]    ErrorCode      Negative response code
 *  \return        E_OK           The operation is finished
 *  \return        E_NOT_OK       The operation has failed
 *  \return        DCM_E_PENDING  The operation is not yet finished
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+7 MISRA-C3:5.9 [Justified:Low] "variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace+6 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+3 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CanDiagUsr_0xFD42_Write_Function(
  P2CONST(uint8, AUTOMATIC, DCM_VAR_NOINIT) Data,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode
  )
{
    static Std_ReturnType returnValue = E_OK;
    Std_ReturnType returnWriteNvMBlock = E_NOT_OK;
    NvM_RequestResultType NvMStatus;

    switch (Data[0])
    {
        /* SFD Test Mode Change */
        case SFD_TEST_MODE_INACTIVE:  /* 0x00 */
        case SFD_TEST_MODE_ACTIVE:    /* 0x01 */
        case SFD_TEST_MODE_DISABLED:  /* 0x02 */
            if (returnValue != DCM_E_PENDING)
            {
                returnWriteNvMBlock = NvM_WriteBlock(NvMConf_NvMBlockDescriptor_NvM_Sfd_Test_Mode, Data);
            }
            else
            {
                returnWriteNvMBlock = E_OK;
            }
            if (E_OK == returnWriteNvMBlock)
            {
                (void)NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_NvM_Sfd_Test_Mode, &NvMStatus);
                if (NVM_REQ_PENDING == NvMStatus)
                {
                    returnValue = DCM_E_PENDING;
                }
                else
                {
                    returnValue = E_OK;
                    NVM_Sfd_Test_Mode_RAM = Data[0];
                }
            }
            break;

        /* Emergency access actuation - value not written to NVM */
        case 0x04:
            if (NVM_Sfd_Test_Mode_RAM == 0x01)
            {
                EmergencyAccess_RequestSfdTestMode();
                returnValue = E_OK;
            }
            else
            {
                returnValue = E_NOT_OK;
                *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
            }
            break;

        /* LED Illumination - value not written to NVM */
        case 0x18:
        case 0x28:
        case 0x38:
        case 0x48:
        case 0x58:
        case 0x68:
        case 0x78:
        case 0x88:
        case 0x98:
        case 0xA8:
        case 0xB8:
        case 0xC8:
        case 0xD8:
        case 0xE8:
        case 0xF8:
            if (NVM_Sfd_Test_Mode_RAM == 0x01)
            {
                /* polyspace+2 MISRA-C3:10.8 [Justified:Low] "does not affect the functionality" */
                /* Activate LED for "high nibble x 200" ms */
                VA_LED_RequestDiag((U16)((Data[0] & (U8)0xF0u) >> 4u) * (U16)200u);
                returnValue = E_OK;
            }
            else
            {
                returnValue = E_NOT_OK;
                *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
            }
            break;

        /* Invalid request parameter */
        default:
            returnValue = E_NOT_OK;
            *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
            break;
	}

	return returnValue;
}
/***********************************************************************************************************************
 *  CAN_DiagUsr_CheckReprogrammingPreconditions()
 ***********************************************************************************************************************/
/*! \brief         Checks the reprorgramming preconditions if order to allow/disallow programming session request
 *  \details	   This functions allows the reset followed after 10 02 request
 *  \param[in]     resetAllowed   Status of resetAllowed
 *  \return        none
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE)
CAN_DiagUsr_CheckReprogrammingPreconditions(
    P2VAR(boolean, AUTOMATIC, DCM_VAR_NOINIT) resetAllowed)
{
  BOOL nm_propulsionSystem = FALSE;


  if ((BO_VehSpeedCondFulfilled == FALSE) || (nm_propulsionSystem == TRUE))
  {
    *resetAllowed = FALSE;
  }
  else
  {
    *resetAllowed = TRUE;
  }

  return E_OK;
}

/***********************************************************************************************************************
 *  CAN_DiagUsr_SupplierIndication()
 ***********************************************************************************************************************/
/*! \brief         Performs manufacturer/supplier specific validations on a diagnostic service request.
 *  \details       This function is a request from the DCM to the application to validate the received diagnostic
 *                 service, additionally to the DCM internal validation.
 *  \param[in]     SID                         Contains the diagnostic service Id
 *  \param[in]     RequestData                 Points to the request data. Points behind the service Id byte
 *  \param[in]     DataSize                    Specifies the requested data length (without the SID byte)
 *  \param[in]     ReqType                     Specifies the diagnostic request type:
 *                                             0 - physical request
 *                                             1 - functional request
 *  \param[in]     SourceAddress               Contains the diagnostic client source address
 *  \param[out]    ErrorCode                   NRC to be sent in the negative response in case of failure (E_NOT_OK)
 *  \return        E_OK                        The operation is finished
 *  \return        DCM_E_REQUEST_NOT_ACCEPTED  The diagnostic service shall not be processed.
 *                                             No response will be sent
 *  \return        E_NOT_OK                    The operation has failed
 *                                             A concrete NRC shall be set, otherwise the DCM sends NRC 0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+10 MISRA-C3:5.9 [Justified:Low] "variable ErrorCode is static from Os_Stubs.c is static" */
/* polyspace+9 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+5 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CAN_DiagUsr_SupplierIndication(
  uint8 SID,
  P2CONST(uint8, AUTOMATIC, DCM_VAR_NOINIT) RequestData,
  uint16 DataSize,
  uint8 ReqType,
  uint16 SourceAddress,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode
  )
{
  Std_ReturnType retVal = E_OK;
  boolean resetAllowed_b = TRUE;

  switch (SID) /* Specific preconditions to be cheked for each SID */
  {
    case 0x10:
      if (RequestData[0u] == 0x02u) /* Programming Session request */
      {
        /* Check if the programming preconditions are met */
        CAN_DiagUsr_CheckReprogrammingPreconditions(&resetAllowed_b);

        if (FALSE == resetAllowed_b)
        {
          /* The precodntitions are not met -> negative response to programming session request */
          *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
          retVal = E_NOT_OK;
        }
        else
        {
          /* Preconditions are met -> copy bootloader relevant information to reset safe RAM */
          (void)memcpy(&Diag__EepData_AU8[DIAG__EEP_PROG_ATTEMPTS_ADDR], AU8_NVM_AswProgAttemtsCnt, sizeof(AU8_NVM_AswProgAttemtsCnt));
          (void)memcpy(&Diag__EepData_AU8[DIAG__EEP_FINGERPRINT_ADDR], AU8_NVM_Fingerprint, sizeof(AU8_NVM_Fingerprint));
          Diag__EepData_AU8[DIAG__EEP_TP_BLOCK_SIZE] = BootloaderTPBlocksize;
          Diag__EepData_AU8[DIAG__EEP_TP_BLOCK_SIZE_ACTIVE] = TP_BLOCK_SIZE_ACTIVE;
        }
      }
      break;

    case 0x85:
      if (BO_VehSpeedCondFulfilled == FALSE)
      {
        *ErrorCode = 0x88; /* VehicleSpeedTooHigh */
        retVal = E_NOT_OK;
      }
      break;

    default:
      /*do nothing*/
      break;
  }

  /* Indicate that a diag request is ongoing */
  if(SID != 0x10)
  {
    BO_ActiveDiag = TRUE;
    U16_DiagSesCounter = 0;
  }

  return retVal;
}
/***********************************************************************************************************************
 *  CAN_DiagUsr_SupplierConfirmation()
 ***********************************************************************************************************************/
/*! \brief         Finishes manufacturer specific actions on a diagnostic service request.
 *  \details       This function is a notification from the DCM to the application that a diagnostic service processing
 *                 is finished.
 *  \param[in]     SID                 Contains the diagnostic service Id
 *  \param[in]     ReqType             Specifies the diagnostic request type:
 *                                     0 - physical request
 *                                     1 - functional request
 *  \param[in]     SourceAddress       Contains the diagnostic client source address
 *  \param[in]     ConfirmationStatus  Contains the response transmission resp. diagnostic response type
 *  \return        E_OK                The operation is finished
 *  \return        E_NOT_OK            The operation has failed. Has no effect on DCM.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 ***********************************************************************************************************************/
/* polyspace+6 MISRA-C3:2.7 [Justified:Low] "Added for further implementation." */
/* polyspace+3 MISRA-C3:D4.5 [Justified:Low] "No overlapping visibility" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) CAN_DiagUsr_SupplierConfirmation(
  uint8 SID,
  uint8 ReqType,
  uint16 SourceAddress,
  Dcm_ConfirmationStatusType ConfirmationStatus
  )
  {
	switch(SID)
	{
		case 0x14:
			DemDtc_ClearDTCInformationActions();
		break;
		/* polyspace+3 MISRA-C3:2.2 [Not a defect:Low] "kept here for the ease of code" */
		case 0x10:
			ConfirmationStatus = E_OK;
		break;

		default:
		 /*do nothing*/
		break;
	}

    /*  Reset Counter   */
    U16_DiagSesCounter = 0;
    BO_ActiveDiag = TRUE;
    
    return E_OK;
  }


/*********************************************************************************************************
 *  Name                   : CAN_DiagUsr_0x06A8_ResetHealInhStatus
 *  Description            : Routine 0x6A8 - Reset healing inhibition status  
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
/* polyspace+5 MISRA-C3:5.9 [Justified:Low] "variable ErrorCode is static from Os_Stubs.c is static" */
Std_ReturnType CAN_DiagUsr_0x06A8_ResetHealInhStatus(
      uint8 DataIn,
      P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) DataOut,
      P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode)
{
  Std_ReturnType retVal = E_OK;
  
  /* Check for input parameter */
  if(DataIn == 0u)
  {
      /* Set the reset healing inhibition global status to TRUE */
      BO_ResetHealInhStatus = TRUE;

      /* Healinh inhibition status is reset */
      *DataOut = 1u;

      /* Set ErrorCode with E_OK */
      *ErrorCode = E_OK;
  }
  else
  {
      /* Invalid input parameter */
      retVal = E_NOT_OK;
      *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }

  return retVal;
}

/*********************************************************************************************************
 *  Name                   : CANDiagUsr_CyclicTask
 *  Description            : Cyclic task for CAN_DiagUsr 
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
void CANDiagUsr_CyclicTask(void)
{   
    /* polyspace+1 MISRA-C3:5.8 [Justified:Low] "this variable is used inside the function only" */
    S_NM_NORMAL_OP_FLAGS S_NORMAL_OP_Request;
    static U8 ActiveKlemme15_Prev = 0u;

    S_NORMAL_OP_Request = CANAPP_get_Normal_OP_Request();
    /* Edge detection KL15 off -> on */
    if ((ActiveKlemme15_Prev == 0u) && (S_NORMAL_OP_Request.u8ActiveKlemme_15 == 1u))
    {
        Dcm_ResetToDefaultSession();
    }
    ActiveKlemme15_Prev = S_NORMAL_OP_Request.u8ActiveKlemme_15;
}

/*********************************************************************************************************
 *  Name                   : ResetSecAccBlockedFlag_after10Min
 *  Description            : If Security Access Blocked Flag reset it in 10 minutes
 *  Parameters             : none
 *  Return                 : none
 *********************************************************************************************************/
void Reset_SecAccBlockedFlag_after10Min(void)
{
  static uint16 counter_10minutes = 0;
  // if flag was activated in FBL after 10 minutes will be reset in APPL
  //  NOTE: we do not know how much it passed in FBL before jumping to APPL
  if(Diag__EepData_AU8[DIAG__EEP_SEC_ACC_DELAY_ADDR] == KEEP_SEC_ACCESS_DELAY_ACTIVE)
  {
    counter_10minutes++;
    if(TEN_MINUTES_COUNT_100MS_TASK <= counter_10minutes)
    {
      Diag__EepData_AU8[DIAG__EEP_SEC_ACC_DELAY_ADDR] = 0xFF;
      counter_10minutes = 0;
    }
  }
  else
  {
    /* do nothing*/
  }
}
