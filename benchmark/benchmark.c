// 30 november 2016
#include <string.h>
#include "benchmark.h"

// TODO we could probably make this portable

typedef struct B B;

struct B {
	benchFunc f;
	int64_t duration;
	int64_t oneSecond;
	int64_t n;
};

// make n nice and round by turning it into a multiple of a power of 10
static int64_t roundUp(int64_t n)
{
	int64_t base, tens, i;

	tens = 0;
	base = n;
	while (base >= 10) {
		base /= 10;
		tens++;
	}
	base = 1;
	for (i = 0; i < tens; i++)
		base *= 10;

	if (n <= base)
		return base;
	if (n <= 2 * base)
		return 2 * base;
	if (n <= 3 * base)
		return 3 * base;
	if (n <= 5 * base)
		return 5 * base;
	return 10 * base;
}

static int64_t timePerOp(B *b)
{
	if (b->n <= 0)
		return 0;
	return b->duration / b->n;
}

static void runN(B *b, int64_t n)
{
	int64_t start, end;

	b->n = n;
	b->duration = 0;
	start = benchCurrentTime();
	(*(b->f))(b->n);
	end = benchCurrentTime();
	b->duration += end - start;
}

int64_t bench(benchFunc f)
{
	B b;
	int64_t n;

	memset(&b, 0, sizeof (B));
	b.f = f;
	b.oneSecond = benchOneSecond();

	// first iteration
	n = 1;
	runN(&b, n);

	// and benchmark
	while (b.duration < b.oneSecond && n < 1000000000) {
		int64_t prevN;

		prevN = n;
		n = b.oneSecond;
		if (timePerOp(&b) != 0)
			n /= timePerOp(&b);
		n = n + (n / 5);			// 1.2x increase each time...
		if (n >= 100 * prevN)		// ...unless we went too fast...
			n = 100 * prevN;
		if (n <= prevN)			// ...or that results in a decrease
			n = prevN + 1;
		n = roundUp(n);		// and make it even
		runN(&b, n);
	}

	return benchTimeToNsec(b.duration) / b.n;
}
