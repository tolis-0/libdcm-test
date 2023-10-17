#ifndef _PRIME_TEST_H
#define _PRIME_TEST_H


#define PRIME_TEST_DECLARATIONS(function) \
	SET_TEST_F(function, uint64_t, primes); \
	SET_TEST_FNS(function, uint64_t, primes26, set26, 472882048); \
	\
	FALSE_TEST_FN(function, uint64_t, b001262, str2); \
	FALSE_TEST_FN(function, uint64_t, b020229, str3); \
	FALSE_TEST_FN(function, uint64_t, b020231, str5); \
	FALSE_TEST_FN(function, uint64_t, b020233, str7); \
	FALSE_TEST_FN(function, uint64_t, a074773, str2357); \
	TRUE_TEST_FN(function, uint64_t, corner_prime, cc_prime); \
	FALSE_TEST_FN(function, uint64_t, corner_composite, cc_comp); \
	\
	TRUE_TEST_FN(function, uint64_t, b049002, p2_2); \
	TRUE_TEST_FN(function, uint64_t, b056130, palb24); \
	TRUE_TEST_FN(function, uint64_t, b272061, sigtp);


#define prime_specific_value_tests(function) \
	function##_str2_test();     /* Strong pseudoprimes base 2 */ \
	function##_str3_test();     /* Strong pseudoprimes base 2 */ \
	function##_str5_test();     /* Strong pseudoprimes base 2 */ \
	function##_str7_test();     /* Strong pseudoprimes base 2 */ \
	function##_str2357_test();  /* Strong pseudoprimes base 2, 3, 5 and 7 */ \
	function##_cc_prime_test(); /* Other corner cases (primes) */ \
	function##_cc_comp_test();  /* Other corner cases (composites) */


#define prime_other_tests(function) \
	function##_p2_2_test();   /* A049002 (oeis.org) */ \
	function##_palb24_test(); /* A056130 (oeis.org) */ \
	function##_sigtp_test();  /* A272061 (oeis.org) */


#endif // _PRIME_TEST_H