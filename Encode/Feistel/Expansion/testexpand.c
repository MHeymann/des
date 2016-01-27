#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "expand.h"

/**
 * Put the bits in the 32bit data piece into the rightmost bits of an
 * unsigned long. 
 */
void lget_data_bits(unsigned long *data_bits, void *data32)
{
	int i;
	unsigned char *datachars = (unsigned char *)data32;
	unsigned char c;
	unsigned long temp;
	for (i = 0; i < 4; i++) {
		c = datachars[i];
		temp = (unsigned long) c;
		temp <<= ((3 - i) * 8);
		*data_bits ^= temp;
	}
}

int main(int argc, char *argv[])
{
	unsigned long space[] = {0, 0};
	unsigned long testdata_long = 0;
	unsigned char testdata[4];
	char original_bits[33];
	char original_bits_expected[] = " 1111   0000   1010   1010   1111   0000   1010   1010";
	char expanded_bits[49];
	char expected_bits[] = "011110100001010101010101011110100001010101010101";
	int i;

	testdata[0] = 240;
	testdata[1] = 170;
	testdata[2] = 240;
	testdata[3] = 170;

	lget_data_bits(&testdata_long, (unsigned char *)testdata);

	printf("\nExpected original:\t%s\n", original_bits_expected);
	printf("Original bits:\t\t");
	print_original_bits(&testdata_long, (char *)&original_bits);
	
	expand(&testdata_long, (unsigned long *)&space);

	printf("\nExpanded bits:\t\t");
	print_expanded_bits((unsigned long *)&space, (char *)&expanded_bits);
	printf("\nExpected output:\t");

	for (i = 0; i < 49; i++) {
		
		printf("%c", expected_bits[i]);
		if (expected_bits[i] != expanded_bits[i]) {
			printf("\n\x1b[1;31mFAILED!\x1b[0m\n");
			goto FREE_DATA;
		}

		if (((i + 1) % 6) == 0) {
			printf(" ");
		}
	}
	printf("\n\n");
	printf("\x1b[1;34mPASSED!\x1b[0m\n\n");

FREE_DATA:

	return 0;
}
