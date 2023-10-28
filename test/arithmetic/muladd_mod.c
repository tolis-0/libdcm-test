#include "../dctest.h"
#include "../gmptest.h"
#include "modulo.h"
#include <stdlib.h>
#include <string.h>


GMP_TEST_BEGIN(mul_mod, 0b1010)
mpz_mul(gmp_r, gmp_a, gmp_b);
mpz_mod(gmp_r, gmp_r, gmp_m);
r = dc_mul_mod(a, b, m);
GMP_TEST_END(mul_mod, 0b1010)

GMP_TEST_BEGIN(muladd_mod, 0b1110)
mpz_mul(gmp_r, gmp_a, gmp_b);
mpz_add(gmp_r, gmp_r, gmp_c);
mpz_mod(gmp_r, gmp_r, gmp_m);
r = dc_muladd_mod(a, b, c, m);
GMP_TEST_END(muladd_mod, 0b1110)

MODULO_PERFORMANCE_START(muladd_mod, 0b1110)
output = dc_muladd_mod(a[i], b[i], c[i], m[i]);
MODULO_PERFORMANCE_END(muladd_mod, 0b1110)


int main(int argc, char **argv)
{
	int i, j;
	test_arguments_setup();

	mandatory_tests {
		for (i = 1; i <= 64; i++)
			for (j = 8; j <= 64; j += 8)
				mul_mod_gmp_test(25000, j, i);
		for (i = 1; i <= 64; i++)
			for (j = 8; j <= 64; j += 8)
				muladd_mod_gmp_test(25000, j, i);
	}

	extra_tests {
		for (i = 1; i <= 64; i++)
			for (j = 8; j <= 64; j += 8)
				mul_mod_gmp_test(1000000, j, i);
		for (i = 1; i <= 64; i++)
			for (j = 8; j <= 64; j += 8)
				muladd_mod_gmp_test(1000000, j, i);
	}

	perf_tests {
		for (int i = 1; i <= 64; i++)
			muladd_mod_performance(100000, i);
	}

	return 0;
}

