#include <iostream>
#include <fstream>
#include <string>
#include "vector.h"
#include "queue.h"

typedef Vector<std::string> VS;

struct Position {
    int row, col;
};

int bfs(VS& field, Position start) {
    const int dRow[] = {-1, 1, 0, 0};
    const int dCol[] = {0, 0, -1, 1};

    Queue<Position> queue;
    queue.insert(start);

    int reachableCells = 0;

    while (!queue.empty()) {
        Position current = queue.get();
        queue.remove();

        if (field.get(current.row)[current.col] == 'x') continue;

        std::string& row = field.get(current.row);
        row[current.col] = 'x';
        reachableCells++;

        for (int i = 0; i < 4; ++i) {
            size_t newRow = static_cast<size_t>(current.row + dRow[i]);
            size_t newCol = static_cast<size_t>(current.col + dCol[i]);

            if (newRow < field.size() &&
                newCol < field.get(0).size() &&
                (field.get(newRow)[newCol] == '.')) {
                Position next = {static_cast<int>(newRow), static_cast<int>(newCol)};
                queue.insert(next);
            }
        }
    }

    return reachableCells;
}

int main(int argc, char **argv) {
    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Failed to open input file: " << argv[1] << "\n";
        return 1;
    }

    std::ofstream output(argv[2]);
    if (!output.is_open()) {
        std::cerr << "Failed to open output file: " << argv[2] << "\n";
        return 1;
    }

    VS field;
    std::string line;
    while (std::getline(input, line)) {
        field.resize(field.size() + 1);
        field.set(field.size() - 1, line);
    }

    // Search start
    Position start{-1, -1};
    for (size_t i = 0; i < field.size(); ++i) {
        for (size_t j = 0; j < field.get(i).size(); ++j) {
            if (field.get(i)[j] == 'X') {
                start = {static_cast<int>(i), static_cast<int>(j)};
                field.get(i)[j] = '.'; // replace start
                break;
            }
        }
        if (start.row != -1) break;
    }

    if (start.row == -1) {
        throw std::runtime_error("Start position 'X' not found in the field.");
    }

    int reachableCells = bfs(field, start);

    output << reachableCells << std::endl;

    for(size_t i = 0; i < field.size(); i++) {
        output << field.get(i) << std::endl;
    }

    input.close();
    output.close();

    return 0;
}
