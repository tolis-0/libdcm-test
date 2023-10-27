#ifndef _GMPTEST_H
#define _GMPTEST_H

#include <gmp.h>

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wunused-variable"

#define GMP_TEST_BEGIN(func) \
	void func##_gmp_test (int total, uint32_t bits, uint32_t div_bits) { \
		int i, passed; \
		uint64_t a, b, c, m, r, r2, expected, expected2; \
		mpz_t gmp_a, gmp_b, gmp_c, gmp_m, gmp_r, gmp_r2; \
		char input[100]; \
		\
		set_rand(); \
		mpz_init(gmp_a); mpz_init(gmp_b); \
		mpz_init(gmp_c); mpz_init(gmp_m); \
		mpz_init(gmp_r); mpz_init(gmp_r2); \
		\
		for (i = 0, passed = 0; i < total; i++) { \
			a = rand_bit(bits); \
			b = rand_bit(bits); \
			c = rand_bit(bits); \
			do { \
				m = rand_bit(div_bits); \
			} while (m == 0); \
			\
			mpz_set_ui(gmp_a, a); \
			mpz_set_ui(gmp_b, b); \
			mpz_set_ui(gmp_c, c); \
			mpz_set_ui(gmp_m, m);


#define GMP_TEST_END(func) \
			expected = mpz_get_ui(gmp_r); \
			expected2 = mpz_get_ui(gmp_r2); \
			snprintf(input, 100, "%"PRIu64", %"PRIu64", %"PRIu64", %"PRIu64, a, b, c, m); \
			_test_check(string, uint64_t, input, expected, r); \
		} \
		\
		_print_test_result2(func, gmp, i, passed, " %3$"PRIu32"bit %4$"PRIu32"divbit", bits, div_bits); \
		mpz_clear(gmp_a); mpz_clear(gmp_b); \
		mpz_clear(gmp_c); mpz_clear(gmp_m); \
		mpz_clear(gmp_r); mpz_clear(gmp_r2); \
	}


#endif // _GMPTEST_H
