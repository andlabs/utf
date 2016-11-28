// 27 november 2016
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include "../utf.h"

// TODO make sure everything checks both the 0 and not-0 element count versions
// TODO simplify all of these anyway

#define RUNEFMT "0x%08" PRIX32

int failed = 0;
int verbose = 0;

void verbosef(const char *fmt, ...)
{
	va_list ap;

	if (!verbose)
		return;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
}

void passfail(int failed, const char *func)
{
	verbosef("%s: ", func);
	if (failed) {
		verbosef("fail\n");
		return;
	}
	verbosef("pass\n");
}

struct utf8map {
	uint32_t rune;
	size_t n;
	uint8_t expected[4];
};

const struct utf8map utf8map[] = {
	{ 0x0000, 1, { 0x00 } },
	{ 0x0001, 1, { 0x01 } },
	{ 0x007e, 1, { 0x7e } },
	{ 0x007f, 1, { 0x7f } },
	{ 0x0080, 2, { 0xc2, 0x80 } },
	{ 0x0081, 2, { 0xc2, 0x81 } },
	{ 0x00bf, 2, { 0xc2, 0xbf } },
	{ 0x00c0, 2, { 0xc3, 0x80 } },
	{ 0x00c1, 2, { 0xc3, 0x81 } },
	{ 0x00c8, 2, { 0xc3, 0x88 } },
	{ 0x00d0, 2, { 0xc3, 0x90 } },
	{ 0x00e0, 2, { 0xc3, 0xa0 } },
	{ 0x00f0, 2, { 0xc3, 0xb0 } },
	{ 0x00f8, 2, { 0xc3, 0xb8 } },
	{ 0x00ff, 2, { 0xc3, 0xbf } },
	{ 0x0100, 2, { 0xc4, 0x80 } },
	{ 0x07ff, 2, { 0xdf, 0xbf } },
	{ 0x0400, 2, { 0xd0, 0x80 } },
	{ 0x0800, 3, { 0xe0, 0xa0, 0x80 } },
	{ 0x0801, 3, { 0xe0, 0xa0, 0x81 } },
	{ 0x1000, 3, { 0xe1, 0x80, 0x80 } },
	{ 0xd000, 3, { 0xed, 0x80, 0x80 } },
	{ 0xd7ff, 3, { 0xed, 0x9f, 0xbf } },		// last code point before surrogate half.
	{ 0xe000, 3, { 0xee, 0x80, 0x80 } },		// first code point after surrogate half.
	{ 0xfffe, 3, { 0xef, 0xbf, 0xbe } },
	{ 0xffff, 3, { 0xef, 0xbf, 0xbf } },
	{ 0x10000, 4, { 0xf0, 0x90, 0x80, 0x80 } },
	{ 0x10001, 4, { 0xf0, 0x90, 0x80, 0x81 } },
	{ 0x40000, 4, { 0xf1, 0x80, 0x80, 0x80 } },
	{ 0x10fffe, 4, { 0xf4, 0x8f, 0xbf, 0xbe } },
	{ 0x10ffff, 4, { 0xf4, 0x8f, 0xbf, 0xbf } },
	{ 0xFFFD, 3, { 0xef, 0xbf, 0xbd } },
	{ 0xFFFFFFFF, 0, { 0 } },
};

void wrongUTF8Output(const struct utf8map *u, char *buf, const char *func)
{
	size_t i;

	printf("%s " RUNEFMT ": wrong output: expected { ",
		func, u->rune);
	for (i = 0; i < u->n; i++)
		printf("0x%" PRIX8 ", ", (uint8_t) (u->expected[i]));
	printf("}, got { ");
	for (i = 0; i < u->n; i++)
		printf("0x%" PRIX8 ", ", (uint8_t) (buf[i]));
	printf("}\n");
	failed = 1;
}

int mustBeInvalid(uint32_t orig, uint32_t rune, ptrdiff_t off, const char *func, const char *context)
{
	if (rune != 0xFFFD) {
		printf("%s " RUNEFMT "%s: wrong rune: expected 0xFFFD, got " RUNEFMT "\n",
			func, orig, context, rune);
		failed = 1;
		return 0;
	}
	if (off != 1) {
		printf("%s " RUNEFMT "%s: wrong size: expected 1, got %td\n",
			func, orig, context, off);
		failed = 1;
		return 0;
	}
	return 1;
}

// TODO add a utf8IsRune()?

void TestUTF8EncodeRune(void)
{
	const struct utf8map *u;
	int selfFailed = 0;
	size_t i, n;
	char buf[4];
	uint8_t byte;
	int match;

	for (u = utf8map; u->rune != 0xFFFFFFFF; u++) {
		n = utf8EncodeRune(u->rune, buf);
		if (n != u->n) {
			printf("TestUTF8EncodeRune " RUNEFMT ": wrong size: wanted %zd, got %zd\n",
				u->rune, u->n, n);
			failed = 1;
			selfFailed = 1;
			continue;
		}
		match = 1;
		for (i = 0; i < u->n; i++) {
			byte = (uint8_t) (buf[i]);
			if (byte != u->expected[i]) {
				match = 0;
				break;
			}
		}
		if (!match) {
			wrongUTF8Output(u, buf, "TestUTF8EncodeRune");
			selfFailed = 1;
			continue;
		}
		verbosef("TestUTF8EncodeRune " RUNEFMT ": pass\n", u->rune);
	}
	passfail(selfFailed, "TestUTF8EncodeRune");
}

void TestUTF8DecodeRune(void)
{
	const struct utf8map *u;
	int selfFailed = 0;
	char buf[4];
	const char *end;
	uint32_t rune;

	for (u = utf8map; u->rune != 0xFFFFFFFF; u++) {
		// TODO get rid of the need for all this casting
		buf[0] = (char) (u->expected[0]);
		if (u->n > 1)
			buf[1] = (char) (u->expected[1]);
		if (u->n > 2)
			buf[2] = (char) (u->expected[2]);
		if (u->n > 3)
			buf[3] = (char) (u->expected[3]);

		end = utf8DecodeRune(buf, u->n, &rune);
		if (rune != u->rune) {
			printf("TestUTF8DecodeRune " RUNEFMT ": wrong rune: got " RUNEFMT "\n",
				u->rune, rune);
			selfFailed = 1;
			continue;
		}
		if ((size_t) (end - buf) != u->n) {
			printf("TestUTF8DecodeRune " RUNEFMT ": wrong size: expected %zd, got %td\n",
				u->rune, u->n, end - buf);
			failed = 1;
			selfFailed = 1;
			continue;
		}

		// TODO "there's an extra byte that bytes left behind - make sure trailing byte works"

		// see if not enough bytes gets handled properly
		// note that we skip this part if the size is 1 because a size of 0 means "assume null terminated"
		if (u->n != 1) {
			end = utf8DecodeRune(buf, u->n - 1, &rune);
			if (!mustBeInvalid(u->rune, rune, end - buf, "TestUTF8DecodeRune", " incomplete sequence")) {
				selfFailed = 1;
				continue;
			}
		}

		// corrupt the sequence and see if it fails
		if (u->n == 1)
			buf[0] = (char) ((uint8_t) 0x80);
		else
			buf[u->n - 1] = (char) ((uint8_t) 0x7F);
		end = utf8DecodeRune(buf, u->n - 1, &rune);
		if (!mustBeInvalid(u->rune, rune, end - buf, "TestUTF8DecodeRune", " invalid sequence")) {
			selfFailed = 1;
			continue;
		}

		verbosef("TestUTF8DecodeRune " RUNEFMT ": pass\n", u->rune);
	}
	passfail(selfFailed, "TestUTF8DecodeRune");
}

// TODO merge with TestUTF8DecodeInvalidSequence? the original Go tests kept them separate
void TestUTF8DecodeSurrogateRune(void)
{
	int selfFailed = 0;
	char buf[3];
	const char *end;
	uint32_t rune;

	buf[0] = (char) ((uint8_t) 0xed);
	buf[1] = (char) ((uint8_t) 0xa0);
	buf[2] = (char) ((uint8_t) 0x80);
	end = utf8DecodeRune(buf, 3, &rune);
	if (!mustBeInvalid(0xd800, rune, end - buf, "TestUTF8DecodeSurrogateRune", " { 0xed, 0xa0, 0x80 }"))
		selfFailed = 1;
	else
		verbosef("TestUTF8DecodeSurrogateRune " RUNEFMT " { 0xed, 0xa0, 0x80 }: pass\n", 0xd800);

	buf[0] = (char) ((uint8_t) 0xed);
	buf[1] = (char) ((uint8_t) 0xbf);
	buf[2] = (char) ((uint8_t) 0xbf);
	end = utf8DecodeRune(buf, 3, &rune);
	if (!mustBeInvalid(0xdfff, rune, end - buf, "TestUTF8DecodeSurrogateRune", " { 0xed, 0xbf, 0xbf }"))
		selfFailed = 1;
	else
		verbosef("TestUTF8DecodeSurrogateRune " RUNEFMT " { 0xed, 0xbf, 0xbf }: pass\n", 0xdfff);

	passfail(selfFailed, "TestUTF8DecodeSurrogateRune");
}

struct invalidUTF8Sequence {
	char seq[4];
	const char *str;
};

const struct invalidUTF8Sequence invalidUTF8Sequences[] = {
	// surrogate min
	{ { 0xed, 0xa0, 0x80, 0x80 }, " { 0xed, 0xa0, 0x80, 0x80 }" },
	// surrogate max
	{ { 0xed, 0xbf, 0xbf, 0x80 }, " { 0xed, 0xbf, 0xbf, 0x80 }" },
	// xx
	{ { 0x91, 0x80, 0x80, 0x80 }, " { 0x91, 0x80, 0x80, 0x80 }" },
	// s1
	{ { 0xC2, 0x7F, 0x80, 0x80 }, " { 0xC2, 0x7F, 0x80, 0x80 }" },
	{ { 0xC2, 0xC0, 0x80, 0x80 }, " { 0xC2, 0xC0, 0x80, 0x80 }" },
	{ { 0xDF, 0x7F, 0x80, 0x80 }, " { 0xDF, 0x7F, 0x80, 0x80 }" },
	{ { 0xDF, 0xC0, 0x80, 0x80 }, " { 0xDF, 0xC0, 0x80, 0x80 }" },
	// s2
	{ { 0xE0, 0x9F, 0xBF, 0x80 }, " { 0xE0, 0x9F, 0xBF, 0x80 }" },
	{ { 0xE0, 0xA0, 0x7F, 0x80 }, " { 0xE0, 0xA0, 0x7F, 0x80 }" },
	{ { 0xE0, 0xBF, 0xC0, 0x80 }, " { 0xE0, 0xBF, 0xC0, 0x80 }" },
	{ { 0xE0, 0xC0, 0x80, 0x80 }, " { 0xE0, 0xC0, 0x80, 0x80 }" },
	// s3
	{ { 0xE1, 0x7F, 0xBF, 0x80 }, " { 0xE1, 0x7F, 0xBF, 0x80 }" },
	{ { 0xE1, 0x80, 0x7F, 0x80 }, " { 0xE1, 0x80, 0x7F, 0x80 }" },
	{ { 0xE1, 0xBF, 0xC0, 0x80 }, " { 0xE1, 0xBF, 0xC0, 0x80 }" },
	{ { 0xE1, 0xC0, 0x80, 0x80 }, " { 0xE1, 0xC0, 0x80, 0x80 }" },
	// s4
	{ { 0xED, 0x7F, 0xBF, 0x80 }, " { 0xED, 0x7F, 0xBF, 0x80 }" },
	{ { 0xED, 0x80, 0x7F, 0x80 }, " { 0xED, 0x80, 0x7F, 0x80 }" },
	{ { 0xED, 0x9F, 0xC0, 0x80 }, " { 0xED, 0x9F, 0xC0, 0x80 }" },
	{ { 0xED, 0xA0, 0x80, 0x80 }, " { 0xED, 0xA0, 0x80, 0x80 }" },
	// s5
	{ { 0xF0, 0x8F, 0xBF, 0xBF }, " { 0xF0, 0x8F, 0xBF, 0xBF }" },
	{ { 0xF0, 0x90, 0x7F, 0xBF }, " { 0xF0, 0x90, 0x7F, 0xBF }" },
	{ { 0xF0, 0x90, 0x80, 0x7F }, " { 0xF0, 0x90, 0x80, 0x7F }" },
	{ { 0xF0, 0xBF, 0xBF, 0xC0 }, " { 0xF0, 0xBF, 0xBF, 0xC0 }" },
	{ { 0xF0, 0xBF, 0xC0, 0x80 }, " { 0xF0, 0xBF, 0xC0, 0x80 }" },
	{ { 0xF0, 0xC0, 0x80, 0x80 }, " { 0xF0, 0xC0, 0x80, 0x80 }" },
	// s6
	{ { 0xF1, 0x7F, 0xBF, 0xBF }, " { 0xF1, 0x7F, 0xBF, 0xBF }" },
	{ { 0xF1, 0x80, 0x7F, 0xBF }, " { 0xF1, 0x80, 0x7F, 0xBF }" },
	{ { 0xF1, 0x80, 0x80, 0x7F }, " { 0xF1, 0x80, 0x80, 0x7F }" },
	{ { 0xF1, 0xBF, 0xBF, 0xC0 }, " { 0xF1, 0xBF, 0xBF, 0xC0 }" },
	{ { 0xF1, 0xBF, 0xC0, 0x80 }, " { 0xF1, 0xBF, 0xC0, 0x80 }" },
	{ { 0xF1, 0xC0, 0x80, 0x80 }, " { 0xF1, 0xC0, 0x80, 0x80 }" },
	// s7
	{ { 0xF4, 0x7F, 0xBF, 0xBF }, " { 0xF4, 0x7F, 0xBF, 0xBF }" },
	{ { 0xF4, 0x80, 0x7F, 0xBF }, " { 0xF4, 0x80, 0x7F, 0xBF }" },
	{ { 0xF4, 0x80, 0x80, 0x7F }, " { 0xF4, 0x80, 0x80, 0x7F }" },
	{ { 0xF4, 0x8F, 0xBF, 0xC0 }, " { 0xF4, 0x8F, 0xBF, 0xC0 }" },
	{ { 0xF4, 0x8F, 0xC0, 0x80 }, " { 0xF4, 0x8F, 0xC0, 0x80 }" },
	{ { 0xF4, 0x90, 0x80, 0x80 }, " { 0xF4, 0x90, 0x80, 0x80 }" },
	{ { 0 }, NULL },
};

void TestUTF8DecodeInvalidSequence(void)
{
	const struct invalidUTF8Sequence *u;
	int selfFailed = 0;
	const char *end;
	uint32_t rune;

	for (u = invalidUTF8Sequences; u->str != NULL; u++) {
		end = utf8DecodeRune(u->seq, 4, &rune);
		if (!mustBeInvalid(0xFFFD, rune, end - u->seq, "TestUTF8DecodeInvalidSequence", u->str)) {
			selfFailed = 1;
			continue;
		}
		verbosef("TestUTF8DecodeInvalidSequence " RUNEFMT "%s: pass\n", 0xFFFD, u->str);
	}
	passfail(selfFailed, "TestUTF8DecodeInvalidSequence");
}

// in Go, rune == int32; here, rune == uint32
// but -1 is 0xFFFFFFFF anyway, and (as of this writing) Go's utf8.EncodeRune() already does an unsigned conversion first to simplify things
void TestUTF8NegativeRune(void)
{
	int selfFailed = 0;
	char buf[4];
	size_t n;
	uint8_t c;

	n = utf8EncodeRune(0xFFFFFFFF, buf);
	if (n != 3) {
		printf("TestUTF8NegativeRune " RUNEFMT ": wrong size: expected 3, got %zd\n",
			0xFFFFFFFF, n);
		failed = 1;
		selfFailed = 1;
		goto out;
	}
	c = (uint8_t) (buf[0]);
	if (c != 0xEF) {
		printf("TestUTF8NegativeRune " RUNEFMT ": wrong first byte: expected 0xEF, got 0x%02" PRIX8 "\n",
			0xFFFFFFFF, c);
		failed = 1;
		selfFailed = 1;
		goto out;
	}
	c = (uint8_t) (buf[1]);
	if (c != 0xBF) {
		printf("TestUTF8NegativeRune " RUNEFMT ": wrong second byte: expected 0xBF, got 0x%02" PRIX8 "\n",
			0xFFFFFFFF, c);
		failed = 1;
		selfFailed = 1;
		goto out;
	}
	c = (uint8_t) (buf[2]);
	if (c != 0xBD) {
		printf("TestUTF8NegativeRune " RUNEFMT ": wrong third byte: expected 0xBD, got 0x%02" PRIX8 "\n",
			0xFFFFFFFF, c);
		failed = 1;
		selfFailed = 1;
		goto out;
	}
out:
	passfail(selfFailed, "TestUTF8NegativeRune");
}

struct runeCountUTF8 {
	char in[20];
	const char *str;
	size_t n;
	size_t out;
};

const struct runeCountUTF8 runeCountsUTF8[] = {
	{ { 0x61, 0x62, 0x63, 0x64, }, "{ 0x61, 0x62, 0x63, 0x64, }", 4, 4 },
	{ { 0xE2, 0x98, 0xBA, 0xE2, 0x98, 0xBB, 0xE2, 0x98, 0xB9, }, "{ 0xE2, 0x98, 0xBA, 0xE2, 0x98, 0xBB, 0xE2, 0x98, 0xB9, }", 9, 3 },
	{ { 0x31, 0x2C, 0x32, 0x2C, 0x33, 0x2C, 0x34, }, "{ 0x31, 0x2C, 0x32, 0x2C, 0x33, 0x2C, 0x34, }", 7, 7 },
	{ { 0xE2, 0x00, }, "{ 0xE2, 0x00, }", 2, 2 },
	{ { 0xE2, 0x80, }, "{ 0xE2, 0x80, }", 2, 2 },
	{ { 0x61, 0xE2, 0x80, }, "{ 0x61, 0xE2, 0x80, }", 3, 3 },
	{ { 0 }, NULL, 0, 0 },
};

void TestUTF8RuneCount(void)
{
	const struct runeCountUTF8 *u;
	int selfFailed = 0;
	uint32_t count;

	for (u = runeCountsUTF8; u->str != NULL; u++) {
		count = utf8RuneCount(u->in, u->n);
		if (count != u->out) {
			printf("TestUTF8RuneCount %s: wrong x: expected %zd, got %zd\n",
				u->str, u->out, count);
			selfFailed = 1;
			continue;
		}
		verbosef("TestUTF8RuneCount %s: pass\n", u->str);
	}
	passfail(selfFailed, "TestUTF8RuneCount");
}

// TODO have a utf8RuneEncodedLength()?

// TODO have a utf8ValidRune()?

// TODO why is there a generic utf8.ValidRune()? check utf16 too

struct encodeUTF16Test {
	uint32_t in[20];
	size_t nIn;
	const char *str;
	uint16_t out[20];
	size_t nOut;
};

const struct encodeUTF16Test encodeUTF16Tests[] = {
	{ { 1, 2, 3, 4 }, 4,
		"{ 1, 2, 3, 4 }",
		{ 1, 2, 3, 4 }, 4 },
	{ { 0xffff, 0x10000, 0x10001, 0x12345, 0x10ffff }, 5,
		"{ 0xffff, 0x10000, 0x10001, 0x12345, 0x10ffff }",
		{ 0xffff, 0xd800, 0xdc00, 0xd800, 0xdc01, 0xd808, 0xdf45, 0xdbff, 0xdfff }, 9, },
	{ { 0x61, 0x62, 0xd7ff, 0xd800, 0xdfff, 0xe000, 0x110000, 0xFFFFFFFF }, 8,
		"{ 0x61, 0x62, 0xd7ff, 0xd800, 0xdfff, 0xe000, 0x110000, 0xFFFFFFFF }",
		{ 0x61, 0x62, 0xd7ff, 0xfffd, 0xfffd, 0xe000, 0xfffd, 0xfffd }, 8 },
	{ { 0 }, 0, NULL, { 0 }, 0 },
};

// This combines TestEncode and TestEncodeRune from the original Go unicode/utf16 tests because they overlap to some extent (but the Go functions operate differently enough that they are separate tests).
void TestUTF16Encode(void)
{
	const struct encodeUTF16Test *u;
	int selfFailed = 0;
	uint16_t buf[2];
	size_t n;
	size_t i, j;
	int iterFailed = 0;
	uint32_t rune;
	const uint16_t *b2;

	for (u = encodeUTF16Tests; u->str != NULL; u++) {
		iterFailed = 0;
		j = 0;
		for (i = 0; i < u->nIn; i++) {
			n = utf16EncodeRune(u->in[i], buf);

			// this is the only part unique to Go's TestEncodeRune
			if (u->in[i] >= 0x10000 && u->in[i] <= 0x10FFFF) {
				b2 = utf16DecodeRune(buf, n, &rune);
				if (rune != u->in[i]) {
					printf("TestUTF16Encode %s: re-encode of input %zd: wrong rune: wanted " RUNEFMT ", got " RUNEFMT "\n",
						u->str, i, u->in[i], rune);
					iterFailed = 1;
					break;
				}
				if (((size_t) (b2 - buf)) != n) {
					printf("TestUTF16Encode %s: re-encode of input %zd: wrong length: expected %zd got %td\n",
						u->str, i, n, b2 - buf);
					iterFailed = 1;
					break;
				}
			}

			if ((j + n) > u->nOut) {
				printf("TestUTF16Encode %s: overflow at input %zd\n",
					u->str, i);
				iterFailed = 1;
				break;
			}
			if (buf[0] != u->out[j]) {
				printf("TestUTF16Encode %s: input %zd output %zd wrong: expected 0x%" PRIX16 ", got 0x%" PRIX16 "\n",
					u->str, i, j, u->out[j], buf[0]);
				iterFailed = 1;
				break;
			}
			j++;
			if (n == 1)
				continue;
			if (buf[1] != u->out[j]) {
				printf("TestUTF16Encode %s: input %zd output %zd (second half of pair) wrong: expected 0x%" PRIX16 ", got 0x%" PRIX16 "\n",
					u->str, i, j, u->out[j], buf[1]);
				iterFailed = 1;
				break;
			}
			j++;
		}
		if (j != u->nOut) {
			printf("TestUTF16Encode %s: underflow: expected %zd points, got %zd\n",
				u->str, u->nOut, j);
			iterFailed = 1;
			// and fall through
		}
		if (iterFailed) {
			failed = 1;
			selfFailed = 1;
			continue;
		}
		verbosef("TestUTF16Encode %s: pass\n", u->str);
	}
	passfail(selfFailed, "TestUTF16Encode");
}

struct decodeUTF16Test {
	uint16_t in[20];
	size_t nIn;
	const char *str;
	uint32_t out[20];
	size_t nOut;
};

const struct decodeUTF16Test decodeUTF16Tests[] = {
	{ { 1, 2, 3, 4 }, 4,
		"{ 1, 2, 3, 4 }",
		{ 1, 2, 3, 4 }, 4 },
	{ { 0xffff, 0xd800, 0xdc00, 0xd800, 0xdc01, 0xd808, 0xdf45, 0xdbff, 0xdfff }, 9,
		"{ 0xffff, 0xd800, 0xdc00, 0xd800, 0xdc01, 0xd808, 0xdf45, 0xdbff, 0xdfff }",
		{ 0xffff, 0x10000, 0x10001, 0x12345, 0x10ffff }, 5 },
	{ { 0xd800, 0x61 }, 2,
		"{ 0xd800, 0x61 }",
		{ 0xfffd, 0x61 }, 2 },
	{ { 0xdfff }, 1,
		"{ 0xdfff }",
		{ 0xfffd }, 1 },
	{ { 0 }, 0, NULL, { 0 }, 0 },
};

void TestUTF16Decode(void)
{
	const struct decodeUTF16Test *u;
	int selfFailed = 0;
	const uint16_t *b, *b2;
	uint32_t rune;
	size_t i, j;
	int iterFailed = 0;

	for (u = decodeUTF16Tests; u->str != NULL; u++) {
		iterFailed = 0;
		i = 0;
		j = 0;
		b = u->in;
		while (i < u->nIn) {
			b2 = utf16DecodeRune(b, u->nIn - i, &rune);
			if ((j + 1) > u->nOut) {
				printf("TestUTF16Decode %s: overflow at input %zd\n",
					u->str, i);
				iterFailed = 1;
				break;
			}
			if (rune != u->out[j]) {
				printf("TestUTF16Decode %s: input %zd output %zd wrong: expected " RUNEFMT ", got " RUNEFMT "\n",
					u->str, i, j, u->out[j], rune);
				iterFailed = 1;
				break;
			}
			j++;
			i += b2 - b;
			b = b2;
		}
		if (j != u->nOut) {
			printf("TestUTF16Decode %s: underflow: expected %zd runes, got %zd\n",
				u->str, u->nOut, j);
			iterFailed = 1;
			// and fall through
		}
		if (iterFailed) {
			failed = 1;
			selfFailed = 1;
			continue;
		}
		verbosef("TestUTF16Decode %s: pass\n", u->str);
	}
	passfail(selfFailed, "TestUTF16Decode");
}

struct decodeUTF16RuneTest {
	uint16_t r[2];
	const char *str;
	uint32_t want;
};

const struct decodeUTF16RuneTest decodeUTF16RuneTests[] = {
	{ { 0xd800, 0xdc00 }, "{ 0xd800, 0xdc00 }", 0x10000 },
	{ { 0xd800, 0xdc01 }, "{ 0xd800, 0xdc01 }", 0x10001 },
	{ { 0xd808, 0xdf45 }, "{ 0xd808, 0xdf45 }", 0x12345 },
	{ { 0xdbff, 0xdfff }, "{ 0xdbff, 0xdfff }", 0x10ffff },
	{ { 0xd800, 0x61 }, "{ 0xd800, 0x61 }", 0xfffd },		// illegal, replacement rune substituted
	{ { 0 }, NULL, 0 },
};

void TestUTF16DecodeRune(void)
{
	const struct decodeUTF16RuneTest *u;
	int selfFailed = 0;
	uint32_t rune;

	for (u = decodeUTF16RuneTests; u->str != NULL; u++) {
		utf16DecodeRune(u->r, 2, &rune);
		if (rune != u->want) {
			printf("TestUTF16DecodeRune %s: wrong rune: wanted " RUNEFMT ", got " RUNEFMT "\n",
				u->str, u->want, rune);
			failed = 1;
			selfFailed = 1;
			continue;
		}
		// TODO test the return is correct?
		verbosef("TestUTF16DecodeRune %s: pass\n", u->str);
	}
	passfail(selfFailed, "TestUTF16DecodeRune");
}

// TODO utf16IsSurrogate()?

int main(int argc, char *argv[])
{
	verbose = (argc > 1) &&
		(argv[1][0] == '-') &&
		(argv[1][1] == 'v') &&
		(argv[1][2] == '\0');

	TestUTF8EncodeRune();
	TestUTF8DecodeRune();
	TestUTF8DecodeSurrogateRune();
	TestUTF8DecodeInvalidSequence();
	TestUTF8NegativeRune();
	TestUTF8RuneCount();

	TestUTF16Encode();
	TestUTF16Decode();
	TestUTF16DecodeRune();

	if (failed) {
		printf("some tests failed\n");
		return 1;
	}
	printf("all tests passed\n");
	return 0;
}
