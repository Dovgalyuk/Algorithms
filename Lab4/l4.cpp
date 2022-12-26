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
            
           /* else if ((matr[kk][i] != 0) && (dist[i] != 0) && (i != a)) // если есть еще один кратчайший путь
            {
                vector <int> NewPath(countVertexes, 0);
                int t;
                int index = 0;
                t = kk; // родитель конечной вершины
                NewPath[index] = b;
                index += 1;
                while (t != a) {
                    NewPath[index] = t;
                    t = parents[t];
                    index += 1;
                }
                NewPath[index] = a;

                cout << "Кратчайший путь: ";
                for (int i = index; i > 0; i--)
                {
                    cout << NewPath[i] << "->";
                }
                cout << NewPath[0] << endl;
                NewPath.clear();
            }*/
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


        // ищем такие же кратчайшие пути, начиная с конечной
        
        for (int i = (countVertexes-1); i > -1; i--) // снова поиск в ширину но с конца
        {

            if (matr[i][b] == true) // проверяем, какие ребра идут в конечную вершину
            {
                vector <int> distBottom(countVertexes, 0); // расстояния до конечной вершины
                vector <int> parentsBottom(countVertexes, 0); // родители
              
                queue.push(i); // помещаем конечную вершину в очередь
                distBottom[i] = distBottom[b] + 1; // записываем расстояние до i от конечной (1)
                parentsBottom[i] = b; // родитель i - конечная вершина

                while (!queue.empty()) // пока очередь не опустела
                {
                    int kk = queue.front(); // берем из очереди крайний элемент
                    queue.pop(); // удаляем его
                    for (int j = (countVertexes-1); j > -1; j--) // смотрим, с какими вершинами смежна kk
                    {
                        if ((matr[j][kk] == true) && (distBottom[j] == 0) && (j != b))
                        {
                            queue.push(j);  //добавляем в очередь вершину j
                            distBottom[j] = distBottom[kk] + 1; // записываем расстояние до j от конечной
                            parentsBottom[j] = kk; // записываем родителя j  
                        }
                    }
                }
                if (distBottom[a] == index) // если пройденное расстояние до начальной равно кратчайшему пути
                {
                    vector <int> pathBottom(countVertexes, 0); // массив для пути
                    int t;
                    int index = 0; // теперь с помощью index отслеживаем место в массиве
                    pathBottom[index] = a;
                    t = parentsBottom[a]; 
                    index += 1;
                    while (t != b) {  // идем к начальной, считывая родителей 
                        pathBottom[index] = t;
                        t = parentsBottom[t];
                        index += 1;
                    }
                    pathBottom[index] = b; 

                    for (int i = 0; i < index; i++) // выводим путь
                    {
                        cout << pathBottom[i] << "->";
                    }
                    cout << b;
                    pathBottom.clear();
                }
                cout << endl;
                distBottom.clear();
                parentsBottom.clear();
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
