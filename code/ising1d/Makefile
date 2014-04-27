CC=g++
CFLAGS=-Wall -Wextra -O2 -march=native

all: ising1d
ising1d: main.cpp ising1d.cpp
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf ising1d libising.a
