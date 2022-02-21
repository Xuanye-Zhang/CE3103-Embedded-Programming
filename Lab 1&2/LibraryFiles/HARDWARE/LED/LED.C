#include "led.h"	

int Led_Count = 2000;//LED blink Delay 

//LED initialization
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); //Enable APB Clock
	
	GPIO_InitStructure.GPIO_Pin = LED_PIN;				//LED Pin
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//Push pull output
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
	GPIO_Init(LED_PORT, &GPIO_InitStructure);			//Initialize LED GPIO
	GPIO_SetBits(LED_PORT,LED_PIN);
}

void led_task(void *pvParameters)
{
    while(1)
    {
      LED=~LED;        //0 on, 1 off   
      //delay_ms(5000);			
      vTaskDelay(Led_Count); //Delay 
    }
} 

void led_task1(void *pvParameters)
{
    LED = ~LED;
} 

void led_task2(void *pvParameters)
{
    while(1)
    {
			BUZZER = 0;
      LED=~LED;        //0 on, 1 off   
      delay_ms(500);			
      //vTaskDelay(500); //Delay 
    }
} 

