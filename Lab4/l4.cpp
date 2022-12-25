#include <iostream>
#include "graf.h"
#include <vector>
#include <queue>

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    cout << "Kоличество вершин: ";
    int countVertexes;
    cin >> countVertexes;
        cout << "---------------------------------------------------------";
    cout << endl;
    Graf<int, int> graf(countVertexes, 1);

    for (int i = 0; i < countVertexes; ++i) { // называем вершины
        int name;
        cout << "Имя для вершины [" << i << "] (число) = ";
        cin >> name;
        graf.setDataVertex(i, name);
    }

    for (int i = 0; i < countVertexes; i++) { // заполняем ребра для каждой вершины   
        cout << endl;
        cout << "Сколько рёбер исходит из вершины " << graf.getDataVertex(i) << "?" << endl;
        int tempCountEdges;
        cin >> tempCountEdges;
        if (tempCountEdges != 0)
        {
            for (int j = 0; j < tempCountEdges; ++j) {
                cout << "В какую вершину идет " << j + 1 << " ребро? ";
                int ToVertex;
                cin >> ToVertex;
                graf.addEdge(graf.getVertex(i), graf.getVertex(ToVertex), 1);
            }
        }
        cout << "---------------------------------------------------------";
    }
    cout << endl;
    cout << "Между какими вершинами нужно найти кратчайший путь? ";
    int a, b;
    cin >> a >> b;
   
    bool** matr = new bool* [countVertexes]; // матрица смежности
    for (int i = 0; i < countVertexes; i++)
    {
        matr[i] = new bool[countVertexes];
        for (int j = 0; j < countVertexes; j++)
        {
            matr[i][j] = false;
        }
    }

    for (int i = 0; i < countVertexes; ++i) // заполняем матрицу
    {
        for (int j = 0; j < countVertexes; ++j)
        {
            if (graf.checkEdge(graf.getVertex(i), graf.getVertex(j)))
            {
                matr[i][j] = true;
            }
        }
    }

    queue <int> queue;
    vector <int> dist(countVertexes, 0); // расстояния до начальной вершины
    vector <int> parents(countVertexes, 0); // родители
  
    queue.push(a); // помещаем начальную вершину в очередь
    while (!queue.empty()) // пока очередь не опустела
    {
        int kk = queue.front(); // берем из очереди крайний элемент
        queue.pop(); // удаляем его
        for (int i = 0; i < countVertexes; ++i) // смотрим, с какими вершинами смежна kk
        {
            if ((matr[kk][i] == true) && (dist[i] == 0) && (i != a))
            {
                queue.push(i);  //добавляем в очередь вершину i
                dist[i] = dist[kk] + 1; // записываем расстояние до i 
                parents[i] = kk;

            } 
        }
    }
    cout << endl;
    if (dist[b] == 0)
    {
        cout << "Такого пути не существует.";
    }

    else
    {
        vector <int> path(countVertexes, 0);
        int t;
        int index = 0;
        path[index] = b;
        t = parents[b];
        index += 1;
        while (t != a) {
            path[index] = t;
            t = parents[t];
            index += 1;             
        }
        path[index] = a; // index в итоге стал равен длине кратчайшего пути
        cout << "Кратчайший путь: ";
        for (int i = index; i > 0; i--)
        {
            cout << path[i] << "->";
        }
        cout << path[0] << endl;
        path.clear();
    }
    dist.clear();
    parents.clear();
    for (int i = 0; i < countVertexes; i++)
    {
        delete[] matr[i];
    }
    delete[] matr;
}
