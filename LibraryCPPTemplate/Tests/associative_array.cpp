#include <iostream>
#include <ctime>
#include "associative_array.h"

int main() {
    auto* array = new AssociativeArray<int, int>();
    for (size_t i = 0; i < 10000; i++)
    {
        array->insert(i, i);
        std::cout << i << std::endl;
    }
    // array->write();
    // array->remove(7);
    // array->write();
    // int count = 20;
    // for (size_t i = 0; i < count; i++)
    // {
    //     array->insert(i, i);
    //     if (!array->isCorrectAVLTree()) {
    //         std::cout << 1 << std::endl;
    //         return 1;
    //     }
    // }
    // for (size_t i = 0; i < count * 2; i++)
    // {
    //     if (i < count) {
    //         if (array->find(i) != i) {
    //             std::cout << 2 << std::endl;
    //             return 1;
    //         }
    //     } else {
    //         if (array->find(i) != NULL) {
    //             std::cout << 3 << std::endl;
    //             return 1;
    //         }
    //     }
    // }
    // array->remove(3);
    // if (!array->isCorrectAVLTree()) {
    //     std::cout << 4 << std::endl;
    //     return 1;
    // }
    // std::cout << "\n\n";
    // array->write();
    // // srand(time(0));
    // // for (size_t i = 0; i < 5; i++)
    // // {
    // //     std::cout << "\n\n";
    // //     int r = rand() % count;
    // //     std::cout << r << std::endl;
    // //     array->remove(r);
    // //     if (!array->isCorrectAVLTree()) {
    // //         std::cout << 4 << std::endl;
    // //         return 1;
    // //     }
    // //     std::cout << "\n\n";
    // // }
    return 0;
}