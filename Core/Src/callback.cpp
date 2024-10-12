//
// Created by chill on 2024/10/12.
//
#include "can.h"
#include "main.h"

extern CAN_RxHeaderTypeDef  RxHeader;
extern uint8_t rx_data[1];
extern CAN_TxHeaderTypeDef TxHeader;
extern uint8_t tx_data[1];
extern uint32_t TxMailbox;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
  if (hcan->Instance==CAN1){
    HAL_CAN_GetRxMessage(&hcan1, CAN_FilterFIFO0, &RxHeader, rx_data);
    if (rx_data[0] == 0x37){
      HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);
    }
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == KEY_Pin){
    HAL_CAN_AddTxMessage(&hcan1, &TxHeader, tx_data, &TxMailbox);
  }
}