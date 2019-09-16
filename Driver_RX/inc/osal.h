/*
 * osal.h
 *
 *  Created on: 15 sep. 2019
 *      Author: miguel
 */

#ifndef RTOS2_TP1_RX_INTERRUPT_WITH_FREERTOS_INC_OSAL_H_
#define RTOS2_TP1_RX_INTERRUPT_WITH_FREERTOS_INC_OSAL_H_

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"


#define semaphore_t		SemaphoreHandle_t
#define semaphoreTake( xSemaphore, xBlockTime )		xSemaphoreTake( xSemaphore, xBlockTime )
#define semaphoreGive( xSemaphore )					xSemaphoreGive( xSemaphore )

#endif /* RTOS2_TP1_RX_INTERRUPT_WITH_FREERTOS_INC_OSAL_H_ */
