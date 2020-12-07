#include "operators.h"

struct value_table_t {
    value_t value;
    unsigned int count_link;
};

bool executor(std::vector<byte_code_t> &);

value_t cast_to_type(token_t);
