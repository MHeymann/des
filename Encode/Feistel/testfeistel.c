#include <stdio.h>

#include "feistel.h"

unsigned long bitmasks[] = {
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
BIT32
};


int main (int argc, char *argv[])
{
	int i = 0;
	char c;
	unsigned long data = 4037734570;
	unsigned long subkey[2] = {453177088, 4235227648};
	char input[] = "11110000101010101111000010101010";
	char output[] = "00100011010010101010100110111011";
	char subkey_string[] = "000110110000001011101111111111000111000001110010";
	printf("\x1b[1;35mtestfeistel\x1b[0m\n\n");

	printf("Bits before feistel:\t ");
	for (i = 0; i < 32; i++) {
		if (bitmasks[i + 1] & data) {
			printf("1");
		} else {
			printf("0");
		}
		if (((i + 1) % 4) == 0) {
			printf("   ");
		}
	}
	printf("\nBits should be:\t\t ");
	for (i = 0; i < 32; i++) {
		printf("%c", input[i]);	
		if (((i + 1) % 4) == 0) {
			printf("   ");
		}

	}
	printf("\n");

	printf("Subkey: \t\t");
	for (i = 0; i < 48; i++) {
		printf("%c", subkey_string[i]);
		if (((i + 1) % 6) == 0) {
			printf(" ");
		}
	}
	printf("\n");
	
	data = feistel(&data, (unsigned long *)subkey);


	printf("After feistel:\t\t ");
	for (i = 0; i < 32; i++) {
		if (bitmasks[i + 1] & data) {
			printf("1");
		} else {
			printf("0");
		}
		if (((i + 1) % 4) == 0) {
			printf("   ");
		}
	}
	printf("\n");

	printf("Should be: \t\t ");
	for (i = 0; i < 32; i++) {
		printf("%c", output[i]);
		if (((i + 1) % 4) == 0) {
			printf("   ");
		}
		if (bitmasks[i + 1] & data) {
			c = '1';
		} else {
			c = '0';
		} 
		if (c != output[i]) {
			printf("\n\x1b[1;31mFAILED!\x1b[0m\n");
			goto QUIT;
		}
	}
	printf("\n");

	printf("\n\x1b[1;35m\\testfeistel\x1b[0m\n");


	printf("\n\x1b[1;34mPASSED!\x1b[0m\n\n");
QUIT:
	return 0;
}
