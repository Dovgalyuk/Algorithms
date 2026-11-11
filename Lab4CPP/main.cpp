#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "floyd.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <input_file>\n";
		return 1;
	}

	ifstream input(argv[1]);
	if (!input.is_open()) {
		cerr << "Ошибка: невозможно открыть файл" << argv[1] << endl;
		return 1;
	}

	Graph<string, int> graph;
	try {
		if (!(input >> graph)) {
			throw runtime_error("Неправильный формат графа");
		}
	}
	catch (const exception& e) {
		cerr << "Ошибка чтения графа: " << e.what() << endl;
		return 1;
	}

	size_t n = graph.size();
	if (n == 0) {
		cout << "Граф пуст" << endl;
		return 0;
	}

	rastMatrix dist;
	nextMatrix next_versh;
	floyd_alg(graph, dist, next_versh);

	cout << "Матрица кратчайших расстояний: " << endl << endl;

	size_t col_width = 5;
	for (size_t i = 0; i < n; i++) {
		size_t len = graph.get_vershina_label(i).length();
		if (len > col_width) {
			col_width = len;
		}
	}
	col_width += 2;

	cout << setw(col_width) << " ";
	for (size_t j = 0; j < n; j++) {
		cout << setw(col_width) << graph.get_vershina_label(j);
	}
	cout << endl;

	for (size_t i = 0; i < n; i++) {
		cout << setw(col_width) << graph.get_vershina_label(i);
		for (size_t j = 0; j < n; j++) {
			if (dist[i][j] >= 1000000000000000LL) {
				cout << setw(col_width) << "INF";
			}
			else {
				cout << setw(col_width) << dist[i][j];
			}
		}
		cout << endl;
	}

	cout << "Кратчайшие маршруты между всеми парами вершин: " << endl << endl;

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			if (i == j) {
				continue;
			}
			cout << graph.get_vershina_label(i) << " -> " << graph.get_vershina_label(j) << ": ";

			if (dist[i][j] >= 1000000000000000LL) {
				cout << "no path" << endl;
			}
			else {
				Vector<size_t> path = vosstanovka_path(next_versh, i, j);
				for (size_t k = 0; k < path.size(); k++) {
					if (k > 0) {
						cout << " -> ";
					}
					cout << graph.get_vershina_label(path[k]);
				}
				cout << " (cost: " << dist[i][j] << ")" << endl;
			}
		}
	}
	return 0;
}
