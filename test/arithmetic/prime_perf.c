#include <stdint.h>
#include <stdlib.h>
#include <gmp.h>
#include "../dctest.h"

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#define PRIME_FUNC_PERFORMANCE(func) \
	void func##_performance (uint64_t total, uint32_t bits) { \
		uint64_t i, *input, a; \
		clock_t start, end; \
		\
		set_rand(); \
		input = (uint64_t *) malloc(total * sizeof(uint64_t)); \
		\
		for (i = 0; i < total; i++) \
			input[i] = rand_bit(bits) | 1; \
		\
		start = clock(); \
		for (i = 0; i < total; i++) \
			a = func(input[i]); \
		end = clock(); \
		free(input); \
		\
		printf(_to_string(func) " %"PRIu32"bit time: %lfs\n", \
			bits, (double) (end - start)/CLOCKS_PER_SEC); \
	}

PRIME_FUNC_PERFORMANCE(ef_prime);
PRIME_FUNC_PERFORMANCE(mr_prime);
PRIME_FUNC_PERFORMANCE(bpsw_prime);

void gmp_performance (uint64_t total, uint32_t bits) {
	uint64_t i, a;
	clock_t start, end = 0; 
	mpz_t *input;

	set_rand();
	input = (mpz_t *) malloc(total * sizeof(mpz_t));
	
	for (i = 0; i < total; i++)
		mpz_init_set_ui(input[i], rand_bit(bits) | 1);
	
	start = clock(); 
	for (i = 0; i < total; i++)
		a = mpz_probab_prime_p(input[i], 25);
	end = clock();
	free(input);
	
	printf("gmp %"PRIu32"bit time: %lfs\n", 
		bits, (double) (end - start)/CLOCKS_PER_SEC);
}

int main ()
{
	int test;

	for (test = 3; test <= 64; test++)
		ef_prime_performance(100000, test);
	/*for (test = 3; test <= 64; test++)
		mr_prime_performance(100000, test);*/
	/*for (test = 3; test <= 64; test++)
		bpsw_prime_performance(100000, test);*/
	/*for (test = 3; test <= 64; test++)
		gmp_performance(100000, test);*/

	return 0;
}
