#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "queue.h"

using namespace std;

struct Cell {
    char type;
    int row, column;
};

int main(int argc, char* argv[]) {
    ifstream file;
    if (argc > 2) return 1;
    if (argc == 2) {
        file.open(argv[1]);
        if (!file) {
            cerr << "Cannot open input file\n";
            return 1;
        }
    }
    istream& input = argc == 2 ? file : cin;

    vector<string> lines;
    string line;
    while (getline(input, line)) {
        const size_t end = line.find_last_not_of(" \t\r");
        line.erase(end == string::npos ? 0 : end + 1);
        const size_t start = line.find_first_not_of(" \t");
        if (start != string::npos) line.erase(0, start);
        lines.push_back(line);
    }
    while (!lines.empty() && lines.back().empty()) lines.pop_back();

    vector<Cell> cells;
    vector<vector<int>> ids(lines.size());
    int start = -1, finish = -1, start_count = 0, finish_count = 0;
    int max_width = 0;
    bool valid = !lines.empty() && lines.size() <= static_cast<size_t>(numeric_limits<int>::max());
    for (size_t r = 0; valid && r < lines.size(); ++r) {
        if (lines[r].empty() || lines[r].size() > static_cast<size_t>(numeric_limits<int>::max() / 2)) {
            valid = false;
            break;
        }
        max_width = max(max_width, static_cast<int>(lines[r].size()));
        for (size_t c = 0; c < lines[r].size(); ++c) {
            const char type = lines[r][c];
            if ((type != '.' && type != '#' && type != 'S' && type != 'E') ||
                cells.size() >= static_cast<size_t>(numeric_limits<int>::max())) {
                valid = false;
                break;
            }
            const int id = static_cast<int>(cells.size());
            if (type == 'S') { start = id; ++start_count; }
            if (type == 'E') { finish = id; ++finish_count; }
            ids[r].push_back(id);
            cells.push_back({type, static_cast<int>(r), static_cast<int>(c)});
        }
    }
    if (!valid || start_count != 1 || finish_count != 1) {
        cout << "No path\n";
        return 0;
    }

    vector<int> offset(lines.size());
    for (size_t r = 0; r < lines.size(); ++r) {
        offset[r] = max_width - static_cast<int>(lines[r].size());
        if (r > 0 && (offset[r] - offset[r - 1]) % 2 == 0) ++offset[r];
    }

    vector<vector<int>> adjacent(cells.size());
    for (size_t i = 0; i < cells.size(); ++i) {
        const int r = cells[i].row, c = cells[i].column;
        if (cells[i].type == '#') continue;
        auto add = [&](int nr, int nc) {
            if (nr >= 0 && nr < static_cast<int>(ids.size()) &&
                nc >= 0 && nc < static_cast<int>(ids[nr].size())) {
                const int next = ids[nr][nc];
                if (cells[next].type != '#') adjacent[i].push_back(next);
            }
        };
        add(r, c - 1);
        add(r, c + 1);
        for (int nr : {r - 1, r + 1}) {
            if (nr < 0 || nr >= static_cast<int>(ids.size())) continue;
            const int left = (2 * c + offset[r] - offset[nr] - 1) / 2;
            add(nr, left);
            add(nr, left + 1);
        }
    }

    Queue forward, backward;
    vector<int> distance_f(cells.size(), -1), distance_b(cells.size(), -1);
    vector<int> previous_f(cells.size(), -1), previous_b(cells.size(), -1);
    forward.insert(start);
    backward.insert(finish);
    distance_f[start] = distance_b[finish] = 0;
    int meeting = -1;
    long long best_distance = numeric_limits<long long>::max();

    auto expand_layer = [&](Queue& queue, vector<int>& distance,
                            const vector<int>& other, vector<int>& previous) {
        const int level = distance[queue.get()];
        auto consider = [&](int current) {
            const long long total_distance = static_cast<long long>(distance[current]) + other[current];
            if (other[current] != -1 && total_distance < best_distance) {
                best_distance = total_distance;
                meeting = current;
            }
        };
        while (!queue.empty() && distance[queue.get()] == level) {
            const int current = queue.get();
            queue.remove();
            consider(current);
            for (int next : adjacent[current]) {
                if (distance[next] != -1) continue;
                distance[next] = distance[current] + 1;
                previous[next] = current;
                queue.insert(next);
                consider(next);
            }
        }
    };

    while (!forward.empty() && !backward.empty() && meeting == -1) {
        expand_layer(forward, distance_f, distance_b, previous_f);
        expand_layer(backward, distance_b, distance_f, previous_b);
    }
    if (meeting == -1) {
        cout << "No path\n";
        return 0;
    }
    for (int current = meeting; current != start; current = previous_f[current])
        if (current != finish) cells[current].type = 'x';
    for (int current = meeting; current != finish; current = previous_b[current])
        if (current != start) cells[current].type = 'x';

    auto border = [&](size_t row, bool top) {
        cout << string(2 * static_cast<size_t>(offset[row]) + 2, ' ');
        for (size_t c = 0; c < lines[row].size(); ++c) cout << (top ? " / \\" : " \\ /");
        cout << '\n';
    };
    border(0, true);
    for (size_t r = 0; r < lines.size(); ++r) {
        cout << string(2 * static_cast<size_t>(offset[r]) + 2, ' ');
        for (int id : ids[r]) cout << "| " << cells[id].type << ' ';
        cout << "|\n";
        if (r + 1 < lines.size() && offset[r + 1] < offset[r]) border(r + 1, true);
        else border(r, false);
    }
    return 0;
}
