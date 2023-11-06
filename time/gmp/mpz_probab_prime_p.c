#include "../../test/dctest.h"
#include <stdlib.h>
#include "gmp.h"

void mpz_probab_prime_p_performance (uint64_t total, uint32_t bits) {
	uint64_t i, num;
	mpz_t *input;
	int result;
	clock_t start, end;

	set_rand();
	input = (mpz_t *) malloc(total * sizeof(mpz_t));

	for (i = 0; i < total; i++) {
		num = (rand_bit(bits) | 1);
		mpz_init_set_ui(input[i], num);
	}

	start = clock();
	for (i = 0; i < total; i++)
		result = mpz_probab_prime_p(input[i], 25);
	end = clock();

	for (i = 0; i < total; i++)
		mpz_clear(input[i]);
	free(input);

	printf("%lf (seconds) (" _to_string(func) " %"PRIu32"bit)\n",
		(double) (end - start)/CLOCKS_PER_SEC, bits);
}

int main(int argc, char **argv)
{
	for (int i = 1; i <= 64; i++)
		mpz_probab_prime_p_performance(100000, i);

	return 0;
}

