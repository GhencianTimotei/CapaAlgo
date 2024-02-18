/*------------------------------------------------------------------------------------------------+
| File: LDC3114.hc                                                                             |
+-------------------------------------------------------------------------------------------------+
| Project: Audi eTab                                                                              |
+-------------------------------------------------------------------------------------------------+
| Short description: Header containing module configurations of LDC3114 driver                        |
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
#ifndef LDC3114_HC
#define LDC3114_HC


/* polyspace:begin <MISRA-C3:2.5: Not a defect : Justify with annotations > Macros used for future config of I2C module */

/* Macros used for configuration */

/* Configured slave addresses. */
#define LDC3114__DEVICE_I2C_BUS_ADDRESS                  0x2AU

/*       ---------------        LDC3114 Register definitions         ------------------------        */

/**************** LDC3114 registers address *****************/
#define LDC3114_REG_ADDR_STATUS_REG                      0x00U
#define LDC3114_REG_ADDR_OUT_REG                         0x01U
#define LDC3114_REG_ADDR_DATA0_LSB                       0x02U
#define LDC3114_REG_ADDR_DATA0_MSB                       0x03U
#define LDC3114_REG_ADDR_DATA1_LSB                       0x04U
#define LDC3114_REG_ADDR_DATA1_MSB                       0x05U
#define LDC3114_REG_ADDR_DATA2_LSB                       0x06U
#define LDC3114_REG_ADDR_DATA2_MSB                       0x07U
#define LDC3114_REG_ADDR_DATA3_LSB                       0x08U
#define LDC3114_REG_ADDR_DATA3_MSB                       0x09U
#define LDC3114_REG_ADDR_RESET_REG                       0x0AU
#define LDC3114_REG_ADDR_RESERVED_1                      0x0BU
#define LDC3114_REG_ADDR_CHANNELS_ENABLE                 0x0CU
#define LDC3114_REG_ADDR_NP_SCAN_RATE                    0x0DU
#define LDC3114_REG_ADDR_GAIN0                           0x0EU
#define LDC3114_REG_ADDR_LP_SCAN_RATE                    0x0FU
#define LDC3114_REG_ADDR_GAIN1                           0x10U
#define LDC3114_REG_ADDR_INTPOL                          0x11U
#define LDC3114_REG_ADDR_GAIN2                           0x12U
#define LDC3114_REG_ADDR_LP_BASE_INC                     0x13U
#define LDC3114_REG_ADDR_GAIN3                           0x14U
#define LDC3114_REG_ADDR_NP_BASE_INC                     0x15U
#define LDC3114_REG_ADDR_BTPAUSE_MAXWIN                  0x16U
#define LDC3114_REG_ADDR_LC_DIV                          0x17U
#define LDC3114_REG_ADDR_HYST                            0x18U
#define LDC3114_REG_ADDR_TWIST                           0x19U
#define LDC3114_REG_ADDR_COMMON_DEFORM                   0x1AU
#define LDC3114_REG_ADDR_RESERVED_2                      0x1BU
#define LDC3114_REG_ADDR_OPOL_DPOL                       0x1CU
#define LDC3114_REG_ADDR_RESERVED_3                      0x1DU
#define LDC3114_REG_ADDR_CNTSC                           0x1EU
#define LDC3114_REG_ADDR_RESERVED_4                      0x1FU
#define LDC3114_REG_ADDR_SENSOR0_CONF                    0x20U
#define LDC3114_REG_ADDR_RESERVED_5                      0x21U
#define LDC3114_REG_ADDR_SENSOR1_CONF                    0x22U
#define LDC3114_REG_ADDR_RESERVED_6                      0x23U
#define LDC3114_REG_ADDR_SENSOR2_CONF                    0x24U
#define LDC3114_REG_ADDR_FTF0                            0x25U
#define LDC3114_REG_ADDR_SENSOR3_CONF                    0x26U
#define LDC3114_REG_ADDR_RESERVED_7                      0x27U
#define LDC3114_REG_ADDR_FTF1_2                          0x28U
#define LDC3114_REG_ADDR_RESERVED_8                      0x29U
#define LDC3114_REG_ADDR_RESERVED_9                      0x2AU
#define LDC3114_REG_ADDR_FTF3                            0x2BU
#define LDC3114_REG_ADDR_RAW_DATA0_3                     0x59U
#define LDC3114_REG_ADDR_RAW_DATA0_2                     0x5AU
#define LDC3114_REG_ADDR_RAW_DATA0_1                     0x5BU
#define LDC3114_REG_ADDR_RAW_DATA1_3                     0x5CU
#define LDC3114_REG_ADDR_RAW_DATA1_2                     0x5DU
#define LDC3114_REG_ADDR_RAW_DATA1_1                     0x5EU
#define LDC3114_REG_ADDR_RAW_DATA2_1                     0x5FU
#define LDC3114_REG_ADDR_RAW_DATA2_2                     0x60U
#define LDC3114_REG_ADDR_RAW_DATA2_3                     0x61U
#define LDC3114_REG_ADDR_RAW_DATA3_1                     0x62U
#define LDC3114_REG_ADDR_RAW_DATA3_2                     0x63U
#define LDC3114_REG_ADDR_RAW_DATA3_3                     0x64U
#define LDC3114_REG_ADDR_MAN_ID_LSB                      0xFCU
#define LDC3114_REG_ADDR_MAN_ID_MSB                      0xFDU
#define LDC3114_REG_ADDR_DEVICE_ID_LSB                   0xFEU
#define LDC3114_REG_ADDR_DEVICE_ID_MSB                   0xFFU

/************* LDC3114 registers default value **************/
#define LDC3114_REG_DEFAULT_RESET_REG                    0x00U
#define LDC3114_REG_DEFAULT_RESERVED_1                   0x00U
#define LDC3114_REG_DEFAULT_CHANNELS_ENABLE              0x1FU
#define LDC3114_REG_DEFAULT_NP_SCAN_RATE                 0x01U
#define LDC3114_REG_DEFAULT_GAIN0                        0x28U
#define LDC3114_REG_DEFAULT_LP_SCAN_RATE                 0x02U
#define LDC3114_REG_DEFAULT_GAIN1                        0x28U
#define LDC3114_REG_DEFAULT_INTPOL                       0x01U
#define LDC3114_REG_DEFAULT_GAIN2                        0x28U
#define LDC3114_REG_DEFAULT_LP_BASE_INC                  0x05U
#define LDC3114_REG_DEFAULT_GAIN3                        0x28U
#define LDC3114_REG_DEFAULT_NP_BASE_INC                  0x03U
#define LDC3114_REG_DEFAULT_BTPAUSE_MAXWIN               0x00U
#define LDC3114_REG_DEFAULT_LC_DIV                       0x03U
#define LDC3114_REG_DEFAULT_HYST                         0x08U
#define LDC3114_REG_DEFAULT_TWIST                        0x00U
#define LDC3114_REG_DEFAULT_COMMON_DEFORM                0x00U
#define LDC3114_REG_DEFAULT_RESERVED_2                   0x00U
#define LDC3114_REG_DEFAULT_OPOL_DPOL                    0x0FU
#define LDC3114_REG_DEFAULT_RESERVED_3                   0x00U
#define LDC3114_REG_DEFAULT_CNTSC                        0x55U
#define LDC3114_REG_DEFAULT_RESERVED_4                   0x00U
#define LDC3114_REG_DEFAULT_SENSOR0_CONF                 0x04U
#define LDC3114_REG_DEFAULT_RESERVED_5                   0x00U
#define LDC3114_REG_DEFAULT_SENSOR1_CONF                 0x04U
#define LDC3114_REG_DEFAULT_RESERVED_6                   0x00U
#define LDC3114_REG_DEFAULT_SENSOR2_CONF                 0x04U
#define LDC3114_REG_DEFAULT_FTF0                         0x02U
#define LDC3114_REG_DEFAULT_SENSOR3_CONF                 0x04U
#define LDC3114_REG_DEFAULT_RESERVED_7                   0x00U
#define LDC3114_REG_DEFAULT_FTF1_2                       0x50U
#define LDC3114_REG_DEFAULT_RESERVED_8                   0x00U
#define LDC3114_REG_DEFAULT_RESERVED_9                   0x00U
#define LDC3114_REG_DEFAULT_FTF3                         0x01U
#define LDC3114_REG_DEFAULT_RAW_DATA0_3                  0x00U
#define LDC3114_REG_DEFAULT_RAW_DATA0_2                  0x00U
#define LDC3114_REG_DEFAULT_RAW_DATA0_1                  0x00U
#define LDC3114_REG_DEFAULT_RAW_DATA1_3                  0x00U
#define LDC3114_REG_DEFAULT_RAW_DATA1_2                  0x00U
#define LDC3114_REG_DEFAULT_RAW_DATA1_1                  0x00U
#define LDC3114_REG_DEFAULT_RAW_DATA2_1                  0x00U
#define LDC3114_REG_DEFAULT_RAW_DATA2_2                  0x00U
#define LDC3114_REG_DEFAULT_RAW_DATA2_3                  0x00U
#define LDC3114_REG_DEFAULT_RAW_DATA3_1                  0x00U
#define LDC3114_REG_DEFAULT_RAW_DATA3_2                  0x00U
#define LDC3114_REG_DEFAULT_RAW_DATA3_3                  0x00U
#define LDC3114_REG_DEFAULT_MAN_ID_LSB                   0x49U
#define LDC3114_REG_DEFAULT_MAN_ID_MSB                   0x54U
#define LDC3114_REG_DEFAULT_DEVICE_ID_LSB                0x00U
#define LDC3114_REG_DEFAULT_DEVICE_ID_MSB                0x40U


/* STATUS register bit masks */
#define LDC3114_STATUS_OUT_STATUS_MASK                   0x80U
#define LDC3114_STATUS_CHIP_READY_MASK                   0x40U
#define LDC3114_STATUS_READY_TO_WRITE_MASK               0x20U
#define LDC3114_STATUS_MAXOUT_MASK                       0x10U
#define LDC3114_STATUS_FSM_WD_MASK                       0x08U
#define LDC3114_STATUS_LC_WD_MASK                        0x04U
#define LDC3114_STATUS_TIMEOUT_MASK                      0x02U
#define LDC3114_STATUS_REGISTER_FLAG_MASK                0x01U

/* OUT register bit masks */
#define LDC3114_OUT_DATA_RDY_MASK                        0x10U
#define LDC3114_OUT_CHANNEL_3_MASK                       0x08U
#define LDC3114_OUT_CHANNEL_2_MASK                       0x04U
#define LDC3114_OUT_CHANNEL_1_MASK                       0x02U
#define LDC3114_OUT_CHANNEL_0_MASK                       0x01U

/* DATA0_LSB register bit masks */
#define LDC3114_DATA_0_LSB_MASK                          0xFFU
/* DATA1_LSB register bit masks */
#define LDC3114_DATA_1_LSB_MASK                          0xFFU
/* DATA2_LSB register bit masks */
#define LDC3114_DATA_2_LSB_MASK                          0xFFU
/* DATA3_LSB register bit masks */
#define LDC3114_DATA_3_LSB_MASK                          0xFFU

/* DATA0_MSB register bit masks */
#define LDC3114_DATA_0_MSB_MASK                          0x0FU
/* DATA1_MSB register bit masks */
#define LDC3114_DATA_1_MSB_MASK                          0x0FU
/* DATA2_MSB register bit masks */
#define LDC3114_DATA_2_MSB_MASK                          0x0FU
/* DATA3_MSB register bit masks */
#define LDC3114_DATA_3_MSB_MASK                          0x0FU

/* RESET register bit masks */
#define LDC3114_RESET_CONFIG_MODE_MASK                   0x01U
#define LDC3114_RESET_FULL_MASK                          0x10U

/* ENABLE register bit masks */
#define LDC3114_ENABLE_LPEN3_MASK                        0x80U
#define LDC3114_ENABLE_LPEN2_MASK                        0x40U
#define LDC3114_ENABLE_LPEN1_MASK                        0x20U
#define LDC3114_ENABLE_LPEN0_MASK                        0x10U
#define LDC3114_ENABLE_EN3_MASK                          0x08U
#define LDC3114_ENABLE_EN2_MASK                          0x04U
#define LDC3114_ENABLE_EN1_MASK                          0x02U
#define LDC3114_ENABLE_EN0_MASK                          0x01U

/* NP_SCAN_RATE register bit mask */
#define LDC3114_NPFSR_MASK                               0x08U
#define LDC3114_NPCS_MASK                                0x04U
#define LDC3114_NPSR_MASK                                0x03U
/* NPSR - Normal Power Mode Scan Rate values : */
#define LDC3114_NPSR_80_SPS_VAL                          0x00U
#define LDC3114_NPSR_40_SPS_VAL                          0x01U
#define LDC3114_NPSR_20_SPS_VAL                          0x02U
#define LDC3114_NPSR_10_SPS_VAL                          0x03U

/* GAIN0 register bit mask .
 * Refer to datasheet Gain Table for detailed config */
#define LDC3114_GAIN0_MASK                               0x3FU

/* LP_SCAN_RATE register bit mask */
#define LDC3114_LPSR_MASK                                0x03U
/* NPSR - Low Power Mode Scan Rate values : */
#define LDC3114_LPSR_5_SPS_VAL                           0x00U
#define LDC3114_LPSR_2_5_SPS_VAL                         0x01U
#define LDC3114_LPSR_1_25_SPS_VAL                        0x02U
#define LDC3114_LPSR_0_625_SPS_VAL                       0x03U

/* GAIN1 register bit mask .
 * Refer to datasheet Gain Table for detailed config */
#define LDC3114_GAIN1_MASK                               0x3FU

/* INTPOL register bit mask */
#define LDC3114_BTSRT_EN_MASK                            0x10U
#define LDC3114_BTN_ALG_EN_MASK                          0x08U
#define LDC3114_INTPOL_MASK                              0x04U
#define LDC3114_DIS_BTN_TO_MASK                          0x02U
#define LDC3114_DIS_BTB_MO_MASK                          0x01U

/* GAIN2 register bit mask .
 * Refer to datasheet Gain Table for detailed config */
#define LDC3114_GAIN2_MASK                               0x3FU

/* LP_BASE_INC register bit mask */
#define LDC3114_LPBI_MASK                                0x07U

/* GAIN3 register bit mask .
 * Refer to datasheet Gain Table for detailed config */
#define LDC3114_GAIN3_MASK                               0x3FU

/* NP_BASE_INC register bit mask */
#define LDC3114_NPBI_MASK                                0x07U

/* BTPAUSE_MAXWIN register bit masks */
#define LDC3114_BTPAUSE3_MASK                            0x80U
#define LDC3114_BTPAUSE2_MASK                            0x40U
#define LDC3114_BTPAUSE1_MASK                            0x20U
#define LDC3114_BTPAUSE0_MASK                            0x10U
#define LDC3114_MAXWIN3_MASK                             0x08U
#define LDC3114_MAXWIN2_MASK                             0x04U
#define LDC3114_MAXWIN1_MASK                             0x02U
#define LDC3114_MAXWIN0_MASK                             0x01U

/* LC_DIVIDER register bit mask */
#define LDC3114_LC_DIVIDER_LCDIV_MASK                    0x07U

/* HYST register bit mask */
#define LDC3114_LC_HYST_MASK                             0x0FU

/* TWIST register bit mask */
#define LDC3114_ANTITWIST_MASK                           0x07U

/* COMMON_DEFORM register bit masks */
#define LDC3114_ANTICOM3_MASK                            0x80U
#define LDC3114_ANTICOM2_MASK                            0x40U
#define LDC3114_ANTICOM1_MASK                            0x20U
#define LDC3114_ANTICOM0_MASK                            0x10U
#define LDC3114_ANTIDEFORM3_MASK                         0x08U
#define LDC3114_ANTIDEFORM2_MASK                         0x04U
#define LDC3114_ANTIDEFORM1_MASK                         0x02U
#define LDC3114_ANTIDEFORM0_MASK                         0x01U

/* OPOL_DPOL register bit masks */
#define LDC3114_OPOL3_MASK                               0x80U
#define LDC3114_OPOL2_MASK                               0x40U
#define LDC3114_OPOL1_MASK                               0x20U
#define LDC3114_OPOL0_MASK                               0x10U
#define LDC3114_DPOL3_MASK                               0x08U
#define LDC3114_DPOL2_MASK                               0x04U
#define LDC3114_DPOL1_MASK                               0x02U
#define LDC3114_DPOL0_MASK                               0x01U

/* CNTSC register bit masks */
#define LDC3114_CNTSC3_MASK                              0xC0U
#define LDC3114_CNTSC2_MASK                              0x30U
#define LDC3114_CNTSC1_MASK                              0x0CU
#define LDC3114_CNTSC0_MASK                              0x03U

/* SENSOR0_CONFIG register bit masks */
#define LDC3114_SENSOR0_CONFIG_RP0_MASK                  0x80U
#define LDC3114_SENSOR0_CONFIG_FREQ0_MASK                0x60U
#define LDC3114_SENSOR0_CONFIG_SENCYC0_MASK              0x1FU

/* SENSOR1_CONFIG register bit masks */
#define LDC3114_SENSOR1_CONFIG_RP1_MASK                  0x80U
#define LDC3114_SENSOR1_CONFIG_FREQ1_MASK                0x60U
#define LDC3114_SENSOR1_CONFIG_SENCYC1_MASK              0x1FU

/* SENSOR2_CONFIG register bit masks */
#define LDC3114_SENSOR2_CONFIG_RP2_MASK                  0x80U
#define LDC3114_SENSOR2_CONFIG_FREQ2_MASK                0x60U
#define LDC3114_SENSOR2_CONFIG_SENCYC2_MASK              0x1FU

/* FTF0 register bit masks */
#define LDC3114_FTF0_MASK                                0x06U

/* SENSOR3_CONFIG register bit masks */
#define LDC3114_SENSOR3_CONFIG_RP3_MASK                  0x80U
#define LDC3114_SENSOR3_CONFIG_FREQ3_MASK                0x60U
#define LDC3114_SENSOR3_CONFIG_SENCYC3_MASK              0x1FU

/* SENSOR_CONFIG register bitfield values */
#define LDC3114_SENSOR_CONFIG_FREQ_1MHZ_3_3MHZ           0x00U
#define LDC3114_SENSOR_CONFIG_FREQ_3_3MHZ_10MHZ          0x20U
#define LDC3114_SENSOR_CONFIG_FREQ_10MHZ_30MHZ           0x40U
#define LDC3114_SENSOR_CONFIG_FREQ_RESERVED              0x60U

#define LDC3114_SENSOR_CONFIG_SENCYC_DEFAULT             0x04U

/* FTF1_2 register bit masks */
#define LDC3114_FTF2_MASK                                0xC0U
#define LDC3114_FTF1_MASK                                0x30U

/* FTF3 register bit masks */
#define LDC3114_FTF3_MASK                                0x03U

/* CNTSC register bitfield values */
#define LDC3114_CNTSC3_0_VAL                             0x00U
#define LDC3114_CNTSC3_1_VAL                             0x40U
#define LDC3114_CNTSC3_2_VAL                             0x80U
#define LDC3114_CNTSC3_3_VAL                             0xC0U

#define LDC3114_CNTSC2_0_VAL                             0x00U
#define LDC3114_CNTSC2_1_VAL                             0x10U
#define LDC3114_CNTSC2_2_VAL                             0x20U
#define LDC3114_CNTSC2_3_VAL                             0x30U

#define LDC3114_CNTSC1_0_VAL                             0x00U
#define LDC3114_CNTSC1_1_VAL                             0x04U
#define LDC3114_CNTSC1_2_VAL                             0x08U
#define LDC3114_CNTSC1_3_VAL                             0x0CU

#define LDC3114_CNTSC0_0_VAL                             0x00U
#define LDC3114_CNTSC0_1_VAL                             0x01U
#define LDC3114_CNTSC0_2_VAL                             0x02U
#define LDC3114_CNTSC0_3_VAL                             0x03U

/* RAW_DATA0_3 register bit masks */
#define LDC3114_RAW_DATA0_3_MASK                         0xFFU
/* RAW_DATA0_2 register bit masks */
#define LDC3114_RAW_DATA0_2_MASK                         0xFFU
/* RAW_DATA0_1 register bit masks */
#define LDC3114_RAW_DATA0_1_MASK                         0xFFU

/* RAW_DATA1_3 register bit masks */
#define LDC3114_RAW_DATA1_3_MASK                         0xFFU
/* RAW_DATA1_2 register bit masks */
#define LDC3114_RAW_DATA1_2_MASK                         0xFFU
/* RAW_DATA1_1 register bit masks */
#define LDC3114_RAW_DATA1_1_MASK                         0xFFU

/* RAW_DATA2_3 register bit masks */
#define LDC3114_RAW_DATA2_3_MASK                         0xFFU
/* RAW_DATA2_2 register bit masks */
#define LDC3114_RAW_DATA2_2_MASK                         0xFFU
/* RAW_DATA2_1 register bit masks */
#define LDC3114_RAW_DATA2_1_MASK                         0xFFU

/* RAW_DATA3_3 register bit masks */
#define LDC3114_RAW_DATA3_3_MASK                         0xFFU
/* RAW_DATA3_2 register bit masks */
#define LDC3114_RAW_DATA3_2_MASK                         0xFFU
/* RAW_DATA3_1 register bit masks */
#define LDC3114_RAW_DATA3_1_MASK                         0xFFU

/* MANUFACTURER_ID_LSB register bit masks */
#define LDC3114_MANUFACTURER_ID_LSB_MASK                 0xFFU
/* MANUFACTURER_ID_MSB register bit masks */
#define LDC3114_MANUFACTURER_ID_MSB_MASK                 0xFFU

/* DEVICE_ID_LSB register bit masks */
#define LDC3114_DEVICE_ID_LSB_MASK                       0xFFU
/* DEVICE_ID_MSB register bit masks */
#define LDC3114_DEVICE_ID_MSB_MASK                       0xFFU

/* LDC3114 registers configuration */
static const U8 LDC3114__ACU8_LdcConfigurationRegValues[] =
{
/* Write config start address  */      LDC3114_REG_ADDR_CHANNELS_ENABLE     ,
/* REG_VAL_CHANNELS_ENABLE     */      LDC3114_ENABLE_LPEN1_MASK | LDC3114_ENABLE_LPEN0_MASK | LDC3114_ENABLE_EN1_MASK | LDC3114_ENABLE_EN0_MASK  ,
/* REG_VAL_NP_SCAN_RATE        */      LDC3114_NPFSR_MASK                   ,
/* REG_VAL_GAIN0               */      LDC3114_REG_DEFAULT_GAIN0            ,
/* REG_VAL_LP_SCAN_RATE        */      LDC3114_LPSR_5_SPS_VAL               ,
/* REG_VAL_GAIN1               */      LDC3114_REG_DEFAULT_GAIN1            ,
/* REG_VAL_INTPOL              */      LDC3114_DIS_BTB_MO_MASK              ,
/* REG_VAL_GAIN2               */      LDC3114_REG_DEFAULT_GAIN2            ,
/* REG_VAL_LP_BASE_INC         */      0x02U                                ,
/* REG_VAL_GAIN3               */      LDC3114_REG_DEFAULT_GAIN3            ,
/* REG_VAL_NP_BASE_INC         */      0x04U                                ,
/* REG_VAL_BTPAUSE_MAXWIN      */      LDC3114_REG_DEFAULT_BTPAUSE_MAXWIN   ,
/* REG_VAL_LC_DIV              */      0x02U                                ,
/* REG_VAL_HYST                */      LDC3114_REG_DEFAULT_HYST             ,
/* REG_VAL_TWIST               */      LDC3114_REG_DEFAULT_TWIST            ,
/* REG_VAL_COMMON_DEFORM       */      LDC3114_REG_DEFAULT_COMMON_DEFORM    ,
/* REG_VAL_RESERVED_2          */      LDC3114_REG_DEFAULT_RESERVED_2       ,
/* REG_VAL_OPOL_DPOL           */      LDC3114_REG_DEFAULT_OPOL_DPOL        ,
/* REG_VAL_RESERVED_3          */      LDC3114_REG_DEFAULT_RESERVED_3       ,
/* REG_VAL_CNTSC               */      LDC3114_CNTSC3_0_VAL | LDC3114_CNTSC2_0_VAL | LDC3114_CNTSC1_0_VAL | LDC3114_CNTSC0_0_VAL,
/* REG_VAL_RESERVED_4          */      LDC3114_REG_DEFAULT_RESERVED_4       ,
/* REG_VAL_SENSOR0_CONF        */      LDC3114_SENSOR_CONFIG_FREQ_3_3MHZ_10MHZ | LDC3114_SENSOR_CONFIG_SENCYC_DEFAULT,
/* REG_VAL_RESERVED_5          */      LDC3114_REG_DEFAULT_RESERVED_5       ,
/* REG_VAL_SENSOR1_CONF        */      LDC3114_SENSOR_CONFIG_FREQ_3_3MHZ_10MHZ | LDC3114_SENSOR_CONFIG_SENCYC_DEFAULT,
/* REG_VAL_RESERVED_6          */      LDC3114_REG_DEFAULT_RESERVED_6       ,
/* REG_VAL_SENSOR2_CONF        */      LDC3114_SENSOR_CONFIG_FREQ_3_3MHZ_10MHZ | LDC3114_SENSOR_CONFIG_SENCYC_DEFAULT,
/* REG_VAL_FTF0                */      LDC3114_REG_DEFAULT_FTF0             ,
/* REG_VAL_SENSOR3_CONF        */      LDC3114_SENSOR_CONFIG_FREQ_3_3MHZ_10MHZ | LDC3114_SENSOR_CONFIG_SENCYC_DEFAULT,
/* REG_VAL_RESERVED_7          */      LDC3114_REG_DEFAULT_RESERVED_7       ,
/* REG_VAL_FTF1_2              */      LDC3114_REG_DEFAULT_FTF1_2           ,
/* REG_VAL_RESERVED_8          */      LDC3114_REG_DEFAULT_RESERVED_8       ,
/* REG_VAL_RESERVED_9          */      LDC3114_REG_DEFAULT_RESERVED_9       ,
/* REG_VAL_FTF3                */      LDC3114_REG_DEFAULT_FTF3             /* , */
/* REG_VAL_RAW_DATA0_3         */      /* LDC3114_REG_DEFAULT_RAW_DATA0_3      , */
/* REG_VAL_RAW_DATA0_2         */      /* LDC3114_REG_DEFAULT_RAW_DATA0_2      , */
/* REG_VAL_RAW_DATA0_1         */      /* LDC3114_REG_DEFAULT_RAW_DATA0_1      , */
/* REG_VAL_RAW_DATA1_3         */      /* LDC3114_REG_DEFAULT_RAW_DATA1_3      , */
/* REG_VAL_RAW_DATA1_2         */      /* LDC3114_REG_DEFAULT_RAW_DATA1_2      , */
/* REG_VAL_RAW_DATA1_1         */      /* LDC3114_REG_DEFAULT_RAW_DATA1_1      , */
/* REG_VAL_RAW_DATA2_1         */      /* LDC3114_REG_DEFAULT_RAW_DATA2_1      , */
/* REG_VAL_RAW_DATA2_2         */      /* LDC3114_REG_DEFAULT_RAW_DATA2_2      , */
/* REG_VAL_RAW_DATA2_3         */      /* LDC3114_REG_DEFAULT_RAW_DATA2_3      , */
/* REG_VAL_RAW_DATA3_1         */      /* LDC3114_REG_DEFAULT_RAW_DATA3_1      , */
/* REG_VAL_RAW_DATA3_2         */      /* LDC3114_REG_DEFAULT_RAW_DATA3_2      , */
/* REG_VAL_RAW_DATA3_3         */      /* LDC3114_REG_DEFAULT_RAW_DATA3_3      , */
/* REG_VAL_MAN_ID_LSB          */      /* LDC3114_REG_DEFAULT_MAN_ID_LSB       , */
/* REG_VAL_MAN_ID_MSB          */      /* LDC3114_REG_DEFAULT_MAN_ID_MSB       , */
/* REG_VAL_DEVICE_ID_LSB       */      /* LDC3114_REG_DEFAULT_DEVICE_ID_LSB    , */
/* REG_VAL_DEVICE_ID_MSB       */      /* LDC3114_REG_DEFAULT_DEVICE_ID_MSB    , */
};

#define LDC3114__NB_OF_EN_CHANNELS_IN_NORMAL_POWER              2U
#define LDC3114__NB_OF_EN_CHANNELS_IN_LOW_POWER                 0U

#define LDC3114__NUMBER_OF_REGISTERS_TO_CONFIG        ((U8)(sizeof(LDC3114__ACU8_LdcConfigurationRegValues)/sizeof(LDC3114__ACU8_LdcConfigurationRegValues[0])) - 1U)



/* polyspace:end <MISRA-C3:2.5: Not a defect :  Justify with annotations > */
/* polyspace < MISRA-C3:2.5 : Not a defect > Justify with annotations > should be kept for future usage */
/* P11 for LPWRB LDC2113 */
#define LDC_LP_ENABLE_PORT      P1
/* polyspace < MISRA-C3:2.5 : Not a defect > Justify with annotations > should be kept for future usage */
#define LDC_LP_ENABLE_PIN       0x02U

#endif /* LDC3114_HC */



/* Automatic logging by PVCS ***********************************************
$Log:
*********************************************************** end of comment */
