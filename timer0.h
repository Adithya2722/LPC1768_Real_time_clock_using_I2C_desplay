#ifndef TIMER0_H
#define TIMER0_H

#include <LPC17xx.h>

typedef enum
{
    FALSE = 0,
    TRUE = 1
} BOOL;

// Bit macros
#define set_bit(dest,pos)    ((dest) |= (1U << (pos)))
#define reset_bit(dest,pos)  ((dest) &= ~(1U << (pos)))

// Function declarations
void timer0_init(void);
void start_timer0(void);
void stop_timer0(void);
void enable_timer0_interrupt(void);
void enable_timer0_mr_reset(void);
void set_timer0_pre_scale_value(uint32_t value);
void set_timer0_match_value(uint32_t value);

#endif