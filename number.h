#include <stdint.h>
#include <stdio.h>

#ifndef __SFC_NUM__
#define __SFC_NUM__

#define SF_MAX 1000000000
#define SF_DIGIT 9

typedef struct {
	int len;
	uint32_t *num;
} Number;

Number *sn_new_number(void);
void sn_multiply(Number * a, Number * b, Number * out);
void sn_sum(Number * num, int p, int ind);
void sn_set_number(Number * num, char *n);
void sn_fill_zero(Number * num);
void sn_print(Number * num);
void sn_cleanup(Number * num);

void *sl_xmalloc(size_t len);
void *sl_xrealloc(void *p, size_t len);
void sl_die(const char *errstr, ...);

#endif
