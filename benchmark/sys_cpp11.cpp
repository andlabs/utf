// 30 november 2016
#include <codecvt>
#include <locale>
#include <chrono>
#include <type_traits>
extern "C" {
#include <stdio.h>
#include "common.h"
}

// thanks to a lot of people in freenode ##c++ for help

// the high resolution clock does not need to be steady
// this is a benchmark; prefer steadiness (TODO does Go?)
// don't do this check at runtime every time
// the extra template is to deal with MSVC 2013
template<class Unused> using steadyClockT = typename std::conditional<
	std::chrono::high_resolution_clock::is_steady,
	std::chrono::high_resolution_clock,
	std::chrono::steady_clock>::type;
using steadyClock = steadyClockT<int>;

int64_t benchCurrentTime(void)
{
	steadyClock::time_point now;
	steadyClock::time_point::duration d;

	now = steadyClock::now();
	d = now.time_since_epoch();
	return std::chrono::nanoseconds(d).count();
}

int64_t benchOneSecond(void)
{
	return 1000000000;
}

int64_t benchTimeToNsec(int64_t c)
{
	return c;		// already nanoseconds
}

typedef std::codecvt_utf8_utf16<char16_t> typeUTF8UTF16;
typedef std::codecvt_utf8<char32_t> typeUTF8Rune;
typedef std::codecvt_utf16<char32_t> typeUTF16Rune;

static typeUTF8UTF16 cvtUTF8UTF16;
static typeUTF8Rune cvtUTF8Rune;
static typeUTF16Rune cvtUTF16Rune;

// TODO does this impact performance?
static std::wstring_convert<typeUTF8UTF16, char16_t> wcvtUTF8UTF16;
static std::wstring_convert<typeUTF8Rune, char32_t> wcvtUTF8Rune;

static char32_t encodeASCIIUTF32[1] = { (char32_t) encodeASCII };
static char32_t encodeJPUTF32[1] = { (char32_t) encodeJP };
static char32_t encodeEmojiUTF32[1] = { (char32_t) encodeEmoji };

void init(void)
{
	if (std::chrono::high_resolution_clock::is_steady)
		printf("benchmarking with std::high_resolution_clock\n");
	else
		printf("benchmarking with std::steady_clock\n");
}

static void systemBenchmarkUTF8RuneCountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		wcvtUTF8Rune.from_bytes(asciiBufUTF8).size();
	}
}

static void systemBenchmarkUTF8UTF16CountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		wcvtUTF8UTF16.from_bytes(asciiBufUTF8).size();
	}
}

static void systemBenchmarkUTF8RuneCountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		wcvtUTF8Rune.from_bytes(jpBufUTF8).size();
	}
}

static void systemBenchmarkUTF8UTF16CountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		wcvtUTF8UTF16.from_bytes(jpBufUTF8).size();
	}
}

static void systemBenchmarkUTF8RuneCountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		wcvtUTF8Rune.from_bytes(emojiBufUTF8).size();
	}
}

static void systemBenchmarkUTF8UTF16CountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		wcvtUTF8UTF16.from_bytes(emojiBufUTF8).size();
	}
}

#define systemBenchmarkUTF16RuneCountASCIIBuf NULL

static void systemBenchmarkUTF16UTF8CountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// silence compiler about signedness
		wcvtUTF8UTF16.to_bytes(reinterpret_cast<const char16_t *>(asciiBufUTF16)).size();
	}
}

#define systemBenchmarkUTF16RuneCountJPBuf NULL

static void systemBenchmarkUTF16UTF8CountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		wcvtUTF8UTF16.to_bytes(reinterpret_cast<const char16_t *>(jpBufUTF16)).size();
	}
}

#define systemBenchmarkUTF16RuneCountEmojiBuf NULL

static void systemBenchmarkUTF16UTF8CountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		wcvtUTF8UTF16.to_bytes(reinterpret_cast<const char16_t *>(emojiBufUTF16)).size();
	}
}

static void systemBenchmarkUTF8EncodeRuneASCII(int64_t n)
{
	int64_t i;
	char buf[4];
	const char32_t *fromNext;
	char *toNext;

	for (i = 0; i < n; i++) {
		// TODO discount state reset from benchmark?
		std::mbstate_t mb = std::mbstate_t();

		// TODO error check
		cvtUTF8Rune.out(mb,
			encodeASCIIUTF32, encodeASCIIUTF32 + 1, fromNext,
			buf, buf + 4, toNext);
	}
}

static void systemBenchmarkUTF8EncodeRuneJP(int64_t n)
{
	int64_t i;
	char buf[4];
	const char32_t *fromNext;
	char *toNext;

	for (i = 0; i < n; i++) {
		// TODO discount state reset from benchmark?
		std::mbstate_t mb = std::mbstate_t();

		// TODO error check
		cvtUTF8Rune.out(mb,
			encodeJPUTF32, encodeJPUTF32 + 1, fromNext,
			buf, buf + 4, toNext);
	}
}

static void systemBenchmarkUTF8EncodeRuneEmoji(int64_t n)
{
	int64_t i;
	char buf[4];
	const char32_t *fromNext;
	char *toNext;

	for (i = 0; i < n; i++) {
		// TODO discount state reset from benchmark?
		std::mbstate_t mb = std::mbstate_t();

		// TODO error check
		cvtUTF8Rune.out(mb,
			encodeEmojiUTF32, encodeEmojiUTF32 + 1, fromNext,
			buf, buf + 4, toNext);
	}
}

static void systemBenchmarkUTF16EncodeRuneASCII(int64_t n)
{
	int64_t i;
	char buf[4];		// note: std::codecvt_utf16 stores UTF-16 in bytes :/
	const char32_t *fromNext;
	char *toNext;

	for (i = 0; i < n; i++) {
		// TODO discount state reset from benchmark?
		std::mbstate_t mb = std::mbstate_t();

		// TODO error check
		cvtUTF16Rune.out(mb,
			encodeASCIIUTF32, encodeASCIIUTF32 + 1, fromNext,
			buf, buf + 4, toNext);
	}
}

static void systemBenchmarkUTF16EncodeRuneJP(int64_t n)
{
	int64_t i;
	char buf[4];
	const char32_t *fromNext;
	char *toNext;

	for (i = 0; i < n; i++) {
		// TODO discount state reset from benchmark?
		std::mbstate_t mb = std::mbstate_t();

		// TODO error check
		cvtUTF16Rune.out(mb,
			encodeJPUTF32, encodeJPUTF32 + 1, fromNext,
			buf, buf + 4, toNext);
	}
}

static void systemBenchmarkUTF16EncodeRuneEmoji(int64_t n)
{
	int64_t i;
	char buf[4];
	const char32_t *fromNext;
	char *toNext;

	for (i = 0; i < n; i++) {
		// TODO discount state reset from benchmark?
		std::mbstate_t mb = std::mbstate_t();

		// TODO error check
		cvtUTF16Rune.out(mb,
			encodeEmojiUTF32, encodeEmojiUTF32 + 1, fromNext,
			buf, buf + 4, toNext);
	}
}

static void systemBenchmarkUTF8DecodeRuneASCII(int64_t n)
{
	int64_t i;
	char32_t buf[1];
	const char *fromNext;
	char32_t *toNext;

	for (i = 0; i < n; i++) {
		// TODO discount state reset from benchmark?
		std::mbstate_t mb = std::mbstate_t();

		// TODO error check
		cvtUTF8Rune.in(mb,
			asciiDecodeUTF8, asciiDecodeUTF8 + 1, fromNext,
			buf, buf + 1, toNext);
	}
}

static void systemBenchmarkUTF8DecodeRuneJP(int64_t n)
{
	int64_t i;
	char32_t buf[1];
	const char *fromNext;
	char32_t *toNext;

	for (i = 0; i < n; i++) {
		// TODO discount state reset from benchmark?
		std::mbstate_t mb = std::mbstate_t();

		// TODO error check
		cvtUTF8Rune.in(mb,
			jpDecodeUTF8, jpDecodeUTF8 + 3, fromNext,
			buf, buf + 1, toNext);
	}
}

static void systemBenchmarkUTF8DecodeRuneEmoji(int64_t n)
{
	int64_t i;
	char32_t buf[1];
	const char *fromNext;
	char32_t *toNext;

	for (i = 0; i < n; i++) {
		// TODO discount state reset from benchmark?
		std::mbstate_t mb = std::mbstate_t();

		// TODO error check
		cvtUTF8Rune.in(mb,
			emojiDecodeUTF8, emojiDecodeUTF8 + 4, fromNext,
			buf, buf + 1, toNext);
	}
}

static void systemBenchmarkUTF16DecodeRuneASCII(int64_t n)
{
	int64_t i;
	char32_t buf[1];
	const char *from = reinterpret_cast<const char *>(asciiDecodeUTF16);
	const char *fromNext;
	char32_t *toNext;

	for (i = 0; i < n; i++) {
		// TODO discount state reset from benchmark?
		std::mbstate_t mb = std::mbstate_t();

		// TODO error check
		cvtUTF16Rune.in(mb,
			from, from + 2, fromNext,
			buf, buf + 1, toNext);
	}
}

static void systemBenchmarkUTF16DecodeRuneJP(int64_t n)
{
	int64_t i;
	char32_t buf[1];
	const char *from = reinterpret_cast<const char *>(jpDecodeUTF16);
	const char *fromNext;
	char32_t *toNext;

	for (i = 0; i < n; i++) {
		// TODO discount state reset from benchmark?
		std::mbstate_t mb = std::mbstate_t();

		// TODO error check
		cvtUTF16Rune.in(mb,
			from, from + 2, fromNext,
			buf, buf + 1, toNext);
	}
}

static void systemBenchmarkUTF16DecodeRuneEmoji(int64_t n)
{
	int64_t i;
	char32_t buf[1];
	const char *from = reinterpret_cast<const char *>(emojiDecodeUTF16);
	const char *fromNext;
	char32_t *toNext;

	for (i = 0; i < n; i++) {
		// TODO discount state reset from benchmark?
		std::mbstate_t mb = std::mbstate_t();

		// TODO error check
		cvtUTF16Rune.in(mb,
			from, from + 4, fromNext,
			buf, buf + 1, toNext);
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
