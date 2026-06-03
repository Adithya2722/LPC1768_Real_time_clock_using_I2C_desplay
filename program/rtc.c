
/*========================================================
                    rtc.c
========================================================*/

#include "rtc.h"

BOOL rtc_isr_tick_flag = FALSE;

void rtc_init()
{
    SET_BIT_9(LPC_SC->PCONP);

    SET_BIT_1(LPC_RTC->CCR);

    CLEAR_BIT_1(LPC_RTC->CCR);

    SET_BIT_4(LPC_RTC->CCR);

    SET_BIT_0(LPC_RTC->CCR);

    LPC_RTC->ILR = 0x03;

    SET_BIT_0(LPC_RTC->CIIR);

    NVIC_EnableIRQ(RTC_IRQn);
}

void rtc_set_time(uint16_t year,
                  uint8_t month,
                  uint8_t day,
                  uint8_t hour,
                  uint8_t minute,
                  uint8_t second)
{
    CLEAR_BIT_0(LPC_RTC->CCR);

    LPC_RTC->YEAR  = year;
    LPC_RTC->MONTH = month;
    LPC_RTC->DOM   = day;

    LPC_RTC->HOUR = hour;
    LPC_RTC->MIN  = minute;
    LPC_RTC->SEC  = second;

    SET_BIT_0(LPC_RTC->CCR);
}

void rtc_get_time(rtc_time_t *time)
{
    time->year   = LPC_RTC->YEAR;
    time->month  = LPC_RTC->MONTH;
    time->day    = LPC_RTC->DOM;

    time->hour   = LPC_RTC->HOUR;
    time->minute = LPC_RTC->MIN;
    time->second = LPC_RTC->SEC;
}

void rtc_date_to_string(char *buffer)
{
    rtc_time_t t;

    rtc_get_time(&t);

    sprintf(buffer,
            "%02d/%02d/%04d",
            t.day,
            t.month,
            t.year);
}

void rtc_time_to_string(char *buffer)
{
    rtc_time_t t;

    rtc_get_time(&t);

    sprintf(buffer,
            "%02d:%02d:%02d",
            t.hour,
            t.minute,
            t.second);
}

void RTC_IRQHandler(void)
{
    if(LPC_RTC->ILR & 0x01)
    {
        LPC_RTC->ILR = 0x01;

        rtc_isr_tick_flag = TRUE;
    }
}

void set_rtc_interrupt_priority(uint8_t priority)
{
#define IPR3 (*((volatile uint32_t *)0xE000E40C))

    IPR3 &= ~(0xFF << 8);

    IPR3 |= ((priority & 0x1F) << 8);
}
