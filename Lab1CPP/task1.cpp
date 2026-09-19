#include <iostream>
#include <fstream>
#include "array.h"

int main(int argc, char **argv) 
{
    std::ifstream input(argv[1]);
    int n;
    input >>n;
    Array<int> arr(n);
    for (int i=0;i<n;i++) {
        int a;
        input >> a;
        arr.set(i,a);
    }
    double sum=0;
    for (int i=0;i<n;i++) sum += arr.get(i);
    double avg =sum/n;

    for (int i=0;i<n;i++) {
        if (arr.get(i) <avg) std::cout << arr.get(i) << " ";
    }
    std::cout << "\n";
    input.close();
    return 0;
}