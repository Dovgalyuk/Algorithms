#include "queue.h"
#include <fstream>

void appendLine(std::string line);
void process();
bool checkIsPointAccessible(Data p);
char getPointValue(Data p);
void Algorithm(std::ifstream &input);