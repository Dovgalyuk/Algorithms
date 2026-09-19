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
    Array<int> counts(1001);
    for (int i=0;i<1001;i++) counts.set(i,0);
    for (int i=0;i<n;i++) {
        int x= arr.get(i);
        counts.set(x, counts.get(x) +1);
    }

    for (int i=0;i<n;i++) {
        if (counts.get(arr.get(i)) ==1) std::cout << arr.get(i) << " ";
    }
    std::cout << "\n";
    input.close();
    return 0;
}