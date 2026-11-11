#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <stdexcept>
#include <queue.h>
#include <vector.h>

using namespace std;

int main(int argc, char* argv[]){
    if (argc != 2)
    {
        cout << "usage: main <input_file>";
        return 1;
    }

    ifstream input(argv[1]);

    if (!input)
    {
        std::cout << "cannot open file";
        return 1;
    }

    Vector* maze = vector_create();

    string line;
    int width = -1;
    int height = 0;

    while (getline(input, line))
    {
        if (line.empty())
            continue;

        if (width == -1){
            width = static_cast<int>(line.size());
        }else if (static_cast<int>(line.size()) != width){
            cout << "maze must be rectangular";
            vector_delete(maze);
            return 1;
        }

        for (int col = 0; col < width; ++col)
        {
            size_t index = vector_size(maze);

            vector_resize(maze, index + 1);
            vector_set(maze, index, line[col]);
        }

        ++height;
    }

    int start = -1;
    int finish = -1;

    for (size_t i = 0; i < vector_size(maze); ++i)
    {
        if (vector_get(maze, i) == 'Q')
        {
            start = static_cast<int>(i);
        }

        if (vector_get(maze, i) == 'E')
        {
            finish = static_cast<int>(i);
        }
    }

    if (start == -1 || finish == -1)
    {
        cout << "start/finish not found";
        vector_delete(maze);
        return 1;
    }

    size_t cellCount = vector_size(maze);

    Vector* distance = vector_create();
    vector_resize(distance, cellCount);

    Vector* parent = vector_create();
    vector_resize(parent, cellCount);

    for (size_t i = 0; i < cellCount; ++i)
    {
        vector_set(distance, i, -1);
        vector_set(parent, i, -1);
    }

    vector_set(distance, start, 0);

    Queue* queue = queue_create();
    queue_insert(queue, start);

    int dr[8] = {
        1,  1,  1,
        0,  0,
        -1, -1, -1
    };

    int dc[8] = {
        -1,  0,  1,
        -1,  1,
        -1,  0,  1
    };

    while (!queue_empty(queue))
    {
        int current = queue_get(queue);
        queue_remove(queue);

        int row = current / width;
        int col = current % width;

        for (int direction = 0; direction < 8; ++direction)
        {
            int nextRow = row + dr[direction];
            int nextCol = col + dc[direction];

            while (
                nextRow >= 0 &&
                nextRow < height &&
                nextCol >= 0 &&
                nextCol < width
            )
            {
                int next = nextRow * width + nextCol;

                if (vector_get(maze, next) == '#')
                {
                    break;
                }

                if (vector_get(distance, next) == -1)
                {
                    vector_set(
                        distance,
                        next,
                        vector_get(distance, current) + 1
                    );

                    vector_set(parent, next, current);

                    queue_insert(queue, next);
                }

                nextRow += dr[direction];
                nextCol += dc[direction];
            }
        }
    }

    // вывод пути

    if (vector_get(distance, finish) == -1)
    {
        cout << "path not found\n";
    }
    else
    {
        Vector* path = vector_create();

        int current = finish;

        while (current != -1)
        {
            size_t index = vector_size(path);

            vector_resize(path, index + 1);
            vector_set(path, index, current);

            current = vector_get(parent, current);
        }

        int step = 0;

        for (int i = static_cast<int>(vector_size(path)) - 1; i >= 0; --i)
        {
            int position = vector_get(path, i);

            vector_set(maze, position, '0' + step);

            ++step;
        }

        vector_delete(path);

        for (int row = 0; row < height; ++row)
        {
            for (int col = 0; col < width; ++col)
            {
                int index = row * width + col;

                cout << static_cast<char>(
                    vector_get(maze, index)
                );
            }

            cout << '\n';
        }
    }
    queue_delete(queue);
    vector_delete(parent);
    vector_delete(distance);
    vector_delete(maze);
    return 0;
}