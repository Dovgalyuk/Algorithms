#include <iostream>
#include <cassert>
#include <string>
#include "graph.h"

using namespace std;

int main() {
	cout << "Начало тестирования графа" << endl;

	Graph<string, int> g(3, 3);
	assert(g.rows() == 3);
	assert(g.cols() == 3);
	assert(g.size() == 9);
	
	cout << "Test 1 (Creation): Passed" << endl;

	string names[] = { "A", "B", "C", "D","E", "F", "G", "H", "I" };
	for (size_t i = 0; i < 9; i++) {
		g.set_vershina_label(i, names[i]);
	}

	assert(g.get_vershina_label(4) == "E");
	assert(g.poisk_vershina("F") == 5);
	cout << "Test 2: passed" << endl;

	g.add_rebro(4, 1, 10);
	g.add_rebro(4, 5, 20);
	g.add_rebro(4, 7, 30);
	g.add_rebro(4, 3, 40);

	assert(g.has_rebro(4, 1) == true);
	assert(g.get_rebro_label(4, 1) == 10);

	assert(g.has_rebro(1, 4) == false);

	try {
		g.add_rebro(4, 8, 50);
		assert(false);
	}
	catch (const invalid_argument&) {

	}
	cout << "Test 3: passed" << endl;


	size_t expected_neighbors[] = { 3,5,1,7 };
	int kolvo = 0;
	for (auto i = g.begin(4); i != g.end(4); i++) {
		assert(kolvo < 4);
		assert(*i == expected_neighbors[kolvo]);
		kolvo++;
	}
	assert(kolvo == 4);
	cout << "Test 4: passed" << endl;

	g.remove_rebro(4, 1);
	assert(g.has_rebro(4, 1) == false);

	kolvo = 0;
	for (auto i = g.begin(4); i != g.end(4); i++) {
		kolvo++;
	}
	assert(kolvo == 3);
	cout << "Test 5: passed" << endl;

	g.resize(4, 3);
	assert(g.rows() == 4);
	assert(g.cols () == 3);
	assert(g.size() == 12);

	assert(g.get_vershina_label(4) == "E");
	assert(g.has_rebro(4, 5) == true);
	
	cout << "Test 6: passed" << endl;
	cout << "All tests passed" << endl;

	return 0;
}