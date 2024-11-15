#include <iostream>
#include <fstream>
#include <limits>
#include <queue>

#include "../LibraryCPPTemplate/graph.h"
#include "../LibraryCPPTemplate/vector.h"

//#define output_path
#define ERROR_VALUE std::numeric_limits<size_t>::max()

size_t find_min_path(Graph<std::string, size_t>& graph, size_t start, size_t end);
int init(Graph<std::string, size_t>& graph, std::ifstream& in);

int main(int argc, char** argv) {
    setlocale(0, "");
    std::string filepath = argv[1];
    std::ifstream in(filepath);

    if (!in.is_open()) {
        std::cout << "File was not opened\n";
        return 1;
    }

    Graph<std::string, size_t> graph;
    if (init(graph, in))
        return 1;

    size_t a = 0, b = 0;
    in >> a >> b;
    if (a >= graph.get_vertices().size() || b >= graph.get_vertices().size()) {
        std::cout << "Invalid indexes\n";
        return 1;
    }

    std::cout << find_min_path(graph, a, b);
    //graph.~Graph();
    return 0;
}

size_t find_min_path(Graph<std::string, size_t>& graph, size_t start, size_t end) {
    Vector<unsigned int> distances(graph.get_vertices().size(), std::numeric_limits<unsigned int>::max());
    Vector<bool> visited(graph.get_vertices().size(), false); 

    using P = std::pair<unsigned int, size_t>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> queue;

    distances[start] = 0;
    queue.push({ 0, start });

    while (!queue.empty()) {
        size_t current = queue.top().second;
        queue.pop();

        if (visited[current]) {
            continue;
        }
        visited[current] = true;

        if (current == end)
            break;

        for (auto it = graph.begin(current); it != graph.end(current); ++it) {
            size_t neighbor_i = it.get_neib_index();
            size_t weight = (*it)->mark;

            unsigned int new_distance = distances[current] + weight;
            if (new_distance < distances[neighbor_i]) {
                distances[neighbor_i] = new_distance;
                queue.push({ new_distance, neighbor_i });
            }
        }
    }

    return distances[end];
}

int init(Graph<std::string, size_t>& graph, std::ifstream &in) {
    int k = 0;
    std::string temp = "";
    in >> k;
    if (k <= 0 || k > std::numeric_limits<int>::max()) {
        std::cout << "Invalid vertices quantity\n";
        return 1;
    }

    while (k) {
        in >> temp;
        if (temp == "") {
            std::cout << "Invalid vertex mark value\n";
            return 1;
        }
        graph.add_vertex(temp);
        k--;
    }

    size_t edge_mark = 0, a = 0, b = 0;
    in >> k;
    if (k <= 0 || k > std::numeric_limits<int>::max()) {
        std::cout << "Invalid edges quantity\n";
        return 1;
    }

    while (k) {
        in >> a >> b >> edge_mark;
        if (a == ERROR_VALUE || b == ERROR_VALUE || edge_mark == ERROR_VALUE) {
            std::cout << "Invalid indes or edge mark\n";
            return 1;
        }
        graph.add_edge(a, b, edge_mark);
        k--;
    }

    return 0;
}