#include "../dctest.h"
#include "prime.h"
#include <string.h>

PRIME_TEST_DECLARATIONS(dc_bpsw);

int main(int argc, char **argv)
{
	int all = 0;
	char str_all[] = "all";
	if (argc > 1 && !strcmp(str_all, argv[1])) all = 1;

	/* First 100,000 primes (oeis.org) */
	dc_bpsw_set_test();      // Values 0 to 1299709

	/* The Twenty-sixth 1,000,000 Primes (primes.utm.edu) */
	if (all) dc_bpsw_set26_test();    // Values 472882049 to 492876847

	/* same as Miller-Rabin */
	prime_specific_value_tests(dc_bpsw);

	/* Other prime sequences */
	prime_other_tests(dc_bpsw);

	return 0;
}