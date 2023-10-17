#include "../dctest.h"
#include <string.h>

SET_TEST_F(dc_miller, uint64_t, primes);
SET_TEST_FNS(dc_miller, uint64_t, primes26, set26, 472882048);

FALSE_TEST_FN(dc_miller, uint64_t, b001262, str2);
FALSE_TEST_FN(dc_miller, uint64_t, b020229, str3);
FALSE_TEST_FN(dc_miller, uint64_t, b020231, str5);
FALSE_TEST_FN(dc_miller, uint64_t, b020233, str7);
FALSE_TEST_FN(dc_miller, uint64_t, a074773, str2357);
TRUE_TEST_FN(dc_miller, uint64_t, corner_prime, cc_prime);
FALSE_TEST_FN(dc_miller, uint64_t, corner_composite, cc_comp);

TRUE_TEST_FN(dc_miller, uint64_t, b049002, p2_2);
TRUE_TEST_FN(dc_miller, uint64_t, b056130, palb24);
TRUE_TEST_FN(dc_miller, uint64_t, b272061, sigtp);


int main(int argc, char **argv)
{
	int all = 0;
	char str_all[] = "all";
	if (argc > 1 && !strcmp(str_all, argv[1])) all = 1;

	/* First 100,000 primes (oeis.org) */
	dc_miller_set_test();      // Values 0 to 1299709

	/* The Twenty-sixth 1,000,000 Primes (primes.utm.edu) */
	if (all) dc_miller_set26_test();    // Values 472882049 to 492876847 

	/* Specific primes for Miller-Rabin */
	dc_miller_str2_test();     // Strong pseudoprimes base 2
	dc_miller_str3_test();     // Strong pseudoprimes base 2
	dc_miller_str5_test();     // Strong pseudoprimes base 2
	dc_miller_str7_test();     // Strong pseudoprimes base 2
	dc_miller_str2357_test();  // Strong pseudoprimes base 2, 3, 5 and 7
	dc_miller_cc_prime_test(); // Other corner cases (primes)
	dc_miller_cc_comp_test();  // Other corner cases (composites)

	/* Other prime sequences */
	dc_miller_p2_2_test();     // A049002 (oeis.org)
	dc_miller_palb24_test();   // A056130 (oeis.org)
	dc_miller_sigtp_test();    // A272061 (oeis.org)

	return 0;
}