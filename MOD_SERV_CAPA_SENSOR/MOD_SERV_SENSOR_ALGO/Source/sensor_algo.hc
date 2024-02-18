/*!
 * \defgroup <module_group (sensor_algo.c) Module purpose>
 * \{
 ******************************************************************************
 * \image html "Kopf_oZusatz_A4hoch_4C.jpg"
 *
 * \par Module Owner:
 *   Huf H&uuml;lsbeck & F&uuml;rst GmbH & Co. KG \n
 *   Steeger Str. 17 \n
 *   42551 Velbert \n
 *   Department PDE-S
 *
 * \par Initial Project:
 *    0678.005 VW_Vip
 *
 ******************************************************************************
 * \par Description:
 *  after performs the capacitive measurement of all enabled sensors,
 * The measured signals for each sensor are then processed to
 * check for user touches, releases.
 *
 *
 ******************************************************************************
 *
 *  $Workfile:   sensor_algo.hc  $
 *  $Revision:   1.4  $
 *  $Date:   Apr 09 2019 15:59:10  $
 *  $Author:   hlehman2  $
 *
 ******************************************************************************
 * Change history:
 *
 *
 *
 * Add new lines above
 ******************************************************************************
 *
 * \par Purpose:
 *    i.e Operating System, Service Layer
 *
 * \par Compiler:
 *    ANSI
 *
 * \par Controller:
 *    independant
 *
 * \par Resources:
 *    | Resource      | Amount    | Remarks     |
 *    | ------------- | --------: | ----------- |
 *    | ROM           |  X Byte   |             |
 *    | RAM           |  X Byte   |             |
 *    | EEPROM        |  X Byte   |             |
 *    | Runtime Init  |    X ms   |             |
 *    | Runtime Task  |    X ms   |             |
 *
 * \par Quality:
 *    | Factor            | Excl  | Good  | Fair  | Poor  |
 *    | ----------------- | ----: | ----: | ----: | ----: |
 *    | _Maintainability_ |   0 % |   0 % |   0 % |   0 % |
 *    | Analyzability     |   0 % |   0 % |   0 % |   0 % |
 *    | Changeability     |   0 % |   0 % |   0 % |   0 % |
 *    | Stability         |   0 % |   0 % |   0 % |   0 % |
 *    | Testability       |   0 % |   0 % |   0 % |   0 % |
 *
 * \par MISRA rules violations:
 *     \li none(?)
 *
 ******************************************************************************
 *
 * \attention
 *   \li text for Information, to do ..
 *
 ******************************************************************************
*/

#ifndef SENSOR_ALGO_HC
  #define SENSOR_ALGO_HC

#include "typedefs.h"

/* polyspace:begin <MISRA-C3:2.5 : Not a defect : Justify with annotations > Libraries are made for more than only this single project and therefore they SHALL BE allowed to contain unused macros*/

/* polyspace:begin <MISRA-C3:19.4 : Not a defect : Justify with annotations > defines to concatenate 2 strings in the pre-compiler,must be unbraced */

#define UNLOCK_SENSOR       ER
#define LOCK_SENSOR         VR
  /* polyspace:end <MISRA-C3:19.4 : Not a defect : Justify with annotations > */ 

/* It will be removed in the moment when it is clear that the touch state is not necessary anymore */
#define TOUCH_DISABLED
/* polyspace:begin <MISRA-C3:2.3 : Not a defect : Justify with annotations > Should be keept for future usage */
typedef struct
{
    XINT approach:1;
    XINT touch:1;
    XINT bit2:1;
    XINT bit3:1;
    XINT bit4:1;
    XINT bit5:1;
    XINT bit6:1;
    XINT bit7:1;
}BOOL_BITS_T;
/* polyspace:end <MISRA-C3:2.3 : Not a defect : Justify with annotations > Should be keept for future usage */

/* polyspace:end <MISRA-C3:19.4: Not a defect : Justify with annotations > */
/* polyspace:end <MISRA-C3:2.5 : Not a defect : Justify with annotations > */
#endif /* SENSOR_ALGO_HC */
 
/* Automatic logging by PVCS ***********************************************

$Log::   J:/vmfs/VW/1508.008_380_ODH/archives/3_Coding/ECU_NFC_STACK-NXP/MCU_RL78/MOD_SERV_CAPA_SENSOR/MOD_SERV_SENSOR_ALGO/Source/senso$
 * 
 *    Rev 1.4   Apr 09 2019 15:59:10   hlehman2
 * Several Misra fixes
 * 
 *    Rev 1.3   Apr 04 2019 11:08:02   hlehman2
 * MISRA fix
 * 
 *    Rev 1.2   May 30 2018 11:02:38   ybadal
 * hall sensor added.
 * 
 *    Rev 1.1   06 Apr 2018 08:07:26   ybadal
 * HIS and Misra partialy fixed, based on algo from VW 511 project actual version.
 * 
 *    Rev 1.10   21 Dec 2015 16:32:26   ybadal
 * misra justifications added.
 * 
 *    Rev 1.9   21 Dec 2015 15:33:28   ybadal
 * prosecution of misra violations correction.
 * 
 *    Rev 1.8   17 Dec 2015 18:02:26   ybadal
 * several misra violations fixed.
 * 
 *    Rev 1.7   15 Dec 2015 16:07:20   ybadal
 * bugs fixed for some misra violations.
 * 
 *    Rev 1.6   14 Dec 2015 16:00:50   ybadal
 * moduls and functions Headers changed to HUF standard header.
 * 
 *    Rev 1.5   09 Sep 2015 10:58:18   umuelle3
 * MISRA changes proposed by Polyspace.
 * 
 *    Rev 1.4   02 Jun 2015 13:12:14   ybadal
 * Diverse TT Punkte und Review Punkte.
 * 
 *    Rev 1.3   29 May 2015 14:24:40   ybadal
 * - Diverse TT Reviews weiter implementiert.
 * - einige Misra Violation behoben.
 * 
 *    Rev 1.2   Jan 26 2015 15:08:48   mstei
 * Changes for compliance with CSpec-095 Rev. 01 - Guideline for Software Coding.pdf:
 * - name of the project changed in the header of the file
 * 
 *    Rev 1.1   17 Jul 2014 10:12:58   ybadal
 * Code Umsetzung zum Review  von 15.07.2014
 * 
 *    Rev 1.0   28 Mar 2014 14:10:44   ybadal
 * Initial revision.
 * 
 *    Rev 1.0   25 Nov 2013 09:44:18   ufalkne
 * Initial revision.
 * 
 *    Rev 1.0   Oct 24 2013 15:48:14   pclemen
 * Initial revision.
 * 
*********************************************************** end of comment */
