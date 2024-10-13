#include <iostream>
#include <fstream>
#include "../LibraryCPP/queue.h"
#include "../LibraryCPP/vector.h"

struct Point {
    int x, y;
};

bool is_valid(int x, int y, int width, int height, const Vector* lab, bool* visited) {
    if (x < 0 || x >= width || y < 0 || y >= height) 
        return false;
    if (visited[y * width + x]) 
        return false;

    if ((char)vector_get(lab, y * width + x) == '#')
        return false;
    else
        return true;
}

Point find_clothest(const Vector* lab, int start_x, int start_y, int width, int height) {
    Queue* queue = queue_create();
    bool* visited = new bool[width * height]();
    Point dir[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

    queue_insert(queue, start_y * width + start_x);
    visited[start_y * width + start_x] = true;

    while (!queue_empty(queue)) 
    {
        int curr = queue_get(queue);
        queue_remove(queue);

        int curr_x = curr % width;
        int curr_y = curr / width;

        char cell = (char)vector_get(lab, curr_y * width + curr_x);
        if (cell >= '0' && cell <= '9') 
        {
            queue_delete(queue);
            delete[] visited;
            return { curr_x, curr_y };
        }

        for (int i = 0; i < 4; ++i) 
        {
            int new_x = curr_x + dir[i].x;
            int new_y = curr_y + dir[i].y;

            if (is_valid(new_x, new_y, width, height, lab, visited)) 
            {
                visited[new_y * width + new_x] = true;
                queue_insert(queue, new_y * width + new_x);
            }
        }
    }

    queue_delete(queue);
    delete[] visited;
    return { -1, -1 };
}

int main() {
    std::ifstream in("input.txt");
    Vector* lab = vector_create();
    int width = 0;
    if (in) 
    {
        char temp;
        int counter = 0;
        while (in.get(temp)) 
        {
            if (temp != '\n') 
            {
                vector_push(lab, temp);
                if(!width)
                    counter++;
            }
            if (temp == '\n' && !width) 
            {
                width = counter;
            }
        }
    }
    in.close();

    int height = vector_size(lab) / width;

    int start_x = -1, start_y = -1;
    for (int y = 0; y < height; y++) 
    {
        for (int x = 0; x < width; x++) 
        {
            if ((char)vector_get(lab, y * width + x) == 'X') 
            {
                start_x = x;
                start_y = y;
                break;
            }
        }
        if (start_x != -1) 
            break;
    }

    if (start_x != -1) 
    {
        Point result = find_clothest(lab, start_x, start_y, width, height);
        if (result.x != -1) 
        {
            std::cout << (char)vector_get(lab, result.y * width + result.x);
        } 
        else 
        {
            std::cout << "End point was not founded\n";
        }
    } 
    else 
    {
        std::cout << "Start point was not founded\n";
    }

    vector_delete(lab);
    return 0;
}
