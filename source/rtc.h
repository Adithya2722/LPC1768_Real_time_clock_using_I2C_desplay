/*========================================================
                    rtc.h
========================================================*/

#ifndef __RTC_H__
#define __RTC_H__

#include "Bitss.h"
#include <stdio.h>

extern BOOL rtc_isr_tick_flag;

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;

    uint8_t hour;
    uint8_t minute;
    uint8_t second;

}rtc_time_t;

void rtc_init();

void rtc_set_time(uint16_t year,
                  uint8_t month,
                  uint8_t day,
                  uint8_t hour,
                  uint8_t minute,
                  uint8_t second);

void rtc_get_time(rtc_time_t *time);

void rtc_date_to_string(char *buffer);

void rtc_time_to_string(char *buffer);

void set_rtc_interrupt_priority(uint8_t priority);

#endif
