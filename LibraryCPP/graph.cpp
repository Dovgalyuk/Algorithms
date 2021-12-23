#include "graph.h"
#include "../LibraryCPPTemplate/array.h"
#include <cmath>
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

    typedef Array<vertex> vertex_array;
    vertex_array* vertex_labels;
    
    typedef Array<edge> matrix_array;
    matrix_array* matrix;
    int vertex_amount;

    iterator* createIterator(int vertex){
        iterator* iter = new iterator(vertex);
        iter->direct_graph = this;
        return iter;
    }

    graph(int vertex_amount){
        vertex_labels=new vertex_array(vertex_amount);
        matrix = new matrix_array(std::pow(vertex_amount,2));
        this->vertex_amount = vertex_amount;
    }

    ~graph(){
        delete vertex_labels;
        delete matrix;
    }
};

graph* create_graph(int vertex_amount){
    return new graph(vertex_amount);
}

iterator* new_iterator(graph* dir_graph,int vertex){
    return dir_graph->createIterator(vertex);
}

void graph_del_iterator(iterator* iter){
    delete iter;
}

void graph_del_graph(graph* graph){
    delete graph;
}

void graph_add_vertex(struct graph * dir_graph)
{
    typedef Array<graph::vertex> vertex_arr;
    vertex_arr* vertex_labels = new vertex_arr(dir_graph->vertex_amount + 1);

    typedef Array<graph::edge> matrix_array;
    matrix_array* matrix = new matrix_array(std::pow(dir_graph->vertex_amount+1,2));
    
    for (auto i=0;i<dir_graph->vertex_amount;++i)
        vertex_labels->set(i,dir_graph->vertex_labels->get(i));
    
    for (auto i=0,j=0;i<std::pow(dir_graph->vertex_amount,2);++j){
        for(auto z=0;z<dir_graph->vertex_amount;++z){
            matrix->set(i+j,dir_graph->matrix->get(i));
            ++i;
        }
    }
    dir_graph->matrix = matrix;
    dir_graph->vertex_labels=vertex_labels;
    ++dir_graph->vertex_amount;
}

void graph_add_edge(graph*dir_graph,int vertex_1,int vertex_2){
    if ((vertex_1*dir_graph->vertex_amount)+vertex_2 < std::pow(dir_graph->vertex_amount,2)){
        graph::edge* edge = new graph::edge;
        edge->label = dir_graph->matrix->get((vertex_1*dir_graph->vertex_amount)+vertex_2).label;
        edge->exists = 1;
        dir_graph->matrix->set(((vertex_1*dir_graph->vertex_amount)+vertex_2), *edge);
    }
}

void graph_remove_vertex(struct graph* dir_graph,int vertex){
    if (vertex < dir_graph->vertex_amount && dir_graph->vertex_amount >1){
        typedef Array<graph::vertex> vertex_array;
        vertex_array* vertex_labels = new vertex_array(dir_graph->vertex_amount-1);
        typedef Array<graph::edge> matrix_array;
        matrix_array* matrix = new matrix_array(std::pow(dir_graph->vertex_amount-1,2));
        
        for(auto i=0,j=0;i<dir_graph->vertex_amount;++i){
            if(i!=vertex){
                vertex_labels->set(j,dir_graph->vertex_labels->get(i));
                ++j;
            }
        }

        for(auto i=0,j=0;i<std::pow(dir_graph->vertex_amount,2);++i){
            if(i/dir_graph->vertex_amount != vertex && i - (i/dir_graph->vertex_amount) * dir_graph->vertex_amount !=vertex){
                matrix->set(j,dir_graph->matrix->get(i));
                ++j;
            }
        }
        dir_graph->matrix = matrix;
        dir_graph->vertex_labels = vertex_labels;
        --dir_graph->vertex_amount;
    }
}

void graph_remove_edge(graph*dir_graph,int vertex_1,int vertex_2){
    if (vertex_1<dir_graph->vertex_amount && vertex_2 < dir_graph->vertex_amount){
        graph::edge * edge =new graph::edge;
        edge->label = dir_graph->matrix->get((vertex_1*dir_graph->vertex_amount)+vertex_2).label;
        edge->exists=0;
        dir_graph->matrix->set(((vertex_1 * dir_graph->vertex_amount) + vertex_2), *edge);
    }
}

void graph_set_vertex(graph* dir_graph,int vertex_index,int vertex_label){
    if(vertex_index<dir_graph->vertex_amount){
        graph::vertex* vertex = new graph::vertex;
        vertex->label = vertex_label;
        dir_graph->vertex_labels->set(vertex_label,*vertex);
    }
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