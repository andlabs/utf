// 30 november 2016
#include <stdint.h>

typedef void (*benchFunc)(int64_t n);
extern uint64_t bench(benchFunc f);
