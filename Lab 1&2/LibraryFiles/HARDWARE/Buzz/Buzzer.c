#include "BUZZER.h"	
#include "system.h"	

int Buzzer_Count;//LED blink Delay 

//LED initialization
void Buzzer_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //Enable APB Clock
	
	GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;				//LED Pin
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//Push pull output
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
	GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);			//Initialize LED GPIO
	GPIO_SetBits(BUZZER_PORT,BUZZER_PIN);
}

void buzzer_task(void *pvParameters)
{
    while(1)
    {
      BUZZER =~BUZZER;        //0 on, 1 off   
      delay_ms(7000);			
     // vTaskDelay(Buzzer_Count); //Delay 
    }
}  