#include <stdio.h>
#include "hello.h"

int count = 0;

void hellocount()
{
	printf("you can enter at least ten times\n");
	while (count < 10)
	{
		printf("please enter");
		if (getchar())
		{
			printf("you enter a key\n");
			count += 1;
			printf("current count: %d\n", count);
		}
	}
}

void helloprint2()
{
	printf("hello world from funct2!\n");
	delay(0x7fffffff);
}
