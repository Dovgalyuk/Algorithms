#ifndef STRING_SET_H
#define STRING_SET_H

#include <string>

struct StringSet;

StringSet* string_set_create();

void string_set_delete(StringSet* set);

bool string_set_insert(StringSet* set, const std::string& value);

bool string_set_contains(const StringSet* set, const std::string& value);

bool string_set_erase(StringSet* set, const std::string& value);

#endif
