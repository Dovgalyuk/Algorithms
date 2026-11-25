#include "string_slice.h"

#include <cstdio>
#include <stdexcept>


static void check(bool condition, const char* name)
{
	if (!condition)
	{
		std::fprintf(stderr, "FAILED: %s\n", name);
		return 1;
	}
}

int main()
{
	String source("0123456789");
	StringSlice slice(source, 2, 5);

	check(slice.size() == 5, "slice length");
	check(slice == StringSlice("23456"), "slice points to the requested fragment");
	check(slice == String("23456") && String("23456") == slice, "mixed string and slice equality");
	check(slice == "23456" && "23456" == slice, "slice equality with C strings");
	check(slice < String("zzzzz") && String("00000") < slice, "mixed string and slice ordering");
	check(slice.data() == source.data() + 2, "slice does not allocate character storage");
	check(slice.c_str() == source.data() + 2, "slice returns a pointer to the source fragment");
	check(slice[0] == '2' && slice.at(4) == '6', "slice indexing");

	StringSlice part = slice.substr(1, 3);
	check(part == StringSlice("345"), "slice of a slice");
	check(part.data() == source.data() + 3, "nested slice keeps the source pointer");

	String ownedCopy = slice.copy();
	check(ownedCopy == "23456", "copy from a slice creates an owned string");
	check(ownedCopy.data() != slice.data(), "slice copy has independent storage");

	check(slice.find(StringSlice("45")) == 2, "substring search in a slice");
	check(slice.find(StringSlice("not")) == String::npos, "substring search not found in a slice");
	check(slice.find(StringSlice("")) == 0, "empty substring search in a slice");
	check(slice.find(StringSlice("34"), 2) == String::npos, "slice search starting position");

	check(StringSlice("abc").compare(StringSlice("abc")) == 0, "equal slice comparison");
	check(StringSlice("abc").compare(StringSlice("abd")) < 0, "less slice comparison");
	check(StringSlice("abd") > StringSlice("abc"), "slice relational operators");
	check(StringSlice("abc") != StringSlice("abcd"), "slice inequality");
	check(StringSlice("abc") != String("abcd") && String("abcd") != StringSlice("abc"), "mixed string and slice inequality");

	String concatenated = StringSlice("left") + StringSlice("right");
	check(concatenated == "leftright", "slice concatenation creates a string");
	check((String("prefix") + slice) == "prefix23456", "string and slice concatenation");
	check((part + String("suffix")) == "345suffix", "slice and string concatenation");
	check((part + "suffix") == "345suffix" && ("prefix" + part) == "prefix345", "slice and C string concatenation");

	StringSlice convertedSlice(source, 0, 3);
	String converted = convertedSlice;
	check(converted == "012", "conversion from slice to string");

	source[3] = 'X';
	check(part == StringSlice("X45"), "slice reflects changes in the source string");

	StringSlice empty;
	check(empty.empty() && empty.data()[0] == '\0', "default empty slice");
	check(StringSlice("abc", 0).empty(), "zero-length slice");

	bool indexException = false;
	try
	{
		static_cast<void>(slice.at(slice.size()));
	}
	catch (const std::out_of_range&)
	{
		indexException = true;
	}
	check(indexException, "checked slice indexing");

	bool positionException = false;
	try
	{
		static_cast<void>(StringSlice(source, source.size() + 1));
	}
	catch (const std::out_of_range&)
	{
		positionException = true;
	}
	check(positionException, "invalid slice position");

	return 0;
}
