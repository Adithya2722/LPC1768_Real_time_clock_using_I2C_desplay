//#include "i2c0.h"
//

#include "LPC17xx.h"
#include <stdint.h>
#include "i2c0.h"

volatile I2C_Transaction i2c0_transaction;

enum IIC_CONTROL_SET {
	ASSERT_ACKNOWLEDGE_FLAG = (1 << 2),
	I2C_INTERRUPT_FLAG      = (1 << 3),
	STOP_FLAG               = (1 << 4),
	START_FLAG              = (1 << 5),
	I2C_INTERFACE_ENABLE    = (1 << 6)
};

enum IIC_STATE {
	START_TRANSMITTED        = 0x08,
	REPEAT_START_TRANSMITTED = 0x10,
	SLA_W_TXD_ACK_RECEIVED   = 0x18,
	DATA_TXD_ACK_RECEIVED    = 0x28,
	SLA_RXD_ACK_RECEIVED     = 0x40,
	DATA_RXD_ACK_TRANSMITTED = 0x50,
	DATA_RXD_NACK_TRANSMITTED= 0x58
};

void i2c0_init(void)
{
	SET_BIT_7(LPC_SC->PCONP);

	LPC_PINCON->PINSEL1 &= ~((3 << 22) | (3 << 24));
	LPC_PINCON->PINSEL1 |= (1 << 22) | (1 << 24);

	LPC_PINCON->I2CPADCFG = 0x00;

	LPC_I2C0->I2SCLH = 0x7D;
	LPC_I2C0->I2SCLL = 0x7D;

	SET_BIT_6(LPC_I2C0->I2CONSET);//Enable the I2C interface

	NVIC_EnableIRQ(I2C0_IRQn);

	i2c0_transaction.status = I2C_IDLE;
}

bool i2c0_write(uint8_t slaveAddr, const uint8_t *data, uint32_t length)
{
	if (i2c0_transaction.status == I2C_BUSY) return false;

	i2c0_transaction.slaveAddr = slaveAddr;
	i2c0_transaction.txLength = length;
	i2c0_transaction.txIndex = 0;
	for (uint32_t i = 0; i < length; i++)
	{
		i2c0_transaction.txBuffer[i] = data[i];
	}
	i2c0_transaction.rxLength = 0;
	i2c0_transaction.rxIndex = 0;
	i2c0_transaction.status = I2C_BUSY;

	LPC_I2C0->I2CONSET = START_FLAG;

	while (i2c0_transaction.status == I2C_BUSY);

	return (i2c0_transaction.status == I2C_DONE);
}

bool i2c0_read(uint8_t slaveAddr, uint8_t *data, uint32_t length)
{
	if (i2c0_transaction.status == I2C_BUSY) return false;

	i2c0_transaction.slaveAddr = slaveAddr;
	i2c0_transaction.txLength = 0;
	i2c0_transaction.txIndex = 0;
	i2c0_transaction.rxLength = length;
	i2c0_transaction.rxIndex = 0;
	i2c0_transaction.status = I2C_BUSY;

	LPC_I2C0->I2CONSET = START_FLAG;

	while (i2c0_transaction.status == I2C_BUSY);

	if (i2c0_transaction.status == I2C_DONE)
	{
		for (uint32_t i = 0; i < length; i++)
		{
			data[i] = i2c0_transaction.rxBuffer[i];
		}
		return true;
	}
	return false;
}

void I2C0_IRQHandler(void)
{
	switch (LPC_I2C0->I2STAT)
	{
	case START_TRANSMITTED:
		if (i2c0_transaction.txLength > 0)
			LPC_I2C0->I2DAT = (i2c0_transaction.slaveAddr << 1); // SLA+W
		else
			LPC_I2C0->I2DAT = (i2c0_transaction.slaveAddr << 1) | 1; // SLA+R
			LPC_I2C0->I2CONCLR = START_FLAG;
		break;

	case SLA_W_TXD_ACK_RECEIVED:
		LPC_I2C0->I2DAT = i2c0_transaction.txBuffer[i2c0_transaction.txIndex++];
		break;

	case DATA_TXD_ACK_RECEIVED:
		if (i2c0_transaction.txIndex < i2c0_transaction.txLength)
		{
			LPC_I2C0->I2DAT = i2c0_transaction.txBuffer[i2c0_transaction.txIndex++];
		}
		else
		{
			LPC_I2C0->I2CONSET = STOP_FLAG;
			i2c0_transaction.status = I2C_DONE;
		}
		break;

	case SLA_RXD_ACK_RECEIVED:
		if (i2c0_transaction.rxIndex < (i2c0_transaction.rxLength - 1))
			LPC_I2C0->I2CONSET = ASSERT_ACKNOWLEDGE_FLAG;
		else
			LPC_I2C0->I2CONCLR = ASSERT_ACKNOWLEDGE_FLAG;
		break;

	case DATA_RXD_ACK_TRANSMITTED:
		i2c0_transaction.rxBuffer[i2c0_transaction.rxIndex++] = LPC_I2C0->I2DAT;
		if (i2c0_transaction.rxIndex < (i2c0_transaction.rxLength - 1))
			LPC_I2C0->I2CONSET = ASSERT_ACKNOWLEDGE_FLAG;
		else
			LPC_I2C0->I2CONCLR = ASSERT_ACKNOWLEDGE_FLAG;
		break;

	case DATA_RXD_NACK_TRANSMITTED:
		i2c0_transaction.rxBuffer[i2c0_transaction.rxIndex++] = LPC_I2C0->I2DAT;
		LPC_I2C0->I2CONSET = STOP_FLAG;
		i2c0_transaction.status = I2C_DONE;
		break;

	default:
		LPC_I2C0->I2CONSET = STOP_FLAG;
		i2c0_transaction.status = I2C_ERROR;
		break;
	}

	LPC_I2C0->I2CONCLR = I2C_INTERRUPT_FLAG;
}

void set_i2c0_interrupt_priority(uint8_t in_interrupt_priority)
{
    #define IPR2   (*((volatile unsigned long *)0xE000E408))

    if(in_interrupt_priority < 32) // LPC176x supports 5 bits of priority
    {
        IPR2 &= ~(0xFF << 8);                       // Clear bits 15:8
        IPR2 |=  ((in_interrupt_priority & 0x1F) << 8); // Set I2C0 priority
    }
}

