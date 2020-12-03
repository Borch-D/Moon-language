//
// Created by dmitriy on 03.12.2020.
//

#ifndef MOON_TOKEN_H
#define MOON_TOKEN_H

#endif //MOON_TOKEN_H

enum token {
    PLUS_TOKEN = 0,
    MINUS_TOKEN,
    MULTIPLY_TOKEN,
    DIV_TOKEN,
    ASSIGN_TOKEN,
    VAL_NAME_TOKEN,
    INT_TOKEN,
    FLOAT_TOKEN,
    ENDL_TOKEN,
    // STRING_TOKEN,
    ERROR_TOKEN
    // QUESTION_TOKEN,
    // COLON_TOKEN
};

struct token_t {
    token token_key;
    const std::string *token_value;
};
