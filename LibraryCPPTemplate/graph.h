// Файл с реализацией АТД граф (класс)

#ifndef GRAPH_H
#define GRAPH_H

typedef struct Vertex {

}Vertex;

template <typename Data>
class Graph {
   public:
       Graph() {

       }
    
       ~Graph() {

       }

       void add_vertex() {

       }

       void add_edge(Vertex a, Vertex b) {

       }

       void delete_vertex(Vertex a) {

       }

       void delete_edge(Vertex a, Vertex b) {

       }

       bool is_bounded(Vertex a, Vertex b) {

       }

       void add_mark(Vertex a) {

       }

       Vector get_marks() {

       }

   private:
       Vector<Vector<int>> relations;
       
};

#endif