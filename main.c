#include <stdio.h>

#include "sfc.h"

int main()
{
	Number *f = sf_new_number();
	sf_factorial(f, 10);
	sf_print(f);
	sf_cleanup(f);
	return 0;
}
