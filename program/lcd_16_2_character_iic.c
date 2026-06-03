/*
 * lcd_16_2_character_iic.c
 *
 *  Created on: 18-Apr-2026
 *      Author: Pranay
 */

#include "lcd_16_2_character_iic.h"

/*========================================================
                    LCD COMMANDS
========================================================*/

enum LCD_COMMANDS
{
    LCD_CLEAR_SCREEN               = 0x01,
    LCD_RETURN_HOME                = 0x02,

    LCD_ENTRY_MODE                 = 0x06,

    LCD_DISPLAY_ON_CURSOR_OFF      = 0x0C,
    LCD_DISPLAY_ON_CURSOR_BLINKING = 0x0E,

    LCD_CURSOR_START_OF_LINE1      = 0x80,
    LCD_CURSOR_START_OF_LINE2      = 0xC0,

    LCD_SHIFT_CURSOR_LEFT          = 0x10,
    LCD_SHIFT_CURSOR_RIGHT         = 0x14,

    LCD_2_LINE_8_BIT_MODE          = 0x38,
    LCD_2_LINE_4_BIT_MODE          = 0x28,

    LCD_1_LINE_8_BIT_MODE          = 0x30,
    LCD_1_LINE_4_BIT_MODE          = 0x20
};

/*========================================================
                    DELAY
========================================================*/

#define SYSTEM_CORE_CLOCK (50000000UL)

void delay_ms(uint32_t ms)
{
    SysTick->LOAD = (SYSTEM_CORE_CLOCK / 1000) - 1;

    SysTick->VAL = 0;

    SysTick->CTRL =
            SysTick_CTRL_CLKSOURCE_Msk |
            SysTick_CTRL_ENABLE_Msk;

    while(ms)
    {
        while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));

        ms--;
    }

    SysTick->CTRL = 0;
}

/*========================================================
                SEND DATA TO LCD
========================================================*/

void lcd_send_4_bits(uint8_t data,uint8_t rs)
{
    uint8_t high;
    uint8_t low;

    uint8_t temp;

    high = data & 0xF0;

    low = (data << 4) & 0xF0;

    // Backlight ON
    high |= 0x08;
    low  |= 0x08;

    // RS bit
    if(rs)
    {
        high |= 0x01;
        low  |= 0x01;
    }

    /*---------------- HIGH NIBBLE ----------------*/

    temp = high | 0x04;

    i2c0_write(LCD_MODULE_IIC_ADDR,&temp,1);

    delay_ms(1);

    temp = high & ~0x04;

    i2c0_write(LCD_MODULE_IIC_ADDR,&temp,1);

    delay_ms(1);

    /*---------------- LOW NIBBLE ----------------*/

    temp = low | 0x04;

    i2c0_write(LCD_MODULE_IIC_ADDR,&temp,1);

    delay_ms(1);

    temp = low & ~0x04;

    i2c0_write(LCD_MODULE_IIC_ADDR,&temp,1);

    delay_ms(1);
}

void lcd_send_8_bits(uint8_t data,uint8_t rs)
{
    lcd_send_4_bits(data,rs);
}

/*========================================================
                    LCD COMMANDS
========================================================*/

void lcd_send_command(uint8_t cmd,uint8_t delay)
{
    lcd_send_4_bits(cmd,0);

    delay_ms(delay);
}

void lcd_send_data(uint8_t data)
{
    lcd_send_4_bits(data,1);
}

/*========================================================
                    LCD CONTROL
========================================================*/

void lcd_clear()
{
    lcd_send_command(LCD_CLEAR_SCREEN,5);
}

void lcd_clear_screen()
{
    lcd_send_command(LCD_CLEAR_SCREEN,5);
}

void lcd_shift_cursor_right()
{
    lcd_send_command(LCD_ENTRY_MODE,1);
}

void lcd_display_on_cursor_off()
{
    lcd_send_command(LCD_DISPLAY_ON_CURSOR_OFF,1);
}

void lcd_display_on_cursor_blinking()
{
    lcd_send_command(LCD_DISPLAY_ON_CURSOR_BLINKING,1);
}

void lcd_cursor_start_of_line1()
{
    lcd_send_command(LCD_CURSOR_START_OF_LINE1,1);
}

void lcd_cursor_start_of_line2()
{
    lcd_send_command(LCD_CURSOR_START_OF_LINE2,1);
}

void lcd_shift_cursor_position_left()
{
    lcd_send_command(LCD_SHIFT_CURSOR_LEFT,1);
}

void lcd_shift_cursor_position_right()
{
    lcd_send_command(LCD_SHIFT_CURSOR_RIGHT,1);
}

/*========================================================
                    LCD MODE
========================================================*/

void lcd_set_2_lines_8bits_mode()
{
    lcd_send_command(LCD_2_LINE_8_BIT_MODE,1);
}

void lcd_set_2_lines_4bits_mode()
{
    lcd_send_command(LCD_2_LINE_4_BIT_MODE,1);
}

void lcd_set_1_line_8bits_mode()
{
    lcd_send_command(LCD_1_LINE_8_BIT_MODE,1);
}

void lcd_set_1_line_4bits_mode()
{
    lcd_send_command(LCD_1_LINE_4_BIT_MODE,1);
}

/*========================================================
                    LCD CURSOR
========================================================*/

void lcd_set_cursor(uint8_t row,uint8_t column)
{
    uint8_t address;

    if(row == 0)
    {
        address = 0x80 + column;
    }
    else
    {
        address = 0xC0 + column;
    }

    lcd_send_command(address,1);
}

/*========================================================
                DISPLAY CHARACTER
========================================================*/

void lcd_display_char(char data)
{
    lcd_send_data(data);

    delay_ms(1);
}

/*========================================================
                DISPLAY STRING
========================================================*/

void lcd_display_string(char *in_string)
{
    while(*in_string)
    {
        lcd_display_char(*in_string++);

        delay_ms(1);
    }
}

/*========================================================
                LCD INITIALIZATION
========================================================*/

void lcd_16_2_character_iic_init(void)
{
    delay_ms(50);

    lcd_send_command(0x33,5);

    lcd_send_command(0x32,5);

    lcd_set_2_lines_4bits_mode();

    lcd_display_on_cursor_off();

    lcd_shift_cursor_right();

    lcd_clear();
}
