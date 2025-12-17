#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "queue.h"

using namespace std;


bool is_valid(int r, int c, int h, int w, const vector<string>& map) {
    return r >= 0 && r < h && c >= 0 && c < w && map[r][c] != '#';
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << "Error opening file: " << argv[1] << endl;
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

    int h = (int)map.size();
    if (h == 0) return 0;
    int w = (int)map[0].size();

    int start_r = -1, start_c = -1;
    int end_r = -1, end_c = -1;

    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            if (map[r][c] == 'S') {
                start_r = r;
                start_c = c;
            } else if (map[r][c] == 'E') {
                end_r = r;
                end_c = c;
            }
        }
    }

    if (start_r == -1 || end_r == -1) {
        cout << "Start or End point not found." << endl;
        return 1;
    }

    Queue* q = queue_create();
    vector<int> parent(h * w, -1);

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

        int dr[6] = {0, 0, -1, -1, 1, 1};
        int dc[6];

        dc[0] = -1;
        dc[1] = 1;

        if (r % 2 == 0) {
            dc[2] = -1;
            dc[3] = 0;
            dc[4] = -1;
            dc[5] = 0;
        } else {
            dc[2] = 0;
            dc[3] = 1;
            dc[4] = 0;
            dc[5] = 1;
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
        vector<int> path;
        int curr = end_id;
        while (curr != start_id) {
            path.push_back(curr);
            curr = parent[curr];
        }
        path.push_back(start_id);
        reverse(path.begin(), path.end());

        cout << (int)path.size() - 1 << endl;

        cout << "Path: ";
        for (int i = 0; i < (int)path.size(); ++i) {
            int r = path[i] / w;
            int c = path[i] % w;
            cout << "(" << c << "," << r << ")";
            if (i < (int)path.size() - 1) {
                cout << " -> ";
            }
            if (map[r][c] != 'S' && map[r][c] != 'E') {
                map[r][c] = 'x';
            }
        }
        cout << endl;

        cout << "Maze with path:" << endl;

        cout << " ";
        for (int c = 0; c < w; ++c) cout << " / \\";
        cout << endl;

        for (int r = 0; r < h; ++r) {
            for (int s = 0; s < 2 * r + 1; ++s) cout << " ";
            
            cout << "|";
            for (int c = 0; c < w; ++c) {
                cout << " " << map[r][c] << " |";
            }
            cout << endl;

            for (int s = 0; s < 2 * r + 1; ++s) cout << " ";
            for (int c = 0; c < w; ++c) {
                cout << " \\ /";
            }
            cout << endl;
        }
    } else {
        cout << "-1" << endl;
    }

    return 0;
}