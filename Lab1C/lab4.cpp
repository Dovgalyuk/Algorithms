#include <iostream>
#include <vector>
#include <algorithm>
#include "graphmatr.h"
#include <climits>
using namespace std;

int V = 5;
vector<int> parent(V);



int find(int i)
{
    if (parent[i] != i)
        parent[i] = find(parent[i]);
    return parent[i];
}
void union1(int i, int j)
{
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

void KruskalMST(Graph<int>cost)
{
    int mincost = 0; 

 
    for (int i = 0; i < V; i++)
        parent[i] = i;

   
    int edge_count = 0, a, b;
    while (edge_count < V - 1) {
        int min = INT_MAX;
        a = -1, b = -1;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (find(i) != find(j) && cost.getEdgeWeight(i,j) < min && cost.getEdgeWeight(i, j) > 0) {
                    min = cost.getEdgeWeight(i, j);
                    a = i;
                    b = j;
                }
            }
        }

        union1(a, b);
        printf("Edge %d:(%d, %d) cost:%d \n", edge_count++, a, b, min);
        mincost += min;
    }
    printf("\n Minimum cost= %d \n", mincost);
}

int main() {
    Graph<int> graph(5);
    graph.addEdge(0, 1, (void*)10);
    graph.addEdge(0, 2, (void*)20);
    graph.addEdge(1, 2, (void*)30);
    graph.addEdge(1, 3, (void*)40);
    graph.addEdge(2, 3, (void*)50);
    graph.addEdge(2, 4, (void*)60);
    graph.addEdge(3, 4, (void*)70);

    
    KruskalMST(graph);
    return 0;
};
