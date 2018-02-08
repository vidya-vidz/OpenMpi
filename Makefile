#!?bin/sh

CC=gcc
CFLAGS=-O3
COPT=-std=c99
OMPFLAGS=-fopenmp

all: dgemm_seq dgemm_l1 dgemm_l2 dgemm_l3
dgemm_seq: main.o dgemm_seq.o
	$(CC) $(CFLAGS) -o $@ main.o dgemm_seq.o
dgemm_l1: main.o dgemm_l1.o
	$(CC) $(CFLAGS) $(OMPFLAGS) -o $@ main.o dgemm_l1.o
dgemm_l2: main.o dgemm_l2.o
	$(CC) $(CFLAGS) $(OMPFLAGS) -o $@ main.o dgemm_l2.o
dgemm_l3: main.o dgemm_l3.o
	$(CC) $(CFLAGS) $(OMPFLAGS) -o $@ main.o dgemm_l3.o
dgemm_seq.o: ./src/dgemm_seq.c
	$(CC) $(CFLAGS) $(COPT) -c -o $@ $<
dgemm_l1.o: ./src/dgemm_l1.c
	$(CC) $(CFLAGS) $(COPT) $(OMPFLAGS) -c -o $@ $<
dgemm_l2.o: ./src/dgemm_l1.c
	$(CC) $(CFLAGS) $(COPT) $(OMPFLAGS) -c -o $@ $<
dgemm_l3.o: ./src/dgemm_l1.c
	$(CC) $(CFLAGS) $(COPT) $(OMPFLAGS) -c -o $@ $<
main.o: ./src/main.c
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -Rf dgemm_seq dgemm_l1 dgemm_l2 dgemm_l3 ./*.o
