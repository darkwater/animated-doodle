#include "c-prog.h"

static const int INPUT_BUF_LEN = 64;

// used for scanf
char input[INPUT_BUF_LEN];

int main() {
    const char *opts[] = {
        "binary",
        "octal",
        "decimal",
        "hexadecimal",
    };

    const int opts_map[] = { 2, 8, 10, 16 };

    printf("Convert from:\n");
    int from_base = input_menu(opts, 4);

    printf("\n");
    printf("Convert to:\n");
    int to_base = input_menu(opts, 4);

    // map inputs to the actual bases
    from_base = opts_map[from_base];
    to_base   = opts_map[to_base];

    printf("\n");
    printf("Converting from base %d to %d\n", from_base, to_base);
    printf("Input value: ");

    readline(input, INPUT_BUF_LEN);

    // parse input
    unsigned long input_val = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        input_val *= from_base;

        char digit = input[i];
        char next_val;
        if (digit >= '0' && digit <= '9') {
            next_val = digit - '0';
        }
        else if (digit >= 'a' && digit <= 'z') {
            next_val = digit - 'a' + 10;
        }
        else {
            printf("Invalid digit: %c at pos %d\n", digit, i);
            return 1;
        }

        if (next_val >= from_base) {
            printf("Digit out of range: %c at pos %d (for base %d)\n", digit, i, from_base);
            return 1;
        }

        input_val += next_val;
    }

    // write output
    char output_buf[65];
    output_buf[63] = '0';
    char *output;
    for (output = output_buf + 63; input_val > 0 && output >= output_buf; output--) {
        *output = digit(input_val % to_base);
        input_val /= to_base;
    }
    output++;

    printf("\n");
    printf("Output: %s\n", output);

    return 0;
}

char digit(int d) {
    if (d >= 0 && d <= 9) {
        return '0' + d;
    }
    else {
        return 'a' + d - 10;
    }
}
