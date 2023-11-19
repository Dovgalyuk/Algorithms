#include <iostream>
#include "graph.h"
#include <vector>
#include <algorithm>

using namespace std;

typedef int Data;
typedef Graph<Data>::Edge GraphEdge;

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
vector<pair<int, GraphEdge>> kruskalMST(Graph<Data>& graph)
{
    vector<pair<int, GraphEdge>> edges;
    vector<pair<int, GraphEdge>> mst; // Минимальное покрывающее дерево

    // Собираем все ребра из графа
    for (int i = 0; i < graph.vertexCount(); i++) 
    {
        Graph<Data>::NeighborIterator it(&graph, i);
        while (it.hasNext())
        {
            GraphEdge edge = it.current();
            edges.push_back(make_pair(i, edge));
            it.next();
        }
    }

    // Сортируем ребра по весу
    sort(edges.begin(), edges.end(), [](const pair<int, GraphEdge>& a, const pair<int, GraphEdge>& b)
        {
            return a.second.weight < b.second.weight;
        });

    DisjointSet dsu(graph.vertexCount());

    // Проходим по отсортированным ребрам и строим MST
    for (auto edge : edges) 
    {
        int from = edge.first;
        int to = edge.second.to;
        if (dsu.find(from) != dsu.find(to))
        {
            dsu.unionSets(from, to);
            mst.push_back(edge);
        }
    }

    return mst;
}


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

    vector<pair<int, GraphEdge>> mst = kruskalMST(graph);

    cout << "Edges of the Minimum Spanning Tree:" << endl;
    for (auto edge : mst) 
    {
        cout << edge.first << " - " << edge.second.to << " : " << edge.second.weight << endl;
    }
    
    return 0;
}
