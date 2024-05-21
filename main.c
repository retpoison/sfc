#include <stdio.h>

#include "sfc.h"

int main()
{
	Number *f = sf_new_number();
	sf_factorial(f, 100);
	sf_print(f);
	sf_cleanup(f);

	Number *a = sf_new_number();
	sf_set_number(a, "125");
	Number *b = sf_new_number();
	sf_set_number(b, "951");
	Number *c = sf_new_number();
	sf_multiply(a, b, c);

	sf_print(c);
	sf_cleanup(a);
	sf_cleanup(b);
	sf_cleanup(c);
	return 0;
}
