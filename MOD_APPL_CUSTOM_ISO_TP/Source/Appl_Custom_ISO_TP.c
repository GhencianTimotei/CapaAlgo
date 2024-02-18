/* polyspace+1 MISRA-C3:1.1 [Justified:Low] "All macro definitions are needed." */
/*
 * Appl_Custom_ISO_TP.c
 *
 *  Created on: Jan 19, 2022
 *      Author: lmilita
 */
#define APP_ISO_TP_C
#include "Platform_Types.h"
#include "ComStack_Types.h"
#include "Com_Cfg.h"
#include "Com_Cot.h"
#include "ComM.h"
#include "Com.h"
#include "Appl_Cbk.h"
#include "string.h"
#include "TimeService.h"
#include "Appl_Custom_ISO_TP.h"
/************************************************************************/
/* This array will be used to store data received through CAN from higher level ECU and then will be forwarded to NFC App */
static U8 AppIsoTp_TxCustomIsoTpBuffer_AU8[APP_ISO_TP_MAX_VALUE_FOR_ROUTING_ARRAY_U16];
/* This array will be used to store data received from NFC App and then will be forwarded on CAN */
static U8 AppIsoTp_RxCustomIsoTpBuffer_AU8[APP_ISO_TP_MAX_VALUE_FOR_ROUTING_ARRAY_U16];
/* This buffer will be used to fill the ISO TP frame content */
static U8 AppIsoTp_TxIsoTpFrame_AU8[APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8];
static U16 AppIsoTp_TxMessageDataLength_U16 = 0U;
static APP_ISO_TP_TX_COMM_LINE_STATUS_ENUM_TYPE AppIsoTp_TxCommunicationLineState_EN = APP_ISO_TP_COMM_LINE_FREE_E;
static U8 AppIsoTp_TxFramesToBeSentFlags_U8 = 0U;
static BOOL AppIsoTp_TxFrameInSending_BO = FALSE;

static APP_ISO_TP_TX_FRAMES_VALUES_TYPE AppIsoTp_ActualTxFrame_U8 = APP_ISO_TP_TX_FRAME_MKEntFT_FBS_01;
static BOOL AppIsoTp_NewDataReceived_BO = FALSE;
static U16 AppIsoTp_RxMessageDataLength_U16 = 0U;
#if(SWR_1084_CHECK_RX_MULTIFRAME_CONSECUTVE_FEATURE != FALSE)
static U8 AppIsoTp_ConsecutiveExpectedFrameSn_U8 = 0xFFU;
static APP_ISO_TP_RX_FRAMES_VALUES_TYPE AppIsoTp_LastReceivedIsoTpFrame_U8 = APP_ISO_TP_NO_RX_FRAME;
#endif


/************************************************************************/
static void AppIsoTp_ComputeNumberOfFramesToBeSent(void);
static void AppIsoTp_ReceiveMainFunction(APP_ISO_TP_RX_FRAMES_VALUES_TYPE ReceivedIsoTpFrame_U8, const SduDataPtrType SduDataPtr);
static void AppIsoTp_CheckReceptionTimer(void);
static void AppIsoTp_TransmitMainFunction(void);
static void AppIsoTp_UpdatedCommunicationStatus(void);


/*************************************************************************************************************
 *  Name                 : Test_Ipdu_Rx_FBS_MKEntFT_01
 *  Description          : Function callback called every time when frame FBS_MKEntFT_01 is received
 *  Parameters           : PduIdType: This type serve as a unique identifier of a PDU within a software module.
 *                         PduInfoType*: pointer to the structured info of a PDU
 *  Return               : Always TRUE - to be able to take actions on frame received
 *  Critical/explanation : -
 *  Author               : lmilita
 *************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
extern BOOL Test_Ipdu_Rx_FBS_MKEntFT_01(PduIdType PduId, const PduInfoType* PduInfoPtr)
{
   AppIsoTp_ReceiveMainFunction(APP_ISO_TP_RX_FRAME_FBS_MKEntFT_01, PduInfoPtr->SduDataPtr);
   return TRUE;    /* Returned value should be always TRUE to be able to take actions on frame received */
}

/*************************************************************************************************************
 *  Name                 : Test_Ipdu_Rx_FBS_MKEntFT_02
 *  Description          : Function callback called every time when frame FBS_MKEntFT_02 is received
 *  Parameters           : PduIdType: This type serve as a unique identifier of a PDU within a software module.
 *                          PduInfoType*: pointer to the structured info of a PDU
 *  Return               : Always TRUE - to be able to take actions on frame received
 *  Critical/explanation : -
 *  Author               : lmilita
 *************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
extern BOOL Test_Ipdu_Rx_FBS_MKEntFT_02(PduIdType PduId, const PduInfoType* PduInfoPtr)
{
   AppIsoTp_ReceiveMainFunction(APP_ISO_TP_RX_FRAME_FBS_MKEntFT_02, PduInfoPtr->SduDataPtr);
   return TRUE;    /* Returned value should be always TRUE to be able to take actions on frame received */
}

/*************************************************************************************************************
 *  Name                 : Test_Ipdu_Rx_FBS_MKEntFT_03
 *  Description          : Function callback called every time when frame FBS_MKEntFT_03 is received
 *  Parameters           : PduIdType: This type serve as a unique identifier of a PDU within a software module.
 *                         PduInfoType*: pointer to the structured info of a PDU
 *  Return               : Always TRUE - to be able to take actions on frame received
 *  Critical/explanation : -
 *  Author               : lmilita
 *************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
extern BOOL Test_Ipdu_Rx_FBS_MKEntFT_03(PduIdType PduId, const PduInfoType* PduInfoPtr)
{
   AppIsoTp_ReceiveMainFunction(APP_ISO_TP_RX_FRAME_FBS_MKEntFT_03, PduInfoPtr->SduDataPtr);
   return TRUE;    /* Returned value should be always TRUE to be able to take actions on frame received */
}

/*************************************************************************************************************
 *  Name                 : Test_Ipdu_Rx_FBS_MKEntFT_04
 *  Description          : Function callback called every time when frame FBS_MKEntFT_04 is received
 *  Parameters           : PduIdType: This type serve as a unique identifier of a PDU within a software module.
 *                         PduInfoType*: pointer to the structured info of a PDU
 *  Return               : Always TRUE - to be able to take actions on frame received
 *  Critical/explanation : -
 *  Author               : lmilita
 *************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
extern BOOL Test_Ipdu_Rx_FBS_MKEntFT_04(PduIdType PduId, const PduInfoType* PduInfoPtr)
{
   AppIsoTp_ReceiveMainFunction(APP_ISO_TP_RX_FRAME_FBS_MKEntFT_04, PduInfoPtr->SduDataPtr);
   return TRUE;    /* Returned value should be always TRUE to be able to take actions on frame received */
}

/*************************************************************************************************************
 *  Name                 : Test_Ipdu_Rx_FBS_MKEntFT_05
 *  Description          : Function callback called every time when frame FBS_MKEntFT_05 is received
 *  Parameters           : PduIdType: This type serve as a unique identifier of a PDU within a software module.
 *                         PduInfoType*: pointer to the structured info of a PDU
 *  Return               : Always TRUE - to be able to take actions on frame received
 *  Critical/explanation : -
 *  Author               : lmilita
 *************************************************************************************************************/
/* polyspace < MISRA-C3:2.7 : Not a defect : Justify with annotations > Paremeter should be kept for future usage */
extern BOOL Test_Ipdu_Rx_FBS_MKEntFT_05(PduIdType PduId, const PduInfoType* PduInfoPtr)
{
   AppIsoTp_ReceiveMainFunction(APP_ISO_TP_RX_FRAME_FBS_MKEntFT_05, PduInfoPtr->SduDataPtr);
   return TRUE;    /* Returned value should be always TRUE to be able to take actions on frame received */
}

/*************************************************************************************************************
 *  Name                 : ISO_TP_MKEntFT_FBS_01_TxConf
 *  Description          : Function called every time when confirmation of frame MKEntFT_FBS_01 transmission is received
 *                       : Clears the flag for APP_ISO_TP_TX_FRAME_MKEntFT_FBS_01 from AppIsoTp_TxFramesToBeSentFlags_U8
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : -
 *  Author               : lmilita
 *************************************************************************************************************/
extern void ISO_TP_MKEntFT_FBS_01_TxConf(void)
{
   AppIsoTp_TxFramesToBeSentFlags_U8 &= INVERT_AND_CAST_TO_U8(0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_01);

   AppIsoTp_UpdatedCommunicationStatus();
}

/*************************************************************************************************************
 *  Name                 : ISO_TP_MKEntFT_FBS_02_TxConf
 *  Description          : Function called every time when confirmation of frame MKEntFT_FBS_02 transmission is received
 *                       : Clears the flag for APP_ISO_TP_TX_FRAME_MKEntFT_FBS_02 from AppIsoTp_TxFramesToBeSentFlags_U8
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : -
 *  Author               : lmilita
 *************************************************************************************************************/
extern void ISO_TP_MKEntFT_FBS_02_TxConf(void)
{
   AppIsoTp_TxFramesToBeSentFlags_U8 &= INVERT_AND_CAST_TO_U8(0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_02);

   AppIsoTp_UpdatedCommunicationStatus();
}

/*************************************************************************************************************
 *  Name                 : ISO_TP_MKEntFT_FBS_03_TxConf
 *  Description          : Function called every time when confirmation of frame MKEntFT_FBS_03 transmission is received
 *                       : Clears the flag for APP_ISO_TP_TX_FRAME_MKEntFT_FBS_03 from AppIsoTp_TxFramesToBeSentFlags_U8
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : -
 *  Author               : lmilita
 *************************************************************************************************************/
extern void ISO_TP_MKEntFT_FBS_03_TxConf(void)
{
   AppIsoTp_TxFramesToBeSentFlags_U8 &= INVERT_AND_CAST_TO_U8(0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_03);

   AppIsoTp_UpdatedCommunicationStatus();
}

/*************************************************************************************************************
 *  Name                 : ISO_TP_MKEntFT_FBS_04_TxConf
 *  Description          : Function called every time when confirmation of frame MKEntFT_FBS_04 transmission is received
 *                       : Clears the flag for APP_ISO_TP_TX_FRAME_MKEntFT_FBS_04 from AppIsoTp_TxFramesToBeSentFlags_U8
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : -
 *  Author               : lmilita
 *************************************************************************************************************/
extern void ISO_TP_MKEntFT_FBS_04_TxConf(void)
{
   AppIsoTp_TxFramesToBeSentFlags_U8 &= INVERT_AND_CAST_TO_U8(0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_04);

   AppIsoTp_UpdatedCommunicationStatus();
}

/*************************************************************************************************************
 *  Name                 : ISO_TP_MKEntFT_FBS_05_TxConf
 *  Description          : Function called every time when confirmation of frame MKEntFT_FBS_05 transmission is received
 *                       : Clears the flag for APP_ISO_TP_TX_FRAME_MKEntFT_FBS_05 from AppIsoTp_TxFramesToBeSentFlags_U8
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : -
 *  Author               : lmilita
 *************************************************************************************************************/
extern void ISO_TP_MKEntFT_FBS_05_TxConf(void)
{
   AppIsoTp_TxFramesToBeSentFlags_U8 &= INVERT_AND_CAST_TO_U8(0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_05);

   AppIsoTp_UpdatedCommunicationStatus();
}



/*************************************************************************************************************
 *  Name                 : AppIsoTp_UpdatedCommunicationStatus
 *  Description          : This function stops the transmission monitor timer,
 *                       : updates AppIsoTp_TxFrameInSending_BO flag, AppIsoTp_ActualTxFrame_U8 and
                         : AppIsoTp_TxCommunicationLineState_EN if all frames were sent
 *                       :
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : -
 *  Author               : mficea
 *************************************************************************************************************/
static void AppIsoTp_UpdatedCommunicationStatus(void)
{
    (void)Tm_StopTimer_SlowTimer(ISO_TP_TRANSMISSION_TIMER);

    AppIsoTp_TxFrameInSending_BO = FALSE;

    if(0U == AppIsoTp_TxFramesToBeSentFlags_U8)
    {
        /* No other frames to be sent. Free comm line */
        AppIsoTp_TxCommunicationLineState_EN = APP_ISO_TP_COMM_LINE_FREE_E;
    }
    else
    {
        /* Go to next frame */
        AppIsoTp_ActualTxFrame_U8++;
    }
}



/*************************************************************************************************************
 *  Name                 : AppIsoTp_ComputeNumberOfFramesToBeSent
 *  Description          : This function sets the flags for all frames that should be sent having
 *                       : length of data to be transmitted as an input
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : -
 *  Author               : mficea
 *************************************************************************************************************/
static void AppIsoTp_ComputeNumberOfFramesToBeSent(void)
{
   if(AppIsoTp_TxMessageDataLength_U16 <= (APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8 - APP_ISO_TP_TX_FF_START_DATA_BYTE_OFFSET_U8))
   {
      AppIsoTp_TxFramesToBeSentFlags_U8 = (0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_01);
   }
   else
   {
      if(AppIsoTp_TxMessageDataLength_U16 <= ((APP_ISO_TP_TX_FRAME_MKEntFT_FBS_03 * APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8) - \
            APP_ISO_TP_TX_FF_START_DATA_BYTE_OFFSET_U8 - APP_ISO_TP_TX_CF_START_DATA_BYTE_OFFSET_U8))
      {
         AppIsoTp_TxFramesToBeSentFlags_U8 = (0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_01) | \
               (0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_02);
      }
      else
      {
         if(AppIsoTp_TxMessageDataLength_U16 <= ((APP_ISO_TP_TX_FRAME_MKEntFT_FBS_04 * APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8) - \
               APP_ISO_TP_TX_FF_START_DATA_BYTE_OFFSET_U8 - (2*APP_ISO_TP_TX_CF_START_DATA_BYTE_OFFSET_U8)))
         {
            AppIsoTp_TxFramesToBeSentFlags_U8 = (0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_01) | \
                  (0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_02) | \
                  (0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_03);
         }
         else
         {
            if(AppIsoTp_TxMessageDataLength_U16 <= ((APP_ISO_TP_TX_FRAME_MKEntFT_FBS_05 * APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8) - \
                  APP_ISO_TP_TX_FF_START_DATA_BYTE_OFFSET_U8 - (3*APP_ISO_TP_TX_CF_START_DATA_BYTE_OFFSET_U8)))
            {
               AppIsoTp_TxFramesToBeSentFlags_U8 = (0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_01) | (0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_02) | \
                     (0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_03) | (0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_04);
            }
            else
            {
               if(AppIsoTp_TxMessageDataLength_U16 <= ((APP_ISO_TP_TX_FRAME_MAX * APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8) - \
                     APP_ISO_TP_TX_FF_START_DATA_BYTE_OFFSET_U8 - (4*APP_ISO_TP_TX_CF_START_DATA_BYTE_OFFSET_U8)))
               {
                  AppIsoTp_TxFramesToBeSentFlags_U8 = (0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_01) | (0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_02) | \
                        (0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_03) | (0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_04) | \
                        (0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_05);
               }
               else{/**/}
            }
         }
      }
   }
}


/*************************************************************************************************************
 *  Name                 : AppIsoTp_SetTransmitData
 *  Description          : This function will be used to build the CAN FD message to be sent to the higher level ECU
 *  Parameters           : const U8 * const DataAddress_PCU - address of the data to be sent
 *                       : U16 DataLength_U16 - Length of data to be sent
 *  Return               : APP_ISO_TP_COMM_ONGOING_E or APP_ISO_TP_COMM_LINE_FREE_E
 *  Critical/explanation : -
 *  Author               : mficea
 *************************************************************************************************************/
extern APP_ISO_TP_TX_COMM_LINE_STATUS_ENUM_TYPE AppIsoTp_SetTransmitData(const U8 * const DataAddress_CPCU8, U16 DataLength_U16)
{
   APP_ISO_TP_TX_COMM_LINE_STATUS_ENUM_TYPE Return_EN = AppIsoTp_TxCommunicationLineState_EN;

   if(APP_ISO_TP_COMM_LINE_FREE_E == AppIsoTp_TxCommunicationLineState_EN)
   {
      if(NULL != DataAddress_CPCU8)
      {
         AppIsoTp_TxCommunicationLineState_EN = APP_ISO_TP_COMM_ONGOING_E;

         if((DataLength_U16 + APP_ISO_TP_HEADER_LENGTH_FOR_ALL_5_FRAMES) <= APP_ISO_TP_MAX_VALUE_FOR_ROUTING_ARRAY_U16)
         {
            AppIsoTp_TxMessageDataLength_U16 = DataLength_U16;
         }
         else
         {
            AppIsoTp_TxMessageDataLength_U16 = APP_ISO_TP_MAX_VALUE_FOR_ROUTING_ARRAY_U16 - APP_ISO_TP_HEADER_LENGTH_FOR_ALL_5_FRAMES;
         }

         memcpy(AppIsoTp_TxCustomIsoTpBuffer_AU8, DataAddress_CPCU8, AppIsoTp_TxMessageDataLength_U16);
         /* Implementation of SWR_1057 */
         /* polyspace+1 MISRA-C3:D4.14 [Justified:Low] "all variables are unsigned" */
         memset(&AppIsoTp_TxCustomIsoTpBuffer_AU8[AppIsoTp_TxMessageDataLength_U16], APP_ISO_TP_PADDING_VALUE_U8, (APP_ISO_TP_MAX_VALUE_FOR_ROUTING_ARRAY_U16 - AppIsoTp_TxMessageDataLength_U16 - APP_ISO_TP_HEADER_LENGTH_FOR_ALL_5_FRAMES));

         /* Each time after content transmission has been built, we should clear the TX Confirmation flags to avoid processing old flags from a previous transmission */

         AppIsoTp_TxFramesToBeSentFlags_U8 = 0U;
         AppIsoTp_ActualTxFrame_U8 = APP_ISO_TP_TX_FRAME_MKEntFT_FBS_01;

         AppIsoTp_ComputeNumberOfFramesToBeSent();

         /* Check if Single Frame is enough or we need multiframes */
         if((AppIsoTp_TxFramesToBeSentFlags_U8 & (U8)(0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_02)) == 0U)
         {   /* Single frame is enough */
            AppIsoTp_TxIsoTpFrame_AU8[APP_ISO_TP_TX_SF_PCI_BYTE_OFFSET_U8] = APP_ISO_TP_PCI_VALUE_FOR_SINGLE_FRAME_U8;    /* Implement SSR_715, equivalent of SWR_1069 */
            AppIsoTp_TxIsoTpFrame_AU8[APP_ISO_TP_TX_SF_DL_BYTE_OFFSET_U8]  = (U8)AppIsoTp_TxMessageDataLength_U16;    /* Implement SSR_699, equivalent of SWR_1068 */
         }
         else
         {   /* Multiple frames will be sent => we prepare the first frame to be transmitted */
            AppIsoTp_TxIsoTpFrame_AU8[APP_ISO_TP_TX_FF_PCI_BYTE_OFFSET_U8] = (U8)(APP_ISO_TP_PCI_VALUE_FOR_FIRST_FRAME_U8 << APP_ISO_TP_NIBLE_SHIFT_BITS_U8);    /* Implement SSR_717, equivalent of SWR_1085 */
            AppIsoTp_TxIsoTpFrame_AU8[APP_ISO_TP_TX_FF_PCI_BYTE_OFFSET_U8]+= (U8)(AppIsoTp_TxMessageDataLength_U16 >> APP_ISO_TP_BYTE_SHIFT_BITS_U8);
            AppIsoTp_TxIsoTpFrame_AU8[APP_ISO_TP_TX_FF_DL_BYTE_OFFSET_U8]  = (U8)AppIsoTp_TxMessageDataLength_U16;    /* Implement SSR_715, equivalent of SWR_1069 */
         }
         /* Copy data from AppIsoTp_TxCustomIsoTpBuffer_AU8 to AppIsoTp_TxIsoTpFrame_AU8 */
         memcpy(&AppIsoTp_TxIsoTpFrame_AU8[APP_ISO_TP_TX_FF_START_DATA_BYTE_OFFSET_U8], AppIsoTp_TxCustomIsoTpBuffer_AU8, (APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8 - APP_ISO_TP_CANTP_MESSAGE_HEADER_LENGTH_U8));

         AppIsoTp_TxFrameInSending_BO = TRUE;
         (void)Tm_StartTimer_SlowTimer(ISO_TP_TRANSMISSION_TIMER, APP_ISO_TP_TIMER_VAL_FOR_1_SECOND_U32);
         /* Implementation of SWR_906 */
         /* polyspace < MISRA-C3:8.3 : Not a defect : Justify with annotations > Function use the same names and type */
      }
      else{}
   }
   else{ /* Wait to Transmit current data */ }

   return Return_EN;
}


/*************************************************************************************************************
 *  Name                 : AppIsoTp_MainPeriodicTask
 *  Description          : Custom ISO TP main periodic task
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : -
 *  Author               : mficea
 *************************************************************************************************************/
extern void AppIsoTp_MainPeriodicTask(void)
{
   AppIsoTp_TransmitMainFunction();
   AppIsoTp_CheckReceptionTimer();
}


/*************************************************************************************************************
 *  Name                 : AppIsoTp_TransmitMainFunction
 *  Description          : Function which handles the transmission of ISO TP Frames
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : -
 *  Author               : mficea
 *************************************************************************************************************/
static void AppIsoTp_TransmitMainFunction(void)
{
   U8 TimerStatus_U8;
   U16 ReadBufferIndex_U16;
   if(APP_ISO_TP_COMM_ONGOING_E == AppIsoTp_TxCommunicationLineState_EN)
   {
      switch(AppIsoTp_ActualTxFrame_U8)
      {
          case APP_ISO_TP_TX_FRAME_MKEntFT_FBS_01:
              /* Frame sent */
              if(((AppIsoTp_TxFramesToBeSentFlags_U8 & (U8)(0x01U << APP_ISO_TP_TX_FRAME_MKEntFT_FBS_01)) != 0U) &&
                  (AppIsoTp_TxFrameInSending_BO != FALSE))
              {
                  (void)Tm_GetStatus_SlowTimer(ISO_TP_TRANSMISSION_TIMER, &TimerStatus_U8);
                  if(TM_READY == TimerStatus_U8)
                  {
                      AppIsoTp_TxCommunicationLineState_EN = APP_ISO_TP_COMM_LINE_FREE_E;
                  }
                  else{/* Wait Tx frame to be sent */}
              }
              else{}
            break;
         case APP_ISO_TP_TX_FRAME_MKEntFT_FBS_02:
            /* Intended fall-through
             * Same handling for all frames */
         case APP_ISO_TP_TX_FRAME_MKEntFT_FBS_03:
            /* Intended fall-through
             * Same handling for all frames */
         case APP_ISO_TP_TX_FRAME_MKEntFT_FBS_04:
            /* Intended fall-through
             * Same handling for all frames */
         case APP_ISO_TP_TX_FRAME_MKEntFT_FBS_05:
            if(FALSE == AppIsoTp_TxFrameInSending_BO)
            {
               /* Build consecutive frame with sequence number 1 */
               AppIsoTp_TxIsoTpFrame_AU8[APP_ISO_TP_TX_CF_PCI_SN_BYTE_OFFSET_U8] = (U8)(APP_ISO_TP_PCI_VALUE_FOR_CONSECUTIVE_FRAME_U8 << APP_ISO_TP_NIBLE_SHIFT_BITS_U8);    /* Implement SSR_695 and SSR_706, equivalent of SWR_1082 and SWR_1083 */
               AppIsoTp_TxIsoTpFrame_AU8[APP_ISO_TP_TX_CF_PCI_SN_BYTE_OFFSET_U8]+= AppIsoTp_ActualTxFrame_U8;    /* Implement SSR_717, equivalent of SWR_1085 */
               /* polyspace+1 MISRA-C3:10.6 [Justified:Low] "The composite expression is assigned to an object with a wider essential type" */
               ReadBufferIndex_U16 = (AppIsoTp_ActualTxFrame_U8*APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8) - AppIsoTp_ActualTxFrame_U8 - APP_ISO_TP_TX_FF_START_DATA_BYTE_OFFSET_U8 + 1U;
               /* Copy data from AppIsoTp_TxCustomIsoTpBuffer_AU8 to AppIsoTp_TxIsoTpFrame_AU8 */
               memcpy(&AppIsoTp_TxIsoTpFrame_AU8[APP_ISO_TP_TX_CF_START_DATA_BYTE_OFFSET_U8], \
                     &AppIsoTp_TxCustomIsoTpBuffer_AU8[ReadBufferIndex_U16], (APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8 - APP_ISO_TP_TX_CF_START_DATA_BYTE_OFFSET_U8));

               AppIsoTp_TxFrameInSending_BO = TRUE;
               (void)Tm_StartTimer_SlowTimer(ISO_TP_TRANSMISSION_TIMER, APP_ISO_TP_TIMER_VAL_FOR_1_SECOND_U32);
               /* Implementation of SWR_906 */
            }
            else
            {
               /* Frame sent */
                if((AppIsoTp_TxFramesToBeSentFlags_U8 & (U8)(0x01U << AppIsoTp_ActualTxFrame_U8)) != 0U)
                {
                    (void)Tm_GetStatus_SlowTimer(ISO_TP_TRANSMISSION_TIMER, &TimerStatus_U8);
                    if(TM_READY == TimerStatus_U8)
                    {
                        AppIsoTp_TxCommunicationLineState_EN = APP_ISO_TP_COMM_LINE_FREE_E;
                    }
                    else{/* Wait Tx frame to be sent */}
                }
                else{}
            }
            break;
         default:
         /*do nothing*/
            break;
      }
   }
   else{/* Nothing to process */}

}


/*************************************************************************************************************
 *  Name                 : AppIsoTp_ReceiveMainFunction
 *  Description          : Receive main function, called for handling of new Rx frames
 *  Parameters           : APP_ISO_TP_RX_FRAMES_VALUES_TYPE ReceivedIsoTpFrame_U8 - frame index received
 *                       : const SduDataPtrType SduDataPtr - Address of received data
 *  Return               : void
 *  Critical/explanation : -
 *  Author               : mficea
 *************************************************************************************************************/
/* polyspace < MISRA-C3:5.3,5.9 : Not a defect : Justify with annotations > It is a local variable, not affect the functionality */
/* polyspace < MISRA-C3:8.13 : Not a defect : Justify with annotations> A const pointer not possible here */
static void AppIsoTp_ReceiveMainFunction(APP_ISO_TP_RX_FRAMES_VALUES_TYPE ReceivedIsoTpFrame_U8, const SduDataPtrType SduDataPtr)
{
#if(SWR_1084_CHECK_RX_MULTIFRAME_CONSECUTVE_FEATURE != FALSE)
   static U16 AlreadyReceivedDataLength_U16 = 0U;
#endif
   U8 ActualReceivedSn_U8 = 0U;
   if(SduDataPtr != NULL)
   {
      switch(ReceivedIsoTpFrame_U8)
      {
         case APP_ISO_TP_RX_FRAME_FBS_MKEntFT_01:    /* During this case we have to decide if frame 01 is First Frame or Single frame */
            if(APP_ISO_TP_PCI_VALUE_FOR_SINGLE_FRAME_U8 == SduDataPtr[APP_ISO_TP_RX_SF_PCI_BYTE_OFFSET_U8])
            {    /* if a single frame is received */

               if(SduDataPtr[APP_ISO_TP_RX_SF_DL_BYTE_OFFSET_U8] <= (APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8 - APP_ISO_TP_CANTP_MESSAGE_HEADER_LENGTH_U8))
               {
                  AppIsoTp_RxMessageDataLength_U16 = SduDataPtr[APP_ISO_TP_RX_SF_DL_BYTE_OFFSET_U8];   /* SSR 701 */
               }
               else
               {
                  /* If Rx data length byte is greater than 62 bytes we use the maximum data length for a CAN ISO TP frame = 62 bytes */
                  AppIsoTp_RxMessageDataLength_U16 = APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8 - APP_ISO_TP_CANTP_MESSAGE_HEADER_LENGTH_U8;
               }
               /* first 2 bytes in received buffer represents PCI and DataLength */
               /* polyspace+2 CERT-C:ARR38-C [Justified:Low] "the length can't be bigger than AppIsoTp_RxCustomIsoTpBuffer_AU8" */
               memcpy(AppIsoTp_RxCustomIsoTpBuffer_AU8, &SduDataPtr[APP_ISO_TP_RX_SF_START_DATA_BYTE_OFFSET_U8], AppIsoTp_RxMessageDataLength_U16);
               AppIsoTp_NewDataReceived_BO = TRUE;
            }
            else
            {
               if(APP_ISO_TP_PCI_VALUE_FOR_FIRST_FRAME_U8 == (APP_ISO_TP_LOWER_NIBLE_MASK_U8 & ((APP_ISO_TP_RX_FF_PCI_MASK_U8 & SduDataPtr[APP_ISO_TP_RX_FF_PCI_BYTE_OFFSET_U8]) >> APP_ISO_TP_NIBLE_SHIFT_BITS_U8)))
               {    /* if a first frame is received, prepare the calculation of total data length */
                  /* polyspace < MISRA-C3:10.4,10.8 : Not a defect : Justify with annotations > Left and right operand has same type */
                  /* polyspace <MISRA-C3:D4.4 : Not a defect: Justify with annotations > Should be kept for future usage */
                  AppIsoTp_RxMessageDataLength_U16 = (((U16)(APP_ISO_TP_LOWER_NIBLE_MASK_U8 & SduDataPtr[APP_ISO_TP_RX_FF_PCI_BYTE_OFFSET_U8])) << APP_ISO_TP_BYTE_SHIFT_BITS_U8) + \
                        (U16)SduDataPtr[APP_ISO_TP_RX_FF_DL_BYTE_OFFSET_U8];   /* SSR 704 */

                  /* For multiframe message: FF 2 bytes + 1 byte for following frames = 6 bytes */
                  if((AppIsoTp_RxMessageDataLength_U16 + APP_ISO_TP_HEADER_LENGTH_FOR_ALL_5_FRAMES) > APP_ISO_TP_MAX_VALUE_FOR_ROUTING_ARRAY_U16)
                  {
                     /* Max data length in 5 ISO TP Frames */
                     AppIsoTp_RxMessageDataLength_U16 = APP_ISO_TP_MAX_VALUE_FOR_ROUTING_ARRAY_U16 - APP_ISO_TP_HEADER_LENGTH_FOR_ALL_5_FRAMES;
                  }
                  else{}

                  /* first 2 bytes in received buffer represents PCI and DataLength */
                  memcpy(AppIsoTp_RxCustomIsoTpBuffer_AU8, &SduDataPtr[APP_ISO_TP_RX_FF_START_DATA_BYTE_OFFSET_U8], (APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8 - APP_ISO_TP_CANTP_MESSAGE_HEADER_LENGTH_U8));

                  (void)Tm_StartTimer_SlowTimer(ISO_TP_RECEPTION_TIMER, APP_ISO_TP_TIMER_VAL_FOR_1_SECOND_U32);
#if(SWR_1084_CHECK_RX_MULTIFRAME_CONSECUTVE_FEATURE != FALSE)
                  AppIsoTp_ConsecutiveExpectedFrameSn_U8 = 1U;
                  AppIsoTp_LastReceivedIsoTpFrame_U8 = APP_ISO_TP_RX_FRAME_FBS_MKEntFT_01;
                  AlreadyReceivedDataLength_U16 = APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8 - APP_ISO_TP_CANTP_MESSAGE_HEADER_LENGTH_U8;
#endif
               }
               else { /* do nothing. TBD: Handle error */}
            }
            break;
         case APP_ISO_TP_RX_FRAME_FBS_MKEntFT_02:
            /* 2nd frame has been received
             * Intended fall-through */
         case APP_ISO_TP_RX_FRAME_FBS_MKEntFT_03:
            /* 3rd frame has been received
             * Intended fall-through */
         case APP_ISO_TP_RX_FRAME_FBS_MKEntFT_04:
            /* 4th frame has been received
             * Intended fall-through */
         case APP_ISO_TP_RX_FRAME_FBS_MKEntFT_05:
            /* 5th frame has been received */
            (void)Tm_StopTimer_SlowTimer(ISO_TP_RECEPTION_TIMER);
            ActualReceivedSn_U8 = SduDataPtr[APP_ISO_TP_RX_CF_PCI_SN_BYTE_OFFSET_U8] & APP_ISO_TP_RX_CF_SN_MASK_U8;
#if(SWR_1084_CHECK_RX_MULTIFRAME_CONSECUTVE_FEATURE != FALSE)
            if((AppIsoTp_ConsecutiveExpectedFrameSn_U8 != ActualReceivedSn_U8) || ((AppIsoTp_LastReceivedIsoTpFrame_U8 + 1U) != ReceivedIsoTpFrame_U8))
            {
               /* Received frame with not consecutive SN OR not consecutive frame */
               AppIsoTp_ConsecutiveExpectedFrameSn_U8 = 0xFFU;
               AppIsoTp_LastReceivedIsoTpFrame_U8 = APP_ISO_TP_NO_RX_FRAME;
            }
            else
            {
               AppIsoTp_LastReceivedIsoTpFrame_U8 = ReceivedIsoTpFrame_U8;
#endif
               /* Relevant data from every Consecutive ISO TP frame is all frame minus first byte (PCI and SN) */
               memcpy(&AppIsoTp_RxCustomIsoTpBuffer_AU8[(ActualReceivedSn_U8 * APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8) - ReceivedIsoTpFrame_U8], \
                     &SduDataPtr[APP_ISO_TP_RX_CF_START_DATA_BYTE_OFFSET_U8], (APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8 - 1U));
#if(SWR_1084_CHECK_RX_MULTIFRAME_CONSECUTVE_FEATURE != FALSE)
               AlreadyReceivedDataLength_U16 += APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8 - 1U;
               /* This means that for receive entire announced data will need another ISO TP frame to come */
               if(AppIsoTp_RxMessageDataLength_U16 > AlreadyReceivedDataLength_U16)
#else
                  if(AppIsoTp_RxMessageDataLength_U16 > ((ReceivedIsoTpFrame_U8 * APP_ISO_TP_CAN_FD_FRAME_LENGTH_IN_BYTES_U8) - (ReceivedIsoTpFrame_U8 + 1U)))
#endif
                  {
                     (void)Tm_StartTimer_SlowTimer(ISO_TP_RECEPTION_TIMER, APP_ISO_TP_TIMER_VAL_FOR_1_SECOND_U32);
#if(SWR_1084_CHECK_RX_MULTIFRAME_CONSECUTVE_FEATURE != FALSE)
                     AppIsoTp_ConsecutiveExpectedFrameSn_U8++;
#endif
                  }
                  else
                  {
                     AppIsoTp_NewDataReceived_BO = TRUE;
#if(SWR_1084_CHECK_RX_MULTIFRAME_CONSECUTVE_FEATURE != FALSE)
                     AlreadyReceivedDataLength_U16 = 0U;
                     AppIsoTp_ConsecutiveExpectedFrameSn_U8 = 0xFFU;
                     AppIsoTp_LastReceivedIsoTpFrame_U8 = APP_ISO_TP_NO_RX_FRAME;
                  }
#endif
            }
            break;
         default:
            /* do nothing*/
            break;
      }
   }
   else{}
}

/*************************************************************************************************************
 *  Name                 : AppIsoTp_GetNewDataReceivedFromCan
 *  Description          : This function provides the new Data received from high level ECU over CAN
 *  Parameters           : U8 **const DataAddress_CPPU8 - address where to store the address of the data received
 *                       : U16 *const DataLengthAddress_CPU16 - address where to store the length of the data received
 *  Return               : TRUE - when new data was received
 *                         FALSE - otherwise
 *  Critical/explanation : -
 *  Author               : lmilita
 *************************************************************************************************************/
extern BOOL AppIsoTp_GetNewDataReceivedFromCan(U8 **const DataAddress_CPPU8, U16 *const DataLengthAddress_CPU16)
{
   BOOL Ret_BO = FALSE;
   if(AppIsoTp_NewDataReceived_BO != FALSE)
   {
      if((DataAddress_CPPU8 != NULL) && (DataLengthAddress_CPU16 != NULL))
      {
         Ret_BO = TRUE;
         AppIsoTp_NewDataReceived_BO = FALSE;
         *DataAddress_CPPU8 = AppIsoTp_RxCustomIsoTpBuffer_AU8;
         *DataLengthAddress_CPU16 = AppIsoTp_RxMessageDataLength_U16;
      }
      else{}
   }
   return Ret_BO;
}

/*************************************************************************************************************
 *  Name                 : AppIsoTp_CheckReceptionTimer
 *  Description          :
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : -
 *  Author               : lmilita
 *************************************************************************************************************/
static void AppIsoTp_CheckReceptionTimer(void)
{
   U8 TimerStatus_U8;
   (void) Tm_GetStatus_SlowTimer(ISO_TP_RECEPTION_TIMER, &TimerStatus_U8);
   if(TM_READY == TimerStatus_U8)
      /* polyspace < RTE:UNR : Not a defect : Justify with annotations> The condition is not redundant*/
   {
      /* TBD: Return some error case to notify NFC APP that no other frame was received in time */
   }
   else
   {
      /* Do nothing. Just wait for the reception frames to come */
   }
}


#if(SWR_1084_CHECK_RX_MULTIFRAME_CONSECUTVE_FEATURE != FALSE)
/*************************************************************************************************************
 *  Name                 : AppIsoTp_ResetMultiframeReceiveProcedure
 *  Description          : Callback needed for reseting the ISO TP multiframe receive procedure to prevent
 *                       : using random received frames SN
 *                       :
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : Because no timeout is defined for multiframe procedure this is more than required.
 *                       : Must be called from NFC App when a new NFC device is detected
 *  Author               : mficea
 *************************************************************************************************************/
extern void AppIsoTp_ResetMultiframeReceiveProcedure(void)
{
   AppIsoTp_ConsecutiveExpectedFrameSn_U8 = 0xFFU;
   AppIsoTp_LastReceivedIsoTpFrame_U8 = APP_ISO_TP_NO_RX_FRAME;
}
#endif
