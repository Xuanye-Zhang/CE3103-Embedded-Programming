#ifndef __SYSTEM_H
#define __SYSTEM_H


#include "FreeRTOSConfig.h"

#include "FreeRTOS.h"
#include "stm32f10x.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

#include "sys.h"
#include "delay.h"


#include "led.h"
#include "oled.h"
#include "BUZZER.h"
#include "show.h"
#include "userbutton.h"
#include "UART.h"

void systemInit(void);

#define RATE_1_HZ		  1
#define RATE_5_HZ		  5
#define RATE_10_HZ		10
#define RATE_20_HZ		20
#define RATE_25_HZ		25
#define RATE_50_HZ		50
#define RATE_100_HZ		100
#define RATE_200_HZ 	200
#define RATE_250_HZ 	250
#define RATE_500_HZ 	500
#define RATE_1000_HZ 	1000


#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stdarg.h"
#endif /* __SYSTEM_H */
