#include "../dctest.h"
#include "prime.h"
#include <string.h>

PRIME_TEST_DECLARATIONS(dc_bpsw);

int main(int argc, char **argv)
{
	test_arguments_setup();

	mandatory_tests {
		dc_bpsw_set_test();      // Values 0 to 1299709
		prime_specific_value_tests(dc_bpsw);
		prime_other_tests(dc_bpsw);
	}

	extra_tests {
		dc_bpsw_set26_test();    // Values 472882049 to 492876847
	}

	return 0;
}