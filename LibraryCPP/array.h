#ifndef ARRAY_H

#define ARRAY_H

#include <stdexcept>
using namespace std;

template<typename Data>

class Array {

public:

	explicit Array(size_t razmer) : razmer_el(razmer) {
		if (razmer == 0) {
			throw invalid_argument("–азмер массива должен быть больше 0");
		}
		uk_znach = new Data[razmer]();
	}

	Array(const Array& a) : razmer_el(a.razmer_el) {
		uk_znach = new Data[razmer_el];
		for (size_t i = 0; i < razmer_el; i++) {
			uk_znach[i] = a.uk_znach[i];
		}
	}

	Array& operator=(const Array& a) {
		if (this != &a) {
			Array kopy(a);
			swap(kopy);
		}
		return *this;
	}

	~Array() {
		delete[] uk_znach;
	}

	Data get(size_t ind) const {
		if (ind >= razmer_el) {
			throw out_of_range("ќшибка! Ёлемента с таким индексом не существует");
		}
		return uk_znach[ind];
	}

	void set(size_t ind, Data znachenie) {
		if (ind >= razmer_el) {
			throw out_of_range("ќшибка! Ёлемента с таким индексом не существует");
		}
		uk_znach[ind] = znachenie;
	}

	size_t size() const {
		return razmer_el;
	}

private:
	Data* uk_znach;
	size_t razmer_el;

	void swap(Array& zn) {
		std::swap(uk_znach, zn.uk_znach);
		std::swap(razmer_el, zn.razmer_el);
	}
};


#endif
