#include "labirint.h"
#include "queue.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

using namespace std;

typedef vector<vector<int>> Labirint;
typedef vector<vector<bool>> Posetili;
typedef vector<vector<bool>> Pyt;
typedef pair<int, int> Kletka;
typedef vector<Kletka> Sosedi;
typedef vector<vector<Kletka>> IznKletki;



static Labirint chtenie_labirinta(const string& filename) {
	ifstream f(filename);
	if (!f) {
		throw runtime_error("Невозможно открыть файл");
	}

	Labirint labirint;
	string stroka;
	while (getline(f, stroka)) {
		if (stroka.empty()) {
			continue;
		}

		vector<int> row;
		istringstream iss(stroka);
		int chislo;
		while (iss >> chislo) {
			row.push_back(chislo);
		}
		if (!row.empty()) {
			labirint.push_back(row);
		}
	}
	return labirint;
}

static Sosedi get_sosednieKletki(const Labirint& labirint, int r, int c) {
	Sosedi result;
	int rows = (int)labirint.size();
	int seredina = rows / 2;

	if (c > 0) {
		result.push_back({ r, c - 1 });
	}
	

	if (r > 0) {
		int nr = r - 1;
		int nc = (r <= seredina) ? (c - 1) : (c + 1);
		if (nc >= 0 && nc < (int)labirint[nr].size()) {
			result.push_back({ nr,nc });
		}
	}

	if (c < (int)labirint[r].size() - 1) {
		result.push_back({ r, c + 1 });
	}

	if (r < rows - 1) {
		int nr = r + 1;
		int nc = (r < seredina) ? (c + 1) : (c - 1);
		if (nc >= 0 && nc < (int)labirint[nr].size()) {
			result.push_back({ nr,nc });
		}
	}
	return result;
}

static Pyt poisk_path(const Labirint& labirint) {
	int rows = (int)labirint.size();
	int seredina = rows / 2;
	
	int start_r = seredina;
	int start_c = 0;
	
	int finish_r = seredina;
	int finish_c = (int)labirint[seredina].size() - 1;

	Posetili visit(rows);
	IznKletki tochki(rows);

	for (int i = 0; i < rows; i++) {
		visit[i].assign(labirint[i].size(), false);
		tochki[i].assign(labirint[i].size(), { -1,-1 });
	}

	Queue* q = queue_create();
	queue_insert(q, start_r * 100 + start_c);
	visit[start_r][start_c] = true;

	while (!queue_empty(q)) {
		int znach = queue_get(q);
		queue_remove(q);

		int r = znach / 100;
		int c = znach % 100;

		if (r == finish_r && c == finish_c) {
			break;
		}

		for (auto& nb : get_sosednieKletki(labirint, r, c)) {
			int nr = nb.first;
			int nc = nb.second;

			if (!visit[nr][nc] && abs(labirint[nr][nc] - labirint[r][c]) == 1) {
				visit[nr][nc] = true;
				tochki[nr][nc] = { r,c };
				queue_insert(q, nr * 100 + nc);
			}
		}
	}
	queue_delete(q);

	Pyt path(rows);
	for (int i = 0; i < rows; i++) {
		path[i].assign(labirint[i].size(), false);
	}

	int r = finish_r;
	int c = finish_c;
	while (r != -1 && c != -1) {
		path[r][c] = true;
		auto p = tochki[r][c];
		r = p.first;
		c = p.second;
	}
	return path;
}

static void print_labirint(const Labirint& labirint, const Pyt& path, const string& filename) {

	ofstream f(filename);
	if (!f) {
		throw runtime_error("Невозможно открыть файл");
	}

	int max_dlina = 0;
	for (auto& row : labirint) {
		if ((int)row.size() > max_dlina) {
			max_dlina = (int)row.size();
		}
	}
	for (int i = 0; i < (int)labirint.size(); i++) {
		int ind = max_dlina - (int)labirint[i].size();
		for (int k = 0; k < ind; k++) {
			f << ' ';
		}

		for (int j = 0; j < (int)labirint[i].size(); j++) {
			if (j > 0) {
				f << ' ';
			}
			if (path[i][j]) {
				f << '#';
			}
			else {
				f << labirint[i][j];
			}
		}
		f << '\n';
	}
}

int reshenie_labirint(const char* input_file, const char* output_file) {
	try {
		auto labirint = chtenie_labirinta(input_file);
		auto path = poisk_path(labirint);
		print_labirint(labirint, path, output_file);
		return 0;
	}
	catch (const exception& e) {
		cerr << "Ошибка: " << e.what() << endl;
		return 1;
	}
}