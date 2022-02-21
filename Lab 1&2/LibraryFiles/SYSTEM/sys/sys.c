#include "sys.h"

void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//Disable all interrupts
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//Enable all interrupts
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}

//Set stack address
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

void JTAG_Set(u8 mode)
{
	u32 temp;
	temp=mode;
	temp<<=25;
	RCC->APB2ENR|=1<<0;     //Enable APB Clock	   
	AFIO->MAPR&=0XF8FFFFFF; //Clean MAPR[26:24]
	AFIO->MAPR|=temp;       //Set jtag mode
} 

