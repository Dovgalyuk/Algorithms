#include "bwa.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

using namespace std;

typedef chrono::steady_clock Clock;

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

        size_t pairs = 0;
        size_t size = 0;
        string key;
        string value;

        auto start = Clock::now();

        ifstream input(argv[1]);
        if (!input) {
            cerr << "file failed to open\n";
            return 1;
        }

        while (input >> key) {
            if (!(input >> value)) {
                cerr << "cant read value\n";
                return 1;
            }

            if (type == 0) {
                bwa.insert(key, value);
            } else if (type == 1) {
                ordered[key] = value;
            } else {
                hashed[key] = value;
            }

            pairs++;
        }

        if (!input.eof() || input.bad()) {
            cerr << "file read failed\n";
            return 1;
        }

        auto finish = Clock::now();
        double seconds =
            chrono::duration<double>(finish - start).count();

        if (type == 0) size = bwa.size();
        if (type == 1) size = ordered.size();
        if (type == 2) size = hashed.size();

        cout << name << ',' << pairs << ','
             << size << ',' << seconds << '\n';
    }

    return 0;
}
