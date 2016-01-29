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
/**
 * Encrypt 64 bits of data using the sixteen subkeys provided, putting the
 * encrypted data into encoded.
 */
void encode(unsigned long **subkeys, unsigned long *data, unsigned long *encoded)
{
	unsigned long encoding_bits[] = {0, 0};
	int i;
	unsigned long temp;
	
	/* initial permutation before sixteen rounds */
	initial_permutation(data, encoding_bits);

	/* 
	 * sixteend rounds of swapping halves and XOR'ing with Feistel function 
	 * output
	 */
	for (i = 0; i < 16; i++) {
		temp = encoding_bits[LEFT] ^ feistel(&encoding_bits[RIGHT], subkeys[i]);
		encoding_bits[LEFT] =encoding_bits[RIGHT];
		encoding_bits[RIGHT] = temp;
	}

	/*
	 * Swap halves.
	 */
	temp = encoding_bits[LEFT];
	encoding_bits[LEFT] = encoding_bits[RIGHT];
	encoding_bits[RIGHT] = temp;

	/*
	 * Final permutation in encoding process.
	 */
	final_permutation((unsigned long *)encoding_bits, encoded);
}

/**
 * Decrypt 64 bits of data using the sixteen subkeys provided, putting the
 * decrypted data into decoded.
 */
void decode(unsigned long **subkeys, unsigned long *data, unsigned long *decoded)
{
	unsigned long decoding_bits[] = {0, 0};
	int i;
	unsigned long temp;
	
	/* initial permutation before sixteen rounds */
	initial_permutation(data, decoding_bits);

	/* 
	 * sixteend rounds of swapping halves and XOR'ing with Feistel function 
	 * output.  Keys are applied in reverse order from what they were during
	 * encryption.  
	 */
	for (i = 15; i >= 0; i--) {
		temp = decoding_bits[LEFT] ^ feistel(&decoding_bits[RIGHT], subkeys[i]);
		decoding_bits[LEFT] = decoding_bits[RIGHT];
		decoding_bits[RIGHT] = temp;
	}

	/*
	 * Swap halves
	 */
	temp = decoding_bits[LEFT];
	decoding_bits[LEFT] = decoding_bits[RIGHT];
	decoding_bits[RIGHT] = temp;

	/*
	 * Final permutation in decoding process.
	 */
	final_permutation((unsigned long *)decoding_bits, decoded);

}

/*** helper functions *********************************************************/


