#ifndef MOON_LEXER_H
#define MOON_LEXER_H

#endif //MOON_LEXER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include "token.h"


enum lexeme_t {
    LETTER_LEXEME = 0,
    ZERO_LEXEME,
    NUMERAL_LEXEME,
    UNDERSCORE_LEXEME,
    DOT_LEXEME,
    ERROR_LEXEME
};

enum val_name_state_t {
    LETTER_VAL_NAME = 0,
    NUMERAL_VAL_NAME,
    UNDERSCORE_VAL_NAME,
    ERROR_VAL_NAME
};

enum number_state_t {
    BEGIN_NUMBER = 0,
    ZERO_BEGIN,
    NUMERAL_BASIC_NUMBER,
    DOT_NUMBER,
    NUMERAL_FRACTIONAL_NUMBER,
    ERROR_NUMBER
};

void text_split_by_words(const std::string &, std::vector<std::string> &);

bool create_token_table(const std::vector<std::string> &, std::vector<token_t> &);

token get_token(const std::string &, const val_name_state_t [3][5], const number_state_t [5][5]);

lexeme_t get_lexeme(char);

void write_token_table(const std::vector<token_t> &);
