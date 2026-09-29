#ifndef BEATNIK_H
#define BEATNIK_H

#include <cstddef>

int beatnik_start(const char* script_file, const char* input_file);

int beatnik_scrabble_ochki(char c);

int beatnik_word_ochki(const char* word);

bool beatnik_token(const char* text, char*** words_out, size_t* count_out);

void beatnik_osvobodit_pamyat(char** words, size_t count);


#endif 

