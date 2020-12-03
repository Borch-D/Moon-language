#ifndef MOON_PARSER_H
#define MOON_PARSER_H

#endif //MOON_PARSER_H

#include "expression_parse.h"

bool parse(const std::vector<token_t> &, std::vector<byte_code_t> &);

bool
operations(std::vector<token_t>::const_iterator &, main_value_t *);

void write_byte_code(std::vector<byte_code_t> &);
