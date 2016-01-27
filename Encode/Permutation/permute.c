#include <stdio.h>

#include "permute.h"

/*** Macros *******************************************************************/

#define LEFT	0
#define RIGHT	1


/*** Static Global Variables **************************************************/

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
	BIT32
};

/*
static unsigned long char_bitmasks[] = {
	'\0',
	CHAR_BIT1,
	CHAR_BIT2,
	CHAR_BIT3,
	CHAR_BIT4,
	CHAR_BIT5,
	CHAR_BIT6,
	CHAR_BIT7,
	CHAR_BIT8
};
*/

unsigned int init_P[] = {
	58,    50,   42,    34,    26,   18,    10,    2,
	60,    52,   44,    36,    28,   20,    12,    4,
	62,    54,   46,    38,    30,   22,    14,    6,
	64,    56,   48,    40,    32,   24,    16,    8,
	57,    49,   41,    33,    25,   17,     9,    1,
	59,    51,   43,    35,    27,   19,    11,    3,
	61,    53,   45,    37,    29,   21,    13,    5,
	63,    55,   47,    39,    31,   23,    15,    7
};

unsigned int final_P[] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25
};


/*** Helper Function Prototype ************************************************/

void set_bit(unsigned long *data_bits, int check_bit,
		unsigned long *permuted_bits, int set_side, int set_bit);


/*** Functions ****************************************************************/

void final_permutation(unsigned long *data_bits, unsigned long *permuted_bits)
{
	int i, j;
	int bit_no;
	
	permuted_bits[0] = 0;
	permuted_bits[1] = 0;
	for (i = 0; i < 32; i++) {
		bit_no = final_P[i];
		set_bit(data_bits, bit_no, permuted_bits, LEFT, i + 1);

		bit_no = final_P[i + 32];
		set_bit(data_bits, bit_no, permuted_bits, RIGHT, i + 1);
	}
}


void initial_permutation(unsigned long *data_bits, unsigned long *permuted_bits)
{
	int i, j;
	int bit_no;
	
	permuted_bits[0] = 0;
	permuted_bits[1] = 0;
	for (i = 0; i < 32; i++) {
		bit_no = init_P[i];
		set_bit(data_bits, bit_no, permuted_bits, LEFT, i + 1);

		bit_no = init_P[i + 32];
		set_bit(data_bits, bit_no, permuted_bits, RIGHT, i + 1);
	}
}


void print_bits_permutation(unsigned long *data, char *string)
{
	char s[65];
	int i;

	if (!string) {
		string = (char *)s;
	}
	string[64] = '\0';

	for (i = 0; i < 32; i++) {
		if (bitmasks[i + 1] & data[LEFT]) {
			string[i] = '1';
		} else {
			string[i] = '0';
		}
		if (bitmasks[i + 1] & data[RIGHT] ) {
			string[i + 32] = '1';
		} else {
			string[i + 32] = '0';
		}
	}

	for (i = 0; i < 64; i++) {
		printf("%c", string[i]);
		if (((i + 1) % 8) == 0) {
			printf(" ");
		}
	}
}


/*** Helper functions *********************************************************/

void set_bit(unsigned long *data_bits,  int check_bit,
		unsigned long *permuted_bits, int set_side, int set_bit)
{
	int check_side;
	if (check_bit > 32) {
		check_side = RIGHT;
		check_bit -= 32;
	} else {
		check_side = LEFT;
	}
	if (bitmasks[check_bit] & data_bits[check_side]) {
		permuted_bits[set_side] ^= bitmasks[set_bit];
	}
}

