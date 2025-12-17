#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "queue.h"

using namespace std;
//проверкa выхода за границы
bool is_valid(int r, int c, int h, int w, const vector<string>& map) {
    return r >= 0 && r < h && c >= 0 && c < w && map[r][c] != '#';
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    vector<string> map;
    string line;
    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        map.push_back(line);
    }
    file.close();

    if (map.empty()) return 0;

    int h = map.size();
    int w = map[0].size();
    int start_r = -1, start_c = -1;
    int end_r = -1, end_c = -1;

    // Поиск  S и E
    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            if (map[r][c] == 'S') {
                start_r = r;
                start_c = c;
            }
            else if (map[r][c] == 'E') {
                end_r = r;
                end_c = c;
            }
        }
    }

    if (start_r == -1 || end_r == -1) {
        cerr << "Start or End point not found." << endl;
        return 1;
    }

    // BFS
    Queue* q = queue_create();

    // Массив хранения предков
    // -1 - > клетка не посещена
    vector<int> parent(h * w, -1);

    // Преобразуем 2D координаты в 1D индекс
    int start_id = start_r * w + start_c;
    int end_id = end_r * w + end_c;

    queue_insert(q, start_id);
    parent[start_id] = start_id; 

    bool found = false;

    while (!queue_empty(q)) {
        int curr_id = queue_get(q);
        queue_remove(q);

        if (curr_id == end_id) {
            found = true;
            break;
        }

        int r = curr_id / w;
        int c = curr_id % w;

        // переделана полностью функция get_neighbors
        int dr[6] = { 0, 0, -1, -1, 1, 1 };
        int dc[6];

        dc[0] = -1; // Left
        dc[1] = 1;  

        if (r % 2 == 0) {
            // Чет
            dc[2] = -1; // Top-Left
            dc[3] = 0;  // Top-Right
            dc[4] = -1; // Bottom-Left
            dc[5] = 0;  // Bottom-Right
        }
        else {
            // Нечеn
            dc[2] = 0;  // Top-Left
            dc[3] = 1;  // Top-Right
            dc[4] = 0;  // Bottom-Left
            dc[5] = 1;  // Bottom-Right
        }

        for (int i = 0; i < 6; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (is_valid(nr, nc, h, w, map)) {
                int next_id = nr * w + nc;
                if (parent[next_id] == -1) {
                    parent[next_id] = curr_id;
                    queue_insert(q, next_id);
                }
            }
        }
    }

    queue_delete(q);

    if (found) {
        // Восстановление пути
        int curr = parent[end_id]; 
        while (curr != start_id) {
            int r = curr / w;
            int c = curr % w;
            if (map[r][c] != 'S' && map[r][c] != 'E') {
                map[r][c] = 'x';
            }
            curr = parent[curr];
        }

        for (const auto& row_str : map) {
            cout << row_str << endl;
        }
    }
    else {
        cout << "-1" << endl;
    }

    return 0;
}
