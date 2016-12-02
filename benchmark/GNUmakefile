# 1 december 2016

# build instructions:
# make SYS=system [MSVC=1] [CPUPROFILE=1]
# SYS is the system to check against; see the sys_* source files for the right suffix to use
# SYS=fallback, for instance, runs only parallel tests
# MSVC=1 uses MSVC instead of a gcc-compatible compiler
# CPUPROFILE=1 enables CPU profiling
# - with MSVC=1, not yet implemented
# - without MSVC=1, using gperftools
# running instructions:
# ./b - run all benchmarks
# ./b -skip - run only benchmarks with a system equivalent
# output format:
# Portable BenchmarkUTF8EncodeRuneASCII                       8ns/op
# System   BenchmarkUTF8EncodeRuneASCII                       22ns/op (slower)
# the Portable line is the speed of the utf functions
# the System line is the speed of the system functions
# the parenthesized word is how the system time compares to the utf time; in the above case, the system routine is slower than ours
# if you want to add your own benchmark system, copy TEMPLATE to sys_SYSNAME.c or similar and fill in the blanks according to the comments and other sys_* files

ifndef SYS
$(error You must specify a system; for instance, $(MAKE) $(MAKEFLAGS) SYS=windows)
endif

OUT = b
ifeq ($(SYS),windows)
OUT = b.exe
endif

CFILES = \
	benchmark.c \
	main.c \
	portable.c

CXXFILES =

MFILES =

ifeq ($(SYS),darwin)
MFILES += sys_$(SYS).m
else ifeq ($(SYS),cpp11)
CXXFILES += sys_$(SYS).cpp
else
CFILES += sys_$(SYS).c
endif

ifeq ($(MSVC),1)

CFLAGS += \
	-W4 \
	-wd4100 \
	-TC \
	-bigobj -nologo \
	-RTC1 -RTCs -RTCu

CXXFLAGS += \
	-W4 \
	-wd4100 \
	-TP \
	-bigobj -nologo \
	-RTC1 -RTCs -RTCu \
	-EHsc

LDFLAGS += \
	-largeaddressaware -nologo -incremental:no \
	kernel32.lib

# TODO CPUPROFILE

CC = cl

CCOUTOPT = -Fo:

CXX = cl

LD = link

LDOUTOPT = -out:

else

CFLAGS += \
	-Wall -Wextra -pedantic --std=c99

CXXFLAGS += \
	-Wall -Wextra -pedantic --std=c++11

MFLAGS += \
	-Wall -Wextra -pedantic --std=c99

LDFLAGS += \
	-Wall -Wextra -pedantic
ifeq ($(SYS),cpp11)
LDFLAGS += --std=c++11
else
LDFLAGS += --std=c99
endif

ifeq ($(SYS),darwin)
LDFLAGS += -framework Foundation -framework AppKit
else ifeq ($(SYS),windows)
LDFLAGS += -lkernel32
endif

ifeq ($(CPUPROFILE),1)
CFLAGS += -g
CXXFLAGS += -g
MFLAGS += -g
# TODO is this -Wl option only available on OS X? it's needed on OS X to do symbol lookup for some reason; see http://stackoverflow.com/questions/10562280/line-number-in-google-perftools-cpu-profiler-on-macosx
LDFLAGS += -g -lprofiler
# -Wl,-no_pie
endif

CCOUTOPT = -o

LD = $(CC)

LDOUTOPT = -o

endif

ifeq ($(SYS),cpp11)
ifneq ($(MSVC),1)
LD = $(CXX)
endif
endif

HFILES = \
	../utf.h \
	benchmark.h \
	common.h

OFILES = \
	utf.o \
	$(CFILES:%.c=%.o) \
	$(CXXFILES:%.cpp=%.o) \
	$(MFILES:%.m=%.o)

$(OUT): $(OFILES)
	$(LD) $(LDOUTOPT)$(OUT) $(OFILES) $(LDFLAGS)

utf.o: ../utf.c $(HFILES)
	$(CC) -c $(CCOUTOPT)$@ $< $(CFLAGS)

%.o: %.c $(HFILES)
	$(CC) -c $(CCOUTOPT)$@ $< $(CFLAGS)

%.o: %.cpp $(HFILES)
	$(CXX) -c $(CCOUTOPT)$@ $< $(CXXFLAGS)

%.o: %.m $(HFILES)
	$(CC) -c $(CCOUTOPT)$@ $< $(MFLAGS)

clean:
	rm -f $(OUT) $(OFILES)
.PHONY: clean
