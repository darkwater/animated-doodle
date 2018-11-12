#include "s-prog.h"

static const int INPUT_BUF_LEN = 64;

// used for scanf
char input[INPUT_BUF_LEN];

int main() {
    const char *opts[] = {
        "palindrome",
        "vowels",
    };

    printf("Choose an option:\n");
    int choice = input_menu(opts, 2);
    printf("\n");

    switch (choice) {
        case 0:
            return palindrome();
        case 1:
            return vowels();
    }

    return 1;
}

int palindrome() {
    printf("Enter strings to test:\n");

    while (1) {
        printf("> ");
        readline(input, INPUT_BUF_LEN);

        if (!strcasecmp(input, "quit")) return 0;
        if (!strcasecmp(input, "q")) return 0;

        bool matching = true;
        char *a = input;
        char *b = index(input, '\0') - 1;
        while (b > a) {
            if (strncasecmp(a, b, 1)) {
                matching = false;
                break;
            }

            a++;
            b--;
        }

        printf("\e[A\r%s %s\e[B\r\e[0m", matching ? "\e[32m " : "\e[31mx", input);
    }
}

int vowels() {
    printf("Enter strings to transform:\n");

    char output[INPUT_BUF_LEN];

    while (1) {
        printf("> ");
        readline(input, INPUT_BUF_LEN);

        if (!strcasecmp(input, "quit")) return 0;
        if (!strcasecmp(input, "q")) return 0;

        memset(output, '\0', INPUT_BUF_LEN);

        char *o = output;
        for (char *c = input; *c != '\0'; c++) {
            if (!index("aiueoAIUEO", *c)) {
                *o = *c;
                o++;
            }
        }

        printf("\e[A\e[2K  %s\n", output);
    }
}
