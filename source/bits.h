#ifndef __BITS_H__
#define __BITS_H__

#include <LPC17xx.h>

typedef enum
{
    FALSE = 0,
    TRUE = 1
} BOOL;

#define set_bit(dest,pos)        ((dest) |= (1U << (pos)))
#define reset_bit(dest,pos)      ((dest) &= ~(1U << (pos)))
#define read_bit(dest,pos)       (((dest) >> (pos)) & 1U)

#endif
