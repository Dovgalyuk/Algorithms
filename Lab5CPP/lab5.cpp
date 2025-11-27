#include "map.h"
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <climits>

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
    vector<size_t> sizes = {1000, 5000, 10000, 50000, 100000, 1000000, 5000000, 10000000};

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



int size_to_x(long long size, long long minSize, long long maxSize, int WIDTH) {
    return 1 + int((size - minSize) * (WIDTH - 3) / double(maxSize - minSize));
}

int time_to_y(long long t, long long max_time, int HEIGHT) {
    int y = HEIGHT - 2 - int(t * (HEIGHT - 3) / double(max_time));
    if (y < 0) y = 0;
    if (y > HEIGHT - 1) y = HEIGHT - 1;
    return y;
}

void plot_series(const vector<long long>& sizes, const vector<long long>& times, char symbol,
vector<vector<char>>& field, long long minSize, long long maxSize, long long max_time,
int WIDTH, int HEIGHT) 
{
    if (sizes.empty()) return;

    for (size_t i = 0; i < sizes.size(); i++) {
        int x = size_to_x(sizes[i], minSize, maxSize, WIDTH);
        int y = time_to_y(times[i], max_time, HEIGHT);

        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            if (field[y][x] == ' ') field[y][x] = symbol;

            else if (field[y][x] != symbol && field[y][x] != 'X') field[y][x] = 'X';
        }

        if (i + 1 < sizes.size()) {
            int x2 = size_to_x(sizes[i + 1], minSize, maxSize, WIDTH);
            long long t1 = times[i], t2 = times[i + 1];
            int dx = x2 - x;
            int steps = std::abs(dx);
            
            if (steps == 0) continue;
            
            for (int j = 1; j < steps; j++) {
                int xi = x + (dx > 0 ? j : -j);
                double frac = j / double(steps);
                long long ti = llround(t1 + (t2 - t1) * frac);
                int yi = time_to_y(ti, max_time, HEIGHT);
                
                if (xi >= 0 && xi < WIDTH && yi >= 0 && yi < HEIGHT) {
                    if (field[yi][xi] == ' ') field[yi][xi] = symbol;

                    else if (field[yi][xi] != symbol && field[yi][xi] != 'X') field[yi][xi] = 'X';
                }
            }
        }
    }
}

void print_graph() {
    vector<long long> sizes_splay, splay_times;
    vector<long long> sizes_std, std_times;

    for (auto& r : res) {
        if (r.l.find("(file)") != string::npos) continue;
        size_t start = r.l.find('(') + 1;
        size_t end = r.l.find(')');
        if (start != string::npos && end != string::npos && end > start) {
            long long size = stoll(r.l.substr(start, end - start));
            if (r.l.find("Splay") != string::npos) {
                sizes_splay.push_back(size);
                splay_times.push_back(r.time);
            } else if (r.l.find("std::map") != string::npos) {
                sizes_std.push_back(size);
                std_times.push_back(r.time);
            }
        }
    }

    if (sizes_splay.empty() && sizes_std.empty()) return;

    long long minSize = LLONG_MAX, maxSize = 0;

    for (auto s : sizes_splay) { minSize = min(minSize, s); maxSize = max(maxSize, s); }
    for (auto s : sizes_std) { minSize = min(minSize, s); maxSize = max(maxSize, s); }

    if (minSize == LLONG_MAX) minSize = 0;

    if (minSize == maxSize) maxSize = minSize + 1;

    long long max_time = 0;

    for (auto t : splay_times) max_time = max(max_time, t);

    for (auto t : std_times) max_time = max(max_time, t);

    if (max_time == 0) max_time = 1;

    const int WIDTH = 80;
    const int HEIGHT = 25;
    const int LABEL_WIDTH = 12;

    vector<vector<char>> field(HEIGHT, vector<char>(WIDTH, ' '));

    for (int x = 0; x < WIDTH; x++) field[HEIGHT-1][x] = '-';
    for (int y = 0; y < HEIGHT; y++) field[y][0] = '|';
    field[HEIGHT-1][0] = '+';

    plot_series(sizes_splay, splay_times, '*', field, minSize, maxSize, max_time, WIDTH, HEIGHT);
    plot_series(sizes_std, std_times, '+', field, minSize, maxSize, max_time, WIDTH, HEIGHT);

    long long step = 1000000;
    long long tickStart = (minSize + step - 1) / step * step;
    long long tickEnd = (maxSize) / step * step;

    for (long long t = tickStart; t <= tickEnd; t += step) {
        int x = size_to_x(t, minSize, maxSize, WIDTH);
        string label = to_string(t / 1000000) + "M";

        if (x + (int)label.size() < WIDTH) {
            for (size_t k = 0; k < label.size(); k++) field[HEIGHT-1][x + k] = label[k];
        }
    }

    vector<string> y_labels(HEIGHT, string(LABEL_WIDTH, ' '));
    vector<int> label_rows = {0, HEIGHT / 4, HEIGHT / 2, 3 * HEIGHT / 4, HEIGHT - 1};

    for (int y : label_rows) {
        long long tv = llround((HEIGHT - 1 - y) / double(HEIGHT - 1) * max_time);
        string s = to_string(tv) + " us";

        if ((int)s.size() < LABEL_WIDTH) s = string(LABEL_WIDTH - s.size(), ' ') + s;
        y_labels[y] = s;
    }

    cout << "\n\n\tTime\n\n";
    for (int y = 0; y < HEIGHT; y++) {
        cout << y_labels[y] << " ";

        for (int x = 0; x < WIDTH; x++) cout << field[y][x];
        
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

    for(const auto& pair : data) splay_map.insert(pair.first, pair.second);

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