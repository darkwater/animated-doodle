#include "m-prog.h"

static const int DISPLAY_PRECISION = 2;
static const int INPUT_BUF_LEN     = 64;

// used for scanf
char input[INPUT_BUF_LEN];

int main() {
    int degree = query_degree();
    double a, b, c, x, x1, x2;

    switch (degree) {
        case -1:
            return 0;

        case 1:
            printf("Solving for x: ax + b = 0\n");
            a = query_constant('a');
            b = query_constant('b');

            printf("\n");
            printf("Solving for x: %.*fx + %.*f = 0\n", DISPLAY_PRECISION, a, DISPLAY_PRECISION, b);

            x = -(b / a);
            printf("x = %.*f\n", DISPLAY_PRECISION, x);
            break;

        case 2:
            printf("Solving for x: ax² + bx + c = 0\n");
            a = query_constant('a');
            b = query_constant('b');
            c = query_constant('c');

            printf("\n");
            printf("Solving for x: %.*fx² + %.*fx + %.*f = 0\n", DISPLAY_PRECISION, a, DISPLAY_PRECISION, b, DISPLAY_PRECISION, c);

            x1 = (-b - sqrt(b*b - 4.0 * a * c)) / (2 * a);
            x2 = (-b + sqrt(b*b - 4.0 * a * c)) / (2 * a);

            if (x1 == x2) {
                printf("x = %.*f\n", DISPLAY_PRECISION, x1);
                break;
            }

            if (x1 != x1) { // nan
                printf("undefined\n");
                break;
            }

            printf("x = %.*f and x = %.*f\n", DISPLAY_PRECISION, x1, DISPLAY_PRECISION, x2);
            break;
    }

    return 0;
}

int query_degree() {
    int degree;

get_input:
    printf("\n");
    printf("[q] to quit\n");
    printf("Input polynomial degree [1-2]: ");

    readline(input, INPUT_BUF_LEN);

    switch (*input) {
        case 'q':
            return -1;

        default:
            degree = atoi(input);
            break;
    }

    if (degree < 1 || degree > 2) {
        printf("Invalid input.\n");
        goto get_input;
    }

    return degree;
}

double query_constant(char name) {
    printf("Input value for %c: ", name);

    readline(input, INPUT_BUF_LEN);

    switch (*input) {
        case 'q':
            return NAN;

        default:
            return strtod(input, NULL);
    }
}
