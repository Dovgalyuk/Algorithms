#include <iostream>
#include <string>
#include <fstream>
#include "queue.h"
#include "list.h"


struct Point {
    int x, y;
};

void Readout(std::ifstream& file, List* list, int* w, int* h);
void Output_labyrinth(List* list, int w, int h);
Point Start_search(int w, int h, List* list);
Point Number_closest_to_the_starting_position(List* list, Point start, int w, int h);
bool Range_and_Wall(int x, int y, int w, int h, List* list, bool* flag_was_here);


void Readout(std::ifstream& file, List* list, int* w, int* h) {
    char simvol;
    bool first = true;
    int character_counter = 0;

    while (file.read(&simvol, 1)) {
        if (simvol != '\n') {
            list_insert_end(list, simvol);
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

    *h = list_size(list) / *w;

}

void Output_labyrinth(List* list, int w, int h) {
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            ListItem* item = list_get(list, y * w + x);
            std::cout << (char)list_item_data(item);
        }
        std::cout << std::endl;
    }
}

Point Start_search(int w, int h, List* list) {
    int startX = -1;
    int startY = -1;
    bool found = false;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            ListItem* item = list_get(list, y * w + x);
            if ((char)list_item_data(item) == 'X') {
                startX = x;
                startY = y;
                found = true;
                break;
            }
        }

    }
    return { startX, startY };
}
bool Range_and_Wall(int x, int y, int w, int h, List* list, bool* flag_was_here) {
    if (x < 0 || y < 0 || x >= w || y >= h) {
        return false;
    }
    if (flag_was_here[y * w + x]) {
        return false;
    }
    ListItem* item = list_get(list, y * w + x);
    if ((char)list_item_data(item) == '#') {
        return false;
    }

    return true;
}

Point Number_closest_to_the_starting_position(List* list, Point start, int w, int h) {
    Queue* queue = queue_create();
    bool* flag_was_here = new bool[w * h]();
    Point four_directions[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
    queue_insert(queue, start.y * w + start.x);
    flag_was_here[start.y * w + start.x] = true;

    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove_one(queue);
        int currentX = current % w;
        int currentY = current / w;
        ListItem* item = list_get(list, currentY * w + currentX);
        char simvol = (char)list_item_data(item);

        if (simvol >= '0' && simvol <= '9') {

            delete[]flag_was_here;
            return { currentX, currentY };
        }
        
         for (int i = 0; i < 4; ++i) {
                int newX = currentX + four_directions[i].x;
                int newY = currentY + four_directions[i].y;
                if (Range_and_Wall(newX, newY, w, h, list, flag_was_here)) {
                    flag_was_here[newY * w + newX] = true;
                    queue_insert(queue, newY * w + newX);
                }
         }
        
    }

    queue_delete(queue);
    delete[]flag_was_here;
    return { -1, -1 };
}

int main() {
    try {
        std::ifstream file("input.txt");
        List* list = list_create();
        int w = 0, h = 0;
        Readout(file, list, &w, &h);
        Output_labyrinth(list, w, h); 
        Point start = Start_search(w, h, list);
        if (start.x != -1) {
            Point result = Number_closest_to_the_starting_position(list, start, w, h);
            if (result.x != -1) {
                ListItem* item = list_get(list, result.y * w + result.x);
                std::cout <<"closest point:"<<(char)list_item_data(item);
            }
            else {
               std::cout<<"The endpoint was not found"<<std::endl; 
            }
        }
        else {
            std::cout << "The starting point was not found" << std::endl;
        }

        list_delete(list);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
      
    }

    return 0;
}
