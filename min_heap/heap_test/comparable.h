#pragma once
#define TEM(vptr) ((temperature*)vptr)

typedef struct {
	int degrees;
}temperature;

#ifdef _cplusplus
extern "C" {
#endif // _cplusplus

int compare_temperature(void*,void*);

int get_temperature(void* ptr);
#ifdef _cplusplus
}
#endif // _cplusplus
