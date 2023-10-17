#include <stdint.h>
#include <gmp.h>
#include "../dctest.h"

#define PRIME_GMP_TEST(func) \
	void func##_gmp_test (int total, uint32_t bits) { \
		int i, passed, output, expected; \
		uint64_t input; \
		mpz_t gmp_input; \
		\
		set_rand(); \
		mpz_init(gmp_input); \
		\
		for (i = 0, passed = 0; i < total; i++) { \
			input = rand_bit(bits); \
			input |= 1; \
			mpz_set_ui(gmp_input, input); \
			\
			expected = mpz_probab_prime_p(gmp_input, 50); \
			if (expected == 2) expected = 1; \
			\
			output = func(input); \
			_test_check(uint64_t, int, input, expected, output); \
		} \
		_print_test_result2(func, gmp, i, passed, \
			" %3$"PRIu32"bit", bits); \
	}

PRIME_GMP_TEST(mr_prime);
PRIME_GMP_TEST(bpsw_prime);

int main ()
{
	int test;

	for (test = 54; test <= 64; test++) {
		mr_prime_gmp_test(50000, test);
	}

	for (test = 54; test <= 64; test++) {
		bpsw_prime_gmp_test(50000, test);
	}

	return 0;
}
