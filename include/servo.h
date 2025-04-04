#ifndef SERVO_H_
#define SERVO_H_

#include "stm32f3xx_hal.h"

typedef struct {
    TIM_HandleTypeDef *htim;
    uint32_t channel;
    uint16_t min_us;  // Usually 500
    uint16_t max_us;  // Usually 2500
} ServoMotor_t;

void SERVO_Init(ServoMotor_t *servo, TIM_HandleTypeDef *htim, uint32_t channel, uint16_t min_us, uint16_t max_us);
void SERVO_SetAngle(ServoMotor_t *servo, uint8_t angle);

#endif