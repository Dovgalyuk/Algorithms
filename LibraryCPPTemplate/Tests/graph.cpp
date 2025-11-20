#include <iostream>
#include <string>
#include "graph.h"

typedef Graph<std::string, int> MyGraph;

int main()
{
    MyGraph* graph = new MyGraph(3);
    
    if (!graph)
    {
        std::cout << "Graph creation error\n";
        return 1;
    }

    std::string tag1 = "Vertex A";
    std::string tag2 = "Vertex B";
    std::string tag3 = "Vertex C";
    
    graph->setVertexTag(0, tag1);
    graph->setVertexTag(1, tag2);
    graph->setVertexTag(2, tag3);

    if (graph->getVertexTag(0) != "Vertex A")
    {
        std::cout << "setVertexTag/getVertexTag error\n";
        return 1;
    }

    MyGraph::Edge edge1(0, 1);
    MyGraph::Edge edge2(1, 2);
    MyGraph::Edge edge3(0, 2);
    
    graph->addEdge(edge1);
    graph->addEdge(edge2);
    graph->addEdge(edge3);

    if (!graph->hasEdge(edge1))
    {
        std::cout << "addEdge/hasEdge error\n";
        return 1;
    }

    graph->setEdgeTag(edge1, 10);
    graph->setEdgeTag(edge2, 20);
    graph->setEdgeTag(edge3, 30);

    if (graph->getEdgeTag(edge1) != 10)
    {
        std::cout << "setEdgeTag/getEdgeTag error\n";
        return 1;
    }

    int neighbor_count = 0;
    MyGraph::Iterator end_iter = graph->end(0);
    for (MyGraph::Iterator it = graph->begin(0); it != end_iter; ++it)
    {
        neighbor_count++;
    }
    
    if (neighbor_count != 2) 
    {
        std::cout << "iterator error - wrong neighbor count\n";
        return 1;
    }

    graph->addVertex();
    std::string tag4 = "Vertex D";
    graph->setVertexTag(3, tag4);

    if (graph->getVertexTag(3) != "Vertex D")
    {
        std::cout << "addVertex error\n";
        return 1;
    }

    MyGraph::Edge edge4(2, 3);
    graph->addEdge(edge4);
    
    if (!graph->hasEdge(edge4))
    {
        std::cout << "addEdge to new vertex error\n";
        return 1;
    }

    graph->removeEdge(edge3);
    
    if (graph->hasEdge(edge3))
    {
        std::cout << "removeEdge error\n";
        return 1;
    }

    auto vertex_tags = graph->getVertexTags();
    if (vertex_tags.size() != 4)
    {
        std::cout << "getVertexTags error\n";
        return 1;
    }

    graph->removeVertex(1);
    
    if (graph->hasEdge(edge1) || graph->hasEdge(edge2))
    {
        std::cout << "removeVertex error - edges not removed\n";
        return 1;
    }

    MyGraph graph2(*graph);

    if (graph2.getVertexTag(0) != graph->getVertexTag(0))
    {
        std::cout << "copy constructor error\n";
        return 1;
    }

    delete graph;
}