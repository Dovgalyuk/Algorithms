#include "../LibraryCPP/queue.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

constexpr int unvisited = -1;

struct Maze
{
    int width = 0;
    int start = unvisited;
    int finish = unvisited;
    std::vector<char> cells;

    int row_length(int row) const
    {
        return width - std::abs(row - width / 2);
    }

    int first_column(int row) const
    {
        return std::max(0, width / 2 - row);
    }
};

bool read_maze(std::istream &input, Maze &maze)
{
    std::vector<std::string> rows;
    for (std::string line; std::getline(input, line);)
    {
        const auto first = line.find_first_not_of(" \t\r");
        if (first == std::string::npos)
            return false;
        const auto last = line.find_last_not_of(" \t\r");
        rows.push_back(line.substr(first, last - first + 1));
    }

    const auto height = rows.size();
    if (input.bad() || height % 2 == 0 || height > std::numeric_limits<int>::max() / height)
        return false;

    maze.width = static_cast<int>(height);
    // Углы квадрата лежат за пределами шестиугольника и считаются стенами.
    maze.cells.assign(maze.width * maze.width, '#');
    for (int row = 0; row < maze.width; ++row)
    {
        const int length = maze.row_length(row);
        if (rows[row].size() != static_cast<std::size_t>(length))
            return false;

        const int row_start = row * maze.width + maze.first_column(row);
        for (int column = 0; column < length; ++column)
        {
            const char value = rows[row][column];
            const int cell = row_start + column;
            if (value == 'S')
            {
                if (maze.start != unvisited)
                    return false;
                maze.start = cell;
            }
            else if (value == 'E')
            {
                if (maze.finish != unvisited)
                    return false;
                maze.finish = cell;
            }
            else if (value != '.' && value != '#')
                return false;

            maze.cells[cell] = value;
        }
    }
    return maze.start != unvisited && maze.finish != unvisited;
}

struct Search
{
    std::vector<int> parent;
    Queue *frontier = queue_create();
    int layer_size = 1;

    Search(int start, std::size_t cell_count) : parent(cell_count, unvisited)
    {
        parent[start] = start;
    }

    ~Search()
    {
        queue_delete(frontier);
    }

    Search(const Search &) = delete;
    Search &operator=(const Search &) = delete;
};

int expand_layer(const Maze &maze, Search &search, const Search &other)
{
    constexpr int offsets[][2] = {{0, -1}, {0, 1}, {-1, 0}, {-1, 1}, {1, -1}, {1, 0}};
    Queue *frontier = search.frontier;
    int next_layer_size = 0;
    for (int i = 0; i < search.layer_size; ++i)
    {
        const int cell = queue_get(frontier);
        queue_remove(frontier);
        const int row = cell / maze.width;
        const int column = cell % maze.width;

        for (const auto &offset : offsets)
        {
            const int next_row = row + offset[0];
            const int next_column = column + offset[1];
            if (next_row < 0 || next_row >= maze.width ||
                next_column < 0 || next_column >= maze.width)
                continue;

            const int next = next_row * maze.width + next_column;
            if (maze.cells[next] == '#' || search.parent[next] != unvisited)
                continue;

            search.parent[next] = cell;
            if (other.parent[next] != unvisited)
                return next;

            queue_insert(frontier, next);
            ++next_layer_size;
        }
    }
    search.layer_size = next_layer_size;
    return unvisited;
}

void mark_path(Maze &maze, const Search &search, int meeting)
{
    int cell = meeting;
    while (cell != search.parent[cell])
    {
        if (maze.cells[cell] == '.')
            maze.cells[cell] = 'x';
        cell = search.parent[cell];
    }
}

bool find_shortest_path(Maze &maze)
{
    Search from_start(maze.start, maze.cells.size());
    Search from_finish(maze.finish, maze.cells.size());
    queue_insert(from_start.frontier, maze.start);
    queue_insert(from_finish.frontier, maze.finish);
    int meeting = unvisited;

    while (!queue_empty(from_start.frontier) && !queue_empty(from_finish.frontier))
    {
        // Один слой от S.
        meeting = expand_layer(maze, from_start, from_finish);
        if (meeting != unvisited)
            break;

        if (queue_empty(from_start.frontier))
            return false;

        // Один слой от E.
        meeting = expand_layer(maze, from_finish, from_start);
        if (meeting != unvisited)
            break;
    }

    if (meeting == unvisited)
        return false;

    mark_path(maze, from_start, meeting);
    mark_path(maze, from_finish, meeting);
    return true;
}

void print_border(int width, int length, char left, char right)
{
    std::cout << std::string(2 * (width - length) + 3, ' ');
    for (int column = 0; column < length; ++column)
    {
        if (column != 0)
            std::cout << ' ';
        std::cout << left << ' ' << right;
    }
    std::cout << '\n';
}

void print_maze(const Maze &maze)
{
    print_border(maze.width, maze.row_length(0), '/', '\\');
    for (int row = 0; row < maze.width; ++row)
    {
        const int length = maze.row_length(row);
        const int row_start = row * maze.width + maze.first_column(row);
        std::cout << std::string(2 * (maze.width - length) + 2, ' ');
        for (int column = 0; column < length; ++column)
            std::cout << "| " << maze.cells[row_start + column] << ' ';
        std::cout << "|\n";

        if (row < maze.width / 2)
            print_border(maze.width, maze.row_length(row + 1), '/', '\\');
        else
            print_border(maze.width, length, '\\', '/');
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: Lab3 <input file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Error: cannot open input file\n";
        return 1;
    }

    Maze maze;
    if (!read_maze(input, maze))
    {
        std::cerr << "Error: invalid hexagonal maze\n";
        return 1;
    }

    if (find_shortest_path(maze))
        print_maze(maze);
    else
        std::cout << "No path\n";
    return 0;
}
