#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include "byte_code.h"

union data_t {
    int val_int;
    float val_float;
};

struct value_t {
    token type;
    data_t data;

    void operator+=(const value_t &);
    void operator-=(const value_t &);
    void operator*=(const value_t &);
    void operator/=(const value_t &);
};

struct value_table_t {
    value_t value;
    unsigned int count_link;
};

bool executor(std::vector<byte_code_t> &);

value_t cast_to_type(token_t);
