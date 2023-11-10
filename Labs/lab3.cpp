#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <climits>
#include "queue.h"

using namespace std;

vector<string> Read(int& sx, int& sy, Queue* queue) {
    vector<string> labyrinth;
    string strbuf;
    ifstream inFile("input.txt");

    if (!inFile.is_open()) {
        cout << "Error: Unable to open the input file." << endl;
        exit(EXIT_FAILURE);
    }

    int k = 0;
    while (getline(inFile, strbuf)) {
        labyrinth.push_back(strbuf);
        for (size_t i = 0; i < labyrinth[k].size(); i++) {
            if (labyrinth[k][i] == 'X') {
                sx = static_cast<int>(k);
                sy = static_cast<int>(i);
                queue_insert(queue, sx);
                queue_insert(queue, sy);
            }
        }
        k++;
    }

    inFile.close();
    return labyrinth;
}

void BFS(vector<string>& labyrinth, int sx, int sy, int& nearestNumber, Queue* queue) {
    const int rows = static_cast<int>(labyrinth.size());
    const int cols = static_cast<int>(labyrinth[0].size());

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    // Перемещение по соседним клеткам в ширину
    const int dx[] = {-1, 0, 1, 0};
    const int dy[] = {0, 1, 0, -1};

    queue_insert(queue, sx);
    queue_insert(queue, sy);
    visited[sx][sy] = true;

    while (!queue_empty(queue)) {
        int x = queue_get(queue);
		queue_remove(queue);
		int y = queue_get(queue);
		queue_remove(queue);

        // Проверка, содержит ли текущая клетка цифру
        if (isdigit(labyrinth[x][y])) {
            nearestNumber = labyrinth[x][y] - '0';
            return;
        }


        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[nx][ny] && labyrinth[nx][ny] != '#') {
                visited[nx][ny] = true;
                queue_insert(queue, nx);
                queue_insert(queue, ny);
            }
        }
    }
}

int main() {
    Queue* queue = queue_create();
    int sx = 0, sy = 0;
    int nearestNumber = -1;

    vector<string> labyrinth = Read(sx, sy, queue);
    BFS(labyrinth, sx, sy, nearestNumber, queue);

    if (nearestNumber != -1) {
        cout << nearestNumber << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }

    queue_delete(queue);

    return 0;
}
