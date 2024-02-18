#ifndef PDL_H
#define PDL_H
#include "Platform_Types.h"

/* polyspace+1 MISRA-C3:2.4 [Justified:Low] "Added for further implementation." */
typedef enum tenPDLSts{
    PDL_INVALID,
    PDL_INCOSISTENT,
    PDL_OK,
}tenPDLSts;

#define PDL_PRESENCE_HEADER 0x1337C0DEu

#define PDL_VALIDITY_HEADER 0xFADEA007u

/******************************************************************************
 *          CONFIGURATION  AREA
 ******************************************************************************/
/* polyspace+1 MISRA-C3:2.4 [Justified:Low] "Added for further implementation." */
typedef struct tstPDLData{
    uint8 ReservedPresenceHeader[32];
    uint32 Header;
    uint8 VersionID[4];
    uint8 pad0[24u];
    uint8 AUDI_PARAMS_BLOCK_DEFAULT[50u];
    uint8 pad1[62u];
    uint16 BATTERY_SUPERVISOR_BLOCK_DEFAULT[6u];
    uint8 pad2[36u];
    uint8 ECU_Serial_Number[20u];
    uint8 pad3[44u];
    uint8 System_Supplier_ECU_Hardware_Number[11u];
    uint8 pad4[53u];
    uint8 System_Supplier_ECU_Hardware_Version_Number[3u];
    uint8 pad5[61u];
    uint8 System_Supplier_ECU_Software_Number[11u];
    uint8 pad6[37u];
    uint8 VW_ECU_Hardware_Number[11u];
    uint8 pad7[53u];
    uint8 VW_ECU_Hardware_Version_Number[3u];
    uint8 pad8[61u];
    uint8 VW_FAZIT_Identification_String[23u];
    uint8 pad9[41u];
    uint8 VW_Spare_Part_Number[11u];
    uint8 pad10[53u];
    uint8 EEPROM_VERSION[2u];
    uint8 pad11[62u];
    uint16 EMERGENCY_ACCESS_BLOCK_DEFAULT[6u];
    uint8 pad12[52u];
    uint16 INDUCTIVE_SENSOR_BLOCK_DEFAULT[14u];
    uint8 pad13[36u];
    uint8 LED_DUTY[1u];
    uint8 pad14[63u];
    uint16 LOCK_SENSOR_BLOCK_DEFAULT[18u];
    uint8 pad15[28u];
    uint16 TIME_NFC_DIAG[10u];
    uint8 pad16[44u];
    uint16 UNLOCK_SENSOR_BLOCK_DEFAULT[18u];
    uint8 pad17[28u];
    uint16 FD02_SPARE_BLOCK_DEFAULT[22u];
    uint8 pad18[20u];
    uint8 ST_DIGIT_NFC_NVM_params_DEFAULT[25u];
    uint8 pad19[39u];
    uint8 System_Supplier_Identifier[100u];
    uint8 pad20[2656u];
    uint32 TransplantErrors;
    uint32 Validity;
    uint32 DataCRC;
    uint8 ReservedValidityHeader[32];
}tstPDLData;

extern const volatile tstPDLData PDL;
tenPDLSts is_pdl_valid(void);
#endif