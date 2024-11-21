#include "lab3.h"
#include <iostream>
#include <fstream>
#include <map>
#include <optional>
#include <vector>
#include <functional>
#include <set>
#include <utility>

std::vector<std::string> maze;
std::set<Data> reachableCells;
Data startCell;

char getPointValue(Data currentCell)
{
    char wall = '#';
    if (size_t (currentCell.first) < maze.size() && size_t(currentCell.second) < maze.at(currentCell.first).size())
    {
        return maze.at(currentCell.first).at(currentCell.second);
    }
    return wall;
}

void appendLine(std::string currentLine)
{
    for (size_t colIndex = 0; colIndex < currentLine.size(); colIndex++)
    {
        if (currentLine[colIndex] == 'X')
        {
            startCell = {maze.size(), colIndex};
        }
    }
    maze.push_back(currentLine);
}

bool checkIsPointAccessible(Data currentCell)
{
    return getPointValue(currentCell) != '#' && reachableCells.count({currentCell.first, currentCell.second}) == 0;
}

void process()
{
    auto queue = queue_create();
    queue_insert(queue, startCell);
    while (!queue_empty(queue))
    {
        Data currentCell = queue_get(queue);
        queue_remove(queue);
        if (checkIsPointAccessible(currentCell))
        {
            reachableCells.insert(currentCell);
        }

        if (currentCell.first > 0)
        {
            Data neighborCell = {currentCell.first - 1, currentCell.second};
            if (checkIsPointAccessible(neighborCell))
            {
                queue_insert(queue, neighborCell);
            }
        }

        if (currentCell.second > 0)
        {
            Data neighborCell = {currentCell.first, currentCell.second - 1};
            if (checkIsPointAccessible(neighborCell))
            {
                queue_insert(queue, neighborCell);
            }
        }

        if (size_t (currentCell.first) < maze.size())
        {
            Data neighborCell = {currentCell.first + 1, currentCell.second};
            if (checkIsPointAccessible(neighborCell))
            {
                queue_insert(queue, neighborCell);
            }
        }

        if (size_t (currentCell.second) < maze.at(currentCell.first).size())
        {
            Data neighborCell = {currentCell.first, currentCell.second + 1};
            if (checkIsPointAccessible(neighborCell))
            {
                queue_insert(queue, neighborCell);
            }
        }
    }
    queue_delete(queue);
}

void Algorithm(std::ifstream &input)
{
    std::string currentLine;
    std::vector<std::string> mazeLines;

    while (!input.eof())
    {
        std::getline(input, currentLine);
        appendLine(currentLine);
        mazeLines.push_back(currentLine);
    }

    process();

    std::cout << std::to_string(reachableCells.size()) << std::endl;

    for (size_t rowIndex = 0; rowIndex < mazeLines.size(); rowIndex++)
    {
        auto updatedLine = mazeLines[rowIndex];
        for (size_t colIndex = 0; colIndex < mazeLines[rowIndex].size(); colIndex++)
        {
            if (reachableCells.count({rowIndex, colIndex}) > 0)
            {
                updatedLine[colIndex] = 'X';
            }
        }
        std::cout << updatedLine << std::endl;
    }
}
