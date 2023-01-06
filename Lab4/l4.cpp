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
    cout << "----------------------------------------------------";
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
        t = parents[b]; // поднимаемся до начальной запоминая родителей
        index += 1;
        while (t != a) {
            path[index] = t;
            t = parents[t];
            index += 1;       // index в итоге стал равен длине кратчайшего пути
        }
        path[index] = a;   // в path хранится путь найденный по поиску в ширину но пока не выводим его

        vector <vector <int>> paths(countVertexes * 10, vector <int>(index + 1, 0)); // таблица для хранения всех кратчайших путей
        
        path.resize(index+1);
        for (auto start = path.begin(), end = prev(path.end()); start < end; ++start, --end) // переворачиваем так как там от конца к началу
        {
            swap(*start, *end);
        }

        for (int i = 0; i < index + 1; i++) // записываем первый путь
        {
            paths[0][i] = path[i];
        }

        int kolvoPaths = 1; // кол-во найденных путей

        for (int i = 0; i < kolvoPaths; i++) // для каждого кратчайшего пути ищем кандидатов
        {
            int spurVertex = 0, nextVertex = 0;
            int lendth = 0;

            for (int j = 0; j < index; j++) // организуем вевление в каждой вершине последнего найденного пути
            {
                vector <int> newPath(index + 1, 0); // новый путь
                spurVertex = paths[i][j]; // вершина ветвления
                nextVertex = paths[i][j + 1]; // вершина после вершины ветвления
           
                matr[spurVertex][nextVertex] = false; // временно удаляем ребро идущее из вершины ветвления

                for (int k = 0; k < j + 1; k++) // записали корневой путь
                {
                    newPath[k] = paths[i][k];
                   
                }

                // поиск в ширину

                vector <int> distNew(countVertexes, 0); // расстояния до начальной вершины
                vector <int> parentsNew(countVertexes, 0); // родители

                queue.push(a); // помещаем начальную вершину в очередь
                while (!queue.empty()) // пока очередь не опустела
                {
                    int kk = queue.front(); // берем из очереди крайний элемент
                    queue.pop(); // удаляем его
                    for (int h = 0; h < countVertexes; ++h) // смотрим, с какими вершинами смежна kk
                    {
                        if ((matr[kk][h] == true) && (distNew[h] == 0) && (h != a))
                        {
                            queue.push(h);  // добавляем в очередь вершину h
                            distNew[h] = distNew[kk] + 1; // записываем расстояние до h
                            parentsNew[h] = kk; // записываем родителя h
                        }
                    }
                }

                matr[spurVertex][nextVertex] = true; // возвращаем ребро на место
                
                if (distNew[b] == index) // если длина соответвтует кратчайшему
                {
                    lendth = index;
                    int v;              
                    newPath[lendth] = b;
                    v = parentsNew[b]; // снова поднимаемся по родителям до начальной
                    lendth--;
                    while ((v != spurVertex) && (lendth != -1)) 
                    {
                        newPath[lendth] = v;
                        v = parentsNew[v];
                        lendth--;         
                    }

                    int flag = 0, count = 0;
                    for (int z = 0; z < kolvoPaths; z++)
                    {
                        flag = 0;
                        for (int y = 0; y < index + 1; y++) // считываем путь чтобы сравнить с ним каждый
                        {
                            if (paths[z][y] == newPath[y])
                            {
                                flag++;
                            }  
                            if (flag == index + 1) { count++; } // если все элементы совпали, сообщаем об этом

                        }
                    }

                    if (count == 0) // если совпадений нет
                    {
                        for (int c = 0; c < index + 1; c++) // записываем путь в таблицу
                        {
                            paths[kolvoPaths][c] = newPath[c];
                        }
                        kolvoPaths++; 
                    }
                  
                    spurVertex = 0;
                    nextVertex = 0;
                    newPath.clear();
                    parentsNew.clear();
                    distNew.clear();
                }
                
            }
        }

        for (int i = 0; i < kolvoPaths; i++) { // вывод путей

         
                for (int j = 0; j < index; j++) {
                    cout << paths[i][j] << "->";
                }
                cout << paths[i][index];
                cout << endl;
            
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
