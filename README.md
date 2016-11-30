# utf: a single-file portable standard C implementation of UTF-8 and UTF-16 utility functions

`utf` is a set of functions for dealing with UTF-8 and UTF-16 text.

`utf` is shipped as just one `.c` file and one `.h` file, so it can be integrated into any project with ease.

`utf` is written in standard C99, making it fully portable.

`utf` is intended to have fully defined and consistent behavior across platforms, including graceful handling of invalid input (so no error codes!).

On the flipside, this means `utf` might not perform optimally. I have yet to run benchmarks, though.

The design of `utf` is based on Go's `unicode/utf8` and `unicode/utf16` packages, however it does not use any of Go's code.

## Documentation
This library calls Unicode codepoints *runes*.

### `utf8EncodeRune()`
```c
size_t utf8EncodeRune(uint32_t rune, char *encoded);
```
`utf8EncodeRune()` encodes the given rune as UTF-8 into `encoded`, returning the number of bytes encoded. `encoded` must be at least 4 bytes long. If the given rune cannot be encoded (for instance, if it is invalid or is a surrogate half), U+FFFD is encoded.

### `utf8DecodeRune()`
```c
const char *utf8DecodeRune(const char *s, size_t nElem, uint32_t *rune);
```
`utf8DecodeRune()` takes the UTF-8 sequence in `s` and decodes its first rune into `rune`. It returns a pointer to the start of the next rune.

`nElem` is the size of `s`; if `nElem` is 0, `s` is assumed to be large enough. Use this for C-style strings terminated with a `'\0'`.

If the first byte of `s` results in an invalid UTF-8 sequence, U+FFFD is stored in `rune` and the returned pointer is offset by *one*. So, for instance, if we pass in the invalid

```
EF BF 20
^
```

then the `EF` will be decoded as U+FFFD and a pointer to `BF` is returned:

```
EF BF 20
   ^
```

If you run `utf8DecodeRune()` again, the `BF` will also become U+FFFD. Keep this in mind.

### `utf16EncodeRune()`
```c
size_t utf16EncodeRune(uint32_t rune, uint16_t *encoded);
```
`utf16EncodeRune()` encodes the given rune as UTF-16 into `encoded`, returning the number of `uint16_t`s encoded. `encoded` must be at least 2 elements long. If the given rune cannot be encoded (for instance, if it is invalid or is a surrogate half), U+FFFD is encoded.

### `utf16DecodeRune()`
```c
const uint16_t *utf16DecodeRune(const uint16_t *s, size_t nElem, uint32_t *rune);
```
`utf16DecodeRune()` takes the UTF-16 sequence in `s` and decodes its first rune into `rune`. It returns a pointer to the start of the next rune.

`nElem` is the size of `s`; if `nElem` is 0, `s` is assumed to be large enough. Use this for C-style strings terminated with a `L'\0'`.

If the first element of `s` results in an invalid UTF-16 sequence, U+FFFD is stored in `rune` and the returned pointer is offset by *one*. So, for instance, if we pass in the invalid

```
FDEF F987 0020
^
```

then the `FDEF` will be decoded as U+FFFD and a pointer to `F987` is returned:

```
FDEF F987 0020
     ^
```

If you run `utf16DecodeRune()` again, the `F987` will also become U+FFFD. Keep this in mind.

### `utf8RuneCount()`
```c
size_t utf8RuneCount(const char *s, size_t nElem);
```
`utf8RuneCount()` returns the number of runes in `s`, following the same rules as `utf8DecoeRune()`. This function runs in O(N) time.

If `nElem` is 0, `utf8RuneCount()` stops at a `'\0'` (which is not included in the count); otherwise, it stops after `nElem` elements.

### `utf8UTF16Count()`
```c
size_t utf8UTF16Count(const char *s, size_t nElem);
```
`utf8UTF16Count()` returns the number of elements (`uint16_t`s) needed to convert `s` from UTF-8 to UTF-16, following the same rules as `utf8DecodeRune()` and `utf16EncodeRune()`. This function runs in O(N) time.

If `nElem` is 0, `utf8UTF16Count()` stops at a `'\0'` (which is not included in the count); otherwise, it stops after `nElem` elements.

### `utf16RuneCount()`
```c
size_t utf16RuneCount(const uint16_t *s, size_t nElem);
```
`utf16RuneCount()` returns the number of runes in `s`, following the same rules as `utf16DecoeRune()`. This function runs in O(N) time.

If `nElem` is 0, `utf16RuneCount()` stops at a `L'\0'` (which is not included in the count); otherwise, it stops after `nElem` elements.

### `utf16UTF8Count()`
```c
size_t utf16UTF8Count(const uint16_t *s, size_t nElem);
```
`utf16UTF8Count()` returns the number of bytes needed to convert `s` from UTF-16 to UTF-8, following the same rules as `utf16DecodeRune()` and `utf8EncodeRune()`. This function runs in O(N) time.

If `nElem` is 0, `utf16UTF8Count()` stops at a `L'\0'` (which is not included in the count); otherwise, it stops after `nElem` elements.

### `wchar_t` Overloads
```c++
inline size_t utf16EncodeRune(uint32_t rune, wchar_t *encoded);
inline const wchar_t *utf16DecodeRune(const wchar_t *s, size_t nElem, uint32_t *rune);
inline size_t utf16RuneCount(const wchar_t *s, size_t nElem);
inline size_t utf16UTF8Count(const wchar_t *s, size_t nElem);
```

These overloads are provided

* if you are using Microsoft's Visual Studio C++ compilers
* if you are using C++, **and**
* if you specified that `wchar_t` should be a distinct type (the default)

These overloads transparently handle `wchar_t *` and `uint16_t *` being incompatible under all of the above conditions for you. There is no other difference.

## Contributing
Welcome.

## TODOs
- Add a utf8IsValid()/utf16IsValid()?
	- Add a utf8IsFull()/utf16IsFull()?
- Add a utf8RuneEncodedLength()/utf16RuneEncodedLength()?
- Add a utf16IsSurrogate()? utfValidRune()? named rune constants?
- Fix remaining MSVC warnings
- Write a real test suite sometime
- Figure out the best way to make this eligible for https://github.com/nothings/single_file_libs#new-libraries-and-corrections-1 (can the license go at the bottom of the .c file? should it, for any other person ever? I've never dealt with file preambles before so I'm not sure what the subtleties are)

## Background
This came about when I was planning the text event system of [libui](https://github.com/andlabs/libui). Windows and OS X both use UTF-16 for its internal string data types; however, libui uses UTF-8 for all text strings. I got away with it so far because I either only needed to convert entire strings or I decided to use grapheme cluster boundaries instead of byte or codepoint offsets. However, this broke apart with the text handling system, since I have to allow attributed strings to be manipulated after they were made. Therefore, I needed to be able to build tables of mappings between UTF-8 byte offsets and UTF-16 array indices. Building such loops with OS-specific APIs introduces a number of pain points, such as what to do about API error codes and what to do about invalid byte sequences.
