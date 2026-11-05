#include "bwa.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

using namespace std;

typedef chrono::steady_clock Clock;

int main(int argc, char **argv){
    if (argc != 3) {
        cerr << "give filename and number of pairs\n";
        return 1;
    }

    try {
        string argument = argv[2];
        size_t pos = 0;
        long long number = stoll(argument, &pos);
        if (number <= 0 || pos != argument.size() ||
            static_cast<unsigned long long>(number) > numeric_limits<size_t>::max()) {
            cerr << "wrong number of pairs\n";
            return 1;
        }
        size_t expected = static_cast<size_t>(number);
        BwaMap map;
        string names[] = {"insert", "find", "erase"};

        // Each phase includes file reading and correctness checks.
        for (int phase = 0; phase < 3; phase++) {
            auto start = Clock::now();
            ifstream input(argv[1]);
            if (!input) {
                cerr << "file failed to open\n";
                return 1;
            }

            string key;
            string value;
            size_t count = 0;
            while (input >> key) {
                if (!(input >> value)) {
                    cerr << "cant read value\n";
                    return 1;
                }
                if (count == expected) {
                    cerr << "too many pairs\n";
                    return 1;
                }

                if (phase == 0) {
                    map.insert(key, value);
                } else if (phase == 1) {
                    const string *found = map.find(key);
                    if (found == nullptr || *found != value) {
                        cerr << "wrong value for key: " << key << '\n';
                        return 1;
                    }
                } else {
                    if (!map.erase(key) || map.find(key) != nullptr ||
                        map.size() != expected - count - 1) {
                        cerr << "erase failed for key: " << key << '\n';
                        return 1;
                    }
                }
                count++;
            }

            if (!input.eof() || input.bad()) {
                cerr << "file read failed\n";
                return 1;
            }
            if (count != expected) {
                cerr << "wrong number of pairs in file\n";
                return 1;
            }
            if (phase < 2 && map.size() != expected) {
                cerr << "wrong map size or duplicate keys\n";
                return 1;
            }
            if (phase == 2 && (map.size() != 0 || map.begin().valid())) {
                cerr << "map is not empty\n";
                return 1;
            }

            auto finish = Clock::now();
            double seconds = chrono::duration<double>(finish - start).count();
            cout << names[phase] << ": " << count << " pairs, "
                 << seconds << " seconds\n";
        }

        cout << "All stress tests passed\n";
    } catch (const exception &error) {
        cerr << error.what() << '\n';
        return 1;
    }
    return 0;
}
