#include "../../dctest.h"
#include "../../gmptest.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>


GMP_TEST_BEGIN(dc_ext_gcd,			u,u,x, x, u,s,s, 0)
mpz_gcdext(gmp_r, gmp_r1, gmp_r2, gmp_a, gmp_b);
r = dc_ext_gcd(a, b, &r1, &r2);
if (a == b && r1 == 1 && r2 == 0) r1 = 0, r2 = 1;
GMP_TEST_END(dc_ext_gcd,			u,u,x, x, u,s,s, 0)

PERFORMANCE_TEST_BEGIN(dc_ext_gcd,	u,u,x, x, u,s,s)
r = dc_ext_gcd(a[i], b[i], &r1, &r2);
PERFORMANCE_TEST_END(dc_ext_gcd,	u,u,x, x, u,s,s)

void dc_ext_gcd_test (int total, uint32_t bits);


int main (int argc, char **argv)
{
	int i;
	test_arguments_setup();

	quick_tests {
		for (i = 1; i <= 64; i++)
			dc_ext_gcd_test(25000, i);
		for (i = 1; i <= 64; i++)
			dc_ext_gcd_gmp_test(25000, i, 0);
	}

	extra_tests {
		for (i = 1; i <= 64; i++)
			dc_ext_gcd_gmp_test(1000000, i, 0);
	}

	perf_tests {
		for (i = 1; i <= 64; i++)
			dc_ext_gcd_perf_test(100000, i);
	}

	return 0;
}


void dc_ext_gcd_test (int total, uint32_t bits)
{
	int i, passed;
	uint64_t a, b, r, expected;
	int64_t r1, r2;
	__int128 tmp1, tmp2;

	set_rand();

	for (passed = i = 0; i < total; i++) {
		a = (rand_bit(bits));
		b = (rand_bit(bits));

		r = dc_ext_gcd(a, b, &r1, &r2);

		tmp1 = (__int128) a * (__int128) r1;
		tmp2 = (__int128) b * (__int128) r2;
		expected = (uint64_t) (tmp1 + tmp2);

		if (expected == r) {
				passed++;
		} else {
			printf("At %" PRIu64 ", %" PRIu64 ": Expected "
					"%" PRIu64 ". Got %"
					PRIu64 ", %" PRId64 ", %" PRId64 "\n",
					a, b, expected, r, r1, r2);
		}
	}

	_print_test_result2(dc_ext_gcd,, i, passed,
		" bits:%3$"PRIu32, bits);
}
