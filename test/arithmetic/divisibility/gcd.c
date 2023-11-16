#include "../../dctest.h"
#include "../../gmptest.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>


GMP_TEST_BEGIN(dc_gcd,			u,u,x, x, u,x,x, 0)
mpz_gcd(gmp_r, gmp_a, gmp_b);
r = dc_gcd(a, b);
GMP_TEST_END(dc_gcd,			u,u,x, x, u,x,x, 0)

PERFORMANCE_TEST_BEGIN(dc_gcd,	u,u,x, x, u,x,x)
r = dc_gcd(a[i], b[i]);
PERFORMANCE_TEST_END(dc_gcd,	u,u,x, x, u,x,x)


int main (int argc, char **argv)
{
	int i;
	test_arguments_setup();

	quick_tests {
		for (i = 1; i <= 64; i++)
			dc_gcd_gmp_test(25000, i, 0);
	}

	extra_tests {
		for (i = 1; i <= 64; i++)
			dc_gcd_gmp_test(1000000, i, 0);
	}

	perf_tests {
		for (i = 1; i <= 64; i++)
			dc_gcd_perf_test(100000, i);
	}

	return 0;
}
