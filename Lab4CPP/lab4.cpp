// Основной файл проекта, здесь main()

#include <iostream>
#include <queue>

typedef unsigned int uint;
typedef struct Vertex {
    uint degree = 0;
    uint mark = 0;
} Vertex;

#include "../LibraryCPPTemplate/vector.h"
#include "../LibraryCPPTemplate/graph.h"

int main() {
    setlocale(0, "");
    Graph<Vertex> graph;
    graph.add_vertex(0);
    graph.add_vertex(1);
    graph.add_vertex(2);
    Vector<int> res = graph.get_marks();
    for (size_t i = 0; i < res.size(); i++) {
        std::cout << res[i] << " ";
    }
    std::cout << std::endl;
	return 0;
}