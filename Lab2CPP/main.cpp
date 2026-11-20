#include "beatnik.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <script.bt> <input.txt>\n";
		return 1;
	}
	return beatnik_start(argv[1], argv[2]);
}