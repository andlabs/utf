# 27 november 2016

OUT = utftest

CFILES = \
	../utf.c \
	test.c

HFILES = \
	../utf.h

$(OUT): test.o utf.o
	$(CC) -o $(OUT) test.o utf.o -Wall -Wextra -pedantic --std=c99

utf.o: ../utf.c $(HFILES)
	$(CC) -c -o utf.o ../utf.c -Wall -Wextra -pedantic --std=c99

test.o: test.c $(HFILES)
	$(CC) -c -o test.o test.c -Wall -Wextra -pedantic --std=c99

clean:
	rm -f $(OUT) *.o
.PHONY: clean
