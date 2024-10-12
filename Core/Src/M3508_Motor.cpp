//
// Created by chill on 2024/10/12.
//

#include "M3508_Motor.h"

float linearMapping(int in, int in_min, int in_max, float out_min, float out_max){
  if (in_min == in_max){
    return out_min;
  }
  else{
    float out = out_min + (out_max - out_min) / (in_max - in_min) * (in - in_min);
    return out;
  }
}

M3508_Motor::M3508_Motor(){
  ratio_ = 19.20321; 		// 电机减速比
  angle_ = 0.0; 	        // deg 输出端累计转动角度
  delta_angle_ = 0.0; 		// deg 输出端新转动的角度
  ecd_angle_ = 0.0; 		// deg 当前电机编码器角度
  last_ecd_angle_ = 0.0;	// deg 上次电机编码器角度
  delta_ecd_angle_ = 0.0; 	// deg 编码器端新转动的角度

  rotate_speed_ = 0.0; 		// dps 反馈转子转速
  current_ = 0.0; 	        // A 反馈转矩电流
  temp_ = 25.0; 		// °C 反馈电机温度 (不太确定...)
}
void M3508_Motor::CanRxMsgCallback(uint8_t rx_data[8]){
  // 解析电机编码器角度
  last_ecd_angle_ = ecd_angle_;
  int ecd_angle = (rx_data[0] << 8) | rx_data[1];
  ecd_angle_ = linearMapping(ecd_angle, 0, 8191, 0.0, 360.0);
  //计算输出端新转动的角度
  float delta = ecd_angle_ - last_ecd_angle_;
  if (delta < -180.0){
    // 顺时针转动时超过360归0情况，此时(ecd_angle_ + 360.0) - last_ecd_angle_为真实转动角度
    delta_ecd_angle_ = delta + 360.0;
  }
  else if (delta > 180.0){
    // 逆时针转动时超过0归360情况，此时ecd_angle_ - (last_ecd_angle_ + 360.0)为真实转动角度
    delta_ecd_angle_ = delta - 360.0;
  }
  else {
    delta_ecd_angle_ = delta;
  }
  // 解析转子转速
  int rotate_speed_rpm = (rx_data[2] << 8) | rx_data[3];
  rotate_speed_ = rotate_speed_rpm * 6.0;
  // 解析转矩电流
  current_ = (rx_data[4] << 8) | rx_data[5];
  // 解析电机温度
  temp_ = rx_data[6];

  //计算输出轴新转动角度和累计转动角度
  delta_angle_ = delta_ecd_angle_ / ratio_;
  angle_ += delta_angle_;
}