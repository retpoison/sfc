#include <stdlib.h>

#include "sfc.h"

int sf_factorial(Number * num, int f)
{
	Number *a = sn_new_number();
	Number *c = sn_new_number();

	for (int _ = 0; _ < f; _++) {
		sn_multiply(a, num, c);
		num->len = c->len;
		if (c->num[c->len - 1] == 0)
			num->len--;
		free(num->num);
		num->num = c->num;
		c->num = NULL;
		sn_sum(a, 1, 0);
	}

	free(a->num);
	free(a);
	free(c);
	return 0;
}
