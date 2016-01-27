#include <stdio.h>

#include "feistel.h"

int main (int argc, char *argv[])
{
	unsigned long data = 4037734570;
	unsigned long subkey[2] = {453177088, 4235227648};
	printf("testfeistel\n");
	
	feistel(&data, (unsigned long *)subkey);

	printf("\\testfeistel\n");

	return 0;
}
