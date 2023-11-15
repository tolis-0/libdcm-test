#include "../../dctest.h"
#include <string.h>


SEQUENCE_TEST_F(uint64_t, dc_pisano, uint64_t, pisano);


int main(int argc, char **argv)
{
	test_arguments_setup();

	mandatory_tests {
		dc_pisano_sequence_test(); // Values 1 to 10000
	}

	quick_tests {

	}

	extra_tests {

	}

	perf_tests {

	}

	return 0;
}
