#include <iostream>
#include <fstream>
#include <string>
#include "utility.h"

bool isPalindrome(int n)
{
    std::string s = std::to_string(n);
    std::string r = s;
    std::reverse(r.begin(), r.end());
    return s == r;
}

Array<int> readDataForPalindroms(const char* filename) {
    std::ifstream fin(filename);

    size_t size;
    fin >> size;
    fin.close();

    Array<int> arr(size);

    int num = 1;
    size_t counter = 0;

    while (counter < size)
    {
        if (isPalindrome(num))
        {
            arr.set(counter, num);
            ++counter;
        }
        ++num;
    }

    return arr;
}


int main(int argc, char** argv)
{
    if (argc <= 1) {
        std::cerr << "Не хватает аргументов командной строки!" << std::endl;
        return 1;
    }

    Array<int> arr = readDataForPalindroms(argv[1]);
    printArray(arr);

    return 0;
}
