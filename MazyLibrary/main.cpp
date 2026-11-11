#include <fstream>
#include <iostream>
#include <string>

#include "vector.h"
#include "queue.h"

int main(int argc, char *argv[])
{
    std::ifstream file;
    std::istream *input = &std::cin;


    if (argc > 1) {
        file.open(argv[1]);
        if (!file) {
            std::cerr << "Cannot open input file\n";
            return 1;
        }
        input = &file;
    }

    Vector<std::string> maze;
    std::string line;
    while (std::getline(*input, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (line.empty())
            continue;

        maze.resize(maze.size() + 1);
        maze.set(maze.size() - 1, line);
    }

    if (maze.size() == 0) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    int height = static_cast<int>(maze.size());
    int width = static_cast<int>(maze.get(0).size());
    int start = -1, finish = -1;

    Vector<char> cells;
    cells.resize(height * width);

    for (int r = 0; r < height; r++) {
        std::string row = maze.get(r);
        if (static_cast<int>(row.size()) != width) {
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }

        for (int c = 0; c < width; c++) {
            cells.set(r * width + c, row[c]);
            if (row[c] == 'X')
                start = r * width + c;
            if (row[c] == 'Y')
                finish = r * width + c;
        }
    }

    if (start == -1 || finish == -1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

   
    Vector<int> previous;
    previous.resize(height * width);
    for (int i = 0; i < height * width; i++)
        previous.set(i, -1);

    Queue<int> q;
    q.insert(start);
    previous.set(start, start);

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    while (!q.empty()) {
        int current = q.get();
        q.remove();

        if (current == finish)
            break;

        int r = current / width;
        int c = current % width;
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= height || nc < 0 || nc >= width)
                continue;
            int next = nr * width + nc;
            if (cells.get(next) == '#')
                continue;
            if (previous.get(next) != -1)
                continue;

            previous.set(next, current);
            q.insert(next);
        }
    }

    if (previous.get(finish) == -1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }


    for (int cell = finish; cell != start; cell = previous.get(cell)) {
        if (cell == finish)
            continue;
        cells.set(cell, 'x');
    }

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++)
            std::cout << cells.get(r * width + c);
        std::cout << '\n';
    }
    return 0;
}
