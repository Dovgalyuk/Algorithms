#include "custom_string.h"

#include <cstdio>
#include <stdexcept>

static int failures = 0;

static void check(bool condition, const char* name)
{
	if (!condition)
	{
		std::fprintf(stderr, "FAILED: %s\n", name);
		failures++;
	}
}

int main()
{
	String empty;
	check(empty.empty(), "default construction creates an empty string");
	check(empty.size() == 0, "empty string size");
	check(empty.c_str()[0] == '\0', "empty string is null terminated");

	String first("Hello");
	check(first.size() == 5, "construction from a C string");
	check(first == "Hello", "equality with a C string");

	String repeated(4, 'x');
	check(repeated == "xxxx", "construction from count and character");

	String copied(first);
	check(copied == first, "copy construction");
	copied[0] = 'J';
	check(first == "Hello" && copied == "Jello", "copy owns independent storage");

	String assigned;
	assigned = first;
	check(assigned == first, "copy assignment");
	assigned = assigned;
	check(assigned == "Hello", "self assignment");
	assigned = "world";
	check(assigned == "world", "assignment from a C string");

	String combined = first + String(" ") + String("world");
	check(combined == "Hello world", "concatenation operator");
	combined += String("!");
	combined += '?';
	check(combined == "Hello world!?", "concatenation assignment");

	String selfAppend("ab");
	selfAppend += selfAppend;
	check(selfAppend == "abab", "self concatenation");

	String aliasedAppend("abcdef");
	aliasedAppend.append(aliasedAppend.data() + 1, 3);
	check(aliasedAppend == "abcdefbcd", "append from an internal character range");

	String searched("abracadabra");
	check(searched.find("cada") == 4, "substring search");
	check(searched.find("abra", 1) == 7, "substring search with a start position");
	check(searched.find("missing") == String::npos, "substring search not found");
	check(searched.find("") == 0, "empty substring search");
	check(searched.find("a", searched.size() + 1) == String::npos, "search past the end");

	String part = searched.substr(3, 4);
	check(part == "acad", "substring copy");
	check(searched.copy() == searched, "explicit copy operation");

	check(String("abc").compare(String("abc")) == 0, "equal comparison");
	check(String("abc").compare(String("abd")) < 0, "less comparison");
	check(String("abd").compare(String("abc")) > 0, "greater comparison");
	check(String("abc") < String("abcd"), "relational operators");
	check(String("abc") != String("abd"), "inequality operator");

	String capacityTest("a");
	capacityTest.reserve(32);
	check(capacityTest.capacity() >= 32, "reserve capacity");
	capacityTest.resize(5, 'z');
	check(capacityTest == String("azzzz"), "resize with fill character");
	capacityTest.resize(2);
	check(capacityTest == "az", "resize smaller");
	capacityTest.clear();
	check(capacityTest.empty() && capacityTest.c_str()[0] == '\0', "clear");

	const char binaryData[] = { 'A', '\0', 'B' };
	String binary(binaryData, 3);
	check(binary.size() == 3, "length-aware construction");
	check(binary[0] == 'A' && binary[1] == '\0' && binary[2] == 'B', "embedded null character");
	check(binary.data()[3] == '\0', "terminator after embedded null character");

	bool indexException = false;
	try
	{
		static_cast<void>(first.at(first.size()));
	}
	catch (const std::out_of_range&)
	{
		indexException = true;
	}
	check(indexException, "checked indexing");

	bool substringException = false;
	try
	{
		static_cast<void>(first.substr(first.size() + 1));
	}
	catch (const std::out_of_range&)
	{
		substringException = true;
	}
	check(substringException, "invalid substring position");

	if (failures != 0)
	{
		std::fprintf(stderr, "%d string test(s) failed\n", failures);
		return 1;
	}

	return 0;
}
