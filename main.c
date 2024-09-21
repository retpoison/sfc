#include <stdio.h>

#include "sfc.h"

int
main()
{
	Number *f = sn_new_number();
	sf_factorial(f, 1500);
	printf("factorial of 1500:\n");
	sn_print(f, '\n');
	sn_cleanup(f);
	f = NULL;

	Number *a = sn_new_number();
	sn_set_number(a, "1252");
	Number *b = sn_new_number();
	sn_set_number(b, "95163");
	Number *c = sn_new_number();

	sn_nmultiply(a, b, c);
	printf("multiply ");
	sn_print(a, ' ');
	printf("by ");
	sn_print(b, ':');
	printf("\n");
	sn_print(c, '\n');

	sn_nsum(a, b, c);
	printf("sum of ");
	sn_print(a, ' ');
	printf("and ");
	sn_print(b, ':');
	printf("\n");
	sn_print(c, '\n');

	sn_cleanup(a);
	a = NULL;
	sn_cleanup(b);
	b = NULL;
	sn_cleanup(c);
	c = NULL;
	return 0;
}
