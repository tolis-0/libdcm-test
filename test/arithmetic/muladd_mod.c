#include "../dctest.h"
#include "../gmptest.h"
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


void muladd_mod_performance (uint64_t total, uint32_t bits);


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
				mul_mod_gmp_test(1000000, j ,i);
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


void muladd_mod_performance (uint64_t total, uint32_t bits) {
	uint64_t i, *a, *b, *c, *m, output;
	clock_t start, end;

	set_rand();
	a = (uint64_t *) malloc(total * sizeof(uint64_t));
	b = (uint64_t *) malloc(total * sizeof(uint64_t));
	c = (uint64_t *) malloc(total * sizeof(uint64_t));
	m = (uint64_t *) malloc(total * sizeof(uint64_t));

	for (i = 0; i < total; i++)
		do {
			m[i] = rand_bit(bits);
		} while (m[i] == 0);

	for (i = 0; i < total; i += 2) {
		a[i] = rand_bit(64);
		b[i] = rand_bit(64);
		c[i] = rand_bit(64);
	}

	for (i = 1; i < total; i += 2) {
		a[i] = rand_bit(bits);
		b[i] = rand_bit(bits);
		c[i] = rand_bit(bits);
	}

	start = clock();
	for (i = 0; i < total; i++){
		output = dc_muladd_mod(a[i], b[i], c[i], m[i]);
	}
	end = clock();

	free(a);
	free(b);
	free(c);
	free(m);

	printf("%lf (seconds) (muladd_mod %"PRIu32"bit)\n",
		(double) (end - start)/CLOCKS_PER_SEC, bits);
}