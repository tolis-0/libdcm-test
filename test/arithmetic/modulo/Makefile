CC = gcc
CFLAGS = -g -g3 -ggdb -Wall -Wextra
LIBFLAGS = -ldcm -lgmp -lm

SOURCEF = $(wildcard *.c)
EXEF = $(patsubst %.c,%,$(SOURCEF))
TESTLIB = ../../dctest.c

.PHONY: clean test

all: $(EXEF)

$(EXEF): %: %.c
	$(CC) $(CFLAGS) -o $@ $< $(TESTLIB) $(LIBFLAGS)

clean:
	find . -type f -executable -delete
	rm -f perf.data perf.data.old

