GENERATES = liboutput_static.a liboutput.so prog prog-a prog-so
TRASH = *.o *~ o.* test_*
CFLAGS = -Wall -Wextra -Wpedantic -fPIC


.PHONY: all test clean distclean trashclean
.SECONDARY: liboutput.a(fun.o const.o)

all: test

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^


liboutput_static.a: liboutput_static.a(fun.o const.o)

liboutput.so: fun.o const.o
	$(CC) $(CFLAGS) -shared -o $@ $^

prog: prog.o const.o fun.o

prog-a: prog.o liboutput_static.a
	cc $^ -o $@

prog-so: prog.o liboutput.so
	cc $^ -o $@

test: prog prog-a prog-so liboutput.so
	./prog > test_prog_0 2>&1
	./prog-a > test_prog-a_0 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so > test_prog-so_0 2>&1
	./prog 123 > test_prog_1 2>&1
	./prog-a 123 > test_prog-a_1 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so 123 > test_prog-so_1 2>&1
	./prog 1 2 3 > test_prog_3 2>&1
	./prog-a 1 2 3 > test_prog-a_3 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so 1 2 3 > test_prog-so_3 2>&1
	cmp test_prog_0 test_prog-a_0 && cmp test_prog_0 test_prog-so_0
	cmp test_prog_1 test_prog-a_1 && cmp test_prog_1 test_prog-so_1
	cmp test_prog_3 test_prog-a_3 && cmp test_prog_3 test_prog-so_3

trashclean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)

clean: trashclean distclean
