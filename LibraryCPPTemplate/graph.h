#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include "vector.h"

#include <algorithm>
#include <cstdint>
#include <istream>
#include <limits>
#include <map>
#include <optional>
#include <stdexcept>
#include <utility>

using namespace std;

using GridVertex = pair<size_t, size_t>;  // cтрока столбец

template <typename EdgeLabel, typename VertexLabel>
class Graph
{
    using Edges = map<GridVertex, EdgeLabel>;

    struct Cell
    {
        optional<VertexLabel> label{in_place};
        Edges outgoing;
    };

public:
    struct NeighborIterator
    {
        typename Edges::const_iterator current;

        const GridVertex &operator*() const
        {
            return current->first;
        }

        NeighborIterator &operator++()
        {
            ++current;
            return *this;
        }

        bool operator!=(const NeighborIterator &other) const
        {
            return current != other.current;
        }
    };

    struct NeighborRange
    {
        NeighborIterator first;
        NeighborIterator last;

        NeighborIterator begin() const { return first; }
        NeighborIterator end() const { return last; }
    };

    explicit Graph(size_t vertexCount = 0) : Graph(1, vertexCount)
    {
    }

    Graph(size_t rows, size_t columns) : rowCount(rows), columnCount(columns)
    {
        if (columns != 0 && rows > numeric_limits<size_t>::max() / columns)
            throw length_error("Grid is too large");

        cells.resize(rows * columns);
    }

    size_t rows() const { return rowCount; }
    size_t columns() const { return columnCount; }

    bool hasVertex(GridVertex vertex) const
    {
        return inside(vertex) && cell(vertex).label.has_value();
    }

    // изменение размера сетки 
    // новые вершины получают пометки по умолчанию
    void resize(size_t rows, size_t columns)
    {
        Graph replacement(rows, columns);
        const size_t keptRows = min(rows, rowCount);
        const size_t keptColumns = min(columns, columnCount);

        for (size_t row = 0; keptColumns != 0 && row < keptRows; ++row)
        {
            for (size_t column = 0; column < keptColumns; ++column)
            {
                const GridVertex vertex{row, column};
                auto &target = replacement.cell(vertex);
                target = cell(vertex);

                for (auto edge = target.outgoing.begin(); edge != target.outgoing.end();)
                {
                    if (!replacement.inside(edge->first))
                        edge = target.outgoing.erase(edge);
                    else
                        ++edge;
                }
            }
        }

        *this = move(replacement);
    }

    // добавление вершины обратно в ранее удалённую клетку
    bool addVertex(GridVertex vertex, const VertexLabel &label = VertexLabel{})
    {
        if (!inside(vertex) || hasVertex(vertex))
            return false;

        cell(vertex).label.emplace(label);
        return true;
    }

    // удаление вершины и все её входящие и исходящие рёбра
    bool removeVertex(GridVertex vertex)
    {
        if (!hasVertex(vertex))
            return false;

        cell(vertex).label.reset();
        cell(vertex).outgoing.clear();

        for (size_t i = 0; i < cells.size(); ++i)
            cells[i].outgoing.erase(vertex);

        return true;
    }

    // добавление ориентированного ребра из from в to с заданной пометкой
    bool addEdge(GridVertex from, GridVertex to, const EdgeLabel &label = EdgeLabel{})
    {
        return hasVertex(from) && hasVertex(to) && cell(from).outgoing.emplace(to, label).second;
    }

    // удаление ребра из from в to, если оно существует
    bool removeEdge(GridVertex from, GridVertex to)
    {
        return hasVertex(from) && cell(from).outgoing.erase(to) != 0;
    }

    // проверка существует ли ребро из from в to
    bool hasEdge(GridVertex from, GridVertex to) const
    {
        return hasVertex(from) && cell(from).outgoing.count(to) != 0;
    }

    // возврат пометки ребра из from в to
    const EdgeLabel &edgeLabel(GridVertex from, GridVertex to) const
    {
        requireVertex(from);
        return cell(from).outgoing.at(to);
    }

    // присвоение пометки существующего ребра из from в to
    void setEdgeLabel(GridVertex from, GridVertex to, const EdgeLabel &label)
    {
        requireVertex(from);
        cell(from).outgoing.at(to) = label;
    }

    // возврат пометки вершины
    const VertexLabel &vertexLabel(GridVertex vertex) const
    {
        requireVertex(vertex);
        return *cell(vertex).label;
    }

    // присвоение пометки существующей вершины
    void setVertexLabel(GridVertex vertex, const VertexLabel &label)
    {
        requireVertex(vertex);
        *cell(vertex).label = label;
    }

    // возврат вектора пометок всех существующих вершин в порядке строк
    Vector<VertexLabel> vertexLabels() const
    {
        Vector<VertexLabel> result;

        for (size_t i = 0; i < cells.size(); ++i)
        {
            if (cells[i].label)
            {
                const size_t index = result.size();
                result.resize(index + 1);
                result.set(index, *cells[i].label);
            }
        }

        return result;
    }

    // возврат диапазона для перебора исходящих соседей вершины
    NeighborRange neighbors(GridVertex vertex) const
    {
        requireVertex(vertex);
        const auto &edges = cell(vertex).outgoing;
        return {{edges.begin()}, {edges.end()}};
    }

    // чтение графа из потока: размеры, пометки вершин по строкам, число рёбер и записи о рёбрах (строка_от столбец_от строка_до столбец_до пометка_ребра)
    friend istream &operator>>(istream &input, Graph &graph)
    {
        long long rows = 0;
        long long columns = 0;
        if (!(input >> rows >> columns))
            return input;

        if (rows < 0 || columns < 0 ||
            static_cast<uintmax_t>(rows) > numeric_limits<size_t>::max() ||
            static_cast<uintmax_t>(columns) > numeric_limits<size_t>::max())
        {
            input.setstate(ios::failbit);
            return input;
        }

        try
        {
            Graph parsed(static_cast<size_t>(rows), static_cast<size_t>(columns));

            for (size_t i = 0; i < parsed.cells.size(); ++i)
            {
                if (!(input >> *parsed.cells[i].label))
                    return input;
            }

            long long edgeCount = 0;
            if (!(input >> edgeCount))
                return input;

            if (edgeCount < 0)
            {
                input.setstate(ios::failbit);
                return input;
            }

            for (long long i = 0; i < edgeCount; ++i)
            {
                long long r1 = 0, c1 = 0, r2 = 0, c2 = 0;
                EdgeLabel label{};
                if (!(input >> r1 >> c1 >> r2 >> c2 >> label))
                    return input;

                if (r1 < 0 || r1 >= rows || c1 < 0 || c1 >= columns ||
                    r2 < 0 || r2 >= rows || c2 < 0 || c2 >= columns ||
                    !parsed.addEdge(
                        {static_cast<size_t>(r1), static_cast<size_t>(c1)},
                        {static_cast<size_t>(r2), static_cast<size_t>(c2)},
                        label))
                {
                    input.setstate(ios::failbit);
                    return input;
                }
            }

            graph = move(parsed);
        }
        catch (const length_error &)
        {
            input.setstate(ios::failbit);
        }

        return input;
    }

private:
    size_t rowCount;
    size_t columnCount;
    Vector<Cell> cells;

    bool inside(GridVertex vertex) const
    {
        return vertex.first < rowCount && vertex.second < columnCount;
    }

    size_t index(GridVertex vertex) const
    {
        return vertex.first * columnCount + vertex.second;
    }

    Cell &cell(GridVertex vertex) { return cells[index(vertex)]; }
    const Cell &cell(GridVertex vertex) const { return cells[index(vertex)]; }

    void requireVertex(GridVertex vertex) const
    {
        if (!hasVertex(vertex))
            throw out_of_range("Vertex does not exist");
    }
};

#endif