#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "queue.h"

void putCoordinates(Queue*& queueX, Queue*& queueY) {
    queue_insert(queueY, queue_get(queueY) - 1);
    queue_insert(queueX, queue_get(queueX));

    queue_insert(queueY, queue_get(queueY) + 1);
    queue_insert(queueX, queue_get(queueX));

    queue_insert(queueX, queue_get(queueX) + 1);
    queue_insert(queueY, queue_get(queueY));

    queue_insert(queueX, queue_get(queueX) - 1);
    queue_insert(queueY, queue_get(queueY));

    queue_remove(queueY);
    queue_remove(queueX);
}


enum labirintElements { X = 88, dot = 46, cage = 35, };

int main()
{
    std::ifstream in;
    std::ofstream out;
    std::vector<std::string> labirint;
    Queue* queueY = queue_create();
    Queue* queueX = queue_create();
    std::string line;

    in.open("labirint.txt");
    out.open("output.txt");
    if (!in.is_open()) {
        std::cout << "Критическая ошибка" << std::endl;
        exit(1);
    }
    else {
        while (!in.eof()) {
            std::getline(in, line);
            labirint.push_back(line + "\n");
        }
    }


    int startX = 0;
    int startY = 0;


    for (int i = 0; i < labirint.size(); i++) {
        for (int j = 0; j < labirint.size(); j++) {
            if (labirint[i][j] == 'X') {
                startY = i;
                startX = j;
            }
        }
    }

    queue_insert(queueY, startY);
    queue_insert(queueX, startX);

    while (!queue_empty(queueY)) {


        putCoordinates(queueX, queueY);

        for (int i = 0; i < 4; i++) {
            switch (labirint[queue_get(queueY)][queue_get(queueX)]) {
            case cage:
                queue_remove(queueY);
                queue_remove(queueX);
                break;
            case dot:
                labirint[queue_get(queueY)][queue_get(queueX)] = 'X';
                queue_insert(queueY, queue_get(queueY));
                queue_insert(queueX, queue_get(queueX));
                queue_remove(queueY);
                queue_remove(queueX);
                break;
            case X:
                queue_remove(queueY);
                queue_remove(queueX);
                break;
            default:
                break;
            }
        }




    }
    int count = 0;

    for (int i = 0; i < labirint.size(); i++) {
        for (int j = 0; j < labirint.size(); j++) {
            if (labirint[i][j] == 'X') {
                count++;
            }
        }
        out << labirint[i];
    }
    out << std::endl << count;
    in.close();
    out.close();

}