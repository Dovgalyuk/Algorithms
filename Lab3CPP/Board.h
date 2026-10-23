#ifndef BOARD_H
#define BOARD_H

#include <cstddef>

class Board
{
public:
	Board(size_t rows, size_t cols);

	Board(const Board& a);
	Board& operator=(const Board& a);
	~Board();

	char get(size_t row, size_t col) const;
	void set(size_t row, size_t col, char value);

	size_t rows() const;
	size_t cols() const;

private:
	char* data_;
	size_t rows_;
	size_t cols_;
};
#endif
