#include "../dctest.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

SEQUENCE_TEST_AF(int8_t, alloc_sieve, isprime);
void alloc_sieve_performance (size_t limit);

int main(int argc, char **argv)
{
	int8_t *is_prime;

	test_arguments_setup();

	mandatory_tests {
		is_prime = dc_alloc_sieve(100000);
		alloc_sieve_sequence_test(is_prime);
		free(is_prime);
	}

	perf_tests {
		for (int i = 8; i <= 30; i++)
			alloc_sieve_performance(1 << i);
	}

	return 0;
}

void alloc_sieve_performance (size_t limit)
{
	int8_t *is_prime;
	clock_t start, end;

	start = clock();
	is_prime = dc_alloc_sieve(limit);
	end = clock();

	free(is_prime);
	printf("%lf (seconds) (sieve size: %zu)\n",
		(double) (end - start)/CLOCKS_PER_SEC, limit);
}
