#ifndef __USERBUTTON_H
#define __USERBUTTON_H
#include "sys.h"
#include "system.h"

//LED Port definition
#define USERB_TASK_PRIO		3     
#define USERB_STK_SIZE 		128   


#define USERB_PORT GPIOD
#define USERB_PIN GPIO_Pin_8
#define USERB PDin(10) 
/*----------------------------------*/


void userB_Init(void);
void userB_task (void *pvParameters);


#endif
