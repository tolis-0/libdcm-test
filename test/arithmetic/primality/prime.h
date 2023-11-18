#ifndef _PRIME_TEST_H
#define _PRIME_TEST_H


#include <stdlib.h>


#define PRIME_TEST_DECLARATIONS(function) \
	SET_TEST_F(function, uint64_t, primes); \
	SET_TEST_FNS(function, uint64_t, primes26, set26, 472882048); \
	\
	FALSE_TEST_FN(function, uint64_t, b001262, str2); \
	FALSE_TEST_FN(function, uint64_t, b020229, str3); \
	FALSE_TEST_FN(function, uint64_t, b020230, str4); \
	FALSE_TEST_FN(function, uint64_t, b020231, str5); \
	FALSE_TEST_FN(function, uint64_t, b020232, str6); \
	FALSE_TEST_FN(function, uint64_t, b020233, str7); \
	FALSE_TEST_FN(function, uint64_t, a074773, str2357); \
	FALSE_TEST_FN(function, uint64_t, b013998, perrin); \
	FALSE_TEST_FN(function, uint64_t, b047713, euler_j); \
	FALSE_TEST_FN(function, uint64_t, b052155, fmt23); \
	FALSE_TEST_FN(function, uint64_t, b083737, fmt235); \
	FALSE_TEST_FN(function, uint64_t, b158358, fmt2nsq); \
	FALSE_TEST_FN(function, uint64_t, b057942, ps2k2); \
	\
	TRUE_TEST_FN(function, uint64_t, b049002, p2_2); \
	TRUE_TEST_FN(function, uint64_t, b056130, palb24); \
	TRUE_TEST_FN(function, uint64_t, b272061, sigtp); \
	TRUE_TEST_FN(function, uint64_t, b077798, palwing); \
	TRUE_TEST_FN(function, uint64_t, b005109, pierpont); \
	TRUE_TEST_FN(function, uint64_t, b037896, k4_1); \
	\
	TRUE_TEST_FN(function, uint64_t, corner_prime, cc_prime); \
	FALSE_TEST_FN(function, uint64_t, corner_composite, cc_comp);


#define pseudoprime_tests(function) \
	do { \
		function##_str2_test();     /* Strong pseudoprimes base 2 */ \
		function##_str3_test();     /* Strong pseudoprimes base 3 */ \
		function##_str4_test();     /* Strong pseudoprimes base 4 */ \
		function##_str5_test();     /* Strong pseudoprimes base 5 */ \
		function##_str6_test();     /* Strong pseudoprimes base 6 */ \
		function##_str7_test();     /* Strong pseudoprimes base 7 */ \
		function##_str2357_test();  /* Strong pseudoprimes base 2, 3, 5 and 7 */ \
		function##_perrin_test();   /* Unrestricted Perrin pseudoprimes */ \
		function##_euler_j_test();  /* Euler-Jacobi pseudoprimes */ \
		function##_fmt23_test();    /* Fermat pseudoprimes base 2 and 3 */ \
		function##_fmt235_test();   /* Fermat pseudoprimes base 2, 3 and 5 */ \
		function##_fmt2nsq_test();  /* Non squarefree Fermat pseudoprimes base 2 */ \
		function##_ps2k2_test();    /* Pseudoprimes base 2 with prime k-2, k+2 */ \
	} while (0)


#define prime_corner_case_tests(function) \
	do { \
		function##_cc_prime_test(); /* Other corner cases (primes) */ \
		function##_cc_comp_test();  /* Other corner cases (composites) */ \
	} while (0)


#define prime_other_tests(function) \
	do { \
		function##_p2_2_test();     /* A049002 (oeis.org) */ \
		function##_palb24_test();   /* A056130 (oeis.org) */ \
		function##_sigtp_test();    /* A272061 (oeis.org) */ \
		function##_palwing_test();  /* A077798 (oeis.org) */ \
		function##_pierpont_test(); /* A005109 (oeis.org) */ \
		function##_k4_1_test();     /* A037896 (oeis.org) */ \
	} while (0)


#define PRIME_PERFORMANCE_DECLARATIONS(func) \
	void func##_performance (uint64_t total, uint32_t bits) { \
		uint64_t i, *input, __attribute__((unused)) a; \
		clock_t start, end; \
		\
		set_rand(); \
		input = malloc(total * sizeof(uint64_t)); \
		\
		for (i = 0; i < total; i++) \
			input[i] = (rand_bit(bits) | 1); \
		\
		start = clock(); \
		for (i = 0; i < total; i++) \
			a = func(input[i]); \
		end = clock(); \
		free(input); \
		\
		printf("%lf (seconds) (" _to_string(func) " %"PRIu32"bit)\n", \
			(double) (end - start)/CLOCKS_PER_SEC, bits); \
	} \
	\
	void func##_p_performance (uint64_t total, uint32_t bits) { \
		uint64_t i, *input, __attribute__((unused)) a; \
		clock_t start, end; \
		\
		if (bits < 2) { \
			fprintf(stderr, "There is no prime with %u bits\n", bits); \
			return; \
		} \
		\
		set_rand(); \
		input = malloc(total * sizeof(uint64_t)); \
		\
		for (i = 0; i < total; i++) { \
			do { \
				input[i] = (rand_bit(bits) | 1); \
			} while (!func(input[i])); \
		} \
		\
		start = clock(); \
		for (i = 0; i < total; i++) \
			a = func(input[i]); \
		end = clock(); \
		free(input); \
		\
		printf("%lf (seconds) (" _to_string(func) " %"PRIu32"bit)\n", \
			(double) (end - start)/CLOCKS_PER_SEC, bits); \
	} \


#endif // _PRIME_TEST_H