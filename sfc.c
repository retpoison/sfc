#include "sfc.h"

Number *new_number()
{
	Number *n = (Number *) xmalloc(sizeof(Number));
	n->len = 1;
	n->num = (char *)xmalloc(n->len * (sizeof(char)));
	n->num[0] = 1;
	return n;
}

int factorial(Number * num, int f)
{
	Number *a = new_number();
	Number *c = (Number *) xmalloc(sizeof(Number));

	for (int _ = 0; _ < f; _++) {
		multiply(a, num, c);
		num->len = c->len;
		if (c->num[c->len - 1] == 0)
			num->len--;
		free(num->num);
		num->num = c->num;
		plus_one(a);
	}

	free(a->num);
	free(a);
	free(c);
	return 0;
}

void multiply(Number * a, Number * b, Number * out)
{
	int cind, carry, n, i, j, k;
	cind = 0;
	carry = 0;
	out->len = a->len + b->len;
	out->num = (char *)xmalloc(out->len * (sizeof(char)));
	fill_zero(out);

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
			carry = (short)(n / 10);
		}
		cind++;
	}
}

void plus_one(Number * num)
{
	char carry = 0, n;
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
		    (char *)xrealloc(num->num, (num->len) * sizeof(char));
		if (num->num == NULL)
			return;
		num->num[num->len - 1] = carry;
	}
}

void fill_zero(Number * num)
{
	for (int i = 0; i < num->len; i++)
		num->num[i] = 0;
}

void print(Number * num)
{
	int i = num->len - 1;
	if (num->num[i] == 0)
		i--;

	for (; i >= 0; i--) {
		printf("%d", num->num[i]);
	}
	printf("\n");
}

void cleanup(Number * num)
{
	free(num->num);
	free(num);
}

/*
 * from https://git.suckless.org/st/file/st.c.html
 * with a few changes.
 */
void die(const char *errstr, ...)
{
	fprintf(stderr, "%s", errstr);
	exit(1);
}

void *xmalloc(size_t len)
{
	void *p;
	if ((p = malloc(len)) == NULL)
		die("malloc: %s\n", strerror(errno));
	return p;
}

void *xrealloc(void *p, size_t len)
{
	if ((p = realloc(p, len)) == NULL)
		die("realloc: %s\n", strerror(errno));
	return p;
}
