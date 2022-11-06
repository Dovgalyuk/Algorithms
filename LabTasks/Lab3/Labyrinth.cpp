#include "Labyrinth.hpp"

Labyrinth::Labyrinth() {
    width = 0;
    height = 0;
}

void Labyrinth::tagCell(const int x, const int y, Queue *queue) {
    if(!tag_map[x][y]) {
        if((map[x+1][y] == '.' || map[x+1][y] == 'Y') && !tag_map[x+1][y]) {
            // Считаем длину пути
            routes[x+1][y] = routes[x][y] + 1;

            queue_insert(queue, x+1);
            queue_insert(queue, y);
        }
        if((map[x-1][y] == '.' || map[x-1][y] == 'Y') && !tag_map[x-1][y]) {
            // Считаем длину пути
            routes[x-1][y] = routes[x][y] + 1;

            queue_insert(queue, x-1);
            queue_insert(queue, y);
        }
        if ((map[x][y+1] == '.' || map[x][y+1] == 'Y') && !tag_map[x][y+1]) {
            // Считаем длину пути
            routes[x][y+1] = routes[x][y] + 1;

            queue_insert(queue, x);
            queue_insert(queue, y+1);
        }
        if ((map[x][y-1] == '.' || map[x][y-1] == 'Y') && !tag_map[x][y-1]) {
            // Считаем длину пути
            routes[x][y-1] = routes[x][y] + 1;

            queue_insert(queue, x);
            queue_insert(queue, y-1);
        }
        tag_map[x][y] = true;
    }
}

void Labyrinth::findExit() {
    // Очередь посещения клеток
    Queue *queue = queue_create();
    int x_start, y_start;
    int x_end, y_end;
    int x, y;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(map[i][j] == 'X') { // Символ стартовой позиции
                x_start = i; y_start = j;
                queue_insert(queue, x_start);
                queue_insert(queue, y_start);

                // Начальная длина путей
                routes[i][j] = 1;
            } else if (map[i][j] == 'Y') { // Символ конечной позиции
                x_end = i; y_end = j;
            }
        }
    }

    while(!queue_empty(queue)) {
        x = queue_get(queue);
        queue_remove(queue);
        y = queue_get(queue);
        queue_remove(queue);

        tagCell(x, y, queue);
    }
    if(!tag_map[x_end][y_end]) { // Условие непроходимости
        throw "IMPOSSIBLE";
    } else {
        drawRoute(x_end, y_end);
    }

}

void Labyrinth::uploadLabyrinth(const std::string path) {
    std::ifstream file(path);
    std::string buff;
    std::string result;

    if(!file.is_open()) {
        throw "Error: file not exist!";
    } else {
        while(!file.eof()) {
            std::getline(file, buff);
            height++;
            for(int i = 0; i < buff.size(); i++) {
                result += buff[i];
            }
        }
    }

    width = buff.size();
    file.close();
    buff.clear();

    // Создание карты посещенных мест, карты путей
    tag_map = new bool *[height];
    routes = new int *[height];
    for(int i = 0; i < height; i++) {
        tag_map[i] = new bool[width];
        routes[i] = new int[width];
        for(int j = 0; j < width; j++) {
            tag_map[i][j] = false;
            routes[i][j] = -1;
        }
    }

    // Создание лабиринта
    int k = 0;
    map = new char *[height];
    for(int i = 0; i < height; i++) {
        map[i] = new char[width];
        for(int j = 0; j < width; j++) {
            map[i][j] = result[k];
            k++;
        }
    }
}

void Labyrinth::drawRoute(const int x_end, const int y_end) {
    int x = x_end;
    int y = y_end;
    map[x][y] = 'Y';

    while(routes[x][y] != 2) { // Отрисовка пути с конца в начало
        if(routes[x-1][y] == routes[x][y] - 1) {
            x--;
            map[x][y] = 'x';
        } else if (routes[x+1][y] == routes[x][y] - 1) {
            x++;
            map[x][y] = 'x';
        } else if (routes[x][y-1] == routes[x][y] - 1) {
            y--;
            map[x][y] = 'x';
        } else if (routes[x][y+1] == routes[x][y] - 1) {
            y++;
            map[x][y] = 'x';
        }
    }
}

void Labyrinth::printLabyrinth() {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            std::cout << map[i][j];
        }
        std::cout << "\n";
    }
}

Labyrinth::~Labyrinth() {
    for(int i = 0; i < height; i++) {
        delete[] map[i];
        delete[] tag_map[i];
        delete[] routes[i];
    }
    delete[] routes; routes = nullptr;
    delete[] map; map = nullptr;
    delete[] tag_map; tag_map = nullptr;
}