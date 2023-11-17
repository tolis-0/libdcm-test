#include "../../dctest.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>


void dc_montgomery_gcd_test (int total, uint32_t bits);


int main (int argc, char **argv)
{
	int i;
	test_arguments_setup();

	quick_tests {
		for (i = 1; i <= 64; i++)
			dc_montgomery_gcd_test(100000, i);
	}

	extra_tests {
		for (i = 1; i <= 64; i++)
			dc_montgomery_gcd_test(2500000, i);
	}

	perf_tests {

	}

	return 0;
}


void dc_montgomery_gcd_test (int total, uint32_t bits)
{
	int i, passed;
	uint64_t high, low, n;
	int64_t s, t, output;
	__int128 calc;

	set_rand();

	for (passed = i = 0; i < total; i++) {
		n = (rand_bit(bits) | 1);

		dc_montgomery_gcd(n, &s, &t);

		calc = ((__int128) s << 64) - ((__int128) t * n);
		output = (int64_t) calc;

		if (output == 1) {
				passed++;
		} else {
			high = (uint64_t) (calc >> 64);
			low = (uint64_t) (calc);
			printf("At %" PRIu64 ": Expected s * 2^64 - t * n = 1"
					". Got %" PRId64 ", %" PRId64 " = %lx%lx\n",
					n, s, t, high, low);
		}
	}

	_print_test_result2(dc_montgomery_gcd,, i, passed,
		" bits:%3$"PRIu32, bits);
}
