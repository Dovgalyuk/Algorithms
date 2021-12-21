#include "graph.h"
#include "../LibraryCPP/array.h"

struct iterator
{
    int Neighboor = 0;
    graph* direct_graph;
    int vertex;

    iterator(int vertex){
        this->vertex = vertex;
    }

    ~iterator(){
        direct_graph = nullptr;
    }
};

struct graph
{
    struct  vertex
    {
        int label = -1;
    };
    
    struct edge
    {
        bool exists = 0;
        int label = -1;
    };

    Array* vertex_arr;
    vertex_arr* vertex_labels;
    Array* matrix_arr;
    matrix_arr* matrix;
    int vertex_amount;

    iterator* createIterator(int vertex){
        
    }

    directed_graph(int vertex_amount){

    }

    ~directed_graph(){

    }
};

void graph_del_iterator(iterator* iter){
    delete iter;
}

void graph_del_graph(graph* graph){
    delete graph;
}

void graph_add_vertex(){

}

void graph_add_edge(){

}

void graph_remove_vertex(){

}

void graph_remove_edge(){

}

void graph_set_vertex(){

}

void graph_set_edge(){

}

int graph_get_vertex(){
    return;
}

int graph_get_edge(){
    return;
}

bool graph_Exists_edge(){
    return;
}

bool graph_Neighboor_empty(){
    return;
}

bool graph_Neighboor_next(){
    return;
}