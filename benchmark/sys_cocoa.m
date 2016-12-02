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
static uint32_t encodeASCIIUTF32[1] = { encodeASCII };
static uint32_t encodeJPUTF32[1] = { encodeJP };
static uint32_t encodeEmojiUTF32[1] = { encodeEmoji };
static NSString *asciiDecodeUTF8NS;
static NSString *jpDecodeUTF8NS;
static NSString *emojiDecodeUTF8NS;
static NSString *asciiDecodeUTF16NS;
static NSString *jpDecodeUTF16NS;
static NSString *emojiDecodeUTF16NS;

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

static NSString *utf8NoCopy(const char *buf, size_t n)
{
	// silence compiler about constness
	return [[NSString alloc] initWithBytesNoCopy:((void *) buf)
		length:n
		encoding:NSUTF8StringEncoding
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

	asciiDecodeUTF8NS = utf8NoCopy(asciiDecodeUTF8, 1);
	jpDecodeUTF8NS = utf8NoCopy(jpDecodeUTF8, 3);
	emojiDecodeUTF8NS = utf8NoCopy(emojiDecodeUTF8, 4);

	asciiDecodeUTF16NS = [[NSString alloc] initWithCharactersNoCopy:((unichar *) asciiDecodeUTF16)
		length:1
		freeWhenDone:NO];
	jpDecodeUTF16NS = [[NSString alloc] initWithCharactersNoCopy:((unichar *) jpDecodeUTF16)
		length:1
		freeWhenDone:NO];
	emojiDecodeUTF16NS = [[NSString alloc] initWithCharactersNoCopy:((unichar *) emojiDecodeUTF16)
		length:2
		freeWhenDone:NO];

	if ([@"hello" lengthOfBytesUsingEncoding:NSUTF8StringEncoding] == 0)
		printf("** -[NSString lengthOfBytesUsingEncoding:NSUTF8StringEncoding] unsupported; some benchmarks might give wrong results");
	if ([@"hello" lengthOfBytesUsingEncoding:NSUTF32StringEncoding] == 0)
		printf("** -[NSString lengthOfBytesUsingEncoding:NSUTF32StringEncoding] unsupported; some benchmarks might give wrong results");
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

#define systemBenchmarkUTF8EncodeRuneASCII NULL

#define systemBenchmarkUTF8EncodeRuneJP NULL

#define systemBenchmarkUTF8EncodeRuneEmoji NULL

static void systemBenchmarkUTF16EncodeRuneASCII(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		[[NSString alloc] initWithBytes:((void *) encodeASCIIUTF32)
			length:4
			encoding:NSUTF32StringEncoding];
	}
}

static void systemBenchmarkUTF16EncodeRuneJP(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		[[NSString alloc] initWithBytes:((void *) encodeJPUTF32)
			length:4
			encoding:NSUTF32StringEncoding];
	}
}

static void systemBenchmarkUTF16EncodeRuneEmoji(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		[[NSString alloc] initWithBytes:((void *) encodeEmojiUTF32)
			length:4
			encoding:NSUTF32StringEncoding];
	}
}

static void systemBenchmarkUTF8DecodeRuneASCII(int64_t n)
{
	int64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		// TODO check failure
		[asciiDecodeUTF8NS getBytes:&rune
			maxLength:4
			usedLength:NULL
			encoding:NSUTF32StringEncoding
			options:0
			range:NSMakeRange(0, 1)
			remainingRange:NULL];
	}
}

static void systemBenchmarkUTF8DecodeRuneJP(int64_t n)
{
	int64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		// TODO check failure
		[jpDecodeUTF8NS getBytes:&rune
			maxLength:4
			usedLength:NULL
			encoding:NSUTF32StringEncoding
			options:0
			range:NSMakeRange(0, 3)
			remainingRange:NULL];
	}
}

static void systemBenchmarkUTF8DecodeRuneEmoji(int64_t n)
{
	int64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		// TODO check failure
		[emojiDecodeUTF8NS getBytes:&rune
			maxLength:4
			usedLength:NULL
			encoding:NSUTF32StringEncoding
			options:0
			range:NSMakeRange(0, 4)
			remainingRange:NULL];
	}
}

static void systemBenchmarkUTF16DecodeRuneASCII(int64_t n)
{
	int64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		// TODO check failure
		[asciiDecodeUTF16NS getBytes:&rune
			maxLength:4
			usedLength:NULL
			encoding:NSUTF32StringEncoding
			options:0
			range:NSMakeRange(0, 1)
			remainingRange:NULL];
	}
}

static void systemBenchmarkUTF16DecodeRuneJP(int64_t n)
{
	int64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		// TODO check failure
		[jpDecodeUTF16NS getBytes:&rune
			maxLength:4
			usedLength:NULL
			encoding:NSUTF32StringEncoding
			options:0
			range:NSMakeRange(0, 1)
			remainingRange:NULL];
	}
}

static void systemBenchmarkUTF16DecodeRuneEmoji(int64_t n)
{
	int64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		// TODO check failure
		[emojiDecodeUTF16NS getBytes:&rune
			maxLength:4
			usedLength:NULL
			encoding:NSUTF32StringEncoding
			options:0
			range:NSMakeRange(0, 2)
			remainingRange:NULL];
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
