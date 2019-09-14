/*
 * Procesa_RX_Task.h
 *
 *  Created on: Sep 13, 2019
 *      Author: gzocco
 */

#ifndef PROGRAMS_RTOS2_RTOS2_TP1_INC_PROCESA_RX_TASK_H_
#define PROGRAMS_RTOS2_RTOS2_TP1_INC_PROCESA_RX_TASK_H_
#include "sapi.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "onRx.h"

#define SIZE_COLA_RX 10
#define MAX_FRAME_SIZE 5

typedef struct {
	uartMap_t uart;
	uint32_t baudRate;
	uint32_t delay;
} taskData_t;

typedef enum{
   ESPERA_PRIMER_BYTE,
   ESPERA_PROX_BYTE,
   TIMEOUT_ESPERA_BYTE,
   EXCEDE_MAX_FRAME_SIZE
} fsmFrameRX_state_t;

void Procesa_RX_Task( void* taskParmPtr );
//extern void onRx( void *noUsado );

void fsmFrameRX_Init( void );
void fsmFrameRX_Update( void );
void fsmFrameRX_Error( void );

fsmFrameRX_state_t fsmFrameRX_state;

QueueHandle_t xQueue_Procesa_RX;

#endif /* PROGRAMS_RTOS2_RTOS2_TP1_INC_PROCESA_RX_TASK_H_ */
