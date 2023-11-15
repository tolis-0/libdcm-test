#ifndef _GMPTEST_H
#define _GMPTEST_H

#include <gmp.h>



#define u_tvar_use 1
#define s_tvar_use 1
#define x_tvar_use 0
#define b_tvar_use 1

#define u_tvar_arg(x) , x
#define s_tvar_arg(x) , x
#define x_tvar_arg(x)
#define b_tvar_arg(x) , x

#define u_tvar_prt(x) x "%"PRIu64
#define s_tvar_prt(x) x "%"PRId64
#define x_tvar_prt(x) ""
#define b_tvar_prt(x) x "%d"

#define u_tvar_mpz mpz_t
#define s_tvar_mpz mpz_t
#define x_tvar_mpz __attribute__((unused)) mpz_t
#define b_tvar_mpz mpz_t

#define u_tvar_int uint64_t
#define s_tvar_int int64_t
#define x_tvar_int __attribute__((unused)) uint64_t
#define b_tvar_int int


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
			if (_a##_tvar_use) mpz_set_ui(gmp_a, a); \
			if (_b##_tvar_use) mpz_set_ui(gmp_b, b); \
			if (_c##_tvar_use) mpz_set_ui(gmp_c, c); \
			if (_m##_tvar_use) mpz_set_ui(gmp_m, m);


#define GMP_TEST_END(func, _a, _b, _c, _m, _r, _r1, _r2, r_exp) \
			if (!r_exp) expected = mpz_get_ui(gmp_r); \
			if (_r1##_tvar_use) expected1 = mpz_get_ui(gmp_r1); \
			if (_r2##_tvar_use) expected2 = mpz_get_ui(gmp_r2); \
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
		_print_test_result2(func, gmp, i, passed, \
			" %3$"PRIu32"bit %4$"PRIu32"divbit", bits, div_bits); \
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
