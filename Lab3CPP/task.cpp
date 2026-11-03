#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "vector.h"
#include "queue.h"

Vector<std::string> maze;
int width =0;
int len(int row) {
    return static_cast<int>(maze.get(row).size());
}

int indent(int row) {
    return 2+2*(width-len(row));
}
void printLine(std::ostream &out,int spaces, const char *pattern, int count) {
    out <<std::string(spaces, ' ');
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
    int height= maze.size();
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
        for ( int i=0; i<6; i++) {
            int nbRow = row + (i < 2 ? 0 : (i < 4 ? -1 : 1));
            if (nbRow < 0 || nbRow >= height) continue;
            int nbCol;
            if (i < 2) {
                nbCol = col + (i == 0 ? -1 : 1);
            } 
            else {
                int twice = len(nbRow) - len(row) + 2 * col + (i % 2 == 0 ? -1 : 1);
                if (twice % 2 != 0) continue;
                nbCol = twice / 2;
            }
            if (nbCol < 0 || nbCol >= len(nbRow)) continue;
            int nbId = nbRow * width + nbCol;
            if (prev.get(nbId) != -2 || maze.get(nbRow)[nbCol] == '#') continue;
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
    printLine(output, indent(0) + 1, "/ \\", len(0));
    for (int r =0; r< height; r++) {
        output << std::string(indent(r), ' ');
        for (int c = 0; c < len(r); c++) output << "| " << maze.get(r)[c] << " ";
        output << "|\n";
        if (r + 1 < height) {
            bool grows = len(r + 1) > len(r);
            int longer = grows ? r + 1 : r;
            printLine(output, indent(longer) + 1, grows ? "/ \\" : "\\ /", len(longer));
        }
    }
    printLine(output, indent(height - 1) + 1, "\\ /", len(height - 1));
}