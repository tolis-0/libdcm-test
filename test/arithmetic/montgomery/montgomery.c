#include "../../dctest.h"
#include <string.h>
#include <time.h>


void dc_montgomery_test (uint8_t k, int total, int bits);


int main (int argc, char **argv)
{
	int i;
	test_arguments_setup();

	quick_tests {
		for (i = 1; i <= 64; i++)
			dc_montgomery_test(64, 100000, i);
	}

	extra_tests {
		for (i = 1; i <= 64; i++)
			dc_montgomery_test(64, 2500000, i);
	}

	perf_tests {

	}

	return 0;
}


void dc_montgomery_test (uint8_t k, int total, int bits)
{
	int i, passed;
	uint64_t R, N, Ninv, R_exp, outp, mask;

	if (k == 64) {
		mask = 0xFFFFFFFFFFFFFFFF;
	} else {
		mask = (1ULL << k) - 1;
	}

	for (passed = i = 0; i < total; i++) {

		N = (rand_bit(bits) | 1);

		if (k == 64) R_exp = (-N) % N;
		else R_exp = (1ULL << k) % N;

		Ninv = dc_montgomery(k, N, &R);

		outp = (Ninv * N + 1) & mask;

		if (outp != 0) {
			printf("At N:%"PRIu64", N':%"PRIu64
					": Expected (N*N'+1) mod 2^%"PRIu8
					":0. Got %"PRIu64"\n",
					N, Ninv, k, outp);
		} else if (R != R_exp) {
			printf("At N:%"PRIu64", N':%"PRIu64
					": Expected R:%"PRIu64
					". Got %"PRIu64"\n",
					N, Ninv, R_exp, R);
		} else {
			passed++;
		}
	}

	_print_test_result2(montgomery,, i, passed,
		" bits:%3$d", bits);
}