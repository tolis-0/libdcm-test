#include <stdint.h>
#include <stdlib.h>
#include "../dctest.h"

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

void ext_gcd_perf (int total, uint32_t bits) {
	int i;
	uint64_t *a, *b, output;
	int64_t t, s;
	clock_t start, end;

	a = (uint64_t *) malloc(total * sizeof(uint64_t));
	b = (uint64_t *) malloc(total * sizeof(uint64_t));

	for (i = 0; i < total; i++) {
		a[i] = rand_bit(bits);
		b[i] = rand_bit(bits);
	}

	start = clock();
	for (i = 0; i < total; i++)
		output = ext_gcd(a[i], b[i], &s, &t);
	end = clock();

	free(a);
	free(b);
	printf("ext_gcd %"PRIu32"bit time: %lfs\n",
		bits, (double) (end - start)/CLOCKS_PER_SEC);
}

int main () 
{
	int test;

	for (test = 10; test <= 64; test++)
		ext_gcd_perf(100000, test);

	return 0;
}
