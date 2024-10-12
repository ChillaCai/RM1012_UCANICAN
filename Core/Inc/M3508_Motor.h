//
// Created by chill on 2024/10/12.
//

#ifndef CAN_M3508_MOTOR_H
#define CAN_M3508_MOTOR_H

#include <cstdint>

class M3508_Motor {
private:
  float ratio_;           // 电机减速比
  float angle_;                // deg 输出端累计转动角度
  float delta_angle_;          // deg 输出端新转动的角度
  float ecd_angle_;            // deg 当前电机编码器角度
  float last_ecd_angle_;       // deg 上次电机编码器角度
  float delta_ecd_angle_;      // deg 编码器端新转动的角度
  float rotate_speed_;         // dps 反馈转子转速
  float current_;               // A 反馈转矩电流
  float temp_;               // °C 反馈电机温度
public:
  M3508_Motor();
  void CanRxMsgCallback(uint8_t rx_data[8]);
};

#endif // CAN_M3508_MOTOR_H
