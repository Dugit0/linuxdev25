CC = gcc
CFLAGS = -fsanitize=address,undefined,signed-integer-overflow,pointer-compare,pointer-subtract,leak,bounds,pointer-overflow -O2 -std=gnu18 -Wall -Wextra -Wno-pointer-sign -Werror=vla -lm

all: Show

Show: Show.c
	$(CC) $(CFLAGS) -lncurses -o Show Show.c

clean:
	rm Show
