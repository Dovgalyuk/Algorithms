#include <iostream>
#include <vector>
#include <map>
#include "graph.h"

Graph* Prima(Graph* graph, Graph* prima){
    auto* Graph = graph;
    auto* Prima = prima;
    std::vector<Graph::Vertex*> vs;
    vs = Graph->GetVertices();
    std::map<int, std::unordered_set<Graph::Edge*>> E;
    std::vector<int> keys;
    for(auto it = E.begin(); it != E.end(); it++){
        keys.push_back(it->first);
    }
    while(keys.size() != vs.size()){

    }



    return Prima;
}

int main() {
	

    auto* graph = new Graph();
    std::vector<Graph::Vertex*> graph_vs;
    graph_vs.reserve(6);

    auto* prima = new Graph();

    for(int i = 1; i < 7; ++i){
        graph_vs.push_back(graph->AddVertex(i)); // точки лежат последовательно от 1 до 6;
        prima->AddVertex(i);
    }
    //std::cout << graph_vs.at(0)->GetData();
    //std::cout << graph_vs.at(1)->GetData();

    graph->AddEdge(*graph_vs.at(0), *graph_vs.at(1), 6 );// 1 -> 2 w:6
    graph->AddEdge(*graph_vs.at(1), *graph_vs.at(0), 6 );// 2 -> 1 w:6

    graph->AddEdge(*graph_vs.at(0), *graph_vs.at(3), 5 );// 1 -> 4 w:5
    graph->AddEdge(*graph_vs.at(3), *graph_vs.at(0), 5 );// 4 -> 1 w:5

    graph->AddEdge(*graph_vs.at(0), *graph_vs.at(2), 1 );// 1 -> 3 w:1
    graph->AddEdge(*graph_vs.at(2), *graph_vs.at(0), 1 );// 3 -> 1 w:1

    graph->AddEdge(*graph_vs.at(1), *graph_vs.at(2), 5);// 2 -> 3 w:5
    graph->AddEdge(*graph_vs.at(2), *graph_vs.at(1), 5);// 3 -> 2 w:5

    graph->AddEdge(*graph_vs.at(1), *graph_vs.at(4), 3 );// 2 -> 5 w:3
    graph->AddEdge(*graph_vs.at(4), *graph_vs.at(1), 3 );// 5 -> 2 w:3

    graph->AddEdge(*graph_vs.at(4), *graph_vs.at(2), 6);// 5 -> 3 w:6
    graph->AddEdge(*graph_vs.at(2), *graph_vs.at(4), 6);// 3 -> 5 w:6

    graph->AddEdge(*graph_vs.at(4), *graph_vs.at(5), 6);// 5 -> 6 w:6
    graph->AddEdge(*graph_vs.at(5), *graph_vs.at(4), 6);// 6 -> 5 w:6

    graph->AddEdge(*graph_vs.at(5), *graph_vs.at(2), 4);// 6 -> 3 w:4
    graph->AddEdge(*graph_vs.at(2), *graph_vs.at(5), 4);// 3 -> 6 w:4

    graph->AddEdge(*graph_vs.at(5), *graph_vs.at(3), 2);// 6 -> 4 w:3
    graph->AddEdge(*graph_vs.at(3), *graph_vs.at(5), 2);// 4 -> 6 w:3

    graph->AddEdge(*graph_vs.at(2), *graph_vs.at(3), 5);// 3 -> 4 w:5
    graph->AddEdge(*graph_vs.at(3), *graph_vs.at(2), 5);// 4 -> 3 w:5

    prima = Prima(graph, prima);



    return 0;
}