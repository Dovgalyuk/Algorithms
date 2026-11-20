#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>

#include "vector.h"
#include "queue.h"
#include "labirint.hpp"

using namespace std;

struct Position { int x, y, z; };

vector<vector<vector<char>>> graph;

int dx[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, 1, -1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};

int encode(int x, int y, int z) {
    int index = x;
    for (int i = 0; i < z; i++) for (const auto& row : graph[i]) index += row.size();
    for (int i = 0; i < y; i++) index += graph[z][i].size();
    return index;
}

Position decode(int index) {
    for (int z = 0; z < (int)graph.size(); z++) {
        for (int y = 0; y < (int)graph[z].size(); y++) {
            int size = graph[z][y].size();
            if (index < size) return {index, y, z};
            index -= size;
        }
    }
    throw runtime_error("Invalid index");
}

void read_labirint(const string& filename) {
    graph.clear();
    ifstream file(filename);
    if (!file.is_open()) throw runtime_error("Cannot open file");

    string line;
    vector<string> layer;

    while (getline(file, line)) {
        if (line.empty()) {
            if (!layer.empty()) {
                graph.push_back({});
                for (const string& row : layer) graph.back().push_back(vector<char>(row.begin(), row.end()));
                layer.clear();
            }
        } else layer.push_back(line);
    }

    if (!layer.empty()) {
        graph.push_back({});
        for (const string& row : layer) graph.back().push_back(vector<char>(row.begin(), row.end()));
    }

    if (graph.empty()) throw runtime_error("Empty labyrinth");
}

int count_cells() {
    int total = 0;
    for (const auto& layer : graph) for (const auto& row : layer) total += row.size();
    return total;
}

Position find_start() {
    for (int z = 0; z < (int)graph.size(); z++)
        for (int y = 0; y < (int)graph[z].size(); y++)
            for (int x = 0; x < (int)graph[z][y].size(); x++)
                if (graph[z][y][x] == 'X') return {x, y, z};

    throw runtime_error("Start not found");
}

bool can_move(int x, int y, int z) {
    if (z < 0 || z >= (int)graph.size()) return false;
    if (y < 0 || y >= (int)graph[z].size()) return false;
    if (x < 0 || x >= (int)graph[z][y].size()) return false;
    return graph[z][y][x] != '#';
}

void add_exits(Queue* queue, Vector* distance) {
    for (int z = 0; z < (int)graph.size(); z++)
        for (int y = 0; y < (int)graph[z].size(); y++)
            for (int x = 0; x < (int)graph[z][y].size(); x++)
                if (graph[z][y][x] >= '0' && graph[z][y][x] <= '9') {
                    int index = encode(x, y, z);
                    queue_insert(queue, index);
                    vector_set(distance, index, 0);
                }
}

int expand_layer(Queue* queue, Vector* distance, Vector* parent, Vector* otherDistance, int depth) {
    int meeting = -1;
    int bestDistance = -1;

    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        if (vector_get(distance, current) != depth) break;
        queue_remove(queue);

        Position pos = decode(current);

        for (int d = 0; d < 6; d++) {
            int nx = pos.x + dx[d], ny = pos.y + dy[d], nz = pos.z + dz[d];
            if (!can_move(nx, ny, nz)) continue;

            int next = encode(nx, ny, nz);
            if (vector_get(distance, next) != -1) continue;

            vector_set(distance, next, depth + 1);
            if (parent != nullptr) vector_set(parent, next, current);

            int other = vector_get(otherDistance, next);
            if (other != -1) {
                int pathLength = depth + 1 + other;
                if (bestDistance == -1 || pathLength < bestDistance) {
                    bestDistance = pathLength;
                    meeting = next;
                }
            }

            queue_insert(queue, next);
        }
    }

    return meeting;
}

void print_exit(int meeting, Vector* parentExit) {
    int current = meeting;
    while (vector_get(parentExit, current) != -1) current = vector_get(parentExit, current);
    Position pos = decode(current);
    cout << graph[pos.z][pos.y][pos.x] << endl;
}

void solve_labirint(const string& filename) {
    read_labirint(filename);
    Position start = find_start();
    int total = count_cells();

    Queue* queueStart = queue_create();
    Queue* queueExit = queue_create();

    Vector* distanceStart = vector_create();
    Vector* distanceExit = vector_create();
    Vector* parentExit = vector_create();

    vector_resize(distanceStart, total);
    vector_resize(distanceExit, total);
    vector_resize(parentExit, total);

    for (int i = 0; i < total; i++) {
        vector_set(distanceStart, i, -1);
        vector_set(distanceExit, i, -1);
        vector_set(parentExit, i, -1);
    }

    int startIndex = encode(start.x, start.y, start.z);
    queue_insert(queueStart, startIndex);
    vector_set(distanceStart, startIndex, 0);

    add_exits(queueExit, distanceExit);

    int meeting = -1, depthStart = 0, depthExit = 0;

    while (!queue_empty(queueStart) && !queue_empty(queueExit) && meeting == -1) {
        meeting = expand_layer(queueStart, distanceStart, nullptr, distanceExit, depthStart++);
        if (meeting != -1) break;
        meeting = expand_layer(queueExit, distanceExit, parentExit, distanceStart, depthExit++);
    }

    if (meeting == -1) cout << "No" << endl;
    else print_exit(meeting, parentExit);

    queue_delete(queueStart);
    queue_delete(queueExit);
    vector_delete(distanceStart);
    vector_delete(distanceExit);
    vector_delete(parentExit);
}

int main(int argc, char* argv[]) {
    if (argc != 2) return 1;
    solve_labirint(argv[1]);
    return 0;
}