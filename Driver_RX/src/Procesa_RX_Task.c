/*
 * Procesa_RX_Task.c
 *
 *  Created on: Sep 13, 2019
 *      Author: gzocco
 */
#include "Procesa_RX_Task.h"
DEBUG_PRINT_ENABLE;

void Procesa_RX_Task( void* pvParameters )
{
	taskData_t* taskData =  (taskData_t*) pvParameters;

	ISR_RX_Data_t ISR_RX_Data;
	ISR_RX_Data.uart=UART_USB;

	debugPrintConfigUart( UART_USB, taskData->baudRate );	// UART for debug messages
	debugPrintlnString( "DEBUG: Inicia Procesa_RX_Task.\n\r" );

	// Creo cola para recibir desde IRQ UART de a 1 byte.
	xQueue_Procesa_RX = xQueueCreate( SIZE_COLA_RX, sizeof( uint8_t ) );
	if( xQueue_Procesa_RX != NULL ) {
		debugPrintlnString( "DEBUG: Procesa_RX_Task: Crear xQueue_Procesa_RX OK \n\r" );
	}else {
		debugPrintlnString( "DEBUG: Procesa_RX_Task: Crear xQueue_Procesa_RX NOK \n\r" );
	}

	// Inicializa UART, interrupcion de RX y IRQ generales de UART.
	uartConfig( taskData->uart, taskData->baudRate);
	uartCallbackSet(taskData->uart, UART_RECEIVE, onRx, &ISR_RX_Data);	//NULL // Seteo un callback al evento de recepcion y habilito su interrupcion
	uartInterrupt(taskData->uart, true);	// Habilito todas las interrupciones de UART_USB

	uint8_t RX_byte;
	char RX_Frame[MAX_FRAME_SIZE]="Test";
	char *RX_Frame_p=RX_Frame;
	portTickType xLastWakeTime = xTaskGetTickCount();
	const TickType_t xTicksToWait = pdMS_TO_TICKS( 0UL );	// Son 100ms=100UL.
	fsmFrameRX_Init( RX_Frame_p );
	while(TRUE) {
		gpioToggle(LED1);
		if( uxQueueMessagesWaiting( xQueue_Procesa_RX ) != 0 ) {
			if( xQueueReceive( xQueue_Procesa_RX, &RX_byte, xTicksToWait) == pdPASS ) {
				RX_byte++;		// Para DEBUG.
				debugPrintChar(RX_byte);
				debugPrintEnter();

				fsmFrameRX_Update( RX_Frame_p );
			}
		}
		vTaskDelayUntil( &xLastWakeTime, taskData->delay / portTICK_RATE_MS );
	}
}

void RX_Init (taskData_t* taskData)
{
	//
	// Inicializa UART, interrupcion de RX y IRQ generales de UART.
	uartConfig( taskData->uart, taskData->baudRate);
	uartCallbackSet(taskData->uart, UART_RECEIVE, onRx, &ISR_RX_Data);	//NULL // Seteo un callback al evento de recepcion y habilito su interrupcion
	uartInterrupt(taskData->uart, true);	// Habilito todas las interrupciones de UART_USB

	// Timer RX
	// Memoria

}

void fsmFrameRX_Init( char *RX_Frame_p )
{
	Inicializar_RX_Frame(&RX_Frame_p, MAX_FRAME_SIZE);
	fsmFrameRX_state=ESPERA_PRIMER_BYTE;
}

void fsmFrameRX_Error( char *RX_Frame_p )
{
	Inicializar_RX_Frame(&RX_Frame_p, MAX_FRAME_SIZE);
	fsmFrameRX_state=ESPERA_PRIMER_BYTE;
}

void Inicializar_RX_Frame(char *vector, uint32_t longitud)
	{
		uint32_t i = 0;

		for (; i < longitud; i++ )
		{
			vector[i] ="";
		}
	}

void fsmFrameRX_Update( char *RX_Frame_p )
{
	static bool_t flagFalling = FALSE;
	static bool_t flagRising = FALSE;

	static uint8_t contFalling = 0;
	static uint8_t contRising = 0;
	//char ver="a";
	uartWriteString(UART_USB, RX_Frame_p);

	switch( fsmFrameRX_state )
	{
	case ESPERA_PRIMER_BYTE:
		// Verifico si me llego algo por UART.
		//if(  ){



		/*
		 * ME falta crear una structura par pasarle el puntero a esto,
		 * donde tenga el contador de bytes RX.
		 *
		 * El timer, al llegar a timeout, tiene que disparar el inicio el proceso de CRC y pasar
		 * los datos a otro lado... para poder seguir recibiendo datos.....
		 *
		 */

		//char *RX_Frame_p
		fsmFrameRX_state = ESPERA_PROX_BYTE;
			//xTimerReset(xOneShotTimerRX,0);		// Reseteo Timer de RX. Comienza cuenta.
		//Incremento cont de bytes rx.
		//}
		break;

	case ESPERA_PROX_BYTE:

		//if( gpioRead(tecla) ){
		// Incremento cont de bytes rx.
		//xTimerReset(xOneShotTimerRX,0);		// Reseteo Timer de RX. Comienza cuenta.
		//}
		break;

	case TIMEOUT_ESPERA_BYTE:

		if( flagFalling == FALSE ){
			flagFalling = TRUE;

		}
		/* CHECK TRANSITION CONDITIONS */
		if( contFalling >= 40 ){
			if( !gpioRead(TEC1) ){

				//  buttonPressed();
				//t_ini=counter;
			} else{
				//fsmButtonState = STATE_BUTTON_UP;
			}
			contFalling = 0;
		}
		contFalling++;
		/* LEAVE */
		//if( fsmButtonState != STATE_BUTTON_FALLING ){
			//flagFalling = FALSE;
		//}
		break;

	case EXCEDE_MAX_FRAME_SIZE:
		/* ENTRY */
		if( flagRising == FALSE ){
			flagRising = TRUE;
		}
		/* CHECK TRANSITION CONDITIONS */

		if( contRising >= 40 ){
			if( gpioRead(TEC1) ){
				//fsmButtonState = STATE_BUTTON_UP;
				//  buttonReleased();
			//	t_fin=counter;

			//	t_pulsacion = t_fin - t_ini;

			} else{
				//fsmButtonState = STATE_BUTTON_DOWN;
			}
			contRising = 0;
		}
		contRising++;

		/* LEAVE */
		if( fsmFrameRX_state == ESPERA_PROX_BYTE ){
			flagRising = FALSE;
		}
		break;

	default:
		fsmFrameRX_Error(RX_Frame_p);
		break;
	}
}

