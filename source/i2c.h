#ifndef __I2C0_H__
#define __I2C0_H__

#include "Bitss.h"
#include <stdint.h>
#include <stdbool.h>

#define IIC_BUFFER_SIZE 64

typedef enum {
    I2C_IDLE,
    I2C_BUSY,
    I2C_DONE,
    I2C_ERROR
} I2C_Status;

typedef struct {
    uint8_t  slaveAddr;
    uint8_t  txBuffer[IIC_BUFFER_SIZE];
    uint32_t txLength;
    uint32_t txIndex;

    uint8_t  rxBuffer[IIC_BUFFER_SIZE];
    uint32_t rxLength;
    uint32_t rxIndex;

    I2C_Status status;
} I2C_Transaction;

extern volatile I2C_Transaction i2c0_transaction;

void i2c0_init(void);
bool i2c0_write(uint8_t slaveAddr, const uint8_t *data, uint32_t length);
bool i2c0_read(uint8_t slaveAddr, uint8_t *data, uint32_t length);
void I2C0_IRQHandler(void);

void I2C0_Init();
void I2C0_Start(void);
void I2C0_Stop(void);
void I2C0_Write(uint8_t data);
void LCD_Send(uint8_t data, uint8_t rs);
void LCD_Command(uint8_t cmd);
void LCD_Data(uint8_t data);
void LCD_Init(void);
void set_i2c0_interrupt_priority(uint8_t in_interrupt_priority);

#endif // __I2C0_H__


