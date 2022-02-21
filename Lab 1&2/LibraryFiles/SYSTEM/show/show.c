#include "show.h"
#include "time.h"
#include "stdio.h"

void show_task(void *pvParameters)
{
   u32 lastWakeTime = getSysTickCnt();
   while(1)
    {	

			vTaskDelayUntil(&lastWakeTime, F2T(RATE_50_HZ));

			oled_show();    
    }
}  

void oled_show(void)
{
	 u32 i;
	 char s[] = "Zhang Xuanye";
	 OLED_Display_On();
	 OLED_ShowString(0,0, s);
	 OLED_Refresh_Gram(); //refresh the OLED RAM
	 
	
	 /*time_t t;
   //struct tm *tm;
	 OLED_Display_On();
	 for (i = 0; i<100; i++){
		 t = time(NULL);
		 OLED_ShowString(0,0, ctime(&t));
		 OLED_Refresh_Gram();
		 delay_ms(1000);
	 } */
	 
	 /*for (i=10; i<100; i++){
		 OLED_ShowNumber( 0,0, i, 2, 12);
		 OLED_Refresh_Gram(); //refresh the OLED RAM
		 delay_ms(1000);
	 } */
	 
	 //OLED_Refresh_Gram();

	  		
}

