// Файл с классом итератора

#ifndef ITERETOR_H
#define ITERATOR_H

template <typename Data>
class Iterator {
public:
    Iterator(Graph<Data>* graph, Data v_mark, size_t neib) {
        this->graph = graph;
        this->mark = v_mark;
        this->neib_index = neib;
    }

    /*Vertex<Data> operator++() {

    }
    */
    bool operator!=(Iterator<Data> iterator) {

    }

private:
    Graph<Data>* graph = nullptr;
    Data mark = Data();
    size_t neib_index = 0;
};

#endif
