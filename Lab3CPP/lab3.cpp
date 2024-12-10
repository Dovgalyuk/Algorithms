#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"

void processQueue(const std::string &inputFile, const std::string &outputFile) {
    std::ifstream input(inputFile);
    std::ofstream output(outputFile);

    if (!input || !output) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    int maxSize;
    input >> maxSize;

    Queue *queue = queue_create();
    int currentSize = 0;

    std::string command;
    while (input >> command) {
        if (command == "ADD") {
            int value;
            input >> value;
            if (currentSize < maxSize) {
                queue_insert(queue, value);
                currentSize++;
            } else {
                output << "INVALID ADD" << std::endl;
            }
        } else if (command == "GET") {
            if (!queue_empty(queue)) {
                output << queue_get(queue) << std::endl;
                queue_remove(queue);
                currentSize--;
            } else {
                output << "INVALID GET" << std::endl;
            }
        }
    }

    output << "QUEUE" << std::endl;
    while (!queue_empty(queue)) {
        output << queue_get(queue) << std::endl;
        queue_remove(queue);
    }

    queue_delete(queue);
}

int main() {
    processQueue("input.txt", "output.txt");
    return 0;
}
