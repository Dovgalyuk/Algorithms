#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>
#include "graph.h"

// Узел для кучи
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
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
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

        // Перебираем соседей с помощью нашего итератора
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

    std::ofstream outfile(argv[2]);
    if (!found) {
        outfile << "NO PATH\n";
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

    outfile << "Cost: " << g_score.get(end_idx) << "\n";
    outfile << "Path: ";
    for (int i = (int)path.size() - 1; i >= 0; --i) {
        int idx = path.get(i);
        outfile << "(" << idx / cols << "," << idx % cols << ")";
        if (i > 0) outfile << " ";
    }
    outfile << "\n";

    return 0;
}