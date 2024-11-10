#include <iostream>
#include <fstream>
#include <limits>
#include "../LibraryCPPTemplate/graph.h"
#include "../LibraryCPPTemplate/vector.h"

#define ERROR_VALUE std::numeric_limits<size_t>::max()

std::pair<unsigned int, Vector<std::string>> find_min_path(Graph<std::string, unsigned int> graph, size_t a, size_t b);
int init(Graph<std::string, unsigned int>& graph, std::ifstream& in);
void output(std::pair<unsigned int, Vector<std::string>> data);

int main(int argc, char** argv) {
    setlocale(0, "");
    std::string filepath = argv[1];
    std::ifstream in(filepath);

    if (!in.is_open()) {
        "Не удалось открыть файл\n";
        return 1;
    }

    Graph<std::string, unsigned int> graph;
    if (init(graph, in))
        return 1;

    size_t a = 0, b = 0;
    in >> a >> b;
    if (a == ERROR_VALUE || b == ERROR_VALUE) {
        std::cout << "Некорректные индексы для нахождения расстония\n";
        return 1;
    }
    output(find_min_path(graph, a, b));

    return 0;
}

std::pair<unsigned int, Vector<std::string>> find_min_path(Graph<std::string, unsigned int> graph, size_t a, size_t b) {

    return { 0, Vector<std::string>() };
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

void output(std::pair<unsigned int, Vector<std::string>> data) {
    std::cout << "Минимальное расстояние от " << data.second[0] << " до " << data.second[data.second.size() - 1] << " : " << data.first << '\n';
    std::cout << "Путь: ";
    for (size_t i = 0; i < data.second.size(); i++) {
        std::cout << data.second[i] << " ";
    }
    std::cout << '\n';
}