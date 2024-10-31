#include <iostream>
#include "graph.h"
#include <algorithm>

typedef Graph<int, int> MyGraph;

int main() {
    MyGraph graph(10);

    // Test 1: get all vertex mark
    std::vector<int> vertices = graph.get_all_vertex_marks();
    std::vector<int> ans1 {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
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
    graph.remove_vertex(10);
    vertices = graph.get_all_vertex_marks();
    std::vector<int> ans2{9, 8, 7, 6, 5, 4, 3, 2, 1};
    for (size_t i = 0; i < vertices.size(); ++i) {
        if(vertices[i] != ans2[i]) {
            flag = 1;
            break;
        }
    }

    if(flag) {
        for (size_t i = 0; i < vertices.size(); ++i) {
            std::cout << vertices[i] << " ";
        }
        std::cout << "\nTest2: Incorrect graph\n";
        return 1;
    }

    //Test 3: Adding vertex
    graph.add_vertex(20);
    vertices = graph.get_all_vertex_marks();
    std::vector<int> ans3{1, 2, 3, 4, 5, 6, 7, 8, 9, 20};
    std::sort(vertices.begin(), vertices.end());
    for (size_t i = 0; i < vertices.size(); ++i) {
        if(vertices[i] != ans3[i]) {
            flag = 1;
            break;
        }
    }
    if(flag) {
        for (size_t i = 0; i < vertices.size(); ++i) {
            std::cout << vertices[i] << " ";
        }
        std::cout << "\nTest3: Incorrect graph\n";
        return 1;
    }

    // Test 4: Adding edge
    graph.add_edge(20, 9, -10);
    graph.add_edge(20, 1, -15);
    graph.add_edge(20, 2, 1000);

    if(!graph.has_edge(20, 9)) {
        std::cout << "\nTest4: Graph have not 20 --> 9 edge\n";
        for(auto it(graph.begin(20)); it != graph.end(20); ++it) {
            std::cout << "To: " << (*it).to << " Mark: " << (*it).mark <<  '\n';
        }
        return 1;
    }
    if(!graph.has_edge(20, 1)) {
        std::cout << "\nTest4: Graph have not 20 --> 1 edge\n";
        for(auto it(graph.begin(20)); it != graph.end(20); ++it) {
            std::cout << "To: " << (*it).to << " Mark: " << (*it).mark <<  '\n';
        }
        return 1;
    }
    if(!graph.has_edge(20, 2)) {
        std::cout << "\nTest4: Graph have not 20 --> 2 edge\n";
        for(auto it(graph.begin(20)); it != graph.end(20); ++it) {
            std::cout << "To: " << (*it).to << " Mark: " << (*it).mark <<  '\n';
        }
        return 1;
    }

    // Test 5: Removing edge
    graph.remove_edge(20, 1);
    if(graph.has_edge(20, 1)) {
        std::cout << "\nTest5: Graph have 20 --> 1 edge\n";
        for(auto it(graph.begin(20)); it != graph.end(20); ++it) {
            std::cout << "To: " << (*it).to << " Mark: " << (*it).mark <<  std::endl;
        }
        return 1;
    }

    // Test 6: Removing vertex
    graph.add_edge(20, 1, -15);
    graph.remove_vertex(9);
    if(graph.has_edge(20, 9)) {
        std::cout << "\nTest6: Graph have 20 --> 9 edge\n";
        for(auto it(graph.begin(20)); it != graph.end(20); ++it) {
            std::cout << "To: " << (*it).to << " Mark: " << (*it).mark <<  std::endl;
        }
        return 1;
    }
    
    // Test 7: Getting edge mark
    if(graph.get_edge_mark(20, 2) != 1000) {
        std::cout << "\nTest7: Graph edge mark: " << graph.get_edge_mark(20, 2) << '\n'; 
        return 1;
    }

    // Test 8: Setting edge mark
    graph.set_edge_mark(20, 2, -100);
    if(graph.get_edge_mark(20, 2) != -100) {
        std::cout << "\nTest8: Graph edge mark:" << graph.get_edge_mark(20, 2) << '\n';
        return 1;
    }
    
    // Test 9: Setting vertex mark
    graph.set_vertex_mark(20, -10);
    graph.set_vertex_mark(2, 3);
    if(!graph.has_edge(-10, 3)) {
        std::cout << "\nTest9: Graph have -10 --> 3 edge\n";
        for(auto it(graph.begin(-10)); it != graph.end(-10); ++it) {
            std::cout << "To: " << (*it).to << " Mark: " << (*it).mark <<  std::endl;
        }
        return 1;
    }

    // Test 10: Getting vertex mark
    if(graph.get_vertex_mark(-10) != -10) {
        std::cout << "Test10: Graph mark: " << graph.get_vertex_mark(-10);
    }

    return 0;
}