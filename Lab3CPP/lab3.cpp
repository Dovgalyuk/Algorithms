#include <iostream>
#include <fstream>
#include <string>
#include "vector.h"
#include "queue.h"

using namespace std;

Queue* organize_numbers(ifstream& input) {
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
    queue_insert(all, queue_get(lessThanA));
    queue_insert(all, queue_get(betweenAandB));
    queue_insert(all, queue_get(greaterThanB));
    return all;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }

    ifstream input(argv[1]);
    if (!input) {
        return 1;
    }
    Queue *result = queue_create();
    result = organize_numbers(input);

    input.close();
    return 0;
}