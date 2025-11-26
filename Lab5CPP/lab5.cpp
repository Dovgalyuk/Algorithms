#include "map.h"
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>

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
    for(const auto& pair : test) std_map.insert(pair);
    end = chrono::high_resolution_clock::now();
    long long std_time   = chrono::duration_cast<chrono::microseconds>(end - start).count();

    res.push_back({"Splay (" + to_string(size) + ")", splay_time});
    res.push_back({"std::map (" + to_string(size) + ")", std_time});
}

void cmp()
{
    vector<size_t> sizes = {1000, 5000, 10000, 50000, 100000, 1000000, 10000000};

    for(int s : sizes)
    {
        cmp_with_random(s);
    }
}

void print_time()
{
    long long max_time = 0;
    for (auto& r : res)
        max_time = max(max_time, r.time);

    const int LABEL_W = 22;   
    const int TIME_W  = 12;  

    for (auto& r : res)
    {
        cout << left << setw(LABEL_W) << r.l; 
        cout << " | ";

        cout << right << setw(TIME_W)          
             << r.time << " us";

        cout << "\n";
    }
}

vector<long long> smooth(const vector<long long>& vals, int pts)
{
    vector<long long> result;
    for(size_t i = 0; i < vals.size() - 1; i++)
    {
        result.push_back(vals[i]);
        for(int j = 1; j < pts; j++)
        {
            long long s = vals[i] + (vals[i+1] - vals[i]) * j / pts;
            result.push_back(s);
        }
    }
    result.push_back(vals.back());
    return result;
}

void print_graph()
{
    vector<size_t> sizes;
    vector<long long> splay_times;
    vector<long long> std_times;
    
    for (auto& r : res) {
        if (r.l.find("(file)") != string::npos) continue;
        
        size_t start = r.l.find('(') + 1;
        size_t end = r.l.find(')');
        if (start != string::npos && end != string::npos) {
            int size = stoi(r.l.substr(start, end - start));
            
            if (r.l.find("Splay") != string::npos) {
                sizes.push_back(size);
                splay_times.push_back(r.time);
            } else if (r.l.find("std::map") != string::npos) {
                std_times.push_back(r.time);
            }
        }
    }

    if (sizes.empty()) return;

    const int WIDTH = 80;
    const int HEIGHT = 25;
    const int LABEL_WIDTH = 12;
    
    vector<vector<char>> field(HEIGHT, vector<char>(WIDTH, ' '));
    
    long long max_time = 0;
    for (auto t : splay_times) max_time = max(max_time, t);
    for (auto t : std_times) max_time = max(max_time, t);
    
    for (int x = 0; x < WIDTH; x++) field[HEIGHT-1][x] = '-'; 
    for (int y = 0; y < HEIGHT; y++) field[y][0] = '|';       
    field[HEIGHT-1][0] = '+'; 
    
    vector<long long> smooth_splay = smooth(splay_times, 3);
    vector<long long> smooth_std = smooth(std_times, 3);
    
    for (size_t i = 0; i < smooth_splay.size(); i++) { 
        int x = (i * (WIDTH - 2)) / smooth_splay.size() + 1; 
        int y = HEIGHT - 2 - (smooth_splay[i] * (HEIGHT - 3)) / max_time; 
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) { 
            field[y][x] = '*'; 
        } 
    }

    for (size_t i = 0; i < smooth_std.size(); i++) {
        int x = (i * (WIDTH - 2)) / smooth_std.size() + 1;
        int y = HEIGHT - 2 - (smooth_std[i] * (HEIGHT - 3)) / max_time;
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            if (field[y][x] == ' ') {
                field[y][x] = '+';
            } else if (field[y][x] == '*') {
                field[y][x] = 'X'; 
            }
        }
    }
    
    for (size_t i = 0; i < sizes.size(); i++) {
        int x = (i * (WIDTH - 2)) / (sizes.size() - 1) + 1;
        string label = to_string(sizes[i] / 1000) + "K";
        if (x + label.length() <= WIDTH) {
            for (size_t j = 0; j < label.length(); j++) {
                field[HEIGHT-1][x+j] = label[j];
            }
        }
    }
    
    vector<string> y_labels(HEIGHT, string(LABEL_WIDTH, ' ')); 

    vector<int> label_rows = {0, HEIGHT/4, HEIGHT/2, 3*HEIGHT/4, HEIGHT-1};
    for (int y : label_rows) {
        long long t = (long long)((HEIGHT - 1 - y) / (double)(HEIGHT - 1) * max_time);
        string s = to_string(t) + " us";
        if ((int)s.size() < LABEL_WIDTH)
            s = string(LABEL_WIDTH - s.size(), ' ') + s;
        y_labels[y] = s;
    }

    cout << "\n\n\tTime\n\n";

    for (int y = 0; y < HEIGHT; y++) {
        cout << y_labels[y] << " ";  

        for (int x = 0; x < WIDTH; x++)
            cout << field[y][x];

        if (y == HEIGHT - 1) cout << ">";
        cout << "\n";
    }

    cout << string(LABEL_WIDTH + WIDTH - 5, ' ') << "Data volume\n";
    cout << "* = Splay Tree   + = std::map   X = Both\n";
    }

int main(int argc, char* argv[])
{
    if(argc < 2) return 1;

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
    for(const auto& pair : data) std_map.insert(pair);
    end = chrono::high_resolution_clock::now();
    long long std_time = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Pairs read: " << data.size() << endl;
    cout << "Unique keys(splay_map): " << splay_map.size() << endl;
    cout << "Unique keys(std::map): " << std_map.size() << endl;

    res.push_back({"Splay (file)", splay_time});
    res.push_back({"std::map (file)", std_time});

    cmp();
    print_time();
    print_graph();
}