#include "../../dctest.h"
#include "../../gmptest.h"
#include "prime.h"
#include <string.h>


PRIME_TEST_DECLARATIONS(dc_prime);
PRIME_PERFORMANCE_DECLARATIONS(dc_prime);

GMP_TEST_BEGIN(dc_prime, 0b10100)
expected = mpz_probab_prime_p(gmp_a, 25);
if (expected == 2) expected = 1;
r = dc_prime(a);
GMP_TEST_END(dc_prime, 0b10100)


int main(int argc, char **argv)
{
	int i;
	test_arguments_setup();

	mandatory_tests {
		dc_prime_set_test();      // Values 0 to 1299709
		pseudoprime_tests(dc_prime);
		prime_corner_case_tests(dc_prime);
		prime_other_tests(dc_prime);
	}

	extra_tests {
		dc_prime_set26_test();    // Values 472882049 to 492876847
		for (int i = 20; i <= 64; i++)
			dc_prime_gmp_test(10000000, i, 0);
	}

	perf_tests {
		for (int i = 1; i <= 64; i++)
			dc_prime_performance(100000, i);
	}

	return 0;
}