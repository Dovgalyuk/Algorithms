#include "lab2.h"

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;

    std::ifstream input;
    input.open(argv[1]);

    if(task(input) != "NO")
    {
        std::cout << "Wrong answer: 1 line of input.txt";
        return 1;
    }

    if(task(input) != "NO")
    {
        std::cout << "Wrong answer: 2 line of input.txt";
        return 1;
    }

    if(task(input) != "YES")
    {
        std::cout << "Wrong answer: 3 line of input.txt";
        return 1;
    }

    if(task(input) != "NO")
    {
        std::cout << "Wrong answer: 4 line of input.txt";
        return 1;
    }

    if(task(input) != "NO")
    {
        std::cout << "Wrong answer: 5 line of input.txt";
        return 1;
    }

    input.close();
    return 0;
}