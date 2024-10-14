#include <iostream>
#include <string>
#include <fstream>
#include "queue.h"
#include "vector.h"

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

Point find_clothest(const Vector* lab, Point start, int width, int height) {
    Queue* queue = queue_create();
    bool* visited = new bool[width * height]();
    Point dir[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

    queue_insert(queue, start.y * width + start.x);
    visited[start.y * width + start.x] = true;

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

void input(std::ifstream& in, int* width, int* height, Vector* vector)
{
    char temp;
    int counter = 0;
    bool first_line = true;

    while (in.get(temp))
    {
        if (temp != '\n')
        {
            vector_push(vector, temp);
            if (first_line)
                counter++;
        }
        if (temp == '\n')
        {
            if (first_line)
            {
                *width = counter;
                first_line = false;
            }
            counter = 0;
        }
    }

    *height = vector_size(vector) / *width;

    in.close();
}

void output(Point start, int width, int height, Vector *vector)
{
    if (start.x != -1)
    {
        Point result = find_clothest(vector, start, width, height);
        if (result.x != -1)
        {
            std::cout << (char)vector_get(vector, result.y * width + result.x);
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
}

Point find_start(int width, int height, Vector* vector)
{
    int start_x = -1, start_y = -1;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if ((char)vector_get(vector, y * width + x) == 'X')
            {
                start_x = x;
                start_y = y;
                break;
            }
        }
        if (start_x != -1)
            break;
    }

    return { start_x, start_y };
}

int main(int argc, char** argv) 
{
    std::string filepath = argv[1];
    std::ifstream in(filepath);

    if (!in)
    {
        std::cout << "File could not be opened\n";
        return 1;
    }

    Vector* vector = vector_create();
    int width = 0, height = 0;
    input(in, &width, &height, vector);

    Point start = find_start(width, height, vector);

    output(start, width, height, vector);
    vector_delete(vector);
    return 0;
}
