#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../graph.h"

static int failures = 0;
#define CHECK(cond)                                                        \
    do {                                                                   \
        if (!(cond)) {                                                     \
            cerr << "FAILED: " #cond " (line " << __LINE__ << ")\n";  \
            ++failures;                                                    \
        }                                                                  \
    } while (0)

int main() {

    Graph<double, string> g(3);
    CHECK(g.Size() == 3);
    CHECK(g.HasVertex("0") && g.HasVertex("2"));


    g.AddVertex("A", "labelA");
    bool thrown = false;
    try { g.AddVertex("A"); } catch (const invalid_argument&) { thrown = true; }
    CHECK(thrown);
    CHECK(g.Size() == 4);


    CHECK(g.AddEdge("A", "0", 1.5));
    CHECK(!g.AddEdge("A", "0", 9.9));
    CHECK(g.HasEdge("A", "0"));
    CHECK(!g.HasEdge("0", "A"));
    CHECK(g.GetEdgeLabel("A", "0") == 1.5);
    g.SetEdgeLabel("A", "0", 2.5);
    CHECK(g.GetEdgeLabel("A", "0") == 2.5);


    CHECK(g.GetVertexLabel("A") == "labelA");
    g.SetVertexLabel("1", "one");
    vector<string> labels = g.GetVertexLabels();
    CHECK(labels.size() == 4);
    CHECK(labels[1] == "one");


    g.AddEdge("A", "1", 3.0);
    g.AddEdge("A", "2", 4.0);
    int count = 0;
    double sum = 0;
    for (auto it = g.Neighbors("A"); it.Valid(); it.Next()) {
        ++count;
        sum += it.Label();
    }
    CHECK(count == 3);
    CHECK(sum == 2.5 + 3.0 + 4.0);


    CHECK(g.RemoveEdge("A", "1"));
    CHECK(!g.RemoveEdge("A", "1"));
    CHECK(!g.HasEdge("A", "1"));


    Graph<int, int> h;
    h.AddVertex("A"); h.AddVertex("B"); h.AddVertex("C");
    h.AddEdge("A", "C", 1);
    h.AddEdge("B", "C", 2);
    h.AddEdge("C", "A", 3);
    h.RemoveVertex("B");
    CHECK(h.Size() == 2);
    CHECK(!h.HasVertex("B"));
    CHECK(h.IndexOf("C") == 1);
    CHECK(h.HasEdge("A", "C") && h.HasEdge("C", "A"));
    CHECK(h.GetEdgeLabel("C", "A") == 3);


    h.Resize(5);
    CHECK(h.Size() == 5);
    h.Resize(2);
    CHECK(h.Size() == 2);

    Graph<int, int> grid(2, 3);
    CHECK(grid.Size() == 6);
    CHECK(grid.HasEdge("0_0", "0_1") && grid.HasEdge("0_1", "0_0"));
    CHECK(grid.HasEdge("0_0", "1_0"));
    CHECK(!grid.HasEdge("0_0", "1_1"));


    istringstream in("3 2\nA 10\nB 20\nC 30\nA B 5\nB C 7\n");
    Graph<int, int> r;
    CHECK(r.Read(in));
    CHECK(r.Size() == 3);
    CHECK(r.GetEdgeLabel("B", "C") == 7);
    CHECK(r.GetVertexLabels() == vector<int>({10, 20, 30}));

    istringstream bad("2 1\nA 0\nB 0\nA Z 1\n");
    Graph<int, int> r2;
    CHECK(!r2.Read(bad));

    if (failures == 0) cout << "All graph tests passed\n";
    return failures == 0 ? 0 : 1;
}