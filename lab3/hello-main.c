#include <stdio.h>
#include "hello.h"

int main()
{
	printf("Hello world from main!\n");
	delay(0x5fffff);

	helloprint();
//	hellocount();
	helloprint2();
	
	printf("Bye\n");
}

void delay(int counter)
{
	int i;
	for (i = 0; i<counter; ++i);
}
