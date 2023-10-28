#ifndef _MODULO_TEST_H
#define _MODULO_TEST_H


#define MODULO_PERFORMANCE_START(func, desc) \
	void func##_performance (uint64_t total, uint32_t bits) { \
	uint64_t i, *a, *b, *c, *m, output; \
	clock_t start, end; \
	\
	set_rand(); \
	a = (uint64_t *) malloc(total * sizeof(uint64_t)); \
	dsc_msk(desc, 0b1000) b = (uint64_t *) malloc(total * sizeof(uint64_t)); \
	dsc_msk(desc, 0b1100) c = (uint64_t *) malloc(total * sizeof(uint64_t)); \
	m = (uint64_t *) malloc(total * sizeof(uint64_t)); \
	\
	for (i = 0; i < total; i++) \
		do { \
			m[i] = rand_bit(bits); \
		} while (m[i] == 0); \
	\
	for (i = 0; i < total; i += 2) { \
		a[i] = rand_bit(64); \
		dsc_msk(desc, 0b1000) b[i] = rand_bit(64); \
		dsc_msk(desc, 0b1100) c[i] = rand_bit(64); \
	} \
	\
	for (i = 1; i < total; i += 2) { \
		a[i] = rand_bit(bits); \
		dsc_msk(desc, 0b1000) b[i] = rand_bit(bits); \
		dsc_msk(desc, 0b1100) c[i] = rand_bit(bits); \
	} \
	\
	start = clock(); \
	for (i = 0; i < total; i++) {


#define MODULO_PERFORMANCE_END(func, desc) \
	} \
	end = clock(); \
	\
	free(a); \
	dsc_msk(desc, 0b1000) free(b); \
	dsc_msk(desc, 0b1100) free(c); \
	free(m); \
	\
	printf("%lf (seconds) (add_mod %"PRIu32"bit)\n", \
		(double) (end - start)/CLOCKS_PER_SEC, bits); \
	}


#endif // _MODULO_TEST_H