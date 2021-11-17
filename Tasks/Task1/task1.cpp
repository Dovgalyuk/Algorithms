#include <iostream>
#include "array.h"

int MAX_NOTE = 5;
int MIN_NOTE = 2;

int generateNote() {
    return std::max(abs(rand()) % (MAX_NOTE + 1), MIN_NOTE);
}

int main() {
    int n = 0;
    std::cin >> n;
    Array* marks = array_create(n);
    for (int i = 0; i < n; ++i) {
        int mark = generateNote();
        array_set(marks, i, mark);
    }

    Array* counter = array_create(MAX_NOTE + 1);
    for (int i = 0; i < array_size(counter); ++i) {
        array_set(counter, i, 0);
    }
    for (int i = 0; i < n; ++i) {
        int note = array_get(marks, i);
        array_set(counter, note, array_get(counter, note) + 1);
    }
    for (int i = 0; i < array_size(counter); ++i) {
        int count = array_get(counter, i);
        if (count > 0) {
            std::cout << "Number of ratings " << i << ": " << count << std::endl;
        }
    }
    array_delete(marks);
    array_delete(counter);
    return 0;
}