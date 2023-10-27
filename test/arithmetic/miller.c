#include "../dctest.h"
#include "prime.h"
#include <string.h>

PRIME_TEST_DECLARATIONS(dc_miller);

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
	}

	return 0;
}