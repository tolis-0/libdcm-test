#include "../dctest.h"
#include "../gmptest.h"
#include "prime.h"
#include <string.h>


PRIME_TEST_DECLARATIONS(dc_miller);

GMP_TEST_BEGIN(dc_miller, 0b10100)
expected = mpz_probab_prime_p(gmp_a, 25);
if (expected == 2) expected = 1;
r = dc_miller(a);
GMP_TEST_END(dc_miller, 0b10100)


int main(int argc, char **argv)
{
	test_arguments_setup();

	mandatory_tests {
		dc_miller_set_test();      // Values 0 to 1299709
		pseudoprime_tests(dc_miller);
		prime_corner_case_tests(dc_miller);
		prime_other_tests(dc_miller);
	}

	extra_tests {
		dc_miller_set26_test();    // Values 472882049 to 492876847
		for (int i = 20; i <= 64; i++)
			dc_miller_gmp_test(10000000, i, 0);
	}

	return 0;
}