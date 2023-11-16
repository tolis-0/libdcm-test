#include "../../dctest.h"
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>


void dc_sqrt_test(int total, uint32_t bits);

PERFORMANCE_TEST_BEGIN(dc_sqrt,	u,x,x, x, u,x,x)
r = dc_sqrt(a[i]);
PERFORMANCE_TEST_END(dc_sqrt,	u,x,x, x, u,x,x)


int main (int argc, char **argv)
{
	int i;
	test_arguments_setup();

	quick_tests {
		for (i = 4; i <= 64; i++)
			dc_sqrt_test(100000, i);
	}

	extra_tests {
		for (i = 4; i <= 64; i++)
			dc_sqrt_test(10000000, i);
	}

	perf_tests {
		for (i = 1; i <= 64; i++)
			dc_sqrt_perf_test(1000000, i);
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
