/*
 * usart_lib.h
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

#ifndef USART_LIB_H_
#define USART_LIB_H_

/*! \file
 * \brief Include usart_lib.h in Your sources. Do not edit this file, unless You know what You are doing.
 * \copyright Piotr Rudzki (c)2015
 * \date 08.03.2016
 * \defgroup macro_grp Macros
 * Macro definitions
 * \defgroup typedefs_grp Type definitions
 * New type definitions
 * \defgroup universal_fct_grp Universal functions
 * This group contains functions used by all modes transmitter and receiver
 * \defgroup interrupt_rx_grp Interrupt mode receiver functions
 * Functions to use with interrupt mode receiver
 * \defgroup interrupt_tx_grp Interrupt mode transmitter functions
 * Functions to use with interrupt mode transmitter
 * \defgroup normal_rx_grp Normal mode receiver functions
 * Functions to use with normal mode receiver
 * \defgroup normal_tx_grp Normal mode transmitter functions
 * Functions to use with normal mode transmitter
 */

#include <avr/io.h>

#include "usart_lib-mach.h"

#if defined (__DOXYGEN__)
/*! \brief define if You want USART0 support in normal mode
 * \ingroup macro_grp
 */
#define USE_USART0
/*! \brief define if You want USART1 support in normal mode
 * \ingroup macro_grp
 */
#define USE_USART1
/*! \brief define if You want USART2 support in normal mode
 * \ingroup macro_grp
 */
#define USE_USART2
/*! \brief define if You want USART3 support in normal mode
 * \ingroup macro_grp
 */
#define USE_USART3
/*! \brief define if You want USART0 support in interrupt mode
 * \ingroup macro_grp
 */
#define USE_USART0_INTERRUPT
/*! \brief define if You want USART1 support in interrupt mode
 * \ingroup macro_grp
 */
#define USE_USART1_INTERRUPT
/*! \brief define if You want USART2 support in interrupt mode
 * \ingroup macro_grp
 */
#define USE_USART2_INTERRUPT
/*! \brief define if You want USART3 support in interrupt mode
 * \ingroup macro_grp
 */
#define USE_USART3_INTERRUPT
#endif

#if !defined (USE_USART0) && !defined (USE_USART1) && !defined (USE_USART2) && !defined (USE_USART3)\
	&& !defined (USE_USART0_INTERRUPT) && !defined (USE_USART1_INTERRUPT)\
	&& !defined (USE_USART2_INTERRUPT) && !defined (USE_USART3_INTERRUPT)
#error "Define minimum one USART to use!!! (USE_USART0 .. USE_USART0_INTERRUPT)"
#endif

// Ring buffers definitions. Default all buffers are 16 bytes long.
// Each buffer length must be power of 2.
#if defined (USE_USART0_INTERRUPT)
#if !defined (USART0_RX_BUFFER_LENGTH)
/*! \brief USART0 receive buffer length used in interrupt mode
 * \warning maximum defined length 256
 * \ingroup macro_grp
 */
#define USART0_RX_BUFFER_LENGTH 16
#endif /* !defined (USART0_RX_BUFFER_LENGTH) */
#if !defined (USART0_TX_BUFFER_LENGTH)
/*! \brief USART0 transmitter buffer length used in interrupt mode
 * \warning maximum defined length 256
 * \ingroup macro_grp
 */
#define USART0_TX_BUFFER_LENGTH 16
#endif /* !defined (USART0_TX_BUFFER_LENGTH) */
#define USART0_RX_BUFFER_MASK (USART0_RX_BUFFER_LENGTH - 1)
#define USART0_TX_BUFFER_MASK (USART0_TX_BUFFER_LENGTH - 1)
#endif /* defined (USE_USART0_INTERRUPT) */
#if defined (USE_USART1_INTERRUPT)
#if !defined (USART1_RX_BUFFER_LENGTH)
/*! \brief USART1 receive buffer length used in interrupt mode
 * \warning maximum defined length 256
 * \ingroup macro_grp
 */
#define USART1_RX_BUFFER_LENGTH 16
#endif /* !defined (USART1_RX_BUFFER_LENGTH) */
#if !defined (USART1_TX_BUFFER_LENGTH)
/*! \brief USART1 transmitter buffer length used in interrupt mode
 * \warning maximum defined length 256
 * \ingroup macro_grp
 */
#define USART1_TX_BUFFER_LENGTH 16
#endif /* !defined (USART1_TX_BUFFER_LENGTH) */
#define USART1_RX_BUFFER_MASK (USART1_RX_BUFFER_LENGTH - 1)
#define USART1_TX_BUFFER_MASK (USART1_TX_BUFFER_LENGTH - 1)
#endif /* defined (USE_USART1_INTERRUPT) */
#if defined (USE_USART2_INTERRUPT)
#if !defined (USART2_RX_BUFFER_LENGTH)
/*! \brief USART2 receive buffer length used in interrupt mode
 * \warning maximum defined length 256
 * \ingroup macro_grp
 */
#define USART2_RX_BUFFER_LENGTH 16
#endif /* !defined (USART2_RX_BUFFER_LENGTH) */
#if !defined (USART2_TX_BUFFER_LENGTH)
/*! \brief USART2 transmitter buffer length used in interrupt mode
 * \warning maximum defined length 256
 * \ingroup macro_grp
 */
#define USART2_TX_BUFFER_LENGTH 16
#endif /* !defined (USART2_TX_BUFFER_LENGTH) */
#define USART2_RX_BUFFER_MASK (USART2_RX_BUFFER_LENGTH - 1)
#define USART2_TX_BUFFER_MASK (USART2_TX_BUFFER_LENGTH - 1)
#endif /* defined (USE_USART2_INTERRUPT) */
#if defined (USE_USART3_INTERRUPT)
#if !defined (USART3_RX_BUFFER_LENGTH)
/*! \brief USART3 receive buffer length used in interrupt mode
 * \warning maximum defined length 256
 * \ingroup macro_grp
 */
#define USART3_RX_BUFFER_LENGTH 16
#endif /* !defined (USART3_RX_BUFFER_LENGTH) */
#if !defined (USART3_TX_BUFFER_LENGTH)
/*! \brief USART3 transmitter buffer length used in interrupt mode
 * \warning maximum defined length 256
 * \ingroup macro_grp
 */
#define USART3_TX_BUFFER_LENGTH 16
#endif /* !defined (USART3_TX_BUFFER_LENGTH) */
#define USART3_RX_BUFFER_MASK (USART3_RX_BUFFER_LENGTH - 1)
#define USART3_TX_BUFFER_MASK (USART3_TX_BUFFER_LENGTH - 1)
#endif /* defined (USE_USART3_INTERRUPT) */

/*! \brief Calculate absolute value for given signed long long. Used by ERROR_CALC(x)
 * \ingroup macro_grp
 */
#define ABS_VAL(x) (((x) < 0LL) ? (-(x)) : (x))
/*! \brief Calculate UBRR register value in normal mode. Used by BAUD_CALC(x)
 * \ingroup macro_grp
 */
#define UBRR_CALC(x) (((F_CPU) + 8UL * (x)) / (16UL * (x)) - 1UL)
/*! \brief Calculate UBRR register value in double mode. Used by BAUD_CALC(x)
 * \ingroup macro_grp
 */
#define DOUBLE_UBRR_CALC(x) (((F_CPU) + 4UL * (x)) / (8UL * (x)) - 1UL)
/*! \brief Calculate baud rate for given UBRR value in normal mode. Used by BAUD_CALC(x)
 * \ingroup macro_grp
 */
#define CM_BAUD(x) ((F_CPU) / (16UL * ((x) + 1UL)))
/*! \brief Calculate baud rate for given UBRR value in double mode. Used by BAUD_CALC(x)
 * \ingroup macro_grp
 */
#define DOUBLE_CM_BAUD(x) ((F_CPU) / (8UL * ((x) + 1UL)))
/*! \brief Calculate baud rate error multiplied by 1000 for given close match baud rate \a x and desired \a y baud rate. Used by BAUD_CALC(x)
 * \ingroup macro_grp
 */
#define ERROR_CALC(x,y) (ABS_VAL(((x) * 1000LL) / (y) - 1000LL))

/*! \brief Calculate UBRR register value for passed baud rate \a x.
 *
 * If baud error in normal mode will be greater then baud error in double mode then macro
 * returns UBRR value for double mode. Because maximum UBRR value must be lower then 4096 (1 << 12),
 * macro sets 15th bit in returned value to indicate double mode.
 * \warning This macro does not check for UBRR overflow!!! It doesn't test if baud rate error isn't
 * too big!!! You should read datasheet for Your MCU to find out best baud rate for used F_CPU.
 * \ingroup macro_grp
 */
#define BAUD_CALC(x) ((ERROR_CALC(CM_BAUD(UBRR_CALC(x)),(x)) <=\
		ERROR_CALC(DOUBLE_CM_BAUD(DOUBLE_UBRR_CALC(x)),(x))) ?\
		UBRR_CALC(x) :\
		(DOUBLE_UBRR_CALC(x) | 0x8000))

/*! \brief USART transmitter status
 * \ingroup typedefs_grp
 */
typedef enum __txStatus{
	STOPPED = 0, /*!< library sets this when transmitter interrupt not working */
	STARTED = 1, /*!< library sets this when transmitter interrupt working */
} _txStatus_T;

/*! \brief USART's names for use with library functions.
 * \ingroup typedefs_grp
 */
typedef enum __usartNumber{
	USART0 = 0, /*!< for USART0 */
	USART1 = 1, /*!< for USART1 */
	USART2 = 2, /*!< for USART2 */
	USART3 = 3, /*!< for USART3 */
} usartNumber_T;

/*! \brief Function pointer for library callbacks
 * \ingroup typedefs_grp
 */
typedef void (*_usartFctPtr_T)(usartNumber_T const);

/*! \brief FIFO buffer type. Used only in interrupt based USART.
 *
 * Maximum buffer capacity: 256 bytes.
 * \ingroup typedefs_grp
 */
typedef struct {
	volatile uint8_t tail; /*!< first byte in buffer */
	volatile uint8_t head; /*!< last byte in buffer */
	volatile uint8_t *data; /*!< pointer to buffer */
} fifo_T;

/*! \brief Transmitter structure. Used only in interrupt based USART.
 * \ingroup typedefs_grp
 */
typedef struct {
	volatile fifo_T *buffer; /*!< pointer to buffer (fifo_T) */
	volatile _txStatus_T status; /*!< interrupt based transmitter status (_txStarted_T)*/
} usartTxBuffer_T;

#if defined (USE_USART0_INTERRUPT) || defined (USE_USART1_INTERRUPT)\
	|| defined (USE_USART2_INTERRUPT) || defined (USE_USART3_INTERRUPT)
/*! \brief Get byte from receive buffer.
 * \return When buffer empty returns -1, otherwise returns data byte.
 * \param usartNumber USART number
 * \ingroup interrupt_rx_grp
*/
int16_t usartGetByteFromReceiveBuffer(usartNumber_T const usartNumber);
/*! \brief Put byte to transmit buffer.
 * \return When buffer full it doesn't put any data in and returns -1,
 * otherwise returns 0.
 * \param usartNumber USART number
 * \param data Byte to put in buffer
 * \ingroup interrupt_tx_grp
 */
int8_t usartPutByteToTransmitBuffer(usartNumber_T const usartNumber, uint8_t const data);
/*! \brief USART initialization.
 *
 * Always must be run for used USART. On the fly baud rate change supported.
 * Simply use this function another time for desired USART. You should wait for
 * all transmissions end before baud change.
 * \param usartNumber USART number (usartNumber_T)
 * \param ubrrValue Value calculated with BAUD_CALC(x) macro
 * \ingroup universal_fct_grp
 */
void usartInit(usartNumber_T const usartNumber, uint16_t const ubrrValue);
/*! \brief Register callback function called when new data in buffer.
 *
 * Callback function must be void type, and get as argument USART number (usartNumber_T).
 * Registering this function is not required.
 * \param callback Pointer to void function. Function must accept USART number as parameter (usartNumber_T)
 * \ingroup interrupt_rx_grp
 */
void registerRxDataReadyCallback(_usartFctPtr_T callback);
/*! \brief Register callback function called when receive buffer full.
 *
 * Callback function must be void type, and get as argument USART number (usartNumber_T).
 * Registering this function is not required.
 * \param callback Pointer to void function. Function must accept USART number as parameter (usartNumber_T)
 * \ingroup interrupt_rx_grp
 */
void registerRxBufferFullCallback(_usartFctPtr_T callback);
/*! \brief Start interrupt based receiver.
 * \param usartNumber USART number (usartNumber_T)
 * \ingroup interrupt_rx_grp
 */
void usartRxStart(usartNumber_T const usartNumber);
#endif /* defined (USE_USART0_INTERRUPT) || defined (USE_USART1_INTERRUPT) || defined (USE_USART2_INTERRUPT) || defined (USE_USART3_INTERRUPT) */
/*! \brief Get receive complete flag.
 * \return Returns non zero value if flag set, else returns 0
 * \param usartNumber USART number (usartNumber_T)
 * \ingroup normal_rx_grp
 */
uint8_t usartDataReceived(usartNumber_T const usartNumber);
/*! \brief Immediate return contents of USART data register.
 * \return USART data register contents
 * \param usartNumber USART number (usartNumber_T)
 * \ingroup normal_rx_grp
 */
uint8_t usartImGetByte(usartNumber_T const usartNumber);
/*! \brief Wait for receive complete flag, then return contents of USART data register.
 * \return USART data register contents
 * \param usartNumber USART number (usartNumber_T)
 * \ingroup normal_rx_grp
 */
uint8_t usartGetByte(usartNumber_T const usartNumber);
#if defined (USE_USART0_INTERRUPT) || defined (USE_USART1_INTERRUPT)\
	|| defined (USE_USART2_INTERRUPT) || defined (USE_USART3_INTERRUPT)
/*! \brief Register callback function called when transmission from buffer ends.
 *
 * Callback function must be void type, and get as argument USART number (usartNumber_T).
 * Registering this function is not required.
 * \param callback Pointer to void function. Function must accept USART number as parameter (usartNumber_T)
 * \ingroup interrupt_tx_grp
 */
void registerTxCompleteCallback(_usartFctPtr_T callback);
/*! \brief Start interrupt based transmitter.
 * \param usartNumber USART number (usartNumber_T)
 * \ingroup interrupt_tx_grp
 */
void usartTxStart(usartNumber_T const usartNumber);
#endif /* defined (USE_USART0_INTERRUPT) || defined (USE_USART1_INTERRUPT) || defined (USE_USART2_INTERRUPT) || defined (USE_USART3_INTERRUPT) */
/*! \brief Get transmit complete flag.
 * \return Returns non zero value if flag set, else returns 0
 * \param usartNumber USART number (usartNumber_T)
 * \ingroup normal_tx_grp
 */
uint8_t usartDataTransferred(usartNumber_T const usartNumber);
/*! \brief Immediate put byte to USART data register.
 * \param usartNumber USART number (usartNumber_T)
 * \param data Byte to put (uint8_t)
 * \ingroup normal_tx_grp
 */
void usartImPutByte(usartNumber_T const usartNumber, uint8_t const data);
/*! \brief Wait for transmit complete flag, then put byte to USART data register.
 * \param usartNumber USART number (usartNumber_T)
 * \param data Byte to put (uint8_t)
 * \ingroup normal_tx_grp
 */
void usartPutByte(usartNumber_T const usartNumber, uint8_t const data);
#endif /* USART_LIB_H_ */