#include "../dctest.h"
#include "prime.h"
#include <string.h>

PRIME_TEST_DECLARATIONS(dc_prime);
PRIME_PERFORMANCE_DECLARATIONS(dc_prime);

int main(int argc, char **argv)
{
	test_arguments_setup();

	mandatory_tests {
		dc_prime_set_test();      // Values 0 to 1299709
		pseudoprime_tests(dc_prime);
		prime_corner_case_tests(dc_prime);
		prime_other_tests(dc_prime);
	}

	extra_tests {
		dc_prime_set26_test();    // Values 472882049 to 492876847
	}

	perf_tests {
		for (int i = 1; i <= 64; i++)
			dc_prime_performance(100000, i);
	}

	return 0;
}