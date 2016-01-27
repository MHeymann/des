#include <stdio.h>
#include "permute.h"

int main(int argc, char *argv[])
{
	unsigned long initial_data[2] = {19088743, 2309737967};
	unsigned long final_data[2] = {172808597, 1128411700};
	unsigned long permuted[2] = {0, 0};
	char string[65];
	char final_expected_input[] = "0000101001001100110110011001010101000011010000100011001000110100";
	char final_expected_output[] = "1000010111101000000100110101010000001111000010101011010000000101";
	char initial_expected_input[] = "0000000100100011010001010110011110001001101010111100110111101111";
	char initial_expected_output[] = "1100110000000000110011001111111111110000101010101111000010101010";
	int i;

	printf("\nInitial Permutation:\n");
	printf("\nexpected input:\t\t");
	for (i = 0; i < 64; i++) {
		printf("%c", initial_expected_input[i]);
		if (((i + 1) % 8) == 0) {
			printf(" ");
		}
	}
	printf("\nactual input:\t\t");
	print_bits_permutation(initial_data, (char *)string);
	printf("\n\n");

	initial_permutation(initial_data, permuted);
	
	printf("actual output:\t\t");
	print_bits_permutation(permuted, (char *)string);

	printf("\nexpected output:\t");
	for (i = 0; i < 64; i++) {
		printf("%c", initial_expected_output[i]);
		if (((i + 1) % 8) == 0) {
			printf(" ");
		}
		if (initial_expected_output[i] != string[i]) {
			printf("\n\n\x1b[1;31mFAILED!\x1b[0m\n");
			goto FINAL;
		}
	}
	printf("\n\n");
	printf("\x1b[1;34mPASSED!\x1b[0m\n");

FINAL:

	printf("\nFinal Permutation:\n");
	printf("\nexpected input:\t\t");
	for (i = 0; i < 64; i++) {
		printf("%c", final_expected_input[i]);
		if (((i + 1) % 8) == 0) {
			printf(" ");
		}
	}
	printf("\nactual input:\t\t");
	print_bits_permutation(final_data, (char *)string);
	printf("\n\n");

	final_permutation(final_data, permuted);
	
	printf("actual output:\t\t");
	print_bits_permutation(permuted, (char *)string);

	printf("\nexpected output:\t");
	for (i = 0; i < 64; i++) {
		printf("%c", final_expected_output[i]);
		if (((i + 1) % 8) == 0) {
			printf(" ");
		}
		if (final_expected_output[i] != string[i]) {
			printf("\n\n\x1b[1;31mFAILED!\x1b[0m\n");
			goto QUIT;
		}
	}

	printf("\n\n");
	printf("\x1b[1;34mPASSED!\x1b[0m\n\n");

QUIT:
	return 0;
}
