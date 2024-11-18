#include "lab3.h"
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
   std::ifstream input;
    if (argc <= 1)
    {
        return -1;
    }
    else
    {
        input = std::ifstream(argv[1]);
    }
    for(auto const & line:Task(input)){
        std::cout<<line<<std::endl;
    }

    return 0;
}