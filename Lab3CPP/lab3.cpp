#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <queue.h>


void lab3(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    int rowscol = 0, rows =0;
    int startX = 0, startY = 0;

    while (std::getline(file, line)) {
        if (rowscol == 0) rowscol = line.length();
        for (int i = 0; i < rowscol; i++){
            if (line[i] == 'X') {
                startX = rows;
                startY = i;
            }
        }
        rows++;
    }

    file.clear();
    file.seekg(0);

    char** pole = new char* [rowscol];
    bool** visited = new bool* [rowscol];

    for (int i = 0; i < rowscol; i++) {
        pole[i] = new char[rowscol+1];
        visited[i] = new bool[rowscol];
        std::getline(file, line);
        for (int j = 0; j < rowscol; j++) {
            pole[i][j] = line[j];
            visited[i][j] = false;
        }
        pole[i][rowscol] = '\0';
    }
    file.close();

    int dx[] = { -1, 0, 1, 0 };
    int dy[] = { 0, 1, 0, -1 };

    Queue* queue = queue_create();
    queue_insert(queue, startX * rowscol + startY);
    visited[startX][startY] = true;
    int o = 1;

    while (!queue_empty(queue)){
        int pos = queue_get(queue);
        queue_remove(queue);

        int x = pos / rowscol;  
        int y = pos % rowscol;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && nx < rowscol && ny >= 0 && ny < rowscol && !visited[nx][ny] && pole[nx][ny] != '#') {
                visited[nx][ny] = true;
                queue_insert(queue, nx * rowscol + ny);
                o++;
            }

        }

    }

    std::cout << o << std::endl;

    for (int i = 0; i < rowscol; i++) {
        for (int j = 0; j < rowscol; j++) {
            if (visited[i][j] && pole[i][j] == '.') {
                std::cout << 'x';
            }
            else {
                std::cout << pole[i][j];
            }
        }

    }

    queue_delete(queue);

    for (int i = 0; i < rowscol; i++) {
        delete[] pole[i];
        delete[] visited[i];
    }
    delete[] pole;
    delete[] visited;

   
}



int main(int argc, char* argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            lab3(argv[i]);
        }
    }
    else {
        std::string filenames[] = { "input.txt", "input2.txt"};
        for (int i = 0; i < 2; i++) {
            lab3(filenames[i]);
        }
    }
    return 0;
}

