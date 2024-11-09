#include "lab3.h"

int main(int argc, char **argv) {
    FILE *input;
    if (argc <= 1) {
        input = stdin;
    } else {
        input = fopen(argv[1], "r");
    }

    FILE* output = fopen("output.txt", "w");

    finding_way_matrix(input, output);

    fclose(input);
    fclose(output);

    return 0;
}