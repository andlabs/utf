// 30 november 2016
#include <stddef.h>
#include "benchmark.h"

extern const char asciiBufUTF8[];
extern const char jpBufUTF8[];
extern const char emojiBufUTF8[];
extern const uint16_t asciiBufUTF16[];
extern const uint16_t jpBufUTF16[];
extern const uint16_t emojiBufUTF16[];
#define encodeASCII 0x61
#define encodeJP 0x672C
#define encodeEmoji 0x1F4DA
extern const char asciiDecodeUTF8[];
extern const char jpDecodeUTF8[];
extern const char emojiDecodeUTF8[];
extern const uint16_t asciiDecodeUTF16[];
extern const uint16_t jpDecodeUTF16[];
extern const uint16_t emojiDecodeUTF16[];

extern const benchFunc portableBenchFuncs[];
extern const benchFunc systemBenchFuncs[];

extern void init(void);

enum {
	BenchmarkUTF8RuneCountASCIIBuf,
	BenchmarkUTF8UTF16CountASCIIBuf,
	BenchmarkUTF8RuneCountJPBuf,
	BenchmarkUTF8UTF16CountJPBuf,
	BenchmarkUTF8RuneCountEmojiBuf,
	BenchmarkUTF8UTF16CountEmojiBuf,
	BenchmarkUTF16RuneCountASCIIBuf,
	BenchmarkUTF16UTF8CountASCIIBuf,
	BenchmarkUTF16RuneCountJPBuf,
	BenchmarkUTF16UTF8CountJPBuf,
	BenchmarkUTF16RuneCountEmojiBuf,
	BenchmarkUTF16UTF8CountEmojiBuf,
	BenchmarkUTF8EncodeRuneASCII,
	BenchmarkUTF8EncodeRuneJP,
	BenchmarkUTF8EncodeRuneEmoji,
	BenchmarkUTF16EncodeRuneASCII,
	BenchmarkUTF16EncodeRuneJP,
	BenchmarkUTF16EncodeRuneEmoji,
	BenchmarkUTF8DecodeRuneASCII,
	BenchmarkUTF8DecodeRuneJP,
	BenchmarkUTF8DecodeRuneEmoji,
	BenchmarkUTF16DecodeRuneASCII,
	BenchmarkUTF16DecodeRuneJP,
	BenchmarkUTF16DecodeRuneEmoji,
};
