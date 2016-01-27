#include <stdio.h>

#include "feistel.h"
#include "Expansion/expand.h"
#include "Substitution/substitution.h"

/*** Macros *******************************************************************/

/*
 * No new macros required
 */

/*** Static Global Variables **************************************************/

/*
 * The table defining the feistel permutation
 */
static int feistel_IP[] = {
	16,   7,  20,  21,
	29,  12,  28,  17,
	 1,  15,  23,  26,
	 5,  18,  31,  10,
	 2,   8,  24,  14,
	32,  27,   3,   9,
	19,  13,  30,   6,
	22,  11,   4,  25
};

/*
 * Bitmasks for addressing individual bits through bitwise operations.
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

/*** Helper Function Prototypes ***********************************************/

void feistel_permute(unsigned long bits, unsigned long *target_space);

/*** Functions ****************************************************************/
/**
 * The feistel function, taking R as 32 bit right side of previous iteration, 
 * expanding it and applying the XOR bitwise operation to it and the relevant 
 * subkey, applying the S-boxes to the result and finally applying the
 * permutation function relevant to Feiste.  The 32 bit value is returned.  
 */
unsigned long feistel(unsigned long *R, unsigned long *subkey)
{
	unsigned long expanded[2] = {0, 0};
	unsigned long ret_val = 0;
#ifdef VERBOSE
	printf("\n\x1b[1;35mfeistel\x1b[0m\n");
	printf("\nRight side bits:\n");
	printf("before expanding:\t");
	print_original_bits(R, NULL);
	printf("\n");
#endif

	/* expand to 48 bits */
	expand(R, (unsigned long *)expanded);	
	
#ifdef VERBOSE
	printf("after expanding:\t");
	print_expanded_bits((unsigned long *)expanded, NULL);	
	printf("\n");

	printf("subkey: \t\t");
	print_expanded_bits((unsigned long *)subkey, NULL);	
	printf("\n");
#endif

	/* XOR With Subkey */
	expanded[0] ^= subkey[0];
	expanded[1] ^= subkey[1];

#ifdef VERBOSE
	printf("after XOR:\t\t");
	print_expanded_bits((unsigned long *)expanded, NULL);	
	printf("\n");
#endif

	/* Apply subsitution boxes */
	substitute((unsigned long *)expanded, &ret_val); 

#ifdef VERBOSE
	printf("after substitution:\t");
	print_original_bits(&ret_val, NULL);
	printf("\n");
#endif

	/* Feistel permutation */
	feistel_permute(ret_val, &ret_val);	

#ifdef VERBOSE
	printf("after permutation:\t");
	print_original_bits(&ret_val, NULL);
	printf("\n");
#endif

#ifdef VERBOSE
	printf("\n\x1b[1;35m\\feistel\x1b[0m\n\n");
#endif

	/* some code */
	return ret_val;
}
/*** Helper Functions *********************************************************/

/**
 * The feistel permutation
 */
void feistel_permute(unsigned long bits, unsigned long *target_space)
{
	int i;
	int bit_no;
	*target_space = 0;
	for (i = 0; i < 32; i++) {
		bit_no = feistel_IP[i];
		if (bits & bitmasks[bit_no]) {
			*target_space ^= bitmasks[i + 1];
		}
	}	
}
