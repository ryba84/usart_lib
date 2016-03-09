/*
 * usart_lib.c
 *
 *  Created on: 08 mar 2016
 *      Author: Piotr Rudzki ryba.lodz@gmail.com
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

#include "usart_lib.h"

#if defined (USE_USART0_INTERRUPT)
uint8_t us0rxBuff[USART0_RX_BUFFER_LENGTH]; // receiver data buffer
volatile fifo_T usart0rxBuffer = { .data = us0rxBuff, }; // receiver circular buffer
uint8_t us0txBuff[USART0_TX_BUFFER_LENGTH]; // transmitter data buffer
fifo_T us0txStruct = { .data = us0txBuff, }; // transmitter circular buffer
volatile usartTxBuffer_T usart0txBuffer = { .buffer = &us0txStruct, .status =
		STOPPED, }; // transmitter structure
#endif /* defined (USE_USART0_INTERRUPT) */
#if defined (USE_USART1_INTERRUPT)
uint8_t us1rxBuff[USART1_RX_BUFFER_LENGTH]; // receiver data buffer
volatile fifo_T usart1rxBuffer = { .data = us1rxBuff, }; // receiver circular buffer
uint8_t us1txBuff[USART1_TX_BUFFER_LENGTH]; // transmitter data buffer
fifo_T us1txStruct = { .data = us1txBuff, }; // transmitter circular buffer
volatile usartTxBuffer_T usart1txBuffer = { .buffer = &us1txStruct, .status =
		STOPPED, };
#endif /* defined (USE_USART1_INTERRUPT) */
#if defined (USE_USART2_INTERRUPT)
uint8_t us2rxBuff[USART2_RX_BUFFER_LENGTH]; // receiver data buffer
volatile fifo_T usart2rxBuffer = { .data = us2rxBuff, }; // receiver circular buffer
uint8_t us2txBuff[USART2_TX_BUFFER_LENGTH]; // transmitter data buffer
fifo_T us2txStruct = { .data = us2txBuff, }; // transmitter circular buffer
volatile usartTxBuffer_T usart2txBuffer = { .buffer = &us2txStruct, .status =
		STOPPED, };
#endif /* defined (USE_USART2_INTERRUPT) */
#if defined (USE_USART3_INTERRUPT)
uint8_t us3rxBuff[USART3_RX_BUFFER_LENGTH]; // receiver data buffer
volatile fifo_T usart3rxBuffer = { .data = us3rxBuff, }; // receiver circular buffer
uint8_t us3txBuff[USART3_TX_BUFFER_LENGTH]; // transmitter data buffer
fifo_T us3txStruct = { .data = us3txBuff, }; // transmitter circular buffer
volatile usartTxBuffer_T usart3txBuffer = { .buffer = &us3txStruct, .status =
		STOPPED, };
#endif /* defined (USE_USART3_INTERRUPT) */

#if defined (USE_USART0_INTERRUPT) || defined (USE_USART1_INTERRUPT)\
	|| defined (USE_USART2_INTERRUPT) || defined (USE_USART3_INTERRUPT)
// Get byte from buffer. Returns data or -1 if buffer empty
int16_t __usartGetByteFromBuffer(volatile fifo_T * const buffer,
		uint8_t const bufferMask) {
	uint8_t tmp = 0;
	if (buffer->tail != buffer->head) { // if buffer not empty
		tmp = buffer->data[buffer->tail]; // get data from buffer
		buffer->tail = (buffer->tail + 1) & bufferMask; // move buffer tail
		return tmp; // return data
	}
	return -1; // return buffer empty
}
// Put byte in buffer. Returns -1 if buffer full
int8_t __usartPutByteToBuffer(uint8_t const data, volatile fifo_T * const buffer,
		uint8_t const bufferMask) {
	uint8_t next = (buffer->head + 1) & bufferMask; // get next byte index in buffer
	if (next != buffer->tail) { // if there is room in buffer
		buffer->data[buffer->head] = data; // put data in buffer
		buffer->head = next; // move head
		return 0;
	}
	return -1;
}
int16_t usartGetByteFromReceiveBuffer(usartNumber_T const usartNumber) {
	volatile fifo_T * buffer = 0;
	uint8_t bufferMask = 0;
	switch (usartNumber) {
#if defined (USE_USART0_INTERRUPT)
	case USART0:
		buffer = &usart0rxBuffer;
		bufferMask = USART0_RX_BUFFER_MASK;
		break;
#endif /* defined (USE_USART0_INTERRUPT) */
#if defined (USE_USART1_INTERRUPT)
	case USART1:
		buffer = &usart1rxBuffer;
		bufferMask = USART1_RX_BUFFER_MASK;
		break;
#endif /* defined (USE_USART1_INTERRUPT) */
#if defined (USE_USART2_INTERRUPT)
	case USART2:
		buffer = &usart2rxBuffer;
		bufferMask = USART2_RX_BUFFER_MASK;
		break;
#endif /* defined (USE_USART2_INTERRUPT) */
#if defined (USE_USART3_INTERRUPT)
	case USART3:
		buffer = &usart3rxBuffer;
		bufferMask = USART3_RX_BUFFER_MASK;
		break;
#endif /* defined (USE_USART3_INTERRUPT) */
	default:
		break;
	}
	return (__usartGetByteFromBuffer(buffer, bufferMask));
}
int8_t usartPutByteToTransmitBuffer(usartNumber_T const usartNumber, uint8_t const data) {
	volatile fifo_T * buffer = 0;
	uint8_t bufferMask = 0;
	switch (usartNumber) {
#if defined (USE_USART0_INTERRUPT)
	case USART0:
		buffer = usart0txBuffer.buffer;
		bufferMask = USART0_TX_BUFFER_MASK;
		break;
#endif /* defined (USE_USART0_INTERRUPT) */
#if defined (USE_USART1_INTERRUPT)
	case USART1:
		buffer = usart1txBuffer.buffer;
		bufferMask = USART1_TX_BUFFER_MASK;
		break;
#endif /* defined (USE_USART1_INTERRUPT) */
#if defined (USE_USART2_INTERRUPT)
	case USART2:
		buffer = usart2txBuffer.buffer;
		bufferMask = USART2_TX_BUFFER_MASK;
		break;
#endif /* defined (USE_USART2_INTERRUPT) */
#if defined (USE_USART3_INTERRUPT)
	case USART3:
		buffer = usart3txBuffer.buffer;
		bufferMask = USART3_TX_BUFFER_MASK;
		break;
#endif /* defined (USE_USART3_INTERRUPT) */
	default:
		break;
	}
	return (__usartPutByteToBuffer(data, buffer, bufferMask));
}
#endif /* defined (USE_USART0_INTERRUPT) || defined (USE_USART1_INTERRUPT) || defined (USE_USART2_INTERRUPT) || defined (USE_USART3_INTERRUPT) */
// USART initialization
void usartInit(usartNumber_T const usartNumber, uint16_t const ubrrValue) {
	switch (usartNumber) {
#if defined (USE_USART0)
	case USART0:
		// set baud rate
		UBRR_HIGH_REG0 = (uint8_t) ((ubrrValue & 0x7fff) >> 8);
		UBRR_LOW_REG0 = (uint8_t) ubrrValue;
		if (ubrrValue & 0x8000) {
			USART0_SET_U2X;
		} else {
			USART0_CLR_U2X;
		}
		// enable receiver and transmitter
		USART0_ENABLE_RXTX;
		// 8N1 (8 bit data, no parity, one stop)
		USART0_8N1_FRAME_FORMAT;
		break;
#endif /* defined (USE_USART0) */
#if defined (USE_USART1)
	case USART1:
		// set baud rate
		UBRR_HIGH_REG1 = (ubrrValue >> 8);
		UBRR_LOW_REG1 = (uint8_t) ubrrValue;
		if ((ubrrValue & 0x10000)) {
			USART1_SET_U2X;
		} else {
			USART1_CLR_U2X;
		}
		// enable receiver and transmitter
		USART1_ENABLE_RXTX;
		// 8N1 (8 bit data, no parity, one stop)
		USART1_8N1_FRAME_FORMAT;
		break;
#endif /* defined (USE_USART1) */
#if defined (USE_USART2)
	case USART2:
		// set baud rate
		UBRR_HIGH_REG2 = (ubrrValue >> 8);
		UBRR_LOW_REG2 = (uint8_t) ubrrValue;
		if (ubrrValue & 0x10000) {
			USART2_SET_U2X;
		} else {
			USART2_CLR_U2X;
		}
		// enable receiver and transmitter
		USART2_ENABLE_RXTX;
		// 8N1 (8 bit data, no parity, one stop)
		USART2_8N1_FRAME_FORMAT;
		break;
#endif /* defined (USE_USART2) */
#if defined (USE_USART3)
	case USART3:
		// set baud rate
		UBRR_HIGH_REG3 = (ubrrValue >> 8);
		UBRR_LOW_REG3 = (uint8_t) ubrrValue;
		if (ubrrValue & 0x10000) {
			USART3_SET_U2X;
		} else {
			USART3_CLR_U2X;
		}
		// enable receiver and transmitter
		USART3_ENABLE_RXTX;
		// 8N1 (8 bit data, no parity, one stop)
		USART3_8N1_FRAME_FORMAT;
		break;
#endif /* defined (USE_USART3) */
	default:
		break;
	}
}
#if defined (USE_USART0_INTERRUPT) || defined (USE_USART1_INTERRUPT)\
	|| defined (USE_USART2_INTERRUPT) || defined (USE_USART3_INTERRUPT)
// Callback function
_usartFctPtr_T _rxDataReadyCallback;
// Callback function
_usartFctPtr_T _rxBufferFullCallback;
void registerRxDataReadyCallback(_usartFctPtr_T callback) {
	_rxDataReadyCallback = callback;
}
void registerRxBufferFullCallback(_usartFctPtr_T callback) {
	_rxBufferFullCallback = callback;
}
// start interrupt based receiver
void usartRxStart(usartNumber_T usartNumber) {
	switch (usartNumber) {
#if defined (USE_USART0_INTERRUPT)
	case USART0:
		USART0_SET_RXCIE;
		break;
#endif /* defined (USE_USART0_INTERRUPT) */
#if defined (USE_USART1_INTERRUPT)
	case USART1:
		USART1_SET_RXCIE;
		break;
#endif /* defined (USE_USART1_INTERRUPT) */
#if defined (USE_USART2_INTERRUPT)
	case USART2:
		USART2_SET_RXCIE;
		break;
#endif /* defined (USE_USART2_INTERRUPT) */
#if defined (USE_USART3_INTERRUPT)
	case USART3:
		USART3_SET_RXCIE;
		break;
#endif /* defined (USE_USART3_INTERRUPT) */
	default:
		break;
	}
}
#endif /* defined (USE_USART0_INTERRUPT) || defined (USE_USART1_INTERRUPT) || defined (USE_USART2_INTERRUPT) || defined (USE_USART3_INTERRUPT) */
uint8_t usartDataReceived(usartNumber_T const usartNumber) {
	uint8_t tmp = 0;
	switch (usartNumber) {
#if defined (USE_USART0)
	case USART0:
		tmp = USART0_TEST_RXC;
		break;
#endif /* defined (USE_USART0) */
#if defined (USE_USART1)
	case USART1:
		tmp = USART1_TEST_RXC;
		break;
#endif /* defined (USE_USART1) */
#if defined (USE_USART2)
	case USART2:
		tmp = USART2_TEST_RXC;
		break;
#endif /* defined (USE_USART2) */
#if defined (USE_USART3)
	case USART3:
		tmp = USART3_TEST_RXC;
		break;
#endif /* defined (USE_USART3) */
	default:
		break;
	}
	return tmp;
}
uint8_t usartImGetByte(usartNumber_T const usartNumber) {
	uint8_t tmp = 0;
	switch (usartNumber) {
#if defined (USE_USART0)
	case USART0:
		tmp = USART_DATA_REG0;
		break;
#endif /* defined (USE_USART0) */
#if defined (USE_USART1)
	case USART1:
		tmp = USART_DATA_REG1;
		break;
#endif /* defined (USE_USART1) */
#if defined (USE_USART2)
	case USART2:
		tmp = USART_DATA_REG2;
		break;
#endif /* defined (USE_USART2) */
#if defined (USE_USART3)
	case USART3:
		tmp = USART_DATA_REG3;
		break;
#endif /* defined (USE_USART3) */
	default:
		break;
	}
	return tmp;
}
uint8_t usartGetByte(usartNumber_T const usartNumber) {
	while (!(usartDataReceived(usartNumber)))
		;
	return usartImGetByte(usartNumber);
}
#if defined (USE_USART0_INTERRUPT) || defined (USE_USART1_INTERRUPT)\
	|| defined (USE_USART2_INTERRUPT) || defined (USE_USART3_INTERRUPT)
// Callback function
void (*_txCompleteCallback)(usartNumber_T const usartNumber);
void registerTxCompleteCallback(_usartFctPtr_T callback) {
	_txCompleteCallback = callback;
}
// Start sending data from buffer.
void usartTxStart(usartNumber_T const usartNumber) {
	volatile usartTxBuffer_T * tmpPtr = 0;
	uint8_t bufferMask = 0;
	int16_t tmp = 0;
	switch (usartNumber) {
#if defined (USE_USART0_INTERRUPT)
	case USART0:
		USART0_SET_TXCIE;
		tmpPtr = &usart0txBuffer;
		bufferMask = USART0_TX_BUFFER_MASK;
		break;
#endif /* defined (USE_USART0_INTERRUPT) */
#if defined (USE_USART1_INTERRUPT)
	case USART1:
		USART1_SET_TXCIE;
		tmpPtr = &usart1txBuffer;
		bufferMask = USART1_TX_BUFFER_MASK;
		break;
#endif /* defined (USE_USART1_INTERRUPT) */
#if defined (USE_USART2_INTERRUPT)
	case USART2:
		USART2_SET_TXCIE;
		tmpPtr = &usart2txBuffer;
		bufferMask = USART2_TX_BUFFER_MASK;
		break;
#endif /* defined (USE_USART2_INTERRUPT) */
#if defined (USE_USART3_INTERRUPT)
	case USART3:
		USART3_SET_TXCIE;
		tmpPtr = &usart3txBuffer;
		bufferMask = USART3_TX_BUFFER_MASK;
		break;
#endif /* defined (USE_USART3_INTERRUPT) */
	default:
		break;
	}
	if (tmpPtr->status == STOPPED) { // if transmitter not working
		tmp = __usartGetByteFromBuffer(tmpPtr->buffer, bufferMask); // get data from buffer
		if (tmp > -1) { // if buffer not empty
			tmpPtr->status = STARTED; // set transmitter working flag
			usartImPutByte(usartNumber, tmp); // send first byte
		}
	}
}
#endif /* defined (USE_USART0_INTERRUPT) || defined (USE_USART1_INTERRUPT) || defined (USE_USART2_INTERRUPT) || defined (USE_USART3_INTERRUPT) */
uint8_t usartDataTransferred(usartNumber_T const usartNumber) {
	uint8_t tmp = 0;
	switch (usartNumber) {
#if defined (USE_USART0)
	case USART0:
		tmp = USART0_TEST_TXC;
		break;
#endif /* defined (USE_USART0) */
#if defined (USE_USART1)
	case USART1:
		tmp = USART1_TEST_TXC;
		break;
#endif /* defined (USE_USART0) */
#if defined (USE_USART2)
	case USART2:
		tmp = USART2_TEST_TXC;
		break;
#endif /* defined (USE_USART0) */
#if defined (USE_USART3)
	case USART3:
		tmp = USART3_TEST_TXC;
		break;
#endif /* defined (USE_USART0) */
	default:
		break;
	}
	return tmp;
}
void usartImPutByte(usartNumber_T const usartNumber, uint8_t const data) {
	switch (usartNumber) {
#if defined (USE_USART0) || defined (USE_USART0_INTERRUPT)
	case USART0:
		USART_DATA_REG0 = data;
		break;
#endif /* defined (USE_USART0) || defined (USE_USART0_INTERRUPT) */
#if defined (USE_USART1) || defined (USE_USART1_INTERRUPT)
	case USART1:
		USART_DATA_REG1 = data;
		break;
#endif /* defined (USE_USART1) || defined (USE_USART1_INTERRUPT) */
#if defined (USE_USART2) || defined (USE_USART2_INTERRUPT)
	case USART2:
		USART_DATA_REG2 = data;
		break;
#endif /* defined (USE_USART2) || defined (USE_USART2_INTERRUPT) */
#if defined (USE_USART3) || defined (USE_USART3_INTERRUPT)
	case USART3:
		USART_DATA_REG3 = data;
		break;
#endif /* defined (USE_USART3) || defined (USE_USART3_INTERRUPT) */
	default:
		break;
	}
}
void usartPutByte(usartNumber_T const usartNumber, uint8_t const data) {
	while (!(usartDataTransferred(usartNumber)))
		;
	usartImPutByte(usartNumber, data);
}
#if defined (USE_USART0_INTERRUPT) || defined (USE_USART1_INTERRUPT)\
	|| defined (USE_USART2_INTERRUPT) || defined (USE_USART3_INTERRUPT)
#if defined (USE_USART0_INTERRUPT)
ISR(USART0_RX_ISR) {
	// if there is room for next byte in buffer
	if (__usartPutByteToBuffer(USART_DATA_REG0, &usart0rxBuffer, USART0_RX_BUFFER_MASK)
			> -1) {
		if (_rxDataReadyCallback) {
			(*_rxDataReadyCallback)(USART0); // new data ready
		}
	} else {
		if (_rxBufferFullCallback) {
			// next received byte generate buffer overrun
			(*_rxBufferFullCallback)(USART0);
		}
	}
}
ISR(USART0_TX_ISR) {
	int16_t tmp = __usartGetByteFromBuffer(usart0txBuffer.buffer,
	USART0_TX_BUFFER_MASK); // get data from buffer
	if (tmp > -1) { // if buffer was not empty
		USART_DATA_REG0 = tmp; // send
	} else {
		usart0txBuffer.status = STOPPED; // set transmitter stop flag
		USART0_CLR_TXCIE; // disable USART TX interrupt
		if (_txCompleteCallback) {
			(*_txCompleteCallback)(USART0); // transmit complete
		}
	}
}
#endif /* defined (USE_USART0_INTERRUPT) */
#if defined (USE_USART1_INTERRUPT)
ISR(USART1_RX_ISR) {
	// if there is room for next byte in buffer
	if (__usartPutByteToBuffer(USART_DATA_REG1, &usart1rxBuffer, USART1_RX_BUFFER_MASK)
			> -1) {
		if (_rxDataReadyCallback) {
			(*_rxDataReadyCallback)(USART1); // new data ready
		}
	} else {
		if (_rxBufferFullCallback) {
			// next received byte generate buffer overrun
			(*_rxBufferFullCallback)(USART1);
		}
	}
}
ISR(USART1_TX_ISR) {
	int16_t tmp = __usartGetByteFromBuffer(usart1txBuffer.buffer,
	USART1_TX_BUFFER_MASK); // get data from buffer
	if (tmp > -1) { // if buffer was not empty
		USART_DATA_REG1 = tmp; // send
	} else {
		usart1txBuffer.status = STOPPED; // set transmitter stop flag
		USART1_CLR_TXCIE; // disable USART TX interrupt
		if (_txCompleteCallback) {
			(*_txCompleteCallback)(USART1); // transmit complete
		}
	}
}
#endif /* defined (USE_USART1_INTERRUPT) */
#if defined (USE_USART2_INTERRUPT)
ISR(USART2_RX_ISR) {
	// if there is room for next byte in buffer
	if (__usartPutByteToBuffer(USART_DATA_REG2, &usart2rxBuffer, USART2_RX_BUFFER_MASK)
			> -1) {
		if (_rxDataReadyCallback) {
			(*_rxDataReadyCallback)(USART2); // new data ready
		}
	} else {
		if (_rxBufferFullCallback) {
			// next received byte generate buffer overrun
			(*_rxBufferFullCallback)(USART2);
		}
	}
}
ISR(USART2_TX_ISR) {
	int16_t tmp = __usartGetByteFromBuffer(usart2txBuffer.buffer,
	USART2_TX_BUFFER_MASK); // get data from buffer
	if (tmp > -1) { // if buffer was not empty
		USART_DATA_REG2 = tmp; // send
	} else {
		usart2txBuffer.status = STOPPED; // set transmitter stop flag
		USART2_CLR_TXCIE; // disable USART TX interrupt
		if (_txCompleteCallback) {
			(*_txCompleteCallback)(USART2); // transmit complete
		}
	}
}
#endif /* defined (USE_USART2_INTERRUPT) */
#if defined (USE_USART3_INTERRUPT)
ISR(USART3_RX_ISR) {
	// if there is room for next byte in buffer
	if (__usartPutByteToBuffer(USART_DATA_REG3, &usart3rxBuffer, USART3_RX_BUFFER_MASK)
			> -1) {
		if (_rxDataReadyCallback) {
			(*_rxDataReadyCallback)(USART3); // new data ready
		}
	} else {
		if (_rxBufferFullCallback) {
			// next received byte generate buffer overrun
			(*_rxBufferFullCallback)(USART3);
		}
	}
}
ISR(USART3_TX_ISR) {
	int16_t tmp = __usartGetByteFromBuffer(usart3txBuffer.buffer,
	USART3_TX_BUFFER_MASK); // get data from buffer
	if (tmp > -1) { // if buffer was not empty
		USART_DATA_REG3 = tmp; // send
	} else {
		usart3txBuffer.status = STOPPED; // set transmitter stop flag
		USART3_CLR_TXCIE; // disable USART TX interrupt
		if (_txCompleteCallback) {
			(*_txCompleteCallback)(USART3); // transmit complete
		}
	}
}
#endif /* defined (USE_USART3_INTERRUPT) */
#endif /* defined (USE_USART0_INTERRUPT) || defined (USE_USART1_INTERRUPT) || defined (USE_USART2_INTERRUPT) || defined (USE_USART3_INTERRUPT) */
