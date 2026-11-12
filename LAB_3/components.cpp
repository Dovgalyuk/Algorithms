#include "queue.h"
#include <fstream>
#include <iostream>
#include <vector>

typedef std::vector<int> Row;
typedef std::vector<Row> Matrix;

int findComponents(const Matrix &graph, Vector &component)
{
    int n = static_cast<int>(graph.size());
    component.resize(0);
    component.resize(n);
    Queue queue;
    int count = 0;
    for (int start = 0; start < n; start++)
    {
        if (component.get(start) != 0) continue;
        count++;
        component.set(start, count);
        queue.insert(start);
        while (!queue.empty())
        {
            int vertex = queue.get();
            queue.remove();
            for (int next = 0; next < n; next++)
            {
                if (graph[vertex][next] != 0 && component.get(next) == 0)
                {
                    // Mark on insertion so a vertex enters the queue only once.
                    component.set(next, count);
                    queue.insert(next);
                }
            }
        }
    }
    return count;
}

int main(int argc, char *argv[])
{
    const char *inputName = DEFAULT_INPUT_FILE;
    const char *outputName = "output.txt";
    if (argc > 1) inputName = argv[1];
    if (argc > 2) outputName = argv[2];
    if (argc > 3)
    {
        std::cerr << "Usage: Lab3Components [input.txt] [output.txt]\n";
        return 1;
    }
    std::ifstream input(inputName);
    int n = 0;
    if (!(input >> n) || n < 0)
    {
        std::cerr << "Cannot read vertex count\n";
        return 1;
    }
    Matrix graph(n, Row(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!(input >> graph[i][j]) || (graph[i][j] != 0 && graph[i][j] != 1))
            {
                std::cerr << "Expected a 0/1 adjacency matrix\n";
                return 1;
            }
        }
    }
    input >> std::ws;
    if (!input.eof())
    {
        std::cerr << "Unexpected data after the matrix\n";
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (graph[i][j] != graph[j][i])
            {
                std::cerr << "The graph must be undirected\n";
                return 1;
            }
        }
    }

    Vector component;
    int count = findComponents(graph, component);

    std::ofstream output(outputName);
    if (!output.is_open())
    {
        std::cerr << "Cannot open output file\n";
        return 1;
    }
    output << count << '\n';
    for (int number = 1; number <= count; number++)
    {
        bool first = true;
        for (int vertex = 0; vertex < n; vertex++)
        {
            if (component.get(vertex) == number)
            {
                if (!first) output << ' ';
                output << vertex + 1;
                first = false;
            }
        }
        output << '\n';
    }
    output.close();
    if (!output)
    {
        std::cerr << "Cannot write output file\n";
        return 1;
    }
    return 0;
}
