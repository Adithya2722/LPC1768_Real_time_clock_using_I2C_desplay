
#ifndef LCD_16_2_CHARACTER_IIC_H_
#define LCD_16_2_CHARACTER_IIC_H_

#include "i2c.h"
#include "Bitss.h"

#include <stdint.h>
#include <string.h>

/*========================================================
                    LCD I2C ADDRESS
========================================================*/

#define LCD_MODULE_IIC_ADDR 0x27

/*========================================================
                    LCD MODE
========================================================*/

static BOOL LCD_8_BIT_MODE = FALSE;

/*========================================================
                    LOW LEVEL FUNCTIONS
========================================================*/

void delay_ms(uint32_t ms);

void lcd_send_4_bits(uint8_t data,uint8_t rs);

void lcd_send_8_bits(uint8_t data,uint8_t rs);

void lcd_send_command(uint8_t cmd,uint8_t delay);

void lcd_send_data(uint8_t data);

/*========================================================
                    LCD DISPLAY FUNCTIONS
========================================================*/

void lcd_display_char(char data);

void lcd_display_string(char *in_string);

void lcd_clear();

void lcd_clear_screen();

void lcd_set_cursor(uint8_t row,uint8_t column);

/*========================================================
                    LCD CURSOR FUNCTIONS
========================================================*/

void lcd_shift_cursor_right();

void lcd_shift_cursor_position_left();

void lcd_shift_cursor_position_right();

void lcd_cursor_start_of_line1();

void lcd_cursor_start_of_line2();

/*========================================================
                    LCD DISPLAY CONTROL
========================================================*/

void lcd_display_on_cursor_off();

void lcd_display_on_cursor_blinking();

/*========================================================
                    LCD MODE CONFIGURATION
========================================================*/

void lcd_set_2_lines_8bits_mode();

void lcd_set_2_lines_4bits_mode();

void lcd_set_1_line_8bits_mode();

void lcd_set_1_line_4bits_mode();

/*========================================================
                    LCD INITIALIZATION
========================================================*/

void lcd_16_2_character_iic_init(void);

#endif /* LCD_16_2_CHARACTER_IIC_H_ */
