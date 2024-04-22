#include "sfc.h"

Number *sf_new_number()
{
	Number *n = (Number *) sl_xmalloc(sizeof(Number));
	n->len = 1;
	n->num = (uint8 *) sl_xmalloc(n->len * (sizeof(uint8)));
	n->num[0] = 1;
	return n;
}

int sf_factorial(Number * num, int f)
{
	Number *a = sf_new_number();
	Number *c = (Number *) sl_xmalloc(sizeof(Number));

	for (int _ = 0; _ < f; _++) {
		sf_multiply(a, num, c);
		num->len = c->len;
		if (c->num[c->len - 1] == 0)
			num->len--;
		free(num->num);
		num->num = c->num;
		sf_plus_one(a);
	}

	free(a->num);
	free(a);
	free(c);
	return 0;
}

void sf_multiply(Number * a, Number * b, Number * out)
{
	int i, j;
	uint8 cind, carry, n, k;
	cind = 0;
	carry = 0;
	out->len = a->len + b->len;
	out->num = (uint8 *) sl_xmalloc(out->len * (sizeof(uint8)));
	sf_fill_zero(out);

	for (i = 0; i < a->len; i++) {
		for (j = 0; j < b->len; j++) {
			n = a->num[i] * b->num[j] + out->num[j + cind]
			    + carry;
			out->num[j + cind] = n % 10;
			carry = (int)(n / 10);
		}
		for (k = j + cind; carry != 0; k++) {
			n = out->num[k] + carry;
			out->num[k] = n % 10;
			carry = (uint8) (n / 10);
		}
		cind++;
	}
}

void sf_plus_one(Number * num)
{
	uint8 carry = 0, n;
	int ind = 0;
	do {
		n = num->num[ind] + 1;
		num->num[ind] = n % 10;
		carry = n / 10;
		ind++;
	}
	while (carry != 0 && ind < num->len);

	if (ind == num->len && carry != 0) {
		num->len++;
		num->num =
		    (uint8 *) sl_xrealloc(num->num, (num->len) * sizeof(uint8));
		if (num->num == NULL)
			return;
		num->num[num->len - 1] = carry;
	}
}

void sf_fill_zero(Number * num)
{
	int i;
	for (i = 0; i < num->len; i++)
		num->num[i] = 0;
}

void sf_print(Number * num)
{
	int i = num->len - 1;
	if (num->num[i] == 0)
		i--;

	for (; i >= 0; i--) {
		printf("%d", num->num[i]);
	}
	printf("\n");
}

void sf_cleanup(Number * num)
{
	free(num->num);
	free(num);
}

/*
 * from https://git.suckless.org/st/file/st.c.html
 * with a few changes.
 */
void sl_die(const char *errstr, ...)
{
	fprintf(stderr, "%s", errstr);
	exit(1);
}

void *sl_xmalloc(size_t len)
{
	void *p;
	if ((p = malloc(len)) == NULL)
		sl_die("malloc: %s\n", strerror(errno));
	return p;
}

void *sl_xrealloc(void *p, size_t len)
{
	if ((p = realloc(p, len)) == NULL)
		sl_die("realloc: %s\n", strerror(errno));
	return p;
}
