#ifndef _GMPTEST_H
#define _GMPTEST_H

#include <gmp.h>


#define gmpt_sprintf_helper(format, ...) \
	do { \
		j += snprintf(buffer + j, n, format, ##__VA_ARGS__); \
		n = 256 - j; \
	} while (0);



#define GMP_TEST_BEGIN(func, _a, _b, _c, _m, _r, _r1, _r2, r_exp) \
	void func##_gmp_test (int total, uint32_t bits, uint32_t div_bits) { \
		int i, passed; \
		\
		_a##_tvar_int a; \
		_b##_tvar_int b; \
		_c##_tvar_int c; \
		_m##_tvar_int m; \
		\
		_r##_tvar_int r, expected; \
		_r1##_tvar_int r1, expected1; \
		_r2##_tvar_int r2, expected2; \
		\
		_a##_tvar_mpz gmp_a; \
		_b##_tvar_mpz gmp_b; \
		_c##_tvar_mpz gmp_c; \
		_m##_tvar_mpz gmp_m; \
		\
		_r##_tvar_mpz gmp_r; \
		_r1##_tvar_mpz gmp_r1; \
		_r2##_tvar_mpz gmp_r2; \
		\
		if ((_m##_tvar_use) && div_bits == 0) { \
			fputs("ERROR: Can't find value for m with 0 div bits", \
				stderr); \
			return; \
		} \
		set_rand(); \
		\
		if (_a##_tvar_use) mpz_init(gmp_a); \
		if (_b##_tvar_use) mpz_init(gmp_b); \
		if (_c##_tvar_use) mpz_init(gmp_c); \
		if (_m##_tvar_use) mpz_init(gmp_m); \
		if (_r##_tvar_use) mpz_init(gmp_r); \
		if (_r1##_tvar_use) mpz_init(gmp_r1); \
		if (_r2##_tvar_use) mpz_init(gmp_r2); \
		\
		for (i = 0, passed = 0; i < total; i++) { \
			if (_a##_tvar_use) a = rand_bit(bits); \
			if (_b##_tvar_use) b = rand_bit(bits); \
			if (_c##_tvar_use) c = rand_bit(bits); \
			if (_m##_tvar_use) do { \
				m = rand_bit(div_bits); \
			} while (m == 0); \
			\
			if (_a##_tvar_use) _a##_tvar_mpz_f(set)(gmp_a, a); \
			if (_b##_tvar_use) _b##_tvar_mpz_f(set)(gmp_b, b); \
			if (_c##_tvar_use) _c##_tvar_mpz_f(set)(gmp_c, c); \
			if (_m##_tvar_use) _m##_tvar_mpz_f(set)(gmp_m, m);


#define GMP_TEST_END(func, _a, _b, _c, _m, _r, _r1, _r2, r_exp) \
			if (!r_exp) expected = _r##_tvar_mpz_f(get)(gmp_r); \
			if (_r1##_tvar_use) \
				expected1 = _r1##_tvar_mpz_f(get)(gmp_r1); \
			if (_r2##_tvar_use) \
				expected2 = _r2##_tvar_mpz_f(get)(gmp_r2); \
			\
			if ((expected == r) && \
				((_r1##_tvar_use) ? (expected1 == r1) : 1) && \
				((_r2##_tvar_use) ? (expected2 == r2) : 1)) { \
				passed++; \
			} else { \
				printf("At " \
					_a##_tvar_prt() \
					_b##_tvar_prt(",") \
					_c##_tvar_prt(",") \
					_m##_tvar_prt(",") \
					": Expected " \
					_r##_tvar_prt() \
					_r1##_tvar_prt(",") \
					_r2##_tvar_prt(",") \
					". Got " \
					_r##_tvar_prt() \
					_r1##_tvar_prt(",") \
					_r2##_tvar_prt(",") \
					"\n" \
					_a##_tvar_arg(a) \
					_b##_tvar_arg(b) \
					_c##_tvar_arg(c) \
					_m##_tvar_arg(m) \
					_r##_tvar_arg(expected) \
					_r1##_tvar_arg(expected1) \
					_r2##_tvar_arg(expected2) \
					_r##_tvar_arg(r) \
					_r1##_tvar_arg(r1) \
					_r2##_tvar_arg(r2) \
					); \
			} \
		} \
		\
		if (div_bits == 0) { \
			_print_test_result2(func, gmp, i, passed, \
				" %3$"PRIu32"bit", bits); \
		} else { \
			_print_test_result2(func, gmp, i, passed, \
				" %3$"PRIu32"bit %4$"PRIu32"divbit", bits, div_bits); \
		} \
		\
		if (_a##_tvar_use) mpz_clear(gmp_a); \
		if (_b##_tvar_use) mpz_clear(gmp_b); \
		if (_c##_tvar_use) mpz_clear(gmp_c); \
		if (_m##_tvar_use) mpz_clear(gmp_m); \
		if (_r##_tvar_use) mpz_clear(gmp_r); \
		if (_r1##_tvar_use) mpz_clear(gmp_r1); \
		if (_r2##_tvar_use) mpz_clear(gmp_r2); \
	}


#endif // _GMPTEST_H
