#include <stdint.h>
#include <gmp.h>
#include "../dctest.h"

#define MODULAR_GMP_BEGIN(func) \
	void func##_gmp_test (int total, uint32_t bits) { \
		int i, passed; \
		uint64_t a, b, m, output, expected; \
		mpz_t gmp_a, gmp_b, gmp_m, gmp_r; \
		char input[70]; \
		\
		set_rand(); \
		mpz_init(gmp_a); \
		mpz_init(gmp_b); \
		mpz_init(gmp_m); \
		mpz_init(gmp_r); \
		\
		for (i = 0, passed = 0; i < total; i++) { \
			a = rand_bit(64); \
			b = rand_bit(64); \
			do { \
				m = rand_bit(bits); \
			} while (m == 0); \
			\
			mpz_set_ui(gmp_a, a); \
			mpz_set_ui(gmp_b, b); \
			mpz_set_ui(gmp_m, m);

#define MODULAR_GMP_END(func) \
			expected = mpz_get_ui(gmp_r); \
			snprintf(input, 70, "%"PRIu64", %"PRIu64", %"PRIu64, a, b, m); \
			_test_check(string, uint64_t, input, expected, output); \
		} \
		\
		_print_test_result2(func, gmp, i, passed, " %3$"PRIu32"bit", bits); \
	}


MODULAR_GMP_BEGIN(fast_mul_mod)
mpz_mul(gmp_r, gmp_a, gmp_b);
mpz_mod(gmp_r, gmp_r, gmp_m);
fast_mul_mod(output, a, b, m);
MODULAR_GMP_END(fast_mul_mod)

MODULAR_GMP_BEGIN(mul_mod)
mpz_mul(gmp_r, gmp_a, gmp_b);
mpz_mod(gmp_r, gmp_r, gmp_m);
output = mul_mod(a, b, m);
MODULAR_GMP_END(mul_mod)

MODULAR_GMP_BEGIN(ext_mod)
mpz_powm(gmp_r, gmp_a, gmp_b, gmp_m);
output = ext_mod(a, b, m);
MODULAR_GMP_END(ext_mod)

int main () 
{
	int test;

	for (test = 4; test <= 64; test += 4)
		fast_mul_mod_gmp_test(100000, test);

	for (test = 4; test <= 64; test += 4)
		mul_mod_gmp_test(100000, test);

	for (test = 4; test <= 64; test += 4)
		ext_mod_gmp_test(50000, test);

	return 0;
}
