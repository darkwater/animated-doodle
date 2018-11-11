#include "r-prog.h"

static const int MAX_NUM_RESISTORS = 32;
static const int INPUT_BUF_LEN     = 64;

// used for scanf
char input[INPUT_BUF_LEN];

// state
Resistor resistors[MAX_NUM_RESISTORS];
int num_resistors = 0;
bool quit;

int main() {
    while (num_resistors < MAX_NUM_RESISTORS) {
        if (query_resistor()) break;
    }

    if (quit) return 0;

    double total_resistance = 0;
    for (int i = 0; i < num_resistors; i++) {
        if (resistors[i].serial) {
            total_resistance += resistors[i].value;
        }
        else {
            total_resistance = (total_resistance * resistors[i].value)
                             / (total_resistance + resistors[i].value);
        }
    }

    printf("\n");
    printf("Total resistance: %f\n", total_resistance);

    return 0;
}

bool query_resistor() {
    int resistor_n = num_resistors + 1;
    double value;
    bool serial;

    printf("\n");
    printf("Input %d%s resistor:\n", resistor_n, num_suffix(resistor_n));
    printf("[c] to calculate\n");
    printf("[d] to delete last\n");
    printf("[q] to quit\n");
    printf("Value in ohm: ");

    readline(input, INPUT_BUF_LEN);

    switch (*input) {
        case 'q':
            quit = true;
        case 'c':
            return true;

        case 'd':
            num_resistors--;
            return false;

        default:
            value = strtod(input, NULL);
            break;
    }

    if (resistor_n == 1) {
        serial = true;
    }
    else {
        printf("[S]erial or [p]arallel: ");

        readline(input, INPUT_BUF_LEN);

        switch (tolower(input[0])) {
            case 'q':
                quit = true;
            case 'c':
                return true;

            case 'd':
                num_resistors--;
                return false;

            case 's':
                serial = true;
                break;
            case 'p':
                serial = false;
                break;

            default:
                printf("Invalid input.\n");
                return false;
        }
    }

    resistors[resistor_n - 1].value = value;
    resistors[resistor_n - 1].serial = serial;

    num_resistors++;
    return false;
}
