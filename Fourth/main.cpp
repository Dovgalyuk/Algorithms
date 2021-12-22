#include "d_graph.h"
#include <vector>
#include <climits>

class PathFinder {
public:
    PathFinder(D_Graph<int>* graph, int vertexCount) {
        int vertexCorrent = 0;
        int min, i, j, a, u, b, v, mincost = 0;
        visited[0] = 1;
        while (vertexCorrent < vertexCount)
        {
            for (i = 0, min = INT_MAX; i < vertexCount; i++)
                for (j = 0; j < vertexCount; j++)
                    if (graph->getVertex(i)->getEdgeTo(graph->getVertex(j))->getWeight() < min)
                        if (visited[i] != 0)
                        {
                            min = graph->getVertex(i)->getEdgeTo(graph->getVertex(j))->getWeight();
                            a = u = i;
                            b = v = j;
                        }
            if (visited[u] == 0 || visited[v] == 0)
            {
                path.push_back(b);
                std::cout << "\n " << vertexCorrent << ": " << a << " -> " << b << " = " << min; //Можно вывести так
                mincost += min;
                visited[b] = 1;
            }
            graph->getVertex(a)->getEdgeTo(graph->getVertex(b))->setWeight(INT_MAX);
            graph->getVertex(b)->getEdgeTo(graph->getVertex(a))->setWeight(INT_MAX);
            vertexCorrent++;
        }
        std::cout << "\n ";
        std::cout << 0 << " --> ";
        for (int i = 0; i < vertexCount - 1; i++)
        {
            std::cout << path[i];
            if (i < vertexCount - 2) std::cout << " --> ";
        }

        std::cout << "\n mincost  " << mincost;
    }
private:
    int visited[10] = { 0 };
    std::vector<int> path;
    int start;
};

int main() {
    const int vertexCount = 5;
    D_Graph<int>* graph = new D_Graph<int>(vertexCount, 0);

    int edges[vertexCount][vertexCount]
    {
  {0, 9, 75, 0, 0},
  {9, 0, 95, 19, 42},
  {75, 95, 0, 51, 66},
  {0, 19, 51, 0, 31},
  {0, 42, 66, 31, 0}
    };
    for (int i = 0; i < vertexCount; i++)
        for (int j = 0; j < vertexCount; j++) {
            if (edges[i][j] == 0)
                edges[i][j] = INT_MAX;
            graph->getVertex(i)->addEdgeTo(graph->getVertex(j));
            graph->getVertex(i)->getEdgeTo(graph->getVertex(j))->setWeight(edges[i][j]);
        }
    PathFinder pathFinder(graph, vertexCount);

    delete graph;
    return 0;
}
