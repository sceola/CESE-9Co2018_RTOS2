/*
 * onRx.h
 *
 *  Created on: Aug 15, 2019
 *      Author: gzocco
 */

#ifndef PROGRAMS_RTOS1_TP_RTOS1_PCSE_CONTROL_UGV_INC_ONRX_H_
#define PROGRAMS_RTOS1_TP_RTOS1_PCSE_CONTROL_UGV_INC_ONRX_H_
#include "sapi.h"
#include "FreeRTOS.h"
#include "queue.h"
void onRx( void *ParmPtr );
extern QueueHandle_t xQueue_Procesa_RX;
typedef struct {
	uartMap_t uart;
} ISR_RX_Data_t;
#endif /* PROGRAMS_RTOS1_TP_RTOS1_PCSE_CONTROL_UGV_INC_ONRX_H_ */
