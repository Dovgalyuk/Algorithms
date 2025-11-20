#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include "graph.h"

const int INF = 1e9;

struct Node 
{
    int index;
    int cost;

    Node(int index, int cost): index(index), cost(cost){}
    
    bool operator>(const Node& other) const
    {
        return cost > other.cost;
    }
};

const int move_size = 4;
const int moves[move_size][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

int heuristic(int current, int finish, int cols)
{
    int current_row = current / cols;
    int current_col = current % cols;
    int finish_row = finish / cols;
    int finish_col = finish % cols;

    return abs(current_row - finish_row) + abs(current_col - finish_col);
}

std::vector<int> path(std::vector<int>& came_from, int start, int finish)
{
    std::vector<int> result;
    int current = finish;
    
    while (current != start) 
    {
        result.push_back(current);
        current = came_from[current];
    }
    result.push_back(start);
    
    std::reverse(result.begin(), result.end());

    return result;
}

std::vector<int> astar(Graph<int, int>& graph, int start, int finish, int cols)
{
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> queue;
    
    std::vector<int> came_from(graph.getVertexTags().size(), -1);
    std::vector<int> cost(graph.getVertexTags().size(), INF);
    
    cost[start] = 0;
    came_from[start] = start;
    
    int start_cost = heuristic(start, finish, cols);
    queue.push(Node(start, start_cost));
    
    while (!queue.empty()) 
    {
        Node current = queue.top();
        queue.pop();
        
        if (current.index == finish) 
        {
            break;
        }
        
        Graph<int, int>::Iterator end_it = graph.end(current.index);
        for (Graph<int, int>::Iterator it = graph.begin(current.index); it != end_it; ++it) 
        {
            int neighbor = *it;
            
            int new_cost = cost[current.index] + graph.getVertexTag(neighbor);
            
            if (new_cost < cost[neighbor]) 
            {
                cost[neighbor] = new_cost;
                came_from[neighbor] = current.index;    

                int total_cost = new_cost + heuristic(neighbor, finish, cols);
                queue.push(Node(neighbor, total_cost));
            }
        }
    }

    return path(came_from, start, finish);
}

void task(std::ifstream& file)
{
    int rows, cols;
    file >> rows >> cols;

    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            file >> matrix[i][j];
        }
    }

    int start_row, start_col, finish_row, finish_col;
    file >> start_row >> start_col >> finish_row >> finish_col;

    int start_index = start_row * cols + start_col;
    int finish_index = finish_row * cols + finish_col;

    Graph<int, int> graph(rows * cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            int index = i * cols + j;
            graph.setVertexTag(index, matrix[i][j]);
        }
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
 
            int from = i * cols + j;
            
            for (int k = 0; k < move_size; k++) 
            {
                int x = i + moves[k][0];
                int y = j + moves[k][1];
                
                if (x >= 0 && x < rows && y >= 0 && y < cols) 
                {
                    int to = x * cols + y;

                    Graph<int, int>::Edge edge(from, to);
                    graph.addEdge(edge);
                }
            }
        }
    }

    std::vector<int> result = astar(graph, start_index, finish_index, cols);
    for (size_t i = 0; i < result.size(); i++) 
    {
        int row = result[i] / cols;
        int col = result[i] % cols;

        std::cout << "(" << row << ", " << col << ")" << std::endl;
    }

    int cost = 0;
    for(size_t i = 0; i < result.size(); i++)
    {
        cost += matrix[result[i] / cols][result[i] % cols];
    }
    std::cout << cost << std::endl;
}

int main(int argc, char **argv)
{
    std::ifstream file(argv[1]);
    task(file);
    file.close();
}