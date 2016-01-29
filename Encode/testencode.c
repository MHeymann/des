#include <stdio.h>

#include "encode.h"

int main(int argc, char *argv[]) 
{
	/* some valid keys for testing */
	unsigned long K1[] =    	{453177088, 4235227648};
	unsigned long K2[] =    	{2041501952, 3687441664};
	unsigned long K3[] =    	{1442613760, 1120901376};
	unsigned long K4[] =		{1923995136, 3677691136};
	unsigned long K5[] =		{2095843072, 3948128256};
	unsigned long K6[] =		{1671773696, 1350250240};
	unsigned long K7[] =		{3968120576, 4128816128};
	unsigned long K8[] =		{4153031168, 3241933568};
	unsigned long K9[] =		{3772508928, 3991372032};
	unsigned long K10[] =		{2985510656, 3125169920};
	unsigned long K11[] =		{559928064, 3738404352};
	unsigned long K12[] =		{1970402560, 2489837824};
	unsigned long K13[] =		{2546323712, 2059026688};
	unsigned long K14[] =		{1598273280, 4075239936};
	unsigned long K15[] =		{3213987072, 1027541504};
	unsigned long K16[] =		{3409808128, 236451072};

	unsigned long *subkeys[16];
	unsigned long word[] = {19088743, 2309737967};
	unsigned long target[2] = {0,0};
	unsigned long target2[2] = {0,0};
	int fail = 0;

	subkeys[0] = K1;
	subkeys[1] = K2;
	subkeys[2] = K3;
	subkeys[3] = K4;
	subkeys[4] = K5;
	subkeys[5] = K6;
	subkeys[6] = K7;
	subkeys[7] = K8;
	subkeys[8] = K9;
	subkeys[9] = K10;
	subkeys[10] = K11;
	subkeys[11] = K12;
	subkeys[12] = K13;
	subkeys[13] = K14;
	subkeys[14] = K15;
	subkeys[15] = K16;

	encode((unsigned long **)subkeys, (unsigned long *) word, (unsigned long *)target);
	decode((unsigned long **)subkeys, (unsigned long *) target, (unsigned long *)target2);
	printf("\nencoded:\t%lu %lu", target[0], target[1]);
	printf("\nword:\t\t%lu %lu\ndecoded:\t%lu %lu\n", word[0], word[1], target2[0], target2[1]);

	if (word[0] != target2[0]) {
		printf("\x1b[1;31mFAILED!\nLeft bits of original word and decoded word don't match!\x1b[0m\n");
		fail = 1;
	}
	if (word[1] != target2[1]) {
		printf("\x1b[1;31mFAILED!\nRight bits of original word and decoded word don't match!\x1b[0m\n");
		fail = 1;
	}
	
	if (!fail) {
		printf("\x1b[1;34mPASSED!\x1b[0m\n");
	}

	return 0;
}
