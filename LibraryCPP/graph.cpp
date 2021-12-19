#include "graph.h"
#include "array.h"

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
};

void del_iterator(iterator* iter){
    delete iter;
}

void del_graph(graph* graph){
    delete graph;
}

void add_vertex(){

}

void add_edge(){

}

void remove_vertex(){

}

void remove_edge(){

}

void set_vertex(){

}

void set_edge(){

}

int get_vertex(){
    return;
}

int get_edge(){
    return;
}

bool Exists_edge(){
    return;
}

bool Neighboor_empty(){
    return;
}

bool Neighboor_next(){
    return;
}