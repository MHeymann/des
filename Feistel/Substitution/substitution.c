#include <stdio.h>
#include <stdlib.h>

#include "substitution.h"

/*** Macros *******************************************************************/

#define OUTER_MASK1	2214592512
#define OUTER_MASK2	34603008
#define OUTER_MASK3	540672
#define OUTER_MASK4	8448

#define INNER_MASK1	2013265920
#define INNER_MASK2	31457280
#define INNER_MASK3	491520
#define INNER_MASK4	7680

/*** Static Global Variables **************************************************/

/*
 * masks four the outerbits of each respective group of four in one half
 * of the data.
 */
static int outer_masks[] = {
	OUTER_MASK1, 
	OUTER_MASK2, 
	OUTER_MASK3, 
	OUTER_MASK4
};

/*
 * masks four the outerbits of each respective group of four in one half
 * of the data.
 */
static int inner_masks[] = {
	INNER_MASK1, 
	INNER_MASK2, 
	INNER_MASK3, 
	INNER_MASK4 
};

/*
 * bitmasks used to address bits in unsigned longs
 */
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
 * bitmasks used to address bits in unsigned characters
 */
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

/**
 * The substitution boxes
 */
static unsigned char S_BOXES[8][4][16] = {
	{ 
		{14,  4,  13,  1,   2, 15,  11,  8,   3, 10,   6, 12,   5,  9,   0,  7},
		{ 0, 15,   7,  4,  14,  2,  13,  1,  10,  6,  12, 11,   9,  5,   3,  8},
		{ 4,  1,  14,  8,  13,  6,   2, 11,  15, 12,   9,  7,   3, 10,   5,  0},
		{15, 12,   8,  2,   4,  9,   1,  7,   5, 11,   3, 14,  10,  0,   6, 13}
	},

	{ 
		{15,  1,   8, 14,   6, 11,   3,  4,   9,  7,   2, 13,  12,  0,   5, 10},
		{ 3, 13,   4,  7,  15,  2,   8, 14,  12,  0,   1, 10,   6,  9,  11,  5},
		{ 0, 14,   7, 11,  10,  4,  13,  1,   5,  8,  12,  6,   9,  3,   2, 15},
		{13,  8,  10,  1,   3, 15,   4,  2,  11,  6,   7, 12,   0,  5,  14,  9}
	},

	{ 
		{10,  0,   9, 14,   6,  3,  15,  5,   1, 13,  12,  7,  11,  4,   2,  8},
		{13,  7,   0,  9,   3,  4,   6, 10,   2,  8,   5, 14,  12, 11,  15,  1},
		{13,  6,   4,  9,   8, 15,   3,  0,  11,  1,   2, 12,   5, 10,  14,  7},
		{ 1, 10,  13,  0,   6,  9,   8,  7,   4, 15,  14,  3,  11,  5,   2, 12}
	},
    
	{ 	
		{ 7, 13,  14,  3,   0,  6,   9, 10,   1,  2,   8,  5,  11, 12,   4, 15},
		{13,  8,  11,  5,   6, 15,   0,  3,   4,  7,   2, 12,   1, 10,  14,  9},
		{10,  6,   9,  0,  12, 11,   7, 13,  15,  1,   3, 14,   5,  2,   8,  4},
		{ 3, 15,   0,  6,  10,  1,  13,  8,   9,  4,   5, 11,  12,  7,   2, 14}
	},

	{ 
		{ 2, 12,   4,  1,   7, 10,  11,  6,   8,  5,   3, 15,  13,  0,  14,  9},
		{14, 11,   2, 12,   4,  7,  13,  1,   5,  0,  15, 10,   3,  9,   8,  6},
		{ 4,  2,   1, 11,  10, 13,   7,  8,  15,  9,  12,  5,   6,  3,   0, 14},
		{11,  8,  12,  7,   1, 14,   2, 13,   6, 15,   0,  9,  10,  4,   5,  3}
	},

	{ 
		{12,  1,  10, 15,   9,  2,   6,  8,   0, 13,   3,  4,  14,  7,   5, 11},
		{10, 15,   4,  2,   7, 12,   9,  5,   6,  1,  13, 14,   0, 11,   3,  8},
		{ 9, 14,  15,  5,   2,  8,  12,  3,   7,  0,   4, 10,   1, 13,  11,  6},
		{ 4,  3,   2, 12,   9,  5,  15, 10,  11, 14,   1,  7,   6,  0,   8, 13}
	},

	{ 
		{ 4, 11,   2, 14,  15,  0,   8, 13,   3, 12,   9,  7,   5, 10,   6,  1},
		{13,  0,  11,  7,   4,  9,   1, 10,  14,  3,   5, 12,   2, 15,   8,  6},
		{ 1,  4,  11, 13,  12,  3,   7, 14,  10, 15,   6,  8,   0,  5,   9,  2},
		{ 6, 11,  13,  8,   1,  4,  10,  7,   9,  5,   0, 15,  14,  2,   3, 12}
	},

	{
		{13,  2,   8,  4,   6, 15,  11,  1,  10,  9,   3, 14,   5,  0,  12,  7},
		{ 1, 15,  13,  8,  10,  3,   7,  4,  12,  5,   6, 11,   0, 14,   9,  2},
		{ 7, 11,   4,  1,   9, 12,  14,  2,   0,  6,  10, 13,  15,  3,   5,  8},
		{ 2,  1,  14,  7,   4, 10,   8, 13,  15, 12,   9,  0,   3,  5,   6, 11}
	}
};


/*** Helper Function Prototypes ***********************************************/

int get_row(unsigned long *data, int group_i);
int get_col(unsigned long *data, int group_i);

/*** Functions ****************************************************************/

/**
 * Substitute groups of six bits with groups of four, according to 8
 * substitution tables.  Put result into a 32 bit unsigned long called 
 * substituted.  
 */
void substitute(unsigned long *data, unsigned long *substituted)
{
	int i, row, col;
	unsigned long replace_mask;

	for (i = 0; i < 8; i++) {
		row = get_row(data, i);
		col = get_col(data, i);
		replace_mask = (unsigned long)S_BOXES[i][row][col];
		replace_mask <<= ((7 - i) * 4);
		*substituted ^= replace_mask;
	}	
}

/**
 * Print the data bits before having undergone substitution.  
 * Put the resultant string into memory pointed at by string.
 * String may be null.  
 */
void print_unsubstituted_data(unsigned long *data, char *string)
{
	int i, free_s = 0;
	if (!string) {
		string = malloc(49);
		free_s = 1;
	}
	string[48] = '\0';
	for (i = 0; i < 24; i++) {
		if (bitmasks[i + 1] & data[0]) {
			string[i] = '1';
		} else {
			string[i] = '0';
		}
		if (bitmasks[i + 1] & data[1]) {
			string[i + 24] = '1';
		} else {
			string[i + 24] = '0';
		}
	}
	for (i = 0; i < 48; i++) {
		printf("%c", string[i]);
		if (((i + 1) % 6) == 0) {
			printf(" ");
		}
	}
	printf("\n");
	if (free_s) {
		free(string);
	}
} 

/**
 * Print the data bits after having undergone substitution.  
 * Put the resultant string into memory pointed at by string.
 * String may be null.  
 */
void print_substituted_data(unsigned long *data, char *string)
{
	int i;

	string[32] = '\0';
	printf(" ");
	for (i = 0; i < 32; i++) {
		if (bitmasks[i + 1] & data[0]) {
			if (string) {
				string[i] = '1';
			}
			printf("1");
		} else {
			if (string) {
				string[i] = '0';
			}
			printf("0");
		}
		if (((i + 1) % 4) == 0) {
			printf("   ");
		}
	}
	printf("\n");
}

/*** Helper Functions *********************************************************/
/**
 * Get the row number in the substitution table for the group of six at 
 * index group_i from the left.  
 */
int get_row(unsigned long *data, int group_i)
{
	int side;
	unsigned long outer_bits;
	if (group_i < 4) {
		side = 0;
	} else {
		group_i -= 4;
		side = 1;
	}
	outer_bits = (data[side] & outer_masks[group_i]) >> (26 - group_i * 6);
	if (outer_bits & BIT27) {
		outer_bits ^= 34;
	}

	return (int) outer_bits;
}

/**
 * Get the column number in the substitution table for the group of six at 
 * index group_i from the left.  
 */
int get_col(unsigned long *data, int group_i)
{
	int side;
	unsigned long inner_bits;
	if (group_i < 4) {
		side = 0;
	} else {
		group_i -= 4;
		side = 1;
	}
	inner_bits = (data[side] & inner_masks[group_i]) >> (27 - group_i * 6);

	return (int) inner_bits;

}
