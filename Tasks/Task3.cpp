#include "queue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>



class Maze {
    public:

struct Pos
    {
        int X;
        int Y;
        Pos() {
            X = 0;
            Y = 0;
        }
        Pos(int x, int y) {
            X = x;
            Y = y;
        }
        Pos movedBy(int x, int y) {
            return Pos(X+x, Y+y);
        }
        
    };

    int M,N;
    std::vector<std::vector<char>> maze;
    
    Pos startPos;
    Queue<Pos> queue; 
    int steps;

    
    Maze(std::string path) {

        steps = 0;

        //maze filling, finding M, N and startPos
        std::ifstream file;
        file.open(path);
        if (!file.is_open()) {
            std::cout << "bad file " << path;
        }
        M =0 ;
        while (!file.eof()) {
            std::string curStr;
            std::getline(file, curStr);
            maze.resize(M+1);
            for (N = 0; N < curStr.length(); N++) {
                maze[M].push_back(curStr[N]);
                if (maze[M][N] == 'X') {
                    startPos = {M, N};
                }  
            }
            M++;
        }
        file.close();    

        

    }

    void printMaze() {
        for (auto line : maze) {
            for (char ch : line) {
                std::cout << ch << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
        
    }

    void solveMaze() {
        queue.insert(startPos);
        while (!queue.empty()) {
            Pos curPos = queue.get();
            queue.remove();
            addToQueue(curPos.movedBy(-1, 0));
            addToQueue(curPos.movedBy(1, 0));
            addToQueue(curPos.movedBy(0, -1));
            addToQueue(curPos.movedBy(0, 1));
        }
        std::cout << "maze solved. " << steps << " cells reached.\n";
        printMaze();
    }

    private:
    void addToQueue(Pos pos) {
        if ((pos.X < M) && (pos.X >= 0) && (pos.Y < N) && (pos.Y >= 0)) {
            if (maze[pos.X][pos.Y] == '.') {
                queue.insert(pos);
                maze[pos.X][pos.Y] = 'x';
                steps++;
            }
        }
    }
};


int main() {
    
    Maze maze = Maze("FileForTask3.txt");
    std::cout << "MAZE "<< maze.M << " by " <<maze.N << "\nStart Pos "<<"(" << maze.startPos.X <<", "<<maze.startPos.Y<<")\n";
    maze.printMaze();
    maze.solveMaze();
    return 0;
}