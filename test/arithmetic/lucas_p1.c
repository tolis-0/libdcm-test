#include "../dctest.h"

#define _conditional_test(condition, o) \
	if (condition) { \
		output = o; \
		goto skip_lucas; \
	} 

#define LUCAS_TEST(test_name, filename, expected) \
	void lucas_P1_##test_name##_test () { \
		int i, passed, output, D, tmp; \
		uint64_t input, negQ; \
		FILE *test_fp; \
		\
		_test_file_open(test_fp, filename); \
		for (i = 0, passed = 0;; i++) { \
			if (fscanf(test_fp, _scan_type(uint64_t), &input) == EOF) break; \
			_conditional_test(input == 5 || input == 11, 1); \
			D = dc_find_jacobi(input); \
			_conditional_test(D == 0, 0); \
			tmp = (1 - D) / 4; \
			if (tmp > 0) { \
				_conditional_test(input % tmp == 0, 0); \
				negQ = input - tmp; \
			} else { \
				negQ = -tmp; \
			} \
			output = dc_lucas_p1(input, negQ); \
skip_lucas: \
			_test_check(uint64_t, int, input, expected, output); \
		} \
		fclose(test_fp); \
		_print_test_result(lucas_prime_P1, test_name, i, passed); \
	}

LUCAS_TEST(pseudoprime, b217120, 1);
LUCAS_TEST(strpseudo, b217255, 1);
LUCAS_TEST(pseudob2345, a074773, 0);
LUCAS_TEST(pseudob2, b001262, 0);
LUCAS_TEST(primes, primes, 1);

int main () 
{
	lucas_P1_pseudoprime_test();
	lucas_P1_strpseudo_test();
	lucas_P1_pseudob2345_test();
	lucas_P1_pseudob2_test();
	lucas_P1_primes_test();

	return 0;
}