#include "Board.h"
#include <stdexcept>
#include <utility>

Board::Board(size_t rows, size_t cols) : data_(new char[rows * cols]), rows_(rows), cols_(cols)
{
	for (size_t i = 0; i < rows_ * cols_; ++i) {
		data_[i] = ' ';
	}
}

Board::Board(const Board& a) : data_(new char[a.rows_ * a.cols_]), rows_(a.rows_), cols_(a.cols_)
{
	for (size_t i = 0; i < rows_ * cols_; ++i)
		data_[i] = a.data_[i];
}

Board& Board::operator=(const Board& a)
{
    if (this == &a)
        return *this;

    Board temp(a);
    std::swap(data_, temp.data_);
    std::swap(rows_, temp.rows_);
    std::swap(cols_, temp.cols_);
    return *this;
}

Board::~Board()
{
    delete[] data_;
}

char Board::get(size_t row, size_t col) const
{
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("Board::get: index out of range");
    return data_[row * cols_ + col];
}

void Board::set(size_t row, size_t col, char value)
{
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("Board::set: index out of range");
    data_[row * cols_ + col] = value;
}

size_t Board::rows() const { return rows_; }
size_t Board::cols() const { return cols_; }
