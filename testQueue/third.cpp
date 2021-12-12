#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include "queue.h"
using namespace std;

typedef Queue<int> queue;
int main(){

    pair<queue, queue> element;
    pair<int, int> neighbor;
    vector<vector<char>> maze;
    string buff;
    ifstream file(R"(C:\Users\vasya\OneDrive\Desktop\file2.txt)");
    if (file.is_open()){
        while (!file.eof())
        {
            getline(file, buff);
            maze.emplace_back(buff.begin(), buff.end());
        }
        file.close();
    } // заполнение вектора
    else
        cout << "File is not open!!!";

        for (int i = 0; i < maze.size(); ++i) {
            for (int j = 0; j < maze[0].size(); ++j) {
                if (maze[i][j] == 'X')
                {
                    element.first.insert(i);
                    element.second.insert(j);
                    break;
                }
            }
        } //  поиск начала

        while (!element.first.empty() && !element.second.empty()){
            neighbor.first = element.first.get();
            neighbor.second = element.second.get();
            element.first.remove();
            element.second.remove();
            if (maze[neighbor.first - 1][neighbor.second] == '.')
            {
                maze[neighbor.first - 1][neighbor.second] = 'x';
                element.first.insert(neighbor.first - 1);
                element.second.insert(neighbor.second);
            }
            else if (maze[neighbor.first + 1][neighbor.second] == '.')
            {
                maze[neighbor.first + 1][neighbor.second] = 'x';
                element.first.insert(neighbor.first + 1);
                element.second.insert(neighbor.second);
            }
            else if (maze[neighbor.first][neighbor.second - 1] == '.')
            {
                maze[neighbor.first][neighbor.second - 1] = 'x';
                element.first.insert(neighbor.first);
                element.second.insert(neighbor.second - 1);
            }
            else if (maze[neighbor.first][neighbor.second + 1] == '.')
            {
                maze[neighbor.first][neighbor.second + 1] = 'x';
                element.first.insert(neighbor.first);
                element.second.insert(neighbor.second + 1);
            }
            else
            {
                cout << "there is no way out" << endl << endl;
            }
        }

        // вывод лабиринта
        for (int i = 0; i < maze.size(); ++i) {
            for (int j = 0; j < maze[0].size(); ++j) {
                cout << maze[i][j];
            }
            cout << endl;
        }


    return 0;
}