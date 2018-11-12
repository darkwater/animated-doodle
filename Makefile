CC=clang

%: %.c %.h common.h
	$(CC) -g -std=c99 -lm -lcurses $< -o $@
