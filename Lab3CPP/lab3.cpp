#include <iostream>
#include <fstream>
#include <string>
#include "vector.h"
#include "queue.h"

using namespace std;

void organize_numbers(ifstream& input) {
    int a, b, number;
    Queue *lessThanA = queue_create();
    Queue *betweenAandB = queue_create();
    Queue *greaterThanB = queue_create();

    input >> a >> b;

    while (input >> number) {
        if (number < a) {
            queue_insert(lessThanA, number);
        } else if (number >= a && number <= b) {
            queue_insert(betweenAandB, number);
        } else {
            queue_insert(greaterThanB, number);
        }
    }

    Queue *all = queue_create();

    // Переносим элементы из очередей в одну общую очередь
    while (!queue_empty(lessThanA)) {
        queue_insert(all, queue_get(lessThanA));
        queue_remove(lessThanA);
    }
    while (!queue_empty(betweenAandB)) {
        queue_insert(all, queue_get(betweenAandB));
        queue_remove(betweenAandB);
    }
    while (!queue_empty(greaterThanB)) {
        queue_insert(all, queue_get(greaterThanB));
        queue_remove(greaterThanB);
    }

    // Освобождаем память для очередей
    queue_delete(lessThanA);
    queue_delete(betweenAandB);
    queue_delete(greaterThanB);
    queue_delete(all);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }

    ifstream input(argv[1]);
    if (!input) {
        return 1;
    }

    organize_numbers(input);

    input.close();
    return 0;
}