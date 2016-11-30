// 30 november 2016
#include "windows.h"
#include "benchmark.h"

// TODO we could probably make this portable

typedef struct B B;

struct B {
	void (*f)(int64_t n);
	LARGE_INTEGER duration;
	LARGE_INTEGER qpf;
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

static int64_t qpcPerOp(B *b)
{
	if (b->n <= 0)
		return 0;
	return b.duration.QuadPart / b->n;
}

static void runN(B *b, int64_t n)
{
	LARGE_INTEGER start, end;

	b->n = n;
	b->duration.QuadPart = 0;
	QueryPerformanceCounter(&start);
	(*(b->f))(b->n);
	QueryPerformanceCounter(&end);
	b->duration.QuadPart += end.QuadPart - start.QuadPart;
}

uint64_t bench(void (*f)(int64_t n))
{
	B b;
	LARGE_INTEGER qpf;
	int64_t n;
	uint64_t res;

	ZeroMemory(&b, sizeof (B));
	// this is in ticks per second, and the default maximum time is per second, so.
	QueryPerformanceFrequency(&(b.qpf));

	// first iteration
	n = 1;
	runN(&b, n);

	// and benchmark
	while (b.duration.QuadPart < b.qpf.QuadPart && n < 1000000000) {
		int64_t prevN;

		prevN = n;
		n = b.qpf.QuadPart;
		if (qpcPerOp(&b) != 0)
			n /= qpcPerOp(&b);
		n = n + (n / 5);			// 1.2x increase each time...
		if (n >= 100 * prevN)		// ...unless we went too fast...
			n = 100 * prevN;
		if (n <= prevN)			// ...or that results in a decrease
			n = prevN + 1;
		n = roundUp(n);		// and make it even
		runN(&b, n);
	}

	// now convert duration from counts to nanocounts
	res = b->duration.QuadPart;
	res *= 1000000000;

	// and finally convert from nanocounts to seconds == naonseconds
	// thanks to ValleyBell for help
	return res / b->qpf.QuadPart;
}
