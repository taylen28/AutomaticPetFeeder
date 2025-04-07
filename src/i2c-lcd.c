#include "i2c-lcd.h"

extern I2C_HandleTypeDef hi2c1;   // <--- Important! Make sure this matches your CubeMX I2C

#define SLAVE_ADDRESS_LCD 0x4E // Change this if your LCD address is different (default is usually 0x27 shifted)

void lcd_send_cmd (char cmd)
{
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (cmd&0xf0);
    data_l = ((cmd<<4)&0xf0);
    data_t[0] = data_u|0x0C;  // en=1, rs=0
    data_t[1] = data_u|0x08;  // en=0, rs=0
    data_t[2] = data_l|0x0C;  // en=1, rs=0
    data_t[3] = data_l|0x08;  // en=0, rs=0
    HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, (uint8_t *) data_t, 4, 100);
}

void lcd_send_data (char data)
{
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (data&0xf0);
    data_l = ((data<<4)&0xf0);
    data_t[0] = data_u|0x0D;  // en=1, rs=1
    data_t[1] = data_u|0x09;  // en=0, rs=1
    data_t[2] = data_l|0x0D;  // en=1, rs=1
    data_t[3] = data_l|0x09;  // en=0, rs=1
    HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, (uint8_t *) data_t, 4, 100);
}

void lcd_clear (void)
{
    lcd_send_cmd(0x01);
    HAL_Delay(2);
}

void lcd_put_cur (int row, int col)
{
    switch (row)
    {
        case 0:
            lcd_send_cmd(0x80 + col);
            break;
        case 1:
            lcd_send_cmd(0xC0 + col);
            break;
    }
}

void lcd_init (void)
{
    HAL_Delay(50);  // wait for >40ms
    lcd_send_cmd (0x30);
    HAL_Delay(5);   // wait for >4.1ms
    lcd_send_cmd (0x30);
    HAL_Delay(1);   // wait for >100us
    lcd_send_cmd (0x30);
    HAL_Delay(10);
    lcd_send_cmd (0x20);  // 4-bit mode
    HAL_Delay(10);

    // Display initialization
    lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
    HAL_Delay(1);
    lcd_send_cmd (0x08); // Display off
    HAL_Delay(1);
    lcd_send_cmd (0x01); // Clear display
    HAL_Delay(2);
    lcd_send_cmd (0x06); // Entry mode set --> Increment cursor
    HAL_Delay(1);
    lcd_send_cmd (0x0C); // Display on, cursor off, blink off
}
void lcd_send_string(char *str)
{
    while (*str) lcd_send_data(*str++);
}