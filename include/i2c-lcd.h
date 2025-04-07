#ifndef INC_I2C_LCD_H_
#define INC_I2C_LCD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f3xx_hal.h"

void lcd_init(void);
void lcd_send_cmd (char cmd);
void lcd_send_data (char data);
void lcd_send_string (char *str);
void lcd_put_cur(int row, int col);
void lcd_clear (void);

#ifdef __cplusplus
}
#endif

#endif /* INC_I2C_LCD_H_ */
