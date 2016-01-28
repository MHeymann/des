#include <stdio.h>

#include "encode.h"
#include "Permutation/permute.h"
#include "Feistel/feistel.h"

/*** Macros *******************************************************************/

#define LEFT	0
#define RIGHT	1


/*** global static variables **************************************************/


/*** helper function prototypes ***********************************************/


/*** functions ****************************************************************/

void encode(unsigned long **subkeys, unsigned long *data, unsigned long *encoded)
{
	unsigned long encoding_bits[] = {0, 0};
	int i;
	unsigned long temp;
	
	printf("data to encode:\t");
	print_bits_permutation((unsigned long *)data, NULL);
	printf("\n");
	initial_permutation(data, encoding_bits);

	for (i = 0; i < 16; i++) {
		temp = encoding_bits[LEFT] ^ feistel(&encoding_bits[RIGHT], subkeys[i]);
		encoding_bits[LEFT] =encoding_bits[RIGHT];
		encoding_bits[RIGHT] = temp;
	}

	temp = encoding_bits[LEFT];
	encoding_bits[LEFT] = encoding_bits[RIGHT];
	encoding_bits[RIGHT] = temp;


	final_permutation((unsigned long *)encoding_bits, encoded);
	printf("data encoded:\t");
	print_bits_permutation((unsigned long *)encoded, NULL);
	printf("\n");

}

void decode(unsigned long **subkeys, unsigned long *data, unsigned long *decoded)
{
	unsigned long decoding_bits[] = {0, 0};
	int i;
	unsigned long temp;
	
	printf("data to decode:\t");
	print_bits_permutation((unsigned long *)data, NULL);
	printf("\n");
	initial_permutation(data, decoding_bits);

	for (i = 15; i >= 0; i--) {
		temp = decoding_bits[LEFT] ^ feistel(&decoding_bits[RIGHT], subkeys[i]);
		decoding_bits[LEFT] = decoding_bits[RIGHT];
		decoding_bits[RIGHT] = temp;
	}

	temp = decoding_bits[LEFT];
	decoding_bits[LEFT] = decoding_bits[RIGHT];
	decoding_bits[RIGHT] = temp;

	final_permutation((unsigned long *)decoding_bits, decoded);
	printf("after decoding:\t");
	print_bits_permutation((unsigned long *)decoded, NULL);
	printf("\n");

}



/*** helper functions *********************************************************/


