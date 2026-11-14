
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "queue.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "Input file not specified" << endl;
        return 1;
    }

    ifstream file(argv[1]);

    if (!file.is_open())
    {
        cerr << "Cannot open input file" << endl;
        return 1;
    }

    vector<vector<string>> maze;
    vector<string> layer;
    string line;

    while (getline(file, line))
    {
        if (line.empty())
        {
            if (!layer.empty())
            {
                maze.push_back(layer);
                layer.clear();
            }
        }
        else
        {
            layer.push_back(line);
        }
    }

    if (!layer.empty())
    {
        maze.push_back(layer);
    }

    int layers = static_cast<int>(maze.size());
    int rows = static_cast<int>(maze[0].size());
    int cols = static_cast<int>(maze[0][0].size());

    int start = -1;

    for (int z = 0; z < layers; z++)
    {
        for (int y = 0; y < rows; y++)
        {
            for (int x = 0; x < cols; x++)
            {
                if (maze[z][y][x] == 'X')
                {
                    start = z * rows * cols + y * cols + x;
                    break;
                }
            }

            if (start != -1) break;
        }

        if (start != -1) break;
    }

    if (start == -1)
    {
        cerr << "Starting point not found" << endl;
        return 1;
    }

    vector<bool> visited(layers * rows * cols, false);

    Queue q;
    q.insert(start);
    visited[start] = true;

    const int dz[] = { 0, 0, 0, 0, -1, 1 };
    const int dy[] = { -1, 1, 0, 0, 0, 0 };
    const int dx[] = { 0, 0, -1, 1, 0, 0 };

    while (!q.empty())
    {
        int current = q.get();
        q.remove();

        int z = current / (rows * cols);
        int y = (current / cols) % rows;
        int x = current % cols;

        char cell = maze[z][y][x];

        if (cell >= '0' && cell <= '9')
        {
            cout << cell << endl;
            return 0;
        }

        for (int i = 0; i < 6; i++)
        {
            int nz = z + dz[i];
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (nz < 0 || nz >= layers ||
                ny < 0 || ny >= rows ||
                nx < 0 || nx >= cols)
            {
                continue;
            }

            if (maze[nz][ny][nx] == '#')
            {
                continue;
            }

            int next = nz * rows * cols + ny * cols + nx;

            if (!visited[next])
            {
                visited[next] = true;
                q.insert(next);
            }
        }
    }

    cout << "No exit found" << endl;

    return 0;
}
