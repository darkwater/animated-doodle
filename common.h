#ifndef COMMON_H
#define COMMON_H

#define __STDC_WANT_LIB_EXT1__
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Return suffix for ordinal numbers
static char* num_suffix(int num) {
    // 11th, 12th, 13th
    if (num % 100 / 10 == 1) return "th";

    switch (num % 10) {
        case 1:
            return "st";
        case 2:
            return "nd";
        case 3:
            return "rd";
        default:
            return "th";
    }
}

// Read a line from stdin
static void readline(char *input, int len) {
    printf("\e[1m");
    fgets(input, len, stdin);
    printf("\e[0m");
}

#endif // COMMON_H
