#include <vector>
#include <stdexcept>
#include <map>
template <typename T>
class Graph {
private:
    std::vector<std::vector<int>> adjMatrix; 
    std::vector<T> vertices; 


public:
    Graph(int numVertices) {
        vertices.resize(numVertices);
        adjMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
    }

    void addEdge(int src, int dest, int weight) {
        if (src >= vertices.size() || dest >= vertices.size()) {
            throw std::out_of_range("Vertex does not exist");
        }
        adjMatrix[src][dest] = weight;
       
    }
    void setEdgeMark(int src, int dest, int weight) {
        if (src >= vertices.size() || dest >= vertices.size()) {
            throw std::out_of_range("Vertex does not exist");
        }
        adjMatrix[src][dest] = weight;

    }
    void addVertex(T data) {
      
        vertices.push_back(data);

       
        int numVertices = vertices.size();
        for (auto& row : adjMatrix) {
            row.resize(numVertices, 0);
        }
        adjMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
    }

    void removeEdge(int src, int dest) {
        if (src >= vertices.size() || dest >= vertices.size()) {
            throw std::out_of_range("Vertex does not exist");
        }
        adjMatrix[src][dest] = 0;
        adjMatrix[dest][src] = 0; 
    }

    bool EdgeExists(int src, int dest) const {
        if (src >= vertices.size() || dest >= vertices.size()) {
            throw std::out_of_range("Vertex does not exist");
        }
        return adjMatrix[src][dest] != 0;
    }

    int getEdgeWeight(int src, int dest) {
        if (src >= vertices.size() || dest >= vertices.size()) {
            throw std::out_of_range("Vertex does not exist");
        }
        return adjMatrix[src][dest];
    }

    void setVertexMark(int vertex, T data) {
        if (vertex >= vertices.size()) {
            throw std::out_of_range("Vertex does not exist");
        }
        vertices[vertex] = data;
    }

    T getVertexMark(int vertex) {
        if (vertex >= vertices.size()) {
            throw std::out_of_range("Vertex does not exist");
        }
        return vertices[vertex];
    }

    void removeVertex(int vertex) {
        if (vertex >= vertices.size()) {
            throw std::out_of_range("Vertex does not exist");
        }
        for (auto& row : adjMatrix) {
            row.erase(row.begin() + vertex);
        }
        adjMatrix.erase(adjMatrix.begin() + vertex);
        vertices.erase(vertices.begin() + vertex);
    }
   
  
    const std::vector<std::vector<int>>& getAdjMatrix() const {
        return adjMatrix;
    }

  
    const std::vector<T>& getVertices() const {
        return vertices;
    }
   
};
