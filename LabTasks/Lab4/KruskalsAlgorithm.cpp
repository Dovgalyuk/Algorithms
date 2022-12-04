#include "KruskalsAlgorithm.hpp"

struct KruskalsAlgorithm::Edge {
    size_t start;
    size_t end;
    int weight;
};

void KruskalsAlgorithm::getAllEdges() {
    size_t vertex_amount = graph->getVertexAmount();
    for(size_t i = 0; i < vertex_amount; i++) {
        auto it = graph->getIterator(i);
        while(*it != nullptr) {
            size_t start = graph->getVertex(i)->getVertexData();
            size_t end = (*it)->getVertexData();
            edges.push_back({start, end, graph->getEdge(start, end)->getEdgeData()});
            ++it;
        }
    }
}

KruskalsAlgorithm::KruskalsAlgorithm(Graph<int> *graph) {
    this->graph = graph;
    mst = new Graph<int>(graph->getVertexAmount(), 0);
    // Установка вершинам метки = порядку вершины
    for(size_t i = 0; i < mst->getVertexAmount(); i++) {
        mst->getVertex(i)->setVertexData(i);
    }

    getAllEdges();
}

KruskalsAlgorithm::~KruskalsAlgorithm() {
    delete graph;
    delete mst;
}

void KruskalsAlgorithm::run() {
    // Сортировка ребер по весу
    std::sort(edges.begin(), edges.end(), [](Edge a, Edge b) { return (a.weight < b.weight); });

    for(size_t i = 0; i < edges.size(); i++) {
        size_t start_vertex = edges[i].start;
        size_t end_vertex = edges[i].end;

        int start_data = graph->getVertex(start_vertex)->getVertexData();
        int end_data = graph->getVertex(end_vertex)->getVertexData();
        // Вершины не принадлежат одному и тому же множеству
        if(start_data != end_data) {
            mst->addEdge(start_vertex, end_vertex, edges[i].weight);

            for(size_t i = 0; i < graph->getVertexAmount(); i++) {
                // Вершины помещаются в одно множество
                if(graph->getVertex(i)->getVertexData() == end_data) {
                    graph->getVertex(i)->setVertexData(start_data);
                }
            }
        }
    }
}

void KruskalsAlgorithm::printResult() {
    std::cout << "== Result ==" << std::endl;
    size_t vertex_amount = mst->getVertexAmount();
    for(size_t i = 0; i < vertex_amount; i++) {
        auto it = mst->getIterator(i);
        while(*it != nullptr) {
            size_t start = mst->getVertex(i)->getVertexData();
            size_t end = (*it)->getVertexData();
            if(mst->isEdgeExist(start, end)) {
                std::cout << "Edge[weight " << mst->getEdge(start, end)->getEdgeData() << "]: (" << start << ")<->(" << end << ")" << std::endl;
            }
            ++it;
        }
    }
}