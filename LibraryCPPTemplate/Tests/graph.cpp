#include <iostream>
#include <string>
#include "../graph.h"

using std::string;
using namespace std;
static void Fail(const string& msg)
{
    cerr << "TEST FAILED: " << msg << "\n";
}

static bool Contains(const Vector<size_t>& v, size_t x)
{
    for (size_t i = 0; i < v.size(); ++i)
        if (v.get(i) == x)
            return true;
    return false;
}
static bool EqualAsSet(const Vector<size_t>& a, const Vector<size_t>& b)
{
    if (a.size() != b.size()) return false;

    for (size_t i = 0; i < a.size(); ++i)
        if (!Contains(b, a.get(i)))
            return false;

    for (size_t i = 0; i < b.size(); ++i)
        if (!Contains(a, b.get(i)))
            return false;

    return true;
}

static Vector<size_t> CollectNeighbors(const Graph<string, int>& g, size_t v)
{
    Vector<size_t> res;
    auto it = g.Neighbors(v);
    while (it.HasNext())
    {
        size_t to = it.Next();
        size_t old = res.size();
        res.resize(old + 1);
        res.set(old, to);
    }
    return res;
}

int main()
{
    Graph<string, int> g(3);
    if (g.VertexCount() != 3)
    {
        Fail("VertexCount() should be 3 after Graph(3)");
        return 1;
    }

    g.SetVertexLabel(0, "A");
    g.SetVertexLabel(1, "B");
    g.SetVertexLabel(2, "C");

    if (g.GetVertexLabel(0) != "A" || g.GetVertexLabel(1) != "B" || g.GetVertexLabel(2) != "C")
    {
        Fail("GetVertexLabel() returned wrong labels after SetVertexLabel()");
        return 1;
    }

    g.AddEdge(0, 1, 5);
    g.AddEdge(1, 2, 7);
    g.AddEdge(0, 2, 10);

    if (!g.HasEdge(0, 1) || !g.HasEdge(1, 2) || !g.HasEdge(0, 2))
    {
        Fail("HasEdge() should be true for added edges");
        return 1;
    }
    if (g.GetEdgeLabel(0, 1) != 5 || g.GetEdgeLabel(1, 2) != 7 || g.GetEdgeLabel(0, 2) != 10)
    {
        Fail("GetEdgeLabel() returned wrong labels for added edges");
        return 1;
    }

    g.RemoveEdge(0, 2);
    if (g.HasEdge(0, 2))
    {
        Fail("RemoveEdge() did not remove edge 0->2");
        return 1;
    }

    g.SetEdgeLabel(0, 2, 42);
    if (!g.HasEdge(0, 2))
    {
        Fail("SetEdgeLabel() should create/enable the edge (exists=true)");
        return 1;
    }
    if (g.GetEdgeLabel(0, 2) != 42)
    {
        Fail("SetEdgeLabel() did not set correct label");
        return 1;
    }

    {
        Vector<size_t> nbA = CollectNeighbors(g, 0);
        Vector<size_t> expA;
        expA.resize(2);
        expA.set(0, 1);
        expA.set(1, 2);

        if (!EqualAsSet(nbA, expA))
        {
            Fail("Neighbors(0) should return {1,2}");
            return 1;
        }
    }

    {
        Vector<size_t> nbB = CollectNeighbors(g, 1);
        Vector<size_t> expB;
        expB.resize(1);
        expB.set(0, 2);

        if (!EqualAsSet(nbB, expB))
        {
            Fail("Neighbors(1) should return {2}");
            return 1;
        }
    }

    {
        Vector<size_t> nbC = CollectNeighbors(g, 2);
        if (nbC.size() != 0)
        {
            Fail("Neighbors(2) should be empty");
            return 1;
        }
    }

    size_t idxD = g.AddVertex("D");
    if (idxD != 3)
    {
        Fail("AddVertex() should return index 3 when adding 4th vertex");
        return 1;
    }
    if (g.VertexCount() != 4)
    {
        Fail("VertexCount() should be 4 after AddVertex()");
        return 1;
    }
    if (g.GetVertexLabel(3) != "D")
    {
        Fail("New vertex label should be 'D'");
        return 1;
    }

    if (!g.HasEdge(0, 1) || g.GetEdgeLabel(0, 1) != 5)
    {
        Fail("Edge 0->1 should remain after AddVertex()");
        return 1;
    }

    g.AddEdge(3, 0, 3);
    g.AddEdge(0, 3, 4);

    if (!g.HasEdge(3, 0) || g.GetEdgeLabel(3, 0) != 3 ||
        !g.HasEdge(0, 3) || g.GetEdgeLabel(0, 3) != 4)
    {
        Fail("Edges involving new vertex D are incorrect");
        return 1;
    }

    g.RemoveVertex(1);

    if (g.VertexCount() != 3)
    {
        Fail("VertexCount() should be 3 after RemoveVertex(1)");
        return 1;
    }
    if (g.GetVertexLabel(0) != "A" || g.GetVertexLabel(1) != "C" || g.GetVertexLabel(2) != "D")
    {
        Fail("Vertex labels are wrong after RemoveVertex(1)");
        return 1;
    }

    if (!g.HasEdge(0, 2) || g.GetEdgeLabel(0, 2) != 4)
    {
        Fail("Edge A->D should become 0->2 with label 4 after removing vertex B");
        return 1;
    }

    if (!g.HasEdge(2, 0) || g.GetEdgeLabel(2, 0) != 3)
    {
        Fail("Edge D->A should become 2->0 with label 3 after removing vertex B");
        return 1;
    }

    if (!g.HasEdge(0, 1) || g.GetEdgeLabel(0, 1) != 42)
    {
        Fail("After removing B, edge A->C should be at 0->1 with label 42");
        return 1;
    }

    {
        Vector<size_t> nbNewC = CollectNeighbors(g, 1);
        if (nbNewC.size() != 0)
        {
            Fail("Vertex C should have no outgoing edges after RemoveVertex(1)");
            return 1;
        }
    }

    cout << "OK\n";

}