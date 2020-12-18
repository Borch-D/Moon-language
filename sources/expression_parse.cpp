//
// Created by dmitriy on 03.12.2020.
//

#include "expression_parse.h"

bool main_expression(std::vector<token_t>::const_iterator begin, std::vector<token_t>::const_iterator end,
                     main_value_t *mainValue) {
    if (begin == end) {
        std::cout << "Main expression is empty!" << std::endl;
        return false;
    }
    auto end_logical_term = begin;
    uint8_t l_bracket_count = 0;
    uint8_t r_bracket_count = 0;
    uint8_t l_s_bracket_count = 0;
    uint8_t r_s_bracket_count = 0;
    uint8_t term_number = 0;
    while (end_logical_term != end) {
        if (end_logical_term->token_key == L_BRACKET_TOKEN) {
            l_bracket_count++;
        } else if (end_logical_term->token_key == R_BRACKET_TOKEN) {
            r_bracket_count++;
        } else if (end_logical_term->token_key == L_S_BRACKET_TOKEN) {
            l_s_bracket_count++;
        } else if (end_logical_term->token_key == R_S_BRACKET_TOKEN) {
            r_s_bracket_count++;
        }
        if ((end_logical_term->token_key == LOGICAL_OR_TOKEN) &&
            l_bracket_count == r_bracket_count && l_s_bracket_count == r_s_bracket_count) {
            if (!logical_term_expression(begin, end_logical_term, mainValue)) {
                std::cout << "Terminal error!" << std::endl;
                return false;
            }
            term_number++;
            if (term_number >= 2) {
                mainValue->byte_code->push_back({LOGICAL_SUM});
            }
            begin = end_logical_term + 1;
        } else if (end_logical_term + 1 == end) {
            if (!logical_term_expression(begin, end_logical_term + 1, mainValue)) {
                std::cout << "Terminal error!" << std::endl;
                return false;
            }
            term_number++;
            if (term_number >= 2) {
                mainValue->byte_code->push_back({LOGICAL_SUM});
            }
            begin = end_logical_term + 1;
        }
        end_logical_term++;
    }
    return true;
}

bool
logical_term_expression(std::vector<token_t>::const_iterator begin, std::vector<token_t>::const_iterator end,
                        main_value_t *mainValue) {
    if (begin == end) {
        std::cout << "Logical term expression is empty!" << std::endl;
        return false;
    }
    auto end_bool_expr = begin;
    uint8_t l_bracket_count = 0;
    uint8_t r_bracket_count = 0;
    uint8_t l_s_bracket_count = 0;
    uint8_t r_s_bracket_count = 0;
    uint8_t bool_number = 0;
    while (end_bool_expr != end) {
        if (end_bool_expr->token_key == L_BRACKET_TOKEN) {
            l_bracket_count++;
        } else if (end_bool_expr->token_key == R_BRACKET_TOKEN) {
            r_bracket_count++;
        } else if (end_bool_expr->token_key == L_S_BRACKET_TOKEN) {
            l_s_bracket_count++;
        } else if (end_bool_expr->token_key == R_S_BRACKET_TOKEN) {
            r_s_bracket_count++;
        }
        if ((end_bool_expr->token_key == LOGICAL_AND_TOKEN) &&
            l_bracket_count == r_bracket_count && l_s_bracket_count == r_s_bracket_count) {
            if (!bool_expression(begin, end_bool_expr, mainValue)) {
                std::cout << "Terminal error!" << std::endl;
                return false;
            }
            bool_number++;
            if (bool_number >= 2) {
                mainValue->byte_code->push_back({LOGICAL_MULTIPLY});
            }
            begin = end_bool_expr + 1;
        } else if (end_bool_expr + 1 == end) {
            if (!bool_expression(begin, end_bool_expr + 1, mainValue)) {
                std::cout << "Terminal error!" << std::endl;
                return false;
            }
            bool_number++;
            if (bool_number >= 2) {
                mainValue->byte_code->push_back({LOGICAL_MULTIPLY});
            }
            begin = end_bool_expr + 1;
        }
        end_bool_expr++;
    }
    return true;
}

bool bool_expression(std::vector<token_t>::const_iterator begin, std::vector<token_t>::const_iterator end,
                     main_value_t *mainValue) {
    if (begin == end) {
        std::cout << "Bool expression is empty!" << std::endl;
        return false;
    }
    auto end_calc_expr = begin;
    uint8_t l_bracket_count = 0;
    uint8_t r_bracket_count = 0;
    uint8_t l_s_bracket_count = 0;
    uint8_t r_s_bracket_count = 0;
    uint8_t calc_number = 0;
    std::map<token, command_t> signs;
    signs.emplace(LESS_TOKEN, COMPARE_LESS);
    signs.emplace(LESS_EQUAL_TOKEN, COMPARE_LESS_EQUAL);
    signs.emplace(MORE_TOKEN, COMPARE_MORE);
    signs.emplace(MORE_EQUAL_TOKEN, COMPARE_MORE_EQUAL);
    signs.emplace(EQUAL_TOKEN, COMPARE_EQUAL);
    signs.emplace(NOT_EQUAL_TOKEN, COMPARE_NOT_EQUAL);
    token last_sign;
    while (end_calc_expr != end) {
        if (end_calc_expr->token_key == L_BRACKET_TOKEN) {
            l_bracket_count++;
        } else if (end_calc_expr->token_key == R_BRACKET_TOKEN) {
            r_bracket_count++;
        } else if (end_calc_expr->token_key == L_S_BRACKET_TOKEN) {
            l_s_bracket_count++;
        } else if (end_calc_expr->token_key == R_S_BRACKET_TOKEN) {
            r_s_bracket_count++;
        }
        if ((signs.find(end_calc_expr->token_key) != signs.end()) && l_bracket_count == r_bracket_count &&
            l_s_bracket_count == r_s_bracket_count) {
            if (!calculate_expression(begin, end_calc_expr, mainValue)) {
                std::cout << "Calculate expression error!" << std::endl;
                return false;
            }
            calc_number++;
            if (calc_number >= 2) {
                auto it = signs.find(last_sign);
                mainValue->byte_code->push_back({it->second});
            }
            last_sign = end_calc_expr->token_key;
            begin = end_calc_expr + 1;
        } else if (end_calc_expr + 1 == end) {
            if (!calculate_expression(begin, end_calc_expr + 1, mainValue)) {
                std::cout << "Terminal error!" << std::endl;
                return false;
            }
            calc_number++;
            if (calc_number >= 2) {
                auto it = signs.find(last_sign);
                mainValue->byte_code->push_back({it->second});
            }
            begin = end_calc_expr + 1;
        }
        end_calc_expr++;
    }
    return true;
}

bool calculate_expression(std::vector<token_t>::const_iterator begin, std::vector<token_t>::const_iterator end,
                          main_value_t *mainValue) {
    if (begin == end) {
        std::cout << "Calculate expression is empty!" << std::endl;
        return false;
    }
    auto end_term = begin;
    uint8_t l_bracket_count = 0;
    uint8_t r_bracket_count = 0;
    uint8_t l_s_bracket_count = 0;
    uint8_t r_s_bracket_count = 0;
    uint8_t term_number = 0;
    token sign = PLUS_TOKEN;
    while (end_term != end) {
        if (end_term->token_key == L_BRACKET_TOKEN) {
            l_bracket_count++;
        } else if (end_term->token_key == R_BRACKET_TOKEN) {
            r_bracket_count++;
        } else if (end_term->token_key == L_S_BRACKET_TOKEN) {
            l_s_bracket_count++;
        } else if (end_term->token_key == R_S_BRACKET_TOKEN) {
            r_s_bracket_count++;
        }
        if ((end_term->token_key == PLUS_TOKEN || end_term->token_key == MINUS_TOKEN) &&
            l_bracket_count == r_bracket_count && l_s_bracket_count == r_s_bracket_count) {
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
        } else if (end_term + 1 == end) {
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
    uint8_t l_s_bracket_count = 0;
    uint8_t r_s_bracket_count = 0;
    uint8_t mult_number = 0;
    token sign = MULTIPLY_TOKEN;
    while (end_mult != end) {
        if (end_mult->token_key == L_BRACKET_TOKEN) {
            l_bracket_count++;
        } else if (end_mult->token_key == R_BRACKET_TOKEN) {
            r_bracket_count++;
        } else if (end_mult->token_key == L_S_BRACKET_TOKEN) {
            l_s_bracket_count++;
        } else if (end_mult->token_key == R_S_BRACKET_TOKEN) {
            r_s_bracket_count++;
        }
        if ((end_mult->token_key == MULTIPLY_TOKEN || end_mult->token_key == DIV_TOKEN) &&
            l_bracket_count == r_bracket_count && l_s_bracket_count == r_s_bracket_count) {
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
        } else if (end_mult + 1 == end) {
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
    } else if (begin + 1 == end &&
               (begin->token_key == INT_TOKEN || begin->token_key == FLOAT_TOKEN || begin->token_key == STRING_TOKEN ||
                begin->token_key == BOOL_TOKEN)) {
        mainValue->byte_code->push_back({PUSH_C, &*begin});
        return true;
    } else if (begin->token_key == L_S_BRACKET_TOKEN && (end - 1)->token_key == R_S_BRACKET_TOKEN) {
        mainValue->byte_code->push_back({OPEN_ARR});
        if (array(begin + 1, end - 1, mainValue)) {
            mainValue->byte_code->push_back({CLOSE_ARR});
            return true;
        }
    } else if (begin->token_key == L_BRACKET_TOKEN && (end - 1)->token_key == R_BRACKET_TOKEN) {
        begin++;
        end--;
        if (main_expression(begin, end, mainValue)) {
            return true;
        }
    } else
        return false;
    return false;
}

bool array(std::vector<token_t>::const_iterator begin, std::vector<token_t>::const_iterator end,
           main_value_t *mainValue) {
    auto end_expr = begin;
    uint8_t l_s_bracket_count = 0;
    uint8_t r_s_bracket_count = 0;
    while (end_expr != end) {
        if (end_expr->token_key == L_S_BRACKET_TOKEN) {
            l_s_bracket_count++;
        } else if (end_expr->token_key == R_S_BRACKET_TOKEN) {
            r_s_bracket_count++;
        }
        if (end_expr->token_key == COMMA_TOKEN && l_s_bracket_count == r_s_bracket_count) {
            if (!main_expression(begin, end_expr, mainValue)) {
                return false;
            }
            begin = end_expr + 1;
        } else if (end_expr + 1 == end) {
            if (!main_expression(begin, end_expr + 1, mainValue)) {
                return false;
            }
        }
        end_expr++;
    }
    return true;
}
