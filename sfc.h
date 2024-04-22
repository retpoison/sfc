#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifndef __SFC__
#define __SFC__

typedef uint8_t uint8;
typedef struct {
	int len;
	uint8 *num;
} Number;

Number *sf_new_number();
int sf_calculate(Number * num, int f);
int sf_factorial(Number * num, int f);
void sf_multiply(Number * a, Number * b, Number * out);
void sf_plus_one(Number * num);
void sf_fill_zero(Number * num);
void sf_print(Number * num);
void sf_cleanup(Number * num);

void *sl_xmalloc(size_t len);
void *sl_xrealloc(void *p, size_t len);
void sl_die(const char *errstr, ...);

#endif
