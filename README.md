# LPC1768_Real_time_clock_using_I2C_desplay
Designed and implemented interrupt-driven bare-metal firmware on LPC1768 ARM Cortex-M3 featuring RTC peripheral configuration and I2C 16x2 LCD driver integration in Embedded C.

## Features

- Bare-metal embedded firmware development
- Register-level peripheral programming
- Real-Time Clock (RTC) configuration
- Interrupt-driven RTC updates
- I2C communication driver implementation
- 16x2 LCD interfacing using PCF8574
- Real-time date and time display
- Modular embedded driver architecture
- ARM Cortex-M3 peripheral handling

- ## Hardware Used

- LPC1768 ARM Cortex-M3 Microcontroller
- 16x2 Character LCD
- PCF8574 I2C LCD Backpack
- LPC1768 Development Board

- ## Software and Tools

- Embedded C
- Keil uVision / MCUXpresso
- CMSIS
- Git
- GitHub

- ## Project Architecture

- RTC Driver
- I2C Driver
- LCD Driver
- Timer Driver
- Interrupt Handling
- Main Application Layer

- ## Folder Structure

├── main.c                                                                                                                                                         
├── rtc.c                                                                                                                                                          
├── rtc.h                                                                                                                                                         
├── timer0.c                                                                                                                                                       
├── timer0.h                                                                                                                                                       
├── i2c0.c                                                                                                                                                         
├── i2c0.h                                                                                                                                                         
├── lcd_16_2_character_iic.c                                                                                                                                       
├── lcd_16_2_character_iic.h                                                                                                                                       
├── Bitss.h                                                                                                                                                        
└── README.md                                                                                                                                                   

## RTC Functionality

- RTC configured using LPC1768 internal RTC peripheral
- Generates interrupt every second
- Displays live date and time on LCD
- Uses interrupt-driven architecture for periodic updates

- ## LCD Interface

- 16x2 LCD operated in 4-bit mode
- PCF8574 I2C backpack communication
- Cursor positioning support
- Real-time string display support

- ## Interrupt Handling

- RTC interrupt configured using NVIC
- Periodic RTC tick interrupt every second
- Efficient interrupt-driven embedded architecture

- ## Output

LCD Display Example:

26/05/2026
14:45:10

## Future Improvements

- Alarm functionality
- UART debugging interface
- EEPROM data logging
- Temperature sensor integration
- Menu-driven LCD interface
- Low-power sleep mode support


## Author
Adithya S Devadiga
Electronics and Communication Engineering (ECE)
Embedded Systems Enthusiast
