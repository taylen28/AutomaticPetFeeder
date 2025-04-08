#ifndef __LCD_PARALLEL_H
#define __LCD_PARALLEL_H

#include "stm32f3xx_hal.h"

// Define which GPIO port and pins we're using
#define LCD_GPIO_PORT GPIOE
#define LCD_RS_Pin GPIO_PIN_8
#define LCD_E_Pin  GPIO_PIN_9
#define LCD_D4_Pin GPIO_PIN_10
#define LCD_D5_Pin GPIO_PIN_11
#define LCD_D6_Pin GPIO_PIN_12
#define LCD_D7_Pin GPIO_PIN_13

// Functions to control LCD
void lcd_init(void);
void lcd_send_string(char *str);
void lcd_put_cur(uint8_t row, uint8_t col);
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_clear(void);

#endif /* __LCD_PARALLEL_H */
