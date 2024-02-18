/* polyspace+1 MISRA-C3:1.1 [Justified:Low] "All macro definitions are needed." */
/*------------------------------------------------------------------------------------------------+
| File: LDC3114.c                                                                                 |
+-------------------------------------------------------------------------------------------------+
| Project: Audi eTab                                                                              |
+-------------------------------------------------------------------------------------------------+
| Short description: The file contains the implementation of the LDC3114 driver                   |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
+-------------------------------------------------------------------------------------------------+
| for Information, to do:                                                                         |
|                                                                                                 |
|                                                                                                 |
+-------------------------------------------------------------------------------------------------+
| $Revision::                                                                                  $: |
| $Date::                                                                                      $: |
| $Author::                                                                                    $: | 
| $URL::                                                                                       $: |
|                                                                                                 |
+------------------------------------------------------------------------------------------------*/
/* polyspace+1 MISRA-C3:2.5 [Justified:Low] "Macro should be kept for future usage" */
#define LDC3114_C_
/* Used interfaces from other modules */
#include "Platform_Types.h"
#include "Dio.h"
#include "inductive_sensor_algo.h"
#include "CDD_I2c.h"
#include "Icu.h"
#include "Gpt.h"
#include "BatterySupervisor.h"
#include "Dem_Dtc.h"
#include "EcuM.h"
/* Provide interface */
/* ----------------- */
#include "LDC3114.h"
#include "NvmMng.h"
#include "Port.h"
#include "S32K144.h"
#include "StdRegMacros.h"
#include "Reg_eSys_LPI2C.h"
/* Private functions, macros, types and data */
#define U32_IIR_WARME_UP_CONSTANT       ((U32)700000u)
#define U32_IIR_WARME_UP_CONSTANT_NOISE ((U32)1024u)
#define U8_LDC3114_FILTER_FILL_LOOP     ((U8) 6u)
#define LDC3114_U16_NOISE_THRESHOLD     ((U16)750u)
/* polyspace+1 MISRA-C3:2.5 [Justified:Low] "kept for future usage" */
#define LPI2C0_MCR                      ((uint32)0x40066010)
/* ---------------------------------------------------- */
/* Public variables */
TASK_LDC3114_VAR_T LDC3114_Sensor_Var_Str[LDC3114_SENSOR_MAX];
/* ---------------------------------------------------- */
/* Private data-types */

typedef enum
{
    LDC3114__E_RESET_MODE = 0u,
    LDC3114__E_STARTING_UP_MODE,
    LDC3114__E_CONFIG_MODE,
    LDC3114__E_RUNNING_MODE
} LDC3114__Enum_LdcInternalStatesType;


static LDC3114__Enum_LdcInternalStatesType   LDC3114__EN_InternalState;

/* Private functions declaration */
static void LDC3114__InternalStatesHandler(void);
static void LDC3114__ReadRegister(U8 U8_RegisterStartAddress, U8* PU8_RegisterData, U8 U8_DataLength);
static void LDC3114__EnableRegisterWrite(void);
static void LDC3114__DisableRegisterWrite(void);
static void LDC3114__WriteRegister(U8 U8_RegisterStartAddress, U8* PU8_RegisterData, U8 U8_NumberOfRegisters);
static void LDC3114__ResetLdc(void);
static BOOL LDC3114__LdcConfigurationValidityOk(void);
static BOOL LDC3114__LdcReadyAfterInternalReset(void);
static BOOL LDC3114__LdcRegistersReadyForWrite(void);
static void LDC3114_mcvd_init(void);

/* debug vars */
#define DEBUG_BUFFER_SIZE 1
#define CHECK_LDC_CONFIG_SAMPLES_NO 49
static U8 U8_Index = 0U;
volatile U8 AU8_DataReceived[DEBUG_BUFFER_SIZE][10U];
static U8 U8_noOfTasksWithoutLDC = 0U;
static U8 U8_resetFlag = 0U;
LDC3114_Sync_T LDC3114_SyncTimeout = {
    (U8)0,
    (U8)0
};
U8 U8_Positives_Values = 0U;
volatile U32 U32_LDC_Remaining_Time = 0U;
U8 bLdcIsrTriggered = LDC_INTERRUPT_FIRST_TIME;
U32 Ch0_NoiseMeasVal = 0u;
U32 Ch1_NoiseMeasVal = 0u;

/*********************************************************************************************************
 *  Name                   : LDC3114_Init
 *  Description            : This function initializes LDC3114 module after reset
 *                         :
 *  Parameters             : void
 *  Return                 : void
 *  Critical/explanation   : -
 *   Author                : mficea
 *********************************************************************************************************/
void LDC3114_Init(void)
{
    Icu_EnableNotification(IcuChannel_LDC_INTB_Interrupt);
    LDC3114__EN_InternalState = LDC3114__E_RESET_MODE;
    U8_Positives_Values = (U8)0;
    LDC3114_mcvd_init();
}

U8 LDC3114_getStatusByte(void) {
    return (U8) AU8_DataReceived[0u][0u];
}

/*********************************************************************************************************
 *  Name                   : LDC3114_CyclicTask
 *  Description            : LDC3114 Periodic Task
 *                         :
 *  Parameters             : void
 *  Return                 : void
 *  Critical/explanation   : -
 *   Author                : mficea
 *********************************************************************************************************/
/* polyspace < MISRA-C3:8.5,8.3: Not a defect : Justify with annotations > LDC3114_CyclicTask is declared once in LDC3114.hi file */
void LDC3114_CyclicTask(void)
{
    LDC3114__InternalStatesHandler();
}

/*********************************************************************************************************
 *  Name                   : LDC3114__InternalStatesHandler
 *  Description            : This handles LDC3114 internal states for starting up
 *                         :
 *  Parameters             : void
 *  Return                 : void
 *  Critical/explanation   : -
 *   Author                : mficea
 *********************************************************************************************************/
static void LDC3114__InternalStatesHandler(void)
{
    /* polyspace < CERT-C:CON43-C : Not a defect : Justify with annotations > No concurrency on this structure */
    static U8 U8_Counter = CHECK_LDC_CONFIG_SAMPLES_NO;
    
    /* polyspace:begin < MISRA-C3:16.1 : Not a defect : Justify with annotations > " */
    switch(LDC3114__EN_InternalState)
    {
        case LDC3114__E_RESET_MODE:

            if( LDC3114__LdcReadyAfterInternalReset() == (BOOL)TRUE )
            {
                LDC3114__EN_InternalState = LDC3114__E_STARTING_UP_MODE;
            }
            else{/* Wait LDC to settle after Reset */}
            break;
	    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
        case LDC3114__E_STARTING_UP_MODE:

            if(LDC3114__LdcConfigurationValidityOk() == (BOOL)FALSE)
            {
                LDC3114__EN_InternalState = LDC3114__E_CONFIG_MODE;
                /* polyspace < MISRA-C3:2.2 : Not a defect : Justify with annotations > Should be kept for future usage */
				LDC3114__EnableRegisterWrite();
            }
            else
            {
                LDC3114__EN_InternalState = LDC3114__E_RUNNING_MODE;
            }
            break;
	    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
        case LDC3114__E_CONFIG_MODE:

            if (LDC3114__LdcRegistersReadyForWrite() == (BOOL)TRUE)
            {
                /* Write LDC config registers
                 * TODO mficea: investigate duration. Maybe a new state should be added */
                /* polyspace<MISRA-C3:11.8 : Not a defect : Justify with annotations > Cast checked by developer*/
		/* polyspace < MISRA-C3:2.2 : Not a defect : Justify with annotations > Should be kept for future usage */
                LDC3114__WriteRegister(LDC3114__ACU8_LdcConfigurationRegValues[0U], (U8*)&LDC3114__ACU8_LdcConfigurationRegValues[1U], LDC3114__NUMBER_OF_REGISTERS_TO_CONFIG);
                /* polyspace < MISRA-C3:2.2 : Not a defect : Justify with annotations > Should be kept for future usage */
                LDC3114__DisableRegisterWrite();
                LDC3114__EN_InternalState = LDC3114__E_RUNNING_MODE;
            }
            else{/* Wait LDC to be Write ready */}
            break;
	    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
        case LDC3114__E_RUNNING_MODE:
            /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
            if (bLdcIsrTriggered == LDC_INTERRUPT_FIRST_TIME)
            {
                /* polyspace+1 MISRA-C3:11.8 [Justified:Low] "the result is as expected" */
                LDC3114__ReadRegister(LDC3114_REG_ADDR_STATUS_REG, (U8 *) &AU8_DataReceived[U8_Index][0], 2U);
            }
            else
            {
                /*do nothing*/
            }
            if((LDC_INTERRUPT_WAIT != bLdcIsrTriggered)&&(LDC_INTERRUPT_FIRST_TIME != bLdcIsrTriggered))
            /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
            {
                    /* Check LDC configuration validity every 50xLDC cyclic task period */
                if(U8_Counter == 0U)
                {
                    U8_Counter = CHECK_LDC_CONFIG_SAMPLES_NO;
                    
                    if(LDC3114__LdcConfigurationValidityOk() == (BOOL)FALSE)
                    {
                        LDC3114__ResetLdc();
                        LDC3114__EN_InternalState = LDC3114__E_RESET_MODE;
                    }
                    else {/* LDC registers config valid */}
                    
                }
                else
                {
                    U8_Counter--;
                }
                
                SuspendAllInterrupts();
                /* polyspace+2 MISRA-C3:11.8 [Justified:Low] "the result is as expected" */
                LDC3114__ReadRegister(LDC3114_REG_ADDR_STATUS_REG, (U8 *) &AU8_DataReceived[U8_Index][0], 2U);
                LDC3114__ReadRegister(LDC3114_REG_ADDR_RAW_DATA0_3, (U8 *) &AU8_DataReceived[U8_Index][2], 6U);
                ResumeAllInterrupts();

                LDC3114_GetSensorsData();
                Inductive_Sensor_Algo();
            }
            else
            {
                /*do nothing*/
            }
            /* polyspace < RTE:OVFL : Not a defect : Justify with annotations >"The index is not outside of the boundaries and the operation will not result into an overflow." */
            U8_Index++;
	    /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
            if(U8_Index >= DEBUG_BUFFER_SIZE)
            {
                U8_Index = 0U;
            }
            else
            {
                /*do nothing*/
            }

            /* Copy status register to a global variable */
            U8_LDC_StatusReg = AU8_DataReceived[U8_Index][0];

            break;
	/* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
        default:
            if (LDC3114__LdcConfigurationValidityOk() == (BOOL)FALSE)
            {
                LDC3114__EN_InternalState = LDC3114__E_CONFIG_MODE;
                /* polyspace < MISRA-C3:2.2 : Not a defect : Justify with annotations > Should be kept for future usage */
                LDC3114__EnableRegisterWrite();
            }
            else
            {
                LDC3114__EN_InternalState = LDC3114__E_RUNNING_MODE;
            }
            break;
   }
     /* polyspace:end < MISRA-C3:16.1 : Not a defect : Justify with annotations > " */
}

/*********************************************************************************************************
 *  Name                   : LDC3114__ReadRegister
 *  Description            : This function read data via I2C interface from LDC 3114 registers
 *                         :
 *  Parameters             : U8 U8_RegisterStartAddress - Register start address
 *                         : U8* PU8_RegisterData - Address where to put read data
 *                         : U8_DataLength - number of registers to be read
 *  Return                 : void
 *  Critical/explanation   : -
 *   Author                : mficea
 *********************************************************************************************************/
/* polyspace < MISRA-C3:8.13: Not a defect : Justify with annotations > A const pointer not possible here */
static void LDC3114__ReadRegister(U8 U8_RegisterStartAddress, U8* PU8_RegisterData, U8 U8_DataLength)
{

    I2c_RequestType S_ReadReg;
    I2c_RequestType S_WriteReg;

    /*configure the write register*/
    S_WriteReg.SlaveAddress = LDC3114__DEVICE_I2C_BUS_ADDRESS << 1;
    S_WriteReg.b10BitsSlaveAddressSize = FALSE;
    S_WriteReg.bHighSpeedMode = FALSE;
    S_WriteReg.bExpectNack = FALSE;
    /* polyspace < MISRA-C3:17.8 : Not a defect : Justify with annotations > U8_RegisterStartAddress ends its purpose in this function*/
    S_WriteReg.pDataBuffer = &U8_RegisterStartAddress;
    S_WriteReg.u8BufferSize = 1U;
    S_WriteReg.eDataDirection = I2C_SEND_DATA;
    (void)I2c_SyncTransmit(I2cConf_I2cChannelConfiguration_I2cChannel, &S_WriteReg);

    /*configure the read register*/
    S_ReadReg.SlaveAddress = ((LDC3114__DEVICE_I2C_BUS_ADDRESS << 1) | 1U);
    S_ReadReg.b10BitsSlaveAddressSize = FALSE;
    S_ReadReg.bHighSpeedMode = FALSE;
    S_ReadReg.bExpectNack = FALSE;
    S_ReadReg.pDataBuffer = PU8_RegisterData;
    S_ReadReg.u8BufferSize = U8_DataLength;
    S_ReadReg.eDataDirection = I2C_RECEIVE_DATA;

    /*read data via I2C*/
    (void)I2c_SyncTransmit(I2cConf_I2cChannelConfiguration_I2cChannel, &S_ReadReg);
}


/*********************************************************************************************************
 *  Name                   : LDC3114__EnableRegisterWrite
 *  Description            : This function set Config Mode flag in Reset register for enabling
 *                         : write for all LDC registers
 *                         :
 *  Parameters             : void
 *  Return                 : void
 *  Critical/explanation   : -
 *   Author                : mficea
 *********************************************************************************************************/
static void LDC3114__EnableRegisterWrite(void)
{

    I2c_RequestType S_WriteEnReg;
    U8 U8_DataToTransmit[2] = {LDC3114_REG_ADDR_RESET_REG, LDC3114_RESET_CONFIG_MODE_MASK};

    /*configure the write register*/
    S_WriteEnReg.SlaveAddress = LDC3114__DEVICE_I2C_BUS_ADDRESS << 1;
    S_WriteEnReg.b10BitsSlaveAddressSize = FALSE;
    S_WriteEnReg.bHighSpeedMode = FALSE;
    S_WriteEnReg.bExpectNack = FALSE;
    S_WriteEnReg.pDataBuffer = U8_DataToTransmit;
    S_WriteEnReg.u8BufferSize = 2u;
    S_WriteEnReg.eDataDirection = I2C_SEND_DATA;

    /*transmit data via I2C*/
    (void)I2c_SyncTransmit(I2cConf_I2cChannelConfiguration_I2cChannel, &S_WriteEnReg);

}

/*********************************************************************************************************
 *  Name                   : LDC3114__DisableRegisterWrite
 *  Description            : This function clear Config Mode flag in Reset register for disabling
 *                         : write for all LDC registers
 *                         :
 *  Parameters             : void
 *  Return                 : void
 *  Critical/explanation   : -
 *   Author                : mficea
 *********************************************************************************************************/
static void LDC3114__DisableRegisterWrite(void)
{
    I2c_RequestType request;
    U8 U8_DataToTransmit[2] = {LDC3114_REG_ADDR_RESET_REG, 0x00u};

    request.SlaveAddress = LDC3114__DEVICE_I2C_BUS_ADDRESS<<1;
    request.b10BitsSlaveAddressSize = FALSE;
    request.bHighSpeedMode = FALSE;
    request.bExpectNack = FALSE;
    request.pDataBuffer = U8_DataToTransmit;
    request.u8BufferSize = 2u;
    request.eDataDirection = I2C_SEND_DATA;
    (void)I2c_SyncTransmit(I2cConf_I2cChannelConfiguration_I2cChannel, &request);
}


/*********************************************************************************************************
 *  Name                   : LDC3114__WriteRegister
 *  Description            : This function write data via I2CS interface into LDC 3114 registers
 *                         :
 *  Parameters             : U8 U8_RegisterStartAddress - Register start address
 *                         : U8* PU8_RegisterData - Address from where to take data to be written
 *                         : U8_NumberOfRegisters - number of registers to be written
 *  Return                 : void
 *  Critical/explanation   : -
 *   Author                : mficea
 *********************************************************************************************************/
/* polyspace < MISRA-C3:8.13: Not a defect : Justify with annotations > A const pointer not possible here */
static void LDC3114__WriteRegister(U8 U8_RegisterStartAddress, U8* PU8_RegisterData, U8 U8_NumberOfRegisters)
{
    I2c_RequestType request;

    U8 AU8_DataToTransmit[51];
    const U8 U8_DataLength = U8_NumberOfRegisters + 1u;
    AU8_DataToTransmit[0] = U8_RegisterStartAddress;

    for(U8 U8_LoopIndex = 1; U8_LoopIndex < U8_DataLength; U8_LoopIndex++)
    {
       AU8_DataToTransmit[U8_LoopIndex] = PU8_RegisterData[U8_LoopIndex - 1u];
    }

    /*configure the request*/
    request.SlaveAddress = LDC3114__DEVICE_I2C_BUS_ADDRESS << 1;
    request.b10BitsSlaveAddressSize = FALSE;
    request.bHighSpeedMode = FALSE;
    request.bExpectNack = FALSE;
    request.pDataBuffer = AU8_DataToTransmit;
    request.u8BufferSize = U8_DataLength;
    request.eDataDirection = I2C_SEND_DATA;

    /*transmit request for write via I2C*/
    (void)I2c_SyncTransmit(I2cConf_I2cChannelConfiguration_I2cChannel, &request);
}


/*********************************************************************************************************
 *  Name                   : LDC3114_SetLdcPowerMode
 *  Description            : Function for setting LDC 3114 power mode
 *                         :
 *  Parameters             : LDC3114_Enum_LdcPowerModesType EN_PowerMode - requested power mode
 *  Return                 : LDC3114_Enum_CommandStatusType - command status
 *  Critical/explanation   : -
 *   Author                : mficea
 *********************************************************************************************************/
/* polyspace<MISRA-C3:8.7: Not a defect : Justify with annotations > External Usage dependent on project setup*/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Parameter hould be kept for future usage */
extern LDC3114_Enum_CommandStatusType LDC3114_SetLdcPowerMode(LDC3114_Enum_LdcPowerModesType EN_PowerMode)
{
    LDC3114_Enum_CommandStatusType EN_Commandresult = LDC3114_E_COMMAND_NOT_ACCEPTED;

    /* reset flag for counting tasks without LDC */
    U8_noOfTasksWithoutLDC = 0U;

    if(LDC3114__EN_InternalState == LDC3114__E_RUNNING_MODE)
    {
        if(EN_PowerMode == LDC3114_E_NORMAL_POWER)
        {
            /* read register to clear INTB pin used for LDC interrupt */
            /* placed near Dio_WriteChannel to minimize the time between pin clear and mode set */
            /* polyspace+1 MISRA-C3:11.8 [Justified:Low] "the result is as expected" */
            LDC3114__ReadRegister(LDC3114_REG_ADDR_STATUS_REG, (U8 *) &AU8_DataReceived[U8_Index][0], 2U);
            Dio_WriteChannel(DioConf_DioChannel_Dio_PTD2_Ind_Sensor_IO, 1u);
        }
        else
        {
            /* read register to clear INTB pin used for LDC interrupt */
            /* placed near Dio_WriteChannel to minimize the time between pin clear and mode set */
            /* polyspace+1 MISRA-C3:11.8 [Justified:Low] "the result is as expected" */
            LDC3114__ReadRegister(LDC3114_REG_ADDR_STATUS_REG, (U8 *) &AU8_DataReceived[U8_Index][0], 2U);
            Dio_WriteChannel(DioConf_DioChannel_Dio_PTD2_Ind_Sensor_IO, 0u);
        }

        EN_Commandresult = LDC3114_E_COMMAND_ACCEPTED;
    }
    else {/* LDC not configured yet */}
    return EN_Commandresult;
}

/*********************************************************************************************************
 *  Name                   : LDC3114_ResetLdc
 *  Description            : Function for triggering reset of LDC 3114
 *                         :
 *  Parameters             : void
 *  Return                 : void
 *  Critical/explanation   : -
 *   Author                : mficea
 *********************************************************************************************************/
static void LDC3114__ResetLdc(void)
{
    U8 U8_RegisterValue = LDC3114_RESET_FULL_MASK;
    /* polyspace < MISRA-C3:2.2 : Not a defect : Justify with annotations > Should be kept for future usage */
    LDC3114__WriteRegister(LDC3114_REG_ADDR_RESET_REG, &U8_RegisterValue, 1U);
}

/*********************************************************************************************************
 *  Name                   : LDC3114__LdcConfigurationValidityOk
 *  Description            : This function read Channels Enable register of LDC 3114 and checks its value
 *                         : with the written value at config phase (expected value).
 *                         : If these 2 values don't match, something went wrong and a reset
 *                         :
 *  Parameters             : void
 *  Return                 : BOOL - TRUE if register has the expected value
 *  Critical/explanation   : -
 *   Author                : mficea
 *********************************************************************************************************/
static BOOL LDC3114__LdcConfigurationValidityOk(void)
{
    BOOL BO_ConfigOk = TRUE;
    U8 U8_RegisterValue = 0;
    /* Verify ADDR_NP_SCAN_RATE register if the correct data is stored in. */
    LDC3114__ReadRegister(LDC3114_REG_ADDR_NP_SCAN_RATE, &U8_RegisterValue, 1U);

    if(U8_RegisterValue != LDC3114__ACU8_LdcConfigurationRegValues[2U])
    {
        BO_ConfigOk = FALSE;
    }
    else{/* Configuration valid */}
    return BO_ConfigOk;
}

/*********************************************************************************************************
 *  Name                   : LDC3114__LdcReadyAfterInternalReset
 *  Description            : This function read Status register of LDC 3114 and checks the flag CHIP_READY
 *                         :
 *  Parameters             : void
 *  Return                 : BOOL - TRUE if LDC is stable after Reset
 *  Critical/explanation   : -
 *   Author                : mficea
 *********************************************************************************************************/
static BOOL LDC3114__LdcReadyAfterInternalReset(void)
{
    BOOL BO_LdcReady = FALSE;
    U8 U8_RegisterValue = 0;
    LDC3114__ReadRegister(LDC3114_REG_ADDR_STATUS_REG, &U8_RegisterValue, 1U);
    if( (U8_RegisterValue & LDC3114_STATUS_CHIP_READY_MASK) != 0U )
    {
        BO_LdcReady = TRUE;
    }
    else{/* LDC not stable */}
    return BO_LdcReady;
}

/*********************************************************************************************************
 *  Name                   : LDC3114__LdcRegistersReadyForWrite
 *  Description            : This function read Status register of LDC 3114 and checks the flag RDY_TO_WRITE
 *                         :
 *  Parameters             : void
 *  Return                 : BOOL - TRUE if LDC registers are ready to be written
 *  Critical/explanation   : -
 *   Author                : mficea
 *********************************************************************************************************/
static BOOL LDC3114__LdcRegistersReadyForWrite(void)
{
    BOOL BO_LdcRegistersReadyToBeWritten = FALSE;
    U8 U8_RegisterValue = 0;
    LDC3114__ReadRegister(LDC3114_REG_ADDR_STATUS_REG, &U8_RegisterValue, 1U);
    if( (U8_RegisterValue & LDC3114_STATUS_READY_TO_WRITE_MASK) != 0U )
    {
        BO_LdcRegistersReadyToBeWritten = TRUE;
    }
    else{/* LDC registers not ready for write */}
    return BO_LdcRegistersReadyToBeWritten;
}


/*********************************************************************************************************
 *  Name                   : LDC3114_GetDiagData
 *  Description            : Function for getting LDC 3114 huf monitor data
 *                         :
 *  Parameters             : pu8Buffer - pointer to save data buffer
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : atofan
 *********************************************************************************************************/
void LDC3114_GetDiagData(U8 *pu8Buffer)
{
    U8 U8_LoopIndex = 0u;
    for(; U8_LoopIndex < LDC3114_HUF_MONITOR_DIAG_DATA_LENGTH; U8_LoopIndex++)
    {
        pu8Buffer[U8_LoopIndex] = AU8_DataReceived[U8_Index][U8_LoopIndex];
    }
}

/*********************************************************************************************************
 *  Name                   : LDC3114_GetSensorsData
 *  Description            : Function for getting LDC 3114 measured values
 *                         :
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
void LDC3114_GetSensorsData(void)
{
    LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH0].U32_last_sample = AU8_DataReceived[U8_Index][4];
    LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH0].U32_last_sample = (LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH0].U32_last_sample << 8u) + AU8_DataReceived[U8_Index][3];
    LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH0].U32_last_sample = (LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH0].U32_last_sample << 8u) + AU8_DataReceived[U8_Index][2];

    LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH1].U32_last_sample = AU8_DataReceived[U8_Index][7];
    LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH1].U32_last_sample = (LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH1].U32_last_sample << 8u) + AU8_DataReceived[U8_Index][6];
    LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH1].U32_last_sample = (LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH1].U32_last_sample << 8u) + AU8_DataReceived[U8_Index][5];

    if((U8_Positives_Values == 0) && (LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH0].U32_last_sample != 0) && (LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH1].U32_last_sample != 0))
    {
        U8_Positives_Values = (U8)1;
    }
    else
    {
        /* do nothing */
    }
}

/*********************************************************************************************************
 *  Name                   : LDC3114_DisableChannels
 *  Description            : Disable LDC3114 Channels
 *                         :
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : atofan
 *********************************************************************************************************/
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
BOOL LDC3114_DisableChannels(void)
{
    U8  u8TxBuf = 0;
    BOOL boOpOK;
    LDC3114__EnableRegisterWrite();
    /* polyspace < MISRA-C3:15.6: Not a defect : Justify with annotations > The body of the iteration-statement has only one line, no confusion. */
    if (TRUE == LDC3114__LdcRegistersReadyForWrite()) {
    /* polyspace < MISRA-C3:2.2 : Not a defect : Justify with annotations > Should be kept for future usage */
    LDC3114__WriteRegister(LDC3114_REG_ADDR_CHANNELS_ENABLE, &u8TxBuf, 1);
    /* polyspace < MISRA-C3:2.2 : Not a defect : Justify with annotations > Should be kept for future usage */
    LDC3114__DisableRegisterWrite();
        boOpOK = TRUE;
    }
    else 
    {
        boOpOK = FALSE;
    }
    return boOpOK;
}

/*********************************************************************************************************
 *  Name                   : LDC3114_EnableChannels
 *  Description            : Enable LDC3114 Channels
 *                         :
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : atofan
 *********************************************************************************************************/
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
BOOL LDC3114_EnableChannels(void)
{
    BOOL boOpOK;
    LDC3114__EnableRegisterWrite();
    /* polyspace < MISRA-C3:15.6: Not a defect : Justify with annotations > The body of the iteration-statement has only one line, no confusion. */
    if ( TRUE == LDC3114__LdcRegistersReadyForWrite()) {
    /* polyspace < MISRA-C3:11.8 : Not a defect : Justify with annotations > Cast checked by developer*/
    /* polyspace < MISRA-C3:2.2 : Not a defect : Justify with annotations > Should be kept for future usage */
    LDC3114__WriteRegister(LDC3114_REG_ADDR_CHANNELS_ENABLE, (U8*)&LDC3114__ACU8_LdcConfigurationRegValues[1], 1);
    /* polyspace < MISRA-C3:2.2 : Not a defect : Justify with annotations > Should be kept for future usage */
    LDC3114__DisableRegisterWrite();
        boOpOK = TRUE;
    }
    else 
    {
        boOpOK = FALSE;
    }
    return boOpOK;
}
/* polyspace < MISRA-C3:8.3 : Not a defect : Justify with annotations > Function use the same names and type, U8 and uint8 are same */
void I2C_ErrorNotification(U8 u8Channel,U8 u8ErrorCode)
{

}

/*********************************************************************************************************
 *  Name                   : LDC3114_ISR
 *  Description            : Interrupt Service Routine for LDC - INTB pin
 *                         :
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : atofan
 *********************************************************************************************************/
void LDC3114_ISR(void)
{
    EcuM_StateType tCurrentEcuMState;
    EcuM_GetState(&tCurrentEcuMState);
    if (ECUM_STATE_SLEEP == tCurrentEcuMState)
    {
        U32_LDC_Remaining_Time = Gpt_GetTimeRemaining(GptConf_GptChannelConfiguration_GptChannelConfiguration_LPTMR);
        bLdcIsrTriggered = LDC_INTERRUPT_OCCURRED;
        U8_noOfTasksWithoutLDC = 0U;
        U8_resetFlag = 0U;
    }
    else
    {
        /* polyspace+1 MISRA-C3:11.8 [Justified:Low] "the result is as expected" */
        LDC3114__ReadRegister(LDC3114_REG_ADDR_STATUS_REG, (U8 *)&AU8_DataReceived[U8_Index][0], 2U);
        if (0u != (AU8_DataReceived[U8_Index][1] & LDC3114_OUT_DATA_RDY_MASK))
        {
            bLdcIsrTriggered = LDC_INTERRUPT_OCCURRED;
            U8_noOfTasksWithoutLDC = 0U;
            U8_resetFlag = 0U;
        }
        else
        {
            /*do nothing*/
        }
    }
}

/*********************************************************************************************************
 *  Name                   : vHandleLDCChStates
 *  Description            : Enable or disable LDC channels
 *                         :
 *  Parameters             : none
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                :
 *********************************************************************************************************/
/* polyspace < MISRA-C3:8.7 : Not a defect : Justify with annotations > External Usage dependent on project setup*/
void vHandleLDCChStates(void)
{
    /* polyspace< MISRA-C3:10.3: Not a defect : Justify with annotations > Left and right operand has same type */
    static BOOL LDC_boChEnabled = 0xFF;
    if ((BatSup_isVoltageInNormal())!= 0U && /* polyspace < MISRA-C3:13.5 : Not a defect : Justify with annotations> the operands are two different conditions*/
        (TRUE != LDC_boChEnabled) &&                                                           /* polyspace < MISRA-C3:8.3,8.5 : Not a defect : Justify with annotations > Function use the same names and type */
        (TRUE == LDC3114_EnableChannels()))
    {
        LDC_boChEnabled = TRUE;
    }
    else if ((BatSup_isVoltageInNormal() == 0u) && /* polyspace < MISRA-C3:13.5 : Not a defect : Justify with annotations> the operands are two different conditions*/
             (FALSE != LDC_boChEnabled) &&                                                          /* polyspace < MISRA-C3:8.3,8.5 : Not a defect : Justify with annotations > Function use the same names and type */
             (TRUE == LDC3114_DisableChannels()))
    {
        LDC_boChEnabled = FALSE;
        Inductive_Algo_Clear_Can_Signal();
    }
    else
    {
        /*do nothing */
    }
}

/*********************************************************************************************************
 *  Name                   : LDC3114_syncErrorHandleLDC
 *  Description            : clear interrupt pin in case of error
 *                         :
 *  Parameters             : mode - LDC running mode
 *  Return                 : none
 *  Critical/explanation   : -
 *   Author                : hcostin
 *********************************************************************************************************/
void LDC3114_syncErrorHandleLDC(LDC3114_Enum_LdcPowerModesType mode)
{
    U8 U8_limitOfTasks = ((mode == LDC3114_E_LOW_POWER)?20U:13U);
    U8 U8_limitOfI2C = U8_limitOfTasks + ((mode == LDC3114_E_LOW_POWER)?16U:10U);
    U8 U8_limitOfReset = U8_limitOfI2C + ((mode == LDC3114_E_LOW_POWER)?16U:10U);
    U8 locIndex;

    if (BatSup_isVoltageInNormal() != 0U) 
    {

        U8_noOfTasksWithoutLDC++;
        if(U8_noOfTasksWithoutLDC > U8_limitOfTasks && U8_noOfTasksWithoutLDC <= U8_limitOfI2C)
        {
            /* level 0: read status register*/
            /* polyspace+1 MISRA-C3:11.8 [Justified:Low] "the result is as expected" */
            LDC3114__ReadRegister(LDC3114_REG_ADDR_STATUS_REG, (U8 *) &AU8_DataReceived[U8_Index][0], 2U);
        }
        else
        {
            /*do nothing*/
        }
        if(U8_noOfTasksWithoutLDC > U8_limitOfI2C && U8_noOfTasksWithoutLDC <= U8_limitOfReset)
        {
            /* level 1: toggle i2c clock line */
            Port_SetPinMode(5,PORT_GPIO_MODE);
            Port_SetPinMode(4,PORT_GPIO_MODE);
            for(locIndex = 0; locIndex < 240u; locIndex++)
            {
                if(0 == locIndex % 8)
                {
                    PTA->PDOR ^= 0x0CU;
                }
            }

            Port_SetPinMode(5, PORT2_LPI2C0_SDA);
            Port_SetPinMode(4, PORT3_LPI2C0_SCL);
        }
        else
        {
            /*do nothing*/
        }
        if(U8_noOfTasksWithoutLDC > U8_limitOfReset)
        {
            if(0 == U8_resetFlag)
            {
                /* level 2: reset LDC chip */
                LDC3114__ResetLdc();
                LDC3114__EN_InternalState = LDC3114__E_RESET_MODE;
                U8_resetFlag=1;
            }
            else
            {
                /* level 3: reset MCU */
                /* here the LDC is kind of dead */
                Mcu_PerformReset();
            }
            
            U8_noOfTasksWithoutLDC = 0U;
        }
        else
        {
            /*do nothing*/
        }
    }
    else
    {
        /*do nothing*/
    }
}




static void LDC3114_mcvd_init(void)
{
    U8 sensor_id;
    U8 U8_power_up_loop;

    for( sensor_id = (U8)0; sensor_id < (U8)LDC3114_SENSOR_MAX; sensor_id +=(U8)1 )
    {
    
      /*! initialization  of sensor id */
      LDC3114_Sensor_Var_Str[sensor_id].en_sensor_id = (EN_LDC3114_SENSOR_ID) sensor_id ;

      /*explicit initialization of filter memory*/
      LDC3114_Sensor_Var_Str[sensor_id].S64_Filt_FeedbackBuffer[LDC3114_MEMORY_DEPTH_1]=0;
      LDC3114_Sensor_Var_Str[sensor_id].S64_Filt_FeedbackBuffer[LDC3114_MEMORY_DEPTH_2]=0;
      LDC3114_Sensor_Var_Str[sensor_id].S64_NoiseDet_FeedbackBuffer[LDC3114_MEMORY_DEPTH_1]=0;
      LDC3114_Sensor_Var_Str[sensor_id].S64_NoiseDet_FeedbackBuffer[LDC3114_MEMORY_DEPTH_2]=0;

    }
    /* TODO: PARAM in DDF, now hardcoded */
    LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH0].U32_NoiseThresh = LDC3114_U16_NOISE_THRESHOLD;
    LDC3114_Sensor_Var_Str[LDC3114_SENSOR_CH1].U32_NoiseThresh = LDC3114_U16_NOISE_THRESHOLD;

    /* first sensor sample initialization */
    /* initialization of the filter with constant value for all active sensors*/
    for( sensor_id = (U8)0; sensor_id < (U8)LDC3114_SENSOR_MAX; sensor_id +=(U8)1 )
    {
        for( U8_power_up_loop = (U8)0; U8_power_up_loop < U8_LDC3114_FILTER_FILL_LOOP; U8_power_up_loop++ )
        {
          LDC3114_iir_filter(&LDC3114_Sensor_Var_Str[sensor_id],U32_IIR_WARME_UP_CONSTANT);/*call the filter function for each sensor*/
          LDC3114_noise_detect(&LDC3114_Sensor_Var_Str[sensor_id],U32_IIR_WARME_UP_CONSTANT_NOISE);/*call the noise detect function for each sensor*/
        }
    }
}

void LDC3114_iir_filter (TASK_LDC3114_VAR_T * Sensor_Var,U32 U32_filter_input)
{  
    S64 S64_FeedbackSum;
    U32 U32_ShiftTemp;

    S64* PS64_ptr_FeedBack = Sensor_Var->S64_Filt_FeedbackBuffer;/*get feedback buffer pointer*/

    /* polyspace+1 MISRA-C3:D4.4 [Justified:Low] "Sections of code should not be commented out" */
    /* B0 = 1; A0=1*/
    S64_FeedbackSum=(S64)U32_filter_input + PS64_ptr_FeedBack[LDC3114_CASCADE_LEVEL1];
    if(0 > S64_FeedbackSum)
    {
        S64_FeedbackSum = 0;
    }
    else
    {
        /* value is ok */
    }
    /* B1 = 2 */
    U32_ShiftTemp = ((U32)U32_filter_input)<<1u;
    PS64_ptr_FeedBack[LDC3114_CASCADE_LEVEL1] = (S64) U32_ShiftTemp;

    /* A1 = 1.625 =  1 + 1/4 + 1/8 + 1/16  */
    PS64_ptr_FeedBack[LDC3114_CASCADE_LEVEL1] += S64_FeedbackSum;
    U32_ShiftTemp = ((S64)S64_FeedbackSum) >> 2u;
    PS64_ptr_FeedBack[LDC3114_CASCADE_LEVEL1] += (S64)U32_ShiftTemp;
    U32_ShiftTemp = ((S64)S64_FeedbackSum) >> 3u;
    PS64_ptr_FeedBack[LDC3114_CASCADE_LEVEL1] += (S64)U32_ShiftTemp;
    U32_ShiftTemp = ((S64)S64_FeedbackSum) >> 4u;
    PS64_ptr_FeedBack[LDC3114_CASCADE_LEVEL1] += (S64)U32_ShiftTemp;


    PS64_ptr_FeedBack[LDC3114_CASCADE_LEVEL1] += PS64_ptr_FeedBack[LDC3114_CASCADE_LEVEL2];

    /* B2 = 1  */
    PS64_ptr_FeedBack[LDC3114_CASCADE_LEVEL2] = (S64)U32_filter_input;
    /* A2 = -0.6875 = -(1/2 + 1/16) */
    U32_ShiftTemp = ((U32)S64_FeedbackSum)>>1u;
    PS64_ptr_FeedBack[LDC3114_CASCADE_LEVEL2] -= (S64)U32_ShiftTemp;
    U32_ShiftTemp = ((U32)S64_FeedbackSum)>>4u;
    PS64_ptr_FeedBack[LDC3114_CASCADE_LEVEL2] -= (S64)U32_ShiftTemp;

    /* Filter result / 2*/
    U32_ShiftTemp= ((U32)S64_FeedbackSum>> 1u);


    /* make sure output does not overflow*/
    if((U32)0xFFFFFF < U32_ShiftTemp)
    {
        Sensor_Var->U32_filter_unit_result = U32_MAX;
    }
    else
    {
        Sensor_Var->U32_filter_unit_result = (U32)U32_ShiftTemp;
    }

}

void LDC3114_noise_detect(TASK_LDC3114_VAR_T * Sensor_Var,U32 U32_filter_input)
{
    S64 S64_Diff1;
    S64 S64_Diff2;
    S64* PS64_ptr_FeedBack = Sensor_Var->S64_NoiseDet_FeedbackBuffer;/*get feedback buffer pointer*/

    /* do serial differences */
    S64_Diff1 = (S64)U32_filter_input - PS64_ptr_FeedBack[LDC3114_MEMORY_DEPTH_1];
    S64_Diff2 = S64_Diff1 - PS64_ptr_FeedBack[LDC3114_MEMORY_DEPTH_2];

    /* forward memory */
    PS64_ptr_FeedBack[LDC3114_MEMORY_DEPTH_2] = S64_Diff1;
    PS64_ptr_FeedBack[LDC3114_MEMORY_DEPTH_1] = (S64)U32_filter_input;

    /* take absolute*/
    if(0 > S64_Diff2)
    {
        S64_Diff2 = -S64_Diff2;
    }
    else
    {
        /* is already absolute */
    }
    /* test against threshold */

    /* DEBUGGING PURPOSE ONLY !!!!!!!!!!!! */
    if (Sensor_Var -> en_sensor_id == LDC3114_SENSOR_CH0)
    {
        Ch0_NoiseMeasVal = (U32)S64_Diff2;
    } else{
        Ch1_NoiseMeasVal = (U32)S64_Diff2;
    }

    if( (U32)S64_Diff2 > Sensor_Var->U32_NoiseThresh)
    {
        Sensor_Var->BO_noise_detected = TRUE;
    }
    else
    {
        Sensor_Var->BO_noise_detected = FALSE;
    }
}