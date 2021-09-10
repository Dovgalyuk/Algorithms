#include <iostream>
#include <ctime>
#include "array.h"

int writeSize() {
    int size;
    std::cout << "Days in a month:";
    std::cin >> size;
    return size;
}

int randRainfall() {
    return rand() % 100;
}

void fillContainer(Array* array) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < array_size(array); i++) {
        array_set(array, i, randRainfall());
    }
}

int getHalfWithMaxRainfall(Array* array) {
    int firstHalf = 0;
    int secondHalf = 0;
    size_t length = array_size(array);
    for (int i = 0; i < length; i++) {
        int num = array_get(array, i);
        if (i < (length / 2))
            firstHalf += num;
        else
            secondHalf += num;
    }
    return firstHalf > secondHalf ? 1 : 2;
}

int getDecadeWithMaxRainfall(Array* array) {
    int maxRainfall = 0;
    int decade = -1;
    int lastMaxRainfall = 0;
    int lastDecade = 0;
    for (int i = 0; i < array_size(array); i++) {
        if (i / 10 != lastDecade) {
            if (lastMaxRainfall > maxRainfall) {
                maxRainfall = lastMaxRainfall;
                decade = lastDecade;
            }
            lastDecade = i / 10;
            lastMaxRainfall = 0;
        }
        lastMaxRainfall += array_get(array, i);
    }
    if (lastMaxRainfall > maxRainfall) {
        decade = lastDecade;
    }
    return decade + 1;
}

void printToConsole(Array* array) {
    for (int i = 0; i < array_size(array); i++) {
        std::cout << array_get(array, i) << " ";
    }
    std::cout << std::endl;
}

int main() {
    int size = writeSize();
    Array* array = array_create(size);
    fillContainer(array);
//    printToConsole(array);
    std::cout << "Most precipitation fell in: " << getHalfWithMaxRainfall(array) << " half a month." << std::endl;
    std::cout << "Most precipitation fell in: " << getDecadeWithMaxRainfall(array) << " ten days of the month." << std::endl;
    array_delete(array);
    return 0;
}
