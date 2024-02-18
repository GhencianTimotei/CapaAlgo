/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Dcm_BaseTypes.h
 *        \brief  Public data type definition interface of DCM
 *
 *      \details  MICROSAR DCM based on AR 4.0.3
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
#if !defined(DCM_BASETYPES_H)
# define DCM_BASETYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
/* DID operation types - bitmapped which gives the application the opportunity to "OR" multiple operations per DID */
#  define DCM_DID_OP_READ                                            ((Dcm_DidOpType)0x01u)
#  define DCM_DID_OP_WRITE                                           ((Dcm_DidOpType)0x02u)
#  define DCM_DID_OP_IO                                              ((Dcm_DidOpType)0x04u)
#  define DCM_DID_OP_SCALINGINFO                                     ((Dcm_DidOpType)0x08u)
#  define DCM_DID_OP_DEFINE                                          ((Dcm_DidOpType)0x10u)
/*! Not used directly!
#  define DCM_DID_OP_IS_AVAILABLE                                    ((Dcm_DidOpType)0x20u)
*/
#  define DCM_DID_OP_ROE                                             ((Dcm_DidOpType)0x40u)

/* Service port operation types */
#  define DCM_DIDMGR_OPTYPE_READ                                     ((Dcm_DidMgrOpCallMemType)0x01u)
#  define DCM_DIDMGR_OPTYPE_READLENGTH                               ((Dcm_DidMgrOpCallMemType)0x02u)
#  define DCM_DIDMGR_OPTYPE_READCHKCOND                              ((Dcm_DidMgrOpCallMemType)0x04u)
#  define DCM_DIDMGR_OPTYPE_RANGEREAD                                DCM_DIDMGR_OPTYPE_READ
#  define DCM_DIDMGR_OPTYPE_RANGEREADLENGTH                          DCM_DIDMGR_OPTYPE_READLENGTH

#  define DCM_DIDMGR_OPTYPE_WRITE                                    ((Dcm_DidMgrOpCallMemType)0x01u)
#  define DCM_DIDMGR_OPTYPE_RANGEWRITE                               DCM_DIDMGR_OPTYPE_WRITE

/* this value shall be for both OP_READ and OP_WRITE OP_TYPES the same! */
#  define DCM_DIDMGR_OPTYPE_RANGEISDIDAVAILABLE                      ((Dcm_DidMgrOpCallMemType)0x10u)

#  define DCM_DIDMGR_OPTYPE_GETSCALING                               ((Dcm_DidMgrOpCallMemType)0x01u)

#  define DCM_DIDMGR_OPTYPE_DEFINE                                   ((Dcm_DidMgrOpCallMemType)0x01u)

#  define DCM_DIDMGR_OPTYPE_IO_RETCTRL2ECU                           ((Dcm_DidMgrOpCallMemType)0x01u)
#  define DCM_DIDMGR_OPTYPE_IO_RST2DEF                               ((Dcm_DidMgrOpCallMemType)0x02u)
#  define DCM_DIDMGR_OPTYPE_IO_FRZCURSTATE                           ((Dcm_DidMgrOpCallMemType)0x04u)
#  define DCM_DIDMGR_OPTYPE_IO_SHRTTRMADJ                            ((Dcm_DidMgrOpCallMemType)0x08u)
# endif /* (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
typedef uint8       Dcm_DidOpMemType;
typedef uint8_least Dcm_DidOpOptType;

typedef Dcm_DidOpMemType Dcm_DidOpType;
# endif /* (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA DECLARATIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#endif /* !defined(DCM_BASETYPES_H) */

/**********************************************************************************************************************
 *  END OF FILE: Dcm_BaseTypes.h
 *********************************************************************************************************************/
