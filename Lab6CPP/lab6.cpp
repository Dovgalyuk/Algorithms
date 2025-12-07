#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <map>
#include <climits>
#include <algorithm>
#include <cmath>

using namespace std;

struct Node 
{
    int left;
    int right;
    char op;
    long long val;
    bool is_leaf;
};

vector<Node> pool;

struct MinMax 
{
    long long mn;
    int mn_id;
    long long mx;
    int mx_id;
};

typedef pair<long long, string> RSol;
typedef RSol (*SolveF)();
typedef map<pair<int,int>, MinMax> DP;
typedef pair<RSol, long long> TRSol;

vector<int> nums;
vector<char> ops;

int make_node(int L, int R, char op, long long val) 
{
    pool.push_back({L, R, op, val, false});
    return pool.size() - 1;
}

int make_num(int x) 
{
    pool.push_back({-1, -1, '\0', x, true});
    return (int)pool.size() - 1;
}

string str(int id) 
{
    const Node &n = pool[id];
    if(n.is_leaf) return to_string(n.val);
    return "(" + str(n.left) + n.op + str(n.right) + ")";
}

void app_op(const MinMax& L, const MinMax& R, char op, MinMax& res)
{
    auto upd = [&](long long val, int id)
    {
        if(val < res.mn) { res.mn = val; res.mn_id = id; }
        if(val > res.mx) { res.mx = val; res.mx_id = id; }
    };

    switch (op) 
    {
            case '+': 
            {
                long long v1 = L.mn + R.mn;
                upd(v1, make_node(L.mn_id, R.mn_id, '+', v1));
                long long v2 = L.mx + R.mx;
                upd(v2, make_node(L.mx_id, R.mx_id, '+', v2));
                break;
            }
            case '-': 
            {
                long long v1 = L.mn - R.mx;
                upd(v1, make_node(L.mn_id, R.mx_id, '-', v1));
                long long v2 = L.mx - R.mn;
                upd(v2, make_node(L.mx_id, R.mn_id, '-', v2));
                break;
            }
            case '*': 
            {
                long long v1 = L.mn * R.mn;
                upd(v1, make_node(L.mn_id, R.mn_id, '*', v1));
                long long v2 = L.mn * R.mx;
                upd(v2, make_node(L.mn_id, R.mx_id, '*', v2));
                long long v3 = L.mx * R.mn;
                upd(v3, make_node(L.mx_id, R.mn_id, '*', v3));
                long long v4 = L.mx * R.mx;
                upd(v4, make_node(L.mx_id, R.mx_id, '*', v4));
                break;
            }
        }
}

MinMax solve(int l, int r) 
{
    if (l == r) 
    {
        int id = make_num(nums[l]);
        return {nums[l], id, nums[l], id};
    }

    MinMax res{LLONG_MAX, -1, LLONG_MIN, -1};

    for (int k = l; k < r; k++) 
    {
        MinMax L = solve(l, k);
        MinMax R = solve(k + 1, r);

        app_op(L, R, ops[k], res);
    }

    return res;
}

DP mem;

MinMax solDP(int l, int r) 
{
    auto key = make_pair(l, r);
    if (mem.count(key)) return mem[key];

    if (l == r) 
    {
        int id = make_num(nums[l]);
        return {nums[l], id, nums[l], id};
    }

    MinMax res{LLONG_MAX, -1, LLONG_MIN, -1};

    for (int k = l; k < r; k++) 
    {
        MinMax L = solDP(l, k);
        MinMax R = solDP(k + 1, r);

        app_op(L, R, ops[k], res);
    }

    return mem[key] = res;
}

string clean_expr(const string& s) 
{
    if (s.size() <= 1) return s;
    if (s.front() != '(' || s.back() != ')') return s;
    int d = 0;
    for (size_t i = 0; i < s.size()-1; i++) 
    {
        if (s[i] == '(') d++;
        if (s[i] == ')') d--;
        if (d == 0) return s;
    }
    return s.substr(1, s.size()-2);
}

void parse_expr(const string& s) 
{
    nums.clear();
    ops.clear();
    int n = 0;
    for (char c : s) 
    {
        if (isdigit(c)) n = n * 10 + (c - '0');
        else { nums.push_back(n); n = 0; ops.push_back(c); }
    }
    nums.push_back(n);
}

RSol run_solve_rec() 
{
    pool.clear();
    MinMax r = solve(0, nums.size()-1);
    string expr = str(r.mx_id);
    return { r.mx, clean_expr(expr) };
}

RSol run_dp() 
{
    pool.clear();
    mem.clear();
    MinMax r = solDP(0, nums.size() - 1);
    return { r.mx, clean_expr(str(r.mx_id)) };
}

TRSol meas_time(SolveF func)
{
    auto start = chrono::high_resolution_clock::now();
    RSol res = func();
    auto end = chrono::high_resolution_clock::now();
    long long time = chrono::duration_cast<chrono::microseconds>(end - start).count();
    return {res, time};
}

int size_to_x(long long size, long long minSize, long long maxSize, int WIDTH) 
{
    return 1 + int((size - minSize) * (WIDTH - 3) / double(maxSize - minSize));
}

int time_to_y(long long t, long long max_time, int HEIGHT) 
{
    int y = HEIGHT - 2 - int(t * (HEIGHT - 3) / double(max_time));
    if (y < 0) y = 0;
    if (y > HEIGHT - 1) y = HEIGHT - 1;
    return y;
}

void plot_series(const vector<long long>& sizes, const vector<long long>& times, char symbol,
                 vector<vector<char>>& field, long long minSize, long long maxSize,
                 long long max_time, int WIDTH, int HEIGHT) 
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

void print_graph(const vector<int>& sizes, const vector<long long>& times_sol,
                 const vector<long long>& times_dp) 
                 {
    const int WIDTH = 80;
    const int HEIGHT = 25;

    long long minSize = *min_element(sizes.begin(), sizes.end());
    long long maxSize = *max_element(sizes.begin(), sizes.end());

    long long max_time = *max_element(times_sol.begin(), times_sol.end());
    max_time = max(max_time, *max_element(times_dp.begin(), times_dp.end()));

    vector<vector<char>> field(HEIGHT, vector<char>(WIDTH, ' '));

    for (int x = 0; x < WIDTH; x++) field[HEIGHT-1][x] = '-';
    for (int y = 0; y < HEIGHT; y++) field[y][0] = '|';
    field[HEIGHT-1][0] = '+';

    plot_series(vector<long long>(sizes.begin(), sizes.end()), times_sol, '*',
                field, minSize, maxSize, max_time, WIDTH, HEIGHT);
    plot_series(vector<long long>(sizes.begin(), sizes.end()), times_dp, '+',
                field, minSize, maxSize, max_time, WIDTH, HEIGHT);

    const int y_labels = 4;
    for (int i = 0; i <= y_labels; i++) 
    {
        double fract = double(i) / y_labels;
        long long val = llround(max_time * (1.0 - fract));
        int y = int((HEIGHT - 2) * fract);
        if (y < 0) y = 0;
        if (y >= HEIGHT) y = HEIGHT - 1;
        string lab = to_string(val) + "us";
        for (size_t j = 0; j < lab.size() && 1 + j < (size_t)WIDTH; j++)
            field[y][1 + j] = lab[j];
    }

    for (size_t i = 0; i < sizes.size(); i++) 
    {
        int x = size_to_x(sizes[i], minSize, maxSize, WIDTH);
        string lab = to_string(sizes[i]);
        int start = x - lab.size() / 2;
        if (start < 1) start = 1;
        for (size_t j = 0; j < lab.size(); j++) 
        {
            int xx = start + j;
            if (xx >= 1 && xx < WIDTH) field[HEIGHT-1][xx] = lab[j];
        }
    }

    for (int y = 0; y < HEIGHT; y++) 
    {
        for (int x = 0; x < WIDTH; x++) cout << field[y][x];
        cout << "\n";
    }

    cout << "+ = SolDP, * = Sol, X = both\n";
}

int main(int argc, char** argv) 
{
    if(argc < 2) return 1;

    ifstream file(argv[1]);
    if(!file.is_open()) return 1;

    vector<string> exprs;
    string a;
    while(getline(file, a)) exprs.push_back(a);
    file.close();

    vector<int> sizes;
    vector<long long> times_sol;
    vector<long long> times_dp;

    for(const auto& e : exprs) 
    {
        parse_expr(e);
        sizes.push_back(nums.size());

        auto meas1 = meas_time(run_solve_rec);
        auto res1 = meas1.first;
        long long t1 = meas1.second;
        times_sol.push_back(t1);

        auto meas2 = meas_time(run_dp);
        auto res2 = meas2.first;
        long long t2 = meas2.second;
        times_dp.push_back(t2);

        cout << "Expr: " << e << "\n";
        cout << " Sol: " << res1.first << " = " << res1.second << " time = " << t1 << " us\n";
        cout << " SolDP: " << res2.first << " = " << res2.second << " time = " << t2 << " us\n";
        cout << "\n";
    }
    print_graph(sizes, times_sol, times_dp);
}
