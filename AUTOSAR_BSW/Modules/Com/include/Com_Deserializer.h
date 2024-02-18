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
/*!        \file  Com_Deserializer.h
 *        \brief  MICROSAR Communication header file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/
#if !defined (COM_DESERIALIZER_H)
# define COM_DESERIALIZER_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "Com_Lcfg.h"

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES (Com)
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
# define COM_START_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */


# if ((COM_EXISTS_UINT8_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_ReadSignal_UInt8
*********************************************************************************************************************/
/*!
    \brief        Reads the related Signal value from the passed PDU buffer.
    \details      -
    \pre          -
    \param[in]    idxRxAccessInfo      index of ComSignal.
    \param[in]    SignalBusSourcePtr buffer the value is read from.
    \return       ApplType specific read value
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(uint8, COM_CODE) Com_Signal_ReadSignal_UInt8(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr);
# endif

# if ((COM_EXISTS_SINT8_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_ReadSignal_SInt8
*********************************************************************************************************************/
/*!
    \brief        Reads the related Signal value from the passed PDU buffer.
    \details      -
    \pre          -
    \param[in]    idxRxAccessInfo      index of ComSignal.
    \param[in]    SignalBusSourcePtr buffer the value is read from.
    \return       ApplType specific read value
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(sint8, COM_CODE) Com_Signal_ReadSignal_SInt8(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr);
# endif

# if ((COM_EXISTS_UINT16_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_ReadSignal_UInt16
*********************************************************************************************************************/
/*!
    \brief        Reads the related Signal value from the passed PDU buffer.
    \details      -
    \pre          -
    \param[in]    idxRxAccessInfo      index of ComSignal.
    \param[in]    SignalBusSourcePtr buffer the value is read from.
    \return       ApplType specific read value
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(uint16, COM_CODE) Com_Signal_ReadSignal_UInt16(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr);
# endif

# if ((COM_EXISTS_SINT16_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_ReadSignal_SInt16
*********************************************************************************************************************/
/*!
    \brief        Reads the related Signal value from the passed PDU buffer.
    \details      -
    \pre          -
    \param[in]    idxRxAccessInfo      index of ComSignal.
    \param[in]    SignalBusSourcePtr buffer the value is read from.
    \return       ApplType specific read value
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(sint16, COM_CODE) Com_Signal_ReadSignal_SInt16(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr);
# endif

# if ((COM_EXISTS_UINT32_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_ReadSignal_UInt32
*********************************************************************************************************************/
/*!
    \brief        Reads the related Signal value from the passed PDU buffer.
    \details      -
    \pre          -
    \param[in]    idxRxAccessInfo      index of ComSignal.
    \param[in]    SignalBusSourcePtr buffer the value is read from.
    \return       ApplType specific read value
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(uint32, COM_CODE) Com_Signal_ReadSignal_UInt32(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr);
# endif

# if ((COM_EXISTS_SINT32_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_ReadSignal_SInt32
*********************************************************************************************************************/
/*!
    \brief        Reads the related Signal value from the passed PDU buffer.
    \details      -
    \pre          -
    \param[in]    idxRxAccessInfo      index of ComSignal.
    \param[in]    SignalBusSourcePtr buffer the value is read from.
    \return       ApplType specific read value
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(sint32, COM_CODE) Com_Signal_ReadSignal_SInt32(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr);
# endif

# if ((COM_EXISTS_UINT64_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_ReadSignal_UInt64
*********************************************************************************************************************/
/*!
    \brief        Reads the related Signal value from the passed PDU buffer.
    \details      -
    \pre          -
    \param[in]    idxRxAccessInfo      index of ComSignal.
    \param[in]    SignalBusSourcePtr buffer the value is read from.
    \return       ApplType specific read value
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(uint64, COM_CODE) Com_Signal_ReadSignal_UInt64(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr);
# endif

# if ((COM_EXISTS_SINT64_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_ReadSignal_SInt64
*********************************************************************************************************************/
/*!
    \brief        Reads the related Signal value from the passed PDU buffer.
    \details      -
    \pre          -
    \param[in]    idxRxAccessInfo      index of ComSignal.
    \param[in]    SignalBusSourcePtr buffer the value is read from.
    \return       ApplType specific read value
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(sint64, COM_CODE) Com_Signal_ReadSignal_SInt64(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr);
# endif

# if ((COM_EXISTS_FLOAT32_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_ReadSignal_Float32
*********************************************************************************************************************/
/*!
    \brief        Reads the related Signal value from the passed PDU buffer.
    \details      -
    \pre          -
    \param[in]    idxRxAccessInfo      index of ComSignal.
    \param[in]    SignalBusSourcePtr buffer the value is read from.
    \return       ApplType specific read value
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(float32, COM_CODE) Com_Signal_ReadSignal_Float32(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr);
# endif

# if ((COM_EXISTS_FLOAT64_APPLTYPEOFRXACCESSINFO == STD_ON) && (COM_BUFFERUSEDOFRXACCESSINFO == STD_ON))
/**********************************************************************************************************************
*  Com_Signal_ReadSignal_Float64
*********************************************************************************************************************/
/*!
    \brief        Reads the related Signal value from the passed PDU buffer.
    \details      -
    \pre          -
    \param[in]    idxRxAccessInfo      index of ComSignal.
    \param[in]    SignalBusSourcePtr buffer the value is read from.
    \return       ApplType specific read value
    \context      TASK
    \synchronous  TRUE
    \reentrant    FALSE
**********************************************************************************************************************/
FUNC(float64, COM_CODE) Com_Signal_ReadSignal_Float64(Com_RxAccessInfoIterType idxRxAccessInfo, P2CONST(uint8, AUTOMATIC, COM_VAR_NOINIT) SignalBusSourcePtr);
# endif


# define COM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* COM_DESERIALIZER_H */

/**********************************************************************************************************************
  END OF FILE: Com_Deserializer.h
**********************************************************************************************************************/
