#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifndef __SFC__
#define __SFC__

#define SF_MAX 1000000000
#define SF_DIGIT 9

typedef struct {
	int len;
	uint32_t *num;
} Number;

Number *sf_new_number();
int sf_calculate(Number * num, int f);
int sf_factorial(Number * num, int f);
void sf_multiply(Number * a, Number * b, Number * out);
void sf_sum(Number * num, int p, int ind);
void sf_set_number(Number * num, char *n);
void sf_fill_zero(Number * num);
void sf_print(Number * num);
void sf_cleanup(Number * num);

void *sl_xmalloc(size_t len);
void *sl_xrealloc(void *p, size_t len);
void sl_die(const char *errstr, ...);

#endif
