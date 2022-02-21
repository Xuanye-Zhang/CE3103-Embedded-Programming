#include "userbutton.h"

// UserButton Initialization

void userB_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); //Enable APB Clock
	
	GPIO_InitStructure.GPIO_Pin = USERB_PIN;				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
//	GPIO_Init(USERB_PORT, &GPIO_InitStructure);			
//	GPIO_SetBits(USERB_PORT,USERB_PIN);
}


static u32 notes[] = {
	 2272, // A - 440 Hz
	 2024, // B - 494 Hz
	 3816, // C - 262 Hz
	 3401, // D - 294 Hz
	 3030, // E - 330 Hz
	 2865, // F - 349 Hz
	 2551, // G - 392 Hz
	 1136, // a - 880 Hz
	 1012, // b - 988 Hz
	 1912, // c - 523 Hz
	 1703, // d - 587 Hz
	 1517, // e - 659 Hz
	 1432, // f - 698 Hz
	 1275, // g - 784 Hz
};
static u8* song = (uint8_t*)"e2,d2,e2,d2,e2,B2,d2,c2,A2_C2,E2,A2,B2_E2,G2,B2,c4_E2,e2,d2,e2,d2,e2,B2,d2,c2,A2_C2,E2,A2,B2_E2,c2,B2,A4";
static uint32_t getNote(uint8_t ch)
{
	 if (ch >= 'A' && ch <= 'G')
	 return notes[ch - 'A'];
	 if (ch >= 'a' && ch <= 'g')
	 return notes[ch - 'a' + 7];
	 return 0;
}
static uint32_t getDuration(uint8_t ch)
{
	 if (ch < '0' || ch > '9')
	 return 400;
	 /* number of ms */
	 return (ch - '0') * 200;
}
static uint32_t getPause(uint8_t ch)
{
	 switch (ch) {
	 case '+':
	 return 0;
	 case ',':
	 return 5;
	 case '.':
	 return 20;
	 case '_':
	 return 30;
	 default:
	 return 5;
	 }
}

static void playNote(uint32_t note, uint32_t durationMs)
{
	 uint32_t t = 0;
	 if (note > 0) {
		 while (t < (durationMs*1000)) {
			 BUZZER = 1; 
			 delay_us(note/2);
			 BUZZER = 0; 
			 delay_us(note/2);
			 t += note;
		 }
	 }
	 else {
			delay_ms(durationMs); // ms timer
	 }
}

static void playSong(uint8_t *song) {
	 uint32_t note = 0;
	 uint32_t dur = 0;
	 uint32_t pause = 0;
	 /*
	 * A song is a collection of tones where each tone is
	 * a note, duration and pause, e.g.
	 * "E2,F4,"
	 */
	 while(*song != '\0') {
		 note = getNote(*song++);
		 if (*song == '\0')
		 break;
		 dur = getDuration(*song++);
		 if (*song == '\0')
		 break;
		 pause = getPause(*song++);
		 playNote(note, dur);
		 delay_us(pause);
	 }
}

void userB_task (void *pvParameters)
{
	BUZZER = 0;
	while(1)
	{
		if (GPIO_ReadInputDataBit(GPIOD,USERB_PIN) == 1)
		{
			vTaskDelay(200);
			// playSong(song);
			//LED = 1;
		}
		
		if (GPIO_ReadInputDataBit(GPIOD,USERB_PIN) == 0)
		{
			playSong(song);
			LED = 0;
			vTaskDelay(500);
		}
	}
}
