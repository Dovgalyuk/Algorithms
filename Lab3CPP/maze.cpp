
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <climits>

#include "queue.h"

using namespace std;

typedef vector<string> Maze;
typedef vector<vector<int>> Matrix;

int expand(Queue *queue,
           const Maze &maze,
           Matrix &distance,
           const Matrix &other_distance,
           Matrix &exit_number,
           int width, int height, int level,
           bool exit_side, int &best_distance)
{
    const int dx[] = {0, 0, -1, 1};
    const int dy[] = {-1, 1, 0, 0};

    int result = -1;
    best_distance = INT_MAX;

    while (!queue_empty(queue))
    {
        int position = queue_get(queue);

        int x = position % width;
        int y = position / width;

        if (distance[y][x] != level)
            break;

        queue_remove(queue);

        for (int i = 0; i < 4; i++)
        {
            int next_x = x + dx[i];
            int next_y = y + dy[i];

            if (next_x < 0 || next_x >= width ||
                next_y < 0 || next_y >= height)
                continue;

            if (maze[next_y][next_x] == '#')
                continue;

            if (other_distance[next_y][next_x] != -1)
            {
                int total_distance =
                    distance[y][x] + 1 +
                    other_distance[next_y][next_x];

                if (total_distance < best_distance)
                {
                    best_distance = total_distance;

                    if (exit_side)
                        result = exit_number[y][x];
                    else
                        result = exit_number[next_y][next_x];
                }

                continue;
            }

            if (distance[next_y][next_x] != -1)
                continue;

            distance[next_y][next_x] = level + 1;

            if (exit_side)
                exit_number[next_y][next_x] = exit_number[y][x];
            queue_insert(queue, next_y * width + next_x);
        }
    }

    return result;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Input file isnt found" << endl;
        return 1;
    }

    ifstream input_file(argv[1]);

    if (!input_file.is_open())
    {
        cerr << "Cant open input file" << endl;
        return 1;
    }

    Maze maze;
    string line;

    while (getline(input_file, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (line.empty())
        {
            cerr << "Empty line in maze" << endl;
            return 1;
        }

        maze.push_back(line);
    }

    input_file.close();

    if (maze.empty())
    {
        cerr << "Maze is empty" << endl;
        return 1;
    }

    int height = static_cast<int>(maze.size());
    int width = static_cast<int>(maze[0].size());

    for (const string &row : maze)
    {
        if (static_cast<int>(row.size()) != width)
        {
            cerr << "Maze must be rectangular" << endl;
            return 1;
        }

        for (char cell : row)
        {
            if (cell != '#' && cell != '.' && cell != 'X' &&
                !(cell >= '0' && cell <= '9'))
            {
                cerr << "Invalid character in maze" << endl;
                return 1;
            }
        }
    }

    int start_x = -1;
    int start_y = -1;
    int start_count = 0;

    vector<pair<int, int>> exits;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (maze[y][x] == 'X')
            {
                start_x = x;
                start_y = y;
                start_count++;
            }

            if (maze[y][x] >= '0' && maze[y][x] <= '9')
            {
                exits.push_back({x, y});
            }
        }
    }
    if (start_count != 1)
    {
        cerr << "Maze must contain exactly one start" << endl;
        return 1;
    }

    if (exits.empty())
    {
        cerr << "Exits not found" << endl;
        return 1;
    }

    Matrix start_distance(
        height, vector<int>(width, -1));

    Matrix exit_distance(
        height, vector<int>(width, -1));

    Matrix exit_number(
        height, vector<int>(width, -1));

    Queue *start_queue = queue_create();
    Queue *exit_queue = queue_create();

    start_distance[start_y][start_x] = 0;

    queue_insert(start_queue, start_y * width + start_x);

    for (const auto &exit : exits)
    {
        int x = exit.first;
        int y = exit.second;

        exit_distance[y][x] = 0;
        exit_number[y][x] = maze[y][x] - '0';

        queue_insert(exit_queue, y * width + x);
    }

    int start_level = 0;
    int exit_level = 0;

    int result = -1;

    while (!queue_empty(start_queue) && !queue_empty(exit_queue))
    {
        int start_best_distance;
        int exit_best_distance;

        int start_result = expand(
            start_queue, maze,
            start_distance, exit_distance, exit_number,
            width, height, start_level, false,
            start_best_distance);

        int exit_result = expand(
            exit_queue, maze,
            exit_distance, start_distance, exit_number,
            width, height, exit_level, true,
            exit_best_distance);

        if (start_result != -1 || exit_result != -1)
        {
            if (start_best_distance <= exit_best_distance)
                result = start_result;
            else
                result = exit_result;

            break;
        }

        start_level++;
        exit_level++;
    }

    if (result != -1)
        cout << result << endl;
    else
        cout << -1 << endl;

    queue_delete(start_queue);
    queue_delete(exit_queue);

    return 0;
}
