#include <iostream>
#include "graph.h"
#include <vector>
#include <algorithm>

using namespace std;

typedef int Data;

class DisjointSet 
{
public:
    DisjointSet(int size) 
    {
        rank = vector<int>(size, 0);
        parent = vector<int>(size);
        for (int i = 0; i < size; i++) 
        {
            parent[i] = i;
        }
    }

    int find(int i) 
    {
        if (parent[i] != i) 
        {
            parent[i] = find(parent[i]); // Путь сжатия
        }
        return parent[i];
    }

    void unionSets(int a, int b) 
    {
        a = find(a);
        b = find(b);
        if (a != b) 
        {
            if (rank[a] < rank[b]) 
            {
                swap(a, b);
            }
            parent[b] = a;
            if (rank[a] == rank[b]) 
            {
                rank[a]++;
            }
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};


// Функция для поиска минимального покрывающего дерева с помощью алгоритма Крускала
vector<Graph<Data>::Edge> kruskalMST(Graph<Data>& graph) 
{
    vector<Graph<Data>::Edge> edges;
    vector<Graph<Data>::Edge> mst; // Минимальное покрывающее дерево

    // Собираем все ребра из графа
    for (int i = 0; i < graph.vertexCount(); i++) 
    {
        List<Graph<Data>::Edge>::Item* current = graph.adjacencyList(i).first();
        while (current != nullptr) 
        {
            // Создаем новое ребро с учетом начальной вершины (i)
            Graph<Data>::Edge newEdge = { i, current->data().to, current->data().weight };
            edges.push_back(newEdge);
            current = current->next();
        }
    }

    // Сортируем ребра по весу
    sort(edges.begin(), edges.end(), [](Graph<Data>::Edge& a, Graph<Data>::Edge& b)
        {
            return a.weight < b.weight;
        });

    DisjointSet dsu(graph.vertexCount());

    // Проходим по отсортированным ребрам и строим MST
    for (auto edge : edges) 
    {
        if (dsu.find(edge.from) != dsu.find(edge.to)) {
            dsu.unionSets(edge.from, edge.to);
            mst.push_back(edge);
        }
    }

    return mst;
}


// Пример использования
int main() 
{
    /*example:
    5
    5
    (0, 1, 10);
    (0, 2, 6);
    (0, 3, 5);
    (1, 3, 15);
    (2, 3, 4);

    Edges of the Minimum Spanning Tree:
    2 - 3 : 4
    0 - 3 : 5
    0 - 1 : 10

    */
    int vertexCount, edgesCount;
    cout << "Enter the number of vertices in the graph: ";
    cin >> vertexCount;

    Graph<Data> graph(vertexCount);

    cout << "Enter the number of edges in the graph: ";
    cin >> edgesCount;

    cout << "Enter the edges in the format: start end weight (each edge on a new line)" << endl;
    for (int i = 0; i < edgesCount; i++) 
    {
        int from, to;
        Data weight;
        cin >> from >> to >> weight;
        graph.addEdge(from, to, weight);
    }

    vector<Graph<Data>::Edge> mst = kruskalMST(graph);

    cout << "Edges of the Minimum Spanning Tree:" << endl;
    for (auto edge : mst) 
    {
        cout << edge.from << " - " << edge.to << " : " << edge.weight << endl;
    }
    
    return 0;
}
