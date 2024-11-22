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
std::vector<std::vector<bool>> reachableCells; 
Data startCell; 
size_t foundCount = 1; 
 
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
    return getPointValue(currentCell) != '#' && !reachableCells[currentCell.first][currentCell.second]; 
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
            reachableCells[currentCell.first][currentCell.second] = true; 
            foundCount++; 
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
    std::vector<std::string> mazeLines; 
 
    while (!input.eof()) 
    { 
        mazeLines.push_back(std::string()); 
        std::getline(input, mazeLines.back()); 
        appendLine(mazeLines.back()); 
        reachableCells.push_back(std::vector<bool>(mazeLines.back().size(),false));
    } 
 
    process(); 
 
    std::cout << std::to_string(foundCount) << std::endl; 
 
    for (size_t rowIndex = 0; rowIndex < mazeLines.size(); rowIndex++) 
    { 
        auto updatedLine = mazeLines[rowIndex]; 
        for (size_t colIndex = 0; colIndex < mazeLines[rowIndex].size(); colIndex++) 
        { 
            if (reachableCells[rowIndex][colIndex]) 
            { 
                updatedLine[colIndex] = 'X'; 
            } 
        } 
        std::cout << updatedLine << std::endl; 
    } 
}
