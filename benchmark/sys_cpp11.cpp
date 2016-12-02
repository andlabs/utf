// 30 november 2016
#include <codecvt>
#include <chrono>
// change any definition to #define name NULL if it should not be defined
extern "C" {
#include "common.h"
}

template<typename T> static int64_t nowToNsec(T now)
{
	typename T::duration d;

	d = now.time_since_epoch();
	return std::chrono::nanoseconds(d).count();
}

int64_t benchCurrentTime(void)
{
	if (std::chrono::high_resolution_clock::is_steady)
		return nowToNsec(std::chrono::high_resolution_clock::now());
	return nowToNsec(std::chrono::steady_clock::now());
}

int64_t benchOneSecond(void)
{
	return 1000000000;
}

int64_t benchTimeToNsec(int64_t c)
{
	return c;		// already nanoseconds
}

static std::codecvt_utf8_utf16<char16_t> cvtUTF8UTF16;
static std::codecvt_utf8<char32_t> cvtUTF8Rune;
static std::codecvt_utf16<char32_t> cvtUTF16Rune;

void init(void)
{
	// code here
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
