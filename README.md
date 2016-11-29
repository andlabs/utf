# utf: a single-file portable standard C implementation of UTF-8 and UTF-16 utility functions

`utf` is a set of functions for dealing with UTF-8 and UTF-16 text.

`utf` is shipped as just one `.c` file and one `.h` file, so it can be integrated into any project with ease. Both files are written in standard C99, with no implementation-specific behavior, and should be completely portable. TODO behavior about invalid input

TODO this is way too awkward

## Documentation
TODO

## Background
This came about when I was planning the text event system of [libui](https://github.com/andlabs/libui). Windows and OS X both use UTF-16 for its internal string data types; however, libui uses UTF-8 for all text strings. I got away with it so far because I either only needed to convert entire strings or I decided to use grapheme cluster boundaries instead of byte or codepoint offsets. However, this broke apart with the text handling system, since I have to allow attributed strings to be manipulated after they were made. Therefore, I needed to be able to build tables of mappings between UTF-8 byte offsets and UTF-16 array indices. Building such loops with OS-specific APIs introduces a number of pain points, such as what to do about API error codes and what to do about invalid byte sequences.
