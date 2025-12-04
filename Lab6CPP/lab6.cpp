#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include <vector>
#include <map>
#include <climits>
#include <algorithm>

using namespace std;

struct Node 
{
    long long value;
    string expr;
};

struct DPNode 
{
    long long mn;
    string mn_expr;
    long long mx;
    string mx_expr;
};

typedef pair<long long,string>(*SolveF)(const string&);

typedef vector<Node> Result;
typedef pair<long long, string> RSol;

typedef map<pair<int,int>, DPNode> DP;
typedef pair<RSol, long long> TRSol;


vector<int> nums;
vector<char> ops;

Result solve(int l, int r) 
{
    if (l == r)
        return { { nums[l], to_string(nums[l]) } };

    Result res;

    for (int k = l; k < r; k++) 
    {
        auto left = solve(l, k);
        auto right = solve(k + 1, r);

        for (auto &a : left) 
        {
            for (auto &b : right)
            {
                long long val;
                if (ops[k] == '+') val = a.value + b.value;
                else if (ops[k] == '-') val = a.value - b.value;
                else val = a.value * b.value;

                res.push_back({ val, "(" + a.expr + ops[k] + b.expr + ")" });
            }
        }
    }

    return res;
}

DP mem;

DPNode solDP(int l, int r)
{
    auto key = make_pair(l, r);
    if (mem.count(key)) return mem[key];

    if (l == r) 
    {
        DPNode rn;
        rn.mn = rn.mx = nums[l];
        rn.mn_expr = rn.mx_expr = to_string(nums[l]);
        return mem[key] = rn;
    }

    long long cur_mn = LLONG_MAX;
    long long cur_mx = LLONG_MIN;
    string cur_mn_expr, cur_mx_expr;

    for (int k = l; k < r; k++)
    {
        DPNode L = solDP(l, k);
        DPNode R = solDP(k + 1, r);

        vector<pair<long long,string>> cand;

        switch (ops[k]) 
        {
            case '+':
                cand.push_back({L.mn + R.mn, "(" + L.mn_expr + "+" + R.mn_expr + ")"});
                cand.push_back({L.mx + R.mx, "(" + L.mx_expr + "+" + R.mx_expr + ")"});
                break;

            case '-':
                cand.push_back({L.mn - R.mx, "(" + L.mn_expr + "-" + R.mx_expr + ")"});
                cand.push_back({L.mx - R.mn, "(" + L.mx_expr + "-" + R.mn_expr + ")"});
                break;

            case '*': {
                cand.push_back({L.mn * R.mn, "(" + L.mn_expr + "*" + R.mn_expr + ")"});
                cand.push_back({L.mn * R.mx, "(" + L.mn_expr + "*" + R.mx_expr + ")"});
                cand.push_back({L.mx * R.mn, "(" + L.mx_expr + "*" + R.mn_expr + ")"});
                cand.push_back({L.mx * R.mx, "(" + L.mx_expr + "*" + R.mx_expr + ")"});
                break;
            }
        }

        for (auto &p : cand) 
        {
            long long v = p.first;
            const string &e = p.second;

            if (v < cur_mn || (v == cur_mn && e < cur_mn_expr)) 
            {
                cur_mn = v;
                cur_mn_expr = e;
            }
            if (v > cur_mx || (v == cur_mx && e < cur_mx_expr)) 
            {
                cur_mx = v;
                cur_mx_expr = e;
            }
        }
    }

    DPNode out;
    out.mn = cur_mn;
    out.mn_expr = cur_mn_expr;
    out.mx = cur_mx;
    out.mx_expr = cur_mx_expr;

    return mem[key] = out;
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
        if (d == 0)
            return s;
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
        if (isdigit(c))
            n = n * 10 + (c - '0');
        else
        {
            nums.push_back(n);
            n = 0;
            ops.push_back(c);
        }
    }
    nums.push_back(n);
}

RSol run_solve(const string& expr)
{
    parse_expr(expr);
    auto all = solve(0, nums.size()-1);

    long long best = LLONG_MIN;
    string best_expr;

    for (auto &r : all)
    {
        if (r.value > best || (r.value == best && r.expr < best_expr))
        {
            best = r.value;
            best_expr = r.expr;
        }
    }
    return { best, clean_expr(best_expr) };
}

RSol run_dp(const string& expr)
{
    parse_expr(expr);
    mem.clear();

    DPNode r = solDP(0, nums.size() - 1);
    return { r.mx, clean_expr(r.mx_expr) };
}

TRSol meas_time(SolveF func, const string& expr) 
{
    auto start = chrono::high_resolution_clock::now();
    RSol res = func(expr);
    auto end   = chrono::high_resolution_clock::now();
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
                 vector<vector<char>>& field, long long minSize, long long maxSize, long long max_time,
                 int WIDTH, int HEIGHT) 
{
    if (sizes.empty()) return;

    for (size_t i = 0; i < sizes.size(); i++) 
    {
        int x = size_to_x(sizes[i], minSize, maxSize, WIDTH);
        int y = time_to_y(times[i], max_time, HEIGHT);

        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) 
        {
            if (field[y][x] == ' ') field[y][x] = symbol;
            else if (field[y][x] != symbol && field[y][x] != 'X') field[y][x] = 'X';
        }

        if (i + 1 < sizes.size()) 
        {
            int x2 = size_to_x(sizes[i + 1], minSize, maxSize, WIDTH);
            long long t1 = times[i], t2 = times[i + 1];
            int dx = x2 - x;
            int steps = std::abs(dx);
            if (steps == 0) continue;

            for (int j = 1; j < steps; j++) 
            {
                int xi = x + (dx > 0 ? j : -j);
                double frac = j / double(steps);
                long long ti = llround(t1 + (t2 - t1) * frac);
                int yi = time_to_y(ti, max_time, HEIGHT);

                if (xi >= 0 && xi < WIDTH && yi >= 0 && yi < HEIGHT) 
                {
                    if (field[yi][xi] == ' ') field[yi][xi] = symbol;
                    else if (field[yi][xi] != symbol && field[yi][xi] != 'X') field[yi][xi] = 'X';
                }
            }
        }
    }
}

void print_graph(const vector<int>& sizes, const vector<long long>& times_sol, const vector<long long>& times_dp) 
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

    plot_series(vector<long long>(sizes.begin(), sizes.end()), times_sol, '*', field, minSize, maxSize, max_time, WIDTH, HEIGHT);
    plot_series(vector<long long>(sizes.begin(), sizes.end()), times_dp, '+', field, minSize, maxSize, max_time, WIDTH, HEIGHT);

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
            if (xx >= 1 && xx < WIDTH)
                field[HEIGHT-1][xx] = lab[j];
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
    while(getline(file, a))
        exprs.push_back(a);

    file.close();

    vector<int> sizes;
    vector<long long> times_sol;
    vector<long long> times_dp;

    for(const auto& e : exprs)
    {
        parse_expr(e);
        sizes.push_back(nums.size());

        auto meas1 = meas_time(run_solve, e);
        auto res1 = meas1.first;
        long long t1 = meas1.second;
        times_sol.push_back(t1);


        auto meas2 = meas_time(run_dp, e);
        auto res2 = meas2.first;
        long long t2 = meas2.second;

        times_dp.push_back(t2);

        cout << "Expr: " << e << "\n";
        cout << "  Sol: " << res1.first << " = " << res1.second << " time = " << t1 << " us\n";
        cout << "  SolDP: " << res2.first << " = " << res2.second << " time = " << t2 << " us\n";
        cout << "\n";
    }

    //На графиках для выражений с количеством операндов > 5-8
    //линия динамического программирования будет практически сливаться с осью X,
    //поскольку время работы DP имеет O(n^3) операций, а время полного перебора
    //растет экспоненциально и быстро уходит далеко за пределы графика.
    //Это демонстрирует преимущества DP-подхода для больших n.
    print_graph(sizes, times_sol, times_dp);

}
