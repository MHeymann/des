#ifndef KEYS_H
#define KEYS_H

/*** **************************************************************************/

/*** **************************************************************************/

#define BIT1	1
#define BIT2	2
#define BIT3	4
#define BIT4	8
#define BIT5	16
#define BIT6	32
#define BIT7	64
#define BIT8	128
#define BIT29	268435456


/*** **************************************************************************/
void get_subkeys(void *key, void **subkeys);
void **alloc_subkeys();
void free_subkeys(void **subkeys);

#endif
