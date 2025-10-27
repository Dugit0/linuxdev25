CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS_SO=-shared -fPIC

TARGET=move
LIB=protect.so
TEST_SCRIPT=run_tests.sh

.PHONY: all test clean

all: $(TARGET) $(LIB)

$(TARGET): move.c
	$(CC) $(CFLAGS) -o $(TARGET) move.c

$(LIB): protect.c
	$(CC) $(CFLAGS) $(LDFLAGS_SO) -o $(LIB) protect.c

test: all $(TEST_SCRIPT)
	@chmod +x $(TEST_SCRIPT)
	@./$(TEST_SCRIPT)

clean:
	rm -f $(TARGET) $(LIB) infile outfile infile_PROTECT
