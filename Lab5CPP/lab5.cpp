#include "map.h"
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;

struct Res
{
    string l;
    long long time;
};

vector<Res> res;

vector<pair<string, string>> random_data(int count)
{
    vector<pair<string, string>> data;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, count*10);

    for(int i = 0; i < count; i++)
    {
        string key = "key_" + to_string(dist(gen));
        string value = "value_" + to_string(i);
        data.emplace_back(key, value);
    }
    return data;
}

void cmp_with_random(int size)
{
    auto test = random_data(size);

    auto start = chrono::high_resolution_clock::now();
    Map splay_map;
    for(const auto& pair : test) splay_map.insert(pair.first, pair.second);
    auto end = chrono::high_resolution_clock::now();
    long long splay_time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::high_resolution_clock::now();
    map<string, string> std_map;
    for(const auto& pair : test) std_map[pair.first] = pair.second;
    end = chrono::high_resolution_clock::now();
    long long std_time   = chrono::duration_cast<chrono::microseconds>(end - start).count();

    res.push_back({"Splay (" + to_string(size) + ")", splay_time});
    res.push_back({"std::map (" + to_string(size) + ")", std_time});
}

void cmp()
{
    vector<int> sizes = {1000, 5000, 10000, 50000, 100000};

    for(int s : sizes)
    {
        cmp_with_random(s);
    }
}

void print_graph()
{
    long long max_time = 0;
    for (auto& r : res)
        max_time = max(max_time, r.time);

    const int LABEL_W = 22;   
    const int GRAPH_W = 70;    
    const int TIME_W  = 12;  

    for (auto& r : res)
    {
        int bar_len = (double(r.time) / max_time) * GRAPH_W;

        cout << left << setw(LABEL_W) << r.l; 
        cout << " | ";

        cout << string(bar_len, '#');           
        cout << setw(GRAPH_W - bar_len) << "";  

        cout << " | ";

        cout << right << setw(TIME_W)          
             << r.time << " us";

        cout << "\n";
    }
}

int main(int argc, char* argv[])
{
    if(argc < 2) return 1;

    cmp();
    ifstream file(argv[1]);
    vector<pair<string, string>> data;
    string a, b;
    size_t count_word = 0;
    string w;

    while(file >> w)
        count_word++;

    if(count_word % 2 != 0)
        cout << "Odd number of words found in file. Last word will be ignored.\n";

    file.clear();
    file.seekg(0);

    while(file >> a >> b)
    {
        data.emplace_back(a, b);
    }
    file.close();

    auto start = chrono::high_resolution_clock::now();
    Map splay_map;
    for(const auto& pair : data)
    {
        splay_map.insert(pair.first, pair.second);
    }
    auto end = chrono::high_resolution_clock::now();
    long long splay_time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::high_resolution_clock::now();
    map<string, string> std_map;
    for(const auto& pair : data)
    {
        std_map[pair.first] = pair.second;
    }
    end = chrono::high_resolution_clock::now();
    long long std_time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Pairs read: " << data.size() << endl;
    cout << "Unique keys(splay_map): " << splay_map.size() << endl;
    cout << "Unique keys(std::map): " << std_map.size() << endl;

    res.push_back({"Splay (file)", splay_time});
    res.push_back({"std::map (file)", std_time});

    print_graph();
}