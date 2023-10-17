#include <stdint.h>
#include <gmp.h>
#include "../dctest.h"

void gcd_gmp_test (int total, uint32_t bits) {
	int i, passed;
	uint64_t a, b, output, expected;
	int64_t t, s;
	mpz_t gmp_n1, gmp_n2, gmp_out;
	char input[50];

	set_rand();
	mpz_init(gmp_n1);
	mpz_init(gmp_n2);
	mpz_init(gmp_out);

	for (i = 0, passed = 0; i < total; i++) {
		a = rand_bit(bits);
		b = rand_bit(bits);
		
		mpz_set_ui(gmp_n1, a);
		mpz_set_ui(gmp_n2, b);
		mpz_gcd(gmp_out, gmp_n1, gmp_n2);
		expected = mpz_get_ui(gmp_out);

		output = ext_gcd(a, b, &s, &t);
		if ((__int128) b*t + (__int128) a*s != (__int128) output) 
			printf("a: %lu, b: %lu, s: %ld, t: %ld,  out: %lu\n", a,b,s,t,output);
		snprintf(input, 50, "%"PRIu64", %"PRIu64, a, b);
		_test_check(string, uint64_t, input, expected, output);
	}

	_print_test_result2(gcd, gmp, i, passed, " %3$"PRIu32"bit", bits);
}

int main () 
{
	int test;

	for (test = 10; test <= 64; test++) {
		gcd_gmp_test(100000, test);
	}

	return 0;
}