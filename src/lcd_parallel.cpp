/* lcd_parallel.h */

#ifndef __LCD_PARALLEL_H
#define __LCD_PARALLEL_H

#include "stm32f3xx_hal.h"

// Define which GPIO and pins we're using
#define LCD_GPIO_PORT GPIOE
#define LCD_RS_Pin GPIO_PIN_8
#define LCD_E_Pin  GPIO_PIN_9
#define LCD_D4_Pin GPIO_PIN_10
#define LCD_D5_Pin GPIO_PIN_11
#define LCD_D6_Pin GPIO_PIN_12
#define LCD_D7_Pin GPIO_PIN_13

void lcd_init(void);
void lcd_send_string(char *str);
void lcd_put_cur(uint8_t row, uint8_t col);
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_clear(void);

#endif /* __LCD_PARALLEL_H */

/* lcd_parallel.c */

#include "lcd_parallel.h"
#include "stm32f3xx_hal.h"

static void lcd_enable(void)
{
    HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_E_Pin, GPIO_PIN_SET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_E_Pin, GPIO_PIN_RESET);
    HAL_Delay(5);
}

static void lcd_send_nibble(uint8_t nibble)
{
    HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_D4_Pin, (nibble & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_D5_Pin, (nibble & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_D6_Pin, (nibble & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_D7_Pin, (nibble & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    lcd_enable();

    HAL_Delay(1);
}

void lcd_send_cmd(uint8_t cmd)
{
    HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_RS_Pin, GPIO_PIN_RESET);
    lcd_send_nibble(cmd >> 4);
    HAL_Delay(5); // 🔥 tiny delay
    lcd_send_nibble(cmd & 0x0F);
    HAL_Delay(5); // 🔥 tiny delay
}

void lcd_send_data(uint8_t data)
{
    HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_RS_Pin, GPIO_PIN_SET);
    lcd_send_nibble(data >> 4);
    HAL_Delay(5); // 🔥 tiny delay
    lcd_send_nibble(data & 0x0F);
    HAL_Delay(5); // 🔥 tiny delay
}

void lcd_clear(void)
{
    lcd_send_cmd(0x01);
    HAL_Delay(2);
}

void lcd_put_cur(uint8_t row, uint8_t col)
{
    uint8_t address;
    switch (row)
    {
        case 0:
            address = 0x80 + col;
            break;
        case 1:
            address = 0xC0 + col;
            break;
        default:
            address = 0x80;
            break;
    }
    lcd_send_cmd(address);
}

void lcd_init(void)
{
    HAL_Delay(100);   // Wait longer for LCD power-up

    lcd_send_nibble(0x03);
    HAL_Delay(10);
    lcd_send_nibble(0x03);
    HAL_Delay(10);
    lcd_send_nibble(0x03);
    HAL_Delay(10);
    lcd_send_nibble(0x02);  // 4-bit mode
    HAL_Delay(10);

    lcd_send_cmd(0x28); // 4-bit, 2 line, 5x8 font
    HAL_Delay(5);
    lcd_send_cmd(0x08); // display off
    HAL_Delay(5);
    lcd_send_cmd(0x01); // clear display
    HAL_Delay(10);      // Wait longer for clear
    lcd_send_cmd(0x06); // entry mode set
    HAL_Delay(5);
    lcd_send_cmd(0x0C); // display ON, cursor OFF
    HAL_Delay(5);
}


void lcd_send_string(char *str)
{
    while (*str)
    {
        lcd_send_data(*str++);
    }
}
