# 1 december 2016

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
	-RTC1 -RTCs -RTCu

LDFLAGS += \
	-largeaddressaware -nologo -incremental:no \
	kernel32.lib

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
