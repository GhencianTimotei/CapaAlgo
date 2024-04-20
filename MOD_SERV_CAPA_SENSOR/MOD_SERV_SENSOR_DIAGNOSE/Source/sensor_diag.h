

#ifndef SENSOR_DIAG_H
#define SENSOR_DIAG_H


#ifdef SENSOR_DIAG_C
	#define SENSOR_DIAG_EXPORT
#else
	#define SENSOR_DIAG_EXPORT extern
#endif



#include "sensor_diag.hc"
#include "sensor_diag.hi"
#include "S32K144.h"
#define SET_PTA_RS232_OUTPUT()    { PTA->PDDR |= RS232_MASK; }
#define SET_PTA_RS232_INPUT()     { PTA->PDDR &= ~(RS232_MASK); }

#define SET_PTA_RS232_LOW()      { PTA->PDOR &= ~(RS232_MASK); }
#define SET_PTA_RS232_HIGH()     { PTA->PDOR |= (RS232_MASK); }

#define SET_PTA_RS232_PCOR()     { PTA->PCOR |= (RS232_MASK); }
#define SET_PORTA_RS232()        { PORTA->PCR[4] |= 0x100; }
extern void NfcDevMsg_SendMessage();
#endif
