#include <iostream>
#include <graph.h>

    /*Программа должна считывать параметры графа
    и искать для него минимальное покрывающее дерево алгоритмом Крускала.
    
    Вершины  1 2 3 4 5 6 = 6 рёбер 10
            1
        /   |   \
       2 -- 3 -- 4   
       |   / \   |
       |  /   \  |
        5       6
    
    1 3 = 1
    6 4 = 2
    2 5 = 3
    3 6 = 4
    1 4 = 5
    2 3 = 5
    3 4 = 5
    5 6 = 6
    5 3 = 6
    1 2 = 6
    Остово по Крускалу

            1
            |
    2   -   3
    |       |  
    5       6   -   4

    1 3 = 1
    4 6 = 2
    2 5 = 3
    3 6 = 4
    2 3 = 5 
    */

int main(){
    int vertex_amount = 6;
    int weight,vertex1,vertex2;
    graph* graph = create_graph(vertex_amount);
    for (auto i = 0; i<vertex_amount;++i){
        std::cin >> vertex1;
        std::cin >> vertex2;
        std::cin >> weight;
        graph_add_edge(graph,vertex1,vertex2,weight);
    }
    
    return 0;
}