#include "list.h"
#include "queue.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

struct Graph {
    int vertices;
    int** adjMatrix;
};

// Function to perform BFS and calculate distances
void bfs(const Graph& graph, int startVertex, std::vector<int>& distances) {
    Queue* queue = queue_create();
    
    // Initialize distances for all vertices as -1 (unreachable)
    for (int i = 0; i < graph.vertices; ++i) {
        distances[i] = -1;
    }
    distances[startVertex] = 0;
    
    // Insert the starting vertex into the queue
    queue_insert(queue, startVertex);
    
    while (!queue_empty(queue)) {
        int current = queue_get(queue);  // Get the current vertex
        queue_remove_one(queue);  // Remove it from the queue
        
        // Iterate over all adjacent vertices of the current vertex
        for (int i = 0; i < graph.vertices; ++i) {
            if (graph.adjMatrix[current][i] == 1 && distances[i] == -1) {
                // If the vertex is reachable and hasn't been visited
                distances[i] = distances[current] + 1;
                queue_insert(queue, i);  // Add it to the queue for further exploration
            }
        }
    }
    
    queue_delete(queue);
}

int main(int argc, char* argv[]) {
    // Reading input from a file
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }
    
    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);
    
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        return 1;
    }
    
    int vertices;
    inputFile >> vertices;
    
    // Create adjacency matrix
    int** adjMatrix = new int*[vertices];
    for (int i = 0; i < vertices; ++i) {
        adjMatrix[i] = new int[vertices];
        for (int j = 0; j < vertices; ++j) {
            inputFile >> adjMatrix[i][j];
        }
    }
    
    Graph graph = {vertices, adjMatrix};
    
    // Perform BFS from the first vertex (0)
    std::vector<int> distances(vertices, -1);
    bfs(graph, 0, distances);
    
    // Write output
    for (int i = 0; i < vertices; ++i) {
        outputFile << distances[i] << "\n";
    }
    
    // Clean up
    for (int i = 0; i < vertices; ++i) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
    
    inputFile.close();
    outputFile.close();
    
    return 0;
}
