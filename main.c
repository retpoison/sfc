#include <stdio.h>

#include "sfc.h"

int
main()
{
	Number *f = sn_new_number();
	sf_factorial(f, 1500);
	sn_print(f);
	sn_cleanup(f);
	f = NULL;

	Number *a = sn_new_number();
	sn_set_number(a, "125");
	Number *b = sn_new_number();
	sn_set_number(b, "951");
	Number *c = sn_new_number();
	sn_nmultiply(a, b, c);

	sn_print(c);
	sn_cleanup(a);
	a = NULL;
	sn_cleanup(b);
	b = NULL;
	sn_cleanup(c);
	c = NULL;
	return 0;
}
