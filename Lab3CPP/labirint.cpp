#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>

#include "queue.h"
// убрал hpp. по привычке его создал тогда, такто да, бесполезный
using namespace std;

vector<vector<vector<char>>> graph;

int dx[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, 1, -1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};
// убрал код энкод, стал все делать напрямую.
using Distance = vector<vector<vector<int>>>;

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
                for (const string& row : layer)
                    graph.back().push_back(vector<char>(row.begin(), row.end()));
                layer.clear();
            }
        } else {
            layer.push_back(line);
        }
    }

    if (!layer.empty()) {
        graph.push_back({});
        for (const string& row : layer)
            graph.back().push_back(vector<char>(row.begin(), row.end()));
    }

    if (graph.empty()) throw runtime_error("Empty labyrinth");
}

Distance create_distance() {
    Distance distance;
    for (const auto& layer : graph) {
        distance.push_back({});
        for (const auto& row : layer)
            distance.back().push_back(vector<int>(row.size(), -1));
    }
    return distance;
}

Position find_start() {
    for (size_t z = 0; z < graph.size(); z++)
        for (size_t y = 0; y < graph[z].size(); y++)
            for (size_t x = 0; x < graph[z][y].size(); x++)
                if (graph[z][y][x] == 'X') return {x, y, z};

    throw runtime_error("Start not found");
}

bool can_move(int x, int y, int z) {
    if (z < 0 || z >= static_cast<int>(graph.size())) return false;
    if (y < 0 || y >= static_cast<int>(graph[z].size())) return false;
    if (x < 0 || x >= static_cast<int>(graph[z][y].size())) return false;
    return graph[z][y][x] != '#';
}

void add_exits(Queue* queue, Distance& distance) {
    for (size_t z = 0; z < graph.size(); z++)
        for (size_t y = 0; y < graph[z].size(); y++)
            for (size_t x = 0; x < graph[z][y].size(); x++)
                if (graph[z][y][x] >= '0' && graph[z][y][x] <= '9') {
                    Position pos = {x, y, z};
                    queue_insert(queue, pos);
                    distance[z][y][x] = 0;
                }
}

bool expand_layer(Queue* queue, Distance& distance, const Distance& otherDistance, int depth, Position& meeting) {
    bool found = false;
    int bestDistance = -1;

    while (!queue_empty(queue)) {
        Position current = queue_get(queue);
        if (distance[current.z][current.y][current.x] != depth) break;
        queue_remove(queue);

        for (int d = 0; d < 6; d++) {
            int nx = static_cast<int>(current.x) + dx[d];
            int ny = static_cast<int>(current.y) + dy[d];
            int nz = static_cast<int>(current.z) + dz[d];

            if (!can_move(nx, ny, nz)) continue;

            size_t x = nx, y = ny, z = nz;
            if (distance[z][y][x] != -1) continue;

            distance[z][y][x] = depth + 1;

            int other = otherDistance[z][y][x];
            if (other != -1) {
                int pathLength = depth + 1 + other;
                if (bestDistance == -1 || pathLength < bestDistance) {
                    bestDistance = pathLength;
                    meeting = {x, y, z};
                    found = true;
                }
            }

            queue_insert(queue, {x, y, z});
        }
    }

    return found;
}

void print_exit(Position meeting, const Distance& distanceExit) {
    Position current = meeting;

    while (distanceExit[current.z][current.y][current.x] > 0) {
        bool found = false;

        for (int d = 0; d < 6; d++) {
            int nx = static_cast<int>(current.x) + dx[d];
            int ny = static_cast<int>(current.y) + dy[d];
            int nz = static_cast<int>(current.z) + dz[d];

            if (!can_move(nx, ny, nz)) continue;

            if (distanceExit[nz][ny][nx] == distanceExit[current.z][current.y][current.x] - 1) {
                current = {static_cast<size_t>(nx), static_cast<size_t>(ny), static_cast<size_t>(nz)};
                found = true;
                break;
            }
        }

        if (!found) throw runtime_error("Path not found");
    }

    cout << graph[current.z][current.y][current.x] << endl;
}

void solve_labirint(const string& filename) {
    read_labirint(filename);

    Position start = find_start();

    Queue* queueStart = queue_create();
    Queue* queueExit = queue_create();

    Distance distanceStart = create_distance();
    Distance distanceExit = create_distance();

    queue_insert(queueStart, start);
    distanceStart[start.z][start.y][start.x] = 0;

    add_exits(queueExit, distanceExit);

    Position meeting = {0, 0, 0};
    int depthStart = 0, depthExit = 0;
    bool found = false;

    while (!queue_empty(queueStart) && !queue_empty(queueExit) && !found) {
        found = expand_layer(queueStart, distanceStart, distanceExit, depthStart++, meeting);
        if (found) break;

        found = expand_layer(queueExit, distanceExit, distanceStart, depthExit++, meeting);
    }

    if (found) print_exit(meeting, distanceExit);
    else cout << "No" << endl;

    queue_delete(queueStart);
    queue_delete(queueExit);
}

int main(int argc, char* argv[]) {
    if (argc != 2) return 1;
    try {
        solve_labirint(argv[1]);
    } catch (const exception& error) {
        cerr << error.what() << endl;
        return 1;
    }
    return 0;
}