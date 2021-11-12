#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <list>

using namespace std;

bool bfs(int** graph, int n, int to, int* visited, list<int>& buffer, int* parents) {
    if (buffer.empty())
        return false;
    int from = buffer.front();
    buffer.pop_front();
    visited[from] = true;
    if (from == to) {
        return true;
    }
    for (int i = 0; i < n; ++i) {
        if (graph[from][i] == 0)
            continue;
        if (visited[i] == true)
            continue;
        if (find(buffer.begin(), buffer.end(), i) != buffer.end())
            continue;
        parents[i] = from;
        buffer.push_back(i);
    }
    return bfs(graph, n, to, visited, buffer, parents);
}

void print_path(int from, int to, int* parents, vector <int> mas, vector <string> Jesus, int kolDyg) {
    int p = -1;
    for (int i = 0; i < kolDyg * 2; i++) {
        if (mas[i] == to + 1) {
            p = i;
        }
    }
    if (to == from) {
        cout << Jesus.at(p);
        return;
    }
    int prefrom = parents[to];
    print_path(from, prefrom, parents, mas, Jesus, kolDyg);
    cout << " -> " << Jesus.at(p);
}

int main()
{
    // City1 City2 City2 End Start City1 Start End
    // City2 End Start City1 City1 City3 City1 City2 City3 City4 City4 End Start End
    // City2 City3 Start City1 City1 City3 City1 City2 City3 City4 City4 End Start End
    string str;
    cout << "Input cities(separete them with one space and only after last pair press enter):\n";
    getline(cin, str);
    int sizeJ = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ' ') {
            sizeJ++;
        }
    }
    vector <string> Jesus(sizeJ + 1);
    int p = 0;
    for (int i = 0; i < str.size(); i++) {
        if (isalpha(str[i]) || isdigit(str[i])) {
            Jesus.at(p) = Jesus.at(p) + str[i];
        }
        else if (str[i] == ' ') {
            p++;
        }
    }
    int kolDyg = (p - 1) / 2;
    int kolVer = 0;
    for (int i = 0; i < p - 1; i++) {
        int temp = 0;
        for (int j = 0; j < i; j++) {
            if (Jesus.at(i) != Jesus.at(j)) {
                temp++;
            }
        }
        if (temp == i) {
            kolVer++;
        }
    }
    // массив номеров
    vector <int> mas(kolDyg * 2);
    int temp = 1; bool hahaha = true;
    for (int i = 0; i < kolDyg * 2; i++) {
        mas[i] = temp;
        for (int j = 0; j < i; j++) {
            if (Jesus.at(i) == Jesus.at(j) && hahaha) {
                mas[i] = mas[j];
                temp--;
                hahaha = false;
            }
        }
        temp++;
        hahaha = true;
    }
    //  первый и последний элемент
    int from;
    int to;
    for (int i = 0; i < kolDyg * 2; i++) {
        if (Jesus.at(i) == Jesus.at(p - 1)) {
            from = mas[i] - 1;
        }
        else if (Jesus.at(i) == Jesus.at(p)) {
            to = mas[i] - 1;
        }
    }
    // Подготовка
    int** graph = new int* [kolVer];
    int* visited = new int[kolVer];
    int* parents = new int[kolVer];
    for (int i = 0; i < kolVer; i++) {
        graph[i] = new int[kolVer];
    }
    for (int i = 0; i < kolVer; i++) {
        for (int j = 0; j < kolVer; j++) {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < kolDyg * 2; i = i + 2) {
        int a, b;
        a = mas[i];
        b = mas[i + 1];
        graph[a - 1][b - 1] = graph[b - 1][a - 1] = 1;
    }
    // Ну погнали
    for (int i = 0; i < kolVer; i++) {
        visited[i] = 0;
    }
    list<int> buffer;
    buffer.push_back(from);
    if (false == bfs(graph, kolVer, to, visited, buffer, parents)) {
        cout << "path does not exist" << endl;
    }
    else {
        print_path(from, to, parents, mas, Jesus, kolDyg);
    }
    // Удаление
    for (int i = 0; i < kolVer; i++) {
        delete[] graph[i];
    }
    delete[] graph;
    delete[] visited;
    delete[] parents;
}