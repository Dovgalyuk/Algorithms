#include "d_graph.h"
#include <vector>
#include <climits>
// struct GraphSettings
// {
//     int vertexCount;
//     std::vector

// };
class PathFinder {
    public:
    PathFinder(D_Graph<int>* graph, int from) {
        start = from;
        for (size_t i = 0; i < graph->size(); i++) {
            if (i == start)
                graph->getVertex(i)->setLabel(0);
            else
                graph->getVertex(i)->setLabel(INT_MAX);
        }

        for (int i = 0; i < graph->size(); i++) {
            used.push_back(0);
            p.push_back(start);
        }

        while (vertexWithMinLabel(graph) != -1) {
            size_t minVertexIndex = vertexWithMinLabel(graph);
            auto minVertex = graph->getVertex(minVertexIndex);
            
            D_Graph<int>::EdgesIterator iterator(minVertex);
    
            while (*iterator != nullptr) {
                int summ = minVertex->getLabel() + (*iterator)->getWeight();
                if (summ < (*iterator)->getDest()->getLabel()) {
                    (*iterator)->getDest()->setLabel(summ);
                    p[graph->getIndexOf((*iterator)->getDest())] = minVertexIndex;
                }

                ++iterator;        
            }
            used[minVertexIndex] = true;
        }
    }
    std::vector<int> pathTo(size_t index) {
        std::vector<int> path;
        int cur = p[index];
        path.push_back(cur);
        while(cur != start) {
            cur = p[cur];
            path.push_back(cur);
        }
        return path;
        
    }
    private:
    
    int vertexWithMinLabel(D_Graph<int>* graph) {
        int minIndex = INT_MAX;
        int minLabel = INT_MAX;
        for (int i = 0; i < graph->size(); i++) {
            if ((graph->getVertex(i)->getLabel() < minLabel) && (!used[i])) {
                minLabel = graph->getVertex(i)->getLabel();
                minIndex = i;
            }
        }
        if (minIndex == INT_MAX) {
            return -1;
        }
        return minIndex;

    }
    std::vector<bool> used;
    std::vector<int> p;
    int start;
};

int main() {
    const int vertexCount = 5;
     D_Graph<int>* graph = new D_Graph<int>(vertexCount, 0);

    
    int edges[10][3] {{0, 1, 10},{0,2,30},{0,3,50},{0,4,10},{4,0,10},{4,3,30},{3,2,20},{3,1,40}, {2,4,10}, {4,2,10}};
    for (int i = 0; i < 10; i++) {
        graph->getVertex(edges[i][0])->addEdgeTo(graph->getVertex(edges[i][1]));
        graph->getVertex(edges[i][0])->getEdgeTo(graph->getVertex(edges[i][1]))->setWeight(edges[i][2]);
    }

    PathFinder pathFinder(graph, 0);
    std::cout << "shortest path to \n";
    for (int i = 0; i < graph->size(); i++) {
        std::cout << i << ":"<<graph->getVertex(i)->getLabel() << " ";
    }
    std::vector<int> path = pathFinder.pathTo(3);
    std::cout << "\npath to 3: ";
    for (auto v: path) {
        std::cout<<"<-"<< v;
    }
    
    delete graph;

    


    

    return 0;
}