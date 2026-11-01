#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "vector.h"
#include "queue.h"

Vector<std::string> maze;
int len(int row) {
    return static_cast<int>(maze.get(row).size());
}

void printLine(std::ostream &out,int indent, const char *pattern, int count) {
    out <<std::string(indent, ' ');
    for (int i=0; i<count;i++) out <<(i ? " " : "") << pattern;
    out << "\n";
}

int main (int argc, char **argv) {
    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);

    std::string text;
    while (std::getline(input, text)) {
        if (text.empty()) continue;
        maze.resize(maze.size() + 1);
        maze.set(maze.size() - 1, text);
    }
    int height= maze.size(), width=0;
    for (int i=0; i< height;i++) width = std::max(width, len(i));

    int start =-1, finish =-1;
    for (int r=0; r< height; r++) {
        for (int c=0; c<len(r); c++) {
            if (maze.get(r)[c] == 'S') start = r*width + c;
            if (maze.get(r)[c] == 'E') finish = r*width +c;
        }
    }
    if (start<0 || finish<0) return 1;

    Vector<int> prev;
    prev.resize(height*width);
    for (int i =0; i < height*width; i++) prev.set(i, -2);
    prev.set(start,-1);

    Queue<int> q;
    q.insert(start);
    while (!q.empty() && prev.get(finish) ==-2) {
        int curr =q.get();
        q.remove();
        int row = curr / width;
        int col= curr % width;
        int shift = (row %2 ==0) ? 0 : -1;
        int nbRow[6] = {row, row, row - 1, row -1, row +1, row +1};
        int nbCol[6] = {col -1, col +1, col +shift, col+ shift +1, col + shift, col + shift + 1};
        for ( int i=0; i<6; i++) {
            if (nbRow[i] < 0 || nbRow[i] >=height) continue;
            if (nbCol[i] < 0 || nbCol[i] >= len(nbRow[i])) continue;
            int nbId = nbRow[i]*width + nbCol[i];
            if (prev.get(nbId) != -2 || maze.get(nbRow[i])[nbCol[i]] == '#') continue;
            prev.set(nbId, curr);
            q.insert(nbId);
        }
    }
    if (prev.get(finish) !=-2) {
        for (int curr = prev.get(finish); curr !=start; curr= prev.get(curr)) {
            std::string s= maze.get(curr / width);
            s[curr % width] ='x';
            maze.set(curr / width, s);
        }
    }
    printLine(output, 5, "/ \\", len(0));
    for (int r =0; r< height; r++) {
        output << std::string(r % 2==0 ? 4 : 2, ' ');
        for (int c=0; c< len(r); c++) output << "| " << maze.get(r)[c] << " ";
        output << "|\n";
        if (r + 1 < height) printLine(output, 3, r % 2 == 0 ? "/ \\" : "\\ /", std::max(len(r), len(r + 1)));
    }
    printLine(output, height % 2 == 1 ? 5 : 3, "\\ /", len(height - 1));
}