#include <stdio.h>

#include "expand.h"
#include "debug.h"

/*** helper function headers **************************************************/
int32_t xor32(int32_t a, int32_t b);
int64_t xor64(int64_t a, int64_t b);

uint64_t expand(uint32_t word) 
{
	uint64_t word64 = (uint64_t)word;
	uint64_t result;
	uint64_t mask4 = 15;
	uint64_t mask1 = 1;
	uint64_t imprint4 = 0;
	uint64_t imprint1 = 0;
	int i;

	result = result ^ result;

	mask1 = mask1 << 31;
	if (mask1 & word64) {
		result = 1;
	}
	mask1 = 1;
	mask1 = mask1 << 4;
	if (mask1 & word64) {
		imprint1 = mask1 << 1;
		result = result | imprint1;
	}
	imprint4 = mask4 & word64;
	imprint4 = imprint4 << 1;
	result = result | imprint4;

	mask1 = 1;
	imprint1 = 1;
	imprint1 = imprint1 << 47;
	if (word64 & mask1) {
		result = result | imprint1;
	}
	imprint1 = imprint1 >> 5;
	mask1 = mask1 << 27;
	if (word64 & mask1) {
		result = result | imprint1;
	}
	mask4 = 15;
	mask4 = mask4 << 28;
	imprint4 = mask4 & word64;
	imprint4 = imprint4 >> 28;
	imprint4 = imprint4 << 43;
	result = result | imprint4;

	mask1 = 1;
	mask4 = 15;
	for (i = 1; i < 7; i++) {
	}

	return result;
}

uint32_t xor32(uint32_t a, uint32_t b)
{
	return a ^ b;
}

uint64_t xor64(uint64_t a, uint64_t b)
{
	return a ^ b;
}
