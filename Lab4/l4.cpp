#include <iostream>
#include "graf.h"
#include "queue.h"
#include "vector.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    cout << "Kоличество вершин: ";
    int countVertexes;
    cin >> countVertexes;
    cout << "-------------------------";
    cout << endl;
    Graf<int, int> graf(countVertexes, 1);

    for (int i = 0; i < countVertexes; ++i) { // помечаем вершины
        graf.setDataVertex(i, i);
    }

    for (int i = 0; i < countVertexes; i++) { // заполняем ребра для каждой вершины   
        cout << endl;
        cout << "Сколько рёбер исходит из вершины " << graf.getDataVertex(i) << "?" << endl;
        int tempCountEdges;
        cin >> tempCountEdges;
        for (int j = 0; j < tempCountEdges; ++j) {
            cout << "В какую вершину идет " << j + 1 << " ребро ? ";
            int ToVertex;
            cin >> ToVertex;
            graf.addEdge(graf.getVertex(i), graf.getVertex(ToVertex),1);
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

    Queue* queue = queue_create();
    Vector* dist = vector_create(); // расстояния до начальной вершины
    Vector* parents = vector_create(); // родители
    for (int i = 0; i < countVertexes; i++) // заполним нулями для дальнейшей проверки
    {
        vector_set(dist, i, 0);
        vector_set(parents, i, -1);
    }
    queue_insert(queue, a); // помещаем начальную вершину в очередь
    while (!queue_empty(queue)) // пока очередь не опустела
    {
        int kk = queue_get(queue); // берем из очереди крайний элемент
        queue_remove(queue); // удаляем его
        for (int i = 0; i < countVertexes; i++) // смотрим, с какими вершинами смежна kk
        {
            if ((matr[kk][i] != 0) && (kk != i) && (vector_get(dist, i) == 0)) // последнее условие - чтобы не трогать начальную вершину в массиве по ее индексу
            {
                queue_insert(queue, i);  //добавляем в очередь вершину i
                vector_set(dist, i, vector_get(dist, kk) + 1); // записываем расстояние до i 
                vector_set(parents, i, kk);
            }
        }
    }

    if (vector_get(dist, b) == 0)
    {
        cout << "Такого пути не существует.";
    }

    else
    {
        Vector* path = vector_create();
        int t;
        int index = 0;
        t = vector_get(parents, b);
        vector_set(path, index, b);
        index += 1;
        while (t != a) {
            vector_set(path, index, t);
            t = vector_get(parents, t);
            index += 1;
        }
        vector_set(path, index, a);

        cout << "Кратчайший путь: ";
        for (int i = index; i > 0; i--)
        {
            cout << vector_get(path, i) << "->";
        }
        cout << vector_get(path, 0) << endl;
        vector_delete(path);
    }
    vector_delete(dist);
    vector_delete(parents);
    queue_delete(queue);
    for (int i = 0; i < countVertexes; i++)
    {
        delete[] matr[i];
    }
    delete[] matr;
}