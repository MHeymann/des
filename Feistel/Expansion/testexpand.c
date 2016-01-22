#include "expand.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	unsigned long *space = alloc_expand_space();
	unsigned char *testdata = malloc(4 * sizeof(char));

	testdata[0] = 240;
	testdata[1] = 170;
	testdata[2] = 240;
	testdata[3] = 170;

	print_original_bits((unsigned long *)testdata);
	expand((unsigned long *)testdata, space);
	print_expanded_bits(space);

	free_expanded_space(space);
	free(testdata);

	return 0;
}
