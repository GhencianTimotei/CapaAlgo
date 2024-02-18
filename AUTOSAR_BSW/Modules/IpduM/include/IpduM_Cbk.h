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
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IpduM_Cbk.h
 *      Project:  MICROSAR IpduM
 *       Module:  Implementation
 *    Generator:  CFG5
 *
 *  Description:  Microsar IPDU Multiplexer callback header file
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#ifndef IPDUM_CBK_H
# define IPDUM_CBK_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "IpduM_Cfg.h"
# include "ComStack_Types.h"
# include "SchM_IpduM.h"

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
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
# define IPDUM_START_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

# if (IPDUM_TRIGGER_TRANSMIT_API == STD_ON)
/*******************************************************************************************
*  IpduM_TriggerTransmit()
*******************************************************************************************/
/*! \brief          Request PDU data from the transmit buffer
 *  \details        IpduM copies the contents of its I-PDU transmit buffer
 *                  to the PDU buffer given by PduInfoPtr->SduDataPtr
 *                  and updates PduInfoPtr->SduLength with length of the copied data.
 *  \param[in]      TxPduId
 *  \param[in,out]  PduInfoPtr    Contains a pointer to a buffer (SduDataPtr) where the SDU
 *                                data shall be copied to, and the available buffer size in SduLengh.
 *                                On return, the service will indicate the length of the copied SDU
 *                                data in SduLength.
 *  \return         E_OK          SDU has been copied and SduLength indicates the number of copied bytes.
 *  \return         E_NOT_OK      No data has been copied, because
 *                                IpduM is not initialized
 *                                or TxPduId is not valid
 *                                or PduInfoPtr is NULL_PTR
 *                                or SduDataPtr is NULL_PTR
 *                                or SduLength is to small
 *                                or the SDU data could not be updated because the just in time update
 *                                   via a trigger transmit call of the upper layer was not successful
 *                                   for multiplexed messages.
 *  \pre            -
 *  \context        TASK|ISR
 *  \reentrant      TRUE for different handle IDs
 *  \synchronous    TRUE
 *  \note           Called by PduR module
 *  \trace          CREQ-102654
 *  \trace          SPEC-2068190, SPEC-2068191, SPEC-2068192, SPEC-2068189
*******************************************************************************************/
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TriggerTransmit(PduIdType TxPduId, P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
# endif

# if(IPDUM_TX_CONFIRMATION_API == STD_ON)
/*******************************************************************************************
*  IpduM_TxConfirmation()
*******************************************************************************************/
/*! \brief        Indicates complete transmission of a PDU
 *  \details      -
 *  \param[in]    TxPduId
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different handle IDs
 *  \synchronous  TRUE
 *  \note         Called by PduR module
 *  \trace        CREQ-102655
 *  \trace        SPEC-2068188, SPEC-2068186
*******************************************************************************************/
FUNC(void, IPDUM_CODE) IpduM_TxConfirmation(PduIdType TxPduId);
# endif

/*******************************************************************************************
*  IpduM_RxIndication()
*******************************************************************************************/
/*! \brief        Indicates complete reception of a PDU
 *  \details      -
 *  \param[in]    RxPduId
 *  \param[out]   PduInfoPtr    Pointer to buffer containing PDU
 *  \pre          -
 *  \context      TASK|ISR
 *  \reentrant    TRUE for different handle IDs
 *  \synchronous  TRUE
 *  \note         Called by PduR module
 *  \trace        CREQ-102656
 *  \trace        SPEC-2068185, SPEC-2068182
*******************************************************************************************/
FUNC(void, IPDUM_CODE) IpduM_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);

# define IPDUM_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */

#endif /* IPDUM_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: IpduM_Cbk.h
 *********************************************************************************************************************/
