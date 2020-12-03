#include "parser.h"

bool parse(const std::vector<token_t> &token_table, std::vector<byte_code_t> &byte_code) {
    if (token_table.empty()) {
        std::cout << "Token table is empty!" << std::endl;
        return false;
    }
    main_value_t mainValue = {&token_table, &byte_code};

    auto it = token_table.begin();
    while (it != token_table.end()) {
        if (it->token_key != ENDL_TOKEN) {
            if (!operations(it, &mainValue)) {
                std::cout << "Parse error!" << std::endl;
                return false;
            }
        }
        it++;
    }
    return true;
}

bool operations(std::vector<token_t>::const_iterator &begin_operation, main_value_t *mainValue) {
    if (begin_operation->token_key == VAL_NAME_TOKEN && (++begin_operation)->token_key == ASSIGN_TOKEN) {
        // если это присваивание
        begin_operation++;
        auto end_operation = std::find_if(begin_operation, mainValue->token_table->end(), isEndl);
        if (expression(begin_operation, end_operation, mainValue)) {
            mainValue->byte_code->push_back({IDENTIFIER, &*(begin_operation-2)});
            mainValue->byte_code->push_back({ASSIGMENT});
            mainValue->val_name.emplace(*((begin_operation-2)->token_value));
            begin_operation = end_operation;
            return true;
        }
    }
    return false;
}

bool expression(std::vector<token_t>::const_iterator begin, std::vector<token_t>::const_iterator end,
                main_value_t *mainValue) {
    if (begin == end) {
        std::cout << "Expression is empty!" << std::endl;
        return false;
    }
    auto end_term = begin;
    uint8_t l_bracket_count = 0;
    uint8_t r_bracket_count = 0;
    uint8_t term_number = 0;
    token sign = PLUS_TOKEN;
    while (end_term != end) {
        if (end_term->token_key == L_BRACKET_TOKEN) {
            l_bracket_count++;
        } else if (end_term->token_key == R_BRACKET_TOKEN) {
            r_bracket_count++;
        }
        if ((end_term->token_key == PLUS_TOKEN || end_term->token_key == MINUS_TOKEN) &&
            l_bracket_count == r_bracket_count) {
            if (!terminal(begin, end_term, mainValue)) {
                std::cout << "Terminal error!" << std::endl;
                return false;
            }
            term_number++;
            if (term_number >= 2) {
                if (sign == PLUS_TOKEN) {
                    mainValue->byte_code->push_back({SUM});
                } else {
                    mainValue->byte_code->push_back({SUB});
                }
            }
            sign = end_term->token_key;
            begin = end_term + 1;
        } else if (end_term + 1 == end && l_bracket_count == r_bracket_count) {
            if (!terminal(begin, end_term + 1, mainValue)) {
                std::cout << "Terminal error!" << std::endl;
                return false;
            }
            term_number++;
            if (term_number >= 2) {
                if (sign == PLUS_TOKEN) {
                    mainValue->byte_code->push_back({SUM});
                } else {
                    mainValue->byte_code->push_back({SUB});
                }
            }
            begin = end_term + 1;
        }
        end_term++;
    }
    return true;
}

bool terminal(std::vector<token_t>::const_iterator begin, std::vector<token_t>::const_iterator end,
              main_value_t *mainValue) {
    if (begin == end) {
        std::cout << "Terminal is empty!" << std::endl;
        return false;
    }
    auto end_mult = begin;
    uint8_t l_bracket_count = 0;
    uint8_t r_bracket_count = 0;
    uint8_t mult_number = 0;
    token sign = MULTIPLY_TOKEN;
    while (end_mult != end) {
        if (end_mult->token_key == L_BRACKET_TOKEN) {
            l_bracket_count++;
        } else if (end_mult->token_key == R_BRACKET_TOKEN) {
            r_bracket_count++;
        }
        if ((end_mult->token_key == MULTIPLY_TOKEN || end_mult->token_key == DIV_TOKEN) &&
            l_bracket_count == r_bracket_count) {
            if (!multiply(begin, end_mult, mainValue)) {
                std::cout << "Multiply error!" << std::endl;
                return false;
            }
            mult_number++;
            if (mult_number >= 2) {
                if (sign == MULTIPLY_TOKEN) {
                    mainValue->byte_code->push_back({MULTIPLY});
                } else {
                    mainValue->byte_code->push_back({DIV});
                }
            }
            sign = end_mult->token_key;
            begin = end_mult + 1;
        } else if (end_mult + 1 == end && l_bracket_count == r_bracket_count) {
            if (!multiply(begin, end_mult + 1, mainValue)) {
                std::cout << "Multiply error!" << std::endl;
                return false;
            }
            mult_number++;
            if (mult_number >= 2) {
                if (sign == MULTIPLY_TOKEN) {
                    mainValue->byte_code->push_back({MULTIPLY});
                } else {
                    mainValue->byte_code->push_back({DIV});
                }
            }
            begin = end_mult + 1;
        }
        end_mult++;
    }
    return true;
}

bool multiply(std::vector<token_t>::const_iterator begin, std::vector<token_t>::const_iterator end,
              main_value_t *mainValue) {
    if (begin == end) {
        std::cout << "Multiply is empty!" << std::endl;
        return false;
    }
    if (begin + 1 == end && begin->token_key == VAL_NAME_TOKEN) {
        if (mainValue->val_name.find(*(begin->token_value)) != mainValue->val_name.end()) {
            mainValue->byte_code->push_back({IDENTIFIER, &*begin});
            mainValue->byte_code->push_back({PUSH_V});
            return true;
        } else {
            std::cout << "Value " << *(begin->token_value) << " didn't declare!" << std::endl;
            return false;
        }
    } else if (begin + 1 == end && (begin->token_key == INT_TOKEN || begin->token_key == FLOAT_TOKEN)) {
        mainValue->byte_code->push_back({PUSH_C, &*begin});
        return true;
    } else if (begin->token_key == L_BRACKET_TOKEN && (end - 1)->token_key == R_BRACKET_TOKEN) {
        begin++;
        end--;
        if (expression(begin, end, mainValue)) {
            return true;
        }
    }
    return false;
}

bool isEndl(token_t t) {
    return t.token_key == ENDL_TOKEN;
}

void write_byte_code(std::vector<byte_code_t> &byte_code) {
    if (byte_code.empty()) {
        std::cout << "Byte code is empty!" << std::endl;
        return;
    }
    for (auto i : byte_code) {
        switch (i.command) {
            case 0: {
                std::cout << "PUSH_C " << *(i.value->token_value) << std::endl;
                break;
            }
            case 1: {
                std::cout << "PUSH_V" << std::endl;
                break;
            }
            case 2: {
                std::cout << "IDENTIFIER " << *(i.value->token_value) << std::endl;
                break;
            }
            case 3: {
                std::cout << "ASSIGMENT" << std::endl;
                break;
            }
            case 4: {
                std::cout << "SUM" << std::endl;
                break;
            }
            case 5: {
                std::cout << "SUB" << std::endl;
                break;
            }
            case 6: {
                std::cout << "MULTIPLY" << std::endl;
                break;
            }
            case 7: {
                std::cout << "DIV" << std::endl;
                break;
            }
        }
    }
}
