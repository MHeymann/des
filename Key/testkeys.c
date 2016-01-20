#include <stdio.h>
#include <stdlib.h>

#include "keys.h"

int main(int argc, char *argv[]) 
{
	unsigned char *testkey_pt;
	void **subkeys;
	
	subkeys = alloc_subkeys(); 
	if (!subkeys) {
		fprintf(stderr, "Memory error!\n");
		return 1;
	}
	
	testkey_pt = malloc(8 * sizeof(char));
	if (!testkey_pt) {
		free_subkeys(subkeys);
	}
	testkey_pt[0] = 19;
	testkey_pt[1] = 52;
	testkey_pt[2] = 87;
	testkey_pt[3] = 121;
	testkey_pt[4] = 155;
	testkey_pt[5] = 188;
	testkey_pt[6] = 223;
	testkey_pt[7] = 241;

	get_subkeys(testkey_pt, subkeys);
	print_subkeys(subkeys);
	free_subkeys(subkeys);

	return 0;
}
