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

    0->1=3
    0->3=2
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

void selection(std::vector<std::vector<forKruskal>>& Vertexses,std::vector<forKruskal> KruskalEdges,int i,bool find_start, bool find_end, size_t current_multy_start, size_t current_multy_end, bool different_mylty){
    //проверка множеств
    if (current_multy_start != -1 && current_multy_end !=-1 && current_multy_start != current_multy_end) {
            different_mylty = true;
        }
        // нет концов - создать новое множество
        if (!find_start && !find_end) {
            std::vector<forKruskal> x;
            KruskalEdges[i].first->data = KruskalEdges[i].weight;
            KruskalEdges[i].end->data = KruskalEdges[i].weight;
            x.push_back(KruskalEdges[i]);
            Vertexses.push_back(x);
        }
        // есть начало ребра и конец но в разных множествах - объединение множеств 
        else if (different_mylty) {
            Vertexses[current_multy_start].insert(Vertexses[current_multy_start].end(), Vertexses[current_multy_end].begin(), (Vertexses[current_multy_end].end()));
            Vertexses[current_multy_end].clear();
            KruskalEdges[i].end->data = KruskalEdges[i].weight;
            Vertexses[current_multy_start].push_back(KruskalEdges[i]);  
        }
        //уже есть 
        else if (find_start && find_end) {
            return;
        }
        //добавить начало в проверенные
        else if (find_start) {
            KruskalEdges[i].end->data = KruskalEdges[i].weight;
            Vertexses[current_multy_start].push_back(KruskalEdges[i]);
        }
        //добавить конец в проверенные
        else if (find_end) {
            KruskalEdges[i].first->data = KruskalEdges[i].weight;
            Vertexses[current_multy_end].push_back(KruskalEdges[i]);
        }
}

void search(std::vector<std::vector<forKruskal>>& Vertexses,std::vector<forKruskal> KruskalEdges,int i){
    bool find_start = false;
    bool find_end = false;
    size_t current_multy_start = -1;
    size_t current_multy_end = -1; 
    bool different_mylty = false;
    for (size_t j = 0; j < Vertexses.size(); j++) {
        for (size_t l = 0; l < Vertexses[j].size(); l++) {
            
            if (KruskalEdges[i].first == Vertexses[j][l].first || KruskalEdges[i].first == Vertexses[j][l].end) {
                current_multy_start = j;
                find_start = true;
            }

            if (KruskalEdges[i].end == Vertexses[j][l].end || KruskalEdges[i].end == Vertexses[j][l].first) {
                find_end = true;
                current_multy_end = j;
            }
        }
    }
    selection(Vertexses,KruskalEdges,i,find_start,find_end,current_multy_start,current_multy_end, different_mylty);
    
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

    graph.showGraph();

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

    std::vector<std::vector<forKruskal>> Vertexses;
    std::vector<forKruskal> x;
    x.push_back(KruskalEdges[0]);
    Vertexses.push_back(x);
    x.clear();

    for (size_t i = 0; i < KruskalEdges.size(); i++) {
        search(Vertexses,KruskalEdges,i);
    }

    _Graph<int> result(VertexCount);

    for (size_t j = 0; j < Vertexses.size(); j++) {
        for (size_t l = 0; l < Vertexses[j].size(); l++) {
            result.setEdgetoVertex(graph.getVertexIndex(Vertexses[j][l].first), graph.getVertexIndex(Vertexses[j][l].end), Vertexses[j][l].weight); 
        }
    } 

    std::cout<<std::endl;
    result.showGraph();
    return 0;
} 