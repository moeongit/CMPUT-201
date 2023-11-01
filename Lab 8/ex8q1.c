#include "ex8q1.h"

int main(void) {
    int is_print, value;
    float index;

    while (!feof(stdin)) {
        // Use the read_line function from ex7q1.h here! Do not try to parse the
        // input yourself (that's a lot harder)

        // read_line(...);

        fprintf(stderr, "%d %0.4f %d\n", is_print, index, value);  // You can remove this
    }
}
