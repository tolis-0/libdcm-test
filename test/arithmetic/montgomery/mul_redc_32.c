#include "../../dctest.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MUL_NUM 20

void dc_mul_redc_32_test (int total, int bits);
void dc_mul_redc_32_perf (int total, int bits);


int main (int argc, char **argv)
{
	int i;
	test_arguments_setup();

	quick_tests {
		for (i = 1; i <= 32; i++)
			dc_mul_redc_32_test(100000, i);
	}

	extra_tests {
		for (i = 1; i <= 32; i++)
			dc_mul_redc_32_test(5000000, i);
	}

	perf_tests {
		/* Does MUL_NUM for each set of N, N' */
		for (i = 1; i <= 32; i++)
			dc_mul_redc_32_perf(100000, i);
	}

	return 0;
}


void dc_mul_redc_32_test (int total, int bits)
{
	int i, k, j, passed;
	uint32_t a, b, c, N, Ninv, expected, outp;
	uint64_t R;

	for (passed = i = k = 0; k < 1000; k++) {

		N = (rand_bit(bits) | 1);
		Ninv = dc_montgomery(32, N, &R);

		for (j = 0; j < total/1000; j++) {
			a = rand_bit(bits) % N;
			b = rand_bit(bits) % N;

			c = dc_mul_mod(a, b, N);
			expected = dc_mul_mod(c, R, N);

			a = dc_mul_mod(a, R, N);
			b = dc_mul_mod(b, R, N);

			outp = dc_mul_redc_32(a, b, N, Ninv);

			i++;
			if (outp == expected) {
					passed++;
			} else {
				printf("At N:%"PRIu32", N'=%"PRIu32
						", a=%"PRIu32", b=%"PRIu32
						": Expected %"PRIu32"=~%"PRIu32
						". Got %"PRIu32"\n",
						N, Ninv, a, b, c, expected, outp);
			}
		}
	}

	_print_test_result2(mul_redc_32,, i, passed,
		" bits:%3$d", bits);
}


void dc_mul_redc_32_perf (int total, int bits)
{
	int i, j;
	uint32_t *a, *b, *N, *Ninv;
	uint32_t __attribute__((unused)) outp;
	uint64_t R;
	clock_t start, end;

	a = malloc(total * MUL_NUM * sizeof(uint32_t));
	b = malloc(total * MUL_NUM * sizeof(uint32_t));
	N = malloc(total * MUL_NUM * sizeof(uint32_t));
	Ninv = malloc(total * MUL_NUM * sizeof(uint32_t));

	for (i = 0; i < total * MUL_NUM; i += MUL_NUM) {

		N[i] = (rand_bit(bits) | 1);
		Ninv[i] = dc_montgomery(32, N[i], &R);

		for (j = 0; j < MUL_NUM; j++) {
			N[i + j] = N[i];
			Ninv[i + j] = Ninv[i];
			a[i + j] = rand_bit(bits) % N[i];
			b[i + j] = rand_bit(bits) % N[i];
		}
	}

	start = clock();
	for (i = 0; i < total * MUL_NUM; i++)
		outp = dc_mul_redc_32(a[i], b[i], N[i], Ninv[i]);
	end = clock();

	free(N);
	free(Ninv);
	free(a);
	free(b);

	printf("%lf (seconds) (mul_redc_32 %dbit)\n",
		(double) (end - start)/CLOCKS_PER_SEC, bits);
}