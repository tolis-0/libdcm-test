#include "../../dctest.h"
#include <string.h>


SEQUENCE_TEST_F(uint64_t, dc_fib_digits, uint64_t, b060384);


int main(int argc, char **argv)
{
	test_arguments_setup();

	mandatory_tests {
		dc_fib_digits_sequence_test(); // Values 0 to 10000
	}

	extra_tests {

	}

	perf_tests {

	}

	return 0;
}