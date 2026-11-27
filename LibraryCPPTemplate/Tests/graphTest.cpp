#include <iostream>
#include <sstream>
#include "Graph.h"

typedef Graph<std::string, int> MyGraph;

int main()
{
    MyGraph g;
    if (g.getVertexMarks().size() != 0)
    {
        std::cout << "Empty graph error\n";
        return 1;
    }

    MyGraph g1(4);
    if (g1.getVertexMarks().size() != 4)
    {
        std::cout << "Invalid vertex count\n";
        return 1;
    }
    g1.addEdge("0", "1", 10);
    if (!g1.hasEdge("0", "1"))
    {
        std::cout << "Edge not found\n";
        return 1;
    }
    if (g1.hasEdge("1", "0"))
    {
        std::cout << "Directed graph error\n";
        return 1;
    }

    MyGraph g2(2, 3);
    if (g2.getVertexMarks().size() != 6)
    {
        std::cout << "Invalid grid size\n";
        return 1;
    }
    if (!g2.hasEdge("0_0", "0_1"))
    {
        std::cout << "Grid horizontal edge error\n";
        return 1;
    }
    if (!g2.hasEdge("0_0", "1_0"))
    {
        std::cout << "Grid vertical edge error\n";
        return 1;
    }
    if (g2.hasEdge("0_0", "1_1"))
    {
        std::cout << "Diagonal edge error\n";
        return 1;
    }

    MyGraph g3;
    g3.addVertex("A");
    g3.addVertex("B");
    g3.addVertex("C");
    if (g3.getVertexMarks().size() != 3)
    {
        std::cout << "Invalid vertex count after add\n";
        return 1;
    }
    g3.setVertexMark("A", "markA");
    g3.setVertexMark("B", "markB");
    if (g3.getVertexMark("A") != "markA")
    {
        std::cout << "Invalid vertex mark\n";
        return 1;
    }
    g3.addEdge("A", "B", 100);
    g3.addEdge("B", "C", 200);
    g3.removeVertex("B");
    if (g3.getVertexMarks().size() != 2)
    {
        std::cout << "Invalid vertex count after remove\n";
        return 1;
    }
    if (g3.hasEdge("A", "B"))
    {
        std::cout << "Edge should be removed with vertex\n";
        return 1;
    }

    MyGraph g4(3);
    g4.addEdge("0", "1", 100);
    g4.addEdge("1", "2", 200);
    g4.addEdge("0", "2", 300);
    if (g4.getEdgeMark("0", "1") != 100)
    {
        std::cout << "Invalid edge mark\n";
        return 1;
    }
    g4.setEdgeMark("0", "1", 150);
    if (g4.getEdgeMark("0", "1") != 150)
    {
        std::cout << "Invalid edge mark after set\n";
        return 1;
    }
    g4.removeEdge("0", "1");
    if (g4.hasEdge("0", "1"))
    {
        std::cout << "Edge should be removed\n";
        return 1;
    }

    MyGraph g5;
    g5.addVertex("X");
    g5.addVertex("Y");
    g5.addVertex("Z");
    g5.addVertex("W");
    g5.addEdge("X", "Y", 1);
    g5.addEdge("X", "Z", 2);
    g5.addEdge("X", "W", 3);
    int count = 0;
    for (auto it = g5.neighborsBegin("X"); it != g5.neighborsEnd("X"); ++it)
    {
        (void)(*it);
        ++count;
    }
    if (count != 3)
    {
        std::cout << "Invalid neighbor count (expected 3, got " << count << ")\n";
        return 1;
    }

    int cnt = 0;
    for (auto it = g5.neighborsBegin("Y"); it != g5.neighborsEnd("Y"); ++it) ++cnt;
    if (cnt != 0)
    {
        std::cout << "Empty neighbor list error\n";
        return 1;
    }

    std::istringstream input(
        "3\n"
        "north south east\n"
        "2\n"
        "north south 11\n"
        "south east 22\n");
    MyGraph g6;
    input >> g6;
    if (g6.getVertexMarks().size() != 3)
    {
        std::cout << "Invalid read size\n";
        return 1;
    }
    if (g6.getEdgeMark("north", "south") != 11)
    {
        std::cout << "Invalid read edge\n";
        return 1;
    }
    if (g6.getEdgeMark("south", "east") != 22)
    {
        std::cout << "Invalid read edge 2\n";
        return 1;
    }
    if (g6.hasEdge("south", "north"))
    {
        std::cout << "Directed graph read error\n";
        return 1;
    }

    MyGraph g7(3);
    g7.addEdge("0", "1", 10);
    g7.addEdge("1", "2", 20);
    MyGraph g8 = g7;
    if (g8.getVertexMarks().size() != 3)
    {
        std::cout << "Invalid copy size\n";
        return 1;
    }
    if (g8.getEdgeMark("0", "1") != 10)
    {
        std::cout << "Invalid copy edge\n";
        return 1;
    }
    g7.setEdgeMark("0", "1", 99);
    if (g8.getEdgeMark("0", "1") != 10)
    {
        std::cout << "Copy is not independent\n";
        return 1;
    }

    g7 = g7;
    if (g7.getEdgeMark("0", "1") != 99)
    {
        std::cout << "Self-assignment error\n";
        return 1;
    }

    MyGraph g9(3);
    g9.setVertexMark("0", "alpha");
    g9.setVertexMark("1", "beta");
    g9.setVertexMark("2", "gamma");
    Vector<std::string> marks = g9.getVertexMarks();
    if (marks.size() != 3)
    {
        std::cout << "Invalid marks size\n";
        return 1;
    }
    if (marks.get(0) != "alpha" || marks.get(1) != "beta" || marks.get(2) != "gamma")
    {
        std::cout << "Invalid marks content\n";
        return 1;
    }

    std::cout << "All graph tests passed\n";
    return 0;
}