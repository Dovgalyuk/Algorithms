#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"

void add_in_file(std::ofstream &file, Queue *queue) {

    while (!queue_empty(queue)) {
        file << queue_get(queue) << ' ';
        queue_remove(queue);
    }

}

int main() {

    Queue *queue_one = queue_create();
    Queue *queue_two = queue_create();
    Queue *queue_three = queue_create();

    std::string str;

    int a = 0, b = 0;

    std::ifstream inFile("C:\\Algorithms\\Laba\\input.txt");
    std::ofstream outFile("C:\\Algorithms\\Laba\\output.txt");

    if (inFile.is_open()) {

        while (!inFile.eof()) {

            // предпологаю что отрезок не может быть от нуля до нуля
            if (a == 0 && b == 0) {
                std::getline(inFile, str);

                a = std::stoi(str.substr());

                b = std::stoi(str.substr(str.find(" ")));
            }
            else {
                inFile >> str;

                if (std::stoi(str) < a) {
                    queue_insert(queue_one, std::stoi(str));
                }
                else if (a <= std::stoi(str) && std::stoi(str) <= b) {
                    queue_insert(queue_two, std::stoi(str));
                }
                else {
                    queue_insert(queue_three, std::stoi(str));
                }
            }

        }
    }
    else {
        std::cout << "Error opening file" << std::endl;
    }

    add_in_file(outFile, queue_one);
    add_in_file(outFile, queue_two);
    add_in_file(outFile, queue_three);

    queue_delete(queue_one);
    queue_delete(queue_two);
    queue_delete(queue_three);

    inFile.close();
    outFile.close();

    return 0;
}