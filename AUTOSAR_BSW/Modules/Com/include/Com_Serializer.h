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
/*!        \file  Com_Serializer.h
 *        \brief  MICROSAR Communication header file
 *
 *      \details  This is the implementation of the MICROSAR Communication module.
 *                The basic software module is based on the AUTOSAR Communication specification.
 *
 *********************************************************************************************************************/
#if !defined (COM_SERIALIZER_H)
# define COM_SERIALIZER_H

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
  Com_NBITNBYTE_GetEndiannesIndex
**********************************************************************************************************************/
/*! \brief        This method return negative Index if bus signal is big endian, otherwise index is returned.
    \details      -
    \pre          -
    \param[in]    bufferIndex         TxBuffer index
    \param[in]    isBusBigEndian      flag, if bus is big endian.
    \return       bufferIndex         if bus is little endian
                  (- bufferIndex)     if bus is big endian.
    \context      TASK
    \synchronous  TRUE
    \reentrant    TRUE
 ****************************************************************************************************************/
# define Com_NBITNBYTE_GetEndiannesIndex(bufferIndex, isBusBigEndian) (((isBusBigEndian) == TRUE) ? (-(bufferIndex)) : (bufferIndex))

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

# if (COM_TXBUFFERUSEDOFTXSIGINFO == STD_ON)
/**********************************************************************************************************************
  Com_Signal_WriteSignal
**********************************************************************************************************************/
/*! \brief        This method writes a signal to the TxIPdu buffer or group signal to shadow buffer.
    \details      -
    \pre          -
    \param[in]    SignalId            ID of the signal or group signal to be written to
    \param[in]    SignalApplSourcePtr Pointer to application memory where the signal is located
    \context      TASK|ISR2
    \note         Interrupts must have been locked by the calling function. This function does not provide a sign
                  conversion to be compatible with gateway use case.
    \synchronous  TRUE
    \reentrant    TRUE, for different handles
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_Signal_WriteSignal(Com_TxSigInfoIterType SignalId, P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SignalApplSourcePtr);
# endif

# define COM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* COM_SERIALIZER_H */

/**********************************************************************************************************************
  END OF FILE: Com_Serializer.h
**********************************************************************************************************************/
