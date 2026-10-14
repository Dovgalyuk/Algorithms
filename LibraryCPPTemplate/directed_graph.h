#ifndef TEMPLATE_DIRECTED_GRAPH
#define TEMPLATE_DIRECTED_GRAPH

#include "vector.h"
#include <istream>
#include <iterator>
#include <ios>

template <typename Vertex, typename Edge>
class Directed_Graph
{
public:
    Directed_Graph() = default;

    explicit Directed_Graph(size_t count_vertex) : size_Graph(count_vertex), vec_Vertex(count_vertex)
    {
        if (count_vertex > 0)
        {
            Graph.resize(1);
            Graph[0].resize(count_vertex);
        }
    }

    Directed_Graph(size_t rows, size_t cols, const Edge &w = Edge{}) : size_Graph(rows * cols), vec_Vertex(rows * cols)
    {
        if (rows * cols == 0)
        {
            return;
        }

        Graph.resize(rows);
        for (auto &row : Graph)
        {
            row.resize(cols);
        }

        for (size_t row = 0; row < rows; row++)
        {
            for (size_t col = 0; col < cols; col++)
            {
                size_t vertex = row * cols + col;

                if (col + 1 < cols)
                {
                    add_edge(vertex, vertex + 1, w);
                    add_edge(vertex + 1, vertex, w);
                }

                if (row + 1 < rows)
                {
                    add_edge(vertex, vertex + cols, w);
                    add_edge(vertex + cols, vertex, w);
                }
            }
        }
    }

    Directed_Graph(const Directed_Graph &graph) : Graph(graph.Graph), size_Graph(graph.size_Graph), vec_Vertex(graph.vec_Vertex)
    {
    }

    Directed_Graph(Directed_Graph &&) = default;

    Directed_Graph &operator=(Directed_Graph &&) = default;

    Directed_Graph &operator=(const Directed_Graph &graph)
    {
        if (this != &graph)
        {
            Directed_Graph tmp(graph);

            Vector<Vector<Cell>> tmp_Graph = Graph;
            size_t tmp_size = size_Graph;
            Vector<Vertex> tmp_vec_vertex = vec_Vertex;

            Graph = tmp.Graph;
            size_Graph = tmp.size_Graph;
            vec_Vertex = tmp.vec_Vertex;

            tmp.Graph = tmp_Graph;
            tmp.size_Graph = tmp_size;
            tmp.vec_Vertex = tmp_vec_vertex;
        }
        return *this;
    }

    ~Directed_Graph() = default;

    static Directed_Graph make_triangle_by_rows(size_t rows, const Edge &w = Edge{})
    {
        Directed_Graph triangle;

        if (rows > 0)
        {
            triangle.size_Graph = rows * rows;
            triangle.vec_Vertex.resize(rows * rows);
            triangle.Graph.resize(rows);
            for (size_t row = 0; row < rows; row++)
            {
                triangle.Graph[row].resize(2 * row + 1);
            }
        }

        for (size_t row = 0; row < rows; row++)
        {
            for (size_t col = 0; col < 2 * row + 1; col++)
            {
                size_t vertex = row * row + col;

                if (col > 0)
                {
                    triangle.add_edge(vertex, row * row + (col - 1), w);
                }

                if (col + 1 < 2 * row + 1)
                {
                    triangle.add_edge(vertex, row * row + (col + 1), w);
                }

                if (col % 2 == 0)
                {
                    if (row + 1 < rows)
                    {
                        triangle.add_edge(vertex, (row + 1) * (row + 1) + (col + 1), w);
                    }
                }
                else
                {
                    if (row > 0)
                    {
                        triangle.add_edge(vertex, (row - 1) * (row - 1) + (col - 1), w);
                    }
                }
            }
        }
        return triangle;
    }

    static Directed_Graph make_triangle_by_vertices(size_t count_vertex, const Edge &w = Edge{})
    {
        size_t rows = 0;

        while (rows * rows < count_vertex)
        {
            rows++;
        }

        if (rows * rows != count_vertex)
        {
            throw std::invalid_argument("invalid count vertexes");
        }

        return make_triangle_by_rows(rows, w);
    }

    Directed_Graph &operator++()
    {
        push_vertex();
        return *this;
    }

    Directed_Graph operator++(int)
    {
        Directed_Graph tmp = *this;
        push_vertex();
        return tmp;
    }

    Directed_Graph &operator--()
    {
        pop_vertex();
        return *this;
    }

    Directed_Graph operator--(int)
    {
        Directed_Graph tmp = *this;
        pop_vertex();
        return tmp;
    }

    void add_vertex(size_t index_vertex, const Vertex &name = Vertex{})
    {
        add_check_index(index_vertex);

        if (Graph.size() == 0)
        {
            Graph.add(0, Vector<Cell>{});
        }

        size_t i_row = 0;
        size_t i_col = 0;

        if (index_vertex == size_Graph)
        {
            i_row = Graph.size() - 1;
            i_col = Graph[i_row].size();
        }
        else
        {
            location(index_vertex, i_row, i_col);
        }

        for (size_t row = 0; row < Graph.size(); row++)
        {
            for (size_t col = 0; col < Graph[row].size(); col++)
            {
                Vector<Link> &out_vertex = Graph[row][col].out_vertex;

                for (size_t i = 0; i < out_vertex.size(); i++)
                {
                    if (out_vertex[i].to_vertex >= index_vertex)
                    {
                        out_vertex[i].to_vertex++;
                    }
                }
            }
        }

        Graph[i_row].add(i_col, Cell{});

        vec_Vertex.add(index_vertex, name);
        size_Graph++;
    }

    void push_vertex(const Vertex &name = Vertex{})
    {
        add_vertex(size_Graph, name);
    }

    void insert_vertex(const Vertex &name = Vertex{})
    {
        add_vertex(0, name);
    }

    void remove_vertex(size_t index_vertex)
    {
        check_index(index_vertex);

        size_t i_row = 0;
        size_t i_col = 0;
        location(index_vertex, i_row, i_col);

        Graph[i_row].remove(i_col);

        if (Graph[i_row].size() == 0)
        {
            Graph.remove(i_row);
        }

        vec_Vertex.remove(index_vertex);
        size_Graph--;

        for (size_t row = 0; row < Graph.size(); row++)
        {
            for (size_t col = 0; col < Graph[row].size(); col++)
            {
                Vector<Link> &out_vertex = Graph[row][col].out_vertex;

                for (size_t i = out_vertex.size(); i > 0; i--)
                {
                    size_t to_vertex = out_vertex[i - 1].to_vertex;

                    if (to_vertex == index_vertex)
                    {
                        out_vertex.remove(i - 1);
                    }
                    else if (to_vertex > index_vertex)
                    {
                        out_vertex[i - 1].to_vertex = to_vertex - 1;
                    }
                }
            }
        }
    }

    void remove_vertex_by_name(const Vertex &name)
    {
        for (size_t i = 0; i < vec_Vertex.size(); i++)
        {
            if (vec_Vertex[i] == name)
            {
                remove_vertex(i);
                return;
            }
        }
        vertex_not_found();
    }

    void pop_vertex()
    {
        check_empty_graph();

        remove_vertex(size_Graph - 1);
    }

    void removeFirst_vertex()
    {
        check_empty_graph();

        remove_vertex(0);
    }

    void add_edge(size_t first_vertex, size_t second_vertex, const Edge &weight)
    {
        check_vertex(first_vertex, second_vertex);

        Cell &from_vertex = cell(first_vertex);
        size_t pos = find_link(from_vertex, second_vertex);

        if (pos < from_vertex.out_vertex.size())
        {
            from_vertex.out_vertex[pos].weight = weight;
        }
        else
        {
            from_vertex.out_vertex.add(from_vertex.out_vertex.size(), Link(second_vertex, weight));
        }
    }

    const Edge &operator()(size_t first_vertex, size_t second_vertex) const
    {
        check_vertex(first_vertex, second_vertex);

        return get_edge(first_vertex, second_vertex);
    }

    const Edge &get_edge(size_t first_vertex, size_t second_vertex) const
    {
        check_vertex(first_vertex, second_vertex);

        const Cell &from_vertex = cell(first_vertex);

        size_t pos = find_link(from_vertex, second_vertex);

        if (pos >= from_vertex.out_vertex.size())
        {
            throw std::runtime_error("directed_graph edge not found");
        }

        return from_vertex.out_vertex[pos].weight;
    }

    void set_edge_weight(size_t first_vertex, size_t second_vertex, const Edge &weight)
    {
        check_vertex(first_vertex, second_vertex);

        Cell &from_vertex = cell(first_vertex);
        size_t pos = find_link(from_vertex, second_vertex);

        if (pos >= from_vertex.out_vertex.size())
        {
            throw std::runtime_error("directed_graph edge not found");
        }

        from_vertex.out_vertex[pos].weight = weight;
    }

    void remove_edge(size_t first_vertex, size_t second_vertex)
    {
        check_vertex(first_vertex, second_vertex);

        Cell &from_vertex = cell(first_vertex);
        size_t pos = find_link(from_vertex, second_vertex);

        if (pos < from_vertex.out_vertex.size())
        {
            from_vertex.out_vertex.remove(pos);
        }
    }

    bool edge(size_t first_vertex, size_t second_vertex) const
    {
        check_vertex(first_vertex, second_vertex);

        const Cell &from_vertex = cell(first_vertex);

        return find_link(from_vertex, second_vertex) < from_vertex.out_vertex.size();
    }

    const Vector<Vertex> &get_vec_vertex() const
    {
        return vec_Vertex;
    }

    void set_vertex_name(size_t index, const Vertex &name)
    {
        check_index(index);

        vec_Vertex[index] = name;
    }

    const Vertex &get_name_vertex(size_t index) const
    {
        check_index(index);

        return vec_Vertex[index];
    }

    size_t get_index_by_name(const Vertex &name) const
    {
        for (size_t i = 0; i < vec_Vertex.size(); i++)
        {
            if (vec_Vertex[i] == name)
            {
                return i;
            }
        }

        vertex_not_found();

        return 0;
    }

    size_t size_graph() const
    {
        return size_Graph;
    }

    bool empty_graph() const
    {
        return size_Graph == 0;
    }

    size_t size_vec_vertex() const
    {
        return vec_Vertex.size();
    }

    bool empty_vec_vertex() const
    {
        return vec_Vertex.size() == 0;
    }

    friend std::istream &operator>>(std::istream &input, Directed_Graph &graph)
    {
        size_t n = 0;

        if (!(input >> n))
        {
            return input;
        }

        Directed_Graph tmp(n);
        for (size_t i = 0; i < n; i++)
        {
            if (!(input >> tmp.vec_Vertex[i]))
            {
                return input;
            }
        }

        size_t m = 0;

        if (input >> m)
        {
            for (size_t k = 0; k < m; k++)
            {
                size_t first = 0;
                size_t second = 0;
                Edge weight{};

                if (!(input >> first >> second >> weight))
                {
                    return input;
                }

                if (first >= n || second >= n)
                {
                    input.setstate(std::ios::failbit);
                    return input;
                }

                tmp.add_edge(first, second, weight);
            }
        }
        else
        {
            if (input.eof())
            {
                try
                {
                    Directed_Graph triangle = make_triangle_by_vertices(n, Edge{});
                    triangle.vec_Vertex = tmp.vec_Vertex;

                    input.clear();
                    graph = std::move(triangle);

                    return input;
                }
                catch (const std::invalid_argument &)
                {
                }
            }

            input.setstate(std::ios::failbit);

            return input;
        }

        graph = std::move(tmp);

        return input;
    }

    class Iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = size_t;
        using difference_type = ptrdiff_t;
        using pointer = const size_t *;
        using reference = size_t;

        Iterator(const Directed_Graph *graph, size_t start, size_t end) : iter_graph(graph), vertex_start(start), vertex_end(end)
        {
        }

        const Edge &weight() const
        {
            return iter_graph->cell(vertex_start).out_vertex[vertex_end].weight;
        }

        size_t operator*() const
        {
            return iter_graph->cell(vertex_start).out_vertex[vertex_end].to_vertex;
        }

        Iterator &operator++()
        {
            vertex_end++;
            return *this;
        }

        Iterator operator++(int)
        {
            auto t = *this;
            ++(*this);
            return t;
        }

        bool operator==(const Iterator &other) const
        {
            return iter_graph == other.iter_graph && vertex_start == other.vertex_start && vertex_end == other.vertex_end;
        }

        bool operator!=(const Iterator &other) const
        {
            return !(*this == other);
        }

    private:
        const Directed_Graph *iter_graph;
        size_t vertex_start;
        size_t vertex_end;
    };

    Iterator begin(size_t index_vertex) const
    {
        check_index(index_vertex);
        return Iterator(this, index_vertex, 0);
    }

    Iterator end(size_t index_vertex) const
    {
        check_index(index_vertex);
        return Iterator(this, index_vertex, cell(index_vertex).out_vertex.size());
    }

private:
    struct Link
    {
        size_t to_vertex = 0;
        Edge weight{};

        Link() = default;

        Link(size_t t, const Edge &w) : to_vertex(t), weight(w) {}
    };

    struct Cell
    {
        Vector<Link> out_vertex;
    };

    Vector<Vector<Cell>> Graph;
    size_t size_Graph = 0;

    Vector<Vertex> vec_Vertex;

private:
    void location(size_t index, size_t &i_row, size_t &i_col) const
    {
        for (size_t row = 0; row < Graph.size(); row++)
        {
            if (index < Graph[row].size())
            {
                i_row = row;
                i_col = index;
                return;
            }
            index -= Graph[row].size();
        }
        throw std::out_of_range("directed_graph subscript vertex of range");
    }

    Cell &cell(size_t index)
    {
        size_t row = 0;
        size_t col = 0;

        location(index, row, col);

        return Graph[row][col];
    }

    const Cell &cell(size_t index) const
    {
        size_t row = 0;
        size_t col = 0;

        location(index, row, col);

        return Graph[row][col];
    }

    static size_t find_link(const Cell &from_vertex, size_t to_vertex)
    {
        for (size_t i = 0; i < from_vertex.out_vertex.size(); i++)
        {
            if (from_vertex.out_vertex[i].to_vertex == to_vertex)
            {
                return i;
            }
        }
        return from_vertex.out_vertex.size();
    }

    void add_check_index(size_t index) const
    {
        if (index > size_Graph)
        {
            throw std::out_of_range("directed_graph subscript vertex of range");
        }
    }

    void check_index(size_t index) const
    {
        if (index >= size_Graph)
        {
            throw std::out_of_range("directed_graph subscript vertex of range");
        }
    }

    void check_empty_graph() const
    {
        if (size_Graph == 0)
        {
            throw std::out_of_range("directed_graph subscript vertex of range");
        }
    }

    void check_vertex(size_t first_vertex, size_t second_vertex) const
    {
        if (first_vertex >= size_Graph || second_vertex >= size_Graph)
        {
            throw std::out_of_range("directed_graph subscript vertex of range");
        }
    }

    void vertex_not_found() const
    {
        throw std::runtime_error("vertex not found");
    }
};
#endif