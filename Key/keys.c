#include <stdio.h>
#include <stdlib.h>
#include "keys.h"

/*** static variables *********************************************************/
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

static unsigned char char_bitmasks[] = {
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

static int PC_1[] = {
	57, 49, 43, 33, 25, 17, 9, 
	1, 58, 50, 42, 34, 26, 18,
	10, 2,  59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4
};

static int PC_2[] = {
	14, 17, 11, 24, 1, 5,
	3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

static int left_shifts[] = {
	1,
	1,
	2,
	2,
	2,
	2,
	2,
	2,
	1,
	2,
	2,
	2,
	2,
	2,
	2,
	1
};

/*** helper function prototypes ***********************************************/
void permutate1(unsigned long *C, unsigned long *D, unsigned long *halves);
void perm1_bitplace(int check_bit, int set_bit, unsigned long *A, unsigned long left, unsigned long right);
void permutate2(void **subkeys, int subkey_i, unsigned long *C, unsigned long *D);
void get_bitvals(void *key, unsigned long *halves);
unsigned long rotate(unsigned long L, int shifts);
int check_bit(unsigned long number, int bit_no);
void set_subkey_bit(unsigned long *subkey, int side, int bitnumber, unsigned long A, int check_bit_no);

/*** functions ****************************************************************/
/**
 * Allocate enough memory to hold 16 subkeys of 6 bytes each
 */
void **alloc_subkeys()
{
	int i, j;
	unsigned long **subkeys = NULL;
	subkeys = malloc(sizeof(unsigned long *) * 16);
	if (!subkeys) {
		fprintf(stderr, "Memory error allocating subkeys! \n");
		return NULL;
	}

	for (i = 0; i < 16; i++) {
		subkeys[i] = NULL;
	}

	for (i = 0; i < 16; i++) {
		subkeys[i] = malloc(2 * sizeof(unsigned long));
		if (!subkeys[i]) {
			fprintf(stderr, "Memory error allocating subkeys in array! \n");
			free_subkeys((void **)subkeys);
			return NULL;
		}
		for (j = 0; j < 2; j++) {
			subkeys[i][j] = 0;
		}
	}

	return (void **)subkeys;
}

/**
 * Free subkeys allocated with alloc_subkey.
 */
void free_subkeys(void **subkeys)
{
	int i;

	if (!subkeys) {
		return;
	}
	for (i = 0; i < 16; i++) {
		if (subkeys[i]) {
			free(subkeys[i]);
		}
	}
	free(subkeys);
}

/**
 * Generate 16 subkeys from the supplied key.
 */
void get_subkeys(void *key, void **subkeys)
{
	unsigned long halves[2]; 
	int i, pc_i;
	unsigned long C[17], D[17];

	halves[0] = 0;
	halves[1] = 0;

	/* 
	 * Put the left and right halves' bits into dedicated variable spaces.
	 * This is to ensure that all systems will store all the bits without
	 * overflow.  
	 */
	get_bitvals(key, halves);

	/* initialise C and D arrays to 0 */
	for (i = 0; i < 17; i++) {
		C[i] = 0;
		D[i] = 0;
	}

	/* Permutate the bits and split into a left and a right half. */
	permutate1(C, D, halves);
	
	/* 
	 * Get the next value of C and D by rotating to the left 
	 * the given value by the amount of bits specified by 
	 * the static array left_shifts.
	 */
	for (i = 1; i < 17; i++) {
		C[i] = rotate(C[i - 1], left_shifts[i - 1]);
		D[i] = rotate(D[i - 1], left_shifts[i - 1]);
	}

	/*
	 * For each of the values of C and D, permutate according to
	 * the static array PC_2.  Store the values in subkeys.  
	 */
	for (i = 1; i < 17; i++) {	
		permutate2(subkeys, i, C, D);
	}
}


/**
 * Print the bits of each of the subkeys. 
 */
void print_subkeys(void **subkeys)
{
	int i, j, k;
	unsigned long *ulp;
	for (i = 0; i < 16; i++) {
		print_subkey(subkeys, i, NULL);
		/*
		printf("K%d:\t", i + 1);
		ulp = (unsigned long *) subkeys[i];
		for (j = 0; j < 2; j++) {
			for (k = 0; k < 24; k++) {
				if (ulp[j] & (bitmasks[k + 1])) {
					printf("1");
				} else {
					printf("0");
				}
			}
		}
		printf("\n");
		*/
	}
}

/**
 * Print the bits of the subkey specified by i. 
 */
void print_subkey(void **subkeys, int i, char *string)
{
	int j, k;
	unsigned long *ulp;
	printf("K%d:\t", i + 1);
	ulp = (unsigned long *) subkeys[i];
	for (j = 0; j < 2; j++) {
		for (k = 0; k < 24; k++) {
			if (ulp[j] & (bitmasks[k + 1])) {
				printf("1");
				if (string) {
					string[j * 24 + k] = '1';
				}
			} else {
				if (string) {
					string[j * 24 + k] = '0';
				}
				printf("0");
			}
			if (((k + 1) % 8) == 0) {
				printf(" ");
			}
		}
	}
	printf("\n");
	if (string) {
		string[48] = '\0';
	}
}

/*** helper functions *********************************************************/
/**
 * Permutate the bits, found in the appropriate two halves, according to
 * the order specified by the static array PC_1.  The result is split into
 * left and right halves.  
 */
void permutate1(unsigned long *C, unsigned long *D, unsigned long *halves)
{
	int set_bit, check_bit;
	for (set_bit = 1; set_bit <= 28; set_bit++) {
		check_bit = PC_1[set_bit - 1];
		perm1_bitplace(check_bit, set_bit, C, halves[0], halves[1]);
		check_bit = PC_1[28 + set_bit - 1];
		perm1_bitplace(check_bit, set_bit, D, halves[0], halves[1]);
	}
}

/**
 * Check bit check_bit in either the left or right half of the key, and place
 * into the unsigned long pointed to by A at position setbit.  
 */
void perm1_bitplace(int check_bit, int set_bit, unsigned long *A, unsigned long left, unsigned long right)
{
	unsigned long *half_pt;
	if (check_bit > 32) {
		half_pt = &right;
		check_bit -= 32;
	} else {
		half_pt = &left;
	}
	if (bitmasks[check_bit] & (*half_pt)) {
		*A ^= bitmasks[set_bit];
	}
}

/**
 * Permutate the bits in C and D based on the values in PC_2 and place into 
 * the array of subkeys.
 */
void permutate2(void **subkeys, int subkey_i, unsigned long *C, unsigned long *D)
{
	int leftright, k, check_bit_no;
	for (leftright = 0; leftright < 2; leftright++) {
		for (k = 0; k < 24; k++) {
			check_bit_no = PC_2[leftright * 24 + k];
			if (check_bit_no <= 28) {
			    /*printf("");*/
				set_subkey_bit((unsigned long *)subkeys[subkey_i - 1], leftright, k + 1, C[subkey_i], check_bit_no);
			} else {
				check_bit_no -= 28;
				set_subkey_bit((unsigned long *)subkeys[subkey_i - 1], leftright, k + 1, D[subkey_i], check_bit_no);
			}
		}
	}
}

/**
 * Set the value of check_bit_no to the the appropriate position in the memory
 * space pointed to by subkey. 
 */
void set_subkey_bit(unsigned long *subkey, int leftright, int setbit_number, unsigned long A, int check_bit_no)
{
	if(A & bitmasks[check_bit_no]) {
		subkey[leftright] ^= bitmasks[setbit_number];
	}
}

/**
 * Take the pointer to the key supplied and use it to place its bits into memory
 * space dedicated to hold the two halves of the key.  
 */
void get_bitvals(void *key, unsigned long *halves)
{
	unsigned char *ckey = (unsigned char *)key;
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 8; j++) {
			if (char_bitmasks[j + 1] & ckey[i]) {
				halves[0] ^= bitmasks[i * 8 + j + 1];
			}
			if (char_bitmasks[j + 1] & ckey[i + 4]) {
				halves[1] ^= bitmasks[i * 8 + j + 1];
			}
		}
	}
}

/**
 * rotate bits 1 to 28 to the left by the amount of bits indicated by shifts.  
 */
unsigned long rotate(unsigned long L, int shifts)
{
	int i;

	for (i = 0; i < shifts; i++) {
		if (L & BIT1) {
			L ^= BIT29;
			L ^= BIT1;
		}
		L <<= 1;
	}

	return L;
}

