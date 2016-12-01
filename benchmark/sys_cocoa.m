// 30 november 2016
#import <Cocoa/Cocoa.h>
#import <mach/mach.h>
#import <mach/mach_time.h>
#import "common.h"

int64_t benchCurrentTime(void)
{
	return (int64_t) mach_absolute_time();
}

int64_t benchOneSecond(void)
{
	mach_timebase_info_data_t mt;
	int64_t num, den;

	// should not fail; see http://stackoverflow.com/questions/31450517/what-are-the-possible-return-values-for-mach-timebase-info
	// also true on 10.12 at least: https://opensource.apple.com/source/xnu/xnu-3789.1.32/libsyscall/wrappers/mach_timebase_info.c.auto.html + https://opensource.apple.com/source/xnu/xnu-3789.1.32/osfmk/kern/clock.c.auto.html
	mach_timebase_info(&mt);
	num = (int64_t) (mt.numer);
	den = (int64_t) (mt.denom);
	return ((int64_t) 1000000000) * den / num;
}

int64_t benchTimeToNsec(int64_t c)
{
	mach_timebase_info_data_t mt;
	int64_t num, den;

	mach_timebase_info(&mt);
	num = (int64_t) (mt.numer);
	den = (int64_t) (mt.denom);
	return c * num / den;
}

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
