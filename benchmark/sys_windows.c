// 30 november 2016
#define UNICODE
#define _UNICODE
#define STRICT
#define STRICT_TYPED_ITEMIDS
#define WINVER			0x0501
#define _WIN32_WINNT		0x0501
#define _WIN32_WINDOWS	0x0501
#define _WIN32_IE			0x0600
#define NTDDI_VERSION		0x05010000
#include <windows.h>
#include "common.h"

static int64_t qpf;

int64_t benchCurrentTime(void)
{
	LARGE_INTEGER qpc;

	QueryPerformanceCounter(&qpc);
	return qpc.QuadPart;
}

int64_t benchOneSecond(void)
{
	// this is in ticks per second, and the default maximum time is one second, so.
	return qpf;
}

int64_t benchTimeToNsec(int64_t c)
{
	int64_t res;

	// convert duration from counts to nanocounts
	res = c * 1000000000;

	// and convert from nanocounts to naonseconds
	// thanks to ValleyBell for help
	res /= qpf;

	return res;
}

void init(void)
{
	LARGE_INTEGER qpfli;

	QueryPerformanceFrequency(&qpfli);
	qpf = qpfli.QuadPart;
}

#define systemBenchmarkUTF8RuneCountASCIIBuf NULL

static void systemBenchmarkUTF8UTF16CountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// TODO errors
		MultiByteToWideChar(CP_UTF8, 0,
			asciiBufUTF8, -1,
			NULL, 0);
	}
}

#define systemBenchmarkUTF8RuneCountJPBuf NULL

static void systemBenchmarkUTF8UTF16CountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// TODO errors
		MultiByteToWideChar(CP_UTF8, 0,
			jpBufUTF8, -1,
			NULL, 0);
	}
}

#define systemBenchmarkUTF8RuneCountEmojiBuf NULL

static void systemBenchmarkUTF8UTF16CountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// TODO errors
		MultiByteToWideChar(CP_UTF8, 0,
			emojiBufUTF8, -1,
			NULL, 0);
	}
}

#define systemBenchmarkUTF16RuneCountASCIIBuf NULL

static void systemBenchmarkUTF16UTF8CountASCIIBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// TODO errors
		WideCharToMultiByte(CP_UTF8, 0,
			asciiBufUTF16, -1,
			NULL, 0,
			NULL, NULL);
	}
}

#define systemBenchmarkUTF16RuneCountJPBuf NULL

static void systemBenchmarkUTF16UTF8CountJPBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// TODO errors
		WideCharToMultiByte(CP_UTF8, 0,
			jpBufUTF16, -1,
			NULL, 0,
			NULL, NULL);
	}
}

#define systemBenchmarkUTF16RuneCountEmojiBuf NULL

static void systemBenchmarkUTF16UTF8CountEmojiBuf(int64_t n)
{
	int64_t i;

	for (i = 0; i < n; i++) {
		// TODO errors
		WideCharToMultiByte(CP_UTF8, 0,
			emojiBufUTF16, -1,
			NULL, 0,
			NULL, NULL);
	}
}

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
