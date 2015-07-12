/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_PERIPHERALNAMES_H
#define MBED_PERIPHERALNAMES_H

#include "cmsis.h"
#include "PinNames.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    UART0 = 0
} UARTName;

// typedef enum {
//     PWM1A = 0;
// } PWMType;

// typedef enum {
//     PWM0_PIN = 0;
// } PWMName;


// typedef enum {
//     SPI_0 = 0,
//     SPI_1,
//     SPI_2,
// } SPIName;

// typedef enum {
//     I2C_0 = 0,
//     I2C_1,
//     I2C_2,
//     I2C_3 
// } I2CName;


#define STDIO_UART_TX     UART_TXD0
#define STDIO_UART_RX     UART_RXD0
#define STDIO_UART        UART0


#ifdef __cplusplus
}
#endif

#endif
