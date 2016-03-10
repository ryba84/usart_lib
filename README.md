##Hardware USART library for AVR 8bit MCU's

###Copyright
>Piotr Rudzki (c)2015 

###License

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/.

For full license see http://www.gnu.org/licenses/gpl-3.0.en.html

###Introduction

For now only supported data format is 8N1. This library supports two modes of operation for up to four USART's.

> - Interrupt based mode with separate circular transmitting and receiving buffers for each enabled USART. 
> - Normal mode without additional buffers.
> - Mixing modes of operation is supported, e.g. USART0 in interrupt based mode, and USART1 in normal mode.

For usage see refman.pdf in doc directory.

###Changelog:

Version 2.0 - 08.03.2016
 - full library rewrite, whole usage change
 - added doxygen generated documentation
 - supported MCU: ATmega162, ATmega48, ATmega88, ATmega168, ATmega328, ATmega640, ATmega1280, ATmega1281, ATmega2560, ATmega2561, Atmega16, ATmega32, ATmega323, ATmega8

###Todo:
 - add support for more AVR MCU's
 - add support for more frame formats
 - add support for MPCM

