#pragma once

template <typename V_type>
struct Vertex {

    Vertex() {}
    Vertex(size_t number, V_type mark) : number(number), mark(mark) {}

    size_t number = std::numeric_limits<size_t>::max();
    V_type mark = V_type();
};