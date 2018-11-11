CC=clang

%: %.c %.h common.h
	$(CC) -lm $< -o $@
