// Файл с реализацией АТД граф (класс)

#ifndef GRAPH_H
#define GRAPH_H

typedef struct Vertex {
    unsigned int degree = 0;
    unsigned int mark;
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
           relations[a.mark][a.mark] = 1;
       }

       void delete_vertex(Vertex a) {

       }

       void delete_edge(Vertex a, Vertex b) { 
           relations[a.mark][a.mark] = 0;
       }

       bool is_bounded(Vertex a, Vertex b) { 
           if (relations[a.mark][b.mark] == 1)
               return true;
           else
               return false;
       }

       void add_mark(Vertex a, unsigned int mark) { 
           a.mark = mark;
       }

       Vector get_marks() { if (1)
       }

   private:
       Vector<Vector<int>> relations;
       
};

#endif