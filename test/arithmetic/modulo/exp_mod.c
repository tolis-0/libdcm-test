#include "../../dctest.h"
#include "../../gmptest.h"
#include "modulo.h"
#include <stdlib.h>
#include <string.h>


GMP_TEST_BEGIN(exp_mod, 0b1010)
mpz_powm(gmp_r, gmp_a, gmp_b, gmp_m);
r = dc_exp_mod(a, b, m);
GMP_TEST_END(exp_mod, 0b1010)

MODULO_PERFORMANCE_START(odd_exp_mod, 0b1010, 1)
output = dc_exp_mod(a[i], b[i], m[i]);
MODULO_PERFORMANCE_END(odd_exp_mod, 0b1010)

MODULO_PERFORMANCE_START(even_exp_mod, 0b1010, 2)
output = dc_exp_mod(a[i], b[i], m[i]);
MODULO_PERFORMANCE_END(even_exp_mod, 0b1010)


int main (int argc, char **argv)
{
	int i, j;
	test_arguments_setup();

	mandatory_tests {
		for (i = 1; i <= 64; i++)
			for (j = 8; j <= 64; j += 8)
				exp_mod_gmp_test(25000, j, i);
	}

	extra_tests {
		for (i = 1; i <= 64; i++)
			for (j = 8; j <= 64; j += 8)
				exp_mod_gmp_test(1000000, j, i);
	}

	perf_tests {
		for (int i = 2; i <= 64; i++)
			odd_exp_mod_performance(100000, i);
		for (int i = 2; i <= 64; i++)
			even_exp_mod_performance(100000, i);
	}

	return 0;
}

