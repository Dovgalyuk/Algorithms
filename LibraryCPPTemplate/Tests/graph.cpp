#include <iostream>
#include "graph.h"
#include <algorithm>

typedef Graph<int, int> MyGraph;

int main() {
    MyGraph graph(10);

    // Test 1: get all vertex mark
    std::vector<int> vertices = graph.get_all_vertex_marks();
    std::vector<int> ans1 (10);
    bool flag = 0;
    for(size_t i = 0; i < 10; i++) {
        if(ans1[i] != vertices[i]) {
            flag = 1;
            break;
        }
    }
    if(flag) {
        for (size_t i = 0; i < vertices.size(); ++i) {
            std::cout << vertices[i] << " ";
        }
        std::cout << "\nTest1: Incorrect graph\n";
        return 1;
    }
    
    // Test 2: Removing vertex
    graph.remove_vertex(9);
    std::vector<int> vertices2 = graph.get_all_vertex_marks();
    std::vector<int> ans2(9);
    for (size_t i = 0; i < vertices2.size(); ++i) {
        if(vertices2[i] != ans2[i]) {
            flag = 1;
            break;
        }
    }

    if(flag) {
        for (size_t i = 0; i < vertices2.size(); ++i) {
            std::cout << vertices2[i] << " ";
        }
        std::cout << "\nTest2: Incorrect graph\n";
        return 1;
    }

    //Test 3: Adding vertex
    graph.add_vertex();
    std::vector<int> vertices3 = graph.get_all_vertex_marks();
    std::vector<int> ans3(11);
    for (size_t i = 0; i < vertices3.size(); ++i) {
        if(vertices3[i] != ans3[i]) {
            flag = 1;
            break;
        }
    }
    if(flag) {
        for (size_t i = 0; i < vertices3.size(); ++i) {
            std::cout << vertices3[i] << " ";
        }
        std::cout << "\nTest3: Incorrect graph\n";
        return 1;
    }

    // Test 4: Adding edge
    graph.add_vertex();
    graph.add_edge(10, 9, -10);
    graph.add_edge(10, 1, -15);
    graph.add_edge(10, 2, 1000);

    if(!graph.has_edge(10, 9)) {
        std::cout << "\nTest4: Graph have not 20 --> 9 edge\n";
        for(auto it(graph.begin(10)); it != graph.end(10); ++it) {
            std::cout << "To: " << (*it).to << " Mark: " << (*it).mark <<  '\n';
        }
        return 1;
    }
    if(!graph.has_edge(10, 1)) {
        std::cout << "\nTest4: Graph have not 20 --> 1 edge\n";
        for(auto it(graph.begin(10)); it != graph.end(10); ++it) {
            std::cout << "To: " << (*it).to << " Mark: " << (*it).mark <<  '\n';
        }
        return 1;
    }
    if(!graph.has_edge(10, 2)) {
        std::cout << "\nTest4: Graph have not 20 --> 2 edge\n";
        for(auto it(graph.begin(10)); it != graph.end(10); ++it) {
            std::cout << "To: " << (*it).to << " Mark: " << (*it).mark <<  '\n';
        }
        return 1;
    }

    // Test 5: Removing edge
    graph.remove_edge(10, 1);
    if(graph.has_edge(2, 1)) {
        std::cout << "\nTest5: Graph have 20 --> 1 edge\n";
        for(auto it(graph.begin(10)); it != graph.end(10); ++it) {
            std::cout << "To: " << (*it).to << " Mark: " << (*it).mark <<  std::endl;
        }
        return 1;
    }

    // Test 6: Removing vertex
    graph.add_vertex();
    graph.add_edge(3, 4, -15);
    graph.remove_vertex(10);
    if(!graph.has_edge(3, 4)) {
        std::cout << "\nTest6: Graph have 10 --> 9 edge\n";
        for(auto it(graph.begin(9)); it != graph.end(9); ++it) {
            std::cout << "To: " << (*it).to << " Mark: " << (*it).mark <<  std::endl;
        }
        return 1;
    }

    // Test 7: Setting edge mark
    graph.add_vertex();
    graph.add_edge(1, 2, 1000);
    graph.set_edge_mark(1, 2, -100);
    if(graph.get_edge_mark(1, 2) != -100) {
        std::cout << "\nTest8: Graph edge mark:" << graph.get_edge_mark(1, 2) << '\n';
        return 1;
    }

    // Test 9: Getting vertex mark
    graph.set_vertex_mark(9, -10);
    if(graph.get_vertex_mark(9) != -10) {
        std::cout << "Test10: Graph mark: " << graph.get_vertex_mark(9);
    }

    return 0;
}