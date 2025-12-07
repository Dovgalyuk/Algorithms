#include "avl.h"
#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include <random>
#include <string>
#include <vector>

void generate(std::string& filename, int n) 
{
    std::ofstream f(filename);
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for(int i = 0; i < n; i++) 
    {
        std::string k = "k" + std::to_string(gen() % 1000000);
        std::string v = "v" + std::to_string(i);
        f << k << " " << v << "\n";
    }

    f.close();
}

long long test_avl(std::string& filename) 
{
    std::ifstream f(filename);
    std::string k, v;
    AVL t;
    
    auto start = std::chrono::high_resolution_clock::now();
    while(f >> k >> v) 
    {
        t.add(k, v);
    }
    auto end = std::chrono::high_resolution_clock::now();
    
    f.close();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

long long test_map(std::string& filename) 
{
    std::ifstream f(filename);
    std::string k, v;
    std::map<std::string, std::string> m;
    
    auto start = std::chrono::high_resolution_clock::now();
    while(f >> k >> v) 
    {
        m.insert({k, v});
    }
    auto end = std::chrono::high_resolution_clock::now();
    
    f.close();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main() 
{
    std::vector<int> sizes = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    
    std::cout << "Size\tAVL (ms)\tmap (ms)" << std::endl;
    
    for(int n : sizes) 
    {
        std::string filename = "test_" + std::to_string(n) + ".txt";
        generate(filename, n);
        
        std::cout << "Testing " << n << ":" << std::endl;

        long long avl_time = test_avl(filename);
        long long map_time = test_map(filename);
        
        std::cout << n << "\t" << avl_time << "\t\t" << map_time << std::endl;
    }
}