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
sn_multiply(Number * a, Number * b, Number * out)
{
	int i, j;
	uint8_t cind = 0;
	uint64_t n, carry = 0, k;

	out->len = a->len + b->len;
	if (out->num != NULL)
		free(out->num);
	out->num = (uint32_t *) sl_xmalloc(out->len * (sizeof(uint32_t)));
	sn_fill_zero(out);

	for (i = 0; i < a->len; i++) {
		for (j = 0; j < b->len; j++) {
			n = (uint64_t) a->num[i] * b->num[j] +
			    out->num[j + cind] + carry;
			out->num[j + cind] = n % SF_MAX;
			carry = n / SF_MAX;
		}
		for (k = j + cind; carry != 0; k++) {
			n = out->num[k] + carry;
			out->num[k] = n % SF_MAX;
			carry = n / SF_MAX;
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

	if (ind == num->len && p != 0) {
		num->len++;
		num->num = (uint32_t *)
		    sl_xrealloc(num->num, (num->len) * sizeof(uint32_t));
		num->num[num->len - 1] = p;
	}
}

void
sn_set_number(Number * num, char *n)
{
	int i, len = strlen(n);
	if (num->num != NULL)
		free(num->num);

	num->len = len / SF_DIGIT + 1;
	num->num = (uint32_t *) sl_xmalloc(num->len * (sizeof(uint32_t)));
	sn_fill_zero(num);

	for (i = 0; i < len; i++) {
		sn_sum(num, (n[len - i - 1] - '0') * pow(10, i % SF_DIGIT),
		       i / SF_DIGIT);
	}
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
	if (num->num[i] == 0)
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
