/* este codigo NO esta en el libro de Sistemas Empotrados en tiempo real
 * pero el objetivo es intriducir a FreeRTOS usando solo una  tarea que 
 * imprime por el puerto serie, e invocando al planificador
 *
 *  - xTaskCreate()
 *  - vTaskStartScheduler()
 *
 * esto hará un busy waiting ... :-(
 *
 *  */
 /*==================[inclusions]=============================================*/

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/*==================[macros and definitions]=================================*/

#define PRIO_TAREA1 1
#define PRIO_TAREA2 1
#define TAM_PILA 150
#define mainDELAY_LOOP_COUNT        ( 0xffffff )

xSemaphoreHandle Sem;

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void vTarea1(void *pvParameters)
{
	extern xSemaphoreHandle Sem;
	//portTickType xLastWakeTime;
	//portTickType xPeriod=10/configTICK_RATE_HZ;
	const char *pcTaskName = "Tarea 1 is running\r\n";
  	uint32_t ul;
   	//volatile uint32_t ul;
   	/* As per most tasks, this task is implemented in an infinite loop. */
	//xLastWakeTime=xTaskGetTickCount();
	const TickType_t xDelay1s=pdMS_TO_TICKS(1000UL);
   	for( ;; ) {
	if (xSemaphoreTake(Sem,portMAX_DELAY)==pdTRUE){
      	/* Print out the name of this task. */
	//usleep(1000);
	printf(pcTaskName);
	//Board_LED_Toggle(4);
	vTaskDelay (xDelay1s);
	}
	xSemaphoreGive(Sem);
      	/* Delay for a period. */
     	for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ ) {}
   	}
}

static void vTarea2(void *pvParameters)
{
	extern xSemaphoreHandle Sem;

	//portTickType xLastWakeTime;
	//portTickType xPeriod=10/configTICK_RATE_HZ;
   	const char *pcTaskName = "Tarea 2 is running\r\n";
    	uint32_t ul;
   	/* As per most tasks, this task is implemented in an infinite loop. */
	//xLastWakeTime=xTaskGetTickCount();
	//const TickType_t xDelay1s=pdMS_TO_TICKS(1000UL);
   	for(;;) {
	if(xSemaphoreTake(Sem, portMAX_DELAY)==pdTRUE){
      	/* Print out the name of this task. */
	printf(pcTaskName);
	Board_LED_Toggle(5);
	 }xSemaphoreGive(Sem);
	//vTaskDelay (xDelay1s);
	/* Delay for a period. */
     	for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ ) {}
   	}
}
/*==================[external functions definition]==========================*/

int main(void)
{
	vSemaphoreCreateBinary(Sem);
    	//Se inicializa HW
	/* Se crean las tareas */
	xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, NULL, PRIO_TAREA1, NULL );
	xTaskCreate(vTarea2, (const char *)"Tarea2", TAM_PILA, NULL, PRIO_TAREA2, NULL );
	vTaskStartScheduler(); /* y por último se arranca el planificador . */
    //Nunca llegara a ese lazo  .... espero
    //for( ;; );
     return 0;
}

/*==================[end of file]============================================*/
