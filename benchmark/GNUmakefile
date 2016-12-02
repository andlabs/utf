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

MFILES =

ifeq ($(SYS),darwin)
MFILES += sys_$(SYS).m
else
CFILES += sys_$(SYS).c
endif

ifeq ($(MSVC),1)

CFLAGS += \
	xxx

LDFLAGS += \
	xxxx \
	kernel32.lib

CC = cl

LD = link

else

CFLAGS += \
	-Wall -Wextra -pedantic --std=c99

MFLAGS += \
	-Wall -Wextra -pedantic --std=c99

LDFLAGS += \
	-Wall -Wextra -pedantic --std=c99

ifeq ($(SYS),darwin)
LDFLAGS += -framework Foundation -framework AppKit
else ifeq ($(SYS),windows)
LDFLAGS += -lkernel32
endif

LD = $(CC)

endif

HFILES = \
	../utf.h \
	benchmark.h \
	common.h

OFILES = \
	utf.o \
	$(CFILES:%.c=%.o) \
	$(MFILES:%.m=%.o)

$(OUT): $(OFILES)
	$(LD) -o$(OUT) $(OFILES) $(LDFLAGS)

utf.o: ../utf.c $(HFILES)
	$(CC) -c -o$@ $< $(CFLAGS)

%.o: %.c $(HFILES)
	$(CC) -c -o$@ $< $(CFLAGS)

%.o: %.m $(HFILES)
	$(CC) -c -o$@ $< $(MFLAGS)

clean:
	rm -f $(OUT) $(OFILES)
.PHONY: clean
