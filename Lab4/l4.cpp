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
    cout << "-------------------------";
    cout << endl;
    Graf<int, int> graf(countVertexes, 1);

    for (int i = 0; i < countVertexes; ++i)   // называем вершины
    {
        graf.setDataVertex(i, i);
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
        cout << "----------------------------------------------------";
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
    
    // поиск в ширину

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
                queue.push(i);  // добавляем в очередь вершину i
                dist[i] = dist[kk] + 1; // записываем расстояние до i 
                parents[i] = kk; // записываем родителя i
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
        cout << "Кратчайшие пути: " << endl;
        vector <int> path(countVertexes, 0); 
        int t;
        int index = 0;   // тут находим длину кратчайшего чтобы потом сравнивать
        path[index] = b;
        t = parents[b];
        index += 1;
        while (t != a) {
            path[index] = t;
            t = parents[t];
            index += 1;       // index в итоге стал равен длине кратчайшего пути
        }
        path[index] = a;   // в path хранится путь найденный по поиску в ширину но мы его не выводим пока что

        // ищем такие же кратчайшие пути

        for (int i = 0; i < countVertexes; ++i) // снова поиск в ширину.
        {

            if (matr[a][i] == true) // проверяем, какие ребра идут в конечную вершину
            {
                vector <int> distTop(countVertexes, 0); // расстояния до конечной вершины
                vector <int> parentsTop(countVertexes, 0); // родители

                
                distTop[i] = distTop[a] + 1; // записываем расстояние до i от начальной (1)
                parentsTop[i] = a; // родитель i - начальная вершина

                queue.push(i); // помещаем начальную вершину в очередь
                while (!queue.empty()) // пока очередь не опустела
                {
                    int kk = queue.front(); // берем из очереди крайний элемент
                    queue.pop(); // удаляем его
                    for (int j = 0; j < countVertexes; ++j) // смотрим, с какими вершинами смежна kk
                    {
                        if ((matr[kk][j] == true) && (distTop[j] == 0))
                        {
                            queue.push(j);  //добавляем в очередь вершину j
                            distTop[j] = distTop[kk] + 1; // записываем расстояние до j от начальной
                            parentsTop[j] = kk; // записываем родителя j  
                        }
                    }
                }
                if (distTop[b] == index) // если пройденное расстояние до конечной равно кратчайшему пути
                {
                    vector <int> pathTop(countVertexes, 0); // массив для пути
                    int t;
                    int index = 0; // теперь с помощью index отслеживаем место в массиве
                    pathTop[index] = b;
                    t = parentsTop[b];
                    index += 1;
                    while (t != a) {  // идем к начальной, считывая родителей 
                        pathTop[index] = t;
                        t = parentsTop[t];
                        index += 1;
                    }
                    pathTop[index] = a;

                    for (int i = index; i > 0; i--) // выводим путь
                    {
                        cout << pathTop[i] << "->";
                    }
                    cout << b;
                    cout << endl;

                    pathTop.clear();
                }
                distTop.clear();
                parentsTop.clear();
            }
        }
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
