#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include "queue.h"
using namespace std;

typedef Queue<int> queue;
int main(){
    int elementY;
    int elementX;
    int num = 0;
    char value[] = "123456789";
    vector<vector<char>> maze;
    string buff;
    int X, Y;
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
                    elementY = i;
                    elementX = j;
                    break;
                }
            }
        } //  поиск начала

        if (maze[elementY - 1][elementX] == '.') // нахождение первых пустых клеток
            maze[elementY - 1][elementX] = value[num];

        if (maze[elementY + 1][elementX] == '.')
            maze[elementY + 1][elementX] = value[num];

        if (maze[elementY][elementX - 1] == '.')
            maze[elementY][elementX - 1] = value[num];

        if (maze[elementY][elementX + 1] == '.')
            maze[elementY][elementX + 1] = value[num];

        num++;
        bool end = false;
        // заполнение путей
        while (!end)
        {
            for (int i = 0; i < maze.size(); ++i) {
                for (int j = 0; j < maze[0].size(); ++j) {
                    if (maze[i][j] == value[num - 1])
                    {
                        if (maze[i - 1][j] == '.')
                            maze[i - 1][j] = value[num];
                        if (maze[i + 1][j] == '.')
                            maze[i + 1][j] = value[num];
                        if (maze[i][j - 1] == '.')
                            maze[i][j - 1] = value[num];
                        if (maze[i][j + 1] == '.')
                            maze[i][j + 1] = value[num];

                    }
                    if (maze[i][j] == 'Y' && maze[i - 1][j] == value[num]) {
                        X = j;
                        Y = i;
                        end = true;
                    }
                    else if (maze[i][j] == 'Y' && maze[i + 1][j] == value[num]) {
                        X = j;
                        Y = i;
                        end = true;
                    }
                    else if (maze[i][j] == 'Y' && maze[i][j - 1] == value[num]) {
                        X = j;
                        Y = i;
                        end = true;
                    }
                    else if (maze[i][j] == 'Y' && maze[i][j + 1] == value[num]) {
                        X = j;
                        Y = i;
                        end = true;
                    }
                }
            }
            num++;
            if(num == 10)
            {
                cout << "Error";
                end = true;
            }
        }

        num = 0;
        // поиск кратчайшего пути
        while (end)
        {
            if (maze[Y][X - 1] == value[num])
                end = false;
            else if (maze[Y][X + 1] == value[num])
                end = false;
            else if (maze[Y - 1][X] == value[num])
                end = false;
            else if (maze[Y + 1][X] == value[num])
                end = false;
            else
                num++;
        }

        num = num+2;
        int buffX = X, buffY = Y;
        int count = num - 1;
        int buffer = 0;

        queue neighborX;
        queue neighborY;

        // заполнение очереди начиная с 1 шага
        while (buffer != num - 1)
        {
            while (count != buffer) {
                if (maze[Y - 1][X] == value[count - 1])
                {
                    Y--;
                    count--;
                }
                else if (maze[Y + 1][X] == value[count - 1])
                {
                    Y++;
                    count--;
                }
                else if (maze[Y][X - 1] == value[count - 1])
                {
                    X--;
                    count--;
                }
                else if (maze[Y][X + 1] == value[count - 1])
                {
                    X++;
                    count--;
                }
            }
            neighborY.insert(Y);
            neighborX.insert(X);
            count = num - 1;
            X = buffX;
            Y = buffY;
            buffer++;
        }

        // заполнение кратчайшего пути
        while (!neighborX.empty() && !neighborY.empty())
        {
            maze[neighborY.get()][neighborX.get()] = 'x';
            neighborY.remove();
            neighborX.remove();
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