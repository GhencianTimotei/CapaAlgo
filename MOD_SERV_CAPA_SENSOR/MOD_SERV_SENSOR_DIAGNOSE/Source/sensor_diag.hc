
#ifndef SENSOR_DIAG_HC
#define SENSOR_DIAG_HC


/* #define P40_DATA_PIN */

#define SENSOR_CAPACITIVE_DATA           0xCAU     /* polyspace < MISRA-C3:2.5 : Not a defect > Justify with annotations > should be kept for future usage */
#define SENSOR_INDUCTIVE_DATA            0x1DU     /* polyspace < MISRA-C3:2.5 : Not a defect > Justify with annotations > should be kept for future usage */
#define BOTH_CAPA_AND_INDUCTIVE_DATA     0x21U     /* polyspace < MISRA-C3:2.5 : Not a defect > Justify with annotations > should be kept for future usage */
#define CAPA_DATA_SUBTYPE_ALGO_VALUES       9U     /* polyspace < MISRA-C3:2.5 : Not a defect > Justify with annotations > should be kept for future usage */
#define CAPA_DATA_SUBTYPE_ADC_VALUES       16U     /* polyspace < MISRA-C3:2.5 : Not a defect > Justify with annotations > should be kept for future usage */
#define SENSOR_DATA_TO_SEND              SENSOR_INDUCTIVE_DATA       /* polyspace < MISRA-C3:2.5 : Not a defect > Justify with annotations > should be kept for future usage */
#define CAPA_DATA_SUBTYPE                CAPA_DATA_SUBTYPE_ADC_VALUES
#endif
