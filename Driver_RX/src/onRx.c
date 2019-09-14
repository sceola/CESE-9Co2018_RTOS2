/*
 * onRx.c
 *
 *  Created on: Aug 15, 2019
 *      Author: gzocco
 *
 *
 *      ISR de recepcion de datos a traves de UART.
 *      Envio los bytes recibidos a la cola de FreeRTOS .
 *
 */
#include "sapi.h"
#include "FreeRTOS.h"
#include "onRx.h"

//DEBUG_PRINT_ENABLE;

void onRx( void *ParmPtr )
{
	//NO ANDA!!!
	ISR_RX_Data_t *uart_p = (ISR_RX_Data_t *) ParmPtr;	// NO ANDA.

	uint8_t RX_byte=0;
	BaseType_t xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	RX_byte = uartRxRead(UART_USB); //UART_USB uart_p->uart
	if( xQueueSendFromISR( xQueue_Procesa_RX, &RX_byte, &xHigherPriorityTaskWoken ) != pdPASS ) {
		// No se puede escribir en la Cola... Llena?
		uartWriteString (UART_USB, "DEBUG: onRX: xQueue_Procesa_RX: Falla envio RX_byte.\r\n");
	}
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
