#include <iostream>
#include <fstream>
#include "array.h"

int main(int argc, char* argv[]) {

    const char* filename = "input.txt";

    if (argc == 2) {
        filename = argv[1];
    }

    std::ifstream file(filename);
    int n;
    file >> n;

    if(n <= 0) {
        std::cout << "Invalid size";
        return 0;
    }

    Array arr(n);

    for(int i = 0; i < n; i++) {
        file >> arr[i];
    }

    for(int i = 0; i < n; i++) {
        bool unDel = true;
        for(int j = 0; j < n; j++) {
            if(i != j) {
                if(arr[i] % arr[j] == 0) {
                unDel = false;
                }
            }
        }
        if(unDel) {
            std::cout << arr[i] << " ";
        }
    }
}