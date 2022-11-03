#include <iostream>
#include <vector>
#include <algorithm>
#include "graph.h"

using std::cin; using std::cout; using std::vector;

struct Edge 
{
    int weight;
    int LeftID, RightID;

    Edge(int from, int to, int weight_) 
    {
        weight = weight_;
        LeftID = from;         // Из вершины 
        RightID = to;         // В вершину
    }
};

struct VertexData 
{
    int data = 0;
    int tag = 0;
};

bool Compare(const Edge& One, const Edge& Two)        // Сравнение для сортировки по весу ребер
{
    return One.weight < Two.weight;
}

int GetRoot(int R, Graph<VertexData>* graph)        // Получение корня
{
    VertexData VertexD = graph->GetVertexData(R);

    if (R == VertexD.data) 
    {
        return R;
    }
    else 
    {
        VertexD.data = GetRoot(VertexD.data, graph);
        graph->SetVertexData(R, VertexD);
        return graph->GetVertexData(R).data;
    }
}

bool Unite(int Left, int b, Graph<VertexData>* graph)
{
    int RLeft = GetRoot(Left, graph), RRight = GetRoot(b, graph);

    if (RLeft == RRight)
    {
        return false;
    }
    else 
    {
        VertexData RLeftData = graph->GetVertexData(RLeft);
        VertexData RRightData = graph->GetVertexData(RRight);

        if (RLeftData.tag < RRightData.tag)
        {
            RLeftData.data = RRightData.data;
            graph->SetVertexData(RLeft, RLeftData);
        }
        else if (RRightData.tag < RLeftData.tag)
        {
            RRightData.data = RLeftData.data;
            graph->SetVertexData(RRight, RRightData);
        }
        else 
        {
            RLeftData.data = RRightData.data;
            graph->SetVertexData(RLeft, RLeftData);

            RRightData.tag = RRightData.tag + 1;
            graph->SetVertexData(RRight, RRightData);
        }
        return true;
    }
}

int main() 
{
    vector<Edge> AllEdges;
    vector<Edge> Result;
    VertexData VertexD;
    int VertexNumber = 0, EdgeCount = 0, Number = 0, WeightTree = 0, Ver1 = 0, Ver2 = 0, EdgeWeight = 0;

    cout << "\n\tEnter the vertex number: "; cin >> VertexNumber; cout << "\n";             
    cout << "\n\tEnter the count of edges: "; cin >> EdgeCount; cout << "\n";

    auto graph = new Graph<VertexData>(VertexNumber, VertexD);
    for (int i = 0; i < VertexNumber; i++)
    {
        VertexD.data = i;
        graph->SetVertexData(i, VertexD);
    }

    cout << "\n\tEnter the links between the vertex:";
    cout << "\n\t(The first two numbers are vertex, and the third number is the weight of the edge between them)\n\n";

    for (int i = 0; i < EdgeCount; i++)
    {
        cout << "\t";
        cin >> Ver1 >> Ver2 >> EdgeWeight;
        graph->AddEdge(graph->GetVertex(Ver1), graph->GetVertex(Ver2), EdgeWeight);        // Добавляем ребра и вершины в граф
    }
                                                    
    for (int i = 0; i < graph->SizeVertexVec(); i++)       // Получаем все значения ребер и их вершины
    {
        auto* it = graph->GetVertex(i);
        Graph<VertexData>::EdgeIterator iter(it);

        while (*iter != nullptr) 
        {
            int to = graph->GetIndexVertex((*iter)->toVertex);
            AllEdges.push_back(Edge(i, to, (*iter)->GetWeight()));
            ++iter;
        }
    }

    sort(AllEdges.begin(), AllEdges.end(), Compare);   // Сортируем вес ребер по неубыванию

    for (auto &i : AllEdges) 
    {
        if (Unite(i.LeftID, i.RightID, graph))
        {
            WeightTree += i.weight;                  // Считаем вес ребер минимального покрывающего дерева
            Result.push_back(i);
        }
    }

    cout << "\n\tVertexes:   Edge weight:\n\n";

    for (auto &i : Result)
    {
        cout <<"\t" << i.LeftID << " -> " << i.RightID << "    = \t" << i.weight << "\n";
    }
    std::cout << "\n\tWeight MST: " << WeightTree << "\n\n";
    delete graph;
}
// Example of how the program works:
//Enter the vertex number : 9
//
//
//Enter the count of edges : 14
//
//
//Enter the links between the vertex :
//(The first two numbers are vertex, and the third number is the weight of the edge between them)
//
//0 1 4
//0 7 8
//1 2 8
//1 7 11
//2 3 7
//2 8 2
//2 5 4
//3 4 9
//3 5 14
//4 5 10
//5 6 2
//6 7 1
//6 8 6
//7 8 7
//
//Vertexes:   Edge Weight :
//
//6 -> 7    =     1
//2 -> 8    =     2
//5 -> 6    =     2
//0 -> 1    =     4
//2 -> 5    =     4
//2 -> 3    =     7
//0 -> 7    =     8
//3 -> 4    =     9
//
//Minimum spanning tree weight : 37
