// 27 november 2016
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include "../utf.h"

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

int main(int argc, char *argv[])
{
	verbose = (argc > 1) &&
		(argv[1][0] == '-') &&
		(argv[1][1] == 'v') &&
		(argv[1][2] == '\0');

	TestUTF8EncodeRune();
	TestUTF8DecodeRune();
	TestUTF8DecodeSurrogateRune();

	if (failed) {
		printf("some tests failed\n");
		return 1;
	}
	printf("all tests passed\n");
	return 0;
}
