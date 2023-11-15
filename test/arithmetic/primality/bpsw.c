#include "../../dctest.h"
#include "../../gmptest.h"
#include "prime.h"
#include <string.h>


PRIME_TEST_DECLARATIONS(dc_bpsw);
PRIME_PERFORMANCE_DECLARATIONS(dc_bpsw);

GMP_TEST_BEGIN(dc_bpsw,		u,x,x, x, b,x,x, 1)
expected = mpz_probab_prime_p(gmp_a, 25);
if (expected == 2) expected = 1;
r = dc_bpsw(a);
GMP_TEST_END(dc_bpsw,		u,x,x, x, b,x,x, 1)


int main(int argc, char **argv)
{
	int i, perf_test_p = 0;
	test_arguments_setup();

	if (argc > 2) {
		if (!strcmp("p", argv[2])) perf_test_p = 1;
	}

	mandatory_tests {
		dc_bpsw_set_test();      // Values 0 to 1299709
		pseudoprime_tests(dc_bpsw);
		prime_corner_case_tests(dc_bpsw);
		prime_other_tests(dc_bpsw);
	}

	quick_tests {
		for (i = 20; i <= 64; i += 8)
			dc_bpsw_gmp_test(100000, i, 0);
		dc_bpsw_gmp_test(100000, 64, 0);
	}

	extra_tests {
		dc_bpsw_set26_test();    // Values 472882049 to 492876847
		for (int i = 20; i <= 64; i++)
			dc_bpsw_gmp_test(10000000, i, 0);
	}

	perf_tests {
		if (perf_test_p) {
			for (i = 2; i <= 64; i++)
				dc_bpsw_p_performance(100000, i);
		} else {
			for (i = 1; i <= 64; i++)
				dc_bpsw_performance(100000, i);
		}
	}

	return 0;
}
