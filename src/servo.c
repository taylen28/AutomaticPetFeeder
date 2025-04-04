#include "servo.h"

static uint32_t us_to_ccr(TIM_HandleTypeDef *htim, uint16_t us) {
    uint32_t timer_clk = HAL_RCC_GetPCLK1Freq();  // Use APB1 clock
    uint32_t prescaler = htim->Init.Prescaler + 1;
    return (timer_clk / prescaler) * us / 1000000;
}


void SERVO_Init(ServoMotor_t *servo, TIM_HandleTypeDef *htim, uint32_t channel, uint16_t min_us, uint16_t max_us) {
    servo->htim = htim;
    servo->channel = channel;
    servo->min_us = min_us;
    servo->max_us = max_us;
    HAL_TIM_PWM_Start(htim, channel);
}

void SERVO_SetAngle(ServoMotor_t *servo, uint8_t angle)
 {
    if (angle > 180) angle = 180;
    uint16_t pulse = servo->min_us + ((servo->max_us - servo->min_us) * angle) / 180;
    uint32_t compare = us_to_ccr(servo->htim, pulse);
    __HAL_TIM_SET_COMPARE(servo->htim, servo->channel, compare);
}
