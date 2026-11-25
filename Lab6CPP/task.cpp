#include <cstddef>
#include <cstdio>
#include <iterator>
#include <stdexcept>

#include "string_slice.h"
#include "vector.h"

static void preprocessStrongSuffix(const StringSlice& pattern, std::size_t* shift, std::size_t* borderPosition)
{
	const std::size_t length = pattern.size();
	std::size_t i = length;
	std::size_t j = length + 1;
	borderPosition[i] = j;

	while (i > 0)
	{
		while (j <= length && pattern[i - 1] != pattern[j - 1])
		{
			if (shift[j] == 0) {
				shift[j] = j - i;
			}
			j = borderPosition[j];
		}
		i--;
		j--;
		borderPosition[i] = j;
	}
}

static void preprocessCaseTwo(std::size_t length, std::size_t* shift, const std::size_t* borderPosition)
{
	std::size_t j = borderPosition[0];
	for (std::size_t i = 0; i <= length; i++)
	{
		if (shift[i] == 0) {
			shift[i] = j;
		}
		if (i == j) {
			j = borderPosition[j];
		}
	}
}

static void boyerMooreSearch(const StringSlice& text, const StringSlice& pattern, Vector<std::size_t>& matches)
{
	const std::size_t textLength = text.size();
	const std::size_t patternLength = pattern.size();

	if (patternLength == 0)
	{
		if (textLength == String::npos) {
			throw std::length_error("Text is too large");
		}
		matches.reserve(textLength + 1);
		for (std::size_t i = 0; i <= textLength; i++) {
			matches.push(i);
		}
		return;
	}

	if (patternLength > textLength) {
		return;
	}
	matches.reserve(textLength - patternLength + 1);

	if (patternLength == String::npos) {
		throw std::length_error("Pattern is too large");
	}
	const std::size_t tableLength = patternLength + 1;
	Vector<std::size_t> shift(tableLength);
	Vector<std::size_t> borderPosition(tableLength);

	preprocessStrongSuffix(pattern, &shift[0], &borderPosition[0]);
	preprocessCaseTwo(patternLength, &shift[0], &borderPosition[0]);

	std::size_t lastOccurrence[256];
	for (std::size_t i = 0; i < 256; i++) {
		lastOccurrence[i] = String::npos;
	}
	for (std::size_t i = 0; i < patternLength; i++) {
		lastOccurrence[static_cast<unsigned char>(pattern[i])] = i;
	}

	std::size_t alignment = 0;
	while (alignment <= textLength - patternLength)
	{
		std::size_t j = patternLength;
		while (j > 0 && pattern[j - 1] == text[alignment + j - 1]) {
			j--;
		}
		if (j == 0)
		{
			matches.push(alignment);
			const std::size_t movement = shift[0] == 0 ? 1 : shift[0];
			alignment += movement;
		}
		else
		{
			const std::size_t mismatchPosition = j - 1;
			const unsigned char mismatchedCharacter = static_cast<unsigned char>(text[alignment + mismatchPosition]);
			const std::size_t previousOccurrence = lastOccurrence[mismatchedCharacter];
			const std::size_t badCharacterShift = previousOccurrence == String::npos || previousOccurrence >= mismatchPosition
				? 1
				: mismatchPosition - previousOccurrence;
			const std::size_t goodSuffixShift = shift[j] == 0 ? 1 : shift[j];
			const std::size_t movement = badCharacterShift > goodSuffixShift ? badCharacterShift : goodSuffixShift;
			alignment += movement;
		}
	}

}

static bool readLine(std::FILE* file, String& line)
{
	line.clear();
	bool readAny = false;
	int value = 0;
	while ((value = std::fgetc(file)) != EOF)
	{
		readAny = true;
		if (value == '\n')
			break;
		line += static_cast<char>(value);
	}
	if (!readAny && value == EOF) {
		return false;
	}
	if (!line.empty() && line[line.size() - 1] == '\r') {
		line.resize(line.size() - 1);
	}
	return true;
}

static bool parseUnsigned(const String& line, std::size_t& value)
{
	value = 0;
	std::size_t i = 0;
	while (i < line.size() && (line[i] == ' ' || line[i] == '\t')) {
		i++;
	}
	if (i == line.size()) {
		return false;
	}
	for (; i < line.size(); i++)
	{
		if (line[i] < '0' || line[i] > '9') {
			return false;
		}
		const std::size_t digit = static_cast<std::size_t>(line[i] - '0');
		if (value > (String::npos - digit) / 10) {
			return false;
		}
		value = value * 10 + digit;
	}
	return true;
}

static void printPositions(const Vector<std::size_t>& positions)
{
	if (positions.size() == 0)
	{
		std::printf("-\n");
		return;
	}

	for (std::size_t i = 0; i < positions.size(); i++)
	{
		if (i != 0) {
			std::printf(" ");
		}
		std::printf("%zu", positions[i]);
	}
	std::printf("\n");
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::fprintf(stderr, "Usage: Lab6CPPTask <input_file>\n");
		return 1;
	}

	std::FILE* input = nullptr;

	if (fopen_s(&input, argv[1], "rb") != 0) {
		input = nullptr;
	}

	if (input == nullptr)
	{
		std::fprintf(stderr, "Cannot open input file: %s\n", argv[1]);
		return 1;
	}

	String countLine;
	std::size_t testCount = 0;
	if (!readLine(input, countLine) || !parseUnsigned(countLine, testCount))
	{
		std::fprintf(stderr, "Invalid test count\n");
		std::fclose(input);
		return 1;
	}

	for (std::size_t testIndex = 0; testIndex < testCount; testIndex++)
	{
		String textLine;
		String patternLine;
		if (!readLine(input, textLine) || !readLine(input, patternLine))
		{
			std::fprintf(stderr, "Incomplete test case %zu\n", testIndex + 1);
			std::fclose(input);
			return 1;
		}

		const String text(textLine);
		const String pattern(patternLine);
		const StringSlice textView(text);
		const StringSlice patternView(pattern);
		Vector<std::size_t> matches;
		boyerMooreSearch(textView, patternView, matches);
		printPositions(matches);
	}

	std::fclose(input);
	return 0;
}
