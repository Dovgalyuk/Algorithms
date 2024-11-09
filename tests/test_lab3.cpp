#include "lab3.h"
#include <cstring>

int main(int argc, char **argv)
{
    FILE *input;
    if (argc <= 1)
        input = stdin;
    else
        input = fopen(argv[1], "r");

    FILE* out = fopen("out.txt", "w");

    finding_way_matrix(input, out);
    fclose(out);
    
    FILE* ans = fopen("out.txt", "r");

    char str[10];

    if (fscanf(ans, "%s", str) < 0) {
        return -1;
    }

    if (std::strcmp(str, "IMPOSSIBLE") == 0) {
        std::cout << "Test passed\n";
    } else {
        std::cout << "Test failed\n";
        return 1;
    }

    fclose(input);
    fclose(ans);

    return 0;
}