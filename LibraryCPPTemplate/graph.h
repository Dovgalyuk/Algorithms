#ifndef TEMPLATE_DIRECTED_GRAPH_H
#define TEMPLATE_DIRECTED_GRAPH_H

#include "vector.h"
#include <istream>
#include <ostream>
#include <stdexcept>
#include <iterator>
#include <cstddef>
#include <utility>

using namespace std;

template <typename VershLabel, typename RebroLabel>

class Graph {

	typedef Vector<VershLabel> VershGr;

	struct elMatrGr {
		bool has_r = false;
		RebroLabel weight{};
	};

	typedef Vector<elMatrGr>elRow;
	typedef Vector<elRow> elMatrix;

public:

	Graph() : rows_gr(0), cols_gr(0) {}

	explicit Graph(size_t kolvo_versh) : rows_gr(1), cols_gr(kolvo_versh) {
		init_storage();
	}

	Graph(size_t rows, size_t cols) : rows_gr(rows), cols_gr(cols) {
		init_storage();
	}

	size_t size() const {
		return rows_gr * cols_gr;
	}

	size_t rows() const {
		return rows_gr;
	}

	size_t cols() const {
		return cols_gr;
	}

	bool empty() const {
		return size() == 0;
	}

	void resize(size_t kolvo_versh) {
		resize(1, kolvo_versh);
	}

	void resize(size_t new_rows, size_t new_cols) {

		size_t new_n = new_rows * new_cols;

		VershGr new_versh(new_n);
		elMatrix new_sm(new_n);
		for (size_t i = 0; i < new_n; i++) {
			new_sm[i].resize(new_n);
		}


		size_t copy_rows = (new_rows < rows_gr) ? new_rows : rows_gr;
		size_t copy_cols = (new_cols < cols_gr) ? new_cols : cols_gr;

		for (size_t old_i = 0; old_i < size(); old_i++) {
			size_t r = old_i / cols_gr;
			size_t c = old_i % cols_gr;
			if (r >= copy_rows || c >= copy_cols) {
				continue;
			}

			size_t new_i = r * new_cols + c;
			new_versh.set(new_i, versh_labels.get(old_i));

			for (size_t old_j = 0; old_j < size(); old_j++) {
				size_t rj = old_j / cols_gr;
				size_t cj = old_j % cols_gr;

				if (rj >= copy_rows || cj >= copy_cols) {
					continue;
				}
				size_t new_j = rj * new_cols + cj;
				new_sm[new_i].set(new_j, smejnost[old_i][old_j]);
			}
		}

		rows_gr = new_rows;
		cols_gr = new_cols;
		versh_labels = move(new_versh);
		smejnost = move(new_sm);
	}

	void add_vershina(const VershLabel& label = VershLabel{}) {
		size_t old_size = size();
		if (old_size == 0) {
			resize(1, 1);
		}
		else if (rows_gr == 1) {
			resize(1, cols_gr + 1);
		}
		else if (cols_gr == 1) {
			resize(rows_gr + 1, 1);
		}
		else {
			resize(rows_gr + 1, cols_gr);
		}

	}

	void remove_vershina(size_t index) {
		check_vershina(index);

		if (index != size() - 1) {
			throw invalid_argument("Можно удалить только последнюю вершину графа");
		}
		if (rows_gr == 1) {
			resize(1, cols_gr - 1);
		}
		else {
			resize(rows_gr - 1, cols_gr);
		}
	}

	void add_rebro(size_t from, size_t to, const RebroLabel& label = RebroLabel{}) {
		check_vershina(from);
		check_vershina(to);
		if (!sosedi_pos(from, to)) {
			throw invalid_argument("Вершины не являются соседними");
		}

		smejnost[from][to].has_r = true;
		smejnost[from][to].weight = label;
	}

	void remove_rebro(size_t from, size_t to) {
		check_vershina(from);
		check_vershina(to);
		if (!sosedi_pos(from, to)) {
			return;
		}
		smejnost[from][to].has_r = false;
	}

	bool has_rebro(size_t from, size_t to) const {
		check_vershina(from);
		check_vershina(to);
		if (!sosedi_pos(from, to)) {
			return false;
		}
		return smejnost[from][to].has_r;
	}

	void set_rebro_label(size_t from, size_t to, const RebroLabel& label) {
		add_rebro(from, to, label);
	}

	RebroLabel get_rebro_label(size_t from, size_t to) const {
		check_vershina(from);
		check_vershina(to);

		if (!sosedi_pos(from, to) || !smejnost[from][to].has_r) {
			return RebroLabel();
		}
		return smejnost[from][to].weight;
	}

	void set_vershina_label(size_t index, const VershLabel& label) {
		check_vershina(index);
		versh_labels.set(index, label);
	}

	VershLabel get_vershina_label(size_t index) const {
		check_vershina(index);
		return versh_labels.get(index);
	}

	VershGr get_vse_versh_labels() const {
		return versh_labels;
	}

	size_t poisk_vershina(const VershLabel& label) const {
		for (size_t i = 0; i < size(); i++) {
			if (versh_labels.get(i) == label) {
				return i;
			}
		}
		throw runtime_error("Вершина не найдена");
	}

	class NeighborIterator {
	public:
		using iterator_category = forward_iterator_tag;
		using value_type = size_t;
		using difference_type = ptrdiff_t;
		using pointer = const size_t*;
		using reference = size_t;

		NeighborIterator(const Graph* graph, size_t vershina, int direction) : graph_gr(graph), vershina_gr(vershina), dir_gr(direction) {
			find_next();
		}

		size_t operator*() const {
			return neighbor;
		}

		NeighborIterator& operator++() {
			dir_gr++;
			find_next();
			return *this;
		}

		NeighborIterator operator++(int) {
			auto temp = *this;
			++(*this);
			return temp;
		}

		bool operator==(const NeighborIterator& other) const {
			return graph_gr == other.graph_gr && vershina_gr == other.vershina_gr && dir_gr == other.dir_gr;
		}

		bool operator!=(const NeighborIterator& other) const {
			return !(*this == other);
		}

		RebroLabel label() const {
			return graph_gr->get_rebro_label(vershina_gr, neighbor);
		}

	private:

		const Graph* graph_gr;
		size_t vershina_gr;
		int dir_gr;
		size_t neighbor{};

		void find_next() {
			while (dir_gr < 4) {
				if (graph_gr->try_get_neighbor(vershina_gr, dir_gr, neighbor)) {
					if (graph_gr->has_rebro(vershina_gr, neighbor)) {
						return;
					}
				}
				dir_gr++;
			}
		}
	};

	NeighborIterator begin(size_t vershina) const {
		check_vershina(vershina);
		return NeighborIterator(this, vershina, 0);
	}

	NeighborIterator end(size_t vershina) const {
		check_vershina(vershina);
		return NeighborIterator(this, vershina, 4);
	}

	friend istream& operator>>(istream& in, Graph& g) {
		size_t rows;
		size_t cols;

		if (!(in >> rows >> cols)) {
			return in;
		}
		g.resize(rows, cols);

		for (size_t i = 0; i < g.size(); i++) {
			VershLabel label;
			if (!(in >> label)) {
				return in;
			}
			g.set_vershina_label(i, label);
		}

		size_t rebra;
		if (in >> rebra) {
			for (size_t i = 0; i < rebra; i++) {
				size_t from;
				size_t to;
				RebroLabel w;
				if (!(in >> from >> to >> w)) {
					return in;
				}
				g.add_rebro(from, to, w);
			}
		}
		return in;
	}
private:
	size_t rows_gr;
	size_t cols_gr;
	VershGr versh_labels;
	elMatrix smejnost;

	void init_storage() {
		size_t total = rows_gr * cols_gr;
		versh_labels.resize(total);
		smejnost.resize(total);
		for (size_t i = 0; i < total; i++) {
			smejnost[i].resize(total);
		}
	}
	void check_vershina(size_t index) const {
		if (index >= size()) {
			throw out_of_range("Вершина находится за пределами");
		}
	}
	bool sosedi_pos(size_t a, size_t b) const {
		size_t r1 = a / cols_gr;
		size_t c1 = a % cols_gr;
		size_t r2 = b / cols_gr;
		size_t c2 = b % cols_gr;

		int dr = static_cast<int>(r2) - static_cast<int>(r1);
		int dc = static_cast<int>(c2) - static_cast<int>(c1);

		return(dr == 0 && (dc == 1 || dc == -1)) || (dc == 0 && (dr == 1 || dr == -1));
	}

	bool try_get_neighbor(size_t vershina, int dir, size_t& neighbor) const {
		size_t r = vershina / cols_gr;
		size_t c = vershina % cols_gr;

		switch (dir) {
		case 0:
			if (c == 0) {
				return false;
			}
			neighbor = vershina - 1;
			return true;
		case 1:
			if (c + 1 >= cols_gr) {
				return false;
			}
			neighbor = vershina + 1;
			return true;
		case 2:
			if (r == 0) {
				return false;
			}
			neighbor = vershina - cols_gr;
			return true;
		case 3:
			if (r + 1 >= rows_gr) {
				return false;
			}
			neighbor = vershina + cols_gr;
			return true;
		}
		return false;
	}
};


#endif 