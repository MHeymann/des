#include <stdio.h>

#include "substitution.h"

int main(int argc, char *argv[])
{
	int i;
	char input[] = "011000010001011110111010100001100110010100100111";
	char output[] = "01011100100000101011010110010111";
	char test_string[33];
	unsigned long ldata[2];
	unsigned long *data;
	unsigned long subd;

	ldata[0] = 1628944896;
	ldata[1] = 2254776064;
	data = (unsigned long *)&ldata;

	printf("\nExpected input:\t\t");
	for (i = 0; i < 48; i++) {
		printf("%c", input[i]);
		if (((i + 1) % 6) == 0) {
			printf(" ");
		}
	}
	printf("\nParsed input:\t\t");
	print_unsubstituted_data(data, NULL);

	subd = 0;
	substitute(data, &subd);

	
	printf("Found output:\t\t");
	print_substituted_data(&subd, (char *)test_string);

	printf("Expected output:\t");
	printf(" ");
	for (i = 0; i < 32; i++) {
		printf("%c", output[i]);
		if (test_string[i] != output[i]) {
			printf("\n\x1b[1;31mFAILED!\x1b[0m\n");
			goto QUIT;
		}
		if ((((i + 1) % 4) == 0) && i != 31) {
			printf("   ");
		}
	}
	printf("\n\n");

	printf("\x1b[1;34mPASSED!\x1b[0m\n\n");

QUIT:
	return 0;
}
