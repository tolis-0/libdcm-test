#include "../../dctest.h"
#include "../../gmptest.h"
#include "modulo.h"
#include <stdlib.h>
#include <string.h>


GMP_TEST_BEGIN(dc_add_mod, 			u,u,x, u, u,x,x, 0)
mpz_add(gmp_r, gmp_a, gmp_b);
mpz_mod(gmp_r, gmp_r, gmp_m);
r = dc_add_mod(a, b, m);
GMP_TEST_END(dc_add_mod,			u,u,x, u, u,x,x, 0)

PERFORMANCE_TEST_BEGIN(dc_add_mod,	u,u,x, u, u,x,x)
r = dc_add_mod(a[i], b[i], m[i]);
PERFORMANCE_TEST_END(dc_add_mod,	u,u,x, u, u,x,x)


int main (int argc, char **argv)
{
	int i, j;
	test_arguments_setup();

	quick_tests {
		for (i = 1; i <= 64; i++)
			for (j = 8; j <= 64; j += 8)
				dc_add_mod_gmp_test(25000, j, i);
	}

	extra_tests {
		for (i = 1; i <= 64; i++)
			for (j = 8; j <= 64; j += 8)
				dc_add_mod_gmp_test(1000000, j, i);
	}

	perf_tests {
		for (int i = 1; i <= 64; i++)
			dc_add_mod_perf_test(100000, i, i);
	}

	return 0;
}
