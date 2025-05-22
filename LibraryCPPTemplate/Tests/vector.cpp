#include "vector.h"
#include <iostream>

typedef Vector<int> MyVector;

int main() {
    try {
        Vector<int> vector;

        vector.resize(5);
        for (size_t i = 0; i < vector.size(); ++i) {
            vector[i] = static_cast<int>(i);
        }

        std::cout << "Vector (size 5): ";
        for (size_t i = 0; i < vector.size(); ++i) {
            std::cout << vector[i] << " ";
        }
        std::cout << "\n";

        vector.resize(10);
        std::cout << "Vector (size 10): ";
        for (size_t i = 0; i < vector.size(); ++i) {
            std::cout << vector[i] << " ";
        }
        std::cout << "\n";
        
        vector.resize(3);
        std::cout << "Vector (size 3): ";
        for (size_t i = 0; i < vector.size(); ++i) {
            std::cout << vector[i] << " ";
        }
        std::cout << "\n";
        for (int i = 1; i <= 1000; ++i) {
            vector.resize(i);
            vector[i-1] = i;
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
