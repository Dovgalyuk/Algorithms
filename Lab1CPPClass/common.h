#ifndef COMMON_H
#define COMMON_H

#include <fstream>
#include "array.h"

Array* array_create_and_read(std::ifstream& inFile);

#endif