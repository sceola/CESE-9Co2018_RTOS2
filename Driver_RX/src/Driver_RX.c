/* RTOS2 - TP1
 * GRUPO N
 * Integrantes:
 *
 *
 */

/*==================[inlcusiones]============================================*/
#include "../inc/Driver_RX.h"


/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

DEBUG_PRINT_ENABLE;

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

// Prototipo de funcion de la tarea

//void tareaA_LED( void* taskParmPtr );
//void tareaC_ENVIA( void* taskParmPtr );

/*==================[funcion principal]======================================*/
taskData_t Procesa_RX_Data;
// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main(void)
{
   // ---------- CONFIGURACIONES ------------------------------

	boardInit();
	Procesa_RX_Data.delay=100;
	Procesa_RX_Data.uart=UART_USB;
	Procesa_RX_Data.baudRate=115200;
	xTaskCreate(
			Procesa_RX_Task,                     // Funcion de la tarea a ejecutar
			(const char *)"Procesa_RX_Task",     // Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE*4, // Cantidad de stack de la tarea
			&Procesa_RX_Data,                          // Parametros de tarea
			tskIDLE_PRIORITY+1,         // Prioridad de la tarea
			0                           // Puntero a la tarea creada en el sistema
	);



   /*
   xTaskCreate(
		   tareaC_ENVIA,                     // Funcion de la tarea a ejecutar
		   (const char *)"tareaC_ENVIA",     // Nombre de la tarea como String amigable para el usuario
		   configMINIMAL_STACK_SIZE*2, // Cantidad de stack de la tarea
		   0,                          // Parametros de tarea
		   tskIDLE_PRIORITY+1,         // Prioridad de la tarea
		   0                           // Puntero a la tarea creada en el sistema
   );
   xTaskCreate(
		   tareaA_LED,                     // Funcion de la tarea a ejecutar
		   (const char *)"tareaA_LED",     // Nombre de la tarea como String amigable para el usuario
		   configMINIMAL_STACK_SIZE*2, // Cantidad de stack de la tarea
		   0,                          // Parametros de tarea
		   tskIDLE_PRIORITY+1,         // Prioridad de la tarea
		   0                           // Puntero a la tarea creada en el sistema
   );
   */

   // Iniciar scheduler
   vTaskStartScheduler();

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {
      // Si cae en este while 1 significa que no pudo iniciar el scheduler
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

/*==================[definiciones de funciones internas]=====================*/
/*
uint32_t counter = 0;

void vApplicationTickHook( void )
{
	counter++;
}
*/
/*==================[definiciones de funciones externas]=====================*/

// Implementacion de funcion de la tarea
/*void tareaB_TECLA( void* taskParmPtr )
{
   fsmButtonInit();

   // Tarea periodica cada 1 ms
   portTickType xPeriodicity =  800 / portTICK_RATE_MS;
   portTickType xLastWakeTime = xTaskGetTickCount();
   
   // ---------- REPETIR POR SIEMPRE --------------------------
   while(TRUE)
   {
	   fsmButtonUpdate(TEC1);
	   vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
   }
}

void tareaA_LED( void* taskParmPtr )
{
	portTickType xLastWakeTime = xTaskGetTickCount();
	uint8_t a=0;
	void * datosProcesar_p=NULL;
	uint8_t dataType=0;

	// ---------- REPETIR POR SIEMPRE --------------------------
	while(TRUE) {
		gpioToggle( LED1 );
		char mensaje[]="LED ON";
		*datosProcesar_p=mensaje;

		//*datosEnviar_p=&(char)mensaje;
		//enviaDatos(&datosEnviar_p);
		enviaDatos(&datosProcesar_p,dataType);
		enviaDatos8(a);
		a++;
		vTaskDelayUntil( &xLastWakeTime, 500 / portTICK_RATE_MS );
	}
}

void tareaC_ENVIA( void* taskParmPtr )
{
	portTickType xLastWakeTime = xTaskGetTickCount();
	while(TRUE) {
		uartWriteByte(UART_USB,recibeDatos());
		vTaskDelayUntil( &xLastWakeTime, 500 / portTICK_RATE_MS );
	}
}



*/

/*==================[fin del archivo]========================================*/
