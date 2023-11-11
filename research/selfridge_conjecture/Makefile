CC = gcc
CFLAGS = -g -g3 -ggdb -Wall -Wextra
LIBFLAGS = -fopenmp -ldcm -lgmp -lm

SOURCEF = $(wildcard *.c)
EXEF = $(patsubst %.c,%,$(SOURCEF))

.PHONY: clean test

all: $(EXEF)

$(EXEF): %: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBFLAGS)

clean:
	find . -type f -executable -delete

