#include <stdio.h>
#include <stdlib.h>

#include "keys.h"

int main(int argc, char *argv[]) 
{
	unsigned char *testkey_pt;
	void **subkeys;
	char *expectedbits[] = {
	"000110110000001011101111111111000111000001110010",
	"011110011010111011011001110110111100100111100101",
	"010101011111110010001010010000101100111110011001",
	"011100101010110111010110110110110011010100011101",
	"011111001110110000000111111010110101001110101000",
	"011000111010010100111110010100000111101100101111",
	"111011001000010010110111111101100001100010111100",
	"111101111000101000111010110000010011101111111011",
	"111000001101101111101011111011011110011110000001",
	"101100011111001101000111101110100100011001001111",
	"001000010101111111010011110111101101001110000110",
	"011101010111000111110101100101000110011111101001",
	"100101111100010111010001111110101011101001000001",
	"010111110100001110110111111100101110011100111010",
	"101111111001000110001101001111010011111100001010",
	"110010110011110110001011000011100001011111110101"
	};
	int i, j;
	char string[49];

	subkeys = alloc_subkeys(); 
	if (!subkeys) {
		fprintf(stderr, "Memory error!\n");
		return 1;
	}
	
	testkey_pt = malloc(8 * sizeof(char));
	if (!testkey_pt) {
		free_subkeys(subkeys);
	}
	testkey_pt[0] = 19;
	testkey_pt[1] = 52;
	testkey_pt[2] = 87;
	testkey_pt[3] = 121;
	testkey_pt[4] = 155;
	testkey_pt[5] = 188;
	testkey_pt[6] = 223;
	testkey_pt[7] = 241;

	get_subkeys(testkey_pt, subkeys);

	for (i = 0; i < 16; i++) {
		printf("Expected:\t");
		for (j = 0; j < 48; j++) {
			printf("%c", expectedbits[i][j]);
			if (((j + 1) % 8) == 0) {
				printf(" ");
			}
		}
		printf("\nFound:\t");
		print_subkey(subkeys, i, (char *)string);
		printf("\n");

		for (j = 0; j < 48; j++) {
			if (expectedbits[i][j] != string[j]) { 
				goto FAIL;
			}
		}
	}

	printf("\x1b[1;34mPASSED!\x1b[0m\n\n");
	goto FREE;
FAIL:
	printf("\x1b[1;31mFAILED!\x1b[0m\n\n");
FREE:
	free_subkeys(subkeys);
	free(testkey_pt);

	return 0;
}
