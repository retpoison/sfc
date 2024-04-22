#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __SFC__
#define __SFC__

typedef struct {
	int len;
	char *num;
} Number;

Number *new_number();
int calculate(Number * num, int f);
int factorial(Number * num, int f);
void multiply(Number * a, Number * b, Number * out);
void plus_one(Number * num);
void fill_zero(Number * num);
void print(Number * num);
void cleanup(Number * num);

void *xmalloc(size_t len);
void *xrealloc(void *p, size_t len);
void die(const char *errstr, ...);

#endif
