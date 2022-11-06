#ifndef H_LABYRINTH
#define H_LABYRINTH

#include <string>
#include <fstream>
#include <iostream>
#include "../../LibraryCPP/queue.h"

class Labyrinth {
    private:
        int width;
        int height;
        // Двумерный массив - лабиринт
        char **map;
        // Карта посещенных мест
        bool **tag_map;
        // Карта путей 
        int **routes;

        void tagCell(const int x, const int y, Queue *queue);
        void drawRoute(const int x_end, const int y_end);
    public: 
        Labyrinth();
        void printLabyrinth();
        void findExit();
        void uploadLabyrinth(const std::string path);
        ~Labyrinth();
};

#endif