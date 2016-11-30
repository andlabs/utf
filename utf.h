// utf by pietro gagliardi (andlabs) — https://github.com/andlabs/utf/
// 10 november 2016

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

// if nElem == 0, assume the buffer has no upper limit and is '\0' terminated
// otherwise, assume buffer is NOT '\0' terminated but is bounded by nElem *elements*

extern size_t utf8EncodeRune(uint32_t rune, char *encoded);
extern const char *utf8DecodeRune(const char *s, size_t nElem, uint32_t *rune);
extern size_t utf16EncodeRune(uint32_t rune, uint16_t *encoded);
extern const uint16_t *utf16DecodeRune(const uint16_t *s, size_t nElem, uint32_t *rune);

extern size_t utf8RuneCount(const char *s, size_t nElem);
extern size_t utf8UTF16Count(const char *s, size_t nElem);
extern size_t utf16RuneCount(const uint16_t *s, size_t nElem);
extern size_t utf16UTF8Count(const uint16_t *s, size_t nElem);

#ifdef __cplusplus
}

// Provide overloads on Windows for using these functions with wchar_t and WCHAR when wchar_t is a keyword in C++ mode (the default).
// Otherwise, you'd need to cast to pass a wchar_t pointer, WCHAR pointer, or equivalent to these functions.
// TODO check this on MinGW-w64
// TODO check this under /Wall
// TODO C-style casts enough? or will that fail in /Wall?
// TODO same for UniChar/unichar on Mac?
#if defined(_MSC_VER) && defined(_WCHAR_T_DEFINED) && defined(_NATIVE_WCHAR_T_DEFINED)

inline size_t utf16EncodeRune(uint32_t rune, wchar_t *encoded)
{
	return utf16EncodeRune(rune, reinterpret_cast<uint16_t *>(encoded));
}

inline const wchar_t *utf16DecodeRune(const wchar_t *s, size_t nElem, uint32_t *rune)
{
	const uint16_t *ret;

	ret = utf16DecodeRune(reinterpret_cast<const uint16_t *>(s), nElem, rune);
	return reinterpret_cast<const wchar_t *>(ret);
}

inline size_t utf16RuneCount(const wchar_t *s, size_t nElem)
{
	return utf16RuneCount(reinterpret_cast<const uint16_t *>(s), nElem);
}

inline size_t utf16UTF8Count(const wchar_t *s, size_t nElem)
{
	return utf16UTF8Count(reinterpret_cast<const uint16_t *>(s), nElem);
}

#endif

#endif
