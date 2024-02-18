/* polyspace < MISRA-C3:D4.10 : Not a defect : Justify with annotations > Precaution taken */
/*
 * PlayProtection.h
 *
 *  Created on: 06 May 2022
 *      Author: Petre
 *
 *  HOW TO USE THIS MODULE:
 *  1. For a new component you have to declare a new enum element into PlayProt_enConfigElemType.
 *      This enum should be correlated to the possition into arrays from C file.
 *  2. Into C file you have to add a new element into PlayProt_configConst which contains configuration from DDF and pointer to functions callbacks
 */
#ifndef MOD_APPL_PLAY_PROT_PLAYPROTECTION_H_
#define MOD_APPL_PLAY_PROT_PLAYPROTECTION_H_

#include "Std_Types.h"
#include "Platform_Types.h"

/* polyspace+1 MISRA-C3:2.4 [Justified:Low] "Added for further implementation." */
typedef enum configElem {
    PlayProt_inductive = 0u,
    PlayProt_capaLock,
    PlayProt_nrOfElements
} PlayProt_enConfigElemType;

extern void PlayProt_mainRunnable(void);
extern void PlayProt_mainRunSleep(void);
extern void PlayProt_init(void);
extern U8 PlayProt_getActivationCounter(PlayProt_enConfigElemType usedComponent);
extern U8 PlayProt_getActiveState(PlayProt_enConfigElemType usedComponent);
extern void PlayProt_writeInductiveValue(U8 *signalVal);
extern void PlayProt_writeUnlockValue(U8 *signalVal);
extern void PlayProt_writeLockValue(U8 *signalVal);
extern void PlayProt_updateParameter(void);
extern U8 PlayProt_getInductiveActiveTime(void);

#endif /* MOD_APPL_PLAY_PROT_PLAYPROTECTION_H_ */