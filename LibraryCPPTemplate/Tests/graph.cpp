#include <iostream>
#include <string>
#include "vector.h"
#include "graph.h"

typedef Vector<int> MyVector;
typedef Digraph<std::string, int> MyGraph;

int main()
{

    MyGraph digraph(6);

    if (digraph.countvert() != 6)
    {
        std::cout << "Invalid initial vertex count\n";
        return 1;
    }
    digraph.setvertlabel(0, "A");
    digraph.setvertlabel(1, "B");
    digraph.setvertlabel(2, "C");
    digraph.setvertlabel(3, "D");
    digraph.setvertlabel(4, "E");
    digraph.setvertlabel(5, "F");

    if (!digraph.addedge(0, 1, 7) || !digraph.addedge(1, 2, 8) || !digraph.addedge(2, 4, 5) || !digraph.addedge(4, 3, 15) || !digraph.addedge(4, 5, 8)) {
        std::cout << "Invalid add edge\n";
        return 1;
    }
    if (!digraph.hasedge(0, 1) || !digraph.hasedge(1, 2) || !digraph.hasedge(2, 4) || !digraph.hasedge(4, 3) || !digraph.hasedge(4, 5)) {
        std::cout << "Invalid has edge\n";
        return 1;
    }
    int edge01 = digraph.getedgelabel(0, 1);
    if (edge01 == 0) {
        std::cout << "Invalid edge\n";
        return 1;
    }

    int edge02 = digraph.getedgelabel(0, 2);
    if (!edge02 == 0) {
        std::cout << "Invalid edge\n";
        return 1;
    }
    for (auto it = digraph.nbegin(4); it != digraph.nend(4); ++it) {
        int weight = it.edgelabel();
        if (weight == 0) {
            std::cout << "Invalid iterator\n";
        }
    }
    digraph.printadmatrix();

    MyGraph copydigraph = digraph;
    size_t newvertex = copydigraph.addvertex();
    if (newvertex != 6) {
        std::cout << "Invalid initial vertex count\n";
        return 1;
    }
    copydigraph.setvertlabel(6, "G");
    if (!copydigraph.addedge(0, 5, 17) || !copydigraph.addedge(5, 6, 18)) {
        std::cout << "Invalid add edge\n";
        return 1;
    }
    if (!copydigraph.removeedge(4, 3) || !copydigraph.removeedge(4, 5)) {
        std::cout << "Invalid remove edge\n";
        return 1;
    }
    bool resrsetedgelabel = copydigraph.setedgelabel(5, 6, 20);
    if (!resrsetedgelabel || copydigraph.getedgelabel(5, 6) != 20)
    {
        std::cout << "Invalid set edge label\n";
        return 1;
    }
    copydigraph.printadmatrix();

    bool resremovevertex = copydigraph.removevertex(4);
    if (!resremovevertex || copydigraph.countvert() != 6)
    {
        std::cout << "Invalid remove vertex\n";
        return 1;
    }

    copydigraph.printadmatrix();

    size_t testsize = 1000;
    MyGraph testdigraph(testsize);
    if (testdigraph.countvert() != testsize)
    {
        std::cout << "Invalid initial vertex count\n";
        return 1;
    }
    for (size_t i = 0; i < testsize; i++) {
        testdigraph.setvertlabel(i, std::to_string(i));
    }
    for (size_t i = 0; i < testsize; i++) {
        size_t vertexlabe = std::stoull(testdigraph.getvertexlabel(i));
        if (vertexlabe != i) {
            std::cout << "Invalid initial vertex lable\n";
            return 1;
        }
    }
    Vector<std::string> resgetallvertexlabels = testdigraph.getallvertexlabels();
    for (size_t i = 0; i < testsize; i++) {
        size_t vertexlabe = std::stoull(resgetallvertexlabels.get(i));
        if (vertexlabe != i) {
            std::cout << "Invalid vertex lable\n";
            return 1;
        }
    }
    return 0;
}