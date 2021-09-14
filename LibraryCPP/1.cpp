#include <iostream>
#include "array.cpp"
#include <ctime>

int writeSize() {
    int size;
    std::cout << " input size array ";
    std::cin >> size;
    return size;
}

void fillContainer(Array* array) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < array_size(array); i++) {
        array_set(array, i, rand() % 100);
    }
}

int main ()
{
    int size = writeSize();
    Array* array = array_create(size);
    fillContainer(array);
    int a,b;
    std:: cout << " input a and b ";
    std:: cin >> a >> b;
    int sum=0;
    
    for (int i = 0; i < array_size(array); i++)
    {
        if (array_get(array, i) % b == 0 || array_get(array, i) % a == 0)
                sum = sum + array_get(array, i);
    }
    
    std::cout << " sum =  " << sum;
    array_delete(array);
    return 0;
}