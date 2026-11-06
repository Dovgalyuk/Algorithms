#include "bwa.h"
#include "vector.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

using namespace std;

typedef chrono::steady_clock Clock;

struct Entry {
    string key;
    string value;
};

typedef Vector<Entry> InputData;

int main(int argc, char **argv){
    if (argc != 2 && argc != 3) {
        cerr << "give filename and optional first container (0, 1, 2)\n";
        return 1;
    }

    int first = 0;
    if (argc == 3) {
        string argument = argv[2];
        if (argument != "0" && argument != "1" && argument != "2") {
            cerr << "wrong first container\n";
            return 1;
        }
        first = argument[0] - '0';
    }

    InputData data;
    ifstream input(argv[1]);
    if (!input) {
        cerr << "file failed to open\n";
        return 1;
    }

    Entry entry;
    while (input >> entry.key) {
        if (!(input >> entry.value)) {
            cerr << "cant read value\n";
            return 1;
        }
        data.resize(data.size() + 1);
        data.at(data.size() - 1) = entry;
    }
    if (!input.eof() || input.bad()) {
        cerr << "file read failed\n";
        return 1;
    }
    input.close();

    cout << "container,pairs,size,seconds\n";

    for (int step = 0; step < 3; step++) {
        int type = (first + step) % 3;
        BwaMap bwa;
        map<string, string> ordered;
        unordered_map<string, string> hashed;

        string name;
        if (type == 0) name = "BWA";
        if (type == 1) name = "map";
        if (type == 2) name = "unordered_map";

        size_t size = 0;
        auto start = Clock::now();

        for (size_t i = 0; i < data.size(); i++) {
            const Entry &pair = data.at(i);
            if (type == 0) {
                bwa.insert(pair.key, pair.value);
            } else if (type == 1) {
                ordered[pair.key] = pair.value;
            } else {
                hashed[pair.key] = pair.value;
            }
        }

        auto finish = Clock::now();
        double seconds =
            chrono::duration<double>(finish - start).count();

        if (type == 0) size = bwa.size();
        if (type == 1) size = ordered.size();
        if (type == 2) size = hashed.size();

        cout << name << ',' << data.size() << ','
             << size << ',' << seconds << '\n';
    }

    return 0;
}
