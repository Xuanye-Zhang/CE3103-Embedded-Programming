#ifndef __BUZZER_H
#define __BUZZER_H

#include "sys.h"
#include "system.h"

// Buzzer GPIO Definition
#define BUZZER_TASK_PRIO		3     
#define BUZZER_STK_SIZE 		32   


#define BUZZER_PORT GPIOB
#define BUZZER_PIN GPIO_Pin_10
#define BUZZER PBout(10) 

void Buzzer_Init(void);  
void buzzer_task(void *pvParameters);
extern int Buzzer_Count;
#endif