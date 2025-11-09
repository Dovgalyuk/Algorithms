#pragma once
#include <iterator>
#include <memory>

template<class T>
class iterator {
public:
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = T*;
	using reference = T&;
	using iterator_category = std::random_access_iterator_tag;
	using iterator_concept = std::random_access_iterator_tag;

	iterator(pointer ptr) : ptr(ptr) {}

	constexpr iterator() noexcept : ptr(nullptr) {}

	reference operator*() const {
		return *ptr;
	}

	pointer operator->() const {
		return ptr;
	}

	iterator& operator++() {
		++ptr;
		return *this;
	}

	iterator operator++(int) {
		iterator tmp = *this;
		++(*this);
		return tmp;
	}

	iterator& operator--() {
		--ptr;
		return *this;
	}

	iterator operator--(int) {
		iterator tmp = *this;
		--(*this);
		return tmp;
	}

	iterator& operator+=(difference_type n) {
		ptr += n;
		return *this;
	}

	iterator operator+(difference_type n) const {
		return iterator(ptr + n);
	}

	friend iterator operator+(difference_type n, const iterator& it) {
		return it + n;
	}

	iterator& operator-=(difference_type n) {
		ptr -= n;
		return *this;
	}

	iterator operator-(difference_type n) const {
		return iterator(ptr - n);
	}

	difference_type operator-(const iterator& other) const {
		return ptr - other.ptr;
	}

	reference operator[](difference_type n) const {
		return *(ptr + n);
	}

	friend constexpr auto operator<=>(const iterator&, const iterator&) = default;

private:
	pointer ptr;
};
