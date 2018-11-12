#ifndef COMMON_H
#define COMMON_H

#define __STDC_WANT_LIB_EXT1__
#include <ctype.h>
#include <curses.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    input = strtok(input, "\n");
    printf("\e[0m");
}

static int input_menu(const char **opts, int num_opts) {
    int choice = 0;

    // init curses
    initscr();
    cbreak();

    while (true) {
        // print options
        for (int i = 0; i < num_opts; i++) {
            char arrow = (choice == i) ? '>' : ' ';
            printf("%c %s\n\r", arrow, opts[i]);
        }

        // get input
        char c = fgetc(stdin);
        switch (c) {
            case 'j': // down
                if (choice < num_opts - 1) choice++;
                break;

            case 'k': // up
                if (choice > 0) choice--;
                break;

            case '\r': // select
                nocbreak();
                endwin();

                return choice;

            case '\e': // escape sequences
                switch (fgetc(stdin)) {
                    case '[':
                        switch (fgetc(stdin)) {
                            case 'A':
                                if (choice > 0) choice--;
                                break;

                            case 'B':
                                if (choice < num_opts - 1) choice++;
                                break;
                        }
                        break;
                }
                break;

            default: // jump to entry starting with this char
                for (int i = choice + 1; i != choice; i++) {
                    // wrap around
                    if (i == num_opts) i = 0;

                    if (opts[i][0] == c) {
                        choice = i;
                        break;
                    }
                }
                break;
        }

        // reset cursor position
        printf("\e[%dA", num_opts);
    }
}

#endif // COMMON_H
