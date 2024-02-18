
/*------------------------------------------------------------------------------------------------+
| File: config.h	                                                                              |
+-------------------------------------------------------------------------------------------------+
| Project: Library                                                                                |
+-------------------------------------------------------------------------------------------------+
| Short description:                                                                              |
| Use this file to define some configurations.                                                    |
|                                                                                                 |
+-------------------------------------------------------------------------------------------------+
| WARNING!!!!!!!!!!!!!!!!!!!!!!!                                                                  |
| THIS FILE IS INCLUDED ALSO IN ASM.                                                              |
| ANYTHING ELSE EXCEPT OF DEFINES COULD AFFECT THE ASM FILE.                                      |
| EVERYTIME WHEN YOU CHANGE THIS FILE PERFORM A CLEAN BUILD!                                      |
+-------------------------------------------------------------------------------------------------+
*/

#ifndef CONFIG_H_							/* To avoid double inclusion */
#define CONFIG_H_

/* IF YOU WANT TO CHANGE ANYTHING READ THE FILE DESCRIPTION !!! */

/* SW Version */
#define PARAM_VER_BYTE_EL_VAR             0x05        /* Electronic Version */
#define PARAM_VER_BYTE_SW_PREFIX          0x09        /* Run */
#define PARAM_VER_BYTE_SW_SUFFIX          0x08        /* Sprint */
#define PARAM_VER_BYTE_SW_ENG_DROP        0x00        /* Engineering Drop - 0 for official releases, 0-FF for an engineering drop */

/* Stringized variant for diag responses. */
#define RUN                 (U8)'9'        /* Run */
#define SPRINT              (U8)'8'        /* Sprint */
#define ENGDROP             (U8)'0'        /* Engineering Drop - 0 for official releases, 0-FF for an engineering drop */

#define ECU_VAR             (U8)'5'        /* Electronic Version */


/* B2 Read by Identifier Data */
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define SUPPLIER_ID_U16                         (U16)0x0072U
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define FUNCTION_ID_U16                         (U16)0x0100U
/* polyspace < MISRA-C3:2.5 : Not a defect : Justify with annotations > Should be kept for future usage */
#define VARIANT_ID_U8                           (U8)PARAM_VER_BYTE_EL_VAR /* from KS3 */

#define V_COMP_IAR_S32

/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

VERY IMPORTANT:
TO TURN ON SWITCH WITH THIS AT LINE 234 IN AUTOSAR_BSW/CfgPrj/Appl/GenData/src/Port_PBcfg.c :
{(Port_InternalPinIdType)4, (uint32)0x00000100, (uint8)0, (Port_PinDirectionType)2, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
TO TURN OFF SWITCH BACK WITH:
{(Port_InternalPinIdType)4, (uint32)0x00000700, (uint8)0, (Port_PinDirectionType)1, (boolean)FALSE, (boolean)FALSE, (boolean)TRUE},

THE RS232 WORKS AT 1.35Mbaud IN EVERY STATE

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/
/* #define RS232_ON */
/* polyspace+2 MISRA-C3:8.6 [Not a defect:Low] "external identifiers are different" */
/* polyspace+1 MISRA-C3:5.1 [Justified:Low] "External identifiers are different" */
extern const U8 VW_Logical_Software_Block_Version_ASW[4];

#endif /* CONFIG_H_ */
