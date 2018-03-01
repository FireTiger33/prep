#include "simple.h"

int custom_is_simple(int number) {
	if(number < 2)
		return 0;
	int div = 1;
	while(++div != number)
		if(!(number % div))
			return 0;
	return 1;
}
