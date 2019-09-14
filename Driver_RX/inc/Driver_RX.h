/*
 * RTOS2_TP1.h
 *
 *  Created on: Sep 13, 2019
 *      Author: gzocco
 */

#ifndef PROGRAMS_RTOS2_RTOS2_TP1_INC_RTOS2_TP1_C_
#define PROGRAMS_RTOS2_RTOS2_TP1_INC_RTOS2_TP1_C_
#include "sapi.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"
#include "stdlib.h"
#include <string.h>

void Procesa_RX_Task( void* taskParmPtr );

typedef struct {
	uartMap_t uart;
	uint32_t baudRate;
	uint32_t delay;
} taskData_t;

#endif /* PROGRAMS_RTOS2_RTOS2_TP1_INC_RTOS2_TP1_C_ */
