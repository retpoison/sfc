#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "number.h"

Number *
sn_new_number(void)
{
	Number *n = (Number *) sl_xmalloc(sizeof(Number));
	n->num = NULL;
	sn_set_number(n, "1");
	return n;
}

void
sn_multiply(Number * num, int p1, int p2, int ind)
{
	uint64_t n = (uint64_t) p1 * p2, carry = 0;

	do {
		n += num->num[ind] + carry;
		num->num[ind] = n % SF_MAX;
		carry = n / SF_MAX;
		ind++;
		n = 0;
	} while (carry != 0 && ind < num->len);

	sn_check_carry(num, carry, ind);
}

void
sn_nmultiply(Number * a, Number * b, Number * out)
{
	int i, j;
	uint64_t cind = 0;

	out->len = a->len + b->len;
	sn_allocate_number(out);

	for (i = 0; i < a->len; i++) {
		for (j = 0; j < b->len; j++) {
			sn_multiply(out, a->num[i], b->num[j], j + cind);
		}
		cind++;
	}
}

void
sn_sum(Number * num, int p, int ind)
{
	uint32_t n;
	do {
		n = num->num[ind] + p;
		num->num[ind] = n % SF_MAX;
		p = n / SF_MAX;
		ind++;
	}
	while (p != 0 && ind < num->len);

	sn_check_carry(num, p, ind);
}

void
sn_nsum(Number * a, Number * b, Number * out)
{
	int i, s;
	Number *bn;

	if (a->len > b->len) {
		bn = a;
		s = b->len;
		bn = a;
	} else {
		bn = b;
		s = a->len;
		bn = b;
	}
	out->len = ((a->len > b->len) ? a->len : b->len) + 1;
	sn_allocate_number(out);

	for (i = 0; i < s; i++) {
		sn_sum(out, a->num[i] + b->num[i], i);
	}
	for (; i < out->len - 1; i++) {
		sn_sum(out, bn->num[i], i);
	}
}

void
sn_set_number(Number * num, char *n)
{
	int i, len = strlen(n);

	num->len = len / SF_DIGIT + 1;
	sn_allocate_number(num);

	for (i = 0; i < len; i++) {
		sn_sum(num, (n[len - i - 1] - '0') * pow(10, i % SF_DIGIT),
		       i / SF_DIGIT);
	}
}

void
sn_allocate_number(Number * num)
{
	if (num->num != NULL)
		free(num->num);
	num->num = (uint32_t *) sl_xmalloc(num->len * (sizeof(uint32_t)));
	sn_fill_zero(num);
}

void
sn_fill_zero(Number * num)
{
	int i;
	for (i = 0; i < num->len; i++)
		num->num[i] = 0;
}

void
sn_print(Number * num)
{
	int i = num->len - 1;
	while (num->num[i] == 0)
		i--;
	printf("%d", num->num[i--]);
	for (; i >= 0; i--) {
		printf("%09d", num->num[i]);
	}
	printf("\n");
}

void
sn_cleanup(Number * num)
{
	if (num->num != NULL)
		free(num->num);
	free(num);
}

void
sn_check_carry(Number * num, uint64_t carry, int ind)
{
	if (ind == num->len && carry != 0) {
		num->len++;
		num->num = (uint32_t *)
		    sl_xrealloc(num->num, (num->len) * sizeof(uint32_t));
		num->num[num->len - 1] = carry;
	}
}

/*
 * from https://git.suckless.org/st/file/st.c.html
 * with a few changes.
 */
void
sl_die(const char *errstr, ...)
{
	fprintf(stderr, "%s", errstr);
	exit(1);
}

void *
sl_xmalloc(size_t len)
{
	void *p;
	if ((p = malloc(len)) == NULL)
		sl_die("malloc: %s\n", strerror(errno));
	return p;
}

void *
sl_xrealloc(void *p, size_t len)
{
	if ((p = realloc(p, len)) == NULL)
		sl_die("realloc: %s\n", strerror(errno));
	return p;
}
