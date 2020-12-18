//
// Created by dmitriy on 03.12.2020.
//

#ifndef MOON_TOKEN_H
#define MOON_TOKEN_H

enum token {
    PLUS_TOKEN = 0,
    MINUS_TOKEN,
    MULTIPLY_TOKEN,
    DIV_TOKEN,
    ASSIGN_TOKEN,
    VAL_NAME_TOKEN,
    INT_TOKEN,
    FLOAT_TOKEN,
    L_BRACKET_TOKEN,
    R_BRACKET_TOKEN,
    ENDL_TOKEN,
    STRING_TOKEN,
    LESS_TOKEN,
    LESS_EQUAL_TOKEN,
    MORE_TOKEN,
    MORE_EQUAL_TOKEN,
    EQUAL_TOKEN,
    NOT_EQUAL_TOKEN,
    LOGICAL_AND_TOKEN,
    LOGICAL_OR_TOKEN,
    BOOL_TOKEN,
    L_S_BRACKET_TOKEN,
    R_S_BRACKET_TOKEN,
    COMMA_TOKEN,
    ERROR_TOKEN
    // QUESTION_TOKEN,
    // COLON_TOKEN
};

struct token_t {
    token token_key;
    const std::string *token_value;
};

#endif //MOON_TOKEN_H

