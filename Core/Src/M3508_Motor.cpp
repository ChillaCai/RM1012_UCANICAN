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
