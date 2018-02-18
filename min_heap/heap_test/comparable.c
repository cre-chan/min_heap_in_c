#include "stdafx.h"
#include "comparable.h"


#define D(a) (a->degrees)

int compare_temperature(void* a,void* b) {
	temperature* _a=a, *_b=b;
	if (D(_a) > D(_b))return 1;
	else if (D(_a) == D(_b)) return 0;
	else  return -1;
}

int get_temperature(void* ptr) {
	temperature* copy = ptr;
	return copy->degrees;
}