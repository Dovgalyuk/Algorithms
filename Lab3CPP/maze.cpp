#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include "queue.h"

namespace
{
struct Cell
{
    int value;
    size_t row;
    size_t column;
    size_t text_begin;
    size_t text_length;
    bool reached;
};

struct Row
{
    size_t text_line;
    size_t offset;
    std::vector<int> cells;
};

int parse_number(const std::string &token)
{
    size_t consumed = 0;
    int value = std::stoi(token, &consumed);
    if (consumed != token.size())
        throw std::runtime_error("Invalid cell value: " + token);
    return value;
}

void solve(std::istream &input)
{
    std::vector<std::string> lines;
    std::vector<Row> rows;
    std::vector<Cell> cells;
    std::string line;
    size_t width = 0;
    while (std::getline(input, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        Row row{lines.size(), 0, {}};
        size_t position = 0;
        while (position < line.size())
        {
            if (std::isspace(static_cast<unsigned char>(line[position])))
            {
                ++position;
                continue;
            }
            size_t begin = position;
            while (position < line.size() &&
                   !std::isspace(static_cast<unsigned char>(line[position])))
                ++position;
            if (cells.size() >= static_cast<size_t>(std::numeric_limits<int>::max()))
                throw std::runtime_error("Too many cells");
            int value = parse_number(line.substr(begin, position - begin));
            row.cells.push_back(static_cast<int>(cells.size()));
            cells.push_back({value, rows.size(), row.cells.size() - 1,
                             begin, position - begin, false});
        }
        if (!row.cells.empty())
        {
            if (row.cells.size() > width)
                width = row.cells.size();
            rows.push_back(row);
        }
        lines.push_back(line);
    }
    if (input.bad())
        throw std::runtime_error("Cannot read maze");
    if (cells.empty())
        throw std::runtime_error("Maze contains no cells");

    size_t start_row = 0;
    for (size_t r = 0; r < rows.size(); ++r)
    {
        if ((width - rows[r].cells.size()) % 2 != 0)
            throw std::runtime_error("Rows cannot be centered on the same cell grid");
        rows[r].offset = (width - rows[r].cells.size()) / 2;
        if (rows[r].offset < rows[start_row].offset)
            start_row = r;
    }

    std::unique_ptr<Queue, decltype(&queue_delete)> pending(queue_create(), queue_delete);
    int start = rows[start_row].cells.front();
    cells[start].reached = true;
    queue_insert(pending.get(), start);

    while (!queue_empty(pending.get()))
    {
        int current = queue_get(pending.get());
        queue_remove(pending.get());
        const Cell &cell = cells[current];
        size_t column = rows[cell.row].offset + cell.column;
        auto visit = [&](int next)
        {
            long long difference = static_cast<long long>(cells[next].value) - cell.value;
            if (!cells[next].reached && (difference == 1 || difference == -1))
            {
                cells[next].reached = true;
                queue_insert(pending.get(), next);
            }
        };
        if (cell.column > 0)
            visit(rows[cell.row].cells[cell.column - 1]);
        if (cell.column + 1 < rows[cell.row].cells.size())
            visit(rows[cell.row].cells[cell.column + 1]);
        auto visit_row = [&](size_t r)
        {
            if (column >= rows[r].offset && column - rows[r].offset < rows[r].cells.size())
                visit(rows[r].cells[column - rows[r].offset]);
        };
        if (cell.row > 0)
            visit_row(cell.row - 1);
        if (cell.row + 1 < rows.size())
            visit_row(cell.row + 1);
    }

    for (const Cell &cell : cells)
    {
        if (!cell.reached)
        {
            // Keep the width even when an unreachable number has several digits.
            std::string marker(cell.text_length, ' ');
            marker[0] = '#';
            lines[rows[cell.row].text_line].replace(cell.text_begin, cell.text_length, marker);
        }
    }
    for (const std::string &text : lines)
        std::cout << text << '\n';
    if (!std::cout)
        throw std::runtime_error("Cannot write output");
}
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: Maze <input-file>\n";
        return 1;
    }
    try
    {
        std::ifstream input(argv[1]);
        if (!input)
            throw std::runtime_error("Cannot open input file");
        solve(input);
        return 0;
    }
    catch (const std::exception &error)
    {
        std::cerr << "Maze: " << error.what() << '\n';
        return 1;
    }
}
