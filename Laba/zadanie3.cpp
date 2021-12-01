#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"

int main() {

    Queue *queue_temp = queue_create();

    Queue *queue_one = queue_create();
    Queue *queue_two = queue_create();
    Queue *queue_three = queue_create();

    std::string str;

    int a = 0, b = 0;

    std::ifstream inFile("C:\\Algorithms\\Laba\\input.txt");
    std::ofstream outFile("C:\\Algorithms\\Laba\\output.txt");

    if (inFile.is_open()) {

        while (!inFile.eof()) {

            inFile >> str;

            queue_insert(queue_temp, std::stoi(str));

        }
    }
    else {
        std::cout << "Error opening file" << std::endl;
    }

    a = queue_get(queue_temp);
    queue_remove(queue_temp);

    b = queue_get(queue_temp);
    queue_remove(queue_temp);

    while (!queue_empty(queue_temp)) {

        if (queue_get(queue_temp) < a) {
            queue_insert(queue_one, queue_get(queue_temp));
            queue_remove(queue_temp);
        }
        
        else if (a <= queue_get(queue_temp) && queue_get(queue_temp) <= b) {
            queue_insert(queue_two, queue_get(queue_temp));
            queue_remove(queue_temp);
        }
        // else if (queue_get(queue_temp) > b) {
        //     queue_insert(queue_three, queue_get(queue_temp));
        //     queue_remove(queue_temp);
        // }
        else {
            queue_insert(queue_three, queue_get(queue_temp));
            queue_remove(queue_temp);
        }
    }

    while (!queue_empty(queue_one)) {
        outFile << queue_get(queue_one) << ' ';
        queue_remove(queue_one);
    }

    while (!queue_empty(queue_two)) {
        outFile << queue_get(queue_two) << ' ';
        queue_remove(queue_two);
    }

    while (!queue_empty(queue_three)) {
        outFile << queue_get(queue_three) << ' ';
        queue_remove(queue_three);
    }

    queue_delete(queue_temp);

    queue_delete(queue_one);
    queue_delete(queue_two);
    queue_delete(queue_three);

    inFile.close();
    outFile.close();

    return 0;
}