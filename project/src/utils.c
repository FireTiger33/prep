#include <string.h>
#include "utils.h"

size_t custom_strlen(const char* str) {
	unsigned int strlen = 0;
	while(str[strlen] != '\0') {
		strlen++;
	}
	return strlen;
}

int custom_pow(int base, int power) {
	if(base == 1 || power == 0) {
		return 1;
	}
	int i = 1;
	long result = base;
	for(; i < power; i++) {
		result *= base;
	}
	return result;
}

