#include <iostream>
#include "graph.h"
#include <vector>
using namespace std;

void Floid(int** matrix, int colvo) //матрица веса и количество вершин
{
    for (int a = 0; a < colvo; a++) { // какой нибудь элемент A
        for (int b = 0; b < colvo; b++) { // какой нибудь элемент B
            for (int c = 0; c < colvo; c++) { // какой нибудь элемент C  
                if (b != c && matrix[b][a] != -1 && matrix[a][c] != -1) { // если из A в B есть ребро и из B в C есть ребро. А так же B != C
                    if (matrix[b][c] == -1) {  // если у B и C не было связи
                        matrix[b][c] = matrix[b][a] + matrix[a][c]; // вес пути от B до C равняется сумме весов путей от B до A и от A до C
                    }
                    else {
                        matrix[b][c] = min(matrix[b][c], matrix[b][a] + matrix[a][c]); // если же они уже были связаны - заменяем на минимальный вес, 
                    }                                                                  // сравнивая текущий и новый
                }
            }
        }
    }
    return;
}

int main() {
    setlocale(LC_ALL, "ru");
    cout << "Введите количество вершин :";
    int countVertexes;
    cin >> countVertexes; 

    auto graph = new Graph<int, int>(countVertexes, 1);

    for (int i = 0; i < countVertexes; ++i) { // помечаем вершины
        int tempData;
        cout << "[" << i << "] = ";
        cin >> tempData;
        graph->setDataVertex(i, tempData);
    }

    for (int i = 0; i < countVertexes; i++) { // заполняем ребра для каждой вершины   
        cout << endl;
        cout << "Вершина: " << graph->getDataVertex(i) << " (с индексом: " << i << ")" << endl;
        cout << "Сколько рёбер у вершины?" << endl;
        int tempCountEdges;
        cin >> tempCountEdges;
        for (int j = 0; j < tempCountEdges; ++j) {
            cout << j + 1 << " ребро. До какой вершины его протянуть? (индекс вершины): ";
            int indexToVertex;
            cin >> indexToVertex;
            cout << "Вес ребра: ";
            int tempWeight;
            cin >> tempWeight;
            graph->addEdge(graph->getVertex(i), graph->getVertex(indexToVertex), tempWeight);
        }
    }

    int** shortPath = new int* [countVertexes]; // создаём таблицу смежности и заполняем её нулями
    for (int i = 0; i < countVertexes; i++)
    {
        shortPath[i] = new int[countVertexes];
        for (int l = 0; l < countVertexes; l++)
        {
            shortPath[i][l] = 0;
        }
    }
    //заполняем матрицу веса между вершинами (нулевая итерация)
    for (int i = 0; i < countVertexes; ++i) {
        for (int j = 0; j < countVertexes; ++j) { //двойной цикл, чтобы каждый сравнить с каждым
            if (i == j) { // сам в себя - всегда ставим ноль
                shortPath[i][j] = 0;
            }
            else {
                if (graph->checkEdge(graph->getVertex(i), graph->getVertex(j))) //если есть путь из одного во второй
                    shortPath[i][j] = graph->getWeightEdge(graph->getVertex(i), graph->getVertex(j)); //заполняем элемент матрицы весом ребра
                else
                    shortPath[i][j] = -1; //если пути нет - ставим минус один - "бесконечность"
            }
        }
    }
    
    Floid(shortPath, countVertexes); //отправляем нашу матрицу проходить итерации

    cout << endl <<"Матрица кратчайших путей: " << endl;

    for (int i = 0; i < countVertexes; i++) {
        for (int j = 0; j < countVertexes; j++) {
            cout << shortPath[i][j] << " ";
        }
        cout << endl;
    }
}