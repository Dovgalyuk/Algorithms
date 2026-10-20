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

    explicit Directed_Graph(size_t count_vertex)
    {
        if (count_vertex > 0)
        {
            Graph.resize(1);
            Graph[0].resize(count_vertex);
        }
    }

    Directed_Graph(size_t rows, size_t cols, const Edge &weight = Edge{}) : shape(Shape::Rectangle)
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

        fill_weights(weight);
    }

    Directed_Graph(const Directed_Graph &graph) : Graph(graph.Graph), shape(graph.shape)
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
            Shape tmp_shape = shape;

            Graph = tmp.Graph;
            shape = tmp.shape;

            tmp.Graph = tmp_Graph;
            tmp.shape = tmp_shape;
        }
        return *this;
    }

    ~Directed_Graph() = default;

    static Directed_Graph make_triangle_by_rows(size_t rows, const Edge &weight = Edge{})
    {
        Directed_Graph triangle;

        triangle.shape = Shape::Triangle;

        triangle.Graph.resize(rows);
        for (size_t row = 0; row < rows; row++)
        {
            triangle.Graph[row].resize(2 * row + 1);
        }

        triangle.fill_weights(weight);

        return triangle;
    }

    static Directed_Graph make_triangle_by_vertices(size_t count_vertex, const Edge &weight = Edge{})
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

        return make_triangle_by_rows(rows, weight);
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

        line();

        if (Graph.size() == 0)
        {
            Graph.add(0, Vector<Cell>{});
        }

        Cell new_cell;
        new_cell.name = name;
        Graph[0].add(index_vertex, new_cell);
    }

    void push_vertex(const Vertex &name = Vertex{})
    {
        add_vertex(size_graph(), name);
    }

    void insert_vertex(const Vertex &name = Vertex{})
    {
        add_vertex(0, name);
    }

    void remove_vertex(size_t index_vertex)
    {
        check_index(index_vertex);

        line();

        Graph[0].remove(index_vertex);

        if (Graph[0].size() == 0)
        {
            Graph.remove(0);
        }
    }

    void remove_vertex_by_name(const Vertex &name)
    {
        for (size_t i = 0; i < size_graph(); i++)
        {
            if (cell(i).name == name)
            {
                remove_vertex(i);
                return;
            }
        }
        vertex_not_found();
    }

    void pop_vertex()
    {
        remove_vertex(size_graph() - 1);
    }

    void removeFirst_vertex()
    {
        remove_vertex(0);
    }

    void add_edge(size_t first_vertex, size_t second_vertex, const Edge &weight)
    {
        check_vertex(first_vertex, second_vertex);

        if (!is_neighbor(first_vertex, second_vertex, false))
        {
            throw std::invalid_argument("vertices are not neighbors");
        }

        cell(second_vertex).weight = weight;
        cell(first_vertex).direction &= ~direction_bit(first_vertex, second_vertex);
    }

    const Edge &operator()(size_t first_vertex, size_t second_vertex) const
    {
        check_vertex(first_vertex, second_vertex);

        return get_edge(first_vertex, second_vertex);
    }

    const Edge &get_edge(size_t first_vertex, size_t second_vertex) const
    {
        check_vertex(first_vertex, second_vertex);

        if (!is_neighbor(first_vertex, second_vertex))
        {
            throw std::runtime_error("directed_graph edge not found");
        }

        return cell(second_vertex).weight;
    }

    void set_edge_weight(size_t first_vertex, size_t second_vertex, const Edge &weight)
    {
        add_edge(first_vertex, second_vertex, weight);
    }

    void remove_edge(size_t first_vertex, size_t second_vertex)
    {
        check_vertex(first_vertex, second_vertex);

        if (is_neighbor(first_vertex, second_vertex, false))
        {
            cell(first_vertex).direction |= direction_bit(first_vertex, second_vertex);
        }
    }

    bool edge(size_t first_vertex, size_t second_vertex) const
    {
        check_vertex(first_vertex, second_vertex);

        return is_neighbor(first_vertex, second_vertex);
    }

    Vector<Vertex> get_vec_vertex() const
    {
        Vector<Vertex> result;

        for (size_t i = 0; i < size_graph(); i++)
        {
            result.add(i, cell(i).name);
        }
        return result;
    }

    void set_vertex_name(size_t index, const Vertex &name)
    {
        check_index(index);

        cell(index).name = name;
    }

    const Vertex &get_name_vertex(size_t index) const
    {
        check_index(index);

        return cell(index).name;
    }

    size_t get_index_by_name(const Vertex &name) const
    {
        for (size_t i = 0; i < size_graph(); i++)
        {
            if (cell(i).name == name)
            {
                return i;
            }
        }

        vertex_not_found();

        return 0;
    }

    friend std::istream &operator>>(std::istream &input, Directed_Graph &graph)
    {
        size_t n = 0;

        if (!(input >> n))
        {
            return input;
        }

        Directed_Graph line(n);
        for (size_t i = 0; i < n; i++)
        {
            if (!(input >> line.cell(i).name))
            {
                return input;
            }
        }

        Directed_Graph triangle;
        bool triangle_b = n > 0;

        if (triangle_b)
        {
            try
            {
                triangle = make_triangle_by_vertices(n, Edge{});
                for (size_t i = 0; i < n; i++)
                {
                    triangle.cell(i).name = line.cell(i).name;
                }
            }
            catch (const std::invalid_argument &)
            {
                triangle_b = false;
            }
        }

        size_t m = 0;

        if (input >> m)
        {
            bool line_b = true;

            line.direction_all();
            triangle.direction_all();

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

                line_b = line_b && line.is_neighbor(first, second, false);
                triangle_b = triangle_b && triangle.is_neighbor(first, second, false);

                if (!line_b && !triangle_b)
                {
                    input.setstate(std::ios::failbit);
                    return input;
                }

                if (line_b)
                {
                    line.add_edge(first, second, weight);
                }
                if (triangle_b)
                {
                    triangle.add_edge(first, second, weight);
                }
            }

            graph = triangle_b ? std::move(triangle) : std::move(line);

            return input;
        }

        if (input.eof() && triangle_b)
        {
            input.clear();
            graph = std::move(triangle);

            return input;
        }

        input.setstate(std::ios::failbit);

        return input;
    }

    size_t size_graph() const
    {
        size_t count = 0;

        for (size_t row = 0; row < Graph.size(); row++)
        {
            count += Graph[row].size();
        }
        return count;
    }

    bool empty_graph() const
    {
        return Graph.size() == 0;
    }

    class Iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = size_t;
        using difference_type = ptrdiff_t;
        using pointer = const size_t *;
        using reference = size_t;

        Iterator(const Directed_Graph *graph, size_t start, bool at_end) : iter_graph(graph), vertex_start(start), list(graph->neighbors(start)), pos(at_end ? list.size() : 0)
        {
        }

        const Edge &weight() const
        {
            return iter_graph->cell(list[pos]).weight;
        }

        size_t operator*() const
        {
            return list[pos];
        }

        Iterator &operator++()
        {
            pos++;
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
            return iter_graph == other.iter_graph && vertex_start == other.vertex_start && pos == other.pos;
        }

        bool operator!=(const Iterator &other) const
        {
            return !(*this == other);
        }

    private:
        const Directed_Graph *iter_graph;
        size_t vertex_start;
        Vector<size_t> list;
        size_t pos;
    };

    Iterator begin(size_t index_vertex) const
    {
        check_index(index_vertex);
        return Iterator(this, index_vertex, false);
    }

    Iterator end(size_t index_vertex) const
    {
        check_index(index_vertex);
        return Iterator(this, index_vertex, true);
    }

private:
    enum class Shape
    {
        Line,
        Rectangle,
        Triangle
    };

    struct Cell
    {
        Vertex name{};
        Edge weight{};
        unsigned char direction = 0;
    };

    Vector<Vector<Cell>> Graph;

    Shape shape = Shape::Line;

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

   Vector<size_t> neighbors(size_t vertex, bool only_open = true) const
    {
        size_t row = 0;
        size_t col = 0;
 
        location(vertex, row, col);
 
        size_t start = vertex - col;
        Vector<size_t> result;
 
        if (col > 0)
        {
            result.add(result.size(), vertex - 1);
        }
        if (col + 1 < Graph[row].size())
        {
            result.add(result.size(), vertex + 1);
        }
        if (row > 0)
        {
            if (shape == Shape::Rectangle)
            {
                result.add(result.size(), start - Graph[row - 1].size() + col);
            }
            else if (shape == Shape::Triangle && col % 2 == 1)
            {
                result.add(result.size(), start - Graph[row - 1].size() + col - 1);
            }
        }
        if (row + 1 < Graph.size())
        {
            if (shape == Shape::Rectangle)
            {
                result.add(result.size(), start + Graph[row].size() + col);
            }
            else if (shape == Shape::Triangle && col % 2 == 0)
            {
                result.add(result.size(), start + Graph[row].size() + col + 1);
            }
        }
        if (!only_open)
        {
            return result;
        }
 
        Vector<size_t> open;
        for (size_t i = 0; i < result.size(); i++)
        {
            if (!(cell(vertex).direction & direction_bit(vertex, result[i])))
            {
                open.add(open.size(), result[i]);
            }
        }
        return open;
    }
 
    unsigned char direction_bit(size_t from, size_t to) const
    {
        size_t row_from = 0;
        size_t col_from = 0;
        size_t row_to = 0;
        size_t col_to = 0;
 
        location(from, row_from, col_from);
        location(to, row_to, col_to);
 
        if (row_from == row_to)
        {
            return col_to < col_from ? 1 : 2;
        }
        return row_to < row_from ? 4 : 8;
    }
 
    void direction_all()
    {
        for (size_t v = 0; v < size_graph(); v++)
        {
            Vector<size_t> list = neighbors(v, false);
 
            for (size_t i = 0; i < list.size(); i++)
            {
                remove_edge(v, list[i]);
            }
        }
    }

     bool is_neighbor(size_t first_vertex, size_t second_vertex, bool only_open = true) const
    {
        Vector<size_t> list = neighbors(first_vertex, only_open);

        for (size_t i = 0; i < list.size(); i++)
        {
            if (list[i] == second_vertex)
            {
                return true;
            }
        }
        return false;
    }   

    void fill_weights(const Edge &weight)
    {
        for (size_t row = 0; row < Graph.size(); row++)
        {
            for (size_t col = 0; col < Graph[row].size(); col++)
            {
                Graph[row][col].weight = weight;
            }
        }
    }

    void line()
    {
        if (shape == Shape::Line)
        {
            return;
        }

        Vector<Cell> row;
        for (size_t r = 0; r < Graph.size(); r++)
        {
            for (size_t c = 0; c < Graph[r].size(); c++)
            {
                row.add(row.size(), Graph[r][c]);
            }
        }

        Vector<Vector<Cell>> flat;
        if (row.size() > 0)
        {
            flat.add(0, row);
        }

        Graph = flat;
        shape = Shape::Line;
    }

    void add_check_index(size_t index) const
    {
        if (index > size_graph())
        {
            throw std::out_of_range("directed_graph subscript vertex of range");
        }
    }

    void check_index(size_t index) const
    {
        if (index >= size_graph())
        {
            throw std::out_of_range("directed_graph subscript vertex of range");
        }
    }

    void check_empty_graph() const
    {
        if (size_graph() == 0)
        {
            throw std::out_of_range("directed_graph subscript vertex of range");
        }
    }

    void check_vertex(size_t first_vertex, size_t second_vertex) const
    {
        if (first_vertex >= size_graph() || second_vertex >= size_graph())
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