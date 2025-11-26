#include "rbtree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

vector<pair<string, string>> gen(int n) {
    vector<pair<string, string>> d;    
    random_device rd;
    mt19937 gen(rd());

    for (int i = 0; i < n; i++) {
        string k = "k" + to_string(gen() % 1000000);
        string v = "v" + to_string(i);
        d.push_back({ k, v });
    }
    return d;
}

void test() {
    RBTree t;
    string v;

    t.add("a", "1");
    t.add("b", "2");
    t.add("c", "3");

    if (t.get("a", v) && v == "1") cout << "+ add/get ok" << endl;

    t.del("b");
    if (!t.get("b", v)) cout << "+ del ok" << endl;

    if (t.count() == 2) cout << "+ size ok" << endl;
}

void speed() {
    vector<int> n = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };

    cout << "size | time" << endl;
    cout << "-----|-----" << endl;

    for (int s : n) {
        auto d = gen(s);

        auto start = chrono::high_resolution_clock::now();
        RBTree t;
        for (auto& p : d) t.add(p.first, p.second);
        auto end = chrono::high_resolution_clock::now();
        auto t1 = chrono::duration_cast<chrono::microseconds>(end - start);

        cout << s << " | " << t1.count() << endl;
    }
}

void comp() {
    vector<int> n = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };
    ofstream csv("performance.csv");
    csv << "Size,RBTree,std::map" << endl;

    cout << "size | rbt | map" << endl;
    cout << "-----|-----|-----" << endl;

    for (int s : n) {
        auto d = gen(s);

        auto s1 = chrono::high_resolution_clock::now();
        RBTree t;
        for (auto& p : d) t.add(p.first, p.second);
        auto e1 = chrono::high_resolution_clock::now();
        auto t1 = chrono::duration_cast<chrono::microseconds>(e1 - s1);

        auto s2 = chrono::high_resolution_clock::now();
        map<string, string> m;
        for (auto& p : d) m.insert({ p.first, p.second });      
        auto e2 = chrono::high_resolution_clock::now();
        auto t2 = chrono::duration_cast<chrono::microseconds>(e2 - s2);

        cout << s << " | " << t1.count() << " | " << t2.count() << endl;
        csv << s << "," << t1.count() << "," << t2.count() << endl;  
    }
    csv.close();   
}

void filetest(const string& fname) {
    ifstream f(fname);
    if (!f.is_open()) {
        cout << "no file: " << fname << endl;
        return;
    }

    RBTree t;
    string line;
    int c = 0;

    while (getline(f, line)) {
        istringstream ss(line);
        string k, v;
        if (ss >> k >> v) {
            t.add(k, v);
            c++;
        }
    }

    cout << "loaded: " << c << endl;
    cout << "size: " << t.count() << endl;

    string val;
    if (t.get("apple", val)) cout << "apple: " << val << endl;
    if (t.get("city", val)) cout << "city: " << val << endl;

    t.del("car");
    cout << "del car, size: " << t.count() << endl;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        filetest(argv[1]);
    }
    else {
        test();
        speed();
        comp();
    }
    return 0;
}