#include "../../dctest.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>


void dc_2powr_gcd_test (int total, unsigned r);
void dc_2powr_gcd_performance (uint64_t total, unsigned r);


int main (int argc, char **argv)
{
	int i;
	test_arguments_setup();

	quick_tests {
		for (i = 1; i <= 64; i++)
			dc_2powr_gcd_test(160000, i);
	}

	extra_tests {
		for (i = 1; i <= 64; i++)
			dc_2powr_gcd_test(3200000, i);
	}

	perf_tests {
		for (i = 1; i <= 64; i++)
			dc_2powr_gcd_performance(100000, i);
	}

	return 0;
}


void dc_2powr_gcd_test (int total, unsigned r)
{
	int i, j, bits, passed;
	uint64_t high, low, n, s, t;
	int64_t output;
	__int128 calc;

	set_rand();
	passed = i = 0;

	for (bits = 1; bits <= 64; bits++) {
		for (j = 0; j < total/64; j++) {
			n = (rand_bit(bits) | 1);

			dc_2powr_gcd(r, n, &s, &t);

			calc = ((__int128) s << r) - ((__int128) t * n);
			output = (int64_t) calc;

			i++;
			if (output == 1) {
					passed++;
			} else {
				high = (uint64_t) (calc >> 64);
				low = (uint64_t) (calc);
				printf("At %" PRIu64 ": Expected s * 2^%u - t * n = 1"
						". Got %" PRIu64 ", %" PRIu64 " = %lx%lx\n",
						n, r, s, t, high, low);
			}
		}
	}

	_print_test_result2(dc_2powr_gcd,, i, passed,
		" r:%3$u", r);
}


void dc_2powr_gcd_performance (uint64_t total, unsigned r)
{
	uint64_t i, *n, __attribute__((unused)) r1, r2;
	uint32_t bits;
	clock_t start, end;

	set_rand();
	n = (uint64_t *) malloc(total * sizeof(uint64_t));

	for (i = 0; i < total; i++) {
		bits = (i & 0x3F) + 1;
		n[i] = (rand_bit(bits) | 1);
	}

	start = clock();
	for (i = 0; i < total; i++)
		dc_2powr_gcd(r, n[i], &r1, &r2);
	end = clock();

	free(n);

	printf("%lf (seconds) (2powr_gcd r=%u)\n",
		(double) (end - start)/CLOCKS_PER_SEC, r);
}
