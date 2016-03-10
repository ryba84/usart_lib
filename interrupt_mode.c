/*
 * interrupt_mode.c
 *
 *  Created on: 08 mar 2016
 *      Author: Piotr Rudzki ryba.lodz@gmail.com
 *
 * Simple interrupt mode example. It only echoes what it receives.
 * To test this example You must pass to compiler USE_USART0_INTERRUPT macro.
 * e.g. -DUSE_USART0_INTERRUPT
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "usart_lib.h"

// usart_lib call this function when new data received
void rxDataReady(usartNumber_T const usartNumber) {
	int16_t tmp = usartGetByteFromReceiveBuffer(usartNumber); // get data from buffer
	if (tmp > -1) { // if buffer not empty
		int8_t txBufferFlag = usartPutByteToTransmitBuffer(usartNumber,(uint8_t)tmp); // put received data to transmit buffer
		if (txBufferFlag == 0) { // if there was room in buffer
			usartTxStart(usartNumber); // start transmitting data
		}
	}
}

int main(void) {
	usartInit(USART0, BAUD_CALC(14400)); // Initialize USART0
	registerRxDataReadyCallback(&rxDataReady); // Register callback
	usartRxStart(USART0); // Start interrupt based receiver

	sei(); // global interrupts enable

// main program loop
	while (1) {
// something to do without waiting for USART
	}
}
