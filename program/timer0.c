/*========================================================
                    timer0.c
========================================================*/

#include "timer0.h"

void timer0_init()
{
    // Power ON TIMER0
    SET_BIT_1(LPC_SC->PCONP);

    // Peripheral clock = CCLK/2
    peripheral_clock_division_for_timer0(DIVIDE_BY_2);

    // Reset timer
    reset_timer0();

    // Prescaler
    set_timer0_prescaler(0);
}

void peripheral_clock_division_for_timer0(CLOCK_DIVISOR divisor)
{
    LPC_SC->PCLKSEL0 &= ~(3 << 2);

    LPC_SC->PCLKSEL0 |= (divisor << 2);
}

void start_timer0()
{
    SET_BIT_0(LPC_TIM0->TCR);
}

void stop_timer0()
{
    CLEAR_BIT_0(LPC_TIM0->TCR);
}

void reset_timer0()
{
    SET_BIT_1(LPC_TIM0->TCR);

    CLEAR_BIT_1(LPC_TIM0->TCR);
}

void set_timer0_prescaler(uint32_t value)
{
    LPC_TIM0->PR = value;
}

void set_timer0_match_value(uint32_t value)
{
    LPC_TIM0->MR0 = value;
}

void enable_timer0_interrupt()
{
    // Interrupt on MR0
    SET_BIT_0(LPC_TIM0->MCR);

    NVIC_EnableIRQ(TIMER0_IRQn);
}

void enable_timer0_reset_on_match()
{
    // Reset on MR0
    SET_BIT_1(LPC_TIM0->MCR);
}

void set_timer0_interrupt_priority(uint8_t priority)
{
#define IPR0 (*((volatile uint32_t *)0xE000E400))

    IPR0 &= ~(0xFF << 3);

    IPR0 |= ((priority & 0x1F) << 3);
}
