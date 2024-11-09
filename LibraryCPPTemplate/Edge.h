#pragma once

template <typename V_type, typename E_type>
struct Edge {

    Edge() {}
    Edge(Vertex<V_type>* a, Vertex<V_type>* b, E_type mark) : start(a), destination(b), mark(mark)  {}

    Vertex<V_type> *start = nullptr;
    Vertex<V_type> *destination = nullptr;
    E_type mark = E_type();
};