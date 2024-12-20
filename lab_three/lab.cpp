#include <iostream>
#include <fstream>
#include <string>
#include "../LibraryCPP/queue.h"

using namespace std;

main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <file_path>" << endl;
        return 1;
    }

    ifstream input(argv[1]);

    if (!input) {
        cout << "Opening error" <<  endl;
        return 1;
    }

    
}