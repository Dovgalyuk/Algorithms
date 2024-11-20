#include <iostream>
#include "blum_filter.h"

int main() {
    BloomFilter filter(10, 0.01);
    
    filter.insert("Dmitry");
    filter.insert("Valentin");
    filter.insert("Roman");

    if(!filter.contains("Dmitry")) {
        std::cout << "Contains 'Dmitry': " << filter.contains("Dmitry") << std::endl;
        return 1;
    }
    if(!filter.contains("Valentin")) {
        std::cout << "Contains 'Valentin': " << filter.contains("Valentin") << std::endl;
        return 1;
    }
    if(!filter.contains("Roman")) {
        std::cout << "Contains 'Roman': " << filter.contains("Roman") << std::endl;
        return 1;
    }
    if(filter.contains("Nikolai")) {
        std::cout << "Contains 'Nikolai': " << filter.contains("Nikolai") << std::endl;
        return 1;
    }

    filter.remove("Dmitry");
    std::cout << "After removing 'Dmitry':" << std::endl;

    if(filter.contains("Dmitry")) {
        std::cout << "Contains 'Dmitry' after remove: " << filter.contains("Dmitry") << std::endl;
        return 1;
    }
    if(!filter.contains("Valentin")) {
        std::cout << "Contains 'Valentin': " << filter.contains("Valentin") << std::endl;
        return 1;
    }
    if(!filter.contains("Roman")) {
        std::cout << "Contains 'Roman': " << filter.contains("Roman") << std::endl;
        return 1;
    }

}