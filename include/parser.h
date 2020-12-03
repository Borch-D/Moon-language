#ifndef MOON_PARSER_H
#define MOON_PARSER_H

#endif //MOON_PARSER_H

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

bool parse(const std::vector<token_t> &, std::vector<byte_code_t> &);

bool
operations(std::vector<token_t>::const_iterator &, main_value_t *);

bool expression(std::vector<token_t>::const_iterator, std::vector<token_t>::const_iterator, main_value_t *);

bool terminal(std::vector<token_t>::const_iterator, std::vector<token_t>::const_iterator, main_value_t *);

bool multiply(std::vector<token_t>::const_iterator, std::vector<token_t>::const_iterator, main_value_t *);

bool isEndl(token_t);

void write_byte_code(std::vector<byte_code_t> &);
