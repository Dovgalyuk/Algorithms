#include "graph.h"
#include <string>
#include <limits>
#include <stdexcept>
#include <iostream>
#include <fstream>

using namespace std;

bool find_path(
    const Graph<string, long long> &residual,
    size_t current,
    size_t sink,
    Vector<bool> &visited,
    Vector<size_t> &parent)
{
    visited.set(current, true);

    if (current == sink) return true;

    for (auto it = residual.neighbors(current); it.valid(); it.next()) {
        size_t next = it.get();

        if (visited.get(next)) continue;
        if (residual.get_edge(current, next) <= 0) continue;

        parent.set(next, current);

        if (find_path(residual, next, sink, visited, parent))
            return true;
    }

    return false;
}

long long max_flow(
    const Graph<string, long long> &graph,
    size_t source,
    size_t sink){
    if (source >= graph.size() || sink >= graph.size()) {
        throw out_of_range("wrong vertex index");
    }
    if (source == sink) {
        throw invalid_argument("source and sink are the same");
    }
    Graph<string, long long> residual = graph;
    for (size_t from = 0; from < graph.size(); from++) {
        for (auto it = graph.neighbors(from); it.valid(); it.next()) {
            size_t to = it.get();
            if (graph.get_edge(from, to) < 0) {
                throw invalid_argument("negative capacity");
            }
            if (!residual.has_edge(to, from)) {
                residual.add_edge(to, from, 0);
            }
        }
    }
    long long flow = 0;
    while (true) {
        Vector<bool> visited;
        Vector<size_t> parent;
        visited.resize(graph.size());
        parent.resize(graph.size());
        if (!find_path(residual, source, sink, visited, parent))
            break;
        long long extra = numeric_limits<long long>::max();
        for (size_t to = sink; to != source; to = parent.get(to)) {
            size_t from = parent.get(to);
            long long capacity = residual.get_edge(from, to);
            if (capacity < extra) extra = capacity;
        }
        if (flow > numeric_limits<long long>::max() - extra) {
            throw overflow_error("flow is too big");
        }
        for (size_t to = sink; to != source; to = parent.get(to)) {
            size_t from = parent.get(to);
            long long forward = residual.get_edge(from, to);
            long long backward = residual.get_edge(to, from);
            if (backward > numeric_limits<long long>::max() - extra) {
                throw overflow_error("residual capacity is too big");
            }
            residual.set_edge(from, to, forward - extra);
            residual.set_edge(to, from, backward + extra);
        }
        flow += extra;
    }
    return flow;
}

int main(int argc, char **argv){
    if (argc != 2) {
        cerr << "give filename as argument\n";
        return 1;
    }
    try {
        ifstream input(argv[1]);
        if (!input) {
            cerr << "file failed to open\n";
            return 1;
        }
        Graph<string, long long> graph;
        graph.read(input);
        string source;
        string sink;
        if (!(input >> source >> sink)) {
            throw runtime_error("cant read source and sink");
        }
        size_t from = graph.find_vertex(source);
        size_t to = graph.find_vertex(sink);
        cout << max_flow(graph, from, to) << '\n';
    }
    catch (const exception &error) {
        cerr << error.what() << '\n';
        return 1;
    }
    return 0;
}