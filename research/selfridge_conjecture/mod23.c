#include <stdio.h>
#include <dcmath.h>
#include <gmp.h>
#include <stdint.h>
#include <signal.h>
#include <stdlib.h>

void sigint_handler (int sigid);

int run = 1;

int main ()
{
	FILE *fp;
	uint64_t rem, n, tested;
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
		fscanf(fp, "%lu", &n);
		fclose(fp);
	}

	if ((n & 1) == 0) {
		fprintf(stderr, "Even input (invalid)\n");
		return 1;
	}

	mpz_init_set_ui(gmp_n, n);

	for (tested = 0; run; n += 2) {

		rem = n % 5;
		if (rem != 2 && rem != 3) goto next_value;

		/* version of dc_prime that doesn't use selfridge_conjecture */
		dc_outp = dc_prime(n);
		gmp_outp = mpz_probab_prime_p(gmp_n, 25);

		if (gmp_outp == 2) gmp_outp = 1;

		/* cross-check dc_prime and mpz_probab_prime */
		if (gmp_outp != dc_outp) {
			printf("input: %lu, dc: %d, gmp: %d\n", n, dc_outp, gmp_outp);
			break;
		}

		sc_outp = dc_selfridge_conjecture(n);

		/* cross-check with dc_selfridge_conjecture */
		if (sc_outp != dc_outp) {
			printf("input: %lu, others: %d, sc: %d\n", n, dc_outp, sc_outp);
		} else {
			tested++;
		}

next_value:
		mpz_add_ui(gmp_n, gmp_n, 2);
	}

	putchar('\n');

	fp = fopen("sc.txt", "w");
	fprintf(fp, "%lu\n", n);
	fclose(fp);

	fp = fopen("history.txt", "a");
	fprintf(fp, "%lu\n", n);
	fclose(fp);

	printf("Current Value: %lu\n", n);
	printf("Tests:         %lu\n", tested);

	mpz_clear(gmp_n);

	return 0;
}


void sigint_handler (int sigid)
{
	if (sigid == SIGINT) run = 0;
}
