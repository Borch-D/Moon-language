//
// Created by dmitriy on 03.12.2020.
//

#ifndef MOON_EXPRESSION_PARSE_H
#define MOON_EXPRESSION_PARSE_H

#endif //MOON_EXPRESSION_PARSE_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include "byte_code.h"

struct main_value_t {
    const std::vector<token_t> *token_table;
    std::vector<byte_code_t> *byte_code;
    std::set<std::string> val_name;
};

bool expression(std::vector<token_t>::const_iterator, std::vector<token_t>::const_iterator, main_value_t *);

bool terminal(std::vector<token_t>::const_iterator, std::vector<token_t>::const_iterator, main_value_t *);

bool multiply(std::vector<token_t>::const_iterator, std::vector<token_t>::const_iterator, main_value_t *);

bool isEndl(token_t);
