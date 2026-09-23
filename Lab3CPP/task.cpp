#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "vector.h"
#include "queue.h"

struct Coordinate
{
    int x;
    int y;
    int z;

    Coordinate() : x(-1), y(-1), z(-1)
    {
    }

    Coordinate(int get_x, int get_y, int get_z) : x(get_x), y(get_y), z(get_z)
    {
    }

    void set_pos(const int &get_x, const int &get_y, const int &get_z)
    {
        x = get_x;
        y = get_y;
        z = get_z;
    }
};

void BFS(const Vector<std::string> &map, const Coordinate &start_pos, const size_t &X, const size_t &Y, const size_t &Z)
{

    Queue<Coordinate> queue;
    queue.insert(start_pos);

    Vector<bool> visited;
    visited.resize(X * Y * Z);

    const size_t start_index = ((size_t)start_pos.z * Y + start_pos.y) * X + start_pos.x;
    visited.set(start_index, true);

    int delta_x[6] = {1, -1, 0, 0, 0, 0};
    int delta_y[6] = {0, 0, 1, -1, 0, 0};
    int delta_z[6] = {0, 0, 0, 0, 1, -1};

    while (!queue.empty())
    {
        Coordinate current = queue.get();
        queue.remove();

        const char number = map.get((size_t)current.z * Y + (size_t)current.y)[current.x];

        if (number >= '0' && number <= '9')
        {
            printf("%c", number);
            return;
        }

        for (int d = 0; d < 6; ++d)
        {
            const int new_x = current.x + delta_x[d];
            const int new_y = current.y + delta_y[d];
            const int new_z = current.z + delta_z[d];

            if (new_x < 0 || new_x >= X)
            {
                continue;
            }

            if (new_y < 0 || new_y >= Y)
            {
                continue;
            }

            if (new_z < 0 || new_z >= Z)
            {
                continue;
            }

            const size_t new_index = ((size_t)new_z * Y + new_y) * X + new_x;

            if (visited.get(new_index))
            {
                continue;
            }
            if (map.get((size_t)new_z * Y + (size_t)new_y)[new_x] == '#')
            {
                continue;
            }
            visited.set(new_index, true);
            queue.insert(Coordinate(new_x, new_y, new_z));
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    Vector<std::string> map;

    size_t X = 0;
    size_t Y = 0;
    size_t Z = 0;

    size_t y_count = 0;
    size_t y_index = 0;

    std::string line;

    Coordinate start_pos;

    std::ifstream input_file(argv[1]);

    if (input_file.is_open())
    {
        while (std::getline(input_file, line))
        {

            if (line.empty())
            {
                if (y_index > 0)
                {
                    Y = y_count;
                    y_count = 0;
                    y_index = 0;
                    Z++;
                }
                continue;
            }

            if (X == 0)
            {
                X = line.size();
            }

            size_t map_size = map.size();
            map.resize(map_size + 1);
            map.set(map_size, line);

            if (start_pos.x == -1 && start_pos.y == -1 && start_pos.z == -1)
            {
                for (size_t i = 0; i < line.size(); i++)
                {
                    if (line[i] == 'X')
                    {
                        start_pos.set_pos((int)i, (int)y_index, (int)Z);
                        break;
                    }
                }
            }
            y_count++;
            y_index++;
        }

        if (y_index > 0)
        {
            Y = y_count;
            Z++;
        }
    }

    input_file.close();

    if (start_pos.x != -1 && start_pos.y != -1 && start_pos.z != -1)
    {
         BFS(map, start_pos, X, Y, Z);
    }

    return 0;
}