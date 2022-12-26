#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"

template<typename Data>
class Graph {
    public:
        Graph(size_t vertex_amount, Data vertex_data) {
            vertexes = new Vector<Vertex*>;
            vertexes->resize(vertex_amount);
            for(size_t i = 0; i < vertex_amount; i++) {
                vertexes->set(i, new Vertex(vertex_data));
            }
            edgeMatrix = new Vector<Edge*>;
            edgeMatrix->resize(vertex_amount * vertex_amount);

            for(size_t i = 0; i < edgeMatrix->size(); i++) {
                edgeMatrix->set(i, nullptr);
            }

        }

        ~Graph() {
            delete vertexes;
            delete edgeMatrix;
        }

        struct Vertex {
            private:
                Data vertex_data;
            public:
                Vertex(Data vertex_data) {
                    this->vertex_data = vertex_data;
                }
                void setVertexData(Data vertex_data) {
                    this->vertex_data = vertex_data;
                }
                Data getVertexData() {
                    return vertex_data;
                }
        };

        struct Edge {
            private:
                Data edge_data;
            public:
                Edge(Data edge_data) {
                    this->edge_data = edge_data;
                }
                void setEdgeData(Data edge_data) {
                    this->edge_data = edge_data;
                }
                Data getEdgeData() {
                    return edge_data;
                }
        };

        size_t getVertexAmount() {
            return vertexes->size();
        }

        struct Iterator {
            private: 
                Graph *graph;
                size_t start;
                int end = -1;

                int getNearVertexIndex() {
                    for(int i = end + 1; i < graph->getVertexAmount(); i++) {
                        if(graph->isEdgeExist(start, i)) {
                            return i;
                        }
                    }
                    return -1;
                }
            public:
                Iterator(Graph *graph, size_t start) {
                    this->graph = graph;
                    this->start = start;
                    this->end = getNearVertexIndex();
                }

                Vertex* operator *() {
                    if(end != -1) {
                        return graph->getVertex(end);
                    } else {
                        return nullptr;
                    }
                }

                void operator ++() {
                    end = getNearVertexIndex();
                }
        };

        Iterator getIterator(size_t start) {
            return Iterator(this, start);
        }

        size_t addVertex(Data vertex_data) {
            size_t index = vertexes->size();
            vertexes->resize(index+1);
            vertexes->set(index, new Vertex(vertex_data));
            size_t vertex_amount = getVertexAmount();

            Vector<Edge*> *buffMatrix = new Vector<Edge*>;
            buffMatrix->resize(vertex_amount * vertex_amount);
            for(size_t i = 0; i < vertex_amount; i++) {
                for(size_t j = 0; j < vertex_amount; j++) {
                    buffMatrix->set((i * vertex_amount) + j, edgeMatrix->get(i * index + j));
                }
            }

            delete edgeMatrix;
            edgeMatrix = buffMatrix;
            return index;
        }

        void removeVertex(size_t index) {
            size_t _vertex_amount = getVertexAmount();

            if(index >= _vertex_amount) {
                return;
            }

            Vertex *vertex = vertexes->get(index);
            delete vertex;
            for(size_t i = index; i < _vertex_amount-1; i++) {
                vertexes->set(i, vertexes->get(i + 1));
            }
            vertexes->resize(_vertex_amount-1);

            size_t vertex_amount = getVertexAmount();
            Vector<Edge*> *buffMatrix = new Vector<Edge*>;
            buffMatrix->resize(vertex_amount * vertex_amount);
            for(size_t i = 0; i < vertex_amount; i++) {
                for(size_t j = 0; j < vertex_amount; j++) {
                   Edge *edge = edgeMatrix->get(((i + (i >= index)) * _vertex_amount) + (j + (j >= index)));
                   buffMatrix->set((i * vertex_amount) + j, edge);
                }
            }
            delete edgeMatrix;
            edgeMatrix = buffMatrix;
        }

        Vertex* getVertex(size_t index) {
            return vertexes->get(index);
        }

        void addEdge(size_t from_vertex_index, size_t to_vertex_index, Data edge_data) {
            Edge *edge = new Edge(edge_data);
            edgeMatrix->set(from_vertex_index * getVertexAmount() + to_vertex_index, edge);
        }

        void removeEdge(size_t from_vertex_index, size_t to_vertex_index) {
             edgeMatrix->set(from_vertex_index * getVertexAmount() + to_vertex_index, nullptr);
        }

        Edge *getEdge(size_t start_vertex_index, size_t end_vertex_index) {
            size_t vertex_amount = getVertexAmount();
            return edgeMatrix->get(start_vertex_index * vertex_amount + end_vertex_index);
        }

        bool isEdgeExist(size_t start_vertex_index, size_t end_vertex_index) {
            return getEdge(start_vertex_index, end_vertex_index) != nullptr;
        }

        
    private: 
        Vector<Vertex*> *vertexes;
        Vector<Edge*> *edgeMatrix;
};

#endif
