#include "lab3.h"

int main(int argc, char **argv)
{
   std::ifstream input;
    if (argc <= 1)
    {
         input = std::ifstream("input.txt");
    }
    else
    {
        input = std::ifstream(argv[1]);
    }
    Algorithm(input);

    return 0;;
}