#ifndef _GMPTEST_H
#define _GMPTEST_H

#include <gmp.h>

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wunused-variable"

/*
 *	Function Description:
 *
 *	form 0bABCD (binary number)
 *	AB:	number of standard inputs (a, b, c)
 *	C:	division/modulo input (m)
 *	D:	extra output (r2)
*/

#define GMP_TEST_BEGIN(func, desc) \
	void func##_gmp_test (int total, uint32_t bits, uint32_t div_bits) { \
		int i, j, n = 100, passed; \
		uint64_t a, b, c, m, r, r2, expected, expected2; \
		mpz_t gmp_a, gmp_b, gmp_c, gmp_m, gmp_r, gmp_r2; \
		char input[100]; \
		\
		set_rand(); \
		mpz_init(gmp_a); \
		dsc_msk(desc, 0b1000) mpz_init(gmp_b); \
		dsc_msk(desc, 0b1100) mpz_init(gmp_c); \
		dsc_msk(desc, 0b0010) mpz_init(gmp_m); \
		mpz_init(gmp_r); \
		dsc_msk(desc, 0b0001) mpz_init(gmp_r2); \
		\
		for (i = 0, passed = 0; i < total; i++) { \
			a = rand_bit(bits); \
			dsc_msk(desc, 0b1000) b = rand_bit(bits); \
			dsc_msk(desc, 0b1100) c = rand_bit(bits); \
			dsc_msk(desc, 0b0010) do { \
				m = rand_bit(div_bits); \
			} while (m == 0); \
			\
			mpz_set_ui(gmp_a, a); \
			dsc_msk(desc, 0b1000) mpz_set_ui(gmp_b, b); \
			dsc_msk(desc, 0b1100) mpz_set_ui(gmp_c, c); \
			dsc_msk(desc, 0b0010) mpz_set_ui(gmp_m, m);


#define GMP_TEST_END(func, desc) \
			if (!(desc & 0b10000)) expected = mpz_get_ui(gmp_r); \
			dsc_msk(desc, 0b0001) expected2 = mpz_get_ui(gmp_r2); \
			j = snprintf(input, n, "%"PRIu64, a), n = 100 - j; \
			dsc_msk(desc, 0b1000) \
				j += snprintf(input + j, n, ", %"PRIu64, b), n = 100 - j; \
			dsc_msk(desc, 0b1100) \
				j += snprintf(input + j, n, ", %"PRIu64, c), n = 100 - j; \
			dsc_msk(desc, 0b0010) \
				j += snprintf(input + j, n, ", %"PRIu64, m), n = 100 - j; \
			_test_check(string, uint64_t, input, expected, r); \
		} \
		\
		_print_test_result2(func, gmp, i, passed, \
			" %3$"PRIu32"bit %4$"PRIu32"divbit", bits, div_bits); \
		mpz_clear(gmp_a); \
		dsc_msk(desc, 0b1000) mpz_clear(gmp_b); \
		dsc_msk(desc, 0b1100) mpz_clear(gmp_c); \
		dsc_msk(desc, 0b0010) mpz_clear(gmp_m); \
		mpz_clear(gmp_r); \
		dsc_msk(desc, 0b0001) mpz_clear(gmp_r2); \
	}


#endif // _GMPTEST_H
