#include "system.h"

#define START_TASK_PRIO		4
#define START_STK_SIZE    256
TaskHandle_t StartTask_Handler;
TimerHandle_t xAutoTimer ;
void start_task(void *pvParameters);
void lab2_task1(void *pvParameters);
void lab2_task2(void *pvParameters);
void lab2_task3(void *pvParameters);
void lab2_task4(void *pvParameters);
void lab2_task5(void *pvParameters);
TimerHandle_t uartTimer;

int main(void)
{
	systemInit();
	BUZZER = 0;
	
//	xTaskCreate((TaskFunction_t ) start_task,
//							(const char*		) "start_task",
//								(uint16_t			) START_STK_SIZE,
//							(void*					) NULL,
//							(UBaseType_t		) START_TASK_PRIO,
//							(TaskHandle_t*	) &StartTask_Handler);
							
//	xTaskCreate((TaskFunction_t ) lab2_task1,
//							(const char*		) "play_song_task",
//								(uint16_t			) START_STK_SIZE,
//							(void*					) NULL,
//							(UBaseType_t		) START_TASK_PRIO,
//							(TaskHandle_t*	) &StartTask_Handler);
	
//			xTaskCreate((TaskFunction_t ) lab2_task2,
//							(const char*		) "led_blink_With_timer_task",
//								(uint16_t			) START_STK_SIZE,
//							(void*					) NULL,
//							(UBaseType_t		) START_TASK_PRIO,
//							(TaskHandle_t*	) &StartTask_Handler);
	
//		xTaskCreate((TaskFunction_t ) lab2_task3,
//							(const char*		) "uart_task",
//								(uint16_t			) START_STK_SIZE,
//							(void*					) NULL,
//							(UBaseType_t		) START_TASK_PRIO,
//							(TaskHandle_t*	) &StartTask_Handler);

			// lab2 task 4 non-Preemptive

			// lab2 task 5 compare prio
			// same prio
//			xTaskCreate(userB_task, "show_task", USERB_STK_SIZE, NULL, 3, NULL);
//			xTaskCreate(lab2_task2, "led_blink_With_timer_task", USERB_STK_SIZE, NULL, 3, NULL);			
//			xTaskCreate(lab2_task3, "compare_prio_task", USERB_STK_SIZE, NULL, 3, NULL);
			
			// lower/higher prio
			//xTaskCreate(userB_task, "playsong_task", USERB_STK_SIZE, NULL, 4, NULL);
			xTaskCreate(lab2_task2, "led_blink_With_timer_task", USERB_STK_SIZE, NULL, 3, NULL);			
			//xTaskCreate(lab2_task3, "compare_prio_task", USERB_STK_SIZE, NULL, 3, NULL);

							
	vTaskStartScheduler();
							

}

// Lab1
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();
	//xTaskCreate(led_task1, "led_task", LED_STK_SIZE, NULL, LED_TASK_PRIO, NULL);
	xTaskCreate(led_task2, "led_task", LED_STK_SIZE, NULL, LED_TASK_PRIO, NULL);
	//xTaskCreate(buzzer_task, "buzzer_task", BUZZER_STK_SIZE, NULL, BUZZER_TASK_PRIO, NULL);
	xTaskCreate(show_task, "show_task", SHOW_STK_SIZE, NULL, SHOW_TASK_PRIO, NULL);
	vTaskDelete(StartTask_Handler);
	
	taskEXIT_CRITICAL();
}

// Lab2

// User button to play the song
void lab2_task1(void *pvParameters)
{
	taskENTER_CRITICAL();
	xTaskCreate(userB_task, "show_task", USERB_STK_SIZE, NULL, USERB_TASK_PRIO, NULL);
	vTaskDelete(StartTask_Handler);
	
	taskEXIT_CRITICAL();
}

// Timer let led blink
void lab2_task2(void *pvParameters)
{
	taskENTER_CRITICAL();
	
	xAutoTimer = xTimerCreate("timer1sec", pdMS_TO_TICKS(1000) , pdTRUE, 0, led_task1);
	if (xTimerStart(xAutoTimer, 0) == pdPASS)
		
	vTaskDelete(StartTask_Handler);

	taskEXIT_CRITICAL();
}

// uart_transfer

void lab2_task3(void *pvParameters)
{
	taskENTER_CRITICAL();
	// Lab2 task 3	
	uart_init(115200);
	
	
	uartTimer = xTimerCreate(
		"SendUART1Sec", 			// name
		pdMS_TO_TICKS(1000),	// period
		pdTRUE,								// auto reload
		(void*) 0,						// timer ID
		uart_task							// callback
	);
	xTimerStart(uartTimer, pdMS_TO_TICKS(0));
	vTaskDelete(StartTask_Handler);
		
	taskEXIT_CRITICAL();
}



