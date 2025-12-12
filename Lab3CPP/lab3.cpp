#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "vector.h"
#include "queue.h"

typedef std::vector<std::pair<std::string, int>> NeighborsList;
typedef std::unordered_map<std::string, size_t> Map;
typedef std::vector<std::string> StringVector;

class PuzzleSolver
{
public:
        bool solve(const std::string& start_state) 
        {
            if (start_state == goal_state) return true;
            
            // Инициализация
            Queue q;
            state_to_index.clear();
            states.clear();
            
            int start_index = 0;
            states.push_back(start_state);
            state_to_index[start_state] = start_index;
            
            parents.resize(1);
            
            q.insert(start_index);
            
            while (!q.empty()) 
            {
                int current_index = q.get();
                q.remove();
                
                std::string current_state = states[current_index];
                
                auto neighbors = get_neighbors(current_state);
                
                for (const auto& neighbor_pair : neighbors)
                {
                    const std::string& neighbor = neighbor_pair.first;
                    
                    // Если достигли цель
                    if (neighbor == goal_state) 
                    {
                        size_t new_index = states.size();
                        states.push_back(neighbor);
                        parents.resize(states.size());
                        
                        parents.set(new_index, current_index);
                        return true;
                    }
                    
                    // Если состояние еще не посещено
                    if (!state_to_index.contains(neighbor)) 
                    {
                        size_t new_index = states.size();
                        states.push_back(neighbor);
                        state_to_index[neighbor] = new_index;
                        
                        parents.resize(states.size());
                        parents.set(new_index, current_index);
                        
                        q.insert((int)new_index);
                    }
                }
            }
            
            return false;
        }   

        void print_solution_path() 
        {
            auto path = get_solution_path();
            
            if (path.empty()) {
                std::cout << "No solution found!\n";
                return;
            }
            
            for (const auto& state : path) 
            {
                for (int row = 0; row < 3; row++) 
                {
                    std::cout << "|";
                    for (int col = 0; col < 3; col++) 
                    {
                        char cell = state[row * 3 + col];
                        std::cout << cell;
                        if (col < 2) {
                            std::cout << "-";
                        }
                    }
                    std::cout << "|\n";
                }
                std::cout << " -----\n";
            }
        }

private:
    const std::string goal_state = "123456780";
    
    Map state_to_index;
    StringVector states;
    Vector parents;
    
    int find_zero(const std::string& state) 
    {
        size_t pos = state.find('0');
        if(pos != std::string::npos) return (int)pos;
        return -1;
    }
    
    std::string swap(std::string state, int i, int j)
    {
        std::swap(state[i], state[j]); 
        return state;
    }
    
    NeighborsList get_neighbors(const std::string& state) 
    {
        NeighborsList neighbors;
        int zero_pos = find_zero(state);
        int row = zero_pos / 3;
        int col = zero_pos % 3;
        
        // Определяем возможные ходы и соответствующие индексы
        if (row > 0) {  // Вверх (0 меняется с элементом выше)
            neighbors.emplace_back(swap(state, zero_pos, zero_pos - 3), zero_pos - 3);
        }
        if (row < 2) {  // Вниз (0 меняется с элементом ниже)
            neighbors.emplace_back(swap(state, zero_pos, zero_pos + 3), zero_pos + 3);
        }
        if (col > 0) {  // Влево (0 меняется с элементом слева)
            neighbors.emplace_back(swap(state, zero_pos, zero_pos - 1), zero_pos - 1);
        }
        if (col < 2) {  // Вправо (0 меняется с элементом справа)
            neighbors.emplace_back(swap(state, zero_pos, zero_pos + 1), zero_pos + 1);
        }
        
        return neighbors;
    }

    StringVector get_solution_path()
    {
        StringVector path;
            
        if (states.empty() || states.back() != goal_state)
        {
            return path;
        }
            
        // Восстанавливаем путь от конечного состояния к начальному
        std::vector<int> indices;
        int current = (int)states.size() - 1;
            
        while (current != -1) 
        {
            indices.push_back((int)current);
            current = parents.get(current);
        }
            
        // Переворачиваем путь (от начального к конечному)
        for (int i = (int)indices.size() - 1; i >= 0; i--)
        {
            path.push_back(states[indices[i]]);
        }
            
        return path;
    }
};


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in)
    {
        return 1;
    }

    std::string start_state;
    if (!(in >> start_state) || start_state.size() != 9)
    {
        return 1;
    }
    
    if (start_state.length() != 9) 
    {
        return 1;
    }
    
    // Проверка, что строка содержит только цифры 0-8 и все цифры разные
    std::string sorted = start_state;
    std::sort(sorted.begin(), sorted.end());
    if (sorted != "012345678")
    {
        return 1;
    }
    
    PuzzleSolver solver;
    
    if (solver.solve(start_state))
    {
        solver.print_solution_path();
    }
    
    return 0;
}