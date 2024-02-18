;/*------------------------------------------------------------------------------------------------+
;| File: sensor_aquisition_mcvd.asm                                                                |
;+-------------------------------------------------------------------------------------------------+
;| Project: Audi eTab                                                                              |
;+-------------------------------------------------------------------------------------------------+
;| Short description: The file contains the implementation of the capacitive sensors acquisition   |
;+------------------------------------------------------------------------------------------------*/

#include "sensor_aquisition.hc"
#include "sensor_aquisition_mcvd.h"
#ifdef INTEGRATE_FROM_V4
/*#include  <ior5f10aae.h>*/
/*#include  <ior5f10aae_ext.h>*/
#endif

        MODULE __SENSOR_MCVD__
 
         section DATA:DATA(0)
        IMPORT  _BO_asm_SampleAB_Flag  ;
        IMPORT  _BO_PowerUpDone_Flag;
        IMPORT     _S_LockRaw;
        IMPORT     _S_UnlockRaw
       
        /*define _buffer  */
        RSEG RCODE:CODE(0)
        
 
        PUBLIC  _SensorAcq_mcvd_both_scan
;/*------------------------------------------------------------------------
;MACRO       : TooglePortDirectionReg
;Author      : ybadal
;Input       :
;Description : macro to toggle port
;------------------------------------------------------------------------*/
TooglePortDirectionReg macro op,mask
        MOV     A,op
        XOR     A,mask
        MOV     op,A
       endm
;/*------------------------------------------------------------------------
;MACRO       : TogglePinLevelReg
;Author      : ybadal
;Input       :
;Description : macro to toggle pin
;------------------------------------------------------------------------*/ 
TogglePinLevelReg  macro portpin,portNum
                 XOR portpin,portNum;    ;/* toggle pin */
                 endm

;/*------------------------------------------------------------------------
;MACRO       : ClearRegMask
;Author      : hcostin
;Input       : negation of mask to be cleared
;Description : macro to clear register
;------------------------------------------------------------------------*/ 
ClearRegMask MACRO reg,mask
                 MOV    A,reg
                 AND    A,mask
                 MOV    reg,A
                 endm

;/*------------------------------------------------------------------------
;MACRO       : SetRegMask
;Author      : hcostin
;Input       : mask to be set
;Description : macro to set register
;------------------------------------------------------------------------*/ 
SetRegMask MACRO reg,mask
                 MOV    A,reg
                 OR     A,mask
                 MOV    reg,A
                 endm

;/*!
;******************************************************************************
;FUNCTION     : _SensorAcq_mcvd_both_scan
;author       : hcostin
;Input        : void
;Output       : void
;
;Global       : _BO_asm_SampleAB_Flag
;
;Functions called: Delay333khz,Delay400khz,DelayDischarge,DelayDischarge5us
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
_SensorAcq_mcvd_both_scan:

  ;/*Enable write to PER0*/
    MOV     A,#0xFE
    MOVW    HL,#IAWCTL
    AND     A,[HL]
    MOV     [HL],A
 ;/* turn-ON adc (set ON bit) */
    MOVW     HL,#PER0
    SET1     [HL].5;                  ;/* turn-ON adc (set ON bit) */

  ;/*disable write to PER0*/
    ONEB    A
    MOVW    HL,#IAWCTL
    OR      A,[HL]
    MOV     [HL],A

    CLRB    A
    MOV     _BO_asm_SampleAB_Flag,A  /* 0 to variable _BO_asm_SampleAB_Flag */

    ClearRegMask BOTH_SENSOR_DIRECTION_GPIO,BOTH_SENSOR_ALL_PINS_NEG;
    ClearRegMask BOTH_SENSOR_LEVEL_GPIO,BOTH_SENSOR_ALL_PINS_NEG;

    ;/*prepare sensor and cload*/
    SetRegMask BOTH_SENSOR_DIRECTION_GPIO,CONST_VAL(BOTH_HBL | BOTH_SHIELD0);
    ;/* toggle Cload => Cload to HIGH */
    SetRegMask BOTH_SENSOR_LEVEL_GPIO,CONST_VAL(BOTH_HBL | BOTH_SHIELD0);

    call DelayDischarge;

    BR bothAquisition_beginn

;/** MCVD BURST   ******************************************************/
    bothAquisition_beginn:;

    ;/* 5 pulses at 333khz */
    REPT 10
        TooglePortDirectionReg BOTH_SENSOR_DIRECTION_GPIO,BOTH_SENSOR_ALL_PINS ;/* toggle Cshield,Csense and Cload */
        call Delay333khz ;make frequnce delay
    ENDR

    ;/* shift phase */
    REPT 3
        NOP
    ENDR
    call Delay400khz ;make frequnce delay

    ;/* 5 pulses at 400khz */
    REPT 10
        TooglePortDirectionReg BOTH_SENSOR_DIRECTION_GPIO,BOTH_SENSOR_ALL_PINS ;/* toggle Cshield,Csense and Cload */
        call Delay400khz ;make frequnce delay
    ENDR

    ;/* 2 pulses at 333khz */
    REPT 4
        TooglePortDirectionReg BOTH_SENSOR_DIRECTION_GPIO,BOTH_SENSOR_ALL_PINS ;/* toggle Cshield,Csense and Cload */
        call Delay333khz ;make frequnce delay
    ENDR

    ;/* shift phase */
    REPT 3
        NOP
    ENDR
    call Delay333khz ;make frequnce delay

    ;/* 2 pulses at 333khz */
    REPT 4
        TooglePortDirectionReg BOTH_SENSOR_DIRECTION_GPIO,BOTH_SENSOR_ALL_PINS ;/* toggle Cshield,Csense and Cload */
        call Delay333khz ;make frequnce delay
    ENDR

    ;/* 5 pulses at 400khz */
    REPT 10
        TooglePortDirectionReg BOTH_SENSOR_DIRECTION_GPIO,BOTH_SENSOR_ALL_PINS ;/* toggle Cshield,Csense and Cload */
        call Delay400khz ;make frequnce delay
    ENDR

    ;/* shif phase */
    REPT 3
        NOP
    ENDR
    call Delay333khz ;make frequnce delay

    ;/* 5 pulses at 333khz */
    REPT 10
        TooglePortDirectionReg BOTH_SENSOR_DIRECTION_GPIO,BOTH_SENSOR_ALL_PINS ;/* toggle Cshield,Csense and Cload */
        call Delay333khz ;make frequnce delay
    ENDR

    ;/* 2.5 pulses at 400khz */
    REPT 5
        TooglePortDirectionReg BOTH_SENSOR_DIRECTION_GPIO,BOTH_SENSOR_ALL_PINS ;/* toggle Cshield,Csense and Cload */
        call Delay400khz ;make frequnce delay
    ENDR

    ;/* shif phase */
    REPT 3
        NOP
    ENDR
    call Delay400khz ;make frequnce delay

    ;/* 2.5 pulses at 400khz */
    REPT 5
        TooglePortDirectionReg BOTH_SENSOR_DIRECTION_GPIO,BOTH_SENSOR_ALL_PINS ;/* toggle Cshield,Csense and Cload */
        call Delay400khz ;make frequnce delay
    ENDR

    ;/* 5 pulses at 333khz */
    REPT 10
        TooglePortDirectionReg BOTH_SENSOR_DIRECTION_GPIO,BOTH_SENSOR_ALL_PINS ;/* toggle Cshield,Csense and Cload */
        call Delay333khz ;make frequnce delay
    ENDR

    ;/* shift phase (maybe not needed)*/
    REPT 3
        NOP
    ENDR
    call Delay400khz ;make frequnce delay

    ;/* 5 pulses at 400khz */
    REPT 10
        TooglePortDirectionReg BOTH_SENSOR_DIRECTION_GPIO,BOTH_SENSOR_ALL_PINS ;/* toggle Cshield,Csense and Cload */
        call Delay400khz ;make frequnce delay
    ENDR

#ifndef VARIANT_1
    MOV A,U8_LOCK_C_LOAD_AD_CHANNEL ;/*set cload lock adc channel*/
    MOV ADS,A
#endif

    MOV     A,_BO_asm_SampleAB_Flag
    BT      A.0,both_Acquisition_SampleB   /* if sample A skip next instruction  */

;/*** Acquisition Sample A (A-Burst has been executed) ***********************/
#ifndef VARIANT_1
    ;/*LOCK sample A*/    
    CLR1 IF1H.0  ;/*ADIF*/
    SET1 ADM0.0  ;/*ADCE*/
    SET1 ADM0.7  ;/*ADCS set GO bit */
    WAIT_FOR_LOCK_ADC_DONE2:
    MOVW     HL,#IF1H
    BF     [HL].0,WAIT_FOR_LOCK_ADC_DONE2;

    MOVW HL,#(_S_LockRaw&0xffff);
    MOVW AX,S:ADCR
    SHRW AX,6
    movw [HL+0],AX
#endif

    ;/*UNLOCK sample A*/
    MOV A,U8_UNLOCK_C_LOAD_AD_CHANNEL ;/*set unlock cload adc channel*/
    MOV ADS,A

    CLR1 IF1H.0  ;/*ADIF*/
    SET1 ADM0.0  ;/*ADCE*/
    SET1 ADM0.7  ;/*ADCS set GO bit */

    WAIT_FOR_UNLOCK_ADC_DONE2_BOTH:
    MOVW     HL,#IF1H
    BF     [HL].0,WAIT_FOR_UNLOCK_ADC_DONE2_BOTH;

    MOVW HL,#(_S_UnlockRaw&0xffff);
    MOVW AX,S:ADCR
    SHRW AX,6
    movw [HL+0],AX

    CLR1 ADM0.0  ;/*ADCE*/

    ;/* PREPARE FOR SAMPLE B TOGGLE */
    ClearRegMask BOTH_SENSOR_DIRECTION_GPIO,BOTH_SENSOR_ALL_PINS_NEG;
    ClearRegMask BOTH_SENSOR_LEVEL_GPIO,BOTH_SENSOR_ALL_PINS_NEG;

    ;/*Enable ISR for LIN*/
    ;call EnableISR;

    ;call DelayDischarge5us;

    SetRegMask BOTH_SENSOR_DIRECTION_GPIO,CONST_VAL(BOTH_HBL | BOTH_HBR | BOTH_SHIELD1);
    ClearRegMask BOTH_SENSOR_DIRECTION_GPIO,CONST_VAL(~(BOTH_HBL | BOTH_HBR | BOTH_SHIELD0));

    SetRegMask BOTH_SENSOR_LEVEL_GPIO,CONST_VAL(BOTH_HBL | BOTH_HBR | BOTH_SHIELD0);

    call DelayDischarge5us;
    call DelayDischarge;

    ONEB    A;
    MOV    _BO_asm_SampleAB_Flag,A;

    SetRegMask BOTH_SENSOR_DIRECTION_GPIO,CONST_VAL(BOTH_HBL);
    ClearRegMask BOTH_SENSOR_LEVEL_GPIO,CONST_VAL(~(BOTH_HBL | BOTH_SHIELD1));

    BR bothAquisition_beginn

;/*** Acquisition Sample B (B-Burst has been executed) *************************/
    ;/*LOCK sample B*/
    both_Acquisition_SampleB:
#ifndef VARIANT_1
    MOV A,U8_LOCK_C_LOAD_AD_CHANNEL ;/*set cload lock adc channel*/
    MOV ADS,A

    CLR1 IF1H.0  /*ADIF*/
    SET1 ADM0.0  /*ADCE*/
    SET1 ADM0.7 /*ADCS set GO bit */
    WAIT_FOR_LOCK_ADC_DONE3:
    MOVW     HL,#IF1H
    BF     [HL].0,WAIT_FOR_LOCK_ADC_DONE3;

    MOVW HL,#(_S_LockRaw&0xffff);
    MOVW AX,S:ADCR
    SHRW AX,6
    movw [HL+2],AX
#endif

    ;/*UNLOCK sample B*/
    MOV A,U8_UNLOCK_C_LOAD_AD_CHANNEL ;/*set cload lock adc channel*/
    MOV ADS,A

    CLR1 IF1H.0  /*ADIF*/
    SET1 ADM0.0  /*ADCE*/
    SET1 ADM0.7 /*ADCS set GO bit */
    WAIT_FOR_UNLOCK_ADC_DONE3_BOTH:
    MOVW     HL,#IF1H
    BF     [HL].0,WAIT_FOR_UNLOCK_ADC_DONE3_BOTH;

    MOVW HL,#(_S_UnlockRaw&0xffff);
    MOVW AX,S:ADCR
    SHRW AX,6
    movw [HL+2],AX

    CLR1 ADM0.0  ;/*ADCE*/

    ;/* END ACQUISITION: */
    SetRegMask BOTH_SENSOR_DIRECTION_GPIO,CONST_VAL(BOTH_HBR | BOTH_SHIELD0)

    ClearRegMask BOTH_SENSOR_LEVEL_GPIO,CONST_VAL(~(BOTH_HBR | BOTH_SHIELD0))
    ClearRegMask BOTH_SENSOR_DIRECTION_GPIO,CONST_VAL(~(BOTH_HBR | BOTH_SHIELD0))

    ClearRegMask BOTH_SENSOR_LEVEL_GPIO,CONST_VAL(~(BOTH_HBL | BOTH_SHIELD0))
    ClearRegMask BOTH_SENSOR_DIRECTION_GPIO,CONST_VAL(~(BOTH_HBL | BOTH_SHIELD0))

    MOV     A,#0xFE
    MOVW    HL,#IAWCTL
    AND     A,[HL]
    MOV     [HL],A
    MOVW     HL,#PER0
    CLR1     [HL].5;                  ;/* turn-off adc (set ON bit) */

  ;/*disable write to PER0*/
    ONEB    A
    MOVW    HL,#IAWCTL
    OR      A,[HL]
    MOV     [HL],A

    RET
/*!
******************************************************************************
FUNCTION     : DelayDischarge5us
author       : hcostin
Input        : void
Output       : void
******************************************************************************/
DelayDischarge5us:
    REPT 154
    nop
    ENDR
    RET

/*!
******************************************************************************
FUNCTION     : DelayDischarge
author       : hcostin
Input        : void
Output       : void
******************************************************************************/
DelayDischarge:
    REPT 58
    nop
    ENDR
    RET

/*!
******************************************************************************
FUNCTION     : Delay333khz
author       : hcostin
Input        : void
Output       : void
******************************************************************************/
Delay333khz:
    REPT 36
    nop
    ENDR
    RET

/*!
******************************************************************************
FUNCTION     : Delay400khz
author       : hcostin
Input        : void
Output       : void
******************************************************************************/
Delay400khz:
    REPT 28
    nop
    ENDR
    RET

/*!
******************************************************************************
FUNCTION     : EnableISR
author       : hcostin
Input        : void
Output       : void
******************************************************************************/
EnableISR:
    EI      ;/*need to enable isrs in between to keep Lin reaction times*/
    REPT 16 ;/* maximum isr service time*/
    nop
    ENDR
    DI
    RET

END
; /* END SENSOR_ACQUISITION_ASM_ */
