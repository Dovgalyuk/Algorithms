#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include "AStar.h"
#include "vector.h"
#include "VectorGraph.h"

using TDDoubleVector = Vector<Vector<double>>;

class GridToGraphConverter {
public:
    static void readGridAndBuildGraph(
        const std::string &filename,
        const std::shared_ptr<IGraph<std::string, double>>& graph,
        std::size_t &start,
        std::size_t &goal,
        std::size_t& gridCols) {

        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        std::size_t rows, cols;
        file >> rows >> cols;

        TDDoubleVector grid;
        for (std::size_t i = 0; i < rows; ++i) {
            Vector<double> row;
            for (std::size_t j = 0; j < cols; ++j) {
                double value;
                file >> value;
                row.push_back(value);
            }
            grid.push_back(row);
        }

        std::size_t startRow, startCol, goalRow, goalCol;
        file >> startRow >> startCol >> goalRow >> goalCol;

        for (std::size_t i = 0; i < rows; ++i) {
            for (std::size_t j = 0; j < cols; ++j) {
                std::stringstream name;
                name << "(" << i << "," << j << ")";
                graph->addVertex(name.str());
            }
        }

        for (std::size_t i = 0; i < rows; ++i) {
            for (std::size_t j = 0; j < cols; ++j) {
                std::size_t current = i * cols + j;

                for (Vector<std::pair<int, int> > directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                        const auto &[di, dj]: directions) {

                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < static_cast<int>(rows) &&
                        nj >= 0 && nj < static_cast<int>(cols)) {
                        std::size_t neighbor = ni * cols + nj;
                        double cost = grid[ni][nj];
                        graph->addEdge(current, neighbor, cost);
                    }
                }
            }
        }

        start = startRow * cols + startCol;
        goal = goalRow * cols + goalCol;

        gridCols = cols;
    }
};

void pathVisualization(const Vector<std::size_t>& path,
                       const std::size_t cols, const std::size_t vertexCount,
                       std::ostream& output) {
    const std::size_t rows = vertexCount / cols;

    Vector display(rows, Vector<std::string>(cols, " . "));

    for (std::size_t i{}; i < path.size(); ++i) {
        const std::size_t current = path[i];
        const std::size_t row = current / cols;
        const std::size_t col = current % cols;

        std::stringstream ss;
        if (i == 0) ss << " S ";
        else if (i == path.size() - 1) ss << " G ";
        else ss << std::setw(2) << i << " ";

        display[row][col] = ss.str();
    }

    output << "Path:\n";
    for (std::size_t i{}; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            output << display[i][j];
        }
        output << std::endl;
    }
}

int main(const int argc, char* argv[]) {
    if (argc < 3) std::exit(1);

    const std::shared_ptr<IGraph<std::string, double>> graph = std::make_shared<VectorGraph<std::string, double>>();
    std::size_t start;
    std::size_t goal;
    std::size_t gridCols;

    GridToGraphConverter::readGridAndBuildGraph(argv[1], graph, start, goal, gridCols);

    std::ofstream output(argv[2]);
    if (auto path = AStar<double>::findPath(graph, start, goal, gridCols); !path.empty()) {
        output << "Steps: " << path.size() - 1;
        double totalCost{};
        for (std::size_t i{}; i < path.size(); ++i) {
            if (i < path.size() - 1) {
                totalCost += graph->getEdge(path[i], path[i + 1]);
            }
        }

        output << "\nTotal cost: " << totalCost << "\n";
        pathVisualization(path, gridCols, graph->vertexCount(), output);
    } else {
        output << "No path found!\n";
    }

    return 0;
}
