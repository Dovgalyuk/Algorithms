#include "helper.h"
#include <string>

constexpr int N = 8;

bool reader(std::istream& input, Vector* arr, int* start, int* end) {
    *start = -1;
    *end = -1;

    std::string line;

    for (int i = 0; i < N; i++) {
        if (!std::getline(input, line) || static_cast<int>(line.size()) != N) return false;

        for (int j = 0; j < N; j++) {
            char cell = line[j];

            if (cell != 'K' && cell != 'E' && cell != '.' && cell != '#') return false;

            int pos = i * N + j;
            vector_set(arr, pos, cell);

            if (cell == 'K') {
                if (*start != -1) return false;
                *start = pos;
            }

            if (cell == 'E') {
                if (*end != -1) return false;
                *end = pos;
            }
        }
    }

    while (std::getline(input, line)) {
        if (!line.empty()) return false;
    }

    return (*start != -1 && *end != -1);
}

void writer(std::ostream& output, Vector* arr) {
    for (int i = 0; i < N; i++) {

        for (int j = 0; j < N; j++) {
            int cell = vector_get(arr, i * N + j);

            if (cell <= 0 ) output << -cell;
            else output << static_cast<char>(cell);
        }
        output << '\n';
    }
}
