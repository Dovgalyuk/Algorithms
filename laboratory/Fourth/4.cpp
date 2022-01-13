    /*Программа должна считывать параметры графа
    и искать для него минимальное покрывающее дерево алгоритмом Крускала.
    
    0->1=3
    0->3=2
    0->5=7
    2->0=8
    2->3=1
    2->4=4
    3->5=1
    4->3=2
    4->5=5

    Остово по Крускалу

    0->3=2
    0->1=3
    2->3=1
    3->5=1
    4->3=2

    */
#include <iostream>
#include <graph.h>
#include <vector>
#include <algorithm>

struct forKruskal
{
    _Graph<int>::Vertex* first = nullptr;
    _Graph<int>::Vertex* end = nullptr;
    int weight = 0;
};

bool comparator(const forKruskal& first, const forKruskal& second){
    return first.weight < second.weight;
}

int main() {
    int VertexCount = 6;
    _Graph<int> graph(VertexCount);
    graph.setEdgetoVertex(0,1,3);
    graph.setEdgetoVertex(0,3,2);
    graph.setEdgetoVertex(0,5,7);
    graph.setEdgetoVertex(2,0,8);
    graph.setEdgetoVertex(2,3,1);
    graph.setEdgetoVertex(2,4,4);
    graph.setEdgetoVertex(3,5,1);
    graph.setEdgetoVertex(4,3,2);
    graph.setEdgetoVertex(4,5,5);

    //graph.showGraph();

    std::vector<forKruskal> KruskalEdges;
    
    for(auto i =0;i<VertexCount;++i){
        _Graph<int>::EdgesIterator iter(graph,graph.getVertex(i));
        for (size_t j =0;j<VertexCount;++j){
            if (++iter){
                forKruskal KrusEdgeFromStruct;
                KrusEdgeFromStruct.weight = iter.getWeight();
                KrusEdgeFromStruct.first = iter.getIt();
                KrusEdgeFromStruct.end = iter.getCurrent();
                KruskalEdges.push_back(KrusEdgeFromStruct);
            }
        }
    }

    sort(KruskalEdges.begin(),KruskalEdges.end(),comparator);

    for(size_t i=0;i<KruskalEdges.size();++i){
        
    }


    return 0;
} 