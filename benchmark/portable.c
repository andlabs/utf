// 30 november 2016
#include "../utf.h"
#include "common.h"

static void portableBenchmarkUTF8RuneCountASCIIBuf(uint64_t n)
{
	uint64_t i;

	for (i = 0; i < n; i++) {
		utf8RuneCount(asciiBufUTF8, 0);
	}
}

static void portableBenchmarkUTF8UTF16CountASCIIBuf(uint64_t n)
{
	uint64_t i;

	for (i = 0; i < n; i++) {
		utf8UTF16Count(asciiBufUTF8, 0);
	}
}

static void portableBenchmarkUTF8RuneCountJPBuf(uint64_t n)
{
	uint64_t i;

	for (i = 0; i < n; i++) {
		utf8RuneCount(jpBufUTF8, 0);
	}
}

static void portableBenchmarkUTF8UTF16CountJPBuf(uint64_t n)
{
	uint64_t i;

	for (i = 0; i < n; i++) {
		utf8UTF16Count(jpBufUTF8, 0);
	}
}

static void portableBenchmarkUTF8RuneCountEmojiBuf(uint64_t n)
{
	uint64_t i;

	for (i = 0; i < n; i++) {
		utf8RuneCount(emojiBufUTF8, 0);
	}
}

static void portableBenchmarkUTF8UTF16CountJPBuf(uint64_t n)
{
	uint64_t i;

	for (i = 0; i < n; i++) {
		utf8UTF16Count(emojiBufUTF8, 0);
	}
}

static void portableBenchmarkUTF16RuneCountASCIIBuf(uint64_t n)
{
	uint64_t i;

	for (i = 0; i < n; i++) {
		utf16RuneCount(asciiBufUTF16, 0);
	}
}

static void portableBenchmarkUTF16UTF8CountASCIIBuf(uint64_t n)
{
	uint64_t i;

	for (i = 0; i < n; i++) {
		utf16UTF8Count(asciiBufUTF16, 0);
	}
}

static void portableBenchmarkUTF16RuneCountJPBuf(uint64_t n)
{
	uint64_t i;

	for (i = 0; i < n; i++) {
		utf16RuneCount(jpBufUTF16, 0);
	}
}

static void portableBenchmarkUTF16UTF8CountJPBuf(uint64_t n)
{
	uint64_t i;

	for (i = 0; i < n; i++) {
		utf16UTF8Count(jpBufUTF16, 0);
	}
}

static void portableBenchmarkUTF16RuneCountEmojiBuf(uint64_t n)
{
	uint64_t i;

	for (i = 0; i < n; i++) {
		utf16RuneCount(emojiBufUTF16, 0);
	}
}

static void portableBenchmarkUTF16UTF8CountJPBuf(uint64_t n)
{
	uint64_t i;

	for (i = 0; i < n; i++) {
		utf16UTF8Count(emojiBufUTF16, 0);
	}
}

static void portableBenchmarkUTF8EncodeRuneASCII(uint64_t n)
{
	uint64_t i;
	char buf[4];

	for (i = 0; i < n; i++) {
		utf8EncodeRune(encodeASCII, buf);
	}
}

static void portableBenchmarkUTF8EncodeRuneJP(uint64_t n)
{
	uint64_t i;
	char buf[4];

	for (i = 0; i < n; i++) {
		utf8EncodeRune(encodeJP, buf);
	}
}

static void portableBenchmarkUTF8EncodeRuneEmoji(uint64_t n)
{
	uint64_t i;
	char buf[4];

	for (i = 0; i < n; i++) {
		utf8EncodeRune(encodeEmoji, buf);
	}
}

static void portableBenchmarkUTF16EncodeRuneASCII(uint64_t n)
{
	uint64_t i;
	uint16_t buf[2];

	for (i = 0; i < n; i++) {
		utf16EncodeRune(encodeASCII, buf);
	}
}

static void portableBenchmarkUTF16EncodeRuneJP(uint64_t n)
{
	uint64_t i;
	uint16_t buf[2];

	for (i = 0; i < n; i++) {
		utf16EncodeRune(encodeJP, buf);
	}
}

static void portableBenchmarkUTF16EncodeRuneEmoji(uint64_t n)
{
	uint64_t i;
	uint16_t buf[2];

	for (i = 0; i < n; i++) {
		utf16EncodeRune(encodeEmoji, buf);
	}
}

static void portableBenchmarkUTF8DecodeRuneASCII(uint64_t n)
{
	uint64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		utf8DecodeRune(asciiDecodeUTF8, 0, &rune);
	}
}

static void portableBenchmarkUTF8DecodeRuneJP(uint64_t n)
{
	uint64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		utf8DecodeRune(jpDecodeUTF8, 0, &rune);
	}
}

static void portableBenchmarkUTF8DecodeRuneEmoji(uint64_t n)
{
	uint64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		utf8DecodeRune(emojiDecodeUTF8, 0, &rune);
	}
}

static void portableBenchmarkUTF16DecodeRuneASCII(uint64_t n)
{
	uint64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		utf16DeocdeRune(asciiDecodeUTF16, 0, &rune);
	}
}

static void portableBenchmarkUTF16DecodeRuneJP(uint64_t n)
{
	uint64_t i;
	uint32_t rune;

	for (i = 0; i < n; i++) {
		utf16DecodeRune(jpDecodeUTF16, 0, &rune);
	}
}

static void portableBenchmarkUTF16DecodeRuneEmoji(uint64_t n)
{
	uint64_t i;
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
	portableBenchmarkUTF8UTF16CountJPBuf,
	portableBenchmarkUTF16RuneCountASCIIBuf,
	portableBenchmarkUTF16UTF8CountASCIIBuf,
	portableBenchmarkUTF16RuneCountJPBuf,
	portableBenchmarkUTF16UTF8CountJPBuf,
	portableBenchmarkUTF16RuneCountEmojiBuf,
	portableBenchmarkUTF16UTF8CountJPBuf,
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
