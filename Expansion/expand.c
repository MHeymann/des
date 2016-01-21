#include <stdio.h>
#include <stdlib.h>

#include "expand.h"
#include "debug.h"

static unsigned long bitmasks[] = {
	0,
	BIT1,
	BIT2,
	BIT3,
	BIT4,
	BIT5,
	BIT6,
	BIT7,
	BIT8,
	BIT9,
	BIT10,
	BIT11,
	BIT12,
	BIT13,
	BIT14,
	BIT15,
	BIT16,
	BIT17,
	BIT18,
	BIT19,
	BIT20,
	BIT21,
	BIT22,
	BIT23,
	BIT24,
	BIT25,
	BIT26,
	BIT27,
	BIT28,
	BIT29,
	BIT30,
	BIT31,
	BIT32,
};


/*** static global variables **************************************************/
int E_Bitselection[] = {
	32, 1,  2,  3,  4,  5,
	4,  5,  6,  7,  8,  9,
	8,  9,  10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1
};

/*** Helper Functions Prototypes **********************************************/


/*** Helper function prototypes ***********************************************/
unsigned long *alloc_expand_space()
{
	unsigned long *space = NULL;

	space = malloc(sizeof(unsigned long) * 2);
	if (!space) {
		fprintf(stderr, "Memory Error on allocating expand space int expand.c\n");
		return NULL;
	}
	space[0] = 0;
	space[1] = 0;
	return space;
}

void free_expanded_space(unsigned long *space) 
{
	free(space);
}

void print_expanded_bits(unsigned long *data) 
{
	int i;
	char string[49];
	
	for (i = 0; i < 24; i++) {
		if (bitmasks[i + 1] ^ data[0]) {
			string[i] = '1';
		} else {
			string[i] = '0';
		}
		if (bitmasks[i + 1] ^ data[1]) {
			string[i + 24] = '1';
		} else {
			string[i + 24] = '0';
		}
	}
	string[48] = '\0';
	printf(string);
}


void expand(unsigned long *data_bits, unsigned long *expanded_bits) 
{
	int i, check_bit;
	
	for (i = 0; i < 24; i++) {
		check_bit = E_Bitselection[i];
		if (bitmasks[check_bit] & *data_bits) {
			expanded_bits[0] ^= bitmasks[i + 1];
		}
		check_bit = E_Bitselection[i + 24];
		if (bitmasks[check_bit] & *data_bits) {
			expanded_bits[1] ^= bitmasks[24 + i + 1];
		}
	}
}

void main(void)
{
	unsigned long *space = alloc_expand_space();
	unsigned char testdata = malloc(sizeof(unsigned long));
	int i;

	testdata[0] = 240;
	testdata[1] = 170;
	testdata[2] = 240;
	testdata[3] = 170;

	expand((unsigned long *)testdata, space);

	free_expanded_space((unsigned long *)testdata, space);
}
