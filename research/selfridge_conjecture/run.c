#include <stdio.h>
#include <dcmath.h>
#include <gmp.h>
#include <stdint.h>
#include <signal.h>
#include <stdlib.h>

void sigint_handler (int sigid);

uint64_t n, tested, valid = 0;
FILE *fp;

int main ()
{
	uint64_t rem;
	int gmp_outp, dc_outp, sc_outp;
	mpz_t gmp_n;

	if (signal(SIGINT, sigint_handler) == SIG_ERR) {
		fprintf(stderr, "Error setting handler for SIGINT\n");
		return 1;
	}

	fp = fopen("sc.txt", "r");
	if (fp == NULL) {
		printf("File not Found, starting from 1\n");
		n = 1;
	} else {
		fscanf(fp, "%llu", &n);
		fclose(fp);
	}

	tested = 0;

	if ((n & 1) == 0) {
		fprintf(stderr, "Even input (invalid)\n");
		return 1;
	}

	mpz_init_set_ui(gmp_n, n);

	for (valid = 1;; n += 2) {

		rem = n % 5;
		if (rem != 2 && rem != 3) goto next_value;

		/* version of dc_prime that doesn't use selfridge_conjecture */
		dc_outp = dc_prime(n);
		gmp_outp = mpz_probab_prime_p(gmp_n, 25);

		if (gmp_outp == 2) gmp_outp = 1;

		/* cross-check dc_prime and mpz_probab_prime */
		if (gmp_outp != dc_outp) {
			printf("input: %llu, dc: %d, gmp: %d\n", n, dc_outp, gmp_outp);
			break;
		}

		sc_outp = dc_selfridge_conjecture(n);

		/* cross-check with dc_selfridge_conjecture */
		if (sc_outp != dc_outp) {
			printf("input: %llu, others: %d, sc: %d\n", n, dc_outp, sc_outp);
		} else tested++;

next_value:
		mpz_add_ui(gmp_n, gmp_n, 2);
	}

	mpz_clear(gmp_n);

	return 0;
}


void sigint_handler (int sigid)
{
	putchar('\n');
	if (valid) {
		fp = fopen("sc.txt", "w");
		fprintf(fp, "%llu\n", n);
		fclose(fp);
		printf("Current Value: %llu\n", n);
		printf("Tests:         %llu\n", tested);
	} else {
		printf("Stopped early with SIGINT\n");
	}

	exit(0);
}
