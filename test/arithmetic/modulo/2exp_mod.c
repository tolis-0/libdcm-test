#include "../../dctest.h"
#include "../../gmptest.h"
#include "modulo.h"
#include <stdlib.h>
#include <string.h>

mpz_t gmp_2;

GMP_TEST_BEGIN(_2exp_mod, 	u,x,x, u, u,x,x, 0)
mpz_powm(gmp_r, gmp_2, gmp_a, gmp_m);
r = dc_2exp_mod(a, m);
GMP_TEST_END(_2exp_mod, 	u,x,x, u, u,x,x, 0)

MODULO_PERFORMANCE_START(odd_2exp_mod, 0b0010, 1)
output = dc_2exp_mod(a[i], m[i]);
MODULO_PERFORMANCE_END(odd_2exp_mod, 0b0010)

MODULO_PERFORMANCE_START(even_2exp_mod, 0b0010, 2)
output = dc_2exp_mod(a[i], m[i]);
MODULO_PERFORMANCE_END(even_2exp_mod, 0b0010)


int main (int argc, char **argv)
{
	int i, j;
	test_arguments_setup();

	mpz_init_set_ui(gmp_2, 2);

	mandatory_tests {
		for (i = 1; i <= 64; i++)
			for (j = 8; j <= 64; j += 8)
				_2exp_mod_gmp_test(25000, j, i);
	}

	extra_tests {
		for (i = 1; i <= 64; i++)
			for (j = 8; j <= 64; j += 8)
				_2exp_mod_gmp_test(1000000, j, i);
	}

	perf_tests {
		for (int i = 2; i <= 64; i++)
			odd_2exp_mod_performance(100000, i);
		for (int i = 2; i <= 64; i++)
			even_2exp_mod_performance(100000, i);
	}

	mpz_clear(gmp_2);

	return 0;
}