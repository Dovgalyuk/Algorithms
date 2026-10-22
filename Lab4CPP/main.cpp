#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>
#include "graph.h"

struct Node {
    int idx; // Индекс в графе (row * cols + col)
    int f;   // Стоимость f = g + h

    bool operator<(const Node& other) const {
        return f < other.f;
    }
};

class PriorityQueue {
private:
    Vector<Node> heap;

    void siftUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap.get(i).f < heap.get(parent).f) {
                Node temp = heap.get(i);
                heap.set(i, heap.get(parent));
                heap.set(parent, temp);
                i = parent;
            }
            else {
                break;
            }
        }
    }

    void siftDown(int i) {
        int n = (int)heap.size();
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < n && heap.get(left).f < heap.get(smallest).f) smallest = left;
            if (right < n && heap.get(right).f < heap.get(smallest).f) smallest = right;

            if (smallest != i) {
                Node temp = heap.get(i);
                heap.set(i, heap.get(smallest));
                heap.set(smallest, temp);
                i = smallest;
            }
            else {
                break;
            }
        }
    }

public:
    void push(Node node) {
        heap.resize(heap.size() + 1);
        heap.set(heap.size() - 1, node);
        siftUp(heap.size() - 1);
    }

    Node pop() {
        Node top = heap.get(0);
        heap.set(0, heap.get(heap.size() - 1));
        heap.resize(heap.size() - 1);
        if (heap.size() > 0) {
            siftDown(0);
        }
        return top;
    }

    bool empty() const {
        return heap.size() == 0;
    }
};

void toCube(int r, int c, int& x, int& y, int& z) {
    x = c - (r - (r & 1)) / 2;
    z = r;
    y = -x - z;
}

int hexDistance(int r1, int c1, int r2, int c2) {
    int x1, y1, z1, x2, y2, z2;
    toCube(r1, c1, x1, y1, z1);
    toCube(r2, c2, x2, y2, z2);
    return (std::abs(x1 - x2) + std::abs(y1 - y2) + std::abs(z1 - z2)) / 2;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file> [output_file]\n";
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile.is_open()) {
        std::cerr << "Cannot open input file\n";
        return 1;
    }

    size_t rows, cols;
    if (!(infile >> rows >> cols)) return 1;

    Graph<int, int> graph(rows, cols);

    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            int cost;
            infile >> cost;
            graph.setVertexData(r, c, cost);
        }
    }

    int start_r, start_c, end_r, end_c;
    infile >> start_r >> start_c >> end_r >> end_c;
    infile.close();

    // A*
    PriorityQueue open_list;

    Vector<int> g_score;
    g_score.resize(rows * cols);
    for (size_t i = 0; i < g_score.size(); ++i) g_score.set(i, INT_MAX);

    Vector<int> parent;
    parent.resize(rows * cols);
    for (size_t i = 0; i < parent.size(); ++i) parent.set(i, -1);

    int start_idx = start_r * cols + start_c;
    int end_idx = end_r * cols + end_c;

    g_score.set(start_idx, 0);
    open_list.push({ start_idx, hexDistance(start_r, start_c, end_r, end_c) });

    bool found = false;

    while (!open_list.empty()) {
        Node current = open_list.pop();

        if (current.idx == end_idx) {
            found = true;
            break;
        }

        int cr = current.idx / cols;
        int cc = current.idx % cols;

        for (auto it = graph.begin(cr, cc); it != graph.end(cr, cc); ++it) {
            int neighborIdx = (int)*it;
            int nr = neighborIdx / cols;
            int nc = neighborIdx % cols;

            int move_cost = graph.getVertexData(nr, nc);
            int tentative_g = g_score.get(current.idx) + move_cost;

            if (tentative_g < g_score.get(neighborIdx)) {
                g_score.set(neighborIdx, tentative_g);
                parent.set(neighborIdx, current.idx);
                int f = tentative_g + hexDistance(nr, nc, end_r, end_c);
                open_list.push({ neighborIdx, f });
            }
        }
    }

    std::ostream* out = &std::cout;
    std::ofstream outfile;
    if (argc >= 3) {
        outfile.open(argv[2]);
        out = &outfile;
    }

    if (!found) {
        *out << "NO PATH\n";
        return 0;
    }

    // Восстанавливаем путь
    Vector<int> path;
    int curr = end_idx;
    while (curr != -1) {
        path.resize(path.size() + 1);
        path.set(path.size() - 1, curr);
        curr = parent.get(curr);
    }

    // Разворачиваем путь
    int path_len = path.size();
    for (int i = 0; i < path_len / 2; ++i) {
        int temp = path.get(i);
        path.set(i, path.get(path_len - 1 - i));
        path.set(path_len - 1 - i, temp);
    }

    // Подготовка поля
    Vector<int> board;
    board.resize(rows * cols);
    for (size_t i = 0; i < rows * cols; ++i) board.set(i, -1);

    for (int i = 0; i < path_len; ++i) {
        board.set(path.get(i), i);
    }

    // Вывод сетки
    *out << "=== Field ===\n";
    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            int idx = r * cols + c;
            int step = board.get(idx);

            if (step != -1) {
                *out << "{" << step << "}    ";
            }
            else {
                *out << graph.getVertexData(r, c) << "    ";
            }
        }
        *out << "\n";
    }
    *out << "\n";

    // Маршрут
    *out << "=== Route ===\n";
    for (int i = 0; i < path_len; ++i) {
        int idx = path.get(i);
        *out << "(" << idx / cols << "," << idx % cols << ")";
        if (i < path_len - 1) *out << " -> ";
    }
    *out << "\n\n";

    // Таблица шагов
    *out << "Step    Move                Cost    Total\n";
    int total_cost = 0;
    for (int i = 1; i < path_len; ++i) {
        int prev_idx = path.get(i - 1);
        int curr_idx = path.get(i);

        int r = curr_idx / cols;
        int c = curr_idx % cols;
        int move_cost = graph.getVertexData(r, c);
        total_cost += move_cost;

        *out << i << "       "
            << "(" << prev_idx / cols << "," << prev_idx % cols << ") -> "
            << "(" << r << "," << c << ")       "
            << move_cost << "       " << total_cost << "\n";
    }
    *out << "\n";

    // Итог
    *out << "Total Cost: " << g_score.get(end_idx) << "   Steps: " << (path_len - 1) << "\n";

    // Выводим в консоль для тестов
    std::cout << "Total Cost: " << g_score.get(end_idx) << "   Steps: " << (path_len - 1) << "\n";

    return 0;
}