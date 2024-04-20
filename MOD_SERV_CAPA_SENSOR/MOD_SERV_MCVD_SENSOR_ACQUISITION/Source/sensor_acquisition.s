;/*------------------------------------------------------------------------------------------------+
;| File: sensor_aquisition.s                                                              |
;+-------------------------------------------------------------------------------------------------+
;| Project: Audi eTab                                                                              |
;+-------------------------------------------------------------------------------------------------+
;| Short description: The file contains the implementation of the capacitive sensors acquisition   |
;+------------------------------------------------------------------------------------------------*/

#define LOCK_HBL_ASM                  1 
#define LOCK_HBR_ASM                  2
#define UNLOCK_HBL_ASM               16
#define UNLOCK_HBR_ASM               15
#define SHIELD_0_ASM                 14
#define SHIELD_1_ASM                  9

#define LOCK_HBL_BIT_ASM       (1<<LOCK_HBL_ASM)
#define LOCK_HBR_BIT_ASM       (1<<LOCK_HBR_ASM)
#define UNLOCK_HBL_BIT_ASM     (1<<UNLOCK_HBL_ASM)
#define UNLOCK_HBR_BIT_ASM     (1<<UNLOCK_HBR_ASM)
#define SHIELD_0_BIT_ASM       (1<<SHIELD_0_ASM)
#define SHIELD_1_BIT_ASM       (1<<SHIELD_1_ASM)

#define TOGGLE_MASK_ASM_VALUE        (LOCK_HBL_BIT_ASM | LOCK_HBR_BIT_ASM | UNLOCK_HBL_BIT_ASM | UNLOCK_HBR_BIT_ASM | SHIELD_0_BIT_ASM | SHIELD_1_BIT_ASM)
#define PREPARE_SAMPLE_A_ASM_VALUE   (LOCK_HBL_BIT_ASM | UNLOCK_HBL_BIT_ASM | SHIELD_0_BIT_ASM)
#define PREPARE_SAMPLE_B_1_ASM_VALUE (LOCK_HBL_BIT_ASM | UNLOCK_HBL_BIT_ASM | LOCK_HBR_BIT_ASM | UNLOCK_HBR_BIT_ASM | SHIELD_1_BIT_ASM)
#define PREPARE_SAMPLE_B_2_ASM_VALUE (LOCK_HBL_BIT_ASM | UNLOCK_HBL_BIT_ASM | LOCK_HBR_BIT_ASM | UNLOCK_HBR_BIT_ASM | SHIELD_0_BIT_ASM)
#define PREPARE_SAMPLE_B_3_ASM_VALUE (LOCK_HBL_BIT_ASM | UNLOCK_HBL_BIT_ASM)
#define PREPARE_SAMPLE_B_5_ASM_VALUE (LOCK_HBL_BIT_ASM | UNLOCK_HBL_BIT_ASM | SHIELD_1_BIT_ASM)

	MODULE sensor_acquisition.s

	SECTION .data : DATA (4)
    THUMB

TOGGLE_MASK_ASM equ TOGGLE_MASK_ASM_VALUE
PREPARE_SAMPLE_A_ASM equ PREPARE_SAMPLE_A_ASM_VALUE;
PREPARE_SAMPLE_B_1_ASM equ PREPARE_SAMPLE_B_1_ASM_VALUE;
PREPARE_SAMPLE_B_2_ASM equ PREPARE_SAMPLE_B_2_ASM_VALUE;
PREPARE_SAMPLE_B_3_ASM equ PREPARE_SAMPLE_B_3_ASM_VALUE;
PREPARE_SAMPLE_B_4_ASM equ PREPARE_SAMPLE_B_5_ASM_VALUE;
ADC_VREF_MASK_ASM equ 0x1E;
ADC_SC1_ADCH_MASK_ASM equ 0x1F;
ADC_UNLOCK_MASK_ASM equ 0xE;
ADC_LOCK_MASK_ASM equ 9;
ADC_SC1_COCO_MASK_ASM equ 0x80;
ADC_SC1_COCO_SHIFT_ASM equ 7;

RIGHT_SHIFT_MEASURED_VALUE_LOCK equ 0;
RIGHT_SHIFT_MEASURED_VALUE_UNLOCK equ 0;

    IMPORT    S_UnlockRaw_ASM;
    IMPORT    S_LockRaw_ASM;

	SECTION .data : CODE (4)
    THUMB

    PUBLIC _SensorAcq_mcvd_both_scan

Toggle_Macro macro
    EOR    R2, R2, R3;
    STR    R2, [R1];
    endm


;/*!
;******************************************************************************
;FUNCTION     : _SensorAcq_mcvd_both_scan
;Input        : void
;Output       : void
;
;Global       :
;
;Functions called: Delay333khz,Delay400khz,DelayDischarge
;
;
;Description  : *  The MCVD  acquisition method works by sharing charge between the externel C-load capacitor
;  (Cl) and the sense electrode capacitance (Cs).
;  The charge sharing is carried out in the following sequence:
;  Step 1. Cl is shortly charged and connected in parallel with Cs . This causes charge to flow between the capacitors until
;  the charge is distributed completely between them.
;  Step1.1  Step 1. is repeated 40 times
;  Step 2. The voltage across Cs, due to the remaining charge, is digitized by the ADC (Sample A).
;  Step3. discharge both capacitors.
;  Step 4. Cs is shortly charged and connected in parallel with Cl . This causes charge to flow between the capacitors until
;  the charge is distributed completely between them.
;  Step4.1  Step 4. is reapeted 40 times
;  Step 4. The resulting voltage across Cs is digitized by the ADC (sample B).
;  The two ADC values sample A and sample B obtained are stored in the buffer.
;
;  When the sensor is touched the effective capacitance of the sensor electrode increases and becomes Cx + Ct. This
;  affects the amount of charge shared between the capacitors.
;  When pre-charging Cs and sharing with Cl,charge remaining on Cs decreases on touch and ADC input voltage decreases ,sample A take decreases value
;  When pre-charging Cl and sharing with Cs, charge transferred to Cs increases on touch and ADC input voltage increases.sample B take increases value
;******************************************************************************/
Generate_Acquisition_Signal:
    PUSH { lr }
    ;/* 5 pulses at 333khz */
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz

    ;/* shift phase */
    NOP
    NOP
    NOP
    BL Delay_400KHz

    ;/* 5 pulses at 400khz */
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz

    ;/* 2 pulses at 333khz */
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz

    ;/* shift phase */
    NOP
    NOP
    NOP
    BL Delay_333KHz

    ;/* 2 pulses at 333khz */
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz

    ;/* 5 pulses at 400khz */
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz

    ;/* shif phase */
    NOP
    NOP
    NOP
    BL Delay_333KHz

    ;/* 5 pulses at 333khz */
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz

    ;/* 2.5 pulses at 400khz */
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz

    ;/* shif phase */
    NOP
    NOP
    NOP
    BL Delay_400KHz

    ;/* 2.5 pulses at 400khz */
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz

    ;/* 5 pulses at 333khz */
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz
    Toggle_Macro
    BL Delay_333KHz

    ;/* shift phase */
    NOP
    NOP
    NOP
    BL Delay_400KHz

    ;/* 5 pulses at 400khz */
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    Toggle_Macro
    BL Delay_400KHz
    POP { lr }
    BX LR

DischargeADC:
    LDR    R4, =ADC_VREF_MASK_ASM; /*R3 keeps the value of mask used for UNLOCK channel*/
    ORR    R4, R4, R2;
    STR    R4, [R1];

    RefVal:
        LDR    R1, =0x4003B000u;           /*R1 keeps address of ADC0_SC1A[0]*/
        LDR    R2, [R1];                   /* R2 keeps the value from address keeped in R1 */

        LDR    R4, =ADC_SC1_COCO_MASK_ASM;
        LDR    R3, =ADC_SC1_COCO_SHIFT_ASM;

        AND    R2, R2, R4;
        LSL    R2, R2, R3;
        CMP    R2, #0;
        BLE    RefVal

    bx lr

_SensorAcq_mcvd_both_scan:
    PUSH { lr }
    cpsid i; /*Disable interrupts*/
    PUSH {R0-R9}; /* ASM START */

    LDR    R8, =RIGHT_SHIFT_MEASURED_VALUE_LOCK
    LDR    R9, =RIGHT_SHIFT_MEASURED_VALUE_UNLOCK

    ;/*********************************** SAMPLE A ***********************************/
    LDR    R1, =0x400FF098u;           /* R1 keeps address of PTC->PIDR */
    LDR    R2, [R1];                   /* R2 keeps the value from address keeped in R1 */

    LDR    R5, =0x400FF080u;           /* R5 keeps address of PTC->PDOR */
    LDR    R6, [R5]                    /* R6 keeps the value from address keeped in R5 */

    LDR    R3, =TOGGLE_MASK_ASM;       /* R3 keeps the value of mask used for toggle all pins */
    LDR    R4, =PREPARE_SAMPLE_A_ASM;  /* R4 keeps the value of mask used for prepare sample A */

    ;/*enable the HIGH-Z for all pins*/
    ORR    R2, R2, R3;
    STR    R2, [R1];

    LDR    R1, =0x400FF094u;           /* R1 keeps address of PTC->PDDR */
    LDR    R2, [R1];                   /* R2 keeps the value from address keeped in R1 */

    ;/*clear level*/
    BIC    R6, R6, R3
    STR    R6, [R5]

    ;/*clear direction*/
    ORR    R2, R2, R3;
    STR    R2, [R1];

    ;/*prepare sensor and cload*/
    BIC    R2, R2, R4
    STR    R2, [R1]

    ;/* toggle Cload => Cload to HIGH */
    ORR    R6, R6, R4
    STR    R6, [R5]

    BL Generate_Acquisition_Signal

    LDR    R1, =0x4003B000u;           /*R1 keeps address of ADC0_SC1A[0]*/
    LDR    R2, [R1];                   /* R2 keeps the value from address keeped in R1 */

    LDR    R4, =ADC_SC1_ADCH_MASK_ASM; /*R3 keeps the value of mask used for ADC_SC1_ADCH*/
    BIC    R2, R2, R4;

    BL Delay_Discharge
    BL DischargeADC
    BL Delay_Discharge
    BL Delay_Discharge

    LDR    R4, =ADC_LOCK_MASK_ASM; /*R3 keeps the value of mask used for UNLOCK channel*/
    ORR    R4, R4, R2;
    STR    R4, [R1];

    Adc_lock_sample_A:
        LDR    R1, =0x4003B000u;           /*R1 keeps address of ADC0_SC1A[0]*/
        LDR    R2, [R1];                   /* R2 keeps the value from address keeped in R1 */

        LDR    R4, =ADC_SC1_COCO_MASK_ASM;
        LDR    R3, =ADC_SC1_COCO_SHIFT_ASM;

        AND    R2, R2, R4;
        LSL    R2, R2, R3;
        CMP    R2, #0;
        BLE    Adc_lock_sample_A

    LDR    R1, =0x4003B048u;
    LDR    R2, [R1];

    LDR    R0, =S_LockRaw_ASM
    LSR    R7, R2, R8
    STRH    R7, [R0]

    BL Delay_Discharge
    BL Delay_Discharge

    LDR    R1, =0x4003B000u;           /*R1 keeps address of ADC0_SC1A[0]*/
    LDR    R2, [R1];                   /* R2 keeps the value from address keeped in R1 */

    LDR    R4, =ADC_SC1_ADCH_MASK_ASM; /*R3 keeps the value of mask used for ADC_SC1_ADCH*/
    BIC    R2, R2, R4;

    BL DischargeADC
    BL Delay_Discharge
    BL Delay_333KHz
    BL Delay_400KHz

    LDR    R4, =ADC_UNLOCK_MASK_ASM; /*R3 keeps the value of mask used for UNLOCK channel*/
    ORR    R4, R4, R2;
    STR    R4, [R1];

    Adc_unlock_sample_A:
        LDR    R1, =0x4003B000u;           /*R1 keeps address of ADC0_SC1A[0]*/
        LDR    R2, [R1];                   /* R2 keeps the value from address keeped in R1 */

        LDR    R4, =ADC_SC1_COCO_MASK_ASM;
        LDR    R3, =ADC_SC1_COCO_SHIFT_ASM;

        AND    R2, R2, R4;
        LSL    R2, R2, R3;
        CMP    R2, #0;
        BLE    Adc_unlock_sample_A

    LDR    R1, =0x4003B048u;
    LDR    R2, [R1];

    LDR    R0, =S_UnlockRaw_ASM
    LSR    R7, R2, R9
    STRH    R7, [R0]

    ;/* delay to match with low power acquisition */
    BL Delay_Discharge
    BL Delay_Discharge
    BL Delay_Discharge

    ;/*********************************** SAMPLE B ***********************************/
    LDR    R1, =0x400FF094u;           /* R1 keeps address of PTC->PDDR */
    LDR    R2, [R1];                   /* R2 keeps the value from address keeped in R1 */

    LDR    R5, =0x400FF080u;           /* R5 keeps address of PTC->PDOR */
    LDR    R6, [R5]                    /* R6 keeps the value from address keeped in R5 */

    LDR    R3, =TOGGLE_MASK_ASM;       /* R3 keeps the value of mask used for toggle all pins */

    ;/*clear level*/
    BIC    R6, R6, R3
    STR    R6, [R5]

    ;/*clear direction*/
    ORR    R2, R2, R3;
    STR    R2, [R1];

    BL Delay_Discharge

    LDR    R4, =PREPARE_SAMPLE_B_1_ASM;  /* R4 keeps the value of mask used for prepare sample B_1 */
    LDR    R3, =PREPARE_SAMPLE_B_2_ASM;  /* R4 keeps the value of mask used for prepare sample B_2 */

    ;/*tristate Cload, Csense and Sh1*/
    BIC    R2, R2, R4
    STR    R2, [R1]

    ;/*set Cload, Csense and Sh0 to output*/
    ORR    R2, R2, R3
    STR    R2, [R1]

    ;/*set Cload, Csense and Sh0 to high*/
    ORR    R6, R6, R3
    STR    R6, [R5]

    BL Delay_Discharge_LP_Match
    BL Delay_Discharge_LP_Match
    BL Delay_Discharge_LP_Match

    LDR    R4, =PREPARE_SAMPLE_B_3_ASM;  /* R4 keeps the value of mask used for prepare sample B_3 */
    LDR    R3, =PREPARE_SAMPLE_B_4_ASM;  /* R4 keeps the value of mask used for prepare sample B_4 */

    ;/*tristate Cload*/
    BIC    R2, R2, R4
    STR    R2, [R1]

    ;/*set Cload and Sh1 to low*/
    BIC    R6, R6, R3
    STR    R6, [R5]

    LDR    R3, =TOGGLE_MASK_ASM;       /* R3 keeps the value of mask used for toggle all pins */

    BL Generate_Acquisition_Signal
    BL Delay_Discharge
    BL Delay_Discharge
    BL Delay_333KHz
    BL Delay_400KHz

    LDR    R1, =0x4003B000u;           /*R1 keeps address of ADC0_SC1A[0]*/
    LDR    R2, [R1];                   /* R2 keeps the value from address keeped in R1 */

    LDR    R4, =ADC_SC1_ADCH_MASK_ASM; /*R3 keeps the value of mask used for ADC_SC1_ADCH*/
    BIC    R2, R2, R4;

    BL DischargeADC

    LDR    R4, =ADC_LOCK_MASK_ASM; /*R3 keeps the value of mask used for UNLOCK channel*/
    ORR    R4, R4, R2;
    STR    R4, [R1];
    
    Adc_lock_sample_B:
        LDR    R1, =0x4003B000u;           /*R1 keeps address of ADC0_SC1A[0]*/
        LDR    R2, [R1];                   /* R2 keeps the value from address keeped in R1 */

        LDR    R4, =ADC_SC1_COCO_MASK_ASM;
        LDR    R3, =ADC_SC1_COCO_SHIFT_ASM;

        AND    R2, R2, R4;
        LSL    R2, R2, R3;
        CMP    R2, #0;
        BLE    Adc_lock_sample_B

    LDR    R1, =0x4003B048u;
    LDR    R2, [R1];

    LDR    R0, =S_LockRaw_ASM+0x02
    LSR    R7, R2, R8
    STRH    R7, [R0]

    BL Delay_Discharge
    BL Delay_Discharge
    BL Delay_Discharge
    BL Delay_333KHz

    LDR    R1, =0x4003B000u;           /*R1 keeps address of ADC0_SC1A[0]*/
    LDR    R2, [R1];                   /* R2 keeps the value from address keeped in R1 */

    LDR    R4, =ADC_SC1_ADCH_MASK_ASM; /*R3 keeps the value of mask used for ADC_SC1_ADCH*/
    BIC    R2, R2, R4;

    BL DischargeADC
    BL Delay_400KHz
    BL Delay_400KHz

    LDR    R4, =ADC_UNLOCK_MASK_ASM; /*R3 keeps the value of mask used for UNLOCK channel*/
    ORR    R4, R4, R2;
    STR    R4, [R1];

    Adc_unlock_sample_B:
        LDR    R1, =0x4003B000u;           /*R1 keeps address of ADC0_SC1A[0]*/
        LDR    R2, [R1];                   /* R2 keeps the value from address keeped in R1 */

        LDR    R4, =ADC_SC1_COCO_MASK_ASM;
        LDR    R3, =ADC_SC1_COCO_SHIFT_ASM;

        AND    R2, R2, R4;
        LSL    R2, R2, R3;
        CMP    R2, #0;
        BLE    Adc_unlock_sample_B

    LDR    R1, =0x4003B048u;
    LDR    R2, [R1];

    LDR    R0, =S_UnlockRaw_ASM+0x02
    LSR    R7, R2, R9
    STRH    R7, [R0]

    LDR    R1, =0x4003B000u;           /*R1 keeps address of ADC0_SC1A[0]*/
    LDR    R2, [R1];                   /* R2 keeps the value from address keeped in R1 */

    LDR    R4, =ADC_SC1_ADCH_MASK_ASM; /*R3 keeps the value of mask used for ADC_SC1_ADCH*/
    BIC    R2, R2, R4;

    BL DischargeADC

    LDR    R1, =0x400FF094u;           /* R1 keeps address of PTC->PDDR */
    LDR    R2, [R1];                   /* R2 keeps the value from address keeped in R1 */

    LDR    R5, =0x400FF080u;           /* R5 keeps address of PTC->PDOR */
    LDR    R6, [R5]                    /* R6 keeps the value from address keeped in R5 */

    LDR    R3, =TOGGLE_MASK_ASM;       /* R3 keeps the value of mask used for toggle all pins */

    ;/* delay to match with low power acquisition */
    BL Delay_Discharge
    BL Delay_Discharge
    BL Delay_Discharge
    BL Delay_Discharge
    BL Delay_Discharge

    ;/*clear level*/
    BIC    R6, R6, R3
    STR    R6, [R5]

    ;/*clear direction*/
    ORR    R2, R2, R3;
    STR    R2, [R1];

    LDR    R1, =0x400FF098u;           /* R1 keeps address of PTC->PIDR */
    LDR    R2, [R1];                   /* R2 keeps the value from address keeped in R1 */

    ;/*disable HIGH-Z for all pins*/
    BIC    R2, R2, R4
    STR    R2, [R1]

    POP {R0-R9}; /* ASM STOP */
    cpsie i; /*Enable interrupts*/

    POP { lr }
	
	bx lr

    Delay_Discharge:
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    Delay_Discharge_LP_Match:
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
Delay_333KHz:
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
Delay_400KHz:
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    BX LR

    end
