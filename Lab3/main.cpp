#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "queue.h"

using namespace std;

int searchLayer(Queue& queue, vector<int>& parent, const vector<int>& other,
                const vector<string>& maze) {
    int rows = maze.size();
    int cols = maze[0].size();
    size_t layerSize = queue.size();
    int dr[] = {1, 0, -1, -1, -1, 0, 1, 1};
    int dc[] = {-1, -1, -1, 0, 1, 1, 0, 1};

    for (size_t i = 0; i < layerSize; i++) {
        int cell = queue.get();
        queue.remove();
        for (int d = 0; d < 8; d++) {
            int r = cell / cols + dr[d];
            int c = cell % cols + dc[d];
            while (r >= 0 && r < rows && c >= 0 && c < cols && maze[r][c] != '#') {
                int next = r * cols + c;
                if (parent[next] == -1) {
                    parent[next] = cell;
                    if (other[next] != -1)
                        return next;
                    queue.insert(next);
                }
                r += dr[d];
                c += dc[d];
            }
        }
    }
    return -1;
}

int main() {
    vector<string> maze;
    string row;
    while (cin >> row)
        maze.push_back(row);
    if (maze.empty())
        return 1;

    int cols = maze[0].size();
    int cells = maze.size() * cols;
    int start = -1;
    int finish = -1;
    for (int i = 0; i < cells; i++) {
        char symbol = maze[i / cols][i % cols];
        if (symbol == 'Q') start = i;
        if (symbol == 'E') finish = i;
    }
    if (start == -1 || finish == -1)
        return 1;

    vector<int> fromStart(cells, -1), fromFinish(cells, -1);
    Queue forward, backward;
    forward.insert(start);
    backward.insert(finish);
    fromStart[start] = start;
    fromFinish[finish] = finish;

    int meet = -1;
    while (meet == -1 && !forward.empty() && !backward.empty()) {
        meet = searchLayer(forward, fromStart, fromFinish, maze);
        if (meet == -1)
            meet = searchLayer(backward, fromFinish, fromStart, maze);
    }
    if (meet == -1) {
        cout << "Пути нет\n";
        return 0;
    }

    vector<int> path;
    for (int p = meet; p != start; p = fromStart[p])
        path.push_back(p);
    path.push_back(start);
    reverse(path.begin(), path.end());
    for (int p = meet; p != finish; p = fromFinish[p])
        path.push_back(fromFinish[p]);

    vector<string> labels(cells);
    for (int i = 0; i < static_cast<int>(path.size()); i++)
        labels[path[i]] = to_string(i);
    for (int i = 0; i < cells; i++) {
        if (i % cols != 0 && path.size() > 10) cout << ' ';
        if (labels[i].empty()) cout << maze[i / cols][i % cols];
        else cout << labels[i];
        if (i % cols == cols - 1) cout << '\n';
    }
}
