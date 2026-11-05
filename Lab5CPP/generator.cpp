#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <stdexcept>

using namespace std;

int main(int argc, char **argv){
    if (argc != 3) {
        cerr << "need filename and number of pairs\n";
        return 1;
    }
    try {
        string argument = argv[2];
        size_t pos = 0;
        long long count = stoll(argument, &pos);
        if (count < 0 || pos != argument.size()) {
            cerr << "wrong number of pairs\n";
            return 1;
        }
        ofstream output(argv[1]);
        if (!output) {
            cerr << "file failed to open\n";
            return 1;
        }
        mt19937 random(53);
        for (long long i = 0; i < count; i++) {
            output << "key" << i << " value" << random() << '\n';
        }
        output.close();
        if (!output) {
            cerr << "file write failed\n";
            return 1;
        }
    } catch (const exception &error) {
        cerr << error.what() << '\n';
        return 1;
    }
    return 0;
}