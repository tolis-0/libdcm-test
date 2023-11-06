#include "../../test/dctest.h"
#include <stdlib.h>
#include <math.h>

void sqrtl_performance (int total, uint32_t bits) {
	int i;
	uint64_t *input;
	clock_t start, end;

	set_rand();
	input = (uint64_t *) malloc(total * sizeof(uint64_t));

	for (i = 0; i < total; i++)
		input[i] = rand_bit(bits);

	start = clock();
	for (i = 0; i < total; i++) {
		volatile uint64_t result = floorl(sqrtl(input[i]));
	}
	end = clock();

	free(input);

	printf("%lf (seconds) (sqrtl %"PRIu32"bit)\n",
		(double) (end - start)/CLOCKS_PER_SEC, bits);
}

int main(int argc, char **argv)
{
	for (int i = 1; i <= 64; i++)
		sqrtl_performance(100000, i);

	return 0;
}
