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

static size_t asciiBufLen = 0;
static size_t jpBufLen = 0;
static size_t emojiBufLen = 0;
static NSString *asciiBufUTF16NS;
static NSString *jpBufUTF16NS;
static NSString *emojiBufUTF16NS;

static NSString *utf16StrToNS(const uint16_t *s)
{
	const uint16_t *t;

	t = s;
	while (*t)
		t++;
	// silence compiler about constness
	return [[NSString alloc] initWithCharactersNoCopy:((unichar *) s)
		length:(t - s)
		freeWhenDone:NO];
}

void init(void)
{
	const char *t;

	asciiBufLen = 0;
	for (t = asciiBufUTF8; *t; t++)
		asciiBufLen++;
	jpBufLen = 0;
	for (t = jpBufUTF8; *t; t++)
		jpBufLen++;
	emojiBufLen = 0;
	for (t = emojiBufUTF8; *t; t++)
		emojiBufLen++;

	asciiBufUTF16NS = utf16StrToNS(asciiBufUTF16);
	jpBufUTF16NS = utf16StrToNS(jpBufUTF16);
	emojiBufUTF16NS = utf16StrToNS(emojiBufUTF16);

	if ([@"hello" lengthOfBytesUsingEncoding:NSUTF8StringEncoding] == 0)
		printf("** -[NSString lengthOfBytesUsingEncoding:NSUTF8StringEncoding] unsupported; some benchmarks might give wrong results");
	if ([@"hello" lengthOfBytesUsingEncoding:NSUTF32StringEncoding] == 0)
		printf("** -[NSString lengthOfBytesUsingEncoding:NSUTF32StringEncoding] unsupported; some benchmarks might give wrong results");
}

static NSString *utf8NoCopy(const char *buf, size_t n)
{
	// silence compiler about constness
	return [[NSString alloc] initWithBytesNoCopy:((void *) buf)
		length:n
		encoding:NSUTF8StringEncoding
		freeWhenDone:NO];
}

static void systemBenchmarkUTF8RuneCountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// silence compiler
		(void) ([utf8NoCopy(asciiBufUTF8, asciiBufLen) lengthOfBytesUsingEncoding:NSUTF32StringEncoding] / 4);
	}
}

static void systemBenchmarkUTF8UTF16CountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		[utf8NoCopy(asciiBufUTF8, asciiBufLen) length];
	}
}

static void systemBenchmarkUTF8RuneCountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		(void) ([utf8NoCopy(jpBufUTF8, jpBufLen) lengthOfBytesUsingEncoding:NSUTF32StringEncoding] / 4);
	}
}

static void systemBenchmarkUTF8UTF16CountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		[utf8NoCopy(jpBufUTF8, jpBufLen) length];
	}
}

static void systemBenchmarkUTF8RuneCountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		(void) ([utf8NoCopy(emojiBufUTF8, emojiBufLen) lengthOfBytesUsingEncoding:NSUTF32StringEncoding] / 4);
	}
}

static void systemBenchmarkUTF8UTF16CountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		[utf8NoCopy(emojiBufUTF8, emojiBufLen) length];
	}
}

static void systemBenchmarkUTF16RuneCountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		(void) ([asciiBufUTF16NS lengthOfBytesUsingEncoding:NSUTF32StringEncoding] / 4);
	}
}

static void systemBenchmarkUTF16UTF8CountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		[asciiBufUTF16NS lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
	}
}

static void systemBenchmarkUTF16RuneCountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		(void) ([jpBufUTF16NS lengthOfBytesUsingEncoding:NSUTF32StringEncoding] / 4);
	}
}

static void systemBenchmarkUTF16UTF8CountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		[jpBufUTF16NS lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
	}
}

static void systemBenchmarkUTF16RuneCountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		(void) ([emojiBufUTF16NS lengthOfBytesUsingEncoding:NSUTF32StringEncoding] / 4);
	}
}

static void systemBenchmarkUTF16UTF8CountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		[emojiBufUTF16NS lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
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
