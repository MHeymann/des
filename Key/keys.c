#include <stdio.h>
#include <stdlib.h>
#include "keys.h"

/*** static variables *********************************************************/
static unsigned char bitmasks[] = {
	'\0',
	BIT1,
	BIT2,
	BIT3, 
	BIT4,
	BIT5,
	BIT6, 
	BIT7,
	BIT8
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
void get_bitvals(void *key, char *bits);
void set_bitvals(char *bits, unsigned char *subkey);
unsigned long rotate(unsigned long L, int shifts);
int check_bit(long number, int bit_no);
void set_subkey_bit(char *bits, int i, long A, int pc_i);

/*** functions ****************************************************************/
void **alloc_subkeys()
{
	int i;
	void **subkeys = NULL;
	subkeys = malloc(sizeof(void *) * 16);
	if (!subkeys) {
		fprintf(stderr, "Memory error allocating subkeys! \n");
		return NULL;
	}

	for (i = 0; i < 16; i++) {
		subkeys[i] = NULL;
	}

	for (i = 0; i < 16; i++) {
		subkeys[i] = malloc(6);
		if (!subkeys[i]) {
			fprintf(stderr, "Memory error allocating subkeys in array! \n");
			free_subkeys(subkeys);
			return NULL;
		}
	}

	return subkeys;
}


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


void get_subkeys(void *key, void **subkeys)
{
	char bits[64]; 
	int i, j, pc_i;
	unsigned long C[17], D[17];
	unsigned char perm_key[56];

	get_bitvals(key, bits);

	for (i = 0; i < 56; i++) {
		perm_key[i] = bits[PC_1[i] - 1];
	}
	
	C[0] = 0;
	D[0] = 0;
	for (i = 0; i < 28; i++) {
		C[0] <<= 1;
		D[0] <<= 1;
		C[0] += perm_key[i];
		D[0] += perm_key[28 + i];
	}

	for (i = 1; i < 17; i++) {
		C[i] = rotate(C[i - 1], left_shifts[i - 1]);
		D[i] = rotate(D[i - 1], left_shifts[i - 1]);
	}

	for (i = 1; i < 17; i++) {
		for (j = 0; j < 48; j++) {
			pc_i = PC_2[j];
			if (pc_i <= 28) {
				set_subkey_bit(bits, j, C[i], pc_i);
			} else {
				pc_i -= 28;
				set_subkey_bit(bits, j, D[i], pc_i);
			}
		}

		set_bitvals(bits, (unsigned char *)subkeys[i - 1]);			
	}

}

/*** helper functions *********************************************************/
void set_subkey_bit(char *bits, int i, long A, int pc_i)
{
	if (check_bit(A, pc_i)) {
		bits[i] = 1;
	} else {
		bits[i] = 0;
	}
}


int check_bit(long number, int bit_no) 
{
	return ((number >> (28 - bit_no)) & BIT1);
}

void set_bitvals(char *bits, unsigned char *subkey) 
{
	int i, j, k;
	unsigned char c = 0;
	for (i = 0; i < 6; i++) {
		c = 0;
		for (j = 0; j < 8; j++) {
			k = i * 8 + j;
			c <<= 1;
			if (bits[k]) {
				c += 1;
			} 
		}
		subkey[i] = c;
	}
}


void get_bitvals(void *key, char *bits)
{
	unsigned char *ckey = (unsigned char *)key;
	int i, j, bitno;

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			bitno = 8 - j;
			if (bitmasks[bitno] & ckey[i]) {
				bits[8 * i + j] = 1;
			} else {
				bits[8 * i + j] = 0;
			}
		}
	}
}


unsigned long rotate(unsigned long L, int shifts)
{
	int i;
	unsigned long rightmost = 0;

	rightmost = L >> (28 - shifts);
	
	for (i = 0; i < shifts; i++) {
		L <<= 1;
		if (L & BIT29) {
			L ^= BIT29;
		}
	}
	L |= rightmost;

	return L;
}

/*** main routine *************************************************************/
int main(int argc, char *arv[]) {
	unsigned long long testkey = 17428856458888819731;
	void **subkeys = alloc_subkeys(); 
	int i, j, k;
	unsigned char *c;

	get_subkeys(&testkey, subkeys);

	for (i = 0; i < 16; i++) {
		printf("K%d:\t", i + 1);
		c = (unsigned char *) subkeys[i];
		for (j = 0; j < 6; j++) {
			for (k = 0; k < 8; k++) {
				if (c[j] & (bitmasks[8 - k])) {
					printf("1");
				} else {
					printf("0");
				}
			}
		}
		printf("\n");
	}

	free_subkeys(subkeys);

	return 0;
}
