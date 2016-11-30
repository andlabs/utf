// 30 november 2016
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "common.h"

struct item {
	const char *name;
	benchFunc portable;
	benchFunc system;
};

static struct item items[] = {
	{ "BenchmarkUTF8RuneCountASCIIBuf", NULL, NULL },
	{ "BenchmarkUTF8UTF16CountASCIIBuf", NULL, NULL },
	{ "BenchmarkUTF8RuneCountJPBuf", NULL, NULL },
	{ "BenchmarkUTF8UTF16CountJPBuf", NULL, NULL },
	{ "BenchmarkUTF8RuneCountEmojiBuf", NULL, NULL },
	{ "BenchmarkUTF8UTF16CountJPBuf", NULL, NULL },
	{ "BenchmarkUTF16RuneCountASCIIBuf", NULL, NULL },
	{ "BenchmarkUTF16UTF8CountASCIIBuf", NULL, NULL },
	{ "BenchmarkUTF16RuneCountJPBuf", NULL, NULL },
	{ "BenchmarkUTF16UTF8CountJPBuf", NULL, NULL },
	{ "BenchmarkUTF16RuneCountEmojiBuf", NULL, NULL },
	{ "BenchmarkUTF16UTF8CountJPBuf", NULL, NULL },
	{ "BenchmarkUTF8EncodeRuneASCII", NULL, NULL },
	{ "BenchmarkUTF8EncodeRuneJP", NULL, NULL },
	{ "BenchmarkUTF8EncodeRuneEmoji", NULL, NULL },
	{ "BenchmarkUTF16EncodeRuneASCII", NULL, NULL },
	{ "BenchmarkUTF16EncodeRuneJP", NULL, NULL },
	{ "BenchmarkUTF16EncodeRuneEmoji", NULL, NULL },
	{ "BenchmarkUTF8DecodeRuneASCII", NULL, NULL },
	{ "BenchmarkUTF8DecodeRuneJP", NULL, NULL },
	{ "BenchmarkUTF8DecodeRuneEmoji", NULL, NULL },
	{ "BenchmarkUTF16DecodeRuneASCII", NULL, NULL },
	{ "BenchmarkUTF16DecodeRuneJP", NULL, NULL },
	{ "BenchmarkUTF16DecodeRuneEmoji", NULL, NULL },
	{ NULL, NULL, NULL },
};

void printTime(uint64_t nsec)
{
	double d;
	uint64_t hours, minutes;

	if (nsec == 0) {
		printf("0s");
		return;
	}
	if (nsec < 1000) {
		printf("%" PRIU64 "ns", nsec);
		return;
	}
	if (nsec < 1000000) {
		d = ((double) nsec) / 1000;
		printf("%.3gus", d);
		return;
	}
	if (nsec < 1000000000) {
		d = ((double) nsec) / 1000000;
		printf("%.6gms", d);
		return;
	}
	hours = nsec / 3600000000000;
	nsec %= 3600000000000;
	if (hours != 0)
		printf("%" PRIU64 "h", hours);
	minutes = nsec / 60000000000;
	nsec %= 60000000000;
	if (minutes != 0)
		printf("%" PRIU64 "m", minutes);
	d = ((double) nsec) / 1000000000;
	printf("%.9gs", d);
}

int main(void)
{
	int i;

	for (i = 0; items[i].name != NULL; i++) {
		items[i].portable = portableFuncFor(i);
		items[i].system = systemFuncFor(i);
	}

	for (i = 0; items[i].name != NULL; i++) {
		uint16_t nsec;

		printf("Portable %-50s ", items[i].name);
		nsec = bench(items[i].portable);
		printTime(nsec);
		printf("/op\n");
		printf("System   %-50s ", items[i].name);
		if (items[i].system != NULL) {
			nsec = bench(items[i].system);
			printTime(nsec);
			printf("/op\n");
		} else
			printf("undefined\n");
	}

	return 0;
}

const char asciiBufUTF8[] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0 };
const char jpBufUTF8[] = { 0xe6, 0x97, 0xa5, 0xe6, 0x9c, 0xac, 0xe8, 0xaa, 0x9e, 0xe6, 0x97, 0xa5, 0xe6, 0x9c, 0xac, 0xe8, 0xaa, 0x9e, 0xe6, 0x97, 0xa5, 0xe6, 0x9c, 0xac, 0xe8, 0xaa, 0x9e, 0xe6, 0x97, 0xa5, 0 };
const char emojiBufUTF8[] = { 0xf0, 0x9f, 0x93, 0x93, 0xf0, 0x9f, 0x93, 0x95, 0xf0, 0x9f, 0x93, 0x97, 0xf0, 0x9f, 0x93, 0x98, 0xf0, 0x9f, 0x93, 0x99, 0xf0, 0x9f, 0x93, 0x94, 0xf0, 0x9f, 0x93, 0x92, 0xf0, 0x9f, 0x92, 0x96, 0xf0, 0x9f, 0x92, 0x98, 0xf0, 0x9f, 0x92, 0x9d, 0xf0, 0x9f, 0x92, 0x9b, 0xf0, 0x9f, 0x92, 0x99, 0xf0, 0x9f, 0x92, 0x9c, 0 };
const uint16_t asciiBufUTF16[] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0 };
const uint16_t jpBufUTF16[] = { 0x65e5, 0x672c, 0x8a9e, 0x65e5, 0x672c, 0x8a9e, 0x65e5, 0x672c, 0x8a9e, 0x65e5, 0 };
const uint16_t emojiBufUTF16[] = { 0xd83d, 0xdcd3, 0xd83d, 0xdcd5, 0xd83d, 0xdcd7, 0xd83d, 0xdcd8, 0xd83d, 0xdcd9, 0xd83d, 0xdcd4, 0xd83d, 0xdcd2, 0xd83d, 0xdc96, 0xd83d, 0xdc98, 0xd83d, 0xdc9d, 0xd83d, 0xdc9b, 0xd83d, 0xdc99, 0xd83d, 0xdc9c, 0 };
const char asciiDecodeUTF8[] = { 0x61 };
const char jpDecodeUTF8[] = { 0xe6, 0x9c, 0xac };
const char emojiDecodeUTF8[] = { 0xf0, 0x9f, 0x93, 0x9a };
const uint16_t asciiDecodeUTF16[] = { 0x61 };
const uint16_t jpDecodeUTF16[] = { 0x672C };
const uint16_t emojiDecodeUTF16[] = { 0xd83d, 0xdcda };
