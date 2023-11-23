#include "../../dctest.h"
#include <string.h>
#include <time.h>
#include <gmp.h>

void dc_monexp_mod_test (int total, int bits);


int main (int argc, char **argv)
{
	int i;
	test_arguments_setup();

	quick_tests {
		for (i = 1; i <= 64; i++)
			dc_monexp_mod_test(100000, i);
	}

	extra_tests {
		for (i = 1; i <= 64; i++)
			dc_monexp_mod_test(2500000, i);
	}

	perf_tests {

	}

	return 0;
}


void dc_monexp_mod_test (int total, int bits)
{
	int i, passed;
	uint64_t base, exp, m, outp, expected;
	mpz_t mpz_base, mpz_m, mpz_r;

	mpz_init(mpz_base);
	mpz_init(mpz_m);
	mpz_init(mpz_r);

	for (passed = i = 0; i < total; i++) {

		m = (rand_bit(bits) | 1);
		base = (rand_bit(bits));
		exp = (rand_bit(bits));

		mpz_set_ui(mpz_base, base);
		mpz_set_ui(mpz_m, m);

		outp = dc_monexp_mod(base, exp, m);
		mpz_powm_ui(mpz_r, mpz_base, exp, mpz_m);
		expected = mpz_get_ui(mpz_r);

		if (outp == expected) {
			passed++;
		} else {
			printf("At base:%"PRIu64", exp:%"PRIu64
					", m:%"PRIu64
					": Expected %"PRIu64
					". Got %"PRIu64"\n",
					base, exp, m, expected, outp);
		}
	}

	mpz_clear(mpz_base);
	mpz_clear(mpz_m);
	mpz_clear(mpz_r);

	_print_test_result2(monexp_mod,, i, passed,
		" bits:%3$d", bits);
}
