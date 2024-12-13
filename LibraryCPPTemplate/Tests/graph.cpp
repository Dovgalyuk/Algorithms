#include "graph.h"
#include "vector.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <limits>

int main() {
    GraphStructure<std::string, std::string>::StructureType structureType = GraphStructure<std::string, std::string>::StructureType::Directed;

    // Проверка количества узлов
    GraphStructure<std::string, std::string> graph(structureType);
    graph.addNode("A");
    graph.addNode("B");
    graph.addNode("C");
    graph.addNode("D");
    graph.addNode("E");

    if (graph.getNodeCount() != 5) {
        std::cout << "Invalid node count\n" << std::endl;
        return 1;
    } else {
        std::cout << "Correct number of nodes\n" << std::endl;
    }

    // Тестирование итератора и добавление соединений
    graph.addConnection(0, 1, "m");
    graph.addConnection(1, 2, "f");
    graph.addConnection(2, 3, "s");
    graph.addConnection(1, 3, "o");
    graph.addConnection(3, 0, "t");
    graph.addConnection(3, 4, "e");

    for (size_t node = 0; node < graph.getNodeCount(); ++node) {
        GraphStructure<std::string, std::string>::Iterator it = graph.getIterator(node);
        std::set<int> actual;

        while (it.hasNext()) {
            actual.insert(static_cast<int>(it.next()));
        }

        std::set<int> expected;
        if (node == 0) {
            expected = { 1 };
        } else if (node == 1) {
            expected = { 2, 3 };
        } else if (node == 2) {
            expected = { 3 };
        } else if (node == 3) {
            expected = { 0, 4 };
        } else if (node == 4) {
            expected = {};
        }

        if (actual == expected) {
            std::cout << "Test passed for node " << node << ": ";
            for (int v : actual) {
                std::cout << v << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "Test failed for node " << node << ": expected { ";
            for (int v : expected) {
                std::cout << v << " ";
            }
            std::cout << "} but got { ";
            for (int v : actual) {
                std::cout << v << " ";
            }
            std::cout << "}" << std::endl;
            return 1;
        }
    }

    // Проверка удаления соединения
    graph.removeConnection(1, 2);
    for (size_t node = 0; node < graph.getNodeCount(); ++node) {
        GraphStructure<std::string, std::string>::Iterator it = graph.getIterator(node);
        std::set<int> actual;

        while (it.hasNext()) {
            actual.insert(static_cast<int>(it.next()));
        }

        std::set<int> expected;
        if (node == 0) {
            expected = { 1 };
        } else if (node == 1) {
            expected = { 3 };
        } else if (node == 2) {
            expected = { 3 };
        } else if (node == 3) {
            expected = { 0, 4 };
        } else if (node == 4) {
            expected = {};
        }

        if (actual == expected) {
            std::cout << "Post-removal test passed for node " << node << ": ";
            for (int v : actual) {
                std::cout << v << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "Post-removal test failed for node " << node << ": expected { ";
            for (int v : expected) {
                std::cout << v << " ";
            }
            std::cout << "} but got { ";
            for (int v : actual) {
                std::cout << v << " ";
            }
            std::cout << "}" << std::endl;
            return 1;
        }
    }

    // Проверка удаления узла
    int indexToRemove = 3;
    std::cout << "Deleting a node with index: " << indexToRemove << std::endl;
    graph.removeNode(indexToRemove);
    if (graph.getNodeCount() != 4) {
        std::cout << "Invalid node deletion" << std::endl;
       
        return 1;
    } else {
        std::cout << "Valid node removal" << std::endl;
    }

    return 0;
}
