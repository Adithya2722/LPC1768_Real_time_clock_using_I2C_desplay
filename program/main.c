/*========================================================
                    main.c
========================================================*/

#include "LPC17xx.h"

#include "Bitss.h"

#include "rtc.h"

#include "i2c.h"

#include "lcd_16_2_character_iic.h"

char date_buffer[20];

char time_buffer[20];

int main()
{
    SystemInit();

    i2c0_init();

    lcd_16_2_character_iic_init();

    rtc_init();

    rtc_set_time(2026,05,26,14,45,00);

    while(1)
    {
        if(rtc_isr_tick_flag == TRUE)
        {
            rtc_isr_tick_flag = FALSE;

            rtc_date_to_string(date_buffer);

            rtc_time_to_string(time_buffer);

            lcd_clear();

            lcd_set_cursor(0,0);

            lcd_display_string(date_buffer);

            lcd_set_cursor(1,0);

            lcd_display_string(time_buffer);
        }
    }
}
