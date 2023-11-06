#include "../../dctest.h"
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>


#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

void dc_sqrt_test(int total, uint32_t bits);
void sqrt_performance (int total, uint32_t bits);


int main (int argc, char **argv)
{
	int i;
	test_arguments_setup();

	mandatory_tests {
		for (i = 4; i <= 64; i++)
			dc_sqrt_test(100000, i);
	}

	extra_tests {
		for (i = 4; i <= 64; i++)
			dc_sqrt_test(2500000, i);
	}

	perf_tests {
		for (i = 1; i <= 64; i++)
			sqrt_performance(100000, i);
	}

	return 0;
}


void dc_sqrt_test(int total, uint32_t bits)
{
	int i, passed;
	uint64_t input, output, expected;

	set_rand();

	for (passed = i = 0; i < total; i++) {
		input = (rand_bit(bits));

		expected = (uint64_t) floorl(sqrtl(input));
		output = dc_sqrt(input);

		_test_check(uint64_t, uint64_t, input, expected, output);
	}

	_print_test_result2(dc_sqrt, math, i, passed,
		" bits:%3$"PRIu32, bits);
}


void sqrt_performance (int total, uint32_t bits)
{
	int i;
	uint64_t *input, a;
	clock_t start, end;

	set_rand();
	input = (uint64_t *) malloc(total * sizeof(uint64_t));

	for (i = 0; i < total; i++)
		input[i] = (rand_bit(bits));

	start = clock();
	for (i = 0; i < total; i++)
		a = dc_sqrt(input[i]);
	end = clock();
	
	free(input);

	printf("%lf (seconds) (dc_sqrt %"PRIu32"bit)\n",
		(double) (end - start)/CLOCKS_PER_SEC, bits);
}
