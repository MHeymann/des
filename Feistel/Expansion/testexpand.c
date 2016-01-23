#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "expand.h"

int main(int argc, char *argv[])
{
	unsigned long *space = alloc_expand_space();
	unsigned char *testdata = malloc(4 * sizeof(char));
	char original_bits[33];
	char original_bits_expected[] = " 1111   0000   1010   1010   1111   0000   1010   1010";
	char expanded_bits[49];
	char expected_bits[] = "011110100001010101010101011110100001010101010101";
	int i;

	testdata[0] = 240;
	testdata[1] = 170;
	testdata[2] = 240;
	testdata[3] = 170;

	printf("original bits:\t\t");
	print_original_bits((unsigned long *)testdata, (char *)&original_bits);
	printf("expected original:\t%s\n", original_bits_expected);
	expand((unsigned long *)testdata, space);
	printf("expended bits:\t\t");
	print_expanded_bits(space, (char *)&expanded_bits);
	printf("bits should be:\t\t");

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
	free_expanded_space(space);
	free(testdata);

	return 0;
}
