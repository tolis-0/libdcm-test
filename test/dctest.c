#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "dctest.h"


void set_rand()
{
	srand(clock());
}

uint64_t rand_bit(uint64_t bits)
{
	uint64_t number;
	int j;

	for (number = 0, j = 0; j < 5; j++) {
		number <<= 15;
		number |= 0x7FFF & rand();
	}
	number &= 0xFFFFFFFFFFFFFFFF >> (64 - bits);

	return number;
}
