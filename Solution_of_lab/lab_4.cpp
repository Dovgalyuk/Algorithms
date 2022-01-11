#include "d_graph.h"
#include <vector>
#include <climits>
#include <string>
#include <iostream>
#include <algorithm>

    struct Kruskal {
        d_graph<int>::Vertex* start = nullptr; //вершина начала для ребра
        d_graph<int>::Vertex* end = nullptr; //вершина конца для ребра
        int weight = 0; //вес ребра
    };

    bool sortByWeight(const Kruskal& first, const Kruskal& second) {
        return first.weight < second.weight;
    }

    int main() {
    int VertexCount = 7; 
    //инициализируем дерево
    d_graph<int> graph(VertexCount);
    graph.setEdgetoVertex(0, 1, 125);
    graph.setEdgetoVertex(0, 3, 225);
    graph.setEdgetoVertex(1, 2, 15);
    graph.setEdgetoVertex(1, 4, 6);
    graph.setEdgetoVertex(2, 4, 11);
    graph.setEdgetoVertex(4, 3, 12);
    graph.setEdgetoVertex(3, 1, 23);
    graph.setEdgetoVertex(2, 5, 3);
    graph.setEdgetoVertex(6, 4, 2);

    //graph.show(); //выводим матрицу смежности для него
   
    std::vector<Kruskal> Edges_kruskal; //вектор рёбер

    //иницализируем его множеством ребер из дерева
    for (int i = 0; i < VertexCount; i++) {
        d_graph<int>::EdgesIterator iterator(graph, graph.getVertex(i));
        for (size_t j = 0; j < VertexCount; j++) {
            if (++iterator) {
                Kruskal edge_kruskal;
                edge_kruskal.weight = iterator.getWeight();
                edge_kruskal.start = iterator.getIt();
                edge_kruskal.end = iterator.getCurrent();
                Edges_kruskal.push_back(edge_kruskal);
            }
        }
    }
    // сортируем все полученные ребра по возрастанию
    sort(Edges_kruskal.begin(), Edges_kruskal.end(), sortByWeight);
    

    
    //множество векторов ребер 
    std::vector<std::vector<Kruskal>> Used_Vertex;

    //иницализируем первый элемент
    std::vector<Kruskal> v;
    v.push_back(Edges_kruskal[0]);
    Used_Vertex.push_back(v);

    for (size_t i = 0; i < Edges_kruskal.size(); i++) {
        bool find_start = false;
        bool find_end = false;
        size_t current_multy_start = -1; //номер множества где нашли начало ребра
        size_t current_multy_end = -1; //номер множества где нашли конца ребра
        bool different_mylty = false; 

        for (size_t j = 0; j < Used_Vertex.size(); j++) {
            for (size_t l = 0; l < Used_Vertex[j].size(); l++) {
        
                if (Edges_kruskal[i].start == Used_Vertex[j][l].start || Edges_kruskal[i].start == Used_Vertex[j][l].end) {
                    current_multy_start = j;
                    find_start = true;
                }

                if (Edges_kruskal[i].end == Used_Vertex[j][l].end || Edges_kruskal[i].end == Used_Vertex[j][l].start) {
                    find_end = true;
                    current_multy_end = j;
                }

            }
        }
        // в разных ли множествах концы ребра нашлись
        if (current_multy_start != -1 && current_multy_end !=-1 && current_multy_start != current_multy_end) {
            different_mylty = true;
        }
        // нет концов ребер => создание нового множества ребер
        if (!find_start && !find_end) {
            std::vector<Kruskal> v;
            Edges_kruskal[i].start->data = Edges_kruskal[i].weight;
            Edges_kruskal[i].end->data = Edges_kruskal[i].weight;
            v.push_back(Edges_kruskal[i]);
            Used_Vertex.push_back(v);
        }
        // есть начало ребра и конец но находятся в разных множествах => объединение множеств 
        else if (different_mylty) {

            Used_Vertex[current_multy_start].insert(Used_Vertex[current_multy_start].end(), Used_Vertex[current_multy_end].begin(), (Used_Vertex[current_multy_end].end()));
            Used_Vertex[current_multy_end].clear();
            Edges_kruskal[i].end->data = Edges_kruskal[i].weight;
            Used_Vertex[current_multy_start].push_back(Edges_kruskal[i]);  
        
        }
        //если оба конца нашлись в одном множестве то ребро не нужно 
        else if (find_start && find_end) {
            continue;
        }
        //если нашелся конец то добавляем вершину начала в множество использованных вершин
        else if (find_start) {
            Edges_kruskal[i].end->data = Edges_kruskal[i].weight;
            Used_Vertex[current_multy_start].push_back(Edges_kruskal[i]);

        }
        //если нашлось начало то добавляем вершину конца в множество использованных вершин
        else if (find_end) {
            Edges_kruskal[i].start->data = Edges_kruskal[i].weight;
            Used_Vertex[current_multy_end].push_back(Edges_kruskal[i]);
        }
    }

    d_graph<int> graph_result(VertexCount);

    //вывод множества вершин для остовного дерева
    for (size_t j = 0; j < Used_Vertex.size(); j++) {
        for (size_t l = 0; l < Used_Vertex[j].size(); l++) {
            /*
            //Вывод информации о ребрах остовного дерева
            std::cout << "start: " << graph.getVertexIndex(Used_Vertex[j][l].start) << std::endl;
            std::cout << "end:   " << graph.getVertexIndex(Used_Vertex[j][l].end) << std::endl;
            std::cout << "weight: " << Used_Vertex[j][l].weight << std::endl << std::endl;
            */
            //иницализация дерева ребрами
            graph_result.setEdgetoVertex(graph.getVertexIndex(Used_Vertex[j][l].start), graph.getVertexIndex(Used_Vertex[j][l].end), Used_Vertex[j][l].weight); 
        }
    } 
    //вывод результата
    graph_result.show();
   
    return 0;
    } 