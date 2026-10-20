#include "graph.h"
#include <fstream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

struct Candidate
{
    int edge_weight;
    std::string from_vertex;
    std::string to_vertex;
};

struct CandidateGreater
{
    bool operator()(const Candidate &first_edge, const Candidate &second_edge) const
    {
        if (first_edge.edge_weight != second_edge.edge_weight) return first_edge.edge_weight > second_edge.edge_weight;
        if (first_edge.from_vertex != second_edge.from_vertex) return first_edge.from_vertex > second_edge.from_vertex;
        return first_edge.to_vertex > second_edge.to_vertex;
    }
};

using GraphType = Graph<int, std::string>;
using EdgeQueue = std::priority_queue<Candidate, std::vector<Candidate>, CandidateGreater>;

bool add_or_lower_edge(GraphType &graph, const std::string &from_vertex, const std::string &to_vertex, int edge_weight)
{
    int previous_weight;
    if (!graph.get_edge_label(from_vertex, to_vertex, previous_weight))
        return graph.add_edge(from_vertex, to_vertex, edge_weight);
    if (edge_weight < previous_weight)
        return graph.set_edge_label(from_vertex, to_vertex, edge_weight);
    return true;
}

void add_candidates(const GraphType &graph, const std::string &current_vertex, const std::unordered_set<std::string> &visited_vertices, EdgeQueue &edge_queue)
{
    GraphType::NeighborIterator neighbor_iterator = graph.neighbors_begin(current_vertex);
    while (neighbor_iterator.hasNext())
    {
        const std::string to_vertex = neighbor_iterator.next();
        if (visited_vertices.count(to_vertex)) continue;
        int edge_weight;
        if (graph.get_edge_label(current_vertex, to_vertex, edge_weight))
            edge_queue.push({edge_weight, current_vertex, to_vertex});
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3) return 1;

    std::ifstream input_file(argv[1]);
    std::ofstream output_file(argv[2], std::ios::binary);
    if (!input_file || !output_file) return 1;

    std::size_t vertex_count, edge_count;
    if (!(input_file >> vertex_count >> edge_count))
    {
        output_file << "Invalid input\n";
        return 1;
    }

    GraphType graph;
    for (std::size_t i = 0; i < vertex_count; ++i)
    {
        std::string vertex_name;
        if (!(input_file >> vertex_name) || !graph.add_vertex(vertex_name, vertex_name))
        {
            output_file << "Invalid input\n";
            return 1;
        }
    }
    for (std::size_t i = 0; i < edge_count; ++i)
    {
        std::string from_vertex, to_vertex;
        int edge_weight;
        if (!(input_file >> from_vertex >> to_vertex >> edge_weight) || !graph.has_vertex(from_vertex) || !graph.has_vertex(to_vertex) ||
            !add_or_lower_edge(graph, from_vertex, to_vertex, edge_weight) ||
            !add_or_lower_edge(graph, to_vertex, from_vertex, edge_weight))
        {
            output_file << "Invalid input\n";
            return 1;
        }
    }

    if (vertex_count == 0)
    {
        output_file << "No spanning tree\n";
        return 0;
    }

    const Vector<std::string> vertex_names = graph.vertex_labels();
    const std::string start_vertex = vertex_names.get(0);
    std::unordered_set<std::string> visited_vertices{start_vertex};
    EdgeQueue edge_queue;
    std::vector<Candidate> tree_edges;
    add_candidates(graph, start_vertex, visited_vertices, edge_queue);

    while (!edge_queue.empty() && tree_edges.size() + 1 < vertex_count)
    {
        const Candidate candidate_edge = edge_queue.top();
        edge_queue.pop();
        if (visited_vertices.count(candidate_edge.to_vertex))
            continue;
        visited_vertices.insert(candidate_edge.to_vertex);
        tree_edges.push_back(candidate_edge);
        add_candidates(graph, candidate_edge.to_vertex, visited_vertices, edge_queue);
    }

    if (tree_edges.size() + 1 != vertex_count)
    {
        output_file << "No spanning tree\n";
        return 0;
    }

    for (const Candidate &candidate_edge : tree_edges)
        output_file << candidate_edge.from_vertex << " - " << candidate_edge.to_vertex << " (" << candidate_edge.edge_weight << ")\n";
    return 0;
}

