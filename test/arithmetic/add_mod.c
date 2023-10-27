#include "../dctest.h"
#include "../gmptest.h"
#include "modulo.h"
#include <stdlib.h>
#include <string.h>


GMP_TEST_BEGIN(add_mod, 0b1010)
mpz_add(gmp_r, gmp_a, gmp_b);
mpz_mod(gmp_r, gmp_r, gmp_m);
r = dc_add_mod(a, b, m);
GMP_TEST_END(add_mod, 0b1010)


MODULO_PERFORMANCE_START(add_mod, 0b1010)
output = dc_add_mod(a[i], b[i], m[i]);
MODULO_PERFORMANCE_END(add_mod, 0b1010)


int main(int argc, char **argv)
{
	int i, j;
	test_arguments_setup();

	mandatory_tests {
		for (i = 1; i <= 64; i++)
			for (j = 8; j <= 64; j += 8)
				add_mod_gmp_test(25000, j, i);
	}

	extra_tests {
		for (i = 1; i <= 64; i++)
			for (j = 8; j <= 64; j += 8)
				add_mod_gmp_test(1000000, j, i);
	}

	perf_tests {
		for (int i = 1; i <= 64; i++)
			add_mod_performance(100000, i);
	}

	return 0;
}


/*void add_mod_performance (uint64_t total, uint32_t bits) {
	uint64_t i, *a, *b, *c, *m, output;
	clock_t start, end;

	set_rand();
	a = (uint64_t *) malloc(total * sizeof(uint64_t));
	b = (uint64_t *) malloc(total * sizeof(uint64_t));
	m = (uint64_t *) malloc(total * sizeof(uint64_t));

	for (i = 0; i < total; i++)
		do {
			m[i] = rand_bit(bits);
		} while (m[i] == 0);

	for (i = 0; i < total; i += 2) {
		a[i] = rand_bit(64);
		b[i] = rand_bit(64);
	}

	for (i = 1; i < total; i += 2) {
		a[i] = rand_bit(bits);
		b[i] = rand_bit(bits);
	}

	start = clock();
	for (i = 0; i < total; i++)
		output = dc_add_mod(a[i], b[i], m[i]);
	end = clock();

	free(a);
	free(b);
	free(m);

	printf("%lf (seconds) (add_mod %"PRIu32"bit)\n",
		(double) (end - start)/CLOCKS_PER_SEC, bits);
}*/