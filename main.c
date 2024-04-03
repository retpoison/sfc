#include <stdio.h>

#include "sfc.h"

int main()
{
	Number *f = new_number();
	factorial(f, 10);
	print(f);
	cleanup(f);
	return 0;
}
