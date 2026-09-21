#include <iostream>
#include <fstream>
#include "../Array.h"

int main(int argc, char* argv[]) {

    const char* filename = "input.txt";

    if (argc == 2) {
        filename = argv[1];
    }

    std::ifstream file(filename);

    if(!file) {
        std::cout << "File open error";
        return 0;
    }

    int n;
    file >> n;

    Array arr(n);

    for(int i = 0; i < n; i++) {
        file >> arr[i];
    }

    int max = arr[0];

    for(int i = 0; i < n; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }

    int first = -1;
    int last = -1;

    for(int i = 0; i < n; i++) {
        if(arr[i] == max) {
            if(first == -1) {
                first = i + 1;
            }
            last = i + 1;
        }
    }

    if (first == last) {
    std::cout << first;
    } else {
    std::cout << first << " " << last;
    }   
}