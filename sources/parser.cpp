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
    if (begin_operation->token_key == VAL_NAME_TOKEN && (begin_operation + 1)->token_key == ASSIGN_TOKEN) {
        // если это присваивание
        begin_operation += 2;
        auto end_operation = std::find_if(begin_operation, mainValue->token_table->end(), isEndl);
        if (main_expression(begin_operation, end_operation, mainValue)) {
            mainValue->byte_code->push_back({IDENTIFIER, &*(begin_operation - 2)});
            mainValue->byte_code->push_back({ASSIGMENT});
            mainValue->val_name.emplace(*((begin_operation - 2)->token_value));
            begin_operation = end_operation;
            return true;
        }
    } else if (begin_operation->token_key == VAL_NAME_TOKEN && (begin_operation + 1)->token_key == L_S_BRACKET_TOKEN &&
               ((begin_operation + 2)->token_key == INT_TOKEN || (begin_operation + 2)->token_key == VAL_NAME_TOKEN) &&
               (begin_operation + 3)->token_key == R_S_BRACKET_TOKEN &&
               (begin_operation + 4)->token_key == ASSIGN_TOKEN) { // если это присваивание переменной массива
        auto end_operation = std::find_if(begin_operation, mainValue->token_table->end(), isEndl);
        if (main_expression(begin_operation + 5, end_operation, mainValue)) {
            if ((begin_operation + 2)->token_key == INT_TOKEN) {
                mainValue->byte_code->push_back({PUSH_C, &*(begin_operation + 2)});
            } else {
                mainValue->byte_code->push_back({IDENTIFIER, &*(begin_operation + 2)});
                mainValue->byte_code->push_back({PUSH_V});
            }
            mainValue->byte_code->push_back({IDENTIFIER, &*begin_operation});
            mainValue->byte_code->push_back({ACCESS});
            mainValue->byte_code->push_back({OVERWRITE});
            mainValue->val_name.emplace(*((begin_operation - 2)->token_value));
            begin_operation = end_operation;
            return true;
        }
    } else if (begin_operation->token_key == IF_TOKEN) { // если встретился if
        auto end_condition = std::find_if(begin_operation, mainValue->token_table->end(), isEndl);
        if (!main_expression(begin_operation + 1, end_condition, mainValue)) {
            return false;
        }
        mainValue->byte_code->push_back({SET_FLAG});
        begin_operation = end_condition;
        return true;
    } else if (begin_operation->token_key == L_F_BRACKET_TOKEN) {
        begin_operation++;
        mainValue->byte_code->push_back({JUMP_IN_END});
        mainValue->byte_code->push_back({START_BLOCK});
        return true;
    } else if (begin_operation->token_key == R_F_BRACKET_TOKEN) {
        begin_operation++;
        mainValue->byte_code->push_back({END_BLOCK});
        mainValue->byte_code->push_back({JUMP_IN_WHILE_LABEL});
        return true;
    } else if (begin_operation->token_key == ELSE_TOKEN) {
        begin_operation++;
        mainValue->byte_code->push_back({RESET_FLAG});
        return true;
    } else if (begin_operation->token_key == WHILE_TOKEN) { // если while
        auto end_condition = std::find_if(begin_operation, mainValue->token_table->end(), isEndl);
        mainValue->byte_code->push_back({WHILE_LABEL});
        if (!main_expression(begin_operation + 1, end_condition, mainValue)) {
            return false;
        }
        mainValue->byte_code->push_back({SET_FLAG});
        begin_operation = end_condition;
        return true;
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
            case 8: {
                std::cout << "LOGICAL_SUM" << std::endl;
                break;
            }
            case 9: {
                std::cout << "LOGICAL_MULTIPLY" << std::endl;
                break;
            }
            case 10: {
                std::cout << "COMPARE_LESS" << std::endl;
                break;
            }
            case 11: {
                std::cout << "COMPARE_LESS_EQUAL" << std::endl;
                break;
            }
            case 12: {
                std::cout << "COMPARE_MORE" << std::endl;
                break;
            }
            case 13: {
                std::cout << "COMPARE_MORE_EQUAL" << std::endl;
                break;
            }
            case 14: {
                std::cout << "COMPARE_EQUAL" << std::endl;
                break;
            }
            case 15: {
                std::cout << "COMPARE_NOT_EQUAL" << std::endl;
                break;
            }
            case 16: {
                std::cout << "OPEN_ARR" << std::endl;
                break;
            }
            case 17: {
                std::cout << "CLOSE_ARR" << std::endl;
                break;
            }
            case 18: {
                std::cout << "ACCESS" << std::endl;
                break;
            }
            case 19: {
                std::cout << "OVERWRITE" << std::endl;
                break;
            }
            case 20: {
                std::cout << "PUSH_A" << std::endl;
                break;
            }
            case 21: {
                std::cout << "START_BLOCK" << std::endl;
                break;
            }
            case 22: {
                std::cout << "END_BLOCK" << std::endl;
                break;
            }
            case 23: {
                std::cout << "SET_FLAG" << std::endl;
                break;
            }
            case 24: {
                std::cout << "JUMP_IN_END" << std::endl;
                break;
            }
            case 25: {
                std::cout << "RESET_FLAG" << std::endl;
                break;
            }
            case 26: {
                std::cout << "JUMP_IN_WHILE_LABEL" << std::endl;
                break;
            }
            case 27: {
                std::cout << "WHILE_LABEL" << std::endl;
                break;
            }
        }
    }
}
