#include <bits/stdc++.h>
#include <fstream>
#include "vector.h"
#include "queue.h"

struct Point {
    int x, y;

    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    Point(const Point& other) : x(other.x), y(other.y) {}

    Point operator+(const Point& other) const {
        return {x + other.x, y + other.y};
    }

    Point& operator=(const Point& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

typedef Vector<Point> VP;
typedef Vector<char> Vc;
typedef Vector<int> Vi;

const Point dPoints[] = {
    {2, 1},
    {2, -1},
    {-2, 1},
    {-2, -1},
    {1, 2},
    {1, -2},
    {-1, 2},
    {-1, -2}
};

bool isValid(const Point& p, const Vc& board) {
    if(p.x >= 0 
        && p.x < 8
        && p.y >= 0
        && p.y < 8) {
        
        return board.get(p.x * 8 + p.y) != '#';
    }
    return false;
}

Vc init_board(std::ifstream& input, Point& start) {
    Vc board(64);

    for (size_t i = 0; i < 8; ++i) {
        std::string str; input >> str;
        for(size_t j = 0; j < 8; ++j) {
            board.set(i * 8 + j, str[j]);
            if(str[j] == 'K') {
                start.x = i; start.y = j;
            }
        }
    }

    return board;
}



void bfs(Vc& board, Point start, std::ofstream& output) {
    Vi dist(64);
    VP prev(64); // for prev point
    
    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 8; j++) {
            dist.set(i * 8 + j, -1);
            prev.set(i * 8 + j, {-1, -1});
        }
    }

    dist.set(start.x * 8 + start.y, 0);  
    prev.set(start.x * 8 + start.y, start);

    Queue<Point> q;
    q.insert(start);

    Point end;
    bool found = false;

    while (!q.empty() && !found) {
        Point curr = q.get();
        q.remove();

        for (size_t i = 0; i < 8; i++) {
            Point np(dPoints[i] + curr);
            if (isValid(np, board) && dist.get(np.x * 8 + np.y) == -1) {
                dist.set(np.x * 8 + np.y, dist.get(curr.x * 8 + curr.y) + 1);
                prev.set(np.x * 8 + np.y, curr);
                q.insert(np);
                if (board.get(np.x * 8 + np.y) == 'E') {
                    found = true;
                    end = np;
                    break;
                }
            }
            
        }
    }

    if (found) {
        Point curr = end;
        while (!(curr == start)) {
            board.set(curr.x * 8 + curr.y, '*'); 
            curr = prev.get(curr.x * 8 + curr.y); // marking the path we have taken
        }
        board.set(curr.x * 8 + curr.y, '*'); // for start
    }

    // Output
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board.get(i * 8 + j) == '#') {
                output << board.get(i * 8 + j);
            } else if (board.get(i * 8 + j) == '*') {
                output << dist.get(i * 8 + j);
            } else {
                output << ".";
            }
        }
        output << '\n';
    }
    output << '\n';
}


void solve(std::ifstream& input, std::ofstream& output) {
    Point start(0, 0);
    Vc board(init_board(input, start));

    bfs(board, start, output);
}


int main(int argc, char **argv) {
    
    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Failed to open input file: " << argv[1] << "\n";
        return 1;
    }

    std::ofstream output(argv[2]);
    if (!output.is_open()) {
        std::cerr << "Failed to open output file: " << argv[2] << "\n";
        return 1;
    }

    size_t t;
    input >> t;

    while(t--) {
        solve(input, output);
    }

    return 0;
}