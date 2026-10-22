#ifndef TOOLS_H
#define TOOLS_H

#include "array.h"
#include <fstream>

Array *array_create_and_read(std::ifstream &input);

#endif