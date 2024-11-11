#include <iostream>
#include <fstream>
#include <limits>
#include <queue>

#include "graph.h"
#include "vector.h"

#define ERROR_VALUE std::numeric_limits<size_t>::max()

std::pair<unsigned int, Vector<std::string>> find_min_path(Graph<std::string, unsigned int> graph, size_t a, size_t b);
int init(Graph<std::string, unsigned int>& graph, std::ifstream& in);
void output(std::pair<unsigned int, Vector<std::string>> data, std::string a, std::string b);

int main(int argc, char** argv) {
    setlocale(0, "");
    std::string filepath = argv[1];
    std::ifstream in(filepath);

    if (!in.is_open()) {
        std::cout << "Не удалось открыть файл\n";
        return 1;
    }

    Graph<std::string, unsigned int> graph;
    if (init(graph, in))
        return 1;

    size_t a = 0, b = 0;
    in >> a >> b;
    if (a >= graph.get_vertices().size() || b >= graph.get_vertices().size()) {
        std::cout << "Некорректные индексы для нахождения расстония\n";
        return 1;
    }
    output(find_min_path(graph, a, b), graph.get_vertices()[a].mark, graph.get_vertices()[b].mark);

    return 0;
}

std::pair<unsigned int, Vector<std::string>> find_min_path(Graph<std::string, unsigned int> graph, size_t start, size_t end) {
    Vector<unsigned int> distances(graph.get_vertices().size(), std::numeric_limits<unsigned int>::max());
    Vector<size_t> previous(graph.get_vertices().size(), ERROR_VALUE);

    using P = std::pair<unsigned int, size_t>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> queue;

    distances[start] = 0;
    queue.push({ 0, start });

    while (!queue.empty()) {
        size_t current = queue.top().second;
        queue.pop();

        if (current == end)
            break;

        for (auto it = graph.begin(current); it != graph.end(current); ++it) {
            size_t neighbor_i = (*it).number;
            unsigned int weight = graph.get_edge_mark(current, neighbor_i);

            unsigned int new_distance = distances[current] + weight;
            if (new_distance < distances[neighbor_i]) {
                distances[neighbor_i] = new_distance;
                previous[neighbor_i] = current;
                queue.push({ new_distance, neighbor_i });
            }
        }
    }

    // Восстановление пути
    Vector<std::string> path;
    for (size_t at = end; at != ERROR_VALUE; at = previous[at]) {
        path.push(graph.get_vertex_by_index(at).mark); // Предполагается, что есть метод get_mark
    }

    return { distances[end], path.reverse(0, path.size() - 1)};
}

int init(Graph<std::string, unsigned int>& graph, std::ifstream &in) {
    int k = 0;
    std::string temp = "";
    in >> k;
    if (k <= 0 || k > std::numeric_limits<int>::max()) {
        std::cout << "Некорректный количество вершин\n";
        return 1;
    }

    while (k) {
        in >> temp;
        if (temp == "") {
            std::cout << "Некорректное значение пометки вершины\n";
            return 1;
        }
        graph.add_vertex(temp);
        k--;
    }

    size_t edge_mark = 0, a = 0, b = 0;
    in >> k;
    if (k <= 0 || k > std::numeric_limits<int>::max()) {
        std::cout << "Некорректный количество ребер\n";
        return 1;
    }

    while (k) {
        if (a != -1) {
            in >> a >> b >> edge_mark;
            if (a == ERROR_VALUE || b == ERROR_VALUE || edge_mark == ERROR_VALUE) {
                std::cout << "Некорректный индекс или пометка ребра\n";
                return 1;
            }
            graph.add_edge(a, b, edge_mark);
        }
        k--;
    }

    return 0;
}

void output(std::pair<unsigned int, Vector<std::string>> data, std::string a, std::string b) {
    std::cout << "Минимальное расстояние от " << a << " до " << b << " : ";
    if(data.first != std::numeric_limits<unsigned int>::max())
        std::cout << data.first << '\n';
    else
        std::cout << "не определено" << '\n';

    std::cout << "Путь: ";

    if (data.first == std::numeric_limits<unsigned int>::max()) {
        std::cout << "не определен" << '\n';
        return;
    }

    for (size_t i = 0; i < data.second.size(); i++) {
        if(i != data.second.size() - 1)
            std::cout << data.second[i] << " -> ";
        else
            std::cout << data.second[i] << '\n';
    }
}