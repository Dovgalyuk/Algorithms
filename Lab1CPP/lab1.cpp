#include <iostream>
#include "array.h"
#include <fstream>
#include <string>
#include <limits>

void findFastestCars(std::istream& in) {
    int n;
    in >> n;

    if (n <= 0) {
        std::cout << "Task4: no data" << std::endl;
        return;
    }

    Array* speeds = array_create(n);
    int maxSpeed = std::numeric_limits<int>::min();

    for (int i = 0; i < n; ++i) {
        int speed;
        in >> speed;
        array_set(speeds, i, speed);

        if (speed > maxSpeed) {
            maxSpeed = speed;
        }
    }

    int firstIndex = -1;
    int lastIndex = -1;

    for (int i = 0; i < n; ++i) {
        if (array_get(speeds, i) == maxSpeed) {
            if (firstIndex == -1) { 
                firstIndex = i;
            }
            lastIndex = i; 
        }
    }

    if (firstIndex == lastIndex) {
        std::cout << "Task4: " << firstIndex + 1 << std::endl;
    } else {
        std::cout << "Task4: " << firstIndex + 1 << " " << lastIndex + 1 << std::endl;
    }

    array_delete(speeds);
}

void findNonDivisibleElements(std::istream& in) {
    int m;
    in >> m;

    if (m <= 0) {
        std::cout << "Task5: no data" << std::endl;
        return;
    }

    Array* arr = array_create(m);
    for (int i = 0; i < m; ++i) {
        int val;
        in >> val;
        array_set(arr, i, val);
    }

    std::cout << "Task5:";
    
    for (int i = 0; i < m; ++i) {
        bool isDivisible = false;
        int currentVal = array_get(arr, i);

        for (int j = 0; j < m; ++j) {
            if (i == j) {
                continue;
            }
            int divisor = array_get(arr, j);

            if (divisor != 0 && currentVal % divisor == 0) {
                isDivisible = true;
                break;
            }
        }

        if (!isDivisible) {
            std::cout << " " << currentVal;
        }
    }
    std::cout << std::endl;
    array_delete(arr);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    std::ifstream infile(argv[1]);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    findFastestCars(infile);
    findNonDivisibleElements(infile);

    infile.close();
    return 0;
}