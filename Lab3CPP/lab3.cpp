#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include "queue.h"
#include <vector>

struct Point {
    int x, y;
};
void Readout(std::ifstream& file, std::vector<char>& labyrinth, size_t* w, size_t* h);
Point Start_search(size_t w, size_t h, const std::vector<char>& labyrinth);
bool Range_and_Wall(int x, int y, size_t w, size_t h, const std::vector<char>& labyrinth, bool* flag_was_here);
Point Number_closest_to_the_starting_position(const std::vector<char>& labyrinth, Point start, size_t w, size_t h);


void Readout(std::ifstream& file, std::vector<char>& labyrinth, size_t* w, size_t* h) {
    char simvol;
    bool first = true;
    int character_counter = 0;

    while (file.read(&simvol, 1)) {
        if (simvol != '\n') {
            labyrinth.push_back(simvol);
            character_counter++;
        }
        if (simvol == '\n') {
            if (first) {
                *w = character_counter;
                first = false;
            }
            character_counter = 0;
        }
    }
    file.close();
    if (*w == 0) {
        throw std::runtime_error("The width of the maze is zero");

    }
    else {
        *h = static_cast<int>(labyrinth.size() / *w);
    }
}




Point Start_search(size_t w, size_t h, const std::vector<char>& labyrinth) {
    for (size_t y = 0; y < h; y++) {
        for (size_t x = 0; x < w; x++) {
            if (labyrinth[y * w + x] == 'X') {
                return {(int) x,(int) y };
            }
        }
    }
    return { -1, -1 };
}


bool Range_and_Wall(int x, int y, size_t w, size_t h, const std::vector<char>& labyrinth, bool* flag_was_here) {
    if (x < 0 || y < 0 || (size_t)x >= w ||(size_t) y >= h) {
        return false;
    }
    if (flag_was_here[y * w + x]) {
        return false;
    }
    if (labyrinth[y * w + x] == '#') {
        return false;
    }

    return true;
}

Point Number_closest_to_the_starting_position(const std::vector<char>& labyrinth, Point start, size_t w, size_t h) {
    Queue* queue = queue_create();
    bool* flag_was_here = new bool[w * h]();
    Point four_directions[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
    queue_insert(queue, Data(start.y * w + start.x));
    flag_was_here[start.y * w + start.x] = true;

    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove_one(queue);
        int currentX = int(current % w);
        int currentY = int(current / w);
        char simvol = labyrinth[currentY * w + currentX];

        if (simvol >= '0' && simvol <= '9') {
            delete[]flag_was_here;
            queue_delete(queue);
            return { currentX, currentY };
        }

        for (int i = 0; i < 4; ++i) {
            int newX = currentX + four_directions[i].x;
            int newY = currentY + four_directions[i].y;
            if (Range_and_Wall(newX, newY, w, h, labyrinth, flag_was_here)) {
                flag_was_here[newY * w + newX] = true;
                queue_insert(queue, Data(newY * w + newX));
            }
        }

    }

    queue_delete(queue);
    delete[]flag_was_here;
    return { -1, -1 };
}


int main(int argc,char** argv) {
    std::vector<char> labyrinth;
    std::string filepath = argv[1];
    std::ifstream file(filepath);

    if (!file)
    {
        std::cout << "the file did not open\n";
        return 1;
    }
    try {
        size_t w = 0, h = 0;
        Readout(file, labyrinth, &w, &h);

        Point start = Start_search(w, h, labyrinth);
        if (start.x != -1) {
            Point result = Number_closest_to_the_starting_position(labyrinth, start, w, h);
            if (result.x != -1) {
                std::cout << labyrinth[result.y * w + result.x] << std::endl;
            }
            else {
                std::cout << "The endpoint was not found." << std::endl;
            }
        }
        else {
            std::cout << "The starting point was not found." << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}


