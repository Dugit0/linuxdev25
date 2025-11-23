CC = gcc
CFLAGS = -fsanitize=address,undefined,signed-integer-overflow,pointer-compare,pointer-subtract,leak,bounds,pointer-overflow -O2 -std=gnu18 -Wall -Wextra -Wno-pointer-sign -Werror=vla -lm

all: run

run: compile
	./main0.out
	./main1.out 4
	./main2.out '.#' 4
	./main3.out 42 '.#' 4

compile: patch
	$(CC) $(CFLAGS) -o main0.out main0.c
	$(CC) $(CFLAGS) -o main1.out main1.c
	$(CC) $(CFLAGS) -o main2.out main2.c
	$(CC) $(CFLAGS) -o main3.out main3.c

patch: main0.c patch1.patch patch2.patch patch3.patch
	cp main0.c main1.c
	patch main1.c < patch1.patch
	cp main1.c main2.c
	patch main2.c < patch2.patch
	cp main2.c main3.c
	patch main3.c < patch3.patch

clean:
	rm *.out main1.c main2.c main3.c
