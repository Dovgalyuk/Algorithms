#include <iostream>
#include <fstream>

#include "stack.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: input file is required\n";
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open())
    {
        std::cerr << "Error: cannot open file\n";
        return 1;
    }

    long long n;

    if (!(file >> n) || n < 0)
    {
        std::cerr << "Error: invalid particle count\n";
        return 1;
    }

    Stack* stack = stack_create();


    for (long long i = 0; i < n; ++i)
    {
        Data coordinate;
        char charge;
        
        file >> coordinate >> charge;

        if (charge == '+')
        {
            stack_push(stack, coordinate);
        }
        else if (!stack_empty(stack))
        {
            Data positive_coordinate = stack_get(stack);

            stack_pop(stack);

            std::cout << positive_coordinate << ' ' << coordinate << '\n';
        }
    }

    stack_delete(stack);
    return 0;
}