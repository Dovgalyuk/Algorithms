#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include "queue.h"
using namespace std;

typedef Queue<int> queue;
int main(){

    pair<queue, queue> element;
    pair<int, int> neighbor[2];
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

        bool end = false;
        neighbor[0].first = element.first.get();
        neighbor[0].second = element.second.get();

        while (!end)
        {
            if (maze[neighbor[0].first - 1][neighbor[0].second] == '.' && neighbor[0].first - 1 != neighbor[1].first)
            {
                neighbor[1].first = neighbor[0].first;
                neighbor[1].second = neighbor[0].second;
                neighbor[0].first--;
                element.first.insert(neighbor[0].first);
                element.second.insert(neighbor[0].second);
            }
            else if (maze[neighbor[0].first + 1][neighbor[0].second] == '.' && neighbor[0].first + 1 != neighbor[1].first)
            {
                neighbor[1].first = neighbor[0].first;
                neighbor[1].second = neighbor[0].second;
                neighbor[0].first++;
                element.first.insert(neighbor[0].first);
                element.second.insert(neighbor[0].second);
            }
            else if (maze[neighbor[0].first][neighbor[0].second - 1] == '.' && neighbor[0].second - 1 != neighbor[1].second)
            {
                neighbor[1].first = neighbor[0].first;
                neighbor[1].second = neighbor[0].second;
                neighbor[0].second--;
                element.first.insert(neighbor[0].first);
                element.second.insert(neighbor[0].second);
            }
            else if (maze[neighbor[0].first][neighbor[0].second + 1] == '.' && neighbor[0].second + 1 != neighbor[1].second)
            {
                neighbor[1].first = neighbor[0].first;
                neighbor[1].second = neighbor[0].second;
                neighbor[0].second++;
                element.first.insert(neighbor[0].first);
                element.second.insert(neighbor[0].second);
            }
            else if (maze[neighbor[0].first][neighbor[0].second + 1] == 'Y')
                end = true;
            else
            {
                cout << "Error";
                end = true;
                return 0;
            }
        }

        element.first.remove();
        element.second.remove();

        while (!element.first.empty())
        {
            maze[element.first.get()][element.second.get()] = 'x';
            element.first.remove();
            element.second.remove();
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