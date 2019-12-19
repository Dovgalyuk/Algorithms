#pragma once
#include "string"
typedef int Label;
struct Edge {
	Label mark;
	size_t to;
};
typedef Edge* Data;
