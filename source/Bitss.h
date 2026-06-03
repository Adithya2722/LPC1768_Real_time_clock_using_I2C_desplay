/*========================================================
                    Bitss.h
========================================================*/

#ifndef __BITSS_H__
#define __BITSS_H__

#include "LPC17xx.h"
#include <stdint.h>

typedef enum
{
    FALSE = 0,
    TRUE
}BOOL;

#define NULL_CHAR '\0'

/*---------------- SET BIT ----------------*/

#define SET_BIT(reg,bit)      ((reg) |=  (1U << (bit)))
#define CLEAR_BIT(reg,bit)    ((reg) &= ~(1U << (bit)))
#define READ_BIT(reg,bit)     ((reg) &   (1U << (bit)))

#define SET_BIT_0(reg)     SET_BIT(reg,0)
#define SET_BIT_1(reg)     SET_BIT(reg,1)
#define SET_BIT_2(reg)     SET_BIT(reg,2)
#define SET_BIT_3(reg)     SET_BIT(reg,3)
#define SET_BIT_4(reg)     SET_BIT(reg,4)
#define SET_BIT_5(reg)     SET_BIT(reg,5)
#define SET_BIT_6(reg)     SET_BIT(reg,6)
#define SET_BIT_7(reg)     SET_BIT(reg,7)
#define SET_BIT_8(reg)     SET_BIT(reg,8)
#define SET_BIT_9(reg)     SET_BIT(reg,9)
#define SET_BIT_10(reg)    SET_BIT(reg,10)
#define SET_BIT_11(reg)    SET_BIT(reg,11)
#define SET_BIT_12(reg)    SET_BIT(reg,12)
#define SET_BIT_13(reg)    SET_BIT(reg,13)
#define SET_BIT_14(reg)    SET_BIT(reg,14)
#define SET_BIT_15(reg)    SET_BIT(reg,15)
#define SET_BIT_16(reg)    SET_BIT(reg,16)
#define SET_BIT_17(reg)    SET_BIT(reg,17)
#define SET_BIT_18(reg)    SET_BIT(reg,18)
#define SET_BIT_19(reg)    SET_BIT(reg,19)
#define SET_BIT_20(reg)    SET_BIT(reg,20)
#define SET_BIT_21(reg)    SET_BIT(reg,21)
#define SET_BIT_22(reg)    SET_BIT(reg,22)
#define SET_BIT_23(reg)    SET_BIT(reg,23)
#define SET_BIT_24(reg)    SET_BIT(reg,24)
#define SET_BIT_25(reg)    SET_BIT(reg,25)
#define SET_BIT_26(reg)    SET_BIT(reg,26)
#define SET_BIT_27(reg)    SET_BIT(reg,27)
#define SET_BIT_28(reg)    SET_BIT(reg,28)
#define SET_BIT_29(reg)    SET_BIT(reg,29)
#define SET_BIT_30(reg)    SET_BIT(reg,30)
#define SET_BIT_31(reg)    SET_BIT(reg,31)

#define CLEAR_BIT_0(reg)   CLEAR_BIT(reg,0)
#define CLEAR_BIT_1(reg)   CLEAR_BIT(reg,1)
#define CLEAR_BIT_2(reg)   CLEAR_BIT(reg,2)
#define CLEAR_BIT_3(reg)   CLEAR_BIT(reg,3)
#define CLEAR_BIT_4(reg)   CLEAR_BIT(reg,4)
#define CLEAR_BIT_5(reg)   CLEAR_BIT(reg,5)
#define CLEAR_BIT_6(reg)   CLEAR_BIT(reg,6)
#define CLEAR_BIT_7(reg)   CLEAR_BIT(reg,7)
#define CLEAR_BIT_8(reg)   CLEAR_BIT(reg,8)
#define CLEAR_BIT_9(reg)   CLEAR_BIT(reg,9)
#define CLEAR_BIT_10(reg)  CLEAR_BIT(reg,10)
#define CLEAR_BIT_11(reg)  CLEAR_BIT(reg,11)
#define CLEAR_BIT_12(reg)  CLEAR_BIT(reg,12)
#define CLEAR_BIT_13(reg)  CLEAR_BIT(reg,13)
#define CLEAR_BIT_14(reg)  CLEAR_BIT(reg,14)
#define CLEAR_BIT_15(reg)  CLEAR_BIT(reg,15)
#define CLEAR_BIT_16(reg)  CLEAR_BIT(reg,16)
#define CLEAR_BIT_17(reg)  CLEAR_BIT(reg,17)
#define CLEAR_BIT_18(reg)  CLEAR_BIT(reg,18)
#define CLEAR_BIT_19(reg)  CLEAR_BIT(reg,19)
#define CLEAR_BIT_20(reg)  CLEAR_BIT(reg,20)
#define CLEAR_BIT_21(reg)  CLEAR_BIT(reg,21)
#define CLEAR_BIT_22(reg)  CLEAR_BIT(reg,22)
#define CLEAR_BIT_23(reg)  CLEAR_BIT(reg,23)
#define CLEAR_BIT_24(reg)  CLEAR_BIT(reg,24)
#define CLEAR_BIT_25(reg)  CLEAR_BIT(reg,25)
#define CLEAR_BIT_26(reg)  CLEAR_BIT(reg,26)
#define CLEAR_BIT_27(reg)  CLEAR_BIT(reg,27)
#define CLEAR_BIT_28(reg)  CLEAR_BIT(reg,28)
#define CLEAR_BIT_29(reg)  CLEAR_BIT(reg,29)
#define CLEAR_BIT_30(reg)  CLEAR_BIT(reg,30)
#define CLEAR_BIT_31(reg)  CLEAR_BIT(reg,31)

#define READ_BIT_0(reg)    READ_BIT(reg,0)

/*---------------- CLOCK DIVIDER ----------------*/

typedef enum
{
    DIVIDE_BY_4 = 0,
    DIVIDE_BY_1,
    DIVIDE_BY_2,
    DIVIDE_BY_8

}CLOCK_DIVISOR;

#endif
