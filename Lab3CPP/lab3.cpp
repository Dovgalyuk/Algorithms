#include <iostream>
#include <fstream>
#include <vector>
#include "queue.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream fin(argv[1]);
    if (!fin) {
        std::cerr << "Error: Cannot open input file" << std::endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;

    std::vector<std::vector<int>> board(n, std::vector<int>(m, 0));
    Queue* q = queue_create();

    int x, y;
    while (fin >> x >> y) {
        x--; y--;
        if (x < 0 || x >= n || y < 0 || y >= m) {
            std::cerr << "Invalid coordinates: " << x+1 << " " << y+1 << std::endl;
            continue;
        }
        board[x][y] = 1;
        queue_insert(q, x * m + y);
    }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int maxIntensity = 1;

    // Обработка очереди
    while (!queue_empty(q)) {
        int pos = queue_get(q);
        queue_remove(q);

        int x = pos / m;
        int y = pos % m;
        int current = board[x][y];

        // Обрабатываем соседей
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            
            // Проверяем границы и что клетка еще не окрашена
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && board[nx][ny] == 0) {
                board[nx][ny] = current + 1;
                if (current + 1 > maxIntensity) {
                    maxIntensity = current + 1;
                }
                queue_insert(q, nx * m + ny);
            }
        }
    }

    queue_delete(q);

    // Выводим результат
    std::cout << maxIntensity << std::endl;
    return 0;
}