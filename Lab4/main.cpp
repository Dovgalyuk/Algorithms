#include <fstream>
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
        std::size_t& gridCols,
        double& minCost) {

        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        minCost = std::numeric_limits<double>::infinity();

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

                if (grid[i][j] < minCost) minCost = grid[i][j];

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

int main(const int argc, char *argv[]) {
    if (argc < 3) std::exit(1);
    std::ofstream output(argv[2]);

    const std::shared_ptr<IGraph<std::string, double>> graph = std::make_shared<VectorGraph<std::string, double>>();
    std::size_t start;
    std::size_t goal;
    std::size_t gridCols;
    double minCost;

    GridToGraphConverter::readGridAndBuildGraph(argv[1], graph, start, goal, gridCols, minCost);

    if (auto path = AStar<double>::findPath(graph, start, goal, gridCols, minCost); !path.empty()) {
        output << "Steps: " << path.size() - 1 << "\n";
        output << "Path: ";
        double totalCost = 0;
        for (std::size_t i = 0; i < path.size(); ++i) {
            if (i > 0) output << " -> ";
            output << graph->getVertex(path[i]);

            if (i < path.size() - 1) {
                totalCost += graph->getEdge(path[i], path[i + 1]);
            }
        }
        output << "\nTotal cost: " << totalCost << "\n";
    } else {
        output << "No path found!\n";
    }

    return 0;
}
