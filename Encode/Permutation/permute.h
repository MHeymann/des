#ifndef PERMUTE_H
#define PERMUTE_H

/*** Macros *******************************************************************/

#define BIT1	2147483648
#define BIT2	1073741824
#define BIT3	536870912
#define BIT4	268435456
#define BIT5	134217728
#define BIT6	67108864
#define BIT7	33554432
#define BIT8	16777216
#define BIT9	8388608
#define BIT10	4194304
#define BIT11	2097152
#define BIT12	1048576
#define BIT13	524288
#define BIT14	262144
#define BIT15	131072
#define BIT16	65536
#define BIT17	32768
#define BIT18	16384
#define BIT19	8192
#define BIT20	4096
#define BIT21	2048
#define BIT22	1024
#define BIT23	512
#define BIT24	256
#define BIT25	128
#define BIT26	64
#define BIT27	32
#define BIT28	16
#define BIT29	8
#define BIT30	4
#define BIT31	2
#define BIT32	1

#define CHAR_BIT1	128
#define CHAR_BIT2	64
#define CHAR_BIT3	32
#define CHAR_BIT4	16
#define CHAR_BIT5	8
#define CHAR_BIT6	4
#define CHAR_BIT7	2
#define CHAR_BIT8	1

/*** Function Prototypes ******************************************************/

/**
 * The final permutation in the encoding process.
 */
void final_permutation(unsigned long *data_bits, unsigned long *permuted_bits);

/**
 * The initial permutation in the encoding process.
 */
void initial_permutation(unsigned long *data_bits, unsigned long *permuted_bits);

/**
 * Print the 64 bits in data, and put the resultant characters in the
 * memory space pointed to by string.  String may be a null pointer.
 */
void print_bits_permutation(unsigned long *data, char *string);

#endif
