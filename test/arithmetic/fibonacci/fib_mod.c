#include "../../dctest.h"
#include "../../gmptest.h"
#include <string.h>
#include <stdlib.h>


#define MAND_N  200000
#define EXTRA_N 2000000

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

GMP_TEST_BEGIN(fib_mod, 0b0010)
mpz_fib_ui(gmp_r, a);
mpz_mod(gmp_r, gmp_r, gmp_m);
r = dc_fib_mod(a, m);
GMP_TEST_END(fib_mod, 0b0010)

void dc_fib_mod_test(int t, uint64_t n_start, uint64_t f_0, uint64_t f_1, uint64_t m);
void dc_fib_mod_performance (uint64_t total, uint32_t bits, uint32_t divbits);


int main(int argc, char **argv)
{
	int i;
	test_arguments_setup();

	mandatory_tests {
		for (i = 1; i <= 64; i++) {
				fib_mod_gmp_test(50000, 4, i);
				fib_mod_gmp_test(20000, 8, i);
				fib_mod_gmp_test(5000, 12, i);
				fib_mod_gmp_test(2000, 16, i);
				fib_mod_gmp_test(200, 20, i);
		}

		dc_fib_mod_test(MAND_N, 103948543, 8273437, 99265733, 100000000);
		dc_fib_mod_test(MAND_N, 207897089, 32316189, 56812120, 100000000);
		dc_fib_mod_test(MAND_N, 1002344234, 59238737, 73373890, 100000000);
		dc_fib_mod_test(MAND_N, 6574645645, 42183145, 6520953, 100000000);

		dc_fib_mod_test(MAND_N, 2710937462, 45764207, 803794246, 987365031);
		dc_fib_mod_test(MAND_N, 5421874925, 220420823, 280553549, 987365031);
		dc_fib_mod_test(MAND_N, 10843749850, 541264870, 279115409, 987365031);

		dc_fib_mod_test(MAND_N, 3804736455, 5137179646, 11398095651, 15523659327);
	}

	extra_tests {
		for (i = 1; i <= 64; i++) {
				fib_mod_gmp_test(1000000, 4, i);
				fib_mod_gmp_test(500000, 8, i);
				fib_mod_gmp_test(50000, 12, i);
				fib_mod_gmp_test(20000, 16, i);
				fib_mod_gmp_test(5000, 20, i);
		}
	}

	perf_tests {
		for (i = 1; i <= 64; i++)
			dc_fib_mod_performance(100000, i, 31);
		for (i = 1; i <= 64; i++)
			dc_fib_mod_performance(100000, i, 63);
		for (i = 1; i <= 64; i++)
			dc_fib_mod_performance(100000, i, 64);
	}

	return 0;
}


void dc_fib_mod_test(int t, uint64_t n, uint64_t f_0, uint64_t f_1, uint64_t m)
{
	int i = 2, passed = 0;
	uint64_t output, tmp;

	output = dc_fib_mod(n, m);
	_test_check2(uint64_t, uint64_t, uint64_t, n, m, f_0, output);
	output = dc_fib_mod(++n, m);
	_test_check2(uint64_t, uint64_t, uint64_t, n, m, f_1, output);

	for (n++; i < t; i++, n++) {
		tmp = dc_add_mod(f_0, f_1, m);
		f_0 = f_1;
		f_1 = tmp;
		output = dc_fib_mod(n, m);
		_test_check2(uint64_t, uint64_t, uint64_t, n, m, f_1, output);
	}

	_print_test_result2(dc_fib_mod, , i, passed,
		" n:%3$"PRIu64" m:%4$"PRIu64, n, m);
}


void dc_fib_mod_performance (uint64_t total, uint32_t bits, uint32_t divbits) {
	uint64_t i, *a, *m, output;
	clock_t start, end;

	set_rand();
	a = (uint64_t *) malloc(total * sizeof(uint64_t));
	m = (uint64_t *) malloc(total * sizeof(uint64_t));

	for (i = 0; i < total; i++) {
		do {
			m[i] = rand_bit(divbits);
		} while (m[i] == 0);
	}

	for (i = 0; i < total; i++)
		a[i] = rand_bit(bits);

	start = clock();
	for (i = 0; i < total; i++)
		output = dc_fib_mod(a[i], m[i]);
	end = clock();

	free(a);
	free(m);

	printf("%lf (seconds) (fib_mod %"PRIu32"bit %"PRIu32"divbit)\n",
		(double) (end - start)/CLOCKS_PER_SEC, bits, divbits);
}