// 30 november 2016
#define UNICODE
#define _UNICODE
#define STRICT
#define STRICT_TYPED_ITEMIDS
#define WINVER			0x0501
#define _WIN32_WINNT		0x0501
#define _WIN32_WINDOWS	0x0501
#define _WIN32_IE			0x0600
#define NTDDI_VERSION		0x05010000
#include <windows.h>
#include "common.h"

int64_t benchCurrentTime(void)
{
	LARGE_INTEGER qpc;

	QueryPerformanceCounter(&qpc);
	return qpc.QuadPart;
}

int64_t benchOneSecond(void)
{
	LARGE_INTEGER qpf;

	// this is in ticks per second, and the default maximum time is one second, so.
	QueryPerformanceFrequency(&qpf);
	return qpf.QuadPart;
}

int64_t benchTimeToNsec(int64_t c)
{
	int64_t res;

	// convert duration from counts to nanocounts
	res = c * 1000000000;

	// and convert from nanocounts to naonseconds
	// benchOneSecond() only calls QueryPerformanceFrequency() so let's just use it directly
	// thanks to ValleyBell for help
	res /= benchOneSecond();

	return res;
}

void init(void)
{
	// TODO call benchOneSecond() here
}

static void systemBenchmarkUTF8RuneCountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF8UTF16CountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF8RuneCountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF8UTF16CountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF8RuneCountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF8UTF16CountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF16RuneCountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF16UTF8CountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF16RuneCountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF16UTF8CountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF16RuneCountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF16UTF8CountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF8EncodeRuneASCII(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF8EncodeRuneJP(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF8EncodeRuneEmoji(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF16EncodeRuneASCII(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF16EncodeRuneJP(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF16EncodeRuneEmoji(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF8DecodeRuneASCII(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF8DecodeRuneJP(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF8DecodeRuneEmoji(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF16DecodeRuneASCII(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF16DecodeRuneJP(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

static void systemBenchmarkUTF16DecodeRuneEmoji(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// code here
	}
}

const benchFunc systemBenchFuncs[] = {
	systemBenchmarkUTF8RuneCountASCIIBuf,
	systemBenchmarkUTF8UTF16CountASCIIBuf,
	systemBenchmarkUTF8RuneCountJPBuf,
	systemBenchmarkUTF8UTF16CountJPBuf,
	systemBenchmarkUTF8RuneCountEmojiBuf,
	systemBenchmarkUTF8UTF16CountEmojiBuf,
	systemBenchmarkUTF16RuneCountASCIIBuf,
	systemBenchmarkUTF16UTF8CountASCIIBuf,
	systemBenchmarkUTF16RuneCountJPBuf,
	systemBenchmarkUTF16UTF8CountJPBuf,
	systemBenchmarkUTF16RuneCountEmojiBuf,
	systemBenchmarkUTF16UTF8CountEmojiBuf,
	systemBenchmarkUTF8EncodeRuneASCII,
	systemBenchmarkUTF8EncodeRuneJP,
	systemBenchmarkUTF8EncodeRuneEmoji,
	systemBenchmarkUTF16EncodeRuneASCII,
	systemBenchmarkUTF16EncodeRuneJP,
	systemBenchmarkUTF16EncodeRuneEmoji,
	systemBenchmarkUTF8DecodeRuneASCII,
	systemBenchmarkUTF8DecodeRuneJP,
	systemBenchmarkUTF8DecodeRuneEmoji,
	systemBenchmarkUTF16DecodeRuneASCII,
	systemBenchmarkUTF16DecodeRuneJP,
	systemBenchmarkUTF16DecodeRuneEmoji,
};
