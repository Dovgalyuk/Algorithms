#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename Data> class Vector {
public:
	Vector() :data_gr(nullptr), size_gr(0), capacity_gr(0) {
	}

	explicit Vector(size_t size) : data_gr(nullptr), size_gr(0), capacity_gr(0) {
		resize(size);
	}

	Vector(const Vector& a) : data_gr(nullptr), size_gr(0), capacity_gr(0) {
		if (a.size_gr > 0) {
			data_gr = new Data[a.size_gr];
			for (size_t i = 0; i < a.size_gr; i++) {
				data_gr[i] = a.data_gr[i];
			}
			size_gr = a.size_gr;
			capacity_gr = a.size_gr;
		}
	}

	Vector& operator=(const Vector& a) {

		if (this != &a) {
			Vector temp(a);
			swap(temp);
		}
		return *this;
	}

	~Vector() {
		delete[] data_gr;
	}

	Data get(size_t index) const {
		if (index >= size_gr) {
			return Data();
		}
		return data_gr[index];
	}

	void set(size_t index, Data value) {
		if (index >= size_gr) {
			return;
		}
		data_gr[index] = value;
	}

	Data& operator[](size_t index) {
		return data_gr[index];
	}

	const Data& operator[](size_t index) const {
		return data_gr[index];
	}


	size_t size() const {
		return size_gr;
	}

	void resize(size_t new_size) {
		if (new_size > capacity_gr) {
			size_t new_capacity = capacity_gr * 2;
			if (new_capacity < new_size) {
				new_capacity = new_size;
			}
			if (new_capacity == 0) {
				new_capacity = new_size;
			}

			Data* new_data = new Data[new_capacity];
			for (size_t i = 0; i < size_gr; i++) {
				new_data[i] = data_gr[i];
			}
			
			delete[] data_gr;
			data_gr = new_data;
			capacity_gr = new_capacity;
		}
		if (new_size > size_gr) {
			for (size_t i = size_gr; i < new_size; i++) {
				data_gr[i] = Data();
			}
		}

		size_gr = new_size;
	}
	void add(const Data& value) {
		resize(size_gr + 1);
		data_gr[size_gr - 1] = value;
	}

private:
	Data* data_gr;
	size_t size_gr;
	size_t capacity_gr;

	void swap(Vector& other) noexcept {
		using std::swap;
		swap(data_gr, other.data_gr);
		swap(size_gr, other.size_gr);
		swap(capacity_gr, other.capacity_gr);
	}
};

#endif 
