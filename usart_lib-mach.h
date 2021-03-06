/*
 * usart_lib-mach.h
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

#ifndef USART_LIB_MACH_H_
#define USART_LIB_MACH_H_

/*! \file
 * \brief Hardware support definitions.
 *
 * If You want add support for new MCU you can edit this file. Read comments in code for details.
 * \copyright Piotr Rudzki (c)2015
 * \date 08.03.2016
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#if defined (__AVR_ATmega161__) // not tested but should work
#if defined (USE_USART2) || defined (USE_USART2_INTERRUPT) || defined (USE_USART3) || defined (USE_USART3_INTERRUPT)
#error "Supported only USART0 and USART1!!!"
#endif /* defined (USE_USART2) || defined (USE_USART2_INTERRUPT) || defined (USE_USART3) || defined (USE_USART3_INTERRUPT) */
// interrupt vectors
#define USART0_RX_ISR UART0_RX_vect
#define USART0_TX_ISR UART0_TX_vect
#define USART1_RX_ISR UART1_RX_vect
#define USART1_TX_ISR UART1_TX_vect
// UBRR and U2X
#define USART0_SET_UBRRH(x) (UBRRH = (UBRRH & 0xf0) | ((ubrrValue >> 8) & 0x0f))
#define USART0_SET_UBRRL(x) (UBRR0 = (uint8_t) ubrrValue)
#define USART1_SET_UBRRH(x) (UBRRH = (UBRRH & 0x0f) | ((ubrrValue >> 4) & 0xf0))
#define USART1_SET_UBRRL(x) (UBRR1 = (uint8_t) ubrrValue)
#define USART0_SET_U2X (UCSR0A = (1 << U2X))
#define USART0_CLR_U2X (UCSR0A &= ~(1 << U2X))
#define USART1_SET_U2X (UCSR1A = (1 << U2X))
#define USART1_CLR_U2X (UCSR1A &= ~(1 << U2X))
// frame format
#define USART0_8N1_FRAME_FORMAT
#define USART1_8N1_FRAME_FORMAT
// transmitter and receiver enable
#define USART0_ENABLE_RXTX (UCSR0B |= (1 << RXEN) | (1 << TXEN))
#define USART1_ENABLE_RXTX (UCSR1B |= (1 << RXEN) | (1 << TXEN))
// data registers
#define USART0_DATA_REG UDR0
#define USART1_DATA_REG UDR1
// RX interrupt
#define USART0_SET_RXCIE (UCSR0B |= (1 << RXCIE))
#define USART0_CLR_RXCIE (UCSR0B &= ~(1 << RXCIE))
#define USART1_SET_RXCIE (UCSR1B |= (1 << RXCIE))
#define USART1_CLR_RXCIE (UCSR1B &= ~(1 << RXCIE))
// TX interrupt
#define USART0_SET_TXCIE (UCSR0B |= (1 << TXCIE))
#define USART0_CLR_TXCIE (UCSR0B &= ~(1 << TXCIE))
#define USART1_SET_TXCIE (UCSR1B |= (1 << TXCIE))
#define USART1_CLR_TXCIE (UCSR1B &= ~(1 << TXCIE))
// test RX complete
#define USART0_TEST_RXC	(UCSR0A & (1 << RXC))
#define USART1_TEST_RXC	(UCSR1A & (1 << RXC))
// test TX complete
#define USART0_TEST_TXC	(UCSR0A & (1 << UDRE))
#define USART1_TEST_TXC	(UCSR1A & (1 << UDRE))
#elif defined (__AVR_ATmega162__) // not tested but should work
#if defined (USE_USART2) || defined (USE_USART2_INTERRUPT) || defined (USE_USART3) || defined (USE_USART3_INTERRUPT)
#error "Supported only USART0 and USART1!!!"
#endif /* defined (USE_USART2) || defined (USE_USART2_INTERRUPT) || defined (USE_USART3) || defined (USE_USART3_INTERRUPT) */
// interrupt vectors
#define USART0_RX_ISR USART0_RXC_vect
#define USART0_TX_ISR USART0_TXC_vect
#define USART1_RX_ISR USART1_RXC_vect
#define USART1_TX_ISR USART1_TXC_vect
// UBRR and U2X
#define USART0_SET_UBRRH(x) (UBRR0H = (ubrrValue >> 8) & 0x0f)
#define USART0_SET_UBRRL(x) (UBRR0L = (uint8_t) ubrrValue)
#define USART1_SET_UBRRH(x) (UBRR0H = (ubrrValue >> 8) & 0x0f)
#define USART1_SET_UBRRL(x) (UBRR0L = (uint8_t) ubrrValue)
#define USART0_SET_U2X (UCSR0A = (1 << U2X0))
#define USART0_CLR_U2X (UCSR0A &= ~(1 << U2X0))
#define USART1_SET_U2X (UCSR1A = (1 << U2X1))
#define USART1_CLR_U2X (UCSR1A &= ~(1 << U2X1))
// frame format
#define USART0_8N1_FRAME_FORMAT (UCSR0C = (1 << URSEL0) | (1 << UCSZ00) | (1 << UCSZ01))
#define USART1_8N1_FRAME_FORMAT (UCSR1C = (1 << URSEL1) | (1 << UCSZ10) | (1 << UCSZ11))
// transmitter and receiver enable
#define USART0_ENABLE_RXTX (UCSR0B |= (1 << RXEN0) | (1 << TXEN0))
#define USART1_ENABLE_RXTX (UCSR1B |= (1 << RXEN1) | (1 << TXEN1))
// data registers
#define USART0_DATA_REG UDR0
#define USART1_DATA_REG UDR1
// RX interrupt
#define USART0_SET_RXCIE (UCSR0B |= (1 << RXCIE0))
#define USART0_CLR_RXCIE (UCSR0B &= ~(1 << RXCIE0))
#define USART1_SET_RXCIE (UCSR1B |= (1 << RXCIE1))
#define USART1_CLR_RXCIE (UCSR1B &= ~(1 << RXCIE1))
// TX interrupt
#define USART0_SET_TXCIE (UCSR0B |= (1 << TXCIE0))
#define USART0_CLR_TXCIE (UCSR0B &= ~(1 << TXCIE0))
#define USART1_SET_TXCIE (UCSR1B |= (1 << TXCIE1))
#define USART1_CLR_TXCIE (UCSR1B &= ~(1 << TXCIE1))
// test RX complete
#define USART0_TEST_RXC	(UCSR0A & (1 << RXC0))
#define USART1_TEST_RXC	(UCSR1A & (1 << RXC1))
// test TX complete
#define USART0_TEST_TXC	(UCSR0A & (1 << UDRE0))
#define USART1_TEST_TXC	(UCSR1A & (1 << UDRE1))
#elif defined (__AVR_ATmega48__) || defined (__AVR_ATmega88__) || defined (__AVR_ATmega168__) || defined (__AVR_ATmega328__)
#if defined (USE_USART1) || defined (USE_USART1_INTERRUPT) || defined (USE_USART2) || defined (USE_USART2_INTERRUPT) || defined (USE_USART3) || defined (USE_USART3_INTERRUPT)
#error "Supported only USART0!!!"
#endif /* defined (USE_USART1) || defined (USE_USART1_INTERRUPT) || defined (USE_USART2) || defined (USE_USART2_INTERRUPT) || defined (USE_USART3) || defined (USE_USART3_INTERRUPT) */
// interrupt vectors
#define USART0_RX_ISR USART_RX_vect
#define USART0_TX_ISR USART_TX_vect
// UBRR and U2X
#define USART0_SET_UBRRH(x) (UBRR0H = (ubrrValue >> 8) & 0x0f)
#define USART0_SET_UBRRL(x) (UBRR0L = (uint8_t) ubrrValue)
#define USART0_SET_U2X (UCSR0A = (1 << U2X0))
#define USART0_CLR_U2X (UCSR0A &= ~(1 << U2X0))
// frame format
#define USART0_8N1_FRAME_FORMAT (UCSR0C = (1 << UCSZ00) | (1 << UCSZ01))
// transmitter and receiver enable
#define USART0_ENABLE_RXTX (UCSR0B |= (1 << RXEN0) | (1 << TXEN0))
// data register
#define USART0_DATA_REG UDR0
// RX interrupt
#define USART0_SET_RXCIE (UCSR0B |= (1 << RXCIE0))
#define USART0_CLR_RXCIE (UCSR0B &= ~(1 << RXCIE0))
// TX interrupt
#define USART0_SET_TXCIE (UCSR0B |= (1 << TXCIE0))
#define USART0_CLR_TXCIE (UCSR0B &= ~(1 << TXCIE0))
// test RX complete
#define USART0_TEST_RXC	(UCSR0A & (1 << RXC0))
// test TX complete
#define USART0_TEST_TXC	(UCSR0A & (1 << UDRE0))
#elif defined (__AVR_ATmega640__) || defined (__AVR_ATmega1280__) ||\
	defined (__AVR_ATmega1281__) || defined (__AVR_ATmega2560__) || defined (__AVR_ATmega2561__)
// interrupt vectors
#define USART0_RX_ISR USART0_RX_vect
#define USART0_TX_ISR USART0_TX_vect
#define USART1_RX_ISR USART1_RX_vect
#define USART1_TX_ISR USART1_TX_vect
#define USART2_RX_ISR USART2_RX_vect
#define USART2_TX_ISR USART2_TX_vect
#define USART3_RX_ISR USART3_RX_vect
#define USART3_TX_ISR USART3_TX_vect
// UBRR and U2X
#define USART0_SET_UBRRH(x) (UBRR0H = (ubrrValue >> 8) & 0x0f)
#define USART0_SET_UBRRL(x) (UBRR0L = (uint8_t) ubrrValue)
#define USART1_SET_UBRRH(x) (UBRR1H = (ubrrValue >> 8) & 0x0f)
#define USART1_SET_UBRRL(x) (UBRR1L = (uint8_t) ubrrValue)
#define USART2_SET_UBRRH(x) (UBRR2H = (ubrrValue >> 8) & 0x0f)
#define USART2_SET_UBRRL(x) (UBRR2L = (uint8_t) ubrrValue)
#define USART3_SET_UBRRH(x) (UBRR3H = (ubrrValue >> 8) & 0x0f)
#define USART3_SET_UBRRL(x) (UBRR3L = (uint8_t) ubrrValue)
#define USART0_SET_U2X (UCSR0A = (1 << U2X0))
#define USART0_CLR_U2X (UCSR0A &= ~(1 << U2X0))
#define USART1_SET_U2X (UCSR1A = (1 << U2X1))
#define USART1_CLR_U2X (UCSR1A &= ~(1 << U2X1))
#define USART2_SET_U2X (UCSR2A = (1 << U2X2))
#define USART2_CLR_U2X (UCSR2A &= ~(1 << U2X2))
#define USART3_SET_U2X (UCSR3A = (1 << U2X3))
#define USART3_CLR_U2X (UCSR3A &= ~(1 << U2X3))
// frame format
#define USART0_8N1_FRAME_FORMAT (UCSR0C = (1 << UCSZ00) | (1 << UCSZ01))
#define USART1_8N1_FRAME_FORMAT (UCSR1C = (1 << UCSZ10) | (1 << UCSZ11))
#define USART2_8N1_FRAME_FORMAT (UCSR2C = (1 << UCSZ20) | (1 << UCSZ21))
#define USART3_8N1_FRAME_FORMAT (UCSR3C = (1 << UCSZ30) | (1 << UCSZ31))
// transmitter and receiver enable
#define USART0_ENABLE_RXTX (UCSR0B |= (1 << RXEN0) | (1 << TXEN0))
#define USART1_ENABLE_RXTX (UCSR1B |= (1 << RXEN1) | (1 << TXEN1))
#define USART2_ENABLE_RXTX (UCSR2B |= (1 << RXEN2) | (1 << TXEN2))
#define USART3_ENABLE_RXTX (UCSR3B |= (1 << RXEN3) | (1 << TXEN3))
// data registers
#define USART0_DATA_REG UDR0
#define USART1_DATA_REG UDR1
#define USART2_DATA_REG UDR2
#define USART3_DATA_REG UDR3
// RX interrupt
#define USART0_SET_RXCIE (UCSR0B |= (1 << RXCIE0))
#define USART0_CLR_RXCIE (UCSR0B &= ~(1 << RXCIE0))
#define USART1_SET_RXCIE (UCSR1B |= (1 << RXCIE1))
#define USART1_CLR_RXCIE (UCSR1B &= ~(1 << RXCIE1))
#define USART2_SET_RXCIE (UCSR2B |= (1 << RXCIE2))
#define USART2_CLR_RXCIE (UCSR2B &= ~(1 << RXCIE2))
#define USART3_SET_RXCIE (UCSR3B |= (1 << RXCIE3))
#define USART3_CLR_RXCIE (UCSR3B &= ~(1 << RXCIE3))
// TX interrupt
#define USART0_SET_TXCIE (UCSR0B |= (1 << TXCIE0))
#define USART0_CLR_TXCIE (UCSR0B &= ~(1 << TXCIE0))
#define USART1_SET_TXCIE (UCSR1B |= (1 << TXCIE1))
#define USART1_CLR_TXCIE (UCSR1B &= ~(1 << TXCIE1))
#define USART2_SET_TXCIE (UCSR2B |= (1 << TXCIE2))
#define USART2_CLR_TXCIE (UCSR2B &= ~(1 << TXCIE2))
#define USART3_SET_TXCIE (UCSR3B |= (1 << TXCIE3))
#define USART3_CLR_TXCIE (UCSR3B &= ~(1 << TXCIE3))
// test RX complete
#define USART0_TEST_RXC	(UCSR0A & (1 << RXC0))
#define USART1_TEST_RXC	(UCSR1A & (1 << RXC1))
#define USART2_TEST_RXC	(UCSR2A & (1 << RXC2))
#define USART3_TEST_RXC	(UCSR3A & (1 << RXC3))
// test TX complete
#define USART0_TEST_TXC	(UCSR0A & (1 << UDRE0))
#define USART1_TEST_TXC	(UCSR1A & (1 << UDRE1))
#define USART2_TEST_TXC	(UCSR2A & (1 << UDRE2))
#define USART3_TEST_TXC	(UCSR3A & (1 << UDRE3))
#elif defined (__AVR_ATmega16__) || defined (__AVR_ATmega32__) ||\
	defined (__AVR_ATmega323__) || defined (__AVR_ATmega8__)
#if defined (USE_USART1) || defined (USE_USART1_INTERRUPT) || defined (USE_USART2) || defined (USE_USART2_INTERRUPT) || defined (USE_USART3) || defined (USE_USART3_INTERRUPT)
#error "Supported only USART0!!!"
#endif /* defined (USE_USART1) || defined (USE_USART1_INTERRUPT) || defined (USE_USART2) || defined (USE_USART2_INTERRUPT) || defined (USE_USART3) || defined (USE_USART3_INTERRUPT) */
// interrupt vectors
#define USART0_RX_ISR USART_RXC_vect
#define USART0_TX_ISR USART_TXC_vect
// UBRR and U2X
#define USART0_SET_UBRRH(x) (UBRRH = (ubrrValue >> 8) & 0x0f)
#define USART0_SET_UBRRL(x) (UBRRL = (uint8_t) ubrrValue)
#define USART0_SET_U2X (UCSRA = (1 << U2X))
#define USART0_CLR_U2X (UCSRA &= ~(1 << U2X))
// frame format
#define USART0_8N1_FRAME_FORMAT (UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1))
// transmitter and receiver enable
#define USART0_ENABLE_RXTX (UCSRB |= (1 << RXEN) | (1 << TXEN))
// data register
#define USART0_DATA_REG UDR
// RX interrupt
#define USART0_SET_RXCIE (UCSRB |= (1 << RXCIE))
#define USART0_CLR_RXCIE (UCSRB &= ~(1 << RXCIE))
// TX interrupt
#define USART0_SET_TXCIE (UCSRB |= (1 << TXCIE))
#define USART0_CLR_TXCIE (UCSRB &= ~(1 << TXCIE))
// test RX complete
#define USART0_TEST_RXC	(UCSRA & (1 << RXC))
// test TX complete
#define USART0_TEST_TXC	(UCSRA & (1 << UDRE))
#else
#error "MCU not supported!!! Edit usart_lib-mach.h to add support."
#endif

#endif /* USART_LIB_MACH_H_ */
