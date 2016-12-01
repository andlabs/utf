// 30 november 2016
#include <time.h>
#include "common.h"

// hopefully the C99-standard clock() will be enough
int64_t benchCurrentTime(void)
{
	return ((int64_t) clock()) * 1000000000;
}

int64_t benchOneSecond(void)
{
	return ((int64_t) CLOCKS_PER_SEC) * 1000000000;
}

int64_t benchTimeToNsec(int64_t c)
{
	return c / CLOCKS_PER_SEC;
}

void init(void)
{
	// do nothing
}

#define systemBenchmarkUTF8RuneCountASCIIBuf NULL

#define systemBenchmarkUTF8UTF16CountASCIIBuf NULL

#define systemBenchmarkUTF8RuneCountJPBuf NULL

#define systemBenchmarkUTF8UTF16CountJPBuf NULL

#define systemBenchmarkUTF8RuneCountEmojiBuf NULL

#define systemBenchmarkUTF8UTF16CountEmojiBuf NULL

#define systemBenchmarkUTF16RuneCountASCIIBuf NULL

#define systemBenchmarkUTF16UTF8CountASCIIBuf NULL

#define systemBenchmarkUTF16RuneCountJPBuf NULL

#define systemBenchmarkUTF16UTF8CountJPBuf NULL

#define systemBenchmarkUTF16RuneCountEmojiBuf NULL

#define systemBenchmarkUTF16UTF8CountEmojiBuf NULL

#define systemBenchmarkUTF8EncodeRuneASCII NULL

#define systemBenchmarkUTF8EncodeRuneJP NULL

#define systemBenchmarkUTF8EncodeRuneEmoji NULL

#define systemBenchmarkUTF16EncodeRuneASCII NULL

#define systemBenchmarkUTF16EncodeRuneJP NULL

#define systemBenchmarkUTF16EncodeRuneEmoji NULL

#define systemBenchmarkUTF8DecodeRuneASCII NULL

#define systemBenchmarkUTF8DecodeRuneJP NULL

#define systemBenchmarkUTF8DecodeRuneEmoji NULL

#define systemBenchmarkUTF16DecodeRuneASCII NULL

#define systemBenchmarkUTF16DecodeRuneJP NULL

#define systemBenchmarkUTF16DecodeRuneEmoji NULL

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
