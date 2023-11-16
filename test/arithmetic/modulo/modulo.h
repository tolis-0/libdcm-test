#ifndef _MODULO_TEST_H
#define _MODULO_TEST_H


#define MODULO_PERFORMANCE_START(func, desc, oddeven) \
	void func##_performance (uint64_t total, uint32_t bits) { \
	uint64_t i, *a, *b, *c, *m, __attribute__((unused)) output; \
	clock_t start, end; \
	\
	set_rand(); \
	a = (uint64_t *) malloc(total * sizeof(uint64_t)); \
	if ((desc & 0b1000) == 0b1000) \
		b = (uint64_t *) malloc(total * sizeof(uint64_t)); \
	if ((desc & 0b1100) == 0b1100) \
		c = (uint64_t *) malloc(total * sizeof(uint64_t)); \
	m = (uint64_t *) malloc(total * sizeof(uint64_t)); \
	\
	for (i = 0; i < total; i++) \
		do { \
			if (oddeven == 1) { \
				m[i] = (rand_bit(bits) | 1); \
			} else if (oddeven == 2) { \
				m[i] = (rand_bit(bits) & 0xFFFFFFFFFFFFFFFE); \
			} else { \
				m[i] = rand_bit(bits); \
			} \
		} while (m[i] == 0); \
	\
	for (i = 0; i < total; i += 2) { \
		a[i] = rand_bit(64); \
		if ((desc & 0b1000) == 0b1000) b[i] = rand_bit(64); \
		if ((desc & 0b1100) == 0b1100) c[i] = rand_bit(64); \
	} \
	\
	for (i = 1; i < total; i += 2) { \
		a[i] = rand_bit(bits); \
		if ((desc & 0b1000) == 0b1000) b[i] = rand_bit(bits); \
		if ((desc & 0b1100) == 0b1100) c[i] = rand_bit(bits); \
	} \
	\
	start = clock(); \
	for (i = 0; i < total; i++) {


#define MODULO_PERFORMANCE_END(func, desc) \
	} \
	end = clock(); \
	\
	free(a); \
	if ((desc & 0b1000) == 0b1000) free(b); \
	if ((desc & 0b1100) == 0b1100) free(c); \
	free(m); \
	\
	printf("%lf (seconds) (add_mod %"PRIu32"bit)\n", \
		(double) (end - start)/CLOCKS_PER_SEC, bits); \
	}


#endif // _MODULO_TEST_H