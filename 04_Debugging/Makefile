CC = gcc
CFLAGS = -O0 -g -std=gnu18

all: range test

test: test1 test2

test1: range
	gdb --batch --quiet -x script1.gdb ./range | grep @@@ | diff gdbout1.txt -

test2: range
	gdb --batch --quiet -x script2.gdb ./range | grep @@@ | diff gdbout2.txt -


range: range.c
	$(CC) $(CFLAGS) -o range range.c

clean:
	rm range
