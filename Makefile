CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2

all: main

main: main.c String.c String.h
	$(CC) $(CFLAGS) -o $@ main.c String.c

tests/test_string: tests/test_string.c String.c String.h
	$(CC) $(CFLAGS) -o $@ tests/test_string.c String.c -lm

test: tests/test_string
	./tests/test_string

clean:
	rm -f main main.exe tests/test_string tests/test_string.exe

.PHONY: all test clean
