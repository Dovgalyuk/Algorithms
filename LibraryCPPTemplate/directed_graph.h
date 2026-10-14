#ifndef TEMPLATE_directionECTED_GRAPH
#define TEMPLATE_directionECTED_GRAPH

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

    Directed_Graph(size_t rows, size_t cols, const Edge &weight = Edge{}) : size_Graph(rows * cols), vec_Vertex(rows * cols), shape(Shape::Rectangle)
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

        fill_edges(weight);
    }

    Directed_Graph(const Directed_Graph &graph) : Graph(graph.Graph), size_Graph(graph.size_Graph), vec_Vertex(graph.vec_Vertex), shape(graph.shape)
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
            Shape tmp_shape = shape;

            Graph = tmp.Graph;
            size_Graph = tmp.size_Graph;
            vec_Vertex = tmp.vec_Vertex;
            shape = tmp.shape;

            tmp.Graph = tmp_Graph;
            tmp.size_Graph = tmp_size;
            tmp.vec_Vertex = tmp_vec_vertex;
            tmp.shape = tmp_shape;
        }
        return *this;
    }

    ~Directed_Graph() = default;

    static Directed_Graph make_triangle_by_rows(size_t rows, const Edge &weight = Edge{})
    {
        Directed_Graph triangle;

        triangle.shape = Shape::Triangle;

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

        triangle.fill_edges(weight);

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

        Vector<Cell> &row = Graph[0];

        if (index_vertex > 0)
        {
            row[index_vertex - 1].neighbour[RIGHT] = false;
        }
        if (index_vertex < size_Graph)
        {
            row[index_vertex].neighbour[LEFT] = false;
        }

        row.add(index_vertex, Cell{});

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

        line();

        Vector<Cell> &row = Graph[0];
        row.remove(index_vertex);

        if (row.size() == 0)
        {
            Graph.remove(0);
        }
        else
        {
            if (index_vertex > 0)
            {
                row[index_vertex - 1].neighbour[RIGHT] = false;
            }
            if (index_vertex < row.size())
            {
                row[index_vertex].neighbour[LEFT] = false;
            }
        }

        vec_Vertex.remove(index_vertex);
        size_Graph--;
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

        size_t direction = find_direction(first_vertex, second_vertex);

        if (direction == NONE)
        {
            throw std::invalid_argument("vertices are not neighbors");
        }

        Cell &from_vertex = cell(first_vertex);
        from_vertex.neighbour[direction] = true;
        from_vertex.weight[direction] = weight;
    }

    const Edge &operator()(size_t first_vertex, size_t second_vertex) const
    {
        check_vertex(first_vertex, second_vertex);

        return get_edge(first_vertex, second_vertex);
    }

    const Edge &get_edge(size_t first_vertex, size_t second_vertex) const
    {
        check_vertex(first_vertex, second_vertex);

        size_t direction = find_direction(first_vertex, second_vertex);
        const Cell &from_vertex = cell(first_vertex);

        if (direction == NONE || !from_vertex.neighbour[direction])
        {
            throw std::runtime_error("directed_graph edge not found");
        }

        return from_vertex.weight[direction];
    }

    void set_edge_weight(size_t first_vertex, size_t second_vertex, const Edge &weight)
    {
        check_vertex(first_vertex, second_vertex);

        size_t direction = find_direction(first_vertex, second_vertex);
        Cell &from_vertex = cell(first_vertex);

        if (direction == NONE || !from_vertex.neighbour[direction])
        {
            throw std::runtime_error("directed_graph edge not found");
        }

        from_vertex.weight[direction] = weight;
    }

    void remove_edge(size_t first_vertex, size_t second_vertex)
    {
        check_vertex(first_vertex, second_vertex);

        size_t direction = find_direction(first_vertex, second_vertex);

        if (direction != NONE)
        {
            cell(first_vertex).neighbour[direction] = false;
        }
    }

    bool edge(size_t first_vertex, size_t second_vertex) const
    {
        check_vertex(first_vertex, second_vertex);

        size_t direction = find_direction(first_vertex, second_vertex);

        return direction != NONE && cell(first_vertex).neighbour[direction];
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

        Directed_Graph line(n);
        for (size_t i = 0; i < n; i++)
        {
            if (!(input >> line.vec_Vertex[i]))
            {
                return input;
            }
        }

        size_t m = 0;

        if (input >> m)
        {
            bool line_b = true;
            bool triangle_b = n > 0;
            Directed_Graph triangle;

            if (triangle_b)
            {
                try
                {
                    triangle = make_triangle_by_vertices(n, Edge{});
                    triangle.clear_edges();
                    triangle.vec_Vertex = line.vec_Vertex;
                }
                catch (const std::invalid_argument &)
                {
                    triangle_b = false;
                }
            }

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

                if (line_b && line.find_direction(first, second) == NONE)
                {
                    line_b = false;
                }
                if (triangle_b && triangle.find_direction(first, second) == NONE)
                {
                    triangle_b = false;
                }

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

            if (triangle_b)
            {
                graph = std::move(triangle);
            }
            else
            {
                graph = std::move(line);
            }

            return input;
        }

        if (input.eof())
        {
            try
            {
                Directed_Graph triangle = make_triangle_by_vertices(n, Edge{});
                triangle.vec_Vertex = line.vec_Vertex;

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
            skip();
        }

        const Edge &weight() const
        {
            return iter_graph->cell(vertex_start).weight[vertex_end];
        }

        size_t operator*() const
        {
            size_t to_vertex = 0;
            iter_graph->neighbor(vertex_start, vertex_end, to_vertex);
            return to_vertex;
        }

        Iterator &operator++()
        {
            vertex_end++;
            skip();
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
        void skip()
        {
            if (vertex_end >= NONE)
            {
                return;
            }

            const Cell &from_vertex = iter_graph->cell(vertex_start);
            size_t to_vertex = 0;

            while (vertex_end < NONE && !(from_vertex.neighbour[vertex_end] && iter_graph->neighbor(vertex_start, vertex_end, to_vertex)))
            {
                vertex_end++;
            }
        }

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
        return Iterator(this, index_vertex, NONE);
    }

private:
    enum Dir
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        NONE
    };

    enum class Shape
    {
        Line,
        Rectangle,
        Triangle
    };

    struct Cell
    {
        Edge weight[NONE]{};
        bool neighbour[NONE]{};
    };

    Vector<Vector<Cell>> Graph;
    size_t size_Graph = 0;

    Vector<Vertex> vec_Vertex;

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

    bool neighbor(size_t vertex, size_t direction, size_t &to_vertex) const
    {
        size_t row = 0;
        size_t col = 0;

        location(vertex, row, col);

        size_t start = vertex - col;

        switch (direction)
        {
        case LEFT:
            if (col == 0)
            {
                return false;
            }
            to_vertex = vertex - 1;
            return true;

        case RIGHT:
            if (col + 1 >= Graph[row].size())
            {
                return false;
            }
            to_vertex = vertex + 1;
            return true;

        case UP:
            if (row == 0)
            {
                return false;
            }
            if (shape == Shape::Rectangle)
            {
                to_vertex = start - Graph[row - 1].size() + col;
                return true;
            }
            if (shape == Shape::Triangle && col % 2 == 1)
            {
                to_vertex = start - Graph[row - 1].size() + col - 1;
                return true;
            }
            return false;

        default: 
            if (row + 1 >= Graph.size())
            {
                return false;
            }
            if (shape == Shape::Rectangle)
            {
                to_vertex = start + Graph[row].size() + col;
                return true;
            }
            if (shape == Shape::Triangle && col % 2 == 0)
            {
                to_vertex = start + Graph[row].size() + col + 1;
                return true;
            }
            return false;
        }
    }

    size_t find_direction(size_t first_vertex, size_t to_vertex) const
    {
        for (size_t direction = 0; direction < NONE; direction++)
        {
            size_t t = 0;

            if (neighbor(first_vertex, direction, t) && t == to_vertex)
            {
                return direction;
            }
        }
        return NONE;
    }

    void fill_edges(const Edge &weight)
    {
        for (size_t vertex = 0; vertex < size_Graph; vertex++)
        {
            Cell &from_vertex = cell(vertex);

            for (size_t direction = 0; direction < NONE; direction++)
            {
                size_t to_vertex = 0;

                if (neighbor(vertex, direction, to_vertex))
                {
                    from_vertex.neighbour[direction] = true;
                    from_vertex.weight[direction] = weight;
                }
            }
        }
    }

    void clear_edges()
    {
        for (size_t vertex = 0; vertex < size_Graph; vertex++)
        {
            Cell &from_vertex = cell(vertex);

            for (size_t direction = 0; direction < NONE; direction++)
            {
                from_vertex.neighbour[direction] = false;
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
        for (size_t i = 0; i < size_Graph; i++)
        {
            row.add(row.size(), Cell{});
        }

        Vector<Vector<Cell>> flat;
        if (size_Graph > 0)
        {
            flat.add(0, row);
        }

        Graph = flat;
        shape = Shape::Line;
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