#include "../dctest.h"
#include <stdlib.h>

SEQUENCE_TEST_F(int32_t, mr_prime, uint64_t, isprime);
SEQUENCE_TEST_F(int32_t, s3_prime, uint64_t, isprime);
SEQUENCE_TEST_F(int32_t, ef_prime, uint64_t, isprime);
SEQUENCE_TEST_F(int32_t, bpsw_prime, uint64_t, isprime);

SEQUENCE_TEST_AF(int8_t, er_sieve, isprime);

SET_TEST_F(mr_prime, uint64_t, primes);
SET_TEST_F(s3_prime, uint64_t, primes);
SET_TEST_F(ef_prime, uint64_t, primes);
SET_TEST_F(bpsw_prime, uint64_t, primes);

SET_TEST_FNS(ef_prime, uint64_t, primes26, set26, 472882048);
SET_TEST_FNS(bpsw_prime, uint64_t, primes26, set26, 472882048);
FALSE_TEST_FN(mr_prime, uint64_t, a074773, strps);
TRUE_TEST_FN(mr_prime, uint64_t, specific_primes, prim);
FALSE_TEST_FN(mr_prime, uint64_t, specific_composites, comp);
TRUE_TEST_FN(mr_prime, uint64_t, b049002, p2_2);
TRUE_TEST_FN(mr_prime, uint64_t, b056130, palb24);
TRUE_TEST_FN(mr_prime, uint64_t, b272061, sigtp);

TRUE_TEST_FN(bpsw_prime, uint64_t, b272061, sigtp);

#define LUCAS_TEST(test_name, filename, expected) \
void lucas_P1_##test_name##_test () { \
	int i, passed, output, D, tmp; \
	uint64_t input, negQ; \
	FILE *test_fp; \
	\
	_test_file_open(test_fp, filename); \
	for (i = 0, passed = 0;; i++) { \
		if (fscanf(test_fp, _scan_type(uint64_t), &input) == EOF) break; \
		if (input == 5 || input == 11) {output = 1; goto skip_lucas_##test_name;} \
		D = find_D_jacobi(input); \
		if (D == 0) {output = 0; goto skip_lucas_##test_name;} \
		\
		tmp = (1 - D) / 4; \
		if (tmp > 0) { \
			if (input % tmp == 0) {output = 0; goto skip_lucas_##test_name;} \
			negQ = input - tmp; \
		} else { \
			negQ = -tmp; \
		} \
		output = lucas_prime_P1(input, negQ); \
skip_lucas_##test_name: \
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
	int8_t *isprime_array;

	mr_prime_sequence_test();
	s3_prime_sequence_test();
	ef_prime_sequence_test();
	bpsw_prime_sequence_test();

	malloc_sieve(isprime_array, 100001);
	er_sieve_sequence_test(isprime_array);
	free(isprime_array);

	mr_prime_set_test();
	s3_prime_set_test();
	ef_prime_set_test();
	bpsw_prime_set_test();

/*	ef_prime_set26_test(); 	// The Twenty-sixth 1,000,000 Primes (primes.utm.edu)
	bpsw_prime_set26_test();*/
	mr_prime_strps_test(); 	// Strong pseudoprimes to bases 2, 3, 5 and 7. (oeis.org)
	mr_prime_prim_test();   // A test for some specific primes
	mr_prime_comp_test();   // A test for some specific composites
	mr_prime_p2_2_test(); 	// Primes of form p^2-2, where p is prime. (oeis.org)
	mr_prime_palb24_test(); // Palindromic primes in bases 2 and 4. (oeis.org)
	mr_prime_sigtp_test(); 	// 64bit of A272061 (oeis.org)
	bpsw_prime_sigtp_test();

	lucas_P1_pseudoprime_test();
	lucas_P1_strpseudo_test();
	lucas_P1_pseudob2345_test();
	lucas_P1_pseudob2_test();
	lucas_P1_primes_test();

	return 0;
}
