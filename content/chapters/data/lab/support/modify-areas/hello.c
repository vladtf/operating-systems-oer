#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static const char boring[8192] = { 69, };
static char dull[16384] = { 69, };
static char nada[32768];

static void alloc_heap(void)
{
	malloc(64 * 1024);
	malloc(64 * 1024);
	malloc(64 * 1024);
	malloc(64 * 1024);
}

static void alloc_stack(size_t order)
{
	char fill[32768];

	fill[0] = 'a';
	fill[32767] = 'b';

	if (order == 0)
		sleep(1000);
	else
		alloc_stack(order-1);
}

int main(void)
{
	puts("Hello, world!");
	alloc_heap();
	alloc_stack(5);
	sleep(10000);

	return 0;
}
