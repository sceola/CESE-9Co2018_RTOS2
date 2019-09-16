/*
 * driver_usart.h
 *
 *  Created on: 15 sep. 2019
 *      Author: miguel
 */

#ifndef RTOS2_TP1_RX_INTERRUPT_WITH_FREERTOS_INC_DRIVER_USART_H_
#define RTOS2_TP1_RX_INTERRUPT_WITH_FREERTOS_INC_DRIVER_USART_H_

#include "sapi.h"
#include "osal.h"

#define MAX_PACKET_SIZE		255
#define MAX_USART_NUMBER	4			/*	number of USART ports */

typedef enum {B1200, B4800, B9600, B19200, B38400, B57600, B115200}baudRate_t;
typedef enum {USART0, USART1, USART2, USART3}portNumber_t;
typedef enum {DATA_BITS_8,DATA_BITS_7}dataBits_t;
typedef enum {STOP_BITS_1, STOP_BITS_2}stopBits_t;
typedef enum {PARITY_NONE, PARITY_EVEN, PARITY_ODD}parity_t;

typedef void (*onPacketReady)(void);	/*	callback function to warn that there is a package ready */

/*
 *	structure for data transfer
*/
typedef struct{
	uint8_t 	*buffer;
	uint32_t	bufferLength;
}tranfer_t;

/*
 * structure used to maintain the port configuration
*/
typedef struct{
	portNumber_t	usartPortNumber;
	baudRate_t		usartBaudRate;
	dataBits_t		usartDataBits;
	parity_t		usartParity;
	stopBits_t		usartStopBits;
}usartPort_t;

/*
 * structure of the USART driver
*/
typedef struct{
	tranfer_t		rxTranfer;
	tranfer_t   	txTranfer;
	usartPort_t		port;
	onPacketReady	callbackFunc;
	semaphore_t		semaphore;
}driverUsart_t;

uint32_t usartInit(driverUsart_t const *obj,
					portNumber_t portNumber,
					baudRate_t baudRate,
					dataBits_t dataBits,
					stopBits_t stopBits,
					parity_t parity);
/**
 * usartReadPacket:
 * 			Get a package if it's ready.
 * 	Parameters
 * 		 *packet	data pointer and package size to receive
 * 		 *obj		driver instance
 * */
uint32_t usartReadPacket(driverUsart_t const *obj, tranfer_t *packet);

/**
 * usartWritePacket:
 * 			Send a package.
 * 	Parameters
 * 		 *packet	data pointer and package size to send
 * 		 *obj		driver instance
 * */
uint32_t usartWritePacket(driverUsart_t const *obj, tranfer_t packet);

/**
 * usartReleasePacket:
 * 			Informs the driver that he can release a package.
 * 	Parameters
 * 		 *packet	data pointer and package size to release
 * 		 *obj		driver instance
 * */
uint32_t usartReleasePacket(driverUsart_t const *obj,tranfer_t packet);

/**
 * setUsartCallbackForPacketReady:
 * 			Configure a callback for the driver to report that a valid package arrived.
 * 	Parameters
 * 		 *callbackFunc	pointer to function.
 * 		 *obj			driver instance
 * */
void setUsartCallbackForPacketReady(driverUsart_t const *obj,onPacketReady *callbackFunc);

/**
 * getPacketReadyStatus:
 * 			Check with the driver if a package is ready.
 * 	Parameters
 * 		 *obj			driver instance
 * */
uint32_t getPacketReadyStatus(driverUsart_t const *obj);

#endif /* RTOS2_TP1_RX_INTERRUPT_WITH_FREERTOS_INC_DRIVER_USART_H_ */
