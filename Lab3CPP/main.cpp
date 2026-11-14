#include "labirint.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <input.txt> <output.txt>\n";
		return 1;
	}
	return reshenie_labirint(argv[1], argv[2]);
}