#ifndef _DCTEST_H
#define _DCTEST_H

#include <time.h>
#include <stdio.h>
#include <dcmath.h>
#include <stdint.h>
#include <inttypes.h>



#define  _to_string(x...) #x


#define _print_type(type) "%" _print_type_##type
#define _print_type_uint32_t PRIu32
#define _print_type_uint64_t PRIu64
#define _print_type_int8_t   PRId8
#define _print_type_int32_t  PRId32
#define _print_type_int64_t  PRId64
#define _print_type_int      "d"
#define _print_type_size_t   "zu"
#define _print_type_string   "s"

#define _scan_type(type) "%" _scan_type_##type
#define _scan_type_uint32_t  SCNu32
#define _scan_type_uint64_t  SCNu64
#define _scan_type_int8_t    SCNd8
#define _scan_type_int32_t   SCNd32
#define _scan_type_int64_t   SCNd64
#define _scan_type_int       "d"
#define _scan_type_size_t    "zu"


#define TEST_PASSED "\033[32mPassed\033[39m"
#define TEST_FAILED "\033[31mFailed\033[39m"




#define u_tvar_use 1
#define s_tvar_use 1
#define x_tvar_use 0
#define b_tvar_use 1

#define u_tvar_arg(x) , x
#define s_tvar_arg(x) , x
#define x_tvar_arg(x)
#define b_tvar_arg(x) , x

#define u_tvar_prt(x) x "%"PRIu64
#define s_tvar_prt(x) x "%"PRId64
#define x_tvar_prt(x) ""
#define b_tvar_prt(x) x "%d"

#define u_tvar_mpz mpz_t
#define s_tvar_mpz mpz_t
#define x_tvar_mpz __attribute__((unused)) mpz_t
#define b_tvar_mpz mpz_t

#define u_tvar_int uint64_t
#define s_tvar_int int64_t
#define x_tvar_int __attribute__((unused)) uint64_t
#define b_tvar_int int

#define u_tvar_out __attribute__((unused)) uint64_t
#define s_tvar_out __attribute__((unused)) int64_t
#define x_tvar_out __attribute__((unused)) uint64_t
#define b_tvar_out __attribute__((unused)) int

#define u_tvar_divb(type) , type div_bits
#define s_tvar_divb(type) , type div_bits
#define x_tvar_divb(type)
#define b_tvar_divb(type) , type div_bits

#define u_tvar_divb_cond check_div_bits_value
#define s_tvar_divb_cond check_div_bits_value
#define x_tvar_divb_cond
#define b_tvar_divb_cond check_div_bits_value

#define u_tvar_divb_print " %"PRIu32"divbit"
#define s_tvar_divb_print " %"PRIu32"divbit"
#define x_tvar_divb_print
#define b_tvar_divb_print " %"PRIu32"divbit"




/* program arguments setup for tests */
#define test_arguments_setup() \
	_Pragma("GCC diagnostic push") \
	_Pragma("GCC diagnostic ignored \"-Wunused-but-set-variable\"") \
	int do_extra_tests = 0, do_perf_tests = 0; \
	if (argc > 1) { \
		if 		(!strcmp("all", argv[1])) 	do_extra_tests = 1; \
		else if (!strcmp("perf", argv[1])) 	do_perf_tests = 1; \
	} \
	_Pragma("GCC diagnostic pop")

#define mandatory_tests if (!do_perf_tests)
#define quick_tests if ((!do_perf_tests) && !(do_extra_tests))
#define extra_tests if ((!do_perf_tests) && do_extra_tests)
#define perf_tests if (do_perf_tests)




#define _print_test_result(function, test_name, all, passed) \
	_print_test_result2(function, test_name, all, passed, )

#define _print_test_result2(function, test_name, all, passed, optional_text, ...) \
	do { \
		printf(_to_string(function test_name) optional_text \
			" test result: %1$d\\%2$d", passed, all, ##__VA_ARGS__); \
		if (passed == i) { \
			puts("  " TEST_PASSED); \
		} else { \
			puts("  " TEST_FAILED); \
		} \
	} while (0)

#define _print_test_time(function, test_name, all, passed, time) \
	_print_test_time2(function, test_name, all, passed, time, )

#define _print_test_time2(function, test_name, all, passed, time, optional_text, ...) \
	do { \
		printf(_to_string(function test_name) optional_text \
			" test result: %1$d\\%2$d", passed, all, ##__VA_ARGS__); \
		if (passed == i) { \
			printf("  " TEST_PASSED "  Time: %.3lfs\n", \
				(double) (time)/CLOCKS_PER_SEC); \
		} else { \
			printf("  " TEST_FAILED "  Time: %.3lfs\n", \
				(double) (time)/CLOCKS_PER_SEC); \
		} \
	} while (0)


#define _test_check(in_type, out_type, input, expected, got) \
	do { \
		if (expected == got) { \
			passed++; \
		} else { \
			printf("at input " _print_type(in_type) \
					": expected " _print_type(out_type) \
					", got " _print_type(out_type) "\n", \
				input, expected, got); \
		} \
	} while (0)

#define _test_check2(in_type, in_type2, out_type, input, input2, expected, got) \
	do { \
		if (expected == got) { \
			passed++; \
		} else { \
			printf("at input " _print_type(in_type) \
					", " _print_type(in_type2) \
					": expected " _print_type(out_type) \
					", got " _print_type(out_type) "\n", \
				input, input2, expected, got); \
		} \
	} while (0)

#define _test_file_open(fp, filename) \
	do { \
		fp = fopen("../data/" _to_string(filename) ".txt", "r"); \
		if (fp == NULL) { \
			perror(_to_string(Failed to open filename.txt)); \
			return; \
		} \
	} while (0)




/* 	Sequence tests. Has a number of input values
	and expected output values.						*/
#define SEQUENCE_TEST(output_type, function, input_type) \
	SEQUENCE_TEST_F(output_type, function, input_type, function)

#define SEQUENCE_TEST_A(output_type, function) \
	SEQUENCE_TEST_AF(output_type, function, function)

#define SEQUENCE_TEST_F(output_type, function, input_type, filename) \
	SEQUENCE_TEST_GENERAL(output_type, function, input_type, filename, function(input), )

#define SEQUENCE_TEST_AF(output_type, function, filename) \
	SEQUENCE_TEST_GENERAL(output_type, function, size_t, filename, array[input], output_type *array)

#define SEQUENCE_TEST_GENERAL(output_type, function, input_type, filename, seq_call, argument) \
	void function##_sequence_test (argument) { \
		int i, passed; \
		input_type input; \
		output_type ret_val, calc_val; \
		FILE *test_fp; \
		\
		_test_file_open(test_fp, filename); \
		for (i = 0, passed = 0;; i++) { \
			if (fscanf(test_fp, _scan_type(input_type) _scan_type(output_type), \
				&input, &ret_val) == EOF) break; \
			calc_val = seq_call; \
			_test_check(input_type, output_type, input, ret_val, calc_val); \
		} \
		fclose(test_fp); \
		_print_test_result(function, sequence, i, passed); \
	}


/* 	Set tests. Has a list of numbers and expects 
	output 1 if the number is in the list, otherwise 0 */
#define SET_TEST_F(function, input_type, filename) \
	SET_TEST_FNS(function, input_type, filename, set, 0)

#define SET_TEST_FNS(function, input_type, filename, test_name, start) \
	void function##_##test_name##_test () { \
		int i, passed, output, expected; \
		clock_t before, after; \
		input_type input, next; \
		FILE *test_fp; \
		\
		_test_file_open(test_fp, filename); \
		if (fscanf(test_fp, _scan_type(input_type), &next) == EOF) { \
			fprintf(stderr, _to_string(filename.txt is empty\n)); \
			return; \
		} \
		input = start; \
		before = clock(); \
		for (i = 0, passed = 0;; i++, input++) { \
			if (input > next) { \
				if (fscanf(test_fp, _scan_type(input_type), &next) == EOF) break; \
			} \
			if (input == next) expected = 1; \
			else expected = 0; \
			output = function(input); \
			_test_check(input_type, int, input, expected, output); \
		} \
		after = clock(); \
		fclose(test_fp); \
		_print_test_time(function, test_name, i, passed, after - before); \
	}


#define FALSE_TEST_FN(function, input_type, filename, test_name) \
	EXPECTED_TEST_FN(0, function, input_type, filename, test_name)

#define TRUE_TEST_FN(function, input_type, filename, test_name) \
	EXPECTED_TEST_FN(1, function, input_type, filename, test_name)

#define EXPECTED_TEST_FN(expected, function, input_type, filename, test_name) \
	void function##_##test_name##_test () { \
		int i, passed, output; \
		input_type input; \
		FILE *test_fp; \
		\
		_test_file_open(test_fp, filename); \
		for (i = 0, passed = 0;; i++) { \
			if (fscanf(test_fp, _scan_type(input_type), &input) == EOF) break; \
			output = function(input); \
			_test_check(input_type, int, input, expected, output); \
		} \
		fclose(test_fp); \
		_print_test_result(function, test_name, i, passed); \
	}





#define PERFORMANCE_TEST_BEGIN(func, _a, _b, _c, _m, _r, _r1, _r2) \
	void func##_perf_test (int total, uint32_t bits \
		_m##_tvar_divb(uint32_t)) { \
		int i; \
		clock_t start, end; \
		\
		_a##_tvar_int *a; \
		_b##_tvar_int *b; \
		_c##_tvar_int *c; \
		_m##_tvar_int *m; \
		\
		_r##_tvar_out r; \
		_r1##_tvar_out r1; \
		_r2##_tvar_out r2; \
		\
		set_rand(); \
		\
		_m##_tvar_divb_cond \
		\
		if (_a##_tvar_use) a = malloc(total * sizeof(_a##_tvar_int)); \
		if (_b##_tvar_use) b = malloc(total * sizeof(_b##_tvar_int)); \
		if (_c##_tvar_use) c = malloc(total * sizeof(_c##_tvar_int)); \
		if (_m##_tvar_use) m = malloc(total * sizeof(_m##_tvar_int)); \
		\
		for (i = 0; i < total; i++) { \
			if (_a##_tvar_use) a[i] = rand_bit(bits); \
			if (_b##_tvar_use) b[i] = rand_bit(bits); \
			if (_c##_tvar_use) c[i] = rand_bit(bits); \
			_Pragma("GCC diagnostic push") \
			_Pragma("GCC diagnostic ignored \"-Wunused-value\"") \
			if (_m##_tvar_use) do { \
				m[i] = rand_bit((0 _m##_tvar_divb())); \
			} while (m[i] == 0); \
			_Pragma("GCC diagnostic pop") \
		} \
		\
		start = clock(); \
		for (i = 0; i < total; i++) {


#define PERFORMANCE_TEST_END(func, _a, _b, _c, _m, _r, _r1, _r2) \
		} \
		end = clock(); \
		\
		if (_a##_tvar_use) free(a); \
		if (_b##_tvar_use) free(b); \
		if (_c##_tvar_use) free(c); \
		if (_m##_tvar_use) free(m); \
		\
		printf("%lf (seconds) " \
			"(" #func " %"PRIu32"bit" \
			_m##_tvar_divb_print \
			")\n", \
			(double) (end - start)/CLOCKS_PER_SEC, \
			bits \
			_m##_tvar_divb() \
			); \
	}


#define check_div_bits_value \
	if (div_bits == 0) { \
		fputs("ERROR: Can't find value for m with 0 div bits", \
			stderr); \
		return; \
	} \




/* dctest.c */
uint64_t rand_bit(uint64_t bits);
void set_rand();



#endif // _DCTEST_H
