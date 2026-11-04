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
		
		Vector<VershLabel> new_versh(new_rows * new_cols);
		Vector<bool> new_r_en(new_rows * new_cols);
		Vector<RebroLabel> new_r_w(new_rows * new_cols);
		Vector<bool> new_l_en(new_rows * new_cols);
		Vector<RebroLabel> new_l_w(new_rows * new_cols);
		Vector<bool> new_d_en(new_rows * new_cols);
		Vector<RebroLabel> new_d_w(new_rows * new_cols);
		Vector<bool> new_u_en(new_rows * new_cols);
		Vector<RebroLabel> new_u_w(new_rows * new_cols);


		size_t copy_rows = (new_rows < rows_gr) ? new_rows : rows_gr;
		size_t copy_cols = (new_cols < cols_gr) ? new_cols : cols_gr;

		for (size_t i = 0; i < copy_rows; i++) {
			for (size_t j = 0; j < copy_cols; j++) {
				size_t old_i = i * cols_gr + j;
				size_t new_i = i * new_cols + j;

				new_versh.set(new_i, versh_labels.get(old_i));
				
				new_r_en.set(new_i, r_enabled.get(old_i));
				new_r_w.set(new_i, r_weight.get(old_i));
				
				new_l_en.set(new_i, l_enabled.get(old_i));
				new_l_w.set(new_i, l_weight.get(old_i));

				new_d_en.set(new_i, d_enabled.get(old_i));
				new_d_w.set(new_i, d_weight.get(old_i));

				new_u_en.set(new_i, u_enabled.get(old_i));
				new_u_w.set(new_i, u_weight.get(old_i));
			}
		}

		rows_gr = new_rows;
		cols_gr = new_cols;
		versh_labels = move(new_versh);

		r_enabled = move(new_r_en);
		r_weight = move(new_r_w);
		l_enabled = move(new_l_en);
		l_weight = move(new_l_w);
		d_enabled = move(new_d_en);
		d_weight = move(new_d_w);
		u_enabled = move(new_u_en);
		u_weight = move(new_u_w);
	}

	void add_vershina(const VershLabel& label = VershLabel{}) {
		if (rows_gr == 0) {
			resize(1);
		}
		else if (cols_gr == 0) {
			resize(rows_gr + 1, 1);
		}
		else {
			if (rows_gr == 1) {
				resize(1, cols_gr + 1);
			}
			else {
				resize(rows_gr + 1, cols_gr);
			}
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

		size_t r1 = from / cols_gr;
		size_t c1 = from % cols_gr;

		size_t r2 = to / cols_gr;
		size_t c2 = to % cols_gr;

		if (r1 == r2) {
			if (c2 == c1 + 1) {
				r_enabled.set(from, true);
				r_weight.set(from, label);
			}
			else if (c2 == c1 - 1) {
				l_enabled.set(from, true);
				l_weight.set(from, label);
			}
		}
		else if (c1 == c2) {
			if (r2 == r1 + 1) {
				d_enabled.set(from, true);
				d_weight.set(from, label);
			}
			else if (r2 == r1 - 1) {
				u_enabled.set(from, true);
				u_weight.set(from, label);
			}
		}
	}

	void remove_rebro(size_t from, size_t to) {
		check_vershina(from);
		check_vershina(to);
		if (!sosedi_pos(from, to)) {
			return;
		}

		size_t r1 = from / cols_gr;
		size_t c1 = from % cols_gr;

		size_t r2 = to / cols_gr;
		size_t c2 = to % cols_gr;

		if (r1 == r2) {
			if (c2 == c1 + 1) {
				r_enabled.set(from, false);
			}
			else if (c2 == c1 - 1) {
				l_enabled.set(from, false);
			}
		}
		else if (c1 == c2) {
			if (r2 == r1 + 1) {
				d_enabled.set(from, false);
			}
			else if (r2 == r1 - 1) {
				u_enabled.set(from, false);
			}
		}
	}

	bool has_rebro(size_t from, size_t to) const {
		check_vershina(from);
		check_vershina(to);
		if (!sosedi_pos(from, to)) {
			return false;
		}

		size_t r1 = from / cols_gr;
		size_t c1 = from % cols_gr;

		size_t r2 = to / cols_gr;
		size_t c2 = to % cols_gr;

		if (r1 == r2) {
			if (c2 == c1 + 1) {
				return r_enabled.get(from);
			}
			if (c2 == c1 - 1) {
				return l_enabled.get(from);
			}
		}
		else if (c1 == c2) {
			if (r2 == r1 + 1) {
				return d_enabled.get(from);
			}
			if (r2 == r1 - 1) {
				return u_enabled.get(from);
			}
		}
		return false;
	}

	void set_rebro_label(size_t from, size_t to, const RebroLabel& label) {
		add_rebro(from, to, label);
	}

	RebroLabel get_rebro_label(size_t from, size_t to) const {
		check_vershina(from);
		check_vershina(to);

		if (!sosedi_pos(from, to)) {
			return RebroLabel();
		}
		size_t r1 = from / cols_gr;
		size_t c1 = from % cols_gr;

		size_t r2 = to / cols_gr;
		size_t c2 = to % cols_gr;

		if (r1 == r2) {
			if (c2 == c1 + 1) {
				return r_weight.get(from);
			}
			if (c2 == c1 - 1) {
				return l_weight.get(from);
			}
		}
		else if (c1 == c2) {
			if (r2 == r1 + 1) {
				return d_weight.get(from);
			}
			if (r2 == r1 - 1) {
				return u_weight.get(from);
			}
		}
		return RebroLabel();
	}

	void set_vershina_label(size_t index, const VershLabel& label) {
		check_vershina(index);
		versh_labels.set(index, label);
	}

	VershLabel get_vershina_label(size_t index) const {
		check_vershina(index);
		return versh_labels.get(index);
	}

	Vector<VershLabel> get_vse_versh_labels() const {
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

	private:

		const Graph* graph_gr;
		size_t vershina_gr;
		int dir_gr;
		size_t neighbor;

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
	Vector<VershLabel> versh_labels;
	Vector<RebroLabel> r_weight;
	Vector<RebroLabel> l_weight;
	Vector<RebroLabel> d_weight;
	Vector<RebroLabel> u_weight;

	Vector<bool> r_enabled;
	Vector<bool> l_enabled;
	Vector<bool> d_enabled;
	Vector<bool> u_enabled;

	void init_storage() {
		size_t total = rows_gr * cols_gr;
		versh_labels.resize(total);
		
		r_enabled.resize(total);
		r_weight.resize(total);
		l_enabled.resize(total);
		l_weight.resize(total);

		d_enabled.resize(total);
		d_weight.resize(total);
		u_enabled.resize(total);
		u_weight.resize(total);
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

		int dr = (int)r2 - (int)r1;
		int dc = (int)c2 - (int)c1;

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


//#ifndef TEMPLATE_DIRECTED_GRAPH_H
//#define TEMPLATE_DIRECTED_GRAPH_H
//
//#include "vector.h"
//#include <istream>
//#include <ostream>
//#include <stdexcept>
//#include <iterator>
//#include <cstddef>
//
//using namespace std;
//
//template <typename VershLabel, typename RebroLabel>
//class Graph {
//public:
//    Graph() : rows_(0), cols_(0) {}
//
//    explicit Graph(size_t kolvo_versh) : rows_(1), cols_(kolvo_versh) {
//        init_storage();
//    }
//
//    Graph(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
//        init_storage();
//    }
//
//    size_t size() const { return rows_ * cols_; }
//    size_t rows() const { return rows_; }
//    size_t cols() const { return cols_; }
//    bool empty() const { return size() == 0; }
//
//    void resize(size_t kolvo_versh) {
//        resize(1, kolvo_versh);
//    }
//
//    void resize(size_t new_rows, size_t new_cols) {
//        Vector<VershLabel> new_versh(new_rows * new_cols);
//        Vector<bool> new_r_en(new_rows * new_cols);
//        Vector<RebroLabel> new_r_w(new_rows * new_cols);
//        Vector<bool> new_l_en(new_rows * new_cols);
//        Vector<RebroLabel> new_l_w(new_rows * new_cols);
//        Vector<bool> new_d_en(new_rows * new_cols);
//        Vector<RebroLabel> new_d_w(new_rows * new_cols);
//        Vector<bool> new_u_en(new_rows * new_cols);
//        Vector<RebroLabel> new_u_w(new_rows * new_cols);
//
//        size_t copy_rows = (new_rows < rows_) ? new_rows : rows_;
//        size_t copy_cols = (new_cols < cols_) ? new_cols : cols_;
//
//        for (size_t i = 0; i < copy_rows; i++) {
//            for (size_t j = 0; j < copy_cols; j++) {
//                size_t old_i = i * cols_ + j;
//                size_t new_i = i * new_cols + j;
//
//                new_versh.set(new_i, versh_labels.get(old_i));
//                new_r_en.set(new_i, r_enabled.get(old_i));
//                new_r_w.set(new_i, r_weight.get(old_i));
//                new_l_en.set(new_i, l_enabled.get(old_i));
//                new_l_w.set(new_i, l_weight.get(old_i));
//                new_d_en.set(new_i, d_enabled.get(old_i));
//                new_d_w.set(new_i, d_weight.get(old_i));
//                new_u_en.set(new_i, u_enabled.get(old_i));
//                new_u_w.set(new_i, u_weight.get(old_i));
//            }
//        }
//
//        rows_ = new_rows;
//        cols_ = new_cols;
//        versh_labels = move(new_versh);
//        r_enabled = move(new_r_en);
//        r_weight = move(new_r_w);
//        l_enabled = move(new_l_en);
//        l_weight = move(new_l_w);
//        d_enabled = move(new_d_en);
//        d_weight = move(new_d_w);
//        u_enabled = move(new_u_en);
//        u_weight = move(new_u_w);
//    }
//
//    void add_vershina(const VershLabel& label = VershLabel{}) {
//        if (rows_ == 0) resize(1);
//        else if (cols_ == 0) resize(rows_ + 1, 1);
//        else {
//            if (rows_ == 1) resize(1, cols_ + 1);
//            else resize(rows_ + 1, cols_);
//        }
//    }
//
//    void remove_vershina(size_t index) {
//        check_vershina(index);
//        if (index != size() - 1) {
//            throw invalid_argument("Можно удалить только последнюю вершину графа");
//        }
//        if (rows_ == 1) resize(1, cols_ - 1);
//        else resize(rows_ - 1, cols_);
//    }
//
//    void add_rebro(size_t from, size_t to, const RebroLabel& label = RebroLabel{}) {
//        check_vershina(from);
//        check_vershina(to);
//        if (!sosedi_pos(from, to)) {
//            throw invalid_argument("Вершины не являются соседними");
//        }
//
//        size_t r1 = from / cols_, c1 = from % cols_;
//        size_t r2 = to / cols_, c2 = to % cols_;
//
//        if (r1 == r2) {
//            if (c2 == c1 + 1) { // право
//                r_enabled.set(from, true);
//                r_weight.set(from, label);
//            }
//            else if (c2 == c1 - 1) { // лево
//                l_enabled.set(from, true);
//                l_weight.set(from, label);
//            }
//        }
//        else if (c1 == c2) {
//            if (r2 == r1 + 1) { // низ
//                d_enabled.set(from, true);
//                d_weight.set(from, label);
//            }
//            else if (r2 == r1 - 1) { // верх
//                u_enabled.set(from, true);
//                u_weight.set(from, label);
//            }
//        }
//    }
//
//    void remove_rebro(size_t from, size_t to) {
//        check_vershina(from);
//        check_vershina(to);
//        if (!sosedi_pos(from, to)) return;
//
//        size_t r1 = from / cols_, c1 = from % cols_;
//        size_t r2 = to / cols_, c2 = to % cols_;
//
//        if (r1 == r2) {
//            if (c2 == c1 + 1) r_enabled.set(from, false);
//            else if (c2 == c1 - 1) l_enabled.set(from, false);
//        }
//        else if (c1 == c2) {
//            if (r2 == r1 + 1) d_enabled.set(from, false);
//            else if (r2 == r1 - 1) u_enabled.set(from, false);
//        }
//    }
//
//    bool has_rebro(size_t from, size_t to) const {
//        check_vershina(from);
//        check_vershina(to);
//        if (!sosedi_pos(from, to)) return false;
//
//        size_t r1 = from / cols_, c1 = from % cols_;
//        size_t r2 = to / cols_, c2 = to % cols_;
//
//        if (r1 == r2) {
//            if (c2 == c1 + 1) return r_enabled.get(from);
//            if (c2 == c1 - 1) return l_enabled.get(from);
//        }
//        else if (c1 == c2) {
//            if (r2 == r1 + 1) return d_enabled.get(from);
//            if (r2 == r1 - 1) return u_enabled.get(from);
//        }
//        return false;
//    }
//
//    void set_rebro_label(size_t from, size_t to, const RebroLabel& label) {
//        add_rebro(from, to, label);
//    }
//
//    RebroLabel get_rebro_label(size_t from, size_t to) const {
//        check_vershina(from);
//        check_vershina(to);
//        if (!sosedi_pos(from, to)) return RebroLabel();
//
//        size_t r1 = from / cols_, c1 = from % cols_;
//        size_t r2 = to / cols_, c2 = to % cols_;
//
//        if (r1 == r2) {
//            if (c2 == c1 + 1) return r_weight.get(from);
//            if (c2 == c1 - 1) return l_weight.get(from);
//        }
//        else if (c1 == c2) {
//            if (r2 == r1 + 1) return d_weight.get(from);
//            if (r2 == r1 - 1) return u_weight.get(from);
//        }
//        return RebroLabel();
//    }
//
//    void set_vershina_label(size_t index, const VershLabel& label) {
//        check_vershina(index);
//        versh_labels.set(index, label);
//    }
//
//    VershLabel get_vershina_label(size_t index) const {
//        check_vershina(index);
//        return versh_labels.get(index);
//    }
//
//    Vector<VershLabel> get_vse_versh_labels() const {
//        return versh_labels;
//    }
//
//    size_t poisk_vershina(const VershLabel& label) const {
//        for (size_t i = 0; i < size(); i++) {
//            if (versh_labels.get(i) == label) return i;
//        }
//        throw runtime_error("Вершина не найдена");
//    }
//
//    class NeighborIterator {
//    public:
//        using iterator_category = forward_iterator_tag;
//        using value_type = size_t;
//        using difference_type = ptrdiff_t;
//        using pointer = const size_t*;
//        using reference = size_t;
//
//        NeighborIterator(const Graph* graph, size_t vershina, int direction)
//            : graph_(graph), vershina_(vershina), dir_(direction) {
//            find_next();
//        }
//
//        size_t operator*() const { return neighbor_; }
//
//        NeighborIterator& operator++() {
//            dir_++;
//            find_next();
//            return *this;
//        }
//
//        NeighborIterator operator++(int) {
//            auto temp = *this;
//            ++(*this);
//            return temp;
//        }
//
//        bool operator==(const NeighborIterator& other) const {
//            return graph_ == other.graph_ && vershina_ == other.vershina_ && dir_ == other.dir_;
//        }
//
//        bool operator!=(const NeighborIterator& other) const {
//            return !(*this == other);
//        }
//
//    private:
//        const Graph* graph_;
//        size_t vershina_;
//        int dir_;
//        size_t neighbor_;
//
//        void find_next() {
//            while (dir_ < 4) {
//                if (graph_->try_get_neighbor(vershina_, dir_, neighbor_)) {
//                    if (graph_->has_rebro(vershina_, neighbor_)) return;
//                }
//                dir_++;
//            }
//        }
//    };
//
//    NeighborIterator begin(size_t vershina) const {
//        check_vershina(vershina);
//        return NeighborIterator(this, vershina, 0);
//    }
//
//    NeighborIterator end(size_t vershina) const {
//        check_vershina(vershina);
//        return NeighborIterator(this, vershina, 4);
//    }
//
//    friend istream& operator>>(istream& in, Graph& g) {
//        size_t r, c;
//        if (!(in >> r >> c)) return in;
//        g.resize(r, c);
//
//        for (size_t i = 0; i < g.size(); i++) {
//            VershLabel label;
//            if (!(in >> label)) return in;
//            g.set_vershina_label(i, label);
//        }
//
//        size_t rebra;
//        if (in >> rebra) {
//            for (size_t i = 0; i < rebra; i++) {
//                size_t from, to;
//                RebroLabel w;
//                if (!(in >> from >> to >> w)) return in;
//                g.add_rebro(from, to, w);
//            }
//        }
//        return in;
//    }
//
//private:
//    size_t rows_;
//    size_t cols_;
//    Vector<VershLabel> versh_labels;
//    Vector<bool> r_enabled, l_enabled, d_enabled, u_enabled;
//    Vector<RebroLabel> r_weight, l_weight, d_weight, u_weight;
//
//    void init_storage() {
//        size_t total = rows_ * cols_;
//        versh_labels.resize(total);
//        r_enabled.resize(total);
//        r_weight.resize(total);
//        l_enabled.resize(total);
//        l_weight.resize(total);
//        d_enabled.resize(total);
//        d_weight.resize(total);
//        u_enabled.resize(total);
//        u_weight.resize(total);
//    }
//
//    void check_vershina(size_t index) const {
//        if (index >= size()) throw out_of_range("Вершина находится за пределами");
//    }
//
//    bool sosedi_pos(size_t a, size_t b) const {
//        size_t r1 = a / cols_, c1 = a % cols_;
//        size_t r2 = b / cols_, c2 = b % cols_;
//
//        int dr = (int)r2 - (int)r1;
//        int dc = (int)c2 - (int)c1;
//
//        return (dr == 0 && (dc == 1 || dc == -1)) || (dc == 0 && (dr == 1 || dr == -1));
//    }
//
//    bool try_get_neighbor(size_t vershina, int dir, size_t& neighbor) const {
//        size_t r = vershina / cols_;
//        size_t c = vershina % cols_;
//
//        switch (dir) {
//        case 0: // лево
//            if (c == 0) return false;
//            neighbor = vershina - 1;
//            return true;
//        case 1: // право
//            if (c + 1 >= cols_) return false;
//            neighbor = vershina + 1;
//            return true;
//        case 2: // верх
//            if (r == 0) return false;
//            neighbor = vershina - cols_;
//            return true;
//        case 3: // низ
//            if (r + 1 >= rows_) return false;
//            neighbor = vershina + cols_;
//            return true;
//        }
//        return false;
//    }
//};
//
//#endif