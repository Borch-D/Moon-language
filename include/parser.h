#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

enum token {
    PLUS_TOKEN = 0,
    MINUS_TOKEN,
    MULTIPLY_TOKEN,
    DIV_TOKEN,
    ASSIGN_TOKEN,
    VAL_NAME_TOKEN,
    INT_TOKEN,
    FLOAT_TOKEN,
    L_BRACKET_TOKEN, // add in lexer
    R_BRACKET_TOKEN, // add in lexer
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

enum command_t {
    PUSH_C = 0,
    PUSH_V,
    IDENTIFIER,
    ASSIGMENT,
    SUM,
    SUB,
    MULTIPLY,
    DIV
};

struct byte_code_t {
    command_t command;
    const std::string *value;
};

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
