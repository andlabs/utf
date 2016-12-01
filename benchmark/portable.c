// 30 november 2016
#include "../utf.h"
#include "common.h"

static void portableBenchmarkUTF8RuneCountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		utf8RuneCount(asciiBufUTF8, 0);
	}
}

static void portableBenchmarkUTF8UTF16CountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		utf8UTF16Count(asciiBufUTF8, 0);
	}
}

static void portableBenchmarkUTF8RuneCountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		utf8RuneCount(jpBufUTF8, 0);
	}
}

static void portableBenchmarkUTF8UTF16CountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		utf8UTF16Count(jpBufUTF8, 0);
	}
}

static void portableBenchmarkUTF8RuneCountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		utf8RuneCount(emojiBufUTF8, 0);
	}
}

static void portableBenchmarkUTF8UTF16CountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		utf8UTF16Count(emojiBufUTF8, 0);
	}
}

static void portableBenchmarkUTF16RuneCountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		utf16RuneCount(asciiBufUTF16, 0);
	}
}

static void portableBenchmarkUTF16UTF8CountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		utf16UTF8Count(asciiBufUTF16, 0);
	}
}

static void portableBenchmarkUTF16RuneCountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		utf16RuneCount(jpBufUTF16, 0);
	}
}

static void portableBenchmarkUTF16UTF8CountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		utf16UTF8Count(jpBufUTF16, 0);
	}
}

static void portableBenchmarkUTF16RuneCountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		utf16RuneCount(emojiBufUTF16, 0);
	}
}

static void portableBenchmarkUTF16UTF8CountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		utf16UTF8Count(emojiBufUTF16, 0);
	}
}

static void portableBenchmarkUTF8EncodeRuneASCII(int64_t n)
{
	int64_t i;
	char buf[4];

	for (i = 0; i < n; i++) {
		utf8EncodeRune(encodeASCII, buf);
	}
}

static void portableBenchmarkUTF8EncodeRuneJP(int64_t n)
{
	int64_t i;
	char buf[4];

	for (i = 0; i < n; i++) {
		utf8EncodeRune(encodeJP, buf);
	}
}

static void portableBenchmarkUTF8EncodeRuneEmoji(int64_t n)
{
	int64_t i;
	char buf[4];

	for (i = 0; i < n; i++) {
		utf8EncodeRune(encodeEmoji, buf);
	}
}

static void portableBenchmarkUTF16EncodeRuneASCII(int64_t n)
{
	int64_t i;
	uint16_t buf[2];

	for (i = 0; i < n; i++) {
		utf16EncodeRune(encodeASCII, buf);
	}
}

static void portableBenchmarkUTF16EncodeRuneJP(int64_t n)
{
	int64_t i;
	uint16_t buf[2];

	for (i = 0; i < n; i++) {
		utf16EncodeRune(encodeJP, buf);
	}
}

static void portableBenchmarkUTF16EncodeRuneEmoji(int64_t n)
{
	int64_t i;
	uint16_t buf[2];

	for (i = 0; i < n; i++) {
		utf16EncodeRune(encodeEmoji, buf);
	}
}

static void portableBenchmarkUTF8DecodeRuneASCII(int64_t n)
{
	int64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		utf8DecodeRune(asciiDecodeUTF8, 0, &rune);
	}
}

static void portableBenchmarkUTF8DecodeRuneJP(int64_t n)
{
	int64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		utf8DecodeRune(jpDecodeUTF8, 0, &rune);
	}
}

static void portableBenchmarkUTF8DecodeRuneEmoji(int64_t n)
{
	int64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		utf8DecodeRune(emojiDecodeUTF8, 0, &rune);
	}
}

static void portableBenchmarkUTF16DecodeRuneASCII(int64_t n)
{
	int64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		utf16DecodeRune(asciiDecodeUTF16, 0, &rune);
	}
}

static void portableBenchmarkUTF16DecodeRuneJP(int64_t n)
{
	int64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		utf16DecodeRune(jpDecodeUTF16, 0, &rune);
	}
}

static void portableBenchmarkUTF16DecodeRuneEmoji(int64_t n)
{
	int64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		utf16DecodeRune(emojiDecodeUTF16, 0, &rune);
	}
}

const benchFunc portableBenchFuncs[] = {
	portableBenchmarkUTF8RuneCountASCIIBuf,
	portableBenchmarkUTF8UTF16CountASCIIBuf,
	portableBenchmarkUTF8RuneCountJPBuf,
	portableBenchmarkUTF8UTF16CountJPBuf,
	portableBenchmarkUTF8RuneCountEmojiBuf,
	portableBenchmarkUTF8UTF16CountEmojiBuf,
	portableBenchmarkUTF16RuneCountASCIIBuf,
	portableBenchmarkUTF16UTF8CountASCIIBuf,
	portableBenchmarkUTF16RuneCountJPBuf,
	portableBenchmarkUTF16UTF8CountJPBuf,
	portableBenchmarkUTF16RuneCountEmojiBuf,
	portableBenchmarkUTF16UTF8CountEmojiBuf,
	portableBenchmarkUTF8EncodeRuneASCII,
	portableBenchmarkUTF8EncodeRuneJP,
	portableBenchmarkUTF8EncodeRuneEmoji,
	portableBenchmarkUTF16EncodeRuneASCII,
	portableBenchmarkUTF16EncodeRuneJP,
	portableBenchmarkUTF16EncodeRuneEmoji,
	portableBenchmarkUTF8DecodeRuneASCII,
	portableBenchmarkUTF8DecodeRuneJP,
	portableBenchmarkUTF8DecodeRuneEmoji,
	portableBenchmarkUTF16DecodeRuneASCII,
	portableBenchmarkUTF16DecodeRuneJP,
	portableBenchmarkUTF16DecodeRuneEmoji,
};
