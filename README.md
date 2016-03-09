License

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/.

For full license see http://www.gnu.org/licenses/gpl-3.0.en.html
Introduction

For now only supported data format is 8N1. This library supports two modes of operation for up to four USART's.

    Interrupt based mode with separate circular transmitting and receiving buffers for each enabled USART
    Normal mode without additional buffers.
    Mixing modes of operation is supported, e.g. USART0 in interrupt based mode, and USART1 in normal mode.

Changelog

Version
    2.0 - 08.03.2016

        full library rewrite, whole usage change
        added doxygen generated documentation
        supported: ATmega162, ATmega48, ATmega88, ATmega168, ATmega328, ATmega640, ATmega1280, ATmega1281, ATmega2560, ATmega2561, Atmega16, ATmega32, ATmega323, ATmega8

Todo:

    add support for more AVR MCU's
    add support for more frame formats
    add support for MPCM

Bug:

    ATmega161 not working! Changes in usartInit(usartNumber_T, uint16_t) function and in usart_lib-mach.h needed.

Usage

    Include usart_lib.h in your sources.
    Define proper macros, below details.
    Desired USART must be initialized before use. In both modes procedure looks identical. Simply call usartInit(usartNumber_T, uint16_t) function.

Interrupt based usage:

    Define minimum one USART to use. e.g. USE_USART0_INTERRUPT, USE_USART1_INTERRUPT, USE_USART1_INTERRUPT, USE_USART1_INTERRUPT. You can simply define this at the beginning usart_lib.h or in CFLAGS passed to AVR-GCC. Second option is preferred.
    Additional define buffers length separate for every USART transmitter and receiver. e.g. USART0_RX_BUFFER_LENGTH=32, USART0_TX_BUFFER_LENGTH=64. NOTE buffer length must be power of 2 and not exceed 256. If you not define buffers for used USART both buffers will be 16 bytes length.
    Use functions provided for this purpose.

Warning
    If interrupt mode isn't used for given USART it should not be enabled by macro USE_USARTx_INTERRUPT. It'll use some flash for two ISR (for receiver and transmitter) and some RAM for buffers! 

See also
    Interrupt mode receiver functions 
    Interrupt mode transmitter functions

Normal usage:

    Define minimum one USART to use: USE_USART0, USE_USART1, USE_USART2, USE_USART3. You can simply define this at the beginning usart_lib.h or in CFLAGS passed to AVR-GCC. Second option is preferred.
    Use functions provided for this purpose.

See also
    Normal mode receiver functions 
    Normal mode transmitter functions 