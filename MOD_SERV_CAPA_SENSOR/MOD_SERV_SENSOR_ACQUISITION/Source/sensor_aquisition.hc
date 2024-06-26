#ifndef SENSOR_AQUISITION_HC
#define SENSOR_AQUISITION_HC



#ifdef SENSOR_AQUISITION_C
#define SENSOR_AQ_EXPORT
#else
#define SENSOR_AQ_EXPORT extern
#endif




/* General Consts*/
#define U8_SENSOR_INI_OFFSET           0
#define U8_SENSOR_MULTISAMPLING_LOOP   1

#define ADC_CHANNEL_7             (0x07U)
#define ADC_CHANNEL_4             (0x04U)
#define ADC_ALL_DIGITAL           (0x01U)

#define U8_SWITCH_HOLD_TO_VDD     ((U8)(ADC_CHANNEL_7)) /* MUX on VDD  P85 */
#define U8_SWITCH_HOLD_TO_GND     ((U8)(ADC_CHANNEL_4)) /* MUX on GND   Pin P82*/
#define ER_AD_CHANNEL             ((U8)(ADC_CHANNEL_INDEX_1_IN_CONFIG)) /* ADC MUX on unlock electrode Pin P84*/
#define VR_AD_CHANNEL             ((U8)(ADC_CHANNEL_INDEX_4_IN_CONFIG)) /* ADC MUX on lock electrode Pin P83 */


/**************************************************************************/
/* Port 8                                     */
/**************************************************************************/
#define  C_HOLD_VDD_PORT                     8
#define  C_HOLD_GND_PORT                     8

#define  ER_SENSOR_GPIO                      8
#define  VR_SENSOR_GPIO                      8
#define  UNLOCK_ACTIVE_SHIELD1_PORT          8
#define  LOCK_ACTIVE_SHIELD1_PORT            8
#define  UNLOCK_ACTIVE_SHIELD0_PORT          8
#define  LOCK_ACTIVE_SHIELD0_PORT            8
#define  UNLOCK_C_LOAD_PORT                  8
#define  LOCK_C_LOAD_PORT  	                 8

#define C_HOLD_VDD_PIN                       1
#define C_HOLD_GND_PIN                       1
#define UNLOCK_ACTIVE_SHIELD1_PIN            1
#define UNLOCK_ACTIVE_SHIELD0_PIN            0
#define LOCK_ACTIVE_SHIELD1_PIN              UNLOCK_ACTIVE_SHIELD1_PIN
#define LOCK_ACTIVE_SHIELD0_PIN              UNLOCK_ACTIVE_SHIELD0_PIN
#define ER_PIN			 	                 3
#define VR_PIN				                 7
#define UNLOCK_C_LOAD_PIN                    2
#define LOCK_C_LOAD_PIN                      6


/* DIO configuration */


/* Port 0 configuration */
#define DIO_SPI_SEL_ROT_HALL2          (0x01U)        /* P00 - SPI Select Rotation HALL 2 (X6_3) */
/* All pins are input except */
#define PORT_0_DIRECTION               (DIO_SPI_SEL_ROT_HALL2)^(0xFFU)   /* has to be inverted for output */
#define PORT_0_PULL_UP                 (0)


/* Port 1 configuration */
#define DIO_CTXD0                      (0x01U)      /* P10 - CAN TX */
#define DIO_CRXD0                      (0x02U)      /* P11 - CAN RX */
#define DIO_INTP5                      (0x04U)      /* P12 - external inerrupt */
#define DIO_P13                        (0x08U)      /* P13 - STB */
#define DIO_SPI_SO00                   (0x20U)      /* P15 - Serial data output*/
#define DIO_SPI_SI00                   (0x40U)      /* P16 - Serial data input */
#define DIO_SPI_SCK00                  (0x80U)      /* P17 - Serial Clock */
/* All pins are input except */
#define PORT_1_DIRECTION               (DIO_CTXD0 | DIO_P13 | DIO_SPI_SO00 | DIO_SPI_SCK00)^(0xFFU) /* has to be inverted for output */
#define PORT_1_PULL_UP                 (0)/*no pull up on interrupt pin as it will be set to rising edge interrupt*/



/* Port 3 configuration */
#define DIO_SPI_SSI00                  (0x01U)      /* P30 - Slave select input */
#define DIO_NFC_ENABLE                 (0x02U)      /* P31 - NFC controller(NXP) enable pin                            */
#define DIO_LDC_LP_ENABLE              (0x04U)      /* P32 - LDC Low Power enable pin                                  */
#define DIO_P33                        (0x08U)      /* P33 - ? */
#define DIO_ANI1                       (0x10U)      /* P34 - ANALOG INPUT */
/* All pins are input except */
#define PORT_3_DIRECTION               (DIO_NFC_ENABLE | DIO_LDC_LP_ENABLE )^(0xFFU) /* has to be inverted for output */
#define PORT_3_PULL_UP                 (0U)



/* Port 4 configuration */
#define DIO_TOOL0                      (0x01U)      /* P40 -  */
#define DIO_TO_10                      (0x02U)      /* P41 -  */
/* All pins are input except */
#define PORT_4_DIRECTION               (DIO_TOOL0 | DIO_TO_10)^(0xFFU)   /* has to be inverted for output */
#define PORT_4_PULL_UP                 (0U)


/* Port 6 configuration */
#define DIO_OPEN_REQUEST               (0x01U)      /* P60 - Open Request */
#define DIO_CHROME_SCREEN_CONNECTION   (0x02U)      /* P61 - Chromblenden anbindung */


/* All pins are input except */
#define PORT_6_DIRECTION               (DIO_OPEN_REQUEST | DIO_CHROME_SCREEN_CONNECTION)^(0xFFU) /* has to be inverted */


/* Port 8 configuration */
#define DIO_ANI2_UB1                   (0x01U)      /* P80 -   */
#define DIO_ANI3_UDATA                 (0x02U)      /* P81 -   */
#define DIO_ANI4_ELECTRODE_LOCK1       (0x04U)      /* P82 -  ANI4 */
#define DIO_ANI5_ELECTRODE_LOCK2       (0x08U)      /* P83 -  ANI5 */
#define DIO_ANI6_ELECTRODE_APROACH1    (0x10U)      /* P84 -  ANI6 */
#define DIO_ANI7_ELECTRODE_APROACH2    (0x20U)      /* P85 -  */
#define DIO_ANI8_TO_07                 (0x40U)      /* P86 -  ANI8 */
#define DIO_ANI9_TO_10                 (0x80U)      /* P87 -  ANI9 */
/* All pins are input except */
#define PORT_8_DIRECTION               (0U)^(0xFFU)   /* has to be inverted for output */
#define PORT_8_PULL_UP                 (0U)

/* Port 9 configuration */
#define DIO_UPLC_ENABLE                (0x01U)      /* P90 - UPLC enable pin */
#define DIO_UB1_ENABLE                 (0x02U)      /* P91 - UB1  enable pin  */
#define DIO_CAPA_ELECTRODE_SHIELD1     (0x04U)      /* P125 - Shield2 */


/* All pins are input except */
#define PORT_9_DIRECTION              (DIO_UB1_ENABLE | DIO_UPLC_ENABLE | DIO_CAPA_ELECTRODE_SHIELD1)^(0xFFU) /* has to be inverted for output */
#define PORT_9_CONTROL                (DIO_UB1_ENABLE | DIO_UPLC_ENABLE | DIO_CAPA_ELECTRODE_SHIELD1)^(0xFFU)   /* has to be inverted for output */
#define PORT_9_PULL_UP                (0U)

/* Port 12 configuration */
#define DIO_P121_X1                    (0x02U)      /* P121 */
#define DIO_P122_X2                    (0x04U)      /* P122 */
#define DIO_CAPA_ELECTRODE_SHIELD2     (0x20U)      /* P125 */

/* All pins are input except */
#define PORT_12_DIRECTION              (DIO_CAPA_ELECTRODE_SHIELD2)^(0xFFU)   /* has to be inverted for output */
#define PORT_12_CONTROL                (DIO_CAPA_ELECTRODE_SHIELD2)^(0xFFU)   /* has to be inverted for output */
#define PORT_12_PULL_UP                (0U)



/* Port 13 configuration */
#define DIO_INTP0                (0x01U)      /* P130 - External interrupt */

/* Doesn't have Port mode or pull up registers */

#define MCU_PORT  PM
#define MCU_PIN   P
#define MCU_ANALOG  ADPC
#define OUTPUT     0
#define INPUT      1
#define HIGH       1
#define LOW        0
#define ANALOG     0
#define DIGITAL    1

#endif /*SENSOR_AQUISITION_HC*/


