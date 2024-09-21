CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -Wno-unused-parameter -O2
LDFLAGS= -lm
all: sfc

%.o: %.c
	$(CC) $(CFLAGS) -c $^

sfc: number.o sfc.o
	$(CC) $(CFLAGS) main.c -o $@ $^ $(LDFLAGS)

clean:
	rm -vf sfc *.o 

