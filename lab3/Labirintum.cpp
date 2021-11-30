#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "queue.h"

void checker(int &startX, int &startY, int columns, int rows) {

    if (startY > rows - 1) {
        startY--;
    }
    else if (startY < 0) {
        startY++;
    }

    if (startX > columns - 1) {
        startX--;
    }
    else if (startX < 0) {
        startX++;
    }
}

enum labirintElements {X = 88, dot = 46, cage = 35,};

int main()
{
    std::ifstream in;
    std::ofstream out;
    std::vector<std::string> labirint;
    Queue* queue = queue_create();
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

    int columns = 0;
    int rows = 0;

    int startX = 0;
    int startY = 0;
  

    for (int i = 0; i < labirint.size(); i++) {
        rows++;
        for (int j = 0; j < labirint.size(); j++) {
            columns++;
            if (labirint[i][j] == 'X') {
                startY = i;
                startX = j;
            }
        }
    }
    int lastX = startX;
    int lastY = startY;

    queue_insert(queue, labirint[startY][startX]);

    while (!queue_empty(queue)) {

        queue_remove(queue);

        for (int i = 0; i < 4; i++) {

            switch (i)
            {
            case 0: 
                startY--;
                checker(startX, startY, columns, rows);
                queue_insert(queue, labirint[startY][startX]);
                break;
            case 1:
                startY++;
                checker(startX, startY, columns, rows);
                queue_insert(queue, labirint[startY][startX]);
                break;
            case 2:
                startX++;
                checker(startX, startY, columns, rows);
                queue_insert(queue, labirint[startY][startX]);
                break;
            case 3:
                startX--;
                checker(startX, startY, columns, rows);
                queue_insert(queue, labirint[startY][startX]);
                break;
            default:
                break;
            }

            switch (labirint[startY][startX]) { 
            case cage:
                startX = lastX;
                startY = lastY;
                queue_remove(queue);
                break;
            case dot:
                labirint[startY][startX] = 'X';
                lastX = startX; 
                lastY = startY;                
                break;
            case X:
                startX = lastX;
                startY = lastY;
                queue_remove(queue);
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