#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "graph.h"

using namespace std;

static int tp = 0;
static int tf = 0;

void check(bool expr, const char *msg){
    if (expr) tp++;
    else tf++;
    cout << (expr ? "PASS: " : "FAIL: ") << msg << '\n';
}

int main(){
    try {
        Graph<string, int> graph;
        check(graph.size() == 0, "empty graph");
        check(graph.add_vertex("A") == 0, "add A");
        check(graph.add_vertex("B") == 1, "add B");
        check(graph.add_vertex("C") == 2, "add C");

        graph.set_vertex(1, "middle");
        check(graph.get_vertex(1) == "middle", "set vertex");
        check(graph.find_vertex("C") == 2, "find C");
        Vector<string> names = graph.get_vertices();
        names.set(0, "copy");
        check(graph.get_vertex(0) == "A", "names copy");

        graph.add_edge(0, 1, 10);
        check(graph.has_edge(0, 1), "add edge");
        check(!graph.has_edge(1, 0), "directed edge");
        graph.set_edge(0, 1, 15);
        check(graph.get_edge(0, 1) == 15, "set edge");
        graph.add_edge(0, 1, 20);
        check(graph.get_edge(0, 1) == 20, "update edge");
        graph.add_edge(0, 2, 0);
        check(graph.has_edge(0, 2) && graph.get_edge(0, 2) == 0, "zero edge");

        auto it = graph.neighbors(0);
        check(it.valid() && it.get() == 1, "first neighbor");
        it.next();
        check(it.valid() && it.get() == 2, "second neighbor");
        it.next();
        check(!it.valid(), "no more neighbors");
        it.next();
        check(!it.valid(), "next after end");
        check(!graph.neighbors(2).valid(), "no neighbors");

        graph.remove_edge(0, 1);
        graph.remove_edge(0, 1);
        check(!graph.has_edge(0, 1), "remove edge");
        bool caught = false;
        try {
            graph.get_edge(0, 1);
        } catch (const out_of_range &) {
            caught = true;
        }
        check(caught, "missing edge error");
        caught = false;
        try {
            graph.set_vertex(3, "wrong");
        } catch (const out_of_range &) {
            caught = true;
        }
        check(caught, "wrong index error");

        graph.add_edge(2, 0, 7);
        graph.add_edge(2, 2, 9);
        check(graph.add_vertex("D") == 3, "add D");
        check(graph.get_edge(2, 0) == 7 && graph.get_edge(2, 2) == 9, "edges after add");
        check(!graph.has_edge(3, 0) && !graph.has_edge(0, 3), "D has no edges");
        graph.remove_vertex(1);
        check(graph.size() == 3 && graph.get_vertex(1) == "C", "remove vertex");
        check(graph.has_edge(0, 1) && graph.get_edge(0, 1) == 0, "edge after remove");
        check(graph.get_edge(1, 0) == 7 && graph.get_edge(1, 1) == 9, "loop after remove");

        Graph<string, int> copy = graph;
        copy.set_vertex(0, "changed");
        copy.set_edge(1, 0, 100);
        check(graph.get_vertex(0) == "A" && graph.get_edge(1, 0) == 7, "graph copy");
        Graph<string, int> assigned;
        assigned = graph;
        assigned.remove_vertex(0);
        check(graph.size() == 3 && assigned.size() == 2, "graph assignment");

        graph.remove_vertex(2);
        graph.remove_vertex(0);
        check(graph.size() == 1 && graph.get_edge(0, 0) == 9, "remove first and last");
        graph.remove_vertex(0);
        check(graph.size() == 0, "remove only vertex");
        check(graph.add_vertex("again") == 0, "reuse graph");

        istringstream good(
            "3 2\n"
            "source A sink\n"
            "source A 10\n"
            "A sink 4\n"
            "source sink\n"
        );
        graph.read(good);
        check(graph.size() == 3 && graph.get_edge(0, 1) == 10 &&
              graph.get_edge(1, 2) == 4, "read graph");
        string source;
        string sink;
        good >> source >> sink;
        check(source == "source" && sink == "sink", "read source and sink");

        const char *bad[] = {
            "",
            "-1 0",
            "1 -1 A",
            "2 0 A A",
            "2 1 A B A unknown 5",
            "2 2 A B A B 1 A B 2",
            "2 1 A B A B"
        };
        for (const char *text : bad) {
            istringstream input(text);
            caught = false;
            try {
                graph.read(input);
            } catch (const exception &) {
                caught = true;
            }
            check(caught, "bad input");
            check(graph.size() == 3 && graph.get_vertex(0) == "source" &&
                  graph.get_edge(1, 2) == 4, "graph unchanged");
        }

        Graph<int, string> other(2);
        other.set_vertex(0, 42);
        other.add_edge(0, 1, "road");
        check(other.get_vertex(0) == 42 && other.get_edge(0, 1) == "road", "other types");
    } catch (const exception &error) {
        tf++;
        cout << "unexpected error: " << error.what() << '\n';
    }
    cout << "\nResults: " << tp << " passed, " << tf << " failed\n";
    return tf > 0 ? 1 : 0;
}
