CC=clang

%: %.c %.h common.h
	$(CC) -std=c99 -lm -lcurses $< -o $@
