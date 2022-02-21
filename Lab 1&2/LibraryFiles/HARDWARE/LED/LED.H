#ifndef __LED_H
#define __LED_H
#include "sys.h"
#include "system.h"

//LED Port definition
#define LED_TASK_PRIO		3     
#define LED_STK_SIZE 		128   


#define LED_PORT GPIOE
#define LED_PIN GPIO_Pin_10
#define LED PEout(10) 
/*----------------------------------*/

void LED_Init(void);  
void led_task(void *pvParameters);
void led_task1(void *pvParameters);
void led_task2(void *pvParameters);
extern int Led_Count;
#endif
