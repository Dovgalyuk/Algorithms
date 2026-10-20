#include "queue.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include "Board.h"

constexpr size_t BOARD_SIZE = 8;
constexpr int NO_PARENT = -1;

const int DR[8] = { -2, -2, -1, -1, 1, 1, 2, 2 };
const int DC[8] = { -1, 1, -2, 2, -2, 2, -1, 1 };

Board readBoard(std::ifstream& in)
{
	Board board(BOARD_SIZE, BOARD_SIZE);

	for (size_t r = 0; r < BOARD_SIZE; ++r) {
		for (size_t c = 0; c < BOARD_SIZE; ++c) {
			char ch;
			in >> ch;
			board.set(r, c, ch);
		}
	}

	return board;
}

void printBoard(const Board& board, std::ofstream& out)
{
	for (size_t r = 0; r < board.rows(); ++r) {
		for (size_t c = 0; c < board.cols(); ++c) {
			out << board.get(r, c);
		}
		out << '\n';
	}
}

bool isValid(const Board& board, int row, int col)
{
	return row >= 0 && row < (int)board.rows() && col >= 0 && col < (int)board.cols() && board.get(row, col) != '#';
}

size_t toIndex(const Board& board, int row, int col)
{
	return (size_t)row * board.cols() + (size_t)col;
}

int rowFromIndex(const Board& board, size_t index)
{
	return (int)(index / board.cols());
}

int colFromIndex(const Board& board, size_t index)
{
	return (int)(index % board.cols());
}

bool findStartAndEnd(const Board& board, size_t& startIdx, size_t& endIdx)
{
	bool foundK = false, foundE = false;
	for (size_t r = 0; r < board.rows(); ++r) {
		for (size_t c = 0; c < board.cols(); c++) {
			if (board.get(r, c) == 'K') { startIdx = toIndex(board, r, c); foundK = true; }
			if (board.get(r, c) == 'E') { endIdx = toIndex(board, r, c); foundE = true; }
		}
	}
	return foundK && foundE;
}

int expandWave(const Board& board, Queue& queue, Vector& distOwn, Vector& parentOwn, const Vector& distOther)
{
	if (queue.empty()) return -1;

	size_t current = (size_t)queue.get();
	queue.remove();

	int r = rowFromIndex(board, current);
	int c = colFromIndex(board, current);

	for (int k = 0; k < 8; ++k) {
		int nr = r + DR[k];
		int nc = c + DC[k];

		if (!isValid(board, nr, nc)) continue;

		size_t nidx = toIndex(board, nr, nc);

		if (distOwn.get(nidx) != -1) continue;

		distOwn.set(nidx, distOwn.get(current) + 1);
		parentOwn.set(nidx, (Data)current);
		queue.insert((Data)nidx);

		if (distOther.get(nidx) != -1) {
			return (int)nidx;
		}
	}

	return -1;
}

int bidirectionalBFS(const Board& board, size_t startIdx, size_t endIdx, Vector& parentK, Vector& parentE)
{
	size_t total = board.rows() * board.cols();

	Vector distK, distE;
	distK.resize(total);
	distE.resize(total);
	parentK.resize(total);
	parentE.resize(total);
	for (size_t i = 0; i < total; ++i) {
		distK.set(i, -1);
		distE.set(i, -1);
		parentK.set(i, NO_PARENT);
		parentE.set(i, NO_PARENT);
	}

	Queue queueK, queueE;
	queueK.insert((Data)startIdx);
	queueE.insert((Data)endIdx);
	distK.set(startIdx, 0);
	distE.set(endIdx, 0);

	if (startIdx == endIdx) return (int)startIdx;

	while (!queueK.empty() && !queueE.empty()) {
		int meeting = expandWave(board, queueK, distK, parentK, distE);
		if (meeting != -1) return meeting;

		meeting = expandWave(board, queueE, distE, parentE, distK);
		if (meeting != -1) return meeting;

	}

	return -1;
}

char encodeNumber(size_t n)
{
	if (n < 10) return (char)('0' + n);
	if (n < 36) return (char)('a' + (n - 10));
	return '?';
}

void markPath(Board& board, size_t startIdx, size_t endIdx, int meeting, const Vector& parentK, const Vector& parentE)
{
	Vector leftHalf;
	{
		size_t len = 0;
		size_t cur = (size_t)meeting;
		while (cur != startIdx) {
			cur = (size_t)parentK.get(cur);
			++len;
			if (len > board.rows() * board.cols()) break;
		}
		leftHalf.resize(len + 1);
		cur = (size_t)meeting;
		for (size_t i = len + 1; i > 0; --i) {
			leftHalf.set(i - 1, (Data)cur);
			cur = (size_t)parentK.get(cur);
		}
	}
	Vector rightHalf;
	{
		size_t len = 0;
		size_t cur = (size_t)meeting;
		while (cur != endIdx) {
			rightHalf.resize(len + 1);
			rightHalf.set(len, (Data)cur);
			++len;
			cur = (size_t)parentE.get(cur);
			if (len > board.rows() * board.cols()) break;
		}
		rightHalf.resize(len + 1);
		rightHalf.set(len, (Data)endIdx);
	}
	size_t number = 0;
	for (size_t i = 0; i < leftHalf.size(); ++i) {
		size_t idx = (size_t)leftHalf.get(i);
		int r = rowFromIndex(board, idx);
		int c = colFromIndex(board, idx);
		if (number <= 9)
			board.set(r, c, (char)('0' + number));
		++number;
	}
	for (size_t i = 1; i < rightHalf.size(); ++i) {
		size_t idx = (size_t)rightHalf.get(i);
		int r = rowFromIndex(board, idx);
		int c = colFromIndex(board, idx);
		board.set(r, c, encodeNumber(number));
		++number;
	}
}

int main(int argc, char* argv[])
{
	if (argc < 3) {
		std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
		return 1;
	}

	std::ifstream infile(argv[1]);
	if (!infile.is_open()) {
		std::cerr << "Cannot open input file " << argv[1] << std::endl;
		return 1;
	}

	Board board = readBoard(infile);

	size_t startIdx = 0, endIdx = 0;
	if (!findStartAndEnd(board, startIdx, endIdx)) {
		std::cerr << "No K or E found in board" << std::endl;
		return 1;
	}

	Vector parentK, parentE;
	int meeting = bidirectionalBFS(board, startIdx, endIdx, parentK, parentE);

	std::ofstream outfile(argv[2]);
	if (!outfile.is_open()) {
		std::cerr << "Cannot open output file " << argv[2] << std::endl;
		return 1;
	}
	if (meeting == -1) {
		outfile << "NO" << std::endl;
	}
	else {
		markPath(board, startIdx, endIdx, meeting, parentK, parentE);
		printBoard(board, outfile);
	}
	
	return 0;
}