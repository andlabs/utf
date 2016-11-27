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
#endif
