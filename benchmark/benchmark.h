// 30 november 2016
#include <stdint.h>

typedef void (*benchFunc)(int64_t n);
extern int64_t bench(benchFunc f);

extern int64_t benchCurrentTime(void);
extern int64_t benchOneSecond(void);
extern int64_t benchTimeToNsec(int64_t c);
