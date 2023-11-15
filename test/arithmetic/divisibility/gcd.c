#include "../../dctest.h"
#include "../../gmptest.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>


GMP_TEST_BEGIN(dc_gcd,		u,u,x, x, u,x,x, 0)
mpz_gcd(gmp_r, gmp_a, gmp_b);
r = dc_gcd(a, b);
GMP_TEST_END(dc_gcd,		u,u,x, x, u,x,x, 0)

void gcd_performance (int total, uint32_t bits);


int main (int argc, char **argv)
{
	int i;
	test_arguments_setup();

	mandatory_tests {
		for (i = 1; i <= 64; i++)
			dc_gcd_gmp_test(25000, i, 0);
	}

	extra_tests {
		for (i = 1; i <= 64; i++)
			dc_gcd_gmp_test(1000000, i, 0);
	}

	perf_tests {
		for (i = 1; i <= 64; i++)
			gcd_performance (100000, i);
	}

	return 0;
}


void gcd_performance (int total, uint32_t bits)
{
	int i;
	uint64_t *input1, *input2, __attribute__((unused)) a;
	clock_t start, end;

	set_rand();
	input1 = malloc(total * sizeof(uint64_t));
	input2 = malloc(total * sizeof(uint64_t));

	for (i = 0; i < total; i++) {
		input1[i] = rand_bit(bits);
		input2[i] = rand_bit(bits);
	}

	start = clock();
	for (i = 0; i < total; i++)
		a = dc_gcd(input1[i], input2[i]);
	end = clock();

	free(input1);
	free(input2);

	printf("%lf (seconds) (dc_sqrt %"PRIu32"bit)\n",
		(double) (end - start)/CLOCKS_PER_SEC, bits);
}
